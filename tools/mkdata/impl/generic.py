from pathlib import Path
from .serializer import Serializer
from mkdata_util import *
import struct

class GenericSerializer(Serializer):
    def __init__(self):
        super().__init__()
        
    def Serialize(self, Arguments : dict) -> None:
        # Structure file; check if it exists.
        ScriptPath = Path(__file__).resolve().parent.parent
        StructConfig = resolve_metadata_path(ScriptPath / Path(f'defs/{Arguments.ex_parameters["format"]}.toml'))
        Input, Output = Path(Arguments.input), Path(Arguments.output)
        Output.parent.mkdir(exist_ok=True, parents=True)
        if not StructConfig.exists():
            print(f'Structure configuration "{StructConfig}" does not exist. Exiting.')
            return 1
        
        # Read structure configuration.
        Configuration = load_metadata(StructConfig)
        if not 0 < len(Configuration.keys()) <= 2:
            print(f'Invalid number of keys in "{StructConfig}"!')
            return 1
        
        structure = flatten(Configuration['STRUCTURE'])
        
        defines = {}
        if 'INCLUDE' in Configuration.keys():
            for include in Configuration['INCLUDE']:
                load_defines((ScriptPath / include).as_posix(), defines)

        format_string = ''
        tree = structure.values()
        tree_flat = flatten_yaml_tree(tree)

        def add_field(size):
            nonlocal format_string
            match size:
                case 's8':
                    format_string += 'b'
                case 'u8':
                    format_string += 'B'
                case 's16':
                    format_string += 'h'
                case 'u16':
                    format_string += 'H'
                case 's32':
                    format_string += 'i'
                case 'u32':
                    format_string += 'I'
                case _:
                    format_string += 'X'

        for e in tree_flat:
            add_field(e)

        with Output.open('wb') as OUT_DATA:
            IN_DATA_RAW = load_source_data(Input)
            IN_DATA_RAW_KEYS = list(IN_DATA_RAW.keys())

            if not 0 < len(IN_DATA_RAW_KEYS) <= 1:
                print(f'Invalid number of keys in "{Arguments.input}"!')
                return 1

            def resolve(value):
                if type(value) == int:
                    return value
                if type(value) == str:
                    final_value = 0
                    tokens = [e.strip() for e in value.split('|')]
                    for token in tokens:
                        if token.isdigit():
                            final_value |= int(token)
                            continue
                        if token in defines.keys():
                            final_value |= defines[token]
                        else:
                            print(f'Label "{token}" not defined!')
                    return final_value
                return -1

            def flatten_field_names(items):
                names = []
                for item in items:
                    if isinstance(item, dict):
                        for name, child in item.items():
                            if isinstance(child, list):
                                for child_item in child:
                                    if isinstance(child_item, dict):
                                        names += flatten_field_names([child_item])
                                    else:
                                        names.append(name)
                            else:
                                names.append(name)
                    elif isinstance(item, list):
                        names += flatten_field_names(item)
                return names

            def resolve_hit(value):
                def pack_hit_count(hit_min, hit_max):
                    return (hit_max << 4) | hit_min

                if type(value) == int:
                    if 0 <= value <= 0xF:
                        return pack_hit_count(value, value)
                    return value
                if type(value) == str:
                    tokens = [e.strip() for e in value.split('|')]
                    if len(tokens) == 2 and all(token.isdigit() for token in tokens):
                        hit_min, hit_max = [int(token) for token in tokens]
                        if 0 <= hit_min <= 0xF and 0 <= hit_max <= 0xF:
                            return pack_hit_count(hit_min, hit_max)
                    if value.isdigit():
                        hit_count = int(value)
                        if 0 <= hit_count <= 0xF:
                            return pack_hit_count(hit_count, hit_count)
                        return hit_count
                    print(f'Invalid Hit field "{value}"; expected MIN | MAX.')
                return -1

            
            IN_DATA_FLAT = flatten_yaml_tree(flatten(IN_DATA_RAW[IN_DATA_RAW_KEYS[0]]).values())
            field_names = flatten_field_names(Configuration['STRUCTURE'])
            OUT_DATA_BUFFER = [
                resolve_hit(item) if index < len(field_names) and field_names[index] == 'Hit' else resolve(item)
                for index, item in enumerate(IN_DATA_FLAT)
            ]
            if Arguments.ex_parameters["format"] == 'personal':
                # Abilities above 255: the ability byte keeps the low 8 bits and EV Yield bit 13 + slot holds bit 8
                # (EV Yield uses bits 0-12). Decoded by THUMB_BRANCH_PML_PersonalGetParam (w2u_ability_storage.cpp).
                personal_fields = list(structure.keys())   # flat layout: one value per field up to the tutors
                ev_yield = personal_fields.index('EV Yield')
                for slot, name in enumerate(('Primary Ability', 'Secondary Ability', 'Hidden Ability')):
                    index = personal_fields.index(name)
                    value = OUT_DATA_BUFFER[index]
                    if value > 511:
                        print(f'{Arguments.input}: {name} {value} is above 511, the personal data limit.')
                        return 1
                    if value > 255:
                        OUT_DATA_BUFFER[index] = value & 0xFF
                        OUT_DATA_BUFFER[ev_yield] |= 1 << (13 + slot)
            while len(format_string) != len(OUT_DATA_BUFFER):
                format_string = format_string[:-1]

            OUT_DATA.write(struct.pack('<' + format_string, *OUT_DATA_BUFFER))
