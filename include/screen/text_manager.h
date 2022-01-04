#ifndef TEXT_MANAGER_H
#define TEXT_MANAGER_H

#include "gba_types.h"

// Initialize text manager
void text_manager_init();

// Update numbers for health and money
void text_manager_update(u32 health, u32 money);

#endif
