from pathlib import Path
from argparse import ArgumentParser
import yaml
import collections.abc
import struct

def flatten(iterable):
    flat = {}
    for e in iterable:
        flat |= e
    return flat

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
        
        structure, includes = flatten(Configuration['STRUCTURE']), Configuration['INCLUDE'] 
        defines = {}
        for include in includes:
            with Path(f'tools/mkdata/{include}').open('r') as INCLUDE_RAW:
                INCLUDE = yaml.safe_load(INCLUDE_RAW)
                defines |= flatten(INCLUDE['DEFINE'])
                
        format_string = ''
        def add_field(size):
            nonlocal format_string
            # print(size)
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
            
        for field, size in structure.items():
            if isinstance(size, collections.abc.Sequence) and type(size) != str:
                # Unroll
                [add_field(e) for e in size]
            else:
                add_field(size)

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

        OUT_DATA_BUFFER = []
        IN_DATA_FLAT = flatten(IN_DATA_RAW[IN_DATA_RAW_KEYS[0]])
        for key, value in IN_DATA_FLAT.items():
            if isinstance(value, collections.abc.Sequence) and type(value) != str:
                [OUT_DATA_BUFFER.append(resolve(e)) for e in value]
            else:
                OUT_DATA_BUFFER.append(resolve(value))
        print(OUT_DATA_BUFFER)
        print(format_string)
        print(struct.calcsize(format_string))
        OUT_DATA.write(struct.pack('<' + format_string, *OUT_DATA_BUFFER))
        
if __name__ == '__main__':
    exit(main())