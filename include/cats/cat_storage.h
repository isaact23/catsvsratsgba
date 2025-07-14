#ifndef CAT_STORAGE_H
#define CAT_STORAGE_H

#include <stdlib.h>
#include "datatypes/cat.h"
#include "gba_types.h"
#include "sprites/sprite_manager.h"

#define GRID_WIDTH 13
#define GRID_HEIGHT 10
#define CAT_LIMIT 20

// Data structure for storing cats
struct cat_storage {
    struct cat cat_array [CAT_LIMIT];
    u8 cat_count;
};

// Initialize cat array
struct cat_storage cat_storage_new();

// Add a cat - return true if successful.
bool cat_storage_add_cat(struct cat_storage* cat_storage, struct cat new_cat);

// Remove a cat - return true if successful.
bool cat_storage_remove_cat(struct cat_storage* cat_storage, u8 x, u8 y);

#endif
