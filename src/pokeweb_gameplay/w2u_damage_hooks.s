.syntax unified
.thumb
.section .text
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
