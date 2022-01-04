#include "game/game_manager.h"

// Time elapsed since beginning of a round
u32 time_elapsed = 0;

// Rounds
const struct round* curr_round;

// Lives and money
u32 catnip;
u32 cheese;

// Initialize game manager
void game_manager_init() {
    catnip = 30;
    cheese = 100;

    audio_manager_init();
    screen_manager_init();
    sprite_manager_init();

    game_manager_start_round(0);
}

// Update game manager every frame
void game_manager_update() {
    audio_manager_update();
    sprite_manager_update();

    rat_manager_spawn(curr_round, time_elapsed);
    rat_manager_update(time_elapsed);

    cat_manager_update(time_elapsed);
    
    time_elapsed++;
}

// Start a round
void game_manager_start_round(u16 round) {
    time_elapsed = 0;
    curr_round = data_rounds_get(round);
}