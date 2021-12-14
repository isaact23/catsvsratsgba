#include "main.h"

int main() {
    screen_manager_init();
    sprite_manager_init();
    sprite_manager_add_rat();
    sprite_manager_update_rats();
    sprite_manager_update();

    while (1) {
        
    }
}
