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
#include "cats/cat_manager.h"
#include "rats/rat_manager.h"

#include "gba_dma.h"
#include "gba_sprites.h"
#include "gba_types.h"

#define SPRITE_PALETTE_MEMORY 0x5000200
#define SPRITE_IMAGE_MEMORY 0x6010000

#define SPRITE_LIMIT 128

// Initialize sprites
void sprite_manager_init();

// Update sprites in memory during vblank
void sprite_manager_update();

// Return a pointer to a new sprite, or NULL if unavailable.
struct sprite* sprite_manager_new_sprite();

// Delete a sprite. Return true if successful.
bool sprite_manager_delete_sprite(struct sprite* sprite);

#endif
