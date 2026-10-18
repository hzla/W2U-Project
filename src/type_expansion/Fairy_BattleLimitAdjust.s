.thumb

.equ TypeCnt, 0x12

@ Each patch is whole Thumb instructions: CTRMap copies a FULL_COPY in halfwords, so a one-byte patch also wrote
@ the next patch's first byte over the instruction's opcode (a `movs r1, #0x11` became `asrs r2, r2, #8`).

@ The move buttons' palette per type (data_ov168_021f3864, 17 entries): Fairy's goes after them.
FULL_COPY_168_0x021F38E8:
    .word 572
    .size FULL_COPY_168_0x021F38E8, . - FULL_COPY_168_0x021F38E8

@ ServerEvent_CalcDamage: no same-type bonus for a typeless move (cmp r2, #TypeCnt; bge)
FULL_COPY_167_0x21A5A92:
    .byte TypeCnt, 0x2A, 0x08, 0xDA
    .size FULL_COPY_167_0x21A5A92, . - FULL_COPY_167_0x21A5A92

@ The type effectiveness of a move (func_ov167_021aa954): a typeless move is neutral (cmp r0, #TypeCnt; blt)
FULL_COPY_167_0x21AA9A6:
    .byte TypeCnt, 0x28, 0x02, 0xDB
    .size FULL_COPY_167_0x21AA9A6, . - FULL_COPY_167_0x21AA9A6

@ splitTypeCore: Roost's Flying is typeless (movs r1, #TypeCnt / movs r0, #TypeCnt), and a typeless type gives
@ way to the other one (cmp r1, #TypeCnt; blt / cmp r0, #TypeCnt; blt)
FULL_COPY_167_0x21BB004:
    movs r1, #TypeCnt
    .size FULL_COPY_167_0x21BB004, . - FULL_COPY_167_0x21BB004

FULL_COPY_167_0x21BB016:
    movs r0, #TypeCnt
    .size FULL_COPY_167_0x21BB016, . - FULL_COPY_167_0x21BB016

FULL_COPY_167_0x21BB022:
    .byte TypeCnt, 0x29, 0x06, 0xDB
    .byte TypeCnt, 0x28, 0x01, 0xDB
    .size FULL_COPY_167_0x21BB022, . - FULL_COPY_167_0x21BB022

FULL_COPY_167_0x21BB034:
    .byte TypeCnt, 0x28, 0x00, 0xDB
    .size FULL_COPY_167_0x21BB034, . - FULL_COPY_167_0x21BB034

@ DoesMonHaveType: no Pokémon has the typeless type (cmp r4, #TypeCnt; bge)
FULL_COPY_167_0x21BB05A:
    .byte TypeCnt, 0x2C, 0x0E, 0xDA
    .size FULL_COPY_167_0x21BB05A, . - FULL_COPY_167_0x21BB05A

@ GetTypeEffectiveness is replaced by THUMB_BRANCH_GetTypeEffectiveness in Types.cpp.
@ Do not also patch the vanilla row stride here; that leaves the old 17x17 embedded
@ chart active with an 18-wide stride when the hooks race, making Flying vs Bug read
@ as not very effective.
@ GetTypeWeaknesses' loop bound (the function is replaced by THUMB_BRANCH_GetTypeWeaknesses too)
FULL_COPY_167_0x21BD318:
    cmp r3, #TypeCnt
    .size FULL_COPY_167_0x21BD318, . - FULL_COPY_167_0x21BD318

@ Instances where type 17 is checked for type none.
@ HandlerColorChange: not for a typeless move (cmp r6, #TypeCnt)
FULL_COPY_167_0x21BF862:
    cmp r6, #TypeCnt
    .size FULL_COPY_167_0x21BF862, . - FULL_COPY_167_0x21BF862

@ HandlerConversion2: fails on a typeless previous move (cmp r4, #TypeCnt), and its type list holds every type
@ (movs r1, #TypeCnt)
FULL_COPY_167_0x21C9E70:
    cmp r4, #TypeCnt
    .size FULL_COPY_167_0x21C9E70, . - FULL_COPY_167_0x21C9E70

FULL_COPY_167_0x21C9E76:
    movs r1, #TypeCnt
    .size FULL_COPY_167_0x21C9E76, . - FULL_COPY_167_0x21C9E76

@ Not 0x21AE0B0: that 0x11 in BattleHandler_Transform is GetBattleMonStat's effective ability (0x11), not a type;
@ as 0x12 (the sex) it ran the ability-change event after every Transform.

@ The previous move's type is 17 for "no move yet" (BattleMon_Create, ClearUsedMoveFlag, TransformSet): as Fairy,
@ Conversion 2 resisted it before the target had moved (movs r2 / r2 / r1, #TypeCnt).
FULL_COPY_167_0x21BA6E8:
    movs r2, #TypeCnt
    .size FULL_COPY_167_0x21BA6E8, . - FULL_COPY_167_0x21BA6E8

FULL_COPY_167_0x21BABCE:
    movs r2, #TypeCnt
    .size FULL_COPY_167_0x21BABCE, . - FULL_COPY_167_0x21BABCE

FULL_COPY_167_0x21BC562:
    movs r1, #TypeCnt
    .size FULL_COPY_167_0x21BC562, . - FULL_COPY_167_0x21BC562
