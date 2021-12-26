#ifndef ROUND_H
#define ROUND_H

#include "datatypes/path.h"

struct rat_spawn_entry {
    uint32_t spawn_time; // Counts up every frame (60 FPS)
    uint8_t rat_type;
    uint8_t path_id;
};

struct round {
    uint16_t round_id;
    uint16_t rat_count;
    struct rat_spawn_entry rat_spawn_entries [];
};

#endif
