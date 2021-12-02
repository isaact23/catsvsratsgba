#include "main.h"

volatile u16* dispcnt = (volatile u16*) 0x4000000;
volatile u16* bg0cnt  = (volatile u16*) 0x4000008;
volatile u16* palette = (volatile u16*) 0x5000000;
volatile u16* vram    = (volatile u16*) 0x6000000;

// Return pointer to one of 4 character blocks
volatile u16* char_block(u16 block) {
    return (volatile u16*) (0x6000000 + (block * 0x800));
}

// Return pointer to one of 32 screen blocks
volatile u16* screen_block(u16 block) {
    return (volatile u16*) (0x6000000 + (block * 0x800));
}

int main() {
    
    // Load palette into palette memory
    for (int i = 0; i < TILES25_PALETTE_SIZE; i++) {
        palette[i] = TILES25_PALETTE[i];
    }

    // Load image into char block 0, two bytes at a time
    volatile u16* dest = char_block(0);
    u16* image = (u16*) TILES25_IMAGE;
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


    while (1) {}
}