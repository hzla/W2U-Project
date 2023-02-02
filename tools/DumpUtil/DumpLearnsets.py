from struct import unpack
from pathlib import Path

PersonalExt = Path('build/IRDO/narcs/a/0/1/8')

MoveNames = []
SpeciesNames = []

with open('txtdmp/Moves.txt') as Moves:
    while (CurrMove := Moves.readline()) != '':
        MoveNames.append(CurrMove.upper().replace('É', 'E').replace('.', '').replace('-', '').replace(' ', '_').replace('\'', '')[:-1])

with open('txtdmp/Species.txt') as Species:
    while (CurrSpecies := Species.readline()) != '':
        SpeciesNames.append(CurrSpecies.upper().replace('É', 'E').replace('.', '').replace('-', '').replace(' ', '_').replace('\'', '')[:-1])

with open('assets/Learnsets.h', 'w') as Personal:
  Personal.write(f'#ifndef __LEARNSET_H\n#define __LEARNSET_H\n\n')
  Personal.write(f'#include "swan/swantypes.h"\n')
  Personal.write('''
struct LearnsetEntry {
    uint16_t Move;
    uint16_t Level;
};
typedef struct {
    LearnsetEntry Entries[];
} LEARNSET_DATA;
\n''')
  Index = 0
  for Entry in sorted(PersonalExt.glob('*')):
      Personal.write(f'#define LEARNSET_{SpeciesNames[Index] if Index < len(SpeciesNames) else str(Index)} {Index}\n')
      Index += 1
  Personal.write(f'\n#endif\n')

with open('assets/Learnsets.cpp', 'w') as Personal:
  Personal.write(f'#include "Learnsets.h"\n\nu32 __size = sizeof(LEARNSET_DATA);\n\nconst LEARNSET_DATA __data[] = {{\n')
  Index = 0
  for Entry in sorted(PersonalExt.glob('*')):
    Personal.write(f'\t[LEARNSET_{SpeciesNames[Index] if Index < len(SpeciesNames) else str(Index)}] = {{\n') # Header
    with Entry.open('rb') as PersonalRAW:
        while True:
            Personal.write(f'\t\t{{\n')
            Mv, Lvl = unpack("<HH", PersonalRAW.read(4))
            Personal.write(f'\t\t\t.Move = {"MOVE_" + MoveNames[Mv] if Mv != 0xFFFF else "ENTRIES_END"},\n\t\t\t.Level = {Lvl if Lvl != 0xFFFF else "ENTRIES_END"},\n')
            Personal.write(f'\t\t}},`\n')
            if Lvl == 0xFFFF and Mv == 0xFFFF:
                break
        PersonalRAW.close()
    Personal.write(f'\t}},\n')
    PersonalRAW.close()
    Index += 1
  Personal.write(f'}};')
  Personal.close()
