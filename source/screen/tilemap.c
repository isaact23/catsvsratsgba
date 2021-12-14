// Set up background tilemap

#include "screen/tilemap.h"

volatile uint16_t* bg_palette = (volatile uint16_t*) 0x5000000;
volatile uint16_t* vram       = (volatile uint16_t*) 0x6000000;

// Return pointer to one of 4 character blocks
volatile uint16_t* char_block(uint16_t block) {
    return (volatile uint16_t*) (0x6000000 + (block * 0x800));
}

// Return pointer to one of 32 screen blocks
volatile uint16_t* screen_block(uint16_t block) {
    return (volatile uint16_t*) (0x6000000 + (block * 0x800));
}

// Set up tilemap
void tilemap_init() {
    
    // Load palette into palette memory
    for (int i = 0; i < IMAGE_TILES_PALETTE_SIZE; i++) {
        bg_palette[i] = IMAGE_TILES_PALETTE[i];
    }

    // Load image into char block 0, two bytes at a time
    volatile uint16_t* dest = char_block(0);
    uint16_t* image = (uint16_t*) IMAGE_TILES_DATA;
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
