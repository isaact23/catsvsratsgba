#include "interact/interact_manager.h"

// Initialize interact manager
void interact_manager_init(struct sprite* (*sprite_manager_new_sprite)()) {
    grid_selector_init(sprite_manager_new_sprite);
}

// Update iteract manager
void interact_manager_update() {
    // Get input
    scanKeys();
    u16 pressedKeys = keysDown();

    grid_selector_update(pressedKeys);
}
