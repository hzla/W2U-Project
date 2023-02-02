#include "Children.h"

u32 __size = sizeof(CHILD_DATA);

const CHILD_DATA __data[] = {
	[CHILDREN_NONE] = {
		.ID = 0,
	},
	[CHILDREN_BULBASAUR] = {
		.ID = 1,
	},
	[CHILDREN_IVYSAUR] = {
		.ID = 10,
	},
	[CHILDREN_VENUSAUR] = {
		.ID = 100,
	},
	[CHILDREN_CHARMANDER] = {
		.ID = 100,
	},
	[CHILDREN_CHARMELEON] = {
		.ID = 102,
	},
	[CHILDREN_CHARIZARD] = {
		.ID = 102,
	},
	[CHILDREN_SQUIRTLE] = {
		.ID = 104,
	},
	[CHILDREN_WARTORTLE] = {
		.ID = 104,
	},
	[CHILDREN_BLASTOISE] = {
		.ID = 236,
	},
	[CHILDREN_CATERPIE] = {
		.ID = 236,
	},
	[CHILDREN_METAPOD] = {
		.ID = 108,
	},
	[CHILDREN_BUTTERFREE] = {
		.ID = 109,
	},
	[CHILDREN_WEEDLE] = {
		.ID = 10,
	},
	[CHILDREN_KAKUNA] = {
		.ID = 109,
	},
	[CHILDREN_BEEDRILL] = {
		.ID = 111,
	},
	[CHILDREN_PIDGEY] = {
		.ID = 111,
	},
	[CHILDREN_PIDGEOTTO] = {
		.ID = 440,
	},
	[CHILDREN_PIDGEOT] = {
		.ID = 114,
	},
	[CHILDREN_RATTATA] = {
		.ID = 115,
	},
	[CHILDREN_RATICATE] = {
		.ID = 116,
	},
	[CHILDREN_SPEAROW] = {
		.ID = 116,
	},
	[CHILDREN_FEAROW] = {
		.ID = 118,
	},
	[CHILDREN_EKANS] = {
		.ID = 118,
	},
	[CHILDREN_ARBOK] = {
		.ID = 10,
	},
	[CHILDREN_PIKACHU] = {
		.ID = 120,
	},
	[CHILDREN_RAICHU] = {
		.ID = 120,
	},
	[CHILDREN_SANDSHREW] = {
		.ID = 439,
	},
	[CHILDREN_SANDSLASH] = {
		.ID = 123,
	},
	[CHILDREN_NIDORAN♀] = {
		.ID = 238,
	},
	[CHILDREN_NIDORINA] = {
		.ID = 239,
	},
	[CHILDREN_NIDOQUEEN] = {
		.ID = 240,
	},
	[CHILDREN_NIDORAN♂] = {
		.ID = 127,
	},
	[CHILDREN_NIDORINO] = {
		.ID = 128,
	},
	[CHILDREN_NIDOKING] = {
		.ID = 129,
	},
	[CHILDREN_CLEFAIRY] = {
		.ID = 13,
	},
	[CHILDREN_CLEFABLE] = {
		.ID = 129,
	},
	[CHILDREN_VULPIX] = {
		.ID = 131,
	},
	[CHILDREN_NINETALES] = {
		.ID = 132,
	},
	[CHILDREN_JIGGLYPUFF] = {
		.ID = 133,
	},
	[CHILDREN_WIGGLYTUFF] = {
		.ID = 133,
	},
	[CHILDREN_ZUBAT] = {
		.ID = 133,
	},
	[CHILDREN_GOLBAT] = {
		.ID = 133,
	},
	[CHILDREN_ODDISH] = {
		.ID = 137,
	},
	[CHILDREN_GLOOM] = {
		.ID = 138,
	},
	[CHILDREN_VILEPLUME] = {
		.ID = 138,
	},
	[CHILDREN_PARAS] = {
		.ID = 13,
	},
	[CHILDREN_PARASECT] = {
		.ID = 140,
	},
	[CHILDREN_VENONAT] = {
		.ID = 140,
	},
	[CHILDREN_VENOMOTH] = {
		.ID = 142,
	},
	[CHILDREN_DIGLETT] = {
		.ID = 446,
	},
	[CHILDREN_DUGTRIO] = {
		.ID = 144,
	},
	[CHILDREN_MEOWTH] = {
		.ID = 145,
	},
	[CHILDREN_PERSIAN] = {
		.ID = 146,
	},
	[CHILDREN_PSYDUCK] = {
		.ID = 147,
	},
	[CHILDREN_GOLDUCK] = {
		.ID = 147,
	},
	[CHILDREN_MANKEY] = {
		.ID = 147,
	},
	[CHILDREN_PRIMEAPE] = {
		.ID = 13,
	},
	[CHILDREN_GROWLITHE] = {
		.ID = 150,
	},
	[CHILDREN_ARCANINE] = {
		.ID = 151,
	},
	[CHILDREN_POLIWAG] = {
		.ID = 152,
	},
	[CHILDREN_POLIWHIRL] = {
		.ID = 152,
	},
	[CHILDREN_POLIWRATH] = {
		.ID = 152,
	},
	[CHILDREN_ABRA] = {
		.ID = 155,
	},
	[CHILDREN_KADABRA] = {
		.ID = 155,
	},
	[CHILDREN_ALAKAZAM] = {
		.ID = 155,
	},
	[CHILDREN_MACHOP] = {
		.ID = 158,
	},
	[CHILDREN_MACHOKE] = {
		.ID = 158,
	},
	[CHILDREN_MACHAMP] = {
		.ID = 16,
	},
	[CHILDREN_BELLSPROUT] = {
		.ID = 158,
	},
	[CHILDREN_WEEPINBELL] = {
		.ID = 161,
	},
	[CHILDREN_VICTREEBEL] = {
		.ID = 161,
	},
	[CHILDREN_TENTACOOL] = {
		.ID = 163,
	},
	[CHILDREN_TENTACRUEL] = {
		.ID = 163,
	},
	[CHILDREN_GEODUDE] = {
		.ID = 165,
	},
	[CHILDREN_GRAVELER] = {
		.ID = 165,
	},
	[CHILDREN_GOLEM] = {
		.ID = 167,
	},
	[CHILDREN_PONYTA] = {
		.ID = 167,
	},
	[CHILDREN_RAPIDASH] = {
		.ID = 41,
	},
	[CHILDREN_SLOWPOKE] = {
		.ID = 16,
	},
	[CHILDREN_SLOWBRO] = {
		.ID = 170,
	},
	[CHILDREN_MAGNEMITE] = {
		.ID = 170,
	},
	[CHILDREN_MAGNETON] = {
		.ID = 172,
	},
	[CHILDREN_FARFETCHD] = {
		.ID = 173,
	},
	[CHILDREN_DODUO] = {
		.ID = 174,
	},
	[CHILDREN_DODRIO] = {
		.ID = 175,
	},
	[CHILDREN_SEEL] = {
		.ID = 175,
	},
	[CHILDREN_DEWGONG] = {
		.ID = 177,
	},
	[CHILDREN_GRIMER] = {
		.ID = 177,
	},
	[CHILDREN_MUK] = {
		.ID = 179,
	},
	[CHILDREN_SHELLDER] = {
		.ID = 16,
	},
	[CHILDREN_CLOYSTER] = {
		.ID = 179,
	},
	[CHILDREN_GASTLY] = {
		.ID = 179,
	},
	[CHILDREN_HAUNTER] = {
		.ID = 43,
	},
	[CHILDREN_GENGAR] = {
		.ID = 298,
	},
	[CHILDREN_ONIX] = {
		.ID = 298,
	},
	[CHILDREN_DROWZEE] = {
		.ID = 438,
	},
	[CHILDREN_HYPNO] = {
		.ID = 60,
	},
	[CHILDREN_KRABBY] = {
		.ID = 187,
	},
	[CHILDREN_KINGLER] = {
		.ID = 187,
	},
	[CHILDREN_VOLTORB] = {
		.ID = 187,
	},
	[CHILDREN_ELECTRODE] = {
		.ID = 19,
	},
	[CHILDREN_EXEGGCUTE] = {
		.ID = 190,
	},
	[CHILDREN_EXEGGUTOR] = {
		.ID = 191,
	},
	[CHILDREN_CUBONE] = {
		.ID = 191,
	},
	[CHILDREN_MAROWAK] = {
		.ID = 193,
	},
	[CHILDREN_HITMONLEE] = {
		.ID = 194,
	},
	[CHILDREN_HITMONCHAN] = {
		.ID = 194,
	},
	[CHILDREN_LICKITUNG] = {
		.ID = 133,
	},
	[CHILDREN_KOFFING] = {
		.ID = 133,
	},
	[CHILDREN_WEEZING] = {
		.ID = 198,
	},
	[CHILDREN_RHYHORN] = {
		.ID = 79,
	},
	[CHILDREN_RHYDON] = {
		.ID = 1,
	},
	[CHILDREN_CHANSEY] = {
		.ID = 19,
	},
	[CHILDREN_TANGELA] = {
		.ID = 200,
	},
	[CHILDREN_KANGASKHAN] = {
		.ID = 201,
	},
	[CHILDREN_HORSEA] = {
		.ID = 360,
	},
	[CHILDREN_SEADRA] = {
		.ID = 203,
	},
	[CHILDREN_GOLDEEN] = {
		.ID = 204,
	},
	[CHILDREN_SEAKING] = {
		.ID = 204,
	},
	[CHILDREN_STARYU] = {
		.ID = 206,
	},
	[CHILDREN_STARMIE] = {
		.ID = 207,
	},
	[CHILDREN_MR_MIME] = {
		.ID = 95,
	},
	[CHILDREN_SCYTHER] = {
		.ID = 209,
	},
	[CHILDREN_JYNX] = {
		.ID = 21,
	},
	[CHILDREN_ELECTABUZZ] = {
		.ID = 209,
	},
	[CHILDREN_MAGMAR] = {
		.ID = 211,
	},
	[CHILDREN_PINSIR] = {
		.ID = 123,
	},
	[CHILDREN_TAUROS] = {
		.ID = 213,
	},
	[CHILDREN_MAGIKARP] = {
		.ID = 214,
	},
	[CHILDREN_GYARADOS] = {
		.ID = 215,
	},
	[CHILDREN_LAPRAS] = {
		.ID = 216,
	},
	[CHILDREN_DITTO] = {
		.ID = 216,
	},
	[CHILDREN_EEVEE] = {
		.ID = 218,
	},
	[CHILDREN_VAPOREON] = {
		.ID = 218,
	},
	[CHILDREN_JOLTEON] = {
		.ID = 21,
	},
	[CHILDREN_FLAREON] = {
		.ID = 220,
	},
	[CHILDREN_PORYGON] = {
		.ID = 220,
	},
	[CHILDREN_OMANYTE] = {
		.ID = 222,
	},
	[CHILDREN_OMASTAR] = {
		.ID = 223,
	},
	[CHILDREN_KABUTO] = {
		.ID = 223,
	},
	[CHILDREN_KABUTOPS] = {
		.ID = 225,
	},
	[CHILDREN_AERODACTYL] = {
		.ID = 458,
	},
	[CHILDREN_SNORLAX] = {
		.ID = 227,
	},
	[CHILDREN_ARTICUNO] = {
		.ID = 228,
	},
	[CHILDREN_ZAPDOS] = {
		.ID = 228,
	},
	[CHILDREN_MOLTRES] = {
		.ID = 23,
	},
	[CHILDREN_DRATINI] = {
		.ID = 116,
	},
	[CHILDREN_DRAGONAIR] = {
		.ID = 231,
	},
	[CHILDREN_DRAGONITE] = {
		.ID = 231,
	},
	[CHILDREN_MEWTWO] = {
		.ID = 137,
	},
	[CHILDREN_MEW] = {
		.ID = 234,
	},
	[CHILDREN_CHIKORITA] = {
		.ID = 235,
	},
	[CHILDREN_BAYLEEF] = {
		.ID = 236,
	},
	[CHILDREN_MEGANIUM] = {
		.ID = 236,
	},
	[CHILDREN_CYNDAQUIL] = {
		.ID = 238,
	},
	[CHILDREN_QUILAVA] = {
		.ID = 239,
	},
	[CHILDREN_TYPHLOSION] = {
		.ID = 23,
	},
	[CHILDREN_TOTODILE] = {
		.ID = 240,
	},
	[CHILDREN_CROCONAW] = {
		.ID = 241,
	},
	[CHILDREN_FERALIGATR] = {
		.ID = 440,
	},
	[CHILDREN_SENTRET] = {
		.ID = 243,
	},
	[CHILDREN_FURRET] = {
		.ID = 244,
	},
	[CHILDREN_HOOTHOOT] = {
		.ID = 245,
	},
	[CHILDREN_NOCTOWL] = {
		.ID = 246,
	},
	[CHILDREN_LEDYBA] = {
		.ID = 246,
	},
	[CHILDREN_LEDIAN] = {
		.ID = 246,
	},
	[CHILDREN_SPINARAK] = {
		.ID = 249,
	},
	[CHILDREN_ARIADOS] = {
		.ID = 172,
	},
	[CHILDREN_CROBAT] = {
		.ID = 250,
	},
	[CHILDREN_CHINCHOU] = {
		.ID = 251,
	},
	[CHILDREN_LANTURN] = {
		.ID = 252,
	},
	[CHILDREN_PICHU] = {
		.ID = 252,
	},
	[CHILDREN_CLEFFA] = {
		.ID = 252,
	},
	[CHILDREN_IGGLYBUFF] = {
		.ID = 255,
	},
	[CHILDREN_TOGEPI] = {
		.ID = 255,
	},
	[CHILDREN_TOGETIC] = {
		.ID = 255,
	},
	[CHILDREN_NATU] = {
		.ID = 258,
	},
	[CHILDREN_XATU] = {
		.ID = 258,
	},
	[CHILDREN_MAREEP] = {
		.ID = 172,
	},
	[CHILDREN_FLAAFFY] = {
		.ID = 258,
	},
	[CHILDREN_AMPHAROS] = {
		.ID = 261,
	},
	[CHILDREN_BELLOSSOM] = {
		.ID = 261,
	},
	[CHILDREN_MARILL] = {
		.ID = 263,
	},
	[CHILDREN_AZUMARILL] = {
		.ID = 263,
	},
	[CHILDREN_SUDOWOODO] = {
		.ID = 265,
	},
	[CHILDREN_POLITOED] = {
		.ID = 265,
	},
	[CHILDREN_HOPPIP] = {
		.ID = 265,
	},
	[CHILDREN_SKIPLOOM] = {
		.ID = 265,
	},
	[CHILDREN_JUMPLUFF] = {
		.ID = 265,
	},
	[CHILDREN_AIPOM] = {
		.ID = 27,
	},
	[CHILDREN_SUNKERN] = {
		.ID = 270,
	},
	[CHILDREN_SUNFLORA] = {
		.ID = 270,
	},
	[CHILDREN_YANMA] = {
		.ID = 270,
	},
	[CHILDREN_WOOPER] = {
		.ID = 273,
	},
	[CHILDREN_QUAGSIRE] = {
		.ID = 273,
	},
	[CHILDREN_ESPEON] = {
		.ID = 273,
	},
	[CHILDREN_UMBREON] = {
		.ID = 276,
	},
	[CHILDREN_MURKROW] = {
		.ID = 276,
	},
	[CHILDREN_SLOWKING] = {
		.ID = 278,
	},
	[CHILDREN_MISDREAVUS] = {
		.ID = 278,
	},
	[CHILDREN_UNOWN] = {
		.ID = 27,
	},
	[CHILDREN_WOBBUFFET] = {
		.ID = 280,
	},
	[CHILDREN_GIRAFARIG] = {
		.ID = 280,
	},
	[CHILDREN_PINECO] = {
		.ID = 280,
	},
	[CHILDREN_FORRETRESS] = {
		.ID = 283,
	},
	[CHILDREN_DUNSPARCE] = {
		.ID = 283,
	},
	[CHILDREN_GLIGAR] = {
		.ID = 285,
	},
	[CHILDREN_STEELIX] = {
		.ID = 285,
	},
	[CHILDREN_SNUBBULL] = {
		.ID = 287,
	},
	[CHILDREN_GRANBULL] = {
		.ID = 287,
	},
	[CHILDREN_QWILFISH] = {
		.ID = 287,
	},
	[CHILDREN_SCIZOR] = {
		.ID = 29,
	},
	[CHILDREN_SHUCKLE] = {
		.ID = 290,
	},
	[CHILDREN_HERACROSS] = {
		.ID = 290,
	},
	[CHILDREN_SNEASEL] = {
		.ID = 290,
	},
	[CHILDREN_TEDDIURSA] = {
		.ID = 293,
	},
	[CHILDREN_URSARING] = {
		.ID = 293,
	},
	[CHILDREN_SLUGMA] = {
		.ID = 293,
	},
	[CHILDREN_MAGCARGO] = {
		.ID = 296,
	},
	[CHILDREN_SWINUB] = {
		.ID = 296,
	},
	[CHILDREN_PILOSWINE] = {
		.ID = 298,
	},
	[CHILDREN_CORSOLA] = {
		.ID = 299,
	},
	[CHILDREN_REMORAID] = {
		.ID = 1,
	},
	[CHILDREN_OCTILLERY] = {
		.ID = 29,
	},
	[CHILDREN_DELIBIRD] = {
		.ID = 300,
	},
	[CHILDREN_MANTINE] = {
		.ID = 300,
	},
	[CHILDREN_SKARMORY] = {
		.ID = 302,
	},
	[CHILDREN_HOUNDOUR] = {
		.ID = 303,
	},
	[CHILDREN_HOUNDOOM] = {
		.ID = 304,
	},
	[CHILDREN_KINGDRA] = {
		.ID = 304,
	},
	[CHILDREN_PHANPY] = {
		.ID = 304,
	},
	[CHILDREN_DONPHAN] = {
		.ID = 307,
	},
	[CHILDREN_PORYGON2] = {
		.ID = 307,
	},
	[CHILDREN_STANTLER] = {
		.ID = 309,
	},
	[CHILDREN_SMEARGLE] = {
		.ID = 29,
	},
	[CHILDREN_TYROGUE] = {
		.ID = 309,
	},
	[CHILDREN_HITMONTOP] = {
		.ID = 311,
	},
	[CHILDREN_SMOOCHUM] = {
		.ID = 312,
	},
	[CHILDREN_ELEKID] = {
		.ID = 313,
	},
	[CHILDREN_MAGBY] = {
		.ID = 314,
	},
	[CHILDREN_MILTANK] = {
		.ID = 406,
	},
	[CHILDREN_BLISSEY] = {
		.ID = 316,
	},
	[CHILDREN_RAIKOU] = {
		.ID = 316,
	},
	[CHILDREN_ENTEI] = {
		.ID = 318,
	},
	[CHILDREN_SUICUNE] = {
		.ID = 318,
	},
	[CHILDREN_LARVITAR] = {
		.ID = 32,
	},
	[CHILDREN_PUPITAR] = {
		.ID = 320,
	},
	[CHILDREN_TYRANITAR] = {
		.ID = 320,
	},
	[CHILDREN_LUGIA] = {
		.ID = 322,
	},
	[CHILDREN_HOOH] = {
		.ID = 322,
	},
	[CHILDREN_CELEBI] = {
		.ID = 324,
	},
	[CHILDREN_TREECKO] = {
		.ID = 325,
	},
	[CHILDREN_GROVYLE] = {
		.ID = 325,
	},
	[CHILDREN_SCEPTILE] = {
		.ID = 327,
	},
	[CHILDREN_TORCHIC] = {
		.ID = 328,
	},
	[CHILDREN_COMBUSKEN] = {
		.ID = 328,
	},
	[CHILDREN_BLAZIKEN] = {
		.ID = 32,
	},
	[CHILDREN_MUDKIP] = {
		.ID = 328,
	},
	[CHILDREN_MARSHTOMP] = {
		.ID = 331,
	},
	[CHILDREN_SWAMPERT] = {
		.ID = 331,
	},
	[CHILDREN_POOCHYENA] = {
		.ID = 333,
	},
	[CHILDREN_MIGHTYENA] = {
		.ID = 333,
	},
	[CHILDREN_ZIGZAGOON] = {
		.ID = 335,
	},
	[CHILDREN_LINOONE] = {
		.ID = 336,
	},
	[CHILDREN_WURMPLE] = {
		.ID = 337,
	},
	[CHILDREN_SILCOON] = {
		.ID = 338,
	},
	[CHILDREN_BEAUTIFLY] = {
		.ID = 339,
	},
	[CHILDREN_CASCOON] = {
		.ID = 32,
	},
	[CHILDREN_DUSTOX] = {
		.ID = 339,
	},
	[CHILDREN_LOTAD] = {
		.ID = 341,
	},
	[CHILDREN_LOMBRE] = {
		.ID = 341,
	},
	[CHILDREN_LUDICOLO] = {
		.ID = 343,
	},
	[CHILDREN_SEEDOT] = {
		.ID = 343,
	},
	[CHILDREN_NUZLEAF] = {
		.ID = 345,
	},
	[CHILDREN_SHIFTRY] = {
		.ID = 345,
	},
	[CHILDREN_TAILLOW] = {
		.ID = 347,
	},
	[CHILDREN_SWELLOW] = {
		.ID = 347,
	},
	[CHILDREN_WINGULL] = {
		.ID = 349,
	},
	[CHILDREN_PELIPPER] = {
		.ID = 173,
	},
	[CHILDREN_RALTS] = {
		.ID = 349,
	},
	[CHILDREN_KIRLIA] = {
		.ID = 351,
	},
	[CHILDREN_GARDEVOIR] = {
		.ID = 352,
	},
	[CHILDREN_SURSKIT] = {
		.ID = 353,
	},
	[CHILDREN_MASQUERAIN] = {
		.ID = 353,
	},
	[CHILDREN_SHROOMISH] = {
		.ID = 355,
	},
	[CHILDREN_BRELOOM] = {
		.ID = 355,
	},
	[CHILDREN_SLAKOTH] = {
		.ID = 357,
	},
	[CHILDREN_VIGOROTH] = {
		.ID = 433,
	},
	[CHILDREN_SLAKING] = {
		.ID = 359,
	},
	[CHILDREN_NINCADA] = {
		.ID = 173,
	},
	[CHILDREN_NINJASK] = {
		.ID = 360,
	},
	[CHILDREN_SHEDINJA] = {
		.ID = 361,
	},
	[CHILDREN_WHISMUR] = {
		.ID = 361,
	},
	[CHILDREN_LOUDRED] = {
		.ID = 363,
	},
	[CHILDREN_EXPLOUD] = {
		.ID = 363,
	},
	[CHILDREN_MAKUHITA] = {
		.ID = 363,
	},
	[CHILDREN_HARIYAMA] = {
		.ID = 366,
	},
	[CHILDREN_AZURILL] = {
		.ID = 366,
	},
	[CHILDREN_NOSEPASS] = {
		.ID = 366,
	},
	[CHILDREN_SKITTY] = {
		.ID = 369,
	},
	[CHILDREN_DELCATTY] = {
		.ID = 37,
	},
	[CHILDREN_SABLEYE] = {
		.ID = 370,
	},
	[CHILDREN_MAWILE] = {
		.ID = 371,
	},
	[CHILDREN_ARON] = {
		.ID = 371,
	},
	[CHILDREN_LAIRON] = {
		.ID = 371,
	},
	[CHILDREN_AGGRON] = {
		.ID = 374,
	},
	[CHILDREN_MEDITITE] = {
		.ID = 374,
	},
	[CHILDREN_MEDICHAM] = {
		.ID = 374,
	},
	[CHILDREN_ELECTRIKE] = {
		.ID = 377,
	},
	[CHILDREN_MANECTRIC] = {
		.ID = 378,
	},
	[CHILDREN_PLUSLE] = {
		.ID = 379,
	},
	[CHILDREN_MINUN] = {
		.ID = 37,
	},
	[CHILDREN_VOLBEAT] = {
		.ID = 380,
	},
	[CHILDREN_ILLUMISE] = {
		.ID = 381,
	},
	[CHILDREN_ROSELIA] = {
		.ID = 382,
	},
	[CHILDREN_GULPIN] = {
		.ID = 383,
	},
	[CHILDREN_SWALOT] = {
		.ID = 384,
	},
	[CHILDREN_CARVANHA] = {
		.ID = 385,
	},
	[CHILDREN_SHARPEDO] = {
		.ID = 386,
	},
	[CHILDREN_WAILMER] = {
		.ID = 387,
	},
	[CHILDREN_WAILORD] = {
		.ID = 387,
	},
	[CHILDREN_NUMEL] = {
		.ID = 387,
	},
	[CHILDREN_CAMERUPT] = {
		.ID = 174,
	},
	[CHILDREN_TORKOAL] = {
		.ID = 390,
	},
	[CHILDREN_SPOINK] = {
		.ID = 390,
	},
	[CHILDREN_GRUMPIG] = {
		.ID = 390,
	},
	[CHILDREN_SPINDA] = {
		.ID = 393,
	},
	[CHILDREN_TRAPINCH] = {
		.ID = 393,
	},
	[CHILDREN_VIBRAVA] = {
		.ID = 393,
	},
	[CHILDREN_FLYGON] = {
		.ID = 396,
	},
	[CHILDREN_CACNEA] = {
		.ID = 396,
	},
	[CHILDREN_CACTURNE] = {
		.ID = 396,
	},
	[CHILDREN_SWABLU] = {
		.ID = 399,
	},
	[CHILDREN_ALTARIA] = {
		.ID = 4,
	},
	[CHILDREN_ZANGOOSE] = {
		.ID = 174,
	},
	[CHILDREN_SEVIPER] = {
		.ID = 399,
	},
	[CHILDREN_LUNATONE] = {
		.ID = 401,
	},
	[CHILDREN_SOLROCK] = {
		.ID = 401,
	},
	[CHILDREN_BARBOACH] = {
		.ID = 403,
	},
	[CHILDREN_WHISCASH] = {
		.ID = 403,
	},
	[CHILDREN_CORPHISH] = {
		.ID = 403,
	},
	[CHILDREN_CRAWDAUNT] = {
		.ID = 406,
	},
	[CHILDREN_BALTOY] = {
		.ID = 406,
	},
	[CHILDREN_CLAYDOL] = {
		.ID = 408,
	},
	[CHILDREN_LILEEP] = {
		.ID = 408,
	},
	[CHILDREN_CRADILY] = {
		.ID = 41,
	},
	[CHILDREN_ANORITH] = {
		.ID = 410,
	},
	[CHILDREN_ARMALDO] = {
		.ID = 410,
	},
	[CHILDREN_FEEBAS] = {
		.ID = 412,
	},
	[CHILDREN_MILOTIC] = {
		.ID = 412,
	},
	[CHILDREN_CASTFORM] = {
		.ID = 412,
	},
	[CHILDREN_KECLEON] = {
		.ID = 415,
	},
	[CHILDREN_SHUPPET] = {
		.ID = 415,
	},
	[CHILDREN_BANETTE] = {
		.ID = 417,
	},
	[CHILDREN_DUSKULL] = {
		.ID = 418,
	},
	[CHILDREN_DUSCLOPS] = {
		.ID = 418,
	},
	[CHILDREN_TROPIUS] = {
		.ID = 41,
	},
	[CHILDREN_CHIMECHO] = {
		.ID = 420,
	},
	[CHILDREN_ABSOL] = {
		.ID = 420,
	},
	[CHILDREN_WYNAUT] = {
		.ID = 422,
	},
	[CHILDREN_SNORUNT] = {
		.ID = 422,
	},
	[CHILDREN_GLALIE] = {
		.ID = 190,
	},
	[CHILDREN_SPHEAL] = {
		.ID = 425,
	},
	[CHILDREN_SEALEO] = {
		.ID = 425,
	},
	[CHILDREN_WALREIN] = {
		.ID = 427,
	},
	[CHILDREN_CLAMPERL] = {
		.ID = 427,
	},
	[CHILDREN_HUNTAIL] = {
		.ID = 200,
	},
	[CHILDREN_GOREBYSS] = {
		.ID = 43,
	},
	[CHILDREN_RELICANTH] = {
		.ID = 198,
	},
	[CHILDREN_LUVDISC] = {
		.ID = 431,
	},
	[CHILDREN_BAGON] = {
		.ID = 431,
	},
	[CHILDREN_SHELGON] = {
		.ID = 433,
	},
	[CHILDREN_SALAMENCE] = {
		.ID = 434,
	},
	[CHILDREN_BELDUM] = {
		.ID = 434,
	},
	[CHILDREN_METANG] = {
		.ID = 436,
	},
	[CHILDREN_METAGROSS] = {
		.ID = 436,
	},
	[CHILDREN_REGIROCK] = {
		.ID = 438,
	},
	[CHILDREN_REGICE] = {
		.ID = 439,
	},
	[CHILDREN_REGISTEEL] = {
		.ID = 43,
	},
	[CHILDREN_LATIAS] = {
		.ID = 440,
	},
	[CHILDREN_LATIOS] = {
		.ID = 441,
	},
	[CHILDREN_KYOGRE] = {
		.ID = 442,
	},
	[CHILDREN_GROUDON] = {
		.ID = 443,
	},
	[CHILDREN_RAYQUAZA] = {
		.ID = 443,
	},
	[CHILDREN_JIRACHI] = {
		.ID = 443,
	},
	[CHILDREN_DEOXYS] = {
		.ID = 446,
	},
	[CHILDREN_TURTWIG] = {
		.ID = 447,
	},
	[CHILDREN_GROTLE] = {
		.ID = 447,
	},
	[CHILDREN_TORTERRA] = {
		.ID = 449,
	},
	[CHILDREN_CHIMCHAR] = {
		.ID = 43,
	},
	[CHILDREN_MONFERNO] = {
		.ID = 449,
	},
	[CHILDREN_INFERNAPE] = {
		.ID = 451,
	},
	[CHILDREN_PIPLUP] = {
		.ID = 451,
	},
	[CHILDREN_PRINPLUP] = {
		.ID = 453,
	},
	[CHILDREN_EMPOLEON] = {
		.ID = 453,
	},
	[CHILDREN_STARLY] = {
		.ID = 455,
	},
	[CHILDREN_STARAVIA] = {
		.ID = 456,
	},
	[CHILDREN_STARAPTOR] = {
		.ID = 456,
	},
	[CHILDREN_BIDOOF] = {
		.ID = 458,
	},
	[CHILDREN_BIBAREL] = {
		.ID = 459,
	},
	[CHILDREN_KRICKETOT] = {
		.ID = 46,
	},
	[CHILDREN_KRICKETUNE] = {
		.ID = 459,
	},
	[CHILDREN_SHINX] = {
		.ID = 215,
	},
	[CHILDREN_LUXIO] = {
		.ID = 81,
	},
	[CHILDREN_LUXRAY] = {
		.ID = 108,
	},
	[CHILDREN_BUDEW] = {
		.ID = 111,
	},
	[CHILDREN_ROSERADE] = {
		.ID = 114,
	},
	[CHILDREN_CRANIDOS] = {
		.ID = 239,
	},
	[CHILDREN_RAMPARDOS] = {
		.ID = 240,
	},
	[CHILDREN_SHIELDON] = {
		.ID = 175,
	},
	[CHILDREN_BASTIODON] = {
		.ID = 193,
	},
	[CHILDREN_BURMY] = {
		.ID = 46,
	},
	[CHILDREN_WORMADAM] = {
		.ID = 133,
	},
	[CHILDREN_MOTHIM] = {
		.ID = 133,
	},
	[CHILDREN_COMBEE] = {
		.ID = 207,
	},
	[CHILDREN_VESPIQUEN] = {
		.ID = 220,
	},
	[CHILDREN_PACHIRISU] = {
		.ID = 137,
	},
	[CHILDREN_BUIZEL] = {
		.ID = 280,
	},
	[CHILDREN_FLOATZEL] = {
		.ID = 299,
	},
	[CHILDREN_CHERUBI] = {
		.ID = 355,
	},
	[CHILDREN_CHERRIM] = {
		.ID = 361,
	},
	[CHILDREN_SHELLOS] = {
		.ID = 479,
	},
	[CHILDREN_GASTRODON] = {
		.ID = 48,
	},
	[CHILDREN_AMBIPOM] = {
		.ID = 480,
	},
	[CHILDREN_DRIFLOON] = {
		.ID = 481,
	},
	[CHILDREN_DRIFBLIM] = {
		.ID = 482,
	},
	[CHILDREN_BUNEARY] = {
		.ID = 483,
	},
	[CHILDREN_LOPUNNY] = {
		.ID = 484,
	},
	[CHILDREN_MISMAGIUS] = {
		.ID = 485,
	},
	[CHILDREN_HONCHKROW] = {
		.ID = 486,
	},
	[CHILDREN_GLAMEOW] = {
		.ID = 487,
	},
	[CHILDREN_PURUGLY] = {
		.ID = 488,
	},
	[CHILDREN_CHINGLING] = {
		.ID = 489,
	},
	[CHILDREN_STUNKY] = {
		.ID = 48,
	},
	[CHILDREN_SKUNTANK] = {
		.ID = 490,
	},
	[CHILDREN_BRONZOR] = {
		.ID = 491,
	},
	[CHILDREN_BRONZONG] = {
		.ID = 492,
	},
	[CHILDREN_BONSLY] = {
		.ID = 493,
	},
	[CHILDREN_MIME_JR] = {
		.ID = 494,
	},
	[CHILDREN_HAPPINY] = {
		.ID = 495,
	},
	[CHILDREN_CHATOT] = {
		.ID = 495,
	},
	[CHILDREN_SPIRITOMB] = {
		.ID = 495,
	},
	[CHILDREN_GIBLE] = {
		.ID = 498,
	},
	[CHILDREN_GABITE] = {
		.ID = 498,
	},
	[CHILDREN_GARCHOMP] = {
		.ID = 4,
	},
	[CHILDREN_MUNCHLAX] = {
		.ID = 50,
	},
	[CHILDREN_RIOLU] = {
		.ID = 498,
	},
	[CHILDREN_LUCARIO] = {
		.ID = 501,
	},
	[CHILDREN_HIPPOPOTAS] = {
		.ID = 501,
	},
	[CHILDREN_HIPPOWDON] = {
		.ID = 501,
	},
	[CHILDREN_SKORUPI] = {
		.ID = 504,
	},
	[CHILDREN_DRAPION] = {
		.ID = 504,
	},
	[CHILDREN_CROAGUNK] = {
		.ID = 506,
	},
	[CHILDREN_TOXICROAK] = {
		.ID = 506,
	},
	[CHILDREN_CARNIVINE] = {
		.ID = 506,
	},
	[CHILDREN_FINNEON] = {
		.ID = 509,
	},
	[CHILDREN_LUMINEON] = {
		.ID = 50,
	},
	[CHILDREN_MANTYKE] = {
		.ID = 509,
	},
	[CHILDREN_SNOVER] = {
		.ID = 511,
	},
	[CHILDREN_ABOMASNOW] = {
		.ID = 511,
	},
	[CHILDREN_WEAVILE] = {
		.ID = 513,
	},
	[CHILDREN_MAGNEZONE] = {
		.ID = 513,
	},
	[CHILDREN_LICKILICKY] = {
		.ID = 515,
	},
	[CHILDREN_RHYPERIOR] = {
		.ID = 515,
	},
	[CHILDREN_TANGROWTH] = {
		.ID = 517,
	},
	[CHILDREN_ELECTIVIRE] = {
		.ID = 517,
	},
	[CHILDREN_MAGMORTAR] = {
		.ID = 519,
	},
	[CHILDREN_TOGEKISS] = {
		.ID = 52,
	},
	[CHILDREN_YANMEGA] = {
		.ID = 519,
	},
	[CHILDREN_LEAFEON] = {
		.ID = 519,
	},
	[CHILDREN_GLACEON] = {
		.ID = 522,
	},
	[CHILDREN_GLISCOR] = {
		.ID = 522,
	},
	[CHILDREN_MAMOSWINE] = {
		.ID = 524,
	},
	[CHILDREN_PORYGONZ] = {
		.ID = 524,
	},
	[CHILDREN_GALLADE] = {
		.ID = 524,
	},
	[CHILDREN_PROBOPASS] = {
		.ID = 527,
	},
	[CHILDREN_DUSKNOIR] = {
		.ID = 527,
	},
	[CHILDREN_FROSLASS] = {
		.ID = 529,
	},
	[CHILDREN_ROTOM] = {
		.ID = 52,
	},
	[CHILDREN_UXIE] = {
		.ID = 529,
	},
	[CHILDREN_MESPRIT] = {
		.ID = 531,
	},
	[CHILDREN_AZELF] = {
		.ID = 532,
	},
	[CHILDREN_DIALGA] = {
		.ID = 532,
	},
	[CHILDREN_PALKIA] = {
		.ID = 532,
	},
	[CHILDREN_HEATRAN] = {
		.ID = 535,
	},
	[CHILDREN_REGIGIGAS] = {
		.ID = 535,
	},
	[CHILDREN_GIRATINA] = {
		.ID = 535,
	},
	[CHILDREN_CRESSELIA] = {
		.ID = 538,
	},
	[CHILDREN_PHIONE] = {
		.ID = 539,
	},
	[CHILDREN_MANAPHY] = {
		.ID = 54,
	},
	[CHILDREN_DARKRAI] = {
		.ID = 540,
	},
	[CHILDREN_SHAYMIN] = {
		.ID = 540,
	},
	[CHILDREN_ARCEUS] = {
		.ID = 540,
	},
	[CHILDREN_VICTINI] = {
		.ID = 543,
	},
	[CHILDREN_SNIVY] = {
		.ID = 543,
	},
	[CHILDREN_SERVINE] = {
		.ID = 543,
	},
	[CHILDREN_SERPERIOR] = {
		.ID = 546,
	},
	[CHILDREN_TEPIG] = {
		.ID = 546,
	},
	[CHILDREN_PIGNITE] = {
		.ID = 548,
	},
	[CHILDREN_EMBOAR] = {
		.ID = 548,
	},
	[CHILDREN_OSHAWOTT] = {
		.ID = 54,
	},
	[CHILDREN_DEWOTT] = {
		.ID = 550,
	},
	[CHILDREN_SAMUROTT] = {
		.ID = 551,
	},
	[CHILDREN_PATRAT] = {
		.ID = 551,
	},
	[CHILDREN_WATCHOG] = {
		.ID = 551,
	},
	[CHILDREN_LILLIPUP] = {
		.ID = 554,
	},
	[CHILDREN_HERDIER] = {
		.ID = 554,
	},
	[CHILDREN_STOUTLAND] = {
		.ID = 556,
	},
	[CHILDREN_PURRLOIN] = {
		.ID = 557,
	},
	[CHILDREN_LIEPARD] = {
		.ID = 557,
	},
	[CHILDREN_PANSAGE] = {
		.ID = 559,
	},
	[CHILDREN_SIMISAGE] = {
		.ID = 56,
	},
	[CHILDREN_PANSEAR] = {
		.ID = 559,
	},
	[CHILDREN_SIMISEAR] = {
		.ID = 561,
	},
	[CHILDREN_PANPOUR] = {
		.ID = 562,
	},
	[CHILDREN_SIMIPOUR] = {
		.ID = 562,
	},
	[CHILDREN_MUNNA] = {
		.ID = 564,
	},
	[CHILDREN_MUSHARNA] = {
		.ID = 564,
	},
	[CHILDREN_PIDOVE] = {
		.ID = 566,
	},
	[CHILDREN_TRANQUILL] = {
		.ID = 566,
	},
	[CHILDREN_UNFEZANT] = {
		.ID = 568,
	},
	[CHILDREN_BLITZLE] = {
		.ID = 568,
	},
	[CHILDREN_ZEBSTRIKA] = {
		.ID = 56,
	},
	[CHILDREN_ROGGENROLA] = {
		.ID = 570,
	},
	[CHILDREN_BOLDORE] = {
		.ID = 570,
	},
	[CHILDREN_GIGALITH] = {
		.ID = 572,
	},
	[CHILDREN_WOOBAT] = {
		.ID = 572,
	},
	[CHILDREN_SWOOBAT] = {
		.ID = 574,
	},
	[CHILDREN_DRILBUR] = {
		.ID = 574,
	},
	[CHILDREN_EXCADRILL] = {
		.ID = 574,
	},
	[CHILDREN_AUDINO] = {
		.ID = 577,
	},
	[CHILDREN_TIMBURR] = {
		.ID = 577,
	},
	[CHILDREN_GURDURR] = {
		.ID = 577,
	},
	[CHILDREN_CONKELDURR] = {
		.ID = 58,
	},
	[CHILDREN_TYMPOLE] = {
		.ID = 580,
	},
	[CHILDREN_PALPITOAD] = {
		.ID = 580,
	},
	[CHILDREN_SEISMITOAD] = {
		.ID = 582,
	},
	[CHILDREN_THROH] = {
		.ID = 582,
	},
	[CHILDREN_SAWK] = {
		.ID = 582,
	},
	[CHILDREN_SEWADDLE] = {
		.ID = 585,
	},
	[CHILDREN_SWADLOON] = {
		.ID = 585,
	},
	[CHILDREN_LEAVANNY] = {
		.ID = 587,
	},
	[CHILDREN_VENIPEDE] = {
		.ID = 588,
	},
	[CHILDREN_WHIRLIPEDE] = {
		.ID = 588,
	},
	[CHILDREN_SCOLIPEDE] = {
		.ID = 58,
	},
	[CHILDREN_COTTONEE] = {
		.ID = 590,
	},
	[CHILDREN_WHIMSICOTT] = {
		.ID = 590,
	},
	[CHILDREN_PETILIL] = {
		.ID = 592,
	},
	[CHILDREN_LILLIGANT] = {
		.ID = 592,
	},
	[CHILDREN_BASCULIN] = {
		.ID = 594,
	},
	[CHILDREN_SANDILE] = {
		.ID = 595,
	},
	[CHILDREN_KROKOROK] = {
		.ID = 595,
	},
	[CHILDREN_KROOKODILE] = {
		.ID = 597,
	},
	[CHILDREN_DARUMAKA] = {
		.ID = 597,
	},
	[CHILDREN_DARMANITAN] = {
		.ID = 599,
	},
	[CHILDREN_MARACTUS] = {
		.ID = 4,
	},
	[CHILDREN_DWEBBLE] = {
		.ID = 60,
	},
	[CHILDREN_CRUSTLE] = {
		.ID = 599,
	},
	[CHILDREN_SCRAGGY] = {
		.ID = 599,
	},
	[CHILDREN_SCRAFTY] = {
		.ID = 602,
	},
	[CHILDREN_SIGILYPH] = {
		.ID = 602,
	},
	[CHILDREN_YAMASK] = {
		.ID = 602,
	},
	[CHILDREN_COFAGRIGUS] = {
		.ID = 605,
	},
	[CHILDREN_TIRTOUGA] = {
		.ID = 605,
	},
	[CHILDREN_CARRACOSTA] = {
		.ID = 607,
	},
	[CHILDREN_ARCHEN] = {
		.ID = 607,
	},
	[CHILDREN_ARCHEOPS] = {
		.ID = 607,
	},
	[CHILDREN_TRUBBISH] = {
		.ID = 60,
	},
	[CHILDREN_GARBODOR] = {
		.ID = 610,
	},
	[CHILDREN_ZORUA] = {
		.ID = 610,
	},
	[CHILDREN_ZOROARK] = {
		.ID = 610,
	},
	[CHILDREN_MINCCINO] = {
		.ID = 613,
	},
	[CHILDREN_CINCCINO] = {
		.ID = 613,
	},
	[CHILDREN_GOTHITA] = {
		.ID = 615,
	},
	[CHILDREN_GOTHORITA] = {
		.ID = 616,
	},
	[CHILDREN_GOTHITELLE] = {
		.ID = 616,
	},
	[CHILDREN_SOLOSIS] = {
		.ID = 618,
	},
	[CHILDREN_DUOSION] = {
		.ID = 619,
	},
	[CHILDREN_REUNICLUS] = {
		.ID = 60,
	},
	[CHILDREN_DUCKLETT] = {
		.ID = 619,
	},
	[CHILDREN_SWANNA] = {
		.ID = 621,
	},
	[CHILDREN_VANILLITE] = {
		.ID = 622,
	},
	[CHILDREN_VANILLISH] = {
		.ID = 622,
	},
	[CHILDREN_VANILLUXE] = {
		.ID = 624,
	},
	[CHILDREN_DEERLING] = {
		.ID = 624,
	},
	[CHILDREN_SAWSBUCK] = {
		.ID = 626,
	},
	[CHILDREN_EMOLGA] = {
		.ID = 627,
	},
	[CHILDREN_KARRABLAST] = {
		.ID = 627,
	},
	[CHILDREN_ESCAVALIER] = {
		.ID = 629,
	},
	[CHILDREN_FOONGUS] = {
		.ID = 63,
	},
	[CHILDREN_AMOONGUSS] = {
		.ID = 629,
	},
	[CHILDREN_FRILLISH] = {
		.ID = 631,
	},
	[CHILDREN_JELLICENT] = {
		.ID = 632,
	},
	[CHILDREN_ALOMOMOLA] = {
		.ID = 633,
	},
	[CHILDREN_JOLTIK] = {
		.ID = 633,
	},
	[CHILDREN_GALVANTULA] = {
		.ID = 633,
	},
	[CHILDREN_FERROSEED] = {
		.ID = 636,
	},
	[CHILDREN_FERROTHORN] = {
		.ID = 636,
	},
	[CHILDREN_KLINK] = {
		.ID = 638,
	},
	[CHILDREN_KLANG] = {
		.ID = 639,
	},
	[CHILDREN_KLINKLANG] = {
		.ID = 63,
	},
	[CHILDREN_TYNAMO] = {
		.ID = 640,
	},
	[CHILDREN_EELEKTRIK] = {
		.ID = 641,
	},
	[CHILDREN_EELEKTROSS] = {
		.ID = 642,
	},
	[CHILDREN_ELGYEM] = {
		.ID = 643,
	},
	[CHILDREN_BEHEEYEM] = {
		.ID = 644,
	},
	[CHILDREN_LITWICK] = {
		.ID = 645,
	},
	[CHILDREN_LAMPENT] = {
		.ID = 646,
	},
	[CHILDREN_CHANDELURE] = {
		.ID = 647,
	},
	[CHILDREN_AXEW] = {
		.ID = 648,
	},
	[CHILDREN_FRAXURE] = {
		.ID = 649,
	},
	[CHILDREN_HAXORUS] = {
		.ID = 63,
	},
	[CHILDREN_CUBCHOO] = {
		.ID = 650,
	},
	[CHILDREN_BEARTIC] = {
		.ID = 651,
	},
	[CHILDREN_CRYOGONAL] = {
		.ID = 652,
	},
	[CHILDREN_SHELMET] = {
		.ID = 653,
	},
	[CHILDREN_ACCELGOR] = {
		.ID = 654,
	},
	[CHILDREN_STUNFISK] = {
		.ID = 655,
	},
	[CHILDREN_MIENFOO] = {
		.ID = 656,
	},
	[CHILDREN_MIENSHAO] = {
		.ID = 657,
	},
	[CHILDREN_DRUDDIGON] = {
		.ID = 658,
	},
	[CHILDREN_GOLETT] = {
		.ID = 659,
	},
	[CHILDREN_GOLURK] = {
		.ID = 66,
	},
	[CHILDREN_PAWNIARD] = {
		.ID = 660,
	},
	[CHILDREN_BISHARP] = {
		.ID = 661,
	},
	[CHILDREN_BOUFFALANT] = {
		.ID = 662,
	},
	[CHILDREN_RUFFLET] = {
		.ID = 663,
	},
	[CHILDREN_BRAVIARY] = {
		.ID = 664,
	},
	[CHILDREN_VULLABY] = {
		.ID = 665,
	},
	[CHILDREN_MANDIBUZZ] = {
		.ID = 666,
	},
	[CHILDREN_HEATMOR] = {
		.ID = 667,
	},
	[CHILDREN_DURANT] = {
		.ID = 668,
	},
	[CHILDREN_DEINO] = {
		.ID = 669,
	},
	[CHILDREN_ZWEILOUS] = {
		.ID = 66,
	},
	[CHILDREN_HYDREIGON] = {
		.ID = 670,
	},
	[CHILDREN_LARVESTA] = {
		.ID = 671,
	},
	[CHILDREN_VOLCARONA] = {
		.ID = 672,
	},
	[CHILDREN_COBALION] = {
		.ID = 673,
	},
	[CHILDREN_TERRAKION] = {
		.ID = 674,
	},
	[CHILDREN_VIRIZION] = {
		.ID = 675,
	},
	[CHILDREN_TORNADUS] = {
		.ID = 676,
	},
	[CHILDREN_THUNDURUS] = {
		.ID = 677,
	},
	[CHILDREN_RESHIRAM] = {
		.ID = 678,
	},
	[CHILDREN_ZEKROM] = {
		.ID = 679,
	},
	[CHILDREN_LANDORUS] = {
		.ID = 66,
	},
	[CHILDREN_KYUREM] = {
		.ID = 680,
	},
	[CHILDREN_KELDEO] = {
		.ID = 681,
	},
	[CHILDREN_MELOETTA] = {
		.ID = 682,
	},
	[CHILDREN_GENESECT] = {
		.ID = 683,
	},
	[CHILDREN_CHESPIN] = {
		.ID = 684,
	},
	[CHILDREN_QUILLADIN] = {
		.ID = 69,
	},
	[CHILDREN_CHESNAUGHT] = {
		.ID = 7,
	},
	[CHILDREN_FENNEKIN] = {
		.ID = 69,
	},
	[CHILDREN_BRAIXEN] = {
		.ID = 69,
	},
	[CHILDREN_DELPHOX] = {
		.ID = 72,
	},
	[CHILDREN_FROAKIE] = {
		.ID = 72,
	},
	[CHILDREN_FROGADIER] = {
		.ID = 74,
	},
	[CHILDREN_GRENINJA] = {
		.ID = 74,
	},
	[CHILDREN_BUNNELBY] = {
		.ID = 74,
	},
	[CHILDREN_DIGGERSBY] = {
		.ID = 77,
	},
	[CHILDREN_FLETCHLING] = {
		.ID = 77,
	},
	[CHILDREN_FLETCHINDER] = {
		.ID = 79,
	},
	[CHILDREN_TALONFLAME] = {
		.ID = 7,
	},
	[CHILDREN_SCATTERBUG] = {
		.ID = 79,
	},
	[CHILDREN_SPEWPA] = {
		.ID = 81,
	},
	[CHILDREN_VIVILLON] = {
		.ID = 81,
	},
	[CHILDREN_LITLEO] = {
		.ID = 83,
	},
	[CHILDREN_PYROAR] = {
		.ID = 84,
	},
	[CHILDREN_FLABEBE] = {
		.ID = 84,
	},
	[CHILDREN_FLOETTE] = {
		.ID = 86,
	},
	[CHILDREN_FLORGES] = {
		.ID = 86,
	},
	[CHILDREN_SKIDDO] = {
		.ID = 88,
	},
	[CHILDREN_GOGOAT] = {
		.ID = 88,
	},
	[CHILDREN_PANCHAM] = {
		.ID = 7,
	},
	[CHILDREN_PANGORO] = {
		.ID = 90,
	},
	[CHILDREN_FURFROU] = {
		.ID = 90,
	},
	[CHILDREN_ESPURR] = {
		.ID = 92,
	},
	[CHILDREN_MEOWSTIC] = {
		.ID = 92,
	},
	[CHILDREN_HONEDGE] = {
		.ID = 92,
	},
	[CHILDREN_DOUBLADE] = {
		.ID = 95,
	},
	[CHILDREN_AEGISLASH] = {
		.ID = 96,
	},
	[CHILDREN_SPRITZEE] = {
		.ID = 96,
	},
	[CHILDREN_AROMATISSE] = {
		.ID = 98,
	},
	[CHILDREN_SWIRLIX] = {
		.ID = 98,
	},
};
