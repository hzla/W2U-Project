.thumb

.type	THUMB_BRANCH_LINK_299_0x021A0488, %function
.type	THUMB_BRANCH_LINK_299_0x021A04CA, %function
.type	THUMB_BRANCH_LINK_299_0x021A04F2, %function
.type	THUMB_BRANCH_LINK_299_0x021A053C, %function
.type	THUMB_BRANCH_LINK_299_0x021A0578, %function

.equ PkmnCnt, 721
.equ RegionalDexPkmCnt, 302
.equ RegionalDexFile, 826

.equ ALWAYS_HAVE_NATL_DEX, 1

@ when clicking on dex in the menu: 302, 301
@ sliding animation: 299, 139
@ blah blah unnecessary
@ habitat: 304, 139

@ ARM9 Patches
FULL_COPY_ARM9_0x0200C1C4: @ Based on what?
    .word PkmnCnt
    .size FULL_COPY_ARM9_0x0200C1C4, . - FULL_COPY_ARM9_0x0200C1C4

FULL_COPY_ARM9_0x0200CEA0: @ Limiter on mon species being invalid
    .word PkmnCnt
    .size FULL_COPY_ARM9_0x0200CEA0, . - FULL_COPY_ARM9_0x0200CEA0

FULL_COPY_ARM9_0x0200D6DC: @ CountDexPkm
    .word PkmnCnt
    .size FULL_COPY_ARM9_0x0200D6DC, . - FULL_COPY_ARM9_0x0200D6DC

FULL_COPY_ARM9_0x0200DB00: @ CountUnovaDexPokes
    .word PkmnCnt
    .size FULL_COPY_ARM9_0x0200DB00, . - FULL_COPY_ARM9_0x0200DB00

FULL_COPY_ARM9_0x0200D728: @ CountRegionalPokesByIndices
    .word PkmnCnt
    .size FULL_COPY_ARM9_0x0200D728, . - FULL_COPY_ARM9_0x0200D728

FULL_COPY_ARM9_0x0200D884: @ CountSeenNationalDexPkm
    .word PkmnCnt
    .size FULL_COPY_ARM9_0x0200D884, . - FULL_COPY_ARM9_0x0200D884

FULL_COPY_ARM9_0x0200D8D0: @ CountSeenRegionalDexPkm
    .word PkmnCnt
    .size FULL_COPY_ARM9_0x0200D8D0, . - FULL_COPY_ARM9_0x0200D8D0

FULL_COPY_ARM9_0x0200DAA8: @ CountPokesInNatDex
    .word PkmnCnt
    .size FULL_COPY_ARM9_0x0200DAA8, . - FULL_COPY_ARM9_0x0200DAA8

FULL_COPY_ARM9_0x0200DB58: @ CountUnovaSeenPokes
    .word PkmnCnt
    .size FULL_COPY_ARM9_0x0200DB58, . - FULL_COPY_ARM9_0x0200DB58


@ .if ALWAYS_HAVE_NATL_DEX
@ FULL_COPY_ARM9_0x0200D1AC:
@     mov r0, #1
@     bx lr
@     .size FULL_COPY_ARM9_0x0200D1AC, . - FULL_COPY_ARM9_0x0200D1AC
@ .endif

FULL_COPY_ARM9_0x020204A4:
    .word RegionalDexFile
    .size FULL_COPY_ARM9_0x020204A4, . - FULL_COPY_ARM9_0x020204A4

FULL_COPY_ARM9_0x0201DE26:
    nop
    .size FULL_COPY_ARM9_0x0201DE26, . - FULL_COPY_ARM9_0x0201DE26

FULL_COPY_ARM9_0x02033CFC:
    .word 0x1EA, 0x2F3, 0x4621, 0x387C, PkmnCnt
    .size FULL_COPY_ARM9_0x02033CFC, . - FULL_COPY_ARM9_0x02033CFC

@ Overlay 299 patches
FULL_COPY_299_0x0219FC12: @ Expand structure 
    mov r6, #0x1B
    lsl r6, #8
    .size FULL_COPY_299_0x0219FC12, . - FULL_COPY_299_0x0219FC12

FULL_COPY_299_0x021A0520: @ Expand structure 
    .word PkmnCnt
    .size FULL_COPY_299_0x021A0520, . - FULL_COPY_299_0x021A0520

FULL_COPY_299_0x021A0550:
    .word PkmnCnt
    .size FULL_COPY_299_0x021A0550, . - FULL_COPY_299_0x021A0550
    
@ basically all the fucking names are baked into the structure because of course.  we move them to the end here
THUMB_BRANCH_LINK_299_0x021A0488:
THUMB_BRANCH_LINK_299_0x021A04CA:
THUMB_BRANCH_LINK_299_0x021A04F2:
    add r1, r5, r1
    push {r0}
    mov r0, #0xC7
    lsl r0, r0, #0x4
    add r1, r1, r0
    pop {r0}
    str r0, [r1, #0x4]
    bx lr
    .size THUMB_BRANCH_LINK_299_0x021A0488, . - THUMB_BRANCH_LINK_299_0x021A0488
    .size THUMB_BRANCH_LINK_299_0x021A04CA, . - THUMB_BRANCH_LINK_299_0x021A04CA
    .size THUMB_BRANCH_LINK_299_0x021A04F2, . - THUMB_BRANCH_LINK_299_0x021A04F2

THUMB_BRANCH_LINK_299_0x021A053C:
    add r0, r5, r0
    push {r1}
    mov r1, #0xC7
    lsl r1, r1, #0x4
    add r0, r1, r0
    pop {r1}
    ldr r0, [r0, #0x4]
    bx lr
    .size THUMB_BRANCH_LINK_299_0x021A053C, . - THUMB_BRANCH_LINK_299_0x021A053C

THUMB_BRANCH_LINK_299_0x021A0578:
    mov r0, #0xC7
    lsl r0, r0, #0x4
    add r2, r0, r2
    ldr r2, [r2, #0x4]
    mov r0, r5
    bx lr
    .size THUMB_BRANCH_LINK_299_0x021A0578, . - THUMB_BRANCH_LINK_299_0x021A0578

@ mon search lists down

@ .org 0x021ACF2C
@ lsl r2, r6, #0x11

FULL_COPY_302_0x021AE244:
    .word PkmnCnt
    .size FULL_COPY_302_0x021AE244, . - FULL_COPY_302_0x021AE244

FULL_COPY_302_0x021AE310: @ Space Limiter
    .word 2 * PkmnCnt
    .size FULL_COPY_302_0x021AE310, . - FULL_COPY_302_0x021AE310

FULL_COPY_302_0x021AE318: @ what the fuck
    .word PkmnCnt
    .size FULL_COPY_302_0x021AE318, . - FULL_COPY_302_0x021AE318

FULL_COPY_302_0x021AE37C: @ a sort of species limiter
    .word 2 * PkmnCnt
    .size FULL_COPY_302_0x021AE37C, . - FULL_COPY_302_0x021AE37C

FULL_COPY_302_0x021AE384:
    .word PkmnCnt
    .size FULL_COPY_302_0x021AE384, . - FULL_COPY_302_0x021AE384

@ .org 0x021AE3F8
@ 
@ .word PkmnCnt + 1 // file size 

@ grabbing regional dex indices is done 1x when clicking pokedex from the start menu
@ the first is from sub_21AE250 in overlay 302, specifically 021AE290
@ clicking on the sliding up anim, we get a return address of 021A0254 in overlay 299.  smallass function
@ second is 0x0200D896 in the arm9.  this is countSeenRegionalDexPokesByIndices, and is taken care of
@ last is 0x0200D6EE in the arm9.  this is countRegionalDexPokesByIndices, and is taken care of
@ switching over to national dex, it is called with an lr of 0x021A0254--fuck
@ clicking on it when in national dex mode, it then calls it once after slide up anim (none before slide up):
@ 0x021A0254 again
@ switching over to regional dex, it appears that 0x021AE290 is responsible for making the lists
@ 0x021A0255 is called then.  it dumps the list of regional dex mons to +C5C of the dex structure
@ followed by the counting functions agai