#include "timer_manager.h"

volatile uint16_t* timer0_counter = (volatile uint16_t*) 0x4000100;
volatile uint16_t* timer0_control = (volatile uint16_t*) 0x4000102;

// Set up timer for beginning of a round
void timer_manager_start() {
    
}