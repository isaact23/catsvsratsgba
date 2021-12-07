// Initialize tilemap with paths, bricks and side panel

#ifndef TILEMAP_H
#define TILEMAP_H

#include <stdlib.h>
#include "gba_int.h"
#include "raw/images/gui/map/tiles25.h"
#include "raw/tilemap_data.h"

// Return pointer to one of 4 character blocks
volatile u16* tilemap_charBlock(u16 block);

// Return pointer to one of 32 screen blocks
volatile u16* tilemap_screenBlock(u16 block);

// Set up tilemap in GBA memory
void tilemap_init();

#endif
