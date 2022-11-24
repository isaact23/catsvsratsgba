#include "screen/text_manager.h"

struct sprite* money_num_array [NUM_CNT];
struct sprite* health_num_array [NUM_CNT];

// Get a digit of a number - return -1 if digit should be hidden
static s8 _get_digit(s32 num, u8 digit);

// Initialize text manager
void text_manager_init(struct sprite* (*new_sprite)()) {

    for (u8 i = 0; i < NUM_CNT; i++) {
        // Initialize sprites for each number
        struct sprite* money_num = new_sprite();
        struct sprite* health_num = new_sprite();
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
        money_num -> attr0 =
            OBJ_Y(NUM_MONEY_Y) |
            ATTR0_COLOR_256 |
            ATTR0_SQUARE;
        if (money_digit < 0) {
            money_num -> attr1 =
                OBJ_X(240) | // Hide number
                ATTR1_SIZE_8;
        } else {
            money_num -> attr1 =
                OBJ_Y(NUM_X + (i * NUM_WIDTH)) |
                ATTR1_SIZE_8;
        }
        money_num -> attr2 =
            OBJ_CHAR(NUM_TILE + (money_digit * 2)) |
            ATTR2_PRIORITY(1);

        s8 health_digit;
        if (health >= 999) {
            health_digit = 9;
        } else {
            health_digit = _get_digit(health, NUM_CNT - i - 1);
        } 
        health_num -> attr0 =
            OBJ_Y(NUM_HEALTH_Y) |
            ATTR0_COLOR_256 |
            ATTR0_SQUARE;
        if (health_digit < 0) {
            health_num -> attr1 =
                OBJ_X(240) | // Hide number
                ATTR1_SIZE_8;
        } else {
            health_num -> attr1 =
                OBJ_X(NUM_X + (i * NUM_WIDTH)) |
                ATTR1_SIZE_8;
        }
        health_num -> attr2 =
            OBJ_CHAR(NUM_TILE + (health_digit * 2)) |
            ATTR2_PRIORITY(1);
    }
}

// Get a digit of a number - return -1 if digit should be hidden
static s8 _get_digit(s32 num, u8 digit) {
    s32 reduced_num = num;
    for (u8 i = 0; i < digit; i++) {
        reduced_num = reduced_num / 10;
    }
    if (reduced_num <= 0 && digit > 0) {
        return -1;
    }
    return reduced_num % 10;
}
