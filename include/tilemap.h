#ifndef TILEMAP_H
#define TILEMAP_H

#include <stdlib.h>

#include "gba_int.h"

#include "raw/tilemap_data.h"
#include "raw/images/gui/map/tiles25.h"

// Return pointer to one of 4 character blocks
volatile u16* char_block(u16 block);

// Return pointer to one of 32 screen blocks
volatile u16* screen_block(u16 block);

// Set up tilemap
void tilemap_init();

#endif