#ifndef RAT_MANAGER_H
#define RAT_MANAGER_H

#include "rat.h"
#include <stdint.h>
#include <stdlib.h>

#define RAT_LIMIT 30 // Statically allocate maximum memory for rats

struct RatManager {
    struct Rat ratArray[RAT_LIMIT];
    uint32_t ratCount;
};

// Initialize rat manager
void rat_manager_init();

// Add a new rat
void rat_manager_add_rat(struct Rat rat);

#endif
