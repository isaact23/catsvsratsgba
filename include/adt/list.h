#ifndef LIST_H
#define LIST_H

#include "gba_types.h"

// The data stored in one list.
struct list {

};

// Create an empty lit.
struct list list_create();

// Add an item.
bool list_add(struct list list);

// Remove an item.
bool list_remove(struct list list);

#endif
