#ifndef INTERACT_MANAGER_H
#define INTERACT_MANAGER_H

#include "gba_input.h"

#include "interact/grid_selector.h"

// Initialize interact manager
void interact_manager_init(
    const enum game_state* const state,
    struct sprite* (*sprite_manager_new_sprite)(),
    bool (*cat_manager_add_cat)(u8 x, u8 y, enum cat_type type),
    bool (*cat_manager_remove_cat)(u8 x, u8 y),
    u16 (*cat_manager_get_price)(enum cat_type type),
    void (*game_manager_add_money)(s32 amount),
    s32 (*game_manager_get_money)(),
    u16 (*cat_manager_get_tile)(enum cat_type type)
);

// Update iteract manager
void interact_manager_update();

#endif
