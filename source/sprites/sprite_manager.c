#include "sprites/sprite_manager.h"

// Sprites
struct sprite sprite_array [SPRITE_LIMIT];
u32 sprite_count = 0;

// Rats
struct rat rat_array [RAT_LIMIT];
u32 rat_count = 0;

// Rounds
const struct round* curr_round;

// Time elapsed since beginning of a round
u32 time_elapsed = 0;


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

// Start a round
void sprite_manager_start_round(u16 round) {
    time_elapsed = 0;
    curr_round = data_rounds_get(round);
}

// Update sprites in memory every vblank
void sprite_manager_update() {
    sprite_manager_spawn_rats();
    sprite_manager_update_rats();
    
    time_elapsed++;

    // Update sprite attributes
    dmaCopy(sprite_array, (void*) OAM, 8 * SPRITE_LIMIT);
}

// Return a pointer to a new sprite
struct sprite* sprite_manager_new_sprite() {
    if (sprite_count >= SPRITE_LIMIT) {
        exit(1);
    }
    struct sprite* new_sprite = &sprite_array[sprite_count];
    new_sprite -> attr1 = 0;
    new_sprite -> attr2 = 0;
    new_sprite -> attr3 = 0;
    sprite_count++;
    return new_sprite;
}

// If enough time has elapsed, spawn a new rat
void sprite_manager_spawn_rats() {
    if (rat_count >= RAT_LIMIT) {
        exit(1);
    }

    // If there are still rats to spawn,
    if (rat_count < curr_round -> rat_count) {
        // Get rat data from round
        struct rat_spawn_entry rat_data = curr_round -> rat_spawn_entries[rat_count];
        // If it is time to spawn this rat,
        if (time_elapsed > rat_data.spawn_time) {
            // Spawn the rat
            struct rat new_rat;
            new_rat.sprite = sprite_manager_new_sprite();
            new_rat.init_time = time_elapsed;

            // Get path data
            if (rat_data.path_id == 0) {
                new_rat.path = &DATA_PATH_0;
            } else if (rat_data.path_id == 1) {
                new_rat.path = &DATA_PATH_1;
            } else {
                exit(1);
            }

            // Initialize rat properties
            new_rat.type = rat_data.rat_type;
            if (new_rat.type == 0) {
                new_rat.speed = 1; // Default rat
                new_rat.fps = 2;
            } else if (new_rat.type == 1) {
                new_rat.speed = 2; // Fast rat
                new_rat.fps = 3;
            } else {
                exit(1);
            }
            new_rat.x = 240;
            new_rat.y = 0;
            rat_array[rat_count] = new_rat;
            rat_count++;
        }
    }
}

// Update rats
void sprite_manager_update_rats() {

    // Iterate through rats
    for (u32 i = 0; i < rat_count; i++) {
        struct rat* rat = &(rat_array[i]);

        // Update rat tile
        if (rat -> type == 0) {
            rat -> tile_id = ((((time_elapsed - rat -> init_time) * rat -> fps) / 60) % 2) * 64;
        } else if (rat -> type == 1) {
            rat -> tile_id = 8 + ((((time_elapsed - rat -> init_time) * rat -> fps) / 60) % 2) * 64;
        } else {
            exit(1);
        }

        // Update rat position based on time elapsed
        u32 progress = time_elapsed - rat -> init_time;
        u32 pixels = (progress * rat -> speed) >> 1;

        // Divide pixels by 16, the tile width, to get tile number
        u16 tile_no = pixels >> 4;

        // Update rat path
        if (tile_no + 1 >= rat -> path -> length) {
            // Mutant path
            if (rat -> path -> id == 0) {
                rat -> path = &DATA_PATH_2;
            }
            // Merge paths
            else if (rat -> path -> id == 1 || rat -> path -> id == 2) {
                rat -> path = &DATA_PATH_3;
            } else {
                //exit(1); // Begin eating cheese
            }

            // Reset to beginning of path
            rat -> init_time = time_elapsed;
            pixels = 0;
            tile_no = 0;
        }

        const s8* tiles = rat -> path -> coords;

        // Get coordinates of current tile
        s16 tile_x = tiles[tile_no * 2];
        s16 tile_y = tiles[tile_no * 2 + 1];

        // Get coordinates of next tile
        s16 tile2_x = tiles[(tile_no + 1) * 2];
        s16 tile2_y = tiles[(tile_no + 1) * 2 + 1];

        s16 pixel_offset = pixels % 16;

        // Same x
        if (tile_x == tile2_x) {
            rat -> x = tile_x * 16;

            // Moving down
            if (tile2_y > tile_y) {
                rat -> y = tile_y * 16 + pixel_offset;
            }
            // Moving up
            else {
                rat -> y = tile_y * 16 - pixel_offset;
            }
        }
        // Same y
        else {
            rat -> y = tile_y * 16;

            // Moving right
            if (tile2_x > tile_x) {
                rat -> x = tile_x * 16 + pixel_offset;
            }
            // Moving left
            else {
                rat -> x = tile_x * 16 - pixel_offset;
            }
        }

        // Send rat data to sprite struct
        struct sprite* sprite = rat -> sprite;
        sprite -> attr1 =
            ((rat -> y) & 0xff) |
            (1 << 13) | // 256 colors
            (0 << 14);  // Shape
        sprite -> attr2 =
            ((rat -> x) & 0x1ff) |
            (1 << 14);  // Size
        sprite -> attr3 =
            ((rat -> tile_id) & 0x3ff) | // Tile index
            (1 << 12);  // Priority
    }
}
