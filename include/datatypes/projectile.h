#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "gba_types.h"
#include "cat.h"
#include "sprite.h"

#define HIT_RADIUS 3

#define PROJECTILE_PAW_TILE 1
#define PROJECTILE_ARROW_TILE 2
#define PROJECTILE_MAGIC_TILE 3

#define PROJECTILE_PAW_SPEED 1
#define PROJECTILE_ARROW_SPEED 2
#define PROJECTILE_MAGIC_SPEED 2

#define PROJECTILE_PAW_DAMAGE 1
#define PROJECTILE_ARROW_DAMAGE 2
#define PROJECTILE_MAGIC_DAMAGE 3

enum projectile_type {
    PAW,
    ARROW,
    MAGIC
};

struct projectile {
    u16 x;
    u16 y;
    u16 speed;
    u16 damage;
    u16 tile;
    struct sprite* sprite;
    struct rat* target;
    enum projectile_type type;
};

#endif
