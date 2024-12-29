#include "state_battle.h"

#include <genesis.h>
#include <resources.h>

Sprite *opt_heart;
Sprite *fight;
Sprite *act;
Sprite *item;
Sprite *mercy;

u8 select;

// heart = SPR_addSprite(&heart_sprite, heart_x, heart_y,
//                        TILE_ATTR(PAL2, TRUE, FALSE, FALSE));

// enemy_heart = SPR_addSprite(&heart_sprite, 80, 80,
//                           TILE_ATTR(PAL1, TRUE, FALSE, FALSE));

void battle_init(state_parameters_t args) {
    SPR_init();

    VDP_showCPULoad(1,1);

    char buf2[32];

    intToStr(MEM_getFree(), buf2, 1);

    VDP_drawText(buf2, 1, 1);

    select = 0;
    VDP_drawText("Start", 10, 13);
    VDP_drawText("Quit", 10, 15);

    opt_heart = SPR_addSprite(&heart_sprite, 24, 198,
                          TILE_ATTR(PAL1, TRUE, FALSE, FALSE));

    fight = SPR_addSprite(&battle_select, 20, 190,
                          TILE_ATTR(PAL1, TRUE, FALSE, FALSE));

    act = SPR_addSprite(&battle_select, 96, 190,
                        TILE_ATTR(PAL1, TRUE, FALSE, FALSE));

    item = SPR_addSprite(&battle_select, 168, 190,
                         TILE_ATTR(PAL1, TRUE, FALSE, FALSE));

    mercy = SPR_addSprite(&battle_select, 244, 190,
                          TILE_ATTR(PAL1, TRUE, FALSE, FALSE));

    SPR_setAnim(act, 1);
    SPR_setAnim(item, 2);
    SPR_setAnim(mercy, 3);

    SPR_setFrame(fight, 1);
}

void battle_input(u16 changed, u16 state) {
    if ((changed & BUTTON_LEFT) && (state & BUTTON_LEFT) && select != 0) {
        select--;

    } else if ((changed & BUTTON_RIGHT) && (state & BUTTON_RIGHT) &&
               select != 3) {
        select++;
    }
    /*
        This is an extremely lazy way of doing this, I will revise this in the
       future. This is just a proof of concept.
    */
    switch (select) {
        case 0:
            SPR_setPosition(opt_heart, 24, 198);
            SPR_setFrame(fight, 1);
            SPR_setFrame(act, 0);
            SPR_setFrame(item, 0);
            SPR_setFrame(mercy, 0);

            break;
        case 1:
            SPR_setPosition(opt_heart, 100, 198);
            SPR_setFrame(fight, 0);
            SPR_setFrame(act, 1);
            SPR_setFrame(item, 0);
            SPR_setFrame(mercy, 0);
            break;
        case 2:
            SPR_setPosition(opt_heart, 172, 198);
            SPR_setFrame(fight, 0);
            SPR_setFrame(act, 0);
            SPR_setFrame(item, 1);
            SPR_setFrame(mercy, 0);
            break;
        case 3:
            SPR_setPosition(opt_heart, 248, 198);
            SPR_setFrame(fight, 0);
            SPR_setFrame(act, 0);
            SPR_setFrame(item, 0);
            SPR_setFrame(mercy, 1);
            break;
    }
}

void battle_update() {}

void battle_clean() {}

void battle_redraw(state_return_t ret) {}

state_return_t battle_shutdown() {}
