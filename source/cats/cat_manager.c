#include "cats/cat_manager.h"

// Cats
struct cat_storage cat_storage;

// Initialize cat manager
void cat_manager_init() {
    projectile_manager_init();
    cat_storage = cat_storage_new();

    cat_manager_add_cat(0, 0, CAT_NORMAL);
    cat_manager_add_cat(1, 2, CAT_WIZARD);
}

// Update cat manager
void cat_manager_update() {

    // Iterate through cats
    for (u8 i = 0; i < cat_storage.cat_count; i++) {
        struct cat* cat = &cat_storage.cat_array[i];
        cat -> time_elapsed = cat -> time_elapsed + 1;

        // Determine tile
        u16 tile = (cat -> base_tile) + (((cat -> time_elapsed) / (cat -> frames_per_sprite) % 2) * 4);

        // Find rats in range


        // Shoot projectiles
        // if (closest_rat exists && cat.time_since_last_fire == 0)

        //projectile_manager_add_projectile();

        // Update cat sprite
        struct sprite* sprite = cat -> sprite;
        sprite -> attr1 =
            ((cat -> pixel_y) & 0xff) | // y position
            (1 << 13) | // 256 colors
            (0 << 14);  // Shape
        sprite -> attr2 =
            ((cat -> pixel_x) & 0x1ff) | // x position
            (1 << 14);  // Size
        sprite -> attr3 =
            (tile & 0x3ff); // Tile index
    }
}

// Add a cat - return true if successful.
bool cat_manager_add_cat(u8 x, u8 y, enum cat_type type) {

    // Initialize cat
    struct cat new_cat;
    new_cat.sprite = sprite_manager_new_sprite();
    new_cat.attacking = false;
    new_cat.type = type;

    switch (new_cat.type) {
        case CAT_ARCHER: {
            new_cat.frames_per_sprite = 35;
            new_cat.frames_per_fire = 30;
            new_cat.attack_range = 64;
            break;
        }
        case CAT_BOMB: {
            new_cat.frames_per_sprite = 25;
            new_cat.frames_per_fire = 120;
            new_cat.attack_range = 16;
            break;
        }
        case CAT_WIZARD: {
            new_cat.frames_per_sprite = 45;
            new_cat.frames_per_fire = 40;
            new_cat.attack_range = 32;
            break;
        }
        default: {
            new_cat.frames_per_sprite = 30;
            new_cat.frames_per_fire = 20;
            new_cat.attack_range = 32;
            break;
        }
    }

    new_cat.time_elapsed = 0;
    new_cat.time_since_last_fire = 0;
    new_cat.base_tile = cat_manager_get_tile(type);
    new_cat.grid_x = x;
    new_cat.grid_y = y;
    new_cat.pixel_x = x << 4;
    new_cat.pixel_y = y << 4;

    return cat_storage_add_cat(&cat_storage, new_cat);
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
