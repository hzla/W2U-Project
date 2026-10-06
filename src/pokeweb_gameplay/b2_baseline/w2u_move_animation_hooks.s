.thumb

.equ W2U_BATTLE_ANIMATIONS_COUNT, 115
.equ W2U_FIRST_NEW_MOVE_ANIMATION_ID, 676

.type THUMB_BRANCH_LINK_LoadAnimationScriptFile_0xB6, %function
.type THUMB_BRANCH_LINK_BtlvEffect_LoadAnimationScript_0x1A, %function

@ Preserve vanilla archive selection for fixed battle animations, but route
@ expanded move IDs back into the move-animation archive after the +115 offset.
THUMB_BRANCH_LINK_LoadAnimationScriptFile_0xB6:
    push    {lr}
    ldr     r3, =0x7FFF
    cmp     r1, r0
    blt     1f
    ldr     r0, =W2U_FIRST_NEW_MOVE_ANIMATION_ID
    cmp     r1, r0
    bge     2f
    movs    r1, #1
    b       3f
2:
    sub     r6, #W2U_BATTLE_ANIMATIONS_COUNT
1:
    movs    r1, #0
3:
    movs    r0, #1
    cmp     r1, r0
    pop     {pc}
    .size THUMB_BRANCH_LINK_LoadAnimationScriptFile_0xB6, . - THUMB_BRANCH_LINK_LoadAnimationScriptFile_0xB6

THUMB_BRANCH_LINK_BtlvEffect_LoadAnimationScript_0x1A:
    push    {r6, r7, lr}
    ldr     r3, =0x7FFF
    cmp     r4, r0
    blt     1f
    ldr     r0, =W2U_FIRST_NEW_MOVE_ANIMATION_ID
    cmp     r4, r0
    bge     2f
    movs    r6, #1
    b       3f
2:
    sub     r4, #W2U_BATTLE_ANIMATIONS_COUNT
1:
    movs    r6, #0
3:
    movs    r7, #1
    cmp     r6, r7
    pop     {r6, r7, pc}
    .size THUMB_BRANCH_LINK_BtlvEffect_LoadAnimationScript_0x1A, . - THUMB_BRANCH_LINK_BtlvEffect_LoadAnimationScript_0x1A
