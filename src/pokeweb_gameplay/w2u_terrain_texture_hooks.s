.thumb

.type THUMB_BRANCH_LINK_168_0x21DE1D0, %function
.type THUMB_BRANCH_LINK_168_0x21E05C2, %function
.type THUMB_BRANCH_LINK_168_0x21DF1DE, %function
.type THUMB_BRANCH_LINK_167_0x21B733E, %function

.extern W2U_TerrainTexture_FieldInit
.extern W2U_TerrainTexture_ApplyPending
.extern W2U_TerrainTexture_AdvanceAnimation
.extern W2U_TerrainTexture_FieldExit
.extern W2U_TerrainTexture_OnSetMessageStart

@ BTLV_FIELD_Init has selected and loaded the season-specific NSBMD. Preserve
@ its native VRAM upload, then give the viewer the resource and selected member.
@ At this callsite r4 is BTLV_FIELD_WORK, r6 is the background-table row, and
@ r5 is the u16 season offset.  0xffff falls back to Spring (entry zero).
THUMB_BRANCH_LINK_168_0x21DE1D0:
    push {r1-r7, lr}
    ldr r3, =0x020494D9
    blx r3
    mov r7, r0
    cmp r7, #0
    beq .Lfield_upload_done
    ldrh r1, [r6, r5]
    ldr r2, =0x0000FFFF
    cmp r1, r2
    bne .Lfield_member_ready
    ldrh r1, [r6, #0]
.Lfield_member_ready:
    mov r2, r1
    ldr r1, [r4, #0]
    mov r0, r4
    bl W2U_TerrainTexture_FieldInit
    b .Lfield_init_done
.Lfield_init_done:
.Lfield_upload_done:
    mov r0, r7
    pop {r1-r7}
    pop {r1}
    bx r1
    .size THUMB_BRANCH_LINK_168_0x21DE1D0, . - THUMB_BRANCH_LINK_168_0x21DE1D0

@ Apply a resource prepared by the logical terrain move after native battle
@ VBlank work, then advance its primary-floor UV animation. Texture and
@ palette transfers therefore never expose a partial frame.
THUMB_BRANCH_LINK_168_0x21E05C2:
    push {r0-r3, lr}
    ldr r3, =0x0204B7F5
    blx r3
    bl W2U_TerrainTexture_ApplyPending
    bl W2U_TerrainTexture_AdvanceAnimation
    pop {r0-r3}
    pop {r1}
    bx r1
    .size THUMB_BRANCH_LINK_168_0x21E05C2, . - THUMB_BRANCH_LINK_168_0x21E05C2

@ Detach and free the borrowed-key replacement before vanilla destroys the
@ original field resource and its VRAM allocation.
THUMB_BRANCH_LINK_168_0x21DF1DE:
    push {r0-r3, lr}
    bl W2U_TerrainTexture_FieldExit
    pop {r0-r3}
    ldr r3, =0x021DE5E5
    blx r3
    pop {r1}
    bx r1
    .size THUMB_BRANCH_LINK_168_0x21DF1DE, . - THUMB_BRANCH_LINK_168_0x21DF1DE

@ SC_MSG_SET has reached the viewer and is about to start drawing its text.
@ Notify the terrain texture layer with the message ID before preserving the
@ native BTLV_StartMsgSet call.  Terrain expiry uses this boundary so the
@ field texture and the disappearance message become visible together.
THUMB_BRANCH_LINK_167_0x21B733E:
    push {r0-r3, lr}
    mov r0, r1
    bl W2U_TerrainTexture_OnSetMessageStart
    pop {r0-r3}
    ldr r3, =0x021D02AD
    blx r3
    pop {r1}
    bx r1
    .size THUMB_BRANCH_LINK_167_0x21B733E, . - THUMB_BRANCH_LINK_167_0x21B733E
