#include "w2u_field_effects.h"

#define W2U_AURA_FIELD_EFFECT_COUNT (FLDEFF_FAIRY_AURA + 1)
#define W2U_AURA_FIELD_SLOT_COUNT 24u
#define W2U_AURA_POWER_RATIO 5448
#define W2U_AURA_BREAK_RATIO 3072

namespace {

struct AuraFieldEffectState {
    BattleEventItem* item;
    u32 ownerMask;
    u8 ownerCount;
    bool active;
};

struct AuraFieldState {
    AuraFieldEffectState effects[W2U_AURA_FIELD_EFFECT_COUNT];
    u32 auraBreakMask;
    u8 auraBreakCount;
};

AuraFieldState sAuraFieldState;

void ClearAuraFieldState()
{
    volatile u8* bytes = (volatile u8*)&sAuraFieldState;
    for (u32 idx = 0; idx < sizeof(sAuraFieldState); ++idx) {
        bytes[idx] = 0;
    }
}

bool IsManagedAuraFieldEffect(FIELD_EFFECT fieldEffect)
{
    return fieldEffect == FLDEFF_DARK_AURA || fieldEffect == FLDEFF_FAIRY_AURA;
}

u32 SlotMask(u32 pokemonSlot)
{
    if (pokemonSlot >= W2U_AURA_FIELD_SLOT_COUNT) {
        return 0;
    }
    return 1u << pokemonSlot;
}

BattleEventHandlerTableEntry* GetAuraFieldHandlers(FIELD_EFFECT fieldEffect, u32* handlerAmount);

BattleEventItem* AddAuraFieldEvent(FIELD_EFFECT fieldEffect, u32 ownerSlot)
{
    u32 handlerAmount = 0;
    BattleEventHandlerTableEntry* handlers = GetAuraFieldHandlers(fieldEffect, &handlerAmount);
    if (handlerAmount == 0 || handlers == 0) {
        return 0;
    }

    return BattleEvent_AddItem(
        EVENTITEM_FIELD,
        (u16)fieldEffect,
        EVENTPRI_FIELD_DEFAULT,
        0,
        ownerSlot,
        handlers,
        (u16)handlerAmount);
}

void ApplyAuraPower(u32 moveType)
{
    if (BattleEventVar_GetValue(VAR_MOVE_TYPE) != (int)moveType) {
        return;
    }

    BattleEventVar_MulValue(
        VAR_MOVE_POWER_RATIO,
        W2U_AuraField_GetAuraBreakMons() ? W2U_AURA_BREAK_RATIO : W2U_AURA_POWER_RATIO);
}

} // namespace

extern "C" void W2U_AuraField_ResetBattleState()
{
    ClearAuraFieldState();
}

extern "C" bool W2U_AuraField_AddEffectOwner(ServerFlow* serverFlow, u32 pokemonSlot, FIELD_EFFECT fieldEffect)
{
    (void)serverFlow;
    if (!IsManagedAuraFieldEffect(fieldEffect)) {
        return false;
    }

    u32 mask = SlotMask(pokemonSlot);
    if (!mask) {
        return false;
    }

    AuraFieldEffectState* effect = &sAuraFieldState.effects[fieldEffect];
    if (effect->ownerMask & mask) {
        return false;
    }

    if (!effect->active) {
        effect->item = AddAuraFieldEvent(fieldEffect, pokemonSlot);
        if (!effect->item) {
            return false;
        }
        effect->active = true;
    }

    effect->ownerMask |= mask;
    ++effect->ownerCount;
    return true;
}

extern "C" bool W2U_AuraField_RemoveEffectOwner(u32 pokemonSlot, FIELD_EFFECT fieldEffect)
{
    if (!IsManagedAuraFieldEffect(fieldEffect)) {
        return false;
    }

    u32 mask = SlotMask(pokemonSlot);
    if (!mask) {
        return false;
    }

    AuraFieldEffectState* effect = &sAuraFieldState.effects[fieldEffect];
    if ((effect->ownerMask & mask) == 0) {
        return false;
    }

    effect->ownerMask &= ~mask;
    if (effect->ownerCount) {
        --effect->ownerCount;
    }

    if (effect->ownerCount == 0) {
        if (effect->item) {
            BattleEventItem_Remove(effect->item);
        }
        effect->item = 0;
        effect->active = false;
    }

    return true;
}

extern "C" bool W2U_AuraField_AddAuraBreakMon(u32 pokemonSlot)
{
    u32 mask = SlotMask(pokemonSlot);
    if (!mask || (sAuraFieldState.auraBreakMask & mask)) {
        return false;
    }

    sAuraFieldState.auraBreakMask |= mask;
    ++sAuraFieldState.auraBreakCount;
    return true;
}

extern "C" bool W2U_AuraField_RemoveAuraBreakMon(u32 pokemonSlot)
{
    u32 mask = SlotMask(pokemonSlot);
    if (!mask || (sAuraFieldState.auraBreakMask & mask) == 0) {
        return false;
    }

    sAuraFieldState.auraBreakMask &= ~mask;
    if (sAuraFieldState.auraBreakCount) {
        --sAuraFieldState.auraBreakCount;
    }
    return true;
}

extern "C" u32 W2U_AuraField_GetAuraBreakMons()
{
    return sAuraFieldState.auraBreakCount;
}

extern "C" void HandlerFieldDarkAura(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)pokemonSlot;
    (void)work;
    ApplyAuraPower(TYPE_DARK);
}

BattleEventHandlerTableEntry FieldDarkAuraHandlers[] = {
    {EVENT_MOVE_POWER, HandlerFieldDarkAura},
};

extern "C" BattleEventHandlerTableEntry* EventAddFieldDarkAura(u32* handlerAmount)
{
    *handlerAmount = W2U_ARRAY_COUNT(FieldDarkAuraHandlers);
    return FieldDarkAuraHandlers;
}

extern "C" void HandlerFieldFairyAura(BattleEventItem* item, ServerFlow* serverFlow, u32 pokemonSlot, u32* work)
{
    (void)item;
    (void)serverFlow;
    (void)pokemonSlot;
    (void)work;
    ApplyAuraPower(TYPE_FAIRY);
}

BattleEventHandlerTableEntry FieldFairyAuraHandlers[] = {
    {EVENT_MOVE_POWER, HandlerFieldFairyAura},
};

extern "C" BattleEventHandlerTableEntry* EventAddFieldFairyAura(u32* handlerAmount)
{
    *handlerAmount = W2U_ARRAY_COUNT(FieldFairyAuraHandlers);
    return FieldFairyAuraHandlers;
}

namespace {

BattleEventHandlerTableEntry* GetAuraFieldHandlers(FIELD_EFFECT fieldEffect, u32* handlerAmount)
{
    if (fieldEffect == FLDEFF_DARK_AURA) {
        return EventAddFieldDarkAura(handlerAmount);
    }
    if (fieldEffect == FLDEFF_FAIRY_AURA) {
        return EventAddFieldFairyAura(handlerAmount);
    }

    *handlerAmount = 0;
    return 0;
}

} // namespace
