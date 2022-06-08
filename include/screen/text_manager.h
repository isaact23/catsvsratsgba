#ifndef TEXT_MANAGER_H
#define TEXT_MANAGER_H

#define NUM_CNT 3
#define NUM_WIDTH 5
#define NUM_X 225
#define NUM_MONEY_Y 140
#define NUM_HEALTH_Y 148
#define NUM_TILE 320

#include "gba_types.h"
#include "sprites/sprite_manager.h"

// Initialize text manager
void text_manager_init();

// Update numbers for health and money
void text_manager_update(s32 health, s32 money);

#endif
