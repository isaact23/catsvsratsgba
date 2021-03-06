#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <stdlib.h>

#include "audio/audio_manager.h"
#include "interact/interact_manager.h"
#include "screen/screen_manager.h"
#include "sprites/sprite_manager.h"

#include "gba_types.h"

// Initialize game manager
void game_manager_init();

// Update game manager every frame
void game_manager_update();

// Start a round
void game_manager_start_round(u16 round);

// Get a sprite from the sprite manager
struct sprite* game_manager_new_sprite();

// Decrease health (cheese) by 1
void game_manager_decrease_health();

// Change money, or return false if money would become negative.
bool game_manager_add_money(s32 amount);

// Get current amount of money.
s32 game_manager_get_money();

#endif
