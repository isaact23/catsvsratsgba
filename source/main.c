#include "main.h"

int main() {

    // Initialize game
    screen_manager_init();
    sprite_manager_init();
    sprite_manager_start_round(0);

    // Initialize vblank interrupt
    irqInit();
    irqEnable(IRQ_VBLANK);

    while (1) {
        VBlankIntrWait();
        sprite_manager_update();
    }
}
