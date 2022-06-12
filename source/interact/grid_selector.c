#include "interact/grid_selector.h"

struct sprite* cursor;
struct sprite* cursor_entity;

// Status of selection
bool selecting = true;
bool erasing = false;
bool placing = false;
enum cat_type selected_cat_type = normal;
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
    if (selecting) {

        // Respond to user input
        if ((pressedKeys & KEY_RIGHT) == KEY_RIGHT) {
            cursor_x++;
            if (cursor_x > 12 && cursor_y > 5) {
                cursor_y = 5;
            }
            if (cursor_x > 13) {
                cursor_x = 13;
            }
        } else if ((pressedKeys & KEY_DOWN) == KEY_DOWN) {
            cursor_y++;
            if (cursor_y > 9) {
                cursor_y = 9;
            }
            if (cursor_x > 12 && cursor_y > 5) {
                cursor_y = 5;
            }
        } else if ((pressedKeys & KEY_LEFT) == KEY_LEFT) {
            if (cursor_x > 0) {
                cursor_x--;
            }
        } else if ((pressedKeys & KEY_UP) == KEY_UP) {
            if (cursor_y > 0) {
                cursor_y--;
            }
        }

        if ((pressedKeys & KEY_A) == KEY_A) {
            if (cursor_x < 13) {
                if (placing) {
                    // TODO: Place cat
                    grid_selector_disable_select();
                }
            } else if (cursor_x == 13) {
                if (cursor_y < 4) {
                    placing = true;
                    erasing = false;
                    switch (cursor_y) {
                        case 1: {
                            selected_cat_type = archer;
                            selected_cat_tile = TILE_CAT_ARCHER;
                            break;
                        }
                        case 2: {
                            selected_cat_type = bomb;
                            selected_cat_tile = TILE_CAT_BOMB;
                            break;
                        }
                        case 3: {
                            selected_cat_type = wizard;
                            selected_cat_tile = TILE_CAT_WIZARD;
                            break;
                        }
                        default: {
                            selected_cat_type = normal;
                            selected_cat_tile = TILE_CAT_NORMAL;
                            break;
                        }
                    }
                } else if (cursor_y == 4) {
                    erasing = true;
                    placing = false;
                } else if (cursor_y == 5) {
                    // TOOD: Start round
                }
            }
        } else if ((pressedKeys & KEY_B) == KEY_B) {
            if (erasing) {
                // TODO: Erase cat
                grid_selector_disable_select();
            }
        } else if ((pressedKeys & KEY_L) == KEY_L) {
            cursor_x = 2;
            cursor_y = 4;
        } else if ((pressedKeys & KEY_R) == KEY_R) {
            cursor_x = 13;
            cursor_y = 2;
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
            (SELECTOR_TILE_2 & 0x3ff) | // Tile index
            (1 << 12);  // Priority
        
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
            (selected_cat_tile & 0x3ff) | // Tile index
            (1 << 12);  // Priority
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
