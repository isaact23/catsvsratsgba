#ifndef RAT_H
#define RAT_H

#include <stdint.h>

#include "datatypes/path.h"
#include "datatypes/sprite.h"
#include "gba_types.h"

struct rat {
    struct sprite* sprite;
    u32 init_time;

    // Rat properties
    u8 type; // 0 - default, 1 - fast, 2 - fat, 3 - robot, 4 - demon
    u16 speed; // Auto-assigned based on type
    u16 tile_id;
    u8 fps;
    s16 hp;

    // Rat location
    const struct path* path;
    u16 x;
    u16 y;
};

#endif
