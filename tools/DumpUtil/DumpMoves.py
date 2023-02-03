from struct import unpack
from pathlib import Path
'''

'''

Count = 0
PersonalExt = Path('build/IRDO/narcs/a/0/2/1')

MoveNames = []

with open('txtdmp/Moves.txt') as Moves:
    while (CurrMove := Moves.readline()) != '':
        MoveNames.append(CurrMove.upper().replace('\X2019', '').replace('É', 'E').replace('.', '').replace('-', '').replace(' ', '_').replace('\'', '')[:-1])

with open('include/Moves.h', 'w') as Personal:
  Personal.write(f'#ifndef __MOVES_H\n#define __MOVES_H\n\n')
  Personal.write(f'#include "swan/swantypes.h"\n')
  Personal.write('''
typedef struct {
  u8 Type;
  u8 Quality;
  u8 Category;
  u8 Power;
  u8 Accuracy;
  u8 BasePP;
  char Priority;
  char HitMinMax;
  u16 InflictStatus;
  u8 InflictChance;
  u8 InflictDuration;
  u8 TurnMin;
  u8 TurnMax;
  u8 CritStage;
  u8 FlinchRate;
  u16 WazaSeqID;
  char Recoil;
  char Heal;
  u8 Target;
  char StatChangeStats[3];
  char StatChangeStages[3];
  char StatChangeChances[3];
  int Flags;
} MOVE_DATA;
\n''')
  for x in range(len(MoveNames)):
    Personal.write(f'#define MOVE_{MoveNames[x]} {x}\n')
  Personal.write(f'\n#endif\n')

with open(f'src/c/Moves.cpp', 'w') as Personal:
  Personal.write(f'#include "Moves.h"\n\nu32 __size = sizeof(MOVE_DATA);\n\nconst MOVE_DATA __data[] = {{\n')
  for Entry in sorted(PersonalExt.glob('*')):
    Personal.write(f'\t[MOVE_{MoveNames[Count]}] = {{\n') # Header
    # Write EntryData
    with Entry.open('rb') as PersonalRAW:
        Personal.write(f'\t\t.Type = {unpack("B", PersonalRAW.read(1))[0]},\n')
        Personal.write(f'\t\t.Quality = {unpack("B", PersonalRAW.read(1))[0]},\n')
        Personal.write(f'\t\t.Category = {unpack("B", PersonalRAW.read(1))[0]},\n')
        Personal.write(f'\t\t.Power = {unpack("B", PersonalRAW.read(1))[0]},\n')
        Personal.write(f'\t\t.Accuracy = {unpack("B", PersonalRAW.read(1))[0]},\n')
        Personal.write(f'\t\t.BasePP = {unpack("B", PersonalRAW.read(1))[0]},\n')
        Personal.write(f'\t\t.Priority = {unpack("B", PersonalRAW.read(1))[0]},\n')
        Personal.write(f'\t\t.HitMinMax = {unpack("B", PersonalRAW.read(1))[0]},\n')
        Personal.write(f'\t\t.InflictStatus = {unpack("<H", PersonalRAW.read(2))[0]},\n')
        Personal.write(f'\t\t.InflictChance = {unpack("B", PersonalRAW.read(1))[0]},\n')
        Personal.write(f'\t\t.InflictDuration = {unpack("B", PersonalRAW.read(1))[0]},\n')
        Personal.write(f'\t\t.TurnMin = {unpack("B", PersonalRAW.read(1))[0]},\n')
        Personal.write(f'\t\t.TurnMax = {unpack("B", PersonalRAW.read(1))[0]},\n')
        Personal.write(f'\t\t.CritStage = {unpack("B", PersonalRAW.read(1))[0]},\n')
        Personal.write(f'\t\t.FlinchRate = {unpack("B", PersonalRAW.read(1))[0]},\n')
        Personal.write(f'\t\t.WazaSeqID = {unpack("<H", PersonalRAW.read(2))[0]},\n')
        Personal.write(f'\t\t.Recoil = {unpack("B", PersonalRAW.read(1))[0]},\n')
        Personal.write(f'\t\t.Target = {unpack("B", PersonalRAW.read(1))[0]},\n')

        Personal.write(f'\t\t.StatChangeStats = {{\n')
        for x in range(3):
          Personal.write(f'\t\t\t{unpack("B", PersonalRAW.read(1))[0]},\n')
        Personal.write(f'\t\t}},\n')

        Personal.write(f'\t\t.StatChangeStages = {{\n')
        for x in range(3):
          Personal.write(f'\t\t\t{unpack("B", PersonalRAW.read(1))[0]},\n')
        Personal.write(f'\t\t}},\n')

        Personal.write(f'\t\t.StatChangeChances = {{\n')
        for x in range(3):
          Personal.write(f'\t\t\t{unpack("B", PersonalRAW.read(1))[0]},\n')
        Personal.write(f'\t\t}},\n')

        Personal.write(f'\t\t.Flags = {hex(unpack(">L", PersonalRAW.read(4))[0])},\n')
        PersonalRAW.close()
    Personal.write(f'\t}},\n')
    Count += 1
  Personal.write(f'}};\n')
  Personal.close()