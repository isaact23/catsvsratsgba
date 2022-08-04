#ifndef RAT_H
#define RAT_H

#include <stdint.h>

#include "datatypes/path.h"
#include "datatypes/sprite.h"
#include "gba_types.h"

enum rat_type {
    RAT_NORMAL = 0,
    RAT_FAST,
    RAT_FAT,
    RAT_ROBOT,
    RAT_DEMON
};

struct rat {
    struct sprite* sprite;
    struct sprite* hp_bar;
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
    s16 hp_max;
    s8 eating; // -1 for not eating, or 0, 1, 2 or 3 for eating location
    s16 time_until_next_bite;
};

#endif
