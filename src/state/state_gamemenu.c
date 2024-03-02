#include "state_gamemenu.h"

#include <genesis.h>

#include "state_menu.h"
#include "graphics/utils.h"
#include "graphics/text.h"
#include "graphics/textbox.h"
#include "savedata.h"
savedata_t *data;

void gamemenu_init(state_parameters_t args) {
    char lvbuf[6], hpbuf[9], gbuf[9];
    data = (savedata_t*)args.parameter_data;
    box_draw(1, 1, 10, 8, PAL1);
    box_draw(1, 8, 10, 11, PAL1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, TRUE, FALSE, TRUE, 
					  TILE_USER_INDEX + 157),1, 8);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, 
                                          TILE_USER_INDEX + 157),10, 8);
    VDP_fillTileMapRect(BG_A, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, TILE_USER_INDEX + 156), 2,
                        8, 8, 1);
    sprintf(lvbuf, "LV %d", data->love);
    sprintf(hpbuf, "HP %d\\%d", data->hp, data->maxhp);
    sprintf(gbuf, "G  %d", data->gold);
    strconvert(lvbuf);
    strconvert(hpbuf);
    strconvert(gbuf);
    for (u8 i = 0; data->name[i] != '\0'; i++) {
    	draw_letter(data->name[i], 2+i, 2, TILE_USER_INDEX, BG_A, PAL1, 0);
    }

    draw_letter('I', 5, 10, TILE_USER_INDEX, BG_A, PAL1, 0);
    draw_letter('T', 6, 10, TILE_USER_INDEX, BG_A, PAL1, 0);
    draw_letter('E', 7, 10, TILE_USER_INDEX, BG_A, PAL1, 0);
    draw_letter('M', 8, 10, TILE_USER_INDEX, BG_A, PAL1, 0);
    
    draw_letter('S', 5, 12, TILE_USER_INDEX, BG_A, PAL1, 0);
    draw_letter('T', 6, 12, TILE_USER_INDEX, BG_A, PAL1, 0);
    draw_letter('A', 7, 12, TILE_USER_INDEX, BG_A, PAL1, 0);
    draw_letter('T', 8, 12, TILE_USER_INDEX, BG_A, PAL1, 0);

    if (data->cell != 0) {
	draw_letter('C', 5, 14, TILE_USER_INDEX, BG_A, PAL1, 0);
	draw_letter('E', 6, 14, TILE_USER_INDEX, BG_A, PAL1, 0);
	draw_letter('L', 7, 14, TILE_USER_INDEX, BG_A, PAL1, 0);
	draw_letter('L', 8, 14, TILE_USER_INDEX, BG_A, PAL1, 0);
    }
    VDP_drawText(lvbuf, 2, 5);
    VDP_drawText(hpbuf, 2, 6);
    VDP_drawText(gbuf, 2, 7);
}
void gamemenu_input(u16 changed, u16 state) {
    if (changed & BUTTON_START && (state & BUTTON_START)) {
        state_pop();
    }
}
void gamemenu_update() {}
void gamemenu_clean() { VDP_clearTextArea(0, 0, 40, 28); }
void gamemenu_redraw(state_return_t ret) {}
state_return_t gamemenu_shutdown() {
    gamemenu_clean();
    state_return_t ret;
    return ret;
}
