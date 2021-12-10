#include "rat_manager.h"

struct RatManager ratManager;

// Initialize rat manager
void rat_manager_init() {
    for (uint32_t i = 0; i < RAT_LIMIT; i++) {
        struct Rat emptyRat = {0, 0, 0, 0};
        ratManager.ratArray[i] = emptyRat;
    }
}