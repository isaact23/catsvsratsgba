#ifndef TILEMAP_H
#define TILEMAP_H

#include <stdint.h>
#include <stdlib.h>

#include "data/data_tilemap.h"
#include "data/data_tilemap_win.h"
#include "data/image_tiles.h"

#include "gba_types.h"
#include "gba_video.h"

// Set up tilemap
void tilemap_init();

#endif