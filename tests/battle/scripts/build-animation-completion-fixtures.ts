/** Animation-only fixture: real battles, unchanged scripts/assets, inert move effects. */
import { createHash } from "node:crypto";
import { pokewebFile } from "./pokeweb-dependency";
import { mkdir, readFile, writeFile } from "node:fs/promises";
import { basename, resolve } from "node:path";
import expansion from "@pokeweb/assets/data/white2upgradeMoveExpansion.json";
import { NintendoDSRom } from "@pokeweb/nds/rom";
import { exportModifiedRom } from "@pokeweb/pokeweb/exportRom";
import { loadProjectFromRomBytes } from "@pokeweb/pokeweb/loader";
import { configureHarnessRuntime, patchHarnessSave, patchHarnessTrainer, validateHarnessRom } from "@pokeweb/pokeweb/battleHarness";
import { prepareBw2TestBattleCodeInjection, stageCodeInjectionDll } from "@pokeweb/pokeweb/pmcModel";
import { getTestBattleConfig, isTestBattleSaveMoveAnimationsEnabled, patchTestBattleSaveMoveAnimations, rawSaveBytesFromDesmumeDsv } from "@pokeweb/pokeweb/testBattle";
import { decompileMoveAnimationBytes, getMoveAnimationTargetInfo } from "@pokeweb/pokeweb/moveAnimationModel";
import { markDirty } from "@pokeweb/pokeweb/projectStore";

const args = new Map<string,string>();
for(let i=2;i<process.argv.length;i+=2) {
  const key=process.argv[i], value=process.argv[i+1];
  if(!["--rom","--save","--out"].includes(key)||!value||args.has(key)) throw new Error("Expected --rom INPUT --save INPUT --out NEW_DIRECTORY");
  args.set(key,value);
}
if(args.size!==3) throw new Error("Expected --rom INPUT --save INPUT --out NEW_DIRECTORY");
const directory=resolve(args.get("--out")!);
await mkdir(directory);
await writeFile(resolve(directory,".gitignore"),"*\n",{flag:"wx"});
const hash=(data:Uint8Array)=>createHash("sha256").update(data).digest("hex");
const bytes=new Uint8Array(await readFile(resolve(args.get("--rom")!)));
const originalSave=new Uint8Array(await readFile(resolve(args.get("--save")!)));
const rom=new NintendoDSRom(bytes,{fileData:"view"});
validateHarnessRom(rom);
globalThis.fetch=(async(request:RequestInfo|URL)=>{
  const url=new URL(request instanceof Request?request.url:String(request));
  if(url.protocol!=="file:") throw new Error("Only bundled local assets are permitted");
  return new Response(new Uint8Array(await readFile(url)));
}) as typeof fetch;
const project=await loadProjectFromRomBytes(bytes,basename(args.get("--rom")!),{selectedNarcs:["message_texts","personal","moves","trdata","trpok","move_animations","battle_animations"]});
const cases=expansion.moves.flatMap((move,index)=>move.sourceId>=744&&move.sourceId<=919 ? [{sourceMoveId:move.sourceId,moveId:expansion.firstTargetMoveId+index,name:move.name}] : []);
const moves=project.narcs.moves!;
if(moves.rawFiles.length<1000) throw new Error("Expected the Pokeweb expanded move-ID layout");
const animations=[];
await mkdir(resolve(directory,"scripts"));
for(const entry of cases) {
  const target=getMoveAnimationTargetInfo(project,entry.moveId);
  if(!target) throw new Error(`Missing animation target for ${entry.name}`);
  const data=project.narcs[target.storeName]!.rawFiles[target.index];
  if(!data?.length) throw new Error(`Missing animation bytes for ${entry.name}`);
  const script=decompileMoveAnimationBytes(data);
  await writeFile(resolve(directory,`scripts/${entry.sourceMoveId}.s`),script,{flag:"wx"});
  animations.push({...entry,scriptBytes:data.length,scriptSha256:hash(data),animationTarget:target});
  // Test animation lifecycle independently of unavailable custom handlers,
  // prerequisites, immunity, recharge, recoil and multi-hit damage. Keep the
  // original animation ID and bytes; use retail Tackle's one-target executor.
  moves.rawFiles[entry.moveId]=moves.rawFiles[33].slice();
  moves.rawFiles[entry.moveId][3]=1; // Power 1 avoids either side fainting.
  moves.rawFiles[entry.moveId][4]=101; // Always-hit native encoding.
  markDirty(project,"moves",entry.moveId);
}
patchHarnessTrainer(project,{trainerId:1,battleType:"Singles",trainer:{ai:0,team:[{speciesId:143,level:50,moves:[150],abilityId:50}]}});
const config=getTestBattleConfig("BW2");
const save=patchTestBattleSaveMoveAnimations(patchHarnessSave(rawSaveBytesFromDesmumeDsv(originalSave),project,{trainerId:1,player:{team:[{speciesId:151,level:50,abilityId:99,moves:[animations.find(x=>x.sourceMoveId===780)!.moveId,33,150,182]}]}}),config,true);
for(const half of [0,config.saveLayout.saveHalfOffset]) if(!isTestBattleSaveMoveAnimationsEnabled(save,config,half)) throw new Error("Battle Scene must be On in both save halves");
const template=new Uint8Array(await readFile(pokewebFile("src/assets/testbattle/BattleHarnessW2.dll")));
const receipt=JSON.parse(await readFile(pokewebFile("src/assets/testbattle/BattleHarnessW2.json"),"utf8"));
if(hash(template)!==receipt.dllSha256) throw new Error("Stale battle harness receipt");
await prepareBw2TestBattleCodeInjection(project);
stageCodeInjectionDll(project,"BattleHarnessW2.dll",configureHarnessRuntime(template,1,0));
const probes=[
  {name:"command",overlay:167,address:0x021cef18,signature:"38b50c1c051c2068"},
  {name:"ability",overlay:167,address:0x021bdcec,signature:"f8b584b01021061c"},
  {name:"damage",overlay:167,address:0x021a5958,signature:"f0b587b01c1c051c"},
  {name:"animation_load",overlay:168,address:0x021e0f28,signature:"f0b583b000900191"},
  {name:"ui",overlay:167,address:0x021cf004,signature:"10b5041c6369002b"},
  {name:"animation_end",overlay:168,address:0x021e3fb0,signature:"f8b582b000240190"},
  {name:"animation_wait",overlay:168,address:0x021e3850,signature:"70b5051c0c1c32f6"},
  {name:"archive_read",overlay:0,address:0x0204a960},
];
for(const probe of probes) {
  if(probe.overlay) {
    const overlay=rom.loadArm9Overlays([probe.overlay]).get(probe.overlay)!;
    if(Buffer.from(overlay.data.subarray(probe.address-overlay.ramAddress,probe.address-overlay.ramAddress+8)).toString("hex")!==probe.signature) throw new Error(`Unsupported US White 2 probe: ${probe.name}`);
  }
}
for(const [name,store] of Object.entries(project.narcs)) if(!["moves","personal","trdata","trpok"].includes(name)||!store?.dirty.size) delete project.narcs[name as keyof typeof project.narcs];
const output=await exportModifiedRom(project,{preserveOriginalLength:true});
await writeFile(resolve(directory,"battle.nds"),output,{flag:"wx"});
await writeFile(resolve(directory,"battle.sav"),save,{flag:"wx"});
await writeFile(resolve(directory,"suite.json"),JSON.stringify({format:"pokeweb-animation-completion-1",animationsEnabled:true,mode:"animation-only inert move metadata; scripts/assets unchanged",inputRomSha256:hash(bytes),inputSaveSha256:hash(originalSave),rom:{file:"battle.nds",sha256:hash(output)},save:{file:"battle.sav",sha256:hash(save)},probes,cases:animations},null,2)+"\n",{flag:"wx"});
console.log(`Prepared ${animations.length} Gen 8/9 scripts; Battle Scene On; one shared ROM/save`);
