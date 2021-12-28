#ifndef TILEMAP_H
#define TILEMAP_H

#include <stdint.h>
#include <stdlib.h>

#include "data/data_tilemap.h"
#include "data/image_tiles.h"
#include "gba_types.h"

// Return pointer to one of 4 character blocks
vu16* char_block(u16 block);

// Return pointer to one of 32 screen blocks
vu16* screen_block(u16 block);

// Set up tilemap
void tilemap_init();

#endif