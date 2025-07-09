#ifndef RAT_MANAGER_H
#define RAT_MANAGER_H

#include <stdlib.h>

#include "data/data_path.h"
#include "datatypes/rat.h"
#include "datatypes/round.h"

#include "gba_sprites.h"
#include "gba_types.h"

#define RAT_LIMIT 64

#define HP_TILE 64
#define HP_TILE_COUNT 14 // minus 1

// Initialize rat manager
void rat_manager_init(
    struct sprite* (*sprite_manager_new_sprite)(),
    bool (*sprite_manager_remove_sprite)(struct sprite* sprite),
    void (*game_manager_decrease_health)(),
    void (*game_manager_end_round)()
);

// Update rats
void rat_manager_update(const struct round* curr_round, u32 time_elapsed);

// Get array of rats
struct rat* rat_manager_get_rats();

// Reset rat manager for new round
void rat_manager_reset();

#endif
