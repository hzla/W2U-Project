from pathlib import Path
from argparse import ArgumentParser
import yaml
import collections.abc
import struct

defines = {}

def flatten_dict(iterable):
    flat = {}
    for e in iterable:
        flat |= e
    return flat

def resolve_label(item):
    global defines
    if type(item) == str:
        # Will err if it doesn't exist.
        return defines[item]
    return item

def load_defines(path):
    global defines
    with Path(path).open('r') as INCLUDE_RAW:
        INCLUDE = yaml.safe_load(INCLUDE_RAW)
        defines |= flatten_dict(INCLUDE['DEFINE'])

def main():
    Parser = ArgumentParser()
    Parser.add_argument('input', metavar='i', type=str)
    Parser.add_argument('tr_data_out', metavar='trd', type=str)
    Parser.add_argument('tr_poke_out', metavar='trp', type=str)
    Arguments = Parser.parse_args()
    Input, tr_data_out, tr_poke_out = Path(Arguments.input), Path(Arguments.tr_data_out), Path(Arguments.tr_poke_out)
    print(Input.as_posix())
    if not Input.exists():
        print(f'"{Arguments.input}" does not exist. Exiting.')
        return 1

    with Input.open('r') as DATA:
        TrainerConfiguration = yaml.safe_load(DATA)

        # Traverse data and resolve to integers
        UserSpecifiedMoves = any(['MOVES' in x for x in TrainerConfiguration['PARTY']])
        UserSpecifiedHeldItem = any(['HELD_ITEM' in x for x in TrainerConfiguration['PARTY']])
        [load_defines(x) for x in [
            'tools/mkdata/enum/species.yml',
            'tools/mkdata/enum/moves.yml',
            'tools/mkdata/enum/items.yml',
            'tools/mkdata/enum/btl_gender.yml',
            'tools/mkdata/enum/btl_abil.yml',
        ]]

        # Generate trpoke first.
        with tr_poke_out.open('wb') as TRPOKE:
            for member in TrainerConfiguration['PARTY']:
                TRPOKE.write(struct.pack('B', resolve_label(member['DIFFICULTY_VALUE'])))
                TRPOKE.write(struct.pack('B', resolve_label((member['ABILITY'] << 0x4) | member['GENDER'] & 0xF)))
                TRPOKE.write(struct.pack('<H', resolve_label(member['LEVEL'])))
                print(resolve_label(member['SPECIES']))
                TRPOKE.write(struct.pack('<H', resolve_label(member['SPECIES'])))
                TRPOKE.write(struct.pack('<H', resolve_label(member['FORM'])))
                if UserSpecifiedHeldItem:
                    TRPOKE.write(struct.pack('<H', resolve_label(member['HELD_ITEM'])))
                if UserSpecifiedMoves:
                    for move in member['MOVES']:
                        TRPOKE.write(struct.pack('B', resolve_label(move)))
        # Now trdata.
        with tr_data_out.open('wb') as TRDATA:
            # Determine format.
            TRPOKE_FORMAT = (1 << 1 if UserSpecifiedHeldItem else 0) | (1 if UserSpecifiedMoves else 0)
            TRDATA.write(struct.pack('B', TRPOKE_FORMAT))
            TRDATA.write(struct.pack('B', resolve_label(TrainerConfiguration['CLASS'])))
            TRDATA.write(struct.pack('B', resolve_label(TrainerConfiguration['BATTLE_TYPE'])))
            TRDATA.write(struct.pack('B', len(TrainerConfiguration['PARTY'])))
            for item in TrainerConfiguration['ITEMS']:
                TRDATA.write(struct.pack('<H', resolve_label(item)))
            TRDATA.write(struct.pack('<I', TrainerConfiguration['AI']))
            TRDATA.write(struct.pack('B', TrainerConfiguration['CAN_HEAL']))
            TRDATA.write(struct.pack('B', TrainerConfiguration['REWARD_MONEY']))
            TRDATA.write(struct.pack('<H', resolve_label(TrainerConfiguration['REWARD_ITEM'])))


        
if __name__ == '__main__':
    exit(main())