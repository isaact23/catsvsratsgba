#include "cats/cat_manager.h"

// Cats
struct cat_storage cat_storage;

// Function pointers
static struct sprite* (*new_sprite)();
static bool (*remove_sprite)(struct sprite* sprite);
struct rat* (*get_rats)();
u8 (*get_rat_count)();

// Initialize cat manager
void cat_manager_init
(
    struct sprite* (*sprite_manager_new_sprite)(), bool (*sprite_manager_remove_sprite)(struct sprite* sprite),
    struct rat* (*rat_manager_get_rats)()
) {
    projectile_manager_init(sprite_manager_remove_sprite);
    cat_storage = cat_storage_new();

    // Function pointers
    new_sprite = sprite_manager_new_sprite;
    remove_sprite = sprite_manager_remove_sprite;
    get_rats = rat_manager_get_rats;

    //cat_manager_add_cat(0, 0, CAT_NORMAL);
    //cat_manager_add_cat(1, 2, CAT_WIZARD);
}

// Update cat manager
void cat_manager_update() {
    projectile_manager_update();

    // Get reference to rats
    struct rat* rats = get_rats();

    // Iterate through cats
    for (u8 i = 0; i < cat_storage.cat_count; i++) {
        struct cat* cat = &cat_storage.cat_array[i];
        cat -> time_elapsed = cat -> time_elapsed + 1;
        cat -> time_since_last_fire = cat -> time_since_last_fire + 1;

        // Determine tile
        u16 tile = (cat -> base_tile) + (((cat -> time_elapsed) / (cat -> frames_per_sprite) % 2) * 4);

        // Attack rats
        if ((cat -> time_since_last_fire) >= (cat -> frames_per_fire)) {

            // Find rats in range
            struct rat* closest_rat = NULL;
            u16 closest_rat_dist = 1000;
            for (u8 i = 0; i < RAT_LIMIT; i++) {
                struct rat* rat = &rats[i];

                // Skip disabled rats
                if (!rat -> active) {
                    continue;
                }

                u16 attack_range = cat -> attack_range;

                // Calculate distances and target the closest rat
                u16 dist = abs((cat -> pixel_x) - (rat -> x)) + abs((cat -> pixel_y) - (rat -> y));
                if (dist <= attack_range && dist <= closest_rat_dist) {
                    closest_rat = rat;
                    closest_rat_dist = dist;
                }
            }

            // Shoot projectiles
            if (closest_rat != NULL) {
                cat -> time_since_last_fire = 0;

                enum projectile_type projectile_type;
                switch (cat -> type) {
                    case CAT_ARCHER: {
                        projectile_type = PROJECTILE_ARROW;
                        break;
                    }
                    case CAT_BOMB: {
                        projectile_type = PROJECTILE_PAW;
                        break;
                    }
                    case CAT_WIZARD: {
                        projectile_type = PROJECTILE_MAGIC;
                        break;
                    }
                    default: {
                        projectile_type = PROJECTILE_PAW;
                        break;
                    }
                }

                struct sprite* proj_sprite = new_sprite();
                if (proj_sprite == NULL) {
                    exit(1);
                }
                projectile_manager_add_projectile(
                    projectile_type, cat -> pixel_x, cat -> pixel_y, proj_sprite, closest_rat);
            }
        }

        // Update cat sprite
        struct sprite* sprite = cat -> sprite;
        sprite -> attr0 =
            OBJ_Y(cat -> pixel_y) |
            ATTR0_COLOR_256 |
            ATTR0_SQUARE;
        sprite -> attr1 =
            OBJ_X(cat -> pixel_x) |
            ATTR1_SIZE_16;
        sprite -> attr2 =
            OBJ_CHAR(tile);
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
            new_cat.frames_per_sprite = CAT_ARCHER_FRAMES_PER_SPRITE;
            new_cat.frames_per_fire = CAT_ARCHER_FRAMES_PER_FIRE;
            new_cat.attack_range = CAT_ARCHER_ATTACK_RANGE;
            break;
        }
        case CAT_BOMB: {
            new_cat.frames_per_sprite = CAT_BOMB_FRAMES_PER_SPRITE;
            new_cat.frames_per_fire = CAT_BOMB_FRAMES_PER_FIRE;
            new_cat.attack_range = CAT_BOMB_ATTACK_RANGE;
            break;
        }
        case CAT_WIZARD: {
            new_cat.frames_per_sprite = CAT_WIZARD_FRAMES_PER_SPRITE;
            new_cat.frames_per_fire = CAT_WIZARD_FRAMES_PER_FIRE;
            new_cat.attack_range = CAT_WIZARD_ATTACK_RANGE;
            break;
        }
        default: {
            new_cat.frames_per_sprite = CAT_NORMAL_FRAMES_PER_SPRITE;
            new_cat.frames_per_fire = CAT_NORMAL_FRAMES_PER_FIRE;
            new_cat.attack_range = CAT_NORMAL_ATTACK_RANGE;
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

// Get the price of a cat type
u16 cat_manager_get_price(enum cat_type type) {
    switch (type) {
        case CAT_ARCHER: { return CAT_ARCHER_PRICE; }
        case CAT_BOMB:   { return CAT_BOMB_PRICE;   }
        case CAT_WIZARD: { return CAT_WIZARD_PRICE; }
        default:         { return CAT_NORMAL_PRICE; }
    }
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
