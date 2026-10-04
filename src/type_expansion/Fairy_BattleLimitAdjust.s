.thumb

.equ TypeCnt, 0x12

FULL_COPY_168_0x021F38E8:
    .word 572
    .size FULL_COPY_168_0x021F38E8, . - FULL_COPY_168_0x021F38E8

FULL_COPY_167_0x21A5A92:
    .byte TypeCnt, 0x2A, 0x08, 0xDA
    .size FULL_COPY_167_0x21A5A92, . - FULL_COPY_167_0x21A5A92

FULL_COPY_167_0x21AA9A6:
    .byte TypeCnt, 0x28, 0x02, 0xDB
    .size FULL_COPY_167_0x21AA9A6, . - FULL_COPY_167_0x21AA9A6

FULL_COPY_167_0x21BB004:
    .byte TypeCnt
    .size FULL_COPY_167_0x21BB004, . - FULL_COPY_167_0x21BB004

FULL_COPY_167_0x21BB016:
    .byte TypeCnt
    .size FULL_COPY_167_0x21BB016, . - FULL_COPY_167_0x21BB016

FULL_COPY_167_0x21BB022:
    .byte TypeCnt, 0x29, 0x06, 0xDB
    .byte TypeCnt, 0x28, 0x01, 0xDB
    .size FULL_COPY_167_0x21BB022, . - FULL_COPY_167_0x21BB022

FULL_COPY_167_0x21BB034:
    .byte TypeCnt, 0x28, 0x00, 0xDB
    .size FULL_COPY_167_0x21BB034, . - FULL_COPY_167_0x21BB034

FULL_COPY_167_0x21BB05A:
    .byte TypeCnt, 0x2C, 0x0E, 0xDA
    .size FULL_COPY_167_0x21BB05A, . - FULL_COPY_167_0x21BB05A

@ GetTypeEffectiveness is replaced by THUMB_BRANCH_GetTypeEffectiveness in Types.cpp.
@ Do not also patch the vanilla row stride here; that leaves the old 17x17 embedded
@ chart active with an 18-wide stride when the hooks race, making Flying vs Bug read
@ as not very effective.
FULL_COPY_167_0x21BD318:
    .byte TypeCnt
    .size FULL_COPY_167_0x21BD318, . - FULL_COPY_167_0x21BD318

@ Instances where type 17 is checked for type none.
FULL_COPY_167_0x21BB026:
    .byte TypeCnt
    .size FULL_COPY_167_0x21BB026, . - FULL_COPY_167_0x21BB026

FULL_COPY_167_0x21BF862:
    .byte TypeCnt
    .size FULL_COPY_167_0x21BF862, . - FULL_COPY_167_0x21BF862

FULL_COPY_167_0x21C9E70:
    .byte TypeCnt
    .size FULL_COPY_167_0x21C9E70, . - FULL_COPY_167_0x21C9E70

FULL_COPY_167_0x21C9E76:
    .byte TypeCnt
    .size FULL_COPY_167_0x21C9E76, . - FULL_COPY_167_0x21C9E76

FULL_COPY_167_0x21AE0B0:
    .byte TypeCnt
    .size FULL_COPY_167_0x21AE0B0, . - FULL_COPY_167_0x21AE0B0
