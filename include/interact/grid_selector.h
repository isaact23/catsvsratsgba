#ifndef GRID_SELECT_H
#define GRID_SELECT_H

#define SELECTOR_TILE_1 216
#define SELECTOR_TILE_2 220

#include "datatypes/sprite.h"
#include "sprites/sprite_manager.h"
#include "gba_types.h"

// Initialize grid selector
void grid_selector_init();

// Update grid selector every frame
void grid_selector_update();

#endif
