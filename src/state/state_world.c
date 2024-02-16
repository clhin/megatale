#include "state_world.h"

#include <genesis.h>
#include <resources.h>
#include <string.h>

#include "../collisions.h"
#include "../graphics/text.h"
#include "state_battle.h"

Sprite *heart;

Sprite *enemy_heart;

box_t heart_bb;
box_t enemy_bb;

u16 heart_x;
u16 heart_y;
u8 velocity;

u16 index = 0;

char buf_test[20];

u8 rank_index = 0;
char rank[74] = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',  'k', 'l', 'm', 'n', 'o',
    'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y',  'z', 'A', 'B', 'C', 'D',
    'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',  'O', 'P', 'Q', 'R', 'S',
    'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2',  '3', '4', '5', '6', '7',
    '8', '9', '.', ',', '(', ')', ':', '!', '?', '\'', '"', '-', '[', ']'};

void world_init(state_parameters_t args) {
    SPR_init();  // Needs to be called after clear?

    u8 res = VDP_loadTileSet(&font_sheet, TILE_USER_INDEX, DMA);

    VDP_setTileMapXY(BG_A, TILE_USER_INDEX + index, 8, 8);

    intToStr(index, buf_test, 1);
    VDP_drawText(buf_test, 8, 9);

    u8 *c = get_char_info(rank[rank_index]);

    VDP_setTileMapXY(
        BG_B, TILE_ATTR_FULL(PAL0, 0, 0, 0, TILE_USER_INDEX + GET_TOP(c)), 20,
        9);

    VDP_setTileMapXY(
        BG_B, TILE_ATTR_FULL(PAL0, 0, 0, 0, TILE_USER_INDEX + GET_MIDDLE(c)),
        20, 10);

    VDP_setTileMapXY(
        BG_B, TILE_ATTR_FULL(PAL0, 0, 0, 0, TILE_USER_INDEX + GET_BOTTOM(c)),
        20, 11);

    /*
Do not uncomment this

VDP_setTileMapXY(VDPPlane plane, u16 tile, u16 x, u16 y);

TILE_ATTR_FULL(PAL0, 0, vflip, hflip,
                       TILE_USER_INDEX + (FONT_SHEET_WIDTH * tile_y + tile_x)
text_info.lines_used = 3;
text_info.asterisks[0] = 1;
text_info.asterisks[1] = 1;
text_info.asterisks[2] = 1;
sprintf(text_info.lines[0], "qpj");
sprintf(text_info.lines[1], "abc def ghi ABC");
sprintf(text_info.lines[2], "z[???]()-!");

textbox_show(TEXT_TORIEL_MODE);
*/
    char buf2[32];

    intToStr(MEM_getFree(), buf2, 1);

    heart_x = 20;
    heart_y = 20;
    velocity = 4;

    heart_bb.x = heart_x;
    heart_bb.y = heart_y;
    heart_bb.w = 8;
    heart_bb.h = 8;

    enemy_bb.x = 80;
    enemy_bb.y = 80;
    enemy_bb.w = 8;
    enemy_bb.h = 8;

    VDP_drawText(buf2, 1, 1);

    heart = SPR_addSprite(&heart_sprite, heart_x, heart_y,
                          TILE_ATTR(PAL2, TRUE, FALSE, FALSE));

    enemy_heart = SPR_addSprite(&heart_sprite, 80, 80,
                                TILE_ATTR(PAL1, TRUE, FALSE, FALSE));
}
void world_input(u16 changed, u16 state) {
    if (state & BUTTON_RIGHT) {
        heart_x += velocity;
    }
    if (state & BUTTON_LEFT) {
        heart_x -= velocity;
    }
    if (state & BUTTON_UP) {
        // I know that if two directions are on it goes *sqrt(2) as fast, but we
        // are dealing with integers and not floating point. Does Sega Genesis
        // support floating point calculation? (Look into this later, simple
        // fix, you just multiple both by 0.707)
        heart_y -= velocity;
    }
    if (state & BUTTON_DOWN) {
        heart_y += velocity;
    }

    if (state & BUTTON_A) {
        state_pop();
    }

    if (state & BUTTON_B) {
        index = (index + 1) % font_sheet.numTile;
        VDP_setTileMapXY(BG_A, TILE_USER_INDEX + index, 8, 8);
        intToStr(index, buf_test, 1);
        VDP_drawText(buf_test, 8, 9);

        rank_index = (rank_index + 1) % 74;
        u8 *c = get_char_info(rank[rank_index]);

        VDP_setTileMapXY(
            BG_B,
            TILE_ATTR_FULL(PAL0, 0, GET_TOP_VFLIP(c), GET_TOP_HFLIP(c),
                           TILE_USER_INDEX + GET_TOP_G_TAIL(c)),
            20, 9);

        VDP_setTileMapXY(BG_B,
                         TILE_ATTR_FULL(PAL0, 0, 0, GET_MIDDLE_HFLIP(c),
                                        TILE_USER_INDEX + GET_MIDDLE(c)),
                         20, 10);

        VDP_setTileMapXY(BG_B,
                         TILE_ATTR_FULL(PAL0, 0, 0, GET_BOTTOM_HFLIP(c),
                                        TILE_USER_INDEX + GET_BOTTOM(c)),
                         20, 11);
    }
}
void world_update() {
    heart_bb.x = heart_x;
    heart_bb.y = heart_y;
    SPR_setPosition(heart, heart_x, heart_y);

    if (collides(heart_bb, enemy_bb)) {
        /*
            Todo: Push battle transistion
        */

        state_info_t state_info;
        state_info.clean = battle_clean;
        state_info.init = battle_init;
        state_info.redraw = battle_redraw;
        state_info.input = battle_input;
        state_info.update = battle_update;
        state_info.shutdown = battle_shutdown;

        state_parameters_t args;
        state_push(state_info, args);

        // VDP_drawText("Battle State transistion", 1, 7);
    }
}
void world_clean() {
    VDP_clearSprites();

    VDP_clearTextArea(0, 0, 40, 28);
}
void world_redraw(state_return_t ret) {}
state_return_t world_shutdown() {
    world_clean();
    state_return_t ret;
    return ret;
}
