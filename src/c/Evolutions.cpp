#include "Evolutions.h"

u32 __size = sizeof(EVOLUTION_DATA);

const EVOLUTION_DATA __data[] = {
	[EVOLUTIONS_NONE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_BULBASAUR] = {
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
	[EVOLUTIONS_IVYSAUR] = {
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
	[EVOLUTIONS_VENUSAUR] = {
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
	[EVOLUTIONS_CHARMANDER] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_CHARMELEON] = {
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
	[EVOLUTIONS_CHARIZARD] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SQUIRTLE] = {
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
	[EVOLUTIONS_WARTORTLE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_BLASTOISE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_CATERPIE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_METAPOD] = {
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
	[EVOLUTIONS_BUTTERFREE] = {
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
	[EVOLUTIONS_WEEDLE] = {
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
	[EVOLUTIONS_KAKUNA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_BEEDRILL] = {
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
	[EVOLUTIONS_PIDGEY] = {
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
	[EVOLUTIONS_PIDGEOTTO] = {
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
	[EVOLUTIONS_PIDGEOT] = {
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
	[EVOLUTIONS_RATTATA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_RATICATE] = {
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
	[EVOLUTIONS_SPEAROW] = {
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
	[EVOLUTIONS_FEAROW] = {
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
	[EVOLUTIONS_EKANS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_ARBOK] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_PIKACHU] = {
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
	[EVOLUTIONS_RAICHU] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SANDSHREW] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SANDSLASH] = {
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
	[EVOLUTIONS_NIDORAN♀] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_NIDORINA] = {
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
	[EVOLUTIONS_NIDOQUEEN] = {
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
	[EVOLUTIONS_NIDORAN♂] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_NIDORINO] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_NIDOKING] = {
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
	[EVOLUTIONS_CLEFAIRY] = {
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
	[EVOLUTIONS_CLEFABLE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_VULPIX] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_NINETALES] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_JIGGLYPUFF] = {
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
	[EVOLUTIONS_WIGGLYTUFF] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_ZUBAT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_GOLBAT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_ODDISH] = {
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
	[EVOLUTIONS_GLOOM] = {
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
	[EVOLUTIONS_VILEPLUME] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_PARAS] = {
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
	[EVOLUTIONS_PARASECT] = {
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
	[EVOLUTIONS_VENONAT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_VENOMOTH] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_DIGLETT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_DUGTRIO] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_MEOWTH] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_PERSIAN] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_PSYDUCK] = {
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
	[EVOLUTIONS_GOLDUCK] = {
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
	[EVOLUTIONS_MANKEY] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_PRIMEAPE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_GROWLITHE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_ARCANINE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_POLIWAG] = {
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
	[EVOLUTIONS_POLIWHIRL] = {
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
	[EVOLUTIONS_POLIWRATH] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_ABRA] = {
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
	[EVOLUTIONS_KADABRA] = {
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
	[EVOLUTIONS_ALAKAZAM] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_MACHOP] = {
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
	[EVOLUTIONS_MACHOKE] = {
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
	[EVOLUTIONS_MACHAMP] = {
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
	[EVOLUTIONS_BELLSPROUT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_WEEPINBELL] = {
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
	[EVOLUTIONS_VICTREEBEL] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_TENTACOOL] = {
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
	[EVOLUTIONS_TENTACRUEL] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_GEODUDE] = {
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
	[EVOLUTIONS_GRAVELER] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_GOLEM] = {
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
	[EVOLUTIONS_PONYTA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_RAPIDASH] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SLOWPOKE] = {
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
	[EVOLUTIONS_SLOWBRO] = {
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
	[EVOLUTIONS_MAGNEMITE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_MAGNETON] = {
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
	[EVOLUTIONS_FARFETCHD] = {
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
	[EVOLUTIONS_DODUO] = {
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
	[EVOLUTIONS_DODRIO] = {
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
	[EVOLUTIONS_SEEL] = {
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
	[EVOLUTIONS_DEWGONG] = {
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
	[EVOLUTIONS_GRIMER] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_MUK] = {
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
	[EVOLUTIONS_SHELLDER] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_CLOYSTER] = {
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
	[EVOLUTIONS_GASTLY] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_HAUNTER] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_GENGAR] = {
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
	[EVOLUTIONS_ONIX] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_DROWZEE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_HYPNO] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_KRABBY] = {
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
	[EVOLUTIONS_KINGLER] = {
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
	[EVOLUTIONS_VOLTORB] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_ELECTRODE] = {
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
	[EVOLUTIONS_EXEGGCUTE] = {
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
	[EVOLUTIONS_EXEGGUTOR] = {
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
	[EVOLUTIONS_CUBONE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_MAROWAK] = {
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
	[EVOLUTIONS_HITMONLEE] = {
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
	[EVOLUTIONS_HITMONCHAN] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_LICKITUNG] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_KOFFING] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_WEEZING] = {
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
	[EVOLUTIONS_RHYHORN] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_RHYDON] = {
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
	[EVOLUTIONS_CHANSEY] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_TANGELA] = {
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
	[EVOLUTIONS_KANGASKHAN] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_HORSEA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SEADRA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_GOLDEEN] = {
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
	[EVOLUTIONS_SEAKING] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_STARYU] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_STARMIE] = {
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
	[EVOLUTIONS_MR_MIME] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SCYTHER] = {
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
	[EVOLUTIONS_JYNX] = {
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
	[EVOLUTIONS_ELECTABUZZ] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_MAGMAR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_PINSIR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_TAUROS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_MAGIKARP] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_GYARADOS] = {
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
	[EVOLUTIONS_LAPRAS] = {
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
	[EVOLUTIONS_DITTO] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_EEVEE] = {
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
	[EVOLUTIONS_VAPOREON] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_JOLTEON] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_FLAREON] = {
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
	[EVOLUTIONS_PORYGON] = {
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
	[EVOLUTIONS_OMANYTE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_OMASTAR] = {
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
	[EVOLUTIONS_KABUTO] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_KABUTOPS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_AERODACTYL] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SNORLAX] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_ARTICUNO] = {
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
	[EVOLUTIONS_ZAPDOS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_MOLTRES] = {
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
	[EVOLUTIONS_DRATINI] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_DRAGONAIR] = {
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
	[EVOLUTIONS_DRAGONITE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_MEWTWO] = {
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
	[EVOLUTIONS_MEW] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_CHIKORITA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_BAYLEEF] = {
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
	[EVOLUTIONS_MEGANIUM] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_CYNDAQUIL] = {
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
	[EVOLUTIONS_QUILAVA] = {
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
	[EVOLUTIONS_TYPHLOSION] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_TOTODILE] = {
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
	[EVOLUTIONS_CROCONAW] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_FERALIGATR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SENTRET] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_FURRET] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_HOOTHOOT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_NOCTOWL] = {
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
	[EVOLUTIONS_LEDYBA] = {
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
	[EVOLUTIONS_LEDIAN] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SPINARAK] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_ARIADOS] = {
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
	[EVOLUTIONS_CROBAT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_CHINCHOU] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_LANTURN] = {
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
	[EVOLUTIONS_PICHU] = {
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
	[EVOLUTIONS_CLEFFA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_IGGLYBUFF] = {
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
	[EVOLUTIONS_TOGEPI] = {
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
	[EVOLUTIONS_TOGETIC] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_NATU] = {
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
	[EVOLUTIONS_XATU] = {
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
	[EVOLUTIONS_MAREEP] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_FLAAFFY] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_AMPHAROS] = {
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
	[EVOLUTIONS_BELLOSSOM] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_MARILL] = {
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
	[EVOLUTIONS_AZUMARILL] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SUDOWOODO] = {
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
	[EVOLUTIONS_POLITOED] = {
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
	[EVOLUTIONS_HOPPIP] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SKIPLOOM] = {
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
	[EVOLUTIONS_JUMPLUFF] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_AIPOM] = {
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
	[EVOLUTIONS_SUNKERN] = {
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
	[EVOLUTIONS_SUNFLORA] = {
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
	[EVOLUTIONS_YANMA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_WOOPER] = {
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
	[EVOLUTIONS_QUAGSIRE] = {
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
	[EVOLUTIONS_ESPEON] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_UMBREON] = {
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
	[EVOLUTIONS_MURKROW] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SLOWKING] = {
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
	[EVOLUTIONS_MISDREAVUS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_UNOWN] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_WOBBUFFET] = {
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
	[EVOLUTIONS_GIRAFARIG] = {
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
	[EVOLUTIONS_PINECO] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_FORRETRESS] = {
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
	[EVOLUTIONS_DUNSPARCE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_GLIGAR] = {
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
	[EVOLUTIONS_STEELIX] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SNUBBULL] = {
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
	[EVOLUTIONS_GRANBULL] = {
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
	[EVOLUTIONS_QWILFISH] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SCIZOR] = {
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
	[EVOLUTIONS_SHUCKLE] = {
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
	[EVOLUTIONS_HERACROSS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SNEASEL] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_TEDDIURSA] = {
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
	[EVOLUTIONS_URSARING] = {
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
	[EVOLUTIONS_SLUGMA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_MAGCARGO] = {
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
	[EVOLUTIONS_SWINUB] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_PILOSWINE] = {
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
	[EVOLUTIONS_CORSOLA] = {
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
	[EVOLUTIONS_REMORAID] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_OCTILLERY] = {
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
	[EVOLUTIONS_DELIBIRD] = {
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
	[EVOLUTIONS_MANTINE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SKARMORY] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_HOUNDOUR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_HOUNDOOM] = {
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
	[EVOLUTIONS_KINGDRA] = {
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
	[EVOLUTIONS_PHANPY] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_DONPHAN] = {
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
	[EVOLUTIONS_PORYGON2] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_STANTLER] = {
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
	[EVOLUTIONS_SMEARGLE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_TYROGUE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_HITMONTOP] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SMOOCHUM] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_ELEKID] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_MAGBY] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_MILTANK] = {
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
	[EVOLUTIONS_BLISSEY] = {
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
	[EVOLUTIONS_RAIKOU] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_ENTEI] = {
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
	[EVOLUTIONS_SUICUNE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_LARVITAR] = {
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
	[EVOLUTIONS_PUPITAR] = {
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
	[EVOLUTIONS_TYRANITAR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_LUGIA] = {
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
	[EVOLUTIONS_HOOH] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_CELEBI] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_TREECKO] = {
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
	[EVOLUTIONS_GROVYLE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SCEPTILE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_TORCHIC] = {
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
	[EVOLUTIONS_COMBUSKEN] = {
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
	[EVOLUTIONS_BLAZIKEN] = {
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
	[EVOLUTIONS_MUDKIP] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_MARSHTOMP] = {
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
	[EVOLUTIONS_SWAMPERT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_POOCHYENA] = {
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
	[EVOLUTIONS_MIGHTYENA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_ZIGZAGOON] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_LINOONE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_WURMPLE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SILCOON] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_BEAUTIFLY] = {
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
	[EVOLUTIONS_CASCOON] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_DUSTOX] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_LOTAD] = {
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
	[EVOLUTIONS_LOMBRE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_LUDICOLO] = {
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
	[EVOLUTIONS_SEEDOT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_NUZLEAF] = {
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
	[EVOLUTIONS_SHIFTRY] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_TAILLOW] = {
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
	[EVOLUTIONS_SWELLOW] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_WINGULL] = {
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
	[EVOLUTIONS_PELIPPER] = {
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
	[EVOLUTIONS_RALTS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_KIRLIA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_GARDEVOIR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SURSKIT] = {
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
	[EVOLUTIONS_MASQUERAIN] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SHROOMISH] = {
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
	[EVOLUTIONS_BRELOOM] = {
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
	[EVOLUTIONS_SLAKOTH] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_VIGOROTH] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SLAKING] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_NINCADA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_NINJASK] = {
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
	[EVOLUTIONS_SHEDINJA] = {
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
	[EVOLUTIONS_WHISMUR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_LOUDRED] = {
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
	[EVOLUTIONS_EXPLOUD] = {
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
	[EVOLUTIONS_MAKUHITA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_HARIYAMA] = {
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
	[EVOLUTIONS_AZURILL] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_NOSEPASS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SKITTY] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_DELCATTY] = {
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
	[EVOLUTIONS_SABLEYE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_MAWILE] = {
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
	[EVOLUTIONS_ARON] = {
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
	[EVOLUTIONS_LAIRON] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_AGGRON] = {
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
	[EVOLUTIONS_MEDITITE] = {
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
	[EVOLUTIONS_MEDICHAM] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_ELECTRIKE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_MANECTRIC] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_PLUSLE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_MINUN] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_VOLBEAT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_ILLUMISE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_ROSELIA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_GULPIN] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SWALOT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_CARVANHA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SHARPEDO] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_WAILMER] = {
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
	[EVOLUTIONS_WAILORD] = {
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
	[EVOLUTIONS_NUMEL] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_CAMERUPT] = {
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
	[EVOLUTIONS_TORKOAL] = {
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
	[EVOLUTIONS_SPOINK] = {
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
	[EVOLUTIONS_GRUMPIG] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SPINDA] = {
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
	[EVOLUTIONS_TRAPINCH] = {
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
	[EVOLUTIONS_VIBRAVA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_FLYGON] = {
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
	[EVOLUTIONS_CACNEA] = {
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
	[EVOLUTIONS_CACTURNE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SWABLU] = {
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
	[EVOLUTIONS_ALTARIA] = {
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
	[EVOLUTIONS_ZANGOOSE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SEVIPER] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_LUNATONE] = {
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
	[EVOLUTIONS_SOLROCK] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_BARBOACH] = {
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
	[EVOLUTIONS_WHISCASH] = {
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
	[EVOLUTIONS_CORPHISH] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_CRAWDAUNT] = {
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
	[EVOLUTIONS_BALTOY] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_CLAYDOL] = {
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
	[EVOLUTIONS_LILEEP] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_CRADILY] = {
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
	[EVOLUTIONS_ANORITH] = {
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
	[EVOLUTIONS_ARMALDO] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_FEEBAS] = {
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
	[EVOLUTIONS_MILOTIC] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_CASTFORM] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_KECLEON] = {
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
	[EVOLUTIONS_SHUPPET] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_BANETTE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_DUSKULL] = {
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
	[EVOLUTIONS_DUSCLOPS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_TROPIUS] = {
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
	[EVOLUTIONS_CHIMECHO] = {
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
	[EVOLUTIONS_ABSOL] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_WYNAUT] = {
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
	[EVOLUTIONS_SNORUNT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_GLALIE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SPHEAL] = {
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
	[EVOLUTIONS_SEALEO] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_WALREIN] = {
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
	[EVOLUTIONS_CLAMPERL] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_HUNTAIL] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_GOREBYSS] = {
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
	[EVOLUTIONS_RELICANTH] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_LUVDISC] = {
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
	[EVOLUTIONS_BAGON] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SHELGON] = {
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
	[EVOLUTIONS_SALAMENCE] = {
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
	[EVOLUTIONS_BELDUM] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_METANG] = {
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
	[EVOLUTIONS_METAGROSS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_REGIROCK] = {
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
	[EVOLUTIONS_REGICE] = {
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
	[EVOLUTIONS_REGISTEEL] = {
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
	[EVOLUTIONS_LATIAS] = {
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
	[EVOLUTIONS_LATIOS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_KYOGRE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_GROUDON] = {
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
	[EVOLUTIONS_RAYQUAZA] = {
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
	[EVOLUTIONS_JIRACHI] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_DEOXYS] = {
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
	[EVOLUTIONS_TURTWIG] = {
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
	[EVOLUTIONS_GROTLE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_TORTERRA] = {
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
	[EVOLUTIONS_CHIMCHAR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_MONFERNO] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_INFERNAPE] = {
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
	[EVOLUTIONS_PIPLUP] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_PRINPLUP] = {
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
	[EVOLUTIONS_EMPOLEON] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_STARLY] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_STARAVIA] = {
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
	[EVOLUTIONS_STARAPTOR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_BIDOOF] = {
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
	[EVOLUTIONS_BIBAREL] = {
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
	[EVOLUTIONS_KRICKETOT] = {
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
	[EVOLUTIONS_KRICKETUNE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SHINX] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_LUXIO] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_LUXRAY] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_BUDEW] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_ROSERADE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_CRANIDOS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_RAMPARDOS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SHIELDON] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_BASTIODON] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_BURMY] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_WORMADAM] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_MOTHIM] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_COMBEE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_VESPIQUEN] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_PACHIRISU] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_BUIZEL] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_FLOATZEL] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_CHERUBI] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_CHERRIM] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SHELLOS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_GASTRODON] = {
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
	[EVOLUTIONS_AMBIPOM] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_DRIFLOON] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_DRIFBLIM] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_BUNEARY] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_LOPUNNY] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_MISMAGIUS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_HONCHKROW] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_GLAMEOW] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_PURUGLY] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_CHINGLING] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_STUNKY] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SKUNTANK] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_BRONZOR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_BRONZONG] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_BONSLY] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_MIME_JR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_HAPPINY] = {
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
	[EVOLUTIONS_CHATOT] = {
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
	[EVOLUTIONS_SPIRITOMB] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_GIBLE] = {
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
	[EVOLUTIONS_GABITE] = {
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
	[EVOLUTIONS_GARCHOMP] = {
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
	[EVOLUTIONS_MUNCHLAX] = {
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
	[EVOLUTIONS_RIOLU] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_LUCARIO] = {
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
	[EVOLUTIONS_HIPPOPOTAS] = {
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
	[EVOLUTIONS_HIPPOWDON] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SKORUPI] = {
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
	[EVOLUTIONS_DRAPION] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_CROAGUNK] = {
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
	[EVOLUTIONS_TOXICROAK] = {
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
	[EVOLUTIONS_CARNIVINE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_FINNEON] = {
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
	[EVOLUTIONS_LUMINEON] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_MANTYKE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SNOVER] = {
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
	[EVOLUTIONS_ABOMASNOW] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_WEAVILE] = {
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
	[EVOLUTIONS_MAGNEZONE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_LICKILICKY] = {
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
	[EVOLUTIONS_RHYPERIOR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_TANGROWTH] = {
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
	[EVOLUTIONS_ELECTIVIRE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_MAGMORTAR] = {
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
	[EVOLUTIONS_TOGEKISS] = {
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
	[EVOLUTIONS_YANMEGA] = {
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
	[EVOLUTIONS_LEAFEON] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_GLACEON] = {
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
	[EVOLUTIONS_GLISCOR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_MAMOSWINE] = {
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
	[EVOLUTIONS_PORYGONZ] = {
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
	[EVOLUTIONS_GALLADE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_PROBOPASS] = {
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
	[EVOLUTIONS_DUSKNOIR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_FROSLASS] = {
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
	[EVOLUTIONS_ROTOM] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_UXIE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_MESPRIT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_AZELF] = {
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
	[EVOLUTIONS_DIALGA] = {
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
	[EVOLUTIONS_PALKIA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_HEATRAN] = {
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
	[EVOLUTIONS_REGIGIGAS] = {
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
	[EVOLUTIONS_GIRATINA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_CRESSELIA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_PHIONE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_MANAPHY] = {
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
	[EVOLUTIONS_DARKRAI] = {
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
	[EVOLUTIONS_SHAYMIN] = {
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
	[EVOLUTIONS_ARCEUS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_VICTINI] = {
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
	[EVOLUTIONS_SNIVY] = {
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
	[EVOLUTIONS_SERVINE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SERPERIOR] = {
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
	[EVOLUTIONS_TEPIG] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_PIGNITE] = {
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
	[EVOLUTIONS_EMBOAR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_OSHAWOTT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_DEWOTT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SAMUROTT] = {
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
	[EVOLUTIONS_PATRAT] = {
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
	[EVOLUTIONS_WATCHOG] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_LILLIPUP] = {
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
	[EVOLUTIONS_HERDIER] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_STOUTLAND] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_PURRLOIN] = {
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
	[EVOLUTIONS_LIEPARD] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_PANSAGE] = {
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
	[EVOLUTIONS_SIMISAGE] = {
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
	[EVOLUTIONS_PANSEAR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SIMISEAR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_PANPOUR] = {
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
	[EVOLUTIONS_SIMIPOUR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_MUNNA] = {
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
	[EVOLUTIONS_MUSHARNA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_PIDOVE] = {
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
	[EVOLUTIONS_TRANQUILL] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_UNFEZANT] = {
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
	[EVOLUTIONS_BLITZLE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_ZEBSTRIKA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_ROGGENROLA] = {
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
	[EVOLUTIONS_BOLDORE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_GIGALITH] = {
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
	[EVOLUTIONS_WOOBAT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SWOOBAT] = {
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
	[EVOLUTIONS_DRILBUR] = {
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
	[EVOLUTIONS_EXCADRILL] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_AUDINO] = {
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
	[EVOLUTIONS_TIMBURR] = {
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
	[EVOLUTIONS_GURDURR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_CONKELDURR] = {
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
	[EVOLUTIONS_TYMPOLE] = {
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
	[EVOLUTIONS_PALPITOAD] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SEISMITOAD] = {
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
	[EVOLUTIONS_THROH] = {
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
	[EVOLUTIONS_SAWK] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SEWADDLE] = {
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
	[EVOLUTIONS_SWADLOON] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_LEAVANNY] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_VENIPEDE] = {
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
	[EVOLUTIONS_WHIRLIPEDE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SCOLIPEDE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_COTTONEE] = {
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
	[EVOLUTIONS_WHIMSICOTT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_PETILIL] = {
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
	[EVOLUTIONS_LILLIGANT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_BASCULIN] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SANDILE] = {
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
	[EVOLUTIONS_KROKOROK] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_KROOKODILE] = {
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
	[EVOLUTIONS_DARUMAKA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_DARMANITAN] = {
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
	[EVOLUTIONS_MARACTUS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_DWEBBLE] = {
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
	[EVOLUTIONS_CRUSTLE] = {
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
	[EVOLUTIONS_SCRAGGY] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SCRAFTY] = {
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
	[EVOLUTIONS_SIGILYPH] = {
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
	[EVOLUTIONS_YAMASK] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_COFAGRIGUS] = {
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
	[EVOLUTIONS_TIRTOUGA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_CARRACOSTA] = {
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
	[EVOLUTIONS_ARCHEN] = {
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
	[EVOLUTIONS_ARCHEOPS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_TRUBBISH] = {
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
	[EVOLUTIONS_GARBODOR] = {
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
	[EVOLUTIONS_ZORUA] = {
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
	[EVOLUTIONS_ZOROARK] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_MINCCINO] = {
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
	[EVOLUTIONS_CINCCINO] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_GOTHITA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_GOTHORITA] = {
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
	[EVOLUTIONS_GOTHITELLE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SOLOSIS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_DUOSION] = {
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
	[EVOLUTIONS_REUNICLUS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_DUCKLETT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SWANNA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_VANILLITE] = {
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
	[EVOLUTIONS_VANILLISH] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_VANILLUXE] = {
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
	[EVOLUTIONS_DEERLING] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SAWSBUCK] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_EMOLGA] = {
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
	[EVOLUTIONS_KARRABLAST] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_ESCAVALIER] = {
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
	[EVOLUTIONS_FOONGUS] = {
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
	[EVOLUTIONS_AMOONGUSS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_FRILLISH] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_JELLICENT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_ALOMOMOLA] = {
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
	[EVOLUTIONS_JOLTIK] = {
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
	[EVOLUTIONS_GALVANTULA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_FERROSEED] = {
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
	[EVOLUTIONS_FERROTHORN] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_KLINK] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_KLANG] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_KLINKLANG] = {
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
	[EVOLUTIONS_TYNAMO] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_EELEKTRIK] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_EELEKTROSS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_ELGYEM] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_BEHEEYEM] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_LITWICK] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_LAMPENT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_CHANDELURE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_AXEW] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_FRAXURE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_HAXORUS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_CUBCHOO] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_BEARTIC] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_CRYOGONAL] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SHELMET] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_ACCELGOR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_STUNFISK] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_MIENFOO] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_MIENSHAO] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_DRUDDIGON] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_GOLETT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_GOLURK] = {
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
	[EVOLUTIONS_PAWNIARD] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_BISHARP] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_BOUFFALANT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_RUFFLET] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_BRAVIARY] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_VULLABY] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_MANDIBUZZ] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_HEATMOR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_DURANT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_DEINO] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_ZWEILOUS] = {
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
	[EVOLUTIONS_HYDREIGON] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_LARVESTA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_VOLCARONA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_COBALION] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_TERRAKION] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_VIRIZION] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_TORNADUS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_THUNDURUS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_RESHIRAM] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_ZEKROM] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_LANDORUS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_KYUREM] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_KELDEO] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_MELOETTA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_GENESECT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_CHESPIN] = {
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
	[EVOLUTIONS_QUILLADIN] = {
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
	[EVOLUTIONS_CHESNAUGHT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_FENNEKIN] = {
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
	[EVOLUTIONS_BRAIXEN] = {
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
	[EVOLUTIONS_DELPHOX] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_FROAKIE] = {
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
	[EVOLUTIONS_FROGADIER] = {
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
	[EVOLUTIONS_GRENINJA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_BUNNELBY] = {
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
	[EVOLUTIONS_DIGGERSBY] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_FLETCHLING] = {
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
	[EVOLUTIONS_FLETCHINDER] = {
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
	[EVOLUTIONS_TALONFLAME] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SCATTERBUG] = {
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
	[EVOLUTIONS_SPEWPA] = {
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
	[EVOLUTIONS_VIVILLON] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_LITLEO] = {
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
	[EVOLUTIONS_PYROAR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_FLABEBE] = {
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
	[EVOLUTIONS_FLOETTE] = {
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
	[EVOLUTIONS_FLORGES] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SKIDDO] = {
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
	[EVOLUTIONS_GOGOAT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_PANCHAM] = {
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
	[EVOLUTIONS_PANGORO] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_FURFROU] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_ESPURR] = {
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
	[EVOLUTIONS_MEOWSTIC] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_HONEDGE] = {
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
	[EVOLUTIONS_DOUBLADE] = {
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
	[EVOLUTIONS_AEGISLASH] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SPRITZEE] = {
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
	[EVOLUTIONS_AROMATISSE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SWIRLIX] = {
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
	[EVOLUTIONS_SLURPUFF] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_INKAY] = {
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
	[EVOLUTIONS_MALAMAR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_BINACLE] = {
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
	[EVOLUTIONS_BARBARACLE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SKRELP] = {
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
	[EVOLUTIONS_DRAGALGE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_CLAUNCHER] = {
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
	[EVOLUTIONS_CLAWITZER] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_HELIOPTILE] = {
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
	[EVOLUTIONS_HELIOLISK] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_TYRUNT] = {
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
	[EVOLUTIONS_TYRANTRUM] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_AMAURA] = {
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
	[EVOLUTIONS_AURORUS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SYLVEON] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_HAWLUCHA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_DEDENNE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_CARBINK] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_GOOMY] = {
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
	[EVOLUTIONS_SLIGGOO] = {
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
	[EVOLUTIONS_GOODRA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_KLEFKI] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_PHANTUMP] = {
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
	[EVOLUTIONS_TREVENANT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_PUMPKABOO] = {
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
	[EVOLUTIONS_GOURGEIST] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_BERGMITE] = {
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
	[EVOLUTIONS_AVALUGG] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_NOIBAT] = {
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
	[EVOLUTIONS_NOIVERN] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_XERNEAS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_YVELTAL] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_ZYGARDE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_DIANCIE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_HOOPA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_VOLCANION] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_EGG] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_BAD_EGG] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_UFO] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_BRYCENMAN] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_MT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_MT2] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_TRANSPORT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_GIANT_15] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_HUMANOID] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_MONSTER] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_F00] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SPIRIT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_WHITE_DOOR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_BLACK_DOOR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_PROP_U1] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_PROP_U2] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_PROP_H1] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_PROP_M1] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_PROP_M2] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_PROP_T1] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_PROP_O1] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_PROP_O2] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_PROP_C1] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_PROP_C2] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_PROP_G1] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_PROP_W1] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_PROP_W2] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_PROP_R1] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_PROP_R2] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_PROP_K1] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_UFO_2] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_GIANT_15_2] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_F002] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_BLACK_BELT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_SMEARGLE_2] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_EGG] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_EGG] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
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
	[EVOLUTIONS_826] = {
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
	[EVOLUTIONS_826] = {
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
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
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
	[EVOLUTIONS_826] = {
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
	[EVOLUTIONS_826] = {
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
	[EVOLUTIONS_826] = {
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
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[EVOLUTIONS_826] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
};
