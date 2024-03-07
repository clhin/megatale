#include "state_world.h"

#include <genesis.h>
#include <resources.h>

#include "../audio/audioEffects.h"
#include "../collisions.h"
#include "../graphics/level.h"
#include "../graphics/text.h"
#include "../graphics/textbox.h"
#include "../graphics/utils.h"
#include "savedata.h"
#include "state_battle.h"
#include "state_gamemenu.h"

Sprite *heart_test;
Sprite *enemy_heart;

Sprite *frisk;

BoxCollision heart_bb;
BoxCollision enemy_bb;

u16 frisk_x;
u16 frisk_y;

u8 xlimit;
u8 ylimit;

int8_t xvelocity;
int8_t yvelocity;

u16 ind = TILE_USER_INDEX;

Map *map;
savedata_t *save;
u16 counter = 0;

void world_init(state_parameters_t args) {
    SPR_init();  // Needs to be called after clear?
#ifdef DEBUG
    char buffer1[32];
#endif
    PAL_setPalette(PAL0, ruinspal.data, DMA);

    VDP_loadTileSet(&font_sheet, TILE_USER_INDEX, DMA);
    ind += font_sheet.numTile;
    map = loadlevel(0, ind);
    MAP_scrollTo(map, 0, 0);
#ifdef DEBUG
    sprintf(buffer1, "font tiles: %d bg tiles: %d", font_sheet.numTile,
            room_one.numTile);
    VDP_drawText(buffer1, 1, 1);
    textbox_init(TEXT_FLOWEY_MODE, FLOWEY_OFFSET,
                 "Make sure there is\nroom in your pockets\nfor that.", TRUE,
                 FALSE, FALSE);
#endif
    char buf2[32];
    intToStr(MEM_getFree(), buf2, 1);

    VDP_drawText(buf2, 1, 1);

    frisk_x = 20;
    frisk_y = 20;
    // startHeartache();
    heart_bb.x = frisk_x;
    heart_bb.y = frisk_y;
    heart_bb.w = frisk_sprite.w;
    heart_bb.h = frisk_sprite.h;

    enemy_bb.x = 80;
    enemy_bb.y = 80;
    enemy_bb.w = 8;
    enemy_bb.h = 8;

    /*
        VDP_drawText(buf2, 1, 1);

        heart = SPR_addSprite(&heart_sprite, heart_x, heart_y,
                              TILE_ATTR(PAL1, TRUE, FALSE, FALSE));
    */
    enemy_heart = SPR_addSprite(&heart_sprite, 22, 88,
                                TILE_ATTR(PAL1, TRUE, FALSE, FALSE));

    // where are we in a world init? Well, we started from the main
    // menu, and thus we have two options as to where we are: 1. we have
    // a blank save (load from the beginning), or we have save data and
    // thus we load from our save state (not implemented yet)
    if (args.parameter_data != NULL) {
        // load save data
    } else {
        // we assume that menu has taken care of the fade to white
        PAL_setPalette(PAL0, ruinspal.data, DMA);
        //		PAL_setPalette(PAL1, frisk_sprite.palette->data, DMA);
        frisk = SPR_addSprite(&frisk_sprite, 80, 80,
                              TILE_ATTR(PAL1, FALSE, FALSE, FALSE));
        SPR_setPriority(frisk, FALSE);
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

    if (state & BUTTON_START) {
        // Odd animations are taking a step, make sure we aren't animating
        // during a pause.
        SPR_setAnim(frisk, frisk->animInd - (frisk->animInd % 2));

        yvelocity = 0;
        xvelocity = 0;
        state_info_t state_info;
        state_info.clean = gamemenu_clean;
        state_info.init = gamemenu_init;
        state_info.redraw = gamemenu_redraw;
        state_info.input = gamemenu_input;
        state_info.update = gamemenu_update;
        state_info.shutdown = gamemenu_shutdown;

        state_parameters_t args;
        state_push(state_info, args);
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
#ifdef DEBUG
    counter++;

    if (counter >= 10) {
        if (textbox_tick())
            textbox_flush("I'm repeating\nmyself", TRUE, FALSE, FALSE);
        counter = 0;
    }
#endif
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
