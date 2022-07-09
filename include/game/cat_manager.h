#ifndef CAT_MANAGER_H
#define CAT_MANAGER_H

#include <stdlib.h>
#include "datatypes/cat.h"
#include "game/cat_storage.h"
#include "sprites/sprite_manager.h"
#include "gba_types.h"

#define TILE_CAT_NORMAL 128
#define TILE_CAT_ARCHER 256
#define TILE_CAT_BOMB 192
#define TILE_CAT_WIZARD 320

// Initialize cat manager
void cat_manager_init();

// Update cat manager
void cat_manager_update();

// Add a cat - return true if successful.
bool cat_manager_add_cat(u8 x, u8 y, enum cat_type type);

// Remove a cat - return true if successful.
bool cat_manager_remove_cat(u8 x, u8 y);

// Get tile corresponding to cat type
u16 cat_manager_get_tile(enum cat_type type);

#endif
