#include "state_intro.h"

#include <genesis.h>
#include <resources.h>

#include "state_menu.h"
#include "../graphics/textbox.h"
#include "../graphics/text.h"



char get_letter(char *str, int idx)
{
    return *(str + idx);
}

int stage = 0;
int change = 0;

int duration = 50;

void intro_init(state_parameters_t args) {
    stage = 0;
    duration = 50;
}



void intro_update() {
    if(stage != 11){
        duration = 50;
    }
    if(stage == 0){
        VDP_loadTileSet(&font_sheet, TILE_USER_INDEX, DMA);

        u8 textPosX1 = 10;
        u8 textPosY1 = 18;
        u16 index = TILE_USER_INDEX + font_sheet.numTile;
        intro_clean();
        const char lines[3][33] = {
        "Long ago, two races",
        "ruled over Earth:",
        "HUMANS and MONSTERS"
        };


        PAL_setPalette(PAL1, textpal.data, DMA);
        /*
        for(unsigned int i = 0; i< sizeof(lines); i++){
            char* line = lines[i];
            for(unsigned int j = 0; j < sizeof(line); j++){
                if(i == 0){
                    draw_letter(get_letter(line, j), '\0', textPosX1+j, textPosY1+i, TILE_USER_INDEX, BG_A, PAL1);
                }else{
                    char* line_1 = lines[i-1];
                    if(j<sizeof(line_1)){
                        draw_letter(get_letter(line, j), get_letter(line_1, j), textPosX1+j, textPosY1+i, TILE_USER_INDEX, BG_A, PAL1);
                    }else{
                        draw_letter(get_letter(line, j), '\0', textPosX1+j, textPosY1+i, TILE_USER_INDEX, BG_A, PAL1);
                    }
                }
            }
        }
        */


        //draw_lines(lines, 3, textPosX1, textPosY1, TILE_USER_INDEX, BG_A, PAL1);
        //draw_letter(char letter, char above, u8 x, u8 y, u16 offset, u8 plane, u8 palette);

        VDP_loadTileSet(&intro_0_tiles, index, DMA);
        PAL_setPalette(PAL2, intropal.data, DMA);
        u32 offset = 0;
        Map *map;
        map = MAP_create(&intro_0, BG_B, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, index));
        MAP_scrollTo(map, offset,0);


        char* line = lines[0];
        for(unsigned int j = 0; j < 19; j++){
            draw_letter(get_letter(line, j), '\0', textPosX1+j, textPosY1, TILE_USER_INDEX, BG_A, PAL1);
            waitMs(100);
        }
        char* line_1 = lines[1];
        for(unsigned int j = 0; j < 17; j++){
            draw_letter(get_letter(line_1, j), '\0', textPosX1+j, textPosY1+3, TILE_USER_INDEX, BG_A, PAL1);
            waitMs(100);
        }
        char* line_2 = lines[2];
        for(unsigned int j = 0; j < 19; j++){
            draw_letter(get_letter(line_2, j), '\0', textPosX1+j, textPosY1+6, TILE_USER_INDEX, BG_A, PAL1);
            waitMs(100);
        }


        stage++;
    }else if(stage == 1){
        VDP_loadTileSet(&font_sheet, TILE_USER_INDEX, DMA);

        u8 textPosX1 = 10;
        u8 textPosY1 = 18;
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

        VDP_loadTileSet(&intro_1_tiles, index, DMA);
        PAL_setPalette(PAL2, intropal.data, DMA);
        u32 offset = 0;
        Map *map;
        map = MAP_create(&intro_1, BG_B, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, index));
        MAP_scrollTo(map, offset,0);

        char* line = lines1[0];
        for(unsigned int j = 0; j < 18; j++){
            draw_letter(get_letter(line, j), '\0', textPosX1+j, textPosY1, TILE_USER_INDEX, BG_A, PAL1);
            waitMs(100);
        }
        char* line_1 = lines1[1];
        for(unsigned int j = 0; j < 15; j++){
            draw_letter(get_letter(line_1, j), '\0', textPosX1+j, textPosY1+3, TILE_USER_INDEX, BG_A, PAL1);
            waitMs(100);
        }
        char* line_2 = lines1[2];
        for(unsigned int j = 0; j < 5; j++){
            draw_letter(get_letter(line_2, j), '\0', textPosX1+j, textPosY1+6, TILE_USER_INDEX, BG_A, PAL1);
            waitMs(100);
        }
        
        stage++;
    }else if(stage == 2){
        VDP_loadTileSet(&font_sheet, TILE_USER_INDEX, DMA);

        u8 textPosX1 = 10;
        u8 textPosY1 = 18;
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


        VDP_loadTileSet(&intro_2_tiles, index, DMA);
        PAL_setPalette(PAL2, intropal.data, DMA);
        u32 offset = 0;
        Map *map;
        map = MAP_create(&intro_2, BG_B, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, index));
        MAP_scrollTo(map, offset,0);

        char* line = lines2[0];
        for(unsigned int j = 0; j < 19; j++){
            draw_letter(get_letter(line, j), '\0', textPosX1+j, textPosY1, TILE_USER_INDEX, BG_A, PAL1);
            waitMs(100);
        }
        char* line_1 = lines2[1];
        for(unsigned int j = 0; j < 15; j++){
            draw_letter(get_letter(line_1, j), '\0', textPosX1+j, textPosY1+3, TILE_USER_INDEX, BG_A, PAL1);
            waitMs(100);
        }
        char* line_2 = lines2[2];
        for(unsigned int j = 0; j < 11; j++){
            draw_letter(get_letter(line_2, j), '\0', textPosX1+j, textPosY1+6, TILE_USER_INDEX, BG_A, PAL1);
            waitMs(100);
        }

        stage++;
    }else if(stage == 3){
        VDP_loadTileSet(&font_sheet, TILE_USER_INDEX, DMA);

        u8 textPosX1 = 10;
        u8 textPosY1 = 18;
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


        VDP_loadTileSet(&intro_3_tiles, index, DMA);
        PAL_setPalette(PAL2, intropal.data, DMA);
        u32 offset = 0;
        Map *map;
        map = MAP_create(&intro_3, BG_B, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, index));
        MAP_scrollTo(map, offset,0);


        char* line = lines3[0];
        for(unsigned int j = 0; j < 24; j++){
            draw_letter(get_letter(line, j), '\0', textPosX1+j, textPosY1, TILE_USER_INDEX, BG_A, PAL1);
            waitMs(100);
        }
        char* line_1 = lines3[1];
        for(unsigned int j = 0; j < 24; j++){
            draw_letter(get_letter(line_1, j), '\0', textPosX1+j, textPosY1+3, TILE_USER_INDEX, BG_A, PAL1);
            waitMs(100);
        }
        char* line_2 = lines3[2];
        for(unsigned int j = 0; j < 6; j++){
            draw_letter(get_letter(line_2, j), '\0', textPosX1+j, textPosY1+6, TILE_USER_INDEX, BG_A, PAL1);
            waitMs(100);
        }

        stage++;
    }else if(stage == 4){
        VDP_loadTileSet(&font_sheet, TILE_USER_INDEX, DMA);

        u8 textPosX1 = 10;
        u8 textPosY1 = 18;
        u16 index = TILE_USER_INDEX + font_sheet.numTile;
        for(int i =0 ; i<duration; i++){
            waitMs  (100);
        }
        intro_clean();
        const char lines4[1][33] = {
            "Many years later..."
        };

        const char* line = lines4[0];
        for(unsigned int j = 0; j < 19; j++){
            draw_letter(get_letter((char*)line, j), '\0', textPosX1+j, textPosY1, TILE_USER_INDEX, BG_A, PAL1);
            waitMs(100);
        }
        stage++;
    }else if(stage == 5){
        VDP_loadTileSet(&font_sheet, TILE_USER_INDEX, DMA);

        u8 textPosX1 = 10;
        u8 textPosY1 = 18;
        u16 index = TILE_USER_INDEX + font_sheet.numTile;
        for(int i =0 ; i<duration; i++){
            waitMs  (100);
        }
        intro_clean();
        const char lines5[2][33] = {
            "MT. EBOTT",
            "201X"
        };


        VDP_loadTileSet(&intro_5_tiles, index, DMA);
        PAL_setPalette(PAL2, intropal.data, DMA);
        u32 offset = 0;
        Map *map;
        map = MAP_create(&intro_5, BG_B, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, index));
        MAP_scrollTo(map, offset,0);

        const char* line = lines5[0];
        for(unsigned int j = 0; j < 9; j++){
            draw_letter(get_letter(line, j), '\0', textPosX1+j, textPosY1, TILE_USER_INDEX, BG_A, PAL1);
            waitMs(100);
        }
        const char* line_1 = lines5[1];
        for(unsigned int j = 0; j < 4; j++){
            draw_letter(get_letter(line_1, j), '\0', textPosX1+j, textPosY1+3, TILE_USER_INDEX, BG_A, PAL1);
            waitMs(100);
        }

        stage++;
    }else if(stage == 6){
        VDP_loadTileSet(&font_sheet, TILE_USER_INDEX, DMA);

        u8 textPosX1 = 10;
        u8 textPosY1 = 18;
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



        VDP_loadTileSet(&intro_6_tiles, index, DMA);
        PAL_setPalette(PAL2, intropal.data, DMA);
        u32 offset = 0;
        Map *map;
        map = MAP_create(&intro_6, BG_B, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, index));
        MAP_scrollTo(map, offset,0);

        const char* line = lines6[0];
        for(unsigned int j = 0; j < 22; j++){
            draw_letter(get_letter(line, j), '\0', textPosX1+j, textPosY1, TILE_USER_INDEX, BG_A, PAL1);
            waitMs(100);
        }
        char* line_1 = lines6[1];
        for(unsigned int j = 0; j < 22; j++){
            draw_letter(get_letter(line_1, j), '\0', textPosX1+j, textPosY1+3, TILE_USER_INDEX, BG_A, PAL1);
            waitMs(100);
        }
        char* line_2 = lines6[2];
        for(unsigned int j = 0; j < 13; j++){
            draw_letter(get_letter(line_2, j), '\0', textPosX1+j, textPosY1+6, TILE_USER_INDEX, BG_A, PAL1);
            waitMs(100);
        }


        stage++;
    }else if(stage == 7){
        VDP_loadTileSet(&font_sheet, TILE_USER_INDEX, DMA);

        u16 index = TILE_USER_INDEX + font_sheet.numTile;
        for(int i =0 ; i<duration; i++){
            waitMs  (100);
        }
        intro_clean();
        VDP_setTextPlane(BG_A);
        PAL_setColor(0,RGB24_TO_VDPCOLOR(0x000000));

        VDP_loadTileSet(&intro_7_tiles, index, DMA);
        PAL_setPalette(PAL2, intropal.data, DMA);
        u32 offset = 0;
        Map *map;
        map = MAP_create(&intro_7, BG_B, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, index));
        MAP_scrollTo(map, offset,0);
        stage++;
    }else if(stage == 8){
        VDP_loadTileSet(&font_sheet, TILE_USER_INDEX, DMA);

        u16 index = TILE_USER_INDEX + font_sheet.numTile;
        for(int i =0 ; i<duration; i++){
            waitMs  (100);
        }
        intro_clean();
        VDP_setTextPlane(BG_A);
        PAL_setColor(0,RGB24_TO_VDPCOLOR(0x000000));

        VDP_loadTileSet(&intro_8_tiles, index, DMA);
        PAL_setPalette(PAL2, intropal.data, DMA);
        u32 offset = 0;
        Map *map;
        map = MAP_create(&intro_8, BG_B, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, index));
        MAP_scrollTo(map, offset,0);
        stage++;
    }else if(stage == 9){
        VDP_loadTileSet(&font_sheet, TILE_USER_INDEX, DMA);

        u16 index = TILE_USER_INDEX + font_sheet.numTile;
        for(int i =0 ; i<duration; i++){
            waitMs  (100);
        }
        intro_clean();

        VDP_setTextPlane(BG_A);
        PAL_setColor(0,RGB24_TO_VDPCOLOR(0x000000));

        VDP_loadTileSet(&intro_9_tiles, index, DMA);
        PAL_setPalette(PAL2, intropal.data, DMA);
        u32 offset = 0;
        Map *map;
        map = MAP_create(&intro_9, BG_B, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, index));
        stage++;
    }else if(stage == 10){
        VDP_loadTileSet(&font_sheet, TILE_USER_INDEX, DMA);

        u16 index = TILE_USER_INDEX + font_sheet.numTile;
        for(int i =0 ; i<duration; i++){
            waitMs  (100);
        }
        intro_clean();


        VDP_setTextPlane(BG_A);
        PAL_setColor(0,RGB24_TO_VDPCOLOR(0x000000));

        VDP_loadTileSet(&intro_last_tiles, index, DMA);
        PAL_setPalette(PAL2, intropal.data, DMA);
        u32 offset = 170;
        Map *map;
        map = MAP_create(&intro_last, BG_B, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, index));
        u32 scrollDir = 1;
        int num = 1;
        while(num) {
            MAP_scrollTo(map, 0, offset);
            offset -= scrollDir;
            if(offset <= 0) {
                num = 0;
            }
            SYS_doVBlankProcess();
        }

        for(int i =0 ; i<duration; i++){
            waitMs  (100);
        }
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
