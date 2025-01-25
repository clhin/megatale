#include "state_intro.h"

#include <genesis.h>
#include <resources.h>

#include "state_menu.h"
#include "../graphics/textbox.h"
#include "../graphics/text.h"
#include "../audio/audio.h"

const char * txtptr;

void intro_init(state_parameters_t args) {
	char * buf = (char*)malloc(327 * sizeof(char));
	VDP_loadTileSet(&font_sheet, TILE_USER_INDEX, DMA);
	VDP_loadTileSet(&intro_0_tiles, TILE_USER_INDEX+font_sheet.numTile, DMA);
	PAL_setPalette(PAL2, intropal.data, DMA);
	aplib_unpack((u8*)introtext,(u8*)buf);
	txtptr = buf;
	textbox_init(TEXT_INTRO_MODE, 18, txtptr, FALSE, FALSE, FALSE);
	playmusic(onceuponatime, 0);
	Map *map = MAP_create(&intro_0, BG_B, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, TILE_USER_INDEX + font_sheet.numTile));
        MAP_scrollTo(map, 0,0);
}

void intro_update() {
	char buf2[32];
	int time = XGM2_getElapsed();

        intToStr((TILE_USER_INDEX + font_sheet.numTile), buf2, 1);

        VDP_drawText(buf2, 1, 1);

	if (time % 5 == 0 && textbox_tick()) {
		if (time == 410) {
			PAL_fadeOutPalette(PAL2,15,FALSE);
			textbox_flush(txtptr+60,FALSE,FALSE,FALSE);
			VDP_fillTileData(0, TILE_USER_INDEX+font_sheet.numTile, intro_0_tiles.numTile, TRUE);
			VDP_loadTileSet(&intro_1_tiles, TILE_USER_INDEX+font_sheet.numTile, DMA);
			Map *map = MAP_create(&intro_1, BG_B, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, TILE_USER_INDEX + font_sheet.numTile));
			MAP_scrollTo(map, 0,0);
			PAL_fadeInPalette(PAL2, intropal.data, 15, TRUE);
		} else if (time == 725) {
			PAL_fadeOutPalette(PAL2,15,FALSE);
			textbox_flush(txtptr+107,FALSE,FALSE,FALSE);
			VDP_fillTileData(0, TILE_USER_INDEX+font_sheet.numTile, intro_1_tiles.numTile, TRUE);
			VDP_loadTileSet(&intro_2_tiles, TILE_USER_INDEX+font_sheet.numTile, DMA);
                        Map *map = MAP_create(&intro_2, BG_B, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, TILE_USER_INDEX + font_sheet.numTile));
                        MAP_scrollTo(map, 0,0);
                        PAL_fadeInPalette(PAL2, intropal.data, 15, TRUE);
		} else if (time == 1090) {
			PAL_fadeOutPalette(PAL2,15,FALSE);
			textbox_flush(txtptr+157,FALSE,FALSE,FALSE);
			VDP_fillTileData(0, TILE_USER_INDEX+font_sheet.numTile, intro_2_tiles.numTile, TRUE);
			VDP_loadTileSet(&intro_3_tiles, TILE_USER_INDEX+font_sheet.numTile, DMA);
                        Map *map = MAP_create(&intro_3, BG_B, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, TILE_USER_INDEX + font_sheet.numTile));
                        MAP_scrollTo(map, 0,0);
                        PAL_fadeInPalette(PAL2, intropal.data, 15, TRUE);
		} else if (time == 1480) {
			PAL_fadeOutPalette(PAL2,15,FALSE);
			textbox_flush(txtptr+215,FALSE,FALSE,FALSE);
		} else if (time == 1750) {
			textbox_flush(txtptr+235,FALSE,FALSE,FALSE);
			VDP_fillTileData(0, TILE_USER_INDEX+font_sheet.numTile, intro_3_tiles.numTile, TRUE);
			VDP_loadTileSet(&intro_5_tiles, TILE_USER_INDEX+font_sheet.numTile, DMA);
                        Map *map = MAP_create(&intro_5, BG_B, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, TILE_USER_INDEX + font_sheet.numTile));
                        MAP_scrollTo(map, 0,0);
                        PAL_fadeInPalette(PAL2, intropal.data, 15, TRUE);
		} else if (time == 2040) {
	//		PAL_fadeOutPalette(PAL2,15,FALSE);
			textbox_flush(txtptr+267,FALSE,FALSE,FALSE);
			VDP_fillTileData(0, TILE_USER_INDEX+font_sheet.numTile, intro_5_tiles.numTile, TRUE);
			VDP_loadTileSet(&intro_6_tiles, TILE_USER_INDEX+font_sheet.numTile, DMA);
                        Map *map = MAP_create(&intro_6, BG_B, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, TILE_USER_INDEX + font_sheet.numTile));
                        MAP_scrollTo(map, 0,0);
                        PAL_fadeInPalette(PAL2, intropal.data, 15, TRUE);
		}
	}
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
}

void intro_clean() { 
	free((void*)txtptr);
	VDP_clearPlane(BG_A, TRUE);
        SPR_clear();
}

void intro_redraw(state_return_t ret) {}

state_return_t intro_shutdown() {
    intro_clean();
    state_return_t ret;
    return ret;
}
