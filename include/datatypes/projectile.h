#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "gba_types.h"
#include "cat.h"
#include "sprite.h"

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
