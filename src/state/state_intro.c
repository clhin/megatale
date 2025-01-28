#include "state_intro.h"

#include <genesis.h>
#include <resources.h>

#include "state_menu.h"
#include "../graphics/textbox.h"
#include "../graphics/text.h"
#include "../audio/audio.h"
#include "../globals.h"

void intro_init(state_parameters_t args) {
	char * buf = (char*)malloc(327 * sizeof(char));
	vram_index = TILE_USER_INDEX;
	VDP_loadTileSet(&font_sheet, vram_index, DMA);
	vram_index += font_sheet.numTile;
	VDP_loadTileSet(&intro_cover_tiles, vram_index, DMA);
	foregroundmap = MAP_create(&intro_cover, BG_A, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vram_index));
	vram_index += intro_cover_tiles.numTile;
	VDP_loadTileSet(&intro_0_tiles, vram_index, DMA);
	map = MAP_create(&intro_0, BG_B, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, vram_index)); 
	PAL_setPalette(PAL2, intropal.data, DMA);
	aplib_unpack((u8*)introtext,(u8*)buf);
	txtptr = buf;
	textbox_init(TEXT_INTRO_MODE, 18, txtptr, FALSE, FALSE, FALSE);
	playmusic(onceuponatime, 0);
	MAP_scrollTo(foregroundmap,0,0);
        MAP_scrollTo(map, 196,236);
}

void intro_update() {
	char buf2[32];
	int time = XGM2_getElapsed();

        intToStr(time, buf2, 1);

        VDP_drawText(buf2, 1, 1);
	VDP_showCPULoad(1,2);


    //VDP_drawText(buf3, 1, 3);
	if (time % 5 == 0 && textbox_tick()) {
		if (time == 410) {
			intro_helper(196,236,60,intro_1,intro_1_tiles);
		} else if (time == 725) {
			intro_helper(196,236,107,intro_2,intro_2_tiles);
		} else if (time == 1090) {
			intro_helper(196,236,157,intro_3,intro_3_tiles);
		} else if (time == 1480) {
			PAL_fadeOutPalette(PAL2,15,FALSE);
			MAP_release(map);
			map = NULL;
			textbox_flush(txtptr+215,FALSE,FALSE,FALSE);
		} else if (time == 1750) {
			textbox_flush(txtptr+235,FALSE,FALSE,FALSE);
			//VDP_fillTileData(0, TILE_USER_INDEX+font_sheet.numTile, intro_3_tiles.numTile, TRUE);
			VDP_loadTileSet(&intro_4_tiles, vram_index, DMA);
                        map = MAP_create(&intro_4, BG_B, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, vram_index));
                        MAP_scrollTo(map, 196,236);
                        PAL_fadeInPalette(PAL2, intropal.data, 15, TRUE);
		} else if (time == 2040) {
			intro_helper(196,236,267,intro_5,intro_5_tiles);
		} else if (time == 2420) {
			textbox_flush("",FALSE,FALSE,FALSE);
			intro_helper(196,236,0,intro_6,intro_6_tiles);
		} else if (time == 2760) {
			intro_helper(196,236,0,intro_7,intro_7_tiles);
		} else if (time == 3095) {
			intro_helper(196,236,0,intro_8,intro_8_tiles);
		} else if (time == 3375) {
			intro_helper(196,732,0,intro_9,intro_9_tiles);
		} else if (time > 3740 && time < 4600) {
			if (map->posY >= 494){
				MAP_scrollToEx(map,196,(map->posY - 2),TRUE);
			}
		} else if (time > 4600) { 
			XGM2_fadeOutAndStop(15);
			PAL_fadeOutPalette(PAL2,15,FALSE);
			state_parameters_t args;
                	state_info_t state_info;
                	state_info.clean = menu_clean;
                	state_info.init = menu_init;
                	state_info.redraw = menu_redraw;
                	state_info.input = menu_input;
                	state_info.update = menu_update;
                	state_info.shutdown = menu_shutdown;
                	state_push(state_info, args);
		}
	}
}

void intro_helper(u8 x, u16 y, u16 idx, const MapDefinition mapDef, const TileSet tileset ){
	PAL_fadeOutPalette(PAL2,15,FALSE);
        MAP_release(map);
	map = NULL;
	if (idx != 0)
        	textbox_flush(txtptr+idx,FALSE,FALSE,FALSE);
                        //VDP_fillTileData(0, TILE_USER_INDEX+font_sheet.numTile, intro_0_tiles.numTile, TRUE);
        VDP_loadTileSet(&tileset, vram_index, DMA);
        map = MAP_create(&mapDef, BG_B, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, vram_index));
        MAP_scrollTo(map, x,y);
        PAL_fadeInPalette(PAL2, intropal.data, 15, TRUE);
}

void intro_input(u16 changed, u16 state) {
    if (changed & BUTTON_A && (state & BUTTON_A)) {
	state_parameters_t args;
        state_info_t state_info;
        state_info.clean = menu_clean;
        state_info.init = menu_init;
        state_info.redraw = menu_redraw;
        state_info.input = menu_input;
        state_info.update = menu_update;
        state_info.shutdown = menu_shutdown;
        state_push(state_info, args);
    }
//    if (state & BUTTON_B)
			
}

void intro_clean() { 
	if (XGM2_isPlaying())
		XGM2_stop();
	if (foregroundmap)
		MAP_release(foregroundmap);
	if (map)
		MAP_release(map);

	free((void*)txtptr);
	VDP_clearPlane(BG_A, TRUE);
	VDP_clearPlane(BG_B, TRUE);
        SPR_clear();
}

void intro_redraw(state_return_t ret) {}

state_return_t intro_shutdown() {
    intro_clean();
    state_return_t ret;
    return ret;
}
