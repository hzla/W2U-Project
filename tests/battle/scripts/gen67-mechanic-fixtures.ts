/** Gen 6/7 ability/item rules, authored independently of the DLL handlers. */
import type { HarnessPokemon } from "@pokeweb/pokeweb/battleHarness";
import type { MoveCase, Variant } from "./build-move-handler-fixtures";
import type { BattleRole } from "./move-handler-doubles-fixtures";
import inventory from "../gen67-mechanic-inventory.json";

type Strike = { move: number; type?: number; powerRatio?: number; attackRatio?: number;
  defenseRatio?: number; finalRatio?: number; typeRatio?: number; critical?: number;
  absorbed?:boolean; userRole?:BattleRole; targetRole?:BattleRole; spread?:boolean; fixedByLevel?:boolean };
export type MechanicExpected = {
  outgoing?: Strike[]; incoming?: Strike[];
  stages?: Partial<Record<BattleRole, number[]>>;
  types?: Partial<Record<BattleRole, number[]>>;
  statuses?: Partial<Record<BattleRole, number>>;
  items?: Partial<Record<BattleRole, number>>;
  consumed?: Partial<Record<BattleRole, number>>;
  beforeStages?: Partial<Record<BattleRole, number[]>>;
  beforeItems?: Partial<Record<BattleRole, number>>;
  terrain?: number;
  terrainTimeline?: number[];
  order?: "user-first" | "opponent-first";
  weatherImmune?: boolean;
  damageTypes?: number[];
  berryPouchHealing?: boolean;
  conditions?: Partial<Record<BattleRole,Record<string,boolean>>>;
  forms?:Partial<Record<BattleRole,number>>;
  beforeForms?:Partial<Record<BattleRole,number>>;
  abilities?:Partial<Record<BattleRole,number>>;
  hpExact?:Partial<Record<BattleRole,number>>;
  directLoss?:Partial<Record<BattleRole,number>>;
  healHalfBeforeHit?:boolean;
  terrainHealing?:BattleRole[];
  hpPoolGrowth?:BattleRole;
  actions?:Partial<Record<BattleRole,Record<number,number>>>;
  foeActions?:Partial<Record<BattleRole,number>>;
  expectedPivot?:boolean;
  symbiosisSubstitute?:boolean;
  replacementThisTurn?:boolean;
};
export const mechanicMoves: Record<number, {id:number;type:number;power:number;category:number;accuracy:number;target:number}> =
  Object.fromEntries([
    [33,0,50,1,100,0], [129,0,60,2,101,5], [52,9,40,2,100,0], [53,9,90,2,100,0],
    [7,9,75,1,100,0], [44,16,60,1,100,0], [55,10,40,2,100,0], [58,14,90,2,100,0],
    [245,0,80,1,100,0], [247,7,80,2,100,0], [352,10,60,2,100,0], [585,17,95,2,100,0], [87,12,110,2,70,0],
    [253,0,90,2,100,9], [497,0,40,2,100,0], [17,2,60,1,100,0], [232,8,50,1,95,0],
    [150,0,0,0,101,7], [86,12,0,0,100,0], [95,13,0,0,60,0], [92,3,0,0,90,0],
    [45,0,0,0,100,5], [204,17,0,0,100,0], [201,5,0,0,101,10], [258,14,0,0,101,10],
    [236,17,0,0,101,7], [604,12,0,0,101,10], [580,11,0,0,101,10],
    [581,17,0,0,101,10], [678,13,0,0,101,10], [261,9,0,0,85,0],
    [105,0,0,0,101,7], [14,0,0,0,101,7], [182,0,0,0,101,7],
    [164,0,0,0,101,7], [588,8,0,0,101,7], [153,0,250,1,100,8], [369,6,70,1,100,0],
    [24,1,30,1,100,0], [69,1,1,1,100,0],
  ].map(([id,type,power,category,accuracy,target])=>[id,{id,type,power,category,accuracy,target}]));
export type MechanicVariant = Variant & {player:HarnessPokemon;allyPlayer?:HarnessPokemon;benchPlayer?:HarnessPokemon;
  definition:typeof mechanicMoves[number];mechanic:{kind:"ability"|"item";id:number;name:string}};
const neutral = [6,6,6,6,6,6,6];
const stages = (i:number,n:number) => neutral.map((v,j)=>j===i?n:v);
const strike = (move:number,options:Omit<Strike,"move">={}):Strike=>({move,...options});

export function gen67MechanicVariants(kind:"ability"|"item"):MechanicVariant[] {
  const variants:MechanicVariant[]=[];
  function add(id:number,name:string,move:number,cases:MoveCase[],player:Partial<HarnessPokemon>={},npc:Partial<Variant>={}) {
    const user:HarnessPokemon={speciesId:151,level:50,abilityId:kind==="ability"?id:50,
      itemId:kind==="item"?id:0,moves:[move,150,182,164],...player};
    const definition=mechanicMoves[move];
    if(!definition)throw new Error(`Missing independent move definition ${move}`);
    variants.push({name,trainerId:variants.length+1,mechanic:{kind,id,name},definition,player:user,
      moveId:move,playerSpecies:user.speciesId,playerForm:user.form,playerAbilityId:user.abilityId!,
      defenderSpecies:143,abilityId:50,trainerMove:150,save:`battle-${name}.sav`,battleType:"Singles",trainerBagItems:[0,0,0,0],
      ...npc,cases:cases.map(c=>({completeTurn:true,userStats:[100,100,100,100,300],targetStats:[100,100,100,100,100],
        accuracyRoll:0,incomingAccuracyRoll:0,secondaryRoll:99,ppSpent:1,...c}))});
  }
  const incoming = (id:string,move:number,options:Omit<Strike,"move">={}):MoveCase=>
    ({id,mechanicAudit:{outgoing:[],incoming:[strike(move,options)]}});
  const outgoing = (id:string,move:number,options:Omit<Strike,"move">={}):MoveCase=>
    ({id,mechanicAudit:{outgoing:[strike(move,options)],incoming:[]}});
  const slot = (moveSlot:number,selectedMoveId:number,c:MoveCase):MoveCase=>
    ({...c,moveSlot,selectedMoveId,expectedExecutedMove:selectedMoveId});
  if(kind==="ability") {
    add(218,"fluffy",150,[incoming("contact-half",33,{finalRatio:2048})],{}, {trainerMove:33});
    add(218,"fluffy-noncontact",150,[incoming("noncontact-normal",129)],{}, {trainerMove:129});
    add(218,"fluffy-fire",150,[incoming("fire-double",53,{finalRatio:8192})],{}, {trainerMove:53});
    add(218,"fluffy-fire-contact",150,[incoming("fire-contact-cancels",7)],{}, {trainerMove:7});
    add(169,"fur-coat",150,[incoming("physical-double-defense",33,{defenseRatio:8192})],{}, {trainerMove:33});
    add(169,"fur-coat-special",150,[incoming("special-unmodified",129)],{}, {trainerMove:129});
    add(171,"bulletproof",150,[{id:"ball-blocked",mechanicAudit:{outgoing:[],incoming:[],statuses:{attacker:0}}}],{}, {trainerMove:247});
    add(171,"bulletproof-control",150,[incoming("nonball-allowed",129)],{}, {trainerMove:129});
    add(199,"water-bubble-power",55,[outgoing("water-double-attacking-stat",55,{attackRatio:8192})]);
    add(199,"water-bubble-fire",150,[incoming("fire-half-attacking-stat",52,{attackRatio:2048})],{}, {trainerMove:52});
    add(199,"water-bubble-burn",150,[{id:"burn-prevented",mechanicAudit:{outgoing:[],incoming:[],statuses:{attacker:0}}}],{}, {trainerMove:261});
    for(const [id,name,type,nativeMove] of [[174,"refrigerate",14,58],[182,"pixilate",17,585],
      [184,"aerilate",2,17],[206,"galvanize",12,87]] as const) {
      // Gen 7 conversion is +20%. Naturally typed attacks must NOT gain that boost.
      add(id,name,33,[outgoing("normal-converted-plus-twenty-percent",33,{type,powerRatio:4915}),
        slot(1,55,outgoing("non-normal-unchanged",55))],{moves:[33,55,150,182]});
      if(mechanicMoves[nativeMove])add(id,`${name}-already-typed`,nativeMove,[outgoing("already-typed-no-conversion-boost",nativeMove)]);
    }
    add(204,"liquid-voice",497,[outgoing("sound-becomes-water-no-power-boost",497,{type:10})]);
    add(204,"liquid-voice-control",33,[outgoing("nonsound-stays-normal",33)]);
    add(168,"protean",55,[{...outgoing("type-before-hit-and-stab",55),mechanicAudit:{outgoing:[strike(55)],incoming:[],types:{attacker:[10,10]},damageTypes:[10,10]}}]);
    add(173,"strong-jaw",44,[outgoing("bite-fifty-percent",44,{powerRatio:6144}),slot(1,33,outgoing("nonbite-unmodified",33))],{moves:[44,33,150,182]});
    add(178,"mega-launcher",352,[outgoing("pulse-fifty-percent",352,{powerRatio:6144}),slot(1,55,outgoing("nonpulse-unmodified",55))],{moves:[352,55,150,182]});
    add(181,"tough-claws",33,[outgoing("contact-thirty-percent",33,{powerRatio:5325}),slot(1,55,outgoing("noncontact-unmodified",55))],{moves:[33,55,150,182]});
    add(200,"steelworker",232,[outgoing("steel-fifty-percent",232,{powerRatio:6144}),slot(1,33,outgoing("nonsteel-unmodified",33))],{moves:[232,33,150,182]});
    add(196,"merciless",33,[{...outgoing("poison-guarantees-critical",33,{critical:1}),statuses:{defender:5}},outgoing("healthy-not-critical",33)]);
    for(const [ability,name,species] of [[4,"battle-armor",452],[75,"shell-armor",366]] as const)
      add(196,`merciless-${name}`,33,[{...outgoing("poison-critical-prevented",33),statuses:{defender:5}}],{}, {abilityId:ability,defenderSpecies:species});
    add(196,"merciless-lucky-chant",33,[{...outgoing("lucky-chant-prevents-poison-critical",33),setupSlot:1,statuses:{defender:5}}],{moves:[33,150,182,164]}, {trainerMove:381});
    for(const [id,name] of [[183,"gooey"],[221,"tangling-hair"]] as const) {
      add(id,name,150,[{id:"contact-lowers-attacker-speed",mechanicAudit:{outgoing:[],incoming:[strike(33)],stages:{defender:stages(4,5)}}}],{}, {trainerMove:33});
      add(id,`${name}-noncontact`,150,[{id:"noncontact-no-speed-drop",mechanicAudit:{outgoing:[],incoming:[strike(129)],stages:{defender:neutral}}}],{}, {trainerMove:129});
    }
    add(192,"stamina",150,[{id:"damage-boosts-defense",mechanicAudit:{outgoing:[],incoming:[strike(33)],stages:{attacker:stages(1,7)}}},
      {id:"capped-no-overflow",userStages:stages(1,12),mechanicAudit:{outgoing:[],incoming:[strike(33)],stages:{attacker:stages(1,12)}}}],{}, {trainerMove:33});
    add(195,"water-compaction",150,[{id:"water-defense-plus-two",mechanicAudit:{outgoing:[],incoming:[strike(55)],stages:{attacker:stages(1,8)}}}],{}, {trainerMove:55});
    add(195,"water-compaction-control",150,[{id:"other-type-no-boost",mechanicAudit:{outgoing:[],incoming:[strike(129)],stages:{attacker:neutral}}}],{}, {trainerMove:129});
    add(172,"competitive",150,[{id:"opponent-drop-spatk-plus-two",mechanicAudit:{outgoing:[],incoming:[],stages:{attacker:[5,6,8,6,6,6,6]}}}],{}, {trainerMove:45});
    add(201,"berserk",150,[{id:"cross-half-spatk-plus-one",userCurrentHp:90,mechanicAudit:{outgoing:[],incoming:[strike(33)],stages:{attacker:stages(2,7)}}},
      {id:"already-below-half-no-boost",userCurrentHp:60,mechanicAudit:{outgoing:[],incoming:[strike(33)],stages:{attacker:neutral}}}],{}, {trainerMove:33});
    add(175,"sweet-veil",150,[{id:"sleep-blocked",mechanicAudit:{outgoing:[],incoming:[],statuses:{attacker:0}}}],{}, {trainerMove:95});
    add(165,"aroma-veil",150,[{id:"taunt-blocked",mechanicAudit:{outgoing:[],incoming:[],conditions:{attacker:{tauntCondition:false}}}}],{}, {trainerMove:269});
    add(165,"aroma-veil-control",150,[{id:"ordinary-ability-taunt-applies",mechanicAudit:{outgoing:[],incoming:[],conditions:{attacker:{tauntCondition:true}}}}],{abilityId:50}, {trainerMove:269});
    add(166,"flower-veil",150,[{id:"grass-stat-drop-blocked",mechanicAudit:{outgoing:[],incoming:[],stages:{attacker:neutral}}}],{speciesId:465}, {trainerMove:45});
    add(166,"flower-veil-status",150,[{id:"grass-status-blocked",mechanicAudit:{outgoing:[],incoming:[],statuses:{attacker:0}}}],{speciesId:465}, {trainerMove:86});
    add(166,"flower-veil-nongrass",150,[{id:"nongrass-not-protected",mechanicAudit:{outgoing:[],incoming:[],stages:{attacker:stages(0,5)}}}],{}, {trainerMove:45});
    for(const [id,name] of [[214,"queenly-majesty"],[219,"dazzling"]] as const) {
      add(id,name,150,[{id:"priority-blocked",mechanicAudit:{outgoing:[],incoming:[]}}],{}, {trainerMove:245});
      add(id,`${name}-control`,150,[incoming("ordinary-priority-allowed",33)],{}, {trainerMove:33});
    }
    add(177,"gale-wings",17,[{...outgoing("full-hp-priority",17),userStats:[100,100,100,100,1],mechanicAudit:{outgoing:[strike(17)],incoming:[strike(33)],order:"user-first"}},
      {id:"damaged-no-priority",userCurrentHp:150,userStats:[100,100,100,100,1],mechanicAudit:{outgoing:[strike(17)],incoming:[strike(33)],order:"opponent-first"}}],{}, {trainerMove:33});
    for(const [id,name,terrain] of [[226,"electric-surge",1],[227,"psychic-surge",4],[228,"misty-surge",3],[229,"grassy-surge",2]] as const)
      add(id,name,150,[{id:"switch-in-sets-terrain",mechanicAudit:{outgoing:[],incoming:[],terrain}}]);
    add(232,"prism-armor",150,[incoming("super-effective-quarter-reduction",44,{typeRatio:8192,finalRatio:3072})],{}, {trainerMove:44});
    add(232,"prism-armor-neutral",150,[incoming("neutral-unmodified",33)],{}, {trainerMove:33});
    add(230,"full-metal-body",150,[{id:"clear-body-alias-blocks-drop",mechanicAudit:{outgoing:[],incoming:[],stages:{attacker:neutral}}}],{}, {trainerMove:45});
    add(231,"shadow-shield",150,[incoming("full-hp-halved",33,{finalRatio:2048}),
      {...incoming("damaged-unmodified",33),userCurrentHp:150}],{}, {trainerMove:33});
    add(212,"corrosion",92,[{id:"steel-can-be-poisoned",mechanicAudit:{outgoing:[],incoming:[],statuses:{defender:5}}}],{}, {defenderSpecies:208});
    add(213,"comatose",150,[{id:"cannot-acquire-paralysis",mechanicAudit:{outgoing:[],incoming:[],statuses:{attacker:0}}}],{}, {trainerMove:86});
    add(186,"dark-aura",44,[outgoing("dark-power-four-thirds",44,{powerRatio:5448}),slot(1,33,outgoing("other-type-unmodified",33))],{moves:[44,33,150,182]});
    add(187,"fairy-aura",585,[outgoing("fairy-power-four-thirds",585,{powerRatio:5448}),slot(1,33,outgoing("other-type-unmodified",33))],{moves:[585,33,150,182]});
    add(188,"aura-break",44,[outgoing("opponents-dark-aura-inverted",44,{powerRatio:3072})],{}, {defenderSpecies:289,abilityId:186,abilitySlot:2});
    add(203,"long-reach",33,[{id:"gooey-retaliation-prevented",mechanicAudit:{outgoing:[strike(33)],incoming:[],stages:{attacker:neutral}}}],{}, {defenderSpecies:463,abilityId:183,abilitySlot:2});
    add(203,"long-reach-fluffy",33,[outgoing("fluffy-contact-reduction-bypassed",33)],{}, {defenderSpecies:242,abilityId:218,abilitySlot:2});
    add(170,"magician",33,[{id:"itemless-attacker-steals",mechanicAudit:{outgoing:[strike(33)],incoming:[],items:{attacker:158,defender:0},consumed:{attacker:0,defender:0}}}],{}, {defenderItemId:158});
    add(170,"magician-occupied",33,[{id:"held-item-prevents-steal",mechanicAudit:{outgoing:[strike(33)],incoming:[],items:{attacker:124,defender:158},consumed:{attacker:0,defender:0}}}],{itemId:124}, {defenderItemId:158});
    add(167,"cheek-pouch",150,[{id:"sitrus-plus-third-hp",userCurrentHp:100,mechanicAudit:{outgoing:[],incoming:[strike(33)],items:{attacker:0},consumed:{attacker:158},berryPouchHealing:true}},
      {id:"no-consumption-no-heal",mechanicAudit:{outgoing:[],incoming:[strike(33)],items:{attacker:158},consumed:{attacker:0}}}],{itemId:158}, {trainerMove:33});
    for(const [id,name,setup,playerSpecies] of [[202,"slush-rush",258,471],[207,"surge-surfer",604,151]] as const)
      add(id,name,33,[{id:"matching-field-doubles-speed",setupSlot:1,userStats:[100,100,100,100,70],mechanicAudit:{outgoing:[strike(33)],incoming:[strike(33)],order:"user-first"}},
        {id:"no-field-normal-speed",userStats:[100,100,100,100,70],mechanicAudit:{outgoing:[strike(33)],incoming:[strike(33)],order:"opponent-first"}}],{speciesId:playerSpecies,moves:[33,setup,150,182]}, {trainerMove:33});
    add(205,"triage",105,[{id:"recover-before-plus-two-priority",userCurrentHp:60,userStats:[100,100,100,100,1],mechanicAudit:{outgoing:[],incoming:[strike(245)],healHalfBeforeHit:true,actions:{attacker:{105:1},defender:{245:1}}}}],{}, {trainerMove:245});
    add(205,"triage-control",33,[{id:"nonhealing-no-priority",userStats:[100,100,100,100,1],mechanicAudit:{outgoing:[strike(33)],incoming:[strike(33)],order:"opponent-first"}}],{}, {trainerMove:33});
    add(176,"stance-change",33,[{id:"attack-changes-to-blade",mechanicAudit:{outgoing:[strike(33)],incoming:[],forms:{attacker:1}}},
      slot(1,588,{id:"kings-shield-restores-shield",setupSlot:0,mechanicAudit:{outgoing:[],incoming:[],beforeForms:{attacker:1},forms:{attacker:0}}})],{speciesId:681,moves:[33,588,150,182]});
    add(176,"stance-change-control",150,[{id:"status-keeps-shield",mechanicAudit:{outgoing:[],incoming:[],forms:{attacker:0}}}],{speciesId:681});
    add(197,"shields-down",150,[{id:"low-hp-exposes-core",userCurrentHp:10,mechanicAudit:{outgoing:[],incoming:[],beforeForms:{attacker:0},forms:{attacker:7}}},
      {id:"healthy-retains-meteor",mechanicAudit:{outgoing:[],incoming:[],forms:{attacker:0}}}],{speciesId:774});
    add(197,"shields-down-status",150,[{id:"meteor-prevents-status",mechanicAudit:{outgoing:[],incoming:[],forms:{attacker:0},statuses:{attacker:0}}}],{speciesId:774}, {trainerMove:95});
    add(197,"shields-down-core-status",150,[{id:"core-can-be-paralyzed",mechanicAudit:{outgoing:[],incoming:[],forms:{attacker:7},statuses:{attacker:1}}}],{speciesId:774,form:7,currentHp:10}, {trainerMove:86});
    add(197,"shields-down-boundary",150,[{id:"exact-half-exposes-core",userCurrentHp:70,mechanicAudit:{outgoing:[],incoming:[],forms:{attacker:7}}}],{speciesId:774,level:52});
    add(197,"shields-down-heal",105,[{id:"healing-restores-meteor",mechanicAudit:{outgoing:[],incoming:[],beforeForms:{attacker:7},forms:{attacker:0}}}],{speciesId:774,form:7,currentHp:10});
    add(208,"schooling",150,[{id:"healthy-school-form",mechanicAudit:{outgoing:[],incoming:[],forms:{attacker:1}}},
      {id:"low-hp-solo-form",userCurrentHp:10,mechanicAudit:{outgoing:[],incoming:[],beforeForms:{attacker:1},forms:{attacker:0}}}],{speciesId:746});
    add(208,"schooling-low-level",150,[{id:"below-level-twenty-stays-solo",mechanicAudit:{outgoing:[],incoming:[],forms:{attacker:0}}}],{speciesId:746,level:19});
    add(211,"power-construct",150,[{id:"below-half-complete-hp-pool",userCurrentHp:10,mechanicAudit:{outgoing:[],incoming:[],beforeForms:{attacker:0},forms:{attacker:2},hpPoolGrowth:"attacker"}},
      {id:"healthy-retains-fifty-percent",mechanicAudit:{outgoing:[],incoming:[],forms:{attacker:0}}}],{speciesId:718});
    add(211,"power-construct-control",150,[{id:"wrong-species-cannot-change",userCurrentHp:10,mechanicAudit:{outgoing:[],incoming:[],forms:{attacker:0}}}]);
    add(209,"disguise",55,[{id:"first-hit-busts-without-hp-cost",mechanicAudit:{outgoing:[strike(55,{absorbed:true})],incoming:[],forms:{defender:1}}}],{abilityId:50},{defenderSpecies:778,defenderForm:0,abilityId:209});
    add(209,"disguise-busted",55,[{id:"busted-form-takes-normal-damage",mechanicAudit:{outgoing:[strike(55)],incoming:[],forms:{defender:1}}}],{abilityId:50},{defenderSpecies:778,defenderForm:1,abilityId:209});
    const doubles = (ally:Partial<HarnessPokemon>={}) => {
      const v=variants.at(-1)!;const partner:HarnessPokemon={speciesId:149,level:50,abilityId:50,moves:[150],...ally};
      Object.assign(v,{battleType:"Doubles",allyPlayer:partner,allySpecies:partner.speciesId,allyAbilityId:partner.abilityId,
        allyMoves:partner.moves,allyLevel:partner.level,defenderAllySpecies:242,defenderAllyAbilityId:50,defenderAllyMove:150});
    };
    add(217,"battery",55,[{id:"ally-special-thirty-percent",mechanicAudit:{outgoing:[strike(55,{attackRatio:5325,targetRole:"defender"})],incoming:[]}},
      slot(1,33,{id:"ally-physical-unmodified",mechanicAudit:{outgoing:[strike(33,{targetRole:"defender"})],incoming:[]}})],{abilityId:50,moves:[55,33,150,182]});doubles({abilityId:217});
    add(217,"battery-self",129,[{id:"holder-does-not-boost-itself",mechanicAudit:{outgoing:[strike(129)],incoming:[]}}]);
    add(216,"dancer",14,[{id:"copies-ally-dance-without-extra-pp",mechanicAudit:{outgoing:[],incoming:[],stages:{attacker:stages(0,8),ally:stages(0,8)},actions:{attacker:{14:1},ally:{14:1,150:1}}}}],{abilityId:50});doubles({abilityId:216});
    add(216,"dancer-control",150,[{id:"nondance-not-copied",mechanicAudit:{outgoing:[],incoming:[],stages:{attacker:neutral,ally:neutral},actions:{attacker:{150:1},ally:{150:1}}}}],{abilityId:50});doubles({abilityId:216});
    add(180,"symbiosis",164,[{id:"berry-use-transfers-donors-item",userCurrentHp:80,mechanicAudit:{outgoing:[],incoming:[],items:{attacker:234,ally:0},consumed:{attacker:158,ally:0},symbiosisSubstitute:true}}],{abilityId:50,itemId:158});doubles({abilityId:180,itemId:234});
    add(180,"symbiosis-control",164,[{id:"no-ability-no-item-transfer",userCurrentHp:80,mechanicAudit:{outgoing:[],incoming:[],items:{attacker:0,ally:234},consumed:{attacker:158,ally:0},symbiosisSubstitute:true}}],{abilityId:50,itemId:158});doubles();variants.at(-1)!.allyPlayer!.itemId=234;
    for(const [id,name] of [[222,"receiver"],[223,"power-of-alchemy"]] as const) {
      add(id,name,182,[{id:"copies-fainted-ally-ability",expectedAbilities:{attacker:50},mechanicAudit:{outgoing:[],incoming:[strike(153,{spread:true,targetRole:"defender"}),strike(153,{spread:true,targetRole:"defenderAlly"})],abilities:{attacker:50},hpExact:{ally:0},actions:{ally:{153:1}}}}]);doubles({level:1,moves:[153]});
      add(id,`${name}-control`,150,[{id:"living-ally-not-copied",mechanicAudit:{outgoing:[],incoming:[],abilities:{attacker:id}}}]);doubles();
    }
    add(220,"soul-heart",182,[{id:"allied-faint-boosts-spatk",mechanicAudit:{outgoing:[],incoming:[strike(153,{spread:true,targetRole:"defender"}),strike(153,{spread:true,targetRole:"defenderAlly"})],stages:{attacker:stages(2,7)},hpExact:{ally:0},actions:{ally:{153:1}}}}]);doubles({level:1,moves:[153]});
    for(const [id,name] of [[224,"beast-boost"],[220,"soul-heart"],[210,"battle-bond"]] as const) {
      add(id,`${name}-ko`,55,[{id:"opponent-ko-triggers-ability",hp:{defender:1},userStats:[100,100,250,100,200],mechanicAudit:{outgoing:[strike(55)],incoming:[],foeActions:{defender:0},hpExact:{defender:0},
        ...(id===210?{forms:{attacker:2}}:{stages:{attacker:stages(2,7)}})}},
        {id:"surviving-target-no-trigger",userStats:[100,100,250,100,200],mechanicAudit:{outgoing:[strike(55)],incoming:[],...(id===210?{forms:{attacker:0}}:{stages:{attacker:neutral}})}}],id===210?{speciesId:658}:{});doubles();
    }
    add(215,"innards-out",33,[{id:"ko-retaliates-pre-hit-hp",hp:{defender:15},mechanicAudit:{outgoing:[strike(33)],incoming:[],foeActions:{defender:0},directLoss:{attacker:15},hpExact:{defender:0}}},
      {id:"survival-no-retaliation",mechanicAudit:{outgoing:[strike(33)],incoming:[]}}],{abilityId:50},{defenderSpecies:771,abilityId:215});doubles();
    for(const [id,name] of [[193,"wimp-out"],[194,"emergency-exit"]] as const) {
      add(id,name,150,[{id:"cross-half-forces-native-replacement",userCurrentHp:90,pivotChoice:1,sourceExit:true,mechanicAudit:{outgoing:[],incoming:[strike(33)],expectedPivot:true}},
        {id:"already-low-no-repeat-switch",userCurrentHp:60,mechanicAudit:{outgoing:[],incoming:[strike(33)],expectedPivot:false}},
        {id:"still-above-half-no-switch",mechanicAudit:{outgoing:[],incoming:[strike(33)],expectedPivot:false}}],{}, {trainerMove:33,incomingAttackerSpecies:149});
      variants.at(-1)!.benchPlayer={speciesId:149,level:50,abilityId:50,moves:[150]};
    }
    add(179,"grass-pelt",150,[{id:"grassy-physical-defense-one-and-half",setupSlot:1,mechanicAudit:{outgoing:[],incoming:[strike(33,{defenseRatio:6144})],terrain:2,terrainHealing:["attacker"]}},
      incoming("no-terrain-physical-unmodified",33)],{moves:[150,580,182,164]}, {trainerMove:33});
    add(179,"grass-pelt-special",150,[{id:"grassy-special-unmodified",setupSlot:1,mechanicAudit:{outgoing:[],incoming:[strike(55)],terrain:2,terrainHealing:["attacker"]}}],{moves:[150,580,182,164]}, {trainerMove:55});
    add(185,"parental-bond",33,[{id:"gen-seven-quarter-final-damage",mechanicAudit:{outgoing:[strike(33),strike(33,{finalRatio:1024})],incoming:[]},
      followup:{slot:0,moveId:33,power:50,category:1,type:0,case:{id:"new-action-resets-second-hit",completeTurn:true,ppSpent:1,mechanicAudit:{outgoing:[strike(33),strike(33,{finalRatio:1024})],incoming:[]}}}},
      slot(1,150,{id:"status-no-extra-action",mechanicAudit:{outgoing:[],incoming:[],actions:{attacker:{150:1}}}})],{moves:[33,150,182,164]});
    add(185,"parental-bond-fixed",69,[{id:"fixed-damage-both-hits-full-level",mechanicAudit:{outgoing:[strike(69,{fixedByLevel:true}),strike(69,{fixedByLevel:true})],incoming:[]}}]);
    add(185,"parental-bond-multistrike",24,[{id:"native-two-hit-move-not-reduced-or-extended",mechanicAudit:{outgoing:[strike(24,{typeRatio:8192}),strike(24,{typeRatio:8192})],incoming:[]}}]);
    add(198,"stakeout",33,[{id:"native-u-turn-replacement-double-attack",userStats:[100,100,100,100,1],mechanicAudit:{outgoing:[strike(33,{attackRatio:8192})],incoming:[strike(369,{typeRatio:8192})],replacementThisTurn:true}},
      {id:"prior-turn-replacement-no-boost",setupSlot:1,userStats:[100,100,100,100,1],mechanicAudit:{outgoing:[strike(33)],incoming:[],replacementThisTurn:false}}],{moves:[33,150,182,164]}, {trainerMove:369,bench:true,incomingSpecies:242,benchMove:150});
    add(198,"stakeout-initial",33,[outgoing("initial-sendout-not-a-switch",33)]);
  } else {
    add(115,"terrain-extender",604,[{id:"eight-turns-including-creation",residualTurns:7,
      mechanicAudit:{outgoing:[],incoming:[],items:{attacker:115},terrainTimeline:[7,6,5,4,3,2,1,0]}}]);
    add(115,"terrain-extender-control",604,[{id:"without-extender-five-turns",residualTurns:4,
      mechanicAudit:{outgoing:[],incoming:[],items:{attacker:0},terrainTimeline:[4,3,2,1,0]}}],{itemId:0});
    add(121,"assault-vest",150,[incoming("special-defense-one-and-half",129,{defenseRatio:6144})],{moves:[33,150,182,164]}, {trainerMove:129});
    // Select an attack: Assault Vest must not accidentally forbid the fixture's command.
    variants.at(-1)!.moveId=33;variants.at(-1)!.definition=mechanicMoves[33];
    variants.at(-1)!.cases[0].mechanicAudit!.outgoing=[strike(33)];
    add(121,"assault-vest-physical",33,[{id:"physical-unmodified",mechanicAudit:{outgoing:[strike(33)],incoming:[strike(33)]}}],{}, {trainerMove:33});
    add(121,"assault-vest-selection",150,[{id:"status-selection-rejected",selectionRejected:true,mechanicAudit:{outgoing:[],incoming:[]}}]);
    for(const [item,name,move,stat] of [[122,"luminous-moss",55,3],[128,"snowball",58,0],[123,"maranga-berry",129,3]] as const) {
      add(item,name,150,[{id:"eligible-hit-consumes-and-boosts",mechanicAudit:{outgoing:[],incoming:[strike(move)],stages:{attacker:stages(stat,7)},items:{attacker:0},consumed:{attacker:item}}},
        {id:"stat-capped-retains-item",userStages:stages(stat,12),mechanicAudit:{outgoing:[],incoming:[strike(move)],stages:{attacker:stages(stat,12)},items:{attacker:item},consumed:{attacker:0}}}],{}, {trainerMove:move});
      add(item,`${name}-wrong-hit`,150,[{id:"ineligible-hit-retains-item",mechanicAudit:{outgoing:[],incoming:[strike(33)],stages:{attacker:neutral},items:{attacker:item},consumed:{attacker:0}}}],{}, {trainerMove:33});
    }
    add(129,"weakness-policy",150,[{id:"super-effective-consumes-plus-two",mechanicAudit:{outgoing:[],incoming:[strike(44,{typeRatio:8192})],stages:{attacker:[8,6,8,6,6,6,6]},items:{attacker:0},consumed:{attacker:129}}}],{}, {trainerMove:44});
    add(129,"weakness-policy-neutral",150,[{id:"neutral-retains-item",mechanicAudit:{outgoing:[],incoming:[strike(33)],stages:{attacker:neutral},items:{attacker:129},consumed:{attacker:0}}}],{}, {trainerMove:33});
    add(126,"roseli-berry",150,[incoming("super-effective-fairy-halved",585,{typeRatio:8192,finalRatio:2048})],{speciesId:197}, {trainerMove:585});
    variants.at(-1)!.cases[0].mechanicAudit!.items={attacker:0};
    variants.at(-1)!.cases[0].mechanicAudit!.consumed={attacker:126};
    add(126,"roseli-neutral",150,[{id:"neutral-fairy-retains-berry",mechanicAudit:{outgoing:[],incoming:[strike(585)],items:{attacker:126},consumed:{attacker:0}}}],{}, {trainerMove:585});
    add(127,"safety-goggles",150,[{id:"powder-sleep-blocked",mechanicAudit:{outgoing:[],incoming:[],statuses:{attacker:0},items:{attacker:127}}}],{}, {trainerMove:79});
    add(127,"safety-goggles-sand",150,[{id:"sand-damage-prevented",setupSlot:1,mechanicAudit:{outgoing:[],incoming:[],weatherImmune:true,items:{attacker:127}}}],{moves:[150,201,182,164]});
    add(114,"protective-pads",33,[{id:"contact-retaliation-blocked",mechanicAudit:{outgoing:[strike(33)],incoming:[],stages:{attacker:neutral},items:{attacker:114}}}],{}, {defenderSpecies:463,abilityId:183,abilitySlot:2});
    for(const [id,name,terrain,move,stat] of [[485,"electric-seed",1,604,1],[486,"grassy-seed",2,580,1],
      [487,"psychic-seed",4,678,3],[488,"misty-seed",3,581,3]] as const) {
      add(id,name,move,[{id:"terrain-consumes-correct-stat-plus-one",mechanicAudit:{outgoing:[],incoming:[],terrain,stages:{attacker:stages(stat,7)},items:{attacker:0},consumed:{attacker:id}}},
        {id:"stat-cap-retains-seed",userStages:stages(stat,12),mechanicAudit:{outgoing:[],incoming:[],terrain,stages:{attacker:stages(stat,12)},items:{attacker:id},consumed:{attacker:0}}},
        slot(1,150,{id:"no-terrain-retains-seed",mechanicAudit:{outgoing:[],incoming:[],stages:{attacker:neutral},items:{attacker:id},consumed:{attacker:0}}})]);
    }
  }
  const ids = new Set(variants.map(v=>v.mechanic.id));
  const declared = kind === "ability" ? [...inventory.coveredAbilityIds,...inventory.scheduledAbilityIds] : inventory.coveredItems.map(item=>item.id);
  if(ids.size !== declared.length || declared.some(id=>!ids.has(id)))throw new Error("Mechanic coverage inventory does not match the executable suite");
  if(new Set(variants.map(v=>v.name)).size !== variants.length)throw new Error("Duplicate mechanic fixture name");
  return variants;
}
