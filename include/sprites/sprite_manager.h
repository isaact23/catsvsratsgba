#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include <time.h>
#include <stdint.h>
#include <stdlib.h>

#include "data/data_path.h"
#include "data/data_rounds.h"
#include "data/image_sprites.h"
#include "datatypes/path.h"
#include "datatypes/rat.h"
#include "datatypes/sprite.h"
#include "gba_dma.h"
#include "gba_sprites.h"
#include "gba_types.h"

#define SPRITE_PALETTE_MEMORY 0x5000200
#define SPRITE_IMAGE_MEMORY 0x6010000

// Statically allocate memory for objects
#define SPRITE_LIMIT 128
#define RAT_LIMIT 30

// Initialize sprites
void sprite_manager_init();

// Start a round
void sprite_manager_start_round(u16 round);

// Update sprites in memory during vblank
void sprite_manager_update();

// Return a pointer to a new sprite
struct sprite* sprite_manager_new_sprite();

// If enough time has elapsed, spawn a new rat
void sprite_manager_spawn_rats();

// Update rats
void sprite_manager_update_rats();

#endif
