#ifndef ROUND_H
#define ROUND_H

#include "datatypes/path.h"
#include "datatypes/rat.h"
#include "gba_types.h"

struct rat_spawn_entry {
    u32 spawn_time; // Counts up every frame (60 FPS)
    enum rat_type rat_type;
    u8 path_id;
};

struct round {
    u16 round_id;
    u16 rat_count;
    struct rat_spawn_entry rat_spawn_entries [];
};

#endif
