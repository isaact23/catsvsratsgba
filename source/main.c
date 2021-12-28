#include "main.h"

vu16* dispstat = (vu16*) 0x4000004;
vu16* vcount   = (vu16*) 0x4000006;

vu32* interrupt_enable   = (vu32*) 0x4000208;
vu16* interrupt_select   = (vu16*) 0x4000200;
vu16* interrupt_state    = (vu16*) 0x4000202;

vu32* interrupt_callback = (vu32*) 0x3007ffc;

void vsync() {
    while (*vcount < 160) {}
}

void on_vblank() {
    // Disable / save interrupts
    *interrupt_enable = 0;
    u16 temp = *interrupt_state;
    
    // Execute game logic
    sprite_manager_update();

    // Restore / enable interrupts
    *interrupt_state = temp;
    *interrupt_enable = 1;
}

int main() {

    // Initialize game
    screen_manager_init();
    sprite_manager_init();
    sprite_manager_start_round(0);

    // Initialize interrupts
    *interrupt_enable = 0;
    *interrupt_callback = (u32) &on_vblank;
    *interrupt_select |= 0x1; // lcd vblank interrupt enable
    *dispstat |= 0x8; // vblank IRQ enable
    *interrupt_enable = 1;

    while (1) {}
}
