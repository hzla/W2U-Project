// Ported from MegaB2W2 (src/patches/MegaEvolution/abilities/UnseenFist.cpp); see docs/megab2w2-integration.md.
// Unseen Fist family (UNSEEN_FIST, PIERCING_DRILL): the holder's contact moves go through Protect and its variants
// (Gen 9 / Showdown: they lose the protect flag, so Mat Block and the damage shields don't stop them either). Piercing
// Drill (Legends Z-A): the same, but a hit that went through protection does 1/4 damage.
// W2U: its protection check (w2u_moves.cpp, flowsub_CheckNoEffect_Protect) raises EVENT_CHECK_PROTECT_BREAK for each
// target with the attacker, the target and the move; VAR_GENERAL_USE_FLAG 1 = broken (Feint's effect, the protection
// ends), 2 = it goes through and the protection stays. The holder answers 2 (unless something already answered).
#include "../ability_api.h"
#include "../megalog.h"

extern "C" b32 BattleMon_GetTurnFlag(BattleMon* bm, u32 flag);

namespace {
constexpr u32 UF_VAR_PROTECT_RESULT = 0x51;   // VAR_GENERAL_USE_FLAG (MegaB2W2: VAR_BREAK_PROTECT)
constexpr u32 UF_PASS_THROUGH = 2;
constexpr u32 UF_TURNFLAG_PROTECT = 7;
constexpr int PIERCING_RATIO = 1024;          // x0.25
u32 g_piercedTargets[ability::MAX_POKE_ID];   // per Piercing Drill holder: targets it hit through protection (bits)

void HandlerUnseenFistBreakCheck(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Attacker() != pokeID || pokeID >= ability::MAX_POKE_ID) return;
    u32 target = ability::Defender();
    u16 move = ability::Move();
    if (target >= ability::MAX_POKE_ID || !ability::MakesContact(sf, move)) return;
    if (BattleEventVar_GetValue(UF_VAR_PROTECT_RESULT) != 0) return;
    BattleEventVar_RewriteValue(UF_VAR_PROTECT_RESULT, UF_PASS_THROUGH);
    bool piercing = ability::HolderAbility(sf, pokeID) == ABIL_PIERCING_DRILL;
    if (piercing && BattleMon_GetTurnFlag(GetBattleMon(sf, target), UF_TURNFLAG_PROTECT))
        g_piercedTargets[pokeID] |= 1u << target;
    if (!ability::Simulating(sf))
        MLOG("[ABIL] Unseen Fist: poke %d move %d ignores protection%s", pokeID, move, piercing ? " (1/4)" : "");
}
void HandlerUnseenFistMoveStart(BattleEventItem*, ServerFlow*, u32 pokeID, u32*) {
    if (ability::Attacker() == pokeID && pokeID < ability::MAX_POKE_ID) g_piercedTargets[pokeID] = 0;
}
void HandlerUnseenFistDamageRatio(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Attacker() != pokeID || pokeID >= ability::MAX_POKE_ID) return;
    u32 defender = ability::Defender();
    if (defender >= 32 || !(g_piercedTargets[pokeID] & (1u << defender))) return;
    ability::MulRatio(PIERCING_RATIO);
    if (!ability::Simulating(sf)) MLOG("[ABIL] Piercing Drill: poke %d -> %d x0.25", pokeID, defender);
}

const BattleEventHandlerTableEntry UNSEEN_FIST_HANDLERS[] = {
    { EVENT_PROTECT_BREAK_CHECK, HandlerUnseenFistBreakCheck },
    { EVENT_MOVE_START, HandlerUnseenFistMoveStart },
    { EVENT_DAMAGE_RATIO, HandlerUnseenFistDamageRatio },
};
} // namespace

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_UnseenFistHandlers[3] = {UNSEEN_FIST_HANDLERS[0], UNSEEN_FIST_HANDLERS[1],
                                                         UNSEEN_FIST_HANDLERS[2]};
static_assert(sizeof(UNSEEN_FIST_HANDLERS) / sizeof(UNSEEN_FIST_HANDLERS[0]) == 3, "MB_UnseenFistHandlers");
