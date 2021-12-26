#include "main.h"

volatile uint16_t* vcount = (volatile uint16_t*) 0x4000006;

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
