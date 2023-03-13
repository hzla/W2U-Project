#ifndef __EVOLUTIONS_H
#define __EVOLUTIONS_H

#include "swan/swantypes.h"

typedef struct {
    uint16_t Method;
    uint16_t Parameter;
    uint16_t TargetSpecies;
} EvoEntry;

typedef struct {
    EvoEntry Entries[0x7];
} EVOLUTION_DATA;

#endif
