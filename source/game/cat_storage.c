#include "game/cat_storage.h"

// Initialize cat array
struct cat_storage cat_storage_new() {
    struct cat_storage cat_storage;

    // Initialize data structure with no cats
    for (u8 i = 0; i < CAT_LIMIT; i++) {
        cat_storage.cat_array[i].open = true;
    }
    for (u8 i = 0; i < GRID_WIDTH; i++) {
        for (u8 j = 0; j < GRID_HEIGHT; j++) {
            cat_storage.cat_map[i][j] = NULL;
        }
    }

    cat_storage.cat_count = 0;
    return cat_storage;
}

// Add a cat - return true if successful.
bool cat_storage_add_cat(struct cat_storage* cat_storage, u8 x, u8 y, enum cat_type type) {

    // If cat storage is full, we cannot add this cat.
    if (cat_storage -> cat_count > CAT_LIMIT) {
        return false;
    }

    // Search for an open slot
    for (u8 i = 0; i < CAT_LIMIT; i++) {

        // Store address of entry
        struct cat_entry* entry = &(cat_storage -> cat_array[i]);

        // If entry is open,
        if (cat_storage -> cat_array[i].open == true) {

            // Initialize cat and add to data structure
            struct cat new_cat;
            new_cat.sprite = sprite_manager_new_sprite();
            new_cat.type = type;
            new_cat.last_attack_time = 0;
            new_cat.x = x;
            new_cat.y = y;
            entry -> open = false;
            entry -> cat = new_cat;
            cat_storage -> cat_map[x][y] = entry;
            cat_storage -> cat_count++;
            return true;
        }
    }

    // No open slots - failed to add cat.
    return false;
}

// Remove a cat - return true if successful.
bool cat_storage_remove_cat(struct cat_storage* cat_storage, u8 x, u8 y) {
    // If there are no cats, we cannot remove a cat.
    if (cat_storage -> cat_count == 0) {
        return false;
    }

    // Find cat on grid and remove.
    struct cat_entry* entry = cat_storage -> cat_map[x][y];
    if (!entry -> open) {
        entry -> open = true;
        return true;
    }

    // If no cat was found, it cannot be removed.
    return false;

}
    
