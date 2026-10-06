/** Four independent native trainer parties; the partner is controlled by AI. */
import type { HarnessPokemon } from "@pokeweb/pokeweb/battleHarness";
import type { MoveCase, Variant } from "./build-move-handler-fixtures";

export type MultiCase = {
  expectedActingSlot?: number;
  expectedPlayerSpecies?: number;
  expectedMultiPower?: number;
  expectedRevivedOriginal?: boolean;
  expectedPartnerHits?: boolean;
};
export type MultiVariant = Variant & {
  battleType: "Multi";
  player: HarnessPokemon;
  benchPlayer: HarnessPokemon;
  partnerTrainerId: number;
  secondTrainerId: number;
};

export function multiVariants(): MultiVariant[] {
  const player: HarnessPokemon = {speciesId:151,level:100,abilityId:50,
    moves:[889,150,226,182],itemId:0};
  const benchPlayer: HarnessPokemon = {speciesId:149,level:100,abilityId:50,
    moves:[889,150,226,863],itemId:0};
  const waits = (count:number) => Array.from({length:count},() =>
    ({slot:1,case:{id:"receive-native-swift",accuracyRoll:0,incomingAccuracyRoll:0}}));
  const pivot = (choice:number) => ({slot:2,case:{id:"native-baton-pass",
    pivotChoice:choice,sourceExit:true,accuracyRoll:0,incomingAccuracyRoll:0}});
  const finish = (id:string,power:number,extra:MoveCase={id}) => ({
    completeTurn:true,accuracyRoll:0,incomingAccuracyRoll:0,secondaryRoll:99,
    targetRole:"defenderAlly" as const,expectedMultiPower:power,...extra,id});
  const base = {battleType:"Multi" as const,abilityId:50,trainerMove:129,
    playerAbilityId:50,playerSpecies:151,allySpecies:25,allyAbilityId:50,
    allyMoves:[150],allyLevel:100,defenderSpecies:129,defenderLevel:50,
    defenderAllySpecies:442,defenderAllyAbilityId:50,defenderAllyMove:150,
    defenderAllyLevel:100,trainerBagItems:[0,0,0,0],player,benchPlayer};
  return [
    {...base,name:"history",trainerId:1,partnerTrainerId:2,secondTrainerId:3,
     save:"battle-multi-history.sav",cases:[
       ...[0,1,2,6,7].map(hits=>finish(`multi-${hits}-hits`,Math.min(350,50+50*hits),
         {id:"history",setupCommands:waits(hits)})),
       finish("partner-hits-do-not-boost-player",50,
         {id:"partner-isolation",setupSlots:[3],setupAccuracyRoll:0,expectedPartnerHits:true}),
       finish("new-party-member-does-not-inherit-history",100,
         {id:"fresh-member",setupCommands:[...waits(2),pivot(1)],expectedActingSlot:1,expectedPlayerSpecies:149}),
       finish("switch-back-preserves-original-history",200,
         {id:"return-member",setupCommands:[...waits(2),pivot(1),pivot(0)]}),
       finish("faint-revive-switch-back-preserves-history",150,
         {id:"revive-member",hp:{attacker:1},setupCommands:[
           {slot:1,case:{id:"native-faint-and-replacement",pivotChoice:1}},
           {slot:3,case:{id:"native-revival",revivalChoice:0}},pivot(0)],
          expectedRevivedOriginal:true}),
     ]},
  ];
}
