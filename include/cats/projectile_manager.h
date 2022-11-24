#ifndef PROJECTILE_MANAGER_H
#define PROJECTILE_MANAGER_H

#include <stdlib.h>

#include "datatypes/projectile.h"
#include "datatypes/rat.h"

#include "gba_sprites.h"

#define PROJECTILE_LIMIT 10

#define HIT_RADIUS 6

#define PROJECTILE_PAW_TILE 136
#define PROJECTILE_ARROW_TILE 140
#define PROJECTILE_MAGIC_TILE 170

#define PROJECTILE_PAW_SPEED 1
#define PROJECTILE_ARROW_SPEED 2
#define PROJECTILE_MAGIC_SPEED 2

#define PROJECTILE_PAW_DAMAGE 1
#define PROJECTILE_ARROW_DAMAGE 2
#define PROJECTILE_MAGIC_DAMAGE 3

// Initialize projectile manager
void projectile_manager_init(bool (*sprite_manager_remove_sprite)(struct sprite* sprite));

// Update all projectiles and sprites
void projectile_manager_update();

// Add a new projectile
bool projectile_manager_add_projectile
    (enum projectile_type type, u16 x, u16 y, struct sprite* sprite, struct rat* target);

#endif
