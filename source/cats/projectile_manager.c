#include "cats/projectile_manager.h"

// TODO: Merge with cat_storage in a generic array

u8 projectile_count = 0;
struct projectile projectiles [PROJECTILE_LIMIT];

// Initialize projectile manager
void projectile_manager_init() {

}

// Update all projectiles and sprites
void projectile_manager_update() {

}

// Add a new projectile
bool projectile_manager_add_projectile(struct projectile projectile) {

    // If projectile array is full, we cannot add a new projectile.
    if (projectile_count >= PROJECTILE_LIMIT) {
        return false;
    }

    projectiles[projectile_count] = projectile;
    return true;
}

// Remove a projectile.

