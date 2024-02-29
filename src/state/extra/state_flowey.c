#include "state_flowey.h"

#include <genesis.h>
#include <resources.h>

#include "../../globals.h"
#include "../../graphics/textbox.h"

/*
https://nochocolate.tumblr.com/post/152434968515/the-flowey-collection
https://imgur.com/a/722kQ
*/

Sprite *heart;
Sprite *flowey;

void flowey_init(state_parameters_t args) {
    SPR_init();
    box_draw(15, 14, 10, 9, PAL1);

    char buf[20];
    intToStr(flowey_battle.maxNumTile, buf, 1);

    VDP_drawText(buf, 0, 0);

    heart = SPR_addSprite(&heart_sprite, PIXEL_WIDTH / 2 - heart_sprite.w / 2,
                          19 * 8, TILE_ATTR(PAL1, TRUE, FALSE, FALSE));

    flowey =
        SPR_addSprite(&flowey_battle, PIXEL_WIDTH / 2 - flowey_battle.w / 2,
                      8 * 8, TILE_ATTR(PAL1, TRUE, FALSE, FALSE));
}
void flowey_input(u16 changed, u16 state) {}
void flowey_update() {}
void flowey_clean() { VDP_clearTextArea(0, 0, 40, 28); }
void flowey_redraw(state_return_t ret) {}
state_return_t flowey_shutdown() {
    state_return_t ret;
    return ret;
}