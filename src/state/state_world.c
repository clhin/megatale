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

#define RIGHT_LIMIT 153
#define DOWN_LIMIT 116
#define LEFT_LIMIT 152
#define UP_LIMIT 115

static void camera_move();
static void handle_collision();

Sprite *frisk;

BoxCollision frisk_bb;

int cur_cam_x;
int cur_cam_y;

short frisk_x;
short frisk_y;

u8 xlimit;
u8 ylimit;

int8_t xvelocity;
int8_t yvelocity;

static u8 priority = 0;

u16 ind = TILE_USER_INDEX;

Map *map;
savedata_t *savefile;

void world_init(state_parameters_t args) {
    SPR_init();  // Needs to be called after clear?
    PAL_setPalette(PAL0, ruinspal.data, DMA);

    VDP_loadTileSet(&font_sheet, TILE_USER_INDEX, DMA);
    ind += font_sheet.numTile;
    map = loadlevel(0, ind);
    cur_cam_x = 0;
    cur_cam_y = 0;
    MAP_scrollTo(map, cur_cam_x, cur_cam_y);

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
        frisk = SPR_addSprite(&frisk_sprite, frisk_x, frisk_y,
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
void world_update() {
//    priority = 0;
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
    handle_collision();
    camera_move();
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

static void handle_collision() {
    //TODO: these if statements suck
    uint8_t flagxstop = 1;
    uint8_t flagystop = 1;
/*    if (frisk_x + xvelocity < 0 || 
        !startcollision[((frisk_y+16)/20)*34+((frisk_x + 2 + xvelocity)/20)] ||
        !startcollision[((frisk_y+16)/20)*34+((frisk_x + 21 + xvelocity)/20)] ||
        !startcollision[((frisk_y+28)/20)*34+((frisk_x + 2 + xvelocity)/20)] ||
        !startcollision[((frisk_y+28)/20)*34+((frisk_x + 21 + xvelocity)/20)]){
	flagxstop = 0;
	if(yvelocity != 0)
	    priority = 0;
    }
    if (frisk_y + yvelocity < 0 ||
        !startcollision[((frisk_y+16+yvelocity)/20)*34+((frisk_x+2)/20)] ||
        !startcollision[((frisk_y+16+yvelocity)/20)*34+((frisk_x+21)/20)] ||
        !startcollision[((frisk_y+28+yvelocity)/20)*34+((frisk_x+2)/20)] ||
        !startcollision[((frisk_y+28+yvelocity)/20)*34+((frisk_x+21)/20)]) {
        flagystop = 0;
	if (xvelocity != 0)
	    priority = 1;
    }
*/
    if (xvelocity == 1){
	if (!startcollision[((frisk_y + 16) / 20) * 34 + ((frisk_x + 21 + xvelocity) / 20)] ||
	    !startcollision[((frisk_y + 28) / 20) * 34 + ((frisk_x + 21 + xvelocity) / 20)]) {
	    flagxstop = 0;
            if(yvelocity != 0)
            	priority = 0;
	}	
    } else if (xvelocity == -1) {
	if (!startcollision[((frisk_y + 16) / 20) * 34 + ((frisk_x + 2 + xvelocity) / 20)] ||
	    !startcollision[((frisk_y + 28) / 20) * 34 + ((frisk_x + 2 + xvelocity) / 20)] ){
	    flagxstop = 0;
            if(yvelocity != 0)
                priority = 0;
	}
    }

    if(yvelocity == 1){
	if (!startcollision[((frisk_y + 16 + yvelocity) / 20) * 34 + ((frisk_x + 21) / 20)] ||
	    !startcollision[((frisk_y + 28 + yvelocity) / 20) * 34 + ((frisk_x + 21) / 20)]) {
	    flagystop = 0;
            if (xvelocity != 0)
                priority = 1;
	}
    } else if (yvelocity == -1) {
	if (!startcollision[((frisk_y + 16 + yvelocity) / 20) * 34 + ((frisk_x + 2) / 20)] ||
	    !startcollision[((frisk_y + 28 + yvelocity) / 20) * 34 + ((frisk_x + 2) / 20)]){
	    flagystop = 0;
            if (xvelocity != 0)
                priority = 1;
	}
    }

    frisk_x += (xvelocity * flagxstop);
    frisk_y += (yvelocity * flagystop);
}

// This function was heavily based of the following code: 
// https://youtu.be/yyYJ7f7pSjQ?si=hlwbLwR5FS7KddZ5
static void camera_move() {
    int player_xpos_scr = frisk_x - cur_cam_x;
    int player_ypos_scr = frisk_y - cur_cam_y;

    int new_cam_x;
    int new_cam_y;

    if (player_xpos_scr > RIGHT_LIMIT) {
	new_cam_x = frisk_x - RIGHT_LIMIT;
    } else if (player_xpos_scr < LEFT_LIMIT){
	new_cam_x = frisk_x - LEFT_LIMIT;
    } else {
	new_cam_x = cur_cam_x;
    }
    if (player_ypos_scr > DOWN_LIMIT) {
        new_cam_y = frisk_y - DOWN_LIMIT;
    } else if (player_ypos_scr < UP_LIMIT){
        new_cam_y = frisk_y - UP_LIMIT;
    } else {
        new_cam_y = cur_cam_y;
    }
    if (new_cam_x < 0)
	new_cam_x = 0;
    else if (new_cam_x > 680-320)
	new_cam_x = 680-320;
    if (new_cam_y  < 0)
	new_cam_y = 0;
    else if (new_cam_y > 240 - 224)
	new_cam_y = 240-224;
    if ((new_cam_x != cur_cam_x) || (new_cam_y != cur_cam_y)){
	cur_cam_x = new_cam_x;
	cur_cam_y = new_cam_y;
	MAP_scrollTo(map, new_cam_x,new_cam_y);
    }
    SPR_setPosition(frisk, frisk_x-new_cam_x, frisk_y-new_cam_y);
}
