#include "interact/interact_manager.h"

// Initialize interact manager
void interact_manager_init() {
    grid_selector_init();
}

// Update iteract manager
void interact_manager_update() {
    // Get input
    scanKeys();
    u16 pressedKeys = keysDown();

    grid_selector_update(pressedKeys);
}
