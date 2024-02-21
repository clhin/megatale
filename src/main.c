#include <genesis.h>
#include <resources.h>

#include "state/state_intro.h"
#include "state/state_manager.h"
const int LEFT_EDGE = 0;
const int RIGHT_EDGE = 320;
const int TOP_EDGE = 0;
const int BOTTOM_EDGE = 224;

void event_handler(u16 joy, u16 changed, u16 state) {
    if (state_top()) {
        state_top()->input(changed, state);
    }
}

int main() {
    JOY_init();
    JOY_setEventHandler(&event_handler);

    VDP_loadFont(font.tileset, DMA);
    PAL_setPalette(PAL1, heart_sprite.palette->data, DMA);
    VDP_setTextPalette(PAL1);
    state_info_t state_info;
    state_info.clean = intro_clean;
    state_info.init = intro_init;
    state_info.redraw = intro_redraw;
    state_info.input = intro_input;
    state_info.update = intro_update;
    state_info.shutdown = intro_shutdown;

    state_parameters_t args;
    state_push(state_info, args);

    while (1) {
        if (state_top()) {
            state_top()->update();
        }
        SPR_update();
        SYS_doVBlankProcess();
    }
    return (0);
}
