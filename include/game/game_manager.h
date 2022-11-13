#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <stdlib.h>

#include "audio/audio_manager.h"
#include "interact/interact_manager.h"
#include "screen/screen_manager.h"
#include "sprites/sprite_manager.h"

#include "gba_types.h"

enum game_state {
    MAIN_MENU = 0,
    TUTORIAL,
    CREDITS,
    STANDBY,
    FIGHT,
    LOSE,
    WIN
};

// Initialize game manager
void game_manager_init();

// Update game manager every frame
void game_manager_update();

// Get current game state
enum game_state game_manager_get_state();

// Start the next round
bool game_manager_next_round();

// Finish the current round.
void game_manager_end_round();

// Decrease health (cheese) by 1
void game_manager_decrease_health();

// Add money.
void game_manager_add_money(s32 amount);

// Get current amount of money.
s32 game_manager_get_money();

#endif
