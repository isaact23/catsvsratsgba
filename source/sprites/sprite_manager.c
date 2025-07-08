#include "sprites/sprite_manager.h"

// Sprites
struct sprite sprite_array [SPRITE_LIMIT];
bool sprite_array_occupied [SPRITE_LIMIT];
u8 sprite_count = 0;

// Initialize sprites
void sprite_manager_init() {
    // Move all unused sprites off-screen
    for (u32 i = 0; i < SPRITE_LIMIT; i++) {
        sprite_array[i].attr0 = 160;
        sprite_array[i].attr1 = 240;
        sprite_array[i].attr2 = 0;
        sprite_array[i].dummy = 0;
        sprite_array_occupied[i] = false;
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

    // If there are no more spaces for sprites, return NULL.
    if (sprite_count >= SPRITE_LIMIT) {
        return NULL;
    }

    // Find an open spot for a new sprite.
    u32 index = 0;
    struct sprite* new_sprite;
    while (sprite_array_occupied[index] && index < SPRITE_LIMIT) {
        index++;
    }
    if (index >= SPRITE_LIMIT) { // No spot found.
        return NULL;
    } else {
        new_sprite = &sprite_array[index];
        sprite_array_occupied[index] = true;
    }

    // Zero out attributes and return pointer to sprite
    new_sprite -> attr0 = 0;
    new_sprite -> attr1 = 0;
    new_sprite -> attr2 = 0;
    sprite_count++;
    return new_sprite;
}

// Delete a sprite. Return true if successful.
bool sprite_manager_remove_sprite(struct sprite* sprite) {

    // If there are no sprites to delete, we cannot delete a sprite.
    if (sprite_count < 1) {
        return false;
    }

    // Move sprite off-screen
    sprite -> attr0 = 160;
    sprite -> attr1 = 240;

    // Free up space for new sprites
    u32 index = sprite - sprite_array; // Use pointer arithmetic to get sprite index
    sprite_array_occupied[index] = false;
    sprite_count--;
    return true;
}
