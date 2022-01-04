#include "pointer_array.h"

// Initialize a pointer array. Pass statically allocated memory to parameters.
void pointer_array_init(struct pointer_array* pointer_array, u16 elem_size, u16 capacity, void* array_mem, u16* index_mem) {
    pointer_array -> array = array_mem;
    pointer_array -> deleted_indices = index_mem;

    pointer_array -> elem_size = elem_size;
    pointer_array -> capacity = capacity;

    pointer_array -> item_count = 0;
    pointer_array -> deleted_count = 0;
}

// Add an item to a pointer array
void* pointer_array_add(struct pointer_array* pointer_array, void* item) {
    // Use the spot from the deleted sprite stack if possible
    u16 index;
    if (pointer_array -> deleted_count > 0) {
        pointer_array -> deleted_count--;
        index = pointer_array -> deleted_indices[pointer_array -> deleted_count];
    } else {
        index = pointer_array -> item_count;
    }

    // Insert the item in the array
    u8* char_array = (u8*) pointer_array -> array;
    u8* char_item = (u8*) item;
    for (u16 i = 0; i < pointer_array -> elem_size; i++) {
        char_array[i] = char_item[i];
    }

    // Return the item's address in the array
    void* new_item = &(pointer_array -> array[index]);
    return new_item;
}

// Remove an item from a pointer array
void pointer_array_remove(struct pointer_array* pointer_array, void* item) {
    if (pointer_array -> deleted_count >= pointer_array -> capacity) {
        exit(1);
    }
    u16 deleted_index = (u16) ((item - (pointer_array -> array)) / (pointer_array -> elem_size));
    pointer_array -> deleted_indices[pointer_array -> deleted_count] = deleted_index;
    pointer_array -> deleted_count++;
}
