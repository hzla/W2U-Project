// Ported from MegaB2W2 (src/patches/MegaEvolution/abilities/LingeringAroma.cpp); see docs/megab2w2-integration.md.
// Mummy family (`logic: LingeringAroma`; data/abilities.yml LINGERING_AROMA, WANDERING_SPIRIT): reactions to a
// contact move, modelled on vanilla Mummy (ov167 0x21C2230: the defender is the holder, not a substitute hit,
// sub_21ABF54 clear, the move makes contact; EFFECT_CHANGE_ABILITY {ability, pokeID, message}; the popup only
// against a foe) (Gen 9 / Showdown):
//   Lingering Aroma: the attacker's ability becomes Lingering Aroma ("A lingering aroma clings to X!").
//   Wandering Spirit: the holder and the attacker swap abilities ("X swapped Abilities with its target!").
// Not over abilities that can't be replaced (Showdown's cantsuppress / failskillswap lists, those in the game).
#include "../ability_api.h"
#include "../megalog.h"
#include "../mb_ids.h"

namespace {
constexpr u16 MUMMY_MSG_SWAPPED = 508;   // bank 18: "{0} swapped Abilities with its target!" (Skill Swap's)
// Wonder Guard, Multitype, Illusion, Zen Mode, Imposter + the Gen 6+ form / special ones
const u16 MUMMY_FIXED[] = { 25, 121, 149, 161, 150, ABIL_STANCE_CHANGE, ABIL_SCHOOLING, ABIL_DISGUISE,
                            ABIL_BATTLE_BOND, ABIL_POWER_CONSTRUCT, ABIL_COMATOSE, ABIL_SHIELDS_DOWN, ABIL_RKS_SYSTEM,
                            ABIL_GULP_MISSILE, ABIL_ICE_FACE, ABIL_NEUTRALIZING_GAS, ABIL_HUNGER_SWITCH,
                            ABIL_AS_ONE_GLASTRIER, ABIL_AS_ONE_SPECTRIER, ABIL_ZERO_TO_HERO, ABIL_COMMANDER,
                            ABIL_TERA_SHIFT, ABIL_LINGERING_AROMA, ABIL_WANDERING_SPIRIT };

bool MummyFixed(u16 a) {
    for (u16 f : MUMMY_FIXED)
        if (f == a) return true;
    return false;
}
void MummyChange(ServerFlow* sf, u32 holder, u32 target, u16 newAbility, u16 msg, bool popup) {
    auto* p = (HandlerParam_ChangeAbility*)BattleHandler_PushWork(sf, EFFECT_CHANGE_ABILITY, holder);
    p->ability = newAbility;
    p->pokeID = (u8)target;
    if (msg) {
        BattleHandler_StrSetup(&p->exStr, ability::STRTYPE_SET, msg);
        BattleHandler_AddArg(&p->exStr, target);
    }
    if (popup) p->header.flags |= HANDLER_ABILITY_POPUP_FLAG;
    BattleHandler_PopWork(sf, p);
}
void HandlerLingeringAromaHit(BattleEventItem*, ServerFlow* sf, u32 pokeID, u32*) {
    if (ability::Defender() != pokeID || BattleEventVar_GetValue(VAR_SUBSTITUTE_HIT) || sub_21ABF54(sf)) return;
    if (!ability::MakesContact(sf, ability::Move())) return;
    u32 attacker = ability::Attacker();
    if (attacker == pokeID || attacker >= ability::MAX_POKE_ID) return;
    BattleMon* bmA = GetBattleMon(sf, attacker);
    u16 theirs = (u16)BattleMon_GetValue(bmA, BMV_ABILITY), mine = ability::HolderAbility(sf, pokeID);
    if (MummyFixed(theirs) || theirs == mine) return;
    bool foe = !IsAllyMonID(pokeID, attacker);
    if (mine == ABIL_LINGERING_AROMA) {
        MummyChange(sf, pokeID, attacker, ABIL_LINGERING_AROMA, BTLMSG_SET_LINGERING_AROMA, foe);
        MLOG("[ABIL] Lingering Aroma: poke %d -> poke %d (was %d)", pokeID, attacker, theirs);
    } else {
        BattleHandler_PushRun(sf, ability::RUN_POPUP_IN, pokeID);
        MummyChange(sf, pokeID, attacker, ABIL_WANDERING_SPIRIT, 0, false);
        MummyChange(sf, pokeID, pokeID, theirs, 0, false);
        auto* m = (HandlerParam_Message*)BattleHandler_PushWork(sf, EFFECT_MESSAGE, pokeID);
        BattleHandler_StrSetup(&m->str, ability::STRTYPE_SET, MUMMY_MSG_SWAPPED);
        BattleHandler_AddArg(&m->str, pokeID);
        BattleHandler_PopWork(sf, m);
        BattleHandler_PushRun(sf, ability::RUN_POPUP_OUT, pokeID);
        MLOG("[ABIL] Wandering Spirit: poke %d swaps with poke %d (ability %d)", pokeID, attacker, theirs);
    }
}

constexpr BattleEventHandlerTableEntry LINGERING_AROMA_HANDLERS[] = {
    { EVENT_AFTER_DAMAGE_REACTION, HandlerLingeringAromaHit },
};
} // namespace

extern "C" const BattleEventHandlerTableEntry* EventAddLingeringAroma(u32* packed) {
    *packed = sizeof(LINGERING_AROMA_HANDLERS) / sizeof(LINGERING_AROMA_HANDLERS[0]);
    return LINGERING_AROMA_HANDLERS;
}

// W2U battle module tables (registry: src/pokeweb_gameplay/battle_modules/registry.json)
BattleEventHandlerTableEntry MB_LingeringAromaHandlers[1] = {LINGERING_AROMA_HANDLERS[0]};
static_assert(sizeof(LINGERING_AROMA_HANDLERS) / sizeof(LINGERING_AROMA_HANDLERS[0]) == 1, "MB_LingeringAromaHandlers");
