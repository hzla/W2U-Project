.thumb

.type THUMB_BRANCH_LINK_168_0x21DF2C0, %function
.type THUMB_BRANCH_LINK_168_0x21DF2F8, %function
.type THUMB_BRANCH_LINK_168_0x21DF248, %function
.type THUMB_BRANCH_LINK_167_0x21B2416, %function

.extern W2U_BattleAnim_Update
.extern W2U_BattleAnim_Draw
.extern W2U_BattleAnim_Term
.extern W2U_BattleAnim_PatchMegaSummaryCache

@ Preserve BTLV_CLACT_Main, then update custom battle PWAN actors before
@ the native battle MCSS draw pass.
THUMB_BRANCH_LINK_168_0x21DF2C0:
    push {r0-r3, lr}
    ldr r3, =0x021E98E5
    blx r3
    bl W2U_BattleAnim_Update
    pop {r0-r3, pc}
    .size THUMB_BRANCH_LINK_168_0x21DF2C0, . - THUMB_BRANCH_LINK_168_0x21DF2C0

@ Native MCSS owns drawing now; this callback is intentionally a no-op after
@ the regular buffer swap, but is kept as a convenient future draw hook.
THUMB_BRANCH_LINK_168_0x21DF2F8:
    push {r0-r3, lr}
    ldr r3, =0x02049ACD
    blx r3
    bl W2U_BattleAnim_Draw
    pop {r0-r3, pc}
    .size THUMB_BRANCH_LINK_168_0x21DF2F8, . - THUMB_BRANCH_LINK_168_0x21DF2F8

@ Free the native battle effect work as usual, then clear custom OAM.
THUMB_BRANCH_LINK_168_0x21DF248:
    push {r0-r3, lr}
    ldr r3, =0x0203A279
    blx r3
    bl W2U_BattleAnim_Term
    pop {r0-r3, pc}
    .size THUMB_BRANCH_LINK_168_0x21DF248, . - THUMB_BRANCH_LINK_168_0x21DF248

@ Preserve the single-battle command UI state machine, then patch the
@ mid-battle Pokemon status cache after that UI has had a chance to allocate it.
THUMB_BRANCH_LINK_167_0x21B2416:
    push {r1-r3, lr}
    ldr r3, =0x021B2259
    blx r3
    push {r0}
    bl W2U_BattleAnim_PatchMegaSummaryCache
    pop {r0}
    pop {r1-r3}
    pop {r1}
    bx r1
    .size THUMB_BRANCH_LINK_167_0x21B2416, . - THUMB_BRANCH_LINK_167_0x21B2416
