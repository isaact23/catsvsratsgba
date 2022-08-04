#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "gba_types.h"
#include "cat.h"
#include "sprite.h"

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

enum projectile_type {
    PROJECTILE_PAW,
    PROJECTILE_ARROW,
    PROJECTILE_MAGIC
};

struct projectile {
    u16 x;
    u16 y;
    u16 speed;
    u16 damage;
    u16 tile;
    u8 shape;
    struct sprite* sprite;
    struct rat* target;
    enum projectile_type type;
};

#endif
