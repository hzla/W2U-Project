#include "Learnsets.h"

u32 __size = sizeof(LEARNSET_DATA);

const LEARNSET_DATA __data[] = {
	[LEARNSET_NONE] = {
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BULBASAUR] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 3,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 7,
		},
		{
			.Move = MOVE_VINE_WHIP,
			.Level = 9,
		},
		{
			.Move = MOVE_POISONPOWDER,
			.Level = 13,
		},
		{
			.Move = MOVE_SLEEP_POWDER,
			.Level = 13,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 15,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 19,
		},
		{
			.Move = MOVE_SWEET_SCENT,
			.Level = 21,
		},
		{
			.Move = MOVE_GROWTH,
			.Level = 25,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 27,
		},
		{
			.Move = MOVE_WORRY_SEED,
			.Level = 31,
		},
		{
			.Move = MOVE_SYNTHESIS,
			.Level = 33,
		},
		{
			.Move = MOVE_SEED_BOMB,
			.Level = 37,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_IVYSAUR] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 3,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 7,
		},
		{
			.Move = MOVE_VINE_WHIP,
			.Level = 9,
		},
		{
			.Move = MOVE_POISONPOWDER,
			.Level = 13,
		},
		{
			.Move = MOVE_SLEEP_POWDER,
			.Level = 13,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 15,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 20,
		},
		{
			.Move = MOVE_SWEET_SCENT,
			.Level = 23,
		},
		{
			.Move = MOVE_GROWTH,
			.Level = 28,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 31,
		},
		{
			.Move = MOVE_WORRY_SEED,
			.Level = 36,
		},
		{
			.Move = MOVE_SYNTHESIS,
			.Level = 39,
		},
		{
			.Move = MOVE_SOLARBEAM,
			.Level = 44,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_VENUSAUR] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 1,
		},
		{
			.Move = MOVE_VINE_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 3,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 7,
		},
		{
			.Move = MOVE_VINE_WHIP,
			.Level = 9,
		},
		{
			.Move = MOVE_POISONPOWDER,
			.Level = 13,
		},
		{
			.Move = MOVE_SLEEP_POWDER,
			.Level = 13,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 15,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 20,
		},
		{
			.Move = MOVE_SWEET_SCENT,
			.Level = 23,
		},
		{
			.Move = MOVE_GROWTH,
			.Level = 28,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 31,
		},
		{
			.Move = MOVE_PETAL_DANCE,
			.Level = 32,
		},
		{
			.Move = MOVE_WORRY_SEED,
			.Level = 39,
		},
		{
			.Move = MOVE_SYNTHESIS,
			.Level = 45,
		},
		{
			.Move = MOVE_PETAL_BLIZZARD,
			.Level = 50,
		},
		{
			.Move = MOVE_SOLARBEAM,
			.Level = 53,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CHARMANDER] = {
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 7,
		},
		{
			.Move = MOVE_SMOKESCREEN,
			.Level = 10,
		},
		{
			.Move = MOVE_DRAGON_RAGE,
			.Level = 16,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 19,
		},
		{
			.Move = MOVE_FIRE_FANG,
			.Level = 25,
		},
		{
			.Move = MOVE_FLAME_BURST,
			.Level = 28,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 34,
		},
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 37,
		},
		{
			.Move = MOVE_FIRE_SPIN,
			.Level = 43,
		},
		{
			.Move = MOVE_INFERNO,
			.Level = 46,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CHARMELEON] = {
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 7,
		},
		{
			.Move = MOVE_SMOKESCREEN,
			.Level = 10,
		},
		{
			.Move = MOVE_DRAGON_RAGE,
			.Level = 17,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 21,
		},
		{
			.Move = MOVE_FIRE_FANG,
			.Level = 28,
		},
		{
			.Move = MOVE_FLAME_BURST,
			.Level = 32,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 39,
		},
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 43,
		},
		{
			.Move = MOVE_FIRE_SPIN,
			.Level = 50,
		},
		{
			.Move = MOVE_INFERNO,
			.Level = 54,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CHARIZARD] = {
		{
			.Move = MOVE_FLARE_BLITZ,
			.Level = 1,
		},
		{
			.Move = MOVE_HEAT_WAVE,
			.Level = 1,
		},
		{
			.Move = MOVE_DRAGON_CLAW,
			.Level = 1,
		},
		{
			.Move = MOVE_SHADOW_CLAW,
			.Level = 1,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 1,
		},
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 1,
		},
		{
			.Move = MOVE_SMOKESCREEN,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 7,
		},
		{
			.Move = MOVE_SMOKESCREEN,
			.Level = 10,
		},
		{
			.Move = MOVE_DRAGON_RAGE,
			.Level = 17,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 21,
		},
		{
			.Move = MOVE_FIRE_FANG,
			.Level = 28,
		},
		{
			.Move = MOVE_FLAME_BURST,
			.Level = 32,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 36,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 41,
		},
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 47,
		},
		{
			.Move = MOVE_FIRE_SPIN,
			.Level = 56,
		},
		{
			.Move = MOVE_INFERNO,
			.Level = 62,
		},
		{
			.Move = MOVE_HEAT_WAVE,
			.Level = 71,
		},
		{
			.Move = MOVE_FLARE_BLITZ,
			.Level = 77,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SQUIRTLE] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 4,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 7,
		},
		{
			.Move = MOVE_WITHDRAW,
			.Level = 10,
		},
		{
			.Move = MOVE_BUBBLE,
			.Level = 13,
		},
		{
			.Move = MOVE_BITE,
			.Level = 16,
		},
		{
			.Move = MOVE_RAPID_SPIN,
			.Level = 19,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 22,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 25,
		},
		{
			.Move = MOVE_AQUA_TAIL,
			.Level = 28,
		},
		{
			.Move = MOVE_SKULL_BASH,
			.Level = 31,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 34,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 37,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 40,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_WARTORTLE] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 4,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 7,
		},
		{
			.Move = MOVE_WITHDRAW,
			.Level = 10,
		},
		{
			.Move = MOVE_BUBBLE,
			.Level = 13,
		},
		{
			.Move = MOVE_BITE,
			.Level = 16,
		},
		{
			.Move = MOVE_RAPID_SPIN,
			.Level = 20,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 24,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 28,
		},
		{
			.Move = MOVE_AQUA_TAIL,
			.Level = 32,
		},
		{
			.Move = MOVE_SKULL_BASH,
			.Level = 36,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 40,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 44,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 48,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BLASTOISE] = {
		{
			.Move = MOVE_FLASH_CANNON,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_WITHDRAW,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 4,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 7,
		},
		{
			.Move = MOVE_WITHDRAW,
			.Level = 10,
		},
		{
			.Move = MOVE_BUBBLE,
			.Level = 13,
		},
		{
			.Move = MOVE_BITE,
			.Level = 16,
		},
		{
			.Move = MOVE_RAPID_SPIN,
			.Level = 20,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 24,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 28,
		},
		{
			.Move = MOVE_AQUA_TAIL,
			.Level = 32,
		},
		{
			.Move = MOVE_SKULL_BASH,
			.Level = 39,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 46,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 53,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 60,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CATERPIE] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_STRING_SHOT,
			.Level = 1,
		},
		{
			.Move = MOVE_BUG_BITE,
			.Level = 15,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_METAPOD] = {
		{
			.Move = MOVE_HARDEN,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 7,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BUTTERFREE] = {
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 10,
		},
		{
			.Move = MOVE_POISONPOWDER,
			.Level = 12,
		},
		{
			.Move = MOVE_STUN_SPORE,
			.Level = 12,
		},
		{
			.Move = MOVE_SLEEP_POWDER,
			.Level = 12,
		},
		{
			.Move = MOVE_GUST,
			.Level = 16,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 18,
		},
		{
			.Move = MOVE_WHIRLWIND,
			.Level = 22,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 24,
		},
		{
			.Move = MOVE_SILVER_WIND,
			.Level = 28,
		},
		{
			.Move = MOVE_TAILWIND,
			.Level = 30,
		},
		{
			.Move = MOVE_RAGE_POWDER,
			.Level = 34,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 36,
		},
		{
			.Move = MOVE_CAPTIVATE,
			.Level = 40,
		},
		{
			.Move = MOVE_BUG_BUZZ,
			.Level = 42,
		},
		{
			.Move = MOVE_QUIVER_DANCE,
			.Level = 46,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_WEEDLE] = {
		{
			.Move = MOVE_POISON_STING,
			.Level = 1,
		},
		{
			.Move = MOVE_STRING_SHOT,
			.Level = 1,
		},
		{
			.Move = MOVE_BUG_BITE,
			.Level = 15,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_KAKUNA] = {
		{
			.Move = MOVE_HARDEN,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 7,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BEEDRILL] = {
		{
			.Move = MOVE_FURY_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_FURY_ATTACK,
			.Level = 10,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 13,
		},
		{
			.Move = MOVE_TWINEEDLE,
			.Level = 16,
		},
		{
			.Move = MOVE_RAGE,
			.Level = 19,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 22,
		},
		{
			.Move = MOVE_TOXIC_SPIKES,
			.Level = 25,
		},
		{
			.Move = MOVE_PIN_MISSILE,
			.Level = 28,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 31,
		},
		{
			.Move = MOVE_ASSURANCE,
			.Level = 34,
		},
		{
			.Move = MOVE_POISON_JAB,
			.Level = 37,
		},
		{
			.Move = MOVE_ENDEAVOR,
			.Level = 40,
		},
		{
			.Move = MOVE_FELL_STINGER,
			.Level = 45,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PIDGEY] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 5,
		},
		{
			.Move = MOVE_GUST,
			.Level = 9,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 13,
		},
		{
			.Move = MOVE_WHIRLWIND,
			.Level = 17,
		},
		{
			.Move = MOVE_TWISTER,
			.Level = 21,
		},
		{
			.Move = MOVE_FEATHERDANCE,
			.Level = 25,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 29,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 33,
		},
		{
			.Move = MOVE_ROOST,
			.Level = 37,
		},
		{
			.Move = MOVE_TAILWIND,
			.Level = 41,
		},
		{
			.Move = MOVE_MIRROR_MOVE,
			.Level = 45,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 49,
		},
		{
			.Move = MOVE_HURRICANE,
			.Level = 53,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PIDGEOTTO] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_GUST,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 5,
		},
		{
			.Move = MOVE_GUST,
			.Level = 9,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 13,
		},
		{
			.Move = MOVE_WHIRLWIND,
			.Level = 17,
		},
		{
			.Move = MOVE_TWISTER,
			.Level = 22,
		},
		{
			.Move = MOVE_FEATHERDANCE,
			.Level = 27,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 32,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 37,
		},
		{
			.Move = MOVE_ROOST,
			.Level = 42,
		},
		{
			.Move = MOVE_TAILWIND,
			.Level = 47,
		},
		{
			.Move = MOVE_MIRROR_MOVE,
			.Level = 52,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 57,
		},
		{
			.Move = MOVE_HURRICANE,
			.Level = 62,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PIDGEOT] = {
		{
			.Move = MOVE_HURRICANE,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_GUST,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 5,
		},
		{
			.Move = MOVE_GUST,
			.Level = 9,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 13,
		},
		{
			.Move = MOVE_WHIRLWIND,
			.Level = 17,
		},
		{
			.Move = MOVE_TWISTER,
			.Level = 22,
		},
		{
			.Move = MOVE_FEATHERDANCE,
			.Level = 27,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 32,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 38,
		},
		{
			.Move = MOVE_ROOST,
			.Level = 44,
		},
		{
			.Move = MOVE_TAILWIND,
			.Level = 50,
		},
		{
			.Move = MOVE_MIRROR_MOVE,
			.Level = 56,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 62,
		},
		{
			.Move = MOVE_HURRICANE,
			.Level = 68,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_RATTATA] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 4,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 7,
		},
		{
			.Move = MOVE_BITE,
			.Level = 10,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 13,
		},
		{
			.Move = MOVE_HYPER_FANG,
			.Level = 16,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 19,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 22,
		},
		{
			.Move = MOVE_ASSURANCE,
			.Level = 25,
		},
		{
			.Move = MOVE_SUPER_FANG,
			.Level = 28,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 31,
		},
		{
			.Move = MOVE_ENDEAVOR,
			.Level = 34,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_RATICATE] = {
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 4,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 7,
		},
		{
			.Move = MOVE_BITE,
			.Level = 10,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 13,
		},
		{
			.Move = MOVE_HYPER_FANG,
			.Level = 16,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 19,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 20,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 24,
		},
		{
			.Move = MOVE_ASSURANCE,
			.Level = 29,
		},
		{
			.Move = MOVE_SUPER_FANG,
			.Level = 34,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 39,
		},
		{
			.Move = MOVE_ENDEAVOR,
			.Level = 44,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SPEAROW] = {
		{
			.Move = MOVE_PECK,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 5,
		},
		{
			.Move = MOVE_FURY_ATTACK,
			.Level = 9,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 13,
		},
		{
			.Move = MOVE_AERIAL_ACE,
			.Level = 17,
		},
		{
			.Move = MOVE_MIRROR_MOVE,
			.Level = 21,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 25,
		},
		{
			.Move = MOVE_ASSURANCE,
			.Level = 29,
		},
		{
			.Move = MOVE_ROOST,
			.Level = 33,
		},
		{
			.Move = MOVE_DRILL_PECK,
			.Level = 37,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_FEAROW] = {
		{
			.Move = MOVE_DRILL_RUN,
			.Level = 1,
		},
		{
			.Move = MOVE_PLUCK,
			.Level = 1,
		},
		{
			.Move = MOVE_PECK,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_FURY_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 5,
		},
		{
			.Move = MOVE_FURY_ATTACK,
			.Level = 9,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 13,
		},
		{
			.Move = MOVE_AERIAL_ACE,
			.Level = 17,
		},
		{
			.Move = MOVE_MIRROR_MOVE,
			.Level = 23,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 29,
		},
		{
			.Move = MOVE_ASSURANCE,
			.Level = 35,
		},
		{
			.Move = MOVE_ROOST,
			.Level = 41,
		},
		{
			.Move = MOVE_DRILL_PECK,
			.Level = 47,
		},
		{
			.Move = MOVE_DRILL_RUN,
			.Level = 53,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_EKANS] = {
		{
			.Move = MOVE_WRAP,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_POISON_STING,
			.Level = 4,
		},
		{
			.Move = MOVE_BITE,
			.Level = 9,
		},
		{
			.Move = MOVE_GLARE,
			.Level = 12,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 17,
		},
		{
			.Move = MOVE_ACID,
			.Level = 20,
		},
		{
			.Move = MOVE_STOCKPILE,
			.Level = 25,
		},
		{
			.Move = MOVE_SWALLOW,
			.Level = 25,
		},
		{
			.Move = MOVE_SPIT_UP,
			.Level = 25,
		},
		{
			.Move = MOVE_ACID_SPRAY,
			.Level = 28,
		},
		{
			.Move = MOVE_MUD_BOMB,
			.Level = 33,
		},
		{
			.Move = MOVE_GASTRO_ACID,
			.Level = 36,
		},
		{
			.Move = MOVE_BELCH,
			.Level = 38,
		},
		{
			.Move = MOVE_HAZE,
			.Level = 41,
		},
		{
			.Move = MOVE_COIL,
			.Level = 44,
		},
		{
			.Move = MOVE_GUNK_SHOT,
			.Level = 49,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ARBOK] = {
		{
			.Move = MOVE_ICE_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_FIRE_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_WRAP,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_POISON_STING,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_POISON_STING,
			.Level = 4,
		},
		{
			.Move = MOVE_BITE,
			.Level = 9,
		},
		{
			.Move = MOVE_GLARE,
			.Level = 12,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 17,
		},
		{
			.Move = MOVE_ACID,
			.Level = 20,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 22,
		},
		{
			.Move = MOVE_STOCKPILE,
			.Level = 27,
		},
		{
			.Move = MOVE_SWALLOW,
			.Level = 27,
		},
		{
			.Move = MOVE_SPIT_UP,
			.Level = 27,
		},
		{
			.Move = MOVE_ACID_SPRAY,
			.Level = 32,
		},
		{
			.Move = MOVE_MUD_BOMB,
			.Level = 39,
		},
		{
			.Move = MOVE_GASTRO_ACID,
			.Level = 44,
		},
		{
			.Move = MOVE_BELCH,
			.Level = 48,
		},
		{
			.Move = MOVE_HAZE,
			.Level = 51,
		},
		{
			.Move = MOVE_COIL,
			.Level = 56,
		},
		{
			.Move = MOVE_GUNK_SHOT,
			.Level = 63,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PIKACHU] = {
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 5,
		},
		{
			.Move = MOVE_PLAY_NICE,
			.Level = 7,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 10,
		},
		{
			.Move = MOVE_ELECTRO_BALL,
			.Level = 13,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 18,
		},
		{
			.Move = MOVE_FEINT,
			.Level = 21,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 23,
		},
		{
			.Move = MOVE_SPARK,
			.Level = 26,
		},
		{
			.Move = MOVE_NUZZLE,
			.Level = 29,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 34,
		},
		{
			.Move = MOVE_SLAM,
			.Level = 37,
		},
		{
			.Move = MOVE_THUNDERBOLT,
			.Level = 42,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 45,
		},
		{
			.Move = MOVE_WILD_CHARGE,
			.Level = 50,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 53,
		},
		{
			.Move = MOVE_THUNDER,
			.Level = 58,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_RAICHU] = {
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDERBOLT,
			.Level = 1,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SANDSHREW] = {
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 3,
		},
		{
			.Move = MOVE_POISON_STING,
			.Level = 5,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 7,
		},
		{
			.Move = MOVE_RAPID_SPIN,
			.Level = 9,
		},
		{
			.Move = MOVE_FURY_CUTTER,
			.Level = 11,
		},
		{
			.Move = MOVE_MAGNITUDE,
			.Level = 14,
		},
		{
			.Move = MOVE_SWIFT,
			.Level = 17,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 20,
		},
		{
			.Move = MOVE_SAND_TOMB,
			.Level = 23,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 26,
		},
		{
			.Move = MOVE_DIG,
			.Level = 30,
		},
		{
			.Move = MOVE_GYRO_BALL,
			.Level = 34,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 38,
		},
		{
			.Move = MOVE_SANDSTORM,
			.Level = 42,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 46,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SANDSLASH] = {
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_POISON_STING,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 3,
		},
		{
			.Move = MOVE_POISON_STING,
			.Level = 5,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 7,
		},
		{
			.Move = MOVE_RAPID_SPIN,
			.Level = 9,
		},
		{
			.Move = MOVE_FURY_CUTTER,
			.Level = 11,
		},
		{
			.Move = MOVE_MAGNITUDE,
			.Level = 14,
		},
		{
			.Move = MOVE_SWIFT,
			.Level = 17,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 20,
		},
		{
			.Move = MOVE_CRUSH_CLAW,
			.Level = 22,
		},
		{
			.Move = MOVE_SAND_TOMB,
			.Level = 24,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 28,
		},
		{
			.Move = MOVE_DIG,
			.Level = 33,
		},
		{
			.Move = MOVE_GYRO_BALL,
			.Level = 38,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 43,
		},
		{
			.Move = MOVE_SANDSTORM,
			.Level = 48,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 53,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_NIDORAN♀] = {
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 7,
		},
		{
			.Move = MOVE_DOUBLE_KICK,
			.Level = 9,
		},
		{
			.Move = MOVE_POISON_STING,
			.Level = 13,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 19,
		},
		{
			.Move = MOVE_BITE,
			.Level = 21,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 25,
		},
		{
			.Move = MOVE_TOXIC_SPIKES,
			.Level = 31,
		},
		{
			.Move = MOVE_FLATTER,
			.Level = 33,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 37,
		},
		{
			.Move = MOVE_CAPTIVATE,
			.Level = 43,
		},
		{
			.Move = MOVE_POISON_FANG,
			.Level = 45,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_NIDORINA] = {
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 7,
		},
		{
			.Move = MOVE_DOUBLE_KICK,
			.Level = 9,
		},
		{
			.Move = MOVE_POISON_STING,
			.Level = 13,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 20,
		},
		{
			.Move = MOVE_BITE,
			.Level = 23,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 28,
		},
		{
			.Move = MOVE_TOXIC_SPIKES,
			.Level = 35,
		},
		{
			.Move = MOVE_FLATTER,
			.Level = 38,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 43,
		},
		{
			.Move = MOVE_CAPTIVATE,
			.Level = 50,
		},
		{
			.Move = MOVE_POISON_FANG,
			.Level = 58,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_NIDOQUEEN] = {
		{
			.Move = MOVE_SUPERPOWER,
			.Level = 1,
		},
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_DOUBLE_KICK,
			.Level = 1,
		},
		{
			.Move = MOVE_POISON_STING,
			.Level = 1,
		},
		{
			.Move = MOVE_CHIP_AWAY,
			.Level = 23,
		},
		{
			.Move = MOVE_BODY_SLAM,
			.Level = 35,
		},
		{
			.Move = MOVE_EARTH_POWER,
			.Level = 43,
		},
		{
			.Move = MOVE_SUPERPOWER,
			.Level = 58,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_NIDORAN♂] = {
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_PECK,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 7,
		},
		{
			.Move = MOVE_DOUBLE_KICK,
			.Level = 9,
		},
		{
			.Move = MOVE_POISON_STING,
			.Level = 13,
		},
		{
			.Move = MOVE_FURY_ATTACK,
			.Level = 19,
		},
		{
			.Move = MOVE_HORN_ATTACK,
			.Level = 21,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 25,
		},
		{
			.Move = MOVE_TOXIC_SPIKES,
			.Level = 31,
		},
		{
			.Move = MOVE_FLATTER,
			.Level = 33,
		},
		{
			.Move = MOVE_POISON_JAB,
			.Level = 37,
		},
		{
			.Move = MOVE_CAPTIVATE,
			.Level = 43,
		},
		{
			.Move = MOVE_HORN_DRILL,
			.Level = 45,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_NIDORINO] = {
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_PECK,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 7,
		},
		{
			.Move = MOVE_DOUBLE_KICK,
			.Level = 9,
		},
		{
			.Move = MOVE_POISON_STING,
			.Level = 13,
		},
		{
			.Move = MOVE_FURY_ATTACK,
			.Level = 20,
		},
		{
			.Move = MOVE_HORN_ATTACK,
			.Level = 23,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 28,
		},
		{
			.Move = MOVE_TOXIC_SPIKES,
			.Level = 35,
		},
		{
			.Move = MOVE_FLATTER,
			.Level = 38,
		},
		{
			.Move = MOVE_POISON_JAB,
			.Level = 43,
		},
		{
			.Move = MOVE_CAPTIVATE,
			.Level = 50,
		},
		{
			.Move = MOVE_HORN_DRILL,
			.Level = 58,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_NIDOKING] = {
		{
			.Move = MOVE_MEGAHORN,
			.Level = 1,
		},
		{
			.Move = MOVE_PECK,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 1,
		},
		{
			.Move = MOVE_DOUBLE_KICK,
			.Level = 1,
		},
		{
			.Move = MOVE_POISON_STING,
			.Level = 1,
		},
		{
			.Move = MOVE_CHIP_AWAY,
			.Level = 23,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 35,
		},
		{
			.Move = MOVE_EARTH_POWER,
			.Level = 43,
		},
		{
			.Move = MOVE_MEGAHORN,
			.Level = 58,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CLEFAIRY] = {
		{
			.Move = MOVE_AFTER_YOU,
			.Level = 1,
		},
		{
			.Move = MOVE_HEALING_WISH,
			.Level = 1,
		},
		{
			.Move = MOVE_DISARMING_VOICE,
			.Level = 1,
		},
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_ENCORE,
			.Level = 1,
		},
		{
			.Move = MOVE_SING,
			.Level = 7,
		},
		{
			.Move = MOVE_DOUBLESLAP,
			.Level = 10,
		},
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 13,
		},
		{
			.Move = MOVE_FOLLOW_ME,
			.Level = 16,
		},
		{
			.Move = MOVE_BESTOW,
			.Level = 19,
		},
		{
			.Move = MOVE_WAKEUP_SLAP,
			.Level = 22,
		},
		{
			.Move = MOVE_MINIMIZE,
			.Level = 25,
		},
		{
			.Move = MOVE_STORED_POWER,
			.Level = 28,
		},
		{
			.Move = MOVE_METRONOME,
			.Level = 31,
		},
		{
			.Move = MOVE_COSMIC_POWER,
			.Level = 34,
		},
		{
			.Move = MOVE_LUCKY_CHANT,
			.Level = 37,
		},
		{
			.Move = MOVE_BODY_SLAM,
			.Level = 40,
		},
		{
			.Move = MOVE_MOONLIGHT,
			.Level = 43,
		},
		{
			.Move = MOVE_MOONBLAST,
			.Level = 46,
		},
		{
			.Move = MOVE_GRAVITY,
			.Level = 49,
		},
		{
			.Move = MOVE_METEOR_MASH,
			.Level = 50,
		},
		{
			.Move = MOVE_HEALING_WISH,
			.Level = 55,
		},
		{
			.Move = MOVE_AFTER_YOU,
			.Level = 58,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CLEFABLE] = {
		{
			.Move = MOVE_DISARMING_VOICE,
			.Level = 1,
		},
		{
			.Move = MOVE_SING,
			.Level = 1,
		},
		{
			.Move = MOVE_DOUBLESLAP,
			.Level = 1,
		},
		{
			.Move = MOVE_MINIMIZE,
			.Level = 1,
		},
		{
			.Move = MOVE_METRONOME,
			.Level = 1,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_VULPIX] = {
		{
			.Move = MOVE_EMBER,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 4,
		},
		{
			.Move = MOVE_ROAR,
			.Level = 7,
		},
		{
			.Move = MOVE_BABYDOLL_EYES,
			.Level = 9,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 10,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 12,
		},
		{
			.Move = MOVE_FIRE_SPIN,
			.Level = 15,
		},
		{
			.Move = MOVE_PAYBACK,
			.Level = 18,
		},
		{
			.Move = MOVE_WILLOWISP,
			.Level = 20,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 23,
		},
		{
			.Move = MOVE_HEX,
			.Level = 26,
		},
		{
			.Move = MOVE_FLAME_BURST,
			.Level = 28,
		},
		{
			.Move = MOVE_EXTRASENSORY,
			.Level = 31,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 34,
		},
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 36,
		},
		{
			.Move = MOVE_IMPRISON,
			.Level = 39,
		},
		{
			.Move = MOVE_FIRE_BLAST,
			.Level = 42,
		},
		{
			.Move = MOVE_GRUDGE,
			.Level = 44,
		},
		{
			.Move = MOVE_CAPTIVATE,
			.Level = 47,
		},
		{
			.Move = MOVE_INFERNO,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_NINETALES] = {
		{
			.Move = MOVE_IMPRISON,
			.Level = 1,
		},
		{
			.Move = MOVE_NASTY_PLOT,
			.Level = 1,
		},
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 1,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 1,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_JIGGLYPUFF] = {
		{
			.Move = MOVE_SING,
			.Level = 1,
		},
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 3,
		},
		{
			.Move = MOVE_POUND,
			.Level = 5,
		},
		{
			.Move = MOVE_PLAY_NICE,
			.Level = 8,
		},
		{
			.Move = MOVE_DISARMING_VOICE,
			.Level = 11,
		},
		{
			.Move = MOVE_DISABLE,
			.Level = 15,
		},
		{
			.Move = MOVE_DOUBLESLAP,
			.Level = 18,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 21,
		},
		{
			.Move = MOVE_ROUND,
			.Level = 24,
		},
		{
			.Move = MOVE_WAKEUP_SLAP,
			.Level = 28,
		},
		{
			.Move = MOVE_REST,
			.Level = 32,
		},
		{
			.Move = MOVE_BODY_SLAM,
			.Level = 35,
		},
		{
			.Move = MOVE_MIMIC,
			.Level = 37,
		},
		{
			.Move = MOVE_GYRO_BALL,
			.Level = 40,
		},
		{
			.Move = MOVE_HYPER_VOICE,
			.Level = 44,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 49,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_WIGGLYTUFF] = {
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 1,
		},
		{
			.Move = MOVE_PLAY_ROUGH,
			.Level = 1,
		},
		{
			.Move = MOVE_SING,
			.Level = 1,
		},
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 1,
		},
		{
			.Move = MOVE_DISABLE,
			.Level = 1,
		},
		{
			.Move = MOVE_DOUBLESLAP,
			.Level = 1,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ZUBAT] = {
		{
			.Move = MOVE_LEECH_LIFE,
			.Level = 1,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 5,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 7,
		},
		{
			.Move = MOVE_BITE,
			.Level = 11,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 13,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 17,
		},
		{
			.Move = MOVE_AIR_CUTTER,
			.Level = 19,
		},
		{
			.Move = MOVE_SWIFT,
			.Level = 23,
		},
		{
			.Move = MOVE_POISON_FANG,
			.Level = 25,
		},
		{
			.Move = MOVE_MEAN_LOOK,
			.Level = 29,
		},
		{
			.Move = MOVE_ACROBATICS,
			.Level = 31,
		},
		{
			.Move = MOVE_HAZE,
			.Level = 35,
		},
		{
			.Move = MOVE_VENOSHOCK,
			.Level = 37,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 41,
		},
		{
			.Move = MOVE_QUICK_GUARD,
			.Level = 43,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GOLBAT] = {
		{
			.Move = MOVE_SCREECH,
			.Level = 1,
		},
		{
			.Move = MOVE_LEECH_LIFE,
			.Level = 1,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 5,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 7,
		},
		{
			.Move = MOVE_BITE,
			.Level = 11,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 13,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 17,
		},
		{
			.Move = MOVE_AIR_CUTTER,
			.Level = 19,
		},
		{
			.Move = MOVE_SWIFT,
			.Level = 24,
		},
		{
			.Move = MOVE_POISON_FANG,
			.Level = 27,
		},
		{
			.Move = MOVE_MEAN_LOOK,
			.Level = 32,
		},
		{
			.Move = MOVE_ACROBATICS,
			.Level = 35,
		},
		{
			.Move = MOVE_HAZE,
			.Level = 40,
		},
		{
			.Move = MOVE_VENOSHOCK,
			.Level = 43,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 48,
		},
		{
			.Move = MOVE_QUICK_GUARD,
			.Level = 51,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ODDISH] = {
		{
			.Move = MOVE_ABSORB,
			.Level = 1,
		},
		{
			.Move = MOVE_SWEET_SCENT,
			.Level = 5,
		},
		{
			.Move = MOVE_ACID,
			.Level = 9,
		},
		{
			.Move = MOVE_POISONPOWDER,
			.Level = 13,
		},
		{
			.Move = MOVE_STUN_SPORE,
			.Level = 14,
		},
		{
			.Move = MOVE_SLEEP_POWDER,
			.Level = 15,
		},
		{
			.Move = MOVE_MEGA_DRAIN,
			.Level = 19,
		},
		{
			.Move = MOVE_LUCKY_CHANT,
			.Level = 23,
		},
		{
			.Move = MOVE_MOONLIGHT,
			.Level = 27,
		},
		{
			.Move = MOVE_GIGA_DRAIN,
			.Level = 31,
		},
		{
			.Move = MOVE_TOXIC,
			.Level = 35,
		},
		{
			.Move = MOVE_NATURAL_GIFT,
			.Level = 39,
		},
		{
			.Move = MOVE_MOONBLAST,
			.Level = 43,
		},
		{
			.Move = MOVE_GRASSY_TERRAIN,
			.Level = 47,
		},
		{
			.Move = MOVE_PETAL_DANCE,
			.Level = 51,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GLOOM] = {
		{
			.Move = MOVE_ABSORB,
			.Level = 1,
		},
		{
			.Move = MOVE_SWEET_SCENT,
			.Level = 1,
		},
		{
			.Move = MOVE_ACID,
			.Level = 1,
		},
		{
			.Move = MOVE_SWEET_SCENT,
			.Level = 5,
		},
		{
			.Move = MOVE_ACID,
			.Level = 9,
		},
		{
			.Move = MOVE_POISONPOWDER,
			.Level = 13,
		},
		{
			.Move = MOVE_STUN_SPORE,
			.Level = 14,
		},
		{
			.Move = MOVE_SLEEP_POWDER,
			.Level = 15,
		},
		{
			.Move = MOVE_MEGA_DRAIN,
			.Level = 19,
		},
		{
			.Move = MOVE_LUCKY_CHANT,
			.Level = 24,
		},
		{
			.Move = MOVE_MOONLIGHT,
			.Level = 29,
		},
		{
			.Move = MOVE_GIGA_DRAIN,
			.Level = 34,
		},
		{
			.Move = MOVE_TOXIC,
			.Level = 39,
		},
		{
			.Move = MOVE_NATURAL_GIFT,
			.Level = 44,
		},
		{
			.Move = MOVE_PETAL_BLIZZARD,
			.Level = 49,
		},
		{
			.Move = MOVE_GRASSY_TERRAIN,
			.Level = 54,
		},
		{
			.Move = MOVE_PETAL_DANCE,
			.Level = 59,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_VILEPLUME] = {
		{
			.Move = MOVE_MEGA_DRAIN,
			.Level = 1,
		},
		{
			.Move = MOVE_AROMATHERAPY,
			.Level = 1,
		},
		{
			.Move = MOVE_POISONPOWDER,
			.Level = 1,
		},
		{
			.Move = MOVE_STUN_SPORE,
			.Level = 1,
		},
		{
			.Move = MOVE_PETAL_BLIZZARD,
			.Level = 49,
		},
		{
			.Move = MOVE_PETAL_DANCE,
			.Level = 59,
		},
		{
			.Move = MOVE_SOLARBEAM,
			.Level = 64,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PARAS] = {
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_STUN_SPORE,
			.Level = 6,
		},
		{
			.Move = MOVE_POISONPOWDER,
			.Level = 6,
		},
		{
			.Move = MOVE_LEECH_LIFE,
			.Level = 11,
		},
		{
			.Move = MOVE_FURY_CUTTER,
			.Level = 17,
		},
		{
			.Move = MOVE_SPORE,
			.Level = 22,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 27,
		},
		{
			.Move = MOVE_GROWTH,
			.Level = 33,
		},
		{
			.Move = MOVE_GIGA_DRAIN,
			.Level = 38,
		},
		{
			.Move = MOVE_AROMATHERAPY,
			.Level = 43,
		},
		{
			.Move = MOVE_RAGE_POWDER,
			.Level = 49,
		},
		{
			.Move = MOVE_XSCISSOR,
			.Level = 54,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PARASECT] = {
		{
			.Move = MOVE_CROSS_POISON,
			.Level = 1,
		},
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_STUN_SPORE,
			.Level = 1,
		},
		{
			.Move = MOVE_POISONPOWDER,
			.Level = 1,
		},
		{
			.Move = MOVE_LEECH_LIFE,
			.Level = 1,
		},
		{
			.Move = MOVE_STUN_SPORE,
			.Level = 6,
		},
		{
			.Move = MOVE_POISONPOWDER,
			.Level = 6,
		},
		{
			.Move = MOVE_LEECH_LIFE,
			.Level = 11,
		},
		{
			.Move = MOVE_FURY_CUTTER,
			.Level = 17,
		},
		{
			.Move = MOVE_SPORE,
			.Level = 22,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 29,
		},
		{
			.Move = MOVE_GROWTH,
			.Level = 37,
		},
		{
			.Move = MOVE_GIGA_DRAIN,
			.Level = 44,
		},
		{
			.Move = MOVE_AROMATHERAPY,
			.Level = 51,
		},
		{
			.Move = MOVE_RAGE_POWDER,
			.Level = 59,
		},
		{
			.Move = MOVE_XSCISSOR,
			.Level = 66,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_VENONAT] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_DISABLE,
			.Level = 1,
		},
		{
			.Move = MOVE_FORESIGHT,
			.Level = 1,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 5,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 11,
		},
		{
			.Move = MOVE_POISONPOWDER,
			.Level = 13,
		},
		{
			.Move = MOVE_LEECH_LIFE,
			.Level = 17,
		},
		{
			.Move = MOVE_STUN_SPORE,
			.Level = 23,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 25,
		},
		{
			.Move = MOVE_SLEEP_POWDER,
			.Level = 29,
		},
		{
			.Move = MOVE_SIGNAL_BEAM,
			.Level = 35,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 37,
		},
		{
			.Move = MOVE_POISON_FANG,
			.Level = 41,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 47,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_VENOMOTH] = {
		{
			.Move = MOVE_QUIVER_DANCE,
			.Level = 1,
		},
		{
			.Move = MOVE_BUG_BUZZ,
			.Level = 1,
		},
		{
			.Move = MOVE_SILVER_WIND,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_DISABLE,
			.Level = 1,
		},
		{
			.Move = MOVE_FORESIGHT,
			.Level = 1,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 1,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 5,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 11,
		},
		{
			.Move = MOVE_POISONPOWDER,
			.Level = 13,
		},
		{
			.Move = MOVE_LEECH_LIFE,
			.Level = 17,
		},
		{
			.Move = MOVE_STUN_SPORE,
			.Level = 23,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 25,
		},
		{
			.Move = MOVE_SLEEP_POWDER,
			.Level = 29,
		},
		{
			.Move = MOVE_GUST,
			.Level = 31,
		},
		{
			.Move = MOVE_SIGNAL_BEAM,
			.Level = 37,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 41,
		},
		{
			.Move = MOVE_POISON_FANG,
			.Level = 47,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 55,
		},
		{
			.Move = MOVE_BUG_BUZZ,
			.Level = 59,
		},
		{
			.Move = MOVE_QUIVER_DANCE,
			.Level = 63,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_DIGLETT] = {
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 4,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 7,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 12,
		},
		{
			.Move = MOVE_MAGNITUDE,
			.Level = 15,
		},
		{
			.Move = MOVE_BULLDOZE,
			.Level = 18,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 23,
		},
		{
			.Move = MOVE_MUD_BOMB,
			.Level = 26,
		},
		{
			.Move = MOVE_EARTH_POWER,
			.Level = 29,
		},
		{
			.Move = MOVE_DIG,
			.Level = 34,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 37,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 40,
		},
		{
			.Move = MOVE_FISSURE,
			.Level = 45,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_DUGTRIO] = {
		{
			.Move = MOVE_ROTOTILLER,
			.Level = 1,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 1,
		},
		{
			.Move = MOVE_TRI_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 4,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 7,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 12,
		},
		{
			.Move = MOVE_MAGNITUDE,
			.Level = 15,
		},
		{
			.Move = MOVE_BULLDOZE,
			.Level = 18,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 23,
		},
		{
			.Move = MOVE_SAND_TOMB,
			.Level = 26,
		},
		{
			.Move = MOVE_MUD_BOMB,
			.Level = 28,
		},
		{
			.Move = MOVE_EARTH_POWER,
			.Level = 33,
		},
		{
			.Move = MOVE_DIG,
			.Level = 40,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 45,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 50,
		},
		{
			.Move = MOVE_FISSURE,
			.Level = 57,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MEOWTH] = {
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 6,
		},
		{
			.Move = MOVE_FAKE_OUT,
			.Level = 9,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 14,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 17,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 22,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 25,
		},
		{
			.Move = MOVE_PAY_DAY,
			.Level = 30,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 33,
		},
		{
			.Move = MOVE_NASTY_PLOT,
			.Level = 38,
		},
		{
			.Move = MOVE_ASSURANCE,
			.Level = 41,
		},
		{
			.Move = MOVE_CAPTIVATE,
			.Level = 46,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 49,
		},
		{
			.Move = MOVE_FEINT,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PERSIAN] = {
		{
			.Move = MOVE_PLAY_ROUGH,
			.Level = 1,
		},
		{
			.Move = MOVE_SWITCHEROO,
			.Level = 1,
		},
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_FAKE_OUT,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 6,
		},
		{
			.Move = MOVE_FAKE_OUT,
			.Level = 9,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 14,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 17,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 22,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 25,
		},
		{
			.Move = MOVE_SWIFT,
			.Level = 28,
		},
		{
			.Move = MOVE_POWER_GEM,
			.Level = 32,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 37,
		},
		{
			.Move = MOVE_NASTY_PLOT,
			.Level = 44,
		},
		{
			.Move = MOVE_ASSURANCE,
			.Level = 49,
		},
		{
			.Move = MOVE_CAPTIVATE,
			.Level = 56,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 61,
		},
		{
			.Move = MOVE_FEINT,
			.Level = 65,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PSYDUCK] = {
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 4,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 8,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 11,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 15,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 18,
		},
		{
			.Move = MOVE_DISABLE,
			.Level = 22,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 25,
		},
		{
			.Move = MOVE_AQUA_TAIL,
			.Level = 29,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 32,
		},
		{
			.Move = MOVE_SOAK,
			.Level = 36,
		},
		{
			.Move = MOVE_PSYCH_UP,
			.Level = 39,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 43,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 46,
		},
		{
			.Move = MOVE_WONDER_ROOM,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GOLDUCK] = {
		{
			.Move = MOVE_AQUA_JET,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 4,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 8,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 11,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 15,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 18,
		},
		{
			.Move = MOVE_DISABLE,
			.Level = 22,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 25,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 29,
		},
		{
			.Move = MOVE_AQUA_TAIL,
			.Level = 32,
		},
		{
			.Move = MOVE_SOAK,
			.Level = 38,
		},
		{
			.Move = MOVE_PSYCH_UP,
			.Level = 43,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 49,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 54,
		},
		{
			.Move = MOVE_WONDER_ROOM,
			.Level = 60,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MANKEY] = {
		{
			.Move = MOVE_COVET,
			.Level = 1,
		},
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_LOW_KICK,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 1,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 9,
		},
		{
			.Move = MOVE_KARATE_CHOP,
			.Level = 13,
		},
		{
			.Move = MOVE_SEISMIC_TOSS,
			.Level = 17,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 21,
		},
		{
			.Move = MOVE_ASSURANCE,
			.Level = 25,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 33,
		},
		{
			.Move = MOVE_CROSS_CHOP,
			.Level = 37,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 41,
		},
		{
			.Move = MOVE_PUNISHMENT,
			.Level = 45,
		},
		{
			.Move = MOVE_CLOSE_COMBAT,
			.Level = 49,
		},
		{
			.Move = MOVE_FINAL_GAMBIT,
			.Level = 53,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PRIMEAPE] = {
		{
			.Move = MOVE_FINAL_GAMBIT,
			.Level = 1,
		},
		{
			.Move = MOVE_FLING,
			.Level = 1,
		},
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_LOW_KICK,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 1,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 9,
		},
		{
			.Move = MOVE_KARATE_CHOP,
			.Level = 13,
		},
		{
			.Move = MOVE_SEISMIC_TOSS,
			.Level = 17,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 21,
		},
		{
			.Move = MOVE_ASSURANCE,
			.Level = 25,
		},
		{
			.Move = MOVE_RAGE,
			.Level = 28,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 35,
		},
		{
			.Move = MOVE_CROSS_CHOP,
			.Level = 41,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 47,
		},
		{
			.Move = MOVE_PUNISHMENT,
			.Level = 53,
		},
		{
			.Move = MOVE_CLOSE_COMBAT,
			.Level = 59,
		},
		{
			.Move = MOVE_FINAL_GAMBIT,
			.Level = 63,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GROWLITHE] = {
		{
			.Move = MOVE_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_ROAR,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 6,
		},
		{
			.Move = MOVE_LEER,
			.Level = 8,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 10,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 12,
		},
		{
			.Move = MOVE_FLAME_WHEEL,
			.Level = 17,
		},
		{
			.Move = MOVE_REVERSAL,
			.Level = 19,
		},
		{
			.Move = MOVE_FIRE_FANG,
			.Level = 21,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 23,
		},
		{
			.Move = MOVE_FLAME_BURST,
			.Level = 28,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 30,
		},
		{
			.Move = MOVE_RETALIATE,
			.Level = 32,
		},
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 34,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 39,
		},
		{
			.Move = MOVE_HEAT_WAVE,
			.Level = 41,
		},
		{
			.Move = MOVE_OUTRAGE,
			.Level = 43,
		},
		{
			.Move = MOVE_FLARE_BLITZ,
			.Level = 45,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ARCANINE] = {
		{
			.Move = MOVE_THUNDER_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_ROAR,
			.Level = 1,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 1,
		},
		{
			.Move = MOVE_FIRE_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_EXTREMESPEED,
			.Level = 34,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_POLIWAG] = {
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 5,
		},
		{
			.Move = MOVE_HYPNOSIS,
			.Level = 8,
		},
		{
			.Move = MOVE_BUBBLE,
			.Level = 11,
		},
		{
			.Move = MOVE_DOUBLESLAP,
			.Level = 15,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 18,
		},
		{
			.Move = MOVE_BODY_SLAM,
			.Level = 21,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 25,
		},
		{
			.Move = MOVE_MUD_SHOT,
			.Level = 28,
		},
		{
			.Move = MOVE_BELLY_DRUM,
			.Level = 31,
		},
		{
			.Move = MOVE_WAKEUP_SLAP,
			.Level = 35,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 38,
		},
		{
			.Move = MOVE_MUD_BOMB,
			.Level = 41,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_POLIWHIRL] = {
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_HYPNOSIS,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 5,
		},
		{
			.Move = MOVE_HYPNOSIS,
			.Level = 8,
		},
		{
			.Move = MOVE_BUBBLE,
			.Level = 11,
		},
		{
			.Move = MOVE_DOUBLESLAP,
			.Level = 15,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 18,
		},
		{
			.Move = MOVE_BODY_SLAM,
			.Level = 21,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 27,
		},
		{
			.Move = MOVE_MUD_SHOT,
			.Level = 32,
		},
		{
			.Move = MOVE_BELLY_DRUM,
			.Level = 37,
		},
		{
			.Move = MOVE_WAKEUP_SLAP,
			.Level = 43,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 48,
		},
		{
			.Move = MOVE_MUD_BOMB,
			.Level = 53,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_POLIWRATH] = {
		{
			.Move = MOVE_CIRCLE_THROW,
			.Level = 1,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 1,
		},
		{
			.Move = MOVE_HYPNOSIS,
			.Level = 1,
		},
		{
			.Move = MOVE_DOUBLESLAP,
			.Level = 1,
		},
		{
			.Move = MOVE_SUBMISSION,
			.Level = 1,
		},
		{
			.Move = MOVE_DYNAMICPUNCH,
			.Level = 32,
		},
		{
			.Move = MOVE_MIND_READER,
			.Level = 43,
		},
		{
			.Move = MOVE_CIRCLE_THROW,
			.Level = 53,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ABRA] = {
		{
			.Move = MOVE_TELEPORT,
			.Level = 1,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_KADABRA] = {
		{
			.Move = MOVE_TELEPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_KINESIS,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 16,
		},
		{
			.Move = MOVE_DISABLE,
			.Level = 18,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 21,
		},
		{
			.Move = MOVE_MIRACLE_EYE,
			.Level = 23,
		},
		{
			.Move = MOVE_REFLECT,
			.Level = 26,
		},
		{
			.Move = MOVE_PSYCHO_CUT,
			.Level = 28,
		},
		{
			.Move = MOVE_RECOVER,
			.Level = 31,
		},
		{
			.Move = MOVE_TELEKINESIS,
			.Level = 33,
		},
		{
			.Move = MOVE_ALLY_SWITCH,
			.Level = 36,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 38,
		},
		{
			.Move = MOVE_ROLE_PLAY,
			.Level = 41,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 43,
		},
		{
			.Move = MOVE_TRICK,
			.Level = 46,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ALAKAZAM] = {
		{
			.Move = MOVE_TELEPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_KINESIS,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 16,
		},
		{
			.Move = MOVE_DISABLE,
			.Level = 18,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 21,
		},
		{
			.Move = MOVE_MIRACLE_EYE,
			.Level = 23,
		},
		{
			.Move = MOVE_REFLECT,
			.Level = 26,
		},
		{
			.Move = MOVE_PSYCHO_CUT,
			.Level = 28,
		},
		{
			.Move = MOVE_RECOVER,
			.Level = 31,
		},
		{
			.Move = MOVE_TELEKINESIS,
			.Level = 33,
		},
		{
			.Move = MOVE_ALLY_SWITCH,
			.Level = 36,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 38,
		},
		{
			.Move = MOVE_CALM_MIND,
			.Level = 41,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 43,
		},
		{
			.Move = MOVE_TRICK,
			.Level = 46,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MACHOP] = {
		{
			.Move = MOVE_LOW_KICK,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 3,
		},
		{
			.Move = MOVE_KARATE_CHOP,
			.Level = 7,
		},
		{
			.Move = MOVE_FORESIGHT,
			.Level = 9,
		},
		{
			.Move = MOVE_LOW_SWEEP,
			.Level = 13,
		},
		{
			.Move = MOVE_SEISMIC_TOSS,
			.Level = 15,
		},
		{
			.Move = MOVE_REVENGE,
			.Level = 19,
		},
		{
			.Move = MOVE_KNOCK_OFF,
			.Level = 21,
		},
		{
			.Move = MOVE_VITAL_THROW,
			.Level = 25,
		},
		{
			.Move = MOVE_WAKEUP_SLAP,
			.Level = 27,
		},
		{
			.Move = MOVE_DUAL_CHOP,
			.Level = 31,
		},
		{
			.Move = MOVE_SUBMISSION,
			.Level = 33,
		},
		{
			.Move = MOVE_BULK_UP,
			.Level = 37,
		},
		{
			.Move = MOVE_CROSS_CHOP,
			.Level = 39,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 43,
		},
		{
			.Move = MOVE_DYNAMICPUNCH,
			.Level = 45,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MACHOKE] = {
		{
			.Move = MOVE_LOW_KICK,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 1,
		},
		{
			.Move = MOVE_KARATE_CHOP,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 3,
		},
		{
			.Move = MOVE_KARATE_CHOP,
			.Level = 7,
		},
		{
			.Move = MOVE_FORESIGHT,
			.Level = 9,
		},
		{
			.Move = MOVE_LOW_SWEEP,
			.Level = 13,
		},
		{
			.Move = MOVE_SEISMIC_TOSS,
			.Level = 15,
		},
		{
			.Move = MOVE_REVENGE,
			.Level = 19,
		},
		{
			.Move = MOVE_KNOCK_OFF,
			.Level = 21,
		},
		{
			.Move = MOVE_VITAL_THROW,
			.Level = 25,
		},
		{
			.Move = MOVE_WAKEUP_SLAP,
			.Level = 27,
		},
		{
			.Move = MOVE_DUAL_CHOP,
			.Level = 33,
		},
		{
			.Move = MOVE_SUBMISSION,
			.Level = 37,
		},
		{
			.Move = MOVE_BULK_UP,
			.Level = 43,
		},
		{
			.Move = MOVE_CROSS_CHOP,
			.Level = 47,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 53,
		},
		{
			.Move = MOVE_DYNAMICPUNCH,
			.Level = 57,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MACHAMP] = {
		{
			.Move = MOVE_WIDE_GUARD,
			.Level = 1,
		},
		{
			.Move = MOVE_LOW_KICK,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 1,
		},
		{
			.Move = MOVE_KARATE_CHOP,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 3,
		},
		{
			.Move = MOVE_KARATE_CHOP,
			.Level = 7,
		},
		{
			.Move = MOVE_FORESIGHT,
			.Level = 9,
		},
		{
			.Move = MOVE_LOW_SWEEP,
			.Level = 13,
		},
		{
			.Move = MOVE_SEISMIC_TOSS,
			.Level = 15,
		},
		{
			.Move = MOVE_REVENGE,
			.Level = 19,
		},
		{
			.Move = MOVE_KNOCK_OFF,
			.Level = 21,
		},
		{
			.Move = MOVE_VITAL_THROW,
			.Level = 25,
		},
		{
			.Move = MOVE_WAKEUP_SLAP,
			.Level = 27,
		},
		{
			.Move = MOVE_DUAL_CHOP,
			.Level = 33,
		},
		{
			.Move = MOVE_SUBMISSION,
			.Level = 37,
		},
		{
			.Move = MOVE_BULK_UP,
			.Level = 43,
		},
		{
			.Move = MOVE_CROSS_CHOP,
			.Level = 47,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 53,
		},
		{
			.Move = MOVE_DYNAMICPUNCH,
			.Level = 57,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BELLSPROUT] = {
		{
			.Move = MOVE_GROWTH,
			.Level = 7,
		},
		{
			.Move = MOVE_WRAP,
			.Level = 11,
		},
		{
			.Move = MOVE_SLEEP_POWDER,
			.Level = 13,
		},
		{
			.Move = MOVE_POISONPOWDER,
			.Level = 15,
		},
		{
			.Move = MOVE_STUN_SPORE,
			.Level = 17,
		},
		{
			.Move = MOVE_ACID,
			.Level = 23,
		},
		{
			.Move = MOVE_KNOCK_OFF,
			.Level = 27,
		},
		{
			.Move = MOVE_SWEET_SCENT,
			.Level = 29,
		},
		{
			.Move = MOVE_GASTRO_ACID,
			.Level = 35,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 39,
		},
		{
			.Move = MOVE_SLAM,
			.Level = 41,
		},
		{
			.Move = MOVE_WRING_OUT,
			.Level = 47,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_WEEPINBELL] = {
		{
			.Move = MOVE_VINE_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWTH,
			.Level = 1,
		},
		{
			.Move = MOVE_WRAP,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWTH,
			.Level = 7,
		},
		{
			.Move = MOVE_WRAP,
			.Level = 11,
		},
		{
			.Move = MOVE_SLEEP_POWDER,
			.Level = 13,
		},
		{
			.Move = MOVE_POISONPOWDER,
			.Level = 15,
		},
		{
			.Move = MOVE_STUN_SPORE,
			.Level = 17,
		},
		{
			.Move = MOVE_ACID,
			.Level = 23,
		},
		{
			.Move = MOVE_KNOCK_OFF,
			.Level = 27,
		},
		{
			.Move = MOVE_SWEET_SCENT,
			.Level = 29,
		},
		{
			.Move = MOVE_GASTRO_ACID,
			.Level = 35,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 39,
		},
		{
			.Move = MOVE_SLAM,
			.Level = 41,
		},
		{
			.Move = MOVE_WRING_OUT,
			.Level = 47,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_VICTREEBEL] = {
		{
			.Move = MOVE_STOCKPILE,
			.Level = 1,
		},
		{
			.Move = MOVE_SWALLOW,
			.Level = 1,
		},
		{
			.Move = MOVE_SPIT_UP,
			.Level = 1,
		},
		{
			.Move = MOVE_VINE_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_SLEEP_POWDER,
			.Level = 1,
		},
		{
			.Move = MOVE_SWEET_SCENT,
			.Level = 1,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 1,
		},
		{
			.Move = MOVE_LEAF_TORNADO,
			.Level = 27,
		},
		{
			.Move = MOVE_LEAF_STORM,
			.Level = 47,
		},
		{
			.Move = MOVE_LEAF_BLADE,
			.Level = 47,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_TENTACOOL] = {
		{
			.Move = MOVE_POISON_STING,
			.Level = 1,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 4,
		},
		{
			.Move = MOVE_CONSTRICT,
			.Level = 7,
		},
		{
			.Move = MOVE_ACID,
			.Level = 10,
		},
		{
			.Move = MOVE_TOXIC_SPIKES,
			.Level = 13,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 16,
		},
		{
			.Move = MOVE_WRAP,
			.Level = 19,
		},
		{
			.Move = MOVE_ACID_SPRAY,
			.Level = 22,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 25,
		},
		{
			.Move = MOVE_BARRIER,
			.Level = 28,
		},
		{
			.Move = MOVE_POISON_JAB,
			.Level = 31,
		},
		{
			.Move = MOVE_BRINE,
			.Level = 34,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 37,
		},
		{
			.Move = MOVE_HEX,
			.Level = 40,
		},
		{
			.Move = MOVE_SLUDGE_WAVE,
			.Level = 43,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 46,
		},
		{
			.Move = MOVE_WRING_OUT,
			.Level = 49,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_TENTACRUEL] = {
		{
			.Move = MOVE_REFLECT_TYPE,
			.Level = 1,
		},
		{
			.Move = MOVE_WRING_OUT,
			.Level = 1,
		},
		{
			.Move = MOVE_POISON_STING,
			.Level = 1,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 1,
		},
		{
			.Move = MOVE_CONSTRICT,
			.Level = 1,
		},
		{
			.Move = MOVE_ACID,
			.Level = 1,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 4,
		},
		{
			.Move = MOVE_CONSTRICT,
			.Level = 7,
		},
		{
			.Move = MOVE_ACID,
			.Level = 10,
		},
		{
			.Move = MOVE_TOXIC_SPIKES,
			.Level = 13,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 16,
		},
		{
			.Move = MOVE_WRAP,
			.Level = 19,
		},
		{
			.Move = MOVE_ACID_SPRAY,
			.Level = 22,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 25,
		},
		{
			.Move = MOVE_BARRIER,
			.Level = 28,
		},
		{
			.Move = MOVE_POISON_JAB,
			.Level = 32,
		},
		{
			.Move = MOVE_BRINE,
			.Level = 36,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 40,
		},
		{
			.Move = MOVE_HEX,
			.Level = 44,
		},
		{
			.Move = MOVE_SLUDGE_WAVE,
			.Level = 48,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 52,
		},
		{
			.Move = MOVE_WRING_OUT,
			.Level = 56,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GEODUDE] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 1,
		},
		{
			.Move = MOVE_MUD_SPORT,
			.Level = 4,
		},
		{
			.Move = MOVE_ROCK_POLISH,
			.Level = 6,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 10,
		},
		{
			.Move = MOVE_MAGNITUDE,
			.Level = 12,
		},
		{
			.Move = MOVE_ROCK_THROW,
			.Level = 16,
		},
		{
			.Move = MOVE_SMACK_DOWN,
			.Level = 18,
		},
		{
			.Move = MOVE_BULLDOZE,
			.Level = 22,
		},
		{
			.Move = MOVE_SELFDESTRUCT,
			.Level = 24,
		},
		{
			.Move = MOVE_STEALTH_ROCK,
			.Level = 28,
		},
		{
			.Move = MOVE_ROCK_BLAST,
			.Level = 30,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 34,
		},
		{
			.Move = MOVE_EXPLOSION,
			.Level = 36,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 40,
		},
		{
			.Move = MOVE_STONE_EDGE,
			.Level = 42,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GRAVELER] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 1,
		},
		{
			.Move = MOVE_MUD_SPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_ROCK_POLISH,
			.Level = 1,
		},
		{
			.Move = MOVE_MUD_SPORT,
			.Level = 4,
		},
		{
			.Move = MOVE_ROCK_POLISH,
			.Level = 6,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 10,
		},
		{
			.Move = MOVE_MAGNITUDE,
			.Level = 12,
		},
		{
			.Move = MOVE_ROCK_THROW,
			.Level = 16,
		},
		{
			.Move = MOVE_SMACK_DOWN,
			.Level = 18,
		},
		{
			.Move = MOVE_BULLDOZE,
			.Level = 22,
		},
		{
			.Move = MOVE_SELFDESTRUCT,
			.Level = 24,
		},
		{
			.Move = MOVE_STEALTH_ROCK,
			.Level = 30,
		},
		{
			.Move = MOVE_ROCK_BLAST,
			.Level = 34,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 40,
		},
		{
			.Move = MOVE_EXPLOSION,
			.Level = 44,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 50,
		},
		{
			.Move = MOVE_STONE_EDGE,
			.Level = 54,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GOLEM] = {
		{
			.Move = MOVE_HEAVY_SLAM,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 1,
		},
		{
			.Move = MOVE_MUD_SPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_ROCK_POLISH,
			.Level = 1,
		},
		{
			.Move = MOVE_MUD_SPORT,
			.Level = 4,
		},
		{
			.Move = MOVE_ROCK_POLISH,
			.Level = 6,
		},
		{
			.Move = MOVE_STEAMROLLER,
			.Level = 10,
		},
		{
			.Move = MOVE_MAGNITUDE,
			.Level = 12,
		},
		{
			.Move = MOVE_ROCK_THROW,
			.Level = 16,
		},
		{
			.Move = MOVE_SMACK_DOWN,
			.Level = 18,
		},
		{
			.Move = MOVE_BULLDOZE,
			.Level = 22,
		},
		{
			.Move = MOVE_SELFDESTRUCT,
			.Level = 24,
		},
		{
			.Move = MOVE_STEALTH_ROCK,
			.Level = 30,
		},
		{
			.Move = MOVE_ROCK_BLAST,
			.Level = 34,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 40,
		},
		{
			.Move = MOVE_EXPLOSION,
			.Level = 44,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 50,
		},
		{
			.Move = MOVE_STONE_EDGE,
			.Level = 54,
		},
		{
			.Move = MOVE_HEAVY_SLAM,
			.Level = 60,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PONYTA] = {
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 4,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 9,
		},
		{
			.Move = MOVE_FLAME_WHEEL,
			.Level = 13,
		},
		{
			.Move = MOVE_STOMP,
			.Level = 17,
		},
		{
			.Move = MOVE_FLAME_CHARGE,
			.Level = 21,
		},
		{
			.Move = MOVE_FIRE_SPIN,
			.Level = 25,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 29,
		},
		{
			.Move = MOVE_INFERNO,
			.Level = 33,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 37,
		},
		{
			.Move = MOVE_FIRE_BLAST,
			.Level = 41,
		},
		{
			.Move = MOVE_BOUNCE,
			.Level = 45,
		},
		{
			.Move = MOVE_FLARE_BLITZ,
			.Level = 49,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_RAPIDASH] = {
		{
			.Move = MOVE_POISON_JAB,
			.Level = 1,
		},
		{
			.Move = MOVE_MEGAHORN,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 4,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 9,
		},
		{
			.Move = MOVE_FLAME_WHEEL,
			.Level = 13,
		},
		{
			.Move = MOVE_STOMP,
			.Level = 17,
		},
		{
			.Move = MOVE_FLAME_CHARGE,
			.Level = 21,
		},
		{
			.Move = MOVE_FIRE_SPIN,
			.Level = 25,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 29,
		},
		{
			.Move = MOVE_INFERNO,
			.Level = 33,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 37,
		},
		{
			.Move = MOVE_FURY_ATTACK,
			.Level = 40,
		},
		{
			.Move = MOVE_FIRE_BLAST,
			.Level = 41,
		},
		{
			.Move = MOVE_BOUNCE,
			.Level = 45,
		},
		{
			.Move = MOVE_FLARE_BLITZ,
			.Level = 49,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SLOWPOKE] = {
		{
			.Move = MOVE_CURSE,
			.Level = 1,
		},
		{
			.Move = MOVE_YAWN,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 5,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 9,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 14,
		},
		{
			.Move = MOVE_DISABLE,
			.Level = 19,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 23,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 28,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 32,
		},
		{
			.Move = MOVE_SLACK_OFF,
			.Level = 36,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 41,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 45,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 49,
		},
		{
			.Move = MOVE_PSYCH_UP,
			.Level = 54,
		},
		{
			.Move = MOVE_HEAL_PULSE,
			.Level = 58,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SLOWBRO] = {
		{
			.Move = MOVE_HEAL_PULSE,
			.Level = 1,
		},
		{
			.Move = MOVE_CURSE,
			.Level = 1,
		},
		{
			.Move = MOVE_YAWN,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 5,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 9,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 14,
		},
		{
			.Move = MOVE_DISABLE,
			.Level = 19,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 23,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 28,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 32,
		},
		{
			.Move = MOVE_SLACK_OFF,
			.Level = 36,
		},
		{
			.Move = MOVE_WITHDRAW,
			.Level = 37,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 43,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 49,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 55,
		},
		{
			.Move = MOVE_PSYCH_UP,
			.Level = 62,
		},
		{
			.Move = MOVE_HEAL_PULSE,
			.Level = 68,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MAGNEMITE] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 5,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 7,
		},
		{
			.Move = MOVE_SONICBOOM,
			.Level = 11,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 13,
		},
		{
			.Move = MOVE_MAGNET_BOMB,
			.Level = 17,
		},
		{
			.Move = MOVE_SPARK,
			.Level = 19,
		},
		{
			.Move = MOVE_MIRROR_SHOT,
			.Level = 23,
		},
		{
			.Move = MOVE_METAL_SOUND,
			.Level = 25,
		},
		{
			.Move = MOVE_ELECTRO_BALL,
			.Level = 29,
		},
		{
			.Move = MOVE_FLASH_CANNON,
			.Level = 31,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 35,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 37,
		},
		{
			.Move = MOVE_LOCKON,
			.Level = 41,
		},
		{
			.Move = MOVE_MAGNET_RISE,
			.Level = 43,
		},
		{
			.Move = MOVE_GYRO_BALL,
			.Level = 47,
		},
		{
			.Move = MOVE_ZAP_CANNON,
			.Level = 49,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MAGNETON] = {
		{
			.Move = MOVE_ZAP_CANNON,
			.Level = 1,
		},
		{
			.Move = MOVE_ELECTRIC_TERRAIN,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 1,
		},
		{
			.Move = MOVE_SONICBOOM,
			.Level = 1,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 5,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 7,
		},
		{
			.Move = MOVE_SONICBOOM,
			.Level = 11,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 13,
		},
		{
			.Move = MOVE_MAGNET_BOMB,
			.Level = 17,
		},
		{
			.Move = MOVE_SPARK,
			.Level = 19,
		},
		{
			.Move = MOVE_MIRROR_SHOT,
			.Level = 23,
		},
		{
			.Move = MOVE_METAL_SOUND,
			.Level = 25,
		},
		{
			.Move = MOVE_ELECTRO_BALL,
			.Level = 29,
		},
		{
			.Move = MOVE_TRI_ATTACK,
			.Level = 30,
		},
		{
			.Move = MOVE_FLASH_CANNON,
			.Level = 33,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 39,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 43,
		},
		{
			.Move = MOVE_LOCKON,
			.Level = 49,
		},
		{
			.Move = MOVE_MAGNET_RISE,
			.Level = 53,
		},
		{
			.Move = MOVE_GYRO_BALL,
			.Level = 59,
		},
		{
			.Move = MOVE_ZAP_CANNON,
			.Level = 63,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_FARFETCHD] = {
		{
			.Move = MOVE_BRAVE_BIRD,
			.Level = 1,
		},
		{
			.Move = MOVE_POISON_JAB,
			.Level = 1,
		},
		{
			.Move = MOVE_PECK,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_FURY_CUTTER,
			.Level = 1,
		},
		{
			.Move = MOVE_FURY_ATTACK,
			.Level = 7,
		},
		{
			.Move = MOVE_AERIAL_ACE,
			.Level = 9,
		},
		{
			.Move = MOVE_KNOCK_OFF,
			.Level = 13,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 19,
		},
		{
			.Move = MOVE_AIR_CUTTER,
			.Level = 21,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 25,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 31,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 33,
		},
		{
			.Move = MOVE_ACROBATICS,
			.Level = 37,
		},
		{
			.Move = MOVE_FEINT,
			.Level = 43,
		},
		{
			.Move = MOVE_FALSE_SWIPE,
			.Level = 45,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 49,
		},
		{
			.Move = MOVE_BRAVE_BIRD,
			.Level = 55,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_DODUO] = {
		{
			.Move = MOVE_PECK,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 5,
		},
		{
			.Move = MOVE_RAGE,
			.Level = 9,
		},
		{
			.Move = MOVE_FURY_ATTACK,
			.Level = 13,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 17,
		},
		{
			.Move = MOVE_PLUCK,
			.Level = 21,
		},
		{
			.Move = MOVE_DOUBLE_HIT,
			.Level = 25,
		},
		{
			.Move = MOVE_ACUPRESSURE,
			.Level = 29,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 33,
		},
		{
			.Move = MOVE_DRILL_PECK,
			.Level = 37,
		},
		{
			.Move = MOVE_UPROAR,
			.Level = 41,
		},
		{
			.Move = MOVE_ENDEAVOR,
			.Level = 45,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 49,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_DODRIO] = {
		{
			.Move = MOVE_PECK,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_RAGE,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 5,
		},
		{
			.Move = MOVE_RAGE,
			.Level = 9,
		},
		{
			.Move = MOVE_FURY_ATTACK,
			.Level = 13,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 17,
		},
		{
			.Move = MOVE_PLUCK,
			.Level = 21,
		},
		{
			.Move = MOVE_TRI_ATTACK,
			.Level = 25,
		},
		{
			.Move = MOVE_ACUPRESSURE,
			.Level = 29,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 35,
		},
		{
			.Move = MOVE_DRILL_PECK,
			.Level = 41,
		},
		{
			.Move = MOVE_UPROAR,
			.Level = 47,
		},
		{
			.Move = MOVE_ENDEAVOR,
			.Level = 53,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 59,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SEEL] = {
		{
			.Move = MOVE_HEADBUTT,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 3,
		},
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 7,
		},
		{
			.Move = MOVE_ICY_WIND,
			.Level = 11,
		},
		{
			.Move = MOVE_ENCORE,
			.Level = 13,
		},
		{
			.Move = MOVE_ICE_SHARD,
			.Level = 17,
		},
		{
			.Move = MOVE_REST,
			.Level = 21,
		},
		{
			.Move = MOVE_AQUA_RING,
			.Level = 23,
		},
		{
			.Move = MOVE_AURORA_BEAM,
			.Level = 27,
		},
		{
			.Move = MOVE_AQUA_JET,
			.Level = 31,
		},
		{
			.Move = MOVE_BRINE,
			.Level = 33,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 37,
		},
		{
			.Move = MOVE_DIVE,
			.Level = 41,
		},
		{
			.Move = MOVE_AQUA_TAIL,
			.Level = 43,
		},
		{
			.Move = MOVE_ICE_BEAM,
			.Level = 47,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 51,
		},
		{
			.Move = MOVE_HAIL,
			.Level = 53,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_DEWGONG] = {
		{
			.Move = MOVE_HEADBUTT,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_SIGNAL_BEAM,
			.Level = 1,
		},
		{
			.Move = MOVE_ICY_WIND,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 3,
		},
		{
			.Move = MOVE_SIGNAL_BEAM,
			.Level = 7,
		},
		{
			.Move = MOVE_ICY_WIND,
			.Level = 11,
		},
		{
			.Move = MOVE_ENCORE,
			.Level = 13,
		},
		{
			.Move = MOVE_ICE_SHARD,
			.Level = 17,
		},
		{
			.Move = MOVE_REST,
			.Level = 21,
		},
		{
			.Move = MOVE_AQUA_RING,
			.Level = 23,
		},
		{
			.Move = MOVE_AURORA_BEAM,
			.Level = 27,
		},
		{
			.Move = MOVE_AQUA_JET,
			.Level = 31,
		},
		{
			.Move = MOVE_BRINE,
			.Level = 33,
		},
		{
			.Move = MOVE_SHEER_COLD,
			.Level = 34,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 39,
		},
		{
			.Move = MOVE_DIVE,
			.Level = 45,
		},
		{
			.Move = MOVE_AQUA_TAIL,
			.Level = 49,
		},
		{
			.Move = MOVE_ICE_BEAM,
			.Level = 55,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 61,
		},
		{
			.Move = MOVE_HAIL,
			.Level = 65,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GRIMER] = {
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_POISON_GAS,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 4,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 7,
		},
		{
			.Move = MOVE_DISABLE,
			.Level = 12,
		},
		{
			.Move = MOVE_SLUDGE,
			.Level = 15,
		},
		{
			.Move = MOVE_MUD_BOMB,
			.Level = 18,
		},
		{
			.Move = MOVE_MINIMIZE,
			.Level = 21,
		},
		{
			.Move = MOVE_FLING,
			.Level = 26,
		},
		{
			.Move = MOVE_SLUDGE_BOMB,
			.Level = 29,
		},
		{
			.Move = MOVE_SLUDGE_WAVE,
			.Level = 32,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 37,
		},
		{
			.Move = MOVE_GUNK_SHOT,
			.Level = 40,
		},
		{
			.Move = MOVE_ACID_ARMOR,
			.Level = 43,
		},
		{
			.Move = MOVE_BELCH,
			.Level = 46,
		},
		{
			.Move = MOVE_MEMENTO,
			.Level = 48,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MUK] = {
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_POISON_GAS,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 1,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 4,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 7,
		},
		{
			.Move = MOVE_DISABLE,
			.Level = 12,
		},
		{
			.Move = MOVE_SLUDGE,
			.Level = 15,
		},
		{
			.Move = MOVE_MUD_BOMB,
			.Level = 18,
		},
		{
			.Move = MOVE_MINIMIZE,
			.Level = 21,
		},
		{
			.Move = MOVE_FLING,
			.Level = 26,
		},
		{
			.Move = MOVE_SLUDGE_BOMB,
			.Level = 29,
		},
		{
			.Move = MOVE_SLUDGE_WAVE,
			.Level = 32,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 37,
		},
		{
			.Move = MOVE_VENOM_DRENCH,
			.Level = 38,
		},
		{
			.Move = MOVE_GUNK_SHOT,
			.Level = 40,
		},
		{
			.Move = MOVE_ACID_ARMOR,
			.Level = 46,
		},
		{
			.Move = MOVE_BELCH,
			.Level = 52,
		},
		{
			.Move = MOVE_MEMENTO,
			.Level = 57,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SHELLDER] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_WITHDRAW,
			.Level = 4,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 8,
		},
		{
			.Move = MOVE_ICICLE_SPEAR,
			.Level = 13,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 16,
		},
		{
			.Move = MOVE_LEER,
			.Level = 20,
		},
		{
			.Move = MOVE_CLAMP,
			.Level = 25,
		},
		{
			.Move = MOVE_ICE_SHARD,
			.Level = 28,
		},
		{
			.Move = MOVE_RAZOR_SHELL,
			.Level = 32,
		},
		{
			.Move = MOVE_AURORA_BEAM,
			.Level = 37,
		},
		{
			.Move = MOVE_WHIRLPOOL,
			.Level = 40,
		},
		{
			.Move = MOVE_BRINE,
			.Level = 44,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 49,
		},
		{
			.Move = MOVE_ICE_BEAM,
			.Level = 52,
		},
		{
			.Move = MOVE_SHELL_SMASH,
			.Level = 56,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 61,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CLOYSTER] = {
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 1,
		},
		{
			.Move = MOVE_SHELL_SMASH,
			.Level = 1,
		},
		{
			.Move = MOVE_TOXIC_SPIKES,
			.Level = 1,
		},
		{
			.Move = MOVE_WITHDRAW,
			.Level = 1,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 1,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 1,
		},
		{
			.Move = MOVE_AURORA_BEAM,
			.Level = 1,
		},
		{
			.Move = MOVE_SPIKE_CANNON,
			.Level = 13,
		},
		{
			.Move = MOVE_SPIKES,
			.Level = 28,
		},
		{
			.Move = MOVE_ICICLE_CRASH,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GASTLY] = {
		{
			.Move = MOVE_HYPNOSIS,
			.Level = 1,
		},
		{
			.Move = MOVE_LICK,
			.Level = 1,
		},
		{
			.Move = MOVE_SPITE,
			.Level = 5,
		},
		{
			.Move = MOVE_MEAN_LOOK,
			.Level = 8,
		},
		{
			.Move = MOVE_CURSE,
			.Level = 12,
		},
		{
			.Move = MOVE_NIGHT_SHADE,
			.Level = 15,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 19,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 22,
		},
		{
			.Move = MOVE_PAYBACK,
			.Level = 26,
		},
		{
			.Move = MOVE_SHADOW_BALL,
			.Level = 29,
		},
		{
			.Move = MOVE_DREAM_EATER,
			.Level = 33,
		},
		{
			.Move = MOVE_DARK_PULSE,
			.Level = 36,
		},
		{
			.Move = MOVE_DESTINY_BOND,
			.Level = 40,
		},
		{
			.Move = MOVE_HEX,
			.Level = 43,
		},
		{
			.Move = MOVE_NIGHTMARE,
			.Level = 47,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_HAUNTER] = {
		{
			.Move = MOVE_HYPNOSIS,
			.Level = 1,
		},
		{
			.Move = MOVE_LICK,
			.Level = 1,
		},
		{
			.Move = MOVE_SPITE,
			.Level = 1,
		},
		{
			.Move = MOVE_SPITE,
			.Level = 5,
		},
		{
			.Move = MOVE_MEAN_LOOK,
			.Level = 8,
		},
		{
			.Move = MOVE_CURSE,
			.Level = 12,
		},
		{
			.Move = MOVE_NIGHT_SHADE,
			.Level = 15,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 19,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 22,
		},
		{
			.Move = MOVE_SHADOW_PUNCH,
			.Level = 25,
		},
		{
			.Move = MOVE_PAYBACK,
			.Level = 28,
		},
		{
			.Move = MOVE_SHADOW_BALL,
			.Level = 33,
		},
		{
			.Move = MOVE_DREAM_EATER,
			.Level = 39,
		},
		{
			.Move = MOVE_DARK_PULSE,
			.Level = 44,
		},
		{
			.Move = MOVE_DESTINY_BOND,
			.Level = 50,
		},
		{
			.Move = MOVE_HEX,
			.Level = 55,
		},
		{
			.Move = MOVE_NIGHTMARE,
			.Level = 61,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GENGAR] = {
		{
			.Move = MOVE_HYPNOSIS,
			.Level = 1,
		},
		{
			.Move = MOVE_LICK,
			.Level = 1,
		},
		{
			.Move = MOVE_SPITE,
			.Level = 1,
		},
		{
			.Move = MOVE_SPITE,
			.Level = 5,
		},
		{
			.Move = MOVE_MEAN_LOOK,
			.Level = 8,
		},
		{
			.Move = MOVE_CURSE,
			.Level = 12,
		},
		{
			.Move = MOVE_NIGHT_SHADE,
			.Level = 15,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 19,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 22,
		},
		{
			.Move = MOVE_SHADOW_PUNCH,
			.Level = 25,
		},
		{
			.Move = MOVE_PAYBACK,
			.Level = 28,
		},
		{
			.Move = MOVE_SHADOW_BALL,
			.Level = 33,
		},
		{
			.Move = MOVE_DREAM_EATER,
			.Level = 39,
		},
		{
			.Move = MOVE_DARK_PULSE,
			.Level = 44,
		},
		{
			.Move = MOVE_DESTINY_BOND,
			.Level = 50,
		},
		{
			.Move = MOVE_HEX,
			.Level = 55,
		},
		{
			.Move = MOVE_NIGHTMARE,
			.Level = 61,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ONIX] = {
		{
			.Move = MOVE_MUD_SPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 1,
		},
		{
			.Move = MOVE_BIND,
			.Level = 1,
		},
		{
			.Move = MOVE_CURSE,
			.Level = 4,
		},
		{
			.Move = MOVE_ROCK_THROW,
			.Level = 7,
		},
		{
			.Move = MOVE_ROCK_TOMB,
			.Level = 10,
		},
		{
			.Move = MOVE_RAGE,
			.Level = 13,
		},
		{
			.Move = MOVE_STEALTH_ROCK,
			.Level = 16,
		},
		{
			.Move = MOVE_ROCK_POLISH,
			.Level = 19,
		},
		{
			.Move = MOVE_GYRO_BALL,
			.Level = 20,
		},
		{
			.Move = MOVE_SMACK_DOWN,
			.Level = 22,
		},
		{
			.Move = MOVE_DRAGONBREATH,
			.Level = 25,
		},
		{
			.Move = MOVE_SLAM,
			.Level = 28,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 31,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 34,
		},
		{
			.Move = MOVE_SAND_TOMB,
			.Level = 37,
		},
		{
			.Move = MOVE_IRON_TAIL,
			.Level = 40,
		},
		{
			.Move = MOVE_DIG,
			.Level = 43,
		},
		{
			.Move = MOVE_STONE_EDGE,
			.Level = 46,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 49,
		},
		{
			.Move = MOVE_SANDSTORM,
			.Level = 52,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_DROWZEE] = {
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_HYPNOSIS,
			.Level = 1,
		},
		{
			.Move = MOVE_DISABLE,
			.Level = 5,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 9,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 13,
		},
		{
			.Move = MOVE_POISON_GAS,
			.Level = 17,
		},
		{
			.Move = MOVE_MEDITATE,
			.Level = 21,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 25,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 29,
		},
		{
			.Move = MOVE_PSYCH_UP,
			.Level = 33,
		},
		{
			.Move = MOVE_SYNCHRONOISE,
			.Level = 37,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 41,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 45,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 49,
		},
		{
			.Move = MOVE_NASTY_PLOT,
			.Level = 53,
		},
		{
			.Move = MOVE_PSYSHOCK,
			.Level = 57,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 61,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_HYPNO] = {
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 1,
		},
		{
			.Move = MOVE_NASTY_PLOT,
			.Level = 1,
		},
		{
			.Move = MOVE_NIGHTMARE,
			.Level = 1,
		},
		{
			.Move = MOVE_SWITCHEROO,
			.Level = 1,
		},
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_HYPNOSIS,
			.Level = 1,
		},
		{
			.Move = MOVE_DISABLE,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_DISABLE,
			.Level = 5,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 9,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 13,
		},
		{
			.Move = MOVE_POISON_GAS,
			.Level = 17,
		},
		{
			.Move = MOVE_MEDITATE,
			.Level = 21,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 25,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 29,
		},
		{
			.Move = MOVE_PSYCH_UP,
			.Level = 33,
		},
		{
			.Move = MOVE_SYNCHRONOISE,
			.Level = 37,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 41,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 45,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 49,
		},
		{
			.Move = MOVE_NASTY_PLOT,
			.Level = 53,
		},
		{
			.Move = MOVE_PSYSHOCK,
			.Level = 57,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 61,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_KRABBY] = {
		{
			.Move = MOVE_MUD_SPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_BUBBLE,
			.Level = 1,
		},
		{
			.Move = MOVE_VICEGRIP,
			.Level = 5,
		},
		{
			.Move = MOVE_LEER,
			.Level = 9,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 11,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 15,
		},
		{
			.Move = MOVE_MUD_SHOT,
			.Level = 19,
		},
		{
			.Move = MOVE_METAL_CLAW,
			.Level = 21,
		},
		{
			.Move = MOVE_STOMP,
			.Level = 25,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 29,
		},
		{
			.Move = MOVE_GUILLOTINE,
			.Level = 31,
		},
		{
			.Move = MOVE_SLAM,
			.Level = 35,
		},
		{
			.Move = MOVE_BRINE,
			.Level = 39,
		},
		{
			.Move = MOVE_CRABHAMMER,
			.Level = 41,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 45,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_KINGLER] = {
		{
			.Move = MOVE_WIDE_GUARD,
			.Level = 1,
		},
		{
			.Move = MOVE_MUD_SPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_BUBBLE,
			.Level = 1,
		},
		{
			.Move = MOVE_VICEGRIP,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_VICEGRIP,
			.Level = 5,
		},
		{
			.Move = MOVE_LEER,
			.Level = 9,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 11,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 15,
		},
		{
			.Move = MOVE_MUD_SHOT,
			.Level = 19,
		},
		{
			.Move = MOVE_METAL_CLAW,
			.Level = 21,
		},
		{
			.Move = MOVE_STOMP,
			.Level = 25,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 32,
		},
		{
			.Move = MOVE_GUILLOTINE,
			.Level = 37,
		},
		{
			.Move = MOVE_SLAM,
			.Level = 44,
		},
		{
			.Move = MOVE_BRINE,
			.Level = 51,
		},
		{
			.Move = MOVE_CRABHAMMER,
			.Level = 56,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 63,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_VOLTORB] = {
		{
			.Move = MOVE_CHARGE,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_SONICBOOM,
			.Level = 4,
		},
		{
			.Move = MOVE_EERIE_IMPULSE,
			.Level = 6,
		},
		{
			.Move = MOVE_SPARK,
			.Level = 9,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 11,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 13,
		},
		{
			.Move = MOVE_CHARGE_BEAM,
			.Level = 16,
		},
		{
			.Move = MOVE_SWIFT,
			.Level = 20,
		},
		{
			.Move = MOVE_ELECTRO_BALL,
			.Level = 22,
		},
		{
			.Move = MOVE_SELFDESTRUCT,
			.Level = 26,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 29,
		},
		{
			.Move = MOVE_MAGNET_RISE,
			.Level = 34,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 37,
		},
		{
			.Move = MOVE_EXPLOSION,
			.Level = 41,
		},
		{
			.Move = MOVE_GYRO_BALL,
			.Level = 46,
		},
		{
			.Move = MOVE_MIRROR_COAT,
			.Level = 48,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ELECTRODE] = {
		{
			.Move = MOVE_MAGNETIC_FLUX,
			.Level = 1,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_SONICBOOM,
			.Level = 1,
		},
		{
			.Move = MOVE_SPARK,
			.Level = 1,
		},
		{
			.Move = MOVE_SONICBOOM,
			.Level = 4,
		},
		{
			.Move = MOVE_EERIE_IMPULSE,
			.Level = 6,
		},
		{
			.Move = MOVE_SPARK,
			.Level = 9,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 11,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 13,
		},
		{
			.Move = MOVE_CHARGE_BEAM,
			.Level = 16,
		},
		{
			.Move = MOVE_SWIFT,
			.Level = 20,
		},
		{
			.Move = MOVE_ELECTRO_BALL,
			.Level = 22,
		},
		{
			.Move = MOVE_SELFDESTRUCT,
			.Level = 26,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 29,
		},
		{
			.Move = MOVE_MAGNET_RISE,
			.Level = 36,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 41,
		},
		{
			.Move = MOVE_EXPLOSION,
			.Level = 47,
		},
		{
			.Move = MOVE_GYRO_BALL,
			.Level = 54,
		},
		{
			.Move = MOVE_MIRROR_COAT,
			.Level = 58,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_EXEGGCUTE] = {
		{
			.Move = MOVE_BARRAGE,
			.Level = 1,
		},
		{
			.Move = MOVE_UPROAR,
			.Level = 1,
		},
		{
			.Move = MOVE_HYPNOSIS,
			.Level = 1,
		},
		{
			.Move = MOVE_REFLECT,
			.Level = 7,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 11,
		},
		{
			.Move = MOVE_BULLET_SEED,
			.Level = 17,
		},
		{
			.Move = MOVE_STUN_SPORE,
			.Level = 19,
		},
		{
			.Move = MOVE_POISONPOWDER,
			.Level = 21,
		},
		{
			.Move = MOVE_SLEEP_POWDER,
			.Level = 23,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 27,
		},
		{
			.Move = MOVE_WORRY_SEED,
			.Level = 33,
		},
		{
			.Move = MOVE_NATURAL_GIFT,
			.Level = 37,
		},
		{
			.Move = MOVE_SOLARBEAM,
			.Level = 43,
		},
		{
			.Move = MOVE_EXTRASENSORY,
			.Level = 47,
		},
		{
			.Move = MOVE_BESTOW,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_EXEGGUTOR] = {
		{
			.Move = MOVE_SEED_BOMB,
			.Level = 1,
		},
		{
			.Move = MOVE_BARRAGE,
			.Level = 1,
		},
		{
			.Move = MOVE_HYPNOSIS,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_STOMP,
			.Level = 1,
		},
		{
			.Move = MOVE_PSYSHOCK,
			.Level = 17,
		},
		{
			.Move = MOVE_EGG_BOMB,
			.Level = 27,
		},
		{
			.Move = MOVE_WOOD_HAMMER,
			.Level = 37,
		},
		{
			.Move = MOVE_LEAF_STORM,
			.Level = 47,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CUBONE] = {
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 3,
		},
		{
			.Move = MOVE_BONE_CLUB,
			.Level = 7,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 11,
		},
		{
			.Move = MOVE_LEER,
			.Level = 13,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 17,
		},
		{
			.Move = MOVE_BONEMERANG,
			.Level = 21,
		},
		{
			.Move = MOVE_RAGE,
			.Level = 23,
		},
		{
			.Move = MOVE_FALSE_SWIPE,
			.Level = 27,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 31,
		},
		{
			.Move = MOVE_FLING,
			.Level = 33,
		},
		{
			.Move = MOVE_BONE_RUSH,
			.Level = 37,
		},
		{
			.Move = MOVE_ENDEAVOR,
			.Level = 41,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 43,
		},
		{
			.Move = MOVE_RETALIATE,
			.Level = 47,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MAROWAK] = {
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_BONE_CLUB,
			.Level = 1,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 3,
		},
		{
			.Move = MOVE_BONE_CLUB,
			.Level = 7,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 11,
		},
		{
			.Move = MOVE_LEER,
			.Level = 13,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 17,
		},
		{
			.Move = MOVE_BONEMERANG,
			.Level = 21,
		},
		{
			.Move = MOVE_RAGE,
			.Level = 23,
		},
		{
			.Move = MOVE_FALSE_SWIPE,
			.Level = 27,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 33,
		},
		{
			.Move = MOVE_FLING,
			.Level = 37,
		},
		{
			.Move = MOVE_BONE_RUSH,
			.Level = 43,
		},
		{
			.Move = MOVE_ENDEAVOR,
			.Level = 49,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 53,
		},
		{
			.Move = MOVE_RETALIATE,
			.Level = 59,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_HITMONLEE] = {
		{
			.Move = MOVE_REVERSAL,
			.Level = 1,
		},
		{
			.Move = MOVE_CLOSE_COMBAT,
			.Level = 1,
		},
		{
			.Move = MOVE_MEGA_KICK,
			.Level = 1,
		},
		{
			.Move = MOVE_REVENGE,
			.Level = 1,
		},
		{
			.Move = MOVE_DOUBLE_KICK,
			.Level = 1,
		},
		{
			.Move = MOVE_MEDITATE,
			.Level = 5,
		},
		{
			.Move = MOVE_ROLLING_KICK,
			.Level = 9,
		},
		{
			.Move = MOVE_JUMP_KICK,
			.Level = 13,
		},
		{
			.Move = MOVE_BRICK_BREAK,
			.Level = 17,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 21,
		},
		{
			.Move = MOVE_FEINT,
			.Level = 25,
		},
		{
			.Move = MOVE_HI_JUMP_KICK,
			.Level = 29,
		},
		{
			.Move = MOVE_MIND_READER,
			.Level = 33,
		},
		{
			.Move = MOVE_FORESIGHT,
			.Level = 37,
		},
		{
			.Move = MOVE_WIDE_GUARD,
			.Level = 41,
		},
		{
			.Move = MOVE_BLAZE_KICK,
			.Level = 45,
		},
		{
			.Move = MOVE_ENDURE,
			.Level = 49,
		},
		{
			.Move = MOVE_MEGA_KICK,
			.Level = 53,
		},
		{
			.Move = MOVE_CLOSE_COMBAT,
			.Level = 57,
		},
		{
			.Move = MOVE_REVERSAL,
			.Level = 61,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_HITMONCHAN] = {
		{
			.Move = MOVE_CLOSE_COMBAT,
			.Level = 1,
		},
		{
			.Move = MOVE_COUNTER,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_PUNCH,
			.Level = 1,
		},
		{
			.Move = MOVE_REVENGE,
			.Level = 1,
		},
		{
			.Move = MOVE_COMET_PUNCH,
			.Level = 1,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 6,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 11,
		},
		{
			.Move = MOVE_MACH_PUNCH,
			.Level = 16,
		},
		{
			.Move = MOVE_BULLET_PUNCH,
			.Level = 16,
		},
		{
			.Move = MOVE_FEINT,
			.Level = 21,
		},
		{
			.Move = MOVE_VACUUM_WAVE,
			.Level = 26,
		},
		{
			.Move = MOVE_QUICK_GUARD,
			.Level = 31,
		},
		{
			.Move = MOVE_THUNDERPUNCH,
			.Level = 36,
		},
		{
			.Move = MOVE_ICE_PUNCH,
			.Level = 36,
		},
		{
			.Move = MOVE_FIRE_PUNCH,
			.Level = 36,
		},
		{
			.Move = MOVE_SKY_UPPERCUT,
			.Level = 41,
		},
		{
			.Move = MOVE_MEGA_PUNCH,
			.Level = 46,
		},
		{
			.Move = MOVE_DETECT,
			.Level = 50,
		},
		{
			.Move = MOVE_FOCUS_PUNCH,
			.Level = 56,
		},
		{
			.Move = MOVE_COUNTER,
			.Level = 61,
		},
		{
			.Move = MOVE_CLOSE_COMBAT,
			.Level = 66,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_LICKITUNG] = {
		{
			.Move = MOVE_LICK,
			.Level = 1,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 5,
		},
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 9,
		},
		{
			.Move = MOVE_KNOCK_OFF,
			.Level = 13,
		},
		{
			.Move = MOVE_WRAP,
			.Level = 17,
		},
		{
			.Move = MOVE_STOMP,
			.Level = 21,
		},
		{
			.Move = MOVE_DISABLE,
			.Level = 25,
		},
		{
			.Move = MOVE_SLAM,
			.Level = 29,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 33,
		},
		{
			.Move = MOVE_CHIP_AWAY,
			.Level = 37,
		},
		{
			.Move = MOVE_ME_FIRST,
			.Level = 41,
		},
		{
			.Move = MOVE_REFRESH,
			.Level = 45,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 49,
		},
		{
			.Move = MOVE_POWER_WHIP,
			.Level = 53,
		},
		{
			.Move = MOVE_WRING_OUT,
			.Level = 57,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_KOFFING] = {
		{
			.Move = MOVE_POISON_GAS,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_SMOG,
			.Level = 4,
		},
		{
			.Move = MOVE_SMOKESCREEN,
			.Level = 7,
		},
		{
			.Move = MOVE_ASSURANCE,
			.Level = 12,
		},
		{
			.Move = MOVE_CLEAR_SMOG,
			.Level = 15,
		},
		{
			.Move = MOVE_SLUDGE,
			.Level = 18,
		},
		{
			.Move = MOVE_SELFDESTRUCT,
			.Level = 23,
		},
		{
			.Move = MOVE_HAZE,
			.Level = 26,
		},
		{
			.Move = MOVE_GYRO_BALL,
			.Level = 29,
		},
		{
			.Move = MOVE_SLUDGE_BOMB,
			.Level = 34,
		},
		{
			.Move = MOVE_EXPLOSION,
			.Level = 37,
		},
		{
			.Move = MOVE_DESTINY_BOND,
			.Level = 40,
		},
		{
			.Move = MOVE_BELCH,
			.Level = 42,
		},
		{
			.Move = MOVE_MEMENTO,
			.Level = 45,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_WEEZING] = {
		{
			.Move = MOVE_POISON_GAS,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_SMOG,
			.Level = 1,
		},
		{
			.Move = MOVE_SMOKESCREEN,
			.Level = 1,
		},
		{
			.Move = MOVE_SMOG,
			.Level = 4,
		},
		{
			.Move = MOVE_SMOKESCREEN,
			.Level = 7,
		},
		{
			.Move = MOVE_ASSURANCE,
			.Level = 12,
		},
		{
			.Move = MOVE_CLEAR_SMOG,
			.Level = 15,
		},
		{
			.Move = MOVE_SLUDGE,
			.Level = 18,
		},
		{
			.Move = MOVE_SELFDESTRUCT,
			.Level = 23,
		},
		{
			.Move = MOVE_HAZE,
			.Level = 26,
		},
		{
			.Move = MOVE_DOUBLE_HIT,
			.Level = 29,
		},
		{
			.Move = MOVE_SLUDGE_BOMB,
			.Level = 34,
		},
		{
			.Move = MOVE_EXPLOSION,
			.Level = 40,
		},
		{
			.Move = MOVE_DESTINY_BOND,
			.Level = 46,
		},
		{
			.Move = MOVE_BELCH,
			.Level = 51,
		},
		{
			.Move = MOVE_MEMENTO,
			.Level = 57,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_RHYHORN] = {
		{
			.Move = MOVE_HORN_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_FURY_ATTACK,
			.Level = 5,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 9,
		},
		{
			.Move = MOVE_SMACK_DOWN,
			.Level = 13,
		},
		{
			.Move = MOVE_STOMP,
			.Level = 17,
		},
		{
			.Move = MOVE_BULLDOZE,
			.Level = 21,
		},
		{
			.Move = MOVE_CHIP_AWAY,
			.Level = 25,
		},
		{
			.Move = MOVE_ROCK_BLAST,
			.Level = 29,
		},
		{
			.Move = MOVE_DRILL_RUN,
			.Level = 33,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 37,
		},
		{
			.Move = MOVE_STONE_EDGE,
			.Level = 41,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 45,
		},
		{
			.Move = MOVE_MEGAHORN,
			.Level = 49,
		},
		{
			.Move = MOVE_HORN_DRILL,
			.Level = 53,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_RHYDON] = {
		{
			.Move = MOVE_HORN_DRILL,
			.Level = 1,
		},
		{
			.Move = MOVE_HORN_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_FURY_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 1,
		},
		{
			.Move = MOVE_FURY_ATTACK,
			.Level = 5,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 9,
		},
		{
			.Move = MOVE_SMACK_DOWN,
			.Level = 13,
		},
		{
			.Move = MOVE_STOMP,
			.Level = 17,
		},
		{
			.Move = MOVE_BULLDOZE,
			.Level = 21,
		},
		{
			.Move = MOVE_CHIP_AWAY,
			.Level = 25,
		},
		{
			.Move = MOVE_ROCK_BLAST,
			.Level = 29,
		},
		{
			.Move = MOVE_DRILL_RUN,
			.Level = 33,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 37,
		},
		{
			.Move = MOVE_STONE_EDGE,
			.Level = 41,
		},
		{
			.Move = MOVE_HAMMER_ARM,
			.Level = 42,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 48,
		},
		{
			.Move = MOVE_MEGAHORN,
			.Level = 55,
		},
		{
			.Move = MOVE_HORN_DRILL,
			.Level = 62,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CHANSEY] = {
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 1,
		},
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 1,
		},
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 5,
		},
		{
			.Move = MOVE_REFRESH,
			.Level = 9,
		},
		{
			.Move = MOVE_DOUBLESLAP,
			.Level = 12,
		},
		{
			.Move = MOVE_SOFTBOILED,
			.Level = 16,
		},
		{
			.Move = MOVE_BESTOW,
			.Level = 20,
		},
		{
			.Move = MOVE_MINIMIZE,
			.Level = 23,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 27,
		},
		{
			.Move = MOVE_SING,
			.Level = 31,
		},
		{
			.Move = MOVE_FLING,
			.Level = 34,
		},
		{
			.Move = MOVE_HEAL_PULSE,
			.Level = 38,
		},
		{
			.Move = MOVE_EGG_BOMB,
			.Level = 42,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 46,
		},
		{
			.Move = MOVE_HEALING_WISH,
			.Level = 50,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 54,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_TANGELA] = {
		{
			.Move = MOVE_INGRAIN,
			.Level = 1,
		},
		{
			.Move = MOVE_CONSTRICT,
			.Level = 1,
		},
		{
			.Move = MOVE_SLEEP_POWDER,
			.Level = 4,
		},
		{
			.Move = MOVE_VINE_WHIP,
			.Level = 7,
		},
		{
			.Move = MOVE_ABSORB,
			.Level = 10,
		},
		{
			.Move = MOVE_POISONPOWDER,
			.Level = 14,
		},
		{
			.Move = MOVE_BIND,
			.Level = 17,
		},
		{
			.Move = MOVE_GROWTH,
			.Level = 20,
		},
		{
			.Move = MOVE_MEGA_DRAIN,
			.Level = 23,
		},
		{
			.Move = MOVE_KNOCK_OFF,
			.Level = 27,
		},
		{
			.Move = MOVE_STUN_SPORE,
			.Level = 30,
		},
		{
			.Move = MOVE_NATURAL_GIFT,
			.Level = 33,
		},
		{
			.Move = MOVE_GIGA_DRAIN,
			.Level = 36,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 38,
		},
		{
			.Move = MOVE_SLAM,
			.Level = 41,
		},
		{
			.Move = MOVE_TICKLE,
			.Level = 44,
		},
		{
			.Move = MOVE_WRING_OUT,
			.Level = 46,
		},
		{
			.Move = MOVE_GRASSY_TERRAIN,
			.Level = 48,
		},
		{
			.Move = MOVE_POWER_WHIP,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_KANGASKHAN] = {
		{
			.Move = MOVE_COMET_PUNCH,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_FAKE_OUT,
			.Level = 7,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 10,
		},
		{
			.Move = MOVE_BITE,
			.Level = 13,
		},
		{
			.Move = MOVE_DOUBLE_HIT,
			.Level = 19,
		},
		{
			.Move = MOVE_RAGE,
			.Level = 22,
		},
		{
			.Move = MOVE_MEGA_PUNCH,
			.Level = 25,
		},
		{
			.Move = MOVE_CHIP_AWAY,
			.Level = 31,
		},
		{
			.Move = MOVE_DIZZY_PUNCH,
			.Level = 34,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 37,
		},
		{
			.Move = MOVE_ENDURE,
			.Level = 43,
		},
		{
			.Move = MOVE_OUTRAGE,
			.Level = 46,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 49,
		},
		{
			.Move = MOVE_REVERSAL,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_HORSEA] = {
		{
			.Move = MOVE_BUBBLE,
			.Level = 1,
		},
		{
			.Move = MOVE_SMOKESCREEN,
			.Level = 5,
		},
		{
			.Move = MOVE_LEER,
			.Level = 9,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 13,
		},
		{
			.Move = MOVE_TWISTER,
			.Level = 17,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 21,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 26,
		},
		{
			.Move = MOVE_BRINE,
			.Level = 31,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 36,
		},
		{
			.Move = MOVE_DRAGON_PULSE,
			.Level = 41,
		},
		{
			.Move = MOVE_DRAGON_DANCE,
			.Level = 46,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 52,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SEADRA] = {
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 1,
		},
		{
			.Move = MOVE_BUBBLE,
			.Level = 1,
		},
		{
			.Move = MOVE_SMOKESCREEN,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_SMOKESCREEN,
			.Level = 5,
		},
		{
			.Move = MOVE_LEER,
			.Level = 9,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 13,
		},
		{
			.Move = MOVE_TWISTER,
			.Level = 17,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 21,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 26,
		},
		{
			.Move = MOVE_BRINE,
			.Level = 31,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 38,
		},
		{
			.Move = MOVE_DRAGON_PULSE,
			.Level = 45,
		},
		{
			.Move = MOVE_DRAGON_DANCE,
			.Level = 52,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 60,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GOLDEEN] = {
		{
			.Move = MOVE_PECK,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 5,
		},
		{
			.Move = MOVE_HORN_ATTACK,
			.Level = 8,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 13,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 16,
		},
		{
			.Move = MOVE_AQUA_RING,
			.Level = 21,
		},
		{
			.Move = MOVE_FURY_ATTACK,
			.Level = 24,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 29,
		},
		{
			.Move = MOVE_WATERFALL,
			.Level = 32,
		},
		{
			.Move = MOVE_HORN_DRILL,
			.Level = 37,
		},
		{
			.Move = MOVE_SOAK,
			.Level = 40,
		},
		{
			.Move = MOVE_MEGAHORN,
			.Level = 45,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SEAKING] = {
		{
			.Move = MOVE_MEGAHORN,
			.Level = 1,
		},
		{
			.Move = MOVE_POISON_JAB,
			.Level = 1,
		},
		{
			.Move = MOVE_PECK,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 1,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 5,
		},
		{
			.Move = MOVE_HORN_ATTACK,
			.Level = 8,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 13,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 16,
		},
		{
			.Move = MOVE_AQUA_RING,
			.Level = 21,
		},
		{
			.Move = MOVE_FURY_ATTACK,
			.Level = 24,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 29,
		},
		{
			.Move = MOVE_WATERFALL,
			.Level = 32,
		},
		{
			.Move = MOVE_HORN_DRILL,
			.Level = 40,
		},
		{
			.Move = MOVE_SOAK,
			.Level = 46,
		},
		{
			.Move = MOVE_MEGAHORN,
			.Level = 54,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_STARYU] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 4,
		},
		{
			.Move = MOVE_RAPID_SPIN,
			.Level = 7,
		},
		{
			.Move = MOVE_RECOVER,
			.Level = 10,
		},
		{
			.Move = MOVE_PSYWAVE,
			.Level = 13,
		},
		{
			.Move = MOVE_SWIFT,
			.Level = 16,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 18,
		},
		{
			.Move = MOVE_CAMOUFLAGE,
			.Level = 22,
		},
		{
			.Move = MOVE_GYRO_BALL,
			.Level = 24,
		},
		{
			.Move = MOVE_BRINE,
			.Level = 28,
		},
		{
			.Move = MOVE_MINIMIZE,
			.Level = 31,
		},
		{
			.Move = MOVE_REFLECT_TYPE,
			.Level = 35,
		},
		{
			.Move = MOVE_POWER_GEM,
			.Level = 37,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 40,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 42,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 46,
		},
		{
			.Move = MOVE_COSMIC_POWER,
			.Level = 49,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 53,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_STARMIE] = {
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_RAPID_SPIN,
			.Level = 1,
		},
		{
			.Move = MOVE_RECOVER,
			.Level = 1,
		},
		{
			.Move = MOVE_SWIFT,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 40,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MR_MIME] = {
		{
			.Move = MOVE_MISTY_TERRAIN,
			.Level = 1,
		},
		{
			.Move = MOVE_MAGICAL_LEAF,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_GUARD,
			.Level = 1,
		},
		{
			.Move = MOVE_WIDE_GUARD,
			.Level = 1,
		},
		{
			.Move = MOVE_POWER_SWAP,
			.Level = 1,
		},
		{
			.Move = MOVE_GUARD_SWAP,
			.Level = 1,
		},
		{
			.Move = MOVE_BARRIER,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_COPYCAT,
			.Level = 4,
		},
		{
			.Move = MOVE_MEDITATE,
			.Level = 8,
		},
		{
			.Move = MOVE_DOUBLESLAP,
			.Level = 11,
		},
		{
			.Move = MOVE_MIMIC,
			.Level = 15,
		},
		{
			.Move = MOVE_PSYWAVE,
			.Level = 15,
		},
		{
			.Move = MOVE_ENCORE,
			.Level = 18,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 22,
		},
		{
			.Move = MOVE_REFLECT,
			.Level = 22,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 25,
		},
		{
			.Move = MOVE_SUBSTITUTE,
			.Level = 29,
		},
		{
			.Move = MOVE_RECYCLE,
			.Level = 32,
		},
		{
			.Move = MOVE_TRICK,
			.Level = 36,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 39,
		},
		{
			.Move = MOVE_ROLE_PLAY,
			.Level = 43,
		},
		{
			.Move = MOVE_BATON_PASS,
			.Level = 46,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SCYTHER] = {
		{
			.Move = MOVE_VACUUM_WAVE,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 5,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 9,
		},
		{
			.Move = MOVE_FALSE_SWIPE,
			.Level = 13,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 17,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 21,
		},
		{
			.Move = MOVE_FURY_CUTTER,
			.Level = 25,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 29,
		},
		{
			.Move = MOVE_RAZOR_WIND,
			.Level = 33,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 37,
		},
		{
			.Move = MOVE_XSCISSOR,
			.Level = 41,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 45,
		},
		{
			.Move = MOVE_DOUBLE_HIT,
			.Level = 49,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 50,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 57,
		},
		{
			.Move = MOVE_FEINT,
			.Level = 61,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_JYNX] = {
		{
			.Move = MOVE_DRAINING_KISS,
			.Level = 1,
		},
		{
			.Move = MOVE_PERISH_SONG,
			.Level = 1,
		},
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_LICK,
			.Level = 1,
		},
		{
			.Move = MOVE_LOVELY_KISS,
			.Level = 1,
		},
		{
			.Move = MOVE_POWDER_SNOW,
			.Level = 1,
		},
		{
			.Move = MOVE_LICK,
			.Level = 5,
		},
		{
			.Move = MOVE_LOVELY_KISS,
			.Level = 8,
		},
		{
			.Move = MOVE_POWDER_SNOW,
			.Level = 11,
		},
		{
			.Move = MOVE_DOUBLESLAP,
			.Level = 15,
		},
		{
			.Move = MOVE_ICE_PUNCH,
			.Level = 18,
		},
		{
			.Move = MOVE_HEART_STAMP,
			.Level = 21,
		},
		{
			.Move = MOVE_MEAN_LOOK,
			.Level = 25,
		},
		{
			.Move = MOVE_FAKE_TEARS,
			.Level = 28,
		},
		{
			.Move = MOVE_WAKEUP_SLAP,
			.Level = 33,
		},
		{
			.Move = MOVE_AVALANCHE,
			.Level = 39,
		},
		{
			.Move = MOVE_BODY_SLAM,
			.Level = 44,
		},
		{
			.Move = MOVE_WRING_OUT,
			.Level = 49,
		},
		{
			.Move = MOVE_PERISH_SONG,
			.Level = 55,
		},
		{
			.Move = MOVE_BLIZZARD,
			.Level = 60,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ELECTABUZZ] = {
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 5,
		},
		{
			.Move = MOVE_LOW_KICK,
			.Level = 8,
		},
		{
			.Move = MOVE_SWIFT,
			.Level = 12,
		},
		{
			.Move = MOVE_SHOCK_WAVE,
			.Level = 15,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 19,
		},
		{
			.Move = MOVE_ELECTRO_BALL,
			.Level = 22,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 26,
		},
		{
			.Move = MOVE_THUNDERPUNCH,
			.Level = 29,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 36,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 42,
		},
		{
			.Move = MOVE_THUNDERBOLT,
			.Level = 49,
		},
		{
			.Move = MOVE_THUNDER,
			.Level = 55,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MAGMAR] = {
		{
			.Move = MOVE_SMOG,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 5,
		},
		{
			.Move = MOVE_SMOKESCREEN,
			.Level = 8,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 12,
		},
		{
			.Move = MOVE_FIRE_SPIN,
			.Level = 15,
		},
		{
			.Move = MOVE_CLEAR_SMOG,
			.Level = 19,
		},
		{
			.Move = MOVE_FLAME_BURST,
			.Level = 22,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 26,
		},
		{
			.Move = MOVE_FIRE_PUNCH,
			.Level = 29,
		},
		{
			.Move = MOVE_LAVA_PLUME,
			.Level = 36,
		},
		{
			.Move = MOVE_SUNNY_DAY,
			.Level = 42,
		},
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 49,
		},
		{
			.Move = MOVE_FIRE_BLAST,
			.Level = 55,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PINSIR] = {
		{
			.Move = MOVE_VICEGRIP,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 1,
		},
		{
			.Move = MOVE_BIND,
			.Level = 4,
		},
		{
			.Move = MOVE_SEISMIC_TOSS,
			.Level = 8,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 11,
		},
		{
			.Move = MOVE_REVENGE,
			.Level = 15,
		},
		{
			.Move = MOVE_VITAL_THROW,
			.Level = 18,
		},
		{
			.Move = MOVE_DOUBLE_HIT,
			.Level = 22,
		},
		{
			.Move = MOVE_BRICK_BREAK,
			.Level = 26,
		},
		{
			.Move = MOVE_SUBMISSION,
			.Level = 29,
		},
		{
			.Move = MOVE_XSCISSOR,
			.Level = 33,
		},
		{
			.Move = MOVE_STORM_THROW,
			.Level = 36,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 40,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 43,
		},
		{
			.Move = MOVE_SUPERPOWER,
			.Level = 47,
		},
		{
			.Move = MOVE_GUILLOTINE,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_TAUROS] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 3,
		},
		{
			.Move = MOVE_RAGE,
			.Level = 5,
		},
		{
			.Move = MOVE_HORN_ATTACK,
			.Level = 8,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 11,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 15,
		},
		{
			.Move = MOVE_REST,
			.Level = 19,
		},
		{
			.Move = MOVE_PAYBACK,
			.Level = 24,
		},
		{
			.Move = MOVE_WORK_UP,
			.Level = 29,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 35,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 41,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 48,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 50,
		},
		{
			.Move = MOVE_GIGA_IMPACT,
			.Level = 63,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MAGIKARP] = {
		{
			.Move = MOVE_SPLASH,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 15,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 30,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GYARADOS] = {
		{
			.Move = MOVE_THRASH,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 20,
		},
		{
			.Move = MOVE_DRAGON_RAGE,
			.Level = 23,
		},
		{
			.Move = MOVE_LEER,
			.Level = 26,
		},
		{
			.Move = MOVE_TWISTER,
			.Level = 29,
		},
		{
			.Move = MOVE_ICE_FANG,
			.Level = 32,
		},
		{
			.Move = MOVE_AQUA_TAIL,
			.Level = 35,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 38,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 41,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 44,
		},
		{
			.Move = MOVE_DRAGON_DANCE,
			.Level = 47,
		},
		{
			.Move = MOVE_HYPER_BEAM,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_LAPRAS] = {
		{
			.Move = MOVE_SING,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_MIST,
			.Level = 4,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 7,
		},
		{
			.Move = MOVE_ICE_SHARD,
			.Level = 10,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 14,
		},
		{
			.Move = MOVE_BODY_SLAM,
			.Level = 18,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 22,
		},
		{
			.Move = MOVE_PERISH_SONG,
			.Level = 27,
		},
		{
			.Move = MOVE_ICE_BEAM,
			.Level = 32,
		},
		{
			.Move = MOVE_BRINE,
			.Level = 37,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 43,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 47,
		},
		{
			.Move = MOVE_SHEER_COLD,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_DITTO] = {
		{
			.Move = MOVE_TRANSFORM,
			.Level = 1,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_EEVEE] = {
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 5,
		},
		{
			.Move = MOVE_BABYDOLL_EYES,
			.Level = 9,
		},
		{
			.Move = MOVE_SWIFT,
			.Level = 10,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 13,
		},
		{
			.Move = MOVE_BITE,
			.Level = 17,
		},
		{
			.Move = MOVE_REFRESH,
			.Level = 20,
		},
		{
			.Move = MOVE_COVET,
			.Level = 23,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 25,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 29,
		},
		{
			.Move = MOVE_BATON_PASS,
			.Level = 33,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 37,
		},
		{
			.Move = MOVE_LAST_RESORT,
			.Level = 41,
		},
		{
			.Move = MOVE_TRUMP_CARD,
			.Level = 45,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_VAPOREON] = {
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 5,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 9,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 13,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 17,
		},
		{
			.Move = MOVE_AURORA_BEAM,
			.Level = 20,
		},
		{
			.Move = MOVE_AQUA_RING,
			.Level = 25,
		},
		{
			.Move = MOVE_ACID_ARMOR,
			.Level = 29,
		},
		{
			.Move = MOVE_HAZE,
			.Level = 33,
		},
		{
			.Move = MOVE_MUDDY_WATER,
			.Level = 37,
		},
		{
			.Move = MOVE_LAST_RESORT,
			.Level = 41,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 45,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_JOLTEON] = {
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 5,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 9,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 13,
		},
		{
			.Move = MOVE_DOUBLE_KICK,
			.Level = 17,
		},
		{
			.Move = MOVE_THUNDER_FANG,
			.Level = 20,
		},
		{
			.Move = MOVE_PIN_MISSILE,
			.Level = 25,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 29,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 33,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 37,
		},
		{
			.Move = MOVE_LAST_RESORT,
			.Level = 41,
		},
		{
			.Move = MOVE_THUNDER,
			.Level = 45,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_FLAREON] = {
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 5,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 9,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 13,
		},
		{
			.Move = MOVE_BITE,
			.Level = 17,
		},
		{
			.Move = MOVE_FIRE_FANG,
			.Level = 20,
		},
		{
			.Move = MOVE_FIRE_SPIN,
			.Level = 25,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 29,
		},
		{
			.Move = MOVE_SMOG,
			.Level = 33,
		},
		{
			.Move = MOVE_LAVA_PLUME,
			.Level = 37,
		},
		{
			.Move = MOVE_LAST_RESORT,
			.Level = 41,
		},
		{
			.Move = MOVE_FLARE_BLITZ,
			.Level = 45,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PORYGON] = {
		{
			.Move = MOVE_CONVERSION_2,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_CONVERSION,
			.Level = 1,
		},
		{
			.Move = MOVE_SHARPEN,
			.Level = 1,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 7,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 12,
		},
		{
			.Move = MOVE_RECOVER,
			.Level = 18,
		},
		{
			.Move = MOVE_MAGNET_RISE,
			.Level = 23,
		},
		{
			.Move = MOVE_SIGNAL_BEAM,
			.Level = 29,
		},
		{
			.Move = MOVE_RECYCLE,
			.Level = 34,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 40,
		},
		{
			.Move = MOVE_LOCKON,
			.Level = 45,
		},
		{
			.Move = MOVE_TRI_ATTACK,
			.Level = 50,
		},
		{
			.Move = MOVE_MAGIC_COAT,
			.Level = 56,
		},
		{
			.Move = MOVE_ZAP_CANNON,
			.Level = 62,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_OMANYTE] = {
		{
			.Move = MOVE_CONSTRICT,
			.Level = 1,
		},
		{
			.Move = MOVE_WITHDRAW,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 7,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 10,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 16,
		},
		{
			.Move = MOVE_LEER,
			.Level = 19,
		},
		{
			.Move = MOVE_MUD_SHOT,
			.Level = 25,
		},
		{
			.Move = MOVE_BRINE,
			.Level = 28,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 34,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 37,
		},
		{
			.Move = MOVE_TICKLE,
			.Level = 43,
		},
		{
			.Move = MOVE_ROCK_BLAST,
			.Level = 46,
		},
		{
			.Move = MOVE_SHELL_SMASH,
			.Level = 50,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 55,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_OMASTAR] = {
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 1,
		},
		{
			.Move = MOVE_CONSTRICT,
			.Level = 1,
		},
		{
			.Move = MOVE_WITHDRAW,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 7,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 10,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 16,
		},
		{
			.Move = MOVE_LEER,
			.Level = 19,
		},
		{
			.Move = MOVE_MUD_SHOT,
			.Level = 25,
		},
		{
			.Move = MOVE_BRINE,
			.Level = 28,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 34,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 37,
		},
		{
			.Move = MOVE_SPIKE_CANNON,
			.Level = 40,
		},
		{
			.Move = MOVE_TICKLE,
			.Level = 48,
		},
		{
			.Move = MOVE_ROCK_BLAST,
			.Level = 56,
		},
		{
			.Move = MOVE_SHELL_SMASH,
			.Level = 67,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 75,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_KABUTO] = {
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 1,
		},
		{
			.Move = MOVE_ABSORB,
			.Level = 6,
		},
		{
			.Move = MOVE_LEER,
			.Level = 11,
		},
		{
			.Move = MOVE_MUD_SHOT,
			.Level = 16,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 21,
		},
		{
			.Move = MOVE_ENDURE,
			.Level = 26,
		},
		{
			.Move = MOVE_AQUA_JET,
			.Level = 31,
		},
		{
			.Move = MOVE_MEGA_DRAIN,
			.Level = 36,
		},
		{
			.Move = MOVE_METAL_SOUND,
			.Level = 41,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 46,
		},
		{
			.Move = MOVE_WRING_OUT,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_KABUTOPS] = {
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 1,
		},
		{
			.Move = MOVE_FEINT,
			.Level = 1,
		},
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 1,
		},
		{
			.Move = MOVE_ABSORB,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_ABSORB,
			.Level = 6,
		},
		{
			.Move = MOVE_LEER,
			.Level = 11,
		},
		{
			.Move = MOVE_MUD_SHOT,
			.Level = 16,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 21,
		},
		{
			.Move = MOVE_ENDURE,
			.Level = 26,
		},
		{
			.Move = MOVE_AQUA_JET,
			.Level = 31,
		},
		{
			.Move = MOVE_MEGA_DRAIN,
			.Level = 36,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 40,
		},
		{
			.Move = MOVE_METAL_SOUND,
			.Level = 45,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 54,
		},
		{
			.Move = MOVE_WRING_OUT,
			.Level = 63,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 72,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_AERODACTYL] = {
		{
			.Move = MOVE_IRON_HEAD,
			.Level = 1,
		},
		{
			.Move = MOVE_ICE_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_FIRE_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 1,
		},
		{
			.Move = MOVE_ROAR,
			.Level = 9,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 17,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 25,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 33,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 41,
		},
		{
			.Move = MOVE_SKY_DROP,
			.Level = 49,
		},
		{
			.Move = MOVE_IRON_HEAD,
			.Level = 57,
		},
		{
			.Move = MOVE_HYPER_BEAM,
			.Level = 65,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 73,
		},
		{
			.Move = MOVE_GIGA_IMPACT,
			.Level = 81,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SNORLAX] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 4,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 9,
		},
		{
			.Move = MOVE_LICK,
			.Level = 12,
		},
		{
			.Move = MOVE_CHIP_AWAY,
			.Level = 17,
		},
		{
			.Move = MOVE_YAWN,
			.Level = 20,
		},
		{
			.Move = MOVE_BODY_SLAM,
			.Level = 25,
		},
		{
			.Move = MOVE_REST,
			.Level = 28,
		},
		{
			.Move = MOVE_SNORE,
			.Level = 28,
		},
		{
			.Move = MOVE_SLEEP_TALK,
			.Level = 33,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 36,
		},
		{
			.Move = MOVE_BLOCK,
			.Level = 41,
		},
		{
			.Move = MOVE_BELLY_DRUM,
			.Level = 44,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 49,
		},
		{
			.Move = MOVE_HEAVY_SLAM,
			.Level = 50,
		},
		{
			.Move = MOVE_GIGA_IMPACT,
			.Level = 57,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ARTICUNO] = {
		{
			.Move = MOVE_ROOST,
			.Level = 1,
		},
		{
			.Move = MOVE_HURRICANE,
			.Level = 1,
		},
		{
			.Move = MOVE_FREEZEDRY,
			.Level = 1,
		},
		{
			.Move = MOVE_TAILWIND,
			.Level = 1,
		},
		{
			.Move = MOVE_SHEER_COLD,
			.Level = 1,
		},
		{
			.Move = MOVE_GUST,
			.Level = 1,
		},
		{
			.Move = MOVE_POWDER_SNOW,
			.Level = 1,
		},
		{
			.Move = MOVE_MIST,
			.Level = 8,
		},
		{
			.Move = MOVE_ICE_SHARD,
			.Level = 15,
		},
		{
			.Move = MOVE_MIND_READER,
			.Level = 22,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 29,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 36,
		},
		{
			.Move = MOVE_ICE_BEAM,
			.Level = 43,
		},
		{
			.Move = MOVE_REFLECT,
			.Level = 50,
		},
		{
			.Move = MOVE_HAIL,
			.Level = 57,
		},
		{
			.Move = MOVE_TAILWIND,
			.Level = 64,
		},
		{
			.Move = MOVE_BLIZZARD,
			.Level = 71,
		},
		{
			.Move = MOVE_SHEER_COLD,
			.Level = 78,
		},
		{
			.Move = MOVE_ROOST,
			.Level = 85,
		},
		{
			.Move = MOVE_HURRICANE,
			.Level = 92,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ZAPDOS] = {
		{
			.Move = MOVE_ROOST,
			.Level = 1,
		},
		{
			.Move = MOVE_ZAP_CANNON,
			.Level = 1,
		},
		{
			.Move = MOVE_DRILL_PECK,
			.Level = 1,
		},
		{
			.Move = MOVE_PECK,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 8,
		},
		{
			.Move = MOVE_DETECT,
			.Level = 15,
		},
		{
			.Move = MOVE_PLUCK,
			.Level = 22,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 29,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 36,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 43,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 50,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 57,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 64,
		},
		{
			.Move = MOVE_DRILL_PECK,
			.Level = 71,
		},
		{
			.Move = MOVE_THUNDER,
			.Level = 78,
		},
		{
			.Move = MOVE_ROOST,
			.Level = 85,
		},
		{
			.Move = MOVE_ZAP_CANNON,
			.Level = 92,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MOLTRES] = {
		{
			.Move = MOVE_ROOST,
			.Level = 1,
		},
		{
			.Move = MOVE_HURRICANE,
			.Level = 1,
		},
		{
			.Move = MOVE_SKY_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_HEAT_WAVE,
			.Level = 1,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 1,
		},
		{
			.Move = MOVE_FIRE_SPIN,
			.Level = 8,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 15,
		},
		{
			.Move = MOVE_ENDURE,
			.Level = 22,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 29,
		},
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 36,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 43,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 50,
		},
		{
			.Move = MOVE_SUNNY_DAY,
			.Level = 57,
		},
		{
			.Move = MOVE_HEAT_WAVE,
			.Level = 64,
		},
		{
			.Move = MOVE_SOLARBEAM,
			.Level = 71,
		},
		{
			.Move = MOVE_SKY_ATTACK,
			.Level = 78,
		},
		{
			.Move = MOVE_ROOST,
			.Level = 85,
		},
		{
			.Move = MOVE_HURRICANE,
			.Level = 92,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_DRATINI] = {
		{
			.Move = MOVE_WRAP,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 5,
		},
		{
			.Move = MOVE_TWISTER,
			.Level = 11,
		},
		{
			.Move = MOVE_DRAGON_RAGE,
			.Level = 15,
		},
		{
			.Move = MOVE_SLAM,
			.Level = 21,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 25,
		},
		{
			.Move = MOVE_DRAGON_TAIL,
			.Level = 31,
		},
		{
			.Move = MOVE_AQUA_TAIL,
			.Level = 35,
		},
		{
			.Move = MOVE_DRAGON_RUSH,
			.Level = 41,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 45,
		},
		{
			.Move = MOVE_DRAGON_DANCE,
			.Level = 51,
		},
		{
			.Move = MOVE_OUTRAGE,
			.Level = 55,
		},
		{
			.Move = MOVE_HYPER_BEAM,
			.Level = 61,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_DRAGONAIR] = {
		{
			.Move = MOVE_WRAP,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 1,
		},
		{
			.Move = MOVE_TWISTER,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 5,
		},
		{
			.Move = MOVE_TWISTER,
			.Level = 11,
		},
		{
			.Move = MOVE_DRAGON_RAGE,
			.Level = 15,
		},
		{
			.Move = MOVE_SLAM,
			.Level = 21,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 25,
		},
		{
			.Move = MOVE_DRAGON_TAIL,
			.Level = 33,
		},
		{
			.Move = MOVE_AQUA_TAIL,
			.Level = 39,
		},
		{
			.Move = MOVE_DRAGON_RUSH,
			.Level = 47,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 53,
		},
		{
			.Move = MOVE_DRAGON_DANCE,
			.Level = 61,
		},
		{
			.Move = MOVE_OUTRAGE,
			.Level = 67,
		},
		{
			.Move = MOVE_HYPER_BEAM,
			.Level = 75,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_DRAGONITE] = {
		{
			.Move = MOVE_HURRICANE,
			.Level = 1,
		},
		{
			.Move = MOVE_FIRE_PUNCH,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDERPUNCH,
			.Level = 1,
		},
		{
			.Move = MOVE_ROOST,
			.Level = 1,
		},
		{
			.Move = MOVE_WRAP,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 1,
		},
		{
			.Move = MOVE_TWISTER,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 5,
		},
		{
			.Move = MOVE_TWISTER,
			.Level = 11,
		},
		{
			.Move = MOVE_DRAGON_RAGE,
			.Level = 15,
		},
		{
			.Move = MOVE_SLAM,
			.Level = 21,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 25,
		},
		{
			.Move = MOVE_DRAGON_TAIL,
			.Level = 33,
		},
		{
			.Move = MOVE_AQUA_TAIL,
			.Level = 39,
		},
		{
			.Move = MOVE_DRAGON_RUSH,
			.Level = 47,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 53,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 55,
		},
		{
			.Move = MOVE_DRAGON_DANCE,
			.Level = 61,
		},
		{
			.Move = MOVE_OUTRAGE,
			.Level = 67,
		},
		{
			.Move = MOVE_HYPER_BEAM,
			.Level = 75,
		},
		{
			.Move = MOVE_HURRICANE,
			.Level = 81,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MEWTWO] = {
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_DISABLE,
			.Level = 1,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 1,
		},
		{
			.Move = MOVE_SWIFT,
			.Level = 8,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 15,
		},
		{
			.Move = MOVE_PSYCH_UP,
			.Level = 22,
		},
		{
			.Move = MOVE_MIRACLE_EYE,
			.Level = 29,
		},
		{
			.Move = MOVE_PSYCHO_CUT,
			.Level = 36,
		},
		{
			.Move = MOVE_POWER_SWAP,
			.Level = 43,
		},
		{
			.Move = MOVE_GUARD_SWAP,
			.Level = 43,
		},
		{
			.Move = MOVE_RECOVER,
			.Level = 50,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 57,
		},
		{
			.Move = MOVE_BARRIER,
			.Level = 64,
		},
		{
			.Move = MOVE_AURA_SPHERE,
			.Level = 70,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 79,
		},
		{
			.Move = MOVE_MIST,
			.Level = 86,
		},
		{
			.Move = MOVE_ME_FIRST,
			.Level = 93,
		},
		{
			.Move = MOVE_PSYSTRIKE,
			.Level = 100,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MEW] = {
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_REFLECT_TYPE,
			.Level = 1,
		},
		{
			.Move = MOVE_TRANSFORM,
			.Level = 1,
		},
		{
			.Move = MOVE_MEGA_PUNCH,
			.Level = 10,
		},
		{
			.Move = MOVE_METRONOME,
			.Level = 20,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 30,
		},
		{
			.Move = MOVE_BARRIER,
			.Level = 40,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 50,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 60,
		},
		{
			.Move = MOVE_ME_FIRST,
			.Level = 70,
		},
		{
			.Move = MOVE_BATON_PASS,
			.Level = 80,
		},
		{
			.Move = MOVE_NASTY_PLOT,
			.Level = 90,
		},
		{
			.Move = MOVE_AURA_SPHERE,
			.Level = 100,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CHIKORITA] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 6,
		},
		{
			.Move = MOVE_POISONPOWDER,
			.Level = 9,
		},
		{
			.Move = MOVE_SYNTHESIS,
			.Level = 12,
		},
		{
			.Move = MOVE_REFLECT,
			.Level = 17,
		},
		{
			.Move = MOVE_MAGICAL_LEAF,
			.Level = 20,
		},
		{
			.Move = MOVE_NATURAL_GIFT,
			.Level = 23,
		},
		{
			.Move = MOVE_SWEET_SCENT,
			.Level = 28,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 31,
		},
		{
			.Move = MOVE_BODY_SLAM,
			.Level = 34,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 39,
		},
		{
			.Move = MOVE_AROMATHERAPY,
			.Level = 42,
		},
		{
			.Move = MOVE_SOLARBEAM,
			.Level = 45,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BAYLEEF] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 1,
		},
		{
			.Move = MOVE_POISONPOWDER,
			.Level = 1,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 6,
		},
		{
			.Move = MOVE_POISONPOWDER,
			.Level = 9,
		},
		{
			.Move = MOVE_SYNTHESIS,
			.Level = 12,
		},
		{
			.Move = MOVE_REFLECT,
			.Level = 18,
		},
		{
			.Move = MOVE_MAGICAL_LEAF,
			.Level = 22,
		},
		{
			.Move = MOVE_NATURAL_GIFT,
			.Level = 26,
		},
		{
			.Move = MOVE_SWEET_SCENT,
			.Level = 32,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 36,
		},
		{
			.Move = MOVE_BODY_SLAM,
			.Level = 40,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 46,
		},
		{
			.Move = MOVE_AROMATHERAPY,
			.Level = 50,
		},
		{
			.Move = MOVE_SOLARBEAM,
			.Level = 54,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MEGANIUM] = {
		{
			.Move = MOVE_PETAL_BLIZZARD,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 1,
		},
		{
			.Move = MOVE_POISONPOWDER,
			.Level = 1,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 6,
		},
		{
			.Move = MOVE_POISONPOWDER,
			.Level = 9,
		},
		{
			.Move = MOVE_SYNTHESIS,
			.Level = 12,
		},
		{
			.Move = MOVE_REFLECT,
			.Level = 18,
		},
		{
			.Move = MOVE_MAGICAL_LEAF,
			.Level = 22,
		},
		{
			.Move = MOVE_NATURAL_GIFT,
			.Level = 26,
		},
		{
			.Move = MOVE_PETAL_DANCE,
			.Level = 32,
		},
		{
			.Move = MOVE_SWEET_SCENT,
			.Level = 34,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 40,
		},
		{
			.Move = MOVE_BODY_SLAM,
			.Level = 46,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 54,
		},
		{
			.Move = MOVE_AROMATHERAPY,
			.Level = 60,
		},
		{
			.Move = MOVE_SOLARBEAM,
			.Level = 66,
		},
		{
			.Move = MOVE_PETAL_BLIZZARD,
			.Level = 70,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CYNDAQUIL] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_SMOKESCREEN,
			.Level = 6,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 10,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 13,
		},
		{
			.Move = MOVE_FLAME_WHEEL,
			.Level = 19,
		},
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 22,
		},
		{
			.Move = MOVE_FLAME_CHARGE,
			.Level = 28,
		},
		{
			.Move = MOVE_SWIFT,
			.Level = 31,
		},
		{
			.Move = MOVE_LAVA_PLUME,
			.Level = 37,
		},
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 40,
		},
		{
			.Move = MOVE_INFERNO,
			.Level = 46,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 49,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 55,
		},
		{
			.Move = MOVE_ERUPTION,
			.Level = 58,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_QUILAVA] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_SMOKESCREEN,
			.Level = 1,
		},
		{
			.Move = MOVE_SMOKESCREEN,
			.Level = 6,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 10,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 13,
		},
		{
			.Move = MOVE_FLAME_WHEEL,
			.Level = 20,
		},
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 24,
		},
		{
			.Move = MOVE_SWIFT,
			.Level = 31,
		},
		{
			.Move = MOVE_FLAME_CHARGE,
			.Level = 35,
		},
		{
			.Move = MOVE_LAVA_PLUME,
			.Level = 42,
		},
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 46,
		},
		{
			.Move = MOVE_INFERNO,
			.Level = 53,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 57,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 64,
		},
		{
			.Move = MOVE_ERUPTION,
			.Level = 68,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_TYPHLOSION] = {
		{
			.Move = MOVE_ERUPTION,
			.Level = 1,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 1,
		},
		{
			.Move = MOVE_GYRO_BALL,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_SMOKESCREEN,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 1,
		},
		{
			.Move = MOVE_SMOKESCREEN,
			.Level = 6,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 10,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 13,
		},
		{
			.Move = MOVE_FLAME_WHEEL,
			.Level = 20,
		},
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 24,
		},
		{
			.Move = MOVE_SWIFT,
			.Level = 31,
		},
		{
			.Move = MOVE_FLAME_CHARGE,
			.Level = 35,
		},
		{
			.Move = MOVE_LAVA_PLUME,
			.Level = 43,
		},
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 48,
		},
		{
			.Move = MOVE_INFERNO,
			.Level = 56,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 61,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 69,
		},
		{
			.Move = MOVE_ERUPTION,
			.Level = 74,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_TOTODILE] = {
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 6,
		},
		{
			.Move = MOVE_RAGE,
			.Level = 8,
		},
		{
			.Move = MOVE_BITE,
			.Level = 13,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 15,
		},
		{
			.Move = MOVE_ICE_FANG,
			.Level = 20,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 22,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 27,
		},
		{
			.Move = MOVE_CHIP_AWAY,
			.Level = 29,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 34,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 36,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 41,
		},
		{
			.Move = MOVE_AQUA_TAIL,
			.Level = 43,
		},
		{
			.Move = MOVE_SUPERPOWER,
			.Level = 48,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CROCONAW] = {
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 6,
		},
		{
			.Move = MOVE_RAGE,
			.Level = 8,
		},
		{
			.Move = MOVE_BITE,
			.Level = 13,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 15,
		},
		{
			.Move = MOVE_ICE_FANG,
			.Level = 21,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 24,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 30,
		},
		{
			.Move = MOVE_CHIP_AWAY,
			.Level = 33,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 39,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 42,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 48,
		},
		{
			.Move = MOVE_AQUA_TAIL,
			.Level = 51,
		},
		{
			.Move = MOVE_SUPERPOWER,
			.Level = 57,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 60,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_FERALIGATR] = {
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_RAGE,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 6,
		},
		{
			.Move = MOVE_RAGE,
			.Level = 8,
		},
		{
			.Move = MOVE_BITE,
			.Level = 13,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 15,
		},
		{
			.Move = MOVE_ICE_FANG,
			.Level = 21,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 24,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 30,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 32,
		},
		{
			.Move = MOVE_CHIP_AWAY,
			.Level = 37,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 45,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 50,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 58,
		},
		{
			.Move = MOVE_AQUA_TAIL,
			.Level = 63,
		},
		{
			.Move = MOVE_SUPERPOWER,
			.Level = 71,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 76,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SENTRET] = {
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_FORESIGHT,
			.Level = 1,
		},
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 4,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 7,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 13,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 16,
		},
		{
			.Move = MOVE_FOLLOW_ME,
			.Level = 19,
		},
		{
			.Move = MOVE_SLAM,
			.Level = 25,
		},
		{
			.Move = MOVE_REST,
			.Level = 28,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 31,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 36,
		},
		{
			.Move = MOVE_BATON_PASS,
			.Level = 39,
		},
		{
			.Move = MOVE_ME_FIRST,
			.Level = 42,
		},
		{
			.Move = MOVE_HYPER_VOICE,
			.Level = 47,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_FURRET] = {
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_FORESIGHT,
			.Level = 1,
		},
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 4,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 7,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 13,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 17,
		},
		{
			.Move = MOVE_FOLLOW_ME,
			.Level = 21,
		},
		{
			.Move = MOVE_SLAM,
			.Level = 28,
		},
		{
			.Move = MOVE_REST,
			.Level = 32,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 36,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 42,
		},
		{
			.Move = MOVE_BATON_PASS,
			.Level = 46,
		},
		{
			.Move = MOVE_ME_FIRST,
			.Level = 50,
		},
		{
			.Move = MOVE_HYPER_VOICE,
			.Level = 56,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_HOOTHOOT] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_FORESIGHT,
			.Level = 1,
		},
		{
			.Move = MOVE_HYPNOSIS,
			.Level = 5,
		},
		{
			.Move = MOVE_PECK,
			.Level = 9,
		},
		{
			.Move = MOVE_UPROAR,
			.Level = 13,
		},
		{
			.Move = MOVE_REFLECT,
			.Level = 17,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 21,
		},
		{
			.Move = MOVE_ECHOED_VOICE,
			.Level = 25,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 29,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 33,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 37,
		},
		{
			.Move = MOVE_SYNCHRONOISE,
			.Level = 41,
		},
		{
			.Move = MOVE_EXTRASENSORY,
			.Level = 45,
		},
		{
			.Move = MOVE_PSYCHO_SHIFT,
			.Level = 49,
		},
		{
			.Move = MOVE_ROOST,
			.Level = 53,
		},
		{
			.Move = MOVE_DREAM_EATER,
			.Level = 57,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_NOCTOWL] = {
		{
			.Move = MOVE_DREAM_EATER,
			.Level = 1,
		},
		{
			.Move = MOVE_SKY_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_FORESIGHT,
			.Level = 1,
		},
		{
			.Move = MOVE_HYPNOSIS,
			.Level = 1,
		},
		{
			.Move = MOVE_HYPNOSIS,
			.Level = 5,
		},
		{
			.Move = MOVE_PECK,
			.Level = 9,
		},
		{
			.Move = MOVE_UPROAR,
			.Level = 13,
		},
		{
			.Move = MOVE_REFLECT,
			.Level = 17,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 22,
		},
		{
			.Move = MOVE_ECHOED_VOICE,
			.Level = 27,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 32,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 37,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 42,
		},
		{
			.Move = MOVE_SYNCHRONOISE,
			.Level = 47,
		},
		{
			.Move = MOVE_EXTRASENSORY,
			.Level = 52,
		},
		{
			.Move = MOVE_PSYCHO_SHIFT,
			.Level = 57,
		},
		{
			.Move = MOVE_ROOST,
			.Level = 62,
		},
		{
			.Move = MOVE_DREAM_EATER,
			.Level = 67,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_LEDYBA] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 6,
		},
		{
			.Move = MOVE_COMET_PUNCH,
			.Level = 9,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 14,
		},
		{
			.Move = MOVE_REFLECT,
			.Level = 14,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 14,
		},
		{
			.Move = MOVE_MACH_PUNCH,
			.Level = 17,
		},
		{
			.Move = MOVE_BATON_PASS,
			.Level = 22,
		},
		{
			.Move = MOVE_SILVER_WIND,
			.Level = 25,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 30,
		},
		{
			.Move = MOVE_SWIFT,
			.Level = 33,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 38,
		},
		{
			.Move = MOVE_BUG_BUZZ,
			.Level = 41,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_LEDIAN] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 1,
		},
		{
			.Move = MOVE_COMET_PUNCH,
			.Level = 1,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 6,
		},
		{
			.Move = MOVE_COMET_PUNCH,
			.Level = 9,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 14,
		},
		{
			.Move = MOVE_REFLECT,
			.Level = 14,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 14,
		},
		{
			.Move = MOVE_MACH_PUNCH,
			.Level = 17,
		},
		{
			.Move = MOVE_BATON_PASS,
			.Level = 24,
		},
		{
			.Move = MOVE_SILVER_WIND,
			.Level = 29,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 36,
		},
		{
			.Move = MOVE_SWIFT,
			.Level = 41,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 48,
		},
		{
			.Move = MOVE_BUG_BUZZ,
			.Level = 53,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SPINARAK] = {
		{
			.Move = MOVE_POISON_STING,
			.Level = 1,
		},
		{
			.Move = MOVE_STRING_SHOT,
			.Level = 1,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 5,
		},
		{
			.Move = MOVE_CONSTRICT,
			.Level = 8,
		},
		{
			.Move = MOVE_LEECH_LIFE,
			.Level = 12,
		},
		{
			.Move = MOVE_NIGHT_SHADE,
			.Level = 15,
		},
		{
			.Move = MOVE_SHADOW_SNEAK,
			.Level = 19,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 22,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 26,
		},
		{
			.Move = MOVE_SPIDER_WEB,
			.Level = 29,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 33,
		},
		{
			.Move = MOVE_PIN_MISSILE,
			.Level = 36,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 40,
		},
		{
			.Move = MOVE_POISON_JAB,
			.Level = 43,
		},
		{
			.Move = MOVE_CROSS_POISON,
			.Level = 47,
		},
		{
			.Move = MOVE_STICKY_WEB,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ARIADOS] = {
		{
			.Move = MOVE_VENOM_DRENCH,
			.Level = 1,
		},
		{
			.Move = MOVE_FELL_STINGER,
			.Level = 1,
		},
		{
			.Move = MOVE_BUG_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_POISON_STING,
			.Level = 1,
		},
		{
			.Move = MOVE_STRING_SHOT,
			.Level = 1,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 1,
		},
		{
			.Move = MOVE_CONSTRICT,
			.Level = 1,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 5,
		},
		{
			.Move = MOVE_CONSTRICT,
			.Level = 8,
		},
		{
			.Move = MOVE_LEECH_LIFE,
			.Level = 12,
		},
		{
			.Move = MOVE_NIGHT_SHADE,
			.Level = 15,
		},
		{
			.Move = MOVE_SHADOW_SNEAK,
			.Level = 19,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 23,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 28,
		},
		{
			.Move = MOVE_SPIDER_WEB,
			.Level = 32,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 37,
		},
		{
			.Move = MOVE_PIN_MISSILE,
			.Level = 41,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 46,
		},
		{
			.Move = MOVE_POISON_JAB,
			.Level = 50,
		},
		{
			.Move = MOVE_CROSS_POISON,
			.Level = 55,
		},
		{
			.Move = MOVE_STICKY_WEB,
			.Level = 58,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CROBAT] = {
		{
			.Move = MOVE_CROSS_POISON,
			.Level = 1,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 1,
		},
		{
			.Move = MOVE_LEECH_LIFE,
			.Level = 1,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 5,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 7,
		},
		{
			.Move = MOVE_BITE,
			.Level = 11,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 13,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 17,
		},
		{
			.Move = MOVE_AIR_CUTTER,
			.Level = 19,
		},
		{
			.Move = MOVE_SWIFT,
			.Level = 24,
		},
		{
			.Move = MOVE_POISON_FANG,
			.Level = 27,
		},
		{
			.Move = MOVE_MEAN_LOOK,
			.Level = 32,
		},
		{
			.Move = MOVE_ACROBATICS,
			.Level = 35,
		},
		{
			.Move = MOVE_HAZE,
			.Level = 40,
		},
		{
			.Move = MOVE_VENOSHOCK,
			.Level = 43,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 48,
		},
		{
			.Move = MOVE_QUICK_GUARD,
			.Level = 51,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CHINCHOU] = {
		{
			.Move = MOVE_BUBBLE,
			.Level = 1,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 6,
		},
		{
			.Move = MOVE_ELECTRO_BALL,
			.Level = 9,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 12,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 17,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 20,
		},
		{
			.Move = MOVE_SPARK,
			.Level = 23,
		},
		{
			.Move = MOVE_SIGNAL_BEAM,
			.Level = 28,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 31,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 34,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 39,
		},
		{
			.Move = MOVE_AQUA_RING,
			.Level = 42,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 45,
		},
		{
			.Move = MOVE_ION_DELUGE,
			.Level = 47,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_LANTURN] = {
		{
			.Move = MOVE_EERIE_IMPULSE,
			.Level = 1,
		},
		{
			.Move = MOVE_BUBBLE,
			.Level = 1,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 1,
		},
		{
			.Move = MOVE_ELECTRO_BALL,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 6,
		},
		{
			.Move = MOVE_ELECTRO_BALL,
			.Level = 9,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 12,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 17,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 20,
		},
		{
			.Move = MOVE_SPARK,
			.Level = 23,
		},
		{
			.Move = MOVE_STOCKPILE,
			.Level = 27,
		},
		{
			.Move = MOVE_SWALLOW,
			.Level = 27,
		},
		{
			.Move = MOVE_SPIT_UP,
			.Level = 27,
		},
		{
			.Move = MOVE_SIGNAL_BEAM,
			.Level = 29,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 33,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 37,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 43,
		},
		{
			.Move = MOVE_AQUA_RING,
			.Level = 47,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 51,
		},
		{
			.Move = MOVE_ION_DELUGE,
			.Level = 54,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 58,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PICHU] = {
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 1,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 5,
		},
		{
			.Move = MOVE_SWEET_KISS,
			.Level = 10,
		},
		{
			.Move = MOVE_NASTY_PLOT,
			.Level = 13,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 18,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CLEFFA] = {
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 1,
		},
		{
			.Move = MOVE_ENCORE,
			.Level = 4,
		},
		{
			.Move = MOVE_SING,
			.Level = 7,
		},
		{
			.Move = MOVE_SWEET_KISS,
			.Level = 10,
		},
		{
			.Move = MOVE_COPYCAT,
			.Level = 13,
		},
		{
			.Move = MOVE_MAGICAL_LEAF,
			.Level = 16,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_IGGLYBUFF] = {
		{
			.Move = MOVE_SING,
			.Level = 1,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 1,
		},
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 3,
		},
		{
			.Move = MOVE_POUND,
			.Level = 5,
		},
		{
			.Move = MOVE_SWEET_KISS,
			.Level = 9,
		},
		{
			.Move = MOVE_COPYCAT,
			.Level = 11,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_TOGEPI] = {
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 1,
		},
		{
			.Move = MOVE_METRONOME,
			.Level = 5,
		},
		{
			.Move = MOVE_SWEET_KISS,
			.Level = 9,
		},
		{
			.Move = MOVE_YAWN,
			.Level = 13,
		},
		{
			.Move = MOVE_ENCORE,
			.Level = 17,
		},
		{
			.Move = MOVE_FOLLOW_ME,
			.Level = 21,
		},
		{
			.Move = MOVE_BESTOW,
			.Level = 25,
		},
		{
			.Move = MOVE_WISH,
			.Level = 29,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 33,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 37,
		},
		{
			.Move = MOVE_BATON_PASS,
			.Level = 41,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 45,
		},
		{
			.Move = MOVE_LAST_RESORT,
			.Level = 49,
		},
		{
			.Move = MOVE_AFTER_YOU,
			.Level = 53,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_TOGETIC] = {
		{
			.Move = MOVE_MAGICAL_LEAF,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 1,
		},
		{
			.Move = MOVE_METRONOME,
			.Level = 1,
		},
		{
			.Move = MOVE_SWEET_KISS,
			.Level = 1,
		},
		{
			.Move = MOVE_METRONOME,
			.Level = 5,
		},
		{
			.Move = MOVE_SWEET_KISS,
			.Level = 9,
		},
		{
			.Move = MOVE_YAWN,
			.Level = 13,
		},
		{
			.Move = MOVE_FAIRY_WIND,
			.Level = 14,
		},
		{
			.Move = MOVE_ENCORE,
			.Level = 17,
		},
		{
			.Move = MOVE_FOLLOW_ME,
			.Level = 21,
		},
		{
			.Move = MOVE_BESTOW,
			.Level = 25,
		},
		{
			.Move = MOVE_WISH,
			.Level = 29,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 33,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 37,
		},
		{
			.Move = MOVE_BATON_PASS,
			.Level = 41,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 45,
		},
		{
			.Move = MOVE_LAST_RESORT,
			.Level = 49,
		},
		{
			.Move = MOVE_AFTER_YOU,
			.Level = 53,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_NATU] = {
		{
			.Move = MOVE_PECK,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_NIGHT_SHADE,
			.Level = 6,
		},
		{
			.Move = MOVE_TELEPORT,
			.Level = 9,
		},
		{
			.Move = MOVE_LUCKY_CHANT,
			.Level = 12,
		},
		{
			.Move = MOVE_STORED_POWER,
			.Level = 17,
		},
		{
			.Move = MOVE_OMINOUS_WIND,
			.Level = 20,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 23,
		},
		{
			.Move = MOVE_WISH,
			.Level = 28,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 33,
		},
		{
			.Move = MOVE_MIRACLE_EYE,
			.Level = 36,
		},
		{
			.Move = MOVE_PSYCHO_SHIFT,
			.Level = 39,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 44,
		},
		{
			.Move = MOVE_POWER_SWAP,
			.Level = 47,
		},
		{
			.Move = MOVE_GUARD_SWAP,
			.Level = 47,
		},
		{
			.Move = MOVE_ME_FIRST,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_XATU] = {
		{
			.Move = MOVE_TAILWIND,
			.Level = 1,
		},
		{
			.Move = MOVE_PECK,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_NIGHT_SHADE,
			.Level = 1,
		},
		{
			.Move = MOVE_TELEPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_NIGHT_SHADE,
			.Level = 6,
		},
		{
			.Move = MOVE_TELEPORT,
			.Level = 9,
		},
		{
			.Move = MOVE_LUCKY_CHANT,
			.Level = 12,
		},
		{
			.Move = MOVE_STORED_POWER,
			.Level = 17,
		},
		{
			.Move = MOVE_OMINOUS_WIND,
			.Level = 20,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 23,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 25,
		},
		{
			.Move = MOVE_WISH,
			.Level = 29,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 35,
		},
		{
			.Move = MOVE_MIRACLE_EYE,
			.Level = 39,
		},
		{
			.Move = MOVE_PSYCHO_SHIFT,
			.Level = 43,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 49,
		},
		{
			.Move = MOVE_POWER_SWAP,
			.Level = 53,
		},
		{
			.Move = MOVE_GUARD_SWAP,
			.Level = 53,
		},
		{
			.Move = MOVE_ME_FIRST,
			.Level = 57,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MAREEP] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 4,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 8,
		},
		{
			.Move = MOVE_COTTON_SPORE,
			.Level = 11,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 15,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 18,
		},
		{
			.Move = MOVE_ELECTRO_BALL,
			.Level = 22,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 25,
		},
		{
			.Move = MOVE_POWER_GEM,
			.Level = 29,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 32,
		},
		{
			.Move = MOVE_COTTON_GUARD,
			.Level = 36,
		},
		{
			.Move = MOVE_SIGNAL_BEAM,
			.Level = 39,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 43,
		},
		{
			.Move = MOVE_THUNDER,
			.Level = 46,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_FLAAFFY] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 4,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 8,
		},
		{
			.Move = MOVE_COTTON_SPORE,
			.Level = 11,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 16,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 20,
		},
		{
			.Move = MOVE_ELECTRO_BALL,
			.Level = 25,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 29,
		},
		{
			.Move = MOVE_POWER_GEM,
			.Level = 34,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 38,
		},
		{
			.Move = MOVE_COTTON_GUARD,
			.Level = 43,
		},
		{
			.Move = MOVE_SIGNAL_BEAM,
			.Level = 47,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 52,
		},
		{
			.Move = MOVE_THUNDER,
			.Level = 56,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_AMPHAROS] = {
		{
			.Move = MOVE_ZAP_CANNON,
			.Level = 1,
		},
		{
			.Move = MOVE_MAGNETIC_FLUX,
			.Level = 1,
		},
		{
			.Move = MOVE_ION_DELUGE,
			.Level = 1,
		},
		{
			.Move = MOVE_DRAGON_PULSE,
			.Level = 1,
		},
		{
			.Move = MOVE_FIRE_PUNCH,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 4,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 8,
		},
		{
			.Move = MOVE_COTTON_SPORE,
			.Level = 11,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 16,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 20,
		},
		{
			.Move = MOVE_ELECTRO_BALL,
			.Level = 25,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 29,
		},
		{
			.Move = MOVE_THUNDERPUNCH,
			.Level = 30,
		},
		{
			.Move = MOVE_POWER_GEM,
			.Level = 35,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 40,
		},
		{
			.Move = MOVE_COTTON_GUARD,
			.Level = 46,
		},
		{
			.Move = MOVE_SIGNAL_BEAM,
			.Level = 51,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 57,
		},
		{
			.Move = MOVE_THUNDER,
			.Level = 62,
		},
		{
			.Move = MOVE_DRAGON_PULSE,
			.Level = 65,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BELLOSSOM] = {
		{
			.Move = MOVE_LEAF_STORM,
			.Level = 1,
		},
		{
			.Move = MOVE_LEAF_BLADE,
			.Level = 1,
		},
		{
			.Move = MOVE_MEGA_DRAIN,
			.Level = 1,
		},
		{
			.Move = MOVE_SWEET_SCENT,
			.Level = 1,
		},
		{
			.Move = MOVE_STUN_SPORE,
			.Level = 1,
		},
		{
			.Move = MOVE_SUNNY_DAY,
			.Level = 1,
		},
		{
			.Move = MOVE_MAGICAL_LEAF,
			.Level = 24,
		},
		{
			.Move = MOVE_PETAL_BLIZZARD,
			.Level = 49,
		},
		{
			.Move = MOVE_LEAF_STORM,
			.Level = 64,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MARILL] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 2,
		},
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 5,
		},
		{
			.Move = MOVE_BUBBLE,
			.Level = 7,
		},
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 10,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 10,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 13,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 16,
		},
		{
			.Move = MOVE_AQUA_TAIL,
			.Level = 20,
		},
		{
			.Move = MOVE_PLAY_ROUGH,
			.Level = 23,
		},
		{
			.Move = MOVE_AQUA_RING,
			.Level = 28,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 31,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 37,
		},
		{
			.Move = MOVE_SUPERPOWER,
			.Level = 40,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 47,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_AZUMARILL] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 2,
		},
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 5,
		},
		{
			.Move = MOVE_BUBBLE,
			.Level = 7,
		},
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 10,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 10,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 13,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 16,
		},
		{
			.Move = MOVE_AQUA_TAIL,
			.Level = 21,
		},
		{
			.Move = MOVE_PLAY_ROUGH,
			.Level = 25,
		},
		{
			.Move = MOVE_AQUA_RING,
			.Level = 31,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 35,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 42,
		},
		{
			.Move = MOVE_SUPERPOWER,
			.Level = 46,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 55,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SUDOWOODO] = {
		{
			.Move = MOVE_WOOD_HAMMER,
			.Level = 1,
		},
		{
			.Move = MOVE_COPYCAT,
			.Level = 1,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 1,
		},
		{
			.Move = MOVE_LOW_KICK,
			.Level = 1,
		},
		{
			.Move = MOVE_ROCK_THROW,
			.Level = 1,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 5,
		},
		{
			.Move = MOVE_LOW_KICK,
			.Level = 8,
		},
		{
			.Move = MOVE_ROCK_THROW,
			.Level = 12,
		},
		{
			.Move = MOVE_MIMIC,
			.Level = 15,
		},
		{
			.Move = MOVE_SLAM,
			.Level = 15,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 19,
		},
		{
			.Move = MOVE_ROCK_TOMB,
			.Level = 22,
		},
		{
			.Move = MOVE_BLOCK,
			.Level = 26,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 29,
		},
		{
			.Move = MOVE_COUNTER,
			.Level = 33,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 36,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 40,
		},
		{
			.Move = MOVE_STONE_EDGE,
			.Level = 43,
		},
		{
			.Move = MOVE_HAMMER_ARM,
			.Level = 47,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_POLITOED] = {
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 1,
		},
		{
			.Move = MOVE_HYPNOSIS,
			.Level = 1,
		},
		{
			.Move = MOVE_DOUBLESLAP,
			.Level = 1,
		},
		{
			.Move = MOVE_PERISH_SONG,
			.Level = 1,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 27,
		},
		{
			.Move = MOVE_BOUNCE,
			.Level = 37,
		},
		{
			.Move = MOVE_HYPER_VOICE,
			.Level = 48,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_HOPPIP] = {
		{
			.Move = MOVE_SPLASH,
			.Level = 1,
		},
		{
			.Move = MOVE_SYNTHESIS,
			.Level = 4,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 6,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 8,
		},
		{
			.Move = MOVE_FAIRY_WIND,
			.Level = 10,
		},
		{
			.Move = MOVE_POISONPOWDER,
			.Level = 12,
		},
		{
			.Move = MOVE_STUN_SPORE,
			.Level = 14,
		},
		{
			.Move = MOVE_SLEEP_POWDER,
			.Level = 16,
		},
		{
			.Move = MOVE_BULLET_SEED,
			.Level = 19,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 22,
		},
		{
			.Move = MOVE_MEGA_DRAIN,
			.Level = 25,
		},
		{
			.Move = MOVE_ACROBATICS,
			.Level = 28,
		},
		{
			.Move = MOVE_RAGE_POWDER,
			.Level = 31,
		},
		{
			.Move = MOVE_COTTON_SPORE,
			.Level = 34,
		},
		{
			.Move = MOVE_UTURN,
			.Level = 37,
		},
		{
			.Move = MOVE_WORRY_SEED,
			.Level = 40,
		},
		{
			.Move = MOVE_GIGA_DRAIN,
			.Level = 43,
		},
		{
			.Move = MOVE_BOUNCE,
			.Level = 46,
		},
		{
			.Move = MOVE_MEMENTO,
			.Level = 49,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SKIPLOOM] = {
		{
			.Move = MOVE_SPLASH,
			.Level = 1,
		},
		{
			.Move = MOVE_SYNTHESIS,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_SYNTHESIS,
			.Level = 4,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 6,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 8,
		},
		{
			.Move = MOVE_FAIRY_WIND,
			.Level = 10,
		},
		{
			.Move = MOVE_POISONPOWDER,
			.Level = 12,
		},
		{
			.Move = MOVE_STUN_SPORE,
			.Level = 14,
		},
		{
			.Move = MOVE_SLEEP_POWDER,
			.Level = 16,
		},
		{
			.Move = MOVE_BULLET_SEED,
			.Level = 20,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 24,
		},
		{
			.Move = MOVE_MEGA_DRAIN,
			.Level = 28,
		},
		{
			.Move = MOVE_ACROBATICS,
			.Level = 32,
		},
		{
			.Move = MOVE_RAGE_POWDER,
			.Level = 36,
		},
		{
			.Move = MOVE_COTTON_SPORE,
			.Level = 40,
		},
		{
			.Move = MOVE_UTURN,
			.Level = 44,
		},
		{
			.Move = MOVE_WORRY_SEED,
			.Level = 48,
		},
		{
			.Move = MOVE_GIGA_DRAIN,
			.Level = 52,
		},
		{
			.Move = MOVE_BOUNCE,
			.Level = 56,
		},
		{
			.Move = MOVE_MEMENTO,
			.Level = 60,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_JUMPLUFF] = {
		{
			.Move = MOVE_SPLASH,
			.Level = 1,
		},
		{
			.Move = MOVE_SYNTHESIS,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_SYNTHESIS,
			.Level = 4,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 6,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 8,
		},
		{
			.Move = MOVE_FAIRY_WIND,
			.Level = 10,
		},
		{
			.Move = MOVE_POISONPOWDER,
			.Level = 12,
		},
		{
			.Move = MOVE_STUN_SPORE,
			.Level = 14,
		},
		{
			.Move = MOVE_SLEEP_POWDER,
			.Level = 16,
		},
		{
			.Move = MOVE_BULLET_SEED,
			.Level = 20,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 24,
		},
		{
			.Move = MOVE_MEGA_DRAIN,
			.Level = 29,
		},
		{
			.Move = MOVE_ACROBATICS,
			.Level = 34,
		},
		{
			.Move = MOVE_RAGE_POWDER,
			.Level = 39,
		},
		{
			.Move = MOVE_COTTON_SPORE,
			.Level = 44,
		},
		{
			.Move = MOVE_UTURN,
			.Level = 49,
		},
		{
			.Move = MOVE_WORRY_SEED,
			.Level = 54,
		},
		{
			.Move = MOVE_GIGA_DRAIN,
			.Level = 59,
		},
		{
			.Move = MOVE_BOUNCE,
			.Level = 64,
		},
		{
			.Move = MOVE_MEMENTO,
			.Level = 69,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_AIPOM] = {
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 4,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 8,
		},
		{
			.Move = MOVE_BATON_PASS,
			.Level = 11,
		},
		{
			.Move = MOVE_TICKLE,
			.Level = 15,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 18,
		},
		{
			.Move = MOVE_SWIFT,
			.Level = 22,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 25,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 29,
		},
		{
			.Move = MOVE_DOUBLE_HIT,
			.Level = 32,
		},
		{
			.Move = MOVE_FLING,
			.Level = 36,
		},
		{
			.Move = MOVE_NASTY_PLOT,
			.Level = 39,
		},
		{
			.Move = MOVE_LAST_RESORT,
			.Level = 43,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SUNKERN] = {
		{
			.Move = MOVE_ABSORB,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWTH,
			.Level = 1,
		},
		{
			.Move = MOVE_INGRAIN,
			.Level = 4,
		},
		{
			.Move = MOVE_GRASSWHISTLE,
			.Level = 7,
		},
		{
			.Move = MOVE_MEGA_DRAIN,
			.Level = 10,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 13,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 16,
		},
		{
			.Move = MOVE_WORRY_SEED,
			.Level = 19,
		},
		{
			.Move = MOVE_GIGA_DRAIN,
			.Level = 22,
		},
		{
			.Move = MOVE_ENDEAVOR,
			.Level = 25,
		},
		{
			.Move = MOVE_SYNTHESIS,
			.Level = 28,
		},
		{
			.Move = MOVE_NATURAL_GIFT,
			.Level = 31,
		},
		{
			.Move = MOVE_SOLARBEAM,
			.Level = 34,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 37,
		},
		{
			.Move = MOVE_SUNNY_DAY,
			.Level = 40,
		},
		{
			.Move = MOVE_SEED_BOMB,
			.Level = 43,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SUNFLORA] = {
		{
			.Move = MOVE_FLOWER_SHIELD,
			.Level = 1,
		},
		{
			.Move = MOVE_ABSORB,
			.Level = 1,
		},
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWTH,
			.Level = 1,
		},
		{
			.Move = MOVE_INGRAIN,
			.Level = 4,
		},
		{
			.Move = MOVE_GRASSWHISTLE,
			.Level = 7,
		},
		{
			.Move = MOVE_MEGA_DRAIN,
			.Level = 10,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 13,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 16,
		},
		{
			.Move = MOVE_WORRY_SEED,
			.Level = 19,
		},
		{
			.Move = MOVE_GIGA_DRAIN,
			.Level = 22,
		},
		{
			.Move = MOVE_BULLET_SEED,
			.Level = 25,
		},
		{
			.Move = MOVE_PETAL_DANCE,
			.Level = 28,
		},
		{
			.Move = MOVE_NATURAL_GIFT,
			.Level = 31,
		},
		{
			.Move = MOVE_SOLARBEAM,
			.Level = 34,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 37,
		},
		{
			.Move = MOVE_SUNNY_DAY,
			.Level = 40,
		},
		{
			.Move = MOVE_LEAF_STORM,
			.Level = 43,
		},
		{
			.Move = MOVE_PETAL_BLIZZARD,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_YANMA] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_FORESIGHT,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 6,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 11,
		},
		{
			.Move = MOVE_SONICBOOM,
			.Level = 14,
		},
		{
			.Move = MOVE_DETECT,
			.Level = 17,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 22,
		},
		{
			.Move = MOVE_UPROAR,
			.Level = 27,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 30,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 33,
		},
		{
			.Move = MOVE_HYPNOSIS,
			.Level = 38,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 43,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 46,
		},
		{
			.Move = MOVE_UTURN,
			.Level = 49,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 54,
		},
		{
			.Move = MOVE_BUG_BUZZ,
			.Level = 57,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_WOOPER] = {
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_MUD_SPORT,
			.Level = 5,
		},
		{
			.Move = MOVE_MUD_SHOT,
			.Level = 9,
		},
		{
			.Move = MOVE_SLAM,
			.Level = 15,
		},
		{
			.Move = MOVE_MUD_BOMB,
			.Level = 19,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 23,
		},
		{
			.Move = MOVE_YAWN,
			.Level = 29,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 33,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 37,
		},
		{
			.Move = MOVE_MIST,
			.Level = 43,
		},
		{
			.Move = MOVE_HAZE,
			.Level = 43,
		},
		{
			.Move = MOVE_MUDDY_WATER,
			.Level = 47,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_QUAGSIRE] = {
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_MUD_SPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_MUD_SPORT,
			.Level = 5,
		},
		{
			.Move = MOVE_MUD_SHOT,
			.Level = 9,
		},
		{
			.Move = MOVE_SLAM,
			.Level = 15,
		},
		{
			.Move = MOVE_MUD_BOMB,
			.Level = 19,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 24,
		},
		{
			.Move = MOVE_YAWN,
			.Level = 31,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 36,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 41,
		},
		{
			.Move = MOVE_MIST,
			.Level = 48,
		},
		{
			.Move = MOVE_HAZE,
			.Level = 48,
		},
		{
			.Move = MOVE_MUDDY_WATER,
			.Level = 53,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ESPEON] = {
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 5,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 9,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 13,
		},
		{
			.Move = MOVE_SWIFT,
			.Level = 17,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 20,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 25,
		},
		{
			.Move = MOVE_PSYCH_UP,
			.Level = 29,
		},
		{
			.Move = MOVE_MORNING_SUN,
			.Level = 33,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 37,
		},
		{
			.Move = MOVE_LAST_RESORT,
			.Level = 41,
		},
		{
			.Move = MOVE_POWER_SWAP,
			.Level = 45,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_UMBREON] = {
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 5,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 9,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 13,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 17,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 20,
		},
		{
			.Move = MOVE_ASSURANCE,
			.Level = 25,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 29,
		},
		{
			.Move = MOVE_MOONLIGHT,
			.Level = 33,
		},
		{
			.Move = MOVE_MEAN_LOOK,
			.Level = 37,
		},
		{
			.Move = MOVE_LAST_RESORT,
			.Level = 41,
		},
		{
			.Move = MOVE_GUARD_SWAP,
			.Level = 45,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MURKROW] = {
		{
			.Move = MOVE_PECK,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 5,
		},
		{
			.Move = MOVE_HAZE,
			.Level = 11,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 15,
		},
		{
			.Move = MOVE_NIGHT_SHADE,
			.Level = 21,
		},
		{
			.Move = MOVE_ASSURANCE,
			.Level = 25,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 31,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 35,
		},
		{
			.Move = MOVE_MEAN_LOOK,
			.Level = 41,
		},
		{
			.Move = MOVE_FOUL_PLAY,
			.Level = 45,
		},
		{
			.Move = MOVE_TAILWIND,
			.Level = 50,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 55,
		},
		{
			.Move = MOVE_TORMENT,
			.Level = 61,
		},
		{
			.Move = MOVE_QUASH,
			.Level = 65,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SLOWKING] = {
		{
			.Move = MOVE_HEAL_PULSE,
			.Level = 1,
		},
		{
			.Move = MOVE_POWER_GEM,
			.Level = 1,
		},
		{
			.Move = MOVE_HIDDEN_POWER,
			.Level = 1,
		},
		{
			.Move = MOVE_CURSE,
			.Level = 1,
		},
		{
			.Move = MOVE_YAWN,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 5,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 9,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 14,
		},
		{
			.Move = MOVE_DISABLE,
			.Level = 19,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 23,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 28,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 32,
		},
		{
			.Move = MOVE_NASTY_PLOT,
			.Level = 36,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 41,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 45,
		},
		{
			.Move = MOVE_TRUMP_CARD,
			.Level = 49,
		},
		{
			.Move = MOVE_PSYCH_UP,
			.Level = 54,
		},
		{
			.Move = MOVE_HEAL_PULSE,
			.Level = 58,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MISDREAVUS] = {
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_PSYWAVE,
			.Level = 1,
		},
		{
			.Move = MOVE_SPITE,
			.Level = 5,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 10,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 14,
		},
		{
			.Move = MOVE_MEAN_LOOK,
			.Level = 19,
		},
		{
			.Move = MOVE_HEX,
			.Level = 23,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 28,
		},
		{
			.Move = MOVE_PAIN_SPLIT,
			.Level = 32,
		},
		{
			.Move = MOVE_PAYBACK,
			.Level = 37,
		},
		{
			.Move = MOVE_SHADOW_BALL,
			.Level = 41,
		},
		{
			.Move = MOVE_PERISH_SONG,
			.Level = 46,
		},
		{
			.Move = MOVE_GRUDGE,
			.Level = 50,
		},
		{
			.Move = MOVE_POWER_GEM,
			.Level = 55,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_UNOWN] = {
		{
			.Move = MOVE_HIDDEN_POWER,
			.Level = 1,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_WOBBUFFET] = {
		{
			.Move = MOVE_COUNTER,
			.Level = 1,
		},
		{
			.Move = MOVE_MIRROR_COAT,
			.Level = 1,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 1,
		},
		{
			.Move = MOVE_DESTINY_BOND,
			.Level = 1,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GIRAFARIG] = {
		{
			.Move = MOVE_POWER_SWAP,
			.Level = 1,
		},
		{
			.Move = MOVE_GUARD_SWAP,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 5,
		},
		{
			.Move = MOVE_ASSURANCE,
			.Level = 10,
		},
		{
			.Move = MOVE_STOMP,
			.Level = 14,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 19,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 23,
		},
		{
			.Move = MOVE_DOUBLE_HIT,
			.Level = 28,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 32,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 37,
		},
		{
			.Move = MOVE_BATON_PASS,
			.Level = 41,
		},
		{
			.Move = MOVE_NASTY_PLOT,
			.Level = 46,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PINECO] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 1,
		},
		{
			.Move = MOVE_SELFDESTRUCT,
			.Level = 6,
		},
		{
			.Move = MOVE_BUG_BITE,
			.Level = 9,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 12,
		},
		{
			.Move = MOVE_RAPID_SPIN,
			.Level = 17,
		},
		{
			.Move = MOVE_BIDE,
			.Level = 20,
		},
		{
			.Move = MOVE_NATURAL_GIFT,
			.Level = 23,
		},
		{
			.Move = MOVE_SPIKES,
			.Level = 28,
		},
		{
			.Move = MOVE_PAYBACK,
			.Level = 31,
		},
		{
			.Move = MOVE_EXPLOSION,
			.Level = 34,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 39,
		},
		{
			.Move = MOVE_GYRO_BALL,
			.Level = 42,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 45,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_FORRETRESS] = {
		{
			.Move = MOVE_HEAVY_SLAM,
			.Level = 1,
		},
		{
			.Move = MOVE_ZAP_CANNON,
			.Level = 1,
		},
		{
			.Move = MOVE_MAGNET_RISE,
			.Level = 1,
		},
		{
			.Move = MOVE_TOXIC_SPIKES,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 1,
		},
		{
			.Move = MOVE_SELFDESTRUCT,
			.Level = 1,
		},
		{
			.Move = MOVE_BUG_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 12,
		},
		{
			.Move = MOVE_RAPID_SPIN,
			.Level = 17,
		},
		{
			.Move = MOVE_BIDE,
			.Level = 20,
		},
		{
			.Move = MOVE_NATURAL_GIFT,
			.Level = 23,
		},
		{
			.Move = MOVE_SPIKES,
			.Level = 28,
		},
		{
			.Move = MOVE_MIRROR_SHOT,
			.Level = 31,
		},
		{
			.Move = MOVE_AUTOTOMIZE,
			.Level = 32,
		},
		{
			.Move = MOVE_PAYBACK,
			.Level = 36,
		},
		{
			.Move = MOVE_EXPLOSION,
			.Level = 42,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 46,
		},
		{
			.Move = MOVE_GYRO_BALL,
			.Level = 50,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 56,
		},
		{
			.Move = MOVE_MAGNET_RISE,
			.Level = 60,
		},
		{
			.Move = MOVE_ZAP_CANNON,
			.Level = 64,
		},
		{
			.Move = MOVE_HEAVY_SLAM,
			.Level = 70,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_DUNSPARCE] = {
		{
			.Move = MOVE_RAGE,
			.Level = 1,
		},
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 1,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 4,
		},
		{
			.Move = MOVE_SPITE,
			.Level = 7,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 10,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 13,
		},
		{
			.Move = MOVE_YAWN,
			.Level = 16,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 19,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 22,
		},
		{
			.Move = MOVE_ROOST,
			.Level = 25,
		},
		{
			.Move = MOVE_GLARE,
			.Level = 28,
		},
		{
			.Move = MOVE_DIG,
			.Level = 31,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 34,
		},
		{
			.Move = MOVE_COIL,
			.Level = 37,
		},
		{
			.Move = MOVE_ENDURE,
			.Level = 40,
		},
		{
			.Move = MOVE_DRILL_RUN,
			.Level = 43,
		},
		{
			.Move = MOVE_ENDEAVOR,
			.Level = 46,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 49,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GLIGAR] = {
		{
			.Move = MOVE_POISON_STING,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 4,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 7,
		},
		{
			.Move = MOVE_KNOCK_OFF,
			.Level = 10,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 13,
		},
		{
			.Move = MOVE_FURY_CUTTER,
			.Level = 16,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 19,
		},
		{
			.Move = MOVE_ACROBATICS,
			.Level = 22,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 27,
		},
		{
			.Move = MOVE_UTURN,
			.Level = 30,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 35,
		},
		{
			.Move = MOVE_XSCISSOR,
			.Level = 40,
		},
		{
			.Move = MOVE_SKY_UPPERCUT,
			.Level = 45,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 50,
		},
		{
			.Move = MOVE_GUILLOTINE,
			.Level = 55,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_STEELIX] = {
		{
			.Move = MOVE_IRON_TAIL,
			.Level = 1,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 1,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 1,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 1,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SNUBBULL] = {
		{
			.Move = MOVE_ICE_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_FIRE_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 7,
		},
		{
			.Move = MOVE_LICK,
			.Level = 13,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 19,
		},
		{
			.Move = MOVE_ROAR,
			.Level = 25,
		},
		{
			.Move = MOVE_RAGE,
			.Level = 31,
		},
		{
			.Move = MOVE_PLAY_ROUGH,
			.Level = 37,
		},
		{
			.Move = MOVE_PAYBACK,
			.Level = 43,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 49,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GRANBULL] = {
		{
			.Move = MOVE_OUTRAGE,
			.Level = 1,
		},
		{
			.Move = MOVE_ICE_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_FIRE_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 7,
		},
		{
			.Move = MOVE_LICK,
			.Level = 13,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 19,
		},
		{
			.Move = MOVE_ROAR,
			.Level = 27,
		},
		{
			.Move = MOVE_RAGE,
			.Level = 35,
		},
		{
			.Move = MOVE_PLAY_ROUGH,
			.Level = 43,
		},
		{
			.Move = MOVE_PAYBACK,
			.Level = 51,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 59,
		},
		{
			.Move = MOVE_OUTRAGE,
			.Level = 67,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_QWILFISH] = {
		{
			.Move = MOVE_FELL_STINGER,
			.Level = 1,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 1,
		},
		{
			.Move = MOVE_DESTINY_BOND,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_SPIKES,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_POISON_STING,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 9,
		},
		{
			.Move = MOVE_MINIMIZE,
			.Level = 9,
		},
		{
			.Move = MOVE_BUBBLE,
			.Level = 13,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 17,
		},
		{
			.Move = MOVE_TOXIC_SPIKES,
			.Level = 21,
		},
		{
			.Move = MOVE_STOCKPILE,
			.Level = 25,
		},
		{
			.Move = MOVE_SPIT_UP,
			.Level = 25,
		},
		{
			.Move = MOVE_REVENGE,
			.Level = 29,
		},
		{
			.Move = MOVE_BRINE,
			.Level = 33,
		},
		{
			.Move = MOVE_PIN_MISSILE,
			.Level = 37,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 41,
		},
		{
			.Move = MOVE_AQUA_TAIL,
			.Level = 45,
		},
		{
			.Move = MOVE_POISON_JAB,
			.Level = 49,
		},
		{
			.Move = MOVE_DESTINY_BOND,
			.Level = 53,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 57,
		},
		{
			.Move = MOVE_FELL_STINGER,
			.Level = 60,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SCIZOR] = {
		{
			.Move = MOVE_FEINT,
			.Level = 1,
		},
		{
			.Move = MOVE_BULLET_PUNCH,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 5,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 9,
		},
		{
			.Move = MOVE_FALSE_SWIPE,
			.Level = 13,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 17,
		},
		{
			.Move = MOVE_METAL_CLAW,
			.Level = 21,
		},
		{
			.Move = MOVE_FURY_CUTTER,
			.Level = 25,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 29,
		},
		{
			.Move = MOVE_RAZOR_WIND,
			.Level = 33,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 37,
		},
		{
			.Move = MOVE_XSCISSOR,
			.Level = 41,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 45,
		},
		{
			.Move = MOVE_DOUBLE_HIT,
			.Level = 49,
		},
		{
			.Move = MOVE_IRON_HEAD,
			.Level = 50,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 57,
		},
		{
			.Move = MOVE_FEINT,
			.Level = 61,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SHUCKLE] = {
		{
			.Move = MOVE_STICKY_WEB,
			.Level = 1,
		},
		{
			.Move = MOVE_WITHDRAW,
			.Level = 1,
		},
		{
			.Move = MOVE_CONSTRICT,
			.Level = 1,
		},
		{
			.Move = MOVE_BIDE,
			.Level = 1,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 1,
		},
		{
			.Move = MOVE_ENCORE,
			.Level = 5,
		},
		{
			.Move = MOVE_WRAP,
			.Level = 9,
		},
		{
			.Move = MOVE_STRUGGLE_BUG,
			.Level = 12,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 16,
		},
		{
			.Move = MOVE_REST,
			.Level = 20,
		},
		{
			.Move = MOVE_ROCK_THROW,
			.Level = 23,
		},
		{
			.Move = MOVE_GASTRO_ACID,
			.Level = 27,
		},
		{
			.Move = MOVE_POWER_TRICK,
			.Level = 31,
		},
		{
			.Move = MOVE_SHELL_SMASH,
			.Level = 34,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 38,
		},
		{
			.Move = MOVE_BUG_BITE,
			.Level = 42,
		},
		{
			.Move = MOVE_POWER_SPLIT,
			.Level = 45,
		},
		{
			.Move = MOVE_GUARD_SPLIT,
			.Level = 45,
		},
		{
			.Move = MOVE_STONE_EDGE,
			.Level = 49,
		},
		{
			.Move = MOVE_STICKY_WEB,
			.Level = 53,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_HERACROSS] = {
		{
			.Move = MOVE_ARM_THRUST,
			.Level = 1,
		},
		{
			.Move = MOVE_BULLET_SEED,
			.Level = 1,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_HORN_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_ENDURE,
			.Level = 1,
		},
		{
			.Move = MOVE_FEINT,
			.Level = 7,
		},
		{
			.Move = MOVE_AERIAL_ACE,
			.Level = 10,
		},
		{
			.Move = MOVE_CHIP_AWAY,
			.Level = 16,
		},
		{
			.Move = MOVE_COUNTER,
			.Level = 19,
		},
		{
			.Move = MOVE_FURY_ATTACK,
			.Level = 25,
		},
		{
			.Move = MOVE_BRICK_BREAK,
			.Level = 28,
		},
		{
			.Move = MOVE_PIN_MISSILE,
			.Level = 31,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 34,
		},
		{
			.Move = MOVE_MEGAHORN,
			.Level = 37,
		},
		{
			.Move = MOVE_CLOSE_COMBAT,
			.Level = 43,
		},
		{
			.Move = MOVE_REVERSAL,
			.Level = 46,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SNEASEL] = {
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 8,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 10,
		},
		{
			.Move = MOVE_ICY_WIND,
			.Level = 14,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 16,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 20,
		},
		{
			.Move = MOVE_METAL_CLAW,
			.Level = 22,
		},
		{
			.Move = MOVE_HONE_CLAWS,
			.Level = 25,
		},
		{
			.Move = MOVE_BEAT_UP,
			.Level = 28,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 32,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 35,
		},
		{
			.Move = MOVE_SNATCH,
			.Level = 40,
		},
		{
			.Move = MOVE_PUNISHMENT,
			.Level = 44,
		},
		{
			.Move = MOVE_ICE_SHARD,
			.Level = 47,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_TEDDIURSA] = {
		{
			.Move = MOVE_FLING,
			.Level = 1,
		},
		{
			.Move = MOVE_COVET,
			.Level = 1,
		},
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_BABYDOLL_EYES,
			.Level = 1,
		},
		{
			.Move = MOVE_LICK,
			.Level = 1,
		},
		{
			.Move = MOVE_FAKE_TEARS,
			.Level = 1,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 8,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 15,
		},
		{
			.Move = MOVE_SWEET_SCENT,
			.Level = 22,
		},
		{
			.Move = MOVE_PLAY_NICE,
			.Level = 25,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 29,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 36,
		},
		{
			.Move = MOVE_REST,
			.Level = 43,
		},
		{
			.Move = MOVE_SNORE,
			.Level = 43,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 50,
		},
		{
			.Move = MOVE_FLING,
			.Level = 57,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_URSARING] = {
		{
			.Move = MOVE_HAMMER_ARM,
			.Level = 1,
		},
		{
			.Move = MOVE_COVET,
			.Level = 1,
		},
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_LICK,
			.Level = 1,
		},
		{
			.Move = MOVE_FAKE_TEARS,
			.Level = 1,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 8,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 15,
		},
		{
			.Move = MOVE_SWEET_SCENT,
			.Level = 22,
		},
		{
			.Move = MOVE_PLAY_NICE,
			.Level = 25,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 29,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 38,
		},
		{
			.Move = MOVE_REST,
			.Level = 47,
		},
		{
			.Move = MOVE_SNORE,
			.Level = 49,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 58,
		},
		{
			.Move = MOVE_HAMMER_ARM,
			.Level = 67,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SLUGMA] = {
		{
			.Move = MOVE_YAWN,
			.Level = 1,
		},
		{
			.Move = MOVE_SMOG,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 6,
		},
		{
			.Move = MOVE_ROCK_THROW,
			.Level = 8,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 13,
		},
		{
			.Move = MOVE_INCINERATE,
			.Level = 15,
		},
		{
			.Move = MOVE_CLEAR_SMOG,
			.Level = 20,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 22,
		},
		{
			.Move = MOVE_FLAME_BURST,
			.Level = 27,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 29,
		},
		{
			.Move = MOVE_LAVA_PLUME,
			.Level = 34,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 36,
		},
		{
			.Move = MOVE_BODY_SLAM,
			.Level = 41,
		},
		{
			.Move = MOVE_RECOVER,
			.Level = 43,
		},
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 48,
		},
		{
			.Move = MOVE_EARTH_POWER,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MAGCARGO] = {
		{
			.Move = MOVE_EARTH_POWER,
			.Level = 1,
		},
		{
			.Move = MOVE_YAWN,
			.Level = 1,
		},
		{
			.Move = MOVE_SMOG,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 1,
		},
		{
			.Move = MOVE_ROCK_THROW,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 6,
		},
		{
			.Move = MOVE_ROCK_THROW,
			.Level = 8,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 13,
		},
		{
			.Move = MOVE_INCINERATE,
			.Level = 15,
		},
		{
			.Move = MOVE_CLEAR_SMOG,
			.Level = 20,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 22,
		},
		{
			.Move = MOVE_FLAME_BURST,
			.Level = 27,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 29,
		},
		{
			.Move = MOVE_LAVA_PLUME,
			.Level = 34,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 36,
		},
		{
			.Move = MOVE_SHELL_SMASH,
			.Level = 38,
		},
		{
			.Move = MOVE_BODY_SLAM,
			.Level = 43,
		},
		{
			.Move = MOVE_RECOVER,
			.Level = 47,
		},
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 54,
		},
		{
			.Move = MOVE_EARTH_POWER,
			.Level = 58,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SWINUB] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 1,
		},
		{
			.Move = MOVE_MUD_SPORT,
			.Level = 5,
		},
		{
			.Move = MOVE_POWDER_SNOW,
			.Level = 8,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 11,
		},
		{
			.Move = MOVE_ENDURE,
			.Level = 14,
		},
		{
			.Move = MOVE_MUD_BOMB,
			.Level = 18,
		},
		{
			.Move = MOVE_ICY_WIND,
			.Level = 21,
		},
		{
			.Move = MOVE_ICE_SHARD,
			.Level = 24,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 28,
		},
		{
			.Move = MOVE_MIST,
			.Level = 35,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 37,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 40,
		},
		{
			.Move = MOVE_BLIZZARD,
			.Level = 44,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 48,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PILOSWINE] = {
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 1,
		},
		{
			.Move = MOVE_PECK,
			.Level = 1,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 1,
		},
		{
			.Move = MOVE_MUD_SPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_POWDER_SNOW,
			.Level = 1,
		},
		{
			.Move = MOVE_MUD_SPORT,
			.Level = 5,
		},
		{
			.Move = MOVE_POWDER_SNOW,
			.Level = 8,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 11,
		},
		{
			.Move = MOVE_ENDURE,
			.Level = 14,
		},
		{
			.Move = MOVE_MUD_BOMB,
			.Level = 18,
		},
		{
			.Move = MOVE_ICY_WIND,
			.Level = 21,
		},
		{
			.Move = MOVE_ICE_FANG,
			.Level = 24,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 28,
		},
		{
			.Move = MOVE_FURY_ATTACK,
			.Level = 33,
		},
		{
			.Move = MOVE_MIST,
			.Level = 37,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 41,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 46,
		},
		{
			.Move = MOVE_BLIZZARD,
			.Level = 52,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 58,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CORSOLA] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 1,
		},
		{
			.Move = MOVE_BUBBLE,
			.Level = 4,
		},
		{
			.Move = MOVE_RECOVER,
			.Level = 8,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 10,
		},
		{
			.Move = MOVE_REFRESH,
			.Level = 13,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 17,
		},
		{
			.Move = MOVE_SPIKE_CANNON,
			.Level = 20,
		},
		{
			.Move = MOVE_LUCKY_CHANT,
			.Level = 23,
		},
		{
			.Move = MOVE_BRINE,
			.Level = 27,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 29,
		},
		{
			.Move = MOVE_ROCK_BLAST,
			.Level = 31,
		},
		{
			.Move = MOVE_ENDURE,
			.Level = 35,
		},
		{
			.Move = MOVE_AQUA_RING,
			.Level = 38,
		},
		{
			.Move = MOVE_POWER_GEM,
			.Level = 41,
		},
		{
			.Move = MOVE_MIRROR_COAT,
			.Level = 45,
		},
		{
			.Move = MOVE_EARTH_POWER,
			.Level = 47,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_REMORAID] = {
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_LOCKON,
			.Level = 6,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 10,
		},
		{
			.Move = MOVE_AURORA_BEAM,
			.Level = 14,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 18,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 22,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 26,
		},
		{
			.Move = MOVE_SIGNAL_BEAM,
			.Level = 30,
		},
		{
			.Move = MOVE_ICE_BEAM,
			.Level = 34,
		},
		{
			.Move = MOVE_BULLET_SEED,
			.Level = 38,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 42,
		},
		{
			.Move = MOVE_HYPER_BEAM,
			.Level = 46,
		},
		{
			.Move = MOVE_SOAK,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_OCTILLERY] = {
		{
			.Move = MOVE_GUNK_SHOT,
			.Level = 1,
		},
		{
			.Move = MOVE_ROCK_BLAST,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_CONSTRICT,
			.Level = 1,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 1,
		},
		{
			.Move = MOVE_AURORA_BEAM,
			.Level = 1,
		},
		{
			.Move = MOVE_CONSTRICT,
			.Level = 6,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 10,
		},
		{
			.Move = MOVE_AURORA_BEAM,
			.Level = 14,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 18,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 22,
		},
		{
			.Move = MOVE_OCTAZOOKA,
			.Level = 25,
		},
		{
			.Move = MOVE_WRING_OUT,
			.Level = 28,
		},
		{
			.Move = MOVE_SIGNAL_BEAM,
			.Level = 34,
		},
		{
			.Move = MOVE_ICE_BEAM,
			.Level = 40,
		},
		{
			.Move = MOVE_BULLET_SEED,
			.Level = 46,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 52,
		},
		{
			.Move = MOVE_HYPER_BEAM,
			.Level = 58,
		},
		{
			.Move = MOVE_SOAK,
			.Level = 64,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_DELIBIRD] = {
		{
			.Move = MOVE_PRESENT,
			.Level = 1,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MANTINE] = {
		{
			.Move = MOVE_PSYBEAM,
			.Level = 1,
		},
		{
			.Move = MOVE_BULLET_SEED,
			.Level = 1,
		},
		{
			.Move = MOVE_SIGNAL_BEAM,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_BUBBLE,
			.Level = 1,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 1,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 1,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 3,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 7,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 11,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 14,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 16,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 19,
		},
		{
			.Move = MOVE_WIDE_GUARD,
			.Level = 23,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 27,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 32,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 36,
		},
		{
			.Move = MOVE_AQUA_RING,
			.Level = 39,
		},
		{
			.Move = MOVE_BOUNCE,
			.Level = 46,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 49,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SKARMORY] = {
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_PECK,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 6,
		},
		{
			.Move = MOVE_METAL_CLAW,
			.Level = 9,
		},
		{
			.Move = MOVE_AIR_CUTTER,
			.Level = 12,
		},
		{
			.Move = MOVE_FURY_ATTACK,
			.Level = 17,
		},
		{
			.Move = MOVE_FEINT,
			.Level = 20,
		},
		{
			.Move = MOVE_SWIFT,
			.Level = 23,
		},
		{
			.Move = MOVE_SPIKES,
			.Level = 28,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 31,
		},
		{
			.Move = MOVE_STEEL_WING,
			.Level = 34,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 39,
		},
		{
			.Move = MOVE_METAL_SOUND,
			.Level = 42,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 45,
		},
		{
			.Move = MOVE_AUTOTOMIZE,
			.Level = 50,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 53,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_HOUNDOUR] = {
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 1,
		},
		{
			.Move = MOVE_HOWL,
			.Level = 4,
		},
		{
			.Move = MOVE_SMOG,
			.Level = 8,
		},
		{
			.Move = MOVE_ROAR,
			.Level = 13,
		},
		{
			.Move = MOVE_BITE,
			.Level = 16,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 20,
		},
		{
			.Move = MOVE_BEAT_UP,
			.Level = 25,
		},
		{
			.Move = MOVE_FIRE_FANG,
			.Level = 28,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 32,
		},
		{
			.Move = MOVE_EMBARGO,
			.Level = 37,
		},
		{
			.Move = MOVE_FOUL_PLAY,
			.Level = 40,
		},
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 44,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 49,
		},
		{
			.Move = MOVE_NASTY_PLOT,
			.Level = 52,
		},
		{
			.Move = MOVE_INFERNO,
			.Level = 56,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_HOUNDOOM] = {
		{
			.Move = MOVE_INFERNO,
			.Level = 1,
		},
		{
			.Move = MOVE_NASTY_PLOT,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 1,
		},
		{
			.Move = MOVE_HOWL,
			.Level = 1,
		},
		{
			.Move = MOVE_SMOG,
			.Level = 1,
		},
		{
			.Move = MOVE_HOWL,
			.Level = 4,
		},
		{
			.Move = MOVE_SMOG,
			.Level = 8,
		},
		{
			.Move = MOVE_ROAR,
			.Level = 13,
		},
		{
			.Move = MOVE_BITE,
			.Level = 16,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 20,
		},
		{
			.Move = MOVE_BEAT_UP,
			.Level = 26,
		},
		{
			.Move = MOVE_FIRE_FANG,
			.Level = 30,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 35,
		},
		{
			.Move = MOVE_EMBARGO,
			.Level = 41,
		},
		{
			.Move = MOVE_FOUL_PLAY,
			.Level = 45,
		},
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 50,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 56,
		},
		{
			.Move = MOVE_NASTY_PLOT,
			.Level = 60,
		},
		{
			.Move = MOVE_INFERNO,
			.Level = 65,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_KINGDRA] = {
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 1,
		},
		{
			.Move = MOVE_YAWN,
			.Level = 1,
		},
		{
			.Move = MOVE_BUBBLE,
			.Level = 1,
		},
		{
			.Move = MOVE_SMOKESCREEN,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_SMOKESCREEN,
			.Level = 5,
		},
		{
			.Move = MOVE_LEER,
			.Level = 9,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 13,
		},
		{
			.Move = MOVE_TWISTER,
			.Level = 17,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 21,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 26,
		},
		{
			.Move = MOVE_BRINE,
			.Level = 31,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 38,
		},
		{
			.Move = MOVE_DRAGON_PULSE,
			.Level = 45,
		},
		{
			.Move = MOVE_DRAGON_DANCE,
			.Level = 52,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 60,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PHANPY] = {
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 1,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 6,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 10,
		},
		{
			.Move = MOVE_NATURAL_GIFT,
			.Level = 15,
		},
		{
			.Move = MOVE_ENDURE,
			.Level = 19,
		},
		{
			.Move = MOVE_SLAM,
			.Level = 24,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 28,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 33,
		},
		{
			.Move = MOVE_LAST_RESORT,
			.Level = 37,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 42,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_DONPHAN] = {
		{
			.Move = MOVE_FIRE_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_HORN_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_BULLDOZE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 1,
		},
		{
			.Move = MOVE_RAPID_SPIN,
			.Level = 6,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 10,
		},
		{
			.Move = MOVE_ASSURANCE,
			.Level = 15,
		},
		{
			.Move = MOVE_KNOCK_OFF,
			.Level = 19,
		},
		{
			.Move = MOVE_SLAM,
			.Level = 24,
		},
		{
			.Move = MOVE_FURY_ATTACK,
			.Level = 25,
		},
		{
			.Move = MOVE_MAGNITUDE,
			.Level = 30,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 37,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 43,
		},
		{
			.Move = MOVE_GIGA_IMPACT,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PORYGON2] = {
		{
			.Move = MOVE_ZAP_CANNON,
			.Level = 1,
		},
		{
			.Move = MOVE_MAGIC_COAT,
			.Level = 1,
		},
		{
			.Move = MOVE_CONVERSION_2,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_CONVERSION,
			.Level = 1,
		},
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 1,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 7,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 12,
		},
		{
			.Move = MOVE_RECOVER,
			.Level = 18,
		},
		{
			.Move = MOVE_MAGNET_RISE,
			.Level = 23,
		},
		{
			.Move = MOVE_SIGNAL_BEAM,
			.Level = 29,
		},
		{
			.Move = MOVE_RECYCLE,
			.Level = 34,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 40,
		},
		{
			.Move = MOVE_LOCKON,
			.Level = 45,
		},
		{
			.Move = MOVE_TRI_ATTACK,
			.Level = 50,
		},
		{
			.Move = MOVE_MAGIC_COAT,
			.Level = 56,
		},
		{
			.Move = MOVE_ZAP_CANNON,
			.Level = 62,
		},
		{
			.Move = MOVE_HYPER_BEAM,
			.Level = 67,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_STANTLER] = {
		{
			.Move = MOVE_ME_FIRST,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 3,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 7,
		},
		{
			.Move = MOVE_HYPNOSIS,
			.Level = 10,
		},
		{
			.Move = MOVE_STOMP,
			.Level = 13,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 16,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 21,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 23,
		},
		{
			.Move = MOVE_CALM_MIND,
			.Level = 27,
		},
		{
			.Move = MOVE_ROLE_PLAY,
			.Level = 33,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 38,
		},
		{
			.Move = MOVE_JUMP_KICK,
			.Level = 43,
		},
		{
			.Move = MOVE_IMPRISON,
			.Level = 49,
		},
		{
			.Move = MOVE_CAPTIVATE,
			.Level = 50,
		},
		{
			.Move = MOVE_ME_FIRST,
			.Level = 55,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SMEARGLE] = {
		{
			.Move = MOVE_SKETCH,
			.Level = 1,
		},
		{
			.Move = MOVE_SKETCH,
			.Level = 11,
		},
		{
			.Move = MOVE_SKETCH,
			.Level = 21,
		},
		{
			.Move = MOVE_SKETCH,
			.Level = 31,
		},
		{
			.Move = MOVE_SKETCH,
			.Level = 41,
		},
		{
			.Move = MOVE_SKETCH,
			.Level = 51,
		},
		{
			.Move = MOVE_SKETCH,
			.Level = 61,
		},
		{
			.Move = MOVE_SKETCH,
			.Level = 71,
		},
		{
			.Move = MOVE_SKETCH,
			.Level = 81,
		},
		{
			.Move = MOVE_SKETCH,
			.Level = 91,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_TYROGUE] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 1,
		},
		{
			.Move = MOVE_FAKE_OUT,
			.Level = 1,
		},
		{
			.Move = MOVE_FORESIGHT,
			.Level = 1,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_HITMONTOP] = {
		{
			.Move = MOVE_ENDEAVOR,
			.Level = 1,
		},
		{
			.Move = MOVE_CLOSE_COMBAT,
			.Level = 1,
		},
		{
			.Move = MOVE_REVENGE,
			.Level = 1,
		},
		{
			.Move = MOVE_ROLLING_KICK,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 6,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 10,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 15,
		},
		{
			.Move = MOVE_TRIPLE_KICK,
			.Level = 19,
		},
		{
			.Move = MOVE_RAPID_SPIN,
			.Level = 24,
		},
		{
			.Move = MOVE_COUNTER,
			.Level = 28,
		},
		{
			.Move = MOVE_FEINT,
			.Level = 33,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 37,
		},
		{
			.Move = MOVE_GYRO_BALL,
			.Level = 42,
		},
		{
			.Move = MOVE_WIDE_GUARD,
			.Level = 46,
		},
		{
			.Move = MOVE_QUICK_GUARD,
			.Level = 46,
		},
		{
			.Move = MOVE_DETECT,
			.Level = 50,
		},
		{
			.Move = MOVE_CLOSE_COMBAT,
			.Level = 55,
		},
		{
			.Move = MOVE_ENDEAVOR,
			.Level = 60,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SMOOCHUM] = {
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_LICK,
			.Level = 5,
		},
		{
			.Move = MOVE_SWEET_KISS,
			.Level = 8,
		},
		{
			.Move = MOVE_POWDER_SNOW,
			.Level = 11,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 15,
		},
		{
			.Move = MOVE_SING,
			.Level = 18,
		},
		{
			.Move = MOVE_HEART_STAMP,
			.Level = 21,
		},
		{
			.Move = MOVE_MEAN_LOOK,
			.Level = 25,
		},
		{
			.Move = MOVE_FAKE_TEARS,
			.Level = 28,
		},
		{
			.Move = MOVE_LUCKY_CHANT,
			.Level = 31,
		},
		{
			.Move = MOVE_AVALANCHE,
			.Level = 35,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 38,
		},
		{
			.Move = MOVE_COPYCAT,
			.Level = 41,
		},
		{
			.Move = MOVE_PERISH_SONG,
			.Level = 45,
		},
		{
			.Move = MOVE_BLIZZARD,
			.Level = 48,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ELEKID] = {
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 5,
		},
		{
			.Move = MOVE_LOW_KICK,
			.Level = 8,
		},
		{
			.Move = MOVE_SWIFT,
			.Level = 12,
		},
		{
			.Move = MOVE_SHOCK_WAVE,
			.Level = 15,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 19,
		},
		{
			.Move = MOVE_ELECTRO_BALL,
			.Level = 22,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 26,
		},
		{
			.Move = MOVE_THUNDERPUNCH,
			.Level = 29,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 33,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 36,
		},
		{
			.Move = MOVE_THUNDERBOLT,
			.Level = 40,
		},
		{
			.Move = MOVE_THUNDER,
			.Level = 43,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MAGBY] = {
		{
			.Move = MOVE_SMOG,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 5,
		},
		{
			.Move = MOVE_SMOKESCREEN,
			.Level = 8,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 12,
		},
		{
			.Move = MOVE_FIRE_SPIN,
			.Level = 15,
		},
		{
			.Move = MOVE_CLEAR_SMOG,
			.Level = 19,
		},
		{
			.Move = MOVE_FLAME_BURST,
			.Level = 22,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 26,
		},
		{
			.Move = MOVE_FIRE_PUNCH,
			.Level = 29,
		},
		{
			.Move = MOVE_LAVA_PLUME,
			.Level = 33,
		},
		{
			.Move = MOVE_SUNNY_DAY,
			.Level = 36,
		},
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 40,
		},
		{
			.Move = MOVE_FIRE_BLAST,
			.Level = 43,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MILTANK] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 3,
		},
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 5,
		},
		{
			.Move = MOVE_STOMP,
			.Level = 8,
		},
		{
			.Move = MOVE_MILK_DRINK,
			.Level = 11,
		},
		{
			.Move = MOVE_BIDE,
			.Level = 15,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 19,
		},
		{
			.Move = MOVE_BODY_SLAM,
			.Level = 24,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 29,
		},
		{
			.Move = MOVE_CAPTIVATE,
			.Level = 35,
		},
		{
			.Move = MOVE_GYRO_BALL,
			.Level = 41,
		},
		{
			.Move = MOVE_HEAL_BELL,
			.Level = 48,
		},
		{
			.Move = MOVE_WAKEUP_SLAP,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BLISSEY] = {
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 1,
		},
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 1,
		},
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 5,
		},
		{
			.Move = MOVE_REFRESH,
			.Level = 9,
		},
		{
			.Move = MOVE_DOUBLESLAP,
			.Level = 12,
		},
		{
			.Move = MOVE_SOFTBOILED,
			.Level = 16,
		},
		{
			.Move = MOVE_BESTOW,
			.Level = 20,
		},
		{
			.Move = MOVE_MINIMIZE,
			.Level = 23,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 27,
		},
		{
			.Move = MOVE_SING,
			.Level = 31,
		},
		{
			.Move = MOVE_FLING,
			.Level = 34,
		},
		{
			.Move = MOVE_HEAL_PULSE,
			.Level = 38,
		},
		{
			.Move = MOVE_EGG_BOMB,
			.Level = 42,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 46,
		},
		{
			.Move = MOVE_HEALING_WISH,
			.Level = 50,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 54,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_RAIKOU] = {
		{
			.Move = MOVE_EXTRASENSORY,
			.Level = 1,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 8,
		},
		{
			.Move = MOVE_ROAR,
			.Level = 15,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 22,
		},
		{
			.Move = MOVE_SPARK,
			.Level = 29,
		},
		{
			.Move = MOVE_REFLECT,
			.Level = 36,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 43,
		},
		{
			.Move = MOVE_THUNDER_FANG,
			.Level = 50,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 57,
		},
		{
			.Move = MOVE_EXTRASENSORY,
			.Level = 64,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 71,
		},
		{
			.Move = MOVE_CALM_MIND,
			.Level = 78,
		},
		{
			.Move = MOVE_THUNDER,
			.Level = 85,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ENTEI] = {
		{
			.Move = MOVE_SACRED_FIRE,
			.Level = 1,
		},
		{
			.Move = MOVE_ERUPTION,
			.Level = 1,
		},
		{
			.Move = MOVE_EXTRASENSORY,
			.Level = 1,
		},
		{
			.Move = MOVE_LAVA_PLUME,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 8,
		},
		{
			.Move = MOVE_ROAR,
			.Level = 15,
		},
		{
			.Move = MOVE_FIRE_SPIN,
			.Level = 22,
		},
		{
			.Move = MOVE_STOMP,
			.Level = 29,
		},
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 36,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 43,
		},
		{
			.Move = MOVE_FIRE_FANG,
			.Level = 50,
		},
		{
			.Move = MOVE_LAVA_PLUME,
			.Level = 57,
		},
		{
			.Move = MOVE_EXTRASENSORY,
			.Level = 64,
		},
		{
			.Move = MOVE_FIRE_BLAST,
			.Level = 71,
		},
		{
			.Move = MOVE_CALM_MIND,
			.Level = 78,
		},
		{
			.Move = MOVE_ERUPTION,
			.Level = 85,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SUICUNE] = {
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 1,
		},
		{
			.Move = MOVE_EXTRASENSORY,
			.Level = 1,
		},
		{
			.Move = MOVE_TAILWIND,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 8,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 15,
		},
		{
			.Move = MOVE_GUST,
			.Level = 22,
		},
		{
			.Move = MOVE_AURORA_BEAM,
			.Level = 29,
		},
		{
			.Move = MOVE_MIST,
			.Level = 36,
		},
		{
			.Move = MOVE_MIRROR_COAT,
			.Level = 43,
		},
		{
			.Move = MOVE_ICE_FANG,
			.Level = 50,
		},
		{
			.Move = MOVE_TAILWIND,
			.Level = 57,
		},
		{
			.Move = MOVE_EXTRASENSORY,
			.Level = 64,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 71,
		},
		{
			.Move = MOVE_CALM_MIND,
			.Level = 78,
		},
		{
			.Move = MOVE_BLIZZARD,
			.Level = 85,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_LARVITAR] = {
		{
			.Move = MOVE_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDSTORM,
			.Level = 5,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 10,
		},
		{
			.Move = MOVE_CHIP_AWAY,
			.Level = 14,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 19,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 23,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 28,
		},
		{
			.Move = MOVE_DARK_PULSE,
			.Level = 32,
		},
		{
			.Move = MOVE_PAYBACK,
			.Level = 37,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 41,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 46,
		},
		{
			.Move = MOVE_STONE_EDGE,
			.Level = 50,
		},
		{
			.Move = MOVE_HYPER_BEAM,
			.Level = 55,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PUPITAR] = {
		{
			.Move = MOVE_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDSTORM,
			.Level = 1,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDSTORM,
			.Level = 5,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 10,
		},
		{
			.Move = MOVE_CHIP_AWAY,
			.Level = 14,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 19,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 23,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 28,
		},
		{
			.Move = MOVE_DARK_PULSE,
			.Level = 34,
		},
		{
			.Move = MOVE_PAYBACK,
			.Level = 41,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 47,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 54,
		},
		{
			.Move = MOVE_STONE_EDGE,
			.Level = 60,
		},
		{
			.Move = MOVE_HYPER_BEAM,
			.Level = 67,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_TYRANITAR] = {
		{
			.Move = MOVE_THUNDER_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_ICE_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_FIRE_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDSTORM,
			.Level = 1,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDSTORM,
			.Level = 5,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 10,
		},
		{
			.Move = MOVE_CHIP_AWAY,
			.Level = 14,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 19,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 23,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 28,
		},
		{
			.Move = MOVE_DARK_PULSE,
			.Level = 34,
		},
		{
			.Move = MOVE_PAYBACK,
			.Level = 41,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 47,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 54,
		},
		{
			.Move = MOVE_STONE_EDGE,
			.Level = 63,
		},
		{
			.Move = MOVE_HYPER_BEAM,
			.Level = 73,
		},
		{
			.Move = MOVE_GIGA_IMPACT,
			.Level = 82,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_LUGIA] = {
		{
			.Move = MOVE_WHIRLWIND,
			.Level = 1,
		},
		{
			.Move = MOVE_WEATHER_BALL,
			.Level = 1,
		},
		{
			.Move = MOVE_GUST,
			.Level = 9,
		},
		{
			.Move = MOVE_DRAGON_RUSH,
			.Level = 15,
		},
		{
			.Move = MOVE_EXTRASENSORY,
			.Level = 23,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 29,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 37,
		},
		{
			.Move = MOVE_AEROBLAST,
			.Level = 43,
		},
		{
			.Move = MOVE_PUNISHMENT,
			.Level = 50,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 57,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 65,
		},
		{
			.Move = MOVE_RECOVER,
			.Level = 71,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 79,
		},
		{
			.Move = MOVE_NATURAL_GIFT,
			.Level = 85,
		},
		{
			.Move = MOVE_CALM_MIND,
			.Level = 93,
		},
		{
			.Move = MOVE_SKY_ATTACK,
			.Level = 99,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_HOOH] = {
		{
			.Move = MOVE_WHIRLWIND,
			.Level = 1,
		},
		{
			.Move = MOVE_WEATHER_BALL,
			.Level = 1,
		},
		{
			.Move = MOVE_GUST,
			.Level = 9,
		},
		{
			.Move = MOVE_BRAVE_BIRD,
			.Level = 15,
		},
		{
			.Move = MOVE_EXTRASENSORY,
			.Level = 23,
		},
		{
			.Move = MOVE_SUNNY_DAY,
			.Level = 29,
		},
		{
			.Move = MOVE_FIRE_BLAST,
			.Level = 37,
		},
		{
			.Move = MOVE_SACRED_FIRE,
			.Level = 43,
		},
		{
			.Move = MOVE_PUNISHMENT,
			.Level = 50,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 57,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 65,
		},
		{
			.Move = MOVE_RECOVER,
			.Level = 71,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 79,
		},
		{
			.Move = MOVE_NATURAL_GIFT,
			.Level = 85,
		},
		{
			.Move = MOVE_CALM_MIND,
			.Level = 93,
		},
		{
			.Move = MOVE_SKY_ATTACK,
			.Level = 99,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CELEBI] = {
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_RECOVER,
			.Level = 1,
		},
		{
			.Move = MOVE_HEAL_BELL,
			.Level = 1,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 10,
		},
		{
			.Move = MOVE_MAGICAL_LEAF,
			.Level = 19,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 28,
		},
		{
			.Move = MOVE_BATON_PASS,
			.Level = 37,
		},
		{
			.Move = MOVE_NATURAL_GIFT,
			.Level = 46,
		},
		{
			.Move = MOVE_HEAL_BLOCK,
			.Level = 55,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 64,
		},
		{
			.Move = MOVE_HEALING_WISH,
			.Level = 73,
		},
		{
			.Move = MOVE_LEAF_STORM,
			.Level = 82,
		},
		{
			.Move = MOVE_PERISH_SONG,
			.Level = 91,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_TREECKO] = {
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_ABSORB,
			.Level = 5,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 9,
		},
		{
			.Move = MOVE_MEGA_DRAIN,
			.Level = 13,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 17,
		},
		{
			.Move = MOVE_GIGA_DRAIN,
			.Level = 21,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 25,
		},
		{
			.Move = MOVE_SLAM,
			.Level = 29,
		},
		{
			.Move = MOVE_DETECT,
			.Level = 33,
		},
		{
			.Move = MOVE_ENERGY_BALL,
			.Level = 37,
		},
		{
			.Move = MOVE_QUICK_GUARD,
			.Level = 41,
		},
		{
			.Move = MOVE_ENDEAVOR,
			.Level = 45,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 49,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GROVYLE] = {
		{
			.Move = MOVE_LEAF_BLADE,
			.Level = 1,
		},
		{
			.Move = MOVE_AERIAL_ACE,
			.Level = 1,
		},
		{
			.Move = MOVE_SLAM,
			.Level = 1,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 1,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SCEPTILE] = {
		{
			.Move = MOVE_LEAF_BLADE,
			.Level = 1,
		},
		{
			.Move = MOVE_AERIAL_ACE,
			.Level = 1,
		},
		{
			.Move = MOVE_SLAM,
			.Level = 1,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 1,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_TORCHIC] = {
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 5,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 10,
		},
		{
			.Move = MOVE_PECK,
			.Level = 14,
		},
		{
			.Move = MOVE_FIRE_SPIN,
			.Level = 19,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 23,
		},
		{
			.Move = MOVE_FLAME_BURST,
			.Level = 28,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 32,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 37,
		},
		{
			.Move = MOVE_MIRROR_MOVE,
			.Level = 41,
		},
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 46,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_COMBUSKEN] = {
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 1,
		},
		{
			.Move = MOVE_DOUBLE_KICK,
			.Level = 1,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 1,
		},
		{
			.Move = MOVE_BULK_UP,
			.Level = 1,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BLAZIKEN] = {
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 1,
		},
		{
			.Move = MOVE_DOUBLE_KICK,
			.Level = 1,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 1,
		},
		{
			.Move = MOVE_BULK_UP,
			.Level = 1,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MUDKIP] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 4,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 9,
		},
		{
			.Move = MOVE_FORESIGHT,
			.Level = 12,
		},
		{
			.Move = MOVE_BIDE,
			.Level = 17,
		},
		{
			.Move = MOVE_MUD_SPORT,
			.Level = 20,
		},
		{
			.Move = MOVE_ROCK_THROW,
			.Level = 25,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 28,
		},
		{
			.Move = MOVE_WHIRLPOOL,
			.Level = 33,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 36,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 41,
		},
		{
			.Move = MOVE_ENDEAVOR,
			.Level = 44,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MARSHTOMP] = {
		{
			.Move = MOVE_WATERFALL,
			.Level = 1,
		},
		{
			.Move = MOVE_MUD_BOMB,
			.Level = 1,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 1,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 1,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SWAMPERT] = {
		{
			.Move = MOVE_WATERFALL,
			.Level = 1,
		},
		{
			.Move = MOVE_MUD_BOMB,
			.Level = 1,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 1,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 1,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_POOCHYENA] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_HOWL,
			.Level = 4,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 7,
		},
		{
			.Move = MOVE_BITE,
			.Level = 10,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 13,
		},
		{
			.Move = MOVE_ROAR,
			.Level = 16,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 19,
		},
		{
			.Move = MOVE_ASSURANCE,
			.Level = 22,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 25,
		},
		{
			.Move = MOVE_EMBARGO,
			.Level = 28,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 30,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 34,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 37,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 40,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MIGHTYENA] = {
		{
			.Move = MOVE_CRUNCH,
			.Level = 1,
		},
		{
			.Move = MOVE_THIEF,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_HOWL,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_HOWL,
			.Level = 4,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 7,
		},
		{
			.Move = MOVE_BITE,
			.Level = 10,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 13,
		},
		{
			.Move = MOVE_ROAR,
			.Level = 16,
		},
		{
			.Move = MOVE_SNARL,
			.Level = 18,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 20,
		},
		{
			.Move = MOVE_ASSURANCE,
			.Level = 24,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 28,
		},
		{
			.Move = MOVE_EMBARGO,
			.Level = 32,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 36,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 40,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 44,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 48,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ZIGZAGOON] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 5,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 7,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 11,
		},
		{
			.Move = MOVE_BABYDOLL_EYES,
			.Level = 12,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 13,
		},
		{
			.Move = MOVE_MUD_SPORT,
			.Level = 17,
		},
		{
			.Move = MOVE_PIN_MISSILE,
			.Level = 19,
		},
		{
			.Move = MOVE_COVET,
			.Level = 23,
		},
		{
			.Move = MOVE_BESTOW,
			.Level = 25,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 29,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 31,
		},
		{
			.Move = MOVE_REST,
			.Level = 35,
		},
		{
			.Move = MOVE_BELLY_DRUM,
			.Level = 37,
		},
		{
			.Move = MOVE_FLING,
			.Level = 41,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_LINOONE] = {
		{
			.Move = MOVE_PLAY_ROUGH,
			.Level = 1,
		},
		{
			.Move = MOVE_ROTOTILLER,
			.Level = 1,
		},
		{
			.Move = MOVE_SWITCHEROO,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 5,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 7,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 11,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 13,
		},
		{
			.Move = MOVE_MUD_SPORT,
			.Level = 17,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 19,
		},
		{
			.Move = MOVE_COVET,
			.Level = 24,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_WURMPLE] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_STRING_SHOT,
			.Level = 1,
		},
		{
			.Move = MOVE_POISON_STING,
			.Level = 5,
		},
		{
			.Move = MOVE_BUG_BITE,
			.Level = 15,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SILCOON] = {
		{
			.Move = MOVE_HARDEN,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 7,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BEAUTIFLY] = {
		{
			.Move = MOVE_GUST,
			.Level = 1,
		},
		{
			.Move = MOVE_GUST,
			.Level = 10,
		},
		{
			.Move = MOVE_ABSORB,
			.Level = 12,
		},
		{
			.Move = MOVE_STUN_SPORE,
			.Level = 15,
		},
		{
			.Move = MOVE_MORNING_SUN,
			.Level = 17,
		},
		{
			.Move = MOVE_AIR_CUTTER,
			.Level = 20,
		},
		{
			.Move = MOVE_MEGA_DRAIN,
			.Level = 22,
		},
		{
			.Move = MOVE_SILVER_WIND,
			.Level = 25,
		},
		{
			.Move = MOVE_ATTRACT,
			.Level = 27,
		},
		{
			.Move = MOVE_WHIRLWIND,
			.Level = 30,
		},
		{
			.Move = MOVE_GIGA_DRAIN,
			.Level = 32,
		},
		{
			.Move = MOVE_BUG_BUZZ,
			.Level = 35,
		},
		{
			.Move = MOVE_RAGE,
			.Level = 37,
		},
		{
			.Move = MOVE_QUIVER_DANCE,
			.Level = 40,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CASCOON] = {
		{
			.Move = MOVE_HARDEN,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 7,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_DUSTOX] = {
		{
			.Move = MOVE_GUST,
			.Level = 1,
		},
		{
			.Move = MOVE_GUST,
			.Level = 10,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 12,
		},
		{
			.Move = MOVE_POISONPOWDER,
			.Level = 15,
		},
		{
			.Move = MOVE_MOONLIGHT,
			.Level = 17,
		},
		{
			.Move = MOVE_VENOSHOCK,
			.Level = 20,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 22,
		},
		{
			.Move = MOVE_SILVER_WIND,
			.Level = 25,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 27,
		},
		{
			.Move = MOVE_WHIRLWIND,
			.Level = 30,
		},
		{
			.Move = MOVE_TOXIC,
			.Level = 32,
		},
		{
			.Move = MOVE_BUG_BUZZ,
			.Level = 35,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 37,
		},
		{
			.Move = MOVE_QUIVER_DANCE,
			.Level = 40,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_LOTAD] = {
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 3,
		},
		{
			.Move = MOVE_ABSORB,
			.Level = 6,
		},
		{
			.Move = MOVE_BUBBLE,
			.Level = 9,
		},
		{
			.Move = MOVE_NATURAL_GIFT,
			.Level = 12,
		},
		{
			.Move = MOVE_MIST,
			.Level = 15,
		},
		{
			.Move = MOVE_MEGA_DRAIN,
			.Level = 18,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 21,
		},
		{
			.Move = MOVE_NATURE_POWER,
			.Level = 24,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 27,
		},
		{
			.Move = MOVE_GIGA_DRAIN,
			.Level = 30,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 33,
		},
		{
			.Move = MOVE_ENERGY_BALL,
			.Level = 36,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_LOMBRE] = {
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 3,
		},
		{
			.Move = MOVE_ABSORB,
			.Level = 6,
		},
		{
			.Move = MOVE_BUBBLE,
			.Level = 9,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 12,
		},
		{
			.Move = MOVE_FAKE_OUT,
			.Level = 16,
		},
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 20,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 24,
		},
		{
			.Move = MOVE_NATURE_POWER,
			.Level = 28,
		},
		{
			.Move = MOVE_UPROAR,
			.Level = 32,
		},
		{
			.Move = MOVE_KNOCK_OFF,
			.Level = 36,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 40,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 44,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_LUDICOLO] = {
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_MEGA_DRAIN,
			.Level = 1,
		},
		{
			.Move = MOVE_NATURE_POWER,
			.Level = 1,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SEEDOT] = {
		{
			.Move = MOVE_BIDE,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 3,
		},
		{
			.Move = MOVE_GROWTH,
			.Level = 9,
		},
		{
			.Move = MOVE_NATURE_POWER,
			.Level = 15,
		},
		{
			.Move = MOVE_SYNTHESIS,
			.Level = 21,
		},
		{
			.Move = MOVE_SUNNY_DAY,
			.Level = 27,
		},
		{
			.Move = MOVE_EXPLOSION,
			.Level = 33,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_NUZLEAF] = {
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 3,
		},
		{
			.Move = MOVE_GROWTH,
			.Level = 6,
		},
		{
			.Move = MOVE_NATURE_POWER,
			.Level = 9,
		},
		{
			.Move = MOVE_FAKE_OUT,
			.Level = 12,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 14,
		},
		{
			.Move = MOVE_TORMENT,
			.Level = 16,
		},
		{
			.Move = MOVE_RAZOR_WIND,
			.Level = 20,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 24,
		},
		{
			.Move = MOVE_LEAF_BLADE,
			.Level = 28,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 32,
		},
		{
			.Move = MOVE_EXTRASENSORY,
			.Level = 36,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SHIFTRY] = {
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 1,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_WHIRLWIND,
			.Level = 1,
		},
		{
			.Move = MOVE_NASTY_PLOT,
			.Level = 1,
		},
		{
			.Move = MOVE_LEAF_TORNADO,
			.Level = 20,
		},
		{
			.Move = MOVE_HURRICANE,
			.Level = 32,
		},
		{
			.Move = MOVE_LEAF_STORM,
			.Level = 44,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_TAILLOW] = {
		{
			.Move = MOVE_PECK,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 5,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 9,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 13,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 17,
		},
		{
			.Move = MOVE_AERIAL_ACE,
			.Level = 21,
		},
		{
			.Move = MOVE_QUICK_GUARD,
			.Level = 25,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 29,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 33,
		},
		{
			.Move = MOVE_ENDEAVOR,
			.Level = 37,
		},
		{
			.Move = MOVE_BRAVE_BIRD,
			.Level = 41,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SWELLOW] = {
		{
			.Move = MOVE_BRAVE_BIRD,
			.Level = 1,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 1,
		},
		{
			.Move = MOVE_PLUCK,
			.Level = 1,
		},
		{
			.Move = MOVE_PECK,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 5,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 9,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 13,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 17,
		},
		{
			.Move = MOVE_AERIAL_ACE,
			.Level = 21,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_WINGULL] = {
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 5,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 8,
		},
		{
			.Move = MOVE_MIST,
			.Level = 12,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 15,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 19,
		},
		{
			.Move = MOVE_AIR_CUTTER,
			.Level = 22,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 26,
		},
		{
			.Move = MOVE_AERIAL_ACE,
			.Level = 29,
		},
		{
			.Move = MOVE_ROOST,
			.Level = 33,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 36,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 40,
		},
		{
			.Move = MOVE_HURRICANE,
			.Level = 43,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PELIPPER] = {
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 1,
		},
		{
			.Move = MOVE_TAILWIND,
			.Level = 1,
		},
		{
			.Move = MOVE_SOAK,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 5,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 8,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 12,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 15,
		},
		{
			.Move = MOVE_PAYBACK,
			.Level = 19,
		},
		{
			.Move = MOVE_ROOST,
			.Level = 22,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 25,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_RALTS] = {
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 4,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 6,
		},
		{
			.Move = MOVE_TELEPORT,
			.Level = 9,
		},
		{
			.Move = MOVE_DISARMING_VOICE,
			.Level = 11,
		},
		{
			.Move = MOVE_LUCKY_CHANT,
			.Level = 14,
		},
		{
			.Move = MOVE_MAGICAL_LEAF,
			.Level = 17,
		},
		{
			.Move = MOVE_HEAL_PULSE,
			.Level = 19,
		},
		{
			.Move = MOVE_DRAINING_KISS,
			.Level = 22,
		},
		{
			.Move = MOVE_CALM_MIND,
			.Level = 24,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 27,
		},
		{
			.Move = MOVE_IMPRISON,
			.Level = 29,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 32,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 34,
		},
		{
			.Move = MOVE_HYPNOSIS,
			.Level = 37,
		},
		{
			.Move = MOVE_DREAM_EATER,
			.Level = 39,
		},
		{
			.Move = MOVE_STORED_POWER,
			.Level = 42,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_KIRLIA] = {
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 1,
		},
		{
			.Move = MOVE_TELEPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 4,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 6,
		},
		{
			.Move = MOVE_TELEPORT,
			.Level = 9,
		},
		{
			.Move = MOVE_DISARMING_VOICE,
			.Level = 11,
		},
		{
			.Move = MOVE_LUCKY_CHANT,
			.Level = 14,
		},
		{
			.Move = MOVE_MAGICAL_LEAF,
			.Level = 17,
		},
		{
			.Move = MOVE_HEAL_PULSE,
			.Level = 19,
		},
		{
			.Move = MOVE_DRAINING_KISS,
			.Level = 23,
		},
		{
			.Move = MOVE_CALM_MIND,
			.Level = 26,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 30,
		},
		{
			.Move = MOVE_IMPRISON,
			.Level = 33,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 37,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 40,
		},
		{
			.Move = MOVE_HYPNOSIS,
			.Level = 44,
		},
		{
			.Move = MOVE_DREAM_EATER,
			.Level = 47,
		},
		{
			.Move = MOVE_STORED_POWER,
			.Level = 51,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GARDEVOIR] = {
		{
			.Move = MOVE_MOONBLAST,
			.Level = 1,
		},
		{
			.Move = MOVE_STORED_POWER,
			.Level = 1,
		},
		{
			.Move = MOVE_MISTY_TERRAIN,
			.Level = 1,
		},
		{
			.Move = MOVE_HEALING_WISH,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 1,
		},
		{
			.Move = MOVE_TELEPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 4,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 6,
		},
		{
			.Move = MOVE_TELEPORT,
			.Level = 9,
		},
		{
			.Move = MOVE_DISARMING_VOICE,
			.Level = 11,
		},
		{
			.Move = MOVE_WISH,
			.Level = 14,
		},
		{
			.Move = MOVE_MAGICAL_LEAF,
			.Level = 17,
		},
		{
			.Move = MOVE_HEAL_PULSE,
			.Level = 19,
		},
		{
			.Move = MOVE_DRAINING_KISS,
			.Level = 23,
		},
		{
			.Move = MOVE_CALM_MIND,
			.Level = 26,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 31,
		},
		{
			.Move = MOVE_IMPRISON,
			.Level = 35,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 40,
		},
		{
			.Move = MOVE_CAPTIVATE,
			.Level = 44,
		},
		{
			.Move = MOVE_HYPNOSIS,
			.Level = 49,
		},
		{
			.Move = MOVE_DREAM_EATER,
			.Level = 53,
		},
		{
			.Move = MOVE_STORED_POWER,
			.Level = 58,
		},
		{
			.Move = MOVE_MOONBLAST,
			.Level = 62,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SURSKIT] = {
		{
			.Move = MOVE_BUBBLE,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 6,
		},
		{
			.Move = MOVE_SWEET_SCENT,
			.Level = 9,
		},
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 14,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 17,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 22,
		},
		{
			.Move = MOVE_MIST,
			.Level = 25,
		},
		{
			.Move = MOVE_HAZE,
			.Level = 25,
		},
		{
			.Move = MOVE_AQUA_JET,
			.Level = 30,
		},
		{
			.Move = MOVE_BATON_PASS,
			.Level = 35,
		},
		{
			.Move = MOVE_STICKY_WEB,
			.Level = 38,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MASQUERAIN] = {
		{
			.Move = MOVE_QUIVER_DANCE,
			.Level = 1,
		},
		{
			.Move = MOVE_WHIRLWIND,
			.Level = 1,
		},
		{
			.Move = MOVE_BUG_BUZZ,
			.Level = 1,
		},
		{
			.Move = MOVE_OMINOUS_WIND,
			.Level = 1,
		},
		{
			.Move = MOVE_BUBBLE,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_SWEET_SCENT,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 6,
		},
		{
			.Move = MOVE_SWEET_SCENT,
			.Level = 9,
		},
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 14,
		},
		{
			.Move = MOVE_GUST,
			.Level = 17,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 22,
		},
		{
			.Move = MOVE_AIR_CUTTER,
			.Level = 22,
		},
		{
			.Move = MOVE_STUN_SPORE,
			.Level = 26,
		},
		{
			.Move = MOVE_SILVER_WIND,
			.Level = 32,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 38,
		},
		{
			.Move = MOVE_BUG_BUZZ,
			.Level = 42,
		},
		{
			.Move = MOVE_WHIRLWIND,
			.Level = 48,
		},
		{
			.Move = MOVE_QUIVER_DANCE,
			.Level = 52,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SHROOMISH] = {
		{
			.Move = MOVE_ABSORB,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_STUN_SPORE,
			.Level = 5,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 8,
		},
		{
			.Move = MOVE_MEGA_DRAIN,
			.Level = 12,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 15,
		},
		{
			.Move = MOVE_MEGA_DRAIN,
			.Level = 19,
		},
		{
			.Move = MOVE_WORRY_SEED,
			.Level = 22,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 26,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BRELOOM] = {
		{
			.Move = MOVE_ABSORB,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_STUN_SPORE,
			.Level = 1,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 1,
		},
		{
			.Move = MOVE_STUN_SPORE,
			.Level = 5,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 8,
		},
		{
			.Move = MOVE_MEGA_DRAIN,
			.Level = 12,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 15,
		},
		{
			.Move = MOVE_FEINT,
			.Level = 19,
		},
		{
			.Move = MOVE_COUNTER,
			.Level = 22,
		},
		{
			.Move = MOVE_MACH_PUNCH,
			.Level = 23,
		},
		{
			.Move = MOVE_FORCE_PALM,
			.Level = 28,
		},
		{
			.Move = MOVE_MIND_READER,
			.Level = 33,
		},
		{
			.Move = MOVE_SKY_UPPERCUT,
			.Level = 39,
		},
		{
			.Move = MOVE_SEED_BOMB,
			.Level = 44,
		},
		{
			.Move = MOVE_DYNAMICPUNCH,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SLAKOTH] = {
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_YAWN,
			.Level = 1,
		},
		{
			.Move = MOVE_ENCORE,
			.Level = 6,
		},
		{
			.Move = MOVE_SLACK_OFF,
			.Level = 9,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 14,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 17,
		},
		{
			.Move = MOVE_COVET,
			.Level = 22,
		},
		{
			.Move = MOVE_CHIP_AWAY,
			.Level = 25,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_VIGOROTH] = {
		{
			.Move = MOVE_REVERSAL,
			.Level = 1,
		},
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 1,
		},
		{
			.Move = MOVE_ENCORE,
			.Level = 1,
		},
		{
			.Move = MOVE_UPROAR,
			.Level = 1,
		},
		{
			.Move = MOVE_ENCORE,
			.Level = 6,
		},
		{
			.Move = MOVE_UPROAR,
			.Level = 9,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 14,
		},
		{
			.Move = MOVE_ENDURE,
			.Level = 17,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 23,
		},
		{
			.Move = MOVE_CHIP_AWAY,
			.Level = 27,
		},
		{
			.Move = MOVE_COUNTER,
			.Level = 33,
		},
		{
			.Move = MOVE_FOCUS_PUNCH,
			.Level = 37,
		},
		{
			.Move = MOVE_REVERSAL,
			.Level = 43,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SLAKING] = {
		{
			.Move = MOVE_HAMMER_ARM,
			.Level = 1,
		},
		{
			.Move = MOVE_PUNISHMENT,
			.Level = 1,
		},
		{
			.Move = MOVE_FLING,
			.Level = 1,
		},
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_YAWN,
			.Level = 1,
		},
		{
			.Move = MOVE_ENCORE,
			.Level = 1,
		},
		{
			.Move = MOVE_SLACK_OFF,
			.Level = 1,
		},
		{
			.Move = MOVE_ENCORE,
			.Level = 6,
		},
		{
			.Move = MOVE_SLACK_OFF,
			.Level = 9,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 14,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 17,
		},
		{
			.Move = MOVE_COVET,
			.Level = 23,
		},
		{
			.Move = MOVE_CHIP_AWAY,
			.Level = 27,
		},
		{
			.Move = MOVE_COUNTER,
			.Level = 33,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 36,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 39,
		},
		{
			.Move = MOVE_FLING,
			.Level = 47,
		},
		{
			.Move = MOVE_PUNISHMENT,
			.Level = 53,
		},
		{
			.Move = MOVE_HAMMER_ARM,
			.Level = 61,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_NINCADA] = {
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 1,
		},
		{
			.Move = MOVE_LEECH_LIFE,
			.Level = 5,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 9,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 13,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 17,
		},
		{
			.Move = MOVE_METAL_CLAW,
			.Level = 21,
		},
		{
			.Move = MOVE_MIND_READER,
			.Level = 25,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_NINJASK] = {
		{
			.Move = MOVE_BUG_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 1,
		},
		{
			.Move = MOVE_LEECH_LIFE,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_LEECH_LIFE,
			.Level = 5,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 9,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 13,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 17,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 20,
		},
		{
			.Move = MOVE_FURY_CUTTER,
			.Level = 20,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 20,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 23,
		},
		{
			.Move = MOVE_MIND_READER,
			.Level = 29,
		},
		{
			.Move = MOVE_BATON_PASS,
			.Level = 35,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 41,
		},
		{
			.Move = MOVE_XSCISSOR,
			.Level = 47,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SHEDINJA] = {
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 1,
		},
		{
			.Move = MOVE_LEECH_LIFE,
			.Level = 5,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 9,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 13,
		},
		{
			.Move = MOVE_SPITE,
			.Level = 17,
		},
		{
			.Move = MOVE_SHADOW_SNEAK,
			.Level = 21,
		},
		{
			.Move = MOVE_MIND_READER,
			.Level = 25,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 29,
		},
		{
			.Move = MOVE_SHADOW_BALL,
			.Level = 33,
		},
		{
			.Move = MOVE_GRUDGE,
			.Level = 37,
		},
		{
			.Move = MOVE_HEAL_BLOCK,
			.Level = 41,
		},
		{
			.Move = MOVE_PHANTOM_FORCE,
			.Level = 45,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_WHISMUR] = {
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_ECHOED_VOICE,
			.Level = 4,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 8,
		},
		{
			.Move = MOVE_HOWL,
			.Level = 11,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 15,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 18,
		},
		{
			.Move = MOVE_STOMP,
			.Level = 22,
		},
		{
			.Move = MOVE_UPROAR,
			.Level = 25,
		},
		{
			.Move = MOVE_ROAR,
			.Level = 29,
		},
		{
			.Move = MOVE_REST,
			.Level = 32,
		},
		{
			.Move = MOVE_SLEEP_TALK,
			.Level = 36,
		},
		{
			.Move = MOVE_HYPER_VOICE,
			.Level = 39,
		},
		{
			.Move = MOVE_SYNCHRONOISE,
			.Level = 43,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_LOUDRED] = {
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_ECHOED_VOICE,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_HOWL,
			.Level = 1,
		},
		{
			.Move = MOVE_ECHOED_VOICE,
			.Level = 4,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 9,
		},
		{
			.Move = MOVE_HOWL,
			.Level = 11,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 15,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 18,
		},
		{
			.Move = MOVE_BITE,
			.Level = 20,
		},
		{
			.Move = MOVE_STOMP,
			.Level = 23,
		},
		{
			.Move = MOVE_UPROAR,
			.Level = 27,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_EXPLOUD] = {
		{
			.Move = MOVE_BOOMBURST,
			.Level = 1,
		},
		{
			.Move = MOVE_ICE_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_FIRE_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_ECHOED_VOICE,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_HOWL,
			.Level = 1,
		},
		{
			.Move = MOVE_ECHOED_VOICE,
			.Level = 4,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 9,
		},
		{
			.Move = MOVE_HOWL,
			.Level = 11,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 15,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 18,
		},
		{
			.Move = MOVE_BITE,
			.Level = 20,
		},
		{
			.Move = MOVE_STOMP,
			.Level = 23,
		},
		{
			.Move = MOVE_UPROAR,
			.Level = 27,
		},
		{
			.Move = MOVE_ROAR,
			.Level = 32,
		},
		{
			.Move = MOVE_REST,
			.Level = 36,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 40,
		},
		{
			.Move = MOVE_SLEEP_TALK,
			.Level = 42,
		},
		{
			.Move = MOVE_HYPER_VOICE,
			.Level = 47,
		},
		{
			.Move = MOVE_SYNCHRONOISE,
			.Level = 53,
		},
		{
			.Move = MOVE_BOOMBURST,
			.Level = 58,
		},
		{
			.Move = MOVE_HYPER_BEAM,
			.Level = 64,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MAKUHITA] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 4,
		},
		{
			.Move = MOVE_ARM_THRUST,
			.Level = 7,
		},
		{
			.Move = MOVE_FAKE_OUT,
			.Level = 10,
		},
		{
			.Move = MOVE_FORCE_PALM,
			.Level = 13,
		},
		{
			.Move = MOVE_WHIRLWIND,
			.Level = 16,
		},
		{
			.Move = MOVE_KNOCK_OFF,
			.Level = 19,
		},
		{
			.Move = MOVE_VITAL_THROW,
			.Level = 22,
		},
		{
			.Move = MOVE_BELLY_DRUM,
			.Level = 25,
		},
		{
			.Move = MOVE_SMELLINGSALT,
			.Level = 28,
		},
		{
			.Move = MOVE_SEISMIC_TOSS,
			.Level = 31,
		},
		{
			.Move = MOVE_WAKEUP_SLAP,
			.Level = 34,
		},
		{
			.Move = MOVE_ENDURE,
			.Level = 37,
		},
		{
			.Move = MOVE_CLOSE_COMBAT,
			.Level = 40,
		},
		{
			.Move = MOVE_REVERSAL,
			.Level = 43,
		},
		{
			.Move = MOVE_HEAVY_SLAM,
			.Level = 46,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_HARIYAMA] = {
		{
			.Move = MOVE_BRINE,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_ARM_THRUST,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 4,
		},
		{
			.Move = MOVE_ARM_THRUST,
			.Level = 7,
		},
		{
			.Move = MOVE_FAKE_OUT,
			.Level = 10,
		},
		{
			.Move = MOVE_FORCE_PALM,
			.Level = 13,
		},
		{
			.Move = MOVE_WHIRLWIND,
			.Level = 16,
		},
		{
			.Move = MOVE_KNOCK_OFF,
			.Level = 19,
		},
		{
			.Move = MOVE_VITAL_THROW,
			.Level = 22,
		},
		{
			.Move = MOVE_BELLY_DRUM,
			.Level = 26,
		},
		{
			.Move = MOVE_SMELLINGSALT,
			.Level = 30,
		},
		{
			.Move = MOVE_SEISMIC_TOSS,
			.Level = 34,
		},
		{
			.Move = MOVE_WAKEUP_SLAP,
			.Level = 38,
		},
		{
			.Move = MOVE_ENDURE,
			.Level = 42,
		},
		{
			.Move = MOVE_CLOSE_COMBAT,
			.Level = 46,
		},
		{
			.Move = MOVE_REVERSAL,
			.Level = 50,
		},
		{
			.Move = MOVE_HEAVY_SLAM,
			.Level = 54,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_AZURILL] = {
		{
			.Move = MOVE_SPLASH,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 2,
		},
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 5,
		},
		{
			.Move = MOVE_BUBBLE,
			.Level = 7,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 10,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 13,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 16,
		},
		{
			.Move = MOVE_SLAM,
			.Level = 20,
		},
		{
			.Move = MOVE_BOUNCE,
			.Level = 23,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_NOSEPASS] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 4,
		},
		{
			.Move = MOVE_BLOCK,
			.Level = 7,
		},
		{
			.Move = MOVE_ROCK_THROW,
			.Level = 10,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 13,
		},
		{
			.Move = MOVE_REST,
			.Level = 16,
		},
		{
			.Move = MOVE_ROCK_THROW,
			.Level = 19,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 22,
		},
		{
			.Move = MOVE_POWER_GEM,
			.Level = 25,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SKITTY] = {
		{
			.Move = MOVE_FAKE_OUT,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_FORESIGHT,
			.Level = 4,
		},
		{
			.Move = MOVE_SING,
			.Level = 7,
		},
		{
			.Move = MOVE_ATTRACT,
			.Level = 10,
		},
		{
			.Move = MOVE_DISARMING_VOICE,
			.Level = 13,
		},
		{
			.Move = MOVE_DOUBLESLAP,
			.Level = 16,
		},
		{
			.Move = MOVE_COPYCAT,
			.Level = 19,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 22,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 25,
		},
		{
			.Move = MOVE_WAKEUP_SLAP,
			.Level = 28,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_DELCATTY] = {
		{
			.Move = MOVE_FAKE_OUT,
			.Level = 1,
		},
		{
			.Move = MOVE_SING,
			.Level = 1,
		},
		{
			.Move = MOVE_ATTRACT,
			.Level = 1,
		},
		{
			.Move = MOVE_DOUBLESLAP,
			.Level = 1,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SABLEYE] = {
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_FORESIGHT,
			.Level = 4,
		},
		{
			.Move = MOVE_NIGHT_SHADE,
			.Level = 6,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 9,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 11,
		},
		{
			.Move = MOVE_DETECT,
			.Level = 14,
		},
		{
			.Move = MOVE_SHADOW_SNEAK,
			.Level = 16,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 19,
		},
		{
			.Move = MOVE_FAKE_OUT,
			.Level = 21,
		},
		{
			.Move = MOVE_PUNISHMENT,
			.Level = 24,
		},
		{
			.Move = MOVE_KNOCK_OFF,
			.Level = 26,
		},
		{
			.Move = MOVE_SHADOW_CLAW,
			.Level = 29,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 31,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 34,
		},
		{
			.Move = MOVE_POWER_GEM,
			.Level = 36,
		},
		{
			.Move = MOVE_SHADOW_BALL,
			.Level = 39,
		},
		{
			.Move = MOVE_FOUL_PLAY,
			.Level = 41,
		},
		{
			.Move = MOVE_QUASH,
			.Level = 44,
		},
		{
			.Move = MOVE_MEAN_LOOK,
			.Level = 46,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MAWILE] = {
		{
			.Move = MOVE_PLAY_ROUGH,
			.Level = 1,
		},
		{
			.Move = MOVE_IRON_HEAD,
			.Level = 1,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_FAIRY_WIND,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_FAKE_TEARS,
			.Level = 5,
		},
		{
			.Move = MOVE_BITE,
			.Level = 9,
		},
		{
			.Move = MOVE_SWEET_SCENT,
			.Level = 13,
		},
		{
			.Move = MOVE_VICEGRIP,
			.Level = 17,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 21,
		},
		{
			.Move = MOVE_BATON_PASS,
			.Level = 25,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 29,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 33,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 37,
		},
		{
			.Move = MOVE_STOCKPILE,
			.Level = 41,
		},
		{
			.Move = MOVE_SWALLOW,
			.Level = 41,
		},
		{
			.Move = MOVE_SPIT_UP,
			.Level = 41,
		},
		{
			.Move = MOVE_IRON_HEAD,
			.Level = 45,
		},
		{
			.Move = MOVE_PLAY_ROUGH,
			.Level = 49,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ARON] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 1,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 4,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 7,
		},
		{
			.Move = MOVE_METAL_CLAW,
			.Level = 10,
		},
		{
			.Move = MOVE_ROCK_TOMB,
			.Level = 13,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 16,
		},
		{
			.Move = MOVE_ROAR,
			.Level = 19,
		},
		{
			.Move = MOVE_IRON_HEAD,
			.Level = 22,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 25,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 28,
		},
		{
			.Move = MOVE_METAL_SOUND,
			.Level = 31,
		},
		{
			.Move = MOVE_IRON_TAIL,
			.Level = 34,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 37,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 40,
		},
		{
			.Move = MOVE_AUTOTOMIZE,
			.Level = 43,
		},
		{
			.Move = MOVE_HEAVY_SLAM,
			.Level = 46,
		},
		{
			.Move = MOVE_METAL_BURST,
			.Level = 49,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_LAIRON] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 1,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 1,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 1,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 4,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 7,
		},
		{
			.Move = MOVE_METAL_CLAW,
			.Level = 10,
		},
		{
			.Move = MOVE_ROCK_TOMB,
			.Level = 13,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 16,
		},
		{
			.Move = MOVE_ROAR,
			.Level = 19,
		},
		{
			.Move = MOVE_IRON_HEAD,
			.Level = 22,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 25,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 28,
		},
		{
			.Move = MOVE_METAL_SOUND,
			.Level = 31,
		},
		{
			.Move = MOVE_IRON_TAIL,
			.Level = 35,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 39,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 43,
		},
		{
			.Move = MOVE_AUTOTOMIZE,
			.Level = 47,
		},
		{
			.Move = MOVE_HEAVY_SLAM,
			.Level = 51,
		},
		{
			.Move = MOVE_METAL_BURST,
			.Level = 55,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_AGGRON] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 1,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 1,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 1,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 4,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 7,
		},
		{
			.Move = MOVE_METAL_CLAW,
			.Level = 10,
		},
		{
			.Move = MOVE_ROCK_TOMB,
			.Level = 13,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 16,
		},
		{
			.Move = MOVE_ROAR,
			.Level = 19,
		},
		{
			.Move = MOVE_IRON_HEAD,
			.Level = 22,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 25,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 28,
		},
		{
			.Move = MOVE_METAL_SOUND,
			.Level = 31,
		},
		{
			.Move = MOVE_IRON_TAIL,
			.Level = 35,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 39,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 45,
		},
		{
			.Move = MOVE_AUTOTOMIZE,
			.Level = 51,
		},
		{
			.Move = MOVE_HEAVY_SLAM,
			.Level = 57,
		},
		{
			.Move = MOVE_METAL_BURST,
			.Level = 63,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MEDITITE] = {
		{
			.Move = MOVE_BIDE,
			.Level = 1,
		},
		{
			.Move = MOVE_MEDITATE,
			.Level = 4,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 7,
		},
		{
			.Move = MOVE_DETECT,
			.Level = 9,
		},
		{
			.Move = MOVE_ENDURE,
			.Level = 12,
		},
		{
			.Move = MOVE_FEINT,
			.Level = 15,
		},
		{
			.Move = MOVE_FORCE_PALM,
			.Level = 17,
		},
		{
			.Move = MOVE_HIDDEN_POWER,
			.Level = 20,
		},
		{
			.Move = MOVE_CALM_MIND,
			.Level = 23,
		},
		{
			.Move = MOVE_MIND_READER,
			.Level = 25,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MEDICHAM] = {
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 1,
		},
		{
			.Move = MOVE_FIRE_PUNCH,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDERPUNCH,
			.Level = 1,
		},
		{
			.Move = MOVE_ICE_PUNCH,
			.Level = 1,
		},
		{
			.Move = MOVE_BIDE,
			.Level = 1,
		},
		{
			.Move = MOVE_MEDITATE,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_DETECT,
			.Level = 1,
		},
		{
			.Move = MOVE_MEDITATE,
			.Level = 4,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 7,
		},
		{
			.Move = MOVE_DETECT,
			.Level = 9,
		},
		{
			.Move = MOVE_ENDURE,
			.Level = 12,
		},
		{
			.Move = MOVE_FEINT,
			.Level = 15,
		},
		{
			.Move = MOVE_FORCE_PALM,
			.Level = 17,
		},
		{
			.Move = MOVE_HIDDEN_POWER,
			.Level = 20,
		},
		{
			.Move = MOVE_CALM_MIND,
			.Level = 23,
		},
		{
			.Move = MOVE_MIND_READER,
			.Level = 25,
		},
		{
			.Move = MOVE_HI_JUMP_KICK,
			.Level = 28,
		},
		{
			.Move = MOVE_PSYCH_UP,
			.Level = 31,
		},
		{
			.Move = MOVE_ACUPRESSURE,
			.Level = 33,
		},
		{
			.Move = MOVE_POWER_TRICK,
			.Level = 36,
		},
		{
			.Move = MOVE_REVERSAL,
			.Level = 42,
		},
		{
			.Move = MOVE_RECOVER,
			.Level = 47,
		},
		{
			.Move = MOVE_COUNTER,
			.Level = 53,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ELECTRIKE] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 4,
		},
		{
			.Move = MOVE_HOWL,
			.Level = 7,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 10,
		},
		{
			.Move = MOVE_SPARK,
			.Level = 13,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 16,
		},
		{
			.Move = MOVE_THUNDER_FANG,
			.Level = 19,
		},
		{
			.Move = MOVE_BITE,
			.Level = 24,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 29,
		},
		{
			.Move = MOVE_ROAR,
			.Level = 34,
		},
		{
			.Move = MOVE_WILD_CHARGE,
			.Level = 39,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 44,
		},
		{
			.Move = MOVE_THUNDER,
			.Level = 49,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MANECTRIC] = {
		{
			.Move = MOVE_ELECTRIC_TERRAIN,
			.Level = 1,
		},
		{
			.Move = MOVE_FIRE_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_HOWL,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 4,
		},
		{
			.Move = MOVE_HOWL,
			.Level = 7,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 10,
		},
		{
			.Move = MOVE_SPARK,
			.Level = 13,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 16,
		},
		{
			.Move = MOVE_THUNDER_FANG,
			.Level = 19,
		},
		{
			.Move = MOVE_BITE,
			.Level = 24,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 30,
		},
		{
			.Move = MOVE_ROAR,
			.Level = 36,
		},
		{
			.Move = MOVE_WILD_CHARGE,
			.Level = 42,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 48,
		},
		{
			.Move = MOVE_THUNDER,
			.Level = 54,
		},
		{
			.Move = MOVE_ELECTRIC_TERRAIN,
			.Level = 60,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PLUSLE] = {
		{
			.Move = MOVE_NUZZLE,
			.Level = 1,
		},
		{
			.Move = MOVE_PLAY_NICE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 4,
		},
		{
			.Move = MOVE_SPARK,
			.Level = 7,
		},
		{
			.Move = MOVE_ENCORE,
			.Level = 10,
		},
		{
			.Move = MOVE_BESTOW,
			.Level = 13,
		},
		{
			.Move = MOVE_SWIFT,
			.Level = 16,
		},
		{
			.Move = MOVE_ELECTRO_BALL,
			.Level = 19,
		},
		{
			.Move = MOVE_COPYCAT,
			.Level = 22,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 25,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 28,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 31,
		},
		{
			.Move = MOVE_BATON_PASS,
			.Level = 34,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 37,
		},
		{
			.Move = MOVE_LAST_RESORT,
			.Level = 40,
		},
		{
			.Move = MOVE_THUNDER,
			.Level = 43,
		},
		{
			.Move = MOVE_NASTY_PLOT,
			.Level = 46,
		},
		{
			.Move = MOVE_ENTRAINMENT,
			.Level = 49,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MINUN] = {
		{
			.Move = MOVE_NUZZLE,
			.Level = 1,
		},
		{
			.Move = MOVE_PLAY_NICE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 4,
		},
		{
			.Move = MOVE_SPARK,
			.Level = 7,
		},
		{
			.Move = MOVE_ENCORE,
			.Level = 10,
		},
		{
			.Move = MOVE_SWITCHEROO,
			.Level = 13,
		},
		{
			.Move = MOVE_SWIFT,
			.Level = 16,
		},
		{
			.Move = MOVE_ELECTRO_BALL,
			.Level = 19,
		},
		{
			.Move = MOVE_COPYCAT,
			.Level = 22,
		},
		{
			.Move = MOVE_FAKE_TEARS,
			.Level = 25,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 28,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 31,
		},
		{
			.Move = MOVE_BATON_PASS,
			.Level = 34,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 37,
		},
		{
			.Move = MOVE_TRUMP_CARD,
			.Level = 40,
		},
		{
			.Move = MOVE_THUNDER,
			.Level = 43,
		},
		{
			.Move = MOVE_NASTY_PLOT,
			.Level = 46,
		},
		{
			.Move = MOVE_ENTRAINMENT,
			.Level = 49,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_VOLBEAT] = {
		{
			.Move = MOVE_FLASH,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 5,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 8,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 12,
		},
		{
			.Move = MOVE_STRUGGLE_BUG,
			.Level = 15,
		},
		{
			.Move = MOVE_MOONLIGHT,
			.Level = 19,
		},
		{
			.Move = MOVE_TAIL_GLOW,
			.Level = 22,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 26,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ILLUMISE] = {
		{
			.Move = MOVE_PLAY_NICE,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_SWEET_SCENT,
			.Level = 5,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 9,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 12,
		},
		{
			.Move = MOVE_STRUGGLE_BUG,
			.Level = 15,
		},
		{
			.Move = MOVE_MOONLIGHT,
			.Level = 19,
		},
		{
			.Move = MOVE_WISH,
			.Level = 22,
		},
		{
			.Move = MOVE_ENCORE,
			.Level = 26,
		},
		{
			.Move = MOVE_FLATTER,
			.Level = 29,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 33,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 36,
		},
		{
			.Move = MOVE_BUG_BUZZ,
			.Level = 40,
		},
		{
			.Move = MOVE_PLAY_ROUGH,
			.Level = 43,
		},
		{
			.Move = MOVE_COVET,
			.Level = 47,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ROSELIA] = {
		{
			.Move = MOVE_ABSORB,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWTH,
			.Level = 4,
		},
		{
			.Move = MOVE_POISON_STING,
			.Level = 7,
		},
		{
			.Move = MOVE_STUN_SPORE,
			.Level = 10,
		},
		{
			.Move = MOVE_MEGA_DRAIN,
			.Level = 13,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 16,
		},
		{
			.Move = MOVE_MAGICAL_LEAF,
			.Level = 19,
		},
		{
			.Move = MOVE_GRASSWHISTLE,
			.Level = 22,
		},
		{
			.Move = MOVE_GIGA_DRAIN,
			.Level = 25,
		},
		{
			.Move = MOVE_TOXIC_SPIKES,
			.Level = 28,
		},
		{
			.Move = MOVE_SWEET_SCENT,
			.Level = 31,
		},
		{
			.Move = MOVE_INGRAIN,
			.Level = 34,
		},
		{
			.Move = MOVE_PETAL_BLIZZARD,
			.Level = 37,
		},
		{
			.Move = MOVE_TOXIC,
			.Level = 40,
		},
		{
			.Move = MOVE_AROMATHERAPY,
			.Level = 43,
		},
		{
			.Move = MOVE_SYNTHESIS,
			.Level = 46,
		},
		{
			.Move = MOVE_PETAL_DANCE,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GULPIN] = {
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_YAWN,
			.Level = 5,
		},
		{
			.Move = MOVE_POISON_GAS,
			.Level = 8,
		},
		{
			.Move = MOVE_SLUDGE,
			.Level = 10,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 12,
		},
		{
			.Move = MOVE_ACID_SPRAY,
			.Level = 17,
		},
		{
			.Move = MOVE_ENCORE,
			.Level = 20,
		},
		{
			.Move = MOVE_TOXIC,
			.Level = 25,
		},
		{
			.Move = MOVE_STOCKPILE,
			.Level = 28,
		},
		{
			.Move = MOVE_SPIT_UP,
			.Level = 28,
		},
		{
			.Move = MOVE_SWALLOW,
			.Level = 28,
		},
		{
			.Move = MOVE_SLUDGE_BOMB,
			.Level = 33,
		},
		{
			.Move = MOVE_GASTRO_ACID,
			.Level = 36,
		},
		{
			.Move = MOVE_BELCH,
			.Level = 41,
		},
		{
			.Move = MOVE_WRING_OUT,
			.Level = 44,
		},
		{
			.Move = MOVE_GUNK_SHOT,
			.Level = 49,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SWALOT] = {
		{
			.Move = MOVE_GUNK_SHOT,
			.Level = 1,
		},
		{
			.Move = MOVE_WRING_OUT,
			.Level = 1,
		},
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_YAWN,
			.Level = 1,
		},
		{
			.Move = MOVE_POISON_GAS,
			.Level = 1,
		},
		{
			.Move = MOVE_SLUDGE,
			.Level = 1,
		},
		{
			.Move = MOVE_YAWN,
			.Level = 5,
		},
		{
			.Move = MOVE_POISON_GAS,
			.Level = 8,
		},
		{
			.Move = MOVE_SLUDGE,
			.Level = 10,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 12,
		},
		{
			.Move = MOVE_ACID_SPRAY,
			.Level = 17,
		},
		{
			.Move = MOVE_ENCORE,
			.Level = 20,
		},
		{
			.Move = MOVE_TOXIC,
			.Level = 25,
		},
		{
			.Move = MOVE_BODY_SLAM,
			.Level = 26,
		},
		{
			.Move = MOVE_STOCKPILE,
			.Level = 30,
		},
		{
			.Move = MOVE_SPIT_UP,
			.Level = 30,
		},
		{
			.Move = MOVE_SWALLOW,
			.Level = 30,
		},
		{
			.Move = MOVE_SLUDGE_BOMB,
			.Level = 37,
		},
		{
			.Move = MOVE_GASTRO_ACID,
			.Level = 42,
		},
		{
			.Move = MOVE_BELCH,
			.Level = 49,
		},
		{
			.Move = MOVE_WRING_OUT,
			.Level = 54,
		},
		{
			.Move = MOVE_GUNK_SHOT,
			.Level = 61,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CARVANHA] = {
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_RAGE,
			.Level = 4,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 8,
		},
		{
			.Move = MOVE_AQUA_JET,
			.Level = 11,
		},
		{
			.Move = MOVE_ASSURANCE,
			.Level = 15,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 18,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 22,
		},
		{
			.Move = MOVE_ICE_FANG,
			.Level = 25,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 29,
		},
		{
			.Move = MOVE_POISON_FANG,
			.Level = 32,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 36,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 39,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 43,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SHARPEDO] = {
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 1,
		},
		{
			.Move = MOVE_FEINT,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_RAGE,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 1,
		},
		{
			.Move = MOVE_RAGE,
			.Level = 4,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 8,
		},
		{
			.Move = MOVE_AQUA_JET,
			.Level = 11,
		},
		{
			.Move = MOVE_ASSURANCE,
			.Level = 15,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 18,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 22,
		},
		{
			.Move = MOVE_ICE_FANG,
			.Level = 25,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 29,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 30,
		},
		{
			.Move = MOVE_POISON_FANG,
			.Level = 34,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 40,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 45,
		},
		{
			.Move = MOVE_SKULL_BASH,
			.Level = 51,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 56,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 62,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_WAILMER] = {
		{
			.Move = MOVE_SPLASH,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 4,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 7,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 10,
		},
		{
			.Move = MOVE_WHIRLPOOL,
			.Level = 13,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 16,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 19,
		},
		{
			.Move = MOVE_MIST,
			.Level = 22,
		},
		{
			.Move = MOVE_BRINE,
			.Level = 25,
		},
		{
			.Move = MOVE_REST,
			.Level = 29,
		},
		{
			.Move = MOVE_DIVE,
			.Level = 33,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 37,
		},
		{
			.Move = MOVE_WATER_SPOUT,
			.Level = 41,
		},
		{
			.Move = MOVE_BOUNCE,
			.Level = 45,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 49,
		},
		{
			.Move = MOVE_HEAVY_SLAM,
			.Level = 53,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_WAILORD] = {
		{
			.Move = MOVE_HEAVY_SLAM,
			.Level = 1,
		},
		{
			.Move = MOVE_SPLASH,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 4,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 7,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 10,
		},
		{
			.Move = MOVE_WHIRLPOOL,
			.Level = 13,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 16,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 19,
		},
		{
			.Move = MOVE_MIST,
			.Level = 22,
		},
		{
			.Move = MOVE_REST,
			.Level = 25,
		},
		{
			.Move = MOVE_BRINE,
			.Level = 29,
		},
		{
			.Move = MOVE_WATER_SPOUT,
			.Level = 33,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 37,
		},
		{
			.Move = MOVE_DIVE,
			.Level = 44,
		},
		{
			.Move = MOVE_BOUNCE,
			.Level = 51,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 58,
		},
		{
			.Move = MOVE_HEAVY_SLAM,
			.Level = 65,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_NUMEL] = {
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 5,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 8,
		},
		{
			.Move = MOVE_MAGNITUDE,
			.Level = 12,
		},
		{
			.Move = MOVE_FLAME_BURST,
			.Level = 15,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 19,
		},
		{
			.Move = MOVE_LAVA_PLUME,
			.Level = 22,
		},
		{
			.Move = MOVE_EARTH_POWER,
			.Level = 26,
		},
		{
			.Move = MOVE_CURSE,
			.Level = 29,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 31,
		},
		{
			.Move = MOVE_YAWN,
			.Level = 36,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 40,
		},
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 43,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 47,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CAMERUPT] = {
		{
			.Move = MOVE_FISSURE,
			.Level = 1,
		},
		{
			.Move = MOVE_ERUPTION,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 5,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 8,
		},
		{
			.Move = MOVE_MAGNITUDE,
			.Level = 12,
		},
		{
			.Move = MOVE_FLAME_BURST,
			.Level = 15,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 19,
		},
		{
			.Move = MOVE_LAVA_PLUME,
			.Level = 22,
		},
		{
			.Move = MOVE_EARTH_POWER,
			.Level = 26,
		},
		{
			.Move = MOVE_CURSE,
			.Level = 29,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 31,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 33,
		},
		{
			.Move = MOVE_YAWN,
			.Level = 39,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 46,
		},
		{
			.Move = MOVE_ERUPTION,
			.Level = 52,
		},
		{
			.Move = MOVE_FISSURE,
			.Level = 59,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_TORKOAL] = {
		{
			.Move = MOVE_EMBER,
			.Level = 1,
		},
		{
			.Move = MOVE_SMOG,
			.Level = 4,
		},
		{
			.Move = MOVE_WITHDRAW,
			.Level = 7,
		},
		{
			.Move = MOVE_RAPID_SPIN,
			.Level = 10,
		},
		{
			.Move = MOVE_FIRE_SPIN,
			.Level = 13,
		},
		{
			.Move = MOVE_SMOKESCREEN,
			.Level = 15,
		},
		{
			.Move = MOVE_FLAME_WHEEL,
			.Level = 18,
		},
		{
			.Move = MOVE_CURSE,
			.Level = 22,
		},
		{
			.Move = MOVE_LAVA_PLUME,
			.Level = 25,
		},
		{
			.Move = MOVE_BODY_SLAM,
			.Level = 27,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 30,
		},
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 34,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 38,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 40,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 42,
		},
		{
			.Move = MOVE_HEAT_WAVE,
			.Level = 45,
		},
		{
			.Move = MOVE_SHELL_SMASH,
			.Level = 47,
		},
		{
			.Move = MOVE_INFERNO,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SPOINK] = {
		{
			.Move = MOVE_SPLASH,
			.Level = 1,
		},
		{
			.Move = MOVE_PSYWAVE,
			.Level = 7,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 10,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 14,
		},
		{
			.Move = MOVE_PSYCH_UP,
			.Level = 15,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 18,
		},
		{
			.Move = MOVE_MAGIC_COAT,
			.Level = 21,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 26,
		},
		{
			.Move = MOVE_POWER_GEM,
			.Level = 29,
		},
		{
			.Move = MOVE_REST,
			.Level = 29,
		},
		{
			.Move = MOVE_SNORE,
			.Level = 33,
		},
		{
			.Move = MOVE_PSYSHOCK,
			.Level = 38,
		},
		{
			.Move = MOVE_PAYBACK,
			.Level = 40,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 44,
		},
		{
			.Move = MOVE_BOUNCE,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GRUMPIG] = {
		{
			.Move = MOVE_SPLASH,
			.Level = 1,
		},
		{
			.Move = MOVE_PSYWAVE,
			.Level = 1,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 1,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 1,
		},
		{
			.Move = MOVE_PSYWAVE,
			.Level = 7,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 10,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 14,
		},
		{
			.Move = MOVE_PSYCH_UP,
			.Level = 15,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 18,
		},
		{
			.Move = MOVE_MAGIC_COAT,
			.Level = 21,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 26,
		},
		{
			.Move = MOVE_POWER_GEM,
			.Level = 29,
		},
		{
			.Move = MOVE_TEETER_DANCE,
			.Level = 32,
		},
		{
			.Move = MOVE_REST,
			.Level = 35,
		},
		{
			.Move = MOVE_SNORE,
			.Level = 35,
		},
		{
			.Move = MOVE_PSYSHOCK,
			.Level = 42,
		},
		{
			.Move = MOVE_PAYBACK,
			.Level = 46,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 52,
		},
		{
			.Move = MOVE_BOUNCE,
			.Level = 60,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SPINDA] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_COPYCAT,
			.Level = 5,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 10,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 14,
		},
		{
			.Move = MOVE_HYPNOSIS,
			.Level = 19,
		},
		{
			.Move = MOVE_DIZZY_PUNCH,
			.Level = 23,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 28,
		},
		{
			.Move = MOVE_TEETER_DANCE,
			.Level = 32,
		},
		{
			.Move = MOVE_UPROAR,
			.Level = 37,
		},
		{
			.Move = MOVE_PSYCH_UP,
			.Level = 41,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 46,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 50,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 55,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_TRAPINCH] = {
		{
			.Move = MOVE_SANDATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_BIDE,
			.Level = 1,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 5,
		},
		{
			.Move = MOVE_BULLDOZE,
			.Level = 8,
		},
		{
			.Move = MOVE_SAND_TOMB,
			.Level = 12,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 15,
		},
		{
			.Move = MOVE_DIG,
			.Level = 19,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 22,
		},
		{
			.Move = MOVE_EARTH_POWER,
			.Level = 26,
		},
		{
			.Move = MOVE_FEINT,
			.Level = 29,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 33,
		},
		{
			.Move = MOVE_SANDSTORM,
			.Level = 36,
		},
		{
			.Move = MOVE_SUPERPOWER,
			.Level = 40,
		},
		{
			.Move = MOVE_HYPER_BEAM,
			.Level = 43,
		},
		{
			.Move = MOVE_FISSURE,
			.Level = 47,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_VIBRAVA] = {
		{
			.Move = MOVE_SANDATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_SONICBOOM,
			.Level = 1,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_BIDE,
			.Level = 1,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 5,
		},
		{
			.Move = MOVE_BULLDOZE,
			.Level = 8,
		},
		{
			.Move = MOVE_SAND_TOMB,
			.Level = 12,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 15,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 19,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 22,
		},
		{
			.Move = MOVE_EARTH_POWER,
			.Level = 26,
		},
		{
			.Move = MOVE_BUG_BUZZ,
			.Level = 29,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 33,
		},
		{
			.Move = MOVE_DRAGONBREATH,
			.Level = 35,
		},
		{
			.Move = MOVE_SANDSTORM,
			.Level = 36,
		},
		{
			.Move = MOVE_UPROAR,
			.Level = 40,
		},
		{
			.Move = MOVE_HYPER_BEAM,
			.Level = 43,
		},
		{
			.Move = MOVE_BOOMBURST,
			.Level = 47,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_FLYGON] = {
		{
			.Move = MOVE_SANDATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_SONICBOOM,
			.Level = 1,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_BIDE,
			.Level = 1,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 5,
		},
		{
			.Move = MOVE_BULLDOZE,
			.Level = 8,
		},
		{
			.Move = MOVE_SAND_TOMB,
			.Level = 12,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 15,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 19,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 22,
		},
		{
			.Move = MOVE_EARTH_POWER,
			.Level = 26,
		},
		{
			.Move = MOVE_DRAGON_TAIL,
			.Level = 29,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 33,
		},
		{
			.Move = MOVE_DRAGONBREATH,
			.Level = 35,
		},
		{
			.Move = MOVE_SANDSTORM,
			.Level = 36,
		},
		{
			.Move = MOVE_UPROAR,
			.Level = 40,
		},
		{
			.Move = MOVE_HYPER_BEAM,
			.Level = 43,
		},
		{
			.Move = MOVE_DRAGON_CLAW,
			.Level = 45,
		},
		{
			.Move = MOVE_DRAGON_RUSH,
			.Level = 47,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CACNEA] = {
		{
			.Move = MOVE_POISON_STING,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_ABSORB,
			.Level = 4,
		},
		{
			.Move = MOVE_GROWTH,
			.Level = 7,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 10,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 13,
		},
		{
			.Move = MOVE_NEEDLE_ARM,
			.Level = 16,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 19,
		},
		{
			.Move = MOVE_INGRAIN,
			.Level = 22,
		},
		{
			.Move = MOVE_PAYBACK,
			.Level = 26,
		},
		{
			.Move = MOVE_SPIKES,
			.Level = 30,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 34,
		},
		{
			.Move = MOVE_PIN_MISSILE,
			.Level = 38,
		},
		{
			.Move = MOVE_ENERGY_BALL,
			.Level = 42,
		},
		{
			.Move = MOVE_COTTON_SPORE,
			.Level = 46,
		},
		{
			.Move = MOVE_SANDSTORM,
			.Level = 50,
		},
		{
			.Move = MOVE_DESTINY_BOND,
			.Level = 54,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CACTURNE] = {
		{
			.Move = MOVE_DESTINY_BOND,
			.Level = 1,
		},
		{
			.Move = MOVE_REVENGE,
			.Level = 1,
		},
		{
			.Move = MOVE_POISON_STING,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_ABSORB,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWTH,
			.Level = 1,
		},
		{
			.Move = MOVE_ABSORB,
			.Level = 4,
		},
		{
			.Move = MOVE_GROWTH,
			.Level = 7,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 10,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 13,
		},
		{
			.Move = MOVE_NEEDLE_ARM,
			.Level = 16,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 19,
		},
		{
			.Move = MOVE_INGRAIN,
			.Level = 22,
		},
		{
			.Move = MOVE_PAYBACK,
			.Level = 26,
		},
		{
			.Move = MOVE_SPIKES,
			.Level = 30,
		},
		{
			.Move = MOVE_SPIKY_SHIELD,
			.Level = 32,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 35,
		},
		{
			.Move = MOVE_PIN_MISSILE,
			.Level = 38,
		},
		{
			.Move = MOVE_ENERGY_BALL,
			.Level = 44,
		},
		{
			.Move = MOVE_COTTON_SPORE,
			.Level = 49,
		},
		{
			.Move = MOVE_SANDSTORM,
			.Level = 54,
		},
		{
			.Move = MOVE_DESTINY_BOND,
			.Level = 59,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SWABLU] = {
		{
			.Move = MOVE_PECK,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 3,
		},
		{
			.Move = MOVE_SING,
			.Level = 5,
		},
		{
			.Move = MOVE_FURY_ATTACK,
			.Level = 7,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 9,
		},
		{
			.Move = MOVE_DISARMING_VOICE,
			.Level = 11,
		},
		{
			.Move = MOVE_MIST,
			.Level = 14,
		},
		{
			.Move = MOVE_ROUND,
			.Level = 17,
		},
		{
			.Move = MOVE_NATURAL_GIFT,
			.Level = 20,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 23,
		},
		{
			.Move = MOVE_REFRESH,
			.Level = 26,
		},
		{
			.Move = MOVE_MIRROR_MOVE,
			.Level = 30,
		},
		{
			.Move = MOVE_COTTON_GUARD,
			.Level = 34,
		},
		{
			.Move = MOVE_DRAGON_PULSE,
			.Level = 38,
		},
		{
			.Move = MOVE_PERISH_SONG,
			.Level = 42,
		},
		{
			.Move = MOVE_MOONBLAST,
			.Level = 46,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ALTARIA] = {
		{
			.Move = MOVE_SKY_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_PLUCK,
			.Level = 1,
		},
		{
			.Move = MOVE_PECK,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_SING,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 3,
		},
		{
			.Move = MOVE_SING,
			.Level = 5,
		},
		{
			.Move = MOVE_FURY_ATTACK,
			.Level = 7,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 9,
		},
		{
			.Move = MOVE_DISARMING_VOICE,
			.Level = 11,
		},
		{
			.Move = MOVE_MIST,
			.Level = 14,
		},
		{
			.Move = MOVE_ROUND,
			.Level = 17,
		},
		{
			.Move = MOVE_NATURAL_GIFT,
			.Level = 20,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 23,
		},
		{
			.Move = MOVE_REFRESH,
			.Level = 26,
		},
		{
			.Move = MOVE_DRAGON_DANCE,
			.Level = 30,
		},
		{
			.Move = MOVE_COTTON_GUARD,
			.Level = 34,
		},
		{
			.Move = MOVE_DRAGONBREATH,
			.Level = 35,
		},
		{
			.Move = MOVE_DRAGON_PULSE,
			.Level = 40,
		},
		{
			.Move = MOVE_PERISH_SONG,
			.Level = 46,
		},
		{
			.Move = MOVE_MOONBLAST,
			.Level = 52,
		},
		{
			.Move = MOVE_SKY_ATTACK,
			.Level = 59,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ZANGOOSE] = {
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 5,
		},
		{
			.Move = MOVE_FURY_CUTTER,
			.Level = 8,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 12,
		},
		{
			.Move = MOVE_HONE_CLAWS,
			.Level = 15,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 19,
		},
		{
			.Move = MOVE_REVENGE,
			.Level = 22,
		},
		{
			.Move = MOVE_CRUSH_CLAW,
			.Level = 26,
		},
		{
			.Move = MOVE_FALSE_SWIPE,
			.Level = 29,
		},
		{
			.Move = MOVE_EMBARGO,
			.Level = 33,
		},
		{
			.Move = MOVE_DETECT,
			.Level = 36,
		},
		{
			.Move = MOVE_XSCISSOR,
			.Level = 40,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 43,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 47,
		},
		{
			.Move = MOVE_CLOSE_COMBAT,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SEVIPER] = {
		{
			.Move = MOVE_WRAP,
			.Level = 1,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 4,
		},
		{
			.Move = MOVE_LICK,
			.Level = 7,
		},
		{
			.Move = MOVE_POISON_TAIL,
			.Level = 10,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 13,
		},
		{
			.Move = MOVE_BITE,
			.Level = 16,
		},
		{
			.Move = MOVE_WRAP,
			.Level = 19,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 22,
		},
		{
			.Move = MOVE_VENOM_DRENCH,
			.Level = 25,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 28,
		},
		{
			.Move = MOVE_GASTRO_ACID,
			.Level = 31,
		},
		{
			.Move = MOVE_POISON_JAB,
			.Level = 34,
		},
		{
			.Move = MOVE_HAZE,
			.Level = 37,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 40,
		},
		{
			.Move = MOVE_BELCH,
			.Level = 43,
		},
		{
			.Move = MOVE_COIL,
			.Level = 46,
		},
		{
			.Move = MOVE_WRING_OUT,
			.Level = 49,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_LUNATONE] = {
		{
			.Move = MOVE_MOONBLAST,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_ROCK_THROW,
			.Level = 1,
		},
		{
			.Move = MOVE_HYPNOSIS,
			.Level = 5,
		},
		{
			.Move = MOVE_ROCK_POLISH,
			.Level = 9,
		},
		{
			.Move = MOVE_PSYWAVE,
			.Level = 13,
		},
		{
			.Move = MOVE_EMBARGO,
			.Level = 17,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 21,
		},
		{
			.Move = MOVE_COSMIC_POWER,
			.Level = 25,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 29,
		},
		{
			.Move = MOVE_HEAL_BLOCK,
			.Level = 33,
		},
		{
			.Move = MOVE_STONE_EDGE,
			.Level = 37,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 41,
		},
		{
			.Move = MOVE_EXPLOSION,
			.Level = 45,
		},
		{
			.Move = MOVE_MAGIC_ROOM,
			.Level = 49,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SOLROCK] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_ROCK_THROW,
			.Level = 1,
		},
		{
			.Move = MOVE_FIRE_SPIN,
			.Level = 5,
		},
		{
			.Move = MOVE_ROCK_POLISH,
			.Level = 9,
		},
		{
			.Move = MOVE_PSYWAVE,
			.Level = 13,
		},
		{
			.Move = MOVE_EMBARGO,
			.Level = 17,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 21,
		},
		{
			.Move = MOVE_COSMIC_POWER,
			.Level = 25,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 29,
		},
		{
			.Move = MOVE_HEAL_BLOCK,
			.Level = 33,
		},
		{
			.Move = MOVE_STONE_EDGE,
			.Level = 37,
		},
		{
			.Move = MOVE_SOLARBEAM,
			.Level = 41,
		},
		{
			.Move = MOVE_EXPLOSION,
			.Level = 45,
		},
		{
			.Move = MOVE_WONDER_ROOM,
			.Level = 49,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BARBOACH] = {
		{
			.Move = MOVE_MUDSLAP,
			.Level = 1,
		},
		{
			.Move = MOVE_MUD_SPORT,
			.Level = 6,
		},
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 6,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 9,
		},
		{
			.Move = MOVE_MUD_BOMB,
			.Level = 13,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 15,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 17,
		},
		{
			.Move = MOVE_MAGNITUDE,
			.Level = 20,
		},
		{
			.Move = MOVE_REST,
			.Level = 25,
		},
		{
			.Move = MOVE_SNORE,
			.Level = 25,
		},
		{
			.Move = MOVE_AQUA_TAIL,
			.Level = 28,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 32,
		},
		{
			.Move = MOVE_MUDDY_WATER,
			.Level = 35,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 39,
		},
		{
			.Move = MOVE_FISSURE,
			.Level = 44,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_WHISCASH] = {
		{
			.Move = MOVE_TICKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 1,
		},
		{
			.Move = MOVE_MUD_SPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_MUD_SPORT,
			.Level = 6,
		},
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 6,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 9,
		},
		{
			.Move = MOVE_MUD_BOMB,
			.Level = 13,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 15,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 17,
		},
		{
			.Move = MOVE_MAGNITUDE,
			.Level = 20,
		},
		{
			.Move = MOVE_REST,
			.Level = 25,
		},
		{
			.Move = MOVE_SNORE,
			.Level = 25,
		},
		{
			.Move = MOVE_AQUA_TAIL,
			.Level = 28,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 30,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 34,
		},
		{
			.Move = MOVE_MUDDY_WATER,
			.Level = 39,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 45,
		},
		{
			.Move = MOVE_FISSURE,
			.Level = 52,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CORPHISH] = {
		{
			.Move = MOVE_BUBBLE,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 5,
		},
		{
			.Move = MOVE_VICEGRIP,
			.Level = 7,
		},
		{
			.Move = MOVE_LEER,
			.Level = 10,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 14,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 17,
		},
		{
			.Move = MOVE_DOUBLE_HIT,
			.Level = 20,
		},
		{
			.Move = MOVE_KNOCK_OFF,
			.Level = 23,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 26,
		},
		{
			.Move = MOVE_RAZOR_SHELL,
			.Level = 31,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 34,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 37,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 39,
		},
		{
			.Move = MOVE_CRABHAMMER,
			.Level = 43,
		},
		{
			.Move = MOVE_GUILLOTINE,
			.Level = 48,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CRAWDAUNT] = {
		{
			.Move = MOVE_BUBBLE,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 1,
		},
		{
			.Move = MOVE_VICEGRIP,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 5,
		},
		{
			.Move = MOVE_VICEGRIP,
			.Level = 7,
		},
		{
			.Move = MOVE_LEER,
			.Level = 10,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 14,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 17,
		},
		{
			.Move = MOVE_DOUBLE_HIT,
			.Level = 20,
		},
		{
			.Move = MOVE_KNOCK_OFF,
			.Level = 23,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 26,
		},
		{
			.Move = MOVE_SWIFT,
			.Level = 30,
		},
		{
			.Move = MOVE_RAZOR_SHELL,
			.Level = 32,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 36,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 40,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 43,
		},
		{
			.Move = MOVE_CRABHAMMER,
			.Level = 48,
		},
		{
			.Move = MOVE_GUILLOTINE,
			.Level = 54,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BALTOY] = {
		{
			.Move = MOVE_HARDEN,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_RAPID_SPIN,
			.Level = 4,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 7,
		},
		{
			.Move = MOVE_HEAL_BLOCK,
			.Level = 10,
		},
		{
			.Move = MOVE_ROCK_TOMB,
			.Level = 13,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 16,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 19,
		},
		{
			.Move = MOVE_COSMIC_POWER,
			.Level = 22,
		},
		{
			.Move = MOVE_POWER_TRICK,
			.Level = 25,
		},
		{
			.Move = MOVE_SELFDESTRUCT,
			.Level = 28,
		},
		{
			.Move = MOVE_EXTRASENSORY,
			.Level = 31,
		},
		{
			.Move = MOVE_GUARD_SPLIT,
			.Level = 34,
		},
		{
			.Move = MOVE_POWER_SPLIT,
			.Level = 34,
		},
		{
			.Move = MOVE_EARTH_POWER,
			.Level = 37,
		},
		{
			.Move = MOVE_SANDSTORM,
			.Level = 40,
		},
		{
			.Move = MOVE_IMPRISON,
			.Level = 43,
		},
		{
			.Move = MOVE_EXPLOSION,
			.Level = 46,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CLAYDOL] = {
		{
			.Move = MOVE_TELEPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_RAPID_SPIN,
			.Level = 1,
		},
		{
			.Move = MOVE_RAPID_SPIN,
			.Level = 4,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 7,
		},
		{
			.Move = MOVE_HEAL_BLOCK,
			.Level = 10,
		},
		{
			.Move = MOVE_ROCK_TOMB,
			.Level = 13,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 16,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 19,
		},
		{
			.Move = MOVE_COSMIC_POWER,
			.Level = 22,
		},
		{
			.Move = MOVE_POWER_TRICK,
			.Level = 25,
		},
		{
			.Move = MOVE_SELFDESTRUCT,
			.Level = 28,
		},
		{
			.Move = MOVE_EXTRASENSORY,
			.Level = 31,
		},
		{
			.Move = MOVE_GUARD_SPLIT,
			.Level = 34,
		},
		{
			.Move = MOVE_POWER_SPLIT,
			.Level = 34,
		},
		{
			.Move = MOVE_HYPER_BEAM,
			.Level = 36,
		},
		{
			.Move = MOVE_EARTH_POWER,
			.Level = 40,
		},
		{
			.Move = MOVE_SANDSTORM,
			.Level = 46,
		},
		{
			.Move = MOVE_IMPRISON,
			.Level = 52,
		},
		{
			.Move = MOVE_EXPLOSION,
			.Level = 58,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_LILEEP] = {
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_CONSTRICT,
			.Level = 1,
		},
		{
			.Move = MOVE_ACID,
			.Level = 5,
		},
		{
			.Move = MOVE_INGRAIN,
			.Level = 9,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 13,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 17,
		},
		{
			.Move = MOVE_BRINE,
			.Level = 21,
		},
		{
			.Move = MOVE_GIGA_DRAIN,
			.Level = 26,
		},
		{
			.Move = MOVE_GASTRO_ACID,
			.Level = 31,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 36,
		},
		{
			.Move = MOVE_ENERGY_BALL,
			.Level = 41,
		},
		{
			.Move = MOVE_STOCKPILE,
			.Level = 46,
		},
		{
			.Move = MOVE_SPIT_UP,
			.Level = 46,
		},
		{
			.Move = MOVE_SWALLOW,
			.Level = 46,
		},
		{
			.Move = MOVE_WRING_OUT,
			.Level = 52,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CRADILY] = {
		{
			.Move = MOVE_WRING_OUT,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_CONSTRICT,
			.Level = 1,
		},
		{
			.Move = MOVE_ACID,
			.Level = 1,
		},
		{
			.Move = MOVE_INGRAIN,
			.Level = 1,
		},
		{
			.Move = MOVE_ACID,
			.Level = 5,
		},
		{
			.Move = MOVE_INGRAIN,
			.Level = 9,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 13,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 17,
		},
		{
			.Move = MOVE_BRINE,
			.Level = 21,
		},
		{
			.Move = MOVE_GIGA_DRAIN,
			.Level = 26,
		},
		{
			.Move = MOVE_GASTRO_ACID,
			.Level = 31,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 36,
		},
		{
			.Move = MOVE_ENERGY_BALL,
			.Level = 44,
		},
		{
			.Move = MOVE_STOCKPILE,
			.Level = 52,
		},
		{
			.Move = MOVE_SPIT_UP,
			.Level = 52,
		},
		{
			.Move = MOVE_SWALLOW,
			.Level = 52,
		},
		{
			.Move = MOVE_WRING_OUT,
			.Level = 61,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ANORITH] = {
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 1,
		},
		{
			.Move = MOVE_MUD_SPORT,
			.Level = 4,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 7,
		},
		{
			.Move = MOVE_FURY_CUTTER,
			.Level = 10,
		},
		{
			.Move = MOVE_SMACK_DOWN,
			.Level = 13,
		},
		{
			.Move = MOVE_METAL_CLAW,
			.Level = 17,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 21,
		},
		{
			.Move = MOVE_BUG_BITE,
			.Level = 25,
		},
		{
			.Move = MOVE_BRINE,
			.Level = 29,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 34,
		},
		{
			.Move = MOVE_CRUSH_CLAW,
			.Level = 39,
		},
		{
			.Move = MOVE_XSCISSOR,
			.Level = 44,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 49,
		},
		{
			.Move = MOVE_ROCK_BLAST,
			.Level = 55,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ARMALDO] = {
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 1,
		},
		{
			.Move = MOVE_MUD_SPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_MUD_SPORT,
			.Level = 4,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 7,
		},
		{
			.Move = MOVE_FURY_CUTTER,
			.Level = 10,
		},
		{
			.Move = MOVE_SMACK_DOWN,
			.Level = 13,
		},
		{
			.Move = MOVE_METAL_CLAW,
			.Level = 17,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 21,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 25,
		},
		{
			.Move = MOVE_BRINE,
			.Level = 29,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 34,
		},
		{
			.Move = MOVE_CRUSH_CLAW,
			.Level = 39,
		},
		{
			.Move = MOVE_XSCISSOR,
			.Level = 46,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 53,
		},
		{
			.Move = MOVE_ROCK_BLAST,
			.Level = 61,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_FEEBAS] = {
		{
			.Move = MOVE_SPLASH,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 15,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 30,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MILOTIC] = {
		{
			.Move = MOVE_WRAP,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 4,
		},
		{
			.Move = MOVE_REFRESH,
			.Level = 7,
		},
		{
			.Move = MOVE_DISARMING_VOICE,
			.Level = 11,
		},
		{
			.Move = MOVE_TWISTER,
			.Level = 14,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 17,
		},
		{
			.Move = MOVE_AQUA_RING,
			.Level = 21,
		},
		{
			.Move = MOVE_CAPTIVATE,
			.Level = 24,
		},
		{
			.Move = MOVE_DRAGON_TAIL,
			.Level = 27,
		},
		{
			.Move = MOVE_RECOVER,
			.Level = 31,
		},
		{
			.Move = MOVE_AQUA_TAIL,
			.Level = 34,
		},
		{
			.Move = MOVE_ATTRACT,
			.Level = 37,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 41,
		},
		{
			.Move = MOVE_COIL,
			.Level = 44,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 47,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 51,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CASTFORM] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 10,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 10,
		},
		{
			.Move = MOVE_POWDER_SNOW,
			.Level = 10,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 15,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 20,
		},
		{
			.Move = MOVE_SUNNY_DAY,
			.Level = 20,
		},
		{
			.Move = MOVE_HAIL,
			.Level = 20,
		},
		{
			.Move = MOVE_WEATHER_BALL,
			.Level = 25,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 35,
		},
		{
			.Move = MOVE_FIRE_BLAST,
			.Level = 35,
		},
		{
			.Move = MOVE_BLIZZARD,
			.Level = 35,
		},
		{
			.Move = MOVE_HURRICANE,
			.Level = 45,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_KECLEON] = {
		{
			.Move = MOVE_THIEF,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_LICK,
			.Level = 1,
		},
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_BIND,
			.Level = 4,
		},
		{
			.Move = MOVE_SHADOW_SNEAK,
			.Level = 7,
		},
		{
			.Move = MOVE_FEINT,
			.Level = 10,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 13,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 16,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 18,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 21,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 25,
		},
		{
			.Move = MOVE_CAMOUFLAGE,
			.Level = 30,
		},
		{
			.Move = MOVE_SHADOW_CLAW,
			.Level = 33,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 38,
		},
		{
			.Move = MOVE_SUBSTITUTE,
			.Level = 42,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 46,
		},
		{
			.Move = MOVE_SYNCHRONOISE,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SHUPPET] = {
		{
			.Move = MOVE_KNOCK_OFF,
			.Level = 1,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 4,
		},
		{
			.Move = MOVE_NIGHT_SHADE,
			.Level = 7,
		},
		{
			.Move = MOVE_SPITE,
			.Level = 10,
		},
		{
			.Move = MOVE_SHADOW_SNEAK,
			.Level = 13,
		},
		{
			.Move = MOVE_WILLOWISP,
			.Level = 16,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 19,
		},
		{
			.Move = MOVE_HEX,
			.Level = 22,
		},
		{
			.Move = MOVE_CURSE,
			.Level = 26,
		},
		{
			.Move = MOVE_SHADOW_BALL,
			.Level = 30,
		},
		{
			.Move = MOVE_EMBARGO,
			.Level = 34,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 38,
		},
		{
			.Move = MOVE_SNATCH,
			.Level = 42,
		},
		{
			.Move = MOVE_GRUDGE,
			.Level = 46,
		},
		{
			.Move = MOVE_TRICK,
			.Level = 50,
		},
		{
			.Move = MOVE_PHANTOM_FORCE,
			.Level = 54,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BANETTE] = {
		{
			.Move = MOVE_PHANTOM_FORCE,
			.Level = 1,
		},
		{
			.Move = MOVE_KNOCK_OFF,
			.Level = 1,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 1,
		},
		{
			.Move = MOVE_NIGHT_SHADE,
			.Level = 1,
		},
		{
			.Move = MOVE_SPITE,
			.Level = 1,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 4,
		},
		{
			.Move = MOVE_NIGHT_SHADE,
			.Level = 7,
		},
		{
			.Move = MOVE_SPITE,
			.Level = 10,
		},
		{
			.Move = MOVE_SHADOW_SNEAK,
			.Level = 13,
		},
		{
			.Move = MOVE_WILLOWISP,
			.Level = 16,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 19,
		},
		{
			.Move = MOVE_HEX,
			.Level = 22,
		},
		{
			.Move = MOVE_CURSE,
			.Level = 26,
		},
		{
			.Move = MOVE_SHADOW_BALL,
			.Level = 30,
		},
		{
			.Move = MOVE_EMBARGO,
			.Level = 34,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 40,
		},
		{
			.Move = MOVE_SNATCH,
			.Level = 46,
		},
		{
			.Move = MOVE_GRUDGE,
			.Level = 52,
		},
		{
			.Move = MOVE_TRICK,
			.Level = 58,
		},
		{
			.Move = MOVE_PHANTOM_FORCE,
			.Level = 64,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_DUSKULL] = {
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_NIGHT_SHADE,
			.Level = 1,
		},
		{
			.Move = MOVE_DISABLE,
			.Level = 6,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 9,
		},
		{
			.Move = MOVE_FORESIGHT,
			.Level = 14,
		},
		{
			.Move = MOVE_SHADOW_SNEAK,
			.Level = 17,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 22,
		},
		{
			.Move = MOVE_WILLOWISP,
			.Level = 25,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 30,
		},
		{
			.Move = MOVE_CURSE,
			.Level = 33,
		},
		{
			.Move = MOVE_HEX,
			.Level = 38,
		},
		{
			.Move = MOVE_SHADOW_BALL,
			.Level = 41,
		},
		{
			.Move = MOVE_MEAN_LOOK,
			.Level = 46,
		},
		{
			.Move = MOVE_PAYBACK,
			.Level = 49,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 54,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_DUSCLOPS] = {
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 1,
		},
		{
			.Move = MOVE_FIRE_PUNCH,
			.Level = 1,
		},
		{
			.Move = MOVE_ICE_PUNCH,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDERPUNCH,
			.Level = 1,
		},
		{
			.Move = MOVE_GRAVITY,
			.Level = 1,
		},
		{
			.Move = MOVE_BIND,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_NIGHT_SHADE,
			.Level = 1,
		},
		{
			.Move = MOVE_DISABLE,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_DISABLE,
			.Level = 6,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 9,
		},
		{
			.Move = MOVE_FORESIGHT,
			.Level = 14,
		},
		{
			.Move = MOVE_SHADOW_SNEAK,
			.Level = 17,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 22,
		},
		{
			.Move = MOVE_WILLOWISP,
			.Level = 25,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 30,
		},
		{
			.Move = MOVE_CURSE,
			.Level = 33,
		},
		{
			.Move = MOVE_SHADOW_PUNCH,
			.Level = 37,
		},
		{
			.Move = MOVE_HEX,
			.Level = 40,
		},
		{
			.Move = MOVE_SHADOW_BALL,
			.Level = 45,
		},
		{
			.Move = MOVE_MEAN_LOOK,
			.Level = 52,
		},
		{
			.Move = MOVE_PAYBACK,
			.Level = 57,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 64,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_TROPIUS] = {
		{
			.Move = MOVE_LEAF_STORM,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_GUST,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWTH,
			.Level = 1,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 1,
		},
		{
			.Move = MOVE_SWEET_SCENT,
			.Level = 6,
		},
		{
			.Move = MOVE_STOMP,
			.Level = 10,
		},
		{
			.Move = MOVE_MAGICAL_LEAF,
			.Level = 16,
		},
		{
			.Move = MOVE_SWEET_SCENT,
			.Level = 21,
		},
		{
			.Move = MOVE_GUST,
			.Level = 26,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CHIMECHO] = {
		{
			.Move = MOVE_HEALING_WISH,
			.Level = 1,
		},
		{
			.Move = MOVE_SYNCHRONOISE,
			.Level = 1,
		},
		{
			.Move = MOVE_WRAP,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 4,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 7,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 10,
		},
		{
			.Move = MOVE_YAWN,
			.Level = 13,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 16,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 19,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 22,
		},
		{
			.Move = MOVE_HEAL_BELL,
			.Level = 27,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ABSOL] = {
		{
			.Move = MOVE_PERISH_SONG,
			.Level = 1,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 1,
		},
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_FEINT,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 4,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 7,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 10,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 13,
		},
		{
			.Move = MOVE_BITE,
			.Level = 16,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 19,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 22,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_WYNAUT] = {
		{
			.Move = MOVE_SPLASH,
			.Level = 1,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 1,
		},
		{
			.Move = MOVE_ENCORE,
			.Level = 1,
		},
		{
			.Move = MOVE_COUNTER,
			.Level = 15,
		},
		{
			.Move = MOVE_MIRROR_COAT,
			.Level = 15,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 15,
		},
		{
			.Move = MOVE_DESTINY_BOND,
			.Level = 15,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SNORUNT] = {
		{
			.Move = MOVE_POWDER_SNOW,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 5,
		},
		{
			.Move = MOVE_ICE_SHARD,
			.Level = 10,
		},
		{
			.Move = MOVE_ICY_WIND,
			.Level = 14,
		},
		{
			.Move = MOVE_BITE,
			.Level = 19,
		},
		{
			.Move = MOVE_ICE_FANG,
			.Level = 23,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 28,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 32,
		},
		{
			.Move = MOVE_FROST_BREATH,
			.Level = 37,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 41,
		},
		{
			.Move = MOVE_BLIZZARD,
			.Level = 46,
		},
		{
			.Move = MOVE_HAIL,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GLALIE] = {
		{
			.Move = MOVE_ICE_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 1,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 1,
		},
		{
			.Move = MOVE_FROST_BREATH,
			.Level = 1,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SPHEAL] = {
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 1,
		},
		{
			.Move = MOVE_POWDER_SNOW,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 5,
		},
		{
			.Move = MOVE_ENCORE,
			.Level = 9,
		},
		{
			.Move = MOVE_ICE_BALL,
			.Level = 13,
		},
		{
			.Move = MOVE_BRINE,
			.Level = 17,
		},
		{
			.Move = MOVE_AURORA_BEAM,
			.Level = 21,
		},
		{
			.Move = MOVE_BODY_SLAM,
			.Level = 26,
		},
		{
			.Move = MOVE_REST,
			.Level = 31,
		},
		{
			.Move = MOVE_SNORE,
			.Level = 31,
		},
		{
			.Move = MOVE_HAIL,
			.Level = 36,
		},
		{
			.Move = MOVE_BLIZZARD,
			.Level = 41,
		},
		{
			.Move = MOVE_SHEER_COLD,
			.Level = 46,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SEALEO] = {
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 1,
		},
		{
			.Move = MOVE_POWDER_SNOW,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 5,
		},
		{
			.Move = MOVE_ENCORE,
			.Level = 9,
		},
		{
			.Move = MOVE_ICE_BALL,
			.Level = 13,
		},
		{
			.Move = MOVE_BRINE,
			.Level = 17,
		},
		{
			.Move = MOVE_AURORA_BEAM,
			.Level = 21,
		},
		{
			.Move = MOVE_BODY_SLAM,
			.Level = 26,
		},
		{
			.Move = MOVE_REST,
			.Level = 31,
		},
		{
			.Move = MOVE_SNORE,
			.Level = 31,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 32,
		},
		{
			.Move = MOVE_HAIL,
			.Level = 38,
		},
		{
			.Move = MOVE_BLIZZARD,
			.Level = 45,
		},
		{
			.Move = MOVE_SHEER_COLD,
			.Level = 52,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_WALREIN] = {
		{
			.Move = MOVE_CRUNCH,
			.Level = 1,
		},
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 1,
		},
		{
			.Move = MOVE_POWDER_SNOW,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 7,
		},
		{
			.Move = MOVE_ENCORE,
			.Level = 7,
		},
		{
			.Move = MOVE_ICE_BALL,
			.Level = 13,
		},
		{
			.Move = MOVE_BRINE,
			.Level = 19,
		},
		{
			.Move = MOVE_AURORA_BEAM,
			.Level = 19,
		},
		{
			.Move = MOVE_BODY_SLAM,
			.Level = 25,
		},
		{
			.Move = MOVE_REST,
			.Level = 31,
		},
		{
			.Move = MOVE_SNORE,
			.Level = 31,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 32,
		},
		{
			.Move = MOVE_HAIL,
			.Level = 38,
		},
		{
			.Move = MOVE_ICE_FANG,
			.Level = 44,
		},
		{
			.Move = MOVE_BLIZZARD,
			.Level = 49,
		},
		{
			.Move = MOVE_SHEER_COLD,
			.Level = 60,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CLAMPERL] = {
		{
			.Move = MOVE_CLAMP,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_WHIRLPOOL,
			.Level = 1,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 1,
		},
		{
			.Move = MOVE_SHELL_SMASH,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_HUNTAIL] = {
		{
			.Move = MOVE_WHIRLPOOL,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 5,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 9,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 11,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 14,
		},
		{
			.Move = MOVE_ICE_FANG,
			.Level = 16,
		},
		{
			.Move = MOVE_BRINE,
			.Level = 19,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 23,
		},
		{
			.Move = MOVE_DIVE,
			.Level = 26,
		},
		{
			.Move = MOVE_BATON_PASS,
			.Level = 29,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 34,
		},
		{
			.Move = MOVE_AQUA_TAIL,
			.Level = 39,
		},
		{
			.Move = MOVE_COIL,
			.Level = 45,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GOREBYSS] = {
		{
			.Move = MOVE_WHIRLPOOL,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 5,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 9,
		},
		{
			.Move = MOVE_DRAINING_KISS,
			.Level = 11,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 14,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 16,
		},
		{
			.Move = MOVE_AQUA_RING,
			.Level = 19,
		},
		{
			.Move = MOVE_CAPTIVATE,
			.Level = 23,
		},
		{
			.Move = MOVE_DIVE,
			.Level = 26,
		},
		{
			.Move = MOVE_BATON_PASS,
			.Level = 29,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 34,
		},
		{
			.Move = MOVE_AQUA_TAIL,
			.Level = 39,
		},
		{
			.Move = MOVE_COIL,
			.Level = 45,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_RELICANTH] = {
		{
			.Move = MOVE_HEAD_SMASH,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 1,
		},
		{
			.Move = MOVE_MUD_SPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_MUD_SPORT,
			.Level = 6,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 10,
		},
		{
			.Move = MOVE_ROCK_TOMB,
			.Level = 15,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 21,
		},
		{
			.Move = MOVE_DIVE,
			.Level = 26,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 31,
		},
		{
			.Move = MOVE_YAWN,
			.Level = 35,
		},
		{
			.Move = MOVE_REST,
			.Level = 41,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 46,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 50,
		},
		{
			.Move = MOVE_HEAD_SMASH,
			.Level = 56,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_LUVDISC] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 4,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 7,
		},
		{
			.Move = MOVE_DRAINING_KISS,
			.Level = 9,
		},
		{
			.Move = MOVE_LUCKY_CHANT,
			.Level = 14,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 17,
		},
		{
			.Move = MOVE_ATTRACT,
			.Level = 22,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 27,
		},
		{
			.Move = MOVE_SWEET_KISS,
			.Level = 31,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 37,
		},
		{
			.Move = MOVE_AQUA_RING,
			.Level = 40,
		},
		{
			.Move = MOVE_CAPTIVATE,
			.Level = 46,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 50,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 55,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BAGON] = {
		{
			.Move = MOVE_RAGE,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 4,
		},
		{
			.Move = MOVE_LEER,
			.Level = 7,
		},
		{
			.Move = MOVE_BITE,
			.Level = 10,
		},
		{
			.Move = MOVE_DRAGONBREATH,
			.Level = 13,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 17,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 21,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 25,
		},
		{
			.Move = MOVE_DRAGON_CLAW,
			.Level = 29,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 34,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 39,
		},
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 44,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 49,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SHELGON] = {
		{
			.Move = MOVE_RAGE,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 4,
		},
		{
			.Move = MOVE_LEER,
			.Level = 7,
		},
		{
			.Move = MOVE_BITE,
			.Level = 10,
		},
		{
			.Move = MOVE_DRAGONBREATH,
			.Level = 13,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 17,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 21,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 25,
		},
		{
			.Move = MOVE_DRAGON_CLAW,
			.Level = 29,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 30,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 35,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 42,
		},
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 49,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 56,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SALAMENCE] = {
		{
			.Move = MOVE_DRAGON_TAIL,
			.Level = 1,
		},
		{
			.Move = MOVE_FIRE_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_RAGE,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 4,
		},
		{
			.Move = MOVE_LEER,
			.Level = 7,
		},
		{
			.Move = MOVE_BITE,
			.Level = 10,
		},
		{
			.Move = MOVE_DRAGONBREATH,
			.Level = 13,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 17,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 21,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 25,
		},
		{
			.Move = MOVE_DRAGON_CLAW,
			.Level = 29,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 30,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 35,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 42,
		},
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 49,
		},
		{
			.Move = MOVE_FLY,
			.Level = 50,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 63,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BELDUM] = {
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 1,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_METANG] = {
		{
			.Move = MOVE_MAGNET_RISE,
			.Level = 1,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_METAL_CLAW,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 20,
		},
		{
			.Move = MOVE_METAL_CLAW,
			.Level = 20,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 23,
		},
		{
			.Move = MOVE_BULLET_PUNCH,
			.Level = 26,
		},
		{
			.Move = MOVE_MIRACLE_EYE,
			.Level = 29,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 32,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 35,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 38,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 41,
		},
		{
			.Move = MOVE_METEOR_MASH,
			.Level = 44,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 47,
		},
		{
			.Move = MOVE_HYPER_BEAM,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_METAGROSS] = {
		{
			.Move = MOVE_MAGNET_RISE,
			.Level = 1,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_METAL_CLAW,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 20,
		},
		{
			.Move = MOVE_METAL_CLAW,
			.Level = 20,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 23,
		},
		{
			.Move = MOVE_BULLET_PUNCH,
			.Level = 26,
		},
		{
			.Move = MOVE_MIRACLE_EYE,
			.Level = 29,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 32,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 35,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 38,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 41,
		},
		{
			.Move = MOVE_METEOR_MASH,
			.Level = 44,
		},
		{
			.Move = MOVE_HAMMER_ARM,
			.Level = 45,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 52,
		},
		{
			.Move = MOVE_HYPER_BEAM,
			.Level = 60,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_REGIROCK] = {
		{
			.Move = MOVE_EXPLOSION,
			.Level = 1,
		},
		{
			.Move = MOVE_STOMP,
			.Level = 1,
		},
		{
			.Move = MOVE_ROCK_THROW,
			.Level = 1,
		},
		{
			.Move = MOVE_CHARGE_BEAM,
			.Level = 1,
		},
		{
			.Move = MOVE_BULLDOZE,
			.Level = 1,
		},
		{
			.Move = MOVE_ROCK_THROW,
			.Level = 7,
		},
		{
			.Move = MOVE_CHARGE_BEAM,
			.Level = 13,
		},
		{
			.Move = MOVE_BULLDOZE,
			.Level = 19,
		},
		{
			.Move = MOVE_CURSE,
			.Level = 25,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 31,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 37,
		},
		{
			.Move = MOVE_STONE_EDGE,
			.Level = 43,
		},
		{
			.Move = MOVE_HAMMER_ARM,
			.Level = 49,
		},
		{
			.Move = MOVE_LOCKON,
			.Level = 55,
		},
		{
			.Move = MOVE_ZAP_CANNON,
			.Level = 55,
		},
		{
			.Move = MOVE_SUPERPOWER,
			.Level = 61,
		},
		{
			.Move = MOVE_HYPER_BEAM,
			.Level = 67,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_REGICE] = {
		{
			.Move = MOVE_EXPLOSION,
			.Level = 1,
		},
		{
			.Move = MOVE_STOMP,
			.Level = 1,
		},
		{
			.Move = MOVE_ICY_WIND,
			.Level = 1,
		},
		{
			.Move = MOVE_CHARGE_BEAM,
			.Level = 1,
		},
		{
			.Move = MOVE_BULLDOZE,
			.Level = 1,
		},
		{
			.Move = MOVE_ICY_WIND,
			.Level = 7,
		},
		{
			.Move = MOVE_CHARGE_BEAM,
			.Level = 13,
		},
		{
			.Move = MOVE_BULLDOZE,
			.Level = 19,
		},
		{
			.Move = MOVE_CURSE,
			.Level = 25,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 31,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 37,
		},
		{
			.Move = MOVE_ICE_BEAM,
			.Level = 43,
		},
		{
			.Move = MOVE_HAMMER_ARM,
			.Level = 49,
		},
		{
			.Move = MOVE_LOCKON,
			.Level = 55,
		},
		{
			.Move = MOVE_ZAP_CANNON,
			.Level = 55,
		},
		{
			.Move = MOVE_SUPERPOWER,
			.Level = 61,
		},
		{
			.Move = MOVE_HYPER_BEAM,
			.Level = 67,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_REGISTEEL] = {
		{
			.Move = MOVE_EXPLOSION,
			.Level = 1,
		},
		{
			.Move = MOVE_STOMP,
			.Level = 1,
		},
		{
			.Move = MOVE_METAL_CLAW,
			.Level = 1,
		},
		{
			.Move = MOVE_CHARGE_BEAM,
			.Level = 1,
		},
		{
			.Move = MOVE_BULLDOZE,
			.Level = 1,
		},
		{
			.Move = MOVE_METAL_CLAW,
			.Level = 7,
		},
		{
			.Move = MOVE_CHARGE_BEAM,
			.Level = 13,
		},
		{
			.Move = MOVE_BULLDOZE,
			.Level = 19,
		},
		{
			.Move = MOVE_CURSE,
			.Level = 25,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 31,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 37,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 37,
		},
		{
			.Move = MOVE_IRON_HEAD,
			.Level = 43,
		},
		{
			.Move = MOVE_FLASH_CANNON,
			.Level = 43,
		},
		{
			.Move = MOVE_HAMMER_ARM,
			.Level = 49,
		},
		{
			.Move = MOVE_LOCKON,
			.Level = 55,
		},
		{
			.Move = MOVE_ZAP_CANNON,
			.Level = 55,
		},
		{
			.Move = MOVE_SUPERPOWER,
			.Level = 61,
		},
		{
			.Move = MOVE_HYPER_BEAM,
			.Level = 67,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_LATIAS] = {
		{
			.Move = MOVE_HEALING_WISH,
			.Level = 1,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 1,
		},
		{
			.Move = MOVE_WISH,
			.Level = 1,
		},
		{
			.Move = MOVE_PSYWAVE,
			.Level = 1,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 4,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 7,
		},
		{
			.Move = MOVE_STORED_POWER,
			.Level = 10,
		},
		{
			.Move = MOVE_REFRESH,
			.Level = 13,
		},
		{
			.Move = MOVE_HEAL_PULSE,
			.Level = 16,
		},
		{
			.Move = MOVE_DRAGONBREATH,
			.Level = 20,
		},
		{
			.Move = MOVE_MIST_BALL,
			.Level = 24,
		},
		{
			.Move = MOVE_PSYCHO_SHIFT,
			.Level = 28,
		},
		{
			.Move = MOVE_RECOVER,
			.Level = 32,
		},
		{
			.Move = MOVE_REFLECT_TYPE,
			.Level = 36,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 41,
		},
		{
			.Move = MOVE_GUARD_SPLIT,
			.Level = 46,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 51,
		},
		{
			.Move = MOVE_DRAGON_PULSE,
			.Level = 56,
		},
		{
			.Move = MOVE_HEALING_WISH,
			.Level = 61,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_LATIOS] = {
		{
			.Move = MOVE_MEMENTO,
			.Level = 1,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 1,
		},
		{
			.Move = MOVE_HEAL_BLOCK,
			.Level = 1,
		},
		{
			.Move = MOVE_PSYWAVE,
			.Level = 1,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 1,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 4,
		},
		{
			.Move = MOVE_DRAGON_DANCE,
			.Level = 7,
		},
		{
			.Move = MOVE_STORED_POWER,
			.Level = 10,
		},
		{
			.Move = MOVE_REFRESH,
			.Level = 13,
		},
		{
			.Move = MOVE_HEAL_PULSE,
			.Level = 16,
		},
		{
			.Move = MOVE_DRAGONBREATH,
			.Level = 20,
		},
		{
			.Move = MOVE_LUSTER_PURGE,
			.Level = 24,
		},
		{
			.Move = MOVE_PSYCHO_SHIFT,
			.Level = 28,
		},
		{
			.Move = MOVE_RECOVER,
			.Level = 32,
		},
		{
			.Move = MOVE_TELEKINESIS,
			.Level = 36,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 41,
		},
		{
			.Move = MOVE_POWER_SPLIT,
			.Level = 46,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 51,
		},
		{
			.Move = MOVE_DRAGON_PULSE,
			.Level = 56,
		},
		{
			.Move = MOVE_MEMENTO,
			.Level = 61,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_KYOGRE] = {
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 1,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 5,
		},
		{
			.Move = MOVE_AQUA_TAIL,
			.Level = 15,
		},
		{
			.Move = MOVE_BODY_SLAM,
			.Level = 20,
		},
		{
			.Move = MOVE_AQUA_RING,
			.Level = 30,
		},
		{
			.Move = MOVE_ICE_BEAM,
			.Level = 35,
		},
		{
			.Move = MOVE_ORIGIN_PULSE,
			.Level = 45,
		},
		{
			.Move = MOVE_CALM_MIND,
			.Level = 50,
		},
		{
			.Move = MOVE_MUDDY_WATER,
			.Level = 60,
		},
		{
			.Move = MOVE_SHEER_COLD,
			.Level = 65,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 75,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 80,
		},
		{
			.Move = MOVE_WATER_SPOUT,
			.Level = 90,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GROUDON] = {
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 1,
		},
		{
			.Move = MOVE_MUD_SHOT,
			.Level = 1,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 5,
		},
		{
			.Move = MOVE_EARTH_POWER,
			.Level = 15,
		},
		{
			.Move = MOVE_LAVA_PLUME,
			.Level = 20,
		},
		{
			.Move = MOVE_REST,
			.Level = 30,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 35,
		},
		{
			.Move = MOVE_PRECIPICE_BLADES,
			.Level = 45,
		},
		{
			.Move = MOVE_BULK_UP,
			.Level = 50,
		},
		{
			.Move = MOVE_SOLARBEAM,
			.Level = 60,
		},
		{
			.Move = MOVE_FISSURE,
			.Level = 65,
		},
		{
			.Move = MOVE_FIRE_BLAST,
			.Level = 75,
		},
		{
			.Move = MOVE_HAMMER_ARM,
			.Level = 80,
		},
		{
			.Move = MOVE_ERUPTION,
			.Level = 90,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_RAYQUAZA] = {
		{
			.Move = MOVE_TWISTER,
			.Level = 1,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 5,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 15,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 20,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 30,
		},
		{
			.Move = MOVE_REST,
			.Level = 35,
		},
		{
			.Move = MOVE_EXTREMESPEED,
			.Level = 45,
		},
		{
			.Move = MOVE_DRAGON_PULSE,
			.Level = 50,
		},
		{
			.Move = MOVE_DRAGON_DANCE,
			.Level = 60,
		},
		{
			.Move = MOVE_FLY,
			.Level = 65,
		},
		{
			.Move = MOVE_HYPER_VOICE,
			.Level = 75,
		},
		{
			.Move = MOVE_OUTRAGE,
			.Level = 80,
		},
		{
			.Move = MOVE_HYPER_BEAM,
			.Level = 90,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_JIRACHI] = {
		{
			.Move = MOVE_WISH,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_REST,
			.Level = 5,
		},
		{
			.Move = MOVE_SWIFT,
			.Level = 10,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 15,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 20,
		},
		{
			.Move = MOVE_REFRESH,
			.Level = 25,
		},
		{
			.Move = MOVE_REST,
			.Level = 30,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 35,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 40,
		},
		{
			.Move = MOVE_GRAVITY,
			.Level = 45,
		},
		{
			.Move = MOVE_HEALING_WISH,
			.Level = 50,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 55,
		},
		{
			.Move = MOVE_COSMIC_POWER,
			.Level = 60,
		},
		{
			.Move = MOVE_LAST_RESORT,
			.Level = 65,
		},
		{
			.Move = MOVE_DOOM_DESIRE,
			.Level = 70,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_DEOXYS] = {
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_WRAP,
			.Level = 1,
		},
		{
			.Move = MOVE_NIGHT_SHADE,
			.Level = 7,
		},
		{
			.Move = MOVE_TELEPORT,
			.Level = 13,
		},
		{
			.Move = MOVE_KNOCK_OFF,
			.Level = 19,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 25,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 31,
		},
		{
			.Move = MOVE_SNATCH,
			.Level = 37,
		},
		{
			.Move = MOVE_PSYCHO_SHIFT,
			.Level = 43,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 49,
		},
		{
			.Move = MOVE_COSMIC_POWER,
			.Level = 55,
		},
		{
			.Move = MOVE_RECOVER,
			.Level = 61,
		},
		{
			.Move = MOVE_PSYCHO_BOOST,
			.Level = 67,
		},
		{
			.Move = MOVE_HYPER_BEAM,
			.Level = 73,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_TURTWIG] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_WITHDRAW,
			.Level = 5,
		},
		{
			.Move = MOVE_ABSORB,
			.Level = 9,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 13,
		},
		{
			.Move = MOVE_CURSE,
			.Level = 17,
		},
		{
			.Move = MOVE_BITE,
			.Level = 21,
		},
		{
			.Move = MOVE_MEGA_DRAIN,
			.Level = 25,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 29,
		},
		{
			.Move = MOVE_SYNTHESIS,
			.Level = 33,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 37,
		},
		{
			.Move = MOVE_GIGA_DRAIN,
			.Level = 41,
		},
		{
			.Move = MOVE_LEAF_STORM,
			.Level = 45,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GROTLE] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_WITHDRAW,
			.Level = 1,
		},
		{
			.Move = MOVE_WITHDRAW,
			.Level = 5,
		},
		{
			.Move = MOVE_ABSORB,
			.Level = 9,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 13,
		},
		{
			.Move = MOVE_CURSE,
			.Level = 17,
		},
		{
			.Move = MOVE_BITE,
			.Level = 22,
		},
		{
			.Move = MOVE_MEGA_DRAIN,
			.Level = 27,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 32,
		},
		{
			.Move = MOVE_SYNTHESIS,
			.Level = 37,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 42,
		},
		{
			.Move = MOVE_GIGA_DRAIN,
			.Level = 47,
		},
		{
			.Move = MOVE_LEAF_STORM,
			.Level = 52,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_TORTERRA] = {
		{
			.Move = MOVE_WOOD_HAMMER,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_WITHDRAW,
			.Level = 1,
		},
		{
			.Move = MOVE_ABSORB,
			.Level = 1,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 1,
		},
		{
			.Move = MOVE_WITHDRAW,
			.Level = 5,
		},
		{
			.Move = MOVE_ABSORB,
			.Level = 9,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 13,
		},
		{
			.Move = MOVE_CURSE,
			.Level = 17,
		},
		{
			.Move = MOVE_BITE,
			.Level = 22,
		},
		{
			.Move = MOVE_MEGA_DRAIN,
			.Level = 27,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 32,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 33,
		},
		{
			.Move = MOVE_SYNTHESIS,
			.Level = 39,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 45,
		},
		{
			.Move = MOVE_GIGA_DRAIN,
			.Level = 51,
		},
		{
			.Move = MOVE_LEAF_STORM,
			.Level = 57,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CHIMCHAR] = {
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 7,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 9,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 15,
		},
		{
			.Move = MOVE_FLAME_WHEEL,
			.Level = 17,
		},
		{
			.Move = MOVE_NASTY_PLOT,
			.Level = 23,
		},
		{
			.Move = MOVE_TORMENT,
			.Level = 25,
		},
		{
			.Move = MOVE_FACADE,
			.Level = 31,
		},
		{
			.Move = MOVE_FIRE_SPIN,
			.Level = 33,
		},
		{
			.Move = MOVE_ACROBATICS,
			.Level = 39,
		},
		{
			.Move = MOVE_SLACK_OFF,
			.Level = 41,
		},
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 47,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MONFERNO] = {
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 7,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 9,
		},
		{
			.Move = MOVE_MACH_PUNCH,
			.Level = 14,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 16,
		},
		{
			.Move = MOVE_FLAME_WHEEL,
			.Level = 19,
		},
		{
			.Move = MOVE_FEINT,
			.Level = 26,
		},
		{
			.Move = MOVE_TORMENT,
			.Level = 29,
		},
		{
			.Move = MOVE_CLOSE_COMBAT,
			.Level = 36,
		},
		{
			.Move = MOVE_FIRE_SPIN,
			.Level = 39,
		},
		{
			.Move = MOVE_ACROBATICS,
			.Level = 46,
		},
		{
			.Move = MOVE_SLACK_OFF,
			.Level = 49,
		},
		{
			.Move = MOVE_FLARE_BLITZ,
			.Level = 56,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_INFERNAPE] = {
		{
			.Move = MOVE_FLARE_BLITZ,
			.Level = 1,
		},
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 1,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 7,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 9,
		},
		{
			.Move = MOVE_MACH_PUNCH,
			.Level = 14,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 16,
		},
		{
			.Move = MOVE_FLAME_WHEEL,
			.Level = 19,
		},
		{
			.Move = MOVE_FEINT,
			.Level = 26,
		},
		{
			.Move = MOVE_PUNISHMENT,
			.Level = 29,
		},
		{
			.Move = MOVE_CLOSE_COMBAT,
			.Level = 36,
		},
		{
			.Move = MOVE_FIRE_SPIN,
			.Level = 42,
		},
		{
			.Move = MOVE_ACROBATICS,
			.Level = 52,
		},
		{
			.Move = MOVE_CALM_MIND,
			.Level = 58,
		},
		{
			.Move = MOVE_FLARE_BLITZ,
			.Level = 68,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PIPLUP] = {
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 4,
		},
		{
			.Move = MOVE_BUBBLE,
			.Level = 8,
		},
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 11,
		},
		{
			.Move = MOVE_PECK,
			.Level = 15,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 18,
		},
		{
			.Move = MOVE_BIDE,
			.Level = 22,
		},
		{
			.Move = MOVE_FURY_ATTACK,
			.Level = 25,
		},
		{
			.Move = MOVE_BRINE,
			.Level = 29,
		},
		{
			.Move = MOVE_WHIRLPOOL,
			.Level = 32,
		},
		{
			.Move = MOVE_MIST,
			.Level = 36,
		},
		{
			.Move = MOVE_DRILL_PECK,
			.Level = 39,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 43,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PRINPLUP] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 4,
		},
		{
			.Move = MOVE_BUBBLE,
			.Level = 8,
		},
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 11,
		},
		{
			.Move = MOVE_PECK,
			.Level = 15,
		},
		{
			.Move = MOVE_METAL_CLAW,
			.Level = 16,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 19,
		},
		{
			.Move = MOVE_BIDE,
			.Level = 24,
		},
		{
			.Move = MOVE_FURY_ATTACK,
			.Level = 28,
		},
		{
			.Move = MOVE_BRINE,
			.Level = 33,
		},
		{
			.Move = MOVE_WHIRLPOOL,
			.Level = 37,
		},
		{
			.Move = MOVE_MIST,
			.Level = 42,
		},
		{
			.Move = MOVE_DRILL_PECK,
			.Level = 46,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_EMPOLEON] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_BUBBLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 4,
		},
		{
			.Move = MOVE_BUBBLE,
			.Level = 8,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 11,
		},
		{
			.Move = MOVE_PECK,
			.Level = 15,
		},
		{
			.Move = MOVE_METAL_CLAW,
			.Level = 16,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 19,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 24,
		},
		{
			.Move = MOVE_FURY_ATTACK,
			.Level = 28,
		},
		{
			.Move = MOVE_BRINE,
			.Level = 33,
		},
		{
			.Move = MOVE_AQUA_JET,
			.Level = 36,
		},
		{
			.Move = MOVE_WHIRLPOOL,
			.Level = 39,
		},
		{
			.Move = MOVE_MIST,
			.Level = 46,
		},
		{
			.Move = MOVE_DRILL_PECK,
			.Level = 52,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 59,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_STARLY] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 5,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 9,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 13,
		},
		{
			.Move = MOVE_ENDEAVOR,
			.Level = 17,
		},
		{
			.Move = MOVE_WHIRLWIND,
			.Level = 21,
		},
		{
			.Move = MOVE_AERIAL_ACE,
			.Level = 25,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 29,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 33,
		},
		{
			.Move = MOVE_BRAVE_BIRD,
			.Level = 37,
		},
		{
			.Move = MOVE_FINAL_GAMBIT,
			.Level = 41,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_STARAVIA] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 5,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 9,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 13,
		},
		{
			.Move = MOVE_ENDEAVOR,
			.Level = 18,
		},
		{
			.Move = MOVE_WHIRLWIND,
			.Level = 23,
		},
		{
			.Move = MOVE_AERIAL_ACE,
			.Level = 28,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 33,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 38,
		},
		{
			.Move = MOVE_BRAVE_BIRD,
			.Level = 43,
		},
		{
			.Move = MOVE_FINAL_GAMBIT,
			.Level = 48,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_STARAPTOR] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 5,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 9,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 13,
		},
		{
			.Move = MOVE_ENDEAVOR,
			.Level = 18,
		},
		{
			.Move = MOVE_WHIRLWIND,
			.Level = 23,
		},
		{
			.Move = MOVE_AERIAL_ACE,
			.Level = 28,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 33,
		},
		{
			.Move = MOVE_CLOSE_COMBAT,
			.Level = 34,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 41,
		},
		{
			.Move = MOVE_BRAVE_BIRD,
			.Level = 49,
		},
		{
			.Move = MOVE_FINAL_GAMBIT,
			.Level = 57,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BIDOOF] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 5,
		},
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 9,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 13,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 17,
		},
		{
			.Move = MOVE_HYPER_FANG,
			.Level = 21,
		},
		{
			.Move = MOVE_YAWN,
			.Level = 25,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 29,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 33,
		},
		{
			.Move = MOVE_SUPER_FANG,
			.Level = 37,
		},
		{
			.Move = MOVE_SUPERPOWER,
			.Level = 41,
		},
		{
			.Move = MOVE_CURSE,
			.Level = 45,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BIBAREL] = {
		{
			.Move = MOVE_ROTOTILLER,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 5,
		},
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 9,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 13,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 15,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 18,
		},
		{
			.Move = MOVE_HYPER_FANG,
			.Level = 23,
		},
		{
			.Move = MOVE_YAWN,
			.Level = 28,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 33,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 38,
		},
		{
			.Move = MOVE_SUPER_FANG,
			.Level = 43,
		},
		{
			.Move = MOVE_SUPERPOWER,
			.Level = 48,
		},
		{
			.Move = MOVE_CURSE,
			.Level = 53,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_KRICKETOT] = {
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_BIDE,
			.Level = 1,
		},
		{
			.Move = MOVE_STRUGGLE_BUG,
			.Level = 6,
		},
		{
			.Move = MOVE_BUG_BITE,
			.Level = 16,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_KRICKETUNE] = {
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_BIDE,
			.Level = 1,
		},
		{
			.Move = MOVE_FURY_CUTTER,
			.Level = 10,
		},
		{
			.Move = MOVE_LEECH_LIFE,
			.Level = 14,
		},
		{
			.Move = MOVE_SING,
			.Level = 18,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 22,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 26,
		},
		{
			.Move = MOVE_XSCISSOR,
			.Level = 30,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 34,
		},
		{
			.Move = MOVE_FELL_STINGER,
			.Level = 36,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 38,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 42,
		},
		{
			.Move = MOVE_STICKY_WEB,
			.Level = 44,
		},
		{
			.Move = MOVE_BUG_BUZZ,
			.Level = 46,
		},
		{
			.Move = MOVE_PERISH_SONG,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SHINX] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 5,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 9,
		},
		{
			.Move = MOVE_BABYDOLL_EYES,
			.Level = 11,
		},
		{
			.Move = MOVE_SPARK,
			.Level = 13,
		},
		{
			.Move = MOVE_BITE,
			.Level = 17,
		},
		{
			.Move = MOVE_ROAR,
			.Level = 21,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 25,
		},
		{
			.Move = MOVE_THUNDER_FANG,
			.Level = 29,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 33,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 37,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 41,
		},
		{
			.Move = MOVE_WILD_CHARGE,
			.Level = 45,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_LUXIO] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 5,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 9,
		},
		{
			.Move = MOVE_SPARK,
			.Level = 13,
		},
		{
			.Move = MOVE_BITE,
			.Level = 18,
		},
		{
			.Move = MOVE_ROAR,
			.Level = 23,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 28,
		},
		{
			.Move = MOVE_THUNDER_FANG,
			.Level = 33,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 38,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 43,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 48,
		},
		{
			.Move = MOVE_WILD_CHARGE,
			.Level = 53,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_LUXRAY] = {
		{
			.Move = MOVE_ELECTRIC_TERRAIN,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 5,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 9,
		},
		{
			.Move = MOVE_SPARK,
			.Level = 13,
		},
		{
			.Move = MOVE_BITE,
			.Level = 18,
		},
		{
			.Move = MOVE_ROAR,
			.Level = 23,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 28,
		},
		{
			.Move = MOVE_THUNDER_FANG,
			.Level = 35,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 42,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 49,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 56,
		},
		{
			.Move = MOVE_WILD_CHARGE,
			.Level = 63,
		},
		{
			.Move = MOVE_ELECTRIC_TERRAIN,
			.Level = 67,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BUDEW] = {
		{
			.Move = MOVE_ABSORB,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWTH,
			.Level = 4,
		},
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 7,
		},
		{
			.Move = MOVE_STUN_SPORE,
			.Level = 10,
		},
		{
			.Move = MOVE_MEGA_DRAIN,
			.Level = 13,
		},
		{
			.Move = MOVE_WORRY_SEED,
			.Level = 16,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ROSERADE] = {
		{
			.Move = MOVE_VENOM_DRENCH,
			.Level = 1,
		},
		{
			.Move = MOVE_GRASSY_TERRAIN,
			.Level = 1,
		},
		{
			.Move = MOVE_WEATHER_BALL,
			.Level = 1,
		},
		{
			.Move = MOVE_POISON_STING,
			.Level = 1,
		},
		{
			.Move = MOVE_MEGA_DRAIN,
			.Level = 1,
		},
		{
			.Move = MOVE_MAGICAL_LEAF,
			.Level = 1,
		},
		{
			.Move = MOVE_SWEET_SCENT,
			.Level = 1,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CRANIDOS] = {
		{
			.Move = MOVE_HEADBUTT,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 6,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 10,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 15,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 19,
		},
		{
			.Move = MOVE_ASSURANCE,
			.Level = 24,
		},
		{
			.Move = MOVE_CHIP_AWAY,
			.Level = 28,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 33,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 37,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 42,
		},
		{
			.Move = MOVE_HEAD_SMASH,
			.Level = 46,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_RAMPARDOS] = {
		{
			.Move = MOVE_HEADBUTT,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 6,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 10,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 15,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 19,
		},
		{
			.Move = MOVE_ASSURANCE,
			.Level = 24,
		},
		{
			.Move = MOVE_CHIP_AWAY,
			.Level = 28,
		},
		{
			.Move = MOVE_ENDEAVOR,
			.Level = 30,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 36,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 43,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 51,
		},
		{
			.Move = MOVE_HEAD_SMASH,
			.Level = 58,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SHIELDON] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 1,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 6,
		},
		{
			.Move = MOVE_METAL_SOUND,
			.Level = 10,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 15,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 19,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 24,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 28,
		},
		{
			.Move = MOVE_ENDURE,
			.Level = 33,
		},
		{
			.Move = MOVE_METAL_BURST,
			.Level = 37,
		},
		{
			.Move = MOVE_IRON_HEAD,
			.Level = 42,
		},
		{
			.Move = MOVE_HEAVY_SLAM,
			.Level = 46,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BASTIODON] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 1,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 1,
		},
		{
			.Move = MOVE_METAL_SOUND,
			.Level = 1,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 6,
		},
		{
			.Move = MOVE_METAL_SOUND,
			.Level = 10,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 15,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 19,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 24,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 28,
		},
		{
			.Move = MOVE_BLOCK,
			.Level = 30,
		},
		{
			.Move = MOVE_ENDURE,
			.Level = 36,
		},
		{
			.Move = MOVE_METAL_BURST,
			.Level = 43,
		},
		{
			.Move = MOVE_IRON_HEAD,
			.Level = 51,
		},
		{
			.Move = MOVE_HEAVY_SLAM,
			.Level = 58,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BURMY] = {
		{
			.Move = MOVE_PROTECT,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 10,
		},
		{
			.Move = MOVE_BUG_BITE,
			.Level = 15,
		},
		{
			.Move = MOVE_HIDDEN_POWER,
			.Level = 20,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_WORMADAM] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 10,
		},
		{
			.Move = MOVE_BUG_BITE,
			.Level = 15,
		},
		{
			.Move = MOVE_HIDDEN_POWER,
			.Level = 20,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 23,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 26,
		},
		{
			.Move = MOVE_GROWTH,
			.Level = 29,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 32,
		},
		{
			.Move = MOVE_CAPTIVATE,
			.Level = 35,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 38,
		},
		{
			.Move = MOVE_ATTRACT,
			.Level = 41,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 44,
		},
		{
			.Move = MOVE_LEAF_STORM,
			.Level = 47,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MOTHIM] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 10,
		},
		{
			.Move = MOVE_BUG_BITE,
			.Level = 15,
		},
		{
			.Move = MOVE_HIDDEN_POWER,
			.Level = 20,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 23,
		},
		{
			.Move = MOVE_GUST,
			.Level = 26,
		},
		{
			.Move = MOVE_POISONPOWDER,
			.Level = 29,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 32,
		},
		{
			.Move = MOVE_CAMOUFLAGE,
			.Level = 35,
		},
		{
			.Move = MOVE_SILVER_WIND,
			.Level = 38,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 41,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 44,
		},
		{
			.Move = MOVE_BUG_BUZZ,
			.Level = 47,
		},
		{
			.Move = MOVE_QUIVER_DANCE,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_COMBEE] = {
		{
			.Move = MOVE_SWEET_SCENT,
			.Level = 1,
		},
		{
			.Move = MOVE_GUST,
			.Level = 1,
		},
		{
			.Move = MOVE_BUG_BITE,
			.Level = 13,
		},
		{
			.Move = MOVE_BUG_BUZZ,
			.Level = 29,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_VESPIQUEN] = {
		{
			.Move = MOVE_FELL_STINGER,
			.Level = 1,
		},
		{
			.Move = MOVE_DESTINY_BOND,
			.Level = 1,
		},
		{
			.Move = MOVE_SWEET_SCENT,
			.Level = 1,
		},
		{
			.Move = MOVE_GUST,
			.Level = 1,
		},
		{
			.Move = MOVE_POISON_STING,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 1,
		},
		{
			.Move = MOVE_FURY_CUTTER,
			.Level = 5,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 9,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 13,
		},
		{
			.Move = MOVE_DEFEND_ORDER,
			.Level = 17,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 21,
		},
		{
			.Move = MOVE_POWER_GEM,
			.Level = 25,
		},
		{
			.Move = MOVE_HEAL_ORDER,
			.Level = 29,
		},
		{
			.Move = MOVE_TOXIC,
			.Level = 33,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 37,
		},
		{
			.Move = MOVE_CAPTIVATE,
			.Level = 41,
		},
		{
			.Move = MOVE_ATTACK_ORDER,
			.Level = 45,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 49,
		},
		{
			.Move = MOVE_DESTINY_BOND,
			.Level = 53,
		},
		{
			.Move = MOVE_FELL_STINGER,
			.Level = 57,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PACHIRISU] = {
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_BIDE,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 5,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 9,
		},
		{
			.Move = MOVE_SPARK,
			.Level = 13,
		},
		{
			.Move = MOVE_ENDURE,
			.Level = 17,
		},
		{
			.Move = MOVE_NUZZLE,
			.Level = 19,
		},
		{
			.Move = MOVE_SWIFT,
			.Level = 21,
		},
		{
			.Move = MOVE_ELECTRO_BALL,
			.Level = 25,
		},
		{
			.Move = MOVE_SWEET_KISS,
			.Level = 29,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 33,
		},
		{
			.Move = MOVE_SUPER_FANG,
			.Level = 37,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 41,
		},
		{
			.Move = MOVE_LAST_RESORT,
			.Level = 45,
		},
		{
			.Move = MOVE_HYPER_FANG,
			.Level = 49,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BUIZEL] = {
		{
			.Move = MOVE_SONICBOOM,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 4,
		},
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 7,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 11,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 15,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 18,
		},
		{
			.Move = MOVE_SWIFT,
			.Level = 21,
		},
		{
			.Move = MOVE_AQUA_JET,
			.Level = 24,
		},
		{
			.Move = MOVE_DOUBLE_HIT,
			.Level = 27,
		},
		{
			.Move = MOVE_WHIRLPOOL,
			.Level = 31,
		},
		{
			.Move = MOVE_RAZOR_WIND,
			.Level = 35,
		},
		{
			.Move = MOVE_AQUA_TAIL,
			.Level = 38,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 41,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 45,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_FLOATZEL] = {
		{
			.Move = MOVE_ICE_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 1,
		},
		{
			.Move = MOVE_SONICBOOM,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 4,
		},
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 7,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 11,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 15,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 18,
		},
		{
			.Move = MOVE_SWIFT,
			.Level = 21,
		},
		{
			.Move = MOVE_AQUA_JET,
			.Level = 24,
		},
		{
			.Move = MOVE_DOUBLE_HIT,
			.Level = 29,
		},
		{
			.Move = MOVE_WHIRLPOOL,
			.Level = 35,
		},
		{
			.Move = MOVE_RAZOR_WIND,
			.Level = 41,
		},
		{
			.Move = MOVE_AQUA_TAIL,
			.Level = 46,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 51,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 57,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CHERUBI] = {
		{
			.Move = MOVE_MORNING_SUN,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWTH,
			.Level = 7,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 10,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 13,
		},
		{
			.Move = MOVE_MAGICAL_LEAF,
			.Level = 19,
		},
		{
			.Move = MOVE_SUNNY_DAY,
			.Level = 22,
		},
		{
			.Move = MOVE_WORRY_SEED,
			.Level = 28,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 31,
		},
		{
			.Move = MOVE_SOLARBEAM,
			.Level = 37,
		},
		{
			.Move = MOVE_LUCKY_CHANT,
			.Level = 40,
		},
		{
			.Move = MOVE_PETAL_BLIZZARD,
			.Level = 47,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CHERRIM] = {
		{
			.Move = MOVE_MORNING_SUN,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWTH,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWTH,
			.Level = 7,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 10,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 13,
		},
		{
			.Move = MOVE_MAGICAL_LEAF,
			.Level = 19,
		},
		{
			.Move = MOVE_SUNNY_DAY,
			.Level = 22,
		},
		{
			.Move = MOVE_PETAL_DANCE,
			.Level = 25,
		},
		{
			.Move = MOVE_WORRY_SEED,
			.Level = 30,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 35,
		},
		{
			.Move = MOVE_SOLARBEAM,
			.Level = 43,
		},
		{
			.Move = MOVE_LUCKY_CHANT,
			.Level = 48,
		},
		{
			.Move = MOVE_PETAL_BLIZZARD,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SHELLOS] = {
		{
			.Move = MOVE_MUDSLAP,
			.Level = 1,
		},
		{
			.Move = MOVE_MUD_SPORT,
			.Level = 2,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 4,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 7,
		},
		{
			.Move = MOVE_MUD_BOMB,
			.Level = 11,
		},
		{
			.Move = MOVE_HIDDEN_POWER,
			.Level = 16,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 22,
		},
		{
			.Move = MOVE_BODY_SLAM,
			.Level = 29,
		},
		{
			.Move = MOVE_MUDDY_WATER,
			.Level = 37,
		},
		{
			.Move = MOVE_RECOVER,
			.Level = 46,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GASTRODON] = {
		{
			.Move = MOVE_MUDSLAP,
			.Level = 1,
		},
		{
			.Move = MOVE_MUD_SPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 1,
		},
		{
			.Move = MOVE_MUD_SPORT,
			.Level = 2,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 4,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 7,
		},
		{
			.Move = MOVE_MUD_BOMB,
			.Level = 11,
		},
		{
			.Move = MOVE_HIDDEN_POWER,
			.Level = 16,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 22,
		},
		{
			.Move = MOVE_BODY_SLAM,
			.Level = 29,
		},
		{
			.Move = MOVE_MUDDY_WATER,
			.Level = 41,
		},
		{
			.Move = MOVE_RECOVER,
			.Level = 54,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_AMBIPOM] = {
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 4,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 8,
		},
		{
			.Move = MOVE_BATON_PASS,
			.Level = 11,
		},
		{
			.Move = MOVE_TICKLE,
			.Level = 15,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 18,
		},
		{
			.Move = MOVE_SWIFT,
			.Level = 22,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 25,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 29,
		},
		{
			.Move = MOVE_DOUBLE_HIT,
			.Level = 32,
		},
		{
			.Move = MOVE_FLING,
			.Level = 36,
		},
		{
			.Move = MOVE_NASTY_PLOT,
			.Level = 39,
		},
		{
			.Move = MOVE_LAST_RESORT,
			.Level = 43,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_DRIFLOON] = {
		{
			.Move = MOVE_CONSTRICT,
			.Level = 1,
		},
		{
			.Move = MOVE_MINIMIZE,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 4,
		},
		{
			.Move = MOVE_GUST,
			.Level = 8,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 13,
		},
		{
			.Move = MOVE_PAYBACK,
			.Level = 16,
		},
		{
			.Move = MOVE_OMINOUS_WIND,
			.Level = 20,
		},
		{
			.Move = MOVE_STOCKPILE,
			.Level = 25,
		},
		{
			.Move = MOVE_HEX,
			.Level = 27,
		},
		{
			.Move = MOVE_SWALLOW,
			.Level = 32,
		},
		{
			.Move = MOVE_SPIT_UP,
			.Level = 32,
		},
		{
			.Move = MOVE_SHADOW_BALL,
			.Level = 36,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 40,
		},
		{
			.Move = MOVE_BATON_PASS,
			.Level = 44,
		},
		{
			.Move = MOVE_EXPLOSION,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_DRIFBLIM] = {
		{
			.Move = MOVE_PHANTOM_FORCE,
			.Level = 1,
		},
		{
			.Move = MOVE_CONSTRICT,
			.Level = 1,
		},
		{
			.Move = MOVE_MINIMIZE,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_GUST,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 4,
		},
		{
			.Move = MOVE_GUST,
			.Level = 8,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 13,
		},
		{
			.Move = MOVE_PAYBACK,
			.Level = 16,
		},
		{
			.Move = MOVE_OMINOUS_WIND,
			.Level = 20,
		},
		{
			.Move = MOVE_STOCKPILE,
			.Level = 25,
		},
		{
			.Move = MOVE_HEX,
			.Level = 27,
		},
		{
			.Move = MOVE_SWALLOW,
			.Level = 34,
		},
		{
			.Move = MOVE_SPIT_UP,
			.Level = 34,
		},
		{
			.Move = MOVE_SHADOW_BALL,
			.Level = 40,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 46,
		},
		{
			.Move = MOVE_BATON_PASS,
			.Level = 52,
		},
		{
			.Move = MOVE_EXPLOSION,
			.Level = 60,
		},
		{
			.Move = MOVE_PHANTOM_FORCE,
			.Level = 65,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BUNEARY] = {
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 1,
		},
		{
			.Move = MOVE_SPLASH,
			.Level = 1,
		},
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_FORESIGHT,
			.Level = 1,
		},
		{
			.Move = MOVE_ENDURE,
			.Level = 6,
		},
		{
			.Move = MOVE_BABYDOLL_EYES,
			.Level = 10,
		},
		{
			.Move = MOVE_FRUSTRATION,
			.Level = 13,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 16,
		},
		{
			.Move = MOVE_JUMP_KICK,
			.Level = 23,
		},
		{
			.Move = MOVE_BATON_PASS,
			.Level = 26,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 33,
		},
		{
			.Move = MOVE_DIZZY_PUNCH,
			.Level = 36,
		},
		{
			.Move = MOVE_AFTER_YOU,
			.Level = 43,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 46,
		},
		{
			.Move = MOVE_ENTRAINMENT,
			.Level = 50,
		},
		{
			.Move = MOVE_BOUNCE,
			.Level = 56,
		},
		{
			.Move = MOVE_HEALING_WISH,
			.Level = 63,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_LOPUNNY] = {
		{
			.Move = MOVE_HEALING_WISH,
			.Level = 1,
		},
		{
			.Move = MOVE_BOUNCE,
			.Level = 1,
		},
		{
			.Move = MOVE_ROTOTILLER,
			.Level = 1,
		},
		{
			.Move = MOVE_MIRROR_COAT,
			.Level = 1,
		},
		{
			.Move = MOVE_MAGIC_COAT,
			.Level = 1,
		},
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 1,
		},
		{
			.Move = MOVE_SPLASH,
			.Level = 1,
		},
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_FORESIGHT,
			.Level = 1,
		},
		{
			.Move = MOVE_ENDURE,
			.Level = 6,
		},
		{
			.Move = MOVE_RETURN,
			.Level = 13,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 16,
		},
		{
			.Move = MOVE_JUMP_KICK,
			.Level = 23,
		},
		{
			.Move = MOVE_BATON_PASS,
			.Level = 26,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 33,
		},
		{
			.Move = MOVE_DIZZY_PUNCH,
			.Level = 36,
		},
		{
			.Move = MOVE_AFTER_YOU,
			.Level = 43,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 46,
		},
		{
			.Move = MOVE_ENTRAINMENT,
			.Level = 53,
		},
		{
			.Move = MOVE_BOUNCE,
			.Level = 56,
		},
		{
			.Move = MOVE_HEALING_WISH,
			.Level = 63,
		},
		{
			.Move = MOVE_HI_JUMP_KICK,
			.Level = 66,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MISMAGIUS] = {
		{
			.Move = MOVE_MYSTICAL_FIRE,
			.Level = 1,
		},
		{
			.Move = MOVE_POWER_GEM,
			.Level = 1,
		},
		{
			.Move = MOVE_PHANTOM_FORCE,
			.Level = 1,
		},
		{
			.Move = MOVE_LUCKY_CHANT,
			.Level = 1,
		},
		{
			.Move = MOVE_MAGICAL_LEAF,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_PSYWAVE,
			.Level = 1,
		},
		{
			.Move = MOVE_SPITE,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_HONCHKROW] = {
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 1,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 1,
		},
		{
			.Move = MOVE_HAZE,
			.Level = 1,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 25,
		},
		{
			.Move = MOVE_NASTY_PLOT,
			.Level = 35,
		},
		{
			.Move = MOVE_FOUL_PLAY,
			.Level = 45,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 55,
		},
		{
			.Move = MOVE_QUASH,
			.Level = 65,
		},
		{
			.Move = MOVE_DARK_PULSE,
			.Level = 75,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GLAMEOW] = {
		{
			.Move = MOVE_FAKE_OUT,
			.Level = 1,
		},
		{
			.Move = MOVE_SCRATCH,
			.Level = 5,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 8,
		},
		{
			.Move = MOVE_HYPNOSIS,
			.Level = 13,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 17,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 20,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 25,
		},
		{
			.Move = MOVE_ASSIST,
			.Level = 29,
		},
		{
			.Move = MOVE_CAPTIVATE,
			.Level = 32,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 37,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 41,
		},
		{
			.Move = MOVE_ATTRACT,
			.Level = 44,
		},
		{
			.Move = MOVE_HONE_CLAWS,
			.Level = 48,
		},
		{
			.Move = MOVE_PLAY_ROUGH,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PURUGLY] = {
		{
			.Move = MOVE_FAKE_OUT,
			.Level = 1,
		},
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_SCRATCH,
			.Level = 5,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 8,
		},
		{
			.Move = MOVE_HYPNOSIS,
			.Level = 13,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 17,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 20,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 25,
		},
		{
			.Move = MOVE_ASSIST,
			.Level = 29,
		},
		{
			.Move = MOVE_CAPTIVATE,
			.Level = 32,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 37,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 38,
		},
		{
			.Move = MOVE_BODY_SLAM,
			.Level = 45,
		},
		{
			.Move = MOVE_ATTRACT,
			.Level = 52,
		},
		{
			.Move = MOVE_HONE_CLAWS,
			.Level = 60,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CHINGLING] = {
		{
			.Move = MOVE_WRAP,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 4,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 7,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 10,
		},
		{
			.Move = MOVE_YAWN,
			.Level = 13,
		},
		{
			.Move = MOVE_LAST_RESORT,
			.Level = 16,
		},
		{
			.Move = MOVE_ENTRAINMENT,
			.Level = 19,
		},
		{
			.Move = MOVE_UPROAR,
			.Level = 32,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_STUNKY] = {
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 1,
		},
		{
			.Move = MOVE_POISON_GAS,
			.Level = 4,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 7,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 10,
		},
		{
			.Move = MOVE_SMOKESCREEN,
			.Level = 14,
		},
		{
			.Move = MOVE_FEINT,
			.Level = 18,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 22,
		},
		{
			.Move = MOVE_TOXIC,
			.Level = 27,
		},
		{
			.Move = MOVE_ACID_SPRAY,
			.Level = 32,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 37,
		},
		{
			.Move = MOVE_MEMENTO,
			.Level = 43,
		},
		{
			.Move = MOVE_BELCH,
			.Level = 46,
		},
		{
			.Move = MOVE_EXPLOSION,
			.Level = 49,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SKUNTANK] = {
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 1,
		},
		{
			.Move = MOVE_POISON_GAS,
			.Level = 1,
		},
		{
			.Move = MOVE_POISON_GAS,
			.Level = 4,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 7,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 10,
		},
		{
			.Move = MOVE_SMOKESCREEN,
			.Level = 14,
		},
		{
			.Move = MOVE_FEINT,
			.Level = 18,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 22,
		},
		{
			.Move = MOVE_TOXIC,
			.Level = 27,
		},
		{
			.Move = MOVE_ACID_SPRAY,
			.Level = 32,
		},
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 34,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 41,
		},
		{
			.Move = MOVE_MEMENTO,
			.Level = 51,
		},
		{
			.Move = MOVE_BELCH,
			.Level = 56,
		},
		{
			.Move = MOVE_EXPLOSION,
			.Level = 61,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BRONZOR] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_HYPNOSIS,
			.Level = 5,
		},
		{
			.Move = MOVE_IMPRISON,
			.Level = 9,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 11,
		},
		{
			.Move = MOVE_PSYWAVE,
			.Level = 15,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 19,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 21,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 25,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 29,
		},
		{
			.Move = MOVE_METAL_SOUND,
			.Level = 31,
		},
		{
			.Move = MOVE_GYRO_BALL,
			.Level = 35,
		},
		{
			.Move = MOVE_EXTRASENSORY,
			.Level = 39,
		},
		{
			.Move = MOVE_PAYBACK,
			.Level = 41,
		},
		{
			.Move = MOVE_HEAL_BLOCK,
			.Level = 45,
		},
		{
			.Move = MOVE_HEAVY_SLAM,
			.Level = 49,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BRONZONG] = {
		{
			.Move = MOVE_SUNNY_DAY,
			.Level = 1,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_HYPNOSIS,
			.Level = 1,
		},
		{
			.Move = MOVE_IMPRISON,
			.Level = 1,
		},
		{
			.Move = MOVE_HYPNOSIS,
			.Level = 5,
		},
		{
			.Move = MOVE_IMPRISON,
			.Level = 9,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 11,
		},
		{
			.Move = MOVE_PSYWAVE,
			.Level = 15,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 19,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 21,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 25,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 29,
		},
		{
			.Move = MOVE_METAL_SOUND,
			.Level = 31,
		},
		{
			.Move = MOVE_BLOCK,
			.Level = 33,
		},
		{
			.Move = MOVE_GYRO_BALL,
			.Level = 36,
		},
		{
			.Move = MOVE_EXTRASENSORY,
			.Level = 42,
		},
		{
			.Move = MOVE_PAYBACK,
			.Level = 46,
		},
		{
			.Move = MOVE_HEAL_BLOCK,
			.Level = 52,
		},
		{
			.Move = MOVE_HEAVY_SLAM,
			.Level = 58,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BONSLY] = {
		{
			.Move = MOVE_FAKE_TEARS,
			.Level = 1,
		},
		{
			.Move = MOVE_COPYCAT,
			.Level = 1,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 5,
		},
		{
			.Move = MOVE_LOW_KICK,
			.Level = 8,
		},
		{
			.Move = MOVE_ROCK_THROW,
			.Level = 12,
		},
		{
			.Move = MOVE_MIMIC,
			.Level = 15,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 19,
		},
		{
			.Move = MOVE_ROCK_TOMB,
			.Level = 22,
		},
		{
			.Move = MOVE_BLOCK,
			.Level = 26,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 29,
		},
		{
			.Move = MOVE_COUNTER,
			.Level = 33,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 36,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 40,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MIME_JR] = {
		{
			.Move = MOVE_TICKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_BARRIER,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_COPYCAT,
			.Level = 4,
		},
		{
			.Move = MOVE_MEDITATE,
			.Level = 8,
		},
		{
			.Move = MOVE_DOUBLESLAP,
			.Level = 11,
		},
		{
			.Move = MOVE_MIMIC,
			.Level = 15,
		},
		{
			.Move = MOVE_ENCORE,
			.Level = 18,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 22,
		},
		{
			.Move = MOVE_REFLECT,
			.Level = 22,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 25,
		},
		{
			.Move = MOVE_SUBSTITUTE,
			.Level = 29,
		},
		{
			.Move = MOVE_RECYCLE,
			.Level = 32,
		},
		{
			.Move = MOVE_TRICK,
			.Level = 36,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 39,
		},
		{
			.Move = MOVE_ROLE_PLAY,
			.Level = 43,
		},
		{
			.Move = MOVE_BATON_PASS,
			.Level = 46,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_HAPPINY] = {
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 1,
		},
		{
			.Move = MOVE_COPYCAT,
			.Level = 5,
		},
		{
			.Move = MOVE_REFRESH,
			.Level = 9,
		},
		{
			.Move = MOVE_SWEET_KISS,
			.Level = 12,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CHATOT] = {
		{
			.Move = MOVE_HYPER_VOICE,
			.Level = 1,
		},
		{
			.Move = MOVE_CHATTER,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFIDE,
			.Level = 1,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 1,
		},
		{
			.Move = MOVE_PECK,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 5,
		},
		{
			.Move = MOVE_MIRROR_MOVE,
			.Level = 9,
		},
		{
			.Move = MOVE_SING,
			.Level = 13,
		},
		{
			.Move = MOVE_FURY_ATTACK,
			.Level = 17,
		},
		{
			.Move = MOVE_CHATTER,
			.Level = 21,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 25,
		},
		{
			.Move = MOVE_ROUND,
			.Level = 29,
		},
		{
			.Move = MOVE_MIMIC,
			.Level = 33,
		},
		{
			.Move = MOVE_ECHOED_VOICE,
			.Level = 37,
		},
		{
			.Move = MOVE_ROOST,
			.Level = 41,
		},
		{
			.Move = MOVE_UPROAR,
			.Level = 45,
		},
		{
			.Move = MOVE_SYNCHRONOISE,
			.Level = 49,
		},
		{
			.Move = MOVE_FEATHERDANCE,
			.Level = 50,
		},
		{
			.Move = MOVE_HYPER_VOICE,
			.Level = 57,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SPIRITOMB] = {
		{
			.Move = MOVE_CURSE,
			.Level = 1,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 1,
		},
		{
			.Move = MOVE_SPITE,
			.Level = 1,
		},
		{
			.Move = MOVE_SHADOW_SNEAK,
			.Level = 1,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 7,
		},
		{
			.Move = MOVE_HYPNOSIS,
			.Level = 13,
		},
		{
			.Move = MOVE_DREAM_EATER,
			.Level = 19,
		},
		{
			.Move = MOVE_OMINOUS_WIND,
			.Level = 25,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 31,
		},
		{
			.Move = MOVE_NASTY_PLOT,
			.Level = 37,
		},
		{
			.Move = MOVE_MEMENTO,
			.Level = 43,
		},
		{
			.Move = MOVE_DARK_PULSE,
			.Level = 49,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GIBLE] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 3,
		},
		{
			.Move = MOVE_DRAGON_RAGE,
			.Level = 7,
		},
		{
			.Move = MOVE_SANDSTORM,
			.Level = 13,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 15,
		},
		{
			.Move = MOVE_SAND_TOMB,
			.Level = 19,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 25,
		},
		{
			.Move = MOVE_DRAGON_CLAW,
			.Level = 27,
		},
		{
			.Move = MOVE_DIG,
			.Level = 31,
		},
		{
			.Move = MOVE_DRAGON_RUSH,
			.Level = 37,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GABITE] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 3,
		},
		{
			.Move = MOVE_DRAGON_RAGE,
			.Level = 7,
		},
		{
			.Move = MOVE_SANDSTORM,
			.Level = 13,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 15,
		},
		{
			.Move = MOVE_SAND_TOMB,
			.Level = 19,
		},
		{
			.Move = MOVE_DUAL_CHOP,
			.Level = 24,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 28,
		},
		{
			.Move = MOVE_DRAGON_CLAW,
			.Level = 33,
		},
		{
			.Move = MOVE_DIG,
			.Level = 40,
		},
		{
			.Move = MOVE_DRAGON_RUSH,
			.Level = 49,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GARCHOMP] = {
		{
			.Move = MOVE_FIRE_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_DRAGON_RAGE,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDSTORM,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 3,
		},
		{
			.Move = MOVE_DRAGON_RAGE,
			.Level = 7,
		},
		{
			.Move = MOVE_SANDSTORM,
			.Level = 13,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 15,
		},
		{
			.Move = MOVE_SAND_TOMB,
			.Level = 19,
		},
		{
			.Move = MOVE_DUAL_CHOP,
			.Level = 24,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 28,
		},
		{
			.Move = MOVE_DRAGON_CLAW,
			.Level = 33,
		},
		{
			.Move = MOVE_DIG,
			.Level = 40,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 48,
		},
		{
			.Move = MOVE_DRAGON_RUSH,
			.Level = 55,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MUNCHLAX] = {
		{
			.Move = MOVE_LAST_RESORT,
			.Level = 1,
		},
		{
			.Move = MOVE_RECYCLE,
			.Level = 1,
		},
		{
			.Move = MOVE_LICK,
			.Level = 1,
		},
		{
			.Move = MOVE_METRONOME,
			.Level = 1,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 4,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 9,
		},
		{
			.Move = MOVE_LICK,
			.Level = 12,
		},
		{
			.Move = MOVE_CHIP_AWAY,
			.Level = 17,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 20,
		},
		{
			.Move = MOVE_BODY_SLAM,
			.Level = 25,
		},
		{
			.Move = MOVE_STOCKPILE,
			.Level = 28,
		},
		{
			.Move = MOVE_SWALLOW,
			.Level = 33,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 36,
		},
		{
			.Move = MOVE_FLING,
			.Level = 41,
		},
		{
			.Move = MOVE_BELLY_DRUM,
			.Level = 44,
		},
		{
			.Move = MOVE_NATURAL_GIFT,
			.Level = 49,
		},
		{
			.Move = MOVE_SNATCH,
			.Level = 50,
		},
		{
			.Move = MOVE_LAST_RESORT,
			.Level = 57,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_RIOLU] = {
		{
			.Move = MOVE_FORESIGHT,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_ENDURE,
			.Level = 1,
		},
		{
			.Move = MOVE_COUNTER,
			.Level = 6,
		},
		{
			.Move = MOVE_FEINT,
			.Level = 11,
		},
		{
			.Move = MOVE_FORCE_PALM,
			.Level = 15,
		},
		{
			.Move = MOVE_COPYCAT,
			.Level = 19,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 24,
		},
		{
			.Move = MOVE_REVERSAL,
			.Level = 29,
		},
		{
			.Move = MOVE_NASTY_PLOT,
			.Level = 47,
		},
		{
			.Move = MOVE_FINAL_GAMBIT,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_LUCARIO] = {
		{
			.Move = MOVE_EXTREMESPEED,
			.Level = 1,
		},
		{
			.Move = MOVE_DRAGON_PULSE,
			.Level = 1,
		},
		{
			.Move = MOVE_CLOSE_COMBAT,
			.Level = 1,
		},
		{
			.Move = MOVE_AURA_SPHERE,
			.Level = 1,
		},
		{
			.Move = MOVE_FORESIGHT,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_DETECT,
			.Level = 1,
		},
		{
			.Move = MOVE_METAL_CLAW,
			.Level = 1,
		},
		{
			.Move = MOVE_COUNTER,
			.Level = 6,
		},
		{
			.Move = MOVE_FEINT,
			.Level = 11,
		},
		{
			.Move = MOVE_POWERUP_PUNCH,
			.Level = 15,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 19,
		},
		{
			.Move = MOVE_METAL_SOUND,
			.Level = 24,
		},
		{
			.Move = MOVE_BONE_RUSH,
			.Level = 29,
		},
		{
			.Move = MOVE_QUICK_GUARD,
			.Level = 33,
		},
		{
			.Move = MOVE_ME_FIRST,
			.Level = 37,
		},
		{
			.Move = MOVE_AURA_SPHERE,
			.Level = 42,
		},
		{
			.Move = MOVE_CALM_MIND,
			.Level = 47,
		},
		{
			.Move = MOVE_HEAL_PULSE,
			.Level = 51,
		},
		{
			.Move = MOVE_CLOSE_COMBAT,
			.Level = 55,
		},
		{
			.Move = MOVE_DRAGON_PULSE,
			.Level = 60,
		},
		{
			.Move = MOVE_EXTREMESPEED,
			.Level = 65,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_HIPPOPOTAS] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 7,
		},
		{
			.Move = MOVE_YAWN,
			.Level = 13,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 19,
		},
		{
			.Move = MOVE_DIG,
			.Level = 19,
		},
		{
			.Move = MOVE_SAND_TOMB,
			.Level = 25,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 31,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 37,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 44,
		},
		{
			.Move = MOVE_FISSURE,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_HIPPOWDON] = {
		{
			.Move = MOVE_ICE_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_FIRE_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_YAWN,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 7,
		},
		{
			.Move = MOVE_YAWN,
			.Level = 13,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 19,
		},
		{
			.Move = MOVE_DIG,
			.Level = 19,
		},
		{
			.Move = MOVE_SAND_TOMB,
			.Level = 25,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 31,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 40,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 50,
		},
		{
			.Move = MOVE_FISSURE,
			.Level = 60,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SKORUPI] = {
		{
			.Move = MOVE_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_POISON_STING,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_KNOCK_OFF,
			.Level = 5,
		},
		{
			.Move = MOVE_PIN_MISSILE,
			.Level = 9,
		},
		{
			.Move = MOVE_ACUPRESSURE,
			.Level = 13,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 16,
		},
		{
			.Move = MOVE_BUG_BITE,
			.Level = 20,
		},
		{
			.Move = MOVE_POISON_FANG,
			.Level = 23,
		},
		{
			.Move = MOVE_VENOSHOCK,
			.Level = 27,
		},
		{
			.Move = MOVE_HONE_CLAWS,
			.Level = 30,
		},
		{
			.Move = MOVE_TOXIC_SPIKES,
			.Level = 34,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 38,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 41,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 45,
		},
		{
			.Move = MOVE_FELL_STINGER,
			.Level = 47,
		},
		{
			.Move = MOVE_CROSS_POISON,
			.Level = 49,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_DRAPION] = {
		{
			.Move = MOVE_THUNDER_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_ICE_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_FIRE_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_POISON_STING,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_KNOCK_OFF,
			.Level = 1,
		},
		{
			.Move = MOVE_KNOCK_OFF,
			.Level = 5,
		},
		{
			.Move = MOVE_PIN_MISSILE,
			.Level = 9,
		},
		{
			.Move = MOVE_ACUPRESSURE,
			.Level = 13,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 16,
		},
		{
			.Move = MOVE_BUG_BITE,
			.Level = 20,
		},
		{
			.Move = MOVE_POISON_FANG,
			.Level = 23,
		},
		{
			.Move = MOVE_VENOSHOCK,
			.Level = 27,
		},
		{
			.Move = MOVE_HONE_CLAWS,
			.Level = 30,
		},
		{
			.Move = MOVE_TOXIC_SPIKES,
			.Level = 34,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 38,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 43,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 49,
		},
		{
			.Move = MOVE_FELL_STINGER,
			.Level = 53,
		},
		{
			.Move = MOVE_CROSS_POISON,
			.Level = 57,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CROAGUNK] = {
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 3,
		},
		{
			.Move = MOVE_POISON_STING,
			.Level = 8,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 10,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 15,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 17,
		},
		{
			.Move = MOVE_REVENGE,
			.Level = 22,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 24,
		},
		{
			.Move = MOVE_MUD_BOMB,
			.Level = 29,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 31,
		},
		{
			.Move = MOVE_VENOSHOCK,
			.Level = 36,
		},
		{
			.Move = MOVE_NASTY_PLOT,
			.Level = 38,
		},
		{
			.Move = MOVE_POISON_JAB,
			.Level = 43,
		},
		{
			.Move = MOVE_SLUDGE_BOMB,
			.Level = 45,
		},
		{
			.Move = MOVE_BELCH,
			.Level = 47,
		},
		{
			.Move = MOVE_FLATTER,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_TOXICROAK] = {
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 1,
		},
		{
			.Move = MOVE_POISON_STING,
			.Level = 1,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 3,
		},
		{
			.Move = MOVE_POISON_STING,
			.Level = 8,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 10,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 15,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 17,
		},
		{
			.Move = MOVE_REVENGE,
			.Level = 22,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 24,
		},
		{
			.Move = MOVE_MUD_BOMB,
			.Level = 29,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 31,
		},
		{
			.Move = MOVE_VENOSHOCK,
			.Level = 36,
		},
		{
			.Move = MOVE_NASTY_PLOT,
			.Level = 41,
		},
		{
			.Move = MOVE_POISON_JAB,
			.Level = 49,
		},
		{
			.Move = MOVE_SLUDGE_BOMB,
			.Level = 54,
		},
		{
			.Move = MOVE_BELCH,
			.Level = 58,
		},
		{
			.Move = MOVE_FLATTER,
			.Level = 62,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CARNIVINE] = {
		{
			.Move = MOVE_BIND,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWTH,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 7,
		},
		{
			.Move = MOVE_VINE_WHIP,
			.Level = 11,
		},
		{
			.Move = MOVE_SWEET_SCENT,
			.Level = 17,
		},
		{
			.Move = MOVE_INGRAIN,
			.Level = 21,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 27,
		},
		{
			.Move = MOVE_LEAF_TORNADO,
			.Level = 31,
		},
		{
			.Move = MOVE_STOCKPILE,
			.Level = 37,
		},
		{
			.Move = MOVE_SPIT_UP,
			.Level = 37,
		},
		{
			.Move = MOVE_SWALLOW,
			.Level = 37,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 41,
		},
		{
			.Move = MOVE_WRING_OUT,
			.Level = 47,
		},
		{
			.Move = MOVE_POWER_WHIP,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_FINNEON] = {
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 6,
		},
		{
			.Move = MOVE_ATTRACT,
			.Level = 10,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 13,
		},
		{
			.Move = MOVE_GUST,
			.Level = 17,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 22,
		},
		{
			.Move = MOVE_CAPTIVATE,
			.Level = 26,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 29,
		},
		{
			.Move = MOVE_AQUA_RING,
			.Level = 33,
		},
		{
			.Move = MOVE_WHIRLPOOL,
			.Level = 38,
		},
		{
			.Move = MOVE_UTURN,
			.Level = 42,
		},
		{
			.Move = MOVE_BOUNCE,
			.Level = 45,
		},
		{
			.Move = MOVE_SILVER_WIND,
			.Level = 49,
		},
		{
			.Move = MOVE_SOAK,
			.Level = 54,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_LUMINEON] = {
		{
			.Move = MOVE_SOAK,
			.Level = 1,
		},
		{
			.Move = MOVE_GUST,
			.Level = 1,
		},
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_ATTRACT,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 6,
		},
		{
			.Move = MOVE_ATTRACT,
			.Level = 10,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 13,
		},
		{
			.Move = MOVE_GUST,
			.Level = 17,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 22,
		},
		{
			.Move = MOVE_CAPTIVATE,
			.Level = 26,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 29,
		},
		{
			.Move = MOVE_AQUA_RING,
			.Level = 35,
		},
		{
			.Move = MOVE_WHIRLPOOL,
			.Level = 42,
		},
		{
			.Move = MOVE_UTURN,
			.Level = 48,
		},
		{
			.Move = MOVE_BOUNCE,
			.Level = 53,
		},
		{
			.Move = MOVE_SILVER_WIND,
			.Level = 59,
		},
		{
			.Move = MOVE_SOAK,
			.Level = 66,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MANTYKE] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_BUBBLE,
			.Level = 1,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 3,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 7,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 11,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 14,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 16,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 19,
		},
		{
			.Move = MOVE_WIDE_GUARD,
			.Level = 23,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 27,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 32,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 36,
		},
		{
			.Move = MOVE_AQUA_RING,
			.Level = 39,
		},
		{
			.Move = MOVE_BOUNCE,
			.Level = 46,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 49,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SNOVER] = {
		{
			.Move = MOVE_POWDER_SNOW,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 5,
		},
		{
			.Move = MOVE_ICY_WIND,
			.Level = 9,
		},
		{
			.Move = MOVE_GRASSWHISTLE,
			.Level = 13,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 17,
		},
		{
			.Move = MOVE_MIST,
			.Level = 21,
		},
		{
			.Move = MOVE_ICE_SHARD,
			.Level = 26,
		},
		{
			.Move = MOVE_INGRAIN,
			.Level = 31,
		},
		{
			.Move = MOVE_WOOD_HAMMER,
			.Level = 36,
		},
		{
			.Move = MOVE_BLIZZARD,
			.Level = 41,
		},
		{
			.Move = MOVE_SHEER_COLD,
			.Level = 46,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ABOMASNOW] = {
		{
			.Move = MOVE_ICE_PUNCH,
			.Level = 1,
		},
		{
			.Move = MOVE_POWDER_SNOW,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 1,
		},
		{
			.Move = MOVE_ICY_WIND,
			.Level = 1,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 5,
		},
		{
			.Move = MOVE_ICY_WIND,
			.Level = 9,
		},
		{
			.Move = MOVE_GRASSWHISTLE,
			.Level = 13,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 17,
		},
		{
			.Move = MOVE_MIST,
			.Level = 21,
		},
		{
			.Move = MOVE_ICE_SHARD,
			.Level = 26,
		},
		{
			.Move = MOVE_INGRAIN,
			.Level = 31,
		},
		{
			.Move = MOVE_WOOD_HAMMER,
			.Level = 36,
		},
		{
			.Move = MOVE_BLIZZARD,
			.Level = 47,
		},
		{
			.Move = MOVE_SHEER_COLD,
			.Level = 58,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_WEAVILE] = {
		{
			.Move = MOVE_EMBARGO,
			.Level = 1,
		},
		{
			.Move = MOVE_REVENGE,
			.Level = 1,
		},
		{
			.Move = MOVE_ASSURANCE,
			.Level = 1,
		},
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 8,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 10,
		},
		{
			.Move = MOVE_ICY_WIND,
			.Level = 14,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 16,
		},
		{
			.Move = MOVE_NASTY_PLOT,
			.Level = 20,
		},
		{
			.Move = MOVE_METAL_CLAW,
			.Level = 22,
		},
		{
			.Move = MOVE_HONE_CLAWS,
			.Level = 25,
		},
		{
			.Move = MOVE_FLING,
			.Level = 28,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 32,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 35,
		},
		{
			.Move = MOVE_SNATCH,
			.Level = 40,
		},
		{
			.Move = MOVE_PUNISHMENT,
			.Level = 44,
		},
		{
			.Move = MOVE_DARK_PULSE,
			.Level = 47,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MAGNEZONE] = {
		{
			.Move = MOVE_ZAP_CANNON,
			.Level = 1,
		},
		{
			.Move = MOVE_MAGNETIC_FLUX,
			.Level = 1,
		},
		{
			.Move = MOVE_MIRROR_COAT,
			.Level = 1,
		},
		{
			.Move = MOVE_BARRIER,
			.Level = 1,
		},
		{
			.Move = MOVE_ELECTRIC_TERRAIN,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 1,
		},
		{
			.Move = MOVE_SONICBOOM,
			.Level = 1,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 5,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 7,
		},
		{
			.Move = MOVE_SONICBOOM,
			.Level = 11,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 13,
		},
		{
			.Move = MOVE_MAGNET_BOMB,
			.Level = 17,
		},
		{
			.Move = MOVE_SPARK,
			.Level = 19,
		},
		{
			.Move = MOVE_MIRROR_SHOT,
			.Level = 23,
		},
		{
			.Move = MOVE_METAL_SOUND,
			.Level = 25,
		},
		{
			.Move = MOVE_ELECTRO_BALL,
			.Level = 29,
		},
		{
			.Move = MOVE_FLASH_CANNON,
			.Level = 33,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 39,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 43,
		},
		{
			.Move = MOVE_LOCKON,
			.Level = 49,
		},
		{
			.Move = MOVE_MAGNET_RISE,
			.Level = 53,
		},
		{
			.Move = MOVE_GYRO_BALL,
			.Level = 59,
		},
		{
			.Move = MOVE_ZAP_CANNON,
			.Level = 63,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_LICKILICKY] = {
		{
			.Move = MOVE_WRING_OUT,
			.Level = 1,
		},
		{
			.Move = MOVE_POWER_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_LICK,
			.Level = 1,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 5,
		},
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 9,
		},
		{
			.Move = MOVE_KNOCK_OFF,
			.Level = 13,
		},
		{
			.Move = MOVE_WRAP,
			.Level = 17,
		},
		{
			.Move = MOVE_STOMP,
			.Level = 21,
		},
		{
			.Move = MOVE_DISABLE,
			.Level = 25,
		},
		{
			.Move = MOVE_SLAM,
			.Level = 29,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 33,
		},
		{
			.Move = MOVE_CHIP_AWAY,
			.Level = 37,
		},
		{
			.Move = MOVE_ME_FIRST,
			.Level = 41,
		},
		{
			.Move = MOVE_REFRESH,
			.Level = 45,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 49,
		},
		{
			.Move = MOVE_POWER_WHIP,
			.Level = 53,
		},
		{
			.Move = MOVE_WRING_OUT,
			.Level = 57,
		},
		{
			.Move = MOVE_GYRO_BALL,
			.Level = 61,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_RHYPERIOR] = {
		{
			.Move = MOVE_ROCK_WRECKER,
			.Level = 1,
		},
		{
			.Move = MOVE_HORN_DRILL,
			.Level = 1,
		},
		{
			.Move = MOVE_POISON_JAB,
			.Level = 1,
		},
		{
			.Move = MOVE_HORN_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_FURY_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 1,
		},
		{
			.Move = MOVE_FURY_ATTACK,
			.Level = 5,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 9,
		},
		{
			.Move = MOVE_SMACK_DOWN,
			.Level = 13,
		},
		{
			.Move = MOVE_STOMP,
			.Level = 17,
		},
		{
			.Move = MOVE_BULLDOZE,
			.Level = 21,
		},
		{
			.Move = MOVE_CHIP_AWAY,
			.Level = 25,
		},
		{
			.Move = MOVE_ROCK_BLAST,
			.Level = 29,
		},
		{
			.Move = MOVE_DRILL_RUN,
			.Level = 33,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 37,
		},
		{
			.Move = MOVE_STONE_EDGE,
			.Level = 41,
		},
		{
			.Move = MOVE_HAMMER_ARM,
			.Level = 42,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 48,
		},
		{
			.Move = MOVE_MEGAHORN,
			.Level = 55,
		},
		{
			.Move = MOVE_HORN_DRILL,
			.Level = 62,
		},
		{
			.Move = MOVE_ROCK_WRECKER,
			.Level = 69,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_TANGROWTH] = {
		{
			.Move = MOVE_BLOCK,
			.Level = 1,
		},
		{
			.Move = MOVE_INGRAIN,
			.Level = 1,
		},
		{
			.Move = MOVE_CONSTRICT,
			.Level = 1,
		},
		{
			.Move = MOVE_SLEEP_POWDER,
			.Level = 4,
		},
		{
			.Move = MOVE_VINE_WHIP,
			.Level = 7,
		},
		{
			.Move = MOVE_ABSORB,
			.Level = 10,
		},
		{
			.Move = MOVE_POISONPOWDER,
			.Level = 14,
		},
		{
			.Move = MOVE_BIND,
			.Level = 17,
		},
		{
			.Move = MOVE_GROWTH,
			.Level = 20,
		},
		{
			.Move = MOVE_MEGA_DRAIN,
			.Level = 23,
		},
		{
			.Move = MOVE_KNOCK_OFF,
			.Level = 27,
		},
		{
			.Move = MOVE_STUN_SPORE,
			.Level = 30,
		},
		{
			.Move = MOVE_NATURAL_GIFT,
			.Level = 33,
		},
		{
			.Move = MOVE_GIGA_DRAIN,
			.Level = 36,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 40,
		},
		{
			.Move = MOVE_SLAM,
			.Level = 43,
		},
		{
			.Move = MOVE_TICKLE,
			.Level = 46,
		},
		{
			.Move = MOVE_WRING_OUT,
			.Level = 49,
		},
		{
			.Move = MOVE_GRASSY_TERRAIN,
			.Level = 50,
		},
		{
			.Move = MOVE_POWER_WHIP,
			.Level = 53,
		},
		{
			.Move = MOVE_BLOCK,
			.Level = 56,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ELECTIVIRE] = {
		{
			.Move = MOVE_ELECTRIC_TERRAIN,
			.Level = 1,
		},
		{
			.Move = MOVE_ION_DELUGE,
			.Level = 1,
		},
		{
			.Move = MOVE_FIRE_PUNCH,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 1,
		},
		{
			.Move = MOVE_LOW_KICK,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 5,
		},
		{
			.Move = MOVE_LOW_KICK,
			.Level = 8,
		},
		{
			.Move = MOVE_SWIFT,
			.Level = 12,
		},
		{
			.Move = MOVE_SHOCK_WAVE,
			.Level = 15,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 19,
		},
		{
			.Move = MOVE_ELECTRO_BALL,
			.Level = 22,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 26,
		},
		{
			.Move = MOVE_THUNDERPUNCH,
			.Level = 29,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 36,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 42,
		},
		{
			.Move = MOVE_THUNDERBOLT,
			.Level = 49,
		},
		{
			.Move = MOVE_THUNDER,
			.Level = 55,
		},
		{
			.Move = MOVE_GIGA_IMPACT,
			.Level = 62,
		},
		{
			.Move = MOVE_ELECTRIC_TERRAIN,
			.Level = 65,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MAGMORTAR] = {
		{
			.Move = MOVE_THUNDERPUNCH,
			.Level = 1,
		},
		{
			.Move = MOVE_SMOG,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 1,
		},
		{
			.Move = MOVE_SMOKESCREEN,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 5,
		},
		{
			.Move = MOVE_SMOKESCREEN,
			.Level = 8,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 12,
		},
		{
			.Move = MOVE_FIRE_SPIN,
			.Level = 15,
		},
		{
			.Move = MOVE_CLEAR_SMOG,
			.Level = 19,
		},
		{
			.Move = MOVE_FLAME_BURST,
			.Level = 22,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 26,
		},
		{
			.Move = MOVE_FIRE_PUNCH,
			.Level = 29,
		},
		{
			.Move = MOVE_LAVA_PLUME,
			.Level = 36,
		},
		{
			.Move = MOVE_SUNNY_DAY,
			.Level = 42,
		},
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 49,
		},
		{
			.Move = MOVE_FIRE_BLAST,
			.Level = 55,
		},
		{
			.Move = MOVE_HYPER_BEAM,
			.Level = 62,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_TOGEKISS] = {
		{
			.Move = MOVE_AFTER_YOU,
			.Level = 1,
		},
		{
			.Move = MOVE_SKY_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_EXTREMESPEED,
			.Level = 1,
		},
		{
			.Move = MOVE_AURA_SPHERE,
			.Level = 1,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 1,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_YANMEGA] = {
		{
			.Move = MOVE_BUG_BUZZ,
			.Level = 1,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 1,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 1,
		},
		{
			.Move = MOVE_BUG_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_FORESIGHT,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 6,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 11,
		},
		{
			.Move = MOVE_SONICBOOM,
			.Level = 14,
		},
		{
			.Move = MOVE_DETECT,
			.Level = 17,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 22,
		},
		{
			.Move = MOVE_UPROAR,
			.Level = 27,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 30,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 33,
		},
		{
			.Move = MOVE_FEINT,
			.Level = 38,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 43,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 46,
		},
		{
			.Move = MOVE_UTURN,
			.Level = 49,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 54,
		},
		{
			.Move = MOVE_BUG_BUZZ,
			.Level = 57,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_LEAFEON] = {
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 5,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 9,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 13,
		},
		{
			.Move = MOVE_GRASSWHISTLE,
			.Level = 17,
		},
		{
			.Move = MOVE_MAGICAL_LEAF,
			.Level = 20,
		},
		{
			.Move = MOVE_GIGA_DRAIN,
			.Level = 25,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 29,
		},
		{
			.Move = MOVE_SYNTHESIS,
			.Level = 33,
		},
		{
			.Move = MOVE_SUNNY_DAY,
			.Level = 37,
		},
		{
			.Move = MOVE_LAST_RESORT,
			.Level = 41,
		},
		{
			.Move = MOVE_LEAF_BLADE,
			.Level = 45,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GLACEON] = {
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 5,
		},
		{
			.Move = MOVE_ICY_WIND,
			.Level = 9,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 13,
		},
		{
			.Move = MOVE_BITE,
			.Level = 17,
		},
		{
			.Move = MOVE_ICE_FANG,
			.Level = 20,
		},
		{
			.Move = MOVE_ICE_SHARD,
			.Level = 25,
		},
		{
			.Move = MOVE_BARRIER,
			.Level = 29,
		},
		{
			.Move = MOVE_MIRROR_COAT,
			.Level = 33,
		},
		{
			.Move = MOVE_HAIL,
			.Level = 37,
		},
		{
			.Move = MOVE_LAST_RESORT,
			.Level = 41,
		},
		{
			.Move = MOVE_BLIZZARD,
			.Level = 45,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GLISCOR] = {
		{
			.Move = MOVE_GUILLOTINE,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_ICE_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_FIRE_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_POISON_JAB,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 1,
		},
		{
			.Move = MOVE_KNOCK_OFF,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 4,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 7,
		},
		{
			.Move = MOVE_KNOCK_OFF,
			.Level = 10,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 13,
		},
		{
			.Move = MOVE_FURY_CUTTER,
			.Level = 16,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 19,
		},
		{
			.Move = MOVE_ACROBATICS,
			.Level = 22,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 27,
		},
		{
			.Move = MOVE_UTURN,
			.Level = 30,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 35,
		},
		{
			.Move = MOVE_XSCISSOR,
			.Level = 40,
		},
		{
			.Move = MOVE_SKY_UPPERCUT,
			.Level = 45,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 50,
		},
		{
			.Move = MOVE_GUILLOTINE,
			.Level = 55,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MAMOSWINE] = {
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 1,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 1,
		},
		{
			.Move = MOVE_PECK,
			.Level = 1,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 1,
		},
		{
			.Move = MOVE_MUD_SPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_POWDER_SNOW,
			.Level = 1,
		},
		{
			.Move = MOVE_MUD_SPORT,
			.Level = 5,
		},
		{
			.Move = MOVE_POWDER_SNOW,
			.Level = 8,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 11,
		},
		{
			.Move = MOVE_ENDURE,
			.Level = 14,
		},
		{
			.Move = MOVE_MUD_BOMB,
			.Level = 18,
		},
		{
			.Move = MOVE_HAIL,
			.Level = 21,
		},
		{
			.Move = MOVE_ICE_FANG,
			.Level = 24,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 28,
		},
		{
			.Move = MOVE_DOUBLE_HIT,
			.Level = 33,
		},
		{
			.Move = MOVE_MIST,
			.Level = 37,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 41,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 46,
		},
		{
			.Move = MOVE_BLIZZARD,
			.Level = 52,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 58,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PORYGONZ] = {
		{
			.Move = MOVE_TRICK_ROOM,
			.Level = 1,
		},
		{
			.Move = MOVE_ZAP_CANNON,
			.Level = 1,
		},
		{
			.Move = MOVE_MAGIC_COAT,
			.Level = 1,
		},
		{
			.Move = MOVE_CONVERSION_2,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_CONVERSION,
			.Level = 1,
		},
		{
			.Move = MOVE_NASTY_PLOT,
			.Level = 1,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 7,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 12,
		},
		{
			.Move = MOVE_RECOVER,
			.Level = 18,
		},
		{
			.Move = MOVE_MAGNET_RISE,
			.Level = 23,
		},
		{
			.Move = MOVE_SIGNAL_BEAM,
			.Level = 29,
		},
		{
			.Move = MOVE_EMBARGO,
			.Level = 34,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 40,
		},
		{
			.Move = MOVE_LOCKON,
			.Level = 45,
		},
		{
			.Move = MOVE_TRI_ATTACK,
			.Level = 50,
		},
		{
			.Move = MOVE_MAGIC_COAT,
			.Level = 56,
		},
		{
			.Move = MOVE_ZAP_CANNON,
			.Level = 62,
		},
		{
			.Move = MOVE_HYPER_BEAM,
			.Level = 67,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GALLADE] = {
		{
			.Move = MOVE_STORED_POWER,
			.Level = 1,
		},
		{
			.Move = MOVE_CLOSE_COMBAT,
			.Level = 1,
		},
		{
			.Move = MOVE_LEAF_BLADE,
			.Level = 1,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 1,
		},
		{
			.Move = MOVE_TELEPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 4,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 6,
		},
		{
			.Move = MOVE_TELEPORT,
			.Level = 9,
		},
		{
			.Move = MOVE_QUICK_GUARD,
			.Level = 11,
		},
		{
			.Move = MOVE_FURY_CUTTER,
			.Level = 14,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 17,
		},
		{
			.Move = MOVE_HEAL_PULSE,
			.Level = 19,
		},
		{
			.Move = MOVE_WIDE_GUARD,
			.Level = 23,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 26,
		},
		{
			.Move = MOVE_PSYCHO_CUT,
			.Level = 31,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 35,
		},
		{
			.Move = MOVE_FEINT,
			.Level = 40,
		},
		{
			.Move = MOVE_FALSE_SWIPE,
			.Level = 44,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 49,
		},
		{
			.Move = MOVE_CLOSE_COMBAT,
			.Level = 53,
		},
		{
			.Move = MOVE_STORED_POWER,
			.Level = 58,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PROBOPASS] = {
		{
			.Move = MOVE_MAGNET_RISE,
			.Level = 1,
		},
		{
			.Move = MOVE_GRAVITY,
			.Level = 1,
		},
		{
			.Move = MOVE_WIDE_GUARD,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 1,
		},
		{
			.Move = MOVE_BLOCK,
			.Level = 1,
		},
		{
			.Move = MOVE_MAGNET_BOMB,
			.Level = 1,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 4,
		},
		{
			.Move = MOVE_BLOCK,
			.Level = 7,
		},
		{
			.Move = MOVE_MAGNET_BOMB,
			.Level = 10,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 13,
		},
		{
			.Move = MOVE_REST,
			.Level = 16,
		},
		{
			.Move = MOVE_SPARK,
			.Level = 19,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 22,
		},
		{
			.Move = MOVE_POWER_GEM,
			.Level = 25,
		},
		{
			.Move = MOVE_ROCK_BLAST,
			.Level = 28,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 31,
		},
		{
			.Move = MOVE_SANDSTORM,
			.Level = 34,
		},
		{
			.Move = MOVE_EARTH_POWER,
			.Level = 37,
		},
		{
			.Move = MOVE_STONE_EDGE,
			.Level = 40,
		},
		{
			.Move = MOVE_LOCKON,
			.Level = 43,
		},
		{
			.Move = MOVE_ZAP_CANNON,
			.Level = 43,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_DUSKNOIR] = {
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 1,
		},
		{
			.Move = MOVE_FIRE_PUNCH,
			.Level = 1,
		},
		{
			.Move = MOVE_ICE_PUNCH,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDERPUNCH,
			.Level = 1,
		},
		{
			.Move = MOVE_GRAVITY,
			.Level = 1,
		},
		{
			.Move = MOVE_BIND,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_NIGHT_SHADE,
			.Level = 1,
		},
		{
			.Move = MOVE_DISABLE,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_DISABLE,
			.Level = 6,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 9,
		},
		{
			.Move = MOVE_FORESIGHT,
			.Level = 14,
		},
		{
			.Move = MOVE_SHADOW_SNEAK,
			.Level = 17,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 22,
		},
		{
			.Move = MOVE_WILLOWISP,
			.Level = 25,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 30,
		},
		{
			.Move = MOVE_CURSE,
			.Level = 33,
		},
		{
			.Move = MOVE_SHADOW_PUNCH,
			.Level = 37,
		},
		{
			.Move = MOVE_HEX,
			.Level = 40,
		},
		{
			.Move = MOVE_SHADOW_BALL,
			.Level = 45,
		},
		{
			.Move = MOVE_MEAN_LOOK,
			.Level = 52,
		},
		{
			.Move = MOVE_PAYBACK,
			.Level = 57,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 64,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_FROSLASS] = {
		{
			.Move = MOVE_DESTINY_BOND,
			.Level = 1,
		},
		{
			.Move = MOVE_POWDER_SNOW,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 1,
		},
		{
			.Move = MOVE_ICE_SHARD,
			.Level = 1,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 5,
		},
		{
			.Move = MOVE_ICE_SHARD,
			.Level = 10,
		},
		{
			.Move = MOVE_ICY_WIND,
			.Level = 14,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 19,
		},
		{
			.Move = MOVE_DRAINING_KISS,
			.Level = 23,
		},
		{
			.Move = MOVE_OMINOUS_WIND,
			.Level = 28,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 32,
		},
		{
			.Move = MOVE_WAKEUP_SLAP,
			.Level = 37,
		},
		{
			.Move = MOVE_CAPTIVATE,
			.Level = 41,
		},
		{
			.Move = MOVE_SHADOW_BALL,
			.Level = 42,
		},
		{
			.Move = MOVE_BLIZZARD,
			.Level = 48,
		},
		{
			.Move = MOVE_HAIL,
			.Level = 54,
		},
		{
			.Move = MOVE_DESTINY_BOND,
			.Level = 61,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ROTOM] = {
		{
			.Move = MOVE_DISCHARGE,
			.Level = 1,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 1,
		},
		{
			.Move = MOVE_TRICK,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 1,
		},
		{
			.Move = MOVE_UPROAR,
			.Level = 8,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 15,
		},
		{
			.Move = MOVE_SHOCK_WAVE,
			.Level = 22,
		},
		{
			.Move = MOVE_OMINOUS_WIND,
			.Level = 29,
		},
		{
			.Move = MOVE_SUBSTITUTE,
			.Level = 36,
		},
		{
			.Move = MOVE_ELECTRO_BALL,
			.Level = 43,
		},
		{
			.Move = MOVE_HEX,
			.Level = 50,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 57,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 64,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_UXIE] = {
		{
			.Move = MOVE_MEMENTO,
			.Level = 1,
		},
		{
			.Move = MOVE_NATURAL_GIFT,
			.Level = 1,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 1,
		},
		{
			.Move = MOVE_REST,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_IMPRISON,
			.Level = 6,
		},
		{
			.Move = MOVE_ENDURE,
			.Level = 16,
		},
		{
			.Move = MOVE_SWIFT,
			.Level = 21,
		},
		{
			.Move = MOVE_YAWN,
			.Level = 31,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 36,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 46,
		},
		{
			.Move = MOVE_EXTRASENSORY,
			.Level = 50,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 61,
		},
		{
			.Move = MOVE_NATURAL_GIFT,
			.Level = 66,
		},
		{
			.Move = MOVE_MEMENTO,
			.Level = 76,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MESPRIT] = {
		{
			.Move = MOVE_HEALING_WISH,
			.Level = 1,
		},
		{
			.Move = MOVE_NATURAL_GIFT,
			.Level = 1,
		},
		{
			.Move = MOVE_COPYCAT,
			.Level = 1,
		},
		{
			.Move = MOVE_REST,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_IMPRISON,
			.Level = 6,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 16,
		},
		{
			.Move = MOVE_SWIFT,
			.Level = 21,
		},
		{
			.Move = MOVE_LUCKY_CHANT,
			.Level = 31,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 36,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 46,
		},
		{
			.Move = MOVE_EXTRASENSORY,
			.Level = 50,
		},
		{
			.Move = MOVE_COPYCAT,
			.Level = 61,
		},
		{
			.Move = MOVE_NATURAL_GIFT,
			.Level = 66,
		},
		{
			.Move = MOVE_HEALING_WISH,
			.Level = 76,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_AZELF] = {
		{
			.Move = MOVE_NATURAL_GIFT,
			.Level = 1,
		},
		{
			.Move = MOVE_LAST_RESORT,
			.Level = 1,
		},
		{
			.Move = MOVE_REST,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_IMPRISON,
			.Level = 6,
		},
		{
			.Move = MOVE_DETECT,
			.Level = 16,
		},
		{
			.Move = MOVE_SWIFT,
			.Level = 21,
		},
		{
			.Move = MOVE_UPROAR,
			.Level = 31,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 36,
		},
		{
			.Move = MOVE_NASTY_PLOT,
			.Level = 46,
		},
		{
			.Move = MOVE_EXTRASENSORY,
			.Level = 50,
		},
		{
			.Move = MOVE_LAST_RESORT,
			.Level = 61,
		},
		{
			.Move = MOVE_NATURAL_GIFT,
			.Level = 66,
		},
		{
			.Move = MOVE_EXPLOSION,
			.Level = 76,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_DIALGA] = {
		{
			.Move = MOVE_DRAGONBREATH,
			.Level = 1,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 1,
		},
		{
			.Move = MOVE_METAL_CLAW,
			.Level = 6,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 10,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 15,
		},
		{
			.Move = MOVE_POWER_GEM,
			.Level = 19,
		},
		{
			.Move = MOVE_METAL_BURST,
			.Level = 24,
		},
		{
			.Move = MOVE_DRAGON_CLAW,
			.Level = 28,
		},
		{
			.Move = MOVE_EARTH_POWER,
			.Level = 33,
		},
		{
			.Move = MOVE_AURA_SPHERE,
			.Level = 37,
		},
		{
			.Move = MOVE_IRON_TAIL,
			.Level = 42,
		},
		{
			.Move = MOVE_ROAR_OF_TIME,
			.Level = 46,
		},
		{
			.Move = MOVE_FLASH_CANNON,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PALKIA] = {
		{
			.Move = MOVE_DRAGONBREATH,
			.Level = 1,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 6,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 10,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 15,
		},
		{
			.Move = MOVE_POWER_GEM,
			.Level = 19,
		},
		{
			.Move = MOVE_AQUA_TAIL,
			.Level = 24,
		},
		{
			.Move = MOVE_DRAGON_CLAW,
			.Level = 28,
		},
		{
			.Move = MOVE_EARTH_POWER,
			.Level = 33,
		},
		{
			.Move = MOVE_AURA_SPHERE,
			.Level = 37,
		},
		{
			.Move = MOVE_AQUA_TAIL,
			.Level = 42,
		},
		{
			.Move = MOVE_SPACIAL_REND,
			.Level = 46,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_HEATRAN] = {
		{
			.Move = MOVE_MAGMA_STORM,
			.Level = 1,
		},
		{
			.Move = MOVE_HEAT_WAVE,
			.Level = 1,
		},
		{
			.Move = MOVE_EARTH_POWER,
			.Level = 1,
		},
		{
			.Move = MOVE_IRON_HEAD,
			.Level = 1,
		},
		{
			.Move = MOVE_FIRE_SPIN,
			.Level = 1,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 9,
		},
		{
			.Move = MOVE_FIRE_FANG,
			.Level = 17,
		},
		{
			.Move = MOVE_METAL_SOUND,
			.Level = 25,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 33,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 41,
		},
		{
			.Move = MOVE_LAVA_PLUME,
			.Level = 49,
		},
		{
			.Move = MOVE_FIRE_SPIN,
			.Level = 57,
		},
		{
			.Move = MOVE_IRON_HEAD,
			.Level = 65,
		},
		{
			.Move = MOVE_EARTH_POWER,
			.Level = 73,
		},
		{
			.Move = MOVE_HEAT_WAVE,
			.Level = 81,
		},
		{
			.Move = MOVE_STONE_EDGE,
			.Level = 88,
		},
		{
			.Move = MOVE_MAGMA_STORM,
			.Level = 96,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_REGIGIGAS] = {
		{
			.Move = MOVE_HEAVY_SLAM,
			.Level = 1,
		},
		{
			.Move = MOVE_CRUSH_GRIP,
			.Level = 1,
		},
		{
			.Move = MOVE_FIRE_PUNCH,
			.Level = 1,
		},
		{
			.Move = MOVE_ICE_PUNCH,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDERPUNCH,
			.Level = 1,
		},
		{
			.Move = MOVE_DIZZY_PUNCH,
			.Level = 1,
		},
		{
			.Move = MOVE_KNOCK_OFF,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 1,
		},
		{
			.Move = MOVE_FORESIGHT,
			.Level = 1,
		},
		{
			.Move = MOVE_REVENGE,
			.Level = 25,
		},
		{
			.Move = MOVE_WIDE_GUARD,
			.Level = 40,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 50,
		},
		{
			.Move = MOVE_PAYBACK,
			.Level = 65,
		},
		{
			.Move = MOVE_CRUSH_GRIP,
			.Level = 75,
		},
		{
			.Move = MOVE_HEAVY_SLAM,
			.Level = 90,
		},
		{
			.Move = MOVE_GIGA_IMPACT,
			.Level = 100,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GIRATINA] = {
		{
			.Move = MOVE_DRAGONBREATH,
			.Level = 1,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 1,
		},
		{
			.Move = MOVE_OMINOUS_WIND,
			.Level = 6,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 10,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 15,
		},
		{
			.Move = MOVE_SHADOW_SNEAK,
			.Level = 19,
		},
		{
			.Move = MOVE_DESTINY_BOND,
			.Level = 24,
		},
		{
			.Move = MOVE_DRAGON_CLAW,
			.Level = 28,
		},
		{
			.Move = MOVE_EARTH_POWER,
			.Level = 33,
		},
		{
			.Move = MOVE_AURA_SPHERE,
			.Level = 37,
		},
		{
			.Move = MOVE_SHADOW_CLAW,
			.Level = 42,
		},
		{
			.Move = MOVE_SHADOW_FORCE,
			.Level = 46,
		},
		{
			.Move = MOVE_HEX,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CRESSELIA] = {
		{
			.Move = MOVE_LUNAR_DANCE,
			.Level = 1,
		},
		{
			.Move = MOVE_PSYCHO_SHIFT,
			.Level = 1,
		},
		{
			.Move = MOVE_PSYCHO_CUT,
			.Level = 1,
		},
		{
			.Move = MOVE_MOONLIGHT,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 1,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 11,
		},
		{
			.Move = MOVE_MIST,
			.Level = 20,
		},
		{
			.Move = MOVE_AURORA_BEAM,
			.Level = 29,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 38,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 47,
		},
		{
			.Move = MOVE_MOONLIGHT,
			.Level = 57,
		},
		{
			.Move = MOVE_PSYCHO_CUT,
			.Level = 66,
		},
		{
			.Move = MOVE_PSYCHO_SHIFT,
			.Level = 75,
		},
		{
			.Move = MOVE_LUNAR_DANCE,
			.Level = 84,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 93,
		},
		{
			.Move = MOVE_MOONBLAST,
			.Level = 99,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PHIONE] = {
		{
			.Move = MOVE_BUBBLE,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 9,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 16,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 24,
		},
		{
			.Move = MOVE_ACID_ARMOR,
			.Level = 31,
		},
		{
			.Move = MOVE_WHIRLPOOL,
			.Level = 39,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 46,
		},
		{
			.Move = MOVE_AQUA_RING,
			.Level = 54,
		},
		{
			.Move = MOVE_DIVE,
			.Level = 61,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 69,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MANAPHY] = {
		{
			.Move = MOVE_TAIL_GLOW,
			.Level = 1,
		},
		{
			.Move = MOVE_BUBBLE,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 9,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 16,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 24,
		},
		{
			.Move = MOVE_ACID_ARMOR,
			.Level = 31,
		},
		{
			.Move = MOVE_WHIRLPOOL,
			.Level = 39,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 46,
		},
		{
			.Move = MOVE_AQUA_RING,
			.Level = 54,
		},
		{
			.Move = MOVE_DIVE,
			.Level = 61,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 69,
		},
		{
			.Move = MOVE_HEART_SWAP,
			.Level = 76,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_DARKRAI] = {
		{
			.Move = MOVE_OMINOUS_WIND,
			.Level = 1,
		},
		{
			.Move = MOVE_DISABLE,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 11,
		},
		{
			.Move = MOVE_HYPNOSIS,
			.Level = 20,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 29,
		},
		{
			.Move = MOVE_NIGHTMARE,
			.Level = 38,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 47,
		},
		{
			.Move = MOVE_HAZE,
			.Level = 57,
		},
		{
			.Move = MOVE_DARK_VOID,
			.Level = 66,
		},
		{
			.Move = MOVE_NASTY_PLOT,
			.Level = 75,
		},
		{
			.Move = MOVE_DREAM_EATER,
			.Level = 84,
		},
		{
			.Move = MOVE_DARK_PULSE,
			.Level = 93,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SHAYMIN] = {
		{
			.Move = MOVE_GROWTH,
			.Level = 1,
		},
		{
			.Move = MOVE_MAGICAL_LEAF,
			.Level = 10,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 19,
		},
		{
			.Move = MOVE_SYNTHESIS,
			.Level = 28,
		},
		{
			.Move = MOVE_SWEET_SCENT,
			.Level = 37,
		},
		{
			.Move = MOVE_NATURAL_GIFT,
			.Level = 46,
		},
		{
			.Move = MOVE_WORRY_SEED,
			.Level = 55,
		},
		{
			.Move = MOVE_AROMATHERAPY,
			.Level = 64,
		},
		{
			.Move = MOVE_ENERGY_BALL,
			.Level = 73,
		},
		{
			.Move = MOVE_SWEET_KISS,
			.Level = 82,
		},
		{
			.Move = MOVE_HEALING_WISH,
			.Level = 91,
		},
		{
			.Move = MOVE_SEED_FLARE,
			.Level = 100,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ARCEUS] = {
		{
			.Move = MOVE_SEISMIC_TOSS,
			.Level = 1,
		},
		{
			.Move = MOVE_COSMIC_POWER,
			.Level = 1,
		},
		{
			.Move = MOVE_NATURAL_GIFT,
			.Level = 1,
		},
		{
			.Move = MOVE_PUNISHMENT,
			.Level = 1,
		},
		{
			.Move = MOVE_GRAVITY,
			.Level = 10,
		},
		{
			.Move = MOVE_EARTH_POWER,
			.Level = 20,
		},
		{
			.Move = MOVE_HYPER_VOICE,
			.Level = 30,
		},
		{
			.Move = MOVE_EXTREMESPEED,
			.Level = 40,
		},
		{
			.Move = MOVE_REFRESH,
			.Level = 50,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 60,
		},
		{
			.Move = MOVE_RECOVER,
			.Level = 70,
		},
		{
			.Move = MOVE_HYPER_BEAM,
			.Level = 80,
		},
		{
			.Move = MOVE_PERISH_SONG,
			.Level = 90,
		},
		{
			.Move = MOVE_JUDGMENT,
			.Level = 100,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_VICTINI] = {
		{
			.Move = MOVE_SEARING_SHOT,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_INCINERATE,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_ENDURE,
			.Level = 9,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 17,
		},
		{
			.Move = MOVE_FLAME_CHARGE,
			.Level = 25,
		},
		{
			.Move = MOVE_REVERSAL,
			.Level = 33,
		},
		{
			.Move = MOVE_FLAME_BURST,
			.Level = 41,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 49,
		},
		{
			.Move = MOVE_INFERNO,
			.Level = 57,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 65,
		},
		{
			.Move = MOVE_FLARE_BLITZ,
			.Level = 73,
		},
		{
			.Move = MOVE_FINAL_GAMBIT,
			.Level = 81,
		},
		{
			.Move = MOVE_STORED_POWER,
			.Level = 89,
		},
		{
			.Move = MOVE_OVERHEAT,
			.Level = 97,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SNIVY] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 4,
		},
		{
			.Move = MOVE_VINE_WHIP,
			.Level = 7,
		},
		{
			.Move = MOVE_WRAP,
			.Level = 10,
		},
		{
			.Move = MOVE_GROWTH,
			.Level = 13,
		},
		{
			.Move = MOVE_LEAF_TORNADO,
			.Level = 16,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 19,
		},
		{
			.Move = MOVE_MEGA_DRAIN,
			.Level = 22,
		},
		{
			.Move = MOVE_SLAM,
			.Level = 25,
		},
		{
			.Move = MOVE_LEAF_BLADE,
			.Level = 28,
		},
		{
			.Move = MOVE_COIL,
			.Level = 31,
		},
		{
			.Move = MOVE_GIGA_DRAIN,
			.Level = 34,
		},
		{
			.Move = MOVE_WRING_OUT,
			.Level = 37,
		},
		{
			.Move = MOVE_GASTRO_ACID,
			.Level = 40,
		},
		{
			.Move = MOVE_LEAF_STORM,
			.Level = 43,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SERVINE] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_VINE_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_WRAP,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 4,
		},
		{
			.Move = MOVE_VINE_WHIP,
			.Level = 7,
		},
		{
			.Move = MOVE_WRAP,
			.Level = 10,
		},
		{
			.Move = MOVE_GROWTH,
			.Level = 13,
		},
		{
			.Move = MOVE_LEAF_TORNADO,
			.Level = 16,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 20,
		},
		{
			.Move = MOVE_MEGA_DRAIN,
			.Level = 24,
		},
		{
			.Move = MOVE_SLAM,
			.Level = 28,
		},
		{
			.Move = MOVE_LEAF_BLADE,
			.Level = 32,
		},
		{
			.Move = MOVE_COIL,
			.Level = 36,
		},
		{
			.Move = MOVE_GIGA_DRAIN,
			.Level = 40,
		},
		{
			.Move = MOVE_WRING_OUT,
			.Level = 44,
		},
		{
			.Move = MOVE_GASTRO_ACID,
			.Level = 48,
		},
		{
			.Move = MOVE_LEAF_STORM,
			.Level = 52,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SERPERIOR] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_VINE_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_WRAP,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 4,
		},
		{
			.Move = MOVE_VINE_WHIP,
			.Level = 7,
		},
		{
			.Move = MOVE_WRAP,
			.Level = 10,
		},
		{
			.Move = MOVE_GROWTH,
			.Level = 13,
		},
		{
			.Move = MOVE_LEAF_TORNADO,
			.Level = 16,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 20,
		},
		{
			.Move = MOVE_MEGA_DRAIN,
			.Level = 24,
		},
		{
			.Move = MOVE_SLAM,
			.Level = 28,
		},
		{
			.Move = MOVE_LEAF_BLADE,
			.Level = 32,
		},
		{
			.Move = MOVE_COIL,
			.Level = 38,
		},
		{
			.Move = MOVE_GIGA_DRAIN,
			.Level = 44,
		},
		{
			.Move = MOVE_WRING_OUT,
			.Level = 50,
		},
		{
			.Move = MOVE_GASTRO_ACID,
			.Level = 56,
		},
		{
			.Move = MOVE_LEAF_STORM,
			.Level = 62,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_TEPIG] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 3,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 7,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 9,
		},
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 13,
		},
		{
			.Move = MOVE_FLAME_CHARGE,
			.Level = 15,
		},
		{
			.Move = MOVE_SMOG,
			.Level = 19,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 21,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 25,
		},
		{
			.Move = MOVE_HEAT_CRASH,
			.Level = 27,
		},
		{
			.Move = MOVE_ASSURANCE,
			.Level = 31,
		},
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 33,
		},
		{
			.Move = MOVE_HEAD_SMASH,
			.Level = 37,
		},
		{
			.Move = MOVE_ROAR,
			.Level = 39,
		},
		{
			.Move = MOVE_FLARE_BLITZ,
			.Level = 43,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PIGNITE] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 1,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 3,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 7,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 9,
		},
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 13,
		},
		{
			.Move = MOVE_FLAME_CHARGE,
			.Level = 15,
		},
		{
			.Move = MOVE_ARM_THRUST,
			.Level = 17,
		},
		{
			.Move = MOVE_SMOG,
			.Level = 20,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 23,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 28,
		},
		{
			.Move = MOVE_HEAT_CRASH,
			.Level = 31,
		},
		{
			.Move = MOVE_ASSURANCE,
			.Level = 36,
		},
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 39,
		},
		{
			.Move = MOVE_HEAD_SMASH,
			.Level = 44,
		},
		{
			.Move = MOVE_ROAR,
			.Level = 47,
		},
		{
			.Move = MOVE_FLARE_BLITZ,
			.Level = 52,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_EMBOAR] = {
		{
			.Move = MOVE_HAMMER_ARM,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 1,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 3,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 7,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 9,
		},
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 13,
		},
		{
			.Move = MOVE_FLAME_CHARGE,
			.Level = 15,
		},
		{
			.Move = MOVE_ARM_THRUST,
			.Level = 17,
		},
		{
			.Move = MOVE_SMOG,
			.Level = 20,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 23,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 28,
		},
		{
			.Move = MOVE_HEAT_CRASH,
			.Level = 31,
		},
		{
			.Move = MOVE_ASSURANCE,
			.Level = 38,
		},
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 43,
		},
		{
			.Move = MOVE_HEAD_SMASH,
			.Level = 50,
		},
		{
			.Move = MOVE_ROAR,
			.Level = 55,
		},
		{
			.Move = MOVE_FLARE_BLITZ,
			.Level = 62,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_OSHAWOTT] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 5,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 7,
		},
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 11,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 13,
		},
		{
			.Move = MOVE_RAZOR_SHELL,
			.Level = 17,
		},
		{
			.Move = MOVE_FURY_CUTTER,
			.Level = 19,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 23,
		},
		{
			.Move = MOVE_REVENGE,
			.Level = 25,
		},
		{
			.Move = MOVE_AQUA_JET,
			.Level = 29,
		},
		{
			.Move = MOVE_ENCORE,
			.Level = 31,
		},
		{
			.Move = MOVE_AQUA_TAIL,
			.Level = 35,
		},
		{
			.Move = MOVE_RETALIATE,
			.Level = 37,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 41,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 43,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_DEWOTT] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 5,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 7,
		},
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 11,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 13,
		},
		{
			.Move = MOVE_RAZOR_SHELL,
			.Level = 17,
		},
		{
			.Move = MOVE_FURY_CUTTER,
			.Level = 20,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 25,
		},
		{
			.Move = MOVE_REVENGE,
			.Level = 28,
		},
		{
			.Move = MOVE_AQUA_JET,
			.Level = 33,
		},
		{
			.Move = MOVE_ENCORE,
			.Level = 36,
		},
		{
			.Move = MOVE_AQUA_TAIL,
			.Level = 41,
		},
		{
			.Move = MOVE_RETALIATE,
			.Level = 44,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 49,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 52,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SAMUROTT] = {
		{
			.Move = MOVE_MEGAHORN,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 5,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 7,
		},
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 11,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 13,
		},
		{
			.Move = MOVE_RAZOR_SHELL,
			.Level = 17,
		},
		{
			.Move = MOVE_FURY_CUTTER,
			.Level = 20,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 25,
		},
		{
			.Move = MOVE_REVENGE,
			.Level = 28,
		},
		{
			.Move = MOVE_AQUA_JET,
			.Level = 33,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 36,
		},
		{
			.Move = MOVE_ENCORE,
			.Level = 38,
		},
		{
			.Move = MOVE_AQUA_TAIL,
			.Level = 45,
		},
		{
			.Move = MOVE_RETALIATE,
			.Level = 50,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 57,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 62,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PATRAT] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 3,
		},
		{
			.Move = MOVE_BITE,
			.Level = 6,
		},
		{
			.Move = MOVE_BIDE,
			.Level = 8,
		},
		{
			.Move = MOVE_DETECT,
			.Level = 11,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 13,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 16,
		},
		{
			.Move = MOVE_HYPNOSIS,
			.Level = 18,
		},
		{
			.Move = MOVE_SUPER_FANG,
			.Level = 21,
		},
		{
			.Move = MOVE_AFTER_YOU,
			.Level = 23,
		},
		{
			.Move = MOVE_WORK_UP,
			.Level = 26,
		},
		{
			.Move = MOVE_HYPER_FANG,
			.Level = 28,
		},
		{
			.Move = MOVE_MEAN_LOOK,
			.Level = 31,
		},
		{
			.Move = MOVE_BATON_PASS,
			.Level = 33,
		},
		{
			.Move = MOVE_SLAM,
			.Level = 36,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_WATCHOG] = {
		{
			.Move = MOVE_ROTOTILLER,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_LOW_KICK,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 3,
		},
		{
			.Move = MOVE_BITE,
			.Level = 6,
		},
		{
			.Move = MOVE_BIDE,
			.Level = 8,
		},
		{
			.Move = MOVE_DETECT,
			.Level = 11,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 13,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 16,
		},
		{
			.Move = MOVE_HYPNOSIS,
			.Level = 18,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 20,
		},
		{
			.Move = MOVE_SUPER_FANG,
			.Level = 22,
		},
		{
			.Move = MOVE_AFTER_YOU,
			.Level = 25,
		},
		{
			.Move = MOVE_PSYCH_UP,
			.Level = 29,
		},
		{
			.Move = MOVE_HYPER_FANG,
			.Level = 32,
		},
		{
			.Move = MOVE_MEAN_LOOK,
			.Level = 36,
		},
		{
			.Move = MOVE_BATON_PASS,
			.Level = 39,
		},
		{
			.Move = MOVE_SLAM,
			.Level = 43,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_LILLIPUP] = {
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 5,
		},
		{
			.Move = MOVE_BITE,
			.Level = 8,
		},
		{
			.Move = MOVE_BABYDOLL_EYES,
			.Level = 10,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 12,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 15,
		},
		{
			.Move = MOVE_WORK_UP,
			.Level = 19,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 22,
		},
		{
			.Move = MOVE_ROAR,
			.Level = 26,
		},
		{
			.Move = MOVE_RETALIATE,
			.Level = 29,
		},
		{
			.Move = MOVE_REVERSAL,
			.Level = 33,
		},
		{
			.Move = MOVE_LAST_RESORT,
			.Level = 36,
		},
		{
			.Move = MOVE_GIGA_IMPACT,
			.Level = 40,
		},
		{
			.Move = MOVE_PLAY_ROUGH,
			.Level = 45,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_HERDIER] = {
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 5,
		},
		{
			.Move = MOVE_BITE,
			.Level = 8,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 12,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 15,
		},
		{
			.Move = MOVE_WORK_UP,
			.Level = 20,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 24,
		},
		{
			.Move = MOVE_ROAR,
			.Level = 29,
		},
		{
			.Move = MOVE_RETALIATE,
			.Level = 33,
		},
		{
			.Move = MOVE_REVERSAL,
			.Level = 38,
		},
		{
			.Move = MOVE_LAST_RESORT,
			.Level = 42,
		},
		{
			.Move = MOVE_GIGA_IMPACT,
			.Level = 47,
		},
		{
			.Move = MOVE_PLAY_ROUGH,
			.Level = 52,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_STOUTLAND] = {
		{
			.Move = MOVE_ICE_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_FIRE_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 5,
		},
		{
			.Move = MOVE_BITE,
			.Level = 8,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 12,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 15,
		},
		{
			.Move = MOVE_WORK_UP,
			.Level = 20,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 24,
		},
		{
			.Move = MOVE_ROAR,
			.Level = 29,
		},
		{
			.Move = MOVE_RETALIATE,
			.Level = 36,
		},
		{
			.Move = MOVE_REVERSAL,
			.Level = 42,
		},
		{
			.Move = MOVE_LAST_RESORT,
			.Level = 51,
		},
		{
			.Move = MOVE_GIGA_IMPACT,
			.Level = 59,
		},
		{
			.Move = MOVE_PLAY_ROUGH,
			.Level = 63,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PURRLOIN] = {
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 3,
		},
		{
			.Move = MOVE_ASSIST,
			.Level = 6,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 10,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 12,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 15,
		},
		{
			.Move = MOVE_TORMENT,
			.Level = 19,
		},
		{
			.Move = MOVE_FAKE_OUT,
			.Level = 21,
		},
		{
			.Move = MOVE_HONE_CLAWS,
			.Level = 24,
		},
		{
			.Move = MOVE_ASSURANCE,
			.Level = 28,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 30,
		},
		{
			.Move = MOVE_CAPTIVATE,
			.Level = 33,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 37,
		},
		{
			.Move = MOVE_SNATCH,
			.Level = 39,
		},
		{
			.Move = MOVE_NASTY_PLOT,
			.Level = 42,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 46,
		},
		{
			.Move = MOVE_PLAY_ROUGH,
			.Level = 49,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_LIEPARD] = {
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_ASSIST,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 3,
		},
		{
			.Move = MOVE_ASSIST,
			.Level = 6,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 10,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 12,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 15,
		},
		{
			.Move = MOVE_TORMENT,
			.Level = 19,
		},
		{
			.Move = MOVE_FAKE_OUT,
			.Level = 22,
		},
		{
			.Move = MOVE_HONE_CLAWS,
			.Level = 26,
		},
		{
			.Move = MOVE_ASSURANCE,
			.Level = 31,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 34,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 38,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 43,
		},
		{
			.Move = MOVE_SNATCH,
			.Level = 47,
		},
		{
			.Move = MOVE_NASTY_PLOT,
			.Level = 50,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 55,
		},
		{
			.Move = MOVE_PLAY_ROUGH,
			.Level = 58,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PANSAGE] = {
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_PLAY_NICE,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 4,
		},
		{
			.Move = MOVE_LICK,
			.Level = 7,
		},
		{
			.Move = MOVE_VINE_WHIP,
			.Level = 10,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 13,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 16,
		},
		{
			.Move = MOVE_BITE,
			.Level = 19,
		},
		{
			.Move = MOVE_SEED_BOMB,
			.Level = 22,
		},
		{
			.Move = MOVE_TORMENT,
			.Level = 25,
		},
		{
			.Move = MOVE_FLING,
			.Level = 28,
		},
		{
			.Move = MOVE_ACROBATICS,
			.Level = 31,
		},
		{
			.Move = MOVE_GRASS_KNOT,
			.Level = 34,
		},
		{
			.Move = MOVE_RECYCLE,
			.Level = 37,
		},
		{
			.Move = MOVE_NATURAL_GIFT,
			.Level = 40,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 43,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SIMISAGE] = {
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_LICK,
			.Level = 1,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 1,
		},
		{
			.Move = MOVE_SEED_BOMB,
			.Level = 1,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PANSEAR] = {
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_PLAY_NICE,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 4,
		},
		{
			.Move = MOVE_LICK,
			.Level = 7,
		},
		{
			.Move = MOVE_INCINERATE,
			.Level = 10,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 13,
		},
		{
			.Move = MOVE_YAWN,
			.Level = 16,
		},
		{
			.Move = MOVE_BITE,
			.Level = 19,
		},
		{
			.Move = MOVE_FLAME_BURST,
			.Level = 22,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 25,
		},
		{
			.Move = MOVE_FLING,
			.Level = 28,
		},
		{
			.Move = MOVE_ACROBATICS,
			.Level = 31,
		},
		{
			.Move = MOVE_FIRE_BLAST,
			.Level = 34,
		},
		{
			.Move = MOVE_RECYCLE,
			.Level = 37,
		},
		{
			.Move = MOVE_NATURAL_GIFT,
			.Level = 40,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 43,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SIMISEAR] = {
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_LICK,
			.Level = 1,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 1,
		},
		{
			.Move = MOVE_FLAME_BURST,
			.Level = 1,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PANPOUR] = {
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_PLAY_NICE,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 4,
		},
		{
			.Move = MOVE_LICK,
			.Level = 7,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 10,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 13,
		},
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 16,
		},
		{
			.Move = MOVE_BITE,
			.Level = 19,
		},
		{
			.Move = MOVE_SCALD,
			.Level = 22,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 25,
		},
		{
			.Move = MOVE_FLING,
			.Level = 28,
		},
		{
			.Move = MOVE_ACROBATICS,
			.Level = 31,
		},
		{
			.Move = MOVE_BRINE,
			.Level = 34,
		},
		{
			.Move = MOVE_RECYCLE,
			.Level = 37,
		},
		{
			.Move = MOVE_NATURAL_GIFT,
			.Level = 40,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 43,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SIMIPOUR] = {
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_LICK,
			.Level = 1,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 1,
		},
		{
			.Move = MOVE_SCALD,
			.Level = 1,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MUNNA] = {
		{
			.Move = MOVE_PSYWAVE,
			.Level = 1,
		},
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 1,
		},
		{
			.Move = MOVE_LUCKY_CHANT,
			.Level = 5,
		},
		{
			.Move = MOVE_YAWN,
			.Level = 7,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 11,
		},
		{
			.Move = MOVE_IMPRISON,
			.Level = 13,
		},
		{
			.Move = MOVE_MOONLIGHT,
			.Level = 17,
		},
		{
			.Move = MOVE_HYPNOSIS,
			.Level = 19,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 23,
		},
		{
			.Move = MOVE_SYNCHRONOISE,
			.Level = 25,
		},
		{
			.Move = MOVE_NIGHTMARE,
			.Level = 29,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 31,
		},
		{
			.Move = MOVE_CALM_MIND,
			.Level = 35,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 37,
		},
		{
			.Move = MOVE_DREAM_EATER,
			.Level = 41,
		},
		{
			.Move = MOVE_TELEKINESIS,
			.Level = 43,
		},
		{
			.Move = MOVE_STORED_POWER,
			.Level = 47,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MUSHARNA] = {
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 1,
		},
		{
			.Move = MOVE_LUCKY_CHANT,
			.Level = 1,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 1,
		},
		{
			.Move = MOVE_HYPNOSIS,
			.Level = 1,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PIDOVE] = {
		{
			.Move = MOVE_GUST,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 4,
		},
		{
			.Move = MOVE_LEER,
			.Level = 8,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 11,
		},
		{
			.Move = MOVE_AIR_CUTTER,
			.Level = 15,
		},
		{
			.Move = MOVE_ROOST,
			.Level = 18,
		},
		{
			.Move = MOVE_DETECT,
			.Level = 22,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 25,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 29,
		},
		{
			.Move = MOVE_RAZOR_WIND,
			.Level = 32,
		},
		{
			.Move = MOVE_FEATHERDANCE,
			.Level = 36,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 39,
		},
		{
			.Move = MOVE_FACADE,
			.Level = 43,
		},
		{
			.Move = MOVE_TAILWIND,
			.Level = 46,
		},
		{
			.Move = MOVE_SKY_ATTACK,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_TRANQUILL] = {
		{
			.Move = MOVE_GUST,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 4,
		},
		{
			.Move = MOVE_LEER,
			.Level = 8,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 11,
		},
		{
			.Move = MOVE_AIR_CUTTER,
			.Level = 15,
		},
		{
			.Move = MOVE_ROOST,
			.Level = 18,
		},
		{
			.Move = MOVE_DETECT,
			.Level = 23,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 27,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 32,
		},
		{
			.Move = MOVE_RAZOR_WIND,
			.Level = 36,
		},
		{
			.Move = MOVE_FEATHERDANCE,
			.Level = 41,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 45,
		},
		{
			.Move = MOVE_FACADE,
			.Level = 50,
		},
		{
			.Move = MOVE_TAILWIND,
			.Level = 54,
		},
		{
			.Move = MOVE_SKY_ATTACK,
			.Level = 59,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_UNFEZANT] = {
		{
			.Move = MOVE_GUST,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 4,
		},
		{
			.Move = MOVE_LEER,
			.Level = 8,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 11,
		},
		{
			.Move = MOVE_AIR_CUTTER,
			.Level = 15,
		},
		{
			.Move = MOVE_ROOST,
			.Level = 18,
		},
		{
			.Move = MOVE_DETECT,
			.Level = 23,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 27,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 33,
		},
		{
			.Move = MOVE_RAZOR_WIND,
			.Level = 38,
		},
		{
			.Move = MOVE_FEATHERDANCE,
			.Level = 44,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 49,
		},
		{
			.Move = MOVE_FACADE,
			.Level = 55,
		},
		{
			.Move = MOVE_TAILWIND,
			.Level = 60,
		},
		{
			.Move = MOVE_SKY_ATTACK,
			.Level = 66,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BLITZLE] = {
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 4,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 8,
		},
		{
			.Move = MOVE_SHOCK_WAVE,
			.Level = 11,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 15,
		},
		{
			.Move = MOVE_FLAME_CHARGE,
			.Level = 18,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 22,
		},
		{
			.Move = MOVE_SPARK,
			.Level = 25,
		},
		{
			.Move = MOVE_STOMP,
			.Level = 29,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 32,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 36,
		},
		{
			.Move = MOVE_WILD_CHARGE,
			.Level = 39,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 43,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ZEBSTRIKA] = {
		{
			.Move = MOVE_ION_DELUGE,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 4,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 8,
		},
		{
			.Move = MOVE_SHOCK_WAVE,
			.Level = 11,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 15,
		},
		{
			.Move = MOVE_FLAME_CHARGE,
			.Level = 18,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 22,
		},
		{
			.Move = MOVE_SPARK,
			.Level = 25,
		},
		{
			.Move = MOVE_STOMP,
			.Level = 31,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 36,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 42,
		},
		{
			.Move = MOVE_WILD_CHARGE,
			.Level = 47,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 53,
		},
		{
			.Move = MOVE_ION_DELUGE,
			.Level = 58,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ROGGENROLA] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 4,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 7,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 10,
		},
		{
			.Move = MOVE_ROCK_BLAST,
			.Level = 14,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 17,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 20,
		},
		{
			.Move = MOVE_SMACK_DOWN,
			.Level = 23,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 27,
		},
		{
			.Move = MOVE_STEALTH_ROCK,
			.Level = 30,
		},
		{
			.Move = MOVE_SANDSTORM,
			.Level = 33,
		},
		{
			.Move = MOVE_STONE_EDGE,
			.Level = 36,
		},
		{
			.Move = MOVE_EXPLOSION,
			.Level = 40,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BOLDORE] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 4,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 7,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 10,
		},
		{
			.Move = MOVE_ROCK_BLAST,
			.Level = 14,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 17,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 20,
		},
		{
			.Move = MOVE_SMACK_DOWN,
			.Level = 23,
		},
		{
			.Move = MOVE_POWER_GEM,
			.Level = 25,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 30,
		},
		{
			.Move = MOVE_STEALTH_ROCK,
			.Level = 36,
		},
		{
			.Move = MOVE_SANDSTORM,
			.Level = 42,
		},
		{
			.Move = MOVE_STONE_EDGE,
			.Level = 48,
		},
		{
			.Move = MOVE_EXPLOSION,
			.Level = 55,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GIGALITH] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 4,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 7,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 10,
		},
		{
			.Move = MOVE_ROCK_BLAST,
			.Level = 14,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 17,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 20,
		},
		{
			.Move = MOVE_SMACK_DOWN,
			.Level = 23,
		},
		{
			.Move = MOVE_POWER_GEM,
			.Level = 25,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 30,
		},
		{
			.Move = MOVE_STEALTH_ROCK,
			.Level = 36,
		},
		{
			.Move = MOVE_SANDSTORM,
			.Level = 42,
		},
		{
			.Move = MOVE_STONE_EDGE,
			.Level = 48,
		},
		{
			.Move = MOVE_EXPLOSION,
			.Level = 55,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_WOOBAT] = {
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 4,
		},
		{
			.Move = MOVE_GUST,
			.Level = 8,
		},
		{
			.Move = MOVE_ASSURANCE,
			.Level = 12,
		},
		{
			.Move = MOVE_HEART_STAMP,
			.Level = 15,
		},
		{
			.Move = MOVE_IMPRISON,
			.Level = 19,
		},
		{
			.Move = MOVE_AIR_CUTTER,
			.Level = 21,
		},
		{
			.Move = MOVE_ATTRACT,
			.Level = 25,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 29,
		},
		{
			.Move = MOVE_CALM_MIND,
			.Level = 29,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 32,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 36,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 41,
		},
		{
			.Move = MOVE_ENDEAVOR,
			.Level = 47,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SWOOBAT] = {
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 1,
		},
		{
			.Move = MOVE_GUST,
			.Level = 1,
		},
		{
			.Move = MOVE_ASSURANCE,
			.Level = 1,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 4,
		},
		{
			.Move = MOVE_GUST,
			.Level = 8,
		},
		{
			.Move = MOVE_ASSURANCE,
			.Level = 12,
		},
		{
			.Move = MOVE_HEART_STAMP,
			.Level = 15,
		},
		{
			.Move = MOVE_IMPRISON,
			.Level = 19,
		},
		{
			.Move = MOVE_AIR_CUTTER,
			.Level = 21,
		},
		{
			.Move = MOVE_ATTRACT,
			.Level = 25,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 29,
		},
		{
			.Move = MOVE_CALM_MIND,
			.Level = 29,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 32,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 36,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 41,
		},
		{
			.Move = MOVE_ENDEAVOR,
			.Level = 47,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_DRILBUR] = {
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_MUD_SPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_RAPID_SPIN,
			.Level = 5,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 8,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 12,
		},
		{
			.Move = MOVE_METAL_CLAW,
			.Level = 15,
		},
		{
			.Move = MOVE_DIG,
			.Level = 19,
		},
		{
			.Move = MOVE_HONE_CLAWS,
			.Level = 22,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 26,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 29,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 33,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 36,
		},
		{
			.Move = MOVE_SANDSTORM,
			.Level = 40,
		},
		{
			.Move = MOVE_DRILL_RUN,
			.Level = 43,
		},
		{
			.Move = MOVE_FISSURE,
			.Level = 47,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_EXCADRILL] = {
		{
			.Move = MOVE_ROTOTILLER,
			.Level = 1,
		},
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_MUD_SPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_RAPID_SPIN,
			.Level = 1,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 1,
		},
		{
			.Move = MOVE_RAPID_SPIN,
			.Level = 5,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 8,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 12,
		},
		{
			.Move = MOVE_METAL_CLAW,
			.Level = 15,
		},
		{
			.Move = MOVE_DIG,
			.Level = 19,
		},
		{
			.Move = MOVE_HONE_CLAWS,
			.Level = 22,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 26,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 29,
		},
		{
			.Move = MOVE_HORN_DRILL,
			.Level = 31,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 36,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 42,
		},
		{
			.Move = MOVE_SANDSTORM,
			.Level = 49,
		},
		{
			.Move = MOVE_DRILL_RUN,
			.Level = 55,
		},
		{
			.Move = MOVE_FISSURE,
			.Level = 62,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_AUDINO] = {
		{
			.Move = MOVE_LAST_RESORT,
			.Level = 1,
		},
		{
			.Move = MOVE_MISTY_TERRAIN,
			.Level = 1,
		},
		{
			.Move = MOVE_PLAY_NICE,
			.Level = 1,
		},
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 1,
		},
		{
			.Move = MOVE_BABYDOLL_EYES,
			.Level = 5,
		},
		{
			.Move = MOVE_REFRESH,
			.Level = 9,
		},
		{
			.Move = MOVE_DISARMING_VOICE,
			.Level = 13,
		},
		{
			.Move = MOVE_DOUBLESLAP,
			.Level = 17,
		},
		{
			.Move = MOVE_ATTRACT,
			.Level = 21,
		},
		{
			.Move = MOVE_SECRET_POWER,
			.Level = 25,
		},
		{
			.Move = MOVE_ENTRAINMENT,
			.Level = 29,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 33,
		},
		{
			.Move = MOVE_HEAL_PULSE,
			.Level = 37,
		},
		{
			.Move = MOVE_AFTER_YOU,
			.Level = 41,
		},
		{
			.Move = MOVE_SIMPLE_BEAM,
			.Level = 45,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 49,
		},
		{
			.Move = MOVE_LAST_RESORT,
			.Level = 53,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_TIMBURR] = {
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 4,
		},
		{
			.Move = MOVE_BIDE,
			.Level = 8,
		},
		{
			.Move = MOVE_LOW_KICK,
			.Level = 12,
		},
		{
			.Move = MOVE_ROCK_THROW,
			.Level = 16,
		},
		{
			.Move = MOVE_WAKEUP_SLAP,
			.Level = 20,
		},
		{
			.Move = MOVE_CHIP_AWAY,
			.Level = 24,
		},
		{
			.Move = MOVE_BULK_UP,
			.Level = 28,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 31,
		},
		{
			.Move = MOVE_DYNAMICPUNCH,
			.Level = 34,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 37,
		},
		{
			.Move = MOVE_HAMMER_ARM,
			.Level = 40,
		},
		{
			.Move = MOVE_STONE_EDGE,
			.Level = 43,
		},
		{
			.Move = MOVE_FOCUS_PUNCH,
			.Level = 46,
		},
		{
			.Move = MOVE_SUPERPOWER,
			.Level = 49,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GURDURR] = {
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 1,
		},
		{
			.Move = MOVE_BIDE,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 4,
		},
		{
			.Move = MOVE_BIDE,
			.Level = 8,
		},
		{
			.Move = MOVE_LOW_KICK,
			.Level = 12,
		},
		{
			.Move = MOVE_ROCK_THROW,
			.Level = 16,
		},
		{
			.Move = MOVE_WAKEUP_SLAP,
			.Level = 20,
		},
		{
			.Move = MOVE_CHIP_AWAY,
			.Level = 24,
		},
		{
			.Move = MOVE_BULK_UP,
			.Level = 29,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 33,
		},
		{
			.Move = MOVE_DYNAMICPUNCH,
			.Level = 37,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 41,
		},
		{
			.Move = MOVE_HAMMER_ARM,
			.Level = 45,
		},
		{
			.Move = MOVE_STONE_EDGE,
			.Level = 49,
		},
		{
			.Move = MOVE_FOCUS_PUNCH,
			.Level = 53,
		},
		{
			.Move = MOVE_SUPERPOWER,
			.Level = 57,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CONKELDURR] = {
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 1,
		},
		{
			.Move = MOVE_BIDE,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 4,
		},
		{
			.Move = MOVE_BIDE,
			.Level = 8,
		},
		{
			.Move = MOVE_LOW_KICK,
			.Level = 12,
		},
		{
			.Move = MOVE_ROCK_THROW,
			.Level = 16,
		},
		{
			.Move = MOVE_WAKEUP_SLAP,
			.Level = 20,
		},
		{
			.Move = MOVE_CHIP_AWAY,
			.Level = 24,
		},
		{
			.Move = MOVE_BULK_UP,
			.Level = 29,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 33,
		},
		{
			.Move = MOVE_DYNAMICPUNCH,
			.Level = 37,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 41,
		},
		{
			.Move = MOVE_HAMMER_ARM,
			.Level = 45,
		},
		{
			.Move = MOVE_STONE_EDGE,
			.Level = 49,
		},
		{
			.Move = MOVE_FOCUS_PUNCH,
			.Level = 53,
		},
		{
			.Move = MOVE_SUPERPOWER,
			.Level = 57,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_TYMPOLE] = {
		{
			.Move = MOVE_BUBBLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 5,
		},
		{
			.Move = MOVE_ROUND,
			.Level = 9,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 12,
		},
		{
			.Move = MOVE_MUD_SHOT,
			.Level = 16,
		},
		{
			.Move = MOVE_AQUA_RING,
			.Level = 20,
		},
		{
			.Move = MOVE_UPROAR,
			.Level = 23,
		},
		{
			.Move = MOVE_MUDDY_WATER,
			.Level = 27,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 31,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 34,
		},
		{
			.Move = MOVE_ECHOED_VOICE,
			.Level = 38,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 42,
		},
		{
			.Move = MOVE_HYPER_VOICE,
			.Level = 45,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PALPITOAD] = {
		{
			.Move = MOVE_BUBBLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 1,
		},
		{
			.Move = MOVE_ROUND,
			.Level = 1,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 5,
		},
		{
			.Move = MOVE_ROUND,
			.Level = 9,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 12,
		},
		{
			.Move = MOVE_MUD_SHOT,
			.Level = 16,
		},
		{
			.Move = MOVE_AQUA_RING,
			.Level = 20,
		},
		{
			.Move = MOVE_UPROAR,
			.Level = 23,
		},
		{
			.Move = MOVE_MUDDY_WATER,
			.Level = 28,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 33,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 37,
		},
		{
			.Move = MOVE_ECHOED_VOICE,
			.Level = 42,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 47,
		},
		{
			.Move = MOVE_HYPER_VOICE,
			.Level = 51,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SEISMITOAD] = {
		{
			.Move = MOVE_BUBBLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 1,
		},
		{
			.Move = MOVE_ROUND,
			.Level = 1,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 5,
		},
		{
			.Move = MOVE_ROUND,
			.Level = 9,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 12,
		},
		{
			.Move = MOVE_MUD_SHOT,
			.Level = 16,
		},
		{
			.Move = MOVE_AQUA_RING,
			.Level = 20,
		},
		{
			.Move = MOVE_UPROAR,
			.Level = 23,
		},
		{
			.Move = MOVE_MUDDY_WATER,
			.Level = 28,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 33,
		},
		{
			.Move = MOVE_ACID,
			.Level = 36,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 39,
		},
		{
			.Move = MOVE_DRAIN_PUNCH,
			.Level = 44,
		},
		{
			.Move = MOVE_ECHOED_VOICE,
			.Level = 49,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 53,
		},
		{
			.Move = MOVE_HYPER_VOICE,
			.Level = 59,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_THROH] = {
		{
			.Move = MOVE_BIND,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_BIDE,
			.Level = 5,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 9,
		},
		{
			.Move = MOVE_SEISMIC_TOSS,
			.Level = 13,
		},
		{
			.Move = MOVE_VITAL_THROW,
			.Level = 17,
		},
		{
			.Move = MOVE_REVENGE,
			.Level = 21,
		},
		{
			.Move = MOVE_STORM_THROW,
			.Level = 25,
		},
		{
			.Move = MOVE_BODY_SLAM,
			.Level = 29,
		},
		{
			.Move = MOVE_BULK_UP,
			.Level = 33,
		},
		{
			.Move = MOVE_CIRCLE_THROW,
			.Level = 37,
		},
		{
			.Move = MOVE_ENDURE,
			.Level = 41,
		},
		{
			.Move = MOVE_WIDE_GUARD,
			.Level = 45,
		},
		{
			.Move = MOVE_SUPERPOWER,
			.Level = 48,
		},
		{
			.Move = MOVE_REVERSAL,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SAWK] = {
		{
			.Move = MOVE_ROCK_SMASH,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_BIDE,
			.Level = 5,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 9,
		},
		{
			.Move = MOVE_DOUBLE_KICK,
			.Level = 13,
		},
		{
			.Move = MOVE_LOW_SWEEP,
			.Level = 17,
		},
		{
			.Move = MOVE_COUNTER,
			.Level = 21,
		},
		{
			.Move = MOVE_KARATE_CHOP,
			.Level = 25,
		},
		{
			.Move = MOVE_BRICK_BREAK,
			.Level = 29,
		},
		{
			.Move = MOVE_BULK_UP,
			.Level = 33,
		},
		{
			.Move = MOVE_RETALIATE,
			.Level = 37,
		},
		{
			.Move = MOVE_ENDURE,
			.Level = 41,
		},
		{
			.Move = MOVE_QUICK_GUARD,
			.Level = 45,
		},
		{
			.Move = MOVE_CLOSE_COMBAT,
			.Level = 48,
		},
		{
			.Move = MOVE_REVERSAL,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SEWADDLE] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_STRING_SHOT,
			.Level = 1,
		},
		{
			.Move = MOVE_BUG_BITE,
			.Level = 8,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 15,
		},
		{
			.Move = MOVE_STRUGGLE_BUG,
			.Level = 22,
		},
		{
			.Move = MOVE_ENDURE,
			.Level = 29,
		},
		{
			.Move = MOVE_STICKY_WEB,
			.Level = 31,
		},
		{
			.Move = MOVE_BUG_BUZZ,
			.Level = 36,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 43,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SWADLOON] = {
		{
			.Move = MOVE_GRASSWHISTLE,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_STRING_SHOT,
			.Level = 1,
		},
		{
			.Move = MOVE_BUG_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 1,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 20,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_LEAVANNY] = {
		{
			.Move = MOVE_FALSE_SWIPE,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_STRING_SHOT,
			.Level = 1,
		},
		{
			.Move = MOVE_BUG_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 1,
		},
		{
			.Move = MOVE_BUG_BITE,
			.Level = 8,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 15,
		},
		{
			.Move = MOVE_STRUGGLE_BUG,
			.Level = 22,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 29,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 32,
		},
		{
			.Move = MOVE_FELL_STINGER,
			.Level = 34,
		},
		{
			.Move = MOVE_LEAF_BLADE,
			.Level = 36,
		},
		{
			.Move = MOVE_XSCISSOR,
			.Level = 39,
		},
		{
			.Move = MOVE_ENTRAINMENT,
			.Level = 43,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 46,
		},
		{
			.Move = MOVE_LEAF_STORM,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_VENIPEDE] = {
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 1,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 1,
		},
		{
			.Move = MOVE_POISON_STING,
			.Level = 5,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 8,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 12,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 15,
		},
		{
			.Move = MOVE_POISON_TAIL,
			.Level = 19,
		},
		{
			.Move = MOVE_BUG_BITE,
			.Level = 22,
		},
		{
			.Move = MOVE_VENOSHOCK,
			.Level = 26,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 29,
		},
		{
			.Move = MOVE_STEAMROLLER,
			.Level = 33,
		},
		{
			.Move = MOVE_TOXIC,
			.Level = 36,
		},
		{
			.Move = MOVE_VENOSHOCK,
			.Level = 38,
		},
		{
			.Move = MOVE_ROCK_CLIMB,
			.Level = 40,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 43,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_WHIRLIPEDE] = {
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 1,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 1,
		},
		{
			.Move = MOVE_POISON_STING,
			.Level = 1,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 1,
		},
		{
			.Move = MOVE_POISON_STING,
			.Level = 5,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 8,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 12,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 15,
		},
		{
			.Move = MOVE_POISON_TAIL,
			.Level = 19,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 22,
		},
		{
			.Move = MOVE_BUG_BITE,
			.Level = 23,
		},
		{
			.Move = MOVE_VENOSHOCK,
			.Level = 28,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 32,
		},
		{
			.Move = MOVE_STEAMROLLER,
			.Level = 37,
		},
		{
			.Move = MOVE_TOXIC,
			.Level = 41,
		},
		{
			.Move = MOVE_VENOM_DRENCH,
			.Level = 43,
		},
		{
			.Move = MOVE_ROCK_CLIMB,
			.Level = 46,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SCOLIPEDE] = {
		{
			.Move = MOVE_MEGAHORN,
			.Level = 1,
		},
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 1,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 1,
		},
		{
			.Move = MOVE_POISON_STING,
			.Level = 1,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 1,
		},
		{
			.Move = MOVE_POISON_STING,
			.Level = 5,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 8,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 12,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 15,
		},
		{
			.Move = MOVE_POISON_TAIL,
			.Level = 19,
		},
		{
			.Move = MOVE_BUG_BITE,
			.Level = 23,
		},
		{
			.Move = MOVE_VENOSHOCK,
			.Level = 28,
		},
		{
			.Move = MOVE_BATON_PASS,
			.Level = 30,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 33,
		},
		{
			.Move = MOVE_STEAMROLLER,
			.Level = 39,
		},
		{
			.Move = MOVE_TOXIC,
			.Level = 44,
		},
		{
			.Move = MOVE_VENOM_DRENCH,
			.Level = 47,
		},
		{
			.Move = MOVE_ROCK_CLIMB,
			.Level = 50,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 55,
		},
		{
			.Move = MOVE_MEGAHORN,
			.Level = 65,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_COTTONEE] = {
		{
			.Move = MOVE_ABSORB,
			.Level = 1,
		},
		{
			.Move = MOVE_FAIRY_WIND,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWTH,
			.Level = 4,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 8,
		},
		{
			.Move = MOVE_STUN_SPORE,
			.Level = 10,
		},
		{
			.Move = MOVE_MEGA_DRAIN,
			.Level = 13,
		},
		{
			.Move = MOVE_COTTON_SPORE,
			.Level = 17,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 19,
		},
		{
			.Move = MOVE_POISONPOWDER,
			.Level = 22,
		},
		{
			.Move = MOVE_GIGA_DRAIN,
			.Level = 26,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 28,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 31,
		},
		{
			.Move = MOVE_ENERGY_BALL,
			.Level = 35,
		},
		{
			.Move = MOVE_COTTON_GUARD,
			.Level = 37,
		},
		{
			.Move = MOVE_SUNNY_DAY,
			.Level = 40,
		},
		{
			.Move = MOVE_ENDEAVOR,
			.Level = 44,
		},
		{
			.Move = MOVE_SOLARBEAM,
			.Level = 46,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_WHIMSICOTT] = {
		{
			.Move = MOVE_GROWTH,
			.Level = 1,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 1,
		},
		{
			.Move = MOVE_MEGA_DRAIN,
			.Level = 1,
		},
		{
			.Move = MOVE_COTTON_SPORE,
			.Level = 1,
		},
		{
			.Move = MOVE_GUST,
			.Level = 10,
		},
		{
			.Move = MOVE_TAILWIND,
			.Level = 28,
		},
		{
			.Move = MOVE_HURRICANE,
			.Level = 46,
		},
		{
			.Move = MOVE_MOONBLAST,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PETILIL] = {
		{
			.Move = MOVE_ABSORB,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWTH,
			.Level = 4,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 8,
		},
		{
			.Move = MOVE_SLEEP_POWDER,
			.Level = 10,
		},
		{
			.Move = MOVE_MEGA_DRAIN,
			.Level = 13,
		},
		{
			.Move = MOVE_SYNTHESIS,
			.Level = 17,
		},
		{
			.Move = MOVE_MAGICAL_LEAF,
			.Level = 19,
		},
		{
			.Move = MOVE_STUN_SPORE,
			.Level = 22,
		},
		{
			.Move = MOVE_GIGA_DRAIN,
			.Level = 26,
		},
		{
			.Move = MOVE_AROMATHERAPY,
			.Level = 28,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 31,
		},
		{
			.Move = MOVE_ENERGY_BALL,
			.Level = 35,
		},
		{
			.Move = MOVE_ENTRAINMENT,
			.Level = 37,
		},
		{
			.Move = MOVE_SUNNY_DAY,
			.Level = 40,
		},
		{
			.Move = MOVE_AFTER_YOU,
			.Level = 44,
		},
		{
			.Move = MOVE_LEAF_STORM,
			.Level = 46,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_LILLIGANT] = {
		{
			.Move = MOVE_GROWTH,
			.Level = 1,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 1,
		},
		{
			.Move = MOVE_MEGA_DRAIN,
			.Level = 1,
		},
		{
			.Move = MOVE_SYNTHESIS,
			.Level = 1,
		},
		{
			.Move = MOVE_TEETER_DANCE,
			.Level = 10,
		},
		{
			.Move = MOVE_QUIVER_DANCE,
			.Level = 28,
		},
		{
			.Move = MOVE_PETAL_DANCE,
			.Level = 46,
		},
		{
			.Move = MOVE_PETAL_BLIZZARD,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BASCULIN] = {
		{
			.Move = MOVE_THRASH,
			.Level = 1,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_UPROAR,
			.Level = 4,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 7,
		},
		{
			.Move = MOVE_BITE,
			.Level = 10,
		},
		{
			.Move = MOVE_AQUA_JET,
			.Level = 13,
		},
		{
			.Move = MOVE_CHIP_AWAY,
			.Level = 16,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 20,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 24,
		},
		{
			.Move = MOVE_AQUA_TAIL,
			.Level = 28,
		},
		{
			.Move = MOVE_SOAK,
			.Level = 32,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 36,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 41,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 46,
		},
		{
			.Move = MOVE_FINAL_GAMBIT,
			.Level = 50,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 56,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SANDILE] = {
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_RAGE,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 4,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 7,
		},
		{
			.Move = MOVE_TORMENT,
			.Level = 10,
		},
		{
			.Move = MOVE_SAND_TOMB,
			.Level = 13,
		},
		{
			.Move = MOVE_ASSURANCE,
			.Level = 16,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 19,
		},
		{
			.Move = MOVE_EMBARGO,
			.Level = 22,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 25,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 28,
		},
		{
			.Move = MOVE_DIG,
			.Level = 31,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 34,
		},
		{
			.Move = MOVE_FOUL_PLAY,
			.Level = 37,
		},
		{
			.Move = MOVE_SANDSTORM,
			.Level = 40,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 43,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 46,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_KROKOROK] = {
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_RAGE,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 4,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 7,
		},
		{
			.Move = MOVE_TORMENT,
			.Level = 10,
		},
		{
			.Move = MOVE_SAND_TOMB,
			.Level = 13,
		},
		{
			.Move = MOVE_ASSURANCE,
			.Level = 16,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 19,
		},
		{
			.Move = MOVE_EMBARGO,
			.Level = 22,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 25,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 28,
		},
		{
			.Move = MOVE_DIG,
			.Level = 32,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 36,
		},
		{
			.Move = MOVE_FOUL_PLAY,
			.Level = 40,
		},
		{
			.Move = MOVE_SANDSTORM,
			.Level = 44,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 48,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 52,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_KROOKODILE] = {
		{
			.Move = MOVE_OUTRAGE,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_RAGE,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 4,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 7,
		},
		{
			.Move = MOVE_TORMENT,
			.Level = 10,
		},
		{
			.Move = MOVE_SAND_TOMB,
			.Level = 13,
		},
		{
			.Move = MOVE_ASSURANCE,
			.Level = 16,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 19,
		},
		{
			.Move = MOVE_EMBARGO,
			.Level = 22,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 25,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 28,
		},
		{
			.Move = MOVE_DIG,
			.Level = 32,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 36,
		},
		{
			.Move = MOVE_FOUL_PLAY,
			.Level = 42,
		},
		{
			.Move = MOVE_SANDSTORM,
			.Level = 48,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 54,
		},
		{
			.Move = MOVE_OUTRAGE,
			.Level = 60,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_DARUMAKA] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 3,
		},
		{
			.Move = MOVE_INCINERATE,
			.Level = 6,
		},
		{
			.Move = MOVE_RAGE,
			.Level = 9,
		},
		{
			.Move = MOVE_FIRE_FANG,
			.Level = 11,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 14,
		},
		{
			.Move = MOVE_UPROAR,
			.Level = 17,
		},
		{
			.Move = MOVE_FACADE,
			.Level = 19,
		},
		{
			.Move = MOVE_FIRE_PUNCH,
			.Level = 22,
		},
		{
			.Move = MOVE_WORK_UP,
			.Level = 25,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 27,
		},
		{
			.Move = MOVE_BELLY_DRUM,
			.Level = 30,
		},
		{
			.Move = MOVE_FLARE_BLITZ,
			.Level = 33,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 35,
		},
		{
			.Move = MOVE_SUPERPOWER,
			.Level = 39,
		},
		{
			.Move = MOVE_OVERHEAT,
			.Level = 42,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_DARMANITAN] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 1,
		},
		{
			.Move = MOVE_INCINERATE,
			.Level = 1,
		},
		{
			.Move = MOVE_RAGE,
			.Level = 1,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 3,
		},
		{
			.Move = MOVE_INCINERATE,
			.Level = 6,
		},
		{
			.Move = MOVE_RAGE,
			.Level = 9,
		},
		{
			.Move = MOVE_FIRE_FANG,
			.Level = 11,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 14,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 17,
		},
		{
			.Move = MOVE_FACADE,
			.Level = 19,
		},
		{
			.Move = MOVE_FIRE_PUNCH,
			.Level = 22,
		},
		{
			.Move = MOVE_WORK_UP,
			.Level = 25,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 27,
		},
		{
			.Move = MOVE_BELLY_DRUM,
			.Level = 30,
		},
		{
			.Move = MOVE_FLARE_BLITZ,
			.Level = 33,
		},
		{
			.Move = MOVE_HAMMER_ARM,
			.Level = 35,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 39,
		},
		{
			.Move = MOVE_SUPERPOWER,
			.Level = 47,
		},
		{
			.Move = MOVE_OVERHEAT,
			.Level = 54,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MARACTUS] = {
		{
			.Move = MOVE_SPIKY_SHIELD,
			.Level = 1,
		},
		{
			.Move = MOVE_COTTON_GUARD,
			.Level = 1,
		},
		{
			.Move = MOVE_AFTER_YOU,
			.Level = 1,
		},
		{
			.Move = MOVE_PECK,
			.Level = 1,
		},
		{
			.Move = MOVE_ABSORB,
			.Level = 1,
		},
		{
			.Move = MOVE_SWEET_SCENT,
			.Level = 3,
		},
		{
			.Move = MOVE_GROWTH,
			.Level = 6,
		},
		{
			.Move = MOVE_PIN_MISSILE,
			.Level = 10,
		},
		{
			.Move = MOVE_MEGA_DRAIN,
			.Level = 13,
		},
		{
			.Move = MOVE_SYNTHESIS,
			.Level = 15,
		},
		{
			.Move = MOVE_COTTON_SPORE,
			.Level = 18,
		},
		{
			.Move = MOVE_NEEDLE_ARM,
			.Level = 22,
		},
		{
			.Move = MOVE_GIGA_DRAIN,
			.Level = 26,
		},
		{
			.Move = MOVE_ACUPRESSURE,
			.Level = 29,
		},
		{
			.Move = MOVE_INGRAIN,
			.Level = 33,
		},
		{
			.Move = MOVE_PETAL_DANCE,
			.Level = 38,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 42,
		},
		{
			.Move = MOVE_SUNNY_DAY,
			.Level = 45,
		},
		{
			.Move = MOVE_PETAL_BLIZZARD,
			.Level = 48,
		},
		{
			.Move = MOVE_SOLARBEAM,
			.Level = 50,
		},
		{
			.Move = MOVE_COTTON_GUARD,
			.Level = 55,
		},
		{
			.Move = MOVE_AFTER_YOU,
			.Level = 57,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_DWEBBLE] = {
		{
			.Move = MOVE_FURY_CUTTER,
			.Level = 1,
		},
		{
			.Move = MOVE_ROCK_BLAST,
			.Level = 5,
		},
		{
			.Move = MOVE_WITHDRAW,
			.Level = 7,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 11,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 13,
		},
		{
			.Move = MOVE_SMACK_DOWN,
			.Level = 17,
		},
		{
			.Move = MOVE_ROCK_POLISH,
			.Level = 19,
		},
		{
			.Move = MOVE_BUG_BITE,
			.Level = 23,
		},
		{
			.Move = MOVE_STEALTH_ROCK,
			.Level = 24,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 29,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 31,
		},
		{
			.Move = MOVE_XSCISSOR,
			.Level = 35,
		},
		{
			.Move = MOVE_SHELL_SMASH,
			.Level = 37,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 41,
		},
		{
			.Move = MOVE_ROCK_WRECKER,
			.Level = 43,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CRUSTLE] = {
		{
			.Move = MOVE_SHELL_SMASH,
			.Level = 1,
		},
		{
			.Move = MOVE_ROCK_BLAST,
			.Level = 1,
		},
		{
			.Move = MOVE_WITHDRAW,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_ROCK_BLAST,
			.Level = 5,
		},
		{
			.Move = MOVE_WITHDRAW,
			.Level = 7,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 11,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 13,
		},
		{
			.Move = MOVE_SMACK_DOWN,
			.Level = 17,
		},
		{
			.Move = MOVE_ROCK_POLISH,
			.Level = 19,
		},
		{
			.Move = MOVE_BUG_BITE,
			.Level = 23,
		},
		{
			.Move = MOVE_STEALTH_ROCK,
			.Level = 24,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 29,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 31,
		},
		{
			.Move = MOVE_XSCISSOR,
			.Level = 38,
		},
		{
			.Move = MOVE_SHELL_SMASH,
			.Level = 43,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 50,
		},
		{
			.Move = MOVE_ROCK_WRECKER,
			.Level = 55,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SCRAGGY] = {
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_LOW_KICK,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 5,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 9,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 12,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 16,
		},
		{
			.Move = MOVE_BRICK_BREAK,
			.Level = 20,
		},
		{
			.Move = MOVE_PAYBACK,
			.Level = 23,
		},
		{
			.Move = MOVE_CHIP_AWAY,
			.Level = 27,
		},
		{
			.Move = MOVE_HI_JUMP_KICK,
			.Level = 31,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 34,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 38,
		},
		{
			.Move = MOVE_FACADE,
			.Level = 42,
		},
		{
			.Move = MOVE_ROCK_CLIMB,
			.Level = 45,
		},
		{
			.Move = MOVE_FOCUS_PUNCH,
			.Level = 48,
		},
		{
			.Move = MOVE_HEAD_SMASH,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SCRAFTY] = {
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_LOW_KICK,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 5,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 9,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 12,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 16,
		},
		{
			.Move = MOVE_BRICK_BREAK,
			.Level = 20,
		},
		{
			.Move = MOVE_PAYBACK,
			.Level = 23,
		},
		{
			.Move = MOVE_CHIP_AWAY,
			.Level = 27,
		},
		{
			.Move = MOVE_HI_JUMP_KICK,
			.Level = 31,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 34,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 38,
		},
		{
			.Move = MOVE_FACADE,
			.Level = 45,
		},
		{
			.Move = MOVE_ROCK_CLIMB,
			.Level = 51,
		},
		{
			.Move = MOVE_FOCUS_PUNCH,
			.Level = 58,
		},
		{
			.Move = MOVE_HEAD_SMASH,
			.Level = 65,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SIGILYPH] = {
		{
			.Move = MOVE_GUST,
			.Level = 1,
		},
		{
			.Move = MOVE_MIRACLE_EYE,
			.Level = 1,
		},
		{
			.Move = MOVE_HYPNOSIS,
			.Level = 4,
		},
		{
			.Move = MOVE_PSYWAVE,
			.Level = 8,
		},
		{
			.Move = MOVE_TAILWIND,
			.Level = 11,
		},
		{
			.Move = MOVE_WHIRLWIND,
			.Level = 14,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 18,
		},
		{
			.Move = MOVE_AIR_CUTTER,
			.Level = 21,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 24,
		},
		{
			.Move = MOVE_REFLECT,
			.Level = 28,
		},
		{
			.Move = MOVE_SYNCHRONOISE,
			.Level = 31,
		},
		{
			.Move = MOVE_MIRROR_MOVE,
			.Level = 34,
		},
		{
			.Move = MOVE_GRAVITY,
			.Level = 38,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 41,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 44,
		},
		{
			.Move = MOVE_COSMIC_POWER,
			.Level = 48,
		},
		{
			.Move = MOVE_SKY_ATTACK,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_YAMASK] = {
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 1,
		},
		{
			.Move = MOVE_DISABLE,
			.Level = 5,
		},
		{
			.Move = MOVE_HAZE,
			.Level = 9,
		},
		{
			.Move = MOVE_NIGHT_SHADE,
			.Level = 13,
		},
		{
			.Move = MOVE_HEX,
			.Level = 17,
		},
		{
			.Move = MOVE_WILLOWISP,
			.Level = 21,
		},
		{
			.Move = MOVE_OMINOUS_WIND,
			.Level = 25,
		},
		{
			.Move = MOVE_CURSE,
			.Level = 29,
		},
		{
			.Move = MOVE_POWER_SPLIT,
			.Level = 33,
		},
		{
			.Move = MOVE_GUARD_SPLIT,
			.Level = 33,
		},
		{
			.Move = MOVE_SHADOW_BALL,
			.Level = 37,
		},
		{
			.Move = MOVE_GRUDGE,
			.Level = 41,
		},
		{
			.Move = MOVE_MEAN_LOOK,
			.Level = 45,
		},
		{
			.Move = MOVE_DESTINY_BOND,
			.Level = 49,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_COFAGRIGUS] = {
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 1,
		},
		{
			.Move = MOVE_DISABLE,
			.Level = 1,
		},
		{
			.Move = MOVE_HAZE,
			.Level = 1,
		},
		{
			.Move = MOVE_DISABLE,
			.Level = 5,
		},
		{
			.Move = MOVE_HAZE,
			.Level = 9,
		},
		{
			.Move = MOVE_NIGHT_SHADE,
			.Level = 13,
		},
		{
			.Move = MOVE_HEX,
			.Level = 17,
		},
		{
			.Move = MOVE_WILLOWISP,
			.Level = 21,
		},
		{
			.Move = MOVE_OMINOUS_WIND,
			.Level = 25,
		},
		{
			.Move = MOVE_CURSE,
			.Level = 29,
		},
		{
			.Move = MOVE_POWER_SPLIT,
			.Level = 33,
		},
		{
			.Move = MOVE_GUARD_SPLIT,
			.Level = 33,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 34,
		},
		{
			.Move = MOVE_SHADOW_BALL,
			.Level = 39,
		},
		{
			.Move = MOVE_GRUDGE,
			.Level = 45,
		},
		{
			.Move = MOVE_MEAN_LOOK,
			.Level = 51,
		},
		{
			.Move = MOVE_DESTINY_BOND,
			.Level = 57,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_TIRTOUGA] = {
		{
			.Move = MOVE_BIDE,
			.Level = 1,
		},
		{
			.Move = MOVE_WITHDRAW,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 5,
		},
		{
			.Move = MOVE_BITE,
			.Level = 8,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 11,
		},
		{
			.Move = MOVE_AQUA_JET,
			.Level = 15,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 18,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 21,
		},
		{
			.Move = MOVE_WIDE_GUARD,
			.Level = 25,
		},
		{
			.Move = MOVE_BRINE,
			.Level = 28,
		},
		{
			.Move = MOVE_SMACK_DOWN,
			.Level = 31,
		},
		{
			.Move = MOVE_CURSE,
			.Level = 35,
		},
		{
			.Move = MOVE_SHELL_SMASH,
			.Level = 38,
		},
		{
			.Move = MOVE_AQUA_TAIL,
			.Level = 41,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 45,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 48,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CARRACOSTA] = {
		{
			.Move = MOVE_BIDE,
			.Level = 1,
		},
		{
			.Move = MOVE_WITHDRAW,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 1,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 5,
		},
		{
			.Move = MOVE_BITE,
			.Level = 8,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 11,
		},
		{
			.Move = MOVE_AQUA_JET,
			.Level = 15,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 18,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 21,
		},
		{
			.Move = MOVE_WIDE_GUARD,
			.Level = 25,
		},
		{
			.Move = MOVE_BRINE,
			.Level = 28,
		},
		{
			.Move = MOVE_SMACK_DOWN,
			.Level = 31,
		},
		{
			.Move = MOVE_CURSE,
			.Level = 35,
		},
		{
			.Move = MOVE_SHELL_SMASH,
			.Level = 40,
		},
		{
			.Move = MOVE_AQUA_TAIL,
			.Level = 45,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 51,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 56,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 61,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ARCHEN] = {
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_ROCK_THROW,
			.Level = 5,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 8,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 11,
		},
		{
			.Move = MOVE_PLUCK,
			.Level = 15,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 18,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 21,
		},
		{
			.Move = MOVE_QUICK_GUARD,
			.Level = 25,
		},
		{
			.Move = MOVE_ACROBATICS,
			.Level = 28,
		},
		{
			.Move = MOVE_DRAGONBREATH,
			.Level = 31,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 35,
		},
		{
			.Move = MOVE_ENDEAVOR,
			.Level = 38,
		},
		{
			.Move = MOVE_UTURN,
			.Level = 41,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 45,
		},
		{
			.Move = MOVE_DRAGON_CLAW,
			.Level = 48,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ARCHEOPS] = {
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_ROCK_THROW,
			.Level = 1,
		},
		{
			.Move = MOVE_ROCK_THROW,
			.Level = 5,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 8,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 11,
		},
		{
			.Move = MOVE_PLUCK,
			.Level = 15,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 18,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 21,
		},
		{
			.Move = MOVE_QUICK_GUARD,
			.Level = 25,
		},
		{
			.Move = MOVE_ACROBATICS,
			.Level = 28,
		},
		{
			.Move = MOVE_DRAGONBREATH,
			.Level = 31,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 35,
		},
		{
			.Move = MOVE_ENDEAVOR,
			.Level = 40,
		},
		{
			.Move = MOVE_UTURN,
			.Level = 45,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 51,
		},
		{
			.Move = MOVE_DRAGON_CLAW,
			.Level = 56,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 61,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_TRUBBISH] = {
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_POISON_GAS,
			.Level = 1,
		},
		{
			.Move = MOVE_RECYCLE,
			.Level = 3,
		},
		{
			.Move = MOVE_TOXIC_SPIKES,
			.Level = 7,
		},
		{
			.Move = MOVE_ACID_SPRAY,
			.Level = 12,
		},
		{
			.Move = MOVE_DOUBLESLAP,
			.Level = 14,
		},
		{
			.Move = MOVE_SLUDGE,
			.Level = 18,
		},
		{
			.Move = MOVE_STOCKPILE,
			.Level = 23,
		},
		{
			.Move = MOVE_SWALLOW,
			.Level = 23,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 25,
		},
		{
			.Move = MOVE_SLUDGE_BOMB,
			.Level = 29,
		},
		{
			.Move = MOVE_CLEAR_SMOG,
			.Level = 34,
		},
		{
			.Move = MOVE_TOXIC,
			.Level = 36,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 40,
		},
		{
			.Move = MOVE_BELCH,
			.Level = 42,
		},
		{
			.Move = MOVE_GUNK_SHOT,
			.Level = 45,
		},
		{
			.Move = MOVE_EXPLOSION,
			.Level = 47,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GARBODOR] = {
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_POISON_GAS,
			.Level = 1,
		},
		{
			.Move = MOVE_RECYCLE,
			.Level = 1,
		},
		{
			.Move = MOVE_TOXIC_SPIKES,
			.Level = 1,
		},
		{
			.Move = MOVE_RECYCLE,
			.Level = 3,
		},
		{
			.Move = MOVE_TOXIC_SPIKES,
			.Level = 7,
		},
		{
			.Move = MOVE_ACID_SPRAY,
			.Level = 12,
		},
		{
			.Move = MOVE_DOUBLESLAP,
			.Level = 14,
		},
		{
			.Move = MOVE_SLUDGE,
			.Level = 18,
		},
		{
			.Move = MOVE_STOCKPILE,
			.Level = 23,
		},
		{
			.Move = MOVE_SWALLOW,
			.Level = 23,
		},
		{
			.Move = MOVE_BODY_SLAM,
			.Level = 25,
		},
		{
			.Move = MOVE_SLUDGE_BOMB,
			.Level = 29,
		},
		{
			.Move = MOVE_CLEAR_SMOG,
			.Level = 34,
		},
		{
			.Move = MOVE_TOXIC,
			.Level = 39,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 46,
		},
		{
			.Move = MOVE_BELCH,
			.Level = 49,
		},
		{
			.Move = MOVE_GUNK_SHOT,
			.Level = 54,
		},
		{
			.Move = MOVE_EXPLOSION,
			.Level = 59,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ZORUA] = {
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 5,
		},
		{
			.Move = MOVE_FAKE_TEARS,
			.Level = 9,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 13,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 17,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 21,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 25,
		},
		{
			.Move = MOVE_FOUL_PLAY,
			.Level = 29,
		},
		{
			.Move = MOVE_TORMENT,
			.Level = 33,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 37,
		},
		{
			.Move = MOVE_EMBARGO,
			.Level = 41,
		},
		{
			.Move = MOVE_PUNISHMENT,
			.Level = 45,
		},
		{
			.Move = MOVE_NASTY_PLOT,
			.Level = 49,
		},
		{
			.Move = MOVE_IMPRISON,
			.Level = 53,
		},
		{
			.Move = MOVE_NIGHT_DAZE,
			.Level = 57,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ZOROARK] = {
		{
			.Move = MOVE_NIGHT_DAZE,
			.Level = 1,
		},
		{
			.Move = MOVE_IMPRISON,
			.Level = 1,
		},
		{
			.Move = MOVE_UTURN,
			.Level = 1,
		},
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 1,
		},
		{
			.Move = MOVE_HONE_CLAWS,
			.Level = 1,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 5,
		},
		{
			.Move = MOVE_HONE_CLAWS,
			.Level = 9,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 13,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 17,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 21,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 25,
		},
		{
			.Move = MOVE_FOUL_PLAY,
			.Level = 29,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 30,
		},
		{
			.Move = MOVE_TORMENT,
			.Level = 34,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 39,
		},
		{
			.Move = MOVE_EMBARGO,
			.Level = 44,
		},
		{
			.Move = MOVE_PUNISHMENT,
			.Level = 49,
		},
		{
			.Move = MOVE_NASTY_PLOT,
			.Level = 54,
		},
		{
			.Move = MOVE_IMPRISON,
			.Level = 59,
		},
		{
			.Move = MOVE_NIGHT_DAZE,
			.Level = 64,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MINCCINO] = {
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_BABYDOLL_EYES,
			.Level = 3,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 7,
		},
		{
			.Move = MOVE_TICKLE,
			.Level = 9,
		},
		{
			.Move = MOVE_DOUBLESLAP,
			.Level = 13,
		},
		{
			.Move = MOVE_ENCORE,
			.Level = 15,
		},
		{
			.Move = MOVE_SWIFT,
			.Level = 19,
		},
		{
			.Move = MOVE_SING,
			.Level = 21,
		},
		{
			.Move = MOVE_TAIL_SLAP,
			.Level = 25,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 27,
		},
		{
			.Move = MOVE_WAKEUP_SLAP,
			.Level = 31,
		},
		{
			.Move = MOVE_ECHOED_VOICE,
			.Level = 33,
		},
		{
			.Move = MOVE_SLAM,
			.Level = 37,
		},
		{
			.Move = MOVE_CAPTIVATE,
			.Level = 39,
		},
		{
			.Move = MOVE_HYPER_VOICE,
			.Level = 43,
		},
		{
			.Move = MOVE_LAST_RESORT,
			.Level = 45,
		},
		{
			.Move = MOVE_AFTER_YOU,
			.Level = 49,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CINCCINO] = {
		{
			.Move = MOVE_BULLET_SEED,
			.Level = 1,
		},
		{
			.Move = MOVE_ROCK_BLAST,
			.Level = 1,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 1,
		},
		{
			.Move = MOVE_TICKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_SING,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_SLAP,
			.Level = 1,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GOTHITA] = {
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 3,
		},
		{
			.Move = MOVE_TICKLE,
			.Level = 7,
		},
		{
			.Move = MOVE_PLAY_NICE,
			.Level = 8,
		},
		{
			.Move = MOVE_FAKE_TEARS,
			.Level = 10,
		},
		{
			.Move = MOVE_DOUBLESLAP,
			.Level = 14,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 16,
		},
		{
			.Move = MOVE_EMBARGO,
			.Level = 19,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 24,
		},
		{
			.Move = MOVE_PSYSHOCK,
			.Level = 25,
		},
		{
			.Move = MOVE_FLATTER,
			.Level = 28,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 31,
		},
		{
			.Move = MOVE_HEAL_BLOCK,
			.Level = 33,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 37,
		},
		{
			.Move = MOVE_TELEKINESIS,
			.Level = 40,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 46,
		},
		{
			.Move = MOVE_MAGIC_ROOM,
			.Level = 48,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GOTHORITA] = {
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_TICKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_PLAY_NICE,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 3,
		},
		{
			.Move = MOVE_TICKLE,
			.Level = 7,
		},
		{
			.Move = MOVE_FAKE_TEARS,
			.Level = 10,
		},
		{
			.Move = MOVE_DOUBLESLAP,
			.Level = 14,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 16,
		},
		{
			.Move = MOVE_EMBARGO,
			.Level = 19,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 24,
		},
		{
			.Move = MOVE_PSYSHOCK,
			.Level = 25,
		},
		{
			.Move = MOVE_FLATTER,
			.Level = 28,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 31,
		},
		{
			.Move = MOVE_HEAL_BLOCK,
			.Level = 34,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 39,
		},
		{
			.Move = MOVE_TELEKINESIS,
			.Level = 43,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 50,
		},
		{
			.Move = MOVE_MAGIC_ROOM,
			.Level = 53,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GOTHITELLE] = {
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_TICKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_PLAY_NICE,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 3,
		},
		{
			.Move = MOVE_TICKLE,
			.Level = 7,
		},
		{
			.Move = MOVE_FAKE_TEARS,
			.Level = 10,
		},
		{
			.Move = MOVE_DOUBLESLAP,
			.Level = 14,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 16,
		},
		{
			.Move = MOVE_EMBARGO,
			.Level = 19,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 24,
		},
		{
			.Move = MOVE_PSYSHOCK,
			.Level = 25,
		},
		{
			.Move = MOVE_FLATTER,
			.Level = 28,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 31,
		},
		{
			.Move = MOVE_HEAL_BLOCK,
			.Level = 34,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 39,
		},
		{
			.Move = MOVE_TELEKINESIS,
			.Level = 45,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 54,
		},
		{
			.Move = MOVE_MAGIC_ROOM,
			.Level = 59,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SOLOSIS] = {
		{
			.Move = MOVE_PSYWAVE,
			.Level = 1,
		},
		{
			.Move = MOVE_REFLECT,
			.Level = 3,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 7,
		},
		{
			.Move = MOVE_SNATCH,
			.Level = 10,
		},
		{
			.Move = MOVE_HIDDEN_POWER,
			.Level = 14,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 16,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 19,
		},
		{
			.Move = MOVE_RECOVER,
			.Level = 24,
		},
		{
			.Move = MOVE_PSYSHOCK,
			.Level = 25,
		},
		{
			.Move = MOVE_ENDEAVOR,
			.Level = 28,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 31,
		},
		{
			.Move = MOVE_PAIN_SPLIT,
			.Level = 33,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 37,
		},
		{
			.Move = MOVE_SKILL_SWAP,
			.Level = 40,
		},
		{
			.Move = MOVE_HEAL_BLOCK,
			.Level = 46,
		},
		{
			.Move = MOVE_WONDER_ROOM,
			.Level = 48,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_DUOSION] = {
		{
			.Move = MOVE_PSYWAVE,
			.Level = 1,
		},
		{
			.Move = MOVE_REFLECT,
			.Level = 1,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 1,
		},
		{
			.Move = MOVE_SNATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_REFLECT,
			.Level = 3,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 7,
		},
		{
			.Move = MOVE_SNATCH,
			.Level = 10,
		},
		{
			.Move = MOVE_HIDDEN_POWER,
			.Level = 14,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 16,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 19,
		},
		{
			.Move = MOVE_RECOVER,
			.Level = 24,
		},
		{
			.Move = MOVE_PSYSHOCK,
			.Level = 25,
		},
		{
			.Move = MOVE_ENDEAVOR,
			.Level = 28,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 31,
		},
		{
			.Move = MOVE_PAIN_SPLIT,
			.Level = 34,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 39,
		},
		{
			.Move = MOVE_SKILL_SWAP,
			.Level = 43,
		},
		{
			.Move = MOVE_HEAL_BLOCK,
			.Level = 50,
		},
		{
			.Move = MOVE_WONDER_ROOM,
			.Level = 53,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_REUNICLUS] = {
		{
			.Move = MOVE_PSYWAVE,
			.Level = 1,
		},
		{
			.Move = MOVE_REFLECT,
			.Level = 1,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 1,
		},
		{
			.Move = MOVE_SNATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_REFLECT,
			.Level = 3,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 7,
		},
		{
			.Move = MOVE_SNATCH,
			.Level = 10,
		},
		{
			.Move = MOVE_HIDDEN_POWER,
			.Level = 14,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 16,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 19,
		},
		{
			.Move = MOVE_RECOVER,
			.Level = 24,
		},
		{
			.Move = MOVE_PSYSHOCK,
			.Level = 25,
		},
		{
			.Move = MOVE_ENDEAVOR,
			.Level = 28,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 31,
		},
		{
			.Move = MOVE_PAIN_SPLIT,
			.Level = 34,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 39,
		},
		{
			.Move = MOVE_DIZZY_PUNCH,
			.Level = 41,
		},
		{
			.Move = MOVE_SKILL_SWAP,
			.Level = 45,
		},
		{
			.Move = MOVE_HEAL_BLOCK,
			.Level = 54,
		},
		{
			.Move = MOVE_WONDER_ROOM,
			.Level = 59,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_DUCKLETT] = {
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 3,
		},
		{
			.Move = MOVE_DEFOG,
			.Level = 6,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 9,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 13,
		},
		{
			.Move = MOVE_AERIAL_ACE,
			.Level = 15,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 19,
		},
		{
			.Move = MOVE_FEATHERDANCE,
			.Level = 21,
		},
		{
			.Move = MOVE_AQUA_RING,
			.Level = 24,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 27,
		},
		{
			.Move = MOVE_ROOST,
			.Level = 30,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 34,
		},
		{
			.Move = MOVE_TAILWIND,
			.Level = 37,
		},
		{
			.Move = MOVE_BRAVE_BIRD,
			.Level = 41,
		},
		{
			.Move = MOVE_HURRICANE,
			.Level = 46,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SWANNA] = {
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_DEFOG,
			.Level = 1,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 3,
		},
		{
			.Move = MOVE_DEFOG,
			.Level = 6,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 9,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 13,
		},
		{
			.Move = MOVE_AERIAL_ACE,
			.Level = 15,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 19,
		},
		{
			.Move = MOVE_FEATHERDANCE,
			.Level = 21,
		},
		{
			.Move = MOVE_AQUA_RING,
			.Level = 24,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 27,
		},
		{
			.Move = MOVE_ROOST,
			.Level = 30,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 34,
		},
		{
			.Move = MOVE_TAILWIND,
			.Level = 40,
		},
		{
			.Move = MOVE_BRAVE_BIRD,
			.Level = 47,
		},
		{
			.Move = MOVE_HURRICANE,
			.Level = 55,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_VANILLITE] = {
		{
			.Move = MOVE_ICICLE_SPEAR,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 4,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 7,
		},
		{
			.Move = MOVE_UPROAR,
			.Level = 10,
		},
		{
			.Move = MOVE_ICY_WIND,
			.Level = 13,
		},
		{
			.Move = MOVE_MIST,
			.Level = 16,
		},
		{
			.Move = MOVE_AVALANCHE,
			.Level = 19,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 22,
		},
		{
			.Move = MOVE_MIRROR_SHOT,
			.Level = 26,
		},
		{
			.Move = MOVE_ACID_ARMOR,
			.Level = 31,
		},
		{
			.Move = MOVE_ICE_BEAM,
			.Level = 35,
		},
		{
			.Move = MOVE_HAIL,
			.Level = 40,
		},
		{
			.Move = MOVE_MIRROR_COAT,
			.Level = 44,
		},
		{
			.Move = MOVE_BLIZZARD,
			.Level = 49,
		},
		{
			.Move = MOVE_SHEER_COLD,
			.Level = 53,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_VANILLISH] = {
		{
			.Move = MOVE_ICICLE_SPEAR,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_UPROAR,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 4,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 7,
		},
		{
			.Move = MOVE_UPROAR,
			.Level = 10,
		},
		{
			.Move = MOVE_ICY_WIND,
			.Level = 13,
		},
		{
			.Move = MOVE_MIST,
			.Level = 16,
		},
		{
			.Move = MOVE_AVALANCHE,
			.Level = 19,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 22,
		},
		{
			.Move = MOVE_MIRROR_SHOT,
			.Level = 26,
		},
		{
			.Move = MOVE_ACID_ARMOR,
			.Level = 31,
		},
		{
			.Move = MOVE_ICE_BEAM,
			.Level = 36,
		},
		{
			.Move = MOVE_HAIL,
			.Level = 42,
		},
		{
			.Move = MOVE_MIRROR_COAT,
			.Level = 47,
		},
		{
			.Move = MOVE_BLIZZARD,
			.Level = 53,
		},
		{
			.Move = MOVE_SHEER_COLD,
			.Level = 58,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_VANILLUXE] = {
		{
			.Move = MOVE_SHEER_COLD,
			.Level = 1,
		},
		{
			.Move = MOVE_FREEZEDRY,
			.Level = 1,
		},
		{
			.Move = MOVE_WEATHER_BALL,
			.Level = 1,
		},
		{
			.Move = MOVE_ICICLE_SPEAR,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_UPROAR,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 4,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 7,
		},
		{
			.Move = MOVE_UPROAR,
			.Level = 10,
		},
		{
			.Move = MOVE_ICY_WIND,
			.Level = 13,
		},
		{
			.Move = MOVE_MIST,
			.Level = 16,
		},
		{
			.Move = MOVE_AVALANCHE,
			.Level = 19,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 22,
		},
		{
			.Move = MOVE_MIRROR_SHOT,
			.Level = 26,
		},
		{
			.Move = MOVE_ACID_ARMOR,
			.Level = 31,
		},
		{
			.Move = MOVE_ICE_BEAM,
			.Level = 36,
		},
		{
			.Move = MOVE_HAIL,
			.Level = 42,
		},
		{
			.Move = MOVE_MIRROR_COAT,
			.Level = 50,
		},
		{
			.Move = MOVE_BLIZZARD,
			.Level = 59,
		},
		{
			.Move = MOVE_SHEER_COLD,
			.Level = 67,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_DEERLING] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_CAMOUFLAGE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 4,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 7,
		},
		{
			.Move = MOVE_DOUBLE_KICK,
			.Level = 10,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 13,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 16,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 20,
		},
		{
			.Move = MOVE_JUMP_KICK,
			.Level = 24,
		},
		{
			.Move = MOVE_AROMATHERAPY,
			.Level = 28,
		},
		{
			.Move = MOVE_ENERGY_BALL,
			.Level = 32,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 36,
		},
		{
			.Move = MOVE_NATURE_POWER,
			.Level = 41,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 46,
		},
		{
			.Move = MOVE_SOLARBEAM,
			.Level = 51,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SAWSBUCK] = {
		{
			.Move = MOVE_MEGAHORN,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_CAMOUFLAGE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 4,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 7,
		},
		{
			.Move = MOVE_DOUBLE_KICK,
			.Level = 10,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 13,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 16,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 20,
		},
		{
			.Move = MOVE_JUMP_KICK,
			.Level = 24,
		},
		{
			.Move = MOVE_AROMATHERAPY,
			.Level = 28,
		},
		{
			.Move = MOVE_ENERGY_BALL,
			.Level = 32,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 36,
		},
		{
			.Move = MOVE_HORN_LEECH,
			.Level = 37,
		},
		{
			.Move = MOVE_NATURE_POWER,
			.Level = 44,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 52,
		},
		{
			.Move = MOVE_SOLARBEAM,
			.Level = 60,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_EMOLGA] = {
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 4,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 7,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 10,
		},
		{
			.Move = MOVE_SPARK,
			.Level = 13,
		},
		{
			.Move = MOVE_NUZZLE,
			.Level = 15,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 16,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 19,
		},
		{
			.Move = MOVE_SHOCK_WAVE,
			.Level = 22,
		},
		{
			.Move = MOVE_ELECTRO_BALL,
			.Level = 26,
		},
		{
			.Move = MOVE_ACROBATICS,
			.Level = 30,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 34,
		},
		{
			.Move = MOVE_ENCORE,
			.Level = 38,
		},
		{
			.Move = MOVE_VOLT_SWITCH,
			.Level = 42,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 46,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_KARRABLAST] = {
		{
			.Move = MOVE_PECK,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 4,
		},
		{
			.Move = MOVE_ENDURE,
			.Level = 8,
		},
		{
			.Move = MOVE_FURY_CUTTER,
			.Level = 13,
		},
		{
			.Move = MOVE_FURY_ATTACK,
			.Level = 16,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 20,
		},
		{
			.Move = MOVE_FALSE_SWIPE,
			.Level = 25,
		},
		{
			.Move = MOVE_BUG_BUZZ,
			.Level = 28,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 32,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 37,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 40,
		},
		{
			.Move = MOVE_XSCISSOR,
			.Level = 44,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 49,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 52,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 56,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ESCAVALIER] = {
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 1,
		},
		{
			.Move = MOVE_FELL_STINGER,
			.Level = 1,
		},
		{
			.Move = MOVE_PECK,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_GUARD,
			.Level = 1,
		},
		{
			.Move = MOVE_TWINEEDLE,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 4,
		},
		{
			.Move = MOVE_QUICK_GUARD,
			.Level = 8,
		},
		{
			.Move = MOVE_TWINEEDLE,
			.Level = 13,
		},
		{
			.Move = MOVE_FURY_ATTACK,
			.Level = 16,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 20,
		},
		{
			.Move = MOVE_FALSE_SWIPE,
			.Level = 25,
		},
		{
			.Move = MOVE_BUG_BUZZ,
			.Level = 28,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 32,
		},
		{
			.Move = MOVE_IRON_HEAD,
			.Level = 37,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 40,
		},
		{
			.Move = MOVE_XSCISSOR,
			.Level = 44,
		},
		{
			.Move = MOVE_REVERSAL,
			.Level = 49,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 52,
		},
		{
			.Move = MOVE_GIGA_IMPACT,
			.Level = 56,
		},
		{
			.Move = MOVE_FELL_STINGER,
			.Level = 60,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_FOONGUS] = {
		{
			.Move = MOVE_ABSORB,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWTH,
			.Level = 6,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 8,
		},
		{
			.Move = MOVE_BIDE,
			.Level = 12,
		},
		{
			.Move = MOVE_MEGA_DRAIN,
			.Level = 15,
		},
		{
			.Move = MOVE_INGRAIN,
			.Level = 18,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 20,
		},
		{
			.Move = MOVE_SWEET_SCENT,
			.Level = 24,
		},
		{
			.Move = MOVE_GIGA_DRAIN,
			.Level = 28,
		},
		{
			.Move = MOVE_TOXIC,
			.Level = 32,
		},
		{
			.Move = MOVE_SYNTHESIS,
			.Level = 35,
		},
		{
			.Move = MOVE_CLEAR_SMOG,
			.Level = 39,
		},
		{
			.Move = MOVE_SOLARBEAM,
			.Level = 43,
		},
		{
			.Move = MOVE_RAGE_POWDER,
			.Level = 45,
		},
		{
			.Move = MOVE_SPORE,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_AMOONGUSS] = {
		{
			.Move = MOVE_ABSORB,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWTH,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_BIDE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWTH,
			.Level = 6,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 8,
		},
		{
			.Move = MOVE_BIDE,
			.Level = 12,
		},
		{
			.Move = MOVE_MEGA_DRAIN,
			.Level = 15,
		},
		{
			.Move = MOVE_INGRAIN,
			.Level = 18,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 20,
		},
		{
			.Move = MOVE_SWEET_SCENT,
			.Level = 24,
		},
		{
			.Move = MOVE_GIGA_DRAIN,
			.Level = 28,
		},
		{
			.Move = MOVE_TOXIC,
			.Level = 32,
		},
		{
			.Move = MOVE_SYNTHESIS,
			.Level = 35,
		},
		{
			.Move = MOVE_CLEAR_SMOG,
			.Level = 43,
		},
		{
			.Move = MOVE_SOLARBEAM,
			.Level = 49,
		},
		{
			.Move = MOVE_RAGE_POWDER,
			.Level = 54,
		},
		{
			.Move = MOVE_SPORE,
			.Level = 62,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_FRILLISH] = {
		{
			.Move = MOVE_BUBBLE,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_ABSORB,
			.Level = 5,
		},
		{
			.Move = MOVE_NIGHT_SHADE,
			.Level = 9,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 13,
		},
		{
			.Move = MOVE_RECOVER,
			.Level = 17,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 22,
		},
		{
			.Move = MOVE_OMINOUS_WIND,
			.Level = 27,
		},
		{
			.Move = MOVE_BRINE,
			.Level = 32,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 37,
		},
		{
			.Move = MOVE_HEX,
			.Level = 43,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 49,
		},
		{
			.Move = MOVE_WRING_OUT,
			.Level = 55,
		},
		{
			.Move = MOVE_WATER_SPOUT,
			.Level = 61,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_JELLICENT] = {
		{
			.Move = MOVE_WATER_SPOUT,
			.Level = 1,
		},
		{
			.Move = MOVE_WRING_OUT,
			.Level = 1,
		},
		{
			.Move = MOVE_BUBBLE,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_ABSORB,
			.Level = 1,
		},
		{
			.Move = MOVE_NIGHT_SHADE,
			.Level = 1,
		},
		{
			.Move = MOVE_ABSORB,
			.Level = 5,
		},
		{
			.Move = MOVE_NIGHT_SHADE,
			.Level = 9,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 13,
		},
		{
			.Move = MOVE_RECOVER,
			.Level = 17,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 22,
		},
		{
			.Move = MOVE_OMINOUS_WIND,
			.Level = 27,
		},
		{
			.Move = MOVE_BRINE,
			.Level = 32,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 37,
		},
		{
			.Move = MOVE_HEX,
			.Level = 45,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 53,
		},
		{
			.Move = MOVE_WRING_OUT,
			.Level = 61,
		},
		{
			.Move = MOVE_WATER_SPOUT,
			.Level = 69,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ALOMOMOLA] = {
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 1,
		},
		{
			.Move = MOVE_WIDE_GUARD,
			.Level = 1,
		},
		{
			.Move = MOVE_HEALING_WISH,
			.Level = 1,
		},
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_AQUA_RING,
			.Level = 5,
		},
		{
			.Move = MOVE_AQUA_JET,
			.Level = 9,
		},
		{
			.Move = MOVE_DOUBLESLAP,
			.Level = 13,
		},
		{
			.Move = MOVE_HEAL_PULSE,
			.Level = 17,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 21,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 25,
		},
		{
			.Move = MOVE_WAKEUP_SLAP,
			.Level = 29,
		},
		{
			.Move = MOVE_SOAK,
			.Level = 33,
		},
		{
			.Move = MOVE_WISH,
			.Level = 37,
		},
		{
			.Move = MOVE_BRINE,
			.Level = 41,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 45,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 49,
		},
		{
			.Move = MOVE_WIDE_GUARD,
			.Level = 53,
		},
		{
			.Move = MOVE_HEALING_WISH,
			.Level = 57,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 61,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_JOLTIK] = {
		{
			.Move = MOVE_STRING_SHOT,
			.Level = 1,
		},
		{
			.Move = MOVE_LEECH_LIFE,
			.Level = 1,
		},
		{
			.Move = MOVE_SPIDER_WEB,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 4,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 7,
		},
		{
			.Move = MOVE_FURY_CUTTER,
			.Level = 12,
		},
		{
			.Move = MOVE_ELECTROWEB,
			.Level = 15,
		},
		{
			.Move = MOVE_BUG_BITE,
			.Level = 18,
		},
		{
			.Move = MOVE_GASTRO_ACID,
			.Level = 23,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 26,
		},
		{
			.Move = MOVE_ELECTRO_BALL,
			.Level = 29,
		},
		{
			.Move = MOVE_SIGNAL_BEAM,
			.Level = 34,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 37,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 40,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 45,
		},
		{
			.Move = MOVE_BUG_BUZZ,
			.Level = 48,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GALVANTULA] = {
		{
			.Move = MOVE_STICKY_WEB,
			.Level = 1,
		},
		{
			.Move = MOVE_STRING_SHOT,
			.Level = 1,
		},
		{
			.Move = MOVE_LEECH_LIFE,
			.Level = 1,
		},
		{
			.Move = MOVE_SPIDER_WEB,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 4,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 7,
		},
		{
			.Move = MOVE_FURY_CUTTER,
			.Level = 12,
		},
		{
			.Move = MOVE_ELECTROWEB,
			.Level = 15,
		},
		{
			.Move = MOVE_BUG_BITE,
			.Level = 18,
		},
		{
			.Move = MOVE_GASTRO_ACID,
			.Level = 23,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 26,
		},
		{
			.Move = MOVE_ELECTRO_BALL,
			.Level = 29,
		},
		{
			.Move = MOVE_SIGNAL_BEAM,
			.Level = 34,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 40,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 46,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 54,
		},
		{
			.Move = MOVE_BUG_BUZZ,
			.Level = 60,
		},
		{
			.Move = MOVE_STICKY_WEB,
			.Level = 65,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_FERROSEED] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 1,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 6,
		},
		{
			.Move = MOVE_CURSE,
			.Level = 9,
		},
		{
			.Move = MOVE_METAL_CLAW,
			.Level = 14,
		},
		{
			.Move = MOVE_PIN_MISSILE,
			.Level = 18,
		},
		{
			.Move = MOVE_GYRO_BALL,
			.Level = 21,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 26,
		},
		{
			.Move = MOVE_MIRROR_SHOT,
			.Level = 30,
		},
		{
			.Move = MOVE_INGRAIN,
			.Level = 35,
		},
		{
			.Move = MOVE_SELFDESTRUCT,
			.Level = 38,
		},
		{
			.Move = MOVE_IRON_HEAD,
			.Level = 43,
		},
		{
			.Move = MOVE_PAYBACK,
			.Level = 47,
		},
		{
			.Move = MOVE_FLASH_CANNON,
			.Level = 52,
		},
		{
			.Move = MOVE_EXPLOSION,
			.Level = 55,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_FERROTHORN] = {
		{
			.Move = MOVE_ROCK_CLIMB,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 1,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 1,
		},
		{
			.Move = MOVE_CURSE,
			.Level = 1,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 6,
		},
		{
			.Move = MOVE_CURSE,
			.Level = 9,
		},
		{
			.Move = MOVE_METAL_CLAW,
			.Level = 14,
		},
		{
			.Move = MOVE_PIN_MISSILE,
			.Level = 18,
		},
		{
			.Move = MOVE_GYRO_BALL,
			.Level = 21,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 26,
		},
		{
			.Move = MOVE_MIRROR_SHOT,
			.Level = 30,
		},
		{
			.Move = MOVE_INGRAIN,
			.Level = 35,
		},
		{
			.Move = MOVE_SELFDESTRUCT,
			.Level = 38,
		},
		{
			.Move = MOVE_POWER_WHIP,
			.Level = 40,
		},
		{
			.Move = MOVE_IRON_HEAD,
			.Level = 46,
		},
		{
			.Move = MOVE_PAYBACK,
			.Level = 53,
		},
		{
			.Move = MOVE_FLASH_CANNON,
			.Level = 61,
		},
		{
			.Move = MOVE_EXPLOSION,
			.Level = 67,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_KLINK] = {
		{
			.Move = MOVE_VICEGRIP,
			.Level = 1,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 6,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 11,
		},
		{
			.Move = MOVE_GEAR_GRIND,
			.Level = 16,
		},
		{
			.Move = MOVE_BIND,
			.Level = 21,
		},
		{
			.Move = MOVE_CHARGE_BEAM,
			.Level = 26,
		},
		{
			.Move = MOVE_AUTOTOMIZE,
			.Level = 31,
		},
		{
			.Move = MOVE_MIRROR_SHOT,
			.Level = 36,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 39,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 42,
		},
		{
			.Move = MOVE_METAL_SOUND,
			.Level = 45,
		},
		{
			.Move = MOVE_SHIFT_GEAR,
			.Level = 48,
		},
		{
			.Move = MOVE_LOCKON,
			.Level = 50,
		},
		{
			.Move = MOVE_ZAP_CANNON,
			.Level = 54,
		},
		{
			.Move = MOVE_HYPER_BEAM,
			.Level = 57,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_KLANG] = {
		{
			.Move = MOVE_VICEGRIP,
			.Level = 1,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 1,
		},
		{
			.Move = MOVE_GEAR_GRIND,
			.Level = 1,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 6,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 11,
		},
		{
			.Move = MOVE_GEAR_GRIND,
			.Level = 16,
		},
		{
			.Move = MOVE_BIND,
			.Level = 21,
		},
		{
			.Move = MOVE_CHARGE_BEAM,
			.Level = 26,
		},
		{
			.Move = MOVE_AUTOTOMIZE,
			.Level = 31,
		},
		{
			.Move = MOVE_MIRROR_SHOT,
			.Level = 36,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 40,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 44,
		},
		{
			.Move = MOVE_METAL_SOUND,
			.Level = 48,
		},
		{
			.Move = MOVE_SHIFT_GEAR,
			.Level = 52,
		},
		{
			.Move = MOVE_LOCKON,
			.Level = 56,
		},
		{
			.Move = MOVE_ZAP_CANNON,
			.Level = 60,
		},
		{
			.Move = MOVE_HYPER_BEAM,
			.Level = 64,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_KLINKLANG] = {
		{
			.Move = MOVE_MAGNETIC_FLUX,
			.Level = 1,
		},
		{
			.Move = MOVE_ZAP_CANNON,
			.Level = 1,
		},
		{
			.Move = MOVE_VICEGRIP,
			.Level = 1,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 1,
		},
		{
			.Move = MOVE_GEAR_GRIND,
			.Level = 1,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 6,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 11,
		},
		{
			.Move = MOVE_GEAR_GRIND,
			.Level = 16,
		},
		{
			.Move = MOVE_BIND,
			.Level = 21,
		},
		{
			.Move = MOVE_CHARGE_BEAM,
			.Level = 25,
		},
		{
			.Move = MOVE_AUTOTOMIZE,
			.Level = 31,
		},
		{
			.Move = MOVE_MIRROR_SHOT,
			.Level = 36,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 40,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 44,
		},
		{
			.Move = MOVE_METAL_SOUND,
			.Level = 48,
		},
		{
			.Move = MOVE_SHIFT_GEAR,
			.Level = 54,
		},
		{
			.Move = MOVE_LOCKON,
			.Level = 60,
		},
		{
			.Move = MOVE_ZAP_CANNON,
			.Level = 66,
		},
		{
			.Move = MOVE_HYPER_BEAM,
			.Level = 72,
		},
		{
			.Move = MOVE_MAGNETIC_FLUX,
			.Level = 76,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_TYNAMO] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 1,
		},
		{
			.Move = MOVE_SPARK,
			.Level = 1,
		},
		{
			.Move = MOVE_CHARGE_BEAM,
			.Level = 1,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_EELEKTRIK] = {
		{
			.Move = MOVE_HEADBUTT,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 1,
		},
		{
			.Move = MOVE_SPARK,
			.Level = 1,
		},
		{
			.Move = MOVE_CHARGE_BEAM,
			.Level = 1,
		},
		{
			.Move = MOVE_BIND,
			.Level = 9,
		},
		{
			.Move = MOVE_ACID,
			.Level = 19,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 29,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 39,
		},
		{
			.Move = MOVE_THUNDERBOLT,
			.Level = 44,
		},
		{
			.Move = MOVE_ACID_SPRAY,
			.Level = 49,
		},
		{
			.Move = MOVE_COIL,
			.Level = 54,
		},
		{
			.Move = MOVE_WILD_CHARGE,
			.Level = 59,
		},
		{
			.Move = MOVE_GASTRO_ACID,
			.Level = 64,
		},
		{
			.Move = MOVE_ZAP_CANNON,
			.Level = 69,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 74,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_EELEKTROSS] = {
		{
			.Move = MOVE_THRASH,
			.Level = 1,
		},
		{
			.Move = MOVE_ZAP_CANNON,
			.Level = 1,
		},
		{
			.Move = MOVE_GASTRO_ACID,
			.Level = 1,
		},
		{
			.Move = MOVE_COIL,
			.Level = 1,
		},
		{
			.Move = MOVE_ION_DELUGE,
			.Level = 1,
		},
		{
			.Move = MOVE_CRUSH_CLAW,
			.Level = 1,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 1,
		},
		{
			.Move = MOVE_ACID,
			.Level = 1,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 1,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 1,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ELGYEM] = {
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 4,
		},
		{
			.Move = MOVE_HEAL_BLOCK,
			.Level = 8,
		},
		{
			.Move = MOVE_MIRACLE_EYE,
			.Level = 11,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 15,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 18,
		},
		{
			.Move = MOVE_HIDDEN_POWER,
			.Level = 22,
		},
		{
			.Move = MOVE_IMPRISON,
			.Level = 25,
		},
		{
			.Move = MOVE_SIMPLE_BEAM,
			.Level = 29,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 32,
		},
		{
			.Move = MOVE_PSYCH_UP,
			.Level = 36,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 39,
		},
		{
			.Move = MOVE_CALM_MIND,
			.Level = 43,
		},
		{
			.Move = MOVE_RECOVER,
			.Level = 46,
		},
		{
			.Move = MOVE_GUARD_SPLIT,
			.Level = 50,
		},
		{
			.Move = MOVE_POWER_SPLIT,
			.Level = 50,
		},
		{
			.Move = MOVE_SYNCHRONOISE,
			.Level = 53,
		},
		{
			.Move = MOVE_WONDER_ROOM,
			.Level = 56,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BEHEEYEM] = {
		{
			.Move = MOVE_WONDER_ROOM,
			.Level = 1,
		},
		{
			.Move = MOVE_SYNCHRONOISE,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_HEAL_BLOCK,
			.Level = 1,
		},
		{
			.Move = MOVE_MIRACLE_EYE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 4,
		},
		{
			.Move = MOVE_HEAL_BLOCK,
			.Level = 8,
		},
		{
			.Move = MOVE_MIRACLE_EYE,
			.Level = 11,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 15,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 18,
		},
		{
			.Move = MOVE_HIDDEN_POWER,
			.Level = 22,
		},
		{
			.Move = MOVE_IMPRISON,
			.Level = 25,
		},
		{
			.Move = MOVE_SIMPLE_BEAM,
			.Level = 29,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 32,
		},
		{
			.Move = MOVE_PSYCH_UP,
			.Level = 36,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 39,
		},
		{
			.Move = MOVE_CALM_MIND,
			.Level = 45,
		},
		{
			.Move = MOVE_RECOVER,
			.Level = 50,
		},
		{
			.Move = MOVE_GUARD_SPLIT,
			.Level = 56,
		},
		{
			.Move = MOVE_POWER_SPLIT,
			.Level = 58,
		},
		{
			.Move = MOVE_SYNCHRONOISE,
			.Level = 63,
		},
		{
			.Move = MOVE_WONDER_ROOM,
			.Level = 68,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_LITWICK] = {
		{
			.Move = MOVE_EMBER,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_MINIMIZE,
			.Level = 3,
		},
		{
			.Move = MOVE_SMOG,
			.Level = 5,
		},
		{
			.Move = MOVE_FIRE_SPIN,
			.Level = 7,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 10,
		},
		{
			.Move = MOVE_NIGHT_SHADE,
			.Level = 13,
		},
		{
			.Move = MOVE_WILLOWISP,
			.Level = 16,
		},
		{
			.Move = MOVE_FLAME_BURST,
			.Level = 20,
		},
		{
			.Move = MOVE_IMPRISON,
			.Level = 24,
		},
		{
			.Move = MOVE_HEX,
			.Level = 28,
		},
		{
			.Move = MOVE_MEMENTO,
			.Level = 33,
		},
		{
			.Move = MOVE_INFERNO,
			.Level = 38,
		},
		{
			.Move = MOVE_CURSE,
			.Level = 43,
		},
		{
			.Move = MOVE_SHADOW_BALL,
			.Level = 49,
		},
		{
			.Move = MOVE_PAIN_SPLIT,
			.Level = 55,
		},
		{
			.Move = MOVE_OVERHEAT,
			.Level = 61,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_LAMPENT] = {
		{
			.Move = MOVE_EMBER,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_MINIMIZE,
			.Level = 1,
		},
		{
			.Move = MOVE_SMOG,
			.Level = 1,
		},
		{
			.Move = MOVE_MINIMIZE,
			.Level = 3,
		},
		{
			.Move = MOVE_SMOG,
			.Level = 5,
		},
		{
			.Move = MOVE_FIRE_SPIN,
			.Level = 7,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 10,
		},
		{
			.Move = MOVE_NIGHT_SHADE,
			.Level = 13,
		},
		{
			.Move = MOVE_WILLOWISP,
			.Level = 16,
		},
		{
			.Move = MOVE_FLAME_BURST,
			.Level = 20,
		},
		{
			.Move = MOVE_IMPRISON,
			.Level = 24,
		},
		{
			.Move = MOVE_HEX,
			.Level = 28,
		},
		{
			.Move = MOVE_MEMENTO,
			.Level = 33,
		},
		{
			.Move = MOVE_INFERNO,
			.Level = 38,
		},
		{
			.Move = MOVE_CURSE,
			.Level = 45,
		},
		{
			.Move = MOVE_SHADOW_BALL,
			.Level = 53,
		},
		{
			.Move = MOVE_PAIN_SPLIT,
			.Level = 61,
		},
		{
			.Move = MOVE_OVERHEAT,
			.Level = 69,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CHANDELURE] = {
		{
			.Move = MOVE_PAIN_SPLIT,
			.Level = 1,
		},
		{
			.Move = MOVE_SMOG,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 1,
		},
		{
			.Move = MOVE_FLAME_BURST,
			.Level = 1,
		},
		{
			.Move = MOVE_HEX,
			.Level = 1,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_AXEW] = {
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 4,
		},
		{
			.Move = MOVE_ASSURANCE,
			.Level = 7,
		},
		{
			.Move = MOVE_DRAGON_RAGE,
			.Level = 10,
		},
		{
			.Move = MOVE_DUAL_CHOP,
			.Level = 13,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 16,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 20,
		},
		{
			.Move = MOVE_FALSE_SWIPE,
			.Level = 24,
		},
		{
			.Move = MOVE_DRAGON_CLAW,
			.Level = 28,
		},
		{
			.Move = MOVE_DRAGON_DANCE,
			.Level = 32,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 36,
		},
		{
			.Move = MOVE_DRAGON_PULSE,
			.Level = 41,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 46,
		},
		{
			.Move = MOVE_GUILLOTINE,
			.Level = 50,
		},
		{
			.Move = MOVE_OUTRAGE,
			.Level = 56,
		},
		{
			.Move = MOVE_GIGA_IMPACT,
			.Level = 61,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_FRAXURE] = {
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_ASSURANCE,
			.Level = 1,
		},
		{
			.Move = MOVE_DRAGON_RAGE,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 4,
		},
		{
			.Move = MOVE_ASSURANCE,
			.Level = 7,
		},
		{
			.Move = MOVE_DRAGON_RAGE,
			.Level = 10,
		},
		{
			.Move = MOVE_DUAL_CHOP,
			.Level = 13,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 16,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 20,
		},
		{
			.Move = MOVE_FALSE_SWIPE,
			.Level = 24,
		},
		{
			.Move = MOVE_DRAGON_CLAW,
			.Level = 28,
		},
		{
			.Move = MOVE_DRAGON_DANCE,
			.Level = 32,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 36,
		},
		{
			.Move = MOVE_DRAGON_PULSE,
			.Level = 42,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 48,
		},
		{
			.Move = MOVE_GUILLOTINE,
			.Level = 54,
		},
		{
			.Move = MOVE_OUTRAGE,
			.Level = 60,
		},
		{
			.Move = MOVE_GIGA_IMPACT,
			.Level = 66,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_HAXORUS] = {
		{
			.Move = MOVE_OUTRAGE,
			.Level = 1,
		},
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_ASSURANCE,
			.Level = 1,
		},
		{
			.Move = MOVE_DRAGON_RAGE,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 4,
		},
		{
			.Move = MOVE_ASSURANCE,
			.Level = 7,
		},
		{
			.Move = MOVE_DRAGON_RAGE,
			.Level = 10,
		},
		{
			.Move = MOVE_DUAL_CHOP,
			.Level = 13,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 16,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 20,
		},
		{
			.Move = MOVE_FALSE_SWIPE,
			.Level = 24,
		},
		{
			.Move = MOVE_DRAGON_CLAW,
			.Level = 28,
		},
		{
			.Move = MOVE_DRAGON_DANCE,
			.Level = 32,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 36,
		},
		{
			.Move = MOVE_DRAGON_PULSE,
			.Level = 42,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 50,
		},
		{
			.Move = MOVE_GUILLOTINE,
			.Level = 58,
		},
		{
			.Move = MOVE_OUTRAGE,
			.Level = 66,
		},
		{
			.Move = MOVE_GIGA_IMPACT,
			.Level = 74,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CUBCHOO] = {
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_POWDER_SNOW,
			.Level = 5,
		},
		{
			.Move = MOVE_BIDE,
			.Level = 9,
		},
		{
			.Move = MOVE_ICY_WIND,
			.Level = 13,
		},
		{
			.Move = MOVE_PLAY_NICE,
			.Level = 15,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 17,
		},
		{
			.Move = MOVE_BRINE,
			.Level = 21,
		},
		{
			.Move = MOVE_ENDURE,
			.Level = 25,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 29,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 33,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 36,
		},
		{
			.Move = MOVE_REST,
			.Level = 41,
		},
		{
			.Move = MOVE_BLIZZARD,
			.Level = 45,
		},
		{
			.Move = MOVE_HAIL,
			.Level = 49,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 53,
		},
		{
			.Move = MOVE_SHEER_COLD,
			.Level = 57,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BEARTIC] = {
		{
			.Move = MOVE_SHEER_COLD,
			.Level = 1,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 1,
		},
		{
			.Move = MOVE_SUPERPOWER,
			.Level = 1,
		},
		{
			.Move = MOVE_AQUA_JET,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_POWDER_SNOW,
			.Level = 1,
		},
		{
			.Move = MOVE_BIDE,
			.Level = 1,
		},
		{
			.Move = MOVE_ICY_WIND,
			.Level = 1,
		},
		{
			.Move = MOVE_PLAY_NICE,
			.Level = 9,
		},
		{
			.Move = MOVE_ICY_WIND,
			.Level = 13,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 17,
		},
		{
			.Move = MOVE_BRINE,
			.Level = 21,
		},
		{
			.Move = MOVE_ENDURE,
			.Level = 25,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 29,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 33,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 36,
		},
		{
			.Move = MOVE_ICICLE_CRASH,
			.Level = 37,
		},
		{
			.Move = MOVE_REST,
			.Level = 41,
		},
		{
			.Move = MOVE_BLIZZARD,
			.Level = 45,
		},
		{
			.Move = MOVE_HAIL,
			.Level = 53,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 59,
		},
		{
			.Move = MOVE_SHEER_COLD,
			.Level = 66,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CRYOGONAL] = {
		{
			.Move = MOVE_SHEER_COLD,
			.Level = 1,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 1,
		},
		{
			.Move = MOVE_ICE_SHARD,
			.Level = 1,
		},
		{
			.Move = MOVE_MIST,
			.Level = 1,
		},
		{
			.Move = MOVE_HAZE,
			.Level = 1,
		},
		{
			.Move = MOVE_BIND,
			.Level = 1,
		},
		{
			.Move = MOVE_ICE_SHARD,
			.Level = 5,
		},
		{
			.Move = MOVE_SHARPEN,
			.Level = 9,
		},
		{
			.Move = MOVE_RAPID_SPIN,
			.Level = 13,
		},
		{
			.Move = MOVE_ICY_WIND,
			.Level = 17,
		},
		{
			.Move = MOVE_MIST,
			.Level = 21,
		},
		{
			.Move = MOVE_HAZE,
			.Level = 21,
		},
		{
			.Move = MOVE_AURORA_BEAM,
			.Level = 25,
		},
		{
			.Move = MOVE_ACID_ARMOR,
			.Level = 29,
		},
		{
			.Move = MOVE_ICE_BEAM,
			.Level = 33,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 37,
		},
		{
			.Move = MOVE_REFLECT,
			.Level = 37,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 41,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 45,
		},
		{
			.Move = MOVE_RECOVER,
			.Level = 49,
		},
		{
			.Move = MOVE_FREEZEDRY,
			.Level = 50,
		},
		{
			.Move = MOVE_SOLARBEAM,
			.Level = 53,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 57,
		},
		{
			.Move = MOVE_SHEER_COLD,
			.Level = 61,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SHELMET] = {
		{
			.Move = MOVE_LEECH_LIFE,
			.Level = 1,
		},
		{
			.Move = MOVE_ACID,
			.Level = 4,
		},
		{
			.Move = MOVE_BIDE,
			.Level = 8,
		},
		{
			.Move = MOVE_CURSE,
			.Level = 13,
		},
		{
			.Move = MOVE_STRUGGLE_BUG,
			.Level = 16,
		},
		{
			.Move = MOVE_MEGA_DRAIN,
			.Level = 20,
		},
		{
			.Move = MOVE_YAWN,
			.Level = 25,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 28,
		},
		{
			.Move = MOVE_ACID_ARMOR,
			.Level = 32,
		},
		{
			.Move = MOVE_GIGA_DRAIN,
			.Level = 37,
		},
		{
			.Move = MOVE_BODY_SLAM,
			.Level = 40,
		},
		{
			.Move = MOVE_BUG_BUZZ,
			.Level = 44,
		},
		{
			.Move = MOVE_RECOVER,
			.Level = 49,
		},
		{
			.Move = MOVE_GUARD_SWAP,
			.Level = 50,
		},
		{
			.Move = MOVE_FINAL_GAMBIT,
			.Level = 56,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ACCELGOR] = {
		{
			.Move = MOVE_WATER_SHURIKEN,
			.Level = 1,
		},
		{
			.Move = MOVE_FINAL_GAMBIT,
			.Level = 1,
		},
		{
			.Move = MOVE_POWER_SWAP,
			.Level = 1,
		},
		{
			.Move = MOVE_LEECH_LIFE,
			.Level = 1,
		},
		{
			.Move = MOVE_ACID_SPRAY,
			.Level = 1,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_ACID_SPRAY,
			.Level = 4,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 8,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 13,
		},
		{
			.Move = MOVE_STRUGGLE_BUG,
			.Level = 16,
		},
		{
			.Move = MOVE_MEGA_DRAIN,
			.Level = 20,
		},
		{
			.Move = MOVE_SWIFT,
			.Level = 25,
		},
		{
			.Move = MOVE_ME_FIRST,
			.Level = 28,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 32,
		},
		{
			.Move = MOVE_GIGA_DRAIN,
			.Level = 37,
		},
		{
			.Move = MOVE_UTURN,
			.Level = 40,
		},
		{
			.Move = MOVE_BUG_BUZZ,
			.Level = 44,
		},
		{
			.Move = MOVE_RECOVER,
			.Level = 49,
		},
		{
			.Move = MOVE_POWER_SWAP,
			.Level = 52,
		},
		{
			.Move = MOVE_FINAL_GAMBIT,
			.Level = 56,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_STUNFISK] = {
		{
			.Move = MOVE_FISSURE,
			.Level = 1,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 1,
		},
		{
			.Move = MOVE_MUD_SPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_BIDE,
			.Level = 5,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 9,
		},
		{
			.Move = MOVE_MUD_SHOT,
			.Level = 13,
		},
		{
			.Move = MOVE_CAMOUFLAGE,
			.Level = 17,
		},
		{
			.Move = MOVE_MUD_BOMB,
			.Level = 21,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 25,
		},
		{
			.Move = MOVE_ENDURE,
			.Level = 30,
		},
		{
			.Move = MOVE_BOUNCE,
			.Level = 35,
		},
		{
			.Move = MOVE_MUDDY_WATER,
			.Level = 40,
		},
		{
			.Move = MOVE_THUNDERBOLT,
			.Level = 45,
		},
		{
			.Move = MOVE_REVENGE,
			.Level = 50,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 55,
		},
		{
			.Move = MOVE_FISSURE,
			.Level = 61,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MIENFOO] = {
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_MEDITATE,
			.Level = 5,
		},
		{
			.Move = MOVE_DETECT,
			.Level = 9,
		},
		{
			.Move = MOVE_FAKE_OUT,
			.Level = 13,
		},
		{
			.Move = MOVE_DOUBLESLAP,
			.Level = 17,
		},
		{
			.Move = MOVE_SWIFT,
			.Level = 21,
		},
		{
			.Move = MOVE_CALM_MIND,
			.Level = 25,
		},
		{
			.Move = MOVE_FORCE_PALM,
			.Level = 29,
		},
		{
			.Move = MOVE_DRAIN_PUNCH,
			.Level = 33,
		},
		{
			.Move = MOVE_JUMP_KICK,
			.Level = 37,
		},
		{
			.Move = MOVE_UTURN,
			.Level = 41,
		},
		{
			.Move = MOVE_QUICK_GUARD,
			.Level = 45,
		},
		{
			.Move = MOVE_BOUNCE,
			.Level = 49,
		},
		{
			.Move = MOVE_HI_JUMP_KICK,
			.Level = 50,
		},
		{
			.Move = MOVE_REVERSAL,
			.Level = 57,
		},
		{
			.Move = MOVE_AURA_SPHERE,
			.Level = 61,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MIENSHAO] = {
		{
			.Move = MOVE_AURA_SPHERE,
			.Level = 1,
		},
		{
			.Move = MOVE_REVERSAL,
			.Level = 1,
		},
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_MEDITATE,
			.Level = 1,
		},
		{
			.Move = MOVE_DETECT,
			.Level = 1,
		},
		{
			.Move = MOVE_FAKE_OUT,
			.Level = 1,
		},
		{
			.Move = MOVE_MEDITATE,
			.Level = 5,
		},
		{
			.Move = MOVE_DETECT,
			.Level = 9,
		},
		{
			.Move = MOVE_FAKE_OUT,
			.Level = 13,
		},
		{
			.Move = MOVE_DOUBLESLAP,
			.Level = 17,
		},
		{
			.Move = MOVE_SWIFT,
			.Level = 21,
		},
		{
			.Move = MOVE_CALM_MIND,
			.Level = 25,
		},
		{
			.Move = MOVE_FORCE_PALM,
			.Level = 29,
		},
		{
			.Move = MOVE_DRAIN_PUNCH,
			.Level = 33,
		},
		{
			.Move = MOVE_JUMP_KICK,
			.Level = 37,
		},
		{
			.Move = MOVE_UTURN,
			.Level = 41,
		},
		{
			.Move = MOVE_WIDE_GUARD,
			.Level = 45,
		},
		{
			.Move = MOVE_BOUNCE,
			.Level = 49,
		},
		{
			.Move = MOVE_HI_JUMP_KICK,
			.Level = 56,
		},
		{
			.Move = MOVE_REVERSAL,
			.Level = 63,
		},
		{
			.Move = MOVE_AURA_SPHERE,
			.Level = 70,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_DRUDDIGON] = {
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_HONE_CLAWS,
			.Level = 5,
		},
		{
			.Move = MOVE_BITE,
			.Level = 9,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 13,
		},
		{
			.Move = MOVE_DRAGON_RAGE,
			.Level = 18,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 21,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 25,
		},
		{
			.Move = MOVE_DRAGON_CLAW,
			.Level = 27,
		},
		{
			.Move = MOVE_CHIP_AWAY,
			.Level = 31,
		},
		{
			.Move = MOVE_REVENGE,
			.Level = 35,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 40,
		},
		{
			.Move = MOVE_DRAGON_TAIL,
			.Level = 45,
		},
		{
			.Move = MOVE_ROCK_CLIMB,
			.Level = 49,
		},
		{
			.Move = MOVE_SUPERPOWER,
			.Level = 55,
		},
		{
			.Move = MOVE_OUTRAGE,
			.Level = 62,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GOLETT] = {
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 1,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 5,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 9,
		},
		{
			.Move = MOVE_SHADOW_PUNCH,
			.Level = 13,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 17,
		},
		{
			.Move = MOVE_MEGA_PUNCH,
			.Level = 21,
		},
		{
			.Move = MOVE_MAGNITUDE,
			.Level = 25,
		},
		{
			.Move = MOVE_DYNAMICPUNCH,
			.Level = 30,
		},
		{
			.Move = MOVE_NIGHT_SHADE,
			.Level = 35,
		},
		{
			.Move = MOVE_CURSE,
			.Level = 40,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 45,
		},
		{
			.Move = MOVE_HAMMER_ARM,
			.Level = 50,
		},
		{
			.Move = MOVE_FOCUS_PUNCH,
			.Level = 55,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GOLURK] = {
		{
			.Move = MOVE_PHANTOM_FORCE,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_PUNCH,
			.Level = 1,
		},
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 1,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 1,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 5,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 9,
		},
		{
			.Move = MOVE_SHADOW_PUNCH,
			.Level = 13,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 17,
		},
		{
			.Move = MOVE_MEGA_PUNCH,
			.Level = 21,
		},
		{
			.Move = MOVE_MAGNITUDE,
			.Level = 25,
		},
		{
			.Move = MOVE_DYNAMICPUNCH,
			.Level = 30,
		},
		{
			.Move = MOVE_NIGHT_SHADE,
			.Level = 35,
		},
		{
			.Move = MOVE_CURSE,
			.Level = 40,
		},
		{
			.Move = MOVE_HEAVY_SLAM,
			.Level = 43,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 50,
		},
		{
			.Move = MOVE_HAMMER_ARM,
			.Level = 60,
		},
		{
			.Move = MOVE_FOCUS_PUNCH,
			.Level = 70,
		},
		{
			.Move = MOVE_PHANTOM_FORCE,
			.Level = 75,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PAWNIARD] = {
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 6,
		},
		{
			.Move = MOVE_FURY_CUTTER,
			.Level = 9,
		},
		{
			.Move = MOVE_TORMENT,
			.Level = 14,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 17,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 22,
		},
		{
			.Move = MOVE_METAL_CLAW,
			.Level = 25,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 30,
		},
		{
			.Move = MOVE_ASSURANCE,
			.Level = 33,
		},
		{
			.Move = MOVE_METAL_SOUND,
			.Level = 38,
		},
		{
			.Move = MOVE_EMBARGO,
			.Level = 41,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 46,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 49,
		},
		{
			.Move = MOVE_IRON_HEAD,
			.Level = 54,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 57,
		},
		{
			.Move = MOVE_GUILLOTINE,
			.Level = 62,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BISHARP] = {
		{
			.Move = MOVE_GUILLOTINE,
			.Level = 1,
		},
		{
			.Move = MOVE_IRON_HEAD,
			.Level = 1,
		},
		{
			.Move = MOVE_METAL_BURST,
			.Level = 1,
		},
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_FURY_CUTTER,
			.Level = 1,
		},
		{
			.Move = MOVE_TORMENT,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 6,
		},
		{
			.Move = MOVE_FURY_CUTTER,
			.Level = 9,
		},
		{
			.Move = MOVE_TORMENT,
			.Level = 14,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 17,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 22,
		},
		{
			.Move = MOVE_METAL_CLAW,
			.Level = 25,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 30,
		},
		{
			.Move = MOVE_ASSURANCE,
			.Level = 33,
		},
		{
			.Move = MOVE_METAL_SOUND,
			.Level = 38,
		},
		{
			.Move = MOVE_EMBARGO,
			.Level = 41,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 46,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 49,
		},
		{
			.Move = MOVE_IRON_HEAD,
			.Level = 57,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 63,
		},
		{
			.Move = MOVE_GUILLOTINE,
			.Level = 71,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BOUFFALANT] = {
		{
			.Move = MOVE_PURSUIT,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_RAGE,
			.Level = 6,
		},
		{
			.Move = MOVE_FURY_ATTACK,
			.Level = 11,
		},
		{
			.Move = MOVE_HORN_ATTACK,
			.Level = 16,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 21,
		},
		{
			.Move = MOVE_REVENGE,
			.Level = 26,
		},
		{
			.Move = MOVE_HEAD_CHARGE,
			.Level = 31,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 36,
		},
		{
			.Move = MOVE_MEGAHORN,
			.Level = 41,
		},
		{
			.Move = MOVE_REVERSAL,
			.Level = 46,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 50,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 56,
		},
		{
			.Move = MOVE_GIGA_IMPACT,
			.Level = 61,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_RUFFLET] = {
		{
			.Move = MOVE_PECK,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_FURY_ATTACK,
			.Level = 5,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 10,
		},
		{
			.Move = MOVE_HONE_CLAWS,
			.Level = 14,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 19,
		},
		{
			.Move = MOVE_AERIAL_ACE,
			.Level = 23,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 28,
		},
		{
			.Move = MOVE_DEFOG,
			.Level = 32,
		},
		{
			.Move = MOVE_TAILWIND,
			.Level = 37,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 41,
		},
		{
			.Move = MOVE_CRUSH_CLAW,
			.Level = 46,
		},
		{
			.Move = MOVE_SKY_DROP,
			.Level = 50,
		},
		{
			.Move = MOVE_WHIRLWIND,
			.Level = 55,
		},
		{
			.Move = MOVE_BRAVE_BIRD,
			.Level = 59,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 64,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BRAVIARY] = {
		{
			.Move = MOVE_THRASH,
			.Level = 1,
		},
		{
			.Move = MOVE_BRAVE_BIRD,
			.Level = 1,
		},
		{
			.Move = MOVE_WHIRLWIND,
			.Level = 1,
		},
		{
			.Move = MOVE_SUPERPOWER,
			.Level = 1,
		},
		{
			.Move = MOVE_PECK,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_FURY_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_FURY_ATTACK,
			.Level = 5,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 10,
		},
		{
			.Move = MOVE_HONE_CLAWS,
			.Level = 14,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 19,
		},
		{
			.Move = MOVE_AERIAL_ACE,
			.Level = 23,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 28,
		},
		{
			.Move = MOVE_DEFOG,
			.Level = 32,
		},
		{
			.Move = MOVE_TAILWIND,
			.Level = 37,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 41,
		},
		{
			.Move = MOVE_CRUSH_CLAW,
			.Level = 46,
		},
		{
			.Move = MOVE_SKY_DROP,
			.Level = 50,
		},
		{
			.Move = MOVE_SUPERPOWER,
			.Level = 51,
		},
		{
			.Move = MOVE_WHIRLWIND,
			.Level = 57,
		},
		{
			.Move = MOVE_BRAVE_BIRD,
			.Level = 63,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 70,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_VULLABY] = {
		{
			.Move = MOVE_GUST,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_FURY_ATTACK,
			.Level = 5,
		},
		{
			.Move = MOVE_PLUCK,
			.Level = 10,
		},
		{
			.Move = MOVE_NASTY_PLOT,
			.Level = 14,
		},
		{
			.Move = MOVE_FLATTER,
			.Level = 19,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 23,
		},
		{
			.Move = MOVE_PUNISHMENT,
			.Level = 28,
		},
		{
			.Move = MOVE_DEFOG,
			.Level = 32,
		},
		{
			.Move = MOVE_TAILWIND,
			.Level = 37,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 41,
		},
		{
			.Move = MOVE_DARK_PULSE,
			.Level = 46,
		},
		{
			.Move = MOVE_EMBARGO,
			.Level = 50,
		},
		{
			.Move = MOVE_WHIRLWIND,
			.Level = 55,
		},
		{
			.Move = MOVE_BRAVE_BIRD,
			.Level = 59,
		},
		{
			.Move = MOVE_MIRROR_MOVE,
			.Level = 64,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MANDIBUZZ] = {
		{
			.Move = MOVE_MIRROR_MOVE,
			.Level = 1,
		},
		{
			.Move = MOVE_BRAVE_BIRD,
			.Level = 1,
		},
		{
			.Move = MOVE_WHIRLWIND,
			.Level = 1,
		},
		{
			.Move = MOVE_BONE_RUSH,
			.Level = 1,
		},
		{
			.Move = MOVE_GUST,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_FURY_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_PLUCK,
			.Level = 1,
		},
		{
			.Move = MOVE_FURY_ATTACK,
			.Level = 5,
		},
		{
			.Move = MOVE_PLUCK,
			.Level = 10,
		},
		{
			.Move = MOVE_NASTY_PLOT,
			.Level = 14,
		},
		{
			.Move = MOVE_FLATTER,
			.Level = 19,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 23,
		},
		{
			.Move = MOVE_PUNISHMENT,
			.Level = 28,
		},
		{
			.Move = MOVE_DEFOG,
			.Level = 32,
		},
		{
			.Move = MOVE_TAILWIND,
			.Level = 37,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 41,
		},
		{
			.Move = MOVE_DARK_PULSE,
			.Level = 46,
		},
		{
			.Move = MOVE_EMBARGO,
			.Level = 50,
		},
		{
			.Move = MOVE_BONE_RUSH,
			.Level = 51,
		},
		{
			.Move = MOVE_WHIRLWIND,
			.Level = 57,
		},
		{
			.Move = MOVE_BRAVE_BIRD,
			.Level = 63,
		},
		{
			.Move = MOVE_MIRROR_MOVE,
			.Level = 70,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_HEATMOR] = {
		{
			.Move = MOVE_INFERNO,
			.Level = 1,
		},
		{
			.Move = MOVE_HONE_CLAWS,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_INCINERATE,
			.Level = 1,
		},
		{
			.Move = MOVE_LICK,
			.Level = 1,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 6,
		},
		{
			.Move = MOVE_BIND,
			.Level = 11,
		},
		{
			.Move = MOVE_FIRE_SPIN,
			.Level = 16,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 21,
		},
		{
			.Move = MOVE_SNATCH,
			.Level = 26,
		},
		{
			.Move = MOVE_FLAME_BURST,
			.Level = 31,
		},
		{
			.Move = MOVE_BUG_BITE,
			.Level = 36,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 41,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 44,
		},
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 47,
		},
		{
			.Move = MOVE_STOCKPILE,
			.Level = 50,
		},
		{
			.Move = MOVE_SPIT_UP,
			.Level = 50,
		},
		{
			.Move = MOVE_SWALLOW,
			.Level = 50,
		},
		{
			.Move = MOVE_INFERNO,
			.Level = 61,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_DURANT] = {
		{
			.Move = MOVE_GUILLOTINE,
			.Level = 1,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 1,
		},
		{
			.Move = MOVE_METAL_SOUND,
			.Level = 1,
		},
		{
			.Move = MOVE_VICEGRIP,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_FURY_CUTTER,
			.Level = 6,
		},
		{
			.Move = MOVE_BITE,
			.Level = 11,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 16,
		},
		{
			.Move = MOVE_METAL_CLAW,
			.Level = 21,
		},
		{
			.Move = MOVE_BUG_BITE,
			.Level = 26,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 31,
		},
		{
			.Move = MOVE_IRON_HEAD,
			.Level = 36,
		},
		{
			.Move = MOVE_DIG,
			.Level = 41,
		},
		{
			.Move = MOVE_ENTRAINMENT,
			.Level = 46,
		},
		{
			.Move = MOVE_XSCISSOR,
			.Level = 51,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 56,
		},
		{
			.Move = MOVE_GUILLOTINE,
			.Level = 61,
		},
		{
			.Move = MOVE_METAL_SOUND,
			.Level = 66,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_DEINO] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_DRAGON_RAGE,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 4,
		},
		{
			.Move = MOVE_BITE,
			.Level = 9,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 12,
		},
		{
			.Move = MOVE_DRAGONBREATH,
			.Level = 17,
		},
		{
			.Move = MOVE_ROAR,
			.Level = 20,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 25,
		},
		{
			.Move = MOVE_SLAM,
			.Level = 28,
		},
		{
			.Move = MOVE_DRAGON_PULSE,
			.Level = 32,
		},
		{
			.Move = MOVE_WORK_UP,
			.Level = 38,
		},
		{
			.Move = MOVE_DRAGON_RUSH,
			.Level = 42,
		},
		{
			.Move = MOVE_BODY_SLAM,
			.Level = 48,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 50,
		},
		{
			.Move = MOVE_HYPER_VOICE,
			.Level = 58,
		},
		{
			.Move = MOVE_OUTRAGE,
			.Level = 62,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ZWEILOUS] = {
		{
			.Move = MOVE_DOUBLE_HIT,
			.Level = 1,
		},
		{
			.Move = MOVE_DRAGON_RAGE,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 4,
		},
		{
			.Move = MOVE_BITE,
			.Level = 9,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 12,
		},
		{
			.Move = MOVE_DRAGONBREATH,
			.Level = 17,
		},
		{
			.Move = MOVE_ROAR,
			.Level = 20,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 25,
		},
		{
			.Move = MOVE_SLAM,
			.Level = 28,
		},
		{
			.Move = MOVE_DRAGON_PULSE,
			.Level = 32,
		},
		{
			.Move = MOVE_WORK_UP,
			.Level = 38,
		},
		{
			.Move = MOVE_DRAGON_RUSH,
			.Level = 42,
		},
		{
			.Move = MOVE_BODY_SLAM,
			.Level = 48,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 55,
		},
		{
			.Move = MOVE_HYPER_VOICE,
			.Level = 64,
		},
		{
			.Move = MOVE_OUTRAGE,
			.Level = 71,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_HYDREIGON] = {
		{
			.Move = MOVE_OUTRAGE,
			.Level = 1,
		},
		{
			.Move = MOVE_HYPER_VOICE,
			.Level = 1,
		},
		{
			.Move = MOVE_TRI_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_DRAGON_RAGE,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 4,
		},
		{
			.Move = MOVE_BITE,
			.Level = 9,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 12,
		},
		{
			.Move = MOVE_DRAGONBREATH,
			.Level = 17,
		},
		{
			.Move = MOVE_ROAR,
			.Level = 20,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 25,
		},
		{
			.Move = MOVE_SLAM,
			.Level = 28,
		},
		{
			.Move = MOVE_DRAGON_PULSE,
			.Level = 32,
		},
		{
			.Move = MOVE_WORK_UP,
			.Level = 38,
		},
		{
			.Move = MOVE_DRAGON_RUSH,
			.Level = 42,
		},
		{
			.Move = MOVE_BODY_SLAM,
			.Level = 48,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 55,
		},
		{
			.Move = MOVE_HYPER_VOICE,
			.Level = 68,
		},
		{
			.Move = MOVE_OUTRAGE,
			.Level = 79,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_LARVESTA] = {
		{
			.Move = MOVE_EMBER,
			.Level = 1,
		},
		{
			.Move = MOVE_STRING_SHOT,
			.Level = 1,
		},
		{
			.Move = MOVE_LEECH_LIFE,
			.Level = 10,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 20,
		},
		{
			.Move = MOVE_FLAME_CHARGE,
			.Level = 30,
		},
		{
			.Move = MOVE_BUG_BITE,
			.Level = 40,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 50,
		},
		{
			.Move = MOVE_FLAME_WHEEL,
			.Level = 60,
		},
		{
			.Move = MOVE_BUG_BUZZ,
			.Level = 70,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 80,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 90,
		},
		{
			.Move = MOVE_FLARE_BLITZ,
			.Level = 100,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_VOLCARONA] = {
		{
			.Move = MOVE_FIERY_DANCE,
			.Level = 1,
		},
		{
			.Move = MOVE_HURRICANE,
			.Level = 1,
		},
		{
			.Move = MOVE_RAGE_POWDER,
			.Level = 1,
		},
		{
			.Move = MOVE_HEAT_WAVE,
			.Level = 1,
		},
		{
			.Move = MOVE_QUIVER_DANCE,
			.Level = 1,
		},
		{
			.Move = MOVE_FLARE_BLITZ,
			.Level = 1,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 1,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 1,
		},
		{
			.Move = MOVE_BUG_BUZZ,
			.Level = 1,
		},
		{
			.Move = MOVE_FLAME_WHEEL,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 1,
		},
		{
			.Move = MOVE_STRING_SHOT,
			.Level = 1,
		},
		{
			.Move = MOVE_LEECH_LIFE,
			.Level = 1,
		},
		{
			.Move = MOVE_GUST,
			.Level = 1,
		},
		{
			.Move = MOVE_LEECH_LIFE,
			.Level = 10,
		},
		{
			.Move = MOVE_GUST,
			.Level = 20,
		},
		{
			.Move = MOVE_FIRE_SPIN,
			.Level = 30,
		},
		{
			.Move = MOVE_WHIRLWIND,
			.Level = 40,
		},
		{
			.Move = MOVE_SILVER_WIND,
			.Level = 50,
		},
		{
			.Move = MOVE_QUIVER_DANCE,
			.Level = 59,
		},
		{
			.Move = MOVE_HEAT_WAVE,
			.Level = 60,
		},
		{
			.Move = MOVE_BUG_BUZZ,
			.Level = 70,
		},
		{
			.Move = MOVE_RAGE_POWDER,
			.Level = 80,
		},
		{
			.Move = MOVE_HURRICANE,
			.Level = 90,
		},
		{
			.Move = MOVE_FIERY_DANCE,
			.Level = 100,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_COBALION] = {
		{
			.Move = MOVE_CLOSE_COMBAT,
			.Level = 1,
		},
		{
			.Move = MOVE_METAL_BURST,
			.Level = 1,
		},
		{
			.Move = MOVE_WORK_UP,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_GUARD,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_DOUBLE_KICK,
			.Level = 7,
		},
		{
			.Move = MOVE_METAL_CLAW,
			.Level = 13,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 19,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 25,
		},
		{
			.Move = MOVE_RETALIATE,
			.Level = 31,
		},
		{
			.Move = MOVE_IRON_HEAD,
			.Level = 37,
		},
		{
			.Move = MOVE_SACRED_SWORD,
			.Level = 42,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 49,
		},
		{
			.Move = MOVE_QUICK_GUARD,
			.Level = 55,
		},
		{
			.Move = MOVE_WORK_UP,
			.Level = 61,
		},
		{
			.Move = MOVE_METAL_BURST,
			.Level = 67,
		},
		{
			.Move = MOVE_CLOSE_COMBAT,
			.Level = 73,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_TERRAKION] = {
		{
			.Move = MOVE_CLOSE_COMBAT,
			.Level = 1,
		},
		{
			.Move = MOVE_WORK_UP,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_GUARD,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_DOUBLE_KICK,
			.Level = 7,
		},
		{
			.Move = MOVE_SMACK_DOWN,
			.Level = 13,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 19,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 25,
		},
		{
			.Move = MOVE_RETALIATE,
			.Level = 31,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 37,
		},
		{
			.Move = MOVE_SACRED_SWORD,
			.Level = 42,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 49,
		},
		{
			.Move = MOVE_QUICK_GUARD,
			.Level = 55,
		},
		{
			.Move = MOVE_WORK_UP,
			.Level = 61,
		},
		{
			.Move = MOVE_STONE_EDGE,
			.Level = 67,
		},
		{
			.Move = MOVE_CLOSE_COMBAT,
			.Level = 73,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_VIRIZION] = {
		{
			.Move = MOVE_CLOSE_COMBAT,
			.Level = 1,
		},
		{
			.Move = MOVE_LEAF_BLADE,
			.Level = 1,
		},
		{
			.Move = MOVE_WORK_UP,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_GUARD,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_DOUBLE_KICK,
			.Level = 7,
		},
		{
			.Move = MOVE_MAGICAL_LEAF,
			.Level = 13,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 19,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 25,
		},
		{
			.Move = MOVE_RETALIATE,
			.Level = 31,
		},
		{
			.Move = MOVE_GIGA_DRAIN,
			.Level = 37,
		},
		{
			.Move = MOVE_SACRED_SWORD,
			.Level = 42,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 49,
		},
		{
			.Move = MOVE_QUICK_GUARD,
			.Level = 55,
		},
		{
			.Move = MOVE_WORK_UP,
			.Level = 61,
		},
		{
			.Move = MOVE_LEAF_BLADE,
			.Level = 67,
		},
		{
			.Move = MOVE_CLOSE_COMBAT,
			.Level = 73,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_TORNADUS] = {
		{
			.Move = MOVE_THRASH,
			.Level = 1,
		},
		{
			.Move = MOVE_HAMMER_ARM,
			.Level = 1,
		},
		{
			.Move = MOVE_HURRICANE,
			.Level = 1,
		},
		{
			.Move = MOVE_TAILWIND,
			.Level = 1,
		},
		{
			.Move = MOVE_UPROAR,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_GUST,
			.Level = 1,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 7,
		},
		{
			.Move = MOVE_BITE,
			.Level = 13,
		},
		{
			.Move = MOVE_REVENGE,
			.Level = 19,
		},
		{
			.Move = MOVE_AIR_CUTTER,
			.Level = 25,
		},
		{
			.Move = MOVE_EXTRASENSORY,
			.Level = 31,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 37,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 43,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 49,
		},
		{
			.Move = MOVE_TAILWIND,
			.Level = 55,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 61,
		},
		{
			.Move = MOVE_HURRICANE,
			.Level = 67,
		},
		{
			.Move = MOVE_DARK_PULSE,
			.Level = 73,
		},
		{
			.Move = MOVE_HAMMER_ARM,
			.Level = 79,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 85,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_THUNDURUS] = {
		{
			.Move = MOVE_THRASH,
			.Level = 1,
		},
		{
			.Move = MOVE_HAMMER_ARM,
			.Level = 1,
		},
		{
			.Move = MOVE_NASTY_PLOT,
			.Level = 1,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 1,
		},
		{
			.Move = MOVE_UPROAR,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 1,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 7,
		},
		{
			.Move = MOVE_BITE,
			.Level = 13,
		},
		{
			.Move = MOVE_REVENGE,
			.Level = 19,
		},
		{
			.Move = MOVE_SHOCK_WAVE,
			.Level = 25,
		},
		{
			.Move = MOVE_HEAL_BLOCK,
			.Level = 31,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 37,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 43,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 49,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 55,
		},
		{
			.Move = MOVE_NASTY_PLOT,
			.Level = 61,
		},
		{
			.Move = MOVE_THUNDER,
			.Level = 67,
		},
		{
			.Move = MOVE_DARK_PULSE,
			.Level = 73,
		},
		{
			.Move = MOVE_HAMMER_ARM,
			.Level = 79,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 85,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_RESHIRAM] = {
		{
			.Move = MOVE_FIRE_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_DRAGON_RAGE,
			.Level = 1,
		},
		{
			.Move = MOVE_IMPRISON,
			.Level = 8,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 15,
		},
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 22,
		},
		{
			.Move = MOVE_DRAGONBREATH,
			.Level = 29,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 36,
		},
		{
			.Move = MOVE_EXTRASENSORY,
			.Level = 43,
		},
		{
			.Move = MOVE_FUSION_FLARE,
			.Level = 50,
		},
		{
			.Move = MOVE_DRAGON_PULSE,
			.Level = 54,
		},
		{
			.Move = MOVE_IMPRISON,
			.Level = 64,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 71,
		},
		{
			.Move = MOVE_FIRE_BLAST,
			.Level = 78,
		},
		{
			.Move = MOVE_OUTRAGE,
			.Level = 85,
		},
		{
			.Move = MOVE_HYPER_VOICE,
			.Level = 92,
		},
		{
			.Move = MOVE_BLUE_FLARE,
			.Level = 100,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ZEKROM] = {
		{
			.Move = MOVE_THUNDER_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_DRAGON_RAGE,
			.Level = 1,
		},
		{
			.Move = MOVE_IMPRISON,
			.Level = 8,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 15,
		},
		{
			.Move = MOVE_THUNDERBOLT,
			.Level = 22,
		},
		{
			.Move = MOVE_DRAGONBREATH,
			.Level = 29,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 36,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 43,
		},
		{
			.Move = MOVE_FUSION_BOLT,
			.Level = 50,
		},
		{
			.Move = MOVE_DRAGON_CLAW,
			.Level = 54,
		},
		{
			.Move = MOVE_IMPRISON,
			.Level = 64,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 71,
		},
		{
			.Move = MOVE_THUNDER,
			.Level = 78,
		},
		{
			.Move = MOVE_OUTRAGE,
			.Level = 85,
		},
		{
			.Move = MOVE_HYPER_VOICE,
			.Level = 92,
		},
		{
			.Move = MOVE_BOLT_STRIKE,
			.Level = 100,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_LANDORUS] = {
		{
			.Move = MOVE_OUTRAGE,
			.Level = 1,
		},
		{
			.Move = MOVE_HAMMER_ARM,
			.Level = 1,
		},
		{
			.Move = MOVE_FISSURE,
			.Level = 1,
		},
		{
			.Move = MOVE_BLOCK,
			.Level = 1,
		},
		{
			.Move = MOVE_MUD_SHOT,
			.Level = 1,
		},
		{
			.Move = MOVE_ROCK_TOMB,
			.Level = 1,
		},
		{
			.Move = MOVE_IMPRISON,
			.Level = 7,
		},
		{
			.Move = MOVE_PUNISHMENT,
			.Level = 13,
		},
		{
			.Move = MOVE_BULLDOZE,
			.Level = 19,
		},
		{
			.Move = MOVE_ROCK_THROW,
			.Level = 25,
		},
		{
			.Move = MOVE_EXTRASENSORY,
			.Level = 31,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 37,
		},
		{
			.Move = MOVE_EARTH_POWER,
			.Level = 43,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 49,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 55,
		},
		{
			.Move = MOVE_SANDSTORM,
			.Level = 61,
		},
		{
			.Move = MOVE_FISSURE,
			.Level = 67,
		},
		{
			.Move = MOVE_STONE_EDGE,
			.Level = 73,
		},
		{
			.Move = MOVE_HAMMER_ARM,
			.Level = 79,
		},
		{
			.Move = MOVE_OUTRAGE,
			.Level = 85,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_KYUREM] = {
		{
			.Move = MOVE_ICY_WIND,
			.Level = 1,
		},
		{
			.Move = MOVE_DRAGON_RAGE,
			.Level = 1,
		},
		{
			.Move = MOVE_IMPRISON,
			.Level = 8,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 15,
		},
		{
			.Move = MOVE_ICE_BEAM,
			.Level = 22,
		},
		{
			.Move = MOVE_DRAGONBREATH,
			.Level = 29,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 36,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 43,
		},
		{
			.Move = MOVE_GLACIATE,
			.Level = 50,
		},
		{
			.Move = MOVE_DRAGON_PULSE,
			.Level = 57,
		},
		{
			.Move = MOVE_IMPRISON,
			.Level = 64,
		},
		{
			.Move = MOVE_ENDEAVOR,
			.Level = 71,
		},
		{
			.Move = MOVE_BLIZZARD,
			.Level = 78,
		},
		{
			.Move = MOVE_OUTRAGE,
			.Level = 85,
		},
		{
			.Move = MOVE_HYPER_VOICE,
			.Level = 92,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_KELDEO] = {
		{
			.Move = MOVE_AQUA_JET,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_DOUBLE_KICK,
			.Level = 7,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 13,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 19,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 25,
		},
		{
			.Move = MOVE_RETALIATE,
			.Level = 31,
		},
		{
			.Move = MOVE_AQUA_TAIL,
			.Level = 37,
		},
		{
			.Move = MOVE_SACRED_SWORD,
			.Level = 43,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 49,
		},
		{
			.Move = MOVE_QUICK_GUARD,
			.Level = 55,
		},
		{
			.Move = MOVE_WORK_UP,
			.Level = 61,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 67,
		},
		{
			.Move = MOVE_CLOSE_COMBAT,
			.Level = 73,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MELOETTA] = {
		{
			.Move = MOVE_ROUND,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 6,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 11,
		},
		{
			.Move = MOVE_SING,
			.Level = 16,
		},
		{
			.Move = MOVE_TEETER_DANCE,
			.Level = 21,
		},
		{
			.Move = MOVE_ACROBATICS,
			.Level = 26,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 31,
		},
		{
			.Move = MOVE_ECHOED_VOICE,
			.Level = 36,
		},
		{
			.Move = MOVE_UTURN,
			.Level = 43,
		},
		{
			.Move = MOVE_WAKEUP_SLAP,
			.Level = 50,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 57,
		},
		{
			.Move = MOVE_HYPER_VOICE,
			.Level = 64,
		},
		{
			.Move = MOVE_ROLE_PLAY,
			.Level = 71,
		},
		{
			.Move = MOVE_CLOSE_COMBAT,
			.Level = 78,
		},
		{
			.Move = MOVE_PERISH_SONG,
			.Level = 85,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GENESECT] = {
		{
			.Move = MOVE_FELL_STINGER,
			.Level = 1,
		},
		{
			.Move = MOVE_TECHNO_BLAST,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_MAGNET_RISE,
			.Level = 1,
		},
		{
			.Move = MOVE_METAL_CLAW,
			.Level = 1,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 1,
		},
		{
			.Move = MOVE_FURY_CUTTER,
			.Level = 7,
		},
		{
			.Move = MOVE_LOCKON,
			.Level = 11,
		},
		{
			.Move = MOVE_FLAME_CHARGE,
			.Level = 18,
		},
		{
			.Move = MOVE_MAGNET_BOMB,
			.Level = 22,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 29,
		},
		{
			.Move = MOVE_METAL_SOUND,
			.Level = 33,
		},
		{
			.Move = MOVE_SIGNAL_BEAM,
			.Level = 40,
		},
		{
			.Move = MOVE_TRI_ATTACK,
			.Level = 44,
		},
		{
			.Move = MOVE_XSCISSOR,
			.Level = 51,
		},
		{
			.Move = MOVE_BUG_BUZZ,
			.Level = 55,
		},
		{
			.Move = MOVE_SIMPLE_BEAM,
			.Level = 62,
		},
		{
			.Move = MOVE_ZAP_CANNON,
			.Level = 66,
		},
		{
			.Move = MOVE_HYPER_BEAM,
			.Level = 73,
		},
		{
			.Move = MOVE_SELFDESTRUCT,
			.Level = 77,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CHESPIN] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_VINE_WHIP,
			.Level = 5,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 8,
		},
		{
			.Move = MOVE_BITE,
			.Level = 11,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 15,
		},
		{
			.Move = MOVE_PIN_MISSILE,
			.Level = 18,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 27,
		},
		{
			.Move = MOVE_SEED_BOMB,
			.Level = 32,
		},
		{
			.Move = MOVE_MUD_SHOT,
			.Level = 35,
		},
		{
			.Move = MOVE_BULK_UP,
			.Level = 39,
		},
		{
			.Move = MOVE_BODY_SLAM,
			.Level = 42,
		},
		{
			.Move = MOVE_PAIN_SPLIT,
			.Level = 45,
		},
		{
			.Move = MOVE_WOOD_HAMMER,
			.Level = 48,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_QUILLADIN] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_VINE_WHIP,
			.Level = 5,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 8,
		},
		{
			.Move = MOVE_BITE,
			.Level = 11,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 15,
		},
		{
			.Move = MOVE_PIN_MISSILE,
			.Level = 20,
		},
		{
			.Move = MOVE_NEEDLE_ARM,
			.Level = 26,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 30,
		},
		{
			.Move = MOVE_SEED_BOMB,
			.Level = 35,
		},
		{
			.Move = MOVE_MUD_SHOT,
			.Level = 39,
		},
		{
			.Move = MOVE_BULK_UP,
			.Level = 44,
		},
		{
			.Move = MOVE_BODY_SLAM,
			.Level = 48,
		},
		{
			.Move = MOVE_PAIN_SPLIT,
			.Level = 52,
		},
		{
			.Move = MOVE_WOOD_HAMMER,
			.Level = 55,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CHESNAUGHT] = {
		{
			.Move = MOVE_FEINT,
			.Level = 1,
		},
		{
			.Move = MOVE_HAMMER_ARM,
			.Level = 1,
		},
		{
			.Move = MOVE_BELLY_DRUM,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_VINE_WHIP,
			.Level = 5,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 8,
		},
		{
			.Move = MOVE_BITE,
			.Level = 11,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 15,
		},
		{
			.Move = MOVE_PIN_MISSILE,
			.Level = 20,
		},
		{
			.Move = MOVE_NEEDLE_ARM,
			.Level = 26,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 30,
		},
		{
			.Move = MOVE_SEED_BOMB,
			.Level = 35,
		},
		{
			.Move = MOVE_SPIKY_SHIELD,
			.Level = 36,
		},
		{
			.Move = MOVE_MUD_SHOT,
			.Level = 41,
		},
		{
			.Move = MOVE_BULK_UP,
			.Level = 44,
		},
		{
			.Move = MOVE_BODY_SLAM,
			.Level = 48,
		},
		{
			.Move = MOVE_PAIN_SPLIT,
			.Level = 52,
		},
		{
			.Move = MOVE_WOOD_HAMMER,
			.Level = 55,
		},
		{
			.Move = MOVE_HAMMER_ARM,
			.Level = 60,
		},
		{
			.Move = MOVE_GIGA_IMPACT,
			.Level = 70,
		},
		{
			.Move = MOVE_SPIKY_SHIELD,
			.Level = 75,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_FENNEKIN] = {
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 5,
		},
		{
			.Move = MOVE_HOWL,
			.Level = 11,
		},
		{
			.Move = MOVE_FLAME_CHARGE,
			.Level = 14,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 17,
		},
		{
			.Move = MOVE_FIRE_SPIN,
			.Level = 20,
		},
		{
			.Move = MOVE_LUCKY_CHANT,
			.Level = 25,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 27,
		},
		{
			.Move = MOVE_PSYSHOCK,
			.Level = 31,
		},
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 35,
		},
		{
			.Move = MOVE_WILLOWISP,
			.Level = 38,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 41,
		},
		{
			.Move = MOVE_SUNNY_DAY,
			.Level = 43,
		},
		{
			.Move = MOVE_MAGIC_ROOM,
			.Level = 46,
		},
		{
			.Move = MOVE_FIRE_BLAST,
			.Level = 48,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BRAIXEN] = {
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 5,
		},
		{
			.Move = MOVE_HOWL,
			.Level = 11,
		},
		{
			.Move = MOVE_FLAME_CHARGE,
			.Level = 14,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 18,
		},
		{
			.Move = MOVE_FIRE_SPIN,
			.Level = 22,
		},
		{
			.Move = MOVE_LUCKY_CHANT,
			.Level = 27,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 30,
		},
		{
			.Move = MOVE_PSYSHOCK,
			.Level = 34,
		},
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 41,
		},
		{
			.Move = MOVE_WILLOWISP,
			.Level = 45,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 48,
		},
		{
			.Move = MOVE_SUNNY_DAY,
			.Level = 51,
		},
		{
			.Move = MOVE_MAGIC_ROOM,
			.Level = 53,
		},
		{
			.Move = MOVE_FIRE_BLAST,
			.Level = 55,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_DELPHOX] = {
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 1,
		},
		{
			.Move = MOVE_ROLE_PLAY,
			.Level = 1,
		},
		{
			.Move = MOVE_SWITCHEROO,
			.Level = 1,
		},
		{
			.Move = MOVE_SHADOW_BALL,
			.Level = 1,
		},
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 5,
		},
		{
			.Move = MOVE_HOWL,
			.Level = 11,
		},
		{
			.Move = MOVE_FLAME_CHARGE,
			.Level = 14,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 18,
		},
		{
			.Move = MOVE_FIRE_SPIN,
			.Level = 22,
		},
		{
			.Move = MOVE_LUCKY_CHANT,
			.Level = 27,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 30,
		},
		{
			.Move = MOVE_PSYSHOCK,
			.Level = 34,
		},
		{
			.Move = MOVE_MYSTICAL_FIRE,
			.Level = 36,
		},
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 42,
		},
		{
			.Move = MOVE_WILLOWISP,
			.Level = 47,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 51,
		},
		{
			.Move = MOVE_SUNNY_DAY,
			.Level = 55,
		},
		{
			.Move = MOVE_MAGIC_ROOM,
			.Level = 58,
		},
		{
			.Move = MOVE_FIRE_BLAST,
			.Level = 61,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 69,
		},
		{
			.Move = MOVE_MYSTICAL_FIRE,
			.Level = 75,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_FROAKIE] = {
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_BUBBLE,
			.Level = 5,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 8,
		},
		{
			.Move = MOVE_LICK,
			.Level = 10,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 14,
		},
		{
			.Move = MOVE_SMOKESCREEN,
			.Level = 18,
		},
		{
			.Move = MOVE_ROUND,
			.Level = 21,
		},
		{
			.Move = MOVE_FLING,
			.Level = 25,
		},
		{
			.Move = MOVE_SMACK_DOWN,
			.Level = 29,
		},
		{
			.Move = MOVE_SUBSTITUTE,
			.Level = 35,
		},
		{
			.Move = MOVE_BOUNCE,
			.Level = 39,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 43,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 48,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_FROGADIER] = {
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_BUBBLE,
			.Level = 5,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 8,
		},
		{
			.Move = MOVE_LICK,
			.Level = 10,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 14,
		},
		{
			.Move = MOVE_SMOKESCREEN,
			.Level = 20,
		},
		{
			.Move = MOVE_ROUND,
			.Level = 23,
		},
		{
			.Move = MOVE_FLING,
			.Level = 28,
		},
		{
			.Move = MOVE_SMACK_DOWN,
			.Level = 33,
		},
		{
			.Move = MOVE_SUBSTITUTE,
			.Level = 38,
		},
		{
			.Move = MOVE_BOUNCE,
			.Level = 44,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 48,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 55,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GRENINJA] = {
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 1,
		},
		{
			.Move = MOVE_ROLE_PLAY,
			.Level = 1,
		},
		{
			.Move = MOVE_MAT_BLOCK,
			.Level = 1,
		},
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_BUBBLE,
			.Level = 5,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 8,
		},
		{
			.Move = MOVE_LICK,
			.Level = 10,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 14,
		},
		{
			.Move = MOVE_SMOKESCREEN,
			.Level = 20,
		},
		{
			.Move = MOVE_SHADOW_SNEAK,
			.Level = 23,
		},
		{
			.Move = MOVE_SPIKES,
			.Level = 28,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 33,
		},
		{
			.Move = MOVE_WATER_SHURIKEN,
			.Level = 36,
		},
		{
			.Move = MOVE_SUBSTITUTE,
			.Level = 43,
		},
		{
			.Move = MOVE_EXTRASENSORY,
			.Level = 49,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 52,
		},
		{
			.Move = MOVE_HAZE,
			.Level = 56,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 60,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 70,
		},
		{
			.Move = MOVE_WATER_SHURIKEN,
			.Level = 75,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BUNNELBY] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 7,
		},
		{
			.Move = MOVE_DOUBLESLAP,
			.Level = 10,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 13,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 15,
		},
		{
			.Move = MOVE_MUD_SHOT,
			.Level = 18,
		},
		{
			.Move = MOVE_DOUBLE_KICK,
			.Level = 20,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 25,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 29,
		},
		{
			.Move = MOVE_DIG,
			.Level = 33,
		},
		{
			.Move = MOVE_BOUNCE,
			.Level = 38,
		},
		{
			.Move = MOVE_SUPER_FANG,
			.Level = 42,
		},
		{
			.Move = MOVE_FACADE,
			.Level = 47,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 49,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_DIGGERSBY] = {
		{
			.Move = MOVE_HAMMER_ARM,
			.Level = 1,
		},
		{
			.Move = MOVE_ROTOTILLER,
			.Level = 1,
		},
		{
			.Move = MOVE_BULLDOZE,
			.Level = 1,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 7,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 13,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 15,
		},
		{
			.Move = MOVE_MUD_SHOT,
			.Level = 18,
		},
		{
			.Move = MOVE_DOUBLE_KICK,
			.Level = 20,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 26,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 31,
		},
		{
			.Move = MOVE_DIG,
			.Level = 37,
		},
		{
			.Move = MOVE_BOUNCE,
			.Level = 42,
		},
		{
			.Move = MOVE_SUPER_FANG,
			.Level = 48,
		},
		{
			.Move = MOVE_FACADE,
			.Level = 53,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 57,
		},
		{
			.Move = MOVE_HAMMER_ARM,
			.Level = 60,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_FLETCHLING] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 6,
		},
		{
			.Move = MOVE_PECK,
			.Level = 10,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 13,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 16,
		},
		{
			.Move = MOVE_ROOST,
			.Level = 21,
		},
		{
			.Move = MOVE_RAZOR_WIND,
			.Level = 25,
		},
		{
			.Move = MOVE_NATURAL_GIFT,
			.Level = 29,
		},
		{
			.Move = MOVE_FLAME_CHARGE,
			.Level = 34,
		},
		{
			.Move = MOVE_ACROBATICS,
			.Level = 39,
		},
		{
			.Move = MOVE_ME_FIRST,
			.Level = 41,
		},
		{
			.Move = MOVE_TAILWIND,
			.Level = 45,
		},
		{
			.Move = MOVE_STEEL_WING,
			.Level = 48,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_FLETCHINDER] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 6,
		},
		{
			.Move = MOVE_PECK,
			.Level = 10,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 13,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 16,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 17,
		},
		{
			.Move = MOVE_ROOST,
			.Level = 25,
		},
		{
			.Move = MOVE_RAZOR_WIND,
			.Level = 27,
		},
		{
			.Move = MOVE_NATURAL_GIFT,
			.Level = 31,
		},
		{
			.Move = MOVE_FLAME_CHARGE,
			.Level = 38,
		},
		{
			.Move = MOVE_ACROBATICS,
			.Level = 42,
		},
		{
			.Move = MOVE_ME_FIRST,
			.Level = 46,
		},
		{
			.Move = MOVE_TAILWIND,
			.Level = 51,
		},
		{
			.Move = MOVE_STEEL_WING,
			.Level = 55,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_TALONFLAME] = {
		{
			.Move = MOVE_BRAVE_BIRD,
			.Level = 1,
		},
		{
			.Move = MOVE_FLARE_BLITZ,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 6,
		},
		{
			.Move = MOVE_PECK,
			.Level = 10,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 13,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 16,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 17,
		},
		{
			.Move = MOVE_ROOST,
			.Level = 25,
		},
		{
			.Move = MOVE_RAZOR_WIND,
			.Level = 27,
		},
		{
			.Move = MOVE_NATURAL_GIFT,
			.Level = 31,
		},
		{
			.Move = MOVE_FLAME_CHARGE,
			.Level = 39,
		},
		{
			.Move = MOVE_ACROBATICS,
			.Level = 44,
		},
		{
			.Move = MOVE_ME_FIRST,
			.Level = 49,
		},
		{
			.Move = MOVE_TAILWIND,
			.Level = 55,
		},
		{
			.Move = MOVE_STEEL_WING,
			.Level = 60,
		},
		{
			.Move = MOVE_BRAVE_BIRD,
			.Level = 64,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SCATTERBUG] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_STRING_SHOT,
			.Level = 1,
		},
		{
			.Move = MOVE_STUN_SPORE,
			.Level = 6,
		},
		{
			.Move = MOVE_BUG_BITE,
			.Level = 15,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SPEWPA] = {
		{
			.Move = MOVE_HARDEN,
			.Level = 1,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 9,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_VIVILLON] = {
		{
			.Move = MOVE_POWDER,
			.Level = 1,
		},
		{
			.Move = MOVE_SLEEP_POWDER,
			.Level = 1,
		},
		{
			.Move = MOVE_POISONPOWDER,
			.Level = 1,
		},
		{
			.Move = MOVE_STUN_SPORE,
			.Level = 1,
		},
		{
			.Move = MOVE_GUST,
			.Level = 1,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 1,
		},
		{
			.Move = MOVE_STRUGGLE_BUG,
			.Level = 12,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 17,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 21,
		},
		{
			.Move = MOVE_DRAINING_KISS,
			.Level = 25,
		},
		{
			.Move = MOVE_AROMATHERAPY,
			.Level = 31,
		},
		{
			.Move = MOVE_BUG_BUZZ,
			.Level = 35,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 41,
		},
		{
			.Move = MOVE_QUIVER_DANCE,
			.Level = 45,
		},
		{
			.Move = MOVE_HURRICANE,
			.Level = 50,
		},
		{
			.Move = MOVE_POWDER,
			.Level = 55,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_LITLEO] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 5,
		},
		{
			.Move = MOVE_WORK_UP,
			.Level = 8,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 11,
		},
		{
			.Move = MOVE_NOBLE_ROAR,
			.Level = 15,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 20,
		},
		{
			.Move = MOVE_FIRE_FANG,
			.Level = 23,
		},
		{
			.Move = MOVE_ENDEAVOR,
			.Level = 28,
		},
		{
			.Move = MOVE_ECHOED_VOICE,
			.Level = 33,
		},
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 36,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 39,
		},
		{
			.Move = MOVE_HYPER_VOICE,
			.Level = 43,
		},
		{
			.Move = MOVE_INCINERATE,
			.Level = 46,
		},
		{
			.Move = MOVE_OVERHEAT,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PYROAR] = {
		{
			.Move = MOVE_HYPER_BEAM,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 5,
		},
		{
			.Move = MOVE_WORK_UP,
			.Level = 8,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 11,
		},
		{
			.Move = MOVE_NOBLE_ROAR,
			.Level = 15,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 20,
		},
		{
			.Move = MOVE_FIRE_FANG,
			.Level = 23,
		},
		{
			.Move = MOVE_ENDEAVOR,
			.Level = 28,
		},
		{
			.Move = MOVE_ECHOED_VOICE,
			.Level = 33,
		},
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 38,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 42,
		},
		{
			.Move = MOVE_HYPER_VOICE,
			.Level = 48,
		},
		{
			.Move = MOVE_INCINERATE,
			.Level = 51,
		},
		{
			.Move = MOVE_OVERHEAT,
			.Level = 57,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_FLABEBE] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_VINE_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_FAIRY_WIND,
			.Level = 6,
		},
		{
			.Move = MOVE_LUCKY_CHANT,
			.Level = 10,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 15,
		},
		{
			.Move = MOVE_WISH,
			.Level = 20,
		},
		{
			.Move = MOVE_MAGICAL_LEAF,
			.Level = 22,
		},
		{
			.Move = MOVE_GRASSY_TERRAIN,
			.Level = 24,
		},
		{
			.Move = MOVE_PETAL_BLIZZARD,
			.Level = 28,
		},
		{
			.Move = MOVE_AROMATHERAPY,
			.Level = 33,
		},
		{
			.Move = MOVE_MISTY_TERRAIN,
			.Level = 37,
		},
		{
			.Move = MOVE_MOONBLAST,
			.Level = 41,
		},
		{
			.Move = MOVE_PETAL_DANCE,
			.Level = 45,
		},
		{
			.Move = MOVE_SOLARBEAM,
			.Level = 48,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_FLOETTE] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_VINE_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_FAIRY_WIND,
			.Level = 6,
		},
		{
			.Move = MOVE_LUCKY_CHANT,
			.Level = 10,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 15,
		},
		{
			.Move = MOVE_WISH,
			.Level = 20,
		},
		{
			.Move = MOVE_MAGICAL_LEAF,
			.Level = 25,
		},
		{
			.Move = MOVE_GRASSY_TERRAIN,
			.Level = 27,
		},
		{
			.Move = MOVE_PETAL_BLIZZARD,
			.Level = 33,
		},
		{
			.Move = MOVE_AROMATHERAPY,
			.Level = 38,
		},
		{
			.Move = MOVE_MISTY_TERRAIN,
			.Level = 43,
		},
		{
			.Move = MOVE_MOONBLAST,
			.Level = 46,
		},
		{
			.Move = MOVE_PETAL_DANCE,
			.Level = 51,
		},
		{
			.Move = MOVE_SOLARBEAM,
			.Level = 58,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_FLORGES] = {
		{
			.Move = MOVE_DISARMING_VOICE,
			.Level = 1,
		},
		{
			.Move = MOVE_LUCKY_CHANT,
			.Level = 1,
		},
		{
			.Move = MOVE_WISH,
			.Level = 1,
		},
		{
			.Move = MOVE_MAGICAL_LEAF,
			.Level = 1,
		},
		{
			.Move = MOVE_FLOWER_SHIELD,
			.Level = 1,
		},
		{
			.Move = MOVE_GRASS_KNOT,
			.Level = 1,
		},
		{
			.Move = MOVE_GRASSY_TERRAIN,
			.Level = 1,
		},
		{
			.Move = MOVE_PETAL_BLIZZARD,
			.Level = 1,
		},
		{
			.Move = MOVE_MISTY_TERRAIN,
			.Level = 1,
		},
		{
			.Move = MOVE_MOONBLAST,
			.Level = 1,
		},
		{
			.Move = MOVE_PETAL_DANCE,
			.Level = 1,
		},
		{
			.Move = MOVE_AROMATHERAPY,
			.Level = 1,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SKIDDO] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWTH,
			.Level = 1,
		},
		{
			.Move = MOVE_VINE_WHIP,
			.Level = 7,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 9,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 12,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 13,
		},
		{
			.Move = MOVE_WORRY_SEED,
			.Level = 16,
		},
		{
			.Move = MOVE_SYNTHESIS,
			.Level = 20,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 22,
		},
		{
			.Move = MOVE_BULLDOZE,
			.Level = 26,
		},
		{
			.Move = MOVE_SEED_BOMB,
			.Level = 30,
		},
		{
			.Move = MOVE_BULK_UP,
			.Level = 34,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 38,
		},
		{
			.Move = MOVE_HORN_LEECH,
			.Level = 42,
		},
		{
			.Move = MOVE_LEAF_BLADE,
			.Level = 45,
		},
		{
			.Move = MOVE_MILK_DRINK,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GOGOAT] = {
		{
			.Move = MOVE_AERIAL_ACE,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWTH,
			.Level = 1,
		},
		{
			.Move = MOVE_VINE_WHIP,
			.Level = 7,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 9,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 12,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 13,
		},
		{
			.Move = MOVE_WORRY_SEED,
			.Level = 16,
		},
		{
			.Move = MOVE_SYNTHESIS,
			.Level = 20,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 22,
		},
		{
			.Move = MOVE_BULLDOZE,
			.Level = 26,
		},
		{
			.Move = MOVE_SEED_BOMB,
			.Level = 30,
		},
		{
			.Move = MOVE_BULK_UP,
			.Level = 34,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 40,
		},
		{
			.Move = MOVE_HORN_LEECH,
			.Level = 47,
		},
		{
			.Move = MOVE_LEAF_BLADE,
			.Level = 55,
		},
		{
			.Move = MOVE_MILK_DRINK,
			.Level = 58,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 60,
		},
		{
			.Move = MOVE_AERIAL_ACE,
			.Level = 65,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PANCHAM] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_ARM_THRUST,
			.Level = 7,
		},
		{
			.Move = MOVE_WORK_UP,
			.Level = 10,
		},
		{
			.Move = MOVE_KARATE_CHOP,
			.Level = 12,
		},
		{
			.Move = MOVE_COMET_PUNCH,
			.Level = 15,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 20,
		},
		{
			.Move = MOVE_CIRCLE_THROW,
			.Level = 25,
		},
		{
			.Move = MOVE_VITAL_THROW,
			.Level = 27,
		},
		{
			.Move = MOVE_BODY_SLAM,
			.Level = 33,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 39,
		},
		{
			.Move = MOVE_ENTRAINMENT,
			.Level = 42,
		},
		{
			.Move = MOVE_PARTING_SHOT,
			.Level = 45,
		},
		{
			.Move = MOVE_SKY_UPPERCUT,
			.Level = 48,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PANGORO] = {
		{
			.Move = MOVE_ENTRAINMENT,
			.Level = 1,
		},
		{
			.Move = MOVE_HAMMER_ARM,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_ARM_THRUST,
			.Level = 7,
		},
		{
			.Move = MOVE_WORK_UP,
			.Level = 10,
		},
		{
			.Move = MOVE_KARATE_CHOP,
			.Level = 12,
		},
		{
			.Move = MOVE_COMET_PUNCH,
			.Level = 15,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 20,
		},
		{
			.Move = MOVE_CIRCLE_THROW,
			.Level = 25,
		},
		{
			.Move = MOVE_VITAL_THROW,
			.Level = 27,
		},
		{
			.Move = MOVE_BODY_SLAM,
			.Level = 35,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 42,
		},
		{
			.Move = MOVE_ENTRAINMENT,
			.Level = 45,
		},
		{
			.Move = MOVE_PARTING_SHOT,
			.Level = 48,
		},
		{
			.Move = MOVE_SKY_UPPERCUT,
			.Level = 52,
		},
		{
			.Move = MOVE_HAMMER_ARM,
			.Level = 57,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 65,
		},
		{
			.Move = MOVE_LOW_SWEEP,
			.Level = 70,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_FURFROU] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 5,
		},
		{
			.Move = MOVE_BABYDOLL_EYES,
			.Level = 9,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 12,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 15,
		},
		{
			.Move = MOVE_BITE,
			.Level = 22,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 27,
		},
		{
			.Move = MOVE_RETALIATE,
			.Level = 33,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 35,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 38,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 42,
		},
		{
			.Move = MOVE_COTTON_GUARD,
			.Level = 48,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ESPURR] = {
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_COVET,
			.Level = 5,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 9,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 13,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 17,
		},
		{
			.Move = MOVE_FAKE_OUT,
			.Level = 19,
		},
		{
			.Move = MOVE_DISARMING_VOICE,
			.Level = 22,
		},
		{
			.Move = MOVE_PSYSHOCK,
			.Level = 25,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MEOWSTIC] = {
		{
			.Move = MOVE_QUICK_GUARD,
			.Level = 1,
		},
		{
			.Move = MOVE_MEAN_LOOK,
			.Level = 1,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 1,
		},
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_COVET,
			.Level = 5,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 9,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 13,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 17,
		},
		{
			.Move = MOVE_FAKE_OUT,
			.Level = 19,
		},
		{
			.Move = MOVE_DISARMING_VOICE,
			.Level = 22,
		},
		{
			.Move = MOVE_PSYSHOCK,
			.Level = 25,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 28,
		},
		{
			.Move = MOVE_MIRACLE_EYE,
			.Level = 31,
		},
		{
			.Move = MOVE_REFLECT,
			.Level = 35,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 40,
		},
		{
			.Move = MOVE_ROLE_PLAY,
			.Level = 43,
		},
		{
			.Move = MOVE_IMPRISON,
			.Level = 45,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 48,
		},
		{
			.Move = MOVE_MISTY_TERRAIN,
			.Level = 50,
		},
		{
			.Move = MOVE_QUICK_GUARD,
			.Level = 53,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_HONEDGE] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 1,
		},
		{
			.Move = MOVE_FURY_CUTTER,
			.Level = 5,
		},
		{
			.Move = MOVE_METAL_SOUND,
			.Level = 8,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 13,
		},
		{
			.Move = MOVE_AUTOTOMIZE,
			.Level = 18,
		},
		{
			.Move = MOVE_SHADOW_SNEAK,
			.Level = 20,
		},
		{
			.Move = MOVE_AERIAL_ACE,
			.Level = 22,
		},
		{
			.Move = MOVE_RETALIATE,
			.Level = 26,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 29,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 32,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 35,
		},
		{
			.Move = MOVE_POWER_TRICK,
			.Level = 39,
		},
		{
			.Move = MOVE_IRON_HEAD,
			.Level = 42,
		},
		{
			.Move = MOVE_SACRED_SWORD,
			.Level = 47,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_DOUBLADE] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 1,
		},
		{
			.Move = MOVE_FURY_CUTTER,
			.Level = 5,
		},
		{
			.Move = MOVE_METAL_SOUND,
			.Level = 8,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 13,
		},
		{
			.Move = MOVE_AUTOTOMIZE,
			.Level = 18,
		},
		{
			.Move = MOVE_SHADOW_SNEAK,
			.Level = 20,
		},
		{
			.Move = MOVE_AERIAL_ACE,
			.Level = 22,
		},
		{
			.Move = MOVE_RETALIATE,
			.Level = 26,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 29,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 32,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 36,
		},
		{
			.Move = MOVE_POWER_TRICK,
			.Level = 41,
		},
		{
			.Move = MOVE_IRON_HEAD,
			.Level = 45,
		},
		{
			.Move = MOVE_SACRED_SWORD,
			.Level = 51,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_AEGISLASH] = {
		{
			.Move = MOVE_FURY_CUTTER,
			.Level = 1,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 1,
		},
		{
			.Move = MOVE_AUTOTOMIZE,
			.Level = 1,
		},
		{
			.Move = MOVE_SHADOW_SNEAK,
			.Level = 1,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 1,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 1,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 1,
		},
		{
			.Move = MOVE_POWER_TRICK,
			.Level = 1,
		},
		{
			.Move = MOVE_IRON_HEAD,
			.Level = 1,
		},
		{
			.Move = MOVE_HEAD_SMASH,
			.Level = 1,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 1,
		},
		{
			.Move = MOVE_AERIAL_ACE,
			.Level = 1,
		},
		{
			.Move = MOVE_KING\X2019S_SHIELD,
			.Level = 1,
		},
		{
			.Move = MOVE_SACRED_SWORD,
			.Level = 1,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SPRITZEE] = {
		{
			.Move = MOVE_SWEET_SCENT,
			.Level = 1,
		},
		{
			.Move = MOVE_FAIRY_WIND,
			.Level = 1,
		},
		{
			.Move = MOVE_SWEET_KISS,
			.Level = 6,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 8,
		},
		{
			.Move = MOVE_ECHOED_VOICE,
			.Level = 13,
		},
		{
			.Move = MOVE_CALM_MIND,
			.Level = 17,
		},
		{
			.Move = MOVE_DRAINING_KISS,
			.Level = 21,
		},
		{
			.Move = MOVE_AROMATHERAPY,
			.Level = 25,
		},
		{
			.Move = MOVE_ATTRACT,
			.Level = 29,
		},
		{
			.Move = MOVE_MOONBLAST,
			.Level = 31,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 35,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 38,
		},
		{
			.Move = MOVE_MISTY_TERRAIN,
			.Level = 42,
		},
		{
			.Move = MOVE_SKILL_SWAP,
			.Level = 44,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 48,
		},
		{
			.Move = MOVE_DISARMING_VOICE,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_AROMATISSE] = {
		{
			.Move = MOVE_AROMATIC_MIST,
			.Level = 1,
		},
		{
			.Move = MOVE_HEAL_PULSE,
			.Level = 1,
		},
		{
			.Move = MOVE_SWEET_SCENT,
			.Level = 1,
		},
		{
			.Move = MOVE_FAIRY_WIND,
			.Level = 1,
		},
		{
			.Move = MOVE_SWEET_KISS,
			.Level = 6,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 8,
		},
		{
			.Move = MOVE_ECHOED_VOICE,
			.Level = 13,
		},
		{
			.Move = MOVE_CALM_MIND,
			.Level = 17,
		},
		{
			.Move = MOVE_DRAINING_KISS,
			.Level = 21,
		},
		{
			.Move = MOVE_AROMATHERAPY,
			.Level = 25,
		},
		{
			.Move = MOVE_ATTRACT,
			.Level = 29,
		},
		{
			.Move = MOVE_MOONBLAST,
			.Level = 31,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 35,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 38,
		},
		{
			.Move = MOVE_MISTY_TERRAIN,
			.Level = 42,
		},
		{
			.Move = MOVE_SKILL_SWAP,
			.Level = 44,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 48,
		},
		{
			.Move = MOVE_DISARMING_VOICE,
			.Level = 53,
		},
		{
			.Move = MOVE_REFLECT,
			.Level = 57,
		},
		{
			.Move = MOVE_PSYCH_UP,
			.Level = 64,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SWIRLIX] = {
		{
			.Move = MOVE_SWEET_SCENT,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_FAIRY_WIND,
			.Level = 5,
		},
		{
			.Move = MOVE_PLAY_NICE,
			.Level = 8,
		},
		{
			.Move = MOVE_FAKE_TEARS,
			.Level = 10,
		},
		{
			.Move = MOVE_ROUND,
			.Level = 13,
		},
		{
			.Move = MOVE_COTTON_SPORE,
			.Level = 17,
		},
		{
			.Move = MOVE_ENDEAVOR,
			.Level = 21,
		},
		{
			.Move = MOVE_AROMATHERAPY,
			.Level = 26,
		},
		{
			.Move = MOVE_DRAINING_KISS,
			.Level = 31,
		},
		{
			.Move = MOVE_ENERGY_BALL,
			.Level = 36,
		},
		{
			.Move = MOVE_COTTON_GUARD,
			.Level = 41,
		},
		{
			.Move = MOVE_WISH,
			.Level = 45,
		},
		{
			.Move = MOVE_PLAY_ROUGH,
			.Level = 49,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 58,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 67,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SLURPUFF] = {
		{
			.Move = MOVE_SWEET_SCENT,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_FAIRY_WIND,
			.Level = 5,
		},
		{
			.Move = MOVE_PLAY_NICE,
			.Level = 8,
		},
		{
			.Move = MOVE_FAKE_TEARS,
			.Level = 10,
		},
		{
			.Move = MOVE_ROUND,
			.Level = 13,
		},
		{
			.Move = MOVE_COTTON_SPORE,
			.Level = 17,
		},
		{
			.Move = MOVE_ENDEAVOR,
			.Level = 21,
		},
		{
			.Move = MOVE_AROMATHERAPY,
			.Level = 26,
		},
		{
			.Move = MOVE_DRAINING_KISS,
			.Level = 31,
		},
		{
			.Move = MOVE_ENERGY_BALL,
			.Level = 36,
		},
		{
			.Move = MOVE_COTTON_GUARD,
			.Level = 41,
		},
		{
			.Move = MOVE_WISH,
			.Level = 45,
		},
		{
			.Move = MOVE_PLAY_ROUGH,
			.Level = 49,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 58,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 67,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_INKAY] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_PECK,
			.Level = 1,
		},
		{
			.Move = MOVE_CONSTRICT,
			.Level = 1,
		},
		{
			.Move = MOVE_REFLECT,
			.Level = 4,
		},
		{
			.Move = MOVE_FOUL_PLAY,
			.Level = 8,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 12,
		},
		{
			.Move = MOVE_PSYWAVE,
			.Level = 13,
		},
		{
			.Move = MOVE_TOPSYTURVY,
			.Level = 15,
		},
		{
			.Move = MOVE_HYPNOSIS,
			.Level = 18,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 21,
		},
		{
			.Move = MOVE_SWITCHEROO,
			.Level = 23,
		},
		{
			.Move = MOVE_PAYBACK,
			.Level = 27,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 31,
		},
		{
			.Move = MOVE_PLUCK,
			.Level = 35,
		},
		{
			.Move = MOVE_PSYCHO_CUT,
			.Level = 39,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 43,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 46,
		},
		{
			.Move = MOVE_SUPERPOWER,
			.Level = 48,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MALAMAR] = {
		{
			.Move = MOVE_SUPERPOWER,
			.Level = 1,
		},
		{
			.Move = MOVE_REVERSAL,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_PECK,
			.Level = 1,
		},
		{
			.Move = MOVE_CONSTRICT,
			.Level = 1,
		},
		{
			.Move = MOVE_REFLECT,
			.Level = 4,
		},
		{
			.Move = MOVE_FOUL_PLAY,
			.Level = 8,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 12,
		},
		{
			.Move = MOVE_PSYWAVE,
			.Level = 13,
		},
		{
			.Move = MOVE_TOPSYTURVY,
			.Level = 15,
		},
		{
			.Move = MOVE_HYPNOSIS,
			.Level = 18,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 21,
		},
		{
			.Move = MOVE_SWITCHEROO,
			.Level = 23,
		},
		{
			.Move = MOVE_PAYBACK,
			.Level = 27,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 31,
		},
		{
			.Move = MOVE_PLUCK,
			.Level = 35,
		},
		{
			.Move = MOVE_PSYCHO_CUT,
			.Level = 39,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 43,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 46,
		},
		{
			.Move = MOVE_SUPERPOWER,
			.Level = 48,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BINACLE] = {
		{
			.Move = MOVE_SHELL_SMASH,
			.Level = 1,
		},
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 4,
		},
		{
			.Move = MOVE_WITHDRAW,
			.Level = 7,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 10,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 13,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 18,
		},
		{
			.Move = MOVE_CLAMP,
			.Level = 20,
		},
		{
			.Move = MOVE_ROCK_POLISH,
			.Level = 24,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 28,
		},
		{
			.Move = MOVE_HONE_CLAWS,
			.Level = 32,
		},
		{
			.Move = MOVE_FURY_CUTTER,
			.Level = 37,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 41,
		},
		{
			.Move = MOVE_RAZOR_SHELL,
			.Level = 45,
		},
		{
			.Move = MOVE_CROSS_CHOP,
			.Level = 49,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BARBARACLE] = {
		{
			.Move = MOVE_STONE_EDGE,
			.Level = 1,
		},
		{
			.Move = MOVE_SKULL_BASH,
			.Level = 1,
		},
		{
			.Move = MOVE_SHELL_SMASH,
			.Level = 1,
		},
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 4,
		},
		{
			.Move = MOVE_WITHDRAW,
			.Level = 7,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 10,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 13,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 18,
		},
		{
			.Move = MOVE_CLAMP,
			.Level = 20,
		},
		{
			.Move = MOVE_ROCK_POLISH,
			.Level = 24,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 28,
		},
		{
			.Move = MOVE_HONE_CLAWS,
			.Level = 32,
		},
		{
			.Move = MOVE_FURY_CUTTER,
			.Level = 37,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 44,
		},
		{
			.Move = MOVE_RAZOR_SHELL,
			.Level = 48,
		},
		{
			.Move = MOVE_CROSS_CHOP,
			.Level = 55,
		},
		{
			.Move = MOVE_STONE_EDGE,
			.Level = 60,
		},
		{
			.Move = MOVE_SKULL_BASH,
			.Level = 65,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SKRELP] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_SMOKESCREEN,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 5,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 9,
		},
		{
			.Move = MOVE_BUBBLE,
			.Level = 12,
		},
		{
			.Move = MOVE_ACID,
			.Level = 15,
		},
		{
			.Move = MOVE_CAMOUFLAGE,
			.Level = 19,
		},
		{
			.Move = MOVE_POISON_TAIL,
			.Level = 23,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 25,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 28,
		},
		{
			.Move = MOVE_TOXIC,
			.Level = 32,
		},
		{
			.Move = MOVE_AQUA_TAIL,
			.Level = 35,
		},
		{
			.Move = MOVE_SLUDGE_BOMB,
			.Level = 38,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 42,
		},
		{
			.Move = MOVE_DRAGON_PULSE,
			.Level = 49,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_DRAGALGE] = {
		{
			.Move = MOVE_DRAGON_TAIL,
			.Level = 1,
		},
		{
			.Move = MOVE_TWISTER,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_SMOKESCREEN,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 5,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 9,
		},
		{
			.Move = MOVE_BUBBLE,
			.Level = 12,
		},
		{
			.Move = MOVE_ACID,
			.Level = 15,
		},
		{
			.Move = MOVE_CAMOUFLAGE,
			.Level = 19,
		},
		{
			.Move = MOVE_POISON_TAIL,
			.Level = 23,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 25,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 28,
		},
		{
			.Move = MOVE_TOXIC,
			.Level = 32,
		},
		{
			.Move = MOVE_AQUA_TAIL,
			.Level = 35,
		},
		{
			.Move = MOVE_SLUDGE_BOMB,
			.Level = 38,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 42,
		},
		{
			.Move = MOVE_DRAGON_PULSE,
			.Level = 53,
		},
		{
			.Move = MOVE_DRAGON_TAIL,
			.Level = 59,
		},
		{
			.Move = MOVE_TWISTER,
			.Level = 67,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CLAUNCHER] = {
		{
			.Move = MOVE_SPLASH,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 7,
		},
		{
			.Move = MOVE_VICEGRIP,
			.Level = 9,
		},
		{
			.Move = MOVE_BUBBLE,
			.Level = 12,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 16,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 20,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 25,
		},
		{
			.Move = MOVE_CRABHAMMER,
			.Level = 30,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 34,
		},
		{
			.Move = MOVE_SMACK_DOWN,
			.Level = 39,
		},
		{
			.Move = MOVE_AQUA_JET,
			.Level = 43,
		},
		{
			.Move = MOVE_MUDDY_WATER,
			.Level = 48,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CLAWITZER] = {
		{
			.Move = MOVE_HEAL_PULSE,
			.Level = 1,
		},
		{
			.Move = MOVE_DARK_PULSE,
			.Level = 1,
		},
		{
			.Move = MOVE_DRAGON_PULSE,
			.Level = 1,
		},
		{
			.Move = MOVE_AURA_SPHERE,
			.Level = 1,
		},
		{
			.Move = MOVE_SPLASH,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 7,
		},
		{
			.Move = MOVE_VICEGRIP,
			.Level = 9,
		},
		{
			.Move = MOVE_BUBBLE,
			.Level = 12,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 16,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 20,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 25,
		},
		{
			.Move = MOVE_CRABHAMMER,
			.Level = 30,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 34,
		},
		{
			.Move = MOVE_SMACK_DOWN,
			.Level = 42,
		},
		{
			.Move = MOVE_AQUA_JET,
			.Level = 47,
		},
		{
			.Move = MOVE_MUDDY_WATER,
			.Level = 53,
		},
		{
			.Move = MOVE_DARK_PULSE,
			.Level = 57,
		},
		{
			.Move = MOVE_DRAGON_PULSE,
			.Level = 63,
		},
		{
			.Move = MOVE_AURA_SPHERE,
			.Level = 67,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_HELIOPTILE] = {
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 6,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 11,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 13,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 17,
		},
		{
			.Move = MOVE_RAZOR_WIND,
			.Level = 22,
		},
		{
			.Move = MOVE_PARABOLIC_CHARGE,
			.Level = 25,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 31,
		},
		{
			.Move = MOVE_BULLDOZE,
			.Level = 35,
		},
		{
			.Move = MOVE_VOLT_SWITCH,
			.Level = 40,
		},
		{
			.Move = MOVE_ELECTRIFY,
			.Level = 45,
		},
		{
			.Move = MOVE_THUNDERBOLT,
			.Level = 49,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_HELIOLISK] = {
		{
			.Move = MOVE_EERIE_IMPULSE,
			.Level = 1,
		},
		{
			.Move = MOVE_ELECTRIFY,
			.Level = 1,
		},
		{
			.Move = MOVE_RAZOR_WIND,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER,
			.Level = 1,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 1,
		},
		{
			.Move = MOVE_PARABOLIC_CHARGE,
			.Level = 1,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_TYRUNT] = {
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_ROAR,
			.Level = 6,
		},
		{
			.Move = MOVE_STOMP,
			.Level = 10,
		},
		{
			.Move = MOVE_BIDE,
			.Level = 12,
		},
		{
			.Move = MOVE_STEALTH_ROCK,
			.Level = 15,
		},
		{
			.Move = MOVE_BITE,
			.Level = 17,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 20,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 26,
		},
		{
			.Move = MOVE_DRAGON_TAIL,
			.Level = 30,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 34,
		},
		{
			.Move = MOVE_DRAGON_CLAW,
			.Level = 37,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 40,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 44,
		},
		{
			.Move = MOVE_HORN_DRILL,
			.Level = 49,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_TYRANTRUM] = {
		{
			.Move = MOVE_HEAD_SMASH,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_ROAR,
			.Level = 6,
		},
		{
			.Move = MOVE_STOMP,
			.Level = 10,
		},
		{
			.Move = MOVE_BIDE,
			.Level = 12,
		},
		{
			.Move = MOVE_STEALTH_ROCK,
			.Level = 15,
		},
		{
			.Move = MOVE_BITE,
			.Level = 17,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 20,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 26,
		},
		{
			.Move = MOVE_DRAGON_TAIL,
			.Level = 30,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 34,
		},
		{
			.Move = MOVE_DRAGON_CLAW,
			.Level = 37,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 42,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 47,
		},
		{
			.Move = MOVE_HORN_DRILL,
			.Level = 53,
		},
		{
			.Move = MOVE_HEAD_SMASH,
			.Level = 58,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 68,
		},
		{
			.Move = MOVE_GIGA_IMPACT,
			.Level = 75,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_AMAURA] = {
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_POWDER_SNOW,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 5,
		},
		{
			.Move = MOVE_ROCK_THROW,
			.Level = 10,
		},
		{
			.Move = MOVE_ICY_WIND,
			.Level = 13,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 15,
		},
		{
			.Move = MOVE_MIST,
			.Level = 18,
		},
		{
			.Move = MOVE_AURORA_BEAM,
			.Level = 20,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 26,
		},
		{
			.Move = MOVE_ROUND,
			.Level = 30,
		},
		{
			.Move = MOVE_AVALANCHE,
			.Level = 34,
		},
		{
			.Move = MOVE_HAIL,
			.Level = 38,
		},
		{
			.Move = MOVE_NATURE_POWER,
			.Level = 41,
		},
		{
			.Move = MOVE_ENCORE,
			.Level = 44,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 47,
		},
		{
			.Move = MOVE_ICE_BEAM,
			.Level = 50,
		},
		{
			.Move = MOVE_HYPER_BEAM,
			.Level = 57,
		},
		{
			.Move = MOVE_BLIZZARD,
			.Level = 65,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_AURORUS] = {
		{
			.Move = MOVE_FREEZEDRY,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_POWDER_SNOW,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 5,
		},
		{
			.Move = MOVE_ROCK_THROW,
			.Level = 10,
		},
		{
			.Move = MOVE_ICY_WIND,
			.Level = 13,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 15,
		},
		{
			.Move = MOVE_MIST,
			.Level = 18,
		},
		{
			.Move = MOVE_AURORA_BEAM,
			.Level = 20,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 26,
		},
		{
			.Move = MOVE_ROUND,
			.Level = 30,
		},
		{
			.Move = MOVE_AVALANCHE,
			.Level = 34,
		},
		{
			.Move = MOVE_HAIL,
			.Level = 38,
		},
		{
			.Move = MOVE_NATURE_POWER,
			.Level = 43,
		},
		{
			.Move = MOVE_ENCORE,
			.Level = 46,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 50,
		},
		{
			.Move = MOVE_ICE_BEAM,
			.Level = 56,
		},
		{
			.Move = MOVE_HYPER_BEAM,
			.Level = 63,
		},
		{
			.Move = MOVE_BLIZZARD,
			.Level = 74,
		},
		{
			.Move = MOVE_FREEZEDRY,
			.Level = 77,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SYLVEON] = {
		{
			.Move = MOVE_DISARMING_VOICE,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 5,
		},
		{
			.Move = MOVE_FAIRY_WIND,
			.Level = 9,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 13,
		},
		{
			.Move = MOVE_SWIFT,
			.Level = 17,
		},
		{
			.Move = MOVE_DRAINING_KISS,
			.Level = 20,
		},
		{
			.Move = MOVE_SKILL_SWAP,
			.Level = 25,
		},
		{
			.Move = MOVE_MISTY_TERRAIN,
			.Level = 29,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 33,
		},
		{
			.Move = MOVE_MOONBLAST,
			.Level = 37,
		},
		{
			.Move = MOVE_LAST_RESORT,
			.Level = 41,
		},
		{
			.Move = MOVE_PSYCH_UP,
			.Level = 45,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_HAWLUCHA] = {
		{
			.Move = MOVE_DETECT,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_HONE_CLAWS,
			.Level = 1,
		},
		{
			.Move = MOVE_KARATE_CHOP,
			.Level = 4,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 8,
		},
		{
			.Move = MOVE_ROOST,
			.Level = 12,
		},
		{
			.Move = MOVE_AERIAL_ACE,
			.Level = 16,
		},
		{
			.Move = MOVE_ENCORE,
			.Level = 20,
		},
		{
			.Move = MOVE_FLING,
			.Level = 24,
		},
		{
			.Move = MOVE_FLYING_PRESS,
			.Level = 28,
		},
		{
			.Move = MOVE_BOUNCE,
			.Level = 32,
		},
		{
			.Move = MOVE_ENDEAVOR,
			.Level = 36,
		},
		{
			.Move = MOVE_FEATHERDANCE,
			.Level = 40,
		},
		{
			.Move = MOVE_HI_JUMP_KICK,
			.Level = 44,
		},
		{
			.Move = MOVE_SKY_ATTACK,
			.Level = 48,
		},
		{
			.Move = MOVE_SKY_DROP,
			.Level = 55,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 60,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_DEDENNE] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 7,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 11,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 14,
		},
		{
			.Move = MOVE_PARABOLIC_CHARGE,
			.Level = 17,
		},
		{
			.Move = MOVE_NUZZLE,
			.Level = 20,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 23,
		},
		{
			.Move = MOVE_VOLT_SWITCH,
			.Level = 26,
		},
		{
			.Move = MOVE_REST,
			.Level = 30,
		},
		{
			.Move = MOVE_SNORE,
			.Level = 31,
		},
		{
			.Move = MOVE_CHARGE_BEAM,
			.Level = 34,
		},
		{
			.Move = MOVE_ENTRAINMENT,
			.Level = 39,
		},
		{
			.Move = MOVE_PLAY_ROUGH,
			.Level = 42,
		},
		{
			.Move = MOVE_THUNDER,
			.Level = 45,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_CARBINK] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 1,
		},
		{
			.Move = MOVE_ROCK_THROW,
			.Level = 5,
		},
		{
			.Move = MOVE_SHARPEN,
			.Level = 8,
		},
		{
			.Move = MOVE_SMACK_DOWN,
			.Level = 12,
		},
		{
			.Move = MOVE_REFLECT,
			.Level = 18,
		},
		{
			.Move = MOVE_STEALTH_ROCK,
			.Level = 21,
		},
		{
			.Move = MOVE_GUARD_SPLIT,
			.Level = 27,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 31,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 35,
		},
		{
			.Move = MOVE_SKILL_SWAP,
			.Level = 40,
		},
		{
			.Move = MOVE_POWER_GEM,
			.Level = 46,
		},
		{
			.Move = MOVE_STONE_EDGE,
			.Level = 49,
		},
		{
			.Move = MOVE_MOONBLAST,
			.Level = 50,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 60,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 70,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GOOMY] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_BUBBLE,
			.Level = 1,
		},
		{
			.Move = MOVE_ABSORB,
			.Level = 5,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 9,
		},
		{
			.Move = MOVE_BIDE,
			.Level = 13,
		},
		{
			.Move = MOVE_DRAGONBREATH,
			.Level = 18,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 25,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 28,
		},
		{
			.Move = MOVE_BODY_SLAM,
			.Level = 32,
		},
		{
			.Move = MOVE_MUDDY_WATER,
			.Level = 38,
		},
		{
			.Move = MOVE_DRAGON_PULSE,
			.Level = 42,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SLIGGOO] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_BUBBLE,
			.Level = 1,
		},
		{
			.Move = MOVE_ABSORB,
			.Level = 5,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 9,
		},
		{
			.Move = MOVE_BIDE,
			.Level = 13,
		},
		{
			.Move = MOVE_DRAGONBREATH,
			.Level = 18,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 25,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 28,
		},
		{
			.Move = MOVE_BODY_SLAM,
			.Level = 32,
		},
		{
			.Move = MOVE_MUDDY_WATER,
			.Level = 38,
		},
		{
			.Move = MOVE_DRAGON_PULSE,
			.Level = 47,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GOODRA] = {
		{
			.Move = MOVE_OUTRAGE,
			.Level = 1,
		},
		{
			.Move = MOVE_FEINT,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_BUBBLE,
			.Level = 1,
		},
		{
			.Move = MOVE_ABSORB,
			.Level = 5,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 9,
		},
		{
			.Move = MOVE_BIDE,
			.Level = 13,
		},
		{
			.Move = MOVE_DRAGONBREATH,
			.Level = 18,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 25,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 28,
		},
		{
			.Move = MOVE_BODY_SLAM,
			.Level = 32,
		},
		{
			.Move = MOVE_MUDDY_WATER,
			.Level = 38,
		},
		{
			.Move = MOVE_DRAGON_PULSE,
			.Level = 47,
		},
		{
			.Move = MOVE_AQUA_TAIL,
			.Level = 50,
		},
		{
			.Move = MOVE_POWER_WHIP,
			.Level = 55,
		},
		{
			.Move = MOVE_OUTRAGE,
			.Level = 63,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_KLEFKI] = {
		{
			.Move = MOVE_FAIRY_LOCK,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_FAIRY_WIND,
			.Level = 5,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 8,
		},
		{
			.Move = MOVE_METAL_SOUND,
			.Level = 12,
		},
		{
			.Move = MOVE_SPIKES,
			.Level = 15,
		},
		{
			.Move = MOVE_DRAINING_KISS,
			.Level = 18,
		},
		{
			.Move = MOVE_CRAFTY_SHIELD,
			.Level = 23,
		},
		{
			.Move = MOVE_FOUL_PLAY,
			.Level = 27,
		},
		{
			.Move = MOVE_TORMENT,
			.Level = 32,
		},
		{
			.Move = MOVE_MIRROR_SHOT,
			.Level = 34,
		},
		{
			.Move = MOVE_IMPRISON,
			.Level = 36,
		},
		{
			.Move = MOVE_RECYCLE,
			.Level = 40,
		},
		{
			.Move = MOVE_PLAY_ROUGH,
			.Level = 43,
		},
		{
			.Move = MOVE_MAGIC_ROOM,
			.Level = 44,
		},
		{
			.Move = MOVE_HEAL_BLOCK,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PHANTUMP] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 5,
		},
		{
			.Move = MOVE_GROWTH,
			.Level = 8,
		},
		{
			.Move = MOVE_INGRAIN,
			.Level = 13,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 19,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 23,
		},
		{
			.Move = MOVE_CURSE,
			.Level = 28,
		},
		{
			.Move = MOVE_WILLOWISP,
			.Level = 31,
		},
		{
			.Move = MOVE_FOREST\X2019S_CURSE,
			.Level = 35,
		},
		{
			.Move = MOVE_DESTINY_BOND,
			.Level = 39,
		},
		{
			.Move = MOVE_PHANTOM_FORCE,
			.Level = 45,
		},
		{
			.Move = MOVE_WOOD_HAMMER,
			.Level = 49,
		},
		{
			.Move = MOVE_HORN_LEECH,
			.Level = 54,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_TREVENANT] = {
		{
			.Move = MOVE_HORN_LEECH,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 5,
		},
		{
			.Move = MOVE_GROWTH,
			.Level = 8,
		},
		{
			.Move = MOVE_INGRAIN,
			.Level = 13,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 19,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 23,
		},
		{
			.Move = MOVE_CURSE,
			.Level = 28,
		},
		{
			.Move = MOVE_WILLOWISP,
			.Level = 31,
		},
		{
			.Move = MOVE_FOREST\X2019S_CURSE,
			.Level = 35,
		},
		{
			.Move = MOVE_DESTINY_BOND,
			.Level = 39,
		},
		{
			.Move = MOVE_PHANTOM_FORCE,
			.Level = 45,
		},
		{
			.Move = MOVE_WOOD_HAMMER,
			.Level = 49,
		},
		{
			.Move = MOVE_SHADOW_CLAW,
			.Level = 55,
		},
		{
			.Move = MOVE_HORN_LEECH,
			.Level = 62,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PUMPKABOO] = {
		{
			.Move = MOVE_TRICK,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 1,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 4,
		},
		{
			.Move = MOVE_TRICKORTREAT,
			.Level = 6,
		},
		{
			.Move = MOVE_WORRY_SEED,
			.Level = 11,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 16,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 20,
		},
		{
			.Move = MOVE_TRICKORTREAT,
			.Level = 23,
		},
		{
			.Move = MOVE_BULLET_SEED,
			.Level = 26,
		},
		{
			.Move = MOVE_SHADOW_SNEAK,
			.Level = 30,
		},
		{
			.Move = MOVE_SHADOW_BALL,
			.Level = 36,
		},
		{
			.Move = MOVE_TRICKORTREAT,
			.Level = 40,
		},
		{
			.Move = MOVE_PAIN_SPLIT,
			.Level = 42,
		},
		{
			.Move = MOVE_SEED_BOMB,
			.Level = 48,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GOURGEIST] = {
		{
			.Move = MOVE_EXPLOSION,
			.Level = 1,
		},
		{
			.Move = MOVE_PHANTOM_FORCE,
			.Level = 1,
		},
		{
			.Move = MOVE_TRICK,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 1,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 4,
		},
		{
			.Move = MOVE_TRICKORTREAT,
			.Level = 6,
		},
		{
			.Move = MOVE_WORRY_SEED,
			.Level = 11,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 16,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 20,
		},
		{
			.Move = MOVE_TRICKORTREAT,
			.Level = 23,
		},
		{
			.Move = MOVE_BULLET_SEED,
			.Level = 26,
		},
		{
			.Move = MOVE_SHADOW_SNEAK,
			.Level = 30,
		},
		{
			.Move = MOVE_SHADOW_BALL,
			.Level = 36,
		},
		{
			.Move = MOVE_TRICKORTREAT,
			.Level = 40,
		},
		{
			.Move = MOVE_PAIN_SPLIT,
			.Level = 42,
		},
		{
			.Move = MOVE_SEED_BOMB,
			.Level = 48,
		},
		{
			.Move = MOVE_PHANTOM_FORCE,
			.Level = 57,
		},
		{
			.Move = MOVE_TRICKORTREAT,
			.Level = 63,
		},
		{
			.Move = MOVE_SHADOW_BALL,
			.Level = 70,
		},
		{
			.Move = MOVE_EXPLOSION,
			.Level = 75,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BERGMITE] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 1,
		},
		{
			.Move = MOVE_POWDER_SNOW,
			.Level = 5,
		},
		{
			.Move = MOVE_ICY_WIND,
			.Level = 10,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 15,
		},
		{
			.Move = MOVE_SHARPEN,
			.Level = 20,
		},
		{
			.Move = MOVE_CURSE,
			.Level = 22,
		},
		{
			.Move = MOVE_ICE_FANG,
			.Level = 26,
		},
		{
			.Move = MOVE_ICE_BALL,
			.Level = 30,
		},
		{
			.Move = MOVE_RAPID_SPIN,
			.Level = 35,
		},
		{
			.Move = MOVE_AVALANCHE,
			.Level = 39,
		},
		{
			.Move = MOVE_BLIZZARD,
			.Level = 43,
		},
		{
			.Move = MOVE_RECOVER,
			.Level = 47,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 49,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_AVALUGG] = {
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 1,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 1,
		},
		{
			.Move = MOVE_SKULL_BASH,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 1,
		},
		{
			.Move = MOVE_POWDER_SNOW,
			.Level = 5,
		},
		{
			.Move = MOVE_ICY_WIND,
			.Level = 10,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 15,
		},
		{
			.Move = MOVE_SHARPEN,
			.Level = 20,
		},
		{
			.Move = MOVE_CURSE,
			.Level = 22,
		},
		{
			.Move = MOVE_ICE_FANG,
			.Level = 26,
		},
		{
			.Move = MOVE_ICE_BALL,
			.Level = 30,
		},
		{
			.Move = MOVE_RAPID_SPIN,
			.Level = 35,
		},
		{
			.Move = MOVE_AVALANCHE,
			.Level = 42,
		},
		{
			.Move = MOVE_BLIZZARD,
			.Level = 46,
		},
		{
			.Move = MOVE_RECOVER,
			.Level = 51,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 56,
		},
		{
			.Move = MOVE_SKULL_BASH,
			.Level = 60,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 65,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_NOIBAT] = {
		{
			.Move = MOVE_SCREECH,
			.Level = 1,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_LEECH_LIFE,
			.Level = 5,
		},
		{
			.Move = MOVE_GUST,
			.Level = 11,
		},
		{
			.Move = MOVE_BITE,
			.Level = 13,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 16,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 18,
		},
		{
			.Move = MOVE_AIR_CUTTER,
			.Level = 23,
		},
		{
			.Move = MOVE_ROOST,
			.Level = 27,
		},
		{
			.Move = MOVE_RAZOR_WIND,
			.Level = 31,
		},
		{
			.Move = MOVE_TAILWIND,
			.Level = 35,
		},
		{
			.Move = MOVE_WHIRLWIND,
			.Level = 40,
		},
		{
			.Move = MOVE_SUPER_FANG,
			.Level = 43,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 48,
		},
		{
			.Move = MOVE_HURRICANE,
			.Level = 58,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_NOIVERN] = {
		{
			.Move = MOVE_MOONLIGHT,
			.Level = 1,
		},
		{
			.Move = MOVE_BOOMBURST,
			.Level = 1,
		},
		{
			.Move = MOVE_DRAGON_PULSE,
			.Level = 1,
		},
		{
			.Move = MOVE_HURRICANE,
			.Level = 1,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 1,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_LEECH_LIFE,
			.Level = 5,
		},
		{
			.Move = MOVE_GUST,
			.Level = 11,
		},
		{
			.Move = MOVE_BITE,
			.Level = 13,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 16,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 18,
		},
		{
			.Move = MOVE_AIR_CUTTER,
			.Level = 23,
		},
		{
			.Move = MOVE_ROOST,
			.Level = 27,
		},
		{
			.Move = MOVE_RAZOR_WIND,
			.Level = 31,
		},
		{
			.Move = MOVE_TAILWIND,
			.Level = 35,
		},
		{
			.Move = MOVE_WHIRLWIND,
			.Level = 40,
		},
		{
			.Move = MOVE_SUPER_FANG,
			.Level = 43,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 53,
		},
		{
			.Move = MOVE_HURRICANE,
			.Level = 62,
		},
		{
			.Move = MOVE_DRAGON_PULSE,
			.Level = 70,
		},
		{
			.Move = MOVE_BOOMBURST,
			.Level = 75,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_XERNEAS] = {
		{
			.Move = MOVE_HEAL_PULSE,
			.Level = 1,
		},
		{
			.Move = MOVE_AROMATHERAPY,
			.Level = 1,
		},
		{
			.Move = MOVE_INGRAIN,
			.Level = 1,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 1,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 5,
		},
		{
			.Move = MOVE_AURORA_BEAM,
			.Level = 10,
		},
		{
			.Move = MOVE_GRAVITY,
			.Level = 18,
		},
		{
			.Move = MOVE_GEOMANCY,
			.Level = 26,
		},
		{
			.Move = MOVE_MOONBLAST,
			.Level = 35,
		},
		{
			.Move = MOVE_MEGAHORN,
			.Level = 44,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 51,
		},
		{
			.Move = MOVE_HORN_LEECH,
			.Level = 55,
		},
		{
			.Move = MOVE_PSYCH_UP,
			.Level = 59,
		},
		{
			.Move = MOVE_MISTY_TERRAIN,
			.Level = 63,
		},
		{
			.Move = MOVE_NATURE_POWER,
			.Level = 72,
		},
		{
			.Move = MOVE_CLOSE_COMBAT,
			.Level = 80,
		},
		{
			.Move = MOVE_GIGA_IMPACT,
			.Level = 88,
		},
		{
			.Move = MOVE_OUTRAGE,
			.Level = 93,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_YVELTAL] = {
		{
			.Move = MOVE_HURRICANE,
			.Level = 1,
		},
		{
			.Move = MOVE_RAZOR_WIND,
			.Level = 1,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 1,
		},
		{
			.Move = MOVE_ROOST,
			.Level = 1,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 5,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 10,
		},
		{
			.Move = MOVE_SNARL,
			.Level = 18,
		},
		{
			.Move = MOVE_OBLIVION_WING,
			.Level = 26,
		},
		{
			.Move = MOVE_DISABLE,
			.Level = 35,
		},
		{
			.Move = MOVE_DARK_PULSE,
			.Level = 44,
		},
		{
			.Move = MOVE_FOUL_PLAY,
			.Level = 51,
		},
		{
			.Move = MOVE_PHANTOM_FORCE,
			.Level = 55,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 59,
		},
		{
			.Move = MOVE_DRAGON_RUSH,
			.Level = 63,
		},
		{
			.Move = MOVE_FOCUS_BLAST,
			.Level = 72,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 80,
		},
		{
			.Move = MOVE_HYPER_BEAM,
			.Level = 88,
		},
		{
			.Move = MOVE_SKY_ATTACK,
			.Level = 93,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_ZYGARDE] = {
		{
			.Move = MOVE_GLARE,
			.Level = 1,
		},
		{
			.Move = MOVE_BULLDOZE,
			.Level = 1,
		},
		{
			.Move = MOVE_DRAGONBREATH,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 5,
		},
		{
			.Move = MOVE_DIG,
			.Level = 10,
		},
		{
			.Move = MOVE_BIND,
			.Level = 18,
		},
		{
			.Move = MOVE_LAND\X2019S_WRATH,
			.Level = 26,
		},
		{
			.Move = MOVE_SANDSTORM,
			.Level = 35,
		},
		{
			.Move = MOVE_HAZE,
			.Level = 44,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 51,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 55,
		},
		{
			.Move = MOVE_CAMOUFLAGE,
			.Level = 59,
		},
		{
			.Move = MOVE_DRAGON_PULSE,
			.Level = 63,
		},
		{
			.Move = MOVE_DRAGON_DANCE,
			.Level = 72,
		},
		{
			.Move = MOVE_COIL,
			.Level = 80,
		},
		{
			.Move = MOVE_EXTREMESPEED,
			.Level = 88,
		},
		{
			.Move = MOVE_OUTRAGE,
			.Level = 93,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_DIANCIE] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 1,
		},
		{
			.Move = MOVE_ROCK_THROW,
			.Level = 5,
		},
		{
			.Move = MOVE_SHARPEN,
			.Level = 8,
		},
		{
			.Move = MOVE_SMACK_DOWN,
			.Level = 12,
		},
		{
			.Move = MOVE_REFLECT,
			.Level = 18,
		},
		{
			.Move = MOVE_STEALTH_ROCK,
			.Level = 21,
		},
		{
			.Move = MOVE_GUARD_SPLIT,
			.Level = 27,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 31,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 35,
		},
		{
			.Move = MOVE_SKILL_SWAP,
			.Level = 40,
		},
		{
			.Move = MOVE_TRICK_ROOM,
			.Level = 46,
		},
		{
			.Move = MOVE_STONE_EDGE,
			.Level = 49,
		},
		{
			.Move = MOVE_MOONBLAST,
			.Level = 50,
		},
		{
			.Move = MOVE_DIAMOND_STORM,
			.Level = 50,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 60,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 70,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_HOOPA] = {
		{
			.Move = MOVE_HYPERSPACE_HOLE,
			.Level = 1,
		},
		{
			.Move = MOVE_TRICK,
			.Level = 1,
		},
		{
			.Move = MOVE_DESTINY_BOND,
			.Level = 1,
		},
		{
			.Move = MOVE_ALLY_SWITCH,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 6,
		},
		{
			.Move = MOVE_MAGIC_COAT,
			.Level = 10,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 15,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 19,
		},
		{
			.Move = MOVE_SKILL_SWAP,
			.Level = 25,
		},
		{
			.Move = MOVE_POWER_SPLIT,
			.Level = 29,
		},
		{
			.Move = MOVE_GUARD_SPLIT,
			.Level = 29,
		},
		{
			.Move = MOVE_PHANTOM_FORCE,
			.Level = 35,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 46,
		},
		{
			.Move = MOVE_WONDER_ROOM,
			.Level = 50,
		},
		{
			.Move = MOVE_TRICK_ROOM,
			.Level = 50,
		},
		{
			.Move = MOVE_SHADOW_BALL,
			.Level = 55,
		},
		{
			.Move = MOVE_NASTY_PLOT,
			.Level = 68,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 75,
		},
		{
			.Move = MOVE_HYPERSPACE_HOLE,
			.Level = 85,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_VOLCANION] = {
		{
			.Move = MOVE_STEAM_ERUPTION,
			.Level = 1,
		},
		{
			.Move = MOVE_FLARE_BLITZ,
			.Level = 1,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 1,
		},
		{
			.Move = MOVE_MIST,
			.Level = 8,
		},
		{
			.Move = MOVE_HAZE,
			.Level = 11,
		},
		{
			.Move = MOVE_FLAME_CHARGE,
			.Level = 15,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 21,
		},
		{
			.Move = MOVE_STOMP,
			.Level = 28,
		},
		{
			.Move = MOVE_SCALD,
			.Level = 32,
		},
		{
			.Move = MOVE_WEATHER_BALL,
			.Level = 40,
		},
		{
			.Move = MOVE_BODY_SLAM,
			.Level = 46,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 50,
		},
		{
			.Move = MOVE_FLARE_BLITZ,
			.Level = 58,
		},
		{
			.Move = MOVE_OVERHEAT,
			.Level = 65,
		},
		{
			.Move = MOVE_EXPLOSION,
			.Level = 76,
		},
		{
			.Move = MOVE_STEAM_ERUPTION,
			.Level = 85,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_EGG] = {
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_WRAP,
			.Level = 1,
		},
		{
			.Move = MOVE_NIGHT_SHADE,
			.Level = 7,
		},
		{
			.Move = MOVE_TELEPORT,
			.Level = 13,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 19,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 25,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 31,
		},
		{
			.Move = MOVE_SUPERPOWER,
			.Level = 37,
		},
		{
			.Move = MOVE_PSYCHO_SHIFT,
			.Level = 43,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 49,
		},
		{
			.Move = MOVE_COSMIC_POWER,
			.Level = 55,
		},
		{
			.Move = MOVE_ZAP_CANNON,
			.Level = 61,
		},
		{
			.Move = MOVE_PSYCHO_BOOST,
			.Level = 67,
		},
		{
			.Move = MOVE_HYPER_BEAM,
			.Level = 73,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BAD_EGG] = {
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_WRAP,
			.Level = 1,
		},
		{
			.Move = MOVE_NIGHT_SHADE,
			.Level = 7,
		},
		{
			.Move = MOVE_TELEPORT,
			.Level = 13,
		},
		{
			.Move = MOVE_KNOCK_OFF,
			.Level = 19,
		},
		{
			.Move = MOVE_SPIKES,
			.Level = 25,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 31,
		},
		{
			.Move = MOVE_SNATCH,
			.Level = 37,
		},
		{
			.Move = MOVE_PSYCHO_SHIFT,
			.Level = 43,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 49,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 55,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 55,
		},
		{
			.Move = MOVE_RECOVER,
			.Level = 61,
		},
		{
			.Move = MOVE_PSYCHO_BOOST,
			.Level = 67,
		},
		{
			.Move = MOVE_COUNTER,
			.Level = 73,
		},
		{
			.Move = MOVE_MIRROR_COAT,
			.Level = 73,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_UFO] = {
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_WRAP,
			.Level = 1,
		},
		{
			.Move = MOVE_NIGHT_SHADE,
			.Level = 7,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 13,
		},
		{
			.Move = MOVE_KNOCK_OFF,
			.Level = 19,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 25,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 31,
		},
		{
			.Move = MOVE_SWIFT,
			.Level = 37,
		},
		{
			.Move = MOVE_PSYCHO_SHIFT,
			.Level = 43,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 49,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 55,
		},
		{
			.Move = MOVE_RECOVER,
			.Level = 61,
		},
		{
			.Move = MOVE_PSYCHO_BOOST,
			.Level = 67,
		},
		{
			.Move = MOVE_EXTREMESPEED,
			.Level = 73,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BRYCENMAN] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 10,
		},
		{
			.Move = MOVE_BUG_BITE,
			.Level = 15,
		},
		{
			.Move = MOVE_HIDDEN_POWER,
			.Level = 20,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 23,
		},
		{
			.Move = MOVE_ROCK_BLAST,
			.Level = 26,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 29,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 32,
		},
		{
			.Move = MOVE_CAPTIVATE,
			.Level = 35,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 38,
		},
		{
			.Move = MOVE_ATTRACT,
			.Level = 41,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 44,
		},
		{
			.Move = MOVE_FISSURE,
			.Level = 47,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MT] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 10,
		},
		{
			.Move = MOVE_BUG_BITE,
			.Level = 15,
		},
		{
			.Move = MOVE_HIDDEN_POWER,
			.Level = 20,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 23,
		},
		{
			.Move = MOVE_MIRROR_SHOT,
			.Level = 26,
		},
		{
			.Move = MOVE_METAL_SOUND,
			.Level = 29,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 32,
		},
		{
			.Move = MOVE_CAPTIVATE,
			.Level = 35,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 38,
		},
		{
			.Move = MOVE_ATTRACT,
			.Level = 41,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 44,
		},
		{
			.Move = MOVE_IRON_HEAD,
			.Level = 47,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MT2] = {
		{
			.Move = MOVE_GROWTH,
			.Level = 1,
		},
		{
			.Move = MOVE_MAGICAL_LEAF,
			.Level = 10,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 19,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 28,
		},
		{
			.Move = MOVE_SWEET_SCENT,
			.Level = 37,
		},
		{
			.Move = MOVE_NATURAL_GIFT,
			.Level = 46,
		},
		{
			.Move = MOVE_WORRY_SEED,
			.Level = 55,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 64,
		},
		{
			.Move = MOVE_ENERGY_BALL,
			.Level = 73,
		},
		{
			.Move = MOVE_SWEET_KISS,
			.Level = 82,
		},
		{
			.Move = MOVE_LEAF_STORM,
			.Level = 91,
		},
		{
			.Move = MOVE_SEED_FLARE,
			.Level = 100,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_TRANSPORT] = {
		{
			.Move = MOVE_DRAGONBREATH,
			.Level = 1,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 1,
		},
		{
			.Move = MOVE_OMINOUS_WIND,
			.Level = 6,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 10,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 15,
		},
		{
			.Move = MOVE_SHADOW_SNEAK,
			.Level = 19,
		},
		{
			.Move = MOVE_DESTINY_BOND,
			.Level = 24,
		},
		{
			.Move = MOVE_DRAGON_CLAW,
			.Level = 28,
		},
		{
			.Move = MOVE_EARTH_POWER,
			.Level = 33,
		},
		{
			.Move = MOVE_AURA_SPHERE,
			.Level = 37,
		},
		{
			.Move = MOVE_SHADOW_CLAW,
			.Level = 42,
		},
		{
			.Move = MOVE_SHADOW_FORCE,
			.Level = 46,
		},
		{
			.Move = MOVE_HEX,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GIANT_15] = {
		{
			.Move = MOVE_DISCHARGE,
			.Level = 1,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 1,
		},
		{
			.Move = MOVE_TRICK,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 1,
		},
		{
			.Move = MOVE_UPROAR,
			.Level = 8,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 15,
		},
		{
			.Move = MOVE_SHOCK_WAVE,
			.Level = 22,
		},
		{
			.Move = MOVE_OMINOUS_WIND,
			.Level = 29,
		},
		{
			.Move = MOVE_SUBSTITUTE,
			.Level = 36,
		},
		{
			.Move = MOVE_ELECTRO_BALL,
			.Level = 43,
		},
		{
			.Move = MOVE_HEX,
			.Level = 50,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 57,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 64,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_HUMANOID] = {
		{
			.Move = MOVE_DISCHARGE,
			.Level = 1,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 1,
		},
		{
			.Move = MOVE_TRICK,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 1,
		},
		{
			.Move = MOVE_UPROAR,
			.Level = 8,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 15,
		},
		{
			.Move = MOVE_SHOCK_WAVE,
			.Level = 22,
		},
		{
			.Move = MOVE_OMINOUS_WIND,
			.Level = 29,
		},
		{
			.Move = MOVE_SUBSTITUTE,
			.Level = 36,
		},
		{
			.Move = MOVE_ELECTRO_BALL,
			.Level = 43,
		},
		{
			.Move = MOVE_HEX,
			.Level = 50,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 57,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 64,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_MONSTER] = {
		{
			.Move = MOVE_DISCHARGE,
			.Level = 1,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 1,
		},
		{
			.Move = MOVE_TRICK,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 1,
		},
		{
			.Move = MOVE_UPROAR,
			.Level = 8,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 15,
		},
		{
			.Move = MOVE_SHOCK_WAVE,
			.Level = 22,
		},
		{
			.Move = MOVE_OMINOUS_WIND,
			.Level = 29,
		},
		{
			.Move = MOVE_SUBSTITUTE,
			.Level = 36,
		},
		{
			.Move = MOVE_ELECTRO_BALL,
			.Level = 43,
		},
		{
			.Move = MOVE_HEX,
			.Level = 50,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 57,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 64,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_F00] = {
		{
			.Move = MOVE_DISCHARGE,
			.Level = 1,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 1,
		},
		{
			.Move = MOVE_TRICK,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 1,
		},
		{
			.Move = MOVE_UPROAR,
			.Level = 8,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 15,
		},
		{
			.Move = MOVE_SHOCK_WAVE,
			.Level = 22,
		},
		{
			.Move = MOVE_OMINOUS_WIND,
			.Level = 29,
		},
		{
			.Move = MOVE_SUBSTITUTE,
			.Level = 36,
		},
		{
			.Move = MOVE_ELECTRO_BALL,
			.Level = 43,
		},
		{
			.Move = MOVE_HEX,
			.Level = 50,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 57,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 64,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SPIRIT] = {
		{
			.Move = MOVE_DISCHARGE,
			.Level = 1,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 1,
		},
		{
			.Move = MOVE_TRICK,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 1,
		},
		{
			.Move = MOVE_UPROAR,
			.Level = 8,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 15,
		},
		{
			.Move = MOVE_SHOCK_WAVE,
			.Level = 22,
		},
		{
			.Move = MOVE_OMINOUS_WIND,
			.Level = 29,
		},
		{
			.Move = MOVE_SUBSTITUTE,
			.Level = 36,
		},
		{
			.Move = MOVE_ELECTRO_BALL,
			.Level = 43,
		},
		{
			.Move = MOVE_HEX,
			.Level = 50,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 57,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 64,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_WHITE_DOOR] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 10,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 10,
		},
		{
			.Move = MOVE_POWDER_SNOW,
			.Level = 10,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 15,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 20,
		},
		{
			.Move = MOVE_SUNNY_DAY,
			.Level = 20,
		},
		{
			.Move = MOVE_HAIL,
			.Level = 20,
		},
		{
			.Move = MOVE_WEATHER_BALL,
			.Level = 25,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 35,
		},
		{
			.Move = MOVE_FIRE_BLAST,
			.Level = 35,
		},
		{
			.Move = MOVE_BLIZZARD,
			.Level = 35,
		},
		{
			.Move = MOVE_HURRICANE,
			.Level = 45,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BLACK_DOOR] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 10,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 10,
		},
		{
			.Move = MOVE_POWDER_SNOW,
			.Level = 10,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 15,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 20,
		},
		{
			.Move = MOVE_SUNNY_DAY,
			.Level = 20,
		},
		{
			.Move = MOVE_HAIL,
			.Level = 20,
		},
		{
			.Move = MOVE_WEATHER_BALL,
			.Level = 25,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 35,
		},
		{
			.Move = MOVE_FIRE_BLAST,
			.Level = 35,
		},
		{
			.Move = MOVE_BLIZZARD,
			.Level = 35,
		},
		{
			.Move = MOVE_HURRICANE,
			.Level = 45,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PROP_U1] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 10,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 10,
		},
		{
			.Move = MOVE_POWDER_SNOW,
			.Level = 10,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 15,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 20,
		},
		{
			.Move = MOVE_SUNNY_DAY,
			.Level = 20,
		},
		{
			.Move = MOVE_HAIL,
			.Level = 20,
		},
		{
			.Move = MOVE_WEATHER_BALL,
			.Level = 25,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 35,
		},
		{
			.Move = MOVE_FIRE_BLAST,
			.Level = 35,
		},
		{
			.Move = MOVE_BLIZZARD,
			.Level = 35,
		},
		{
			.Move = MOVE_HURRICANE,
			.Level = 45,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PROP_U2] = {
		{
			.Move = MOVE_MORNING_SUN,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWTH,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWTH,
			.Level = 7,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 10,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 13,
		},
		{
			.Move = MOVE_MAGICAL_LEAF,
			.Level = 19,
		},
		{
			.Move = MOVE_SUNNY_DAY,
			.Level = 22,
		},
		{
			.Move = MOVE_PETAL_DANCE,
			.Level = 25,
		},
		{
			.Move = MOVE_WORRY_SEED,
			.Level = 30,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 35,
		},
		{
			.Move = MOVE_SOLARBEAM,
			.Level = 43,
		},
		{
			.Move = MOVE_LUCKY_CHANT,
			.Level = 48,
		},
		{
			.Move = MOVE_PETAL_BLIZZARD,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PROP_H1] = {
		{
			.Move = MOVE_THRASH,
			.Level = 1,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_UPROAR,
			.Level = 4,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 7,
		},
		{
			.Move = MOVE_BITE,
			.Level = 10,
		},
		{
			.Move = MOVE_AQUA_JET,
			.Level = 13,
		},
		{
			.Move = MOVE_CHIP_AWAY,
			.Level = 16,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 20,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 24,
		},
		{
			.Move = MOVE_AQUA_TAIL,
			.Level = 28,
		},
		{
			.Move = MOVE_SOAK,
			.Level = 32,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 36,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 41,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 46,
		},
		{
			.Move = MOVE_FINAL_GAMBIT,
			.Level = 50,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 56,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PROP_M1] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 1,
		},
		{
			.Move = MOVE_INCINERATE,
			.Level = 1,
		},
		{
			.Move = MOVE_RAGE,
			.Level = 1,
		},
		{
			.Move = MOVE_ROLLOUT,
			.Level = 3,
		},
		{
			.Move = MOVE_INCINERATE,
			.Level = 6,
		},
		{
			.Move = MOVE_RAGE,
			.Level = 9,
		},
		{
			.Move = MOVE_FIRE_FANG,
			.Level = 11,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 14,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 17,
		},
		{
			.Move = MOVE_FACADE,
			.Level = 19,
		},
		{
			.Move = MOVE_FIRE_PUNCH,
			.Level = 22,
		},
		{
			.Move = MOVE_WORK_UP,
			.Level = 25,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 27,
		},
		{
			.Move = MOVE_BELLY_DRUM,
			.Level = 30,
		},
		{
			.Move = MOVE_FLARE_BLITZ,
			.Level = 33,
		},
		{
			.Move = MOVE_HAMMER_ARM,
			.Level = 35,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 39,
		},
		{
			.Move = MOVE_SUPERPOWER,
			.Level = 47,
		},
		{
			.Move = MOVE_OVERHEAT,
			.Level = 54,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PROP_M2] = {
		{
			.Move = MOVE_ROUND,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 6,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 11,
		},
		{
			.Move = MOVE_SING,
			.Level = 16,
		},
		{
			.Move = MOVE_TEETER_DANCE,
			.Level = 21,
		},
		{
			.Move = MOVE_ACROBATICS,
			.Level = 26,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 31,
		},
		{
			.Move = MOVE_ECHOED_VOICE,
			.Level = 36,
		},
		{
			.Move = MOVE_UTURN,
			.Level = 43,
		},
		{
			.Move = MOVE_WAKEUP_SLAP,
			.Level = 50,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 57,
		},
		{
			.Move = MOVE_HYPER_VOICE,
			.Level = 64,
		},
		{
			.Move = MOVE_ROLE_PLAY,
			.Level = 71,
		},
		{
			.Move = MOVE_CLOSE_COMBAT,
			.Level = 78,
		},
		{
			.Move = MOVE_PERISH_SONG,
			.Level = 85,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PROP_T1] = {
		{
			.Move = MOVE_ICY_WIND,
			.Level = 1,
		},
		{
			.Move = MOVE_DRAGON_RAGE,
			.Level = 1,
		},
		{
			.Move = MOVE_IMPRISON,
			.Level = 8,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 15,
		},
		{
			.Move = MOVE_ICE_BEAM,
			.Level = 22,
		},
		{
			.Move = MOVE_DRAGONBREATH,
			.Level = 29,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 36,
		},
		{
			.Move = MOVE_FUSION_FLARE,
			.Level = 43,
		},
		{
			.Move = MOVE_ICE_BURN,
			.Level = 50,
		},
		{
			.Move = MOVE_DRAGON_PULSE,
			.Level = 57,
		},
		{
			.Move = MOVE_IMPRISON,
			.Level = 64,
		},
		{
			.Move = MOVE_ENDEAVOR,
			.Level = 71,
		},
		{
			.Move = MOVE_BLIZZARD,
			.Level = 78,
		},
		{
			.Move = MOVE_OUTRAGE,
			.Level = 85,
		},
		{
			.Move = MOVE_HYPER_VOICE,
			.Level = 92,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PROP_O1] = {
		{
			.Move = MOVE_ICY_WIND,
			.Level = 1,
		},
		{
			.Move = MOVE_DRAGON_RAGE,
			.Level = 1,
		},
		{
			.Move = MOVE_IMPRISON,
			.Level = 8,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 15,
		},
		{
			.Move = MOVE_ICE_BEAM,
			.Level = 22,
		},
		{
			.Move = MOVE_DRAGONBREATH,
			.Level = 29,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 36,
		},
		{
			.Move = MOVE_FUSION_BOLT,
			.Level = 43,
		},
		{
			.Move = MOVE_FREEZE_SHOCK,
			.Level = 50,
		},
		{
			.Move = MOVE_DRAGON_PULSE,
			.Level = 57,
		},
		{
			.Move = MOVE_IMPRISON,
			.Level = 64,
		},
		{
			.Move = MOVE_ENDEAVOR,
			.Level = 71,
		},
		{
			.Move = MOVE_BLIZZARD,
			.Level = 78,
		},
		{
			.Move = MOVE_OUTRAGE,
			.Level = 85,
		},
		{
			.Move = MOVE_HYPER_VOICE,
			.Level = 92,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PROP_O2] = {
		{
			.Move = MOVE_AQUA_JET,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_DOUBLE_KICK,
			.Level = 7,
		},
		{
			.Move = MOVE_BUBBLEBEAM,
			.Level = 13,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 19,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 25,
		},
		{
			.Move = MOVE_RETALIATE,
			.Level = 31,
		},
		{
			.Move = MOVE_AQUA_TAIL,
			.Level = 37,
		},
		{
			.Move = MOVE_SACRED_SWORD,
			.Level = 43,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 49,
		},
		{
			.Move = MOVE_QUICK_GUARD,
			.Level = 55,
		},
		{
			.Move = MOVE_WORK_UP,
			.Level = 61,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 67,
		},
		{
			.Move = MOVE_CLOSE_COMBAT,
			.Level = 73,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PROP_C1] = {
		{
			.Move = MOVE_THRASH,
			.Level = 1,
		},
		{
			.Move = MOVE_HAMMER_ARM,
			.Level = 1,
		},
		{
			.Move = MOVE_HURRICANE,
			.Level = 1,
		},
		{
			.Move = MOVE_TAILWIND,
			.Level = 1,
		},
		{
			.Move = MOVE_UPROAR,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_GUST,
			.Level = 1,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 7,
		},
		{
			.Move = MOVE_BITE,
			.Level = 13,
		},
		{
			.Move = MOVE_REVENGE,
			.Level = 19,
		},
		{
			.Move = MOVE_AIR_CUTTER,
			.Level = 25,
		},
		{
			.Move = MOVE_EXTRASENSORY,
			.Level = 31,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 37,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 43,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 49,
		},
		{
			.Move = MOVE_TAILWIND,
			.Level = 55,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 61,
		},
		{
			.Move = MOVE_HURRICANE,
			.Level = 67,
		},
		{
			.Move = MOVE_DARK_PULSE,
			.Level = 73,
		},
		{
			.Move = MOVE_HAMMER_ARM,
			.Level = 79,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 85,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PROP_C2] = {
		{
			.Move = MOVE_THRASH,
			.Level = 1,
		},
		{
			.Move = MOVE_HAMMER_ARM,
			.Level = 1,
		},
		{
			.Move = MOVE_NASTY_PLOT,
			.Level = 1,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 1,
		},
		{
			.Move = MOVE_UPROAR,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 1,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 7,
		},
		{
			.Move = MOVE_BITE,
			.Level = 13,
		},
		{
			.Move = MOVE_REVENGE,
			.Level = 19,
		},
		{
			.Move = MOVE_SHOCK_WAVE,
			.Level = 25,
		},
		{
			.Move = MOVE_HEAL_BLOCK,
			.Level = 31,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 37,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 43,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 49,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 55,
		},
		{
			.Move = MOVE_NASTY_PLOT,
			.Level = 61,
		},
		{
			.Move = MOVE_THUNDER,
			.Level = 67,
		},
		{
			.Move = MOVE_DARK_PULSE,
			.Level = 73,
		},
		{
			.Move = MOVE_HAMMER_ARM,
			.Level = 79,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 85,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PROP_G1] = {
		{
			.Move = MOVE_OUTRAGE,
			.Level = 1,
		},
		{
			.Move = MOVE_HAMMER_ARM,
			.Level = 1,
		},
		{
			.Move = MOVE_FISSURE,
			.Level = 1,
		},
		{
			.Move = MOVE_BLOCK,
			.Level = 1,
		},
		{
			.Move = MOVE_MUD_SHOT,
			.Level = 1,
		},
		{
			.Move = MOVE_ROCK_TOMB,
			.Level = 1,
		},
		{
			.Move = MOVE_IMPRISON,
			.Level = 7,
		},
		{
			.Move = MOVE_PUNISHMENT,
			.Level = 13,
		},
		{
			.Move = MOVE_BULLDOZE,
			.Level = 19,
		},
		{
			.Move = MOVE_ROCK_THROW,
			.Level = 25,
		},
		{
			.Move = MOVE_EXTRASENSORY,
			.Level = 31,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 37,
		},
		{
			.Move = MOVE_EARTH_POWER,
			.Level = 43,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 49,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 55,
		},
		{
			.Move = MOVE_SANDSTORM,
			.Level = 61,
		},
		{
			.Move = MOVE_FISSURE,
			.Level = 67,
		},
		{
			.Move = MOVE_STONE_EDGE,
			.Level = 73,
		},
		{
			.Move = MOVE_HAMMER_ARM,
			.Level = 79,
		},
		{
			.Move = MOVE_OUTRAGE,
			.Level = 85,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PROP_W1] = {
		{
			.Move = MOVE_HYPNOSIS,
			.Level = 1,
		},
		{
			.Move = MOVE_LICK,
			.Level = 1,
		},
		{
			.Move = MOVE_SPITE,
			.Level = 1,
		},
		{
			.Move = MOVE_SPITE,
			.Level = 5,
		},
		{
			.Move = MOVE_MEAN_LOOK,
			.Level = 8,
		},
		{
			.Move = MOVE_CURSE,
			.Level = 12,
		},
		{
			.Move = MOVE_NIGHT_SHADE,
			.Level = 15,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 19,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 22,
		},
		{
			.Move = MOVE_SHADOW_PUNCH,
			.Level = 25,
		},
		{
			.Move = MOVE_PAYBACK,
			.Level = 28,
		},
		{
			.Move = MOVE_SHADOW_BALL,
			.Level = 33,
		},
		{
			.Move = MOVE_DREAM_EATER,
			.Level = 39,
		},
		{
			.Move = MOVE_DARK_PULSE,
			.Level = 44,
		},
		{
			.Move = MOVE_DESTINY_BOND,
			.Level = 50,
		},
		{
			.Move = MOVE_HEX,
			.Level = 55,
		},
		{
			.Move = MOVE_NIGHTMARE,
			.Level = 61,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PROP_W2] = {
		{
			.Move = MOVE_STORED_POWER,
			.Level = 1,
		},
		{
			.Move = MOVE_ME_FIRST,
			.Level = 1,
		},
		{
			.Move = MOVE_MAGICAL_LEAF,
			.Level = 1,
		},
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_COVET,
			.Level = 5,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 9,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 13,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 17,
		},
		{
			.Move = MOVE_FAKE_OUT,
			.Level = 19,
		},
		{
			.Move = MOVE_DISARMING_VOICE,
			.Level = 22,
		},
		{
			.Move = MOVE_PSYSHOCK,
			.Level = 25,
		},
		{
			.Move = MOVE_CHARGE_BEAM,
			.Level = 28,
		},
		{
			.Move = MOVE_SHADOW_BALL,
			.Level = 31,
		},
		{
			.Move = MOVE_EXTRASENSORY,
			.Level = 35,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 40,
		},
		{
			.Move = MOVE_ROLE_PLAY,
			.Level = 43,
		},
		{
			.Move = MOVE_SIGNAL_BEAM,
			.Level = 45,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 48,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 50,
		},
		{
			.Move = MOVE_STORED_POWER,
			.Level = 53,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PROP_R1] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 5,
		},
		{
			.Move = MOVE_BABYDOLL_EYES,
			.Level = 9,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 12,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 15,
		},
		{
			.Move = MOVE_BITE,
			.Level = 22,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 27,
		},
		{
			.Move = MOVE_RETALIATE,
			.Level = 33,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 35,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 38,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 42,
		},
		{
			.Move = MOVE_COTTON_GUARD,
			.Level = 48,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PROP_R2] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 5,
		},
		{
			.Move = MOVE_BABYDOLL_EYES,
			.Level = 9,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 12,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 15,
		},
		{
			.Move = MOVE_BITE,
			.Level = 22,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 27,
		},
		{
			.Move = MOVE_RETALIATE,
			.Level = 33,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 35,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 38,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 42,
		},
		{
			.Move = MOVE_COTTON_GUARD,
			.Level = 48,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_PROP_K1] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 5,
		},
		{
			.Move = MOVE_BABYDOLL_EYES,
			.Level = 9,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 12,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 15,
		},
		{
			.Move = MOVE_BITE,
			.Level = 22,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 27,
		},
		{
			.Move = MOVE_RETALIATE,
			.Level = 33,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 35,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 38,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 42,
		},
		{
			.Move = MOVE_COTTON_GUARD,
			.Level = 48,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_UFO_2] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 5,
		},
		{
			.Move = MOVE_BABYDOLL_EYES,
			.Level = 9,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 12,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 15,
		},
		{
			.Move = MOVE_BITE,
			.Level = 22,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 27,
		},
		{
			.Move = MOVE_RETALIATE,
			.Level = 33,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 35,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 38,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 42,
		},
		{
			.Move = MOVE_COTTON_GUARD,
			.Level = 48,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_GIANT_15_2] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 5,
		},
		{
			.Move = MOVE_BABYDOLL_EYES,
			.Level = 9,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 12,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 15,
		},
		{
			.Move = MOVE_BITE,
			.Level = 22,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 27,
		},
		{
			.Move = MOVE_RETALIATE,
			.Level = 33,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 35,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 38,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 42,
		},
		{
			.Move = MOVE_COTTON_GUARD,
			.Level = 48,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_F002] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 5,
		},
		{
			.Move = MOVE_BABYDOLL_EYES,
			.Level = 9,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 12,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 15,
		},
		{
			.Move = MOVE_BITE,
			.Level = 22,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 27,
		},
		{
			.Move = MOVE_RETALIATE,
			.Level = 33,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 35,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 38,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 42,
		},
		{
			.Move = MOVE_COTTON_GUARD,
			.Level = 48,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_BLACK_BELT] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 5,
		},
		{
			.Move = MOVE_BABYDOLL_EYES,
			.Level = 9,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 12,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 15,
		},
		{
			.Move = MOVE_BITE,
			.Level = 22,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 27,
		},
		{
			.Move = MOVE_RETALIATE,
			.Level = 33,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 35,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 38,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 42,
		},
		{
			.Move = MOVE_COTTON_GUARD,
			.Level = 48,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_SMEARGLE_2] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 5,
		},
		{
			.Move = MOVE_BABYDOLL_EYES,
			.Level = 9,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 12,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 15,
		},
		{
			.Move = MOVE_BITE,
			.Level = 22,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 27,
		},
		{
			.Move = MOVE_RETALIATE,
			.Level = 33,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 35,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 38,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 42,
		},
		{
			.Move = MOVE_COTTON_GUARD,
			.Level = 48,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_EGG] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 5,
		},
		{
			.Move = MOVE_BABYDOLL_EYES,
			.Level = 9,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 12,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 15,
		},
		{
			.Move = MOVE_BITE,
			.Level = 22,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 27,
		},
		{
			.Move = MOVE_RETALIATE,
			.Level = 33,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 35,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 38,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 42,
		},
		{
			.Move = MOVE_COTTON_GUARD,
			.Level = 48,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_EGG] = {
		{
			.Move = MOVE_MOONBLAST,
			.Level = 1,
		},
		{
			.Move = MOVE_STORED_POWER,
			.Level = 1,
		},
		{
			.Move = MOVE_MISTY_TERRAIN,
			.Level = 1,
		},
		{
			.Move = MOVE_HEALING_WISH,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 1,
		},
		{
			.Move = MOVE_TELEPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 4,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 6,
		},
		{
			.Move = MOVE_TELEPORT,
			.Level = 9,
		},
		{
			.Move = MOVE_DISARMING_VOICE,
			.Level = 11,
		},
		{
			.Move = MOVE_WISH,
			.Level = 14,
		},
		{
			.Move = MOVE_MAGICAL_LEAF,
			.Level = 17,
		},
		{
			.Move = MOVE_HEAL_PULSE,
			.Level = 19,
		},
		{
			.Move = MOVE_DRAINING_KISS,
			.Level = 23,
		},
		{
			.Move = MOVE_CALM_MIND,
			.Level = 26,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 31,
		},
		{
			.Move = MOVE_IMPRISON,
			.Level = 35,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 40,
		},
		{
			.Move = MOVE_CAPTIVATE,
			.Level = 44,
		},
		{
			.Move = MOVE_HYPNOSIS,
			.Level = 49,
		},
		{
			.Move = MOVE_DREAM_EATER,
			.Level = 53,
		},
		{
			.Move = MOVE_STORED_POWER,
			.Level = 58,
		},
		{
			.Move = MOVE_MOONBLAST,
			.Level = 62,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_759] = {
		{
			.Move = MOVE_ZAP_CANNON,
			.Level = 1,
		},
		{
			.Move = MOVE_MAGNETIC_FLUX,
			.Level = 1,
		},
		{
			.Move = MOVE_ION_DELUGE,
			.Level = 1,
		},
		{
			.Move = MOVE_DRAGON_PULSE,
			.Level = 1,
		},
		{
			.Move = MOVE_FIRE_PUNCH,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 4,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 8,
		},
		{
			.Move = MOVE_COTTON_SPORE,
			.Level = 11,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 16,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 20,
		},
		{
			.Move = MOVE_ELECTRO_BALL,
			.Level = 25,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 29,
		},
		{
			.Move = MOVE_THUNDERPUNCH,
			.Level = 30,
		},
		{
			.Move = MOVE_POWER_GEM,
			.Level = 35,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 40,
		},
		{
			.Move = MOVE_COTTON_GUARD,
			.Level = 46,
		},
		{
			.Move = MOVE_SIGNAL_BEAM,
			.Level = 51,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 57,
		},
		{
			.Move = MOVE_THUNDER,
			.Level = 62,
		},
		{
			.Move = MOVE_DRAGON_PULSE,
			.Level = 65,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_760] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 1,
		},
		{
			.Move = MOVE_VINE_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 3,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 7,
		},
		{
			.Move = MOVE_VINE_WHIP,
			.Level = 9,
		},
		{
			.Move = MOVE_POISONPOWDER,
			.Level = 13,
		},
		{
			.Move = MOVE_SLEEP_POWDER,
			.Level = 13,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 15,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 20,
		},
		{
			.Move = MOVE_SWEET_SCENT,
			.Level = 23,
		},
		{
			.Move = MOVE_GROWTH,
			.Level = 28,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 31,
		},
		{
			.Move = MOVE_PETAL_DANCE,
			.Level = 32,
		},
		{
			.Move = MOVE_WORRY_SEED,
			.Level = 39,
		},
		{
			.Move = MOVE_SYNTHESIS,
			.Level = 45,
		},
		{
			.Move = MOVE_PETAL_BLIZZARD,
			.Level = 50,
		},
		{
			.Move = MOVE_SOLARBEAM,
			.Level = 53,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_761] = {
		{
			.Move = MOVE_FLARE_BLITZ,
			.Level = 1,
		},
		{
			.Move = MOVE_HEAT_WAVE,
			.Level = 1,
		},
		{
			.Move = MOVE_DRAGON_CLAW,
			.Level = 1,
		},
		{
			.Move = MOVE_SHADOW_CLAW,
			.Level = 1,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 1,
		},
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 1,
		},
		{
			.Move = MOVE_SMOKESCREEN,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 7,
		},
		{
			.Move = MOVE_SMOKESCREEN,
			.Level = 10,
		},
		{
			.Move = MOVE_DRAGON_RAGE,
			.Level = 17,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 21,
		},
		{
			.Move = MOVE_FIRE_FANG,
			.Level = 28,
		},
		{
			.Move = MOVE_FLAME_BURST,
			.Level = 32,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 36,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 41,
		},
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 47,
		},
		{
			.Move = MOVE_FIRE_SPIN,
			.Level = 56,
		},
		{
			.Move = MOVE_INFERNO,
			.Level = 62,
		},
		{
			.Move = MOVE_HEAT_WAVE,
			.Level = 71,
		},
		{
			.Move = MOVE_FLARE_BLITZ,
			.Level = 77,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_762] = {
		{
			.Move = MOVE_FLARE_BLITZ,
			.Level = 1,
		},
		{
			.Move = MOVE_HEAT_WAVE,
			.Level = 1,
		},
		{
			.Move = MOVE_DRAGON_CLAW,
			.Level = 1,
		},
		{
			.Move = MOVE_SHADOW_CLAW,
			.Level = 1,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 1,
		},
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 1,
		},
		{
			.Move = MOVE_SMOKESCREEN,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 7,
		},
		{
			.Move = MOVE_SMOKESCREEN,
			.Level = 10,
		},
		{
			.Move = MOVE_DRAGON_RAGE,
			.Level = 17,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 21,
		},
		{
			.Move = MOVE_FIRE_FANG,
			.Level = 28,
		},
		{
			.Move = MOVE_FLAME_BURST,
			.Level = 32,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 36,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 41,
		},
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 47,
		},
		{
			.Move = MOVE_FIRE_SPIN,
			.Level = 56,
		},
		{
			.Move = MOVE_INFERNO,
			.Level = 62,
		},
		{
			.Move = MOVE_HEAT_WAVE,
			.Level = 71,
		},
		{
			.Move = MOVE_FLARE_BLITZ,
			.Level = 77,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_763] = {
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_DISABLE,
			.Level = 1,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 1,
		},
		{
			.Move = MOVE_SWIFT,
			.Level = 8,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 15,
		},
		{
			.Move = MOVE_PSYCH_UP,
			.Level = 22,
		},
		{
			.Move = MOVE_MIRACLE_EYE,
			.Level = 29,
		},
		{
			.Move = MOVE_PSYCHO_CUT,
			.Level = 36,
		},
		{
			.Move = MOVE_POWER_SWAP,
			.Level = 43,
		},
		{
			.Move = MOVE_GUARD_SWAP,
			.Level = 43,
		},
		{
			.Move = MOVE_RECOVER,
			.Level = 50,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 57,
		},
		{
			.Move = MOVE_BARRIER,
			.Level = 64,
		},
		{
			.Move = MOVE_AURA_SPHERE,
			.Level = 70,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 79,
		},
		{
			.Move = MOVE_MIST,
			.Level = 86,
		},
		{
			.Move = MOVE_ME_FIRST,
			.Level = 93,
		},
		{
			.Move = MOVE_PSYSTRIKE,
			.Level = 100,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_764] = {
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_DISABLE,
			.Level = 1,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 1,
		},
		{
			.Move = MOVE_SWIFT,
			.Level = 8,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 15,
		},
		{
			.Move = MOVE_PSYCH_UP,
			.Level = 22,
		},
		{
			.Move = MOVE_MIRACLE_EYE,
			.Level = 29,
		},
		{
			.Move = MOVE_PSYCHO_CUT,
			.Level = 36,
		},
		{
			.Move = MOVE_POWER_SWAP,
			.Level = 43,
		},
		{
			.Move = MOVE_GUARD_SWAP,
			.Level = 43,
		},
		{
			.Move = MOVE_RECOVER,
			.Level = 50,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 57,
		},
		{
			.Move = MOVE_BARRIER,
			.Level = 64,
		},
		{
			.Move = MOVE_AURA_SPHERE,
			.Level = 70,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 79,
		},
		{
			.Move = MOVE_MIST,
			.Level = 86,
		},
		{
			.Move = MOVE_ME_FIRST,
			.Level = 93,
		},
		{
			.Move = MOVE_PSYSTRIKE,
			.Level = 100,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_765] = {
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 1,
		},
		{
			.Move = MOVE_DOUBLE_KICK,
			.Level = 1,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 1,
		},
		{
			.Move = MOVE_BULK_UP,
			.Level = 1,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_766] = {
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 1,
		},
		{
			.Move = MOVE_FIRE_PUNCH,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDERPUNCH,
			.Level = 1,
		},
		{
			.Move = MOVE_ICE_PUNCH,
			.Level = 1,
		},
		{
			.Move = MOVE_BIDE,
			.Level = 1,
		},
		{
			.Move = MOVE_MEDITATE,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_DETECT,
			.Level = 1,
		},
		{
			.Move = MOVE_MEDITATE,
			.Level = 4,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 7,
		},
		{
			.Move = MOVE_DETECT,
			.Level = 9,
		},
		{
			.Move = MOVE_ENDURE,
			.Level = 12,
		},
		{
			.Move = MOVE_FEINT,
			.Level = 15,
		},
		{
			.Move = MOVE_FORCE_PALM,
			.Level = 17,
		},
		{
			.Move = MOVE_HIDDEN_POWER,
			.Level = 20,
		},
		{
			.Move = MOVE_CALM_MIND,
			.Level = 23,
		},
		{
			.Move = MOVE_MIND_READER,
			.Level = 25,
		},
		{
			.Move = MOVE_HI_JUMP_KICK,
			.Level = 28,
		},
		{
			.Move = MOVE_PSYCH_UP,
			.Level = 31,
		},
		{
			.Move = MOVE_ACUPRESSURE,
			.Level = 33,
		},
		{
			.Move = MOVE_POWER_TRICK,
			.Level = 36,
		},
		{
			.Move = MOVE_REVERSAL,
			.Level = 42,
		},
		{
			.Move = MOVE_RECOVER,
			.Level = 47,
		},
		{
			.Move = MOVE_COUNTER,
			.Level = 53,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_767] = {
		{
			.Move = MOVE_INFERNO,
			.Level = 1,
		},
		{
			.Move = MOVE_NASTY_PLOT,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 1,
		},
		{
			.Move = MOVE_HOWL,
			.Level = 1,
		},
		{
			.Move = MOVE_SMOG,
			.Level = 1,
		},
		{
			.Move = MOVE_HOWL,
			.Level = 4,
		},
		{
			.Move = MOVE_SMOG,
			.Level = 8,
		},
		{
			.Move = MOVE_ROAR,
			.Level = 13,
		},
		{
			.Move = MOVE_BITE,
			.Level = 16,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 20,
		},
		{
			.Move = MOVE_BEAT_UP,
			.Level = 26,
		},
		{
			.Move = MOVE_FIRE_FANG,
			.Level = 30,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 35,
		},
		{
			.Move = MOVE_EMBARGO,
			.Level = 41,
		},
		{
			.Move = MOVE_FOUL_PLAY,
			.Level = 45,
		},
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 50,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 56,
		},
		{
			.Move = MOVE_NASTY_PLOT,
			.Level = 60,
		},
		{
			.Move = MOVE_INFERNO,
			.Level = 65,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_768] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 1,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 1,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 1,
		},
		{
			.Move = MOVE_MUDSLAP,
			.Level = 4,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 7,
		},
		{
			.Move = MOVE_METAL_CLAW,
			.Level = 10,
		},
		{
			.Move = MOVE_ROCK_TOMB,
			.Level = 13,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 16,
		},
		{
			.Move = MOVE_ROAR,
			.Level = 19,
		},
		{
			.Move = MOVE_IRON_HEAD,
			.Level = 22,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 25,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 28,
		},
		{
			.Move = MOVE_METAL_SOUND,
			.Level = 31,
		},
		{
			.Move = MOVE_IRON_TAIL,
			.Level = 35,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 39,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 45,
		},
		{
			.Move = MOVE_AUTOTOMIZE,
			.Level = 51,
		},
		{
			.Move = MOVE_HEAVY_SLAM,
			.Level = 57,
		},
		{
			.Move = MOVE_METAL_BURST,
			.Level = 63,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_769] = {
		{
			.Move = MOVE_PHANTOM_FORCE,
			.Level = 1,
		},
		{
			.Move = MOVE_KNOCK_OFF,
			.Level = 1,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 1,
		},
		{
			.Move = MOVE_NIGHT_SHADE,
			.Level = 1,
		},
		{
			.Move = MOVE_SPITE,
			.Level = 1,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 4,
		},
		{
			.Move = MOVE_NIGHT_SHADE,
			.Level = 7,
		},
		{
			.Move = MOVE_SPITE,
			.Level = 10,
		},
		{
			.Move = MOVE_SHADOW_SNEAK,
			.Level = 13,
		},
		{
			.Move = MOVE_WILLOWISP,
			.Level = 16,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 19,
		},
		{
			.Move = MOVE_HEX,
			.Level = 22,
		},
		{
			.Move = MOVE_CURSE,
			.Level = 26,
		},
		{
			.Move = MOVE_SHADOW_BALL,
			.Level = 30,
		},
		{
			.Move = MOVE_EMBARGO,
			.Level = 34,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 40,
		},
		{
			.Move = MOVE_SNATCH,
			.Level = 46,
		},
		{
			.Move = MOVE_GRUDGE,
			.Level = 52,
		},
		{
			.Move = MOVE_TRICK,
			.Level = 58,
		},
		{
			.Move = MOVE_PHANTOM_FORCE,
			.Level = 64,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_770] = {
		{
			.Move = MOVE_THUNDER_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_ICE_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_FIRE_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDSTORM,
			.Level = 1,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDSTORM,
			.Level = 5,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 10,
		},
		{
			.Move = MOVE_CHIP_AWAY,
			.Level = 14,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 19,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 23,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 28,
		},
		{
			.Move = MOVE_DARK_PULSE,
			.Level = 34,
		},
		{
			.Move = MOVE_PAYBACK,
			.Level = 41,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 47,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 54,
		},
		{
			.Move = MOVE_STONE_EDGE,
			.Level = 63,
		},
		{
			.Move = MOVE_HYPER_BEAM,
			.Level = 73,
		},
		{
			.Move = MOVE_GIGA_IMPACT,
			.Level = 82,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_771] = {
		{
			.Move = MOVE_FEINT,
			.Level = 1,
		},
		{
			.Move = MOVE_BULLET_PUNCH,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 5,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 9,
		},
		{
			.Move = MOVE_FALSE_SWIPE,
			.Level = 13,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 17,
		},
		{
			.Move = MOVE_METAL_CLAW,
			.Level = 21,
		},
		{
			.Move = MOVE_FURY_CUTTER,
			.Level = 25,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 29,
		},
		{
			.Move = MOVE_RAZOR_WIND,
			.Level = 33,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 37,
		},
		{
			.Move = MOVE_XSCISSOR,
			.Level = 41,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 45,
		},
		{
			.Move = MOVE_DOUBLE_HIT,
			.Level = 49,
		},
		{
			.Move = MOVE_IRON_HEAD,
			.Level = 50,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 57,
		},
		{
			.Move = MOVE_FEINT,
			.Level = 61,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_772] = {
		{
			.Move = MOVE_VICEGRIP,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 1,
		},
		{
			.Move = MOVE_BIND,
			.Level = 4,
		},
		{
			.Move = MOVE_SEISMIC_TOSS,
			.Level = 8,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 11,
		},
		{
			.Move = MOVE_REVENGE,
			.Level = 15,
		},
		{
			.Move = MOVE_VITAL_THROW,
			.Level = 18,
		},
		{
			.Move = MOVE_DOUBLE_HIT,
			.Level = 22,
		},
		{
			.Move = MOVE_BRICK_BREAK,
			.Level = 26,
		},
		{
			.Move = MOVE_SUBMISSION,
			.Level = 29,
		},
		{
			.Move = MOVE_XSCISSOR,
			.Level = 33,
		},
		{
			.Move = MOVE_STORM_THROW,
			.Level = 36,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 40,
		},
		{
			.Move = MOVE_THRASH,
			.Level = 43,
		},
		{
			.Move = MOVE_SUPERPOWER,
			.Level = 47,
		},
		{
			.Move = MOVE_GUILLOTINE,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_773] = {
		{
			.Move = MOVE_IRON_HEAD,
			.Level = 1,
		},
		{
			.Move = MOVE_ICE_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_FIRE_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_SUPERSONIC,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 1,
		},
		{
			.Move = MOVE_ROAR,
			.Level = 9,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 17,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 25,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 33,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 41,
		},
		{
			.Move = MOVE_SKY_DROP,
			.Level = 49,
		},
		{
			.Move = MOVE_IRON_HEAD,
			.Level = 57,
		},
		{
			.Move = MOVE_HYPER_BEAM,
			.Level = 65,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 73,
		},
		{
			.Move = MOVE_GIGA_IMPACT,
			.Level = 81,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_774] = {
		{
			.Move = MOVE_EXTREMESPEED,
			.Level = 1,
		},
		{
			.Move = MOVE_DRAGON_PULSE,
			.Level = 1,
		},
		{
			.Move = MOVE_CLOSE_COMBAT,
			.Level = 1,
		},
		{
			.Move = MOVE_AURA_SPHERE,
			.Level = 1,
		},
		{
			.Move = MOVE_FORESIGHT,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_DETECT,
			.Level = 1,
		},
		{
			.Move = MOVE_METAL_CLAW,
			.Level = 1,
		},
		{
			.Move = MOVE_COUNTER,
			.Level = 6,
		},
		{
			.Move = MOVE_FEINT,
			.Level = 11,
		},
		{
			.Move = MOVE_POWERUP_PUNCH,
			.Level = 15,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 19,
		},
		{
			.Move = MOVE_METAL_SOUND,
			.Level = 24,
		},
		{
			.Move = MOVE_BONE_RUSH,
			.Level = 29,
		},
		{
			.Move = MOVE_QUICK_GUARD,
			.Level = 33,
		},
		{
			.Move = MOVE_ME_FIRST,
			.Level = 37,
		},
		{
			.Move = MOVE_AURA_SPHERE,
			.Level = 42,
		},
		{
			.Move = MOVE_CALM_MIND,
			.Level = 47,
		},
		{
			.Move = MOVE_HEAL_PULSE,
			.Level = 51,
		},
		{
			.Move = MOVE_CLOSE_COMBAT,
			.Level = 55,
		},
		{
			.Move = MOVE_DRAGON_PULSE,
			.Level = 60,
		},
		{
			.Move = MOVE_EXTREMESPEED,
			.Level = 65,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_775] = {
		{
			.Move = MOVE_ICE_PUNCH,
			.Level = 1,
		},
		{
			.Move = MOVE_POWDER_SNOW,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 1,
		},
		{
			.Move = MOVE_ICY_WIND,
			.Level = 1,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 5,
		},
		{
			.Move = MOVE_ICY_WIND,
			.Level = 9,
		},
		{
			.Move = MOVE_GRASSWHISTLE,
			.Level = 13,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 17,
		},
		{
			.Move = MOVE_MIST,
			.Level = 21,
		},
		{
			.Move = MOVE_ICE_SHARD,
			.Level = 26,
		},
		{
			.Move = MOVE_INGRAIN,
			.Level = 31,
		},
		{
			.Move = MOVE_WOOD_HAMMER,
			.Level = 36,
		},
		{
			.Move = MOVE_BLIZZARD,
			.Level = 47,
		},
		{
			.Move = MOVE_SHEER_COLD,
			.Level = 58,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_776] = {
		{
			.Move = MOVE_FURY_CUTTER,
			.Level = 1,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 1,
		},
		{
			.Move = MOVE_AUTOTOMIZE,
			.Level = 1,
		},
		{
			.Move = MOVE_SHADOW_SNEAK,
			.Level = 1,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 1,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 1,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 1,
		},
		{
			.Move = MOVE_POWER_TRICK,
			.Level = 1,
		},
		{
			.Move = MOVE_IRON_HEAD,
			.Level = 1,
		},
		{
			.Move = MOVE_HEAD_SMASH,
			.Level = 1,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 1,
		},
		{
			.Move = MOVE_AERIAL_ACE,
			.Level = 1,
		},
		{
			.Move = MOVE_KING\X2019S_SHIELD,
			.Level = 1,
		},
		{
			.Move = MOVE_SACRED_SWORD,
			.Level = 1,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_777] = {
		{
			.Move = MOVE_FLASH_CANNON,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 1,
		},
		{
			.Move = MOVE_WITHDRAW,
			.Level = 1,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 4,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 7,
		},
		{
			.Move = MOVE_WITHDRAW,
			.Level = 10,
		},
		{
			.Move = MOVE_BUBBLE,
			.Level = 13,
		},
		{
			.Move = MOVE_BITE,
			.Level = 16,
		},
		{
			.Move = MOVE_RAPID_SPIN,
			.Level = 20,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 24,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 28,
		},
		{
			.Move = MOVE_AQUA_TAIL,
			.Level = 32,
		},
		{
			.Move = MOVE_SKULL_BASH,
			.Level = 39,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 46,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 53,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 60,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_778] = {
		{
			.Move = MOVE_COMET_PUNCH,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_FAKE_OUT,
			.Level = 7,
		},
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 10,
		},
		{
			.Move = MOVE_BITE,
			.Level = 13,
		},
		{
			.Move = MOVE_DOUBLE_HIT,
			.Level = 19,
		},
		{
			.Move = MOVE_RAGE,
			.Level = 22,
		},
		{
			.Move = MOVE_MEGA_PUNCH,
			.Level = 25,
		},
		{
			.Move = MOVE_CHIP_AWAY,
			.Level = 31,
		},
		{
			.Move = MOVE_DIZZY_PUNCH,
			.Level = 34,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 37,
		},
		{
			.Move = MOVE_ENDURE,
			.Level = 43,
		},
		{
			.Move = MOVE_OUTRAGE,
			.Level = 46,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 49,
		},
		{
			.Move = MOVE_REVERSAL,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_779] = {
		{
			.Move = MOVE_THRASH,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 20,
		},
		{
			.Move = MOVE_DRAGON_RAGE,
			.Level = 23,
		},
		{
			.Move = MOVE_LEER,
			.Level = 26,
		},
		{
			.Move = MOVE_TWISTER,
			.Level = 29,
		},
		{
			.Move = MOVE_ICE_FANG,
			.Level = 32,
		},
		{
			.Move = MOVE_AQUA_TAIL,
			.Level = 35,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 38,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 41,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 44,
		},
		{
			.Move = MOVE_DRAGON_DANCE,
			.Level = 47,
		},
		{
			.Move = MOVE_HYPER_BEAM,
			.Level = 50,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_780] = {
		{
			.Move = MOVE_PERISH_SONG,
			.Level = 1,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 1,
		},
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_FEINT,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 4,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 7,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 10,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 13,
		},
		{
			.Move = MOVE_BITE,
			.Level = 16,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 19,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 22,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 25,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 29,
		},
		{
			.Move = MOVE_DETECT,
			.Level = 33,
		},
		{
			.Move = MOVE_PSYCHO_CUT,
			.Level = 37,
		},
		{
			.Move = MOVE_ME_FIRST,
			.Level = 41,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 45,
		},
		{
			.Move = MOVE_RAZOR_WIND,
			.Level = 49,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 53,
		},
		{
			.Move = MOVE_PERISH_SONG,
			.Level = 57,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_781] = {
		{
			.Move = MOVE_TELEPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_KINESIS,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 16,
		},
		{
			.Move = MOVE_DISABLE,
			.Level = 18,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 21,
		},
		{
			.Move = MOVE_MIRACLE_EYE,
			.Level = 23,
		},
		{
			.Move = MOVE_REFLECT,
			.Level = 26,
		},
		{
			.Move = MOVE_PSYCHO_CUT,
			.Level = 28,
		},
		{
			.Move = MOVE_RECOVER,
			.Level = 31,
		},
		{
			.Move = MOVE_TELEKINESIS,
			.Level = 33,
		},
		{
			.Move = MOVE_ALLY_SWITCH,
			.Level = 36,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 38,
		},
		{
			.Move = MOVE_CALM_MIND,
			.Level = 41,
		},
		{
			.Move = MOVE_FUTURE_SIGHT,
			.Level = 43,
		},
		{
			.Move = MOVE_TRICK,
			.Level = 46,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_782] = {
		{
			.Move = MOVE_ARM_THRUST,
			.Level = 1,
		},
		{
			.Move = MOVE_BULLET_SEED,
			.Level = 1,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_HORN_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_ENDURE,
			.Level = 1,
		},
		{
			.Move = MOVE_FEINT,
			.Level = 7,
		},
		{
			.Move = MOVE_AERIAL_ACE,
			.Level = 10,
		},
		{
			.Move = MOVE_CHIP_AWAY,
			.Level = 16,
		},
		{
			.Move = MOVE_COUNTER,
			.Level = 19,
		},
		{
			.Move = MOVE_FURY_ATTACK,
			.Level = 25,
		},
		{
			.Move = MOVE_BRICK_BREAK,
			.Level = 28,
		},
		{
			.Move = MOVE_PIN_MISSILE,
			.Level = 31,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 34,
		},
		{
			.Move = MOVE_MEGAHORN,
			.Level = 37,
		},
		{
			.Move = MOVE_CLOSE_COMBAT,
			.Level = 43,
		},
		{
			.Move = MOVE_REVERSAL,
			.Level = 46,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_783] = {
		{
			.Move = MOVE_PLAY_ROUGH,
			.Level = 1,
		},
		{
			.Move = MOVE_IRON_HEAD,
			.Level = 1,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_FAIRY_WIND,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_FAKE_TEARS,
			.Level = 5,
		},
		{
			.Move = MOVE_BITE,
			.Level = 9,
		},
		{
			.Move = MOVE_SWEET_SCENT,
			.Level = 13,
		},
		{
			.Move = MOVE_VICEGRIP,
			.Level = 17,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 21,
		},
		{
			.Move = MOVE_BATON_PASS,
			.Level = 25,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 29,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 33,
		},
		{
			.Move = MOVE_SUCKER_PUNCH,
			.Level = 37,
		},
		{
			.Move = MOVE_STOCKPILE,
			.Level = 41,
		},
		{
			.Move = MOVE_SWALLOW,
			.Level = 41,
		},
		{
			.Move = MOVE_SPIT_UP,
			.Level = 41,
		},
		{
			.Move = MOVE_IRON_HEAD,
			.Level = 45,
		},
		{
			.Move = MOVE_PLAY_ROUGH,
			.Level = 49,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_784] = {
		{
			.Move = MOVE_ELECTRIC_TERRAIN,
			.Level = 1,
		},
		{
			.Move = MOVE_FIRE_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_HOWL,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 4,
		},
		{
			.Move = MOVE_HOWL,
			.Level = 7,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 10,
		},
		{
			.Move = MOVE_SPARK,
			.Level = 13,
		},
		{
			.Move = MOVE_ODOR_SLEUTH,
			.Level = 16,
		},
		{
			.Move = MOVE_THUNDER_FANG,
			.Level = 19,
		},
		{
			.Move = MOVE_BITE,
			.Level = 24,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 30,
		},
		{
			.Move = MOVE_ROAR,
			.Level = 36,
		},
		{
			.Move = MOVE_WILD_CHARGE,
			.Level = 42,
		},
		{
			.Move = MOVE_CHARGE,
			.Level = 48,
		},
		{
			.Move = MOVE_THUNDER,
			.Level = 54,
		},
		{
			.Move = MOVE_ELECTRIC_TERRAIN,
			.Level = 60,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_785] = {
		{
			.Move = MOVE_FIRE_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_DRAGON_RAGE,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDSTORM,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 3,
		},
		{
			.Move = MOVE_DRAGON_RAGE,
			.Level = 7,
		},
		{
			.Move = MOVE_SANDSTORM,
			.Level = 13,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 15,
		},
		{
			.Move = MOVE_SAND_TOMB,
			.Level = 19,
		},
		{
			.Move = MOVE_DUAL_CHOP,
			.Level = 24,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 28,
		},
		{
			.Move = MOVE_DRAGON_CLAW,
			.Level = 33,
		},
		{
			.Move = MOVE_DIG,
			.Level = 40,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 48,
		},
		{
			.Move = MOVE_DRAGON_RUSH,
			.Level = 55,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_786] = {
		{
			.Move = MOVE_MEMENTO,
			.Level = 1,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 1,
		},
		{
			.Move = MOVE_HEAL_BLOCK,
			.Level = 1,
		},
		{
			.Move = MOVE_PSYWAVE,
			.Level = 1,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 1,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 4,
		},
		{
			.Move = MOVE_DRAGON_DANCE,
			.Level = 7,
		},
		{
			.Move = MOVE_STORED_POWER,
			.Level = 10,
		},
		{
			.Move = MOVE_REFRESH,
			.Level = 13,
		},
		{
			.Move = MOVE_HEAL_PULSE,
			.Level = 16,
		},
		{
			.Move = MOVE_DRAGONBREATH,
			.Level = 20,
		},
		{
			.Move = MOVE_LUSTER_PURGE,
			.Level = 24,
		},
		{
			.Move = MOVE_PSYCHO_SHIFT,
			.Level = 28,
		},
		{
			.Move = MOVE_RECOVER,
			.Level = 32,
		},
		{
			.Move = MOVE_TELEKINESIS,
			.Level = 36,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 41,
		},
		{
			.Move = MOVE_POWER_SPLIT,
			.Level = 46,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 51,
		},
		{
			.Move = MOVE_DRAGON_PULSE,
			.Level = 56,
		},
		{
			.Move = MOVE_MEMENTO,
			.Level = 61,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_787] = {
		{
			.Move = MOVE_HEALING_WISH,
			.Level = 1,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 1,
		},
		{
			.Move = MOVE_WISH,
			.Level = 1,
		},
		{
			.Move = MOVE_PSYWAVE,
			.Level = 1,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_SPORT,
			.Level = 4,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 7,
		},
		{
			.Move = MOVE_STORED_POWER,
			.Level = 10,
		},
		{
			.Move = MOVE_REFRESH,
			.Level = 13,
		},
		{
			.Move = MOVE_HEAL_PULSE,
			.Level = 16,
		},
		{
			.Move = MOVE_DRAGONBREATH,
			.Level = 20,
		},
		{
			.Move = MOVE_MIST_BALL,
			.Level = 24,
		},
		{
			.Move = MOVE_PSYCHO_SHIFT,
			.Level = 28,
		},
		{
			.Move = MOVE_RECOVER,
			.Level = 32,
		},
		{
			.Move = MOVE_REFLECT_TYPE,
			.Level = 36,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 41,
		},
		{
			.Move = MOVE_GUARD_SPLIT,
			.Level = 46,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 51,
		},
		{
			.Move = MOVE_DRAGON_PULSE,
			.Level = 56,
		},
		{
			.Move = MOVE_HEALING_WISH,
			.Level = 61,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_788] = {
		{
			.Move = MOVE_TRICK,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 1,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 4,
		},
		{
			.Move = MOVE_TRICKORTREAT,
			.Level = 6,
		},
		{
			.Move = MOVE_WORRY_SEED,
			.Level = 11,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 16,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 20,
		},
		{
			.Move = MOVE_TRICKORTREAT,
			.Level = 23,
		},
		{
			.Move = MOVE_BULLET_SEED,
			.Level = 26,
		},
		{
			.Move = MOVE_SHADOW_SNEAK,
			.Level = 30,
		},
		{
			.Move = MOVE_SHADOW_BALL,
			.Level = 36,
		},
		{
			.Move = MOVE_TRICKORTREAT,
			.Level = 40,
		},
		{
			.Move = MOVE_PAIN_SPLIT,
			.Level = 42,
		},
		{
			.Move = MOVE_SEED_BOMB,
			.Level = 48,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_789] = {
		{
			.Move = MOVE_TRICK,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 1,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 4,
		},
		{
			.Move = MOVE_TRICKORTREAT,
			.Level = 6,
		},
		{
			.Move = MOVE_WORRY_SEED,
			.Level = 11,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 16,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 20,
		},
		{
			.Move = MOVE_TRICKORTREAT,
			.Level = 23,
		},
		{
			.Move = MOVE_BULLET_SEED,
			.Level = 26,
		},
		{
			.Move = MOVE_SHADOW_SNEAK,
			.Level = 30,
		},
		{
			.Move = MOVE_SHADOW_BALL,
			.Level = 36,
		},
		{
			.Move = MOVE_TRICKORTREAT,
			.Level = 40,
		},
		{
			.Move = MOVE_PAIN_SPLIT,
			.Level = 42,
		},
		{
			.Move = MOVE_SEED_BOMB,
			.Level = 48,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_790] = {
		{
			.Move = MOVE_TRICK,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 1,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 4,
		},
		{
			.Move = MOVE_TRICKORTREAT,
			.Level = 6,
		},
		{
			.Move = MOVE_WORRY_SEED,
			.Level = 11,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 16,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 20,
		},
		{
			.Move = MOVE_TRICKORTREAT,
			.Level = 23,
		},
		{
			.Move = MOVE_BULLET_SEED,
			.Level = 26,
		},
		{
			.Move = MOVE_SHADOW_SNEAK,
			.Level = 30,
		},
		{
			.Move = MOVE_SHADOW_BALL,
			.Level = 36,
		},
		{
			.Move = MOVE_TRICKORTREAT,
			.Level = 40,
		},
		{
			.Move = MOVE_PAIN_SPLIT,
			.Level = 42,
		},
		{
			.Move = MOVE_SEED_BOMB,
			.Level = 48,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_791] = {
		{
			.Move = MOVE_EXPLOSION,
			.Level = 1,
		},
		{
			.Move = MOVE_PHANTOM_FORCE,
			.Level = 1,
		},
		{
			.Move = MOVE_TRICK,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 1,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 4,
		},
		{
			.Move = MOVE_TRICKORTREAT,
			.Level = 6,
		},
		{
			.Move = MOVE_WORRY_SEED,
			.Level = 11,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 16,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 20,
		},
		{
			.Move = MOVE_TRICKORTREAT,
			.Level = 23,
		},
		{
			.Move = MOVE_BULLET_SEED,
			.Level = 26,
		},
		{
			.Move = MOVE_SHADOW_SNEAK,
			.Level = 30,
		},
		{
			.Move = MOVE_SHADOW_BALL,
			.Level = 36,
		},
		{
			.Move = MOVE_TRICKORTREAT,
			.Level = 40,
		},
		{
			.Move = MOVE_PAIN_SPLIT,
			.Level = 42,
		},
		{
			.Move = MOVE_SEED_BOMB,
			.Level = 48,
		},
		{
			.Move = MOVE_PHANTOM_FORCE,
			.Level = 57,
		},
		{
			.Move = MOVE_TRICKORTREAT,
			.Level = 63,
		},
		{
			.Move = MOVE_SHADOW_BALL,
			.Level = 70,
		},
		{
			.Move = MOVE_EXPLOSION,
			.Level = 75,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_792] = {
		{
			.Move = MOVE_EXPLOSION,
			.Level = 1,
		},
		{
			.Move = MOVE_PHANTOM_FORCE,
			.Level = 1,
		},
		{
			.Move = MOVE_TRICK,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 1,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 4,
		},
		{
			.Move = MOVE_TRICKORTREAT,
			.Level = 6,
		},
		{
			.Move = MOVE_WORRY_SEED,
			.Level = 11,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 16,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 20,
		},
		{
			.Move = MOVE_TRICKORTREAT,
			.Level = 23,
		},
		{
			.Move = MOVE_BULLET_SEED,
			.Level = 26,
		},
		{
			.Move = MOVE_SHADOW_SNEAK,
			.Level = 30,
		},
		{
			.Move = MOVE_SHADOW_BALL,
			.Level = 36,
		},
		{
			.Move = MOVE_TRICKORTREAT,
			.Level = 40,
		},
		{
			.Move = MOVE_PAIN_SPLIT,
			.Level = 42,
		},
		{
			.Move = MOVE_SEED_BOMB,
			.Level = 48,
		},
		{
			.Move = MOVE_PHANTOM_FORCE,
			.Level = 57,
		},
		{
			.Move = MOVE_TRICKORTREAT,
			.Level = 63,
		},
		{
			.Move = MOVE_SHADOW_BALL,
			.Level = 70,
		},
		{
			.Move = MOVE_EXPLOSION,
			.Level = 75,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_793] = {
		{
			.Move = MOVE_EXPLOSION,
			.Level = 1,
		},
		{
			.Move = MOVE_PHANTOM_FORCE,
			.Level = 1,
		},
		{
			.Move = MOVE_TRICK,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 1,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 4,
		},
		{
			.Move = MOVE_TRICKORTREAT,
			.Level = 6,
		},
		{
			.Move = MOVE_WORRY_SEED,
			.Level = 11,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 16,
		},
		{
			.Move = MOVE_LEECH_SEED,
			.Level = 20,
		},
		{
			.Move = MOVE_TRICKORTREAT,
			.Level = 23,
		},
		{
			.Move = MOVE_BULLET_SEED,
			.Level = 26,
		},
		{
			.Move = MOVE_SHADOW_SNEAK,
			.Level = 30,
		},
		{
			.Move = MOVE_SHADOW_BALL,
			.Level = 36,
		},
		{
			.Move = MOVE_TRICKORTREAT,
			.Level = 40,
		},
		{
			.Move = MOVE_PAIN_SPLIT,
			.Level = 42,
		},
		{
			.Move = MOVE_SEED_BOMB,
			.Level = 48,
		},
		{
			.Move = MOVE_PHANTOM_FORCE,
			.Level = 57,
		},
		{
			.Move = MOVE_TRICKORTREAT,
			.Level = 63,
		},
		{
			.Move = MOVE_SHADOW_BALL,
			.Level = 70,
		},
		{
			.Move = MOVE_EXPLOSION,
			.Level = 75,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_794] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_VINE_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_FAIRY_WIND,
			.Level = 6,
		},
		{
			.Move = MOVE_LUCKY_CHANT,
			.Level = 10,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 15,
		},
		{
			.Move = MOVE_WISH,
			.Level = 20,
		},
		{
			.Move = MOVE_MAGICAL_LEAF,
			.Level = 25,
		},
		{
			.Move = MOVE_GRASSY_TERRAIN,
			.Level = 27,
		},
		{
			.Move = MOVE_PETAL_BLIZZARD,
			.Level = 33,
		},
		{
			.Move = MOVE_AROMATHERAPY,
			.Level = 38,
		},
		{
			.Move = MOVE_MISTY_TERRAIN,
			.Level = 43,
		},
		{
			.Move = MOVE_MOONBLAST,
			.Level = 46,
		},
		{
			.Move = MOVE_PETAL_DANCE,
			.Level = 51,
		},
		{
			.Move = MOVE_SOLARBEAM,
			.Level = 58,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_795] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_VINE_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_FAIRY_WIND,
			.Level = 6,
		},
		{
			.Move = MOVE_LUCKY_CHANT,
			.Level = 10,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 15,
		},
		{
			.Move = MOVE_WISH,
			.Level = 20,
		},
		{
			.Move = MOVE_MAGICAL_LEAF,
			.Level = 25,
		},
		{
			.Move = MOVE_GRASSY_TERRAIN,
			.Level = 27,
		},
		{
			.Move = MOVE_PETAL_BLIZZARD,
			.Level = 33,
		},
		{
			.Move = MOVE_AROMATHERAPY,
			.Level = 38,
		},
		{
			.Move = MOVE_MISTY_TERRAIN,
			.Level = 43,
		},
		{
			.Move = MOVE_MOONBLAST,
			.Level = 46,
		},
		{
			.Move = MOVE_PETAL_DANCE,
			.Level = 51,
		},
		{
			.Move = MOVE_SOLARBEAM,
			.Level = 58,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_796] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_VINE_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_FAIRY_WIND,
			.Level = 6,
		},
		{
			.Move = MOVE_LUCKY_CHANT,
			.Level = 10,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 15,
		},
		{
			.Move = MOVE_WISH,
			.Level = 20,
		},
		{
			.Move = MOVE_MAGICAL_LEAF,
			.Level = 25,
		},
		{
			.Move = MOVE_GRASSY_TERRAIN,
			.Level = 27,
		},
		{
			.Move = MOVE_PETAL_BLIZZARD,
			.Level = 33,
		},
		{
			.Move = MOVE_AROMATHERAPY,
			.Level = 38,
		},
		{
			.Move = MOVE_MISTY_TERRAIN,
			.Level = 43,
		},
		{
			.Move = MOVE_MOONBLAST,
			.Level = 46,
		},
		{
			.Move = MOVE_PETAL_DANCE,
			.Level = 51,
		},
		{
			.Move = MOVE_SOLARBEAM,
			.Level = 58,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_797] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_VINE_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_FAIRY_WIND,
			.Level = 6,
		},
		{
			.Move = MOVE_LUCKY_CHANT,
			.Level = 10,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 15,
		},
		{
			.Move = MOVE_WISH,
			.Level = 20,
		},
		{
			.Move = MOVE_MAGICAL_LEAF,
			.Level = 25,
		},
		{
			.Move = MOVE_GRASSY_TERRAIN,
			.Level = 27,
		},
		{
			.Move = MOVE_PETAL_BLIZZARD,
			.Level = 33,
		},
		{
			.Move = MOVE_AROMATHERAPY,
			.Level = 38,
		},
		{
			.Move = MOVE_MISTY_TERRAIN,
			.Level = 43,
		},
		{
			.Move = MOVE_MOONBLAST,
			.Level = 46,
		},
		{
			.Move = MOVE_PETAL_DANCE,
			.Level = 51,
		},
		{
			.Move = MOVE_SOLARBEAM,
			.Level = 58,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_798] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_VINE_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_FAIRY_WIND,
			.Level = 6,
		},
		{
			.Move = MOVE_LUCKY_CHANT,
			.Level = 10,
		},
		{
			.Move = MOVE_RAZOR_LEAF,
			.Level = 15,
		},
		{
			.Move = MOVE_WISH,
			.Level = 20,
		},
		{
			.Move = MOVE_MAGICAL_LEAF,
			.Level = 25,
		},
		{
			.Move = MOVE_GRASSY_TERRAIN,
			.Level = 27,
		},
		{
			.Move = MOVE_PETAL_BLIZZARD,
			.Level = 33,
		},
		{
			.Move = MOVE_AROMATHERAPY,
			.Level = 38,
		},
		{
			.Move = MOVE_MISTY_TERRAIN,
			.Level = 43,
		},
		{
			.Move = MOVE_MOONBLAST,
			.Level = 46,
		},
		{
			.Move = MOVE_LIGHT_OF_RUIN,
			.Level = 50,
		},
		{
			.Move = MOVE_PETAL_DANCE,
			.Level = 51,
		},
		{
			.Move = MOVE_SOLARBEAM,
			.Level = 58,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_799] = {
		{
			.Move = MOVE_MUDDY_WATER,
			.Level = 1,
		},
		{
			.Move = MOVE_MUD_BOMB,
			.Level = 1,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 1,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 1,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_800] = {
		{
			.Move = MOVE_LEAF_BLADE,
			.Level = 1,
		},
		{
			.Move = MOVE_AERIAL_ACE,
			.Level = 1,
		},
		{
			.Move = MOVE_SLAM,
			.Level = 1,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 1,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_801] = {
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_SCRATCH,
			.Level = 1,
		},
		{
			.Move = MOVE_FORESIGHT,
			.Level = 4,
		},
		{
			.Move = MOVE_NIGHT_SHADE,
			.Level = 6,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 9,
		},
		{
			.Move = MOVE_FURY_SWIPES,
			.Level = 11,
		},
		{
			.Move = MOVE_DETECT,
			.Level = 14,
		},
		{
			.Move = MOVE_SHADOW_SNEAK,
			.Level = 16,
		},
		{
			.Move = MOVE_FAINT_ATTACK,
			.Level = 19,
		},
		{
			.Move = MOVE_FAKE_OUT,
			.Level = 21,
		},
		{
			.Move = MOVE_PUNISHMENT,
			.Level = 24,
		},
		{
			.Move = MOVE_KNOCK_OFF,
			.Level = 26,
		},
		{
			.Move = MOVE_SHADOW_CLAW,
			.Level = 29,
		},
		{
			.Move = MOVE_CONFUSE_RAY,
			.Level = 31,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 34,
		},
		{
			.Move = MOVE_POWER_GEM,
			.Level = 36,
		},
		{
			.Move = MOVE_SHADOW_BALL,
			.Level = 39,
		},
		{
			.Move = MOVE_FOUL_PLAY,
			.Level = 41,
		},
		{
			.Move = MOVE_QUASH,
			.Level = 44,
		},
		{
			.Move = MOVE_MEAN_LOOK,
			.Level = 46,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_802] = {
		{
			.Move = MOVE_SKY_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_PLUCK,
			.Level = 1,
		},
		{
			.Move = MOVE_PECK,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 1,
		},
		{
			.Move = MOVE_SING,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 3,
		},
		{
			.Move = MOVE_SING,
			.Level = 5,
		},
		{
			.Move = MOVE_FURY_ATTACK,
			.Level = 7,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 9,
		},
		{
			.Move = MOVE_DISARMING_VOICE,
			.Level = 11,
		},
		{
			.Move = MOVE_MIST,
			.Level = 14,
		},
		{
			.Move = MOVE_ROUND,
			.Level = 17,
		},
		{
			.Move = MOVE_NATURAL_GIFT,
			.Level = 20,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 23,
		},
		{
			.Move = MOVE_REFRESH,
			.Level = 26,
		},
		{
			.Move = MOVE_DRAGON_DANCE,
			.Level = 30,
		},
		{
			.Move = MOVE_COTTON_GUARD,
			.Level = 34,
		},
		{
			.Move = MOVE_DRAGONBREATH,
			.Level = 35,
		},
		{
			.Move = MOVE_DRAGON_PULSE,
			.Level = 40,
		},
		{
			.Move = MOVE_PERISH_SONG,
			.Level = 46,
		},
		{
			.Move = MOVE_MOONBLAST,
			.Level = 52,
		},
		{
			.Move = MOVE_SKY_ATTACK,
			.Level = 59,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_803] = {
		{
			.Move = MOVE_STORED_POWER,
			.Level = 1,
		},
		{
			.Move = MOVE_CLOSE_COMBAT,
			.Level = 1,
		},
		{
			.Move = MOVE_LEAF_BLADE,
			.Level = 1,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 1,
		},
		{
			.Move = MOVE_TELEPORT,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 4,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 6,
		},
		{
			.Move = MOVE_TELEPORT,
			.Level = 9,
		},
		{
			.Move = MOVE_QUICK_GUARD,
			.Level = 11,
		},
		{
			.Move = MOVE_FURY_CUTTER,
			.Level = 14,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 17,
		},
		{
			.Move = MOVE_HEAL_PULSE,
			.Level = 19,
		},
		{
			.Move = MOVE_WIDE_GUARD,
			.Level = 23,
		},
		{
			.Move = MOVE_SWORDS_DANCE,
			.Level = 26,
		},
		{
			.Move = MOVE_PSYCHO_CUT,
			.Level = 31,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 35,
		},
		{
			.Move = MOVE_FEINT,
			.Level = 40,
		},
		{
			.Move = MOVE_FALSE_SWIPE,
			.Level = 44,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 49,
		},
		{
			.Move = MOVE_CLOSE_COMBAT,
			.Level = 53,
		},
		{
			.Move = MOVE_STORED_POWER,
			.Level = 58,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_804] = {
		{
			.Move = MOVE_LAST_RESORT,
			.Level = 1,
		},
		{
			.Move = MOVE_MISTY_TERRAIN,
			.Level = 1,
		},
		{
			.Move = MOVE_PLAY_NICE,
			.Level = 1,
		},
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_HELPING_HAND,
			.Level = 1,
		},
		{
			.Move = MOVE_BABYDOLL_EYES,
			.Level = 5,
		},
		{
			.Move = MOVE_REFRESH,
			.Level = 9,
		},
		{
			.Move = MOVE_DISARMING_VOICE,
			.Level = 13,
		},
		{
			.Move = MOVE_DOUBLESLAP,
			.Level = 17,
		},
		{
			.Move = MOVE_ATTRACT,
			.Level = 21,
		},
		{
			.Move = MOVE_SECRET_POWER,
			.Level = 25,
		},
		{
			.Move = MOVE_ENTRAINMENT,
			.Level = 29,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 33,
		},
		{
			.Move = MOVE_HEAL_PULSE,
			.Level = 37,
		},
		{
			.Move = MOVE_AFTER_YOU,
			.Level = 41,
		},
		{
			.Move = MOVE_SIMPLE_BEAM,
			.Level = 45,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 49,
		},
		{
			.Move = MOVE_LAST_RESORT,
			.Level = 53,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_805] = {
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 1,
		},
		{
			.Move = MOVE_FEINT,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_RAGE,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 1,
		},
		{
			.Move = MOVE_RAGE,
			.Level = 4,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 8,
		},
		{
			.Move = MOVE_AQUA_JET,
			.Level = 11,
		},
		{
			.Move = MOVE_ASSURANCE,
			.Level = 15,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 18,
		},
		{
			.Move = MOVE_SWAGGER,
			.Level = 22,
		},
		{
			.Move = MOVE_ICE_FANG,
			.Level = 25,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 29,
		},
		{
			.Move = MOVE_SLASH,
			.Level = 30,
		},
		{
			.Move = MOVE_POISON_FANG,
			.Level = 34,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 40,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 45,
		},
		{
			.Move = MOVE_SKULL_BASH,
			.Level = 51,
		},
		{
			.Move = MOVE_TAUNT,
			.Level = 56,
		},
		{
			.Move = MOVE_NIGHT_SLASH,
			.Level = 62,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_806] = {
		{
			.Move = MOVE_HEAL_PULSE,
			.Level = 1,
		},
		{
			.Move = MOVE_CURSE,
			.Level = 1,
		},
		{
			.Move = MOVE_YAWN,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 5,
		},
		{
			.Move = MOVE_WATER_GUN,
			.Level = 9,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 14,
		},
		{
			.Move = MOVE_DISABLE,
			.Level = 19,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 23,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 28,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 32,
		},
		{
			.Move = MOVE_SLACK_OFF,
			.Level = 36,
		},
		{
			.Move = MOVE_WITHDRAW,
			.Level = 37,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 43,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 49,
		},
		{
			.Move = MOVE_RAIN_DANCE,
			.Level = 55,
		},
		{
			.Move = MOVE_PSYCH_UP,
			.Level = 62,
		},
		{
			.Move = MOVE_HEAL_PULSE,
			.Level = 68,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_807] = {
		{
			.Move = MOVE_IRON_TAIL,
			.Level = 1,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 1,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 1,
		},
		{
			.Move = MOVE_SCREECH,
			.Level = 1,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_808] = {
		{
			.Move = MOVE_HURRICANE,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_GUST,
			.Level = 1,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_SANDATTACK,
			.Level = 5,
		},
		{
			.Move = MOVE_GUST,
			.Level = 9,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 13,
		},
		{
			.Move = MOVE_WHIRLWIND,
			.Level = 17,
		},
		{
			.Move = MOVE_TWISTER,
			.Level = 22,
		},
		{
			.Move = MOVE_FEATHERDANCE,
			.Level = 27,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 32,
		},
		{
			.Move = MOVE_WING_ATTACK,
			.Level = 38,
		},
		{
			.Move = MOVE_ROOST,
			.Level = 44,
		},
		{
			.Move = MOVE_TAILWIND,
			.Level = 50,
		},
		{
			.Move = MOVE_MIRROR_MOVE,
			.Level = 56,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 62,
		},
		{
			.Move = MOVE_HURRICANE,
			.Level = 68,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_809] = {
		{
			.Move = MOVE_ICE_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 1,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 1,
		},
		{
			.Move = MOVE_FROST_BREATH,
			.Level = 1,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_810] = {
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_HARDEN,
			.Level = 1,
		},
		{
			.Move = MOVE_ROCK_THROW,
			.Level = 5,
		},
		{
			.Move = MOVE_SHARPEN,
			.Level = 8,
		},
		{
			.Move = MOVE_SMACK_DOWN,
			.Level = 12,
		},
		{
			.Move = MOVE_REFLECT,
			.Level = 18,
		},
		{
			.Move = MOVE_STEALTH_ROCK,
			.Level = 21,
		},
		{
			.Move = MOVE_GUARD_SPLIT,
			.Level = 27,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 31,
		},
		{
			.Move = MOVE_FLAIL,
			.Level = 35,
		},
		{
			.Move = MOVE_SKILL_SWAP,
			.Level = 40,
		},
		{
			.Move = MOVE_TRICK_ROOM,
			.Level = 46,
		},
		{
			.Move = MOVE_STONE_EDGE,
			.Level = 49,
		},
		{
			.Move = MOVE_MOONBLAST,
			.Level = 50,
		},
		{
			.Move = MOVE_DIAMOND_STORM,
			.Level = 50,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 60,
		},
		{
			.Move = MOVE_SAFEGUARD,
			.Level = 70,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_811] = {
		{
			.Move = MOVE_MAGNET_RISE,
			.Level = 1,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_METAL_CLAW,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 20,
		},
		{
			.Move = MOVE_METAL_CLAW,
			.Level = 20,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 23,
		},
		{
			.Move = MOVE_BULLET_PUNCH,
			.Level = 26,
		},
		{
			.Move = MOVE_MIRACLE_EYE,
			.Level = 29,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 32,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 35,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 38,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 41,
		},
		{
			.Move = MOVE_METEOR_MASH,
			.Level = 44,
		},
		{
			.Move = MOVE_HAMMER_ARM,
			.Level = 45,
		},
		{
			.Move = MOVE_IRON_DEFENSE,
			.Level = 52,
		},
		{
			.Move = MOVE_HYPER_BEAM,
			.Level = 60,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_812] = {
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 1,
		},
		{
			.Move = MOVE_WATER_PULSE,
			.Level = 1,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 5,
		},
		{
			.Move = MOVE_AQUA_TAIL,
			.Level = 15,
		},
		{
			.Move = MOVE_BODY_SLAM,
			.Level = 20,
		},
		{
			.Move = MOVE_AQUA_RING,
			.Level = 30,
		},
		{
			.Move = MOVE_ICE_BEAM,
			.Level = 35,
		},
		{
			.Move = MOVE_ORIGIN_PULSE,
			.Level = 45,
		},
		{
			.Move = MOVE_CALM_MIND,
			.Level = 50,
		},
		{
			.Move = MOVE_MUDDY_WATER,
			.Level = 60,
		},
		{
			.Move = MOVE_SHEER_COLD,
			.Level = 65,
		},
		{
			.Move = MOVE_HYDRO_PUMP,
			.Level = 75,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 80,
		},
		{
			.Move = MOVE_WATER_SPOUT,
			.Level = 90,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_813] = {
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 1,
		},
		{
			.Move = MOVE_MUD_SHOT,
			.Level = 1,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 5,
		},
		{
			.Move = MOVE_EARTH_POWER,
			.Level = 15,
		},
		{
			.Move = MOVE_LAVA_PLUME,
			.Level = 20,
		},
		{
			.Move = MOVE_REST,
			.Level = 30,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 35,
		},
		{
			.Move = MOVE_PRECIPICE_BLADES,
			.Level = 45,
		},
		{
			.Move = MOVE_BULK_UP,
			.Level = 50,
		},
		{
			.Move = MOVE_SOLARBEAM,
			.Level = 60,
		},
		{
			.Move = MOVE_FISSURE,
			.Level = 65,
		},
		{
			.Move = MOVE_FIRE_BLAST,
			.Level = 75,
		},
		{
			.Move = MOVE_HAMMER_ARM,
			.Level = 80,
		},
		{
			.Move = MOVE_ERUPTION,
			.Level = 90,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_814] = {
		{
			.Move = MOVE_TWISTER,
			.Level = 1,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 5,
		},
		{
			.Move = MOVE_ANCIENTPOWER,
			.Level = 15,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 20,
		},
		{
			.Move = MOVE_AIR_SLASH,
			.Level = 30,
		},
		{
			.Move = MOVE_REST,
			.Level = 35,
		},
		{
			.Move = MOVE_EXTREMESPEED,
			.Level = 45,
		},
		{
			.Move = MOVE_DRAGON_PULSE,
			.Level = 50,
		},
		{
			.Move = MOVE_DRAGON_DANCE,
			.Level = 60,
		},
		{
			.Move = MOVE_FLY,
			.Level = 65,
		},
		{
			.Move = MOVE_HYPER_VOICE,
			.Level = 75,
		},
		{
			.Move = MOVE_OUTRAGE,
			.Level = 80,
		},
		{
			.Move = MOVE_HYPER_BEAM,
			.Level = 90,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_815] = {
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 5,
		},
		{
			.Move = MOVE_PLAY_NICE,
			.Level = 7,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 10,
		},
		{
			.Move = MOVE_ELECTRO_BALL,
			.Level = 13,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 18,
		},
		{
			.Move = MOVE_FEINT,
			.Level = 21,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 23,
		},
		{
			.Move = MOVE_SPARK,
			.Level = 26,
		},
		{
			.Move = MOVE_NUZZLE,
			.Level = 29,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 34,
		},
		{
			.Move = MOVE_SLAM,
			.Level = 37,
		},
		{
			.Move = MOVE_THUNDERBOLT,
			.Level = 42,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 45,
		},
		{
			.Move = MOVE_WILD_CHARGE,
			.Level = 50,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 53,
		},
		{
			.Move = MOVE_THUNDER,
			.Level = 58,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_816] = {
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 5,
		},
		{
			.Move = MOVE_PLAY_NICE,
			.Level = 7,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 10,
		},
		{
			.Move = MOVE_ELECTRO_BALL,
			.Level = 13,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 18,
		},
		{
			.Move = MOVE_FEINT,
			.Level = 21,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 23,
		},
		{
			.Move = MOVE_SPARK,
			.Level = 26,
		},
		{
			.Move = MOVE_NUZZLE,
			.Level = 29,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 34,
		},
		{
			.Move = MOVE_SLAM,
			.Level = 37,
		},
		{
			.Move = MOVE_THUNDERBOLT,
			.Level = 42,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 45,
		},
		{
			.Move = MOVE_WILD_CHARGE,
			.Level = 50,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 53,
		},
		{
			.Move = MOVE_THUNDER,
			.Level = 58,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_817] = {
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 5,
		},
		{
			.Move = MOVE_PLAY_NICE,
			.Level = 7,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 10,
		},
		{
			.Move = MOVE_ELECTRO_BALL,
			.Level = 13,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 18,
		},
		{
			.Move = MOVE_FEINT,
			.Level = 21,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 23,
		},
		{
			.Move = MOVE_SPARK,
			.Level = 26,
		},
		{
			.Move = MOVE_NUZZLE,
			.Level = 29,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 34,
		},
		{
			.Move = MOVE_SLAM,
			.Level = 37,
		},
		{
			.Move = MOVE_THUNDERBOLT,
			.Level = 42,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 45,
		},
		{
			.Move = MOVE_WILD_CHARGE,
			.Level = 50,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 53,
		},
		{
			.Move = MOVE_THUNDER,
			.Level = 58,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_818] = {
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 5,
		},
		{
			.Move = MOVE_PLAY_NICE,
			.Level = 7,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 10,
		},
		{
			.Move = MOVE_ELECTRO_BALL,
			.Level = 13,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 18,
		},
		{
			.Move = MOVE_FEINT,
			.Level = 21,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 23,
		},
		{
			.Move = MOVE_SPARK,
			.Level = 26,
		},
		{
			.Move = MOVE_NUZZLE,
			.Level = 29,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 34,
		},
		{
			.Move = MOVE_SLAM,
			.Level = 37,
		},
		{
			.Move = MOVE_THUNDERBOLT,
			.Level = 42,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 45,
		},
		{
			.Move = MOVE_WILD_CHARGE,
			.Level = 50,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 53,
		},
		{
			.Move = MOVE_THUNDER,
			.Level = 58,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_819] = {
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 5,
		},
		{
			.Move = MOVE_PLAY_NICE,
			.Level = 7,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 10,
		},
		{
			.Move = MOVE_ELECTRO_BALL,
			.Level = 13,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 18,
		},
		{
			.Move = MOVE_FEINT,
			.Level = 21,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 23,
		},
		{
			.Move = MOVE_SPARK,
			.Level = 26,
		},
		{
			.Move = MOVE_NUZZLE,
			.Level = 29,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 34,
		},
		{
			.Move = MOVE_SLAM,
			.Level = 37,
		},
		{
			.Move = MOVE_THUNDERBOLT,
			.Level = 42,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 45,
		},
		{
			.Move = MOVE_WILD_CHARGE,
			.Level = 50,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 53,
		},
		{
			.Move = MOVE_THUNDER,
			.Level = 58,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_820] = {
		{
			.Move = MOVE_TAIL_WHIP,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDERSHOCK,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 5,
		},
		{
			.Move = MOVE_PLAY_NICE,
			.Level = 7,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 10,
		},
		{
			.Move = MOVE_ELECTRO_BALL,
			.Level = 13,
		},
		{
			.Move = MOVE_THUNDER_WAVE,
			.Level = 18,
		},
		{
			.Move = MOVE_FEINT,
			.Level = 21,
		},
		{
			.Move = MOVE_DOUBLE_TEAM,
			.Level = 23,
		},
		{
			.Move = MOVE_SPARK,
			.Level = 26,
		},
		{
			.Move = MOVE_NUZZLE,
			.Level = 29,
		},
		{
			.Move = MOVE_DISCHARGE,
			.Level = 34,
		},
		{
			.Move = MOVE_SLAM,
			.Level = 37,
		},
		{
			.Move = MOVE_THUNDERBOLT,
			.Level = 42,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 45,
		},
		{
			.Move = MOVE_WILD_CHARGE,
			.Level = 50,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 53,
		},
		{
			.Move = MOVE_THUNDER,
			.Level = 58,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_821] = {
		{
			.Move = MOVE_HYPERSPACE_FURY,
			.Level = 1,
		},
		{
			.Move = MOVE_TRICK,
			.Level = 1,
		},
		{
			.Move = MOVE_DESTINY_BOND,
			.Level = 1,
		},
		{
			.Move = MOVE_ALLY_SWITCH,
			.Level = 1,
		},
		{
			.Move = MOVE_CONFUSION,
			.Level = 1,
		},
		{
			.Move = MOVE_ASTONISH,
			.Level = 6,
		},
		{
			.Move = MOVE_MAGIC_COAT,
			.Level = 10,
		},
		{
			.Move = MOVE_LIGHT_SCREEN,
			.Level = 15,
		},
		{
			.Move = MOVE_PSYBEAM,
			.Level = 19,
		},
		{
			.Move = MOVE_SKILL_SWAP,
			.Level = 25,
		},
		{
			.Move = MOVE_POWER_SPLIT,
			.Level = 29,
		},
		{
			.Move = MOVE_GUARD_SPLIT,
			.Level = 29,
		},
		{
			.Move = MOVE_KNOCK_OFF,
			.Level = 46,
		},
		{
			.Move = MOVE_WONDER_ROOM,
			.Level = 50,
		},
		{
			.Move = MOVE_TRICK_ROOM,
			.Level = 50,
		},
		{
			.Move = MOVE_DARK_PULSE,
			.Level = 55,
		},
		{
			.Move = MOVE_PSYCHIC,
			.Level = 75,
		},
		{
			.Move = MOVE_HYPERSPACE_FURY,
			.Level = 85,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_822] = {
		{
			.Move = MOVE_FISSURE,
			.Level = 1,
		},
		{
			.Move = MOVE_ERUPTION,
			.Level = 1,
		},
		{
			.Move = MOVE_GROWL,
			.Level = 1,
		},
		{
			.Move = MOVE_TACKLE,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 1,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 5,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 8,
		},
		{
			.Move = MOVE_MAGNITUDE,
			.Level = 12,
		},
		{
			.Move = MOVE_FLAME_BURST,
			.Level = 15,
		},
		{
			.Move = MOVE_AMNESIA,
			.Level = 19,
		},
		{
			.Move = MOVE_LAVA_PLUME,
			.Level = 22,
		},
		{
			.Move = MOVE_EARTH_POWER,
			.Level = 26,
		},
		{
			.Move = MOVE_CURSE,
			.Level = 29,
		},
		{
			.Move = MOVE_TAKE_DOWN,
			.Level = 31,
		},
		{
			.Move = MOVE_ROCK_SLIDE,
			.Level = 33,
		},
		{
			.Move = MOVE_YAWN,
			.Level = 39,
		},
		{
			.Move = MOVE_EARTHQUAKE,
			.Level = 46,
		},
		{
			.Move = MOVE_ERUPTION,
			.Level = 52,
		},
		{
			.Move = MOVE_FISSURE,
			.Level = 59,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_823] = {
		{
			.Move = MOVE_HEALING_WISH,
			.Level = 1,
		},
		{
			.Move = MOVE_BOUNCE,
			.Level = 1,
		},
		{
			.Move = MOVE_ROTOTILLER,
			.Level = 1,
		},
		{
			.Move = MOVE_MIRROR_COAT,
			.Level = 1,
		},
		{
			.Move = MOVE_MAGIC_COAT,
			.Level = 1,
		},
		{
			.Move = MOVE_DEFENSE_CURL,
			.Level = 1,
		},
		{
			.Move = MOVE_SPLASH,
			.Level = 1,
		},
		{
			.Move = MOVE_POUND,
			.Level = 1,
		},
		{
			.Move = MOVE_FORESIGHT,
			.Level = 1,
		},
		{
			.Move = MOVE_ENDURE,
			.Level = 6,
		},
		{
			.Move = MOVE_RETURN,
			.Level = 13,
		},
		{
			.Move = MOVE_QUICK_ATTACK,
			.Level = 16,
		},
		{
			.Move = MOVE_JUMP_KICK,
			.Level = 23,
		},
		{
			.Move = MOVE_BATON_PASS,
			.Level = 26,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 33,
		},
		{
			.Move = MOVE_DIZZY_PUNCH,
			.Level = 36,
		},
		{
			.Move = MOVE_AFTER_YOU,
			.Level = 43,
		},
		{
			.Move = MOVE_CHARM,
			.Level = 46,
		},
		{
			.Move = MOVE_ENTRAINMENT,
			.Level = 53,
		},
		{
			.Move = MOVE_BOUNCE,
			.Level = 56,
		},
		{
			.Move = MOVE_HEALING_WISH,
			.Level = 63,
		},
		{
			.Move = MOVE_HI_JUMP_KICK,
			.Level = 66,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_824] = {
		{
			.Move = MOVE_DRAGON_TAIL,
			.Level = 1,
		},
		{
			.Move = MOVE_FIRE_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_THUNDER_FANG,
			.Level = 1,
		},
		{
			.Move = MOVE_RAGE,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 1,
		},
		{
			.Move = MOVE_LEER,
			.Level = 1,
		},
		{
			.Move = MOVE_BITE,
			.Level = 1,
		},
		{
			.Move = MOVE_EMBER,
			.Level = 4,
		},
		{
			.Move = MOVE_LEER,
			.Level = 7,
		},
		{
			.Move = MOVE_BITE,
			.Level = 10,
		},
		{
			.Move = MOVE_DRAGONBREATH,
			.Level = 13,
		},
		{
			.Move = MOVE_HEADBUTT,
			.Level = 17,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 21,
		},
		{
			.Move = MOVE_CRUNCH,
			.Level = 25,
		},
		{
			.Move = MOVE_DRAGON_CLAW,
			.Level = 29,
		},
		{
			.Move = MOVE_PROTECT,
			.Level = 30,
		},
		{
			.Move = MOVE_ZEN_HEADBUTT,
			.Level = 35,
		},
		{
			.Move = MOVE_SCARY_FACE,
			.Level = 42,
		},
		{
			.Move = MOVE_FLAMETHROWER,
			.Level = 49,
		},
		{
			.Move = MOVE_FLY,
			.Level = 50,
		},
		{
			.Move = MOVE_DOUBLEEDGE,
			.Level = 63,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
	[LEARNSET_825] = {
		{
			.Move = MOVE_FURY_ATTACK,
			.Level = 1,
		},
		{
			.Move = MOVE_FURY_ATTACK,
			.Level = 10,
		},
		{
			.Move = MOVE_FOCUS_ENERGY,
			.Level = 13,
		},
		{
			.Move = MOVE_TWINEEDLE,
			.Level = 16,
		},
		{
			.Move = MOVE_RAGE,
			.Level = 19,
		},
		{
			.Move = MOVE_PURSUIT,
			.Level = 22,
		},
		{
			.Move = MOVE_TOXIC_SPIKES,
			.Level = 25,
		},
		{
			.Move = MOVE_PIN_MISSILE,
			.Level = 28,
		},
		{
			.Move = MOVE_AGILITY,
			.Level = 31,
		},
		{
			.Move = MOVE_ASSURANCE,
			.Level = 34,
		},
		{
			.Move = MOVE_POISON_JAB,
			.Level = 37,
		},
		{
			.Move = MOVE_ENDEAVOR,
			.Level = 40,
		},
		{
			.Move = MOVE_FELL_STINGER,
			.Level = 45,
		},
		{
			.Move = ENTRIES_END,
			.Level = 65535,
		},
	},
};