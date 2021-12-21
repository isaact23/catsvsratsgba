#ifndef DATA_PATH_H
#define DATA_PATH_H

#include <stdint.h>

#define DATA_PATH_LENGTH0 23
#define DATA_PATH_LENGTH1 11
#define DATA_PATH_LENGTH2 8
#define DATA_PATH_LENGTH3 6

// Format: (x, y), (x, y)...
extern const int8_t DATA_PATH_COORDS0 []; // Top left path
extern const int8_t DATA_PATH_COORDS1 []; // Bottom left segment
extern const int8_t DATA_PATH_COORDS2 []; // Top middle segment
extern const int8_t DATA_PATH_COORDS3 []; // Cheese segment


#endif
