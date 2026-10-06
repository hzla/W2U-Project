/** Focused native coverage for the remaining non-item-dependent move effects. */
import type { HarnessPokemon } from "@pokeweb/pokeweb/battleHarness";
import type { MoveCase, Variant } from "./build-move-handler-fixtures";

export const remainingDefinitions = {
  "thousand-arrows": {id:614,constant:"MOVE_THOUSAND_ARROWS",module:"moves/type",handler:"ThousandArrowsHandlers",type:4,power:90,category:1,accuracy:100,target:5},
  "thousand-waves": {id:615,constant:"MOVE_THOUSAND_WAVES",module:"moves/trapping",handler:"ThousandWavesHandlers",type:4,power:90,category:1,accuracy:100,target:5},
  "hyperspace-hole": {id:593,constant:"MOVE_HYPERSPACE_HOLE",module:"moves/guards",handler:"HyperspaceHoleHandlers",type:13,power:80,category:2,accuracy:101,target:0},
  "hyperspace-fury": {id:621,constant:"MOVE_HYPERSPACE_FURY",module:"moves/guards",handler:"HyperspaceFuryHandlers",type:16,power:100,category:1,accuracy:101,target:0},
  "fairy-lock": {id:587,constant:"MOVE_FAIRY_LOCK",module:"moves/trapping",handler:"FairyLockHandlers",type:17,power:0,category:0,accuracy:101,target:10},
  "gear-up": {id:674,constant:"MOVE_GEAR_UP",module:"moves/stats",handler:"MagneticFluxHandlers",type:8,power:0,category:0,accuracy:101,target:7},
  "psychic-fangs": {id:706,constant:"MOVE_PSYCHIC_FANGS",module:"moves/screens",handler:"BrickBreakAuroraVeilHandlers",type:13,power:85,category:1,accuracy:100,target:0},
  "order-up": {id:856,constant:"MOVE_ORDER_UP",module:"moves/stats",handler:"OrderUpHandlers",type:15,power:80,category:1,accuracy:100,target:0},
};
const stages = (...changes:[number,number][]) => changes.reduce((values,[index,value])=>{values[index]=value;return values;},Array(7).fill(6) as number[]);
type Definition = typeof remainingDefinitions[keyof typeof remainingDefinitions];
type AuditVariant = Variant & {player:HarnessPokemon;allyPlayer?:HarnessPokemon;benchPlayer?:HarnessPokemon;definition:Definition};

export function remainingVariants(name:string): AuditVariant[] {
  if (!Object.hasOwn(remainingDefinitions,name)) return [];
  const definition = remainingDefinitions[name as keyof typeof remainingDefinitions];
  const variants:AuditVariant[]=[];
  function add(label:string,cases:MoveCase[],player:Partial<HarnessPokemon>={},npc:Partial<Variant>={},ally?:Partial<HarnessPokemon>) {
    const user:HarnessPokemon={speciesId:151,level:50,abilityId:50,moves:[definition.id,150,89,164],itemId:0,...player};
    const partner=ally&&{speciesId:149,level:50,abilityId:50,moves:[150],...ally};
    variants.push({name:label,trainerId:variants.length+1,definition,moveId:definition.id,player:user,
      playerSpecies:user.speciesId,playerForm:user.form,playerAbilityId:user.abilityId!,save:`battle-${label}.sav`,
      abilityId:50,trainerMove:150,trainerBagItems:[0,0,0,0],defenderSpecies:143,
      battleType:partner?"Doubles":"Singles",allyPlayer:partner,allySpecies:partner?.speciesId,
      allyAbilityId:partner?.abilityId,allyMoves:partner?.moves,defenderAllySpecies:242,defenderAllyAbilityId:50,
      ...npc,cases:cases.map(c=>({completeTurn:true,accuracyRoll:0,incomingAccuracyRoll:0,secondaryRoll:99,ppSpent:1,...c}))});
  }
  const hit=(id:string,power=definition.power,typeRatio=4096):MoveCase=>({id,audit:{powers:[power],typeRatio}});
  const blocked=(id:string):MoveCase=>({id,audit:{noDamage:true}});
  const ground=(id:string,ratio=4096):MoveCase=>({id,audit:{powers:[90],typeRatio:ratio,conditions:{defender:{knockedDownCondition:true}}}});
  const trap=(id:string):MoveCase=>({id,audit:{powers:[90],trapSource:true,conditions:{defender:{trapCondition:true}}}});
  if(name==="thousand-arrows") {
    add("flying",[{...ground("airborne-fire-flying-neutral"),followup:{slot:2,moveId:89,power:100,type:4,category:1,
      case:{id:"grounded-fire-flying-super-effective",completeTurn:true,accuracyRoll:0,secondaryRoll:99,audit:{powers:[100],typeRatio:8192}}}}],{}, {defenderSpecies:6});
    add("levitate",[ground("levitate-grounded")],{}, {abilityId:26,abilitySlot:2});
    add("balloon",[{...hit("balloon-popped-and-grounded"),audit:{powers:[90],items:{defender:0}},
      followup:{slot:2,moveId:89,power:100,type:4,category:1,case:{id:"popped-balloon-no-ground-immunity",completeTurn:true,accuracyRoll:0,secondaryRoll:99,audit:{powers:[100]}}}}],{}, {defenderItemId:541});
    add("magnet-rise",[{...ground("magnet-rise-removed"),setupSlot:1}],{}, {trainerMove:393});
    add("fly",[{...ground("fly-hit-and-cancelled"),userStats:[100,100,100,100,1],audit:{...ground("x").audit,conditionFlags:{defender:{clear:1<<3}}}}],{}, {defenderSpecies:6,trainerMove:19});
    add("dig",[{...blocked("dig-still-unreachable"),userStats:[100,100,100,100,1]}],{moves:[614,150,89,164]}, {trainerMove:91});
    add("protect",[blocked("protect-blocks-grounding")],{}, {trainerMove:182});
    add("substitute",[{...hit("substitute-not-grounded"),setupSlot:1,audit:{powers:[90],beforeSubstitute:{defender:true},conditions:{defender:{knockedDownCondition:false}}}}],{}, {trainerMove:164});
    add("spread",[{id:"two-targets-grounded",audit:{powers:[90,90],spread:true,conditions:{defender:{knockedDownCondition:true},defenderAlly:{knockedDownCondition:true}}}}],{}, {defenderSpecies:6,defenderAllySpecies:149},{});
    add("sheer-force",[ground("primary-grounding-not-sheer-force-secondary")],{abilityId:125},{defenderSpecies:6});
  } else if(name==="thousand-waves") {
    add("ordinary",[trap("source-linked-trap")]);
    add("ghost",[{...hit("ghost-damaged-not-trapped"),audit:{powers:[90],conditions:{defender:{trapCondition:false}}}}],{}, {defenderSpecies:623});
    add("shield-dust",[trap("primary-trap-ignores-shield-dust")],{}, {abilityId:19,abilitySlot:2});
    add("sheer-force",[trap("primary-trap-survives-sheer-force")],{abilityId:125});
    add("substitute",[{...hit("substitute-no-trap"),setupSlot:1,audit:{powers:[90],beforeSubstitute:{defender:true},conditions:{defender:{trapCondition:false}}}}],{}, {trainerMove:164});
    add("protect",[blocked("protect-no-trap")],{}, {trainerMove:182});
    add("spread",[{id:"two-opponents-trapped",audit:{powers:[90,90],spread:true,conditions:{defender:{trapCondition:true},defenderAlly:{trapCondition:true}},trapSource:true}}],{}, {},{});
    add("source-exit",[{id:"source-exit-releases-trap",sourceExit:true,audit:{powers:[90],conditions:{defender:{trapCondition:false}}}}],{},{trainerMove:46,incomingAttackerSpecies:149});
    variants.at(-1)!.benchPlayer={speciesId:149,level:50,abilityId:50,moves:[150]};
  } else if(name.startsWith("hyperspace-")) {
    const fury=name==="hyperspace-fury",user:Partial<HarnessPokemon>=fury?{speciesId:720,form:1}:{};
    const damage=(id:string):MoveCase=>({...hit(id),bypassSubstitute:true,
      audit:{powers:[definition.power],accuracyThreshold:0,...(fury?{stages:{attacker:stages([1,5])}}:{})}});
    add("ordinary",[damage("ordinary-hit")],user);
    add("protect",[damage("protect-broken")],user,{trainerMove:182});
    add("detect",[damage("detect-broken")],user,{trainerMove:197});
    add("kings-shield",[damage("custom-guard-broken")],user,{trainerMove:588});
    add("spiky-shield",[{...damage("spiky-shield-no-contact-punishment"),audit:{...damage("x").audit,hpChange:{attacker:0}}}],user,{trainerMove:596});
    add("baneful-bunker",[{...damage("baneful-bunker-no-poison"),audit:{...damage("x").audit,statuses:{attacker:0}}}],user,{trainerMove:661});
    add("mat-block",[damage("mat-block-broken")],user,{trainerMove:561});
    add("substitute",[{...damage("substitute-bypassed"),setupSlot:1,audit:{...damage("x").audit,beforeSubstitute:{defender:true}}}],user,{trainerMove:164});
    add("break-followup",[{...damage("ally-attack-after-protect-broken"),userStats:[80,100,80,100,300],audit:{...damage("x").audit,
      incomingTargets:[{source:"ally",target:"defender",move:129,count:1},{source:"ally",target:"defenderAlly",move:129,count:1}]}}],user,{trainerMove:182},{moves:[129]});
    if(fury) {
      add("confined",[blocked("hoopa-confined-fails")],{speciesId:720,form:0});
      add("other-species",[blocked("non-hoopa-fails")]);
      add("transformed",[{...damage("transformed-hoopa-unbound-can-use"),setupSlot:1,targetStats:[20,100,100,100,60]}],{moves:[621,144,150,182]},{defenderSpecies:720,defenderForm:1,trainerMove:621});
    } else {
      add("dark",[blocked("dark-immunity-remains")],{}, {defenderSpecies:197});
    }
  } else if(name==="fairy-lock") {
    // The client switch checker is observed after the native POKEMON button;
    // no test assigns a trapping flag or calls the checker directly.
    add("ordinary",[{id:"locks-next-turn-then-expires",checkSwitch:true,audit:{noDamage:true,switchBlocked:true},
      followup:{slot:1,moveId:150,power:0,type:0,category:0,case:{id:"expires-after-next-turn",completeTurn:true,checkSwitch:true,audit:{noDamage:true,switchBlocked:false}}}}],{moves:[587,150,182,164]});
    add("ghost",[{id:"ghost-can-switch",checkSwitch:true,audit:{noDamage:true,switchBlocked:false}}],{speciesId:94,moves:[587,150,182,164]});
    add("shed-shell",[{id:"shed-shell-can-switch",checkSwitch:true,audit:{noDamage:true,switchBlocked:false}}],{itemId:295,moves:[587,150,182,164]});
    add("repeat",[{id:"cannot-refresh-active-lock",audit:{noDamage:true},followup:{slot:0,moveId:587,power:0,type:17,category:0,
      case:{id:"repeat-does-not-extend",completeTurn:true,checkSwitch:true,audit:{noDamage:true,switchBlocked:false}}}}],{moves:[587,150,182,164]});
    for(const variant of variants) variant.benchPlayer={speciesId:149,level:50,abilityId:50,moves:[150]};
  } else if(name==="gear-up") {
    add("plus",[{id:"plus-attack-spatk-only",audit:{noDamage:true,stages:{attacker:stages([0,7],[2,7])}}}],{abilityId:57});
    add("minus",[{id:"minus-attack-spatk-only",audit:{noDamage:true,stages:{attacker:stages([0,7],[2,7])}}}],{abilityId:58});
    add("ineligible",[{id:"no-eligible-no-boost",audit:{noDamage:true,stages:{attacker:stages()}}}]);
    add("capped",[{id:"capped-no-overflow",userStages:stages([0,12],[2,12]),audit:{noDamage:true,stages:{attacker:stages([0,12],[2,12])}}}],{abilityId:57});
    add("suppressed",[{id:"suppressed-plus-not-eligible",setupSlot:1,audit:{noDamage:true,conditions:{attacker:{gastroAcidCondition:true}},stages:{attacker:stages()}}}],{abilityId:57},{trainerMove:380});
    add("both-allies",[{id:"eligible-allies-not-opponents",audit:{noDamage:true,stages:{attacker:stages([0,7],[2,7]),ally:stages([0,7],[2,7]),defender:stages(),defenderAlly:stages()}}}],{abilityId:57},{abilityId:57,abilitySlot:2},{abilityId:58});
    add("only-ally",[{id:"ineligible-user-eligible-ally",audit:{noDamage:true,stages:{attacker:stages(),ally:stages([0,7],[2,7])}}}],{},{},{abilityId:57});
  } else if(name==="psychic-fangs") {
    for(const [label,move,effect] of [["reflect",115,"0"],["light-screen",113,"1"]] as const) {
      add(label,[{...hit("screen-removed-before-damage"),setupSlot:1,audit:{powers:[85],beforeScreens:[{}, {[effect]:1}],actionScreens:[{},{}]}}],{},{trainerMove:move});
    }
    add("substitute",[{...hit("screen-removed-through-substitute"),setupSlots:[1,1],audit:{powers:[85],beforeSubstitute:{defender:true},beforeScreens:[{}, {"0":1}],screens:[{},{}]}}],{moves:[706,115,113,756]}, {trainerMove:164});
    // Establish our screen natively, then transfer it before the attack.
    variants.at(-1)!.cases[0].setupSlots=[1,3];
    // Taunt stops the foe immediately re-establishing Veil in the same
    // animation-free frame as our action checkpoint. It does not remove it.
    add("veil",[{...hit("veil-removed-before-damage"),setupSlots:[1,2],audit:{powers:[85],beforeCustomSides:[{}, {"15":1}],actionCustomSides:[{},{}],conditions:{defender:{tauntCondition:true}}}}],{moves:[706,258,269,150]},{trainerMove:694});
    add("both-screens",[{...hit("both-screens-removed"),setupSlots:[1,2,3],audit:{powers:[85],beforeScreens:[{}, {"0":1,"1":1}],screens:[{},{}]}}],{moves:[706,115,113,756]});
    add("protect",[blocked("protect-blocks-screen-break")],{}, {trainerMove:182});
    add("ordinary",[hit("ordinary-damage")]);
    add("miss",[{...blocked("miss-preserves-screen"),setupSlot:1,accuracyStage:0,accuracyRoll:99,audit:{noDamage:true,beforeScreens:[{}, {"0":1}],actionScreens:[{}, {"0":1}]}}],{},{trainerMove:115});
    add("dark",[{...blocked("immunity-preserves-screen"),setupSlot:1,audit:{noDamage:true,beforeScreens:[{}, {"0":1}],actionScreens:[{}, {"0":1}]}}],{},{defenderSpecies:197,trainerMove:115});
  } else if(name==="order-up") {
    add("uncommanded",[{...hit("no-commander-no-boost"),audit:{powers:[80],stages:{attacker:stages()}}}],{speciesId:977});
    for(const [label,form,stat] of [["curly",0,0],["droopy",1,1],["stretchy",2,4]] as const) {
      add(label,[{id:"commanded-form-boost",audit:{powers:[80],stages:{attacker:stages([0,8],[1,8],[2,8],[3,8],[4,8],[stat,9])}}}],
        {speciesId:977},{},{speciesId:978,form,abilityId:279});
    }
    add("commanded-protect",[{id:"protect-no-order-boost",audit:{noDamage:true,stages:{attacker:stages([0,8],[1,8],[2,8],[3,8],[4,8])}}}],{speciesId:977},{trainerMove:182},{speciesId:978,abilityId:279});
    add("commanded-fairy",[{id:"fairy-immunity-no-order-boost",audit:{noDamage:true,stages:{attacker:stages([0,8],[1,8],[2,8],[3,8],[4,8])}}}],{speciesId:977},{defenderSpecies:700},{speciesId:978,abilityId:279});
    add("commanded-substitute",[{...hit("substitute-still-boosts"),setupSlot:1,audit:{powers:[80],beforeSubstitute:{defender:true},stages:{attacker:stages([0,9],[1,8],[2,8],[3,8],[4,8])}}}],{speciesId:977},{trainerMove:164},{speciesId:978,abilityId:279});
    add("sheer-force",[{...hit("sheer-force-power-and-order-boost"),audit:{powers:[80],effectivePowers:[104],stages:{attacker:stages([0,9],[1,8],[2,8],[3,8],[4,8])}}}],{speciesId:977,abilityId:125},{},{speciesId:978,abilityId:279});
    add("commanded-miss",[{...blocked("miss-no-order-boost"),accuracyStage:0,accuracyRoll:99,audit:{noDamage:true,stages:{attacker:stages([0,8],[1,8],[2,8],[3,8],[4,8],[5,0])}}}],{speciesId:977},{},{speciesId:978,abilityId:279});
    add("commanded-capped",[{...hit("capped-order-boost-no-overflow"),userStats:[40,100,100,100,100],userStages:stages([0,12],[1,8],[2,8],[3,8],[4,8]),
      audit:{powers:[80],stages:{attacker:stages([0,12],[1,8],[2,8],[3,8],[4,8])}}}],{speciesId:977},{},{speciesId:978,abilityId:279});
  }
  return variants;
}
