#include "interact/grid_selector.h"

struct sprite* cursor;

// Initialize grid selector
void grid_selector_init() {
    cursor = sprite_manager_new_sprite();
}

// Update grid selector every frame
void grid_selector_update() {
    cursor -> attr1 =
        (20 & 0xff) | // y position
        (1 << 13) | // 256 colors
        (0 << 14);  // Shape
    cursor -> attr2 =
        (20 & 0x1ff) | // x position
        (1 << 14);  // Size
    cursor -> attr3 =
        (SELECTOR_TILE_2 & 0x3ff) | // Tile index
        (1 << 12);  // Priority
}
