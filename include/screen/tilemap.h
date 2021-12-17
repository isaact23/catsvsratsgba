#ifndef TILEMAP_H
#define TILEMAP_H

#include <stdint.h>
#include <stdlib.h>

#include "data/data_tilemap.h"
#include "data/image_tiles.h"

// Return pointer to one of 4 character blocks
volatile uint16_t* char_block(uint16_t block);

// Return pointer to one of 32 screen blocks
volatile uint16_t* screen_block(uint16_t block);

// Set up tilemap
void tilemap_init();

#endif