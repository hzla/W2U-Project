.thumb

.equ PkmnCnt, 1023
.equ RegionalDexPkmCnt, 302
.equ RegionalDexFile, 1290

.equ ALWAYS_HAVE_NATL_DEX, 1

@ The expanded pokegra shared block moved the Substitute doll from
@ 15020..15032 to 17940..17952. BTLV_MCSS_SetMigawari still uses a native
@ literal pool instead of GetPokemonDataIDBase. Redirect both facing sets
@ and their shared palette; the NCER IDs are derived from palette -11/-5.
@ Keep this base in sync with the graphics staging validation.
.equ SubstituteGraphicsBase, 17940

FULL_COPY_168_0x021E7EBC:
    .word SubstituteGraphicsBase + 0  @ front NCBR
    .word SubstituteGraphicsBase + 6  @ back NCBR
    .word SubstituteGraphicsBase + 12 @ shared NCLR
    .word SubstituteGraphicsBase + 2  @ front NANR
    .word SubstituteGraphicsBase + 8  @ back NANR
    .word SubstituteGraphicsBase + 3  @ front NMCR
    .word SubstituteGraphicsBase + 9  @ back NMCR
    .word SubstituteGraphicsBase + 4  @ front NMAR
    .word SubstituteGraphicsBase + 10 @ back NMAR
    .word SubstituteGraphicsBase + 5  @ front NCEC
    .word SubstituteGraphicsBase + 11 @ back NCEC
    .size FULL_COPY_168_0x021E7EBC, . - FULL_COPY_168_0x021E7EBC

@ when clicking on dex in the menu: 302, 301
@ sliding animation: 299, 139
@ blah blah unnecessary
@ habitat: 304, 139

@ ARM9 Patches...
@ Not sure what this is...?
FULL_COPY_sub_200C124_0xA0:
    .word PkmnCnt
    .size FULL_COPY_sub_200C124_0xA0, . - FULL_COPY_sub_200C124_0xA0

FULL_COPY_PML_PkmDecryptCheck_0x32:
    nop
    .size FULL_COPY_PML_PkmDecryptCheck_0x32, . - FULL_COPY_PML_PkmDecryptCheck_0x32

@ Enable PersonalData load of "egg indexes"
FULL_COPY_PML_PersonalGetDatID_0x5C:
    .word 0xFFFF - PkmnCnt 
    .size FULL_COPY_PML_PersonalGetDatID_0x5C, . - FULL_COPY_PML_PersonalGetDatID_0x5C

@ Expand evolution methods...
@ Add 6 bytes to file size
FULL_COPY_CheckEvolveSpecies_0xAC:
    movs r1, #0x30
    .size FULL_COPY_CheckEvolveSpecies_0xAC, . - FULL_COPY_CheckEvolveSpecies_0xAC

@ Read 1 more entry
FULL_COPY_CheckEvolveSpecies_0x33E:
    cmp r0, #8
    .size FULL_COPY_CheckEvolveSpecies_0x33E, . - FULL_COPY_CheckEvolveSpecies_0x33E

FULL_COPY_CheckEvolveSpecies_0x36E:
    cmp r0, #8
    .size FULL_COPY_CheckEvolveSpecies_0x36E, . - FULL_COPY_CheckEvolveSpecies_0x36E

FULL_COPY_CheckEvolveSpecies_0x3EC:
    cmp r0, #8
    .size FULL_COPY_CheckEvolveSpecies_0x3EC, . - FULL_COPY_CheckEvolveSpecies_0x3EC
    
FULL_COPY_CheckEvolveSpecies_0x44C:
    cmp r0, #8
    .size FULL_COPY_CheckEvolveSpecies_0x44C, . - FULL_COPY_CheckEvolveSpecies_0x44C
