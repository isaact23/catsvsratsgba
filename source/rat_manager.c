#include "rat_manager.h"

struct Rat ratArray[RAT_LIMIT];
uint32_t ratCount = 0;

volatile uint16_t* sprite_palette    = (volatile uint16_t*) 0x5000200;
volatile uint16_t* sprite_image_vram = (volatile uint16_t*) 0x6010000;
volatile uint16_t* sprite_attributes = (volatile uint16_t*) 0x7000000;

// Add a new rat
void rat_manager_add_rat(struct Rat rat) {
    if (ratCount >= RAT_LIMIT) {
        exit(1);
    }
    ratArray[ratCount] = rat;
    ratCount++;
}

// Render all rats
void rat_manager_render() {
    // TODO: Calculate x/y positions

    // Copy sprite palette to sprite palette memory
    for (uint32_t i = 0; i < IMAGE_RAT_DEFAULT_WALK_PALETTE_SIZE; i++) {
        sprite_palette[i] = IMAGE_RAT_DEFAULT_WALK_PALETTE[i];
    }

    // Copy sprite into sprite image memory
    for (uint32_t i = 0; i < IMAGE_RAT_DEFAULT_WALK_WIDTH * IMAGE_RAT_DEFAULT_WALK_HEIGHT * 64; i++) {
        sprite_image_vram[i] = IMAGE_RAT_DEFAULT_WALK_DATA[i];
    }

    // Update sprite attributes
    for (uint32_t i = 0; i < ratCount; i++) {
        struct Rat rat = ratArray[i];
        sprite_attributes[i * 4] =
            (rat.y)   |
            (1 << 13) | // 256 colors
            (0 << 14);  // Square shape
        sprite_attributes[i * 4 + 1] =
            (rat.x)   |
            (1 << 14);  // 16x16 sprite size (2x2 tiles)
        sprite_attributes[i * 4 + 2] =
            0; // Tile index
    }
}
