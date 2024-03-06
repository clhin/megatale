#include <genesis.h>
#include <resources.h>

// Only define this if you want the game to go directly into testing
#include "globals.h"

#ifdef TEST_MODE
#include "state/testing/state_test.h"
#else
#include "state/state_intro.h"
#endif
#include "audio/audioEffects.h"
#include "state/state_manager.h"

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
    
    // Audio effects testing
    saveSound();


#ifndef TEST_MODE
    state_info.clean = intro_clean;
    state_info.init = intro_init;
    state_info.redraw = intro_redraw;
    state_info.input = intro_input;
    state_info.update = intro_update;
    state_info.shutdown = intro_shutdown;
#else
    state_info.clean = test_clean;
    state_info.init = test_init;
    state_info.redraw = test_redraw;
    state_info.input = test_input;
    state_info.update = test_update;
    state_info.shutdown = test_shutdown;
#endif

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
