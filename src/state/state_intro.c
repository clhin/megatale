#include "state_intro.h"

#include <genesis.h>
#include <resources.h>

#include "state_menu.h"
#include "../graphics/textbox.h"
#include "../graphics/text.h"

int stage = 0;
int change = 0;

int duration = 50;

void intro_init(state_parameters_t args) {
    stage = 0;
    duration = 50;
    VDP_setScrollingMode(HSCROLL_PLANE,VSCROLL_PLANE);
    fix16 offsetX = FIX16(0);
    fix16 offsetY = FIX16(0);
}



void intro_update() {
    if(stage != 11){
        duration = 50;
    }
    if(stage == 0){
        s16 textPosX = 10;
        s16 textPosY = 20;
        VDP_loadTileSet(&font_sheet, TILE_USER_INDEX, DMA);

        u8 textPosX1 = 10;
        u8 textPosY1 = 20;
        u16 index = TILE_USER_INDEX + font_sheet.numTile;
        intro_clean();
        const char lines[3][33] = {
        "Long ago, two races",
        "ruled over Earth:",
        "HUMANS and MONSTERS"
        };

        PAL_setPalette(PAL1, font_sheet_image.palette->data, DMA);
        draw_lines(lines, 3, textPosX1, textPosY1, TILE_USER_INDEX, BG_A, PAL1);
        

        VDP_loadTileSet(&intro_0_tiles, index, DMA);
        PAL_setPalette(PAL2, intropal.data, DMA);
        u32 offset = 0;
        Map *map;
        map = MAP_create(&intro_0, BG_B, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, index));
        MAP_scrollTo(map, offset,0);
        stage++;
    }else if(stage == 1){
        s16 textPosX = 10;
        s16 textPosY = 20;
        VDP_loadTileSet(&font_sheet, TILE_USER_INDEX, DMA);

        u8 textPosX1 = 10;
        u8 textPosY1 = 20;
        u16 index = TILE_USER_INDEX + font_sheet.numTile;
        for(int i =0 ; i<duration; i++){
            waitMs  (100);
        }
        intro_clean();

        const char lines1[3][33] = {
            "One day, war broke",
            "out between two",
            "races"
        };

        PAL_setPalette(PAL1, font_sheet_image.palette->data, DMA);
        draw_lines(lines1, 3, textPosX1, textPosY1, TILE_USER_INDEX, BG_A, PAL1);

        VDP_loadTileSet(&intro_1_tiles, index, DMA);
        PAL_setPalette(PAL2, intropal.data, DMA);
        u32 offset = 0;
        Map *map;
        map = MAP_create(&intro_1, BG_B, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, index));
        MAP_scrollTo(map, offset,0);
        stage++;
    }else if(stage == 2){
        s16 textPosX = 10;
        s16 textPosY = 20;
        VDP_loadTileSet(&font_sheet, TILE_USER_INDEX, DMA);

        u8 textPosX1 = 10;
        u8 textPosY1 = 20;
        u16 index = TILE_USER_INDEX + font_sheet.numTile;
        for(int i =0 ; i<duration; i++){
            waitMs  (100);
        }
        intro_clean();
            
        const char lines2[3][33] = {
                "After a long battle",
                "the humans were",
                "victorious."
        };

        PAL_setPalette(PAL1, font_sheet_image.palette->data, DMA);
        draw_lines(lines2, 3, textPosX1, textPosY1, TILE_USER_INDEX, BG_A, PAL1);

        VDP_loadTileSet(&intro_2_tiles, index, DMA);
        PAL_setPalette(PAL2, intropal.data, DMA);
        u32 offset = 0;
        Map *map;
        map = MAP_create(&intro_2, BG_B, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, index));
        MAP_scrollTo(map, offset,0);
        stage++;
    }else if(stage == 3){
        s16 textPosX = 10;
        s16 textPosY = 20;
        VDP_loadTileSet(&font_sheet, TILE_USER_INDEX, DMA);

        u8 textPosX1 = 10;
        u8 textPosY1 = 20;
        u16 index = TILE_USER_INDEX + font_sheet.numTile;
        for(int i =0 ; i<duration; i++){
            waitMs  (100);
        }
        intro_clean();

        const char lines3[3][33] = {
            "They sealed the monsters",
            "underground with a magic",
            "spell."
        };

        PAL_setPalette(PAL1, font_sheet_image.palette->data, DMA);
        draw_lines(lines3, 3, textPosX1, textPosY1, TILE_USER_INDEX, BG_A, PAL1);

        VDP_loadTileSet(&intro_3_tiles, index, DMA);
        PAL_setPalette(PAL2, intropal.data, DMA);
        u32 offset = 0;
        Map *map;
        map = MAP_create(&intro_3, BG_B, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, index));
        MAP_scrollTo(map, offset,0);
        stage++;
    }else if(stage == 4){
        s16 textPosX = 10;
        s16 textPosY = 20;
        VDP_loadTileSet(&font_sheet, TILE_USER_INDEX, DMA);

        u8 textPosX1 = 10;
        u8 textPosY1 = 20;
        u16 index = TILE_USER_INDEX + font_sheet.numTile;
        for(int i =0 ; i<duration; i++){
            waitMs  (100);
        }
        intro_clean();
        const char lines4[1][33] = {
            "Many years later..."
        };

        PAL_setPalette(PAL1, font_sheet_image.palette->data, DMA);
        draw_lines(lines4, 1, textPosX1, textPosY1, TILE_USER_INDEX, BG_A, PAL1);
        stage++;
    }else if(stage == 5){
        s16 textPosX = 10;
        s16 textPosY = 20;
        VDP_loadTileSet(&font_sheet, TILE_USER_INDEX, DMA);

        u8 textPosX1 = 10;
        u8 textPosY1 = 20;
        u16 index = TILE_USER_INDEX + font_sheet.numTile;
        for(int i =0 ; i<duration; i++){
            waitMs  (100);
        }
        intro_clean();
        const char lines5[2][33] = {
            "MT. EBOTT",
            "201X"
        };

        PAL_setPalette(PAL1, font_sheet_image.palette->data, DMA);
        draw_lines(lines5, 2, textPosX1, textPosY1, TILE_USER_INDEX, BG_A, PAL1);

       VDP_loadTileSet(&intro_5_tiles, index, DMA);
        PAL_setPalette(PAL2, intropal.data, DMA);
        u32 offset = 0;
        Map *map;
        map = MAP_create(&intro_5, BG_B, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, index));
        MAP_scrollTo(map, offset,0);
        stage++;
    }else if(stage == 6){
        s16 textPosX = 10;
        s16 textPosY = 20;
        VDP_loadTileSet(&font_sheet, TILE_USER_INDEX, DMA);

        u8 textPosX1 = 10;
        u8 textPosY1 = 20;
        u16 index = TILE_USER_INDEX + font_sheet.numTile;
        for(int i =0 ; i<duration; i++){
            waitMs  (100);
        }
        intro_clean();

        const char lines6[3][33] = {
            "Legends say that those",
            "who climb the mountain",
            "never returns"
        };


        PAL_setPalette(PAL1, font_sheet_image.palette->data, DMA);
        draw_lines(lines6, 2, textPosX1, textPosY1, TILE_USER_INDEX, BG_A, PAL1);

        VDP_loadTileSet(&intro_6_tiles, index, DMA);
        PAL_setPalette(PAL2, intropal.data, DMA);
        u32 offset = 0;
        Map *map;
        map = MAP_create(&intro_6, BG_B, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, index));
        MAP_scrollTo(map, offset,0);
        stage++;
    }else if(stage == 7){
        s16 textPosX = 10;
        s16 textPosY = 20;
        VDP_loadTileSet(&font_sheet, TILE_USER_INDEX, DMA);

        u8 textPosX1 = 10;
        u8 textPosY1 = 20;
        u16 index = TILE_USER_INDEX + font_sheet.numTile;
        for(int i =0 ; i<duration; i++){
            waitMs  (100);
        }
        intro_clean();
        VDP_setTextPlane(BG_A);
        VDP_setPaletteColor(0,RGB24_TO_VDPCOLOR(0x000000));

        VDP_loadTileSet(&intro_7_tiles, index, DMA);
        PAL_setPalette(PAL2, intropal.data, DMA);
        u32 offset = 0;
        Map *map;
        map = MAP_create(&intro_7, BG_B, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, index));
        MAP_scrollTo(map, offset,0);
        stage++;
    }else if(stage == 8){
        s16 textPosX = 10;
        s16 textPosY = 20;
        VDP_loadTileSet(&font_sheet, TILE_USER_INDEX, DMA);

        u8 textPosX1 = 10;
        u8 textPosY1 = 20;
        u16 index = TILE_USER_INDEX + font_sheet.numTile;
        for(int i =0 ; i<duration; i++){
            waitMs  (100);
        }
        intro_clean();
        VDP_setTextPlane(BG_A);
        VDP_setPaletteColor(0,RGB24_TO_VDPCOLOR(0x000000));

        VDP_loadTileSet(&intro_8_tiles, index, DMA);
        PAL_setPalette(PAL2, intropal.data, DMA);
        u32 offset = 0;
        Map *map;
        map = MAP_create(&intro_8, BG_B, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, index));
        MAP_scrollTo(map, offset,0);
        stage++;
    }else if(stage == 9){
        s16 textPosX = 10;
        s16 textPosY = 20;
        VDP_loadTileSet(&font_sheet, TILE_USER_INDEX, DMA);

        u8 textPosX1 = 10;
        u8 textPosY1 = 20;
        u16 index = TILE_USER_INDEX + font_sheet.numTile;
        for(int i =0 ; i<duration; i++){
            waitMs  (100);
        }
        intro_clean();

        VDP_setTextPlane(BG_A);
        VDP_setPaletteColor(0,RGB24_TO_VDPCOLOR(0x000000));

        VDP_loadTileSet(&intro_9_tiles, index, DMA);
        PAL_setPalette(PAL2, intropal.data, DMA);
        u32 offset = 0;
        Map *map;
        map = MAP_create(&intro_9, BG_B, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, index));
        stage++;
    }else if(stage == 10){
        s16 textPosX = 10;
        s16 textPosY = 20;
        VDP_loadTileSet(&font_sheet, TILE_USER_INDEX, DMA);

        u8 textPosX1 = 10;
        u8 textPosY1 = 20;
        u16 index = TILE_USER_INDEX + font_sheet.numTile;
        for(int i =0 ; i<duration; i++){
            waitMs  (100);
        }
        intro_clean();
        VDP_setTextPlane(BG_A);
        VDP_setPaletteColor(0,RGB24_TO_VDPCOLOR(0x000000));


        VDP_loadTileSet(&intro_last_tiles, index, DMA);
        PAL_setPalette(PAL2, intropal.data, DMA);
        u32 offset = 0;
        Map *map;
        map = MAP_create(&intro_last, BG_B, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, index));
        stage++;
    }else{
        intro_clean();
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

void intro_input(u16 changed, u16 state) {
    //keep  
    if (changed & BUTTON_A && (state & BUTTON_A)){
        stage = 11;
        duration = 0;
    }
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
