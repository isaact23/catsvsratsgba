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
    if (IMAGE_TILES_WIDTH * IMAGE_TILES_HEIGHT > 250) {
        exit(1);
    }
    for (int i = 0; i < IMAGE_TILES_WIDTH * IMAGE_TILES_HEIGHT * 32; i++) { // 5760 bytes fits in 1 char block (16 kilobytes)
        dest[i] = image[i];
    }

    // Load tile data into screen block 16
    dest = SCREEN_BASE_BLOCK(16);
    for (int i = 0; i < TILEMAP_WIDTH * TILEMAP_HEIGHT; i++) { // 640 bytes fits in 1 screen block (2 kilobytes)
        dest[i] = TILEMAP[i];
    }
}
