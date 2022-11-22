#include "game/game_manager.h"

// Game state
enum game_state state;

// Time elapsed since beginning of a round
u32 time_elapsed = 0;

// Rounds
u16 round_number = 0;
const struct round* round_data;

// Lives and money
s32 health;
s32 money;

// Start a round
static void _game_manager_start_round(u16 round);
// Switch game mode
static void _game_manager_switch_mode(enum game_state new_state);

// Initialize game manager
void game_manager_init() {
    // Initialize health and money
    health = 100;
    money = 100;

    // Initialize sub-systems
    audio_manager_init();
    sprite_manager_init();

    screen_manager_init(&sprite_manager_new_sprite);
    interact_manager_init(&game_manager_next_round, &sprite_manager_new_sprite, &cat_manager_add_cat, &cat_manager_remove_cat,
        &cat_manager_get_price, &game_manager_add_money, &game_manager_get_money, &cat_manager_get_tile);

    rat_manager_init(&sprite_manager_new_sprite, &sprite_manager_remove_sprite, &game_manager_decrease_health,
        &game_manager_end_round);
    cat_manager_init(&sprite_manager_new_sprite, &sprite_manager_remove_sprite,
        &rat_manager_get_rats);

    // Setup round 0
    _game_manager_switch_mode(WIN);
    //game_manager_start_round(round_number);
}

// Update game manager every frame
void game_manager_update() {
    audio_manager_update();
    sprite_manager_update();

    screen_manager_update(health, money);
    interact_manager_update();

    rat_manager_update(round_data, time_elapsed);
    cat_manager_update();
    
    time_elapsed++;
}

// Get current game state
enum game_state game_manager_get_state() {
    return state;
}

// Start the next round. Return true if successful.
bool game_manager_next_round() {
    if (state == STANDBY) {
        _game_manager_switch_mode(FIGHT);
        _game_manager_start_round(round_number);
        return true;
    }
    return false;
}

// Finish the current round.
void game_manager_end_round() {
    round_number++;
    if (state == FIGHT) {
        if (round_number >= ROUND_COUNT) {
            _game_manager_switch_mode(WIN);
        } else {
            _game_manager_switch_mode(STANDBY);
        }
    }
}

// Decrease health (cheese) by 1
void game_manager_decrease_health() {
    health--;
    if (health <= 0) {
        health = 0;
        if (state == FIGHT) {
            _game_manager_switch_mode(LOSE);
        }
    }
}

// Add money.
void game_manager_add_money(s32 amount) {
    s32 sum = money + amount;
    if (sum < 0) {
        sum = 0;
    }
    money = sum;
}

// Get current amount of money.
s32 game_manager_get_money() {
    return money;
}


// Start a round
static void _game_manager_start_round(u16 round) {
    time_elapsed = 0;
    round_data = data_rounds_get(round);
    round_number = round;
}

// Switch game mode
static void _game_manager_switch_mode(enum game_state new_state) {
    state = new_state;
    switch (new_state) {
        case MAIN_MENU: {
            return;
        }
        case TUTORIAL: {
            return;
        }
        case CREDITS: {
            return;
        }
        case STANDBY: {
            audio_manager_play_sound(MUSIC_BETWEEN_ROUNDS);
            return;
        }
        case FIGHT: {
            audio_manager_play_sound(MUSIC_DURING_ROUNDS);
            return;
        }
        case LOSE: {
            audio_manager_stop_sounds();
            audio_manager_play_sound(MUSIC_LOSE);
            screen_manager_lose_gui();
            return;
        }
        case WIN: {
            audio_manager_stop_sounds();
            audio_manager_play_sound(MUSIC_WIN);
            screen_manager_win_gui();
            return;
        }
        default: {
            return;
        }
    }
}