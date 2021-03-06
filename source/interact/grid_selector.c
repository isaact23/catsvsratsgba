#include "interact/grid_selector.h"

struct sprite* cursor;
struct sprite* cursor_entity;

// Status of selection
bool selecting = false;
bool erasing = false;
bool placing = false;
enum cat_type selected_cat_type = CAT_NORMAL;
s32 selected_cat_price;
u16 selected_cat_tile = 0;

// Store coordinates of cursor.
// Grid is 13 x 10. If x = 13, cursor is on navbar.
u8 cursor_x = 2;
u8 cursor_y = 0;

// Initialize grid selector
void grid_selector_init() {
    cursor = sprite_manager_new_sprite();
    cursor_entity = sprite_manager_new_sprite();
}

// Update grid selector every frame
void grid_selector_update(u16 pressedKeys) {

    // Respond to user input
    if ((pressedKeys & KEY_RIGHT) == KEY_RIGHT) {
        selecting = true;
        cursor_x++;
        if (cursor_x > 12 && cursor_y > 5) {
            cursor_y = 5;
        }
        if (cursor_x > 13) {
            cursor_x = 13;
        }

    } else if ((pressedKeys & KEY_DOWN) == KEY_DOWN) {
        selecting = true;
        cursor_y++;
        if (cursor_y > 9) {
            cursor_y = 9;
        }
        if (cursor_x > 12 && cursor_y > 5) {
            cursor_y = 5;
        }

    } else if ((pressedKeys & KEY_LEFT) == KEY_LEFT) {
        selecting = true;
        if (cursor_x > 0) {
            cursor_x--;
        }

    } else if ((pressedKeys & KEY_UP) == KEY_UP) {
        selecting = true;
        if (cursor_y > 0) {
            cursor_y--;
        }

    } else if ((pressedKeys & KEY_L) == KEY_L) {
        selecting = true;
        cursor_x = 2;
        cursor_y = 4;

    } else if ((pressedKeys & KEY_R) == KEY_R) {
        selecting = true;
        cursor_x = 13;
        cursor_y = 2;
    }

    if (selecting) {

        if ((pressedKeys & KEY_A) == KEY_A) {

            // Press A on grid
            if (cursor_x < 13) {
                if (placing) {
                    bool success = cat_manager_add_cat(cursor_x, cursor_y, selected_cat_type);
                    if (success) {
                        game_manager_add_money(-selected_cat_price);
                        grid_selector_disable_select();
                        placing = false;
                    }
                } else if (erasing) {
                    bool success = cat_manager_remove_cat(cursor_x, cursor_y);
                    if (success) {
                        grid_selector_disable_select();
                        erasing = false;
                    }
                }

            // Press A on navbar
            } else if (cursor_x == 13) {

                // Select a cat to place
                if (cursor_y < 4) {
                    switch (cursor_y) {
                        case 1:  { selected_cat_type = CAT_ARCHER; selected_cat_price = CAT_ARCHER_PRICE; break; }
                        case 2:  { selected_cat_type = CAT_BOMB;   selected_cat_price = CAT_BOMB_PRICE;   break; }
                        case 3:  { selected_cat_type = CAT_WIZARD; selected_cat_price = CAT_WIZARD_PRICE; break; }
                        default: { selected_cat_type = CAT_NORMAL; selected_cat_price = CAT_NORMAL_PRICE; break; }
                    }
                    // If we can afford this cat, select it.
                    if (selected_cat_price <= game_manager_get_money()) {
                        placing = true;
                        erasing = false;
                        selected_cat_tile = cat_manager_get_tile(selected_cat_type);
                    }

                // Select eraser
                } else if (cursor_y == 4) {
                    erasing = true;
                    placing = false;
                
                // Start round
                } else if (cursor_y == 5) {
                    // TOOD: Start round
                }
            }

        // Press B to cancel operation
        } else if ((pressedKeys & KEY_B) == KEY_B) {

            // Cancel placement
            if (placing) {
                placing = false;
                grid_selector_disable_select();

            // Cancel erasing
            } else if (erasing) {
                erasing = false;
                grid_selector_disable_select();
            }
        }

        // Calculate on-screen coordinates for cursor
        u8 x = 240;
        u8 y = 0;
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

        // Update sprite attributes
        cursor -> attr1 =
            (y & 0xff) | // y position
            (1 << 13) | // 256 colors
            (0 << 14);  // Shape
        cursor -> attr2 =
            (x & 0x1ff) | // x position
            (1 << 14);  // Size
        cursor -> attr3 =
            (SELECTOR_TILE_2 & 0x3ff); // Tile index
        
        if (!placing) {
            x = 240;
        }
        cursor_entity -> attr1 =
            (y & 0xff) | // y position
            (1 << 13) | // 256 colors
            (0 << 14);  // Shape
        cursor_entity -> attr2 =
            (x & 0x1ff) | // x position
            (1 << 14);  // Size
        cursor_entity -> attr3 =
            (selected_cat_tile & 0x3ff); // Tile index
    }
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
    cursor_x = 14;
    cursor_y = 10;
}
