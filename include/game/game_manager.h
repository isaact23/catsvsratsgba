#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "screen/screen_manager.h"
#include "sprites/sprite_manager.h"

#include "gba_types.h"

// Initialize game manager
void game_manager_init();

// Update game manager every frame
void game_manager_update();

// Start a round
void game_manager_start_round(u16 round);

#endif