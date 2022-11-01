#ifndef GRID_SELECT_H
#define GRID_SELECT_H

#define SELECTOR_TILE_1 216
#define SELECTOR_TILE_2 220

#define TILE_SIZE 16
#define ICON_X_OFFSET 210
#define CAT_ICON_SIZE 27
#define CAT_ICON_Y_OFFSET 2
#define BUTTON_SIZE 14
#define BUTTON_OFFSET 130

#include "datatypes/cat.h"
#include "datatypes/sprite.h"

#include "gba_input.h"
#include "gba_types.h"

// Initialize grid selector
void grid_selector_init(
    struct sprite* (*sprite_manager_new_sprite)(),
    bool (*cat_manager_add_cat)(u8 x, u8 y, enum cat_type type),
    bool (*cat_manager_remove_cat)(u8 x, u8 y),
    u16 (*cat_manager_get_price)(enum cat_type type),
    void (*game_manager_add_money)(s32 amount),
    s32 (*game_manager_get_money)(),
    u16 (*cat_manager_get_tile)(enum cat_type type)
);

// Update grid selector every frame
void grid_selector_update(u16 pressedKeys);

// Enable selection mode
void grid_selector_enable_select();

// Disable selection mode
void grid_selector_disable_select();

#endif
