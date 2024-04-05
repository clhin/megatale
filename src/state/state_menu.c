#include "state_menu.h"

#include <genesis.h>
#include <resources.h>

#include "utils/save.h"
#include "savedata.h"
#include "state_world.h"

#include "audio/audioEffects.h"

#include "graphics/level.h"

#include "graphics/text.h"
#include "graphics/textbox.h"

#define MENU_START 0
#define MENU_QUIT 1

Sprite *heart;
Map * menu_background;
u8 heart_pos = MENU_START;
int x = 6;
int y = 8;

void menu_init(state_parameters_t args) {
     SPR_init();
     VDP_loadTileSet(&font_sheet, TILE_USER_INDEX, DMA);
    // This checks the case where there is no save data (0x42 is the flag that says whether or not
    // there is data that has been saved)
    if (SRAM_readByte(0) == 0x42) {
    
        u16 ind = TILE_USER_INDEX + font_sheet.numTile;
        u16 tmp = ind;

        menu_background = loadlevel(0, 1, tmp);
        MAP_scrollTo(menu_background, 0, 125);

        //char buf2[32];

        //intToStr(MEM_getFree(), buf2, 1);

        //VDP_drawText(buf2, 1, 1);

        PAL_setPalette(PAL1, heart_sprite.palette->data, DMA);
        PAL_setPalette(PAL2, intropal.data, DMA);

        heart = SPR_addSprite(&heart_sprite, 9 * 8, 13 * 8,
                          TILE_ATTR(PAL1, TRUE, FALSE, FALSE));
    
        VDP_drawText("Start", 11, 10);
        VDP_drawText("Quit", 25, 10);
        return;
    }


    char buf2[32];

    intToStr(MEM_getFree(), buf2, 1);

    VDP_drawText(buf2, 1, 1);

    PAL_setPalette(PAL1, heart_sprite.palette->data, DMA);
    PAL_setPalette(PAL2, intropal.data, DMA);

    char letters[26][33];

    strcpy(letters[0], "       Name the fallen human.");
    strcpy(letters[1], " ");
    strcpy(letters[2], "                Name ");
    strcpy(letters[3], "     A   B   C   D   E   F   G");
    strcpy(letters[4], "     H   I   J   K   L   M   N");
    strcpy(letters[5], "     O   P   Q   R   S   T   U");
    strcpy(letters[6], "     V   W   X   Y   Z    ");
    strcpy(letters[7], "     a   b   c   d   e   f   g");
    strcpy(letters[8], "     h   i   j   k   l   m   n");
    strcpy(letters[9], "     o   p   q   r   s   t   u");
    strcpy(letters[10], "     v   w   x   y   z    ");
    strcpy(letters[11], "    Quit     Backspace     Done");


    draw_lines(letters, 13, 2, 1, TILE_USER_INDEX, BG_A, PAL1);
    
    heart = SPR_addSprite(&heart_sprite, 6 * 8, 8 * 8,
                          TILE_ATTR(PAL1, TRUE, FALSE, FALSE));

}

void menu_input(u16 changed, u16 state) {
    if (SRAM_readByte(0) != 0x42) {
        if ((changed & BUTTON_DOWN) && (state & BUTTON_DOWN) && (heart_pos == MENU_START)) {
        SPR_setPosition(heart, 5 * 8,  (heart_pos + 1) * 8);
        heart_pos = MENU_QUIT;
        } else if ((changed & BUTTON_UP) && (state & BUTTON_UP) &&
               heart_pos == MENU_QUIT) {
            SPR_setPosition(heart, 9 * 8, 13 * 8);
            heart_pos = MENU_START;
        }

        if (changed & BUTTON_A && (state & BUTTON_A)) {
            // Play Select Sound When Pressing A
            selectSound();

            state_parameters_t args;
	        SYS_disableInts();
	        savedata_t *p = malloc(sizeof(savedata_t));
    	    readsave(p);
	        args.parameter_data = p;
	        SYS_enableInts();
            state_info_t state_info;
            state_info.clean = world_clean;
            state_info.init = world_init;
            state_info.redraw = world_redraw;
            state_info.input = world_input;
            state_info.update = world_update;
            state_info.shutdown = world_shutdown;

            state_push(state_info, args);

            return;
        }
    }

    // Case where there is no saved data and we need to type the name
    // int x = 5;
    // int y = 8;
    if ((changed & BUTTON_DOWN) && (state & BUTTON_DOWN)) {
        y += 2;
        SPR_setPosition(heart, x * 8, y * 8);
    } else if ((changed & BUTTON_UP) && (state & BUTTON_UP)) {
        y -= 2;
        SPR_setPosition(heart, x * 8, y * 8);
    } else if ((changed & BUTTON_RIGHT) && (state & BUTTON_RIGHT)) {
        x += 4;
        SPR_setPosition(heart, x * 8, y * 8);
    } else if ((changed & BUTTON_LEFT) && (state & BUTTON_LEFT)) {
        x -= 4;
        SPR_setPosition(heart, x * 8, y * 8);
    }

    if (changed & BUTTON_A && (state & BUTTON_A)) {
        // Play Select Sound When Pressing A
        selectSound();

        state_parameters_t args;
	SYS_disableInts();
	savedata_t *p = malloc(sizeof(savedata_t));
    	readsave(p);
	args.parameter_data = p;
	SYS_enableInts();
        state_info_t state_info;
        state_info.clean = world_clean;
        state_info.init = world_init;
        state_info.redraw = world_redraw;
        state_info.input = world_input;
        state_info.update = world_update;
        state_info.shutdown = world_shutdown;

        state_push(state_info, args);
    }
}

void menu_update() {}

void menu_clean() {
    VDP_clearSprites();

    VDP_clearTextArea(0, 0, 40, 28);
}

void menu_redraw(state_return_t ret) {
    state_parameters_t p;
    menu_init(p);
}

state_return_t menu_shutdown() {
    menu_clean();
    state_return_t ret;
    return ret;
}
