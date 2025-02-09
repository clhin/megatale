#include <genesis.h>
#include <resources.h>

#include "globals.h"

#ifdef TEST_MODE
#include "state/testing/state_test.h"
#else
#include "state/state_intro.h"
#endif
#include "state/state_manager.h"

void event_handler(u16 joy, u16 changed, u16 state) {
    if (state_top()) {
        state_top()->input(changed, state);
    }
}

int main() {
    JOY_init();
    JOY_setEventHandler(&event_handler);

    VDP_loadFont(&font, DMA);
    PAL_setPalette(PAL1, heart_sprite.palette->data, DMA);
    VDP_setTextPalette(PAL1);
    state_info_t state_info;

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
