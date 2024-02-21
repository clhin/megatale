#include "state_world.h"

#include <genesis.h>
#include <resources.h>

#include "../collisions.h"
#include "../graphics/text.h"
#include "../graphics/textbox.h"
#include "state_battle.h"

#define TRUE 1
#define FALSE 0

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

void world_init(state_parameters_t args) {
    SPR_init();  // Needs to be called after clear?

    u8 res = VDP_loadTileSet(&font_sheet, TILE_USER_INDEX, DMA);

    // Palette for textbox
    //    PAL_setColor(33, RGB24_TO_VDPCOLOR(0x000000));
    //    PAL_setColor(34, RGB24_TO_VDPCOLOR(0xffffff));
    //    PAL_setColor(35, RGB24_TO_VDPCOLOR(0x111111));

    //   Initialize textbox

    text_info.lines_used = 3;
    text_info.asterisks[0] = 1;
    text_info.asterisks[1] = 1;
    text_info.asterisks[2] = 1;
    sprintf(text_info.lines[0], "ppppppp");
    sprintf(text_info.lines[1], "WWWWW");
    sprintf(text_info.lines[2], "XXXX");

    textbox_show(TEXT_DIALOGUE_MODE);

    char buf2[32];

    intToStr(MEM_getFree(), buf2, 1);

    frisk_x = 20;
    frisk_y = 20;
    //velocity = 4;

    heart_bb.x = frisk_x;
    heart_bb.y = frisk_y;
    heart_bb.w = 8;
    heart_bb.h = 8;

    enemy_bb.x = 80;
    enemy_bb.y = 80;
    enemy_bb.w = 8;
    enemy_bb.h = 8;
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
	SPR_setFrame(frisk, 2);
    } else if (state & BUTTON_LEFT) {
        xvelocity = -1;
    } else {
    	xvelocity = 0;
	//SPR_setAnimationLoop(frisk, FALSE);
	SPR_setFrame(frisk, 0);
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
    heart_bb.x = frisk_x;
    heart_bb.y = frisk_y;
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

    if (counter >= 5) {
        if (textbox_tick()) textbox_close();
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
