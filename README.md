# Pokémon White 2 Upgrade

## Setup
You will need the following tools to use this repository:
- [armips](https://github.com/Kingcom/armips/releases)
- [arm-none-eabi-{as, gcc, ld}](https://developer.arm.com/downloads/-/gnu-rm)
- [CTRMap (Community Edition)](https://github.com/kingdom-of-ds-hacking/CTRMap-CE/releases)
- gcc
- GNU Make (anything over 3.81)
- Java 1.8
- [ndstool (2.2.0)](https://github.com/devkitPro/ndstool)
- A Linux environment (native or Windows Subsystem for Linux)

## Installation
1) Clone this repository using `git clone --recursive git@github.com:PlatinumMaster/White2Upgrade.git`, then `cd White2Upgrade`.
2) Put `CTRMap.jar` in `tools/CTRMap`.
3) Grab a fresh American Pokémon White 2 ROM (tested on `3e50aec3db401332175a5d2b5fe2a68ac1a05ec63995dba9d1506b1b51837446`), name it `IRDO.nds`, and place it in the root directory of the repository (i.e in the same folder as `Makefile`).
4) Run `make`. If all goes well, you shall see `expansion.nds`.

## Contributing
TODO

## Credits
TODO