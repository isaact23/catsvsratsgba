#include "screen/screen_manager.h"

// Initialize the screen.
void screen_manager_init(struct sprite* (*sprite_manager_new_sprite)()) {
    // Set up display control
    REG_DISPCNT =
        (0 << 0)  | // Display mode 0
        (0 << 6)  | // 1 for 1D sprite mode, 0 for 2D sprite mode
        (1 << 8)  | // Enable background 0
        (1 << 9)  | // Enable background 1
        (1 << 12);  // Screen display OBJ

    // Set up background 0
    REG_BG0CNT = (3 << 0)   |  // Priority (3 is lowest)
                 (1 << 7)   |  // 0 is 16 colors, 1 is 256
                 (16 << 8)  |  // Tile data stored in screen block 16
                 (1 << 13)  |  // Enable wrapping
                 (0 << 14);    // Background size, 0 is 256x256 (32x32 tiles)

    // Set up background 1 (win/lose GUI)
    REG_BG1CNT = (0 << 0)  | // Priority (0 is highest)
                 (1 << 7)  | // 256 colors
                 (17 << 8) | // Screen block 17 tile data
                 (0 << 13) | // Disable wrapping
                 (0 << 14);  // 32x32 tiles

    // Initialize tilemap
    tilemap_init();

    // Initialize text
    text_manager_init(sprite_manager_new_sprite);
}

// Update the screen.
void screen_manager_update(s32 health, s32 money) {
    text_manager_update(health, money);
}

// Display win GUI.
void screen_manager_win_gui() {

}

// Display loss GUI.
void screen_manager_lose_gui() {

}
