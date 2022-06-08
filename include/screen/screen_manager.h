#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include "screen/tilemap.h"
#include "screen/text_manager.h"

// Initialize the screen.
void screen_manager_init();

// Update the screen.
void screen_manager_update(s32 health, s32 money);

#endif
