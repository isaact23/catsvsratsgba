// Set up background tilemap

#include "tilemap.h"

volatile uint16_t* dispcnt = (volatile uint16_t*) 0x4000000;
volatile uint16_t* bg0cnt  = (volatile uint16_t*) 0x4000008;
volatile uint16_t* palette = (volatile uint16_t*) 0x5000000;
volatile uint16_t* vram    = (volatile uint16_t*) 0x6000000;

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
    for (int i = 0; i < TILES25_PALETTE_SIZE; i++) {
        palette[i] = TILES25_PALETTE[i];
    }

    // Load image into char block 0, two bytes at a time
    volatile uint16_t* dest = char_block(0);
    uint16_t* image = (uint16_t*) TILES25_IMAGE;
    if (TILES25_WIDTH * TILES25_HEIGHT > 16000) {
        exit(-1);
    }
    for (int i = 0; i < ((TILES25_WIDTH * TILES25_HEIGHT) / 2); i++) {
        dest[i] = image[i];
    }

    // Load tile data into screen block 16
    dest = screen_block(16);
    for (int i = 0; i < (TILEMAP_WIDTH * TILEMAP_HEIGHT); i++) {
        dest[i] = TILEMAP[i];
    }

    *dispcnt = 0x100; // Display mode 0; enable background 0

    *bg0cnt = (1 << 7)  | // 0 is 16 colors, 1 is 256
              (16 << 8) | // Tile data stored in screen block 16
              (1 << 13) | // Enable wrapping
              (0 << 14);  // Background size, 0 is 256x256 (32x32 tiles)
}