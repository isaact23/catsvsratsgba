#ifndef RAT_MANAGER_H
#define RAT_MANAGER_H

#include <stdint.h>
#include <stdlib.h>

#include "data/image_rat_default_walk.h"

#define RAT_LIMIT 30 // Statically allocate maximum memory for rats

struct Rat {
    uint8_t type; // 0 - default, 1 - fast, 2 - fat, 3 - robot, 4 - demon
    uint32_t progress;
    uint16_t x;
    uint16_t y;
};

// Add a new rat
void rat_manager_add_rat(struct Rat rat);

// Render all rats
void rat_manager_render();

#endif
