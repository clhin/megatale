#include "state_intro.h"

#include <genesis.h>
#include <resources.h>

#include "state_menu.h"
#include "../graphics/textbox.h"
#include "../graphics/text.h"


void intro_init(state_parameters_t args) {
    s16 textPosX = 10;
    s16 textPosY = 20;


    /*
    const char lines[3][33] = {
    "Long ago, two races",
    "ruled over Earth:",
    "HUMANS and MONSTERS"
    };
    u8 numLines = 3;
    u8 textPosX1 = 10;
    u8 textPosY1 = 20;
    u16 offset = 1;
    // Use textbox_init function to draw the text
    VDP_loadTileSet(font.tileset, 1, DMA);
    PAL_setPalette(PAL0, font.palette->data, DMA);
    VDP_setPaletteColor(0,RGB24_TO_VDPCOLOR(0x000000));
    draw_lines(lines, 3, textPosX1, textPosY1, offset, BG_A, PAL0);
    */
    VDP_loadTileSet(intro_0_images.tileset, 1, DMA);
    PAL_setPalette(PAL1, intro_0_images.palette->data, DMA);
    VDP_setTileMapEx(BG_B, intro_0_images.tilemap ,TILE_ATTR_FULL(PAL1,0,FALSE,FALSE,1),1,0,0,0,32,18,DMA);
    VDP_drawText("Long ago, two races", textPosX, textPosY);
    VDP_drawText("ruled over Earth:", textPosX, textPosY+1);
    VDP_drawText("HUMANS and MONSTERS", textPosX, textPosY+2);

    waitMs	(5000);
        intro_clean();
        VDP_setTextPlane(BG_A);
        VDP_setPaletteColor(0,RGB24_TO_VDPCOLOR(0x000000));

        VDP_loadTileSet(intro_1_images.tileset, 1, DMA);
        PAL_setPalette(PAL1, intro_1_images.palette->data, DMA);
        VDP_setTileMapEx(BG_B, intro_1_images.tilemap ,TILE_ATTR_FULL(PAL1,0,FALSE,FALSE,1),1,0,0,0,32,18,DMA);

        VDP_drawText("One day, war broke", textPosX, textPosY);
        VDP_drawText("out between two", textPosX, textPosY+1);
        VDP_drawText("races", textPosX, textPosY+2);


        waitMs	(5000);
        intro_clean();
        VDP_setTextPlane(BG_A);
        VDP_setPaletteColor(0,RGB24_TO_VDPCOLOR(0x000000));

        VDP_loadTileSet(intro_2_images.tileset, 1, DMA);
        PAL_setPalette(PAL1, intro_2_images.palette->data, DMA);
        VDP_setTileMapEx(BG_B, intro_2_images.tilemap ,TILE_ATTR_FULL(PAL1,0,FALSE,FALSE,1),1,0,0,0,32,18,DMA);

        VDP_drawText("After a long battle,", textPosX, textPosY);
        VDP_drawText("the humans were", textPosX, textPosY+1);
        VDP_drawText("victorious", textPosX, textPosY+2);

        waitMs	(5000);
        intro_clean();
        VDP_setTextPlane(BG_A);
        VDP_setPaletteColor(0,RGB24_TO_VDPCOLOR(0x000000));

        VDP_loadTileSet(intro_3_images.tileset, 1, DMA);
        PAL_setPalette(PAL1, intro_3_images.palette->data, DMA);
        VDP_setTileMapEx(BG_B, intro_3_images.tilemap ,TILE_ATTR_FULL(PAL1,0,FALSE,FALSE,1),1,0,0,0,32,18,DMA);

        VDP_drawText("They sealed the monsters", textPosX, textPosY);
        VDP_drawText("underground with a magic", textPosX, textPosY+1);
        VDP_drawText("spell/", textPosX, textPosY+2);

        waitMs	(5000);
        intro_clean();
        VDP_drawText("Many years later...", textPosX, textPosY);

        waitMs	(5000);
        intro_clean();
        VDP_setTextPlane(BG_A);
        VDP_setPaletteColor(0,RGB24_TO_VDPCOLOR(0x000000));

        VDP_loadTileSet(intro_5_images.tileset, 1, DMA);
        PAL_setPalette(PAL1, intro_5_images.palette->data, DMA);
        VDP_setTileMapEx(BG_B, intro_5_images.tilemap ,TILE_ATTR_FULL(PAL1,0,FALSE,FALSE,1),1,0,0,0,32,18,DMA);

        VDP_drawText("MT. EBOTT", textPosX, textPosY);
        VDP_drawText("201X", textPosX, textPosY+1);

        waitMs	(5000);
        intro_clean();
        VDP_setTextPlane(BG_A);
        VDP_setPaletteColor(0,RGB24_TO_VDPCOLOR(0x000000));

        VDP_loadTileSet(intro_6_images.tileset, 1, DMA);
        PAL_setPalette(PAL1, intro_6_images.palette->data, DMA);
        VDP_setTileMapEx(BG_B, intro_6_images.tilemap ,TILE_ATTR_FULL(PAL1,0,FALSE,FALSE,1),1,0,0,0,32,18,DMA);

        VDP_drawText("Legends say that those", textPosX, textPosY);
        VDP_drawText("who climb the mountain", textPosX, textPosY+1);
        VDP_drawText("never returns", textPosX, textPosY+2);

        
        waitMs	(5000);
        intro_clean();
        VDP_setTextPlane(BG_A);
        VDP_setPaletteColor(0,RGB24_TO_VDPCOLOR(0x000000));

        VDP_loadTileSet(intro_7_images.tileset, 1, DMA);
        PAL_setPalette(PAL1, intro_7_images.palette->data, DMA);
        VDP_setTileMapEx(BG_B, intro_7_images.tilemap ,TILE_ATTR_FULL(PAL1,0,FALSE,FALSE,1),1,0,0,0,32,18,DMA);


        waitMs	(5000);
        intro_clean();
        VDP_setTextPlane(BG_A);
        VDP_setPaletteColor(0,RGB24_TO_VDPCOLOR(0x000000));

        VDP_loadTileSet(intro_8_images.tileset, 1, DMA);
        PAL_setPalette(PAL1, intro_8_images.palette->data, DMA);
        VDP_setTileMapEx(BG_B, intro_8_images.tilemap ,TILE_ATTR_FULL(PAL1,0,FALSE,FALSE,1),1,0,0,0,32,18,DMA);


        waitMs	(5000);
        intro_clean();

        VDP_setTextPlane(BG_A);
        VDP_setPaletteColor(0,RGB24_TO_VDPCOLOR(0x000000));

        VDP_loadTileSet(intro_9_images.tileset, 1, DMA);
        PAL_setPalette(PAL1, intro_9_images.palette->data, DMA);
        VDP_setTileMapEx(BG_B, intro_9_images.tilemap ,TILE_ATTR_FULL(PAL1,0,FALSE,FALSE,1),1,0,0,0,32,18,DMA);


        waitMs	(5000);
        intro_clean();
        VDP_setTextPlane(BG_A);
        VDP_setPaletteColor(0,RGB24_TO_VDPCOLOR(0x000000));

        VDP_loadTileSet(intro_last_images.tileset, 1, DMA);
        PAL_setPalette(PAL1, intro_last_images.palette->data, DMA);
        VDP_setTileMapEx(BG_B, intro_last_images.tilemap ,TILE_ATTR_FULL(PAL1,0,FALSE,FALSE,1),1,0,0,0,32,18,DMA);

}
void intro_input(u16 changed, u16 state) {
    //keep    
    if (changed & BUTTON_A && (state & BUTTON_A)){
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


void intro_update() {
}

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