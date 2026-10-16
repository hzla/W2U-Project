// The handler tables of the C mechanics (src/mechanics, written against include/w2u/battle_api.h), declared for the
// C++ side: the battle module registry's generated entries (w2u_battle_module_api_entries.inc) count them. The
// mechanics define them as const BattleEventHandlerEntry[] (the same layout as BattleEventHandlerTableEntry).
#pragma once
#include "w2u_abilities.h"

extern "C" BattleEventHandlerTableEntry FluffyHandlers[1];   // abilities/fluffy.c: Fluffy, Ice Scales, Aura Guard
extern "C" BattleEventHandlerTableEntry PowerSpotHandlers[1];  // abilities/power_spot.c: Power Spot, Steely Spirit
extern "C" BattleEventHandlerTableEntry BatteryHandlers[1];    // abilities/power_spot.c
extern "C" BattleEventHandlerTableEntry PunkRockHandlers[2];   // abilities/punk_rock.c
extern "C" BattleEventHandlerTableEntry EarthEaterHandlers[1];    // abilities/absorb.c
extern "C" BattleEventHandlerTableEntry WellBakedBodyHandlers[1]; // abilities/absorb.c
extern "C" BattleEventHandlerTableEntry MindsEyeHandlers[4];      // abilities/minds_eye.c
extern "C" BattleEventHandlerTableEntry PropellerTailHandlers[1]; // abilities/propeller_tail.c: Propeller Tail, Stalwart
extern "C" BattleEventHandlerTableEntry GoodAsGoldHandlers[1];
extern "C" BattleEventHandlerTableEntry NeuroforceHandlers[1];
extern "C" BattleEventHandlerTableEntry StaminaHandlers[1];
extern "C" BattleEventHandlerTableEntry WaterCompactionHandlers[1];
extern "C" BattleEventHandlerTableEntry SteamEngineHandlers[1];
extern "C" BattleEventHandlerTableEntry ThermalExchangeHandlers[6];
extern "C" BattleEventHandlerTableEntry EelevateHandlers[4];
extern "C" BattleEventHandlerTableEntry DampHandlers[5];
extern "C" BattleEventHandlerTableEntry SpicySprayHandlers[1];
extern "C" BattleEventHandlerTableEntry ToxicChainHandlers[1];
extern "C" BattleEventHandlerTableEntry ScreenCleanerHandlers[2];
extern "C" BattleEventHandlerTableEntry WindRiderHandlers[5];
extern "C" BattleEventHandlerTableEntry RuinHandlers[4];
extern "C" BattleEventHandlerTableEntry NeighHandlers[4];
extern "C" BattleEventHandlerTableEntry HospitalityHandlers[2];
extern "C" BattleEventHandlerTableEntry GorillaTacticsHandlers[4];
extern "C" BattleEventHandlerTableEntry MirrorArmorHandlers[4];
extern "C" BattleEventHandlerTableEntry PurifyingSaltHandlers[7];
extern "C" BattleEventHandlerTableEntry BoostHandlers[2];
extern "C" BattleEventHandlerTableEntry ChargeHandlers[5];
extern "C" BattleEventHandlerTableEntry UnseenFistHandlers[3];
extern "C" BattleEventHandlerTableEntry LingeringAromaHandlers[1];
extern "C" BattleEventHandlerTableEntry CottonDownHandlers[1];
extern "C" BattleEventHandlerTableEntry PerishBodyHandlers[1];
extern "C" BattleEventHandlerTableEntry ToxicDebrisHandlers[1];
extern "C" BattleEventHandlerTableEntry PoisonPuppeteerHandlers[1];
extern "C" BattleEventHandlerTableEntry PastelVeilHandlers[4];
extern "C" BattleEventHandlerTableEntry TeraShellHandlers[2];
extern "C" BattleEventHandlerTableEntry GuardDogHandlers[2];
extern "C" BattleEventHandlerTableEntry IntimidateTrackedHandlers[2];
extern "C" BattleEventHandlerTableEntry IntrepidSwordHandlers[1];
extern "C" BattleEventHandlerTableEntry QuickDrawHandlers[2];
extern "C" BattleEventHandlerTableEntry MyceliumMightHandlers[4];
extern "C" BattleEventHandlerTableEntry MegaSolHandlers[2];
extern "C" BattleEventHandlerTableEntry ProtosynthesisHandlers[11];
extern "C" BattleEventHandlerTableEntry SandSpitHandlers[1];
extern "C" BattleEventHandlerTableEntry PulseHandlers[3];
extern "C" BattleEventHandlerTableEntry MimicryHandlers[5];
extern "C" BattleEventHandlerTableEntry GrassPeltHandlers[1];
extern "C" BattleEventHandlerTableEntry RipenHandlers[1];
extern "C" BattleEventHandlerTableEntry OpportunistHandlers[5];
extern "C" BattleEventHandlerTableEntry CudChewHandlers[1];
extern "C" BattleEventHandlerTableEntry CuriousMedicineHandlers[2];
extern "C" BattleEventHandlerTableEntry CostarHandlers[2];
extern "C" BattleEventHandlerTableEntry SupersweetSyrupHandlers[2];
extern "C" BattleEventHandlerTableEntry SupremeOverlordHandlers[3];
extern "C" BattleEventHandlerTableEntry IceFaceHandlers[4];
extern "C" BattleEventHandlerTableEntry GulpMissileHandlers[5];
extern "C" BattleEventHandlerTableEntry HungerSwitchHandlers[1];
extern "C" BattleEventHandlerTableEntry ZeroToHeroHandlers[1];
extern "C" BattleEventHandlerTableEntry CommanderHandlers[8];
extern "C" BattleEventHandlerTableEntry ProteanHandlers[2];
extern "C" BattleEventHandlerTableEntry BerserkHandlers[2];
extern "C" BattleEventHandlerTableEntry QueenlyMajestyHandlers[2];
