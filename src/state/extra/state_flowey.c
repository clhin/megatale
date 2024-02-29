#include "state_flowey.h"

#include <genesis.h>
#include <resources.h>

#include "../../battle/battle_dialogue.h"
#include "../../globals.h"
#include "../../graphics/textbox.h"
/*
https://nochocolate.tumblr.com/post/152434968515/the-flowey-collection
https://imgur.com/a/722kQ
*/

Sprite *heart;
Sprite *flowey;

u8 dialogue_x;
u8 dialogue_y;
u8 tick;
u16 c;

void flowey_init(state_parameters_t args) {
    dialogue_x = 0;
    dialogue_y = 0;
    tick = 0;
    c = 0;

    SPR_init();
    box_draw(15, 14, 10, 9, PAL1);

    heart = SPR_addSprite(&heart_sprite, PIXEL_WIDTH / 2 - heart_sprite.w / 2,
                          19 * 8, TILE_ATTR(PAL1, TRUE, FALSE, FALSE));

    flowey =
        SPR_addSprite(&flowey_battle, PIXEL_WIDTH / 2 - flowey_battle.w / 2,
                      8 * 8, TILE_ATTR(PAL1, TRUE, FALSE, FALSE));
}
void flowey_input(u16 changed, u16 state) {}
void flowey_update() {
    tick++;

    if (tick >= 5) {
        tick = 0;

        if (flowey_battle_dialogue[c] == '\n') {
            dialogue_x = 0;
            dialogue_y++;
        } else {
            char buf[2];
            buf[0] = flowey_battle_dialogue[c];
            buf[1] = '\0';
            VDP_drawText(buf, dialogue_x, dialogue_y);
            dialogue_x++;
        }
        c++;
    }
}
void flowey_clean() { VDP_clearTextArea(0, 0, 40, 28); }
void flowey_redraw(state_return_t ret) {}
state_return_t flowey_shutdown() {
    state_return_t ret;
    return ret;
}