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

def flatten_yaml_tree(items):
    data = []
    if len(items) == 0:
        return data
    for item in items:
        flatten_yaml_tree_helper(item, data)
    return data

def flatten_yaml_tree_helper(item, data):
    # Check if we are working with a scalar type (string/number in this case).
    seq_type = type(item)
    if seq_type == list:
        # Call unroll sequence again on "item".
        data += flatten_yaml_tree(item)
    elif seq_type == dict:
        # Treat as a sequence. 
        data += flatten_yaml_tree(list(item.values()))
    else:
        data.append(item)

def main():
    Parser = ArgumentParser()
    Parser.add_argument('input', metavar='i', type=str)
    Parser.add_argument('type', metavar='t', type=str)
    Parser.add_argument('output', metavar='o', type=str)
    Arguments = Parser.parse_args()

    # Structure file; check if it exists.
    StructConfig = Path(f'tools/mkdata/defs/{Arguments.type}.yml')
    Input, Output = Path(Arguments.input), Path(Arguments.output)
    if not StructConfig.exists():
        print(f'Structure configuration "{Arguments.type}.yml" does not exist. Exiting.')
        return 1
    
    # Read structure configuration.
    with StructConfig.open('r') as STRUCT_DEF:
        Configuration = yaml.safe_load(STRUCT_DEF)
        if not 0 < len(Configuration.keys()) <= 2:
            print(f'Invalid number of keys in "{Arguments.type}.yml"!')
            return 1
        
        structure = flatten_dict(Configuration['STRUCTURE'])
        
        defines = {}
        if 'INCLUDE' in Configuration.keys():
            for include in Configuration['INCLUDE']:
                with Path(f'tools/mkdata/{include}').open('r') as INCLUDE_RAW:
                    INCLUDE = yaml.safe_load(INCLUDE_RAW)
                    defines |= flatten_dict(INCLUDE['DEFINE'])

        format_string = ''
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
        
        [add_field(e) for e in flatten_yaml_tree(structure.values())]

    with Input.open('r') as IN_DATA, Output.open('wb') as OUT_DATA:
        IN_DATA_RAW = yaml.safe_load(IN_DATA)
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

        
        IN_DATA_FLAT = flatten_yaml_tree(flatten_dict(IN_DATA_RAW[IN_DATA_RAW_KEYS[0]]).values())
        OUT_DATA_BUFFER = [resolve(item) for item in IN_DATA_FLAT]

        while len(format_string) != len(OUT_DATA_BUFFER):
            format_string = format_string[:-1]

        OUT_DATA.write(struct.pack('<' + format_string, *OUT_DATA_BUFFER))

        
if __name__ == '__main__':
    exit(main())