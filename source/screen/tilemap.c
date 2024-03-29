// Set up background tilemap

#include "screen/tilemap.h"

// Set up tilemap
void tilemap_init() {
    
    // Load palette into palette memory
    for (int i = 0; i < IMAGE_TILES_PALETTE_SIZE; i++) { // 132 bytes fits in palette (1 kilobyte)
        BG_PALETTE[i] = IMAGE_TILES_PALETTE[i];
    }

    // Load image into char block 0, two bytes at a time
    vu16* dest = CHAR_BASE_BLOCK(0);
    u16* image = (u16*) IMAGE_TILES_DATA;
    for (int i = 0; i < IMAGE_TILES_WIDTH * IMAGE_TILES_HEIGHT * 32; i++) { // 19200 bytes fits in 2 char block (16 kilobytes)
        dest[i] = image[i];
    }

    // Load tile data into screen block 16
    dest = SCREEN_BASE_BLOCK(16);
    for (int i = 0; i < TILEMAP_WIDTH * TILEMAP_HEIGHT; i++) { // 1080 bytes fits in 1 screen block (2 kilobytes)
        dest[i] = TILEMAP[i];
    }

    // Load tile data for win gui into screen block 17
    dest = SCREEN_BASE_BLOCK(17);
    for (int i = 0; i < TILEMAP_WIN_WIDTH * TILEMAP_WIN_HEIGHT; i++) { // 2048 bytes fits in 1 screen block (2 kilobytes)
        dest[i] = TILEMAP_WIN[i];
    }
}
