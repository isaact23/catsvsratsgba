#include "rats/rat_manager.h"

// Rats
struct rat rat_array [RAT_LIMIT];
u16 rats_spawned = 0;
u16 rats_alive = 0;
u8 next_eat_pos = 0; // Next position to place a rat to consume cheese, ranges from 0 to 3

// Function pointers
static struct sprite* (*new_sprite)();
bool (*remove_sprite)(struct sprite* sprite);
void (*decrease_health)();
void (*end_round)();


// If enough time has elapsed, spawn a new rat. Return true if successful.
static bool _rat_manager_spawn(const struct round* curr_round, u32 time_elapsed);

// Remove a rat. Return true if successful.
static bool _rat_manager_remove(struct rat* rat);

// Update path position of a rat
static void _rat_manager_update_rat_position(struct rat* rat, u32 time_elapsed);


// Initialize rat manager
void rat_manager_init(
    struct sprite* (*sprite_manager_new_sprite)(),
    bool (*sprite_manager_remove_sprite)(struct sprite* sprite),
    void (*game_manager_decrease_health)(),
    void (*game_manager_end_round)()
) {
    // Function pointer to sprite manager's new sprite
    new_sprite = sprite_manager_new_sprite;
    remove_sprite = sprite_manager_remove_sprite;
    decrease_health = game_manager_decrease_health;
    end_round = game_manager_end_round;
}

// Update rats
void rat_manager_update(const struct round* curr_round, u32 time_elapsed) {
    // Spawn new rat. Ignore failures (rats can be spawned later)
    _rat_manager_spawn(curr_round, time_elapsed);

    // Check if all rats have been killed.
    if (rats_alive == 0 && rats_spawned >= (curr_round -> rat_count)) {
        end_round();
        return;
    }

    // Iterate through rats
    for (u32 i = 0; i < RAT_LIMIT; i++) {
        struct rat* rat = &(rat_array[i]);

        // Skip empty rat entries
        if (!(rat -> active)) {
            continue;
        }
        // Remove dead rats
        if (rat -> hp <= 0) {
            _rat_manager_remove(rat);
            continue;
        }

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

        // If the rat is eating, handle cheese consumption.
        } else {
            if (rat -> time_until_next_bite <= 0) {
                decrease_health();
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
        
        // Update HP bar
        // Move something from range 0 to MAX_HP to range 14 to 0, then pick tile
        u8 adjusted_hp = (rat -> hp) * HP_TILE_COUNT / (rat -> hp_max);
        u8 adjusted_hp_flipped = 14 - adjusted_hp;
        u8 tile = (adjusted_hp_flipped * 4) + HP_TILE;

        struct sprite* hp_bar = rat -> hp_bar;
        hp_bar -> attr1 =
            (((rat -> y) - 6) & 0xff) |
            (1 << 13) |
            (1 << 14); // Horizontal shape
        hp_bar -> attr2 =
            ((rat -> x) & 0x1ff);
        hp_bar -> attr3 =
            tile & 0x3ff;
    }
}

// Get array of rats
struct rat* rat_manager_get_rats() {
    return rat_array;
}

// If enough time has elapsed, spawn a new rat. Return true if successful.
static bool _rat_manager_spawn(const struct round* curr_round, u32 time_elapsed) {

    // If there are still rats to spawn,
    if (rats_spawned < curr_round -> rat_count) {

        // Rat index is the array index to insert the next rat.
        u16 rat_index = 0;

        // Get rat data from round
        struct rat_spawn_entry rat_data = curr_round -> rat_spawn_entries[rats_spawned];

        // If it is time to spawn this rat,
        if (time_elapsed > rat_data.spawn_time) {

            // Find index in rat_array for new rat.
            while (rat_array[rat_index].active) {
                rat_index++;
                if (rat_index >= RAT_LIMIT) {
                    return false;
                }
            }

            // Spawn the rat
            struct rat new_rat;
            new_rat.sprite = new_sprite();
            new_rat.hp_bar = new_sprite();
            if (new_rat.sprite == NULL || new_rat.hp_bar == NULL) {
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
                new_rat.hp_max = 10;
            } else if (new_rat.type == RAT_FAST) {
                new_rat.speed = 2;
                new_rat.fps = 3;
                new_rat.hps = 1;
                new_rat.hp_max = 10;
            } else {
                exit(1);
            }
            new_rat.hp = new_rat.hp_max;

            // Initialize all rats with these values
            new_rat.active = true;
            new_rat.x = 240;
            new_rat.y = 0;
            new_rat.eating = -1;
            new_rat.time_until_next_bite = 0;

            new_rat.index = rat_index;

            // Copy rat to rat array
            rat_array[rat_index] = new_rat;
            rats_spawned++;
            rats_alive++;
        }
    }
    return true;
}

// Remove a rat. Return true if successful.
static bool _rat_manager_remove(struct rat* rat) {
    if (rat -> index >= RAT_LIMIT) {
        return false;
    }
    if (!(rat -> active)) {
        return false;
    }
    rat -> active = false;
    rats_alive--;

    // Remove sprites, and return true if both removals are successful.
    bool success1 = remove_sprite(rat -> sprite);
    bool success2 = remove_sprite(rat -> hp_bar);
    return success1 && success2;
}

// Update path position of a rat
static void _rat_manager_update_rat_position(struct rat* rat, u32 time_elapsed) {
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