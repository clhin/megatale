#include "state_flowey.h"

#include <genesis.h>
#include <globals.h>
#include <resources.h>

#include "../../audio/audioEffects.h"
#include "../../battle/battle_data.h"
#include "../../battle/battle_dialogue.h"
#include "../../graphics/textbox.h"

/*
https://nochocolate.tumblr.com/post/152434968515/the-flowey-collection
https://imgur.com/a/722kQ
*/

Sprite *heart;
Sprite *flowey;

// Making it dynamic because amount used is concerning.
// For circle, instead of individually checking each bb we could just imagine it
// as two circles and track when j < i
projectile_data_t **bullets;

u8 dialogue_x;
u8 dialogue_y;
u8 tick;
u8 frame_tick;
u16 c;

u8 next_dialogue;
u8 next_trigger;

void flowey_init(state_parameters_t args) {
    /*
        Should already be loaded in by state_world but we're using it until pull
       request
    */

    VDP_loadTileSet(&font_sheet, TILE_USER_INDEX, DMA);

    next_dialogue = FALSE;
    next_trigger = FALSE;

    frame_tick = 0;

    dialogue_x = 0;
    dialogue_y = 0;
    tick = 0;
    c = DIALOGUE_FLOWEY1;

    SPR_init();
    box_draw(15, 15, 10, 9, PAL1);

    bullets = MEM_alloc(sizeof(projectile_data_t) * 32);

    for (u8 i = 0; i < 32; ++i) {
        s16 x = fix16ToInt(fix16Mul(cosFix16(i * 32), FIX16(40)));
        s16 y = fix16ToInt(fix16Mul(sinFix16(i * 32), FIX16(40)));

        bullets[i]->bullet =
            SPR_addSprite(&flowey_bullet, (PIXEL_WIDTH / 2 - 4) + x,
                          (19 * 8) + y, TILE_ATTR(PAL1, TRUE, FALSE, FALSE));
        if (bullets[i] == NULL) SYS_reset();
        bullets[i]->x = (PIXEL_WIDTH / 2 - 4) + x;
        bullets[i]->y = (19 * 8) + y;
        bullets[i]->a_x = 0;
        bullets[i]->a_y = 0;

        bullets[i]->v_x = -x / 2;
        bullets[i]->v_y = -y / 2;
    }

    heart = SPR_addSprite(&heart_sprite, PIXEL_WIDTH / 2 - 4, 19 * 8,
                          TILE_ATTR(PAL1, TRUE, FALSE, FALSE));

    flowey =
        SPR_addSprite(&flowey_battle, PIXEL_WIDTH / 2 - flowey_battle.w / 2,
                      8 * 7, TILE_ATTR(PAL1, TRUE, FALSE, FALSE));
}
void flowey_input(u16 changed, u16 state) {
    if (state & BUTTON_A && next_dialogue) {
        next_trigger = TRUE;
        next_dialogue = FALSE;
    }
}
void flowey_update() {
    if (next_trigger) {
        next_trigger = FALSE;
        dialogue_x = 0;
        dialogue_y = 0;
        VDP_clearTextArea(0, 0, 22, 4);
    }
    if (next_dialogue) return;
    tick++;

    if (tick % 5 == 0) {
        if (flowey_battle_dialogue[c] == '\n') {
            dialogue_x = 0;
            dialogue_y++;
        } else if (flowey_battle_dialogue[c] == '\0') {
            for (u8 i = 0; i < 32; ++i) {
                SPR_setPosition(bullets[i]->bullet, bullets[i]->x + 10,
                                bullets[i]->y);
            }

            next_dialogue = TRUE;
        } else {
            char buf[2];
            buf[0] = flowey_battle_dialogue[c];
            buf[1] = '\0';
            VDP_drawText(buf, dialogue_x, dialogue_y);
            dialogue_x++;
        }

        c++;
    }

    if (tick == 10) {
        tick = 0;
        frame_tick = !frame_tick;
        SPR_setFrame(flowey, frame_tick);
    }
}
void flowey_clean() { VDP_clearTextArea(0, 0, 40, 28); }
void flowey_redraw(state_return_t ret) {}
state_return_t flowey_shutdown() {
    state_return_t ret;
    return ret;
}