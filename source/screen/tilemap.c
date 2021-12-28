// Set up background tilemap

#include "screen/tilemap.h"

vu16* bg_palette = (vu16*) 0x5000000;
vu16* vram       = (vu16*) 0x6000000;

// Return pointer to one of 4 character blocks
vu16* char_block(u16 block) {
    return (vu16*) (0x6000000 + (block * 0x800));
}

// Return pointer to one of 32 screen blocks
vu16* screen_block(u16 block) {
    return (vu16*) (0x6000000 + (block * 0x800));
}

// Set up tilemap
void tilemap_init() {
    
    // Load palette into palette memory
    for (int i = 0; i < IMAGE_TILES_PALETTE_SIZE; i++) {
        bg_palette[i] = IMAGE_TILES_PALETTE[i];
    }

    // Load image into char block 0, two bytes at a time
    vu16* dest = char_block(0);
    u16* image = (u16*) IMAGE_TILES_DATA;
    if (IMAGE_TILES_WIDTH * IMAGE_TILES_HEIGHT > 250) {
        exit(1);
    }
    for (int i = 0; i < IMAGE_TILES_WIDTH * IMAGE_TILES_HEIGHT * 32; i++) {
        dest[i] = image[i];
    }

    // Load tile data into screen block 16
    dest = screen_block(16);
    for (int i = 0; i < TILEMAP_WIDTH * TILEMAP_HEIGHT; i++) {
        dest[i] = TILEMAP[i];
    }
}
