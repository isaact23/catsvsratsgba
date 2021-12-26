#include "data/data_path.h"

// Format: (x, y), (x, y)...
// Top left path
const struct path DATA_PATH_0 =
{
    .id = 0,
    .length = 23,
    .coords = {
        -1, 1,  0,  1,  1,  1,  2,  1,  2,  2,  2,  3,  3,  3,  4, 3,
        4, 2,  4,  1,  5,  1,  6,  1,  7,  1,  8,  1,  9,  1,  9, 2,
        9, 3,  10, 3,  11, 3,  11, 2,  11, 1,  11, 0,  11, -1,
    }
};

// Bottom left segment
const struct path DATA_PATH_1 =
{
    .id = 1,
    .length = 11,
    .coords = {
        -1, 7,  0, 7,  1, 7,  1, 6,  1, 5,  2, 5,  3, 5,  4, 5,
        4, 6,  5, 6,  6, 6,
    }
};

// Top middle segment
const struct path DATA_PATH_2 =
{
    .id = 2,
    .length = 8,
    .coords = {
        6, -1, 6, 0,  6, 1,  6, 2,  6, 3,  6, 4,  6, 5,  6, 6,
    }
};

// Cheese segment
const struct path DATA_PATH_3 =
{
    .id = 3,
    .length = 6,
    .coords = {
        6, 6,  6, 7,  6, 8,  7, 8,  8, 8,  8, 7,
    }
};
