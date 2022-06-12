#include "game/cat_manager.h"

// Cats
struct cat_storage cat_storage;

// Initialize cat manager
void cat_manager_init() {
    cat_storage = cat_storage_new();

    cat_storage_add_cat(&cat_storage, 0, 0, normal);
    cat_storage_add_cat(&cat_storage, 1, 1, wizard);
}

// Update cat manager
void cat_manager_update(u32 time_elapsed) {

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
        case archer: { return TILE_CAT_ARCHER; }
        case bomb:   { return TILE_CAT_BOMB;   }
        case wizard: { return TILE_CAT_WIZARD; }
        default:     { return TILE_CAT_NORMAL; }
    }
}
