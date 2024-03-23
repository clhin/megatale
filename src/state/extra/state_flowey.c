#include "state_flowey.h"

#include <genesis.h>
#include <globals.h>
#include <resources.h>

#include "../../audio/audioEffects.h"
#include "../../battle/battle_data.h"
#include "../../battle/battle_dialogue.h"
#include "../../graphics/textbox.h"

/*

5 - "Down here, love is shared through.." incidentally 5 particles.

*/

// Remove this when PRing
#define DEBUG

#define MAX_FLOWEY_PELLETS 32

#define FLOWEY_CENTER_X (PIXEL_WIDTH / 2)
#define FLOWEY_CENTER_Y (8 * 7 + 25)

typedef enum {
    S_FLOWEY_NOTHING,
    S_FLOWEY_GEN_PELLETS,
    S_FLOWEY_THROW_PELLETS
} flowey_state_t;

// https://github.com/Stephane-D/SGDK/blob/master/sample/game/sonic/src/entities.c
/*
https://nochocolate.tumblr.com/post/152434968515/the-flowey-collection
https://imgur.com/a/722kQ
*/

// Local functions
void pellet_animator(Sprite *master);
void helper_dialogue_tick();
void helper_scene_state();

Sprite *heart;
Sprite *flowey;

u8 tick;

u16 vram_ind;

struct {
    u8 x;
    u8 y;
    u16 c;

    /*
        next: the dialogue is over, waiting for user's keypress
        press: the user keypressed
    */
    u8 next;
    u8 press;
    u8 i;

    u8 face_frame;

} dialogue;

struct {
    u8 pellets_used;
    projectile_data_t *pellets;
    u16 **pellet_vram;
    flowey_state_t state;

} battle;

void flowey_init(state_parameters_t args) {
    /*
        Should already be loaded in by state_world but we're using it until pull
       request
    */
    tick = 0;

    vram_ind = TILE_USER_INDEX;

    dialogue.next = FALSE;
    dialogue.press = FALSE;

    dialogue.x = 0;
    dialogue.y = 0;

    dialogue.c = DIALOGUE_FLOWEY3;

    dialogue.face_frame = 0;

    dialogue.i = 0;

    battle.state = S_FLOWEY_NOTHING;

    // Begin loading

    VDP_loadTileSet(&font_sheet, TILE_USER_INDEX, DMA);
    vram_ind += font_sheet.numTile;

    SPR_init();

    battle.pellets = MEM_alloc(sizeof(projectile_data_t) * MAX_FLOWEY_PELLETS);

    battle.pellets[0].spr = SPR_addSprite(&flowey_bullet, 0, 0,
                                          TILE_ATTR(PAL1, TRUE, FALSE, FALSE));

    SPR_setVisibility(battle.pellets[0].spr, HIDDEN);
    SPR_setAutoTileUpload(battle.pellets[0].spr, FALSE);
    SPR_setFrameChangeCallback(battle.pellets[0].spr, pellet_animator);

    u16 num_tiles;

    battle.pellet_vram = SPR_loadAllFrames(battle.pellets[0].spr->definition,
                                           vram_ind, &num_tiles);
    vram_ind += num_tiles;

    box_draw(15, 15, 10, 9, PAL1);

    heart = SPR_addSprite(&heart_sprite, PIXEL_WIDTH / 2 - 4, 19 * 8,
                          TILE_ATTR(PAL1, TRUE, FALSE, FALSE));
    flowey =
        SPR_addSprite(&flowey_battle, PIXEL_WIDTH / 2 - flowey_battle.w / 2,
                      8 * 7, TILE_ATTR(PAL1, TRUE, FALSE, FALSE));
}
void flowey_input(u16 changed, u16 state) {
    if (dialogue.next && (state & BUTTON_A)) {
        dialogue.press = TRUE;
    }
}
void flowey_update() {
    tick++;

    if (battle.state == S_FLOWEY_GEN_PELLETS && tick % 5 == 0) {
        for (u8 i = 0; i < 5; ++i) {
            projectile_lerp(&battle.pellets[i], 11);
            s16 x = battle.pellets[i].x;
            s16 y = battle.pellets[i].y;
            SPR_setPosition(battle.pellets[i].spr, x, y);
        }
    } else if (battle.state == S_FLOWEY_THROW_PELLETS && tick % 2 == 0) {
        // battle.pellets[0].x += battle.pellets[0].v_x;
        // battle.pellets[0].y += battle.pellets[0].v_y;
        // SPR_setPosition(battle.pellets[0].spr, battle.pellets[0].x ,
        // battle.pellets[0].y);
    }

    if (dialogue.press) {
        dialogue.next = FALSE;
        dialogue.press = FALSE;

        VDP_clearTextArea(0, 0, 22, 4);
        dialogue.x = 0;
        dialogue.y = 0;

        // Move towards next dialogue, call helper function if there's a
        // transistion.
        dialogue.i++;
        helper_scene_state();

#ifdef DEBUG
        char buf[3];
        intToStr(dialogue.i, buf, 1);
        VDP_drawText(buf, 30, 0);
#endif
    }

    if (tick % 5 == 0 && !dialogue.next) {
        helper_dialogue_tick();

        /*
            If dialogue is finished we close flowey's mouth, otherwise continue
           by just going from 0~1 talking.
        */
        if (dialogue.next) {
            SPR_setFrame(flowey, 0);
        } else if (tick % 10 == 0) {
            dialogue.face_frame = !dialogue.face_frame;
            SPR_setFrame(flowey, dialogue.face_frame);
        }
    }
}
void flowey_clean() { VDP_clearTextArea(0, 0, 40, 28); }
void flowey_redraw(state_return_t ret) {}
state_return_t flowey_shutdown() {
    state_return_t ret;
    return ret;
}

void pellet_animator(Sprite *master) {
    // If no pellets we ignore this.
    if (SPR_getVisibility(master) == HIDDEN) return;

    u16 tileIndex = battle.pellet_vram[master->animInd][master->frameInd];

    for (u8 i = 0; i < battle.pellets_used; ++i) {
        Sprite *spr = battle.pellets[i].spr;

        SPR_setVRAMTileIndex(spr, tileIndex);
    }
}

void helper_dialogue_tick() {
    if (dialogue.next) return;

    if (flowey_battle_dialogue[dialogue.c] == '\n') {
        dialogue.x = 0;
        dialogue.y++;
    } else if (flowey_battle_dialogue[dialogue.c] == '\0') {
        dialogue.next = TRUE;
    } else {
        // Very basic way of having one character load at a time
        char buf[2];
        buf[0] = flowey_battle_dialogue[dialogue.c];
        buf[1] = '\0';
        VDP_drawText(buf, dialogue.x, dialogue.y);
        dialogue.x++;
    }
    dialogue.c++;
}

void helper_scene_state() {
    u16 x = FLOWEY_CENTER_X - 4;
    u16 y = FLOWEY_CENTER_Y - 4;

    u16 end_x[5] = {FLOWEY_CENTER_X - 4 - 50, FLOWEY_CENTER_X - 4 - 25,
                    FLOWEY_CENTER_X - 4, FLOWEY_CENTER_X - 4 + 25,
                    FLOWEY_CENTER_X - 4 + 50};

    u16 end_y[5] = {FLOWEY_CENTER_Y - 21, FLOWEY_CENTER_Y - 41,
                    FLOWEY_CENTER_Y - 51, FLOWEY_CENTER_Y - 41,
                    FLOWEY_CENTER_Y - 21};

    /*
    Based on how far we are in the dialogue, we adjust accordingly.

    5: is "Down here, love is shared [...]" - 5 bullets come out from flowey
   and surrond him above in a circle.

    If we look at the unit circle, we position them

*/
    switch (dialogue.i) {
        case 1:
            battle.state = S_FLOWEY_GEN_PELLETS;

            battle.pellets_used = 5;

            for (u8 i = 1; i < 5; ++i) {
                battle.pellets[i].spr =
                    SPR_addSpriteEx(battle.pellets[0].spr->definition, 0, 0,
                                    TILE_ATTR(PAL1, TRUE, FALSE, FALSE), 0);
            }
            for (u8 i = 0; i < 5; ++i) {
                SPR_setPosition(battle.pellets[i].spr, x, y);
                SPR_setVisibility(battle.pellets[i].spr, VISIBLE);

                battle.pellets[i].x = x;
                battle.pellets[i].y = y;
                battle.pellets[i].start_x = x;
                battle.pellets[i].start_y = y;

                battle.pellets[i].end_x = end_x[i];
                battle.pellets[i].end_y = end_y[i];
            }

            break;

        case 3:
            battle.state = S_FLOWEY_THROW_PELLETS;

            s16 end_x = heart->x + 4;
            s16 end_y = heart->y + 4;

            s16 d_x = end_x - battle.pellets[0].x;
            s16 d_y = end_y = battle.pellets[0].y;

            battle.pellets[0].v_x = d_x / 10;
            battle.pellets[0].v_y = d_y / 10;
            // We set the telos of the pellets towards random parts of the
            // bottom of the screen
            break;
    }
}
