#ifndef CAT_H
#define CAT_H

#include "gba_types.h"

enum cat_type {
    CAT_NORMAL = 0,
    CAT_ARCHER,
    CAT_BOMB,
    CAT_WIZARD
};

struct cat {
    struct sprite* sprite;
    bool attacking;
    u32 time_elapsed;
    u32 time_since_last_fire;

    // Cat long-term properties
    enum cat_type type;
    u16 attack_range; // Stored in pixels
    u16 frames_per_sprite;
    u16 frames_per_fire;
    u16 base_tile;
    u8 grid_x;
    u8 grid_y;
    u8 pixel_x;
    u8 pixel_y;
};

#endif
