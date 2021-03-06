#include "screen/text_manager.h"

struct sprite* money_num_array [NUM_CNT];
struct sprite* health_num_array [NUM_CNT];

// Initialize text manager
void text_manager_init() {
    for (u8 i = 0; i < NUM_CNT; i++) {
        // Initialize sprites for each number
        struct sprite* money_num = sprite_manager_new_sprite();
        struct sprite* health_num = sprite_manager_new_sprite();
        if (money_num == NULL || health_num == NULL) {
            exit(1);
        }

        money_num_array[i] = money_num;
        health_num_array[i] = health_num;
    }
}

// Update numbers for health and money
void text_manager_update(s32 health, s32 money) {
    // Update sprite attributes
    for (u8 i = 0; i < NUM_CNT; i++) {
        struct sprite* money_num = money_num_array[i];
        struct sprite* health_num = health_num_array[i];

        s8 money_digit;
        if (money >= 999) {
            money_digit = 9;
        } else {
            money_digit = _get_digit(money, NUM_CNT - i - 1);
        }
        money_num -> attr1 =
            ((NUM_MONEY_Y) & 0xff) |
            (1 << 13) | // 256 colors
            (0 << 14);  // Shape
        if (money_digit < 0) {
            money_num -> attr2 =
                (240) | // Hide number
                (0 << 14);  // Size
        } else {
            money_num -> attr2 =
                ((NUM_X + (i * NUM_WIDTH)) & 0x1ff) |
                (0 << 14);  // Size
        }
        money_num -> attr3 =
            ((NUM_TILE + (money_digit * 2)) & 0x3ff) | // Tile index
            (1 << 12);  // Priority

        s8 health_digit;
        if (health >= 999) {
            health_digit = 9;
        } else {
            health_digit = _get_digit(health, NUM_CNT - i - 1);
        } 
        health_num -> attr1 =
            ((NUM_HEALTH_Y) & 0xff) |
            (1 << 13) | // 256 colors
            (0 << 14);  // Shape
        if (health_digit < 0) {
            health_num -> attr2 =
                (240) | // Hide number
                (0 << 14);  // Size
        } else {
            health_num -> attr2 =
                ((NUM_X + (i * NUM_WIDTH)) & 0x1ff) |
                (0 << 14);  // Size
        }
        health_num -> attr3 =
            ((NUM_TILE + (health_digit * 2)) & 0x3ff) | // Tile index
            (1 << 12);  // Priority
    }
}

// Get a digit of a number - return -1 if digit should be hidden
s8 _get_digit(s32 num, u8 digit) {
    s32 reduced_num = num;
    for (u8 i = 0; i < digit; i++) {
        reduced_num = reduced_num / 10;
    }
    if (reduced_num <= 0 && digit > 0) {
        return -1;
    }
    return reduced_num % 10;
}
