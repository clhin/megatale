#include "state_world.h"

#include <genesis.h>
#include <resources.h>

#include "../collisions.h"
#include "../graphics/level.h"
#include "../graphics/text.h"
//#include "../graphics/textbox.h"
#include "../graphics/strutils.h"
#include "../globals.h"
#include "savedata.h"
#include "../save/save.h"
#include "state_battle.h"
#include "state_gamemenu.h"

Sprite *frisk;

BoxCollision frisk_bb;

int cur_cam_x;
int cur_cam_y;

short frisk_x;
short frisk_y;

short levelxlimit;
short levelylimit;

int8_t xvelocity;
int8_t yvelocity;
int8_t interact;
int8_t cancel;

static u8 priority = 0;

savedata_t *savefile;

static void animate_frisk();  
static void camera_move();  
static void handle_collision();  
static void handle_collision_helper(u8,u8,u8,u8*);  
static u8 map_collision_locator(u16 idx); 

void world_init(state_parameters_t args) {
    SPR_init();  // Needs to be called after clear?

    frisk_bb.x = frisk_x;
    frisk_bb.y = frisk_y;
    frisk_bb.w = frisk_sprite.w;
    frisk_bb.h = frisk_sprite.h;
    // where are we in a world init? Well, we started from the main
    // menu, and thus we have two options as to where we are: 1. we have
    // a blank save (load from the beginning), or we have save data and
    // thus we check the validity of our save and load from our save state 
    // (not implemented yet)
    if (SRAM_readByte(0) == SAVE_VALID) {
        // load save data
    } else {
	map = loadlevel(0,0);
    	cur_cam_x = 0;
    	cur_cam_y = 0;
    	MAP_scrollTo(map, cur_cam_x, cur_cam_y);

	savefile = args.parameter_data;
        // we assume that menu has taken care of the fade to white
        //		PAL_setPalette(PAL1, frisk_sprite.palette->data, DMA);
        frisk = SPR_addSprite(&frisk_sprite, frisk_x, frisk_y,
			      TILE_ATTR(PAL1, FALSE, FALSE, FALSE));
	savefile->room = 0;
	savefile->maxhp = 20;
	savefile->hp = 20;
	savefile->at = 0;
	savefile->def = 0;
	savefile->gold = 0;
	savefile->love = 1;
	savefile->exp = 0;
	savefile->kills = 0;
	savefile->weapon = 2;
	savefile->armor = 3;
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
    if (state & BUTTON_A)
	interact = 1;
    else
	interact = 0;

    if (state & BUTTON_B)
	cancel = 1;
    else
	cancel = 0;
    // use as a debug button for now, later it will be the same as the start button
    if (state & BUTTON_C)
	savefile->cell = 1;
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
	args.parameter_data = savefile;
        state_push(state_info, args);
    }
}
void world_update() {
    animate_frisk();
    handle_collision();
    camera_move();
#ifdef DEBUG
    char ypos[4];
    sprintf(ypos, "%d", frisk_y);
    VDP_drawText(ypos, 1,1);
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

static void animate_frisk() {
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
}

static void handle_collision() {
    u8 flagxstop = 1;
    u8 flagystop = 1;

    //TODO: lots of divides here, can we factor this out? maybe a double array would infact be better
    if (xvelocity == 1){
	u8 xtopright = map_collision_locator(((frisk_y + 16) / 20) * (levelxlimit/20) + ((frisk_x + 21 + xvelocity) / 20));
	u8 xbottomright = map_collision_locator(((frisk_y + 28) / 20) * (levelxlimit/20) + ((frisk_x + 21 + xvelocity) / 20));
	handle_collision_helper(xtopright, xbottomright, TRUE, &flagxstop);
    } else if (xvelocity == -1) {
	u8 xtopleft = map_collision_locator(((frisk_y + 16) / 20) * (levelxlimit/20) + ((frisk_x + 2 + xvelocity) / 20));
	u8 xbottomleft = map_collision_locator(((frisk_y + 28) / 20) * (levelxlimit/20) + ((frisk_x + 2 + xvelocity) / 20));
	handle_collision_helper(xtopleft, xbottomleft, TRUE, &flagxstop);
    }

    if(yvelocity == 1){
	u8 ybottomleft = map_collision_locator(((frisk_y + 28 + yvelocity) / 20) * (levelxlimit/20) + ((frisk_x + 2) / 20));
	u8 ybottomright = map_collision_locator(((frisk_y + 28 + yvelocity) / 20) * (levelxlimit/20) + ((frisk_x + 21) / 20));
	handle_collision_helper(ybottomleft, ybottomright, FALSE, &flagystop);
    } else if (yvelocity == -1) {
	u8 ytopleft = map_collision_locator(((frisk_y + 16 + yvelocity) / 20) * (levelxlimit/20) + ((frisk_x + 2) / 20));
	u8 ytopright = map_collision_locator(((frisk_y + 16 + yvelocity) / 20) * (levelxlimit/20) + ((frisk_x + 21) / 20));
	handle_collision_helper(ytopleft, ytopright, FALSE, &flagystop);
    }

    frisk_x += (xvelocity * flagxstop);
    frisk_y += (yvelocity * flagystop);
}

static u8 map_collision_locator(u16 idx) {
    switch(savefile->room) {
	case 0:
	    return startcollision[idx];
	case 1:
	    return maincollision[idx];
	case 2:
	    return ruins1_collision[idx];
	case 3:
	    return ruins2_collision[idx];
	case 4:
	    return ruins3_collision[idx];
	default:
	    //error, just assume it can't be walked in I guess
	    return 0;
    }
    return 0;
}

void handle_collision_helper(u8 corner1, u8 corner2, u8 x, u8 *flag) {
    if (!corner1 || !corner2){
	*flag = 0;
	if (x){
            if (yvelocity != 0)
                priority = 0;
        } else /* if y, the only other option */ {
            if (xvelocity != 0)
                priority = 1;
	}
    } else if (corner1 == 2 || corner2 == 2) {
	switch (savefile->room) {
	    case 0:
		PAL_fadeOutAll(15,FALSE);
		VDP_clearTextAreaBG(BG_B, 0, 0, 80, 35);
		MAP_release(map);
		map = loadlevel(savefile->room, savefile->room + 1);
		++savefile->room;
		break;
	    case 1:
		PAL_fadeOutAll(15,FALSE);
                VDP_clearTextAreaBG(BG_B, 0, 0, 40, 52);
                MAP_release(map);
		if (frisk_y >= 160) {
			MAP_release(map);
                	map = loadlevel(savefile->room, savefile->room - 1);
			--savefile->room;
		} else {
			map = loadlevel(savefile->room, savefile->room + 1);
			++savefile->room;
		}
		break;
	    case 2:
		PAL_fadeOutAll(15,FALSE);
                VDP_clearTextAreaBG(BG_B, 0, 0, 40, 60);
                MAP_release(map);
		if (frisk_y >= 420) {
                	map = loadlevel(savefile->room, savefile->room - 1);
			--savefile->room;
		} else {
			map = loadlevel(savefile->room, savefile->room + 1);
			++savefile->room;
		}
		break;
	    case 3:
		PAL_fadeOutAll(15,FALSE);
                VDP_clearTextAreaBG(BG_B, 0, 0, 40, 30);
                MAP_release(map);
		if (frisk_y >= 190) {
                	map = loadlevel(savefile->room, savefile->room - 1);
			--savefile->room;
		 } else {
			map = loadlevel(savefile->room, savefile->room + 1);
			++savefile->room;
		}
		break;
	    default:
		//do nothing
		break;
	}
    } else if (corner1 == 3 || corner2 == 3) {
/*	if (savefile->room == 1 && !SRAM_readByte(FLOWEY_1ST_ENCOUNTER)) {
	    char buf[243];
	    u8 asterisks = 0;
	    aplib_unpack((u8*)buf,(u8*)floweyintro);
	    parse_dialog(buf,&textpos,&asterisks,243);
	    if (textpos == 0) {
	    	if (asterisks == 1)
		    textbox_init(TEXT_FLOWEY_MODE, 1, buf, TRUE,FALSE,FALSE);
		else if (asterisks == 2)
		    textbox_init(TEXT_FLOWEY_MODE, 1, buf, TRUE,TRUE,FALSE);
		else
		    textbox_init(TEXT_FLOWEY_MODE, 1, buf, TRUE,TRUE,TRUE);
	    } else {
		if (asterisks == 1)
		    textbox_flush(buf, TRUE,FALSE,FALSE);
		else if (asterisks == 2)
		    textbox_flush(buf, TRUE,TRUE,FALSE);
		else
		    textbox_flush(buf, TRUE,TRUE,TRUE);
	    }
	} */
    }
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
    else if (new_cam_x > levelxlimit - 320)
	new_cam_x = levelxlimit - 320;
    if (new_cam_y  < 0)
	new_cam_y = 0;
    else if (new_cam_y > levelylimit - 224)
	new_cam_y = levelylimit - 224;
    if ((new_cam_x != cur_cam_x) || (new_cam_y != cur_cam_y)){
	cur_cam_x = new_cam_x;
	cur_cam_y = new_cam_y;
	MAP_scrollTo(map, new_cam_x,new_cam_y);
    }
    SPR_setPosition(frisk, frisk_x-new_cam_x, frisk_y-new_cam_y);
}
