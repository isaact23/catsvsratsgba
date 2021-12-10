#include "rat_manager.h"

struct RatManager ratManager;

// Initialize rat manager
void rat_manager_init() {
    ratManager.ratCount = 0;
}

// Add a new rat
void rat_manager_add_rat(struct Rat rat) {
    if (ratManager.ratCount >= RAT_LIMIT) {
        exit(1);
    }
    ratManager.ratArray[ratManager.ratCount] = rat;
    ratManager.ratCount++;
}
