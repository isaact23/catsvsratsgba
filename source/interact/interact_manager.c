#include "interact/interact_manager.h"

// Initialize interact manager
void interact_manager_init(
    bool (*game_manager_next_round)(),
    struct sprite* (*sprite_manager_new_sprite)(),
    bool (*cat_manager_add_cat)(u8 x, u8 y, enum cat_type type),
    bool (*cat_manager_remove_cat)(u8 x, u8 y),
    u16 (*cat_manager_get_price)(enum cat_type type),
    void (*game_manager_add_money)(s32 amount),
    s32 (*game_manager_get_money)(),
    u16 (*cat_manager_get_tile)(enum cat_type type))
{
    grid_selector_init(game_manager_next_round, sprite_manager_new_sprite, cat_manager_add_cat,
    cat_manager_remove_cat, cat_manager_get_price, game_manager_add_money, game_manager_get_money,
    cat_manager_get_tile);
}

// Update iteract manager
void interact_manager_update() {
    // Get input
    scanKeys();
    u16 pressedKeys = keysDown();

    grid_selector_update(pressedKeys);
}
