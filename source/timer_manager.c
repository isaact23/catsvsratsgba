#include "timer_manager.h"

vu16* timer0_counter = (vu16*) 0x4000100;
vu16* timer0_control = (vu16*) 0x4000102;

// Set up timer for beginning of a round
void timer_manager_start() {
    
}