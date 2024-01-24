#include "state_world.h"

#include <genesis.h>
#include <resources.h>

#include "../collisions.h"

Sprite *heart;

Sprite *enemy_heart;

box_t heart_bb;
box_t enemy_bb;

u16 heart_x;
u16 heart_y;
u8 velocity;

void world_init(state_parameters_t args) {
    SPR_init();  // Needs to be called after clear?

    heart_x = 20;
    heart_y = 20;
    velocity = 4;

    heart_bb.x = heart_x;
    heart_bb.y = heart_y;
    heart_bb.w = 8;
    heart_bb.h = 8;

    enemy_bb.x = 80;
    enemy_bb.y = 80;
    enemy_bb.w = 8;
    enemy_bb.h = 8;

    VDP_drawText("You are now in the world.", 1, 1);
    VDP_drawText("Try moving the red heart to the green heart", 1, 2);
    VDP_drawText("to start a battle.", 5, 3);

    heart = SPR_addSprite(&heart_sprite, heart_x, heart_y,
                          TILE_ATTR(PAL2, TRUE, FALSE, FALSE));

    enemy_heart = SPR_addSprite(&heart_sprite, 80, 80,
                                TILE_ATTR(PAL1, TRUE, FALSE, FALSE));
}
void world_input(u16 changed, u16 state) {
    if (state & BUTTON_RIGHT) {
        heart_x += velocity;
    }
    if (state & BUTTON_LEFT) {
        heart_x -= velocity;
    }
    if (state & BUTTON_UP) {
        // I know that if two directions are on it goes *sqrt(2) as fast, but we
        // are dealing with integers and not floating point. Does Sega Genesis
        // support floating point calculation? (Look into this later, simple
        // fix, you just multiple both by 0.707)
        heart_y -= velocity;
    }
    if (state & BUTTON_DOWN) {
        heart_y += velocity;
    }
}
void world_update() {
    heart_bb.x = heart_x;
    heart_bb.y = heart_y;
    SPR_setPosition(heart, heart_x, heart_y);

    if (collides(heart_bb, enemy_bb)) {
        /*
            Todo: Push battle transistion
        */
        VDP_drawText("Battle State transistion", 1, 7);
    }
}
void world_clean() {}
void world_redraw() {}
state_return_t world_shutdown() {}