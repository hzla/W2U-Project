.syntax unified
.thumb

@ Native Transform success tail, shared by server and client BattleMons.
@ r4=user, r7=target. Replay ORR/STRB setting the native Transform flag, then
@ fill the unused base-param species word (0xec). The following native MOV
@ restores the Boolean return value. Failed Transform never reaches this hook.
@ Copy narrow resident critical-boost and direct-hit histories after Transform.
.type THUMB_BRANCH_LINK_167_0x21BC572, %function
THUMB_BRANCH_LINK_167_0x21BC572:
    orrs r0, r1
    strb r0, [r4, #27]
    ldrh r1, [r7, #12]
    movs r0, #0xec
    strh r1, [r4, r0]
    push {r3, lr}
    movs r0, r4
    movs r1, r7
    bl W2U_CopyTransformMoveState
    pop {r3, pc}
    .size THUMB_BRANCH_LINK_167_0x21BC572, . - THUMB_BRANCH_LINK_167_0x21BC572
