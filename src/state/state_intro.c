#include "state_intro.h"

#include <genesis.h>
#include <resources.h>

#include "state_menu.h"



void intro_init(state_parameters_t args) {
    s16 textPosX = 10;
    s16 textPosY = 20;

    VDP_setPlaneSize(32,128,TRUE);
    VDP_setTextPlane(BG_A);

    VDP_setPaletteColor(0,RGB24_TO_VDPCOLOR(0x000000));

    VDP_loadTileSet(intro_0_images.tileset, 1, DMA);
    PAL_setPalette(PAL1, intro_0_images.palette->data, DMA);
    VDP_setTileMapEx(BG_B, intro_0_images.tilemap ,TILE_ATTR_FULL(PAL1,0,FALSE,FALSE,1),0,0,0,0,32,18,DMA);


    VDP_drawText("Long ago, two races", textPosX, textPosY);
    VDP_drawText("ruled over Earth:", textPosX, textPosY+1);
    VDP_drawText("HUMANS and MONSTERS", textPosX, textPosY+2);

}
void intro_input(u16 changed, u16 state) {
    //keep
    if (changed & BUTTON_A && (state & BUTTON_A)) {
        state_info_t state_info;
        state_info.clean = menu_clean;
        state_info.init = menu_init;
        state_info.redraw = menu_redraw;
        state_info.input = menu_input;
        state_info.update = menu_update;
        state_info.shutdown = menu_shutdown;

        state_parameters_t args;
        state_replace(state_info, args);
    }
}

void intro_update() {}

void intro_clean() { 
    VDP_clearTextArea(0, 0, 40, 28);
    VDP_clearPlane(BG_B, TRUE);
 }

void intro_redraw(state_return_t ret) {}

state_return_t intro_shutdown() {
    intro_clean();
    state_return_t ret;
    return ret;
}