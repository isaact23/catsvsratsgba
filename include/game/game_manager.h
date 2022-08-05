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

// Decrease health (cheese) by 1
void game_manager_decrease_health();

// Change money, or return false if money would become negative.
bool game_manager_add_money(s32 amount);

// Get current amount of money.
s32 game_manager_get_money();

// Delete a sprite. Return true if successful.
bool game_manager_remove_sprite(struct sprite* sprite);

// Get array of rats from rat manager
struct rat* game_manager_get_rats();

// Get rat count from rat manager
u8 game_manager_get_rat_count();

#endif
