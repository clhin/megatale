#include "state_intro.h"

#include <genesis.h>

#include "state_menu.h"

void intro_init(state_parameters_t args) {
    VDP_drawText("Placeholder for intro", 1, 1);
    VDP_drawText("Press A-joystick (H) to continue", 1, 2);
}
void intro_input(u16 changed, u16 state) {
    if (changed & BUTTON_A && (state & BUTTON_A)) {
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
void intro_update() {}
void intro_clean() { VDP_clearTextArea(0, 0, 40, 28); }
void intro_redraw(state_return_t ret) {}
state_return_t intro_shutdown() {
    intro_clean();
    state_return_t ret;
    return ret;
}