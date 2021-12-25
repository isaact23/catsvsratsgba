#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include <time.h>
#include <stdint.h>
#include <stdlib.h>

#include "data/data_path.h"
#include "data/data_rounds.h"
#include "data/image_rat_default_walk.h"

// Statically allocate memory for objects
#define SPRITE_LIMIT 128
#define RAT_LIMIT 30

struct sprite {
    uint16_t attr1;
    uint16_t attr2;
    uint16_t attr3;
};

struct rat {
    struct sprite* sprite;
    uint32_t init_time;

    // Path properties
    uint8_t path_id;
    uint8_t path_length;
    const int8_t* path_address;

    // Rat properties
    uint8_t type; // 0 - default, 1 - fast, 2 - fat, 3 - robot, 4 - demon
    uint16_t slowness; // Auto-assigned based on type
    uint16_t x;
    uint16_t y;
};

// Initialize sprites
void sprite_manager_init();

// Start a round
void sprite_manager_start_round(uint16_t round);

// Update sprites in memory during vblank
void sprite_manager_update();

// Return a pointer to a new sprite
struct sprite* sprite_manager_new_sprite();

// Add a new rat
void sprite_manager_add_rat();

// Update rats
void sprite_manager_update_rats();

#endif
