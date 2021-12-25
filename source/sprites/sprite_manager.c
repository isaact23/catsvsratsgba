#include "sprites/sprite_manager.h"

volatile uint16_t* sprite_palette    = (volatile uint16_t*) 0x5000200;
volatile uint16_t* sprite_image_vram = (volatile uint16_t*) 0x6010000;
volatile uint16_t* sprite_attributes = (volatile uint16_t*) 0x7000000;

struct sprite sprites [SPRITE_LIMIT];
uint32_t sprite_count = 0;

struct rat rat_array[RAT_LIMIT];
uint32_t rat_count = 0;

uint32_t time_elapsed;

// Initialize sprites
void sprite_manager_init() {

    // Move all unused sprites off-screen
    for (uint32_t i = 1; i < SPRITE_LIMIT; i++) {
        sprites[i].attr1 = 240;
    }

    // Copy sprite palette to sprite palette memory
    for (uint32_t i = 0; i < IMAGE_RAT_DEFAULT_WALK_PALETTE_SIZE; i++) {
        sprite_palette[i] = IMAGE_RAT_DEFAULT_WALK_PALETTE[i];
    }

    // Copy sprite into sprite image memory
    uint16_t* sprite16 = (uint16_t*) IMAGE_RAT_DEFAULT_WALK_DATA;
    for (uint32_t i = 0; i < IMAGE_RAT_DEFAULT_WALK_WIDTH * IMAGE_RAT_DEFAULT_WALK_HEIGHT * 32; i++) {
        sprite_image_vram[i] = sprite16[i];
    }
}

// Start a round
void sprite_manager_start_round(uint16_t round) {
    time_elapsed = 0;
}

// Update sprites in memory every vblank
void sprite_manager_update() {
    sprite_manager_update_rats();
    
    time_elapsed++;

    // Update sprite attributes
    for (uint32_t i = 0; i < SPRITE_LIMIT; i++) {
        struct sprite sprite = sprites[i];
        sprite_attributes[i * 4] = sprite.attr1;
        sprite_attributes[i * 4 + 1] = sprite.attr2;
        sprite_attributes[i * 4 + 2] = sprite.attr3;
    }
}

// Return a pointer to a new sprite
struct sprite* sprite_manager_new_sprite() {
    if (sprite_count >= SPRITE_LIMIT) {
        exit(1);
    }
    struct sprite* new_sprite = &sprites[sprite_count];
    new_sprite -> attr1 = 0;
    new_sprite -> attr2 = 0;
    new_sprite -> attr3 = 0;
    sprite_count++;
    return new_sprite;
}

// Add a new rat
void sprite_manager_add_rat() {
    if (rat_count >= RAT_LIMIT) {
        exit(1);
    }
    struct rat new_rat;
    new_rat.sprite = sprite_manager_new_sprite();
    new_rat.init_time = time_elapsed;

    new_rat.path_id = 0;
    new_rat.path_length = DATA_PATH_LENGTH0;
    new_rat.path_address = DATA_PATH_COORDS0;

    new_rat.type = 0;
    new_rat.slowness = 15;
    new_rat.x = 25;
    new_rat.y = 25;
    rat_array[rat_count] = new_rat;
    rat_count++;
}

// Update rats
void sprite_manager_update_rats() {
    // Move rats
    rat_array[0].x = (uint16_t) ((time_elapsed - rat_array[0].init_time) >> 4);

    // Iterate through rats
    for (uint32_t i = 0; i < rat_count; i++) {
        struct rat* rat = &(rat_array[i]);

        // Update rat position based on time elapsed
        uint32_t progress = time_elapsed - rat -> init_time;
        uint32_t pixels = progress / rat -> slowness;

        // Divide pixels by 16, the tile width, to get tile number
        uint16_t tile_no = pixels >> 4;

        // Update rat path
        if (tile_no >= rat -> path_length) {
            // Mutant path
            if (rat -> path_id == 0) {
                rat -> path_id = 2;
                rat -> path_length = DATA_PATH_LENGTH2;
                rat -> path_address = DATA_PATH_COORDS2;
            }
            // Merge paths
            else if (rat -> path_id == 1 || rat -> path_id == 2) {
                rat -> path_id = 3;
                rat -> path_length = DATA_PATH_LENGTH3;
                rat -> path_address = DATA_PATH_COORDS3;
            }

            // Reset to beginning of path
            rat -> init_time = time_elapsed;
            pixels = 0;
            tile_no = 0;
        }

        const int8_t* tiles = rat -> path_address;

        // Get coordinates of current tile
        int16_t tile_x = tiles[tile_no * 2] * 16;
        int16_t tile_y = tiles[tile_no * 2 + 1] * 16;

        // Get coordinates of next tile
        int16_t tile2_x = tiles[(tile_no + 1) * 2] * 16;
        int16_t tile2_y = tiles[(tile_no + 1) * 2 + 1] * 16;

        int16_t pixel_offset = pixels % 16;

        // Same x
        if (tile_x == tile2_x) {
            rat -> x = tile_x;

            // Moving down
            if (tile2_y > tile_y) {
                rat -> y = tile_y + pixel_offset;
            }
            // Moving up
            else {
                rat -> y = tile_y - pixel_offset;
            }
        }
        // Same y
        else {
            rat -> y = tile_y;

            // Moving right
            if (tile2_x > tile_x) {
                rat -> x = tile_x + pixel_offset;
            }
            // Moving left
            else {
                rat -> x = tile_x - pixel_offset;
            }
        }

        // Send rat data to sprite struct
        struct sprite* sprite = rat -> sprite;
        sprite -> attr1 =
            (rat -> y & 0xff) |
            (1 << 13) | // 256 colors
            (0 << 14);  // Shape
        sprite -> attr2 =
            (rat -> x & 0x1ff) |
            (1 << 14);  // Size
        sprite -> attr3 =
            0         | // Tile index
            (1 << 12);  // Priority */
    }
}
