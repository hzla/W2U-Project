from pathlib import Path
from argparse import ArgumentParser
import yaml
import collections.abc
import struct

def flatten_dict(iterable):
    flat = {}
    for e in iterable:
        flat |= e
    return flat

def main():
    Parser = ArgumentParser()
    Parser.add_argument('input', metavar='i', type=str)
    Parser.add_argument('output', metavar='o', type=str)
    Arguments = Parser.parse_args()
    Input, Output = Path(Arguments.input), Path(Arguments.output)
    print(Input.as_posix())
    if not Input.exists():
        print(f'"{Arguments.input}" does not exist. Exiting.')
        return 1
    
    defines = {}
    with Path(f'tools/mkdata/enum/species.yml').open('r') as INCLUDE_RAW:
        INCLUDE = yaml.safe_load(INCLUDE_RAW)
        defines |= flatten_dict(INCLUDE['DEFINE'])

    with Input.open('r') as DATA:
        Encounters = yaml.safe_load(DATA)
        with Output.open('wb') as DATA_SERIALIZED:
            for Key in Encounters.keys():
                DATA_SERIALIZED.write(struct.pack('B', Encounters[Key]['GRASS_SINGLES']))
                DATA_SERIALIZED.write(struct.pack('B', Encounters[Key]['GRASS_DOUBLES']))
                DATA_SERIALIZED.write(struct.pack('B', Encounters[Key]['GRASS_RARE']))
                DATA_SERIALIZED.write(struct.pack('B', Encounters[Key]['SURF_SINGLES']))
                DATA_SERIALIZED.write(struct.pack('B', Encounters[Key]['SURF_RARE']))
                DATA_SERIALIZED.write(struct.pack('B', Encounters[Key]['FISH_SINGLES']))
                DATA_SERIALIZED.write(struct.pack('B', Encounters[Key]['FISH_RARE']))
                DATA_SERIALIZED.write(struct.pack('B', Encounters[Key]['UNKNOWN']))
                for Category in ['GRASS', 'SURF', 'FISH']:
                    for EncType in ['SINGLES', 'DOUBLES', 'SPECIAL']:
                        if EncType not in Encounters[Key][Category]:
                            continue
                        for Slot in Encounters[Key][Category][EncType]:
                            species = 0
                            if type(Encounters[Key][Category][EncType][Slot]['Species']) == str:
                                if Encounters[Key][Category][EncType][Slot]['Species'] in defines.keys():
                                    species = defines[Encounters[Key][Category][EncType][Slot]['Species']]
                                else:
                                    print(f'Unknown species "{Encounters[Key][Category][EncType][Slot]["Species"]}')
                                    return 1
                            else:
                                species = Encounters[Key][Category][EncType][Slot]['Form']
                            form = Encounters[Key][Category][EncType][Slot]['Form']
                            DATA_SERIALIZED.write(struct.pack('<H', (form << 0xB) | species))
                            DATA_SERIALIZED.write(struct.pack('B', Encounters[Key][Category][EncType][Slot]['Minimum Level']))
                            DATA_SERIALIZED.write(struct.pack('B', Encounters[Key][Category][EncType][Slot]['Maximum Level']))
    
        
if __name__ == '__main__':
    exit(main())