#ifndef RAT_H
#define RAT_H

#include <stdint.h>

#include "datatypes/path.h"
#include "datatypes/sprite.h"

struct rat {
    struct sprite* sprite;
    uint32_t init_time;

    // Rat properties
    uint8_t type; // 0 - default, 1 - fast, 2 - fat, 3 - robot, 4 - demon
    uint16_t slowness; // Auto-assigned based on type

    // Rat location
    const struct path* path;
    uint16_t x;
    uint16_t y;
};

#endif
