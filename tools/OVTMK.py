from argparse import ArgumentParser
from struct import pack
import yaml
from yaml.loader import SafeLoader


def main():
    Parser = ArgumentParser()
    Parser.add_argument('input', metavar='i', type=str)
    Parser.add_argument('output', metavar='o', type=str)
    Arguments = Parser.parse_args()

    OVT_DATA = None
    with open(Arguments.input, 'r') as OVT_TXT:
        OVT_DATA = yaml.load(OVT_TXT, Loader=SafeLoader)

    with open(Arguments.output, 'wb') as OVT:
        for OVL in OVT_DATA:
            ENTRY_DATA = OVT_DATA[OVL]
            OVT.write(pack('<I', OVL))
            OVT.write(pack('<I', ENTRY_DATA['MountAddress']))
            OVT.write(pack('<I', ENTRY_DATA['MountSize']))
            OVT.write(pack('<I', ENTRY_DATA['BSSSize']))
            OVT.write(pack('<I', ENTRY_DATA['StaticInitializerAddress']))
            OVT.write(pack('<I', ENTRY_DATA['StaticInitializerEndAddress']))
            OVT.write(pack('<I', ENTRY_DATA['FileID']))
            # It's all decmped anyway.
            OVT.write(pack('<I', ENTRY_DATA['MountSize']))
    return


if __name__ == '__main__':
    main()