.thumb

.type THUMB_BRANCH_LINK_BattleClient_ActionSelectRoot_0x58, %function
.type THUMB_BRANCH_LINK_BattleClient_ActionSelectFight_0x8E, %function
.type THUMB_BRANCH_LINK_BattleClient_ActionSelectFight_0x9A, %function
.type THUMB_BRANCH_LINK_168_0x21EB65C, %function
.type THUMB_BRANCH_LINK_169_0x689ACE8, %function
.type W2U_DISABLED_THUMB_BRANCH_LINK_ServerFlow_ActOrderProcMain_0x56, %function
.type THUMB_BRANCH_LINK_167_0x21B8A52, %function
.type THUMB_BRANCH_LINK_167_0x21B8A60, %function

@ Preserve the original BattleAction_SetNull call and run Mega root cleanup.
THUMB_BRANCH_LINK_BattleClient_ActionSelectRoot_0x58:
    push {r0-r3, lr}
    bl W2U_Mega_OnActionSelectRoot
    pop {r0-r3}
    bl BattleAction_SetNull
    pop {r1}
    bx r1
    .size THUMB_BRANCH_LINK_BattleClient_ActionSelectRoot_0x58, . - THUMB_BRANCH_LINK_BattleClient_ActionSelectRoot_0x58

@ Poll Mega input before vanilla move wait, then draw the sub-screen button after it.
THUMB_BRANCH_LINK_BattleClient_ActionSelectFight_0x8E:
    push {r0-r3, lr}
    bl W2U_Mega_OnActionSelectFightWait
    pop {r0-r3}
    push {r0}
    bl BattleViewCmd_UI_SelectMove_Wait
    pop {r1}
    push {r0-r3}
    mov r0, r1
    bl W2U_Mega_OnActionSelectFightPostWait
    pop {r0-r3}
    pop {r1}
    bx r1
    .size THUMB_BRANCH_LINK_BattleClient_ActionSelectFight_0x8E, . - THUMB_BRANCH_LINK_BattleClient_ActionSelectFight_0x8E

@ Preserve the original BattleAction_GetAction call and commit a queued Mega flag.
THUMB_BRANCH_LINK_BattleClient_ActionSelectFight_0x9A:
    push {r1-r3, lr}
    push {r0}
    bl BattleAction_GetAction
    pop {r1}
    mov r2, r0
    push {r2}
    mov r0, r1
    mov r1, r2
    bl W2U_Mega_OnActionSelected
    pop {r0}
    pop {r1-r3, pc}
    .size THUMB_BRANCH_LINK_BattleClient_ActionSelectFight_0x9A, . - THUMB_BRANCH_LINK_BattleClient_ActionSelectFight_0x9A

@ Substitute the move-selection touch table with one that appends Mega at index 6.
@ This preserves the original BTLV_INPUT_CheckKey ABI, including stack args.
THUMB_BRANCH_LINK_168_0x21EB65C:
    push {r4-r5, lr}
    ldr r4, [sp,#12]
    ldr r5, [sp,#16]
    sub sp, #8
    str r4, [sp,#0]
    str r5, [sp,#4]
    bl W2U_Mega_WrapNativeInputCheckKey
    add sp, #8
    pop {r4-r5}
    pop {r1}
    bx r1
    .size THUMB_BRANCH_LINK_168_0x21EB65C, . - THUMB_BRANCH_LINK_168_0x21EB65C

@ Preserve the original native move-select input helper, then consume hit index 6.
@ r0 is BTLV_INPUT_WORK*, r1 is the waza-info out byte, r2 is the hit out int.
THUMB_BRANCH_LINK_169_0x689ACE8:
    push {r0-r3, lr}
    ldr r3, =0x0689AD85
    blx r3
    push {r0}
    ldr r3, [sp,#0]
    ldr r2, [sp,#12]
    ldr r1, [sp,#8]
    ldr r0, [sp,#4]
    bl W2U_Mega_OnNativeMoveSelectInputAfter
    add sp, #20
    pop {r1}
    bx r1
    .size THUMB_BRANCH_LINK_169_0x689ACE8, . - THUMB_BRANCH_LINK_169_0x689ACE8

@ Preserve the original sub_0219FAA0 call in ServerFlow_ActOrderProcMain.
@ Only run Mega action-order processing when a selected action committed a form.
W2U_DISABLED_THUMB_BRANCH_LINK_ServerFlow_ActOrderProcMain_0x3A:
    push {r0-r3, lr}
    bl W2U_Mega_OnActionOrderHook
    cmp r0, #0
    beq 1f
    mov r0, r5
    bl W2U_Mega_ProcessActionOrder
1:
    pop {r0-r3}
    ldr r3, =0x0219FAA1
    blx r3
    pop {r1}
    bx r1
    .size W2U_DISABLED_THUMB_BRANCH_LINK_ServerFlow_ActOrderProcMain_0x3A, . - W2U_DISABLED_THUMB_BRANCH_LINK_ServerFlow_ActOrderProcMain_0x3A

@ Disabled: Dancer now replaces ServerFlow_ActOrderProcMain as a whole loop.
@ r0 is ServerFlow*, r1 is current ActionOrderWork*.
W2U_DISABLED_THUMB_BRANCH_LINK_ServerFlow_ActOrderProcMain_0x56:
    push {lr}
    bl W2U_ActionOrder_ProcWithExtras
    pop {r1}
    bx r1
    .size W2U_DISABLED_THUMB_BRANCH_LINK_ServerFlow_ActOrderProcMain_0x56, . - W2U_DISABLED_THUMB_BRANCH_LINK_ServerFlow_ActOrderProcMain_0x56

@ Preserve the client SC_ACT_CHANGE_FORM call to BattleViewCmd_ChangeForm_Start.
@ At this site r6 is the server command args and r7 is the resolved view pos.
THUMB_BRANCH_LINK_167_0x21B8A52:
    push {r0-r3, lr}
    mov r0, r6
    mov r1, r7
    bl W2U_Mega_OnClientChangeFormStart
    pop {r0-r3}
    ldr r3, =0x021D04A1
    blx r3
    pop {r1}
    bx r1
    .size THUMB_BRANCH_LINK_167_0x21B8A52, . - THUMB_BRANCH_LINK_167_0x21B8A52

@ Preserve the client SC_ACT_CHANGE_FORM call to BattleViewCmd_ChangeForm_Wait.
@ Only after the vanilla wait returns true is the transform animation complete.
THUMB_BRANCH_LINK_167_0x21B8A60:
    push {r1-r3, lr}
    ldr r3, =0x021D04BD
    blx r3
    mov r1, r0
    push {r0}
    mov r0, r6
    bl W2U_Mega_OnClientChangeFormWait
    pop {r0}
    pop {r1-r3}
    pop {r2}
    bx r2
    .size THUMB_BRANCH_LINK_167_0x21B8A60, . - THUMB_BRANCH_LINK_167_0x21B8A60

@ Pass the BattleMon pointer to the unremovable-item check used by Trick.
FULL_COPY_HandlerTrick_0x6C:
    nop
    .size FULL_COPY_HandlerTrick_0x6C, . - FULL_COPY_HandlerTrick_0x6C

FULL_COPY_HandlerTrick_0x82:
    ldr r0, [sp,#0x4]
    .size FULL_COPY_HandlerTrick_0x82, . - FULL_COPY_HandlerTrick_0x82

FULL_COPY_HandlerTrick_0x9A:
    ldr r0, [sp,#0x4]
    .size FULL_COPY_HandlerTrick_0x9A, . - FULL_COPY_HandlerTrick_0x9A

@ Pass the BattleMon pointer to the unremovable-item check used by Bestow.
FULL_COPY_HandlerBestow_0x66:
    nop
    .size FULL_COPY_HandlerBestow_0x66, . - FULL_COPY_HandlerBestow_0x66

FULL_COPY_HandlerCommon_CheckUnchangeableItem_0x18:
    movs r0, r5
    .size FULL_COPY_HandlerCommon_CheckUnchangeableItem_0x18, . - FULL_COPY_HandlerCommon_CheckUnchangeableItem_0x18

FULL_COPY_HandlerCommon_CheckIfCanStealPokeItem_0x4A:
    movs r0, r4
    .size FULL_COPY_HandlerCommon_CheckIfCanStealPokeItem_0x4A, . - FULL_COPY_HandlerCommon_CheckIfCanStealPokeItem_0x4A
