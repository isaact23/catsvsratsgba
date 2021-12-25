#ifndef DATA_ROUNDS_H
#define DATA_ROUNDS_H

#include <stdint.h>

struct rat_spawn_entry {
    uint32_t spawn_time; // Counts up every frame (60 FPS)
    uint8_t rat_type;
    uint8_t spawn_path;
};

extern const struct rat_spawn_entry ROUND0 [];

#endif
