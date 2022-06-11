#ifndef CAT_H
#define CAT_H

#include "gba_types.h"

enum cat_type {
    normal = 0,
    archer,
    bomb,
    wizard
};

struct cat {
    struct sprite* sprite;
    u32 last_attack_time;

    // Cat long-term properties
    u8 x;
    u8 y;

    // Cat status
    u16 tile_id;
};

#endif
