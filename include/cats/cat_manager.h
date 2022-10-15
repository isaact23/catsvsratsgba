#ifndef CAT_MANAGER_H
#define CAT_MANAGER_H

#include <stdlib.h>
#include "datatypes/cat.h"
#include "cats/cat_storage.h"
#include "cats/projectile_manager.h"
#include "gba_types.h"

#define TILE_CAT_NORMAL 128
#define TILE_CAT_ARCHER 256
#define TILE_CAT_BOMB 192
#define TILE_CAT_WIZARD 320

#define CAT_NORMAL_PRICE 10
#define CAT_ARCHER_PRICE 20
#define CAT_BOMB_PRICE 30
#define CAT_WIZARD_PRICE 40

// Initialize cat manager
void cat_manager_init(struct sprite* (*sprite_manager_new_sprite)());

// Update cat manager
void cat_manager_update();

// Add a cat - return true if successful.
bool cat_manager_add_cat(u8 x, u8 y, enum cat_type type);

// Remove a cat - return true if successful.
bool cat_manager_remove_cat(u8 x, u8 y);

// Get the price of a cat type
u16 cat_manager_get_price(enum cat_type type);

// Get tile corresponding to cat type
u16 cat_manager_get_tile(enum cat_type type);

// Delete a sprite. Return true if successful.
bool cat_manager_remove_sprite(struct sprite* sprite);

#endif
