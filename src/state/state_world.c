#include "state_world.h"

#include <genesis.h>
#include <resources.h>

#include "../collisions.h"
#include "state_battle.h"

Sprite *heart;

Sprite *enemy_heart;

box_t heart_bb;
box_t enemy_bb;

u16 heart_x;
u16 heart_y;
u8 velocity;

void world_init(state_parameters_t args) {
    SPR_init();  // Needs to be called after clear?

    u8 res = VDP_loadTileSet(&font_sheet, TILE_USER_INDEX, DMA);

    char buf[4];
    intToStr(res, buf, 1);

    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL0, 0, 0, 0, TILE_USER_INDEX + 0),
                     4, 3);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL0, 0, 0, 0, TILE_USER_INDEX + 26),
                     4, 4);

    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL0, 0, 0, 0, TILE_USER_INDEX + 1),
                     5, 3);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL0, 0, 0, 0, TILE_USER_INDEX + 27),
                     5, 4);

    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL0, 0, 0, 0, TILE_USER_INDEX + 2),
                     6, 3);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL0, 0, 0, 0, TILE_USER_INDEX + 28),
                     6, 4);

    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL0, 0, 0, 0, TILE_USER_INDEX + 3),
                     7, 3);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL0, 0, 0, 0, TILE_USER_INDEX + 29),
                     7, 4);
    // VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL0, 0, 0, 0,
    // TILE_USER_INDEX + 0),
    //     4, 3);
    // VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL0, 0, 0, 0,
    // TILE_USER_INDEX + 26),
    //     4, 4);
    char buf2[32];

    intToStr(MEM_getFree(), buf2, 1);

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

    VDP_drawText(buf2, 1, 1);
    VDP_drawText(buf, 1, 2);

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

    if (state & BUTTON_A) {
        state_pop();
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

        state_info_t state_info;
        state_info.clean = battle_clean;
        state_info.init = battle_init;
        state_info.redraw = battle_redraw;
        state_info.input = battle_input;
        state_info.update = battle_update;
        state_info.shutdown = battle_shutdown;

        state_parameters_t args;
        state_push(state_info, args);

        // VDP_drawText("Battle State transistion", 1, 7);
    }
}
void world_clean() {
    VDP_clearSprites();

    VDP_clearTextArea(0, 0, 40, 28);
}
void world_redraw(state_return_t ret) {}
state_return_t world_shutdown() {
    world_clean();
    state_return_t ret;
    return ret;
}
