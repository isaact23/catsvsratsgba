#ifndef PATH_H
#define PATH_H

#include "gba_types.h"

struct path {
    u8 id;
    u16 length;
    s8 coords [];
};

#endif
