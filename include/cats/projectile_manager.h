#ifndef PROJECTILE_MANAGER_H
#define PROJECTILE_MANAGER_H

#include "datatypes/projectile.h"

#define PROJECTILE_LIMIT 10

// Initialize projectile manager
void projectile_manager_init();

// Update all projectiles and sprites
void projectile_manager_update();

// Add a new projectile
bool projectile_manager_add_projectile(struct projectile projectile);

#endif
