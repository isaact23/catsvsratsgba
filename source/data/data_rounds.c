#include "data/data_rounds.h"

const struct round* data_rounds_get(u16 round) {
    if (round >= ROUND_COUNT) {
        exit(1);
    }
    if (round == 0) {
        return &DATA_ROUNDS_ROUND0;
    } else if (round == 1) {
        return &DATA_ROUNDS_ROUND1;
    } else if (round == 2) {
        return &DATA_ROUNDS_ROUND2;
    }
    exit(1);
}

const struct round DATA_ROUNDS_ROUND0 = {
    .round_id = 0,
    .rat_count = 3,
    .rat_spawn_entries = {
        {0, RAT_NORMAL, 0},
        {30, RAT_NORMAL, 0},
        {60, RAT_NORMAL, 1},
    }
};

const struct round DATA_ROUNDS_ROUND1 = {
    .round_id = 1,
    .rat_count = 10,
    .rat_spawn_entries = {
        {0, RAT_NORMAL, 0},
        {20, RAT_NORMAL, 0},
        {40, RAT_NORMAL, 0},
        {60, RAT_NORMAL, 0},
        {80, RAT_NORMAL, 0},
        {100, RAT_NORMAL, 1},
        {120, RAT_NORMAL, 1},
        {140, RAT_NORMAL, 1},
        {160, RAT_NORMAL, 1},
        {180, RAT_NORMAL, 1},
    }
};

const struct round DATA_ROUNDS_ROUND2 = {
    .round_id = 2,
    .rat_count = 10,
    .rat_spawn_entries = {
        {0, RAT_NORMAL, 0},
        {30, RAT_NORMAL, 0},
        {35, RAT_FAST, 0},
        {60, RAT_NORMAL, 1},
        {90, RAT_NORMAL, 1},
        {120, RAT_FAST, 1},
        {135, RAT_FAST, 1},
        {150, RAT_FAST, 1},
        {160, RAT_NORMAL, 0},
        {170, RAT_NORMAL, 1},
    }
};
