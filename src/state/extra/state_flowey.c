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

#define HEART_CENTER_X (PIXEL_WIDTH / 2)
#define HEART_CENTER_Y (19 * 8)

typedef enum {
    S_FLOWEY_NOTHING,
    S_FLOWEY_GEN_PELLETS,
    S_FLOWEY_THROW_PELLETS,
    S_FLOWEY_HIT,
    S_FLOWEY_DIE,
    S_FLOWEY_DODGE1,
    S_FLOWEY_DODGE2,
    S_FLOWEY_DODGE3
} flowey_state_t;

// https://github.com/Stephane-D/SGDK/blob/master/sample/game/sonic/src/entities.c
/*
https://nochocolate.tumblr.com/post/152434968515/the-flowey-collection
https://imgur.com/a/722kQ
*/

// Local functions
void pellet_animator(Sprite *master);
void helper_dialogue_tick();
void helper_heart_tick();
void helper_battle_tick();
void helper_scene_state();

// Local variables
const u8 faces[19] = {0, 0, 0, 0, 0, 1, 2, 0, 0, 6, 6, 6, 5, 3, 3, 4, 0, 5, 5};

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
    u8 blocking;
} dialogue;

struct {
    u8 pellets_used;
    projectile_data_t *pellets;
    u16 **pellet_vram;
    flowey_state_t state;

    s16 heart_x;
    s16 heart_y;
    s16 heart_vx;
    s16 heart_vy;
    u8 heart_blocking;
    u8 heart_collide;
    u8 dodge_count;

    // Battle box [15, 15, 10, 9]
    u8 box_x;
    u8 box_y;
    u8 box_w;
    u8 box_h;
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

    dialogue.c = D_FLOWEY_TALK0;

    dialogue.face_frame = 0;

    dialogue.i = 0;
    dialogue.blocking = 0;

    battle.state = S_FLOWEY_NOTHING;

    battle.dodge_count = 0;

    // Proportions of box
    battle.box_x = 15;
    battle.box_y = 15;
    battle.box_w = 10;
    battle.box_h = 9;
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

    box_draw(battle.box_x, battle.box_y, battle.box_w, battle.box_h, PAL1);

    heart = SPR_addSprite(&heart_sprite, HEART_CENTER_X - 4, HEART_CENTER_Y,
                          TILE_ATTR(PAL1, TRUE, FALSE, FALSE));

    battle.heart_x = HEART_CENTER_X - 4;
    battle.heart_y = HEART_CENTER_Y;
    battle.heart_vx = 0;
    battle.heart_vy = 0;
    battle.heart_collide = 0;
    battle.heart_blocking = 0;
    flowey =
        SPR_addSprite(&flowey_battle, PIXEL_WIDTH / 2 - flowey_battle.w / 2,
                      8 * 7, TILE_ATTR(PAL1, TRUE, FALSE, FALSE));
}
void flowey_input(u16 changed, u16 state) {
    if (dialogue.next && (state & BUTTON_A) &&
        battle.state != S_FLOWEY_THROW_PELLETS &&
        battle.state != S_FLOWEY_DIE) {
        dialogue.press = TRUE;
    }

    if (state & BUTTON_RIGHT) {
        battle.heart_vx = 1;
    } else if (state & BUTTON_LEFT) {
        battle.heart_vx = -1;
    } else {
        if (changed & BUTTON_RIGHT || changed & BUTTON_LEFT)
            battle.heart_vx = 0;
    }

    if (state & BUTTON_UP) {
        battle.heart_vy = -1;
    } else if (state & BUTTON_DOWN) {
        battle.heart_vy = 1;
    } else {
        if (changed & BUTTON_UP || changed & BUTTON_DOWN) battle.heart_vy = 0;
    }
}
void flowey_update() {
    tick++;

    helper_heart_tick();
    helper_battle_tick();

    if (dialogue.press) {
        dialogue.next = FALSE;
        dialogue.press = FALSE;

        VDP_clearTextArea(0, 0, 22, 4);
        dialogue.x = 0;
        dialogue.y = 0;

        // Move towards next dialogue, call helper function if there's a
        // transistion.
        helper_scene_state();

#ifdef DEBUG
        char buf[3];
        intToStr(dialogue.i, buf, 1);
        VDP_drawText(buf, 30, 0);
#endif
    }
    // add tick % 5
    if (!dialogue.next && !dialogue.blocking) {
        SPR_setAnim(flowey, faces[dialogue.i]);
        helper_dialogue_tick();

        /*
            If dialogue is finished we close flowey's mouth, otherwise
           continue by just going from 0~1 talking.
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

void helper_heart_tick() {
    if (battle.heart_blocking) return;
    s16 temp_x = battle.heart_x + battle.heart_vx;
    s16 temp_y = battle.heart_y + battle.heart_vy;

    /*
        Box has boundaries of 10x9 at 15,15.

        That means, the left bound is at tile edge of tile 16, right bound is at
       edge of tile 23 (15 + 10 - 2)

       That means, the top bound is at tile edge
       of tile 16, bottom bound is at edge of tile 22 (15 + 9 - 2)
    */
    temp_x = clamp(temp_x, (battle.box_x + 1) * 8,
                   (battle.box_x + battle.box_w - 2) * 8);
    temp_y = clamp(temp_y, (battle.box_x + 1) * 8,
                   (battle.box_x + battle.box_h - 2) * 8);

    battle.heart_x = temp_x;
    battle.heart_y = temp_y;
    SPR_setPosition(heart, battle.heart_x, battle.heart_y);
}

void helper_battle_tick() {
    if (battle.state == S_FLOWEY_GEN_PELLETS && tick % 3 == 0) {
        for (u8 i = 0; i < 5; ++i) {
            projectile_lerp(&battle.pellets[i], 14);
            s16 x = battle.pellets[i].x;
            s16 y = battle.pellets[i].y;
            SPR_setPosition(battle.pellets[i].spr, x, y);
        }
    } else if (battle.state == S_FLOWEY_THROW_PELLETS && tick % 3 == 0) {
        u8 not_clear = 0;
        for (u8 i = 0; i < 5; ++i) {
            if (SPR_getVisibility(battle.pellets[i].spr) != VISIBLE) continue;

            not_clear |= (1 << i);

            battle.pellets[i].x += battle.pellets[i].v_x;
            battle.pellets[i].y += battle.pellets[i].v_y;
            SPR_setPosition(battle.pellets[i].spr, battle.pellets[i].x,
                            battle.pellets[i].y);

            if (circles_collide(battle.pellets[i].x, battle.pellets[i].y, 4,
                                battle.heart_x, battle.heart_y, 4)) {
                // dialogue.c = DIALOGUE_FLOWEY9;
                // dialogue.i = 8;         // i increments to 9

                battle.heart_collide = 1;
                dialogue.press = TRUE;  // Emualate it being pressed.
                return;
            }

            if (battle.pellets[i].y >= PIXEL_HEIGHT)
                SPR_setVisibility(battle.pellets[i].spr, HIDDEN);
        }

        if (!not_clear) {
            //  dialogue.c = DODGE_FLOWEY1;
            //    dialogue.i = 12;
            battle.heart_collide = 0;
            dialogue.press = TRUE;
            battle.dodge_count++;
            return;
        }
    } else if (battle.state == S_FLOWEY_DIE && tick % 3 == 0) {
        if (battle.pellets_used < MAX_FLOWEY_PELLETS) {
            SPR_setVisibility(battle.pellets[battle.pellets_used].spr, VISIBLE);
            battle.pellets_used++;
        } else {
            battle.heart_blocking = FALSE;
            dialogue.blocking = FALSE;
        }
    }
}
void helper_scene_state() {
    // If scene was previously pellets being thrown
    if (dialogue.i == I_FLOWEY_TALK8 && battle.heart_collide) {
        dialogue.i = I_FLOWEY_HIT1;
        dialogue.c = D_FLOWEY_HIT1;
    } else if (dialogue.i == I_FLOWEY_TALK8 && !battle.heart_collide) {
        /*
        1: "Let's try that again"
        2: "Are you braindead?"
        3: Angry
        */
        switch (battle.dodge_count) {
            case 1:
                dialogue.i = I_FLOWEY_DODGE0_0;
                dialogue.c = D_FLOWEY_DODGE0_0;
                break;
            case 2:
                dialogue.i = I_FLOWEY_DODGE1_0;
                dialogue.c = D_FLOWEY_DODGE1_0;
                break;
            case 3:
                dialogue.i = I_FLOWEY_DODGE2_0;
                dialogue.c = D_FLOWEY_DODGE2_0;
                break;
        }
        dialogue.blocking = FALSE;
    } else if (dialogue.i == I_FLOWEY_DODGE0_1 ||
               dialogue.i ==
                   I_FLOWEY_DODGE1_1) {  // Second or third flowey attempt
        dialogue.i = I_FLOWEY_TALK8;
        dialogue.c = 0;  // Placeholder
        dialogue.blocking = TRUE;
        // Give him default face (note that it does that in intro)
        SPR_setAnim(flowey, 0);
    } else if (dialogue.i == I_FLOWEY_DODGE2_1) {
        dialogue.i = I_FLOWEY_DIE;
        dialogue.c = D_FLOWEY_DIE;
    } else {
        dialogue.i++;
    }

    const u16 x = FLOWEY_CENTER_X - 4;
    const u16 y = FLOWEY_CENTER_Y - 4;

    const u16 end_x[5] = {FLOWEY_CENTER_X - 4 - 50, FLOWEY_CENTER_X - 4 - 25,
                          FLOWEY_CENTER_X - 4, FLOWEY_CENTER_X - 4 + 25,
                          FLOWEY_CENTER_X - 4 + 50};

    const u16 end_y[5] = {FLOWEY_CENTER_Y - 21, FLOWEY_CENTER_Y - 41,
                          FLOWEY_CENTER_Y - 51, FLOWEY_CENTER_Y - 41,
                          FLOWEY_CENTER_Y - 21};

    /*
    Based on how far we are in the dialogue, we adjust accordingly.

    5: is "Down here, love is shared [...]" - 5 bullets come out from flowey
    and surrond him above in a circle.

    If we look at the unit circle, we position them

    */
    switch (dialogue.i) {
        /*
        "Down here, love is shared [...]" - 5 bullets come out from flowey
    and surrond him above in a circle.
        */
        case I_FLOWEY_TALK5:
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
            /*
                The pellets then chase after the player and disappear at the
               bottom. Different response if player dodges or collides.
            */
        case I_FLOWEY_TALK8:
            // Flowey attempts to hit you numerous times, past the first one,
            // they spawn at where they moved to instead of moving there, so we
            // need to keep this in mind.
            if (battle.dodge_count > 0) {
                for (u8 i = 0; i < 5; ++i) {
                    SPR_setPosition(battle.pellets[i].spr, end_x[i], end_y[i]);
                    SPR_setVisibility(battle.pellets[i].spr, VISIBLE);

                    battle.pellets[i].x = end_x[i];
                    battle.pellets[i].y = end_y[i];
                }
            }

            battle.state = S_FLOWEY_THROW_PELLETS;

            s16 end_x = battle.heart_x + 4;
            s16 end_y = battle.heart_y + 4;

            for (u8 i = 0; i < 5; ++i) {
                s16 d_x = end_x - battle.pellets[i].x + 4;
                s16 d_y = end_y - battle.pellets[i].y + 4;

                battle.pellets[i].v_x = d_x / 30;
                battle.pellets[i].v_y = d_y / 30;
            }
            break;
        case I_FLOWEY_HIT1:
            battle.state = S_FLOWEY_HIT;

            for (u8 i = 0; i < 5; ++i) {
                battle.pellets_used = 0;
                SPR_setVisibility(battle.pellets[i].spr, HIDDEN);
            }
            break;
            /*
            Die!
            */
        case I_FLOWEY_DIE:
            battle.state = S_FLOWEY_DIE;

            // Why do we block? We need a circle of bullets to be created around
            // the player, after which flowey then says die.
            dialogue.blocking = TRUE;
            battle.heart_blocking = TRUE;

            SPR_setAnim(flowey, 5);

            // Resize the box (I don't know, it does this for some reason?)
            // Heart being put in it is handled by clamp() in update sequence.

            VDP_clearTileMapRect(BG_A, battle.box_x, battle.box_y, battle.box_w,
                                 battle.box_h);

            battle.box_x += 2;
            battle.box_y += 2;
            battle.box_w -= 4;
            battle.box_h -= 3;
            box_draw(battle.box_x, battle.box_y, battle.box_w, battle.box_h,
                     PAL1);

            battle.heart_x = clamp(battle.heart_x, (battle.box_x + 1) * 8,
                                   (battle.box_x + battle.box_w - 2) * 8);
            battle.heart_y = clamp(battle.heart_y, (battle.box_x + 1) * 8,
                                   (battle.box_x + battle.box_h - 2) * 8);

            SPR_setPosition(heart, battle.heart_x, battle.heart_y);

            // We already have 5 bullets loaded, we have 32 in total. We load
            // the other 27.

            // We go ahead and set positions but make them all invisible.

            battle.pellets_used = 0;

            for (u8 i = 0; i < MAX_FLOWEY_PELLETS; ++i) {
                if (i >= 5) {
                    battle.pellets[i].spr =
                        SPR_addSpriteEx(battle.pellets[0].spr->definition, 0, 0,
                                        TILE_ATTR(PAL1, TRUE, FALSE, FALSE), 0);
                }

                SPR_setVisibility(battle.pellets[i].spr, HIDDEN);

                f16 x_adj = fix16Mul(cosFix16(i * 32), FIX16(32.0));
                f16 y_adj = fix16Mul(sinFix16(i * 32), FIX16(32.0));

                battle.pellets[i].x = battle.heart_x + fix16ToInt(x_adj);
                battle.pellets[i].y = battle.heart_y + fix16ToInt(y_adj);

                SPR_setPosition(battle.pellets[i].spr, battle.pellets[i].x,
                                battle.pellets[i].y);
            }

            break;
        case I_FLOWEY_DODGE0_0:
        case I_FLOWEY_DODGE1_0:
            battle.state = S_FLOWEY_DODGE1;
            break;
        case I_FLOWEY_DODGE2_0:
            battle.state = S_FLOWEY_NOTHING;
    }
}
