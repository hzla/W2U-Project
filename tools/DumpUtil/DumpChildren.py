from struct import unpack
from pathlib import Path
'''
typedef struct {
    u16 ID;
} CHILD_DATA;
'''

PersonalExt = Path('build/IRDO/narcs/a/0/2/0')

SpeciesNames = []

with open('txtdmp/Species.txt') as Species:
    while (CurrSpecies := Species.readline()) != '':
        SpeciesNames.append(CurrSpecies.upper().replace('\X2019', '').replace('É', 'E').replace('.', '').replace('-', '').replace(' ', '_').replace('\'', '')[:-1])

with open('assets/Children.h', 'w') as Personal:
  Personal.write(f'#ifndef __CHILD_H\n#define __CHILD_H\n\n')
  Personal.write(f'#include "swan/swantypes.h"\n')
  Personal.write('''
typedef struct {
    u16 ID;
} CHILD_DATA;
\n''')
  for x in range(len(SpeciesNames)):
    Personal.write(f'#define CHILDREN_{SpeciesNames[x]} {x}\n')
  Personal.write(f'\n#endif\n')

Count = 0
with open(f'assets/Children.cpp', 'w') as Personal:
  Personal.write(f'#include "Children.h"\n\nu32 __size = sizeof(CHILD_DATA);\n\nconst CHILD_DATA __data[] = {{\n')
  for Entry in sorted(PersonalExt.glob('*')):
    Personal.write(f'\t[CHILDREN_{SpeciesNames[Count]}] = {{\n') # Header
    # Write EntryData
    with Entry.open('rb') as PersonalRAW:
        Personal.write(f'\t\t.ID = {unpack("<H", PersonalRAW.read(2))[0]},\n')
        PersonalRAW.close()
    Personal.write(f'\t}},\n')
    Count += 1
  Personal.write(f'}};\n')
  Personal.close()
