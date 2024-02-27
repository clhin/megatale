#include "state_flowey.h"

#include <genesis.h>

#include "../../graphics/textbox.h"
void flowey_init(state_parameters_t args) { SPR_init(); }
void flowey_input(u16 changed, u16 state) {}
void flowey_update() {}
void flowey_clean() { VDP_clearTextArea(0, 0, 40, 28); }
void flowey_redraw(state_return_t ret) {}
state_return_t flowey_shutdown() {
    state_return_t ret;
    return ret;
}