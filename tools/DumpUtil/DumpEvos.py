from struct import unpack
from pathlib import Path

PersonalExt = Path('build/IRDO/narcs/a/0/1/9')

MoveNames = []
SpeciesNames = []

with open('txtdmp/Moves.txt') as Moves:
    while (CurrMove := Moves.readline()) != '':
        MoveNames.append(CurrMove.upper().replace('É', 'E').replace('.', '').replace('-', '').replace(' ', '_').replace('\'', '')[:-1])

with open('txtdmp/Species.txt') as Species:
    while (CurrSpecies := Species.readline()) != '':
        SpeciesNames.append(CurrSpecies.upper().replace('É', 'E').replace('.', '').replace('-', '').replace(' ', '_').replace('\'', '')[:-1])

with open('assets/Evolutions.h', 'w') as Personal:
  Personal.write(f'#ifndef __EVOLUTIONS_H\n#define __EVOLUTIONS_H\n\n')
  Personal.write(f'#include "swan/swantypes.h"\n')
  Personal.write('''
typedef struct {
    uint16_t Method;
    uint16_t Parameter;
    uint16_t TargetSpecies;
} EvoEntry;

typedef struct {
    EvoEntry Entries[0x7];
} EVOLUTION_DATA;
\n''')
  Index = 0
  for Entry in sorted(PersonalExt.glob('*')):
      Personal.write(f'#define EVOLUTIONS_{SpeciesNames[Index] if Index < len(SpeciesNames) else str(Index)} {Index}\n')
      Index += 1
  Personal.write(f'\n#endif\n')

Count = 0
with open('assets/Evolutions.cpp', 'w') as Personal:
    Personal.write(f'#include "Evolutions.h"\n\nu32 __size = sizeof(EVOLUTION_DATA);\n\nconst EVOLUTION_DATA __data[] = {{\n')
    for Entry in sorted(PersonalExt.glob('*')):
        Personal.write(f'\t[EVOLUTIONS_{SpeciesNames[Count] if Count < len(SpeciesNames) else str(Index)}] = {{\n') # Header
        with Entry.open('rb') as PersonalRAW:
            for x in range(7):
                Personal.write(f'\t\t{{\n')
                Method, Param, Target = unpack("<HHH", PersonalRAW.read(6))
                Personal.write(f'\t\t\t.Method = {Method},\n')
                Personal.write(f'\t\t\t.Parameter = {Param},\n')
                Personal.write(f'\t\t\t.TargetSpecies = {"SPECIES_" + SpeciesNames[Target] if Target < len(SpeciesNames) else str(Index)},\n')
                Personal.write(f'\t\t}},\n')
            PersonalRAW.close()
        Personal.write(f'\t}},\n')
        Count += 1
    Personal.write(f'}};\n')
    Personal.close()
# for Entry in sorted(PersonalExt.glob('*')):
#     with open(f'evolutions/{Entry.stem[2:]}.inc', 'w') as Personal:
#         Personal.write(f'Species{(Count := Count + 1)}_EvoConfig:\n') # Header
#         # Write EntryData
#         with Entry.open('rb') as PersonalRAW:
#             while (PersonalRAW.tell() < 0x2A):
#                 Method, Param, Target = unpack("<HHH", PersonalRAW.read(6))
#                 Personal.write(f'\tEvoEntry {Method}, {Param}, {Target}\n')
#             PersonalRAW.close()
#         Personal.close()
