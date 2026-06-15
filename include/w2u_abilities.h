#ifndef __W2U_ABILITIES_H
#define __W2U_ABILITIES_H

#include "w2u_battle.h"
#include "Moves.h"

typedef u32 MOVE_ID;

#ifndef TYPE_NULL
#define TYPE_NULL (TYPE_FAIRY + 1)
#endif

enum W2UAbilityId : u32 {
    ABIL_AROMA_VEIL = 165,
    ABIL_FLOWER_VEIL = 166,
    ABIL_CHEEK_POUCH = 167,
    ABIL_PROTEAN = 168,
    ABIL_FUR_COAT = 169,
    ABIL_MAGICIAN = 170,
    ABIL_BULLETPROOF = 171,
    ABIL_COMPETITIVE = 172,
    ABIL_STRONG_JAW = 173,
    ABIL_REFRIGERATE = 174,
    ABIL_SWEET_VEIL = 175,
    ABIL_STANCE_CHANGE = 176,
    ABIL_GALE_WINGS = 177,
    ABIL_MEGA_LAUNCHER = 178,
    ABIL_GRASS_PELT = 179,
    ABIL_SYMBIOSIS = 180,
    ABIL_TOUGH_CLAWS = 181,
    ABIL_PIXILATE = 182,
    ABIL_GOOEY = 183,
    ABIL_AERILATE = 184,
    ABIL_PARENTAL_BOND = 185,
    ABIL_DARK_AURA = 186,
    ABIL_FAIRY_AURA = 187,
    ABIL_AURA_BREAK = 188,
    ABIL_PRIMORDIAL_SEA = 189,
    ABIL_DESOLATE_LAND = 190,
    ABIL_DELTA_STREAM = 191,
    ABIL_STAMINA = 192,
    ABIL_WIMP_OUT = 193,
    ABIL_EMERGENCY_EXIT = 194,
    ABIL_WATER_COMPACTION = 195,
    ABIL_MERCILESS = 196,
    ABIL_SHIELDS_DOWN = 197,
    ABIL_STAKEOUT = 198,
    ABIL_WATER_BUBBLE = 199,
    ABIL_STEELWORKER = 200,
    ABIL_BERSERK = 201,
    ABIL_SLUSH_RUSH = 202,
    ABIL_LONG_REACH = 203,
    ABIL_LIQUID_VOICE = 204,
    ABIL_TRIAGE = 205,
    ABIL_GALVANIZE = 206,
    ABIL_SURGE_SURFER = 207,
    ABIL_SCHOOLING = 208,
    ABIL_DISGUISE = 209,
    ABIL_BATTLE_BOND = 210,
    ABIL_POWER_CONSTRUCT = 211,
    ABIL_CORROSION = 212,
    ABIL_COMATOSE = 213,
    ABIL_QUEENLY_MAGESTY = 214,
    ABIL_QUEENLY_MAJESTY = ABIL_QUEENLY_MAGESTY,
    ABIL_INNARDS_OUT = 215,
    ABIL_DANCER = 216,
    ABIL_BATTERY = 217,
    ABIL_FLUFFY = 218,
    ABIL_DAZZLING = 219,
    ABIL_SOUL_HEART = 220,
    ABIL_TANGLING_HAIR = 221,
    ABIL_RECEIVER = 222,
    ABIL_POWER_OF_ALCHEMY = 223,
    ABIL_BEAST_BOOST = 224,
    ABIL_RKS_SYSTEM = 225,
    ABIL_ELECTRIC_SURGE = 226,
    ABIL_PSYCHIC_SURGE = 227,
    ABIL_MISTY_SURGE = 228,
    ABIL_GRASSY_SURGE = 229,
    ABIL_FULL_METAL_BODY = 230,
    ABIL_SHADOW_SHIELD = 231,
    ABIL_PRISM_ARMOR = 232,
};

enum BattleEventVar : u32 {
    VAR_MON_ID = 0x2,
    VAR_ATTACKING_MON = 0x3,
    VAR_DEFENDING_MON = 0x4,
    VAR_TARGET_COUNT = 0x5,
    VAR_TARGET_MON_ID = 0x6,
    NEW_VAR_MON_ID = 0x7,
    NEW_VAR_ATTACKING_MON = 0x8,
    NEW_VAR_DEFENDING_MON = 0x9,
    VAR_MOVE_ID = 0x12,
    VAR_POKE_TYPE = 0x15,
    VAR_MOVE_TYPE = 0x16,
    VAR_MOVE_PRIORITY = 0x18,
    VAR_MOVE_SERIAL = 0x19,
    VAR_MOVE_CATEGORY = 0x1A,
    VAR_TARGET_TYPE = 0x1B,
    VAR_USER_TYPE = 0x1C,
    VAR_CONDITION_ID = 0x1D,
    VAR_VOLUME = 0x20,
    VAR_FAIL_CAUSE = 0x22,
    VAR_EFFECT_TURN_COUNT = 0x24,
    VAR_CRIT_STAGE = 0x2C,
    VAR_ITEM = 0x2D,
    VAR_ITEM_REACTION = 0x2E,
    VAR_MOVE_POWER = 0x30,
    VAR_MOVE_POWER_RATIO = 0x31,
    VAR_DAMAGE = 0x32,
    VAR_RATIO = 0x35,
    VAR_TYPE_EFFECTIVENESS = 0x38,
    VAR_WEATHER = 0x39,
    VAR_WORK_ADDRESS = 0x3F,
    VAR_NO_EFFECT_FLAG = 0x40,
    VAR_MOVE_FAIL_FLAG = 0x41,
    VAR_SUBSTITUTE_FLAG = 0x46,
    VAR_NO_TYPE_EFFECTIVENESS = 0x4B,
    VAR_SET_TYPE_EFFECTIVENESS = 0x4C,
    VAR_DELAY_ATTACK_FLAG = 0x4D,
    VAR_MAGIC_COAT_FLAG = 0x4E,
    VAR_MESSAGE_FLAG = 0x4F,
    VAR_GENERAL_USE_FLAG = 0x51,
    VAR_SIDE = 0x52,
    VAR_SIDE_EFFECT = 0x53,
    VAR_PARTING_SHOT_FLAG = VAR_DELAY_ATTACK_FLAG,
    VAR_MIRROR_ARMOR_FLAG = VAR_MAGIC_COAT_FLAG,
};

enum MoveFailCause : u32 {
    MOVE_FAIL_NULL = 0x0,
    MOVE_FAIL_MOVELOCK = 0x11,
    MOVE_FAIL_NO_REACTION = 0x19,
    MOVE_FAIL_OTHER = 0x1A,
};

enum BattleEventType : u32 {
    EVENT_ACTION_PROCESSING_END = 0x2,
    EVENT_MOVE_SEQUENCE_START = 0x3,
    EVENT_MOVE_SEQUENCE_END = 0x4,
    EVENT_BYPASS_SUBSTITUTE = 0x5,
    EVENT_CHECK_SLEEP = 0xE,
    EVENT_GET_MOVE_PRIORITY = 0x11,
    EVENT_CHECK_FLOATING = 0x12,
    EVENT_CALC_SPEED = 0x13,
    EVENT_BEFORE_ATTACKS = 0x15,
    EVENT_MOVE_EXECUTE_CHECK1 = 0x1E,
    EVENT_MOVE_EXECUTE_CHECK2 = 0x1F,
    EVENT_MOVE_EXECUTE_FAIL = 0x21,
    EVENT_MOVE_EXECUTE_EFFECTIVE = 0x25,
    EVENT_MOVE_EXECUTE_NOEFFECT = 0x26,
    EVENT_MOVE_EXECUTE_END = 0x27,
    EVENT_MOVE_PARAM = 0x28,
    EVENT_REDIRECT_TARGETEND = 0x2B,
    EVENT_NOEFFECT_CHECK = 0x2C,
    EVENT_ABILITY_CHECK_NO_EFFECT = 0x2D,
    EVENT_CRITICAL_CHECK = 0x36,
    EVENT_MOVE_BASE_POWER = 0x37,
    EVENT_MOVE_POWER = 0x38,
    EVENT_ATTACKER_POWER = 0x3B,
    EVENT_DEFENDER_GUARD = 0x3C,
    EVENT_CHECK_TYPE_EFFECTIVENESS = 0x3E,
    EVENT_AFTER_DAMAGE_REACTION = 0x44,
    EVENT_MOVE_DAMAGE_PROCESSING_2 = 0x47,
    EVENT_MOVE_DAMAGE_REACTION_1 = 0x4B,
    EVENT_MOVE_DAMAGE_SIDE_AFTER = 0x4D,
    EVENT_SWITCH_OUT_END = 0x54,
    EVENT_SWITCH_IN = 0x55,
    EVENT_STAT_STAGE_CHANGE_LAST_CHECK = 0x5B,
    EVENT_STAT_STAGE_CHANGE_FAIL = 0x5C,
    EVENT_STAT_STAGE_CHANGE_APPLIED = 0x5D,
    EVENT_ADD_CONDITION_CHECK_FAIL = 0x65,
    EVENT_ADD_CONDITION_FAIL = 0x67,
    EVENT_ABILITY_NULLIFIED = 0x6A,
    EVENT_CONSUME_ITEM = 0x6F,
    EVENT_USE_TEMP_ITEM_AFTER = 0x71,
    EVENT_USE_ITEM = 0x72,
    EVENT_USE_ITEM_TEMP = 0x73,
    EVENT_TURN_CHECK_BEGIN = 0x76,
    EVENT_TURN_CHECK_DONE = 0x78,
    EVENT_WEATHER_CHECK = 0x7A,
    EVENT_MOVE_WEATHER_TURN_COUNT = 0x7C,
    EVENT_WEATHER_CHANGE = 0x7D,
    EVENT_AFTER_WEATHER_CHANGE = 0x7E,
    EVENT_WEATHER_REACTION = 0x7F,
    EVENT_BEFORE_ABILITY_CHANGE = 0x89,
    EVENT_AFTER_ABILITY_CHANGE = 0x8A,
    EVENT_RECOVER_HP = 0x8F,
    EVENT_CHECK_CHARGE_UP_FAIL = 0x93,
    EVENT_CHECK_CHARGE_UP_SKIP = 0x94,
    EVENT_CHARGE_UP_START = 0x95,
    EVENT_CHARGE_UP_START_DONE = 0x96,
    EVENT_CHARGE_UP_SKIP = 0x97,
    EVENT_CHARGE_UP_END = 0x98,
    EVENT_DAMAGE_PROCESSING_START = 0x81,
    EVENT_DAMAGE_PROCESSING_END_HIT_REAL = 0x83,
    EVENT_DAMAGE_PROCESSING_END_HIT_2 = 0x85,
    EVENT_ITEM_REWRITE_DONE = 0x9D,
    EVENT_CALL_FIELD_EFFECT = 0x9E,
    EVENT_UNCATEGORIZED_MOVE = 0xA0,
    EVENT_UNCATEGORIZED_MOVE_NO_TARGET = 0xA1,
    EVENT_NOTIFY_FAINTED = 0xA3,
    EVENT_PROTECT_BROKEN = EVENT_MOVE_EXECUTE_CHECK2,
    EVENT_PROTECT_SUCCESS = EVENT_BEFORE_ATTACKS,
    EVENT_GROUNDED_BY_GRAVITY = EVENT_CHECK_FLOATING,
    EVENT_TERRAIN_CHECK = EVENT_WEATHER_CHECK,
    EVENT_TERRAIN_CHANGE = EVENT_WEATHER_CHANGE,
    EVENT_TERRAIN_CHANGE_FAIL = EVENT_AFTER_WEATHER_CHANGE,
    EVENT_AFTER_TERRAIN_CHANGE = EVENT_AFTER_ABILITY_CHANGE,
    EVENT_MOVE_TERRAIN_TURN_COUNT = EVENT_MOVE_WEATHER_TURN_COUNT,
};

enum BattleEventItemType : u32 {
    EVENTITEM_MOVE = 0x0,
    EVENTITEM_POS = 0x1,
    EVENTITEM_SIDE = 0x2,
    EVENTITEM_FIELD = 0x3,
    EVENTITEM_ABILITY = 0x4,
    EVENTITEM_ITEM = 0x5,
};

enum BattleEventPriority : u32 {
    EVENTPRI_MOVE_DEFAULT = 0x0,
    EVENTPRI_POS_DEFAULT = 0x1,
    EVENTPRI_SIDE_DEFAULT = 0x2,
    EVENTPRI_FIELD_DEFAULT = 0x3,
    EVENTPRI_ABILITY_DEFAULT = 0x5,
    EVENTPRI_ITEM_DEFAULT = 0x6,
    EVENTPRI_ABILITY_STALL = 0x7,
};

enum W2UMoveFlagIndex : u32 {
    MOVE_FLAG_INDEX_CONTACT = 0x0,
    MOVE_FLAG_INDEX_REQUIRES_CHARGE = 0x1,
    MOVE_FLAG_INDEX_BLOCKED_BY_PROTECT = 0x3,
    MOVE_FLAG_INDEX_GROUNDED_BY_GRAVITY = 0x9,
    MOVE_FLAG_INDEX_POWDER = 0xE,
    MOVE_FLAG_INDEX_HEALING = 0x12,
    MOVE_FLAG_INDEX_DANCE = 0x13,
    MOVE_FLAG_INDEX_BULLET = 0x14,
    MOVE_FLAG_INDEX_BITE = 0x15,
    MOVE_FLAG_INDEX_PULSE = 0x16,
};

struct BattleEventItem;
struct ServerFlow;

typedef void (*BattleEventHandler)(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work);

enum MoveField : u32 {
    MVDATA_TARGET = 0x1B,
};

struct MoveParam {
    u16 moveID;
    u16 originalMoveID;
    u16 userType;
    u8 moveType;
    u8 damageType;
    u32 category;
    u32 targetType;
    u32 flags;
};

struct BattleEventHandlerTableEntry {
    BattleEventType eventType;
    BattleEventHandler handler;
};

struct AbilityEventAddTable {
    ABILITY ability;
    BattleEventHandlerTableEntry* (*func)(u32* handlerAmount);
};

extern "C" u32 BattleMon_GetID(BattleMon* battleMon);
extern "C" u16 BattleMon_GetPokeType(BattleMon* battleMon);
extern "C" u16 PokeTypePair_MakeMonotype(u16 type);
extern "C" u32 DivideMaxHPZeroCheck(BattleMon* battleMon, u32 denominator);
extern "C" u8 PML_MoveGetType(MOVE_ID moveID);
extern "C" u32 PML_MoveGetCategory(MOVE_ID moveID);
extern "C" u32 PML_MoveGetParam(MOVE_ID moveID, MoveField field);
extern "C" b32 PML_MoveIsDamaging(MOVE_ID moveID);
extern "C" u32 getMoveFlag(MOVE_ID moveID, u32 flagIndex);
extern "C" b32 PML_ItemIsBerry(ITEM itemID);
extern "C" b32 PML_ItemIsMail(ITEM itemID);
extern "C" u32 GetTypeEffectiveness(u32 moveType, u32 pokemonType);
extern "C" u32 GetTypeEffectivenessMultiplier(u32 effectiveness1, u32 effectiveness2);

extern "C" int BattleEventVar_GetValue(BattleEventVar eventVar);
extern "C" b32 BattleEventVar_GetValueIfExist(BattleEventVar eventVar, u32* value);
extern "C" void BattleEventVar_Push();
extern "C" void BattleEventVar_Pop();
extern "C" void BattleEventVar_SetValue(BattleEventVar eventVar, int value);
extern "C" void BattleEventVar_SetConstValue(BattleEventVar eventVar, int value);
extern "C" void BattleEventVar_SetRewriteOnceValue(BattleEventVar eventVar, int value);
extern "C" u32 BattleEventVar_RewriteValue(BattleEventVar eventVar, int value);
extern "C" void BattleEventVar_MulValue(BattleEventVar eventVar, int value);
extern "C" void BattleEvent_CallHandlers(ServerFlow* serverFlow, BattleEventType event);
extern "C" void THUMB_BRANCH_ServerEvent_GetMoveParam(
    ServerFlow* serverFlow,
    MOVE_ID moveID,
    BattleMon* battleMon,
    MoveParam* moveParam);

extern "C" BattleEventItem* BattleEvent_AddItem(
    BattleEventItemType eventType,
    u16 subID,
    BattleEventPriority mainPriority,
    u32 subPriority,
    u32 dependID,
    const BattleEventHandlerTableEntry* handlerTable,
    u16 handlerAmount);
extern "C" void BattleEventItem_Remove(BattleEventItem* item);

extern "C" u32 AbilityEvent_GetSubPriority(BattleMon* battleMon);
extern "C" BattleEventPriority GetHandlerMainPriority(u32* handlerAmount);
extern "C" void BattleHandler_PushRun(ServerFlow* serverFlow, BattleHandlerEffect effect, u32 pokemonSlot);

#endif
