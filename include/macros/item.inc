@ struct ItemData
@ {
@   u16 Price;
@   u8 HeldEffect;
@   u8 HeldArgument;
@   u8 NaturalGiftEffect;
@   u8 FlingEffect;
@   u8 FlingPower;
@   u8 NaturalGiftPower;
@   u16 Packed;
@   u8 EffectField;
@   u8 EffectBattle;
@   u8 HasBattleStats;
@   u8 ItemClass;
@   u8 Consumable;
@   u8 SortIndex;
@   ItemBattleStats BattleStats;
@ };
@ 
@ struct ItemBattleStats
@ {
@   u8 CureInflict;
@   u8 Boost[4];
@   u8 FunctionFlags0;
@   u8 FunctionFlags1;
@   char EVHP;
@   char EVATK;
@   char EVDEF;
@   char EVSPE;
@   char EVSPA;
@   char EVSPD;
@   u8 HealAmount;
@   u8 PPGain;
@   char Friendship1;
@   char Friendship2;
@   char Friendship3;
@   char field_1F;
@   char field_20;
@ };

.macro Price 