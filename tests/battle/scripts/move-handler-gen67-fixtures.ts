/** Non-Z Gen 6/7 effect audit. Expected outcomes are independent of handlers. */
import inventory from "../gen67-move-inventory.json";
import type { HarnessPokemon } from "@pokeweb/pokeweb/battleHarness";
import type { BattleRole } from "./move-handler-doubles-fixtures";
import type { MoveCase, Variant } from "./build-move-handler-fixtures";

export type Gen67Expected = {
  powers?: number[]; type?: number; category?: number; typeRatio?: number;
  critical?: number; finalRatio?: number; ignoreDefenseStages?: boolean; damageUserStages?: number[];
  stages?: Partial<Record<BattleRole, number[]>>;
  types?: Partial<Record<BattleRole, number[]>>;
  statuses?: Partial<Record<BattleRole, number>>;
  hpChange?: Partial<Record<BattleRole, number>>;
  healing?: { role: BattleRole; ratio?: number; targetAttack?: boolean; rounding?: "down" | "unspecified"; atTurnEnd?: boolean };
  beforeStatuses?: Partial<Record<BattleRole, number>>;
  beforeItems?: Partial<Record<BattleRole, {held: number; consumed: number}>>;
  beforeSubstitute?: Partial<Record<BattleRole, boolean>>;
  conditions?: Partial<Record<BattleRole, Record<string, boolean>>>;
  incomingHits?: number; incomingType?: number; incomingCritical?: number;
  screens?: [Record<string, number>, Record<string, number>];
  customSides?: [Record<string, number>, Record<string, number>];
  noDamage?: boolean; selectionRejected?: boolean;
  accuracyThreshold?: number; moneyDouble?: boolean;
  effectivePowers?: number[]; terrain?: number; extraUserMove?: number;
  hpLossFraction?: { role: BattleRole; divisor: number; roundUp?: boolean };
  trapSource?: boolean;
  incomingTargets?: {source: BattleRole;target: BattleRole;move: number;count: number}[];
};
type Definition = typeof inventory.moves[number];
type AuditVariant = Variant & { player: HarnessPokemon; allyPlayer?: HarnessPokemon;
  benchPlayer?: HarnessPokemon; definition: Definition };
const neutral = [6,6,6,6,6,6,6];
const stages = (...changes: [number,number][]) => neutral.map((v,i)=>changes.find(([index])=>index===i)?.[1] ?? v);

export function gen67Variants(): AuditVariant[] {
  const variants: AuditVariant[] = [];
  function add(id: number, name: string, cases: MoveCase[], player: Partial<HarnessPokemon> = {}, npc: Partial<Variant> = {}, ally?: Partial<HarnessPokemon>) {
    const definition = [...inventory.moves,...inventory.residentMoves].find(m=>m.id===id);
    if (!definition) throw new Error(`Missing Gen 6/7 audit inventory ${id}`);
    const user: HarnessPokemon = {speciesId:151,level:50,abilityId:50,moves:[id,150,182,164],itemId:0,...player};
    const partner: HarnessPokemon | undefined = ally && {speciesId:149,level:50,abilityId:50,moves:[150],...ally};
    variants.push({name,trainerId:variants.length+1,moveId:id,definition,player:user,
      playerSpecies:user.speciesId,playerForm:user.form,playerAbilityId:user.abilityId!,
      abilityId:50,trainerMove:150,save:`battle-${name}.sav`,battleType:partner?"Doubles":"Singles",
      allyPlayer:partner,allySpecies:partner?.speciesId,allyAbilityId:partner?.abilityId,allyMoves:partner?.moves,
      defenderSpecies:143,defenderAllySpecies:242,defenderAllyAbilityId:50,
      ...npc,cases:cases.map(c=>({completeTurn:true,accuracyRoll:0,incomingAccuracyRoll:0,secondaryRoll:99,ppSpent:1,...c}))});
  }
  const hit = (id:string,power:number,typeRatio=4096):MoveCase => ({id,audit:{powers:[power],typeRatio}});
  add(573,"freeze-dry-water",[hit("water-super-effective",70,8192)],{}, {defenderSpecies:9});
  add(573,"freeze-dry-dual",[hit("water-ground-four-times",70,16384)],{}, {defenderSpecies:260});
  add(573,"freeze-dry-neutral",[hit("non-water-normal-ice-chart",70)]);
  add(560,"flying-press",[hit("normal-two-times",80)]);
  variants.at(-1)!.cases[0].audit!.typeRatio=8192;
  add(560,"flying-press-grass",[hit("grass-combined-two-times",80,8192)],{}, {defenderSpecies:465});
  add(560,"flying-press-minimize",[{id:"minimize-guaranteed-hit-double-damage",setupSlot:1,accuracyRoll:99,audit:{powers:[80],typeRatio:8192,finalRatio:8192,accuracyThreshold:0}}],{}, {trainerMove:107});
  add(565,"fell-stinger",[hit("survivor-no-boost",30),{currentHp:1,completeTurn:false,...hit("ko-gen6-plus-two",30),audit:{powers:[30],stages:{attacker:stages([0,8])}}}]);
  add(563,"rototiller",[{id:"grounded-grass-only",audit:{noDamage:true,stages:{attacker:stages([0,7],[2,7]),defender:neutral}}}],{speciesId:465});
  add(563,"rototiller-airborne",[{id:"levitating-grass-not-boosted",audit:{noDamage:true,stages:{attacker:neutral}}}],{speciesId:465,abilityId:26});
  add(579,"flower-shield",[{id:"grounded-grass-defense",audit:{noDamage:true,stages:{attacker:stages([1,7])}}}],{speciesId:465});
  add(579,"flower-shield-airborne",[{id:"levitating-grass-still-eligible",audit:{noDamage:true,stages:{attacker:stages([1,7])}}}],{speciesId:465,abilityId:26});
  add(576,"topsy-turvy",[{id:"all-seven-stages-inverted",defenderStages:[12,0,10,2,9,3,6],audit:{noDamage:true,stages:{defender:[0,12,2,10,3,9,6]}}},
    {id:"neutral-unchanged",audit:{noDamage:true,stages:{defender:neutral}}}]);
  add(663,"darkest-lariat",[hit("neutral-defense",85),
    {id:"ignore-defense-and-evasion-keep-user-attack",userStages:stages([0,8]),defenderStages:stages([1,12],[6,12]),accuracyRoll:99,
      audit:{powers:[85],ignoreDefenseStages:true,accuracyThreshold:100}},
    {id:"ignore-defense-drops",defenderStages:stages([1,0]),audit:{powers:[85],ignoreDefenseStages:true}}]);
  add(739,"freezy-frost",[{id:"damage-then-haze-both-sides",userStages:stages([0,9],[3,4]),defenderStages:stages([1,9],[2,11]),
    audit:{powers:[100],stages:{attacker:neutral,defender:neutral}}}]);
  add(683,"speed-swap",[{id:"swap-raw-speed-not-stages",userStats:[100,100,100,100,170],targetStats:[100,100,100,100,70],
    userStages:stages([4,9]),defenderStages:stages([4,2]),audit:{noDamage:true,stages:{attacker:stages([4,9]),defender:stages([4,2])}}}]);
  add(668,"strength-sap",[{id:"heal-from-pre-drop-attack",userCurrentHp:1,targetStats:[80,100,100,100,70],
    audit:{noDamage:true,healing:{role:"attacker",targetAttack:true},stages:{defender:stages([0,5])}}},
    {id:"attack-stage-factors-into-healing",userCurrentHp:1,targetStats:[40,100,100,100,70],defenderStages:stages([0,8]),
      audit:{noDamage:true,healing:{role:"attacker",targetAttack:true},stages:{defender:stages([0,7])}}},
    {id:"minus-six-fails-no-healing",userCurrentHp:1,defenderStages:stages([0,0]),audit:{noDamage:true,hpChange:{attacker:0},stages:{defender:stages([0,0])}}}]);
  add(599,"venom-drench",[{id:"poisoned-three-drops",statuses:{defender:5},audit:{noDamage:true,stages:{defender:stages([0,5],[2,5],[4,5])}}},
    {id:"healthy-no-drops",audit:{noDamage:true,stages:{defender:neutral}}}]);
  add(602,"magnetic-flux-plus",[{id:"plus-defense-spdef-boost",audit:{noDamage:true,stages:{attacker:stages([1,7],[3,7])}}}],{abilityId:57});
  add(602,"magnetic-flux-ineligible",[{id:"other-ability-no-boost",audit:{noDamage:true,stages:{attacker:neutral}}}]);
  add(659,"shore-up",[{id:"ordinary-half-heal",userCurrentHp:1,audit:{noDamage:true,healing:{role:"attacker",ratio:2048}}},
    {id:"sand-two-thirds-heal",setupSlot:1,userCurrentHp:1,audit:{noDamage:true,healing:{role:"attacker",ratio:2732}}}],{speciesId:232,moves:[659,201,150,182]});
  add(659,"shore-up-rounding",[{id:"odd-max-hp-floor-half",userCurrentHp:1,audit:{noDamage:true,healing:{role:"attacker",ratio:2048}}},
    {id:"sand-fraction-floor-not-nearest",setupSlot:1,userCurrentHp:1,audit:{noDamage:true,healing:{role:"attacker",ratio:2732}}}],{speciesId:260,moves:[659,201,150,182]});
  add(666,"floral-healing",[{id:"ordinary-half-heal",currentHp:1,audit:{noDamage:true,healing:{role:"defender",ratio:2048,rounding:"unspecified"}}},
    {id:"grassy-two-thirds-heal",setupSlot:1,currentHp:1,audit:{noDamage:true,healing:{role:"defender",ratio:2732,rounding:"unspecified"}}}],{moves:[666,580,150,182]});
  add(660,"first-impression",[hit("first-turn-works",90),{id:"later-turn-selection-rejected",setupSlot:1,selectionRejected:true,audit:{noDamage:true,selectionRejected:true}}]);
  add(596,"spiky-shield",[{id:"contact-block-and-eighth-recoil",completeTurn:true,audit:{noDamage:true,incomingHits:0,hpChange:{attacker:0},hpLossFraction:{role:"defender",divisor:8}}}],{}, {trainerMove:17});
  add(661,"baneful-bunker",[{id:"contact-block-and-poison",completeTurn:true,audit:{noDamage:true,incomingHits:0,statuses:{defender:5},hpChange:{attacker:0}}}],{}, {trainerMove:17});
  add(588,"kings-shield",[{id:"contact-block-gen6-two-stage-attack-drop",completeTurn:true,audit:{noDamage:true,incomingHits:0,stages:{defender:stages([0,4])},hpChange:{attacker:0}}}],{}, {trainerMove:17});
  add(588,"kings-shield-status",[{id:"status-move-not-blocked",completeTurn:true,audit:{noDamage:true,statuses:{attacker:1}}}],{}, {trainerMove:86});
  add(685,"purify",[{id:"cure-target-heal-user-half",statuses:{defender:4},userCurrentHp:1,audit:{noDamage:true,statuses:{defender:0},healing:{role:"attacker",ratio:2048}}},
    {id:"healthy-target-no-heal",userCurrentHp:1,audit:{noDamage:true,hpChange:{attacker:0}}}]);
  add(682,"burn-up-fire",[{...hit("pure-fire-becomes-typeless",130),audit:{powers:[130],types:{attacker:[18,18]}}}],{speciesId:157});
  add(682,"burn-up-dual",[{...hit("fire-flying-keeps-flying",130),audit:{powers:[130],types:{attacker:[2,2]}}}],{speciesId:6});
  add(682,"burn-up-no-fire",[{id:"non-fire-cannot-use",audit:{noDamage:true,types:{attacker:[13,13]}}}]);
  add(686,"revelation-dance",[{...hit("matches-primary-psychic",90),audit:{powers:[90],type:13}}]);
  add(686,"revelation-dance-normalize",[{...hit("normalize-cannot-replace-primary",90),audit:{powers:[90],type:13}}],{abilityId:96});
  add(722,"photon-geyser",[
    {id:"higher-attack-physical",userStats:[160,100,80,100,100],audit:{powers:[100],category:1}},
    {id:"higher-spatk-special",userStats:[80,100,160,100,100],audit:{powers:[100],category:2}},
    {id:"tie-special",userStats:[100,100,100,100,100],audit:{powers:[100],category:2}},
    {id:"stages-determine-category",userStats:[80,100,100,100,100],userStages:stages([0,8]),audit:{powers:[100],category:1}},
  ]);
  add(687,"core-enforcer",[{id:"already-moved-suppressed",userStats:[100,100,100,100,1],audit:{powers:[100],conditions:{defender:{gastroAcidCondition:true}}}},
    {id:"not-moved-not-suppressed",userStats:[100,100,100,100,500],audit:{powers:[100],conditions:{defender:{gastroAcidCondition:false}}}}]);
  add(714,"moongeist-beam",[hit("levitate-ordinary-damage",100)],{}, {defenderSpecies:232,abilityId:26,abilitySlot:2});
  add(713,"sunsteel-strike",[hit("ordinary-damage",100)]);
  add(737,"baddy-bad",[{...hit("damage-and-reflect",90),audit:{powers:[90],screens:[{"0":1},{}]}}]);
  add(736,"glitzy-glow",[{...hit("damage-and-light-screen",90),audit:{powers:[90],screens:[{"1":1},{}]}}]);
  add(694,"aurora-veil",[{id:"hail-sets-veil",setupSlot:1,audit:{noDamage:true,customSides:[{"15":1},{}]}},
    {id:"no-hail-no-veil",audit:{noDamage:true,customSides:[{},{}]}}],{moves:[694,258,150,182]});
  add(712,"spectral-thief",[{id:"steal-positive-before-damage",userStats:[40,120,120,120,120],defenderStages:[8,3,10,6,7,9,0],
    audit:{powers:[90],typeRatio:8192,damageUserStages:[8,6,10,6,7,9,6],stages:{attacker:[8,6,10,6,7,9,6],defender:[6,3,6,6,6,6,0]}}},
    {...hit("no-boosts-still-deals-damage",90),audit:{powers:[90],typeRatio:8192,stages:{attacker:neutral,defender:neutral}}}],{}, {defenderSpecies:202});
  add(738,"sappy-seed",[{...hit("damage-and-leech-seed",90),audit:{powers:[90],conditions:{defender:{leechSeedCondition:true}}}}]);
  add(677,"anchor-shot",[{...hit("damage-and-trap",80),audit:{powers:[80],trapSource:true,conditions:{attacker:{trapCondition:false},defender:{trapCondition:true}}}}]);
  add(662,"spirit-shackle",[{...hit("damage-and-trap",80),audit:{powers:[80],typeRatio:8192,trapSource:true,conditions:{attacker:{trapCondition:false},defender:{trapCondition:true}}}}],{}, {defenderSpecies:202});
  add(664,"sparkling-aria",[{id:"hit-cures-burn",statuses:{defender:4},audit:{powers:[90],statuses:{defender:0}}}]);
  add(740,"sparkly-swirl",[{id:"damage-cures-user-status",userStatusBefore:4,statuses:{attacker:4},audit:{powers:[90],statuses:{attacker:0}}}]);
  add(676,"pollen-puff",[hit("opponent-takes-damage",90)]);
  add(690,"beak-blast",[{id:"contact-while-heating-burns",completeTurn:true,audit:{powers:[100],statuses:{defender:4},incomingHits:1}}],{}, {trainerMove:17});
  add(704,"shell-trap",[{id:"physical-hit-releases-trap",completeTurn:true,audit:{powers:[150],incomingHits:1}},
    {id:"substitute-hit-does-not-release",setupSlot:3,audit:{noDamage:true}}],{}, {trainerMove:33});
  add(704,"shell-trap-special",[{id:"special-hit-does-not-release",completeTurn:true,audit:{noDamage:true,incomingHits:1}}],{}, {trainerMove:129});
  add(675,"throat-chop",[{id:"sound-move-prevented-this-turn",completeTurn:true,audit:{powers:[80],stages:{attacker:neutral}}}],{}, {trainerMove:45});
  add(569,"ion-deluge",[{id:"normal-incoming-becomes-electric",completeTurn:true,audit:{noDamage:true,incomingHits:1,incomingType:12}}],{}, {trainerMove:33});
  add(582,"electrify",[{id:"pending-incoming-becomes-electric",completeTurn:true,audit:{noDamage:true,incomingHits:1,incomingType:12}}],{}, {trainerMove:55});
  add(721,"plasma-fists",[{id:"normal-incoming-becomes-electric",completeTurn:true,audit:{powers:[100],incomingHits:1,incomingType:12}}],{}, {trainerMove:33});
  add(600,"powder",[{id:"fire-move-blocked-quarter-hp",completeTurn:true,audit:{noDamage:true,incomingHits:0,hpChange:{attacker:0},hpLossFraction:{role:"defender",divisor:4}}}],{}, {trainerMove:52});
  add(673,"laser-focus",[{id:"next-turn-guaranteed-critical",audit:{noDamage:true},
    followup:{slot:1,moveId:33,power:50,category:1,type:0,case:{id:"focused-tackle",audit:{powers:[50],critical:1}}}}],{moves:[673,33,150,182]});
  add(603,"happy-hour",[{id:"prize-money-double-flag",audit:{noDamage:true,moneyDouble:true}}]);
  add(604,"electric-terrain",[{id:"grounded-sleep-prevention",completeTurn:true,audit:{noDamage:true,statuses:{attacker:0}}}],{}, {trainerMove:95});
  add(604,"electric-terrain-asleep",[{id:"does-not-cure-existing-sleep",setupSlot:1,currentHp:1,completeTurn:false,
    audit:{noDamage:true,beforeStatuses:{defender:2},statuses:{defender:2}}}],{}, {trainerMove:156});
  add(581,"misty-terrain-asleep",[{id:"native-rest-sleep-control",setupSlot:1,currentHp:1,completeTurn:false,
    audit:{noDamage:true,beforeStatuses:{defender:2},statuses:{defender:2}}}],{}, {trainerMove:156});
  add(604,"electric-terrain-power",[{id:"current-gen8-power-policy",audit:{noDamage:true},followup:{slot:1,moveId:85,power:90,type:12,category:2,
    case:{id:"grounded-electric-boost",audit:{powers:[90],effectivePowers:[117],type:12,category:2}}}}],{moves:[604,85,150,182]});
  add(580,"grassy-terrain",[{id:"grounded-end-turn-sixteenth-heal",userCurrentHp:100,completeTurn:true,audit:{noDamage:true,healing:{role:"attacker",ratio:256,atTurnEnd:true}}}]);
  add(581,"misty-terrain",[{id:"grounded-paralysis-prevention",completeTurn:true,audit:{noDamage:true,statuses:{attacker:0}}}],{}, {trainerMove:86});
  add(678,"psychic-terrain",[{id:"block-incoming-priority-after-setup",setupSlot:0,completeTurn:true,audit:{noDamage:true,incomingHits:0}}],{}, {trainerMove:98});
  add(567,"trick-or-treat",[{id:"added-ghost-gives-normal-immunity",audit:{noDamage:true},followup:{slot:1,moveId:33,power:40,type:0,category:1,case:{id:"normal-immune",audit:{noDamage:true}}}}],{moves:[567,33,150,182]}, {defenderSpecies:232});
  add(571,"forests-curse",[{id:"added-grass-fire-weakness",audit:{noDamage:true},followup:{slot:1,moveId:53,power:90,type:9,category:2,
    case:{id:"extra-grass-fire-two-times",audit:{powers:[90],category:2,type:9,typeRatio:8192}}}}],{moves:[571,53,150,182]});
  add(575,"parting-shot",[{id:"both-offenses-lowered-no-bench",audit:{noDamage:true,stages:{defender:stages([0,5],[2,5])}}}]);
  add(564,"sticky-web",[{id:"deploy-one-opposing-web",audit:{noDamage:true,customSides:[{}, {"14":1}]}},
    {id:"repeat-does-not-stack",setupSlot:0,audit:{noDamage:true,customSides:[{}, {"14":1}]}}]);
  add(561,"mat-block",[{id:"first-turn-blocks-damage",completeTurn:true,userStats:[100,100,100,100,500],audit:{noDamage:true,incomingHits:0,hpChange:{attacker:0}}}],{}, {trainerMove:33});
  add(578,"crafty-shield",[{id:"blocks-targeted-status",completeTurn:true,audit:{noDamage:true,statuses:{attacker:0}}}],{}, {trainerMove:86});
  add(578,"crafty-shield-damage",[{id:"does-not-block-damage",completeTurn:true,audit:{noDamage:true,incomingHits:1}}],{}, {trainerMove:33});
  add(707,"stomping-tantrum",[{id:"fresh-turn-normal-power",audit:{powers:[75]}},
    {id:"failed-thunder-wave-doubles-power",setupSlot:1,audit:{powers:[150]}},
    {id:"successful-splash-not-doubled",setupSlot:2,audit:{powers:[75]}}],{moves:[707,86,150,182]}, {defenderSpecies:232});
  add(720,"mind-blown",[{id:"hit-costs-half-max-hp-rounded-up",audit:{powers:[150],hpLossFraction:{role:"attacker",divisor:2,roundUp:true}}}]);
  add(720,"mind-blown-protect",[{id:"protect-still-costs-half-hp",audit:{noDamage:true,hpLossFraction:{role:"attacker",divisor:2,roundUp:true}}}],{}, {trainerMove:182});
  add(720,"mind-blown-magic-guard",[{id:"magic-guard-prevents-payment",audit:{powers:[150],hpChange:{attacker:0}}}],{abilityId:98});
  add(720,"mind-blown-damp",[{id:"damp-prevents-attack-and-payment",audit:{noDamage:true,hpChange:{attacker:0}}}],{}, {defenderSpecies:9,abilityId:6,abilitySlot:2});
  add(689,"instruct",[{id:"ally-repeats-tackle-immediately",userStats:[100,100,100,100,1],targetRole:"ally",completeTurn:true,
    audit:{noDamage:true,incomingTargets:[{source:"ally",target:"defender",move:33,count:2}]}}],{}, {},{moves:[33]});
  add(671,"spotlight",[{id:"redirect-ally-attack-to-spotlight-target",targetRole:"defender",allyTargetRole:"defenderAlly",completeTurn:true,
    audit:{noDamage:true,incomingTargets:[{source:"ally",target:"defender",move:33,count:1}]}}],{}, {},{moves:[33]});
  add(676,"pollen-puff-ally",[{id:"heal-ally-half-no-damage",targetRole:"ally",hp:{ally:1},completeTurn:true,
    audit:{noDamage:true,healing:{role:"ally",ratio:2048}}}],{}, {},{});
  add(594,"water-shuriken-ash",[{id:"ash-three-strikes-twenty-power-gen7-special",audit:{powers:[20,20,20],category:2}}],{speciesId:658,form:2,abilityId:210});
  add(673,"laser-focus-dancer",[{id:"same-turn-dancer-critical",completeTurn:true,userStats:[100,100,100,100,500],
    audit:{powers:[90],type:13,category:2,critical:1,extraUserMove:686,
      incomingTargets:[{source:"ally",target:"defender",move:686,count:1}]}}],{abilityId:216}, {},{moves:[686]});
  add(562,"belch",[{id:"uneaten-berry-cannot-select",selectionRejected:true,audit:{selectionRejected:true,noDamage:true}}]);
  // Use native Substitute's HP payment to activate Sitrus. This tests Belch's
  // berry gate without depending on a separate Gen 8 Stuff Cheeks handler.
  add(562,"belch-eaten-berry",[{id:"eaten-sitrus-enables-belch",setupSlot:1,userCurrentHp:100,
    audit:{powers:[120],beforeItems:{attacker:{held:0,consumed:158}}}}],{itemId:158,moves:[562,164,150,182]});
  add(562,"belch-natural-gift",[{id:"using-berry-as-ammunition-does-not-enable-belch",setupSlot:1,setupAccuracyRoll:0,selectionRejected:true,
    audit:{selectionRejected:true,noDamage:true}}],{itemId:158,moves:[562,363,150,182]});
  add(714,"moongeist-beam-multiscale",[hit("ignore-full-hp-multiscale",100)],{}, {defenderSpecies:68,abilityId:136,abilitySlot:2});
  add(713,"sunsteel-strike-wonder-guard",[hit("ignore-neutral-wonder-guard",100)],{}, {defenderSpecies:128,abilityId:25,abilitySlot:2});
  add(722,"photon-geyser-fur-coat",[{id:"physical-also-ignores-fur-coat",userStats:[160,100,80,100,100],audit:{powers:[100],category:1}}],{}, {defenderSpecies:242,abilityId:169,abilitySlot:2});
  add(687,"core-enforcer-stance-change",[{id:"cannot-suppress-stance-change",userStats:[100,100,100,100,1],audit:{powers:[100],conditions:{defender:{gastroAcidCondition:false}}}}],{}, {defenderSpecies:463,abilityId:176,abilitySlot:2});
  add(712,"spectral-thief-simple",[{id:"simple-doubles-stolen-attack",userStats:[40,120,120,120,120],defenderStages:stages([0,7]),
    audit:{powers:[90],typeRatio:8192,damageUserStages:stages([0,8]),stages:{attacker:stages([0,8]),defender:neutral}}}],{abilityId:86},{defenderSpecies:202});
  add(712,"spectral-thief-contrary",[{id:"contrary-inverts-stolen-attack",userStats:[40,120,120,120,120],defenderStages:stages([0,8]),
    audit:{powers:[90],typeRatio:8192,damageUserStages:stages([0,4]),stages:{attacker:stages([0,4]),defender:neutral}}}],{abilityId:126},{defenderSpecies:202});
  add(673,"laser-focus-battle-armor",[{id:"battle-armor-vetoes-focused-critical",audit:{noDamage:true},
    followup:{slot:1,moveId:33,power:50,category:1,type:0,case:{id:"armor-veto",audit:{powers:[50],critical:0}}}}],{moves:[673,33,150,182]}, {defenderSpecies:289,abilityId:4,abilitySlot:2});
  add(712,"spectral-thief-substitute",[
    {id:"bypass-native-substitute",setupSlot:2,bypassSubstitute:true,
      audit:{powers:[90],typeRatio:8192,beforeSubstitute:{defender:true}}},
    {id:"steal-boosts-through-substitute",setupSlot:2,bypassSubstitute:true,
      userStats:[40,120,120,120,120],defenderStages:stages([0,8]),
      audit:{powers:[90],typeRatio:8192,beforeSubstitute:{defender:true},damageUserStages:stages([0,8]),
        stages:{attacker:stages([0,8]),defender:neutral}}},
    {id:"native-tackle-still-hits-doll",setupSlot:2,moveSlot:1,selectedMoveId:33,expectedExecutedMove:33,
      userStats:[40,120,120,120,120],
      audit:{powers:[50],type:0,category:1,beforeSubstitute:{defender:true}}}
  ],{moves:[712,33,150,182]}, {defenderSpecies:202,trainerMove:164});
  add(712,"spectral-thief-clear-body-cap",[{id:"clear-body-and-user-cap-do-not-prevent-stealing",userStats:[40,120,120,120,120],
    userStages:stages([0,12]),defenderStages:stages([0,8]),audit:{powers:[90],typeRatio:8192,stages:{attacker:stages([0,12]),defender:neutral}}}],{},
    {defenderSpecies:202,abilityId:29,abilitySlot:2});
  return variants;
}
