#ifndef RAT_MANAGER_H
#define RAT_MANAGER_H

#include <stdlib.h>

#include "data/data_path.h"
#include "datatypes/rat.h"
#include "datatypes/round.h"
#include "game/game_manager.h"

#include "gba_types.h"

#define RAT_LIMIT 64

#define HP_TILE 64
#define HP_TILE_COUNT 14 // minus 1

// Initialize rat manager
void rat_manager_init();

// Update rats
void rat_manager_update(const struct round* curr_round, u32 time_elapsed);

// Get array of rats
struct rat* rat_manager_get_rats();

// Get rat count
u8 rat_manager_get_rat_count();

// If enough time has elapsed, spawn a new rat
void _rat_manager_spawn(const struct round* curr_round, u32 time_elapsed);

// Update path position of a rat
void _rat_manager_update_rat_position(struct rat* rat, u32 time_elapsed);

#endif
