#include "screen/screen_manager.h"

volatile uint16_t* dispcnt = (volatile uint16_t*) 0x4000000;
volatile uint16_t* bg0cnt  = (volatile uint16_t*) 0x4000008;

// Initialize the screen.
void screen_manager_init() {
    // Set up display control
    *dispcnt =
        (0 << 0)  | // Display mode 0
        (0 << 6)  | // 1 for 1D sprite mode, 0 for 2D sprite mode
        (1 << 8)  | // Enable background 0
        (1 << 12);  // Screen display OBJ

    // Set up background 0
    *bg0cnt = (1 << 7)  | // 0 is 16 colors, 1 is 256
              (16 << 8) | // Tile data stored in screen block 16
              (1 << 13) | // Enable wrapping
              (0 << 14);  // Background size, 0 is 256x256 (32x32 tiles)

    // Initialize tilemap
    tilemap_init();
}