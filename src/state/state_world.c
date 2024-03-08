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

extern const u8 startcollision[408];

Sprite *frisk;

BoxCollision frisk_bb;

short frisk_x;
short frisk_y;

u8 xlimit;
u8 ylimit;

int8_t xvelocity;
int8_t yvelocity;

u16 ind = TILE_USER_INDEX;

Map *map;
savedata_t *savefile;

void world_init(state_parameters_t args) {
    SPR_init();  // Needs to be called after clear?
    PAL_setPalette(PAL0, ruinspal.data, DMA);

    VDP_loadTileSet(&font_sheet, TILE_USER_INDEX, DMA);
    ind += font_sheet.numTile;
    map = loadlevel(0, ind);
    MAP_scrollTo(map, 0, 0);

    frisk_x = 140;
    frisk_y = 106;
    frisk_bb.x = frisk_x;
    frisk_bb.y = frisk_y;
    frisk_bb.w = frisk_sprite.w;
    frisk_bb.h = frisk_sprite.h;


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
        frisk = SPR_addSprite(&frisk_sprite, 140, 106,
                              TILE_ATTR(PAL1, FALSE, FALSE, FALSE));
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
char dispx[4],dispy[4],dispc[4], dispe[4];
void world_update() {
    sprintf(dispx, "%d", frisk_x);
    sprintf(dispy, "%d", frisk_y);
    sprintf(dispc, "%d", startcollision[(frisk_y/20)*34+(frisk_x+2/20)]);
    sprintf(dispe, "%d", (frisk_y/20)*34+(frisk_x+2/20));
    VDP_drawText(dispx,1, 1);
    VDP_drawText(dispy,10,1);
    VDP_drawText(dispc,20,1);
    VDP_drawText(dispe,30,1);
    static uint8_t priority = 0;
    frisk_bb.x = frisk_x;
    frisk_bb.y = frisk_y;
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
    
    //TODO: these if statements suck, and when moving against a wall, if the player is no longer
    // moving against the wall, the up button (for instance) will not push the player up into the
    // newly valid space
    if (frisk_x + xvelocity < 0 || !startcollision[((frisk_y+16)/20)*34+((frisk_x + 2 + xvelocity)/20)] || !startcollision[((frisk_y+16)/20)*34+((frisk_x + 21 + xvelocity)/20)] || !startcollision[((frisk_y+28)/20)*34+((frisk_x + 2 + xvelocity)/20)] || !startcollision[((frisk_y+28)/20)*34+((frisk_x + 21 + xvelocity)/20)]){
    	xvelocity = 0;
    }
    if (frisk_y + yvelocity < 0 || !startcollision[((frisk_y+16+yvelocity)/20)*34+((frisk_x+2)/20)] || !startcollision[((frisk_y+16+yvelocity)/20)*34+((frisk_x+21)/20)] || !startcollision[((frisk_y+28+yvelocity)/20)*34+((frisk_x+2)/20)] || !startcollision[((frisk_y+28+yvelocity)/20)*34+((frisk_x+21)/20)]) {
        yvelocity = 0;
    }
    frisk_x += xvelocity;
    frisk_y += yvelocity;
    SPR_setPosition(frisk, frisk_x, frisk_y);
    
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
