#include "game/cat_storage.h"

// Initialize cat array
struct cat_storage cat_storage_new() {
    struct cat_storage cat_storage;
    cat_storage.cat_count = 0;
    return cat_storage;
}

// Add a cat - return true if successful.
bool cat_storage_add_cat(struct cat_storage* cat_storage, u8 x, u8 y, enum cat_type type) {
    // If cat storage is full, we cannot add this cat.
    if (cat_storage -> cat_count > CAT_LIMIT) {
        return false;
    }

    // Initialize cat
    struct cat new_cat;
    new_cat.sprite = sprite_manager_new_sprite();
    new_cat.attacking = false;
    new_cat.type = type;
    switch (new_cat.type) {
        case CAT_ARCHER: { new_cat.time_per_frame = 35; break; }
        case CAT_BOMB:   { new_cat.time_per_frame = 25; break; }
        case CAT_WIZARD: { new_cat.time_per_frame = 45; break; }
        default:         { new_cat.time_per_frame = 30; break; }
    }
    new_cat.time_per_frame = 1;
    new_cat.time_elapsed = 0;
    new_cat.base_tile = cat_manager_get_tile(type);
    new_cat.grid_x = x;
    new_cat.grid_y = y;
    new_cat.pixel_x = x << 4;
    new_cat.pixel_y = y << 4;

    // Add cat to array
    cat_storage -> cat_array[cat_storage -> cat_count] = new_cat;
    cat_storage -> cat_count++;

    return true;
}

// Remove a cat - return true if successful.
bool cat_storage_remove_cat(struct cat_storage* cat_storage, u8 x, u8 y) {
    // If there are no cats, we cannot remove a cat.
    if (cat_storage -> cat_count == 0) {
        return false;
    }

    // Find cat with desired coordinates.
    for (u8 i = 0; i < (cat_storage -> cat_count); i++) {
        struct cat target = cat_storage -> cat_array[i];
        if (target.grid_x == x && target.grid_y == y) {

            // Move cat at end of array to slot of cat being removed
            cat_storage -> cat_array[i] = cat_storage -> cat_array[cat_storage -> cat_count - 1];
            cat_storage -> cat_count--;
            return true;
        }
    }

    // No cat with desired coordinates found, so cat cannot be removed.
    return false;
}
