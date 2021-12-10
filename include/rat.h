#ifndef RAT_H
#define RAT_H

#include <stdint.h>

struct Rat {
    uint8_t type; // 0 - default, 1 - fast, 2 - fat, 3 - robot, 4 - demon
    uint32_t progress;
    uint16_t x;
    uint16_t y;
};

#endif
