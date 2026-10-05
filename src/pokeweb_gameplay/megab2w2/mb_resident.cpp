// MegaB2W2 wave C, the resident half (White2Upgrade.dll, White 2 only; ported from MegaB2W2's PropellerTail.cpp,
// QuickDraw.cpp, MegaServer.cpp, EffectAbilities.cpp and MoveAbilities.cpp). Engine call sites the event system
// does not reach, and the state they share with battle module abilities/mb_hooked (mb_resident.h). Every call site
// below is a BL whose target was checked against vanilla White 2 and W2U's overlay 167; none is hooked by W2U.
// See docs/megab2w2-integration.md (wave C).
#include "ability_api.h"
#include "mb_resident.h"

extern "C" {
b32  Battle_IsRedirectBlocked(ServerFlow* sf, u32 attacker, u32 redirector, u16 move);   // ov167 0x21ABE10
u32  BattleField_GetWeather();                                                          // ov167 0x21D59F0
void BattleHandler_UseHeldItem(ServerFlow* sf, void* param);                            // ov167 0x21AD968
void BattleHandler_RecoverHP(ServerFlow* sf, void* param, u32 a2);                      // ov167 0x21AC8AC
u32  BattleHandler_Damage(ServerFlow* sf, void* param);                                 // ov167 0x21AC9D8
void BattleHandler_StatChange(ServerFlow* sf, void* param, u32 a2);                     // ov167 0x21ACDD0
void BattleHandler_ForceUseItem(ServerFlow* sf, void* param);                           // ov167 0x21AD9BC
}

namespace {
constexpr u32 NONE = 0xFF;
constexpr u32 MAX_ID = ability::MAX_POKE_ID;

u16 sSortMove[MAX_ID];          // the move of each fight action at the last action-order sort
u8 sRipenUser = NONE;           // a Ripen holder eating a Berry (its UseHeldItem / ForceUseItem is running)
u8 sCudChewing = NONE;          // a Cud Chew holder's second bite is running
u16 sCudBerry[MAX_ID];
u8 sCudCounter[MAX_ID];
u8 sOppPendingCopies[MAX_ID];
bool sOppCopying;
u8 sMegaSolAttacker = NONE;

struct HandlerParam_ForceUseItemFX { HandlerParam_Header header; u8 pokeID; u8 ateBerry; u16 item; };
struct HandlerParam_DamageFX { HandlerParam_Header header; u16 amount; u8 pokeID; u8 flags; };

u32 HeaderPoke(void* param) { return (((HandlerParam_Header*)param)->flags >> 8) & 0x1F; }
BattleMon* Mon(ServerFlow* sf, u32 pokeID) { return pokeID < MAX_ID ? GetBattleMon(sf, pokeID) : nullptr; }

// ---- Propeller Tail / Stalwart: the holder's moves are not redirected -------------------------------------------
// Lightning Rod / Storm Drain (0x21C0D82) and Follow Me / Rage Powder (0x21C64C4) ask Battle_IsRedirectBlocked
// first (nonzero: no redirection). W2U's Spotlight checks the abilities itself (w2u_moves.cpp).
b32 RedirectBlocked(ServerFlow* sf, u32 attacker, u32 redirector, u16 move) {
    BattleMon* bm = Mon(sf, attacker);
    if (ability::HasActiveAbility(bm, ABIL_PROPELLER_TAIL) || ability::HasActiveAbility(bm, ABIL_STALWART)) return 1;
    return Battle_IsRedirectBlocked(sf, attacker, redirector, move);
}

// ---- Ripen / Cud Chew: Berries eaten ----------------------------------------------------------------------------
// The handler-effect dispatcher (ov167 0x21AC4F8) carries a held item's effects out inside its UseHeldItem, so a
// "this Ripen holder is eating a Berry" flag around that call sees the Berry's own heal / stat / damage effects.
void UseItem(ServerFlow* sf, void* param, bool force) {
    u32 pokeID = force ? ((HandlerParam_ForceUseItemFX*)param)->pokeID : HeaderPoke(param);
    BattleMon* bm = Mon(sf, pokeID);
    u16 item = !bm ? 0 : force ? ((HandlerParam_ForceUseItemFX*)param)->item : BattleMon_GetHeldItem(bm);
    u8 prev = sRipenUser;
    if (bm && ability::IsBerry(item) && ability::HasActiveAbility(bm, ABIL_RIPEN)) sRipenUser = (u8)pokeID;
    if (force) BattleHandler_ForceUseItem(sf, param);
    else BattleHandler_UseHeldItem(sf, param);
    sRipenUser = prev;
    if (bm && ability::IsBerry(item) && sCudChewing != pokeID && ability::HasActiveAbility(bm, ABIL_CUD_CHEW)) {
        sCudBerry[pokeID] = item;
        sCudCounter[pokeID] = 2;   // the end of this turn, then the next: chewed again
    }
}
} // namespace

// ---- the call sites --------------------------------------------------------------------------------------------
extern "C" b32 THUMB_BRANCH_LINK_167_0x21C0D82(ServerFlow* sf, u32 a, u32 r, u16 m) { return RedirectBlocked(sf, a, r, m); }
extern "C" b32 THUMB_BRANCH_LINK_167_0x21C64C4(ServerFlow* sf, u32 a, u32 r, u16 m) { return RedirectBlocked(sf, a, r, m); }

// The two ServerEvent_GetMovePriority calls: the turn's first action order (0x21A0266, before its event 0x0F check)
// and SortActionOrderBySpeed (0x219FBF8). Event 0x0F follows for the same Pokemon without a move.
extern "C" u32 THUMB_BRANCH_LINK_167_0x21A0266(ServerFlow* sf, u16 move, BattleMon* bm) {
    u32 id = BattleMon_GetID(bm);
    if (id < MAX_ID) sSortMove[id] = move;
    return ServerEvent_GetMovePriority(sf, move, bm);
}
extern "C" u32 THUMB_BRANCH_LINK_167_0x219FBF8(ServerFlow* sf, u16 move, BattleMon* bm) {
    u32 id = BattleMon_GetID(bm);
    if (id < MAX_ID) sSortMove[id] = move;
    return ServerEvent_GetMovePriority(sf, move, bm);
}

extern "C" void THUMB_BRANCH_LINK_167_0x21AC59E(ServerFlow* sf, void* param) { UseItem(sf, param, false); }
extern "C" void THUMB_BRANCH_LINK_167_0x21AC6D6(ServerFlow* sf, void* param) {
    UseItem(sf, param, true);
    sCudChewing = NONE;
}
extern "C" void THUMB_BRANCH_LINK_167_0x21AC5AA(ServerFlow* sf, void* param, u32 a2) {
    auto* p = (HandlerParam_RecoverHP*)param;
    if (sRipenUser != NONE && p->pokeID == sRipenUser) p->amount = (u16)(p->amount * 2);   // Sitrus, Oran...
    BattleHandler_RecoverHP(sf, param, a2);
}
extern "C" u32 THUMB_BRANCH_LINK_167_0x21AC5C0(ServerFlow* sf, void* param) {
    auto* p = (HandlerParam_DamageFX*)param;
    if (sRipenUser != NONE && p->pokeID != sRipenUser) p->amount = (u16)(p->amount * 2);   // Jaboca / Rowap
    return BattleHandler_Damage(sf, param);
}
extern "C" void THUMB_BRANCH_LINK_167_0x21AC604(ServerFlow* sf, void* param, u32 a2) {
    auto* p = (HandlerParam_ChangeStatStage*)param;
    bool single = p->stages > 0 && p->pokeCount == 1 && p->pokeIDs[0] < MAX_ID;
    bool copy = single && sOppPendingCopies[p->pokeIDs[0]] > 0;
    if (copy) --sOppPendingCopies[p->pokeIDs[0]];
    if (single && sRipenUser != NONE && p->pokeIDs[0] == sRipenUser)                     // Liechi, Salac...
        p->stages = (s8)(p->stages * 2 > 6 ? 6 : p->stages * 2);
    bool prev = sOppCopying;
    if (copy) sOppCopying = true;
    BattleHandler_StatChange(sf, param, a2);
    sOppCopying = prev;
}

// ServerEvent_GetWeather (ov167 0x21A65A0), rewritten whole as vanilla: Air Lock / Cloud Nine (event 0x7A,
// VAR_WEATHER_NEGATED) -> no weather, else the field's. Mega Sol first: during its holder's move, sun. (Its 8-byte
// GetWeather thunk at 0x21ABE08 is too short for PMC's 12-byte branch.)
extern "C" u32 THUMB_BRANCH_ServerEvent_GetWeather(ServerFlow* sf) {
    if (sMegaSolAttacker != NONE && ability::HasActiveAbility(Mon(sf, sMegaSolAttacker), ABIL_MEGA_SOL))
        return WEATHER_SUN;
    BattleEventVar_Push();
    BattleEventVar_SetRewriteOnceValue(VAR_WEATHER_NEGATED, 0);
    BattleEvent_CallHandlers(sf, EVENT_WEATHER_NEGATION);
    int negated = BattleEventVar_GetValue(VAR_WEATHER_NEGATED);
    BattleEventVar_Pop();
    return negated ? 0 : BattleField_GetWeather();
}

// ---- the API (mb_resident.h) ------------------------------------------------------------------------------------
extern "C" void W2U_MB_ResetBattleState() {
    sRipenUser = sCudChewing = sMegaSolAttacker = NONE;
    sOppCopying = false;
    for (u32 i = 0; i < MAX_ID; ++i) {
        sSortMove[i] = 0; sCudBerry[i] = 0; sCudCounter[i] = 0; sOppPendingCopies[i] = 0;
    }
}

extern "C" u16 W2U_MB_PendingMove(ServerFlow* sf, u32 pokeID) {
    ActionOrderWork* all = SF_ActOrder(sf);
    for (u32 i = 0; i < SF_NumActOrder(sf); ++i) {
        const ActionOrderWork& e = all[i];
        if (e.done || !e.battleMon || BattleMon_GetID(e.battleMon) != pokeID) continue;
        if ((e.action & 0xF) != BTL_ACTION_FIGHT) return 0;
        return (u16)(e.action >> 7);
    }
    // The turn's first order runs before the action order is filled in: the move just noted for this Pokemon.
    return pokeID < MAX_ID ? sSortMove[pokeID] : 0;
}

extern "C" void W2U_MB_ClearPendingMove(u32 pokeID) {
    if (pokeID < MAX_ID) sSortMove[pokeID] = 0;
}

extern "C" u16 W2U_MB_CudChewTurnEnd(u32 pokeID) {
    if (pokeID >= MAX_ID || !sCudBerry[pokeID] || --sCudCounter[pokeID]) return 0;
    u16 item = sCudBerry[pokeID];
    sCudBerry[pokeID] = 0;
    sCudChewing = (u8)pokeID;   // cleared when the bite has run: it is not noted again
    return item;
}
extern "C" void W2U_MB_CudChewForget(u32 pokeID) {
    if (pokeID < MAX_ID) sCudBerry[pokeID] = 0;
}

extern "C" void W2U_MB_OpportunistCopyQueued(u32 pokeID) {
    if (pokeID < MAX_ID) ++sOppPendingCopies[pokeID];
}
extern "C" bool W2U_MB_OpportunistCopying() { return sOppCopying; }

extern "C" void W2U_MB_SetMegaSolAttacker(u32 pokeID) { sMegaSolAttacker = (u8)(pokeID < MAX_ID ? pokeID : NONE); }
