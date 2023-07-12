#include "Species.h"
#include "Evolutions.h"

u32 __size = sizeof(EVOLUTION_DATA);

const EVOLUTION_DATA __data[] = {
	[SPECIES_NONE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_BULBASAUR] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 16,
				.TargetSpecies = SPECIES_IVYSAUR,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_IVYSAUR] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 7,
				.TargetSpecies = SPECIES_METAPOD,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_VENUSAUR] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 30,
				.TargetSpecies = SPECIES_ELECTRODE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CHARMANDER] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CHARMELEON] = {
		 .Entries = {
			{
				.Method = 8,
				.Parameter = 85,
				.TargetSpecies = SPECIES_EXEGGUTOR,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CHARIZARD] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SQUIRTLE] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 28,
				.TargetSpecies = SPECIES_MAROWAK,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_WARTORTLE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_BLASTOISE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CATERPIE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_METAPOD] = {
		 .Entries = {
			{
				.Method = 21,
				.Parameter = 205,
				.TargetSpecies = SPECIES_LICKILICKY,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_BUTTERFREE] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 35,
				.TargetSpecies = SPECIES_WEEZING,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_WEEDLE] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 10,
				.TargetSpecies = SPECIES_BUTTERFREE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_KAKUNA] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_BEEDRILL] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 42,
				.TargetSpecies = SPECIES_RHYDON,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PIDGEY] = {
		 .Entries = {
			{
				.Method = 6,
				.Parameter = 321,
				.TargetSpecies = SPECIES_RHYPERIOR,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PIDGEOTTO] = {
		 .Entries = {
			{
				.Method = 1,
				.Parameter = 0,
				.TargetSpecies = SPECIES_BLISSEY,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PIDGEOT] = {
		 .Entries = {
			{
				.Method = 21,
				.Parameter = 246,
				.TargetSpecies = SPECIES_TANGROWTH,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_RATTATA] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_RATICATE] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 32,
				.TargetSpecies = SPECIES_SEADRA,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SPEAROW] = {
		 .Entries = {
			{
				.Method = 6,
				.Parameter = 235,
				.TargetSpecies = SPECIES_KINGDRA,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_FEAROW] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 33,
				.TargetSpecies = SPECIES_SEAKING,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_EKANS] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ARBOK] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PIKACHU] = {
		 .Entries = {
			{
				.Method = 8,
				.Parameter = 84,
				.TargetSpecies = SPECIES_STARMIE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_RAICHU] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SANDSHREW] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SANDSLASH] = {
		 .Entries = {
			{
				.Method = 6,
				.Parameter = 233,
				.TargetSpecies = SPECIES_SCIZOR,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_NIDORAN_M] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_NIDORINA] = {
		 .Entries = {
			{
				.Method = 6,
				.Parameter = 322,
				.TargetSpecies = SPECIES_ELECTIVIRE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_NIDOQUEEN] = {
		 .Entries = {
			{
				.Method = 6,
				.Parameter = 323,
				.TargetSpecies = SPECIES_MAGMORTAR,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_NIDORAN_F] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_NIDORINO] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_NIDOKING] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 20,
				.TargetSpecies = SPECIES_GYARADOS,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CLEFAIRY] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 7,
				.TargetSpecies = SPECIES_KAKUNA,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CLEFABLE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_VULPIX] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_NINETALES] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_JIGGLYPUFF] = {
		 .Entries = {
			{
				.Method = 26,
				.Parameter = 0,
				.TargetSpecies = SPECIES_LEAFEON,
			},
			{
				.Method = 27,
				.Parameter = 0,
				.TargetSpecies = SPECIES_GLACEON,
			},
			{
				.Method = 8,
				.Parameter = 83,
				.TargetSpecies = SPECIES_JOLTEON,
			},
			{
				.Method = 8,
				.Parameter = 84,
				.TargetSpecies = SPECIES_VAPOREON,
			},
			{
				.Method = 8,
				.Parameter = 82,
				.TargetSpecies = SPECIES_FLAREON,
			},
			{
				.Method = 2,
				.Parameter = 0,
				.TargetSpecies = SPECIES_ESPEON,
			},
			{
				.Method = 3,
				.Parameter = 0,
				.TargetSpecies = SPECIES_UMBREON,
			},
		 },
	},
	[SPECIES_WIGGLYTUFF] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ZUBAT] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GOLBAT] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ODDISH] = {
		 .Entries = {
			{
				.Method = 6,
				.Parameter = 252,
				.TargetSpecies = SPECIES_PORYGON2,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GLOOM] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 40,
				.TargetSpecies = SPECIES_OMASTAR,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_VILEPLUME] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PARAS] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 10,
				.TargetSpecies = SPECIES_BEEDRILL,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PARASECT] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 40,
				.TargetSpecies = SPECIES_KABUTOPS,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_VENONAT] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_VENOMOTH] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_DIGLETT] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_DUGTRIO] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MEOWTH] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PERSIAN] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PSYDUCK] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 30,
				.TargetSpecies = SPECIES_DRAGONAIR,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GOLDUCK] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 55,
				.TargetSpecies = SPECIES_DRAGONITE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MANKEY] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PRIMEAPE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GROWLITHE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ARCANINE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_POLIWAG] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 16,
				.TargetSpecies = SPECIES_BAYLEEF,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_POLIWHIRL] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 32,
				.TargetSpecies = SPECIES_MEGANIUM,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_POLIWRATH] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ABRA] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 14,
				.TargetSpecies = SPECIES_QUILAVA,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_KADABRA] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 36,
				.TargetSpecies = SPECIES_TYPHLOSION,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ALAKAZAM] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MACHOP] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 18,
				.TargetSpecies = SPECIES_CROCONAW,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MACHOKE] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 30,
				.TargetSpecies = SPECIES_FERALIGATR,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MACHAMP] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 18,
				.TargetSpecies = SPECIES_PIDGEOTTO,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_BELLSPROUT] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_WEEPINBELL] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 15,
				.TargetSpecies = SPECIES_FURRET,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_VICTREEBEL] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_TENTACOOL] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 20,
				.TargetSpecies = SPECIES_NOCTOWL,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_TENTACRUEL] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GEODUDE] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 18,
				.TargetSpecies = SPECIES_LEDIAN,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GRAVELER] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GOLEM] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 22,
				.TargetSpecies = SPECIES_ARIADOS,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PONYTA] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_RAPIDASH] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SLOWPOKE] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 36,
				.TargetSpecies = SPECIES_PIDGEOT,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SLOWBRO] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 27,
				.TargetSpecies = SPECIES_LANTURN,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MAGNEMITE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MAGNETON] = {
		 .Entries = {
			{
				.Method = 1,
				.Parameter = 0,
				.TargetSpecies = SPECIES_PIKACHU,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_FARFETCHD] = {
		 .Entries = {
			{
				.Method = 1,
				.Parameter = 0,
				.TargetSpecies = SPECIES_CLEFAIRY,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_DODUO] = {
		 .Entries = {
			{
				.Method = 1,
				.Parameter = 0,
				.TargetSpecies = SPECIES_JIGGLYPUFF,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_DODRIO] = {
		 .Entries = {
			{
				.Method = 1,
				.Parameter = 0,
				.TargetSpecies = SPECIES_TOGETIC,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SEEL] = {
		 .Entries = {
			{
				.Method = 8,
				.Parameter = 107,
				.TargetSpecies = SPECIES_TOGEKISS,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_DEWGONG] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 25,
				.TargetSpecies = SPECIES_XATU,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GRIMER] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MUK] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 15,
				.TargetSpecies = SPECIES_FLAAFFY,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SHELLDER] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CLOYSTER] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 30,
				.TargetSpecies = SPECIES_AMPHAROS,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GASTLY] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_HAUNTER] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GENGAR] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 18,
				.TargetSpecies = SPECIES_AZUMARILL,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ONIX] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_DROWZEE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_HYPNO] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_KRABBY] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 18,
				.TargetSpecies = SPECIES_SKIPLOOM,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_KINGLER] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 27,
				.TargetSpecies = SPECIES_JUMPLUFF,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_VOLTORB] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ELECTRODE] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 20,
				.TargetSpecies = SPECIES_RATICATE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_EXEGGCUTE] = {
		 .Entries = {
			{
				.Method = 21,
				.Parameter = 458,
				.TargetSpecies = SPECIES_AMBIPOM,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_EXEGGUTOR] = {
		 .Entries = {
			{
				.Method = 8,
				.Parameter = 80,
				.TargetSpecies = SPECIES_SUNFLORA,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CUBONE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MAROWAK] = {
		 .Entries = {
			{
				.Method = 21,
				.Parameter = 246,
				.TargetSpecies = SPECIES_YANMEGA,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_HITMONLEE] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 20,
				.TargetSpecies = SPECIES_QUAGSIRE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_HITMONCHAN] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_LICKITUNG] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_KOFFING] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_WEEZING] = {
		 .Entries = {
			{
				.Method = 8,
				.Parameter = 108,
				.TargetSpecies = SPECIES_HONCHKROW,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_RHYHORN] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_RHYDON] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 32,
				.TargetSpecies = SPECIES_VENUSAUR,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CHANSEY] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_TANGELA] = {
		 .Entries = {
			{
				.Method = 8,
				.Parameter = 108,
				.TargetSpecies = SPECIES_MISMAGIUS,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_KANGASKHAN] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_HORSEA] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SEADRA] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GOLDEEN] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 31,
				.TargetSpecies = SPECIES_FORRETRESS,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SEAKING] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_STARYU] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_STARMIE] = {
		 .Entries = {
			{
				.Method = 20,
				.Parameter = 327,
				.TargetSpecies = SPECIES_GLISCOR,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MR_MIME] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SCYTHER] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 23,
				.TargetSpecies = SPECIES_GRANBULL,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_JYNX] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 20,
				.TargetSpecies = SPECIES_FEAROW,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ELECTABUZZ] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MAGMAR] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PINSIR] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_TAUROS] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MAGIKARP] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GYARADOS] = {
		 .Entries = {
			{
				.Method = 20,
				.Parameter = 326,
				.TargetSpecies = SPECIES_WEAVILE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_LAPRAS] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 30,
				.TargetSpecies = SPECIES_URSARING,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_DITTO] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_EEVEE] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 38,
				.TargetSpecies = SPECIES_MAGCARGO,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_VAPOREON] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_JOLTEON] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_FLAREON] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 33,
				.TargetSpecies = SPECIES_PILOSWINE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PORYGON] = {
		 .Entries = {
			{
				.Method = 21,
				.Parameter = 246,
				.TargetSpecies = SPECIES_MAMOSWINE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_OMANYTE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_OMASTAR] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 25,
				.TargetSpecies = SPECIES_OCTILLERY,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_KABUTO] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_KABUTOPS] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_AERODACTYL] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SNORLAX] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ARTICUNO] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 24,
				.TargetSpecies = SPECIES_HOUNDOOM,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ZAPDOS] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MOLTRES] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 22,
				.TargetSpecies = SPECIES_ARBOK,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_DRATINI] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_DRAGONAIR] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 25,
				.TargetSpecies = SPECIES_DONPHAN,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_DRAGONITE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MEWTWO] = {
		 .Entries = {
			{
				.Method = 6,
				.Parameter = 324,
				.TargetSpecies = SPECIES_PORYGONZ,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MEW] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CHIKORITA] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_BAYLEEF] = {
		 .Entries = {
			{
				.Method = 11,
				.Parameter = 20,
				.TargetSpecies = SPECIES_HITMONCHAN,
			},
			{
				.Method = 9,
				.Parameter = 20,
				.TargetSpecies = SPECIES_HITMONLEE,
			},
			{
				.Method = 10,
				.Parameter = 20,
				.TargetSpecies = SPECIES_HITMONTOP,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MEGANIUM] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CYNDAQUIL] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 30,
				.TargetSpecies = SPECIES_JYNX,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_QUILAVA] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 30,
				.TargetSpecies = SPECIES_ELECTABUZZ,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_TYPHLOSION] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_TOTODILE] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 30,
				.TargetSpecies = SPECIES_MAGMAR,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CROCONAW] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_FERALIGATR] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SENTRET] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_FURRET] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_HOOTHOOT] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_NOCTOWL] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 30,
				.TargetSpecies = SPECIES_PUPITAR,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_LEDYBA] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 55,
				.TargetSpecies = SPECIES_TYRANITAR,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_LEDIAN] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SPINARAK] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ARIADOS] = {
		 .Entries = {
			{
				.Method = 8,
				.Parameter = 83,
				.TargetSpecies = SPECIES_RAICHU,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CROBAT] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CHINCHOU] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_LANTURN] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 16,
				.TargetSpecies = SPECIES_GROVYLE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PICHU] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 36,
				.TargetSpecies = SPECIES_SCEPTILE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CLEFFA] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_IGGLYBUFF] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 16,
				.TargetSpecies = SPECIES_COMBUSKEN,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_TOGEPI] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 36,
				.TargetSpecies = SPECIES_BLAZIKEN,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_TOGETIC] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_NATU] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 16,
				.TargetSpecies = SPECIES_MARSHTOMP,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_XATU] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 36,
				.TargetSpecies = SPECIES_SWAMPERT,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MAREEP] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_FLAAFFY] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_AMPHAROS] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 18,
				.TargetSpecies = SPECIES_MIGHTYENA,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_BELLOSSOM] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MARILL] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 20,
				.TargetSpecies = SPECIES_LINOONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_AZUMARILL] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SUDOWOODO] = {
		 .Entries = {
			{
				.Method = 12,
				.Parameter = 7,
				.TargetSpecies = SPECIES_SILCOON,
			},
			{
				.Method = 13,
				.Parameter = 7,
				.TargetSpecies = SPECIES_CASCOON,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_POLITOED] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 10,
				.TargetSpecies = SPECIES_BEAUTIFLY,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_HOPPIP] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SKIPLOOM] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 10,
				.TargetSpecies = SPECIES_DUSTOX,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_JUMPLUFF] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_AIPOM] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 22,
				.TargetSpecies = SPECIES_SANDSLASH,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SUNKERN] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 14,
				.TargetSpecies = SPECIES_LOMBRE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SUNFLORA] = {
		 .Entries = {
			{
				.Method = 8,
				.Parameter = 84,
				.TargetSpecies = SPECIES_LUDICOLO,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_YANMA] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_WOOPER] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 14,
				.TargetSpecies = SPECIES_NUZLEAF,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_QUAGSIRE] = {
		 .Entries = {
			{
				.Method = 8,
				.Parameter = 85,
				.TargetSpecies = SPECIES_SHIFTRY,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ESPEON] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_UMBREON] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 22,
				.TargetSpecies = SPECIES_SWELLOW,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MURKROW] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SLOWKING] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 25,
				.TargetSpecies = SPECIES_PELIPPER,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MISDREAVUS] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_UNOWN] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_WOBBUFFET] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 20,
				.TargetSpecies = SPECIES_KIRLIA,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GIRAFARIG] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 30,
				.TargetSpecies = SPECIES_GARDEVOIR,
			},
			{
				.Method = 17,
				.Parameter = 109,
				.TargetSpecies = SPECIES_GALLADE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PINECO] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_FORRETRESS] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 22,
				.TargetSpecies = SPECIES_MASQUERAIN,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_DUNSPARCE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GLIGAR] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 23,
				.TargetSpecies = SPECIES_BRELOOM,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_STEELIX] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SNUBBULL] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 18,
				.TargetSpecies = SPECIES_VIGOROTH,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GRANBULL] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 36,
				.TargetSpecies = SPECIES_SLAKING,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_QWILFISH] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SCIZOR] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 16,
				.TargetSpecies = SPECIES_NIDORINA,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SHUCKLE] = {
		 .Entries = {
			{
				.Method = 14,
				.Parameter = 20,
				.TargetSpecies = SPECIES_NINJASK,
			},
			{
				.Method = 15,
				.Parameter = 20,
				.TargetSpecies = SPECIES_SHEDINJA,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_HERACROSS] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SNEASEL] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_TEDDIURSA] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 20,
				.TargetSpecies = SPECIES_LOUDRED,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_URSARING] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 40,
				.TargetSpecies = SPECIES_EXPLOUD,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SLUGMA] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MAGCARGO] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 24,
				.TargetSpecies = SPECIES_HARIYAMA,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SWINUB] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PILOSWINE] = {
		 .Entries = {
			{
				.Method = 1,
				.Parameter = 0,
				.TargetSpecies = SPECIES_MARILL,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CORSOLA] = {
		 .Entries = {
			{
				.Method = 25,
				.Parameter = 0,
				.TargetSpecies = SPECIES_PROBOPASS,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_REMORAID] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_OCTILLERY] = {
		 .Entries = {
			{
				.Method = 8,
				.Parameter = 81,
				.TargetSpecies = SPECIES_NIDOQUEEN,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_DELIBIRD] = {
		 .Entries = {
			{
				.Method = 8,
				.Parameter = 81,
				.TargetSpecies = SPECIES_DELCATTY,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MANTINE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SKARMORY] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_HOUNDOUR] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_HOUNDOOM] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 32,
				.TargetSpecies = SPECIES_LAIRON,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_KINGDRA] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 42,
				.TargetSpecies = SPECIES_AGGRON,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PHANPY] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_DONPHAN] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 37,
				.TargetSpecies = SPECIES_MEDICHAM,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PORYGON2] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_STANTLER] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 26,
				.TargetSpecies = SPECIES_MANECTRIC,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SMEARGLE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_TYROGUE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_HITMONTOP] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SMOOCHUM] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ELEKID] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MAGBY] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MILTANK] = {
		 .Entries = {
			{
				.Method = 8,
				.Parameter = 107,
				.TargetSpecies = SPECIES_ROSERADE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_BLISSEY] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 26,
				.TargetSpecies = SPECIES_SWALOT,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_RAIKOU] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ENTEI] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 30,
				.TargetSpecies = SPECIES_SHARPEDO,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SUICUNE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_LARVITAR] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 16,
				.TargetSpecies = SPECIES_NIDORINO,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PUPITAR] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 40,
				.TargetSpecies = SPECIES_WAILORD,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_TYRANITAR] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_LUGIA] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 33,
				.TargetSpecies = SPECIES_CAMERUPT,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_HOOH] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CELEBI] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_TREECKO] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 32,
				.TargetSpecies = SPECIES_GRUMPIG,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GROVYLE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SCEPTILE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_TORCHIC] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 35,
				.TargetSpecies = SPECIES_VIBRAVA,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_COMBUSKEN] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 45,
				.TargetSpecies = SPECIES_FLYGON,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_BLAZIKEN] = {
		 .Entries = {
			{
				.Method = 8,
				.Parameter = 81,
				.TargetSpecies = SPECIES_NIDOKING,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MUDKIP] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MARSHTOMP] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 32,
				.TargetSpecies = SPECIES_CACTURNE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SWAMPERT] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_POOCHYENA] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 35,
				.TargetSpecies = SPECIES_ALTARIA,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MIGHTYENA] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ZIGZAGOON] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_LINOONE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_WURMPLE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SILCOON] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_BEAUTIFLY] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 30,
				.TargetSpecies = SPECIES_WHISCASH,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CASCOON] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_DUSTOX] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_LOTAD] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 30,
				.TargetSpecies = SPECIES_CRAWDAUNT,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_LOMBRE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_LUDICOLO] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 36,
				.TargetSpecies = SPECIES_CLAYDOL,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SEEDOT] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_NUZLEAF] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 40,
				.TargetSpecies = SPECIES_CRADILY,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SHIFTRY] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_TAILLOW] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 40,
				.TargetSpecies = SPECIES_ARMALDO,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SWELLOW] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_WINGULL] = {
		 .Entries = {
			{
				.Method = 16,
				.Parameter = 170,
				.TargetSpecies = SPECIES_MILOTIC,
			},
			{
				.Method = 6,
				.Parameter = 537,
				.TargetSpecies = SPECIES_MILOTIC,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PELIPPER] = {
		 .Entries = {
			{
				.Method = 8,
				.Parameter = 81,
				.TargetSpecies = SPECIES_CLEFABLE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_RALTS] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_KIRLIA] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GARDEVOIR] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SURSKIT] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 37,
				.TargetSpecies = SPECIES_BANETTE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MASQUERAIN] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SHROOMISH] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 37,
				.TargetSpecies = SPECIES_DUSCLOPS,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_BRELOOM] = {
		 .Entries = {
			{
				.Method = 6,
				.Parameter = 325,
				.TargetSpecies = SPECIES_DUSKNOIR,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SLAKOTH] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_VIGOROTH] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SLAKING] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_NINCADA] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_NINJASK] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 15,
				.TargetSpecies = SPECIES_WOBBUFFET,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SHEDINJA] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 42,
				.TargetSpecies = SPECIES_GLALIE,
			},
			{
				.Method = 18,
				.Parameter = 109,
				.TargetSpecies = SPECIES_FROSLASS,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_WHISMUR] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_LOUDRED] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 32,
				.TargetSpecies = SPECIES_SEALEO,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_EXPLOUD] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 44,
				.TargetSpecies = SPECIES_WALREIN,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MAKUHITA] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_HARIYAMA] = {
		 .Entries = {
			{
				.Method = 6,
				.Parameter = 226,
				.TargetSpecies = SPECIES_HUNTAIL,
			},
			{
				.Method = 6,
				.Parameter = 227,
				.TargetSpecies = SPECIES_GOREBYSS,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_AZURILL] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_NOSEPASS] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SKITTY] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_DELCATTY] = {
		 .Entries = {
			{
				.Method = 8,
				.Parameter = 82,
				.TargetSpecies = SPECIES_NINETALES,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SABLEYE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MAWILE] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 30,
				.TargetSpecies = SPECIES_SHELGON,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ARON] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 50,
				.TargetSpecies = SPECIES_SALAMENCE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_LAIRON] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_AGGRON] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 20,
				.TargetSpecies = SPECIES_METANG,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MEDITITE] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 45,
				.TargetSpecies = SPECIES_METAGROSS,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MEDICHAM] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ELECTRIKE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MANECTRIC] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PLUSLE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MINUN] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_VOLBEAT] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ILLUMISE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ROSELIA] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GULPIN] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SWALOT] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CARVANHA] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SHARPEDO] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_WAILMER] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 18,
				.TargetSpecies = SPECIES_GROTLE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_WAILORD] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 32,
				.TargetSpecies = SPECIES_TORTERRA,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_NUMEL] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CAMERUPT] = {
		 .Entries = {
			{
				.Method = 8,
				.Parameter = 81,
				.TargetSpecies = SPECIES_WIGGLYTUFF,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_TORKOAL] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 14,
				.TargetSpecies = SPECIES_MONFERNO,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SPOINK] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 36,
				.TargetSpecies = SPECIES_INFERNAPE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GRUMPIG] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SPINDA] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 16,
				.TargetSpecies = SPECIES_PRINPLUP,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_TRAPINCH] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 36,
				.TargetSpecies = SPECIES_EMPOLEON,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_VIBRAVA] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_FLYGON] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 14,
				.TargetSpecies = SPECIES_STARAVIA,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CACNEA] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 34,
				.TargetSpecies = SPECIES_STARAPTOR,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CACTURNE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SWABLU] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 15,
				.TargetSpecies = SPECIES_BIBAREL,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ALTARIA] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 16,
				.TargetSpecies = SPECIES_CHARMELEON,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ZANGOOSE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SEVIPER] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_LUNATONE] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 10,
				.TargetSpecies = SPECIES_KRICKETUNE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SOLROCK] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_BARBOACH] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 15,
				.TargetSpecies = SPECIES_LUXIO,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_WHISCASH] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 30,
				.TargetSpecies = SPECIES_LUXRAY,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CORPHISH] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CRAWDAUNT] = {
		 .Entries = {
			{
				.Method = 2,
				.Parameter = 0,
				.TargetSpecies = SPECIES_ROSELIA,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_BALTOY] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CLAYDOL] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 30,
				.TargetSpecies = SPECIES_RAMPARDOS,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_LILEEP] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CRADILY] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 22,
				.TargetSpecies = SPECIES_GOLBAT,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ANORITH] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 30,
				.TargetSpecies = SPECIES_BASTIODON,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ARMALDO] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_FEEBAS] = {
		 .Entries = {
			{
				.Method = 24,
				.Parameter = 20,
				.TargetSpecies = SPECIES_WORMADAM,
			},
			{
				.Method = 23,
				.Parameter = 20,
				.TargetSpecies = SPECIES_MOTHIM,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MILOTIC] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CASTFORM] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_KECLEON] = {
		 .Entries = {
			{
				.Method = 24,
				.Parameter = 21,
				.TargetSpecies = SPECIES_VESPIQUEN,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SHUPPET] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_BANETTE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_DUSKULL] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 26,
				.TargetSpecies = SPECIES_FLOATZEL,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_DUSCLOPS] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_TROPIUS] = {
		 .Entries = {
			{
				.Method = 1,
				.Parameter = 0,
				.TargetSpecies = SPECIES_CROBAT,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CHIMECHO] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 25,
				.TargetSpecies = SPECIES_CHERRIM,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ABSOL] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_WYNAUT] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 30,
				.TargetSpecies = SPECIES_GASTRODON,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SNORUNT] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GLALIE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SPHEAL] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 28,
				.TargetSpecies = SPECIES_DRIFBLIM,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SEALEO] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_WALREIN] = {
		 .Entries = {
			{
				.Method = 1,
				.Parameter = 0,
				.TargetSpecies = SPECIES_LOPUNNY,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CLAMPERL] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_HUNTAIL] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GOREBYSS] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 21,
				.TargetSpecies = SPECIES_GLOOM,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_RELICANTH] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_LUVDISC] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 38,
				.TargetSpecies = SPECIES_PURUGLY,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_BAGON] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SHELGON] = {
		 .Entries = {
			{
				.Method = 3,
				.Parameter = 0,
				.TargetSpecies = SPECIES_CHIMECHO,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SALAMENCE] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 34,
				.TargetSpecies = SPECIES_SKUNTANK,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_BELDUM] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_METANG] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 33,
				.TargetSpecies = SPECIES_BRONZONG,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_METAGROSS] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_REGIROCK] = {
		 .Entries = {
			{
				.Method = 21,
				.Parameter = 102,
				.TargetSpecies = SPECIES_SUDOWOODO,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_REGICE] = {
		 .Entries = {
			{
				.Method = 21,
				.Parameter = 102,
				.TargetSpecies = SPECIES_MR_MIME,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_REGISTEEL] = {
		 .Entries = {
			{
				.Method = 8,
				.Parameter = 85,
				.TargetSpecies = SPECIES_VILEPLUME,
			},
			{
				.Method = 8,
				.Parameter = 80,
				.TargetSpecies = SPECIES_BELLOSSOM,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_LATIAS] = {
		 .Entries = {
			{
				.Method = 19,
				.Parameter = 110,
				.TargetSpecies = SPECIES_CHANSEY,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_LATIOS] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_KYOGRE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GROUDON] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 24,
				.TargetSpecies = SPECIES_GABITE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_RAYQUAZA] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 48,
				.TargetSpecies = SPECIES_GARCHOMP,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_JIRACHI] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_DEOXYS] = {
		 .Entries = {
			{
				.Method = 1,
				.Parameter = 0,
				.TargetSpecies = SPECIES_SNORLAX,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_TURTWIG] = {
		 .Entries = {
			{
				.Method = 2,
				.Parameter = 0,
				.TargetSpecies = SPECIES_LUCARIO,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GROTLE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_TORTERRA] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 34,
				.TargetSpecies = SPECIES_HIPPOWDON,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CHIMCHAR] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MONFERNO] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_INFERNAPE] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 40,
				.TargetSpecies = SPECIES_DRAPION,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PIPLUP] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PRINPLUP] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 37,
				.TargetSpecies = SPECIES_TOXICROAK,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_EMPOLEON] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_STARLY] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_STARAVIA] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 31,
				.TargetSpecies = SPECIES_LUMINEON,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_STARAPTOR] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_BIDOOF] = {
		 .Entries = {
			{
				.Method = 22,
				.Parameter = 223,
				.TargetSpecies = SPECIES_MANTINE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_BIBAREL] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 40,
				.TargetSpecies = SPECIES_ABOMASNOW,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_KRICKETOT] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 24,
				.TargetSpecies = SPECIES_PARASECT,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_KRICKETUNE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SHINX] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_LUXIO] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_LUXRAY] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_BUDEW] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ROSERADE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CRANIDOS] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_RAMPARDOS] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SHIELDON] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_BASTIODON] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_BURMY] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_WORMADAM] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MOTHIM] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_COMBEE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_VESPIQUEN] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PACHIRISU] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_BUIZEL] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_FLOATZEL] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CHERUBI] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CHERRIM] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SHELLOS] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GASTRODON] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 31,
				.TargetSpecies = SPECIES_VENOMOTH,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_AMBIPOM] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_DRIFLOON] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_DRIFBLIM] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_BUNEARY] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_LOPUNNY] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MISMAGIUS] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_HONCHKROW] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GLAMEOW] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PURUGLY] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CHINGLING] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_STUNKY] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SKUNTANK] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_BRONZOR] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_BRONZONG] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_BONSLY] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MIME_JR] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_HAPPINY] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 17,
				.TargetSpecies = SPECIES_SERVINE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CHATOT] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 36,
				.TargetSpecies = SPECIES_SERPERIOR,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SPIRITOMB] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GIBLE] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 17,
				.TargetSpecies = SPECIES_PIGNITE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GABITE] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 36,
				.TargetSpecies = SPECIES_EMBOAR,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GARCHOMP] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 36,
				.TargetSpecies = SPECIES_CHARIZARD,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MUNCHLAX] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 26,
				.TargetSpecies = SPECIES_DUGTRIO,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_RIOLU] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_LUCARIO] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 17,
				.TargetSpecies = SPECIES_DEWOTT,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_HIPPOPOTAS] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 36,
				.TargetSpecies = SPECIES_SAMUROTT,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_HIPPOWDON] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SKORUPI] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 20,
				.TargetSpecies = SPECIES_WATCHOG,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_DRAPION] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CROAGUNK] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 16,
				.TargetSpecies = SPECIES_HERDIER,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_TOXICROAK] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 32,
				.TargetSpecies = SPECIES_STOUTLAND,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CARNIVINE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_FINNEON] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 20,
				.TargetSpecies = SPECIES_LIEPARD,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_LUMINEON] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MANTYKE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SNOVER] = {
		 .Entries = {
			{
				.Method = 8,
				.Parameter = 85,
				.TargetSpecies = SPECIES_SIMISAGE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ABOMASNOW] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_WEAVILE] = {
		 .Entries = {
			{
				.Method = 8,
				.Parameter = 82,
				.TargetSpecies = SPECIES_SIMISEAR,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MAGNEZONE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_LICKILICKY] = {
		 .Entries = {
			{
				.Method = 8,
				.Parameter = 84,
				.TargetSpecies = SPECIES_SIMIPOUR,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_RHYPERIOR] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_TANGROWTH] = {
		 .Entries = {
			{
				.Method = 8,
				.Parameter = 81,
				.TargetSpecies = SPECIES_MUSHARNA,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ELECTIVIRE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MAGMORTAR] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 21,
				.TargetSpecies = SPECIES_TRANQUILL,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_TOGEKISS] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 28,
				.TargetSpecies = SPECIES_PERSIAN,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_YANMEGA] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 32,
				.TargetSpecies = SPECIES_UNFEZANT,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_LEAFEON] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GLACEON] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 27,
				.TargetSpecies = SPECIES_ZEBSTRIKA,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GLISCOR] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MAMOSWINE] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 25,
				.TargetSpecies = SPECIES_BOLDORE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PORYGONZ] = {
		 .Entries = {
			{
				.Method = 5,
				.Parameter = 0,
				.TargetSpecies = SPECIES_GIGALITH,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GALLADE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PROBOPASS] = {
		 .Entries = {
			{
				.Method = 1,
				.Parameter = 0,
				.TargetSpecies = SPECIES_SWOOBAT,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_DUSKNOIR] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_FROSLASS] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 31,
				.TargetSpecies = SPECIES_EXCADRILL,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ROTOM] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_UXIE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MESPRIT] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_AZELF] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 25,
				.TargetSpecies = SPECIES_GURDURR,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_DIALGA] = {
		 .Entries = {
			{
				.Method = 5,
				.Parameter = 0,
				.TargetSpecies = SPECIES_CONKELDURR,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PALKIA] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_HEATRAN] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 25,
				.TargetSpecies = SPECIES_PALPITOAD,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_REGIGIGAS] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 36,
				.TargetSpecies = SPECIES_SEISMITOAD,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GIRATINA] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CRESSELIA] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PHIONE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MANAPHY] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 33,
				.TargetSpecies = SPECIES_GOLDUCK,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_DARKRAI] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 20,
				.TargetSpecies = SPECIES_SWADLOON,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SHAYMIN] = {
		 .Entries = {
			{
				.Method = 1,
				.Parameter = 0,
				.TargetSpecies = SPECIES_LEAVANNY,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ARCEUS] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_VICTINI] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 22,
				.TargetSpecies = SPECIES_WHIRLIPEDE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SNIVY] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 30,
				.TargetSpecies = SPECIES_SCOLIPEDE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SERVINE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SERPERIOR] = {
		 .Entries = {
			{
				.Method = 8,
				.Parameter = 80,
				.TargetSpecies = SPECIES_WHIMSICOTT,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_TEPIG] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PIGNITE] = {
		 .Entries = {
			{
				.Method = 8,
				.Parameter = 80,
				.TargetSpecies = SPECIES_LILLIGANT,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_EMBOAR] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_OSHAWOTT] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_DEWOTT] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SAMUROTT] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 29,
				.TargetSpecies = SPECIES_KROKOROK,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PATRAT] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 40,
				.TargetSpecies = SPECIES_KROOKODILE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_WATCHOG] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_LILLIPUP] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 35,
				.TargetSpecies = SPECIES_DARMANITAN,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_HERDIER] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_STOUTLAND] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PURRLOIN] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 34,
				.TargetSpecies = SPECIES_CRUSTLE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_LIEPARD] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PANSAGE] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 39,
				.TargetSpecies = SPECIES_SCRAFTY,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SIMISAGE] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 28,
				.TargetSpecies = SPECIES_PRIMEAPE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PANSEAR] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SIMISEAR] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PANPOUR] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 34,
				.TargetSpecies = SPECIES_COFAGRIGUS,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SIMIPOUR] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MUNNA] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 37,
				.TargetSpecies = SPECIES_CARRACOSTA,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MUSHARNA] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PIDOVE] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 37,
				.TargetSpecies = SPECIES_ARCHEOPS,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_TRANQUILL] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_UNFEZANT] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 36,
				.TargetSpecies = SPECIES_GARBODOR,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_BLITZLE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ZEBSTRIKA] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ROGGENROLA] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 30,
				.TargetSpecies = SPECIES_ZOROARK,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_BOLDORE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GIGALITH] = {
		 .Entries = {
			{
				.Method = 8,
				.Parameter = 107,
				.TargetSpecies = SPECIES_CINCCINO,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_WOOBAT] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SWOOBAT] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 32,
				.TargetSpecies = SPECIES_GOTHORITA,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_DRILBUR] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 41,
				.TargetSpecies = SPECIES_GOTHITELLE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_EXCADRILL] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_AUDINO] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 32,
				.TargetSpecies = SPECIES_DUOSION,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_TIMBURR] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 41,
				.TargetSpecies = SPECIES_REUNICLUS,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GURDURR] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CONKELDURR] = {
		 .Entries = {
			{
				.Method = 8,
				.Parameter = 82,
				.TargetSpecies = SPECIES_ARCANINE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_TYMPOLE] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 35,
				.TargetSpecies = SPECIES_SWANNA,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PALPITOAD] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SEISMITOAD] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 35,
				.TargetSpecies = SPECIES_VANILLISH,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_THROH] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 47,
				.TargetSpecies = SPECIES_VANILLUXE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SAWK] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SEWADDLE] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 34,
				.TargetSpecies = SPECIES_SAWSBUCK,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SWADLOON] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_LEAVANNY] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_VENIPEDE] = {
		 .Entries = {
			{
				.Method = 7,
				.Parameter = 0,
				.TargetSpecies = SPECIES_ESCAVALIER,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_WHIRLIPEDE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SCOLIPEDE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_COTTONEE] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 39,
				.TargetSpecies = SPECIES_AMOONGUSS,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_WHIMSICOTT] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PETILIL] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 40,
				.TargetSpecies = SPECIES_JELLICENT,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_LILLIGANT] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_BASCULIN] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SANDILE] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 36,
				.TargetSpecies = SPECIES_GALVANTULA,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_KROKOROK] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_KROOKODILE] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 40,
				.TargetSpecies = SPECIES_FERROTHORN,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_DARUMAKA] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_DARMANITAN] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 38,
				.TargetSpecies = SPECIES_KLANG,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MARACTUS] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_DWEBBLE] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 25,
				.TargetSpecies = SPECIES_POLIWHIRL,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CRUSTLE] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 49,
				.TargetSpecies = SPECIES_KLINKLANG,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SCRAGGY] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SCRAFTY] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 39,
				.TargetSpecies = SPECIES_EELEKTRIK,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SIGILYPH] = {
		 .Entries = {
			{
				.Method = 8,
				.Parameter = 83,
				.TargetSpecies = SPECIES_EELEKTROSS,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_YAMASK] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_COFAGRIGUS] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 42,
				.TargetSpecies = SPECIES_BEHEEYEM,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_TIRTOUGA] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CARRACOSTA] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 41,
				.TargetSpecies = SPECIES_LAMPENT,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ARCHEN] = {
		 .Entries = {
			{
				.Method = 8,
				.Parameter = 108,
				.TargetSpecies = SPECIES_CHANDELURE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ARCHEOPS] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_TRUBBISH] = {
		 .Entries = {
			{
				.Method = 8,
				.Parameter = 84,
				.TargetSpecies = SPECIES_POLIWRATH,
			},
			{
				.Method = 6,
				.Parameter = 221,
				.TargetSpecies = SPECIES_POLITOED,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GARBODOR] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 38,
				.TargetSpecies = SPECIES_FRAXURE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ZORUA] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 48,
				.TargetSpecies = SPECIES_HAXORUS,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ZOROARK] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MINCCINO] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 37,
				.TargetSpecies = SPECIES_BEARTIC,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CINCCINO] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GOTHITA] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GOTHORITA] = {
		 .Entries = {
			{
				.Method = 7,
				.Parameter = 0,
				.TargetSpecies = SPECIES_ACCELGOR,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GOTHITELLE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SOLOSIS] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_DUOSION] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 50,
				.TargetSpecies = SPECIES_MIENSHAO,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_REUNICLUS] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_DUCKLETT] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SWANNA] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_VANILLITE] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 43,
				.TargetSpecies = SPECIES_GOLURK,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_VANILLISH] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_VANILLUXE] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 52,
				.TargetSpecies = SPECIES_BISHARP,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_DEERLING] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SAWSBUCK] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_EMOLGA] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 54,
				.TargetSpecies = SPECIES_BRAVIARY,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_KARRABLAST] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ESCAVALIER] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 54,
				.TargetSpecies = SPECIES_MANDIBUZZ,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_FOONGUS] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 16,
				.TargetSpecies = SPECIES_KADABRA,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_AMOONGUSS] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_FRILLISH] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_JELLICENT] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ALOMOMOLA] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 50,
				.TargetSpecies = SPECIES_ZWEILOUS,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_JOLTIK] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 64,
				.TargetSpecies = SPECIES_HYDREIGON,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GALVANTULA] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_FERROSEED] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 59,
				.TargetSpecies = SPECIES_VOLCARONA,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_FERROTHORN] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_KLINK] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_KLANG] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_KLINKLANG] = {
		 .Entries = {
			{
				.Method = 5,
				.Parameter = 0,
				.TargetSpecies = SPECIES_ALAKAZAM,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_TYNAMO] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_EELEKTRIK] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_EELEKTROSS] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ELGYEM] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_BEHEEYEM] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_LITWICK] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_LAMPENT] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CHANDELURE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_AXEW] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_FRAXURE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_HAXORUS] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CUBCHOO] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_BEARTIC] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CRYOGONAL] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SHELMET] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ACCELGOR] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_STUNFISK] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MIENFOO] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MIENSHAO] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_DRUDDIGON] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GOLETT] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GOLURK] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 28,
				.TargetSpecies = SPECIES_MACHOKE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PAWNIARD] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_BISHARP] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_BOUFFALANT] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_RUFFLET] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_BRAVIARY] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_VULLABY] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MANDIBUZZ] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_HEATMOR] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_DURANT] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_DEINO] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ZWEILOUS] = {
		 .Entries = {
			{
				.Method = 5,
				.Parameter = 0,
				.TargetSpecies = SPECIES_MACHAMP,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_HYDREIGON] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_LARVESTA] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_VOLCARONA] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_COBALION] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_TERRAKION] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_VIRIZION] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_TORNADUS] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_THUNDURUS] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_RESHIRAM] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ZEKROM] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_LANDORUS] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_KYUREM] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_KELDEO] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MELOETTA] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GENESECT] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CHESPIN] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 16,
				.TargetSpecies = SPECIES_QUILLADIN,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_QUILLADIN] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 36,
				.TargetSpecies = SPECIES_CHESNAUGHT,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CHESNAUGHT] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_FENNEKIN] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 16,
				.TargetSpecies = SPECIES_BRAIXEN,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_BRAIXEN] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 36,
				.TargetSpecies = SPECIES_DELPHOX,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_DELPHOX] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_FROAKIE] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 16,
				.TargetSpecies = SPECIES_FROGADIER,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_FROGADIER] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 36,
				.TargetSpecies = SPECIES_GRENINJA,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GRENINJA] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_BUNNELBY] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 20,
				.TargetSpecies = SPECIES_DIGGERSBY,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_DIGGERSBY] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_FLETCHLING] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 17,
				.TargetSpecies = SPECIES_FLETCHINDER,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_FLETCHINDER] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 35,
				.TargetSpecies = SPECIES_TALONFLAME,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_TALONFLAME] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SCATTERBUG] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 9,
				.TargetSpecies = SPECIES_SPEWPA,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SPEWPA] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 12,
				.TargetSpecies = SPECIES_VIVILLON,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_VIVILLON] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_LITLEO] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 35,
				.TargetSpecies = SPECIES_PYROAR,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PYROAR] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_FLABéBé] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 19,
				.TargetSpecies = SPECIES_FLOETTE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_FLOETTE] = {
		 .Entries = {
			{
				.Method = 8,
				.Parameter = 107,
				.TargetSpecies = SPECIES_FLORGES,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_FLORGES] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SKIDDO] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 32,
				.TargetSpecies = SPECIES_GOGOAT,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GOGOAT] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PANCHAM] = {
		 .Entries = {
			{
				.Method = 30,
				.Parameter = 32,
				.TargetSpecies = SPECIES_PANGORO,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PANGORO] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_FURFROU] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ESPURR] = {
		 .Entries = {
			{
				.Method = 23,
				.Parameter = 25,
				.TargetSpecies = SPECIES_MEOWSTIC,
			},
			{
				.Method = 34,
				.Parameter = 25,
				.TargetSpecies = SPECIES_MEOWSTIC,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MEOWSTIC] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_HONEDGE] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 35,
				.TargetSpecies = SPECIES_DOUBLADE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_DOUBLADE] = {
		 .Entries = {
			{
				.Method = 8,
				.Parameter = 108,
				.TargetSpecies = SPECIES_AEGISLASH,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_AEGISLASH] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SPRITZEE] = {
		 .Entries = {
			{
				.Method = 6,
				.Parameter = 647,
				.TargetSpecies = SPECIES_AROMATISSE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_AROMATISSE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SWIRLIX] = {
		 .Entries = {
			{
				.Method = 6,
				.Parameter = 646,
				.TargetSpecies = SPECIES_SLURPUFF,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SLURPUFF] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_INKAY] = {
		 .Entries = {
			{
				.Method = 28,
				.Parameter = 30,
				.TargetSpecies = SPECIES_MALAMAR,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_MALAMAR] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_BINACLE] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 39,
				.TargetSpecies = SPECIES_BARBARACLE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_BARBARACLE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SKRELP] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 48,
				.TargetSpecies = SPECIES_DRAGALGE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_DRAGALGE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CLAUNCHER] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 37,
				.TargetSpecies = SPECIES_CLAWITZER,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CLAWITZER] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_HELIOPTILE] = {
		 .Entries = {
			{
				.Method = 8,
				.Parameter = 80,
				.TargetSpecies = SPECIES_HELIOLISK,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_HELIOLISK] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_TYRUNT] = {
		 .Entries = {
			{
				.Method = 32,
				.Parameter = 39,
				.TargetSpecies = SPECIES_TYRANTRUM,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_TYRANTRUM] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_AMAURA] = {
		 .Entries = {
			{
				.Method = 33,
				.Parameter = 39,
				.TargetSpecies = SPECIES_AURORUS,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_AURORUS] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SYLVEON] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_HAWLUCHA] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_DEDENNE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_CARBINK] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GOOMY] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 40,
				.TargetSpecies = SPECIES_SLIGGOO,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_SLIGGOO] = {
		 .Entries = {
			{
				.Method = 31,
				.Parameter = 50,
				.TargetSpecies = SPECIES_GOODRA,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GOODRA] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_KLEFKI] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PHANTUMP] = {
		 .Entries = {
			{
				.Method = 5,
				.Parameter = 0,
				.TargetSpecies = SPECIES_TREVENANT,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_TREVENANT] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_PUMPKABOO] = {
		 .Entries = {
			{
				.Method = 5,
				.Parameter = 0,
				.TargetSpecies = SPECIES_GOURGEIST,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_GOURGEIST] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_BERGMITE] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 37,
				.TargetSpecies = SPECIES_AVALUGG,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_AVALUGG] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_NOIBAT] = {
		 .Entries = {
			{
				.Method = 4,
				.Parameter = 48,
				.TargetSpecies = SPECIES_NOIVERN,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_NOIVERN] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_XERNEAS] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_YVELTAL] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_ZYGARDE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_DIANCIE] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_HOOPA] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_VOLCANION] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_EGG] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_BAD_EG] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_724] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_725] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_726] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_727] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_728] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_729] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_730] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_731] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_732] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_733] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_734] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_735] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_736] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_737] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_738] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_739] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_740] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_741] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_742] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_743] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_744] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_745] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_746] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_747] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_748] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_749] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_750] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_751] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_752] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_753] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_754] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_755] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_756] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_757] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_758] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_759] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_760] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_761] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_762] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_763] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_764] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_765] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_766] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_767] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_768] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_769] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_770] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_771] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_772] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_773] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_774] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_775] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_776] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_777] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_778] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_779] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_780] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_781] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_782] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_783] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_784] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_785] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_786] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_787] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_788] = {
		 .Entries = {
			{
				.Method = 5,
				.Parameter = 0,
				.TargetSpecies = SPECIES_GOURGEIST,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_789] = {
		 .Entries = {
			{
				.Method = 5,
				.Parameter = 0,
				.TargetSpecies = SPECIES_GOURGEIST,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_790] = {
		 .Entries = {
			{
				.Method = 5,
				.Parameter = 0,
				.TargetSpecies = SPECIES_GOURGEIST,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_791] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_792] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_793] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_794] = {
		 .Entries = {
			{
				.Method = 8,
				.Parameter = 107,
				.TargetSpecies = SPECIES_FLORGES,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_795] = {
		 .Entries = {
			{
				.Method = 8,
				.Parameter = 107,
				.TargetSpecies = SPECIES_FLORGES,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_796] = {
		 .Entries = {
			{
				.Method = 8,
				.Parameter = 107,
				.TargetSpecies = SPECIES_FLORGES,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_797] = {
		 .Entries = {
			{
				.Method = 8,
				.Parameter = 107,
				.TargetSpecies = SPECIES_FLORGES,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_798] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_799] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_800] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_801] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_802] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_803] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_804] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_805] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_806] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_807] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_808] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_809] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_810] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_811] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_812] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_813] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_814] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_815] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_816] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_817] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_818] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_819] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_820] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_821] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_822] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_823] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_824] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
	[SPECIES_825] = {
		 .Entries = {
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
			{
				.Method = 0,
				.Parameter = 0,
				.TargetSpecies = SPECIES_NONE,
			},
		 },
	},
};
