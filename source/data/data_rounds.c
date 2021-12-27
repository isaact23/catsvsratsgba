#include "data/data_rounds.h"

const struct round* data_rounds_get(uint16_t round) {
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
        {60, 0, 0}, {120, 0, 1}, {150, 1, 1}
    }
};
