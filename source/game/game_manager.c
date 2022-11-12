#include "game/game_manager.h"

// Time elapsed since beginning of a round
u32 time_elapsed = 0;

// Rounds
const struct round* curr_round;

// Lives and money
s32 health;
s32 money;

// Initialize game manager
void game_manager_init() {
    health = 100;
    money = 100;

    audio_manager_init();
    sprite_manager_init();

    screen_manager_init(&sprite_manager_new_sprite);
    interact_manager_init(&sprite_manager_new_sprite, &cat_manager_add_cat, &cat_manager_remove_cat,
        &cat_manager_get_price, &game_manager_add_money, &game_manager_get_money, &cat_manager_get_tile);

    rat_manager_init(&sprite_manager_new_sprite, &sprite_manager_remove_sprite, &game_manager_decrease_health);
    cat_manager_init(&sprite_manager_new_sprite, &sprite_manager_remove_sprite,
        &rat_manager_get_rats, &rat_manager_get_rat_count);

    game_manager_start_round(0);
}

// Update game manager every frame
void game_manager_update() {
    audio_manager_update();
    sprite_manager_update();

    screen_manager_update(health, money);
    interact_manager_update();

    rat_manager_update(curr_round, time_elapsed);
    cat_manager_update();
    
    time_elapsed++;
}

// Start a round
void game_manager_start_round(u16 round) {
    time_elapsed = 0;
    curr_round = data_rounds_get(round);

    if (health <= 0) {
        exit(1); // GAME OVER SCREEN
    }
}

// Decrease health (cheese) by 1
void game_manager_decrease_health() {
    health--;
    if (health <= 0) {
        health = 0;
    }
}

// Add money.
void game_manager_add_money(s32 amount) {
    s32 sum = money + amount;
    if (sum < 0) {
        sum = 0;
    }
}

// Get current amount of money.
s32 game_manager_get_money() {
    return money;
}
