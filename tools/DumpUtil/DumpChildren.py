from struct import unpack
from pathlib import Path
'''
struct ChildPkmn {
    uint16_t Move;
    uint16_t Level;
};
'''

Count = -1
PersonalExt = Path('build/IRDO/narcs/a/0/2/0')

for Entry in sorted(PersonalExt.glob('*')):
    with open(f'children/{Entry.stem[2:]}.inc', 'w') as Personal:
        Personal.write(f'Species{(Count := Count + 1)}_Children:\n') # Header
        # Write EntryData
        with Entry.open('rb') as PersonalRAW:
            Child = unpack("<H", PersonalRAW.read(2))
            Personal.write(f'\Child {Child}\n')
            PersonalRAW.close()
        Personal.close()
