.syntax unified
.thumb
.section .text
.global THUMB_BRANCH_LINK_ServerControl_CheckFainted_0x30
.type THUMB_BRANCH_LINK_ServerControl_CheckFainted_0x30, %function
.thumb_func
@ W2/B2 CheckFainted: native dead latch is set before Add(record, slot).
@ r4 retains ServerFlow. This observes committed faints, not switch notices.
THUMB_BRANCH_LINK_ServerControl_CheckFainted_0x30:
    movs r2, r4
    ldr r3, =W2U_RecordCommittedFaint
    bx r3
    .size THUMB_BRANCH_LINK_ServerControl_CheckFainted_0x30, . - THUMB_BRANCH_LINK_ServerControl_CheckFainted_0x30

.global THUMB_BRANCH_LINK_ServerEvent_CalcDamage_0x1C0
.type THUMB_BRANCH_LINK_ServerEvent_CalcDamage_0x1C0, %function
.thumb_func
@ Verified US W2/B2 CalcDamage call at entry + 0x1C0 stores the
@ u32 final result at [sp,#8] before its event-0x48 call, in both branches.
@ Tail forwarding preserves the native SP/LR and all callee-saved registers.
THUMB_BRANCH_LINK_ServerEvent_CalcDamage_0x1C0:
    add r2, sp, #8
    ldr r3, =W2U_DispatchFinalMoveDamage
    bx r3
    .size THUMB_BRANCH_LINK_ServerEvent_CalcDamage_0x1C0, . - THUMB_BRANCH_LINK_ServerEvent_CalcDamage_0x1C0

.global THUMB_BRANCH_LINK_ServerEvent_GetAttackPower_0x4E
.type THUMB_BRANCH_LINK_ServerEvent_GetAttackPower_0x4E, %function
.thumb_func
@ Verified US W2/B2 +0x4E: r5=MoveParam, r4=raw-stat selector,
@ r0=ServerFlow, r1=native event 0x39. Preserve the native frame and pass
@ the selected stat back in r4 before its raw/staged/critical readers.
THUMB_BRANCH_LINK_ServerEvent_GetAttackPower_0x4E:
    push {r3, lr}
    movs r2, r5
    movs r3, r4
    ldr r4, =W2U_DispatchAttackStatSelector
    blx r4
    movs r4, r0
    pop {r3, pc}
    .size THUMB_BRANCH_LINK_ServerEvent_GetAttackPower_0x4E, . - THUMB_BRANCH_LINK_ServerEvent_GetAttackPower_0x4E

.global THUMB_BRANCH_LINK_167_0x21A462A
.type THUMB_BRANCH_LINK_167_0x21A462A, %function
.thumb_func
@ Native per-hit classifier: r0=defender, [sp,#32]=MoveParam.
@ Preserve SP/LR so the caller stores our result in its normal damage flags.
THUMB_BRANCH_LINK_167_0x21A462A:
    ldr r1, [sp, #32]
    ldr r3, =W2U_CheckDamagingSubstitute
    bx r3
    .size THUMB_BRANCH_LINK_167_0x21A462A, . - THUMB_BRANCH_LINK_167_0x21A462A

.global THUMB_BRANCH_LINK_ServerControl_DamageRoot_0x5E
.type THUMB_BRANCH_LINK_ServerControl_DamageRoot_0x5E, %function
.thumb_func
@ Verified W2/B2: r0=filtered PokeSet, r4=MoveParam. Tail forward without
@ disturbing the native stack or its stored original target count.
THUMB_BRANCH_LINK_ServerControl_DamageRoot_0x5E:
    movs r1, r4
    ldr r3, =W2U_GetFilteredMultiHitTargetCount
    bx r3
    .size THUMB_BRANCH_LINK_ServerControl_DamageRoot_0x5E, . - THUMB_BRANCH_LINK_ServerControl_DamageRoot_0x5E

.global THUMB_BRANCH_LINK_167_0x21A487E
.type THUMB_BRANCH_LINK_167_0x21A487E, %function
.thumb_func
@ Verified W2/B2 SingleCount ratio selector: [sp,#16]=MoveParam, r0=PokeSet.
THUMB_BRANCH_LINK_167_0x21A487E:
    ldr r1, [sp, #16]
    ldr r3, =W2U_GetDamageSpreadTargetCount
    bx r3
    .size THUMB_BRANCH_LINK_167_0x21A487E, . - THUMB_BRANCH_LINK_167_0x21A487E
