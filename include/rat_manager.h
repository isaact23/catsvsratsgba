#ifndef RAT_MANAGER_H
#define RAT_MANAGER_H

#include "rat.h"
#include <stdint.h>

#define RAT_LIMIT 30 // Statically allocate maximum memory for rats

struct RatManager {
    struct Rat ratArray[RAT_LIMIT];
};

// Initialize rat manager
void rat_manager_init();

#endif
