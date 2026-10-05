// Ported from MegaB2W2 (src/patches/MegaEvolution/abilities/MoveAbilities.cpp); see docs/megab2w2-integration.md.
// Abilities that change how the holder's own moves work (Gen 9 / Showdown), one file, three logic names:
//   Mycelium Might    Status moves go last in their priority bracket (event 0x0F, var 0x11 = 0; the move from the
//                     resident core, as Quick Draw) and ignore the target's ability (vanilla Mold Breaker's start /
//                     end handlers, called only for status moves).
//   Poison Puppeteer  A Pokemon the holder poisons (or badly poisons) also becomes confused (event 0x68: the status
//                     was inflicted; Confuse Ray's continuation; not if already confused).
//   Mega Sol          The holder's moves act as if the sun were out (Fire x1.5 / Water x0.5, one-turn Solar Beam,
//                     Fire Weather Ball, Synthesis 2/3, Thunder / Hurricane 50%...): while its move runs
//                     (EVENT_MOVE_START .. EVENT_MOVE_END) the resident ServerEvent_GetWeather answers sun. (Everything
//                     that reads the weather during that move sees sun - a target's Leaf Guard, its sandstorm Sp. Def
//                     boost: Showdown limits this to the holder.)
#include "../ability_api.h"
#include "../megalog.h"
#include "../mb_resident.h"

extern "C" {
void HandlerMoldBreakerStart(BattleEventItem* item, ServerFlow* sf, u32 pokeID, u32* work);   // ov167 0x21C0A3C
void HandlerMoldBreakerEnd(BattleEventItem* item, ServerFlow* sf, u32 pokeID, u32* work);     // ov167 0x21C0A68
}

namespace {
constexpr u32 MV_EVENT_SPECIAL_PRIORITY = 0x0F, MV_VAR_SPECIAL_PRIORITY = 0x11, MV_LAST = 0;
constexpr u32 MV_EVENT_STATUS_INFLICTED = 0x68, MV_CONDITION_CONFUSION = 6;
constexpr u16 MV_CONFUSE_RAY = 109;

// ---- Mycelium Might ----------------------------------------------------------------------------------------
void HandlerMyceliumMightPriority(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Subject() != pokeID) return;
    u16 move = W2U_MB_PendingMove(sf, pokeID);
    if (!move || !ability::IsStatusMove(move)) return;
    BattleEventVar_RewriteValue(MV_VAR_SPECIAL_PRIORITY, MV_LAST);
    if (!ability::Simulating(sf)) MLOG("[ABIL] Mycelium Might: poke %d moves last (move %d)", pokeID, move);
}
// work[1] = 1: the Mold Breaker skip check is on for this move
void HandlerMyceliumMightMoveStart(BattleEventItem* item, ServerFlow* sf, u32 pokeID, u32* work) {
    if (ability::Attacker() != pokeID || !ability::IsStatusMove(ability::Move()) || work[1]) return;
    HandlerMoldBreakerStart(item, sf, pokeID, work);
    work[1] = 1;
}
void HandlerMyceliumMightMoveEnd(BattleEventItem* item, ServerFlow* sf, u32 pokeID, u32* work) {
    if (!work[1]) return;
    work[1] = 0;
    HandlerMoldBreakerEnd(item, sf, pokeID, work);
}
void HandlerMyceliumMightTurnEnd(BattleEventItem*, ServerFlow*, u32 pokeID, u32*) { W2U_MB_ClearPendingMove(pokeID); }
const BattleEventHandlerTableEntry MYCELIUM_MIGHT_HANDLERS[] = {
    { MV_EVENT_SPECIAL_PRIORITY, HandlerMyceliumMightPriority },
    { EVENT_MOVE_START, HandlerMyceliumMightMoveStart },
    { EVENT_MOVE_END, HandlerMyceliumMightMoveEnd },
    { EVENT_TURN_CHECK, HandlerMyceliumMightTurnEnd },
};

// ---- Poison Puppeteer --------------------------------------------------------------------------------------
void HandlerPoisonPuppeteerStatus(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Attacker() != pokeID || (u32)BattleEventVar_GetValue(VAR_CONDITION) != COND_POISON) return;
    u32 target = ability::Defender();
    if (target == pokeID || target >= ability::MAX_POKE_ID) return;
    BattleMon* bm = GetBattleMon(sf, target);
    if (BattleMon_IsFainted(bm) || CheckCondition(bm, MV_CONDITION_CONFUSION)) return;
    auto* p = (HandlerParam_AddCondition*)BattleHandler_PushWork(sf, EFFECT_ADD_CONDITION, pokeID);
    p->header.flags |= HANDLER_ABILITY_POPUP_FLAG;
    p->condition = MV_CONDITION_CONFUSION;
    BTL_MakeSickCont(PML_MoveGetSickCont(MV_CONFUSE_RAY), GetBattleMon(sf, pokeID), &p->cont);
    p->pokeID = (u8)target;
    BattleHandler_PopWork(sf, p);
    MLOG("[ABIL] Poison Puppeteer: poke %d confuses poke %d", pokeID, target);
}
const BattleEventHandlerTableEntry POISON_PUPPETEER_HANDLERS[] = {
    { MV_EVENT_STATUS_INFLICTED, HandlerPoisonPuppeteerStatus },
};

// ---- Mega Sol ----------------------------------------------------------------------------------------------
void HandlerMegaSolMoveStart(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Attacker() != pokeID) return;
    W2U_MB_SetMegaSolAttacker(pokeID);
    if (!ability::Simulating(sf)) MLOG("[ABIL] Mega Sol: poke %d move %d in sunlight", pokeID, ability::Move());
}
void HandlerMegaSolMoveEnd(BattleEventItem*, ServerFlow*, u32 pokeID, u32*) {
    if (ability::Attacker() == pokeID) W2U_MB_SetMegaSolAttacker(0xFF);
}
const BattleEventHandlerTableEntry MEGA_SOL_HANDLERS[] = {
    { EVENT_MOVE_START, HandlerMegaSolMoveStart },
    { EVENT_MOVE_END, HandlerMegaSolMoveEnd },
};
} // namespace

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_MyceliumMightHandlers[4] = {MYCELIUM_MIGHT_HANDLERS[0], MYCELIUM_MIGHT_HANDLERS[1],
                                                            MYCELIUM_MIGHT_HANDLERS[2], MYCELIUM_MIGHT_HANDLERS[3]};
BattleEventHandlerTableEntry MB_PoisonPuppeteerHandlers[1] = {POISON_PUPPETEER_HANDLERS[0]};
BattleEventHandlerTableEntry MB_MegaSolHandlers[2] = {MEGA_SOL_HANDLERS[0], MEGA_SOL_HANDLERS[1]};
static_assert(sizeof(MYCELIUM_MIGHT_HANDLERS) / sizeof(MYCELIUM_MIGHT_HANDLERS[0]) == 4, "MB_MyceliumMightHandlers");
static_assert(sizeof(POISON_PUPPETEER_HANDLERS) / sizeof(POISON_PUPPETEER_HANDLERS[0]) == 1,
              "MB_PoisonPuppeteerHandlers");
static_assert(sizeof(MEGA_SOL_HANDLERS) / sizeof(MEGA_SOL_HANDLERS[0]) == 2, "MB_MegaSolHandlers");
