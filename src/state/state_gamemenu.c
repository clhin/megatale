#include "state_gamemenu.h"

#include <genesis.h>
#include <resources.h>
#include "graphics/text.h"
#include "graphics/textbox.h"
#include "graphics/strutils.h"
#include "savedata.h"
#include "state_menu.h"

#include "audio/audioEffects.h"

savedata_t *data;
Sprite * heart; 
u8 current_selection;

#define ITEM 0
#define STAT 1
#define CELL 2

const char option_texts[3][MAX_LINE_LENGTH] = {"ITEM", "STAT", "CELL"};

void gamemenu_init(state_parameters_t args) {
    selectSound();
    char lvbuf[6], hpbuf[9], gbuf[9];
    PAL_setPalette(PAL2, intropal.data, DMA);
    heart = SPR_addSprite(&heart_sprite, 3 * 8, data->item[0] ? 11 *  8 - 1 : 13 * 8 - 1,
			  TILE_ATTR(PAL1, TRUE, FALSE, FALSE));
    current_selection = data->item[0] ? 0 : 1;
    data = (savedata_t *)args.parameter_data;
    box_draw(1, 1, 10, 8, PAL1);
    box_draw(1, 8, 10, 11, PAL1);
    VDP_setTileMapXY(
        BG_A, TILE_ATTR_FULL(PAL1, TRUE, FALSE, TRUE, TILE_USER_INDEX + 157), 1,
        8);
    VDP_setTileMapXY(
        BG_A, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, TILE_USER_INDEX + 157),
        10, 8);
    VDP_fillTileMapRect(
        BG_A, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, TILE_USER_INDEX + 156),
        2, 8, 8, 1);
    sprintf(lvbuf, "LV %d", data->love);
    sprintf(hpbuf, "HP %d\\%d", data->hp, data->maxhp);
    sprintf(gbuf, "G  %d", data->gold);
    strconvert(lvbuf);
    strconvert(hpbuf);
    strconvert(gbuf);
    //for (u8 i = 0; data->name[i] != '\0'; i++) {
    //    draw_letter(data->name[i], 2 + i, 2, TILE_USER_INDEX, BG_A, PAL1, 0);
    //}
    draw_lines(option_texts, data->cell != 0 ? 3 : 2, 5, 10, TILE_USER_INDEX,
               BG_A, PAL1);
    current_selection = 0;
    if (data->item[0] == 0) {
	// Just kidding, rewrite the ITEM entry in gray
	draw_letter('I', NULL, 5, 10, TILE_USER_INDEX, BG_A, PAL2);
        draw_letter('T', NULL, 6, 10, TILE_USER_INDEX, BG_A, PAL2);
        draw_letter('E', NULL, 7, 10, TILE_USER_INDEX, BG_A, PAL2);
        draw_letter('M', NULL, 8, 10, TILE_USER_INDEX, BG_A, PAL2);
	VDP_setTileMapXY(
        BG_A, TILE_ATTR_FULL(PAL1, TRUE, 0, 0, TILE_USER_INDEX + 31),
        5, 12);
VDP_setTileMapXY(
        BG_A, TILE_ATTR_FULL(PAL1, TRUE, 0, 0, TILE_USER_INDEX + 33),
        6, 12);
VDP_setTileMapXY(
        BG_A, TILE_ATTR_FULL(PAL1, TRUE, 0, 0, TILE_USER_INDEX + 31),
        7, 12);
VDP_setTileMapXY(
        BG_A, TILE_ATTR_FULL(PAL1, TRUE, 0, 0, TILE_USER_INDEX + 33),
        8, 12);
	current_selection = 1;
    }

    VDP_drawText(lvbuf, 2, 5);
    VDP_drawText(hpbuf, 2, 6);
    VDP_drawText(gbuf, 2, 7);
}
void gamemenu_input(u16 changed, u16 state) {
    if (changed & BUTTON_START && (state & BUTTON_START)) {
        state_pop();
    }
    if (state & BUTTON_A) {
	if (current_selection == ITEM) {
	} else if (current_selection == STAT) {
	    box_draw(11, 1, 24, 27, PAL1);
	    char stats[12][33];
	    //stats[0][0] = '\0';
	    //sprintf(stats[0], " ");
	    strcpy(stats[0], "\"CHARA\""); //replace with data->name when main menu is done
	    strcpy(stats[1], " ");
	    sprintf(stats[2], "LV %d", data->love);
	    sprintf(stats[3], "HP %d/%d", data->hp, data->maxhp);
	    sprintf(stats[4], " ");
	    sprintf(stats[5], "AT %d(%d)     ", data->at, data->at);
	    sprintf(stats[6], "DF %d(%d)     ", data->def, data->def);
	    sprintf(stats[5]+10, "EXP:%d", data->exp);
	    sprintf(stats[6]+10, "NEXT:65535");//, data->exp);
	    
	    strcpy(stats[7], " ");
	    sprintf(stats[8], "WEAPON:%s", getitemname(data->weapon)); //replace with item to name translated
	    sprintf(stats[9], "ARMOR:%s", getitemname(data->armor));
	    strcpy(stats[10], " ");
	    sprintf(stats[11], "GOLD: %d    ", data->gold);
	    if (data->kills > 0)
		sprintf(stats[11]+10, "KILLS:%d", data->kills);
	    draw_lines(stats, 12, 13, 2,
                TILE_USER_INDEX, BG_A, PAL1);

	   //draw_lines(exp, 2, 23, 12, TILE_USER_INDEX, BG_A, PAL1);
	} else { // cell phone
	    box_draw(11, 1, 24, 18, PAL1);
	    char selections [1][33];
	    // this will need to be adjusted later for other callers
	    // for now we can just use toriel
	    strcpy(selections[0], "Toriel's Phone");
	    draw_lines(selections, 1, 16, 2,
                TILE_USER_INDEX, BG_A, PAL1);
	}
    }
    if (state & BUTTON_B) {}
    if (state & BUTTON_UP) {
	if (current_selection == ITEM) {
	    if (data->cell != 0) {
	        current_selection = CELL;
	        SPR_setPosition(heart, 3 * 8, 15 * 8 - 1);
	    } else {
	        current_selection = STAT;
		SPR_setPosition(heart, 3 * 8, 13 * 8 - 1);
	    }
	
	} else if (current_selection == STAT) {
	    if (data->item[0] != 0) {
		current_selection = ITEM;
		SPR_setPosition(heart, 3 * 8, 11 * 8 - 1);	
	    } else if (data->cell != 0) {
		current_selection = CELL;
                SPR_setPosition(heart, 3 * 8, 15 * 8 - 1);
	    }
	} else if (current_selection == CELL) {
	    current_selection = STAT;
            SPR_setPosition(heart, 3 * 8, 13 * 8 - 1);
	}
    } else if (state & BUTTON_DOWN) {
	if (current_selection == ITEM) {
            current_selection = STAT;
            SPR_setPosition(heart, 3 * 8, 13 * 8 - 1);
        } else if (current_selection == STAT) {
           if (data->cell != 0) {
		current_selection = CELL;
		SPR_setPosition(heart, 3 * 8, 15 * 8 - 1);
	   } else if (data->item[0] != 0){
		current_selection = ITEM;
		SPR_setPosition(heart, 3 * 8, 11 * 8 - 1);
	   }
        } else if (current_selection == CELL) {
	   if (data->item[0] != 0){
                current_selection = ITEM;
                SPR_setPosition(heart, 3 * 8, 11 * 8 - 1);
           } else {
		current_selection = STAT;
		SPR_setPosition(heart, 3 * 8, 13 * 8 - 1);
	   }
	}
    }
}
void gamemenu_update() {}
void gamemenu_clean() { 
    SPR_releaseSprite(heart);
    VDP_clearTextArea(0, 0, 40, 28);
}
void gamemenu_redraw(state_return_t ret) {}
state_return_t gamemenu_shutdown() {
    gamemenu_clean();
    state_return_t ret;
    return ret;
}
