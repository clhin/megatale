#include <genesis.h>
#include <resources.h>

#include "state/state_manager.h"
#include "state/state_menu.h"
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

    state_info_t state_info;
    state_info.clean = menu_clean;
    state_info.init = menu_init;
    state_info.redraw = menu_redraw;
    state_info.input = menu_input;
    state_info.update = menu_update;
    state_info.shutdown = menu_shutdown;

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