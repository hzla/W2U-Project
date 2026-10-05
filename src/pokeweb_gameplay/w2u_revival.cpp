#include "w2u_moves.h"

// The asynchronous chooser and its pointers are resident, never in a child.
// Private native layouts below are pinned against both clean US games.
struct RevivalSelectParam {
    BattleParty* party;
    u8 numSelect;
    u8 prohibited[6];
    u8 mode;
};
struct RevivalSelectResult {
    u8 member[3], outPosition[3], count, maximum, cancelled;
};
struct RevivalWork {
    HandlerParam_Header header;
    u8 pokeID, padding;
    u16 recoverHP;
    HandlerParam_StrParams exStr;
};
static_assert(sizeof(RevivalSelectParam) == 12, "Native selection parameter");
static_assert(sizeof(RevivalSelectResult) == 9, "Native selection result");
static_assert(sizeof(RevivalWork) == 48, "Native revival work");

typedef b32 (*RevivalClientProc)(void*, int*);
extern "C" RevivalClientProc BattleClient_GetSubProc(void*, u32, b32*);
extern "C" u32 BattleAdapter_GetRecvData(void*, const u8**);
extern "C" void MainModule_BattlePosOwner(MainModule*, u32, u8*, u8*);
extern "C" void BattleView_StartPokeSelect(void*, const RevivalSelectParam*, int, b32, RevivalSelectResult*);
extern "C" b32 BattleView_WaitPokeSelect(void*);
extern "C" void BattleServer_RequestChangePokemon(BtlServerWk*, u32);
extern "C" b32 ServerControl_OnlyPokeIn(ServerFlow*, void*);
extern "C" void ServerFlow_AddRevivedMonRecord(ServerFlow*, u32);

struct RevivalPending {
    ServerFlow* flow;
    u8 owner, positionIndex;
};
static RevivalPending sRevival;

extern "C" void W2U_Revival_Reset()
{
    sRevival.flow = 0;
    sRevival.owner = sRevival.positionIndex = 0;
}

static BattleMon* FaintedMember(PokeCon* con, u32 owner, u32 member)
{
    if (!con || owner >= 4) return 0;
    BattleParty* party = PokeCon_GetBattleParty(con, owner);
    if (!party || member >= party->memberCount || member >= 6) return 0;
    BattleMon* mon = BattleParty_GetPartyMember(party, member);
    return mon && BattleMon_IsFainted(mon) ? mon : 0;
}

extern "C" u32 W2U_GetBattlePartyOwner(ServerFlow* flow, u32 slot)
{
    if (!flow || !flow->pokeCon || slot >= 24) return 4;
    // Native IDs encode side/partner, not the index of party[4]. Ordinary
    // battles use trainer 0/1 even though opposing Pokémon IDs start at 12.
    for (u32 owner = 0; owner < 4; ++owner) {
        BattleParty* party = PokeCon_GetBattleParty(flow->pokeCon, owner);
        if (!party) continue;
        for (u32 member = 0; member < party->memberCount && member < 6; ++member) {
            BattleMon* mon = BattleParty_GetPartyMember(party, member);
            if (mon && BattleMon_GetID(mon) == slot) return owner;
        }
    }
    return 4;
}

extern "C" bool W2U_Revival_CanUse(ServerFlow* flow, u32 slot)
{
    if (!flow || !flow->pokeCon || slot >= 24) return false;
    const u32 owner = W2U_GetBattlePartyOwner(flow, slot);
    if (owner >= 4) return false;
    for (u32 member = 0; member < 6; ++member)
        if (FaintedMember(flow->pokeCon, owner, member)) return true;
    return false;
}

extern "C" bool W2U_Revival_Begin(ServerFlow* flow, u32 slot)
{
    if (!flow || flow->simulationCounter || sRevival.flow ||
        !W2U_Revival_CanUse(flow, slot) ||
        !Handler_CheckReservedMemberChangeAction(flow)) return false;
    const u32 pos = Handler_PokeIDToPokePos(flow, slot);
    if (pos >= 6) return false;
    u8 owner = 4, index = 3;
    MainModule_BattlePosOwner(flow->mainModule, pos, &owner, &index);
    if (owner >= 4 || index >= 3) return false;
    sRevival.flow = flow;
    sRevival.owner = owner;
    sRevival.positionIndex = index;
    // A tagged request uses the existing adapter/record/reply round trip.
    // No switch-out operation runs, and only our chooser consumes the tag.
    BattleServer_RequestChangePokemon(flow->server, 0x80u | pos);
    BattleHandler_PushRun(flow, EFFECT_FORCE_MOVE_SUCCESS, slot);
    flow->flowResult = 1; // Native POKE_CHANGE suspension.
    return true;
}

template<class T> static T& ClientField(void* client, u32 offset)
{
    return *reinterpret_cast<T*>(static_cast<u8*>(client) + offset);
}

static bool RevivalRequest(void* client, u8* owner, u8* positionIndex)
{
    const u8* request = 0;
    const u32 count = BattleAdapter_GetRecvData(ClientField<void*>(client, 0x50), &request);
    if (count != 1 || !request || (request[0] & 0xF8) != 0x80 || (request[0] & 7) >= 6)
        return false;
    MainModule_BattlePosOwner(ClientField<MainModule*>(client, 0), request[0] & 7, owner, positionIndex);
    return *owner < 4 && *positionIndex < 3;
}

static b32 ReturnRevivalChoice(void* client, u32 member, u32 positionIndex)
{
    // Native CHANGE payload, interpreted as a revival only by our pending
    // server transaction. The ordinary switch path never sees this action.
    u32& action = ClientField<u32>(client, 0x12C);
    action = member < 6 ? 3u | (positionIndex << 4) | (member << 7) : 0;
    ClientField<void*>(client, 0xE0) = &action;
    ClientField<u32>(client, 0xE4) = sizeof(action);
    return true;
}

static b32 RevivalClientSelect(void* client, int* sequence)
{
    u8 owner = 4, positionIndex = 3;
    if (!RevivalRequest(client, &owner, &positionIndex) ||
        ClientField<u8>(client, 0x1AE) != owner)
        return ReturnRevivalChoice(client, 6, 0);
    PokeCon* con = ClientField<PokeCon*>(client, 4);
    if (ClientField<u8>(client, 0x1AF) == 1) {
        // Native AI clients have no party UI. Restrict them to their own
        // fainted members; their reply still goes through the normal adapter.
        for (u32 member = 0; member < 6; ++member)
            if (FaintedMember(con, owner, member))
                return ReturnRevivalChoice(client, member, positionIndex);
        return ReturnRevivalChoice(client, 6, 0);
    }
    void* view = ClientField<void*>(client, 0x54);
    RevivalSelectParam& param = ClientField<RevivalSelectParam>(client, 0x18C);
    RevivalSelectResult& result = ClientField<RevivalSelectResult>(client, 0x198);
    if (*sequence == 0) {
        param.party = PokeCon_GetBattleParty(con, owner);
        param.numSelect = 1;
        for (u32 i = 0; i < 6; ++i) param.prohibited[i] = 0;
        param.mode = 3; // Native ITEMUSE: allows fainted party members.
        for (u32 i = 0; i < 3; ++i) result.member[i] = result.outPosition[i] = 0xFF;
        result.count = 0;
        result.maximum = 1;
        result.cancelled = true;
        BattleView_StartPokeSelect(view, &param, 0, false, &result);
        // Only selection metadata: no bag operation or item is consumed.
        *reinterpret_cast<u16*>(static_cast<u8*>(view) + 0x130) = 28; // Revive, not a PP item.
        for (u32 i = 0; i < 6; ++i) static_cast<u8*>(view)[0x144 + i] = 0;
        *sequence = 1;
    } else if (BattleView_WaitPokeSelect(view)) {
        if (result.cancelled || !result.count) return ReturnRevivalChoice(client, 6, 0);
        const u32 member = result.member[0];
        if (FaintedMember(con, owner, member)) return ReturnRevivalChoice(client, member, positionIndex);
        // A living Pokémon is never healed. Reopen the chooser without
        // another move execution or PP payment, rather than reviving a default.
        *sequence = 0;
    }
    return false;
}

extern "C" RevivalClientProc W2U_Revival_GetClientProc(void* client, u32 command, b32* recordLock)
{
    RevivalClientProc original = BattleClient_GetSubProc(client, command, recordLock);
    u8 owner, index;
    // Recorded replies are already native CHANGE payloads: replay uses its
    // original reader, not an interactive chooser or an AI replacement.
    if (command == 6 && ClientField<u8>(client, 0x1AF) != 2 && RevivalRequest(client, &owner, &index))
        return RevivalClientSelect;
    return original;
}

extern "C" b32 W2U_Revival_Resume(ServerFlow* flow, void* clientActions)
{
    if (sRevival.flow != flow) return ServerControl_OnlyPokeIn(flow, clientActions);
    const u32 owner = sRevival.owner, positionIndex = sRevival.positionIndex;
    W2U_Revival_Reset(); // Clear before work can dispatch other events.
    const u8* bytes = static_cast<const u8*>(clientActions);
    const u32 action = *reinterpret_cast<const u32*>(bytes + owner * 12);
    if (bytes[0x30 + owner] != 1 || (action & 15) != 3 ||
        ((action >> 4) & 7) != positionIndex || (action & ~0x3FFu)) return false;
    BattleMon* target = FaintedMember(flow->pokeCon, owner, (action >> 7) & 7);
    if (!target) return false;
    const u32 slot = BattleMon_GetID(target);
    RevivalWork* work = static_cast<RevivalWork*>(BattleHandler_PushWork(flow, (BattleHandlerEffect)0x2C, slot));
    if (!work) return false;
    work->pokeID = slot;
    const u32 half = BattleMon_GetValue(target, VALUE_MAX_HP) >> 1;
    work->recoverHP = half ? half : 1;
    BattleHandler_StrSetup(&work->exStr, 2, 3); // Native revival message.
    BattleHandler_AddArg(&work->exStr, slot);
    BattleHandler_PopWork(flow, work);
    ServerFlow_AddRevivedMonRecord(flow, slot);
    return false; // Resume the remaining queued actions, never switch the user.
}
