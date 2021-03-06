#include "sprites/sprite_manager.h"

// Sprites
struct sprite sprite_array [SPRITE_LIMIT];
u8 sprite_count = 0;

// Initialize sprites
void sprite_manager_init() {
    // Move all unused sprites off-screen
    for (u32 i = 0; i < SPRITE_LIMIT; i++) {
        sprite_array[i].attr1 = 160;
        sprite_array[i].attr2 = 240;
        sprite_array[i].attr3 = 0;
        sprite_array[i].dummy = 0;
    }

    // Copy sprite palette to sprite palette memory
    dmaCopy(IMAGE_SPRITES_PALETTE, (void*) SPRITE_PALETTE_MEMORY, IMAGE_SPRITES_PALETTE_SIZE * 2);

    // Copy sprite into sprite image memory
    u16* sprite16 = (u16*) IMAGE_SPRITES_DATA;
    dmaCopy(sprite16, (void*) SPRITE_IMAGE_MEMORY, IMAGE_SPRITES_WIDTH * IMAGE_SPRITES_HEIGHT * 64);
}

// Update sprites in memory every vblank
void sprite_manager_update() {
    // Update sprite attributes
    dmaCopy(sprite_array, (void*) OAM, 8 * SPRITE_LIMIT);
}

// Return a pointer to a new sprite, or NULL if unavailable.
struct sprite* sprite_manager_new_sprite() {
    if (sprite_count >= SPRITE_LIMIT) {
        return NULL;
    }
    struct sprite* new_sprite = &sprite_array[sprite_count];

    // Zero out attributes and return pointer to sprite
    new_sprite -> attr1 = 0;
    new_sprite -> attr2 = 0;
    new_sprite -> attr3 = 0;
    sprite_count++;
    return new_sprite;
}
