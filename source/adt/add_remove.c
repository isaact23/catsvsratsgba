// A container that can both add and remove objects, address-preserving.
#include "add_remove.h"

// Create an empty container.
struct add_remove add_remove_create() {
    struct add_remove container;
    return container;
}
