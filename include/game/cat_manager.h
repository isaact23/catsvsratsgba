#ifndef CAT_MANAGER_H
#define CAT_MANAGER_H

#include "datatypes/cat.h"

#include "gba_types.h"

#define CAT_LIMIT 20

// Initialize cat manager
void cat_manager_init();

// Update cat manager
void cat_manager_update(u32 time_elapsed);

#endif
