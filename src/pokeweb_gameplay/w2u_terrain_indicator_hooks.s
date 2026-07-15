.thumb

.type THUMB_BRANCH_LINK_168_0x21EACD0, %function
.type THUMB_BRANCH_LINK_168_0x21EA714, %function
.type THUMB_BRANCH_LINK_168_0x21EE2E2, %function

.extern W2U_TerrainIndicator_Create
.extern W2U_TerrainIndicator_Hide
.extern W2U_TerrainIndicator_Term

@ The vanilla command-screen path has just created Weather. Build Terrain from
@ the same battgra resource group so both indicators share native OAM lifetime.
THUMB_BRANCH_LINK_168_0x21EACD0:
    push {r0-r3, lr}
    ldr r3, =0x021EE749
    blx r3
    ldr r0, [sp, #0]
    bl W2U_TerrainIndicator_Create
    pop {r0-r3}
    pop {r1}
    bx r1
    .size THUMB_BRANCH_LINK_168_0x21EACD0, . - THUMB_BRANCH_LINK_168_0x21EACD0

@ BTLV_INPUT_ExitBG: remove both widgets and destroy Terrain's private CLUNIT
@ before the battle input heap and shared graphics registrations are released.
THUMB_BRANCH_LINK_168_0x21EA714:
    push {r0-r3, lr}
    ldr r3, =0x021EE8ED
    blx r3
    bl W2U_TerrainIndicator_Term
    pop {r0-r3}
    pop {r1}
    bx r1
    .size THUMB_BRANCH_LINK_168_0x21EA714, . - THUMB_BRANCH_LINK_168_0x21EA714

@ BTLV_INPUT_ClearScreen: mirror Weather cleanup while retaining the CLUNIT for
@ the next command-screen transition in the same battle.
THUMB_BRANCH_LINK_168_0x21EE2E2:
    push {r0-r3, lr}
    ldr r3, =0x021EE8ED
    blx r3
    bl W2U_TerrainIndicator_Hide
    pop {r0-r3}
    pop {r1}
    bx r1
    .size THUMB_BRANCH_LINK_168_0x21EE2E2, . - THUMB_BRANCH_LINK_168_0x21EE2E2
