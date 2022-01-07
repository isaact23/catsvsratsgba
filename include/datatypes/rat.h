#ifndef RAT_H
#define RAT_H

#include <stdint.h>

#include "datatypes/path.h"
#include "datatypes/sprite.h"
#include "gba_types.h"

enum rat_type {
    DEFAULT = 0,
    FAST,
    FAT,
    ROBOT,
    DEMON
};

struct rat {
    struct sprite* sprite;
    u32 init_time;

    // Rat long-term properties
    enum rat_type type;
    u16 speed; // Auto-assigned based on type
    u8 fps; // Sprite frames per second
    u8 hps; // Health damage per second while eating cheese

    // Rat status
    const struct path* path;
    u16 tile_id;
    u16 x;
    u16 y;
    s16 hp;
    s8 eating; // -1 for not eating, or 0, 1, 2 or 3 for eating location
};

#endif
