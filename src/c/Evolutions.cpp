#include "Species.h"
#include "Evolutions.h"

u32 __size = sizeof(EVOLUTION_DATA);

const EVOLUTION_DATA __data[] = {
	[SPECIES_NONE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_BULBASAUR] = {
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
	[SPECIES_IVYSAUR] = {
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
	[SPECIES_VENUSAUR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_CHARMANDER] = {
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
	[SPECIES_CHARMELEON] = {
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
	[SPECIES_CHARIZARD] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SQUIRTLE] = {
		{
			.Method = 4,
			.Parameter = 16,
			.TargetSpecies = SPECIES_WARTORTLE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_WARTORTLE] = {
		{
			.Method = 4,
			.Parameter = 36,
			.TargetSpecies = SPECIES_BLASTOISE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_BLASTOISE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_CATERPIE] = {
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
	[SPECIES_METAPOD] = {
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
	[SPECIES_BUTTERFREE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_WEEDLE] = {
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
	[SPECIES_KAKUNA] = {
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
	[SPECIES_BEEDRILL] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_PIDGEY] = {
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
	[SPECIES_PIDGEOTTO] = {
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
	[SPECIES_PIDGEOT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_RATTATA] = {
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
	[SPECIES_RATICATE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SPEAROW] = {
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
	[SPECIES_FEAROW] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_EKANS] = {
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
	[SPECIES_ARBOK] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_PIKACHU] = {
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
	[SPECIES_RAICHU] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SANDSHREW] = {
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
	[SPECIES_SANDSLASH] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_NIDORAN♀] = {
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
	[SPECIES_NIDORINA] = {
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
	[SPECIES_NIDOQUEEN] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_NIDORAN♂] = {
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
	[SPECIES_NIDORINO] = {
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
	[SPECIES_NIDOKING] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_CLEFAIRY] = {
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
	[SPECIES_CLEFABLE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_VULPIX] = {
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
	[SPECIES_NINETALES] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_JIGGLYPUFF] = {
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
	[SPECIES_WIGGLYTUFF] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_ZUBAT] = {
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
	[SPECIES_GOLBAT] = {
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
	[SPECIES_ODDISH] = {
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
	[SPECIES_GLOOM] = {
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
	[SPECIES_VILEPLUME] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_PARAS] = {
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
	[SPECIES_PARASECT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_VENONAT] = {
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
	[SPECIES_VENOMOTH] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_DIGLETT] = {
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
	[SPECIES_DUGTRIO] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_MEOWTH] = {
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
	[SPECIES_PERSIAN] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_PSYDUCK] = {
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
	[SPECIES_GOLDUCK] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_MANKEY] = {
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
	[SPECIES_PRIMEAPE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_GROWLITHE] = {
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
	[SPECIES_ARCANINE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_POLIWAG] = {
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
	[SPECIES_POLIWHIRL] = {
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
	[SPECIES_POLIWRATH] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_ABRA] = {
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
	[SPECIES_KADABRA] = {
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
	[SPECIES_ALAKAZAM] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_MACHOP] = {
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
	[SPECIES_MACHOKE] = {
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
	[SPECIES_MACHAMP] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_BELLSPROUT] = {
		{
			.Method = 4,
			.Parameter = 21,
			.TargetSpecies = SPECIES_WEEPINBELL,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_WEEPINBELL] = {
		{
			.Method = 8,
			.Parameter = 85,
			.TargetSpecies = SPECIES_VICTREEBEL,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_VICTREEBEL] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_TENTACOOL] = {
		{
			.Method = 4,
			.Parameter = 30,
			.TargetSpecies = SPECIES_TENTACRUEL,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_TENTACRUEL] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_GEODUDE] = {
		{
			.Method = 4,
			.Parameter = 25,
			.TargetSpecies = SPECIES_GRAVELER,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_GRAVELER] = {
		{
			.Method = 5,
			.Parameter = 0,
			.TargetSpecies = SPECIES_GOLEM,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_GOLEM] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_PONYTA] = {
		{
			.Method = 4,
			.Parameter = 40,
			.TargetSpecies = SPECIES_RAPIDASH,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_RAPIDASH] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SLOWPOKE] = {
		{
			.Method = 4,
			.Parameter = 37,
			.TargetSpecies = SPECIES_SLOWBRO,
		},
		{
			.Method = 6,
			.Parameter = 221,
			.TargetSpecies = SPECIES_SLOWKING,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SLOWBRO] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_MAGNEMITE] = {
		{
			.Method = 4,
			.Parameter = 30,
			.TargetSpecies = SPECIES_MAGNETON,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_MAGNETON] = {
		{
			.Method = 25,
			.Parameter = 0,
			.TargetSpecies = SPECIES_MAGNEZONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_FARFETCHD] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_DODUO] = {
		{
			.Method = 4,
			.Parameter = 31,
			.TargetSpecies = SPECIES_DODRIO,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_DODRIO] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SEEL] = {
		{
			.Method = 4,
			.Parameter = 34,
			.TargetSpecies = SPECIES_DEWGONG,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_DEWGONG] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_GRIMER] = {
		{
			.Method = 4,
			.Parameter = 38,
			.TargetSpecies = SPECIES_MUK,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_MUK] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SHELLDER] = {
		{
			.Method = 8,
			.Parameter = 84,
			.TargetSpecies = SPECIES_CLOYSTER,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_CLOYSTER] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_GASTLY] = {
		{
			.Method = 4,
			.Parameter = 25,
			.TargetSpecies = SPECIES_HAUNTER,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_HAUNTER] = {
		{
			.Method = 5,
			.Parameter = 0,
			.TargetSpecies = SPECIES_GENGAR,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_GENGAR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_ONIX] = {
		{
			.Method = 6,
			.Parameter = 233,
			.TargetSpecies = SPECIES_STEELIX,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_DROWZEE] = {
		{
			.Method = 4,
			.Parameter = 26,
			.TargetSpecies = SPECIES_HYPNO,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_HYPNO] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_KRABBY] = {
		{
			.Method = 4,
			.Parameter = 28,
			.TargetSpecies = SPECIES_KINGLER,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_KINGLER] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_VOLTORB] = {
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
	[SPECIES_ELECTRODE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_EXEGGCUTE] = {
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
	[SPECIES_EXEGGUTOR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_CUBONE] = {
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
	[SPECIES_MAROWAK] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_HITMONLEE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_HITMONCHAN] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_LICKITUNG] = {
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
	[SPECIES_KOFFING] = {
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
	[SPECIES_WEEZING] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_RHYHORN] = {
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
	[SPECIES_RHYDON] = {
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
	[SPECIES_CHANSEY] = {
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
	[SPECIES_TANGELA] = {
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
	[SPECIES_KANGASKHAN] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_HORSEA] = {
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
	[SPECIES_SEADRA] = {
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
	[SPECIES_GOLDEEN] = {
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
	[SPECIES_SEAKING] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_STARYU] = {
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
	[SPECIES_STARMIE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_MR_MIME] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SCYTHER] = {
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
	[SPECIES_JYNX] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_ELECTABUZZ] = {
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
	[SPECIES_MAGMAR] = {
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
	[SPECIES_PINSIR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_TAUROS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_MAGIKARP] = {
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
	[SPECIES_GYARADOS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_LAPRAS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_DITTO] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_EEVEE] = {
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
	[SPECIES_VAPOREON] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_JOLTEON] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_FLAREON] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_PORYGON] = {
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
	[SPECIES_OMANYTE] = {
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
	[SPECIES_OMASTAR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_KABUTO] = {
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
	[SPECIES_KABUTOPS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_AERODACTYL] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SNORLAX] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_ARTICUNO] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_ZAPDOS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_MOLTRES] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_DRATINI] = {
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
	[SPECIES_DRAGONAIR] = {
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
	[SPECIES_DRAGONITE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_MEWTWO] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_MEW] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_CHIKORITA] = {
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
	[SPECIES_BAYLEEF] = {
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
	[SPECIES_MEGANIUM] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_CYNDAQUIL] = {
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
	[SPECIES_QUILAVA] = {
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
	[SPECIES_TYPHLOSION] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_TOTODILE] = {
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
	[SPECIES_CROCONAW] = {
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
	[SPECIES_FERALIGATR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SENTRET] = {
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
	[SPECIES_FURRET] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_HOOTHOOT] = {
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
	[SPECIES_NOCTOWL] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_LEDYBA] = {
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
	[SPECIES_LEDIAN] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SPINARAK] = {
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
	[SPECIES_ARIADOS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_CROBAT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_CHINCHOU] = {
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
	[SPECIES_LANTURN] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_PICHU] = {
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
	[SPECIES_CLEFFA] = {
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
	[SPECIES_IGGLYBUFF] = {
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
	[SPECIES_TOGEPI] = {
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
	[SPECIES_TOGETIC] = {
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
	[SPECIES_NATU] = {
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
	[SPECIES_XATU] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_MAREEP] = {
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
	[SPECIES_FLAAFFY] = {
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
	[SPECIES_AMPHAROS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_BELLOSSOM] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_MARILL] = {
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
	[SPECIES_AZUMARILL] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SUDOWOODO] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_POLITOED] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_HOPPIP] = {
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
	[SPECIES_SKIPLOOM] = {
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
	[SPECIES_JUMPLUFF] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_AIPOM] = {
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
	[SPECIES_SUNKERN] = {
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
	[SPECIES_SUNFLORA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_YANMA] = {
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
	[SPECIES_WOOPER] = {
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
	[SPECIES_QUAGSIRE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_ESPEON] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_UMBREON] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_MURKROW] = {
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
	[SPECIES_SLOWKING] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_MISDREAVUS] = {
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
	[SPECIES_UNOWN] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_WOBBUFFET] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_GIRAFARIG] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_PINECO] = {
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
	[SPECIES_FORRETRESS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_DUNSPARCE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_GLIGAR] = {
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
	[SPECIES_STEELIX] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SNUBBULL] = {
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
	[SPECIES_GRANBULL] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_QWILFISH] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SCIZOR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SHUCKLE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_HERACROSS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SNEASEL] = {
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
	[SPECIES_TEDDIURSA] = {
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
	[SPECIES_URSARING] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SLUGMA] = {
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
	[SPECIES_MAGCARGO] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SWINUB] = {
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
	[SPECIES_PILOSWINE] = {
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
	[SPECIES_CORSOLA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_REMORAID] = {
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
	[SPECIES_OCTILLERY] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_DELIBIRD] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_MANTINE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SKARMORY] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_HOUNDOUR] = {
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
	[SPECIES_HOUNDOOM] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_KINGDRA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_PHANPY] = {
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
	[SPECIES_DONPHAN] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_PORYGON2] = {
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
	[SPECIES_STANTLER] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SMEARGLE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_TYROGUE] = {
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
	[SPECIES_HITMONTOP] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SMOOCHUM] = {
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
	[SPECIES_ELEKID] = {
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
	[SPECIES_MAGBY] = {
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
	[SPECIES_MILTANK] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_BLISSEY] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_RAIKOU] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_ENTEI] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SUICUNE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_LARVITAR] = {
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
	[SPECIES_PUPITAR] = {
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
	[SPECIES_TYRANITAR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_LUGIA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_HOOH] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_CELEBI] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_TREECKO] = {
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
	[SPECIES_GROVYLE] = {
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
	[SPECIES_SCEPTILE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_TORCHIC] = {
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
	[SPECIES_COMBUSKEN] = {
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
	[SPECIES_BLAZIKEN] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_MUDKIP] = {
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
	[SPECIES_MARSHTOMP] = {
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
	[SPECIES_SWAMPERT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_POOCHYENA] = {
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
	[SPECIES_MIGHTYENA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_ZIGZAGOON] = {
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
	[SPECIES_LINOONE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_WURMPLE] = {
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
	[SPECIES_SILCOON] = {
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
	[SPECIES_BEAUTIFLY] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_CASCOON] = {
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
	[SPECIES_DUSTOX] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_LOTAD] = {
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
	[SPECIES_LOMBRE] = {
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
	[SPECIES_LUDICOLO] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SEEDOT] = {
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
	[SPECIES_NUZLEAF] = {
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
	[SPECIES_SHIFTRY] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_TAILLOW] = {
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
	[SPECIES_SWELLOW] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_WINGULL] = {
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
	[SPECIES_PELIPPER] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_RALTS] = {
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
	[SPECIES_KIRLIA] = {
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
	[SPECIES_GARDEVOIR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SURSKIT] = {
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
	[SPECIES_MASQUERAIN] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SHROOMISH] = {
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
	[SPECIES_BRELOOM] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SLAKOTH] = {
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
	[SPECIES_VIGOROTH] = {
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
	[SPECIES_SLAKING] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_NINCADA] = {
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
	[SPECIES_NINJASK] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SHEDINJA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_WHISMUR] = {
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
	[SPECIES_LOUDRED] = {
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
	[SPECIES_EXPLOUD] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_MAKUHITA] = {
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
	[SPECIES_HARIYAMA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_AZURILL] = {
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
	[SPECIES_NOSEPASS] = {
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
	[SPECIES_SKITTY] = {
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
	[SPECIES_DELCATTY] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SABLEYE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_MAWILE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_ARON] = {
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
	[SPECIES_LAIRON] = {
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
	[SPECIES_AGGRON] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_MEDITITE] = {
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
	[SPECIES_MEDICHAM] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_ELECTRIKE] = {
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
	[SPECIES_MANECTRIC] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_PLUSLE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_MINUN] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_VOLBEAT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_ILLUMISE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_ROSELIA] = {
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
	[SPECIES_GULPIN] = {
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
	[SPECIES_SWALOT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_CARVANHA] = {
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
	[SPECIES_SHARPEDO] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_WAILMER] = {
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
	[SPECIES_WAILORD] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_NUMEL] = {
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
	[SPECIES_CAMERUPT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_TORKOAL] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SPOINK] = {
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
	[SPECIES_GRUMPIG] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SPINDA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_TRAPINCH] = {
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
	[SPECIES_VIBRAVA] = {
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
	[SPECIES_FLYGON] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_CACNEA] = {
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
	[SPECIES_CACTURNE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SWABLU] = {
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
	[SPECIES_ALTARIA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_ZANGOOSE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SEVIPER] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_LUNATONE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SOLROCK] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_BARBOACH] = {
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
	[SPECIES_WHISCASH] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_CORPHISH] = {
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
	[SPECIES_CRAWDAUNT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_BALTOY] = {
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
	[SPECIES_CLAYDOL] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_LILEEP] = {
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
	[SPECIES_CRADILY] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_ANORITH] = {
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
	[SPECIES_ARMALDO] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_FEEBAS] = {
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
	[SPECIES_MILOTIC] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_CASTFORM] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_KECLEON] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SHUPPET] = {
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
	[SPECIES_BANETTE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_DUSKULL] = {
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
	[SPECIES_DUSCLOPS] = {
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
	[SPECIES_TROPIUS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_CHIMECHO] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_ABSOL] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_WYNAUT] = {
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
	[SPECIES_SNORUNT] = {
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
	[SPECIES_GLALIE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SPHEAL] = {
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
	[SPECIES_SEALEO] = {
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
	[SPECIES_WALREIN] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_CLAMPERL] = {
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
	[SPECIES_HUNTAIL] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_GOREBYSS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_RELICANTH] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_LUVDISC] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_BAGON] = {
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
	[SPECIES_SHELGON] = {
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
	[SPECIES_SALAMENCE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_BELDUM] = {
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
	[SPECIES_METANG] = {
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
	[SPECIES_METAGROSS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_REGIROCK] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_REGICE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_REGISTEEL] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_LATIAS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_LATIOS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_KYOGRE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_GROUDON] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_RAYQUAZA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_JIRACHI] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_DEOXYS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_TURTWIG] = {
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
	[SPECIES_GROTLE] = {
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
	[SPECIES_TORTERRA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_CHIMCHAR] = {
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
	[SPECIES_MONFERNO] = {
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
	[SPECIES_INFERNAPE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_PIPLUP] = {
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
	[SPECIES_PRINPLUP] = {
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
	[SPECIES_EMPOLEON] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_STARLY] = {
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
	[SPECIES_STARAVIA] = {
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
	[SPECIES_STARAPTOR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_BIDOOF] = {
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
	[SPECIES_BIBAREL] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_KRICKETOT] = {
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
	[SPECIES_KRICKETUNE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SHINX] = {
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
	[SPECIES_LUXIO] = {
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
	[SPECIES_LUXRAY] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_BUDEW] = {
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
	[SPECIES_ROSERADE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_CRANIDOS] = {
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
	[SPECIES_RAMPARDOS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SHIELDON] = {
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
	[SPECIES_BASTIODON] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_BURMY] = {
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
	[SPECIES_WORMADAM] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_MOTHIM] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_COMBEE] = {
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
	[SPECIES_VESPIQUEN] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_PACHIRISU] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_BUIZEL] = {
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
	[SPECIES_FLOATZEL] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_CHERUBI] = {
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
	[SPECIES_CHERRIM] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SHELLOS] = {
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
	[SPECIES_GASTRODON] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_AMBIPOM] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_DRIFLOON] = {
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
	[SPECIES_DRIFBLIM] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_BUNEARY] = {
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
	[SPECIES_LOPUNNY] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_MISMAGIUS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_HONCHKROW] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_GLAMEOW] = {
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
	[SPECIES_PURUGLY] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_CHINGLING] = {
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
	[SPECIES_STUNKY] = {
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
	[SPECIES_SKUNTANK] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_BRONZOR] = {
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
	[SPECIES_BRONZONG] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_BONSLY] = {
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
	[SPECIES_MIME_JR] = {
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
	[SPECIES_HAPPINY] = {
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
	[SPECIES_CHATOT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SPIRITOMB] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_GIBLE] = {
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
	[SPECIES_GABITE] = {
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
	[SPECIES_GARCHOMP] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_MUNCHLAX] = {
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
	[SPECIES_RIOLU] = {
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
	[SPECIES_LUCARIO] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_HIPPOPOTAS] = {
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
	[SPECIES_HIPPOWDON] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SKORUPI] = {
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
	[SPECIES_DRAPION] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_CROAGUNK] = {
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
	[SPECIES_TOXICROAK] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_CARNIVINE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_FINNEON] = {
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
	[SPECIES_LUMINEON] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_MANTYKE] = {
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
	[SPECIES_SNOVER] = {
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
	[SPECIES_ABOMASNOW] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_WEAVILE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_MAGNEZONE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_LICKILICKY] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_RHYPERIOR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_TANGROWTH] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_ELECTIVIRE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_MAGMORTAR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_TOGEKISS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_YANMEGA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_LEAFEON] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_GLACEON] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_GLISCOR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_MAMOSWINE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_PORYGONZ] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_GALLADE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_PROBOPASS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_DUSKNOIR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_FROSLASS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_ROTOM] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_UXIE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_MESPRIT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_AZELF] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_DIALGA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_PALKIA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_HEATRAN] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_REGIGIGAS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_GIRATINA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_CRESSELIA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_PHIONE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_MANAPHY] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_DARKRAI] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SHAYMIN] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_ARCEUS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_VICTINI] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SNIVY] = {
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
	[SPECIES_SERVINE] = {
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
	[SPECIES_SERPERIOR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_TEPIG] = {
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
	[SPECIES_PIGNITE] = {
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
	[SPECIES_EMBOAR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_OSHAWOTT] = {
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
	[SPECIES_DEWOTT] = {
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
	[SPECIES_SAMUROTT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_PATRAT] = {
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
	[SPECIES_WATCHOG] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_LILLIPUP] = {
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
	[SPECIES_HERDIER] = {
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
	[SPECIES_STOUTLAND] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_PURRLOIN] = {
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
	[SPECIES_LIEPARD] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_PANSAGE] = {
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
	[SPECIES_SIMISAGE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_PANSEAR] = {
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
	[SPECIES_SIMISEAR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_PANPOUR] = {
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
	[SPECIES_SIMIPOUR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_MUNNA] = {
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
	[SPECIES_MUSHARNA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_PIDOVE] = {
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
	[SPECIES_TRANQUILL] = {
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
	[SPECIES_UNFEZANT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_BLITZLE] = {
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
	[SPECIES_ZEBSTRIKA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_ROGGENROLA] = {
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
	[SPECIES_BOLDORE] = {
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
	[SPECIES_GIGALITH] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_WOOBAT] = {
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
	[SPECIES_SWOOBAT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_DRILBUR] = {
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
	[SPECIES_EXCADRILL] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_AUDINO] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_TIMBURR] = {
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
	[SPECIES_GURDURR] = {
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
	[SPECIES_CONKELDURR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_TYMPOLE] = {
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
	[SPECIES_PALPITOAD] = {
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
	[SPECIES_SEISMITOAD] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_THROH] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SAWK] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SEWADDLE] = {
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
	[SPECIES_SWADLOON] = {
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
	[SPECIES_LEAVANNY] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_VENIPEDE] = {
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
	[SPECIES_WHIRLIPEDE] = {
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
	[SPECIES_SCOLIPEDE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_COTTONEE] = {
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
	[SPECIES_WHIMSICOTT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_PETILIL] = {
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
	[SPECIES_LILLIGANT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_BASCULIN] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SANDILE] = {
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
	[SPECIES_KROKOROK] = {
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
	[SPECIES_KROOKODILE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_DARUMAKA] = {
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
	[SPECIES_DARMANITAN] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_MARACTUS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_DWEBBLE] = {
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
	[SPECIES_CRUSTLE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SCRAGGY] = {
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
	[SPECIES_SCRAFTY] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SIGILYPH] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_YAMASK] = {
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
	[SPECIES_COFAGRIGUS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_TIRTOUGA] = {
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
	[SPECIES_CARRACOSTA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_ARCHEN] = {
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
	[SPECIES_ARCHEOPS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_TRUBBISH] = {
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
	[SPECIES_GARBODOR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_ZORUA] = {
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
	[SPECIES_ZOROARK] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_MINCCINO] = {
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
	[SPECIES_CINCCINO] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_GOTHITA] = {
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
	[SPECIES_GOTHORITA] = {
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
	[SPECIES_GOTHITELLE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SOLOSIS] = {
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
	[SPECIES_DUOSION] = {
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
	[SPECIES_REUNICLUS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_DUCKLETT] = {
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
	[SPECIES_SWANNA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_VANILLITE] = {
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
	[SPECIES_VANILLISH] = {
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
	[SPECIES_VANILLUXE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_DEERLING] = {
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
	[SPECIES_SAWSBUCK] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_EMOLGA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_KARRABLAST] = {
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
	[SPECIES_ESCAVALIER] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_FOONGUS] = {
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
	[SPECIES_AMOONGUSS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_FRILLISH] = {
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
	[SPECIES_JELLICENT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_ALOMOMOLA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_JOLTIK] = {
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
	[SPECIES_GALVANTULA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_FERROSEED] = {
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
	[SPECIES_FERROTHORN] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_KLINK] = {
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
	[SPECIES_KLANG] = {
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
	[SPECIES_KLINKLANG] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_TYNAMO] = {
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
	[SPECIES_EELEKTRIK] = {
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
	[SPECIES_EELEKTROSS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_ELGYEM] = {
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
	[SPECIES_BEHEEYEM] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_LITWICK] = {
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
	[SPECIES_LAMPENT] = {
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
	[SPECIES_CHANDELURE] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_AXEW] = {
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
	[SPECIES_FRAXURE] = {
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
	[SPECIES_HAXORUS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_CUBCHOO] = {
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
	[SPECIES_BEARTIC] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_CRYOGONAL] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SHELMET] = {
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
	[SPECIES_ACCELGOR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_STUNFISK] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_MIENFOO] = {
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
	[SPECIES_MIENSHAO] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_DRUDDIGON] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_GOLETT] = {
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
	[SPECIES_GOLURK] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_PAWNIARD] = {
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
	[SPECIES_BISHARP] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_BOUFFALANT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_RUFFLET] = {
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
	[SPECIES_BRAVIARY] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_VULLABY] = {
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
	[SPECIES_MANDIBUZZ] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_HEATMOR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_DURANT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_DEINO] = {
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
	[SPECIES_ZWEILOUS] = {
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
	[SPECIES_HYDREIGON] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_LARVESTA] = {
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
	[SPECIES_VOLCARONA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_COBALION] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_TERRAKION] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_VIRIZION] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_TORNADUS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_THUNDURUS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_RESHIRAM] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_ZEKROM] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_LANDORUS] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_KYUREM] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_KELDEO] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_MELOETTA] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_GENESECT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_EGG] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_BAD_EGG] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_UFO] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_BRYCENMAN] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_MT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_MT2] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_TRANSPORT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_GIANT_15] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_HUMANOID] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_MONSTER] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_F00] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SPIRIT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_WHITE_DOOR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_BLACK_DOOR] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_PROP_U1] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_PROP_U2] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_PROP_H1] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_PROP_M1] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_PROP_M2] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_PROP_T1] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_PROP_O1] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_PROP_O2] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_PROP_C1] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_PROP_C2] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_PROP_G1] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_PROP_W1] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_PROP_W2] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_PROP_R1] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_PROP_R2] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_PROP_K1] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_UFO_2] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_GIANT_15_2] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_F002] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_BLACK_BELT] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_SMEARGLE_2] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_EGG] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_EGG] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_687] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_688] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_689] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_690] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_691] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_692] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_693] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_694] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_695] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_696] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_697] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_698] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_699] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_700] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_701] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_702] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_703] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_704] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_705] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_706] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_707] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
	},
	[SPECIES_708] = {
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
			.Parameter = 0,
			.TargetSpecies = SPECIES_NONE,
		},
		{
			.Method = 0,
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
