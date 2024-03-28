#include "state_intro.h"

#include <genesis.h>
#include <resources.h>

#include "state_menu.h"
#include "../graphics/textbox.h"
#include "../graphics/text.h"


void intro_init(state_parameters_t args) {
    s16 textPosX = 10;
    s16 textPosY = 20;
    VDP_loadTileSet(&font_sheet, TILE_USER_INDEX, DMA);

    const char lines[3][33] = {
    "Long ago, two races",
    "ruled over Earth:",
    "HUMANS and MONSTERS"
    };

    u8 textPosX1 = 10;
    u8 textPosY1 = 20;
    u16 index = TILE_USER_INDEX + font_sheet.numTile;
    PAL_setPalette(PAL1, font_sheet_image.palette->data, DMA);
    draw_lines(lines, 3, textPosX1, textPosY1, TILE_USER_INDEX, BG_A, PAL1);


    VDP_loadTileSet(intro_0_images.tileset, index, DMA);
    PAL_setPalette(PAL2, intro_0_images.palette->data, DMA);
    VDP_setTileMapEx(BG_B, intro_0_images.tilemap ,TILE_ATTR_FULL(PAL2,0,FALSE,FALSE,index),1,0,0,0,32,18,DMA);

    waitMs	(5000);
        intro_clean();

            const char lines1[3][33] = {
            "One day, war broke",
            "out between two",
            "races"
            };

    PAL_setPalette(PAL1, font_sheet_image.palette->data, DMA);
    draw_lines(lines1, 3, textPosX1, textPosY1, TILE_USER_INDEX, BG_A, PAL1);

    VDP_loadTileSet(intro_1_images.tileset, index, DMA);
    PAL_setPalette(PAL2, intro_1_images.palette->data, DMA);
    VDP_setTileMapEx(BG_B, intro_1_images.tilemap ,TILE_ATTR_FULL(PAL2,0,FALSE,FALSE,index),1,0,0,0,32,18,DMA);

    waitMs	(5000);
        intro_clean();
        
        const char lines2[3][33] = {
            "After a long battle",
            "the humans were",
            "victorious."
        };

    PAL_setPalette(PAL1, font_sheet_image.palette->data, DMA);
    draw_lines(lines2, 3, textPosX1, textPosY1, TILE_USER_INDEX, BG_A, PAL1);

    VDP_loadTileSet(intro_2_images.tileset, index, DMA);
    PAL_setPalette(PAL2, intro_2_images.palette->data, DMA);
    VDP_setTileMapEx(BG_B, intro_2_images.tilemap ,TILE_ATTR_FULL(PAL2,0,FALSE,FALSE,index),1,0,0,0,32,18,DMA);

    waitMs	(5000);
        intro_clean();

        const char lines3[3][33] = {
            "They sealed the monsters",
            "underground with a magic",
            "spell."
        };

    PAL_setPalette(PAL1, font_sheet_image.palette->data, DMA);
    draw_lines(lines3, 3, textPosX1, textPosY1, TILE_USER_INDEX, BG_A, PAL1);

    VDP_loadTileSet(intro_3_images.tileset, index, DMA);
    PAL_setPalette(PAL2, intro_3_images.palette->data, DMA);
    VDP_setTileMapEx(BG_B, intro_3_images.tilemap ,TILE_ATTR_FULL(PAL2,0,FALSE,FALSE,index),1,0,0,0,32,18,DMA);
        
    waitMs	(5000);
        intro_clean();
       const char lines4[1][33] = {
            "Many years later..."
        };

    PAL_setPalette(PAL1, font_sheet_image.palette->data, DMA);
    draw_lines(lines4, 1, textPosX1, textPosY1, TILE_USER_INDEX, BG_A, PAL1);

    waitMs	(5000);
        intro_clean();
        const char lines5[2][33] = {
            "MT. EBOTT",
            "201X"
        };

    PAL_setPalette(PAL1, font_sheet_image.palette->data, DMA);
    draw_lines(lines5, 2, textPosX1, textPosY1, TILE_USER_INDEX, BG_A, PAL1);

    VDP_loadTileSet(intro_5_images.tileset, index, DMA);
    PAL_setPalette(PAL2, intro_5_images.palette->data, DMA);
    VDP_setTileMapEx(BG_B, intro_5_images.tilemap ,TILE_ATTR_FULL(PAL2,0,FALSE,FALSE,index),1,0,0,0,32,18,DMA);


    waitMs	(5000);
        intro_clean();

        const char lines6[3][33] = {
            "Legends say that those",
            "who climb the mountain",
            "never returns"
        };


    PAL_setPalette(PAL1, font_sheet_image.palette->data, DMA);
    draw_lines(lines6, 2, textPosX1, textPosY1, TILE_USER_INDEX, BG_A, PAL1);

    VDP_loadTileSet(intro_6_images.tileset, index, DMA);
    PAL_setPalette(PAL2, intro_6_images.palette->data, DMA);
    VDP_setTileMapEx(BG_B, intro_6_images.tilemap ,TILE_ATTR_FULL(PAL2,0,FALSE,FALSE,index),1,0,0,0,32,18,DMA);


        
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