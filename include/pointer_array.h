// A pointer array stores items in a contiguous memory block, managing the
// addition and deletion of elements while maintaining the position of
// existing elements in the array.

#ifndef POINTER_ARRAY_H
#define POINTER_ARRAY_H

#include <stdlib.h>

#include "gba_types.h"

struct pointer_array {
    void* array;
    u16 elem_size;
    u16 capacity;
    u16 item_count;
    u16* deleted_indices;
    u16 deleted_count;
};

// Initialize a pointer array. Pass memory to parameter mem.
void pointer_array_init(struct pointer_array* pointer_array, u16 elem_size, u16 capacity, void* array_mem, u16* index_mem);

// Add an item to a pointer array and return its address
void* pointer_array_add(struct pointer_array* pointer_array, void* item);

// Remove an item from a pointer array
void pointer_array_remove(struct pointer_array* pointer_array, void* item);

#endif
