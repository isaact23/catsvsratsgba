#include "main.h"

volatile uint16_t* sprite_palette      = (volatile uint16_t*) 0x5000200;
volatile uint16_t* sprite_image_vram   = (volatile uint16_t*) 0x6010000;

int main() {
    tilemap_init();
    rat_manager_init();

    // http://ianfinlayson.net/class/cpsc305/notes/15-sprites

    while (1) {
        
    }
}
