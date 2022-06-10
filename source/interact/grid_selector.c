#include "interact/grid_selector.h"

struct sprite* cursor;

bool selecting = true;

// Store coordinates of cursor.
// Grid is 13 x 10. If x = 13, cursor is on navbar.
u8 cursor_x = 2;
u8 cursor_y = 0;

// Initialize grid selector
void grid_selector_init() {
    cursor = sprite_manager_new_sprite();
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
    cursor_x = 14;
    cursor_y = 10;
}
