#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include <stdint.h>
#include <stdlib.h>

#include "data/image_rat_default_walk.h"

// Statically allocate memory for objects
#define SPRITE_LIMIT 128
#define RAT_LIMIT 30

struct Sprite {
    uint16_t attr1;
    uint16_t attr2;
    uint16_t attr3;
};

struct Rat {
    struct Sprite* sprite;
    uint8_t type; // 0 - default, 1 - fast, 2 - fat, 3 - robot, 4 - demon
    uint32_t progress;
    uint16_t x;
    uint16_t y;
};

// Initialize sprites
void sprite_manager_init();

// Update sprites in memory during vblank
void sprite_manager_update();

// Return a pointer to a new sprite
struct Sprite* sprite_manager_new_sprite();

// Add a new rat
void sprite_manager_add_rat();

// Update rats
void sprite_manager_update_rats();

#endif
