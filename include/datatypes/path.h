#ifndef PATH_H
#define PATH_H

#include <stdint.h>

struct path {
    uint8_t id;
    uint16_t length;
    int8_t coords [];
};

#endif
