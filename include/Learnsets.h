#ifndef __LEARNSET_H
#define __LEARNSET_H

#include "swan/swantypes.h"

#define LEVEL_UP_MOVE(MOVE, LEVEL) ((MOVE << 0x10) | LEVEL)
#define LEVEL_UP_END 0xFFFFFFFF
struct LearnsetEntry {
    uint16_t Move;
    uint16_t Level;
};
typedef struct {
    LearnsetEntry Entries[0x20];
} LEARNSET_DATA;


#endif
