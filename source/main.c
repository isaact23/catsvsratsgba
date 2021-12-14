#include "main.h"

int main() {
    screen_manager_init();
    struct Rat rat1 = {0, 0, 25, 25};
    rat_manager_add_rat(rat1);
    rat_manager_render();

    while (1) {
        
    }
}
