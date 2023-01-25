from struct import unpack
from pathlib import Path
'''
struct SpeciesLearnset {
    LearnsetEntry[] Entries;
};
struct LearnsetEntry {
    uint16_t Move;
    uint16_t Level;
};
'''

Count = -1
PersonalExt = Path('build/IRDO/narcs/a/0/1/8')

for Entry in sorted(PersonalExt.glob('*')):
    with open(f'learnsets/{Entry.stem[2:]}.inc', 'w') as Personal:
        Personal.write(f'Species{(Count := Count + 1)}_Learnset:\n') # Header
        # Write EntryData
        with Entry.open('rb') as PersonalRAW:
            while (True):
                Mv, Lvl = unpack("<HH", PersonalRAW.read(4))
                Personal.write(f'\tLearnsetEntry {Mv}, {Lvl}\n')
                if Lvl == 0xFFFF and Mv == 0xFFFF:
                    break
            PersonalRAW.close()
        Personal.close()
