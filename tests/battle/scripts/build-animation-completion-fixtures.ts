/** Animation-only fixture: real battles, unchanged scripts/assets, inert move effects. */
import { createHash } from "node:crypto";
import { execFileSync } from "node:child_process";
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
import { compileMoveAnimation, decompileMoveAnimationBytes, getMoveAnimationTargetInfo } from "@pokeweb/pokeweb/moveAnimationModel";
import { markDirty } from "@pokeweb/pokeweb/projectStore";
import { setRomFileReplacement } from "@pokeweb/pokeweb/fileSystemModel";
import { parseRpm } from "@pokeweb/pokeweb/rpm";
import { findPwanOverrideForSpecies, listPwanSpeciesTargets, upsertPwanOverride } from "@pokeweb/pokeweb/pwanAnimationModel";
import { upsertTrainerPwanOverride } from "@pokeweb/pokeweb/trainerPwanAnimationModel";
import { trainerGraphicIndexForClass } from "@pokeweb/pokeweb/trainerSpriteModel";
import { parsePwanHeader } from "@pokeweb/pokeweb/pwanCompiler";
import { w2animEditorToLinear, w2animLinearToEditor } from "@pokeweb/pokeweb/w2animAnimationModel";

const args = new Map<string,string>();
for(let i=2;i<process.argv.length;i+=2) {
  const key=process.argv[i], value=process.argv[i+1];
  if(!["--rom","--save","--out","--sprites","--modules","--baseline-control","--native-mechanics","--stress-loader","--isolate-particles","--authoring-smoke"].includes(key)||!value||args.has(key)) throw new Error("Expected --rom INPUT --save INPUT --out NEW_DIRECTORY");
  args.set(key,value);
}
if(!["--rom","--save","--out"].every(key=>args.has(key))) throw new Error("Expected --rom INPUT --save INPUT --out NEW_DIRECTORY");
const sprites=args.get("--sprites")??"streamed", modules=args.get("--modules")??"missing";
if(!["streamed","native"].includes(sprites)||!["missing","production","corrupt","wrong-abi","truncated","corrupt-tables","heap-refusal"].includes(modules)) throw new Error("Unsupported sprite/module fixture mode");
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
const authoringSmoke=args.get("--authoring-smoke")==="yes";
const project=await loadProjectFromRomBytes(bytes,basename(args.get("--rom")!),{selectedNarcs:["message_texts","personal","moves","trdata","trpok","move_animations","battle_animations",...(authoringSmoke?["pokemon_sprites","trainer_sprites"] as const:[])]});
const nativeIds = Boolean(project.w2animAnimations);
const baselineControl=args.get("--baseline-control")==="yes";
const nativeMechanics=args.get("--native-mechanics")==="yes";
const stressLoader=args.get("--stress-loader");
const isolateParticles=args.get("--isolate-particles")==="yes";
if(baselineControl) {
  // Diagnostic only: pinned, prebuilt incoming core and its original Pyro
  // Ball assets. This is not fresh-build release-acceptance evidence.
  const pinned=(path:string)=>new Uint8Array(execFileSync("git",["show",`4369e8a4738ea435a350eff4e9c527d523bd8c31:${path}`]));
  const fileId=rom.filenames.idOf("patches/White2Upgrade.dll");
  if(fileId===undefined)throw new Error("Missing core for baseline control");
  setRomFileReplacement(project,fileId,pinned("vfs/data/patches/White2Upgrade.dll"));
  project.narcs.move_animations!.rawFiles[780]=pinned("data/graphics/move_animations/5_00000780.bin");
  markDirty(project,"move_animations",780);
  // Battle particles are loaded through their own archive; stage its one
  // changed member without altering any other source-ROM assets.
  const {NARC}=await import("@pokeweb/nds/narc");
  const spaId=rom.filenames.idOf("a/0/0/6");
  if(spaId===undefined)throw new Error("Missing particle archive");
  const spas=new NARC(rom.files[spaId]);
  spas.files[960]=pinned("data/graphics/move_spas/6_00000960.bin");
  setRomFileReplacement(project,spaId,spas.save());
}
const cases=expansion.moves.flatMap((move,index)=>move.sourceId>=744&&move.sourceId<=919 ? [{sourceMoveId:move.sourceId,moveId:nativeIds ? move.sourceId : expansion.firstTargetMoveId+index,name:move.name}] : []);
const moves=project.narcs.moves!;
if(moves.rawFiles.length < (nativeIds ? 920 : 1000)) throw new Error("Incomplete move-ID layout");
if (nativeIds) {
  // Animation-only fixture: no child mechanic table may reintroduce recoil,
  // self-KO or field effects into the inert native executor. Production DLLs
  // are untouched; missing-module behavior is exercised only in this copy.
  const registry=JSON.parse(await readFile(new URL("../../../src/pokeweb_gameplay/battle_modules/registry.json",import.meta.url),"utf8"));
  for (const module of registry.modules) {
    const fileId=rom.filenames.idOf(`lib/w2u_battle/${module.name}.dll`);
    if(fileId===undefined) throw new Error(`Missing production module ${module.name}`);
    if(modules==="missing") setRomFileReplacement(project,fileId,new Uint8Array());
    else if(modules==="truncated") setRomFileReplacement(project,fileId,rom.files[fileId]!.subarray(0,16));
    else if(modules==="heap-refusal") {
      const expanded=rom.files[fileId]!.slice(), view=new DataView(expanded.buffer,expanded.byteOffset,expanded.byteLength);
      const exec=view.getUint32(8,true);
      view.setUint32(4,128*1024,true);view.setUint32(exec+12,128*1024-expanded.length,true);
      setRomFileReplacement(project,fileId,expanded);
    }
    else if(modules==="corrupt-tables") {
      const corrupt=rom.files[fileId]!.slice();
      const view=new DataView(corrupt.buffer,corrupt.byteOffset,corrupt.byteLength);
      const exec=view.getUint32(8,true), info=exec+view.getUint32(exec+8,true);
      const symbols=exec+view.getUint32(info+4,true);
      view.setUint32(symbols+20,0xfffffffe,true);
      setRomFileReplacement(project,fileId,corrupt);
    } else if(modules==="corrupt"||modules==="wrong-abi") {
      const corrupt=rom.files[fileId]!.slice();
      const hits=[];for(let at=0;at+4<=corrupt.length;at+=4)if(new DataView(corrupt.buffer,corrupt.byteOffset+at,4).getUint32(0,true)===0x4d423257)hits.push(at);
      if(hits.length!==1)throw new Error(`Cannot locate unique module API magic in ${module.name}`);
      if(modules==="wrong-abi") corrupt[hits[0]!+4]=2;
      else corrupt[hits[0]!]^=0xff;
      setRomFileReplacement(project,fileId,corrupt);
    }
  }
}
if(stressLoader){
  if(modules!=="production"||baselineControl)throw new Error("Stress fixture requires production modules/current core");
  const fileId=rom.filenames.idOf("lib/w2u_battle/abilities/veils.dll");
  if(fileId===undefined)throw new Error("Missing veils module");
  setRomFileReplacement(project,fileId,new Uint8Array(await readFile(resolve(stressLoader))));
}
const animations=[];
await mkdir(resolve(directory,"scripts"));
for(const entry of cases) {
  const target=getMoveAnimationTargetInfo(project,entry.moveId);
  if(!target) throw new Error(`Missing animation target for ${entry.name}`);
  let data=project.narcs[target.storeName]!.rawFiles[target.index];
  if(!data?.length) throw new Error(`Missing animation bytes for ${entry.name}`);
  const originalScriptSha256=hash(data);
  let script=decompileMoveAnimationBytes(data);
  if(isolateParticles && [778,833].includes(entry.sourceMoveId)){
    script=script.split("\n").filter(line=>!/^\s*(LoadSPA|Emit)\b/.test(line)).join("\n");
    data=compileMoveAnimation(project,entry.moveId,script);
    project.narcs[target.storeName]!.rawFiles[target.index]=data;markDirty(project,target.storeName,target.index);
  }
  await writeFile(resolve(directory,`scripts/${entry.sourceMoveId}.s`),script,{flag:"wx"});
  animations.push({...entry,scriptBytes:data.length,scriptSha256:hash(data),originalScriptSha256,animationTarget:target});
  // Test animation lifecycle independently of unavailable custom handlers,
  // prerequisites, immunity, recharge, recoil and multi-hit damage. Keep the
  // original animation ID and bytes; use retail Tackle's one-target executor.
  moves.rawFiles[entry.moveId]=nativeMechanics ? moves.rawFiles[entry.moveId].slice() : moves.rawFiles[33].slice();
  moves.rawFiles[entry.moveId][3]=1; // Power 1 avoids either side fainting.
  moves.rawFiles[entry.moveId][4]=101; // Always-hit native encoding.
  markDirty(project,"moves",entry.moveId);
}
if(authoringSmoke){
  if(!nativeIds||modules!=="production"||baselineControl||isolateParticles)throw new Error("Authoring smoke requires current production w2anim");
  // Private diagnostic art, not a release asset: exercise the real editor's
  // new native-Pokemon and trainer carrier materializers in the native game.
  const source=findPwanOverrideForSpecies(project,650,0)?.front;
  const target=listPwanSpeciesTargets(project).find(row=>row.speciesId===151&&row.formIndex===0);
  if(!source||!target)throw new Error("Missing authoring smoke source/target");
  upsertPwanOverride(project,{speciesId:151,formIndex:0,assetIndex:target.assetIndex,front:structuredClone(source),back:structuredClone(source),nativePaletteSource:"front",carrierTemplate:"w2u-gen6-placeholder"});
  const trainer=structuredClone(source), header=parsePwanHeader(trainer.pwanBytes);
  for(let frame=0;frame<header.frameCount;++frame){
    const at=header.frameOffset+frame*4608;
    const linear=w2animEditorToLinear(trainer.pwanBytes.subarray(at,at+4608));
    linear.fill(0,0,8*48);trainer.pwanBytes.set(w2animLinearToEditor(linear),at);
  }
  upsertTrainerPwanOverride(project,{graphicIndex:trainerGraphicIndexForClass(project,0),animation:trainer});
}
const playerSpecies = nativeIds && sprites==="streamed" && !authoringSmoke ? 650 : 151;
const defenderSpecies = nativeIds && sprites==="streamed" ? 651 : 143;
const checkpointMoveId = animations.find(x=>x.sourceMoveId===780)!.moveId;
if(nativeMechanics){project.narcs.personal!.rawFiles[defenderSpecies][4]=200;markDirty(project,"personal",defenderSpecies);}
patchHarnessTrainer(project,{trainerId:1,battleType:"Singles",trainer:{ai:0,...(authoringSmoke?{trainerClass:0}:{}),team:[{speciesId:defenderSpecies,level:50,moves:[nativeMechanics?33:150],abilityId:50}]}});
const config=getTestBattleConfig("BW2");
const save=patchTestBattleSaveMoveAnimations(patchHarnessSave(rawSaveBytesFromDesmumeDsv(originalSave),project,{trainerId:1,player:{team:[{speciesId:playerSpecies,level:50,abilityId:stressLoader?165:99,itemId:155,moves:[checkpointMoveId,33,150,182]}]}}),config,true);
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
  {name:"sprite_alloc",overlay:0,address:0x0203a228},
  {name:"sprite_free",overlay:0,address:0x0203a278},
  {name:"move_registration",overlay:167,address:0x021c5b44,signature:"f0b585b00d1c"},
  {name:"pmc_alloc",overlay:344,address:0x021fd822,signature:"072370b5cd1d0600"},
  {name:"script_pc",overlay:0,address:0x02015a68},
  {name:"primary_script_pc",overlay:0,address:0x02015910},
  {name:"vm_command",overlay:0,address:0x02015974},
  {name:"particle_emitter",overlay:0,address:0x02050098},
  {name:"particle_parse",overlay:0,address:0x02050ff4},
  {name:"particle_create",overlay:0,address:0x0204f9ac},
  {name:"mcss_request",overlay:0,address:0x02019c32},
  {name:"mcss_request",overlay:0,address:0x0201aa84},
  {name:"mcss_request",overlay:0,address:0x0201afbe},
];
for(const probe of probes) {
  if(probe.overlay) {
    const overlay=rom.loadArm9Overlays([probe.overlay]).get(probe.overlay)!;
    if(Buffer.from(overlay.data.subarray(probe.address-overlay.ramAddress,probe.address-overlay.ramAddress+probe.signature!.length/2)).toString("hex")!==probe.signature) throw new Error(`Unsupported US White 2 probe: ${probe.name}`);
  }
}
for(const [name,store] of Object.entries(project.narcs)) {
  const authoringStore=authoringSmoke&&["pokemon_sprites","trainer_sprites"].includes(name);
  // The materializer still needs untouched native palettes/carrier sheets.
  if(!authoringStore&&(!["moves","personal","trdata","trpok","move_animations"].includes(name)||!store?.dirty.size)) delete project.narcs[name as keyof typeof project.narcs];
}
const output=await exportModifiedRom(project,{preserveOriginalLength:true});
const exported = new NintendoDSRom(output,{fileData:"view"});
const core = parseRpm(exported.getFileByName("patches/White2Upgrade.dll"),{allowedMagics:["DLXF"]});
const nameHash=(name:string)=>{let value=0x811c9dc5;for(const ch of name)value=Math.imul(value^ch.charCodeAt(0),0x01000193)>>>0;return value;};
const coreOffsets=Object.fromEntries(["THUMB_BRANCH_MoveEvent_AddItem","W2U_BattleModules_GetTelemetry","W2U_BattleState_OnBattleExit"].map(name=>{
  const symbol=core.symbols.find(s=>s.nameHash===nameHash(name));if(!symbol)throw new Error(`Missing resident symbol ${name}`);return [name,symbol.address];
}));
await writeFile(resolve(directory,"battle.nds"),output,{flag:"wx"});
await writeFile(resolve(directory,"battle.sav"),save,{flag:"wx"});
await writeFile(resolve(directory,"suite.json"),JSON.stringify({format:"pokeweb-animation-completion-1",animationsEnabled:true,mode:isolateParticles?"DIAGNOSTIC particle commands removed; not acceptance evidence":nativeMechanics?"native move effects with reduced power and faster attacking target; scripts/assets unchanged":"animation-only inert move metadata; scripts/assets unchanged",authoringSmoke,isolateParticles,syntheticAllGroupRegistration:Boolean(stressLoader),baselineControl,nativeMechanics,playerSpecies,defenderSpecies,checkpointMoveId,animationBackend:nativeIds?"w2anim":"native",moduleMode:modules,coreOffsets,inputRomSha256:hash(bytes),inputSaveSha256:hash(originalSave),rom:{file:"battle.nds",sha256:hash(output)},save:{file:"battle.sav",sha256:hash(save)},probes,cases:animations},null,2)+"\n",{flag:"wx"});
console.log(`Prepared ${animations.length} Gen 8/9 scripts; Battle Scene On; one shared ROM/save`);
