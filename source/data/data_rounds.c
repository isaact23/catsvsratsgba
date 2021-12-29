#include "data/data_rounds.h"

const struct round* data_rounds_get(u16 round) {
    if (round == 0) {
        return &DATA_ROUNDS_ROUND0;
    }
    exit(1);
}

const struct round DATA_ROUNDS_ROUND0 = {
    .round_id = 0,
    .rat_count = 4,
    .rat_spawn_entries = {
        {
            .spawn_time = 0, 
            .rat_type = 0,
            .path_id = 0
        },
        {60, 0, 0}, {120, 0, 1}, {150, 1, 1},
        /*{180, 1, 1},
        {240, 1, 1},
        {300, 1, 1},
        {360, 1, 1},
        {420, 1, 1},
        {480, 1, 1},
        {540, 1, 1},
        {600, 1, 1},
        {660, 1, 1},
        {720, 1, 1},
        {780, 1, 1},
        {860, 1, 1},*/
    }
};
