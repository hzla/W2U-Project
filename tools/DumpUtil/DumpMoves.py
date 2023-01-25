from struct import unpack
from pathlib import Path
'''
struct __attribute__((packed)) __attribute__((aligned(2))) MoveData
{
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
};

'''

Count = -1
PersonalExt = Path('build/IRDO/narcs/a/0/2/1')

for Entry in sorted(PersonalExt.glob('*')):
    with open(f'moves/{Entry.stem[2:]}.inc', 'w') as Personal:
        Personal.write(f'.align 4\n\n') # Header
        Personal.write(f'Item{(Count := Count + 1)}:\n') # Header
        # Write EntryData
        with Entry.open('rb') as PersonalRAW:
            Personal.write(f'\tType {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tQuality {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tCategory {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tPower {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tAccuracy {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tBasePP {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tPriority {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tHitMinMax {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tInflictStatus {unpack("<H", PersonalRAW.read(2))[0]}\n')
            Personal.write(f'\tInflictChance {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tInflictDuration {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tTurnMin {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tTurnMax {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tCritStage {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tFlinchRate {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tMoveAnimationID {unpack("<H", PersonalRAW.read(2))[0]}\n')
            Personal.write(f'\tRecoil {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tTarget {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tStatChangeStats {unpack("B", PersonalRAW.read(1))[0]}, {unpack("B", PersonalRAW.read(1))[0]}, {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tStatChangeStages {unpack("B", PersonalRAW.read(1))[0]}, {unpack("B", PersonalRAW.read(1))[0]}, {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tStatChangeChances {unpack("B", PersonalRAW.read(1))[0]}, {unpack("B", PersonalRAW.read(1))[0]}, {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tFlags {hex(unpack(">L", PersonalRAW.read(4))[0])}\n')
            PersonalRAW.close()
            Personal.close()
