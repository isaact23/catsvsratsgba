#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "gba_types.h"
#include "cat.h"

enum projectile_type {
    PAW,
    ARROW,
    MAGIC
};

struct projectile {
    u8 x;
    u8 y;
    struct cat target;
    enum projectile_type type;
};

#endif
