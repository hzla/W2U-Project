from struct import unpack
from pathlib import Path
'''
struct EvoEntry {
    uint16_t Method;
    uint16_t Parameter;
    uint16_t TargetSpecies;
};
'''

Count = -1
PersonalExt = Path('build/IRDO/narcs/a/0/1/9')

for Entry in sorted(PersonalExt.glob('*')):
    with open(f'evolutions/{Entry.stem[2:]}.inc', 'w') as Personal:
        Personal.write(f'Species{(Count := Count + 1)}_EvoConfig:\n') # Header
        # Write EntryData
        with Entry.open('rb') as PersonalRAW:
            while (PersonalRAW.tell() < 0x2A):
                Method, Param, Target = unpack("<HHH", PersonalRAW.read(6))
                Personal.write(f'\tEvoEntry {Method}, {Param}, {Target}\n')
            PersonalRAW.close()
        Personal.close()
