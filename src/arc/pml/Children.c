#include "Species.h"
#include "Children.h"

u32 __size = sizeof(CHILD_DATA);

const CHILD_DATA __data[] = {
	[SPECIES_NONE] = {
		.ID = 0,
	},
	[SPECIES_BULBASAUR] = {
		.ID = 1,
	},
	[SPECIES_IVYSAUR] = {
		.ID = 1,
	},
	[SPECIES_VENUSAUR] = {
		.ID = 1,
	},
	[SPECIES_CHARMANDER] = {
		.ID = 4,
	},
	[SPECIES_CHARMELEON] = {
		.ID = 4,
	},
	[SPECIES_CHARIZARD] = {
		.ID = 4,
	},
	[SPECIES_SQUIRTLE] = {
		.ID = 7,
	},
	[SPECIES_WARTORTLE] = {
		.ID = 7,
	},
	[SPECIES_BLASTOISE] = {
		.ID = 7,
	},
	[SPECIES_CATERPIE] = {
		.ID = 10,
	},
	[SPECIES_METAPOD] = {
		.ID = 10,
	},
	[SPECIES_BUTTERFREE] = {
		.ID = 10,
	},
	[SPECIES_WEEDLE] = {
		.ID = 13,
	},
	[SPECIES_KAKUNA] = {
		.ID = 13,
	},
	[SPECIES_BEEDRILL] = {
		.ID = 13,
	},
	[SPECIES_PIDGEY] = {
		.ID = 16,
	},
	[SPECIES_PIDGEOTTO] = {
		.ID = 16,
	},
	[SPECIES_PIDGEOT] = {
		.ID = 16,
	},
	[SPECIES_RATTATA] = {
		.ID = 19,
	},
	[SPECIES_RATICATE] = {
		.ID = 19,
	},
	[SPECIES_SPEAROW] = {
		.ID = 21,
	},
	[SPECIES_FEAROW] = {
		.ID = 21,
	},
	[SPECIES_EKANS] = {
		.ID = 23,
	},
	[SPECIES_ARBOK] = {
		.ID = 23,
	},
	[SPECIES_PIKACHU] = {
		.ID = 172,
	},
	[SPECIES_RAICHU] = {
		.ID = 172,
	},
	[SPECIES_SANDSHREW] = {
		.ID = 27,
	},
	[SPECIES_SANDSLASH] = {
		.ID = 27,
	},
	[SPECIES_NIDORAN_M] = {
		.ID = 29,
	},
	[SPECIES_NIDORINA] = {
		.ID = 29,
	},
	[SPECIES_NIDOQUEEN] = {
		.ID = 29,
	},
	[SPECIES_NIDORAN_F] = {
		.ID = 32,
	},
	[SPECIES_NIDORINO] = {
		.ID = 32,
	},
	[SPECIES_NIDOKING] = {
		.ID = 32,
	},
	[SPECIES_CLEFAIRY] = {
		.ID = 173,
	},
	[SPECIES_CLEFABLE] = {
		.ID = 173,
	},
	[SPECIES_VULPIX] = {
		.ID = 37,
	},
	[SPECIES_NINETALES] = {
		.ID = 37,
	},
	[SPECIES_JIGGLYPUFF] = {
		.ID = 174,
	},
	[SPECIES_WIGGLYTUFF] = {
		.ID = 174,
	},
	[SPECIES_ZUBAT] = {
		.ID = 41,
	},
	[SPECIES_GOLBAT] = {
		.ID = 41,
	},
	[SPECIES_ODDISH] = {
		.ID = 43,
	},
	[SPECIES_GLOOM] = {
		.ID = 43,
	},
	[SPECIES_VILEPLUME] = {
		.ID = 43,
	},
	[SPECIES_PARAS] = {
		.ID = 46,
	},
	[SPECIES_PARASECT] = {
		.ID = 46,
	},
	[SPECIES_VENONAT] = {
		.ID = 48,
	},
	[SPECIES_VENOMOTH] = {
		.ID = 48,
	},
	[SPECIES_DIGLETT] = {
		.ID = 50,
	},
	[SPECIES_DUGTRIO] = {
		.ID = 50,
	},
	[SPECIES_MEOWTH] = {
		.ID = 52,
	},
	[SPECIES_PERSIAN] = {
		.ID = 52,
	},
	[SPECIES_PSYDUCK] = {
		.ID = 54,
	},
	[SPECIES_GOLDUCK] = {
		.ID = 54,
	},
	[SPECIES_MANKEY] = {
		.ID = 56,
	},
	[SPECIES_PRIMEAPE] = {
		.ID = 56,
	},
	[SPECIES_GROWLITHE] = {
		.ID = 58,
	},
	[SPECIES_ARCANINE] = {
		.ID = 58,
	},
	[SPECIES_POLIWAG] = {
		.ID = 60,
	},
	[SPECIES_POLIWHIRL] = {
		.ID = 60,
	},
	[SPECIES_POLIWRATH] = {
		.ID = 60,
	},
	[SPECIES_ABRA] = {
		.ID = 63,
	},
	[SPECIES_KADABRA] = {
		.ID = 63,
	},
	[SPECIES_ALAKAZAM] = {
		.ID = 63,
	},
	[SPECIES_MACHOP] = {
		.ID = 66,
	},
	[SPECIES_MACHOKE] = {
		.ID = 66,
	},
	[SPECIES_MACHAMP] = {
		.ID = 66,
	},
	[SPECIES_BELLSPROUT] = {
		.ID = 69,
	},
	[SPECIES_WEEPINBELL] = {
		.ID = 69,
	},
	[SPECIES_VICTREEBEL] = {
		.ID = 69,
	},
	[SPECIES_TENTACOOL] = {
		.ID = 72,
	},
	[SPECIES_TENTACRUEL] = {
		.ID = 72,
	},
	[SPECIES_GEODUDE] = {
		.ID = 74,
	},
	[SPECIES_GRAVELER] = {
		.ID = 74,
	},
	[SPECIES_GOLEM] = {
		.ID = 74,
	},
	[SPECIES_PONYTA] = {
		.ID = 77,
	},
	[SPECIES_RAPIDASH] = {
		.ID = 77,
	},
	[SPECIES_SLOWPOKE] = {
		.ID = 79,
	},
	[SPECIES_SLOWBRO] = {
		.ID = 79,
	},
	[SPECIES_MAGNEMITE] = {
		.ID = 81,
	},
	[SPECIES_MAGNETON] = {
		.ID = 81,
	},
	[SPECIES_FARFETCHD] = {
		.ID = 83,
	},
	[SPECIES_DODUO] = {
		.ID = 84,
	},
	[SPECIES_DODRIO] = {
		.ID = 84,
	},
	[SPECIES_SEEL] = {
		.ID = 86,
	},
	[SPECIES_DEWGONG] = {
		.ID = 86,
	},
	[SPECIES_GRIMER] = {
		.ID = 88,
	},
	[SPECIES_MUK] = {
		.ID = 88,
	},
	[SPECIES_SHELLDER] = {
		.ID = 90,
	},
	[SPECIES_CLOYSTER] = {
		.ID = 90,
	},
	[SPECIES_GASTLY] = {
		.ID = 92,
	},
	[SPECIES_HAUNTER] = {
		.ID = 92,
	},
	[SPECIES_GENGAR] = {
		.ID = 92,
	},
	[SPECIES_ONIX] = {
		.ID = 95,
	},
	[SPECIES_DROWZEE] = {
		.ID = 96,
	},
	[SPECIES_HYPNO] = {
		.ID = 96,
	},
	[SPECIES_KRABBY] = {
		.ID = 98,
	},
	[SPECIES_KINGLER] = {
		.ID = 98,
	},
	[SPECIES_VOLTORB] = {
		.ID = 100,
	},
	[SPECIES_ELECTRODE] = {
		.ID = 100,
	},
	[SPECIES_EXEGGCUTE] = {
		.ID = 102,
	},
	[SPECIES_EXEGGUTOR] = {
		.ID = 102,
	},
	[SPECIES_CUBONE] = {
		.ID = 104,
	},
	[SPECIES_MAROWAK] = {
		.ID = 104,
	},
	[SPECIES_HITMONLEE] = {
		.ID = 236,
	},
	[SPECIES_HITMONCHAN] = {
		.ID = 236,
	},
	[SPECIES_LICKITUNG] = {
		.ID = 108,
	},
	[SPECIES_KOFFING] = {
		.ID = 109,
	},
	[SPECIES_WEEZING] = {
		.ID = 109,
	},
	[SPECIES_RHYHORN] = {
		.ID = 111,
	},
	[SPECIES_RHYDON] = {
		.ID = 111,
	},
	[SPECIES_CHANSEY] = {
		.ID = 440,
	},
	[SPECIES_TANGELA] = {
		.ID = 114,
	},
	[SPECIES_KANGASKHAN] = {
		.ID = 115,
	},
	[SPECIES_HORSEA] = {
		.ID = 116,
	},
	[SPECIES_SEADRA] = {
		.ID = 116,
	},
	[SPECIES_GOLDEEN] = {
		.ID = 118,
	},
	[SPECIES_SEAKING] = {
		.ID = 118,
	},
	[SPECIES_STARYU] = {
		.ID = 120,
	},
	[SPECIES_STARMIE] = {
		.ID = 120,
	},
	[SPECIES_MR_MIME] = {
		.ID = 439,
	},
	[SPECIES_SCYTHER] = {
		.ID = 123,
	},
	[SPECIES_JYNX] = {
		.ID = 238,
	},
	[SPECIES_ELECTABUZZ] = {
		.ID = 239,
	},
	[SPECIES_MAGMAR] = {
		.ID = 240,
	},
	[SPECIES_PINSIR] = {
		.ID = 127,
	},
	[SPECIES_TAUROS] = {
		.ID = 128,
	},
	[SPECIES_MAGIKARP] = {
		.ID = 129,
	},
	[SPECIES_GYARADOS] = {
		.ID = 129,
	},
	[SPECIES_LAPRAS] = {
		.ID = 131,
	},
	[SPECIES_DITTO] = {
		.ID = 132,
	},
	[SPECIES_EEVEE] = {
		.ID = 133,
	},
	[SPECIES_VAPOREON] = {
		.ID = 133,
	},
	[SPECIES_JOLTEON] = {
		.ID = 133,
	},
	[SPECIES_FLAREON] = {
		.ID = 133,
	},
	[SPECIES_PORYGON] = {
		.ID = 137,
	},
	[SPECIES_OMANYTE] = {
		.ID = 138,
	},
	[SPECIES_OMASTAR] = {
		.ID = 138,
	},
	[SPECIES_KABUTO] = {
		.ID = 140,
	},
	[SPECIES_KABUTOPS] = {
		.ID = 140,
	},
	[SPECIES_AERODACTYL] = {
		.ID = 142,
	},
	[SPECIES_SNORLAX] = {
		.ID = 446,
	},
	[SPECIES_ARTICUNO] = {
		.ID = 144,
	},
	[SPECIES_ZAPDOS] = {
		.ID = 145,
	},
	[SPECIES_MOLTRES] = {
		.ID = 146,
	},
	[SPECIES_DRATINI] = {
		.ID = 147,
	},
	[SPECIES_DRAGONAIR] = {
		.ID = 147,
	},
	[SPECIES_DRAGONITE] = {
		.ID = 147,
	},
	[SPECIES_MEWTWO] = {
		.ID = 150,
	},
	[SPECIES_MEW] = {
		.ID = 151,
	},
	[SPECIES_CHIKORITA] = {
		.ID = 152,
	},
	[SPECIES_BAYLEEF] = {
		.ID = 152,
	},
	[SPECIES_MEGANIUM] = {
		.ID = 152,
	},
	[SPECIES_CYNDAQUIL] = {
		.ID = 155,
	},
	[SPECIES_QUILAVA] = {
		.ID = 155,
	},
	[SPECIES_TYPHLOSION] = {
		.ID = 155,
	},
	[SPECIES_TOTODILE] = {
		.ID = 158,
	},
	[SPECIES_CROCONAW] = {
		.ID = 158,
	},
	[SPECIES_FERALIGATR] = {
		.ID = 158,
	},
	[SPECIES_SENTRET] = {
		.ID = 161,
	},
	[SPECIES_FURRET] = {
		.ID = 161,
	},
	[SPECIES_HOOTHOOT] = {
		.ID = 163,
	},
	[SPECIES_NOCTOWL] = {
		.ID = 163,
	},
	[SPECIES_LEDYBA] = {
		.ID = 165,
	},
	[SPECIES_LEDIAN] = {
		.ID = 165,
	},
	[SPECIES_SPINARAK] = {
		.ID = 167,
	},
	[SPECIES_ARIADOS] = {
		.ID = 167,
	},
	[SPECIES_CROBAT] = {
		.ID = 41,
	},
	[SPECIES_CHINCHOU] = {
		.ID = 170,
	},
	[SPECIES_LANTURN] = {
		.ID = 170,
	},
	[SPECIES_PICHU] = {
		.ID = 172,
	},
	[SPECIES_CLEFFA] = {
		.ID = 173,
	},
	[SPECIES_IGGLYBUFF] = {
		.ID = 174,
	},
	[SPECIES_TOGEPI] = {
		.ID = 175,
	},
	[SPECIES_TOGETIC] = {
		.ID = 175,
	},
	[SPECIES_NATU] = {
		.ID = 177,
	},
	[SPECIES_XATU] = {
		.ID = 177,
	},
	[SPECIES_MAREEP] = {
		.ID = 179,
	},
	[SPECIES_FLAAFFY] = {
		.ID = 179,
	},
	[SPECIES_AMPHAROS] = {
		.ID = 179,
	},
	[SPECIES_BELLOSSOM] = {
		.ID = 43,
	},
	[SPECIES_MARILL] = {
		.ID = 298,
	},
	[SPECIES_AZUMARILL] = {
		.ID = 298,
	},
	[SPECIES_SUDOWOODO] = {
		.ID = 438,
	},
	[SPECIES_POLITOED] = {
		.ID = 60,
	},
	[SPECIES_HOPPIP] = {
		.ID = 187,
	},
	[SPECIES_SKIPLOOM] = {
		.ID = 187,
	},
	[SPECIES_JUMPLUFF] = {
		.ID = 187,
	},
	[SPECIES_AIPOM] = {
		.ID = 190,
	},
	[SPECIES_SUNKERN] = {
		.ID = 191,
	},
	[SPECIES_SUNFLORA] = {
		.ID = 191,
	},
	[SPECIES_YANMA] = {
		.ID = 193,
	},
	[SPECIES_WOOPER] = {
		.ID = 194,
	},
	[SPECIES_QUAGSIRE] = {
		.ID = 194,
	},
	[SPECIES_ESPEON] = {
		.ID = 133,
	},
	[SPECIES_UMBREON] = {
		.ID = 133,
	},
	[SPECIES_MURKROW] = {
		.ID = 198,
	},
	[SPECIES_SLOWKING] = {
		.ID = 79,
	},
	[SPECIES_MISDREAVUS] = {
		.ID = 200,
	},
	[SPECIES_UNOWN] = {
		.ID = 201,
	},
	[SPECIES_WOBBUFFET] = {
		.ID = 360,
	},
	[SPECIES_GIRAFARIG] = {
		.ID = 203,
	},
	[SPECIES_PINECO] = {
		.ID = 204,
	},
	[SPECIES_FORRETRESS] = {
		.ID = 204,
	},
	[SPECIES_DUNSPARCE] = {
		.ID = 206,
	},
	[SPECIES_GLIGAR] = {
		.ID = 207,
	},
	[SPECIES_STEELIX] = {
		.ID = 95,
	},
	[SPECIES_SNUBBULL] = {
		.ID = 209,
	},
	[SPECIES_GRANBULL] = {
		.ID = 209,
	},
	[SPECIES_QWILFISH] = {
		.ID = 211,
	},
	[SPECIES_SCIZOR] = {
		.ID = 123,
	},
	[SPECIES_SHUCKLE] = {
		.ID = 213,
	},
	[SPECIES_HERACROSS] = {
		.ID = 214,
	},
	[SPECIES_SNEASEL] = {
		.ID = 215,
	},
	[SPECIES_TEDDIURSA] = {
		.ID = 216,
	},
	[SPECIES_URSARING] = {
		.ID = 216,
	},
	[SPECIES_SLUGMA] = {
		.ID = 218,
	},
	[SPECIES_MAGCARGO] = {
		.ID = 218,
	},
	[SPECIES_SWINUB] = {
		.ID = 220,
	},
	[SPECIES_PILOSWINE] = {
		.ID = 220,
	},
	[SPECIES_CORSOLA] = {
		.ID = 222,
	},
	[SPECIES_REMORAID] = {
		.ID = 223,
	},
	[SPECIES_OCTILLERY] = {
		.ID = 223,
	},
	[SPECIES_DELIBIRD] = {
		.ID = 225,
	},
	[SPECIES_MANTINE] = {
		.ID = 458,
	},
	[SPECIES_SKARMORY] = {
		.ID = 227,
	},
	[SPECIES_HOUNDOUR] = {
		.ID = 228,
	},
	[SPECIES_HOUNDOOM] = {
		.ID = 228,
	},
	[SPECIES_KINGDRA] = {
		.ID = 116,
	},
	[SPECIES_PHANPY] = {
		.ID = 231,
	},
	[SPECIES_DONPHAN] = {
		.ID = 231,
	},
	[SPECIES_PORYGON2] = {
		.ID = 137,
	},
	[SPECIES_STANTLER] = {
		.ID = 234,
	},
	[SPECIES_SMEARGLE] = {
		.ID = 235,
	},
	[SPECIES_TYROGUE] = {
		.ID = 236,
	},
	[SPECIES_HITMONTOP] = {
		.ID = 236,
	},
	[SPECIES_SMOOCHUM] = {
		.ID = 238,
	},
	[SPECIES_ELEKID] = {
		.ID = 239,
	},
	[SPECIES_MAGBY] = {
		.ID = 240,
	},
	[SPECIES_MILTANK] = {
		.ID = 241,
	},
	[SPECIES_BLISSEY] = {
		.ID = 440,
	},
	[SPECIES_RAIKOU] = {
		.ID = 243,
	},
	[SPECIES_ENTEI] = {
		.ID = 244,
	},
	[SPECIES_SUICUNE] = {
		.ID = 245,
	},
	[SPECIES_LARVITAR] = {
		.ID = 246,
	},
	[SPECIES_PUPITAR] = {
		.ID = 246,
	},
	[SPECIES_TYRANITAR] = {
		.ID = 246,
	},
	[SPECIES_LUGIA] = {
		.ID = 249,
	},
	[SPECIES_HOOH] = {
		.ID = 250,
	},
	[SPECIES_CELEBI] = {
		.ID = 251,
	},
	[SPECIES_TREECKO] = {
		.ID = 252,
	},
	[SPECIES_GROVYLE] = {
		.ID = 252,
	},
	[SPECIES_SCEPTILE] = {
		.ID = 252,
	},
	[SPECIES_TORCHIC] = {
		.ID = 255,
	},
	[SPECIES_COMBUSKEN] = {
		.ID = 255,
	},
	[SPECIES_BLAZIKEN] = {
		.ID = 255,
	},
	[SPECIES_MUDKIP] = {
		.ID = 258,
	},
	[SPECIES_MARSHTOMP] = {
		.ID = 258,
	},
	[SPECIES_SWAMPERT] = {
		.ID = 258,
	},
	[SPECIES_POOCHYENA] = {
		.ID = 261,
	},
	[SPECIES_MIGHTYENA] = {
		.ID = 261,
	},
	[SPECIES_ZIGZAGOON] = {
		.ID = 263,
	},
	[SPECIES_LINOONE] = {
		.ID = 263,
	},
	[SPECIES_WURMPLE] = {
		.ID = 265,
	},
	[SPECIES_SILCOON] = {
		.ID = 265,
	},
	[SPECIES_BEAUTIFLY] = {
		.ID = 265,
	},
	[SPECIES_CASCOON] = {
		.ID = 265,
	},
	[SPECIES_DUSTOX] = {
		.ID = 265,
	},
	[SPECIES_LOTAD] = {
		.ID = 270,
	},
	[SPECIES_LOMBRE] = {
		.ID = 270,
	},
	[SPECIES_LUDICOLO] = {
		.ID = 270,
	},
	[SPECIES_SEEDOT] = {
		.ID = 273,
	},
	[SPECIES_NUZLEAF] = {
		.ID = 273,
	},
	[SPECIES_SHIFTRY] = {
		.ID = 273,
	},
	[SPECIES_TAILLOW] = {
		.ID = 276,
	},
	[SPECIES_SWELLOW] = {
		.ID = 276,
	},
	[SPECIES_WINGULL] = {
		.ID = 278,
	},
	[SPECIES_PELIPPER] = {
		.ID = 278,
	},
	[SPECIES_RALTS] = {
		.ID = 280,
	},
	[SPECIES_KIRLIA] = {
		.ID = 280,
	},
	[SPECIES_GARDEVOIR] = {
		.ID = 280,
	},
	[SPECIES_SURSKIT] = {
		.ID = 283,
	},
	[SPECIES_MASQUERAIN] = {
		.ID = 283,
	},
	[SPECIES_SHROOMISH] = {
		.ID = 285,
	},
	[SPECIES_BRELOOM] = {
		.ID = 285,
	},
	[SPECIES_SLAKOTH] = {
		.ID = 287,
	},
	[SPECIES_VIGOROTH] = {
		.ID = 287,
	},
	[SPECIES_SLAKING] = {
		.ID = 287,
	},
	[SPECIES_NINCADA] = {
		.ID = 290,
	},
	[SPECIES_NINJASK] = {
		.ID = 290,
	},
	[SPECIES_SHEDINJA] = {
		.ID = 290,
	},
	[SPECIES_WHISMUR] = {
		.ID = 293,
	},
	[SPECIES_LOUDRED] = {
		.ID = 293,
	},
	[SPECIES_EXPLOUD] = {
		.ID = 293,
	},
	[SPECIES_MAKUHITA] = {
		.ID = 296,
	},
	[SPECIES_HARIYAMA] = {
		.ID = 296,
	},
	[SPECIES_AZURILL] = {
		.ID = 298,
	},
	[SPECIES_NOSEPASS] = {
		.ID = 299,
	},
	[SPECIES_SKITTY] = {
		.ID = 300,
	},
	[SPECIES_DELCATTY] = {
		.ID = 300,
	},
	[SPECIES_SABLEYE] = {
		.ID = 302,
	},
	[SPECIES_MAWILE] = {
		.ID = 303,
	},
	[SPECIES_ARON] = {
		.ID = 304,
	},
	[SPECIES_LAIRON] = {
		.ID = 304,
	},
	[SPECIES_AGGRON] = {
		.ID = 304,
	},
	[SPECIES_MEDITITE] = {
		.ID = 307,
	},
	[SPECIES_MEDICHAM] = {
		.ID = 307,
	},
	[SPECIES_ELECTRIKE] = {
		.ID = 309,
	},
	[SPECIES_MANECTRIC] = {
		.ID = 309,
	},
	[SPECIES_PLUSLE] = {
		.ID = 311,
	},
	[SPECIES_MINUN] = {
		.ID = 312,
	},
	[SPECIES_VOLBEAT] = {
		.ID = 313,
	},
	[SPECIES_ILLUMISE] = {
		.ID = 314,
	},
	[SPECIES_ROSELIA] = {
		.ID = 406,
	},
	[SPECIES_GULPIN] = {
		.ID = 316,
	},
	[SPECIES_SWALOT] = {
		.ID = 316,
	},
	[SPECIES_CARVANHA] = {
		.ID = 318,
	},
	[SPECIES_SHARPEDO] = {
		.ID = 318,
	},
	[SPECIES_WAILMER] = {
		.ID = 320,
	},
	[SPECIES_WAILORD] = {
		.ID = 320,
	},
	[SPECIES_NUMEL] = {
		.ID = 322,
	},
	[SPECIES_CAMERUPT] = {
		.ID = 322,
	},
	[SPECIES_TORKOAL] = {
		.ID = 324,
	},
	[SPECIES_SPOINK] = {
		.ID = 325,
	},
	[SPECIES_GRUMPIG] = {
		.ID = 325,
	},
	[SPECIES_SPINDA] = {
		.ID = 327,
	},
	[SPECIES_TRAPINCH] = {
		.ID = 328,
	},
	[SPECIES_VIBRAVA] = {
		.ID = 328,
	},
	[SPECIES_FLYGON] = {
		.ID = 328,
	},
	[SPECIES_CACNEA] = {
		.ID = 331,
	},
	[SPECIES_CACTURNE] = {
		.ID = 331,
	},
	[SPECIES_SWABLU] = {
		.ID = 333,
	},
	[SPECIES_ALTARIA] = {
		.ID = 333,
	},
	[SPECIES_ZANGOOSE] = {
		.ID = 335,
	},
	[SPECIES_SEVIPER] = {
		.ID = 336,
	},
	[SPECIES_LUNATONE] = {
		.ID = 337,
	},
	[SPECIES_SOLROCK] = {
		.ID = 338,
	},
	[SPECIES_BARBOACH] = {
		.ID = 339,
	},
	[SPECIES_WHISCASH] = {
		.ID = 339,
	},
	[SPECIES_CORPHISH] = {
		.ID = 341,
	},
	[SPECIES_CRAWDAUNT] = {
		.ID = 341,
	},
	[SPECIES_BALTOY] = {
		.ID = 343,
	},
	[SPECIES_CLAYDOL] = {
		.ID = 343,
	},
	[SPECIES_LILEEP] = {
		.ID = 345,
	},
	[SPECIES_CRADILY] = {
		.ID = 345,
	},
	[SPECIES_ANORITH] = {
		.ID = 347,
	},
	[SPECIES_ARMALDO] = {
		.ID = 347,
	},
	[SPECIES_FEEBAS] = {
		.ID = 349,
	},
	[SPECIES_MILOTIC] = {
		.ID = 349,
	},
	[SPECIES_CASTFORM] = {
		.ID = 351,
	},
	[SPECIES_KECLEON] = {
		.ID = 352,
	},
	[SPECIES_SHUPPET] = {
		.ID = 353,
	},
	[SPECIES_BANETTE] = {
		.ID = 353,
	},
	[SPECIES_DUSKULL] = {
		.ID = 355,
	},
	[SPECIES_DUSCLOPS] = {
		.ID = 355,
	},
	[SPECIES_TROPIUS] = {
		.ID = 357,
	},
	[SPECIES_CHIMECHO] = {
		.ID = 433,
	},
	[SPECIES_ABSOL] = {
		.ID = 359,
	},
	[SPECIES_WYNAUT] = {
		.ID = 360,
	},
	[SPECIES_SNORUNT] = {
		.ID = 361,
	},
	[SPECIES_GLALIE] = {
		.ID = 361,
	},
	[SPECIES_SPHEAL] = {
		.ID = 363,
	},
	[SPECIES_SEALEO] = {
		.ID = 363,
	},
	[SPECIES_WALREIN] = {
		.ID = 363,
	},
	[SPECIES_CLAMPERL] = {
		.ID = 366,
	},
	[SPECIES_HUNTAIL] = {
		.ID = 366,
	},
	[SPECIES_GOREBYSS] = {
		.ID = 366,
	},
	[SPECIES_RELICANTH] = {
		.ID = 369,
	},
	[SPECIES_LUVDISC] = {
		.ID = 370,
	},
	[SPECIES_BAGON] = {
		.ID = 371,
	},
	[SPECIES_SHELGON] = {
		.ID = 371,
	},
	[SPECIES_SALAMENCE] = {
		.ID = 371,
	},
	[SPECIES_BELDUM] = {
		.ID = 374,
	},
	[SPECIES_METANG] = {
		.ID = 374,
	},
	[SPECIES_METAGROSS] = {
		.ID = 374,
	},
	[SPECIES_REGIROCK] = {
		.ID = 377,
	},
	[SPECIES_REGICE] = {
		.ID = 378,
	},
	[SPECIES_REGISTEEL] = {
		.ID = 379,
	},
	[SPECIES_LATIAS] = {
		.ID = 380,
	},
	[SPECIES_LATIOS] = {
		.ID = 381,
	},
	[SPECIES_KYOGRE] = {
		.ID = 382,
	},
	[SPECIES_GROUDON] = {
		.ID = 383,
	},
	[SPECIES_RAYQUAZA] = {
		.ID = 384,
	},
	[SPECIES_JIRACHI] = {
		.ID = 385,
	},
	[SPECIES_DEOXYS] = {
		.ID = 386,
	},
	[SPECIES_TURTWIG] = {
		.ID = 387,
	},
	[SPECIES_GROTLE] = {
		.ID = 387,
	},
	[SPECIES_TORTERRA] = {
		.ID = 387,
	},
	[SPECIES_CHIMCHAR] = {
		.ID = 390,
	},
	[SPECIES_MONFERNO] = {
		.ID = 390,
	},
	[SPECIES_INFERNAPE] = {
		.ID = 390,
	},
	[SPECIES_PIPLUP] = {
		.ID = 393,
	},
	[SPECIES_PRINPLUP] = {
		.ID = 393,
	},
	[SPECIES_EMPOLEON] = {
		.ID = 393,
	},
	[SPECIES_STARLY] = {
		.ID = 396,
	},
	[SPECIES_STARAVIA] = {
		.ID = 396,
	},
	[SPECIES_STARAPTOR] = {
		.ID = 396,
	},
	[SPECIES_BIDOOF] = {
		.ID = 399,
	},
	[SPECIES_BIBAREL] = {
		.ID = 399,
	},
	[SPECIES_KRICKETOT] = {
		.ID = 401,
	},
	[SPECIES_KRICKETUNE] = {
		.ID = 401,
	},
	[SPECIES_SHINX] = {
		.ID = 403,
	},
	[SPECIES_LUXIO] = {
		.ID = 403,
	},
	[SPECIES_LUXRAY] = {
		.ID = 403,
	},
	[SPECIES_BUDEW] = {
		.ID = 406,
	},
	[SPECIES_ROSERADE] = {
		.ID = 406,
	},
	[SPECIES_CRANIDOS] = {
		.ID = 408,
	},
	[SPECIES_RAMPARDOS] = {
		.ID = 408,
	},
	[SPECIES_SHIELDON] = {
		.ID = 410,
	},
	[SPECIES_BASTIODON] = {
		.ID = 410,
	},
	[SPECIES_BURMY] = {
		.ID = 412,
	},
	[SPECIES_WORMADAM] = {
		.ID = 412,
	},
	[SPECIES_MOTHIM] = {
		.ID = 412,
	},
	[SPECIES_COMBEE] = {
		.ID = 415,
	},
	[SPECIES_VESPIQUEN] = {
		.ID = 415,
	},
	[SPECIES_PACHIRISU] = {
		.ID = 417,
	},
	[SPECIES_BUIZEL] = {
		.ID = 418,
	},
	[SPECIES_FLOATZEL] = {
		.ID = 418,
	},
	[SPECIES_CHERUBI] = {
		.ID = 420,
	},
	[SPECIES_CHERRIM] = {
		.ID = 420,
	},
	[SPECIES_SHELLOS] = {
		.ID = 422,
	},
	[SPECIES_GASTRODON] = {
		.ID = 422,
	},
	[SPECIES_AMBIPOM] = {
		.ID = 190,
	},
	[SPECIES_DRIFLOON] = {
		.ID = 425,
	},
	[SPECIES_DRIFBLIM] = {
		.ID = 425,
	},
	[SPECIES_BUNEARY] = {
		.ID = 427,
	},
	[SPECIES_LOPUNNY] = {
		.ID = 427,
	},
	[SPECIES_MISMAGIUS] = {
		.ID = 200,
	},
	[SPECIES_HONCHKROW] = {
		.ID = 198,
	},
	[SPECIES_GLAMEOW] = {
		.ID = 431,
	},
	[SPECIES_PURUGLY] = {
		.ID = 431,
	},
	[SPECIES_CHINGLING] = {
		.ID = 433,
	},
	[SPECIES_STUNKY] = {
		.ID = 434,
	},
	[SPECIES_SKUNTANK] = {
		.ID = 434,
	},
	[SPECIES_BRONZOR] = {
		.ID = 436,
	},
	[SPECIES_BRONZONG] = {
		.ID = 436,
	},
	[SPECIES_BONSLY] = {
		.ID = 438,
	},
	[SPECIES_MIME_JR] = {
		.ID = 439,
	},
	[SPECIES_HAPPINY] = {
		.ID = 440,
	},
	[SPECIES_CHATOT] = {
		.ID = 441,
	},
	[SPECIES_SPIRITOMB] = {
		.ID = 442,
	},
	[SPECIES_GIBLE] = {
		.ID = 443,
	},
	[SPECIES_GABITE] = {
		.ID = 443,
	},
	[SPECIES_GARCHOMP] = {
		.ID = 443,
	},
	[SPECIES_MUNCHLAX] = {
		.ID = 446,
	},
	[SPECIES_RIOLU] = {
		.ID = 447,
	},
	[SPECIES_LUCARIO] = {
		.ID = 447,
	},
	[SPECIES_HIPPOPOTAS] = {
		.ID = 449,
	},
	[SPECIES_HIPPOWDON] = {
		.ID = 449,
	},
	[SPECIES_SKORUPI] = {
		.ID = 451,
	},
	[SPECIES_DRAPION] = {
		.ID = 451,
	},
	[SPECIES_CROAGUNK] = {
		.ID = 453,
	},
	[SPECIES_TOXICROAK] = {
		.ID = 453,
	},
	[SPECIES_CARNIVINE] = {
		.ID = 455,
	},
	[SPECIES_FINNEON] = {
		.ID = 456,
	},
	[SPECIES_LUMINEON] = {
		.ID = 456,
	},
	[SPECIES_MANTYKE] = {
		.ID = 458,
	},
	[SPECIES_SNOVER] = {
		.ID = 459,
	},
	[SPECIES_ABOMASNOW] = {
		.ID = 459,
	},
	[SPECIES_WEAVILE] = {
		.ID = 215,
	},
	[SPECIES_MAGNEZONE] = {
		.ID = 81,
	},
	[SPECIES_LICKILICKY] = {
		.ID = 108,
	},
	[SPECIES_RHYPERIOR] = {
		.ID = 111,
	},
	[SPECIES_TANGROWTH] = {
		.ID = 114,
	},
	[SPECIES_ELECTIVIRE] = {
		.ID = 239,
	},
	[SPECIES_MAGMORTAR] = {
		.ID = 240,
	},
	[SPECIES_TOGEKISS] = {
		.ID = 175,
	},
	[SPECIES_YANMEGA] = {
		.ID = 193,
	},
	[SPECIES_LEAFEON] = {
		.ID = 133,
	},
	[SPECIES_GLACEON] = {
		.ID = 133,
	},
	[SPECIES_GLISCOR] = {
		.ID = 207,
	},
	[SPECIES_MAMOSWINE] = {
		.ID = 220,
	},
	[SPECIES_PORYGONZ] = {
		.ID = 137,
	},
	[SPECIES_GALLADE] = {
		.ID = 280,
	},
	[SPECIES_PROBOPASS] = {
		.ID = 299,
	},
	[SPECIES_DUSKNOIR] = {
		.ID = 355,
	},
	[SPECIES_FROSLASS] = {
		.ID = 361,
	},
	[SPECIES_ROTOM] = {
		.ID = 479,
	},
	[SPECIES_UXIE] = {
		.ID = 480,
	},
	[SPECIES_MESPRIT] = {
		.ID = 481,
	},
	[SPECIES_AZELF] = {
		.ID = 482,
	},
	[SPECIES_DIALGA] = {
		.ID = 483,
	},
	[SPECIES_PALKIA] = {
		.ID = 484,
	},
	[SPECIES_HEATRAN] = {
		.ID = 485,
	},
	[SPECIES_REGIGIGAS] = {
		.ID = 486,
	},
	[SPECIES_GIRATINA] = {
		.ID = 487,
	},
	[SPECIES_CRESSELIA] = {
		.ID = 488,
	},
	[SPECIES_PHIONE] = {
		.ID = 489,
	},
	[SPECIES_MANAPHY] = {
		.ID = 490,
	},
	[SPECIES_DARKRAI] = {
		.ID = 491,
	},
	[SPECIES_SHAYMIN] = {
		.ID = 492,
	},
	[SPECIES_ARCEUS] = {
		.ID = 493,
	},
	[SPECIES_VICTINI] = {
		.ID = 494,
	},
	[SPECIES_SNIVY] = {
		.ID = 495,
	},
	[SPECIES_SERVINE] = {
		.ID = 495,
	},
	[SPECIES_SERPERIOR] = {
		.ID = 495,
	},
	[SPECIES_TEPIG] = {
		.ID = 498,
	},
	[SPECIES_PIGNITE] = {
		.ID = 498,
	},
	[SPECIES_EMBOAR] = {
		.ID = 498,
	},
	[SPECIES_OSHAWOTT] = {
		.ID = 501,
	},
	[SPECIES_DEWOTT] = {
		.ID = 501,
	},
	[SPECIES_SAMUROTT] = {
		.ID = 501,
	},
	[SPECIES_PATRAT] = {
		.ID = 504,
	},
	[SPECIES_WATCHOG] = {
		.ID = 504,
	},
	[SPECIES_LILLIPUP] = {
		.ID = 506,
	},
	[SPECIES_HERDIER] = {
		.ID = 506,
	},
	[SPECIES_STOUTLAND] = {
		.ID = 506,
	},
	[SPECIES_PURRLOIN] = {
		.ID = 509,
	},
	[SPECIES_LIEPARD] = {
		.ID = 509,
	},
	[SPECIES_PANSAGE] = {
		.ID = 511,
	},
	[SPECIES_SIMISAGE] = {
		.ID = 511,
	},
	[SPECIES_PANSEAR] = {
		.ID = 513,
	},
	[SPECIES_SIMISEAR] = {
		.ID = 513,
	},
	[SPECIES_PANPOUR] = {
		.ID = 515,
	},
	[SPECIES_SIMIPOUR] = {
		.ID = 515,
	},
	[SPECIES_MUNNA] = {
		.ID = 517,
	},
	[SPECIES_MUSHARNA] = {
		.ID = 517,
	},
	[SPECIES_PIDOVE] = {
		.ID = 519,
	},
	[SPECIES_TRANQUILL] = {
		.ID = 519,
	},
	[SPECIES_UNFEZANT] = {
		.ID = 519,
	},
	[SPECIES_BLITZLE] = {
		.ID = 522,
	},
	[SPECIES_ZEBSTRIKA] = {
		.ID = 522,
	},
	[SPECIES_ROGGENROLA] = {
		.ID = 524,
	},
	[SPECIES_BOLDORE] = {
		.ID = 524,
	},
	[SPECIES_GIGALITH] = {
		.ID = 524,
	},
	[SPECIES_WOOBAT] = {
		.ID = 527,
	},
	[SPECIES_SWOOBAT] = {
		.ID = 527,
	},
	[SPECIES_DRILBUR] = {
		.ID = 529,
	},
	[SPECIES_EXCADRILL] = {
		.ID = 529,
	},
	[SPECIES_AUDINO] = {
		.ID = 531,
	},
	[SPECIES_TIMBURR] = {
		.ID = 532,
	},
	[SPECIES_GURDURR] = {
		.ID = 532,
	},
	[SPECIES_CONKELDURR] = {
		.ID = 532,
	},
	[SPECIES_TYMPOLE] = {
		.ID = 535,
	},
	[SPECIES_PALPITOAD] = {
		.ID = 535,
	},
	[SPECIES_SEISMITOAD] = {
		.ID = 535,
	},
	[SPECIES_THROH] = {
		.ID = 538,
	},
	[SPECIES_SAWK] = {
		.ID = 539,
	},
	[SPECIES_SEWADDLE] = {
		.ID = 540,
	},
	[SPECIES_SWADLOON] = {
		.ID = 540,
	},
	[SPECIES_LEAVANNY] = {
		.ID = 540,
	},
	[SPECIES_VENIPEDE] = {
		.ID = 543,
	},
	[SPECIES_WHIRLIPEDE] = {
		.ID = 543,
	},
	[SPECIES_SCOLIPEDE] = {
		.ID = 543,
	},
	[SPECIES_COTTONEE] = {
		.ID = 546,
	},
	[SPECIES_WHIMSICOTT] = {
		.ID = 546,
	},
	[SPECIES_PETILIL] = {
		.ID = 548,
	},
	[SPECIES_LILLIGANT] = {
		.ID = 548,
	},
	[SPECIES_BASCULIN] = {
		.ID = 550,
	},
	[SPECIES_SANDILE] = {
		.ID = 551,
	},
	[SPECIES_KROKOROK] = {
		.ID = 551,
	},
	[SPECIES_KROOKODILE] = {
		.ID = 551,
	},
	[SPECIES_DARUMAKA] = {
		.ID = 554,
	},
	[SPECIES_DARMANITAN] = {
		.ID = 554,
	},
	[SPECIES_MARACTUS] = {
		.ID = 556,
	},
	[SPECIES_DWEBBLE] = {
		.ID = 557,
	},
	[SPECIES_CRUSTLE] = {
		.ID = 557,
	},
	[SPECIES_SCRAGGY] = {
		.ID = 559,
	},
	[SPECIES_SCRAFTY] = {
		.ID = 559,
	},
	[SPECIES_SIGILYPH] = {
		.ID = 561,
	},
	[SPECIES_YAMASK] = {
		.ID = 562,
	},
	[SPECIES_COFAGRIGUS] = {
		.ID = 562,
	},
	[SPECIES_TIRTOUGA] = {
		.ID = 564,
	},
	[SPECIES_CARRACOSTA] = {
		.ID = 564,
	},
	[SPECIES_ARCHEN] = {
		.ID = 566,
	},
	[SPECIES_ARCHEOPS] = {
		.ID = 566,
	},
	[SPECIES_TRUBBISH] = {
		.ID = 568,
	},
	[SPECIES_GARBODOR] = {
		.ID = 568,
	},
	[SPECIES_ZORUA] = {
		.ID = 570,
	},
	[SPECIES_ZOROARK] = {
		.ID = 570,
	},
	[SPECIES_MINCCINO] = {
		.ID = 572,
	},
	[SPECIES_CINCCINO] = {
		.ID = 572,
	},
	[SPECIES_GOTHITA] = {
		.ID = 574,
	},
	[SPECIES_GOTHORITA] = {
		.ID = 574,
	},
	[SPECIES_GOTHITELLE] = {
		.ID = 574,
	},
	[SPECIES_SOLOSIS] = {
		.ID = 577,
	},
	[SPECIES_DUOSION] = {
		.ID = 577,
	},
	[SPECIES_REUNICLUS] = {
		.ID = 577,
	},
	[SPECIES_DUCKLETT] = {
		.ID = 580,
	},
	[SPECIES_SWANNA] = {
		.ID = 580,
	},
	[SPECIES_VANILLITE] = {
		.ID = 582,
	},
	[SPECIES_VANILLISH] = {
		.ID = 582,
	},
	[SPECIES_VANILLUXE] = {
		.ID = 582,
	},
	[SPECIES_DEERLING] = {
		.ID = 585,
	},
	[SPECIES_SAWSBUCK] = {
		.ID = 585,
	},
	[SPECIES_EMOLGA] = {
		.ID = 587,
	},
	[SPECIES_KARRABLAST] = {
		.ID = 588,
	},
	[SPECIES_ESCAVALIER] = {
		.ID = 588,
	},
	[SPECIES_FOONGUS] = {
		.ID = 590,
	},
	[SPECIES_AMOONGUSS] = {
		.ID = 590,
	},
	[SPECIES_FRILLISH] = {
		.ID = 592,
	},
	[SPECIES_JELLICENT] = {
		.ID = 592,
	},
	[SPECIES_ALOMOMOLA] = {
		.ID = 594,
	},
	[SPECIES_JOLTIK] = {
		.ID = 595,
	},
	[SPECIES_GALVANTULA] = {
		.ID = 595,
	},
	[SPECIES_FERROSEED] = {
		.ID = 597,
	},
	[SPECIES_FERROTHORN] = {
		.ID = 597,
	},
	[SPECIES_KLINK] = {
		.ID = 599,
	},
	[SPECIES_KLANG] = {
		.ID = 599,
	},
	[SPECIES_KLINKLANG] = {
		.ID = 599,
	},
	[SPECIES_TYNAMO] = {
		.ID = 602,
	},
	[SPECIES_EELEKTRIK] = {
		.ID = 602,
	},
	[SPECIES_EELEKTROSS] = {
		.ID = 602,
	},
	[SPECIES_ELGYEM] = {
		.ID = 605,
	},
	[SPECIES_BEHEEYEM] = {
		.ID = 605,
	},
	[SPECIES_LITWICK] = {
		.ID = 607,
	},
	[SPECIES_LAMPENT] = {
		.ID = 607,
	},
	[SPECIES_CHANDELURE] = {
		.ID = 607,
	},
	[SPECIES_AXEW] = {
		.ID = 610,
	},
	[SPECIES_FRAXURE] = {
		.ID = 610,
	},
	[SPECIES_HAXORUS] = {
		.ID = 610,
	},
	[SPECIES_CUBCHOO] = {
		.ID = 613,
	},
	[SPECIES_BEARTIC] = {
		.ID = 613,
	},
	[SPECIES_CRYOGONAL] = {
		.ID = 615,
	},
	[SPECIES_SHELMET] = {
		.ID = 616,
	},
	[SPECIES_ACCELGOR] = {
		.ID = 616,
	},
	[SPECIES_STUNFISK] = {
		.ID = 618,
	},
	[SPECIES_MIENFOO] = {
		.ID = 619,
	},
	[SPECIES_MIENSHAO] = {
		.ID = 619,
	},
	[SPECIES_DRUDDIGON] = {
		.ID = 621,
	},
	[SPECIES_GOLETT] = {
		.ID = 622,
	},
	[SPECIES_GOLURK] = {
		.ID = 622,
	},
	[SPECIES_PAWNIARD] = {
		.ID = 624,
	},
	[SPECIES_BISHARP] = {
		.ID = 624,
	},
	[SPECIES_BOUFFALANT] = {
		.ID = 626,
	},
	[SPECIES_RUFFLET] = {
		.ID = 627,
	},
	[SPECIES_BRAVIARY] = {
		.ID = 627,
	},
	[SPECIES_VULLABY] = {
		.ID = 629,
	},
	[SPECIES_MANDIBUZZ] = {
		.ID = 629,
	},
	[SPECIES_HEATMOR] = {
		.ID = 631,
	},
	[SPECIES_DURANT] = {
		.ID = 632,
	},
	[SPECIES_DEINO] = {
		.ID = 633,
	},
	[SPECIES_ZWEILOUS] = {
		.ID = 633,
	},
	[SPECIES_HYDREIGON] = {
		.ID = 633,
	},
	[SPECIES_LARVESTA] = {
		.ID = 636,
	},
	[SPECIES_VOLCARONA] = {
		.ID = 636,
	},
	[SPECIES_COBALION] = {
		.ID = 638,
	},
	[SPECIES_TERRAKION] = {
		.ID = 639,
	},
	[SPECIES_VIRIZION] = {
		.ID = 640,
	},
	[SPECIES_TORNADUS] = {
		.ID = 641,
	},
	[SPECIES_THUNDURUS] = {
		.ID = 642,
	},
	[SPECIES_RESHIRAM] = {
		.ID = 643,
	},
	[SPECIES_ZEKROM] = {
		.ID = 644,
	},
	[SPECIES_LANDORUS] = {
		.ID = 645,
	},
	[SPECIES_KYUREM] = {
		.ID = 646,
	},
	[SPECIES_KELDEO] = {
		.ID = 647,
	},
	[SPECIES_MELOETTA] = {
		.ID = 648,
	},
	[SPECIES_GENESECT] = {
		.ID = 649,
	},
	[SPECIES_CHESPIN] = {
		.ID = 650,
	},
	[SPECIES_QUILLADIN] = {
		.ID = 651,
	},
	[SPECIES_CHESNAUGHT] = {
		.ID = 652,
	},
	[SPECIES_FENNEKIN] = {
		.ID = 653,
	},
	[SPECIES_BRAIXEN] = {
		.ID = 654,
	},
	[SPECIES_DELPHOX] = {
		.ID = 655,
	},
	[SPECIES_FROAKIE] = {
		.ID = 656,
	},
	[SPECIES_FROGADIER] = {
		.ID = 657,
	},
	[SPECIES_GRENINJA] = {
		.ID = 658,
	},
	[SPECIES_BUNNELBY] = {
		.ID = 659,
	},
	[SPECIES_DIGGERSBY] = {
		.ID = 660,
	},
	[SPECIES_FLETCHLING] = {
		.ID = 661,
	},
	[SPECIES_FLETCHINDER] = {
		.ID = 662,
	},
	[SPECIES_TALONFLAME] = {
		.ID = 663,
	},
	[SPECIES_SCATTERBUG] = {
		.ID = 664,
	},
	[SPECIES_SPEWPA] = {
		.ID = 665,
	},
	[SPECIES_VIVILLON] = {
		.ID = 666,
	},
	[SPECIES_LITLEO] = {
		.ID = 667,
	},
	[SPECIES_PYROAR] = {
		.ID = 668,
	},
	[SPECIES_FLABéBé] = {
		.ID = 669,
	},
	[SPECIES_FLOETTE] = {
		.ID = 670,
	},
	[SPECIES_FLORGES] = {
		.ID = 671,
	},
	[SPECIES_SKIDDO] = {
		.ID = 672,
	},
	[SPECIES_GOGOAT] = {
		.ID = 673,
	},
	[SPECIES_PANCHAM] = {
		.ID = 674,
	},
	[SPECIES_PANGORO] = {
		.ID = 675,
	},
	[SPECIES_FURFROU] = {
		.ID = 676,
	},
	[SPECIES_ESPURR] = {
		.ID = 677,
	},
	[SPECIES_MEOWSTIC] = {
		.ID = 678,
	},
	[SPECIES_HONEDGE] = {
		.ID = 679,
	},
	[SPECIES_DOUBLADE] = {
		.ID = 680,
	},
	[SPECIES_AEGISLASH] = {
		.ID = 681,
	},
	[SPECIES_SPRITZEE] = {
		.ID = 682,
	},
	[SPECIES_AROMATISSE] = {
		.ID = 683,
	},
	[SPECIES_SWIRLIX] = {
		.ID = 684,
	},
};
