#include "state_gamemenu.h"

#include <genesis.h>

#include "graphics/text.h"
#include "graphics/textbox.h"
#include "graphics/utils.h"
#include "savedata.h"
#include "state_menu.h"
savedata_t *data;

const char option_texts[3][MAX_LINE_LENGTH] = {"ITEM", "STAT", "CELL"};

void gamemenu_init(state_parameters_t args) {
    char lvbuf[6], hpbuf[9], gbuf[9];
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

    VDP_drawText(lvbuf, 2, 5);
    VDP_drawText(hpbuf, 2, 6);
    VDP_drawText(gbuf, 2, 7);
//    VDP_drawText(lvbuf, 2, 5);
  //  VDP_drawText(hpbuf, 2, 6);
    //VDP_drawText(gbuf, 2, 7);
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
