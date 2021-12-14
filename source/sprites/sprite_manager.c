#include "sprites/sprite_manager.h"

volatile uint16_t* sprite_palette    = (volatile uint16_t*) 0x5000200;
volatile uint16_t* sprite_image_vram = (volatile uint16_t*) 0x6010000;
volatile uint16_t* sprite_attributes = (volatile uint16_t*) 0x7000000;

struct Sprite sprites [SPRITE_LIMIT];
uint32_t spriteCount = 0;

struct Rat ratArray[RAT_LIMIT];
uint32_t ratCount = 0;

// Initialize sprites
void sprite_manager_init() {

    // Move all unused sprites off-screen
    for (uint32_t i = 1; i < SPRITE_LIMIT; i++) {
        sprites[i].attr1 = 240;
    }

    // Copy sprite palette to sprite palette memory
    for (uint32_t i = 0; i < IMAGE_RAT_DEFAULT_WALK_PALETTE_SIZE; i++) {
        sprite_palette[i] = IMAGE_RAT_DEFAULT_WALK_PALETTE[i];
    }

    // Copy sprite into sprite image memory
    uint16_t* sprite16 = (uint16_t*) IMAGE_RAT_DEFAULT_WALK_DATA;
    for (uint32_t i = 0; i < IMAGE_RAT_DEFAULT_WALK_WIDTH * IMAGE_RAT_DEFAULT_WALK_HEIGHT * 32; i++) {
        sprite_image_vram[i] = sprite16[i];
    }

    sprite_manager_update();
}

// Update sprites in memory during vblank
void sprite_manager_update() {

    // Update sprite attributes
    for (uint32_t i = 0; i < SPRITE_LIMIT; i++) {
        struct Sprite sprite = sprites[i];
        sprite_attributes[i * 4] = sprite.attr1;
        sprite_attributes[i * 4 + 1] = sprite.attr2;
        sprite_attributes[i * 4 + 2] = sprite.attr3;
    }
}

// Return a pointer to a new sprite
struct Sprite* sprite_manager_new_sprite() {
    if (spriteCount >= SPRITE_LIMIT) {
        exit(1);
    }
    struct Sprite* newSprite = &sprites[spriteCount];
    newSprite -> attr1 = 0;
    newSprite -> attr2 = 0;
    newSprite -> attr3 = 0;
    spriteCount++;
    return newSprite;
}

// Add a new rat
void sprite_manager_add_rat() {
    if (ratCount >= RAT_LIMIT) {
        exit(1);
    }
    struct Rat newRat;
    newRat.sprite = sprite_manager_new_sprite();
    newRat.type = 0;
    newRat.progress = 0;
    newRat.x = 25;
    newRat.y = 25;
    ratArray[ratCount] = newRat;
    ratCount++;
}

// Update rats
void sprite_manager_update_rats() {
    // Send rat data to sprite attributes
    for (uint32_t i = 0; i < ratCount; i++) {
        struct Rat rat = ratArray[i];
        struct Sprite* sprite = rat.sprite;
        sprite -> attr1 =
            (rat.y)   |
            (1 << 13) | // 256 colors
            (0 << 14);  // Shape
        sprite -> attr2 =
            (rat.x)   |
            (1 << 14);  // Size
        sprite -> attr3 =
            0         | // Tile index
            (1 << 12);  // Priority */
    }
}