#include "state_flowey.h"

#include <genesis.h>
#include <resources.h>

#include "../../graphics/textbox.h"

Sprite *heart;

void flowey_init(state_parameters_t args) {
    SPR_init();
    box_draw(15, 14, 10, 9, PAL1);

    heart = SPR_addSprite(&heart_sprite, 20 * 8 - 4, 19 * 8 - 4,
                          TILE_ATTR(PAL1, TRUE, FALSE, FALSE));
}
void flowey_input(u16 changed, u16 state) {}
void flowey_update() {}
void flowey_clean() { VDP_clearTextArea(0, 0, 40, 28); }
void flowey_redraw(state_return_t ret) {}
state_return_t flowey_shutdown() {
    state_return_t ret;
    return ret;
}