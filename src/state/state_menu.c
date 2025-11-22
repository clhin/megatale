#include "state_menu.h"

#include <genesis.h>
#include <resources.h>

#include "save/save.h"
#include "savedata.h"
#include "state_world.h"

#include "graphics/level.h"

#include "graphics/text.h"
//#include "graphics/textbox.h"
#include "../globals.h"

void menu_init(state_parameters_t args) {
	char *buf = (char*)malloc(sizeof(char)*924);
	txtptr = buf;
	vram_index = TILE_USER_INDEX + font_sheet.numTile;
	VDP_loadTileSet(&titlescreen_tiles, vram_index, DMA);
        map = MAP_create(&titlescreen, BG_B, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, vram_index));
	MAP_scrollTo(map,0,0);
	map = foregroundmap;
	aplib_unpack((u8*)mainmenu_text,(u8*)buf);
	startTimer(0);
}

void menu_input(u16 changed, u16 state) {
	if (state & BUTTON_A && map == foregroundmap) {
		if (SRAM_readByte(0) == 0x42) {
			MAP_release(map);
                        map = NULL;
			loadlevel(1,1);
			
		} else {
			MAP_release(map);
			map = NULL;
			state_parameters_t args;
        state_pusher(args,config_init,config_input, config_update, config_clean,config_redraw,config_shutdown);
		}
	}
}

void menu_update() {
	char buf[2];
	intToStr(getTimer(0,FALSE),buf,FALSE);
	VDP_drawText(buf,0,0);
	if (getTimer(0,FALSE) > 240000 && map == foregroundmap) {
		VDP_drawText(txtptr,0,23);
	}
	if ((getTimer(0,FALSE) > 1000000) && map == foregroundmap) {
		state_pop();
	}
}

void menu_clean() {
	VDP_clearPlane(BG_A, TRUE);
        VDP_clearPlane(BG_B, TRUE);	
}

void menu_redraw(state_return_t ret) {
}

state_return_t menu_shutdown() {
    menu_clean();
    state_return_t ret;
    return ret;
}
