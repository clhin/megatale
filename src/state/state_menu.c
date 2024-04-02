#include "state_menu.h"

#include <genesis.h>
#include <resources.h>

#include "utils/save.h"
#include "savedata.h"
#include "state_world.h"

#include "audio/audioEffects.h"

#include "graphics/level.h"

#define MENU_START 0
#define MENU_QUIT 1

Sprite *heart;
Map * menu_background;
u8 heart_pos = MENU_START;
//u16 ind = TILE_USER_INDEX;

void menu_init(state_parameters_t args) {
    //u16 tmp = TILE_USER_INDEX + room_main_tiles.numTile;
    SPR_init();
    
    u16 ind = TILE_USER_INDEX + font_sheet.numTile;
    u16 tmp = ind;

    menu_background = loadlevel(0, 1, tmp);
    MAP_scrollTo(menu_background, 0, 125);

    char buf2[32];

    intToStr(MEM_getFree(), buf2, 1);

    VDP_drawText(buf2, 1, 1);

    PAL_setPalette(PAL1, heart_sprite.palette->data, DMA);
    PAL_setPalette(PAL2, intropal.data, DMA);

    heart = SPR_addSprite(&heart_sprite, 9 * 8, 13 * 8,
                          TILE_ATTR(PAL1, TRUE, FALSE, FALSE));

    VDP_drawText("Start", 10, 13);
    VDP_drawText("Quit", 10, 15);
}

void menu_input(u16 changed, u16 state) {
    if ((changed & BUTTON_DOWN) && (state & BUTTON_DOWN) &&
        (heart_pos == MENU_START)) {
        SPR_setPosition(heart, 9 * 8, (heart_pos + 15) * 8);
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
