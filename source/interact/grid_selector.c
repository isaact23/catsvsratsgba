#include "interact/grid_selector.h"

struct sprite* cursor;
struct sprite* cursor_entity;

// Function pointers
bool (*next_round)();
enum game_state (*get_state)();
static struct sprite* (*new_sprite)();
bool (*add_cat)(u8 x, u8 y, enum cat_type type);
bool (*remove_cat)(u8 x, u8 y);
u16 (*get_cat_price)(enum cat_type type);
void (*add_money)(s32 amount);
s32 (*get_money)();
u16 (*get_cat_tile)(enum cat_type type);

// Determine if a key is pressed.
static bool pressed(enum KEYPAD_BITS queryKey);

// Status of selection
bool selecting = false;
bool erasing = false;
bool placing = false;
enum cat_type selected_cat_type = CAT_NORMAL;
s32 selected_cat_price = 0;
u16 selected_cat_tile = 0;

// Store coordinates of cursor.
// Grid is 13 x 10. If x = 13, cursor is on navbar.
u8 cursor_x = 2;
u8 cursor_y = 0;

// Store pressed keys.
u16 keys;

// Initialize grid selector
void grid_selector_init(
    bool (*game_manager_next_round)(),
    struct sprite* (*sprite_manager_new_sprite)(),
    bool (*cat_manager_add_cat)(u8 x, u8 y, enum cat_type type),
    bool (*cat_manager_remove_cat)(u8 x, u8 y),
    u16 (*cat_manager_get_price)(enum cat_type type),
    void (*game_manager_add_money)(s32 amount),
    s32 (*game_manager_get_money)(),
    u16 (*cat_manager_get_tile)(enum cat_type type))
{
    cursor = sprite_manager_new_sprite();
    cursor_entity = sprite_manager_new_sprite();

    // Function pointers
    next_round = game_manager_next_round;
    new_sprite = sprite_manager_new_sprite;
    add_cat = cat_manager_add_cat;
    remove_cat = cat_manager_remove_cat;
    get_cat_price = cat_manager_get_price;
    add_money = game_manager_add_money;
    get_money = game_manager_get_money;
    get_cat_tile = cat_manager_get_tile;
}

// Update grid selector every frame
void grid_selector_update(u16 pressedKeys) {
    keys = pressedKeys;

    // Respond to user input
    if (pressed(KEY_RIGHT)) {
        selecting = true;
        cursor_x++;
        if (cursor_x > 12 && cursor_y > 5) {
            cursor_y = 5;
        }
        if (cursor_x > 13) {
            cursor_x = 13;
        }

    } else if (pressed(KEY_DOWN)) {
        selecting = true;
        cursor_y++;
        if (cursor_y > 9) {
            cursor_y = 9;
        }
        if (cursor_x > 12 && cursor_y > 5) {
            cursor_y = 5;
        }

    } else if (pressed(KEY_LEFT)) {
        selecting = true;
        if (cursor_x > 0) {
            cursor_x--;
        }

    } else if (pressed(KEY_UP)) {
        selecting = true;
        if (cursor_y > 0) {
            cursor_y--;
        }

    } else if (pressed(KEY_L)) {
        selecting = true;
        cursor_x = 2;
        cursor_y = 4;

    } else if (pressed(KEY_R)) {
        selecting = true;
        cursor_x = 13;
        cursor_y = 2;
    }

    if (selecting) {

        if (pressed(KEY_A)) {

            // 'A' pressed on grid
            if (cursor_x < 13) {
                if (placing) {
                    bool success = add_cat(cursor_x, cursor_y, selected_cat_type);
                    if (success) {
                        add_money(-selected_cat_price);
                        grid_selector_disable_select();
                        placing = false;
                    }
                } else if (erasing) {

                    bool success = remove_cat(cursor_x, cursor_y);
                    if (success) {
                        grid_selector_disable_select();
                        erasing = false;
                    }
                }

            // 'A' pressed on navbar
            } else if (cursor_x == 13) {

                // Select a cat to place
                if (cursor_y < 4) {
                    switch (cursor_y) {
                        case 1:  { selected_cat_type = CAT_ARCHER; break; }
                        case 2:  { selected_cat_type = CAT_BOMB;   break; }
                        case 3:  { selected_cat_type = CAT_WIZARD; break; }
                        default: { selected_cat_type = CAT_NORMAL; break; }
                    }
                    selected_cat_price = get_cat_price(selected_cat_type);
                    
                    // If we can afford this cat, select it.
                    if (selected_cat_price <= get_money()) {
                        placing = true;
                        erasing = false;
                        selected_cat_tile = get_cat_tile(selected_cat_type);
                    }

                // Select eraser
                } else if (cursor_y == 4) {
                    erasing = true;
                    placing = false;
                
                // Start round
                } else if (cursor_y == 5) {
                    next_round();
                }
            }

        // Press B to cancel operation
        } else if (pressed(KEY_B)) {

            // Cancel placement
            if (placing) {
                placing = false;
                grid_selector_disable_select();

            // Cancel erasing
            } else if (erasing) {
                erasing = false;
                grid_selector_disable_select();

            // Cancel selecting
            } else if (selecting) {
                selecting = false;
                grid_selector_disable_select();
            }

        }
    }
    // If A is pressed when we're not selecting, start selecting
    else if (pressed(KEY_A)) {
        selecting = true;
    }

    // Cursor defaults to off-screen.
    u8 x = 240;
    u8 y = 0;

    // Calculate on-screen coordinates for cursor if selecting.
    if (selecting) {
        if (cursor_x < 13) {
            x = cursor_x * TILE_SIZE;
            if (cursor_y < 10) {
                y = cursor_y * TILE_SIZE;
            } else {
                grid_selector_disable_select();
            }
        } else if (cursor_x == 13) {
            x = ICON_X_OFFSET;
            if (cursor_y < 4) {
                y = CAT_ICON_Y_OFFSET + (CAT_ICON_SIZE * cursor_y);
            } else if (cursor_y < 6) {
                y = BUTTON_OFFSET + (BUTTON_SIZE * (cursor_y - 4));
            } else {
                grid_selector_disable_select();
            }
        } else {
            grid_selector_disable_select();
        }
    }

    // Update sprite attributes
    cursor -> attr0 =
        OBJ_Y(y) |
        ATTR0_COLOR_256 |
        ATTR0_SQUARE;
    cursor -> attr1 =
        OBJ_X(x) |
        ATTR1_SIZE_16;
    cursor -> attr2 =
        OBJ_CHAR(SELECTOR_TILE_2);
    
    // Disable cursor entity if we are not placing a cat.
    if (!placing) {
        x = 240;
    }
    cursor_entity -> attr0 =
        OBJ_Y(y) |
        ATTR0_COLOR_256 |
        ATTR0_SQUARE;
    cursor_entity -> attr1 =
        OBJ_X(x) |
        ATTR1_SIZE_16;
    cursor_entity -> attr2 =
        OBJ_CHAR(selected_cat_tile);
        
}

// Enable selection mode
void grid_selector_enable_select() {
    selecting = true;
    cursor_x = 2;
    cursor_y = 2;
}

// Disable selection mode
void grid_selector_disable_select() {
    selecting = false;
    erasing = false;
    placing = false;
    cursor_x = 10;
    cursor_y = 4;
}

// Determine if a key is pressed.
static bool pressed(enum KEYPAD_BITS queryKey) {
    return ((keys & queryKey) == queryKey);
}
