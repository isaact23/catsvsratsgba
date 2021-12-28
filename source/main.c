#include "main.h"

vu16* vcount = (vu16*) 0x4000006;

// vu32* interrupt_enable = (vu32*) 

void vsync() {
    while (*vcount < 160) {}
}

int main() {
    screen_manager_init();
    sprite_manager_init();
    sprite_manager_start_round(0);

    while (1) {
        vsync();
        sprite_manager_update();
    }
}
