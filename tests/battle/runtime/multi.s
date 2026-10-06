.syntax unified
.cpu arm946e-s
.thumb
.text
.balign 4
.global FULL_COPY_ARM9_0x020182c0
.type FULL_COPY_ARM9_0x020182c0,%object
FULL_COPY_ARM9_0x020182c0:
 push {r3}
 ldr r3,1f
 mov ip,r3
 pop {r3}
 bx ip
 .balign 4
1: .word W2UTest_SetMultiTrainer
.size FULL_COPY_ARM9_0x020182c0,.-FULL_COPY_ARM9_0x020182c0
