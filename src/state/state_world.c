#include "state_world.h"

#include <genesis.h>
#include <resources.h>

#include "../collisions.h"
#include "../graphics/text.h"
#include "../graphics/textbox.h"
#include "../graphics/utils.h"
#include "state_battle.h"

Sprite *heart_test;
Sprite *enemy_heart;

Sprite *frisk;

box_t heart_bb;
box_t enemy_bb;

u16 frisk_x;
u16 frisk_y;
int8_t xvelocity;
int8_t yvelocity;

u16 index = 0;

u16 counter = 0;

char strings[2][MAX_LINE_LENGTH];

void world_init(state_parameters_t args) {
    strcpy(strings[0], "Qell,!");
    strcpy(strings[1], "World!");

    SPR_init();  // Needs to be called after clear?

    u8 res = VDP_loadTileSet(&font_sheet, TILE_USER_INDEX, DMA);

    textbox_init(TEXT_FLOWEY_MODE, FLOWEY_OFFSET,
                 "Make sure there is\nroom in your pockets\nfor that.", TRUE,
                 FALSE, FALSE);

    char buf2[32];
    intToStr(MEM_getFree(), buf2, 1);

    VDP_drawText(buf2, 1, 1);

    frisk_x = 20;
    frisk_y = 20;

    heart_bb.x = frisk_x;
    heart_bb.y = frisk_y;
    heart_bb.w = frisk_sprite.w;
    heart_bb.h = frisk_sprite.h;

    enemy_bb.x = 80;
    enemy_bb.y = 80;
    enemy_bb.w = 8;
    enemy_bb.h = 8;

    draw_lines(strings, 2, 2, 9, TILE_USER_INDEX, BG_A, PAL1);

    /*
        VDP_drawText(buf2, 1, 1);

        heart = SPR_addSprite(&heart_sprite, heart_x, heart_y,
                              TILE_ATTR(PAL1, TRUE, FALSE, FALSE));
    */
    enemy_heart = SPR_addSprite(&heart_sprite, 80, 80,
                                TILE_ATTR(PAL1, TRUE, FALSE, FALSE));

    // where are we in a world init? Well, we started from the main
    // menu, and thus we have two options as to where we are: 1. we have
    // a blank save (load from the beginning), or we have save data and
    // thus we load from our save state (not implemented yet)
    if (0 /* save state */) {
        // load save data
    } else {
        // we assume that menu has taken care of the fade to white
        PAL_setPalette(PAL0, ruinspal.data, DMA);
        //		PAL_setPalette(PAL1, frisk_sprite.palette->data, DMA);
        frisk = SPR_addSprite(&frisk_sprite, 80, 80,
                              TILE_ATTR(PAL1, TRUE, FALSE, FALSE));
        heart_test = SPR_addSprite(&heart_sprite, 80, 80,
                                   TILE_ATTR(PAL1, TRUE, FALSE, FALSE));
    }
}
void world_input(u16 changed, u16 state) {
    if (state & BUTTON_RIGHT) {
        xvelocity = 1;
    } else if (state & BUTTON_LEFT) {
        xvelocity = -1;
    } else {
        xvelocity = 0;
    }
    if (state & BUTTON_UP) {
        yvelocity = -1;
    } else if (state & BUTTON_DOWN) {
        yvelocity = 1;
    } else {
        yvelocity = 0;
    }

    if (state & BUTTON_A) {
        state_pop();
    }
}
void world_update() {
    static uint8_t priority = 0;
    heart_bb.x = frisk_x;
    heart_bb.y = frisk_y;
    if (xvelocity != 0 && yvelocity == 0) {
        priority = 1;
    } else if (xvelocity == 0 && yvelocity != 0) {
        priority = 0;
    }
    if (priority) {
        if (xvelocity == -1) {
            SPR_setHFlip(frisk, TRUE);
            SPR_setAnim(frisk, SIDE_WALK);
        } else if (xvelocity == 1) {
            SPR_setHFlip(frisk, FALSE);
            SPR_setAnim(frisk, SIDE_WALK);
        } else {
            SPR_setAnim(frisk, SIDE);
        }
    } else {
        SPR_setHFlip(frisk, FALSE);
        if (yvelocity == -1) {
            SPR_setAnim(frisk, BACK_WALK);
        } else if (yvelocity == 1) {
            SPR_setAnim(frisk, FRONT_WALK);
        } else {
            if (frisk->animInd == FRONT_WALK)
                SPR_setAnim(frisk, FRONT);
            else if (frisk->animInd == BACK_WALK)
                SPR_setAnim(frisk, BACK);
        }
    }
    SPR_setPosition(frisk, frisk_x + xvelocity, frisk_y + yvelocity);
    frisk_x += xvelocity;
    frisk_y += yvelocity;
    //    if (xvelocity) {
    //	SPR_setAnim(frisk, 2);
    //    }
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
    }
    counter++;

    if (counter >= 10) {
        if (textbox_tick())
            textbox_flush("I'm repeating\nmyself", TRUE, FALSE, FALSE);
        counter = 0;
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
