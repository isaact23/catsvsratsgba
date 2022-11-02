#include "cats/projectile_manager.h"

u8 projectile_count = 0;
struct projectile projectiles [PROJECTILE_LIMIT];

// Initialize projectile manager
void projectile_manager_init() {

}

// Update all projectiles and sprites
void projectile_manager_update() {

    // Iterate through projectiles.
    for (u8 i = 0; i < projectile_count; i++) {
        struct projectile* projectile = &projectiles[i];

        // Get coordinates of projectile and target
        struct rat* target = projectile -> target;
        u16 target_x = target -> x;
        u16 target_y = target -> y;
        u16 proj_x = projectile -> x;
        u16 proj_y = projectile -> y;

        // Move projectile toward target
        if (target_x > proj_x) {
            proj_x += (projectile -> speed);
        } else if (target_x < proj_x) {
            proj_x -= (projectile -> speed);
        }
        if (target_y > proj_y) {
            proj_y += (projectile -> speed);
        } else if (target_y < proj_y) {
            proj_y -= (projectile -> speed);
        }

        // If target is hit, remove projectile
        if ((abs(target_x - proj_x) <= HIT_RADIUS) &&
            (abs(target_y - proj_y) <= HIT_RADIUS))
        {
            // Inflict damage on rat
            target -> hp -= projectile -> damage;
            if (target -> hp <= 0) {
                target -> hp = 0;
            }

            // Remove projectile and sprite
            cat_manager_remove_sprite(projectile -> sprite);
            *projectile = projectiles[projectile_count - 1];
            projectile_count--;
            i--;

        } else {

            // Update projectile sprite OAM 
            struct sprite* sprite = projectile -> sprite;
            sprite -> attr1 = 
                (proj_y & 0xff) |
                (1 << 13) | // Palette mode
                ((projectile -> shape) << 14);
            sprite -> attr2 =
                (proj_x & 0x1ff);
            sprite -> attr3 =
                ((projectile -> tile) & 0x3ff); // Tile index

        }
        
        // Update projectile position
        projectile -> x = proj_x;
        projectile -> y = proj_y;
    }
}

// Add a new projectile
bool projectile_manager_add_projectile
    (enum projectile_type type, u16 x, u16 y, struct sprite* sprite, struct rat* target)
{

    // If projectile array is full, we cannot add a new projectile.
    if (projectile_count >= PROJECTILE_LIMIT) {
        return false;
    }

    // Initialize new projectile
    struct projectile proj;
    proj.type = type;
    proj.x = x;
    proj.y = y;
    proj.sprite = sprite;
    proj.target = target;

    switch (type) {
        case PROJECTILE_PAW: {
            proj.speed  = PROJECTILE_PAW_SPEED;
            proj.damage = PROJECTILE_PAW_DAMAGE;
            proj.tile   = PROJECTILE_PAW_TILE;
            proj.shape = 0;
            break;
        };
        case PROJECTILE_ARROW: {
            proj.speed  = PROJECTILE_ARROW_SPEED;
            proj.damage = PROJECTILE_ARROW_DAMAGE;
            proj.tile   = PROJECTILE_ARROW_TILE;
            proj.shape = 1; // 16 x 8
            break;
        }
        case PROJECTILE_MAGIC: {
            proj.speed  = PROJECTILE_MAGIC_SPEED;
            proj.damage = PROJECTILE_MAGIC_DAMAGE;
            proj.tile   = PROJECTILE_MAGIC_TILE;
            proj.shape = 0;
            break;
        }
    }

    projectiles[projectile_count] = proj;
    projectile_count++;
    return true;
}
