#include "rats/rat_manager.h"

// Rats
struct rat rat_array [RAT_LIMIT];
u8 rat_count = 0;
u8 next_eat_pos = 0; // Next position to place a rat to consume cheese, ranges from 0 to 3

// Initialize rat manager
void rat_manager_init() {
    
}

// Update rats
void rat_manager_update(const struct round* curr_round, u32 time_elapsed) {
    _rat_manager_spawn(curr_round, time_elapsed);

    // Iterate through rats
    for (u32 i = 0; i < rat_count; i++) {
        struct rat* rat = &(rat_array[i]);

        // Update rat sprite
        u16 sprite_tile;
        u16 frame_counter = ((time_elapsed - rat -> init_time) * rat -> fps) / 60;
        if (rat -> eating < 0) {
            if (rat -> type == 0) {
                sprite_tile = (frame_counter % 2) * 4;
            } else if (rat -> type == 1) {
                sprite_tile = 16 + (frame_counter % 2) * 4;
            } else {
                exit(1);
            }
        } else {
            if (rat -> type == 0) {
                sprite_tile = 8 + (frame_counter % 2) * 4;
            } else if (rat -> type == 1) {
                sprite_tile = 24 + (frame_counter % 2) * 4;
            } else {
                exit(1);
            }
        }
        rat -> tile_id = sprite_tile;

        // If the rat is not eating, update path position.
        if (rat -> eating < 0) {
            _rat_manager_update_rat_position(rat, time_elapsed);
        }

        // If the rat is eating, handle cheese consumption.
        if (rat -> eating >= 0) {
            if (rat -> time_until_next_bite <= 0) {
                game_manager_decrease_health();
                if (rat -> hps <= 0) {
                    exit(1);
                }
                rat -> time_until_next_bite = 60 / (rat -> hps);
            }
            rat -> time_until_next_bite--;
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

// Get array of rats
struct rat* rat_manager_get_rats() {
    return rat_array;
}

// Get rat count
u8 rat_manager_get_rat_count() {
    return rat_count;
}

// If enough time has elapsed, spawn a new rat
void _rat_manager_spawn(const struct round* curr_round, u32 time_elapsed) {
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
            new_rat.sprite = game_manager_new_sprite();
            if (new_rat.sprite == NULL) {
                exit(1);
            }
            new_rat.init_time = time_elapsed;

            // Get path data
            if (rat_data.path_id == 0) {
                new_rat.path = &DATA_PATH_0;
            } else if (rat_data.path_id == 1) {
                new_rat.path = &DATA_PATH_1;
            } else {
                exit(1);
            }

            // Initialize rat based on type
            new_rat.type = rat_data.rat_type;
            if (new_rat.type == RAT_NORMAL) {
                new_rat.speed = 1;
                new_rat.fps = 2;
                new_rat.hps = 1;
                new_rat.hp = 10;
            } else if (new_rat.type == RAT_FAST) {
                new_rat.speed = 2;
                new_rat.fps = 3;
                new_rat.hps = 1;
                new_rat.hp = 10;
            } else {
                exit(1);
            }

            // Initialize all rats with these values
            new_rat.x = 240;
            new_rat.y = 0;
            new_rat.eating = -1;
            new_rat.time_until_next_bite = 0;

            // Copy rat to rat array
            rat_array[rat_count] = new_rat;
            rat_count++;
        }
    }
}

// Update path position of a rat
void _rat_manager_update_rat_position(struct rat* rat, u32 time_elapsed) {
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
            // Begin eating cheese
            rat -> eating = next_eat_pos;
            next_eat_pos++;
            if (next_eat_pos > 3 || next_eat_pos < 0) {
                next_eat_pos = 0;
            }
            if (next_eat_pos == 0) {
                rat -> x = 144;
                rat -> y = 112;
            } else if (next_eat_pos == 1) {
                rat -> x = 160;
                rat -> y = 96;
            } else if (next_eat_pos == 2) {
                rat -> x = 176;
                rat -> y = 112;
            } else if (next_eat_pos == 3) {
                rat -> x = 160;
                rat -> y = 128;
            }
            return;
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
}