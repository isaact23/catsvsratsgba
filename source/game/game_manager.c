#include "game/game_manager.h"

// Time elapsed since beginning of a round
u32 time_elapsed = 0;

// Rounds
const struct round* curr_round;

// Lives and money
u32 health;
u32 money;

// Initialize game manager
void game_manager_init() {
    health = 100;
    money = 30;

    audio_manager_init();
    screen_manager_init();
    sprite_manager_init();
    text_manager_update(health, money);

    game_manager_start_round(0);
}

// Update game manager every frame
void game_manager_update() {
    audio_manager_update();
    sprite_manager_update();

    rat_manager_spawn(curr_round, time_elapsed);
    rat_manager_update(time_elapsed);
    cat_manager_update(time_elapsed);

    text_manager_update(health, money);
    
    time_elapsed++;
}

// Start a round
void game_manager_start_round(u16 round) {
    time_elapsed = 0;
    curr_round = data_rounds_get(round);
}

// Get a sprite from the sprite manager
struct sprite* game_manager_new_sprite() {
    return sprite_manager_new_sprite();
}
