#include "main.h"

int main() {
    // Initialize game
    game_manager_init();

    // Initialize vblank interrupt
    irqInit();
    irqEnable(IRQ_VBLANK);

    while (1) {
        VBlankIntrWait();
        game_manager_update();
    }
}
