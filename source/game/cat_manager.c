#include "game/cat_manager.h"

// Cats
struct cat_storage cat_storage;

// Initialize cat manager
void cat_manager_init() {
    cat_storage = cat_storage_new();

    cat_storage_add_cat(&cat_storage, 0, 0, CAT_NORMAL);
    cat_storage_add_cat(&cat_storage, 1, 2, CAT_WIZARD);
}

// Update cat manager
void cat_manager_update(u32 time_elapsed) {

    // Iterate through cats
    for (u8 i = 0; i < cat_storage.cat_count; i++) {
        struct cat cat = cat_storage.cat_array[i];
        cat.time_elapsed = cat.time_elapsed + 1;

        // Determine tile
        u16 tile = cat.base_tile + (((cat.time_elapsed / cat.time_per_frame) % 2) * 4);

        // Update cat sprite
        struct sprite* sprite = cat.sprite;
        sprite -> attr1 =
            (cat.pixel_y & 0xff) | // y position
            (1 << 13) | // 256 colors
            (0 << 14);  // Shape
        sprite -> attr2 =
            (cat.pixel_x & 0x1ff) | // x position
            (1 << 14);  // Size
        sprite -> attr3 =
            (tile & 0x3ff); // Tile index
    }
}

// Add a cat - return true if successful.
bool cat_manager_add_cat(u8 x, u8 y, enum cat_type type) {
    return cat_storage_add_cat(&cat_storage, x, y, type);
}

// Remove a cat - return true if successful.
bool cat_manager_remove_cat(u8 x, u8 y) {
    return cat_storage_remove_cat(&cat_storage, x, y);
}

// Get tile corresponding to cat type
u16 cat_manager_get_tile(enum cat_type type) {
    switch (type) {
        case CAT_ARCHER: { return TILE_CAT_ARCHER; }
        case CAT_BOMB:   { return TILE_CAT_BOMB;   }
        case CAT_WIZARD: { return TILE_CAT_WIZARD; }
        default:         { return TILE_CAT_NORMAL; }
    }
}
