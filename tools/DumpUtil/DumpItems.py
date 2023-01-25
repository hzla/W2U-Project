from struct import unpack
from pathlib import Path
'''
struct ItemData
{
  u16 Price;
  u8 HeldEffect;
  u8 HeldArgument;
  u8 NaturalGiftEffect;
  u8 FlingEffect;
  u8 FlingPower;
  u8 NaturalGiftPower;
  u16 Packed;
  u8 EffectField;
  u8 EffectBattle;
  u8 HasBattleStats;
  u8 ItemClass;
  u8 Consumable;
  u8 SortIndex;
  ItemBattleStats BattleStats;
};

struct ItemBattleStats
{
  u8 CureInflict;
  u8 Boost[4];
  u8 FunctionFlags0;
  u8 FunctionFlags1;
  char EVHP;
  char EVATK;
  char EVDEF;
  char EVSPE;
  char EVSPA;
  char EVSPD;
  u8 HealAmount;
  u8 PPGain;
  char Friendship1;
  char Friendship2;
  char Friendship3;
  char field_1F;
  char field_20;
};

'''

Count = -1
PersonalExt = Path('build/IRDO/narcs/a/0/2/1')

for Entry in sorted(PersonalExt.glob('*')):
    with open(f'items/{Entry.stem[2:]}.inc', 'w') as Personal:
        Personal.write(f'.align 4\n\n') # Header
        Personal.write(f'Item{(Count := Count + 1)}:\n') # Header
        # Write EntryData
        with Entry.open('rb') as PersonalRAW:
            Personal.write(f'\tPrice {unpack("<H", PersonalRAW.read(2))[0]}\n')
            Personal.write(f'\tHeldEffect {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tHeldArgument {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tNaturalGiftEffect {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tFlingEffect {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tFlingPower {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tNaturalGiftPower {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tPacked {unpack("<H", PersonalRAW.read(2))[0]}\n')
            Personal.write(f'\tFieldEffect {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tBattleEffect {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tHasBattleStats {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tItemClass {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tConsumable {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tSortIndex {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'Item{Count}_BattleStats:\n')
            Personal.write(f'\tCureInflict {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tBoost {unpack("B", PersonalRAW.read(1))[0]}, {unpack("B", PersonalRAW.read(1))[0]}, {unpack("B", PersonalRAW.read(1))[0]}, {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tFunctionFlags0 {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tFunctionFlags1 {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tEVHP {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tEVATK {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tEVDEF {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tEVSPE {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tEVSPA {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tEVSPD {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tHealAmount {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tPPGain {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tFriendship1 {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tFriendship2 {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tFriendship3 {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tUnk1F {unpack("B", PersonalRAW.read(1))[0]}\n')
            Personal.write(f'\tUnk20 {unpack("B", PersonalRAW.read(1))[0]}\n')
            PersonalRAW.close()
            Personal.close()
