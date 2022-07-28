#ifndef PROJECTILE_MANAGER_H
#define PROJECTILE_MANAGER_H

#include <stdlib.h>

#include "datatypes/projectile.h"
#include "datatypes/rat.h"

#define PROJECTILE_LIMIT 10

// Initialize projectile manager
void projectile_manager_init();

// Update all projectiles and sprites
void projectile_manager_update();

// Add a new projectile
bool projectile_manager_add_projectile
    (enum projectile_type type, u16 x, u16 y, struct sprite* sprite, struct rat* target);

#endif
