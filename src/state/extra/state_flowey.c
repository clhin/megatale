#include "state_flowey.h"

#include <genesis.h>
#include <globals.h>
#include <resources.h>

#include "../../audio/audioEffects.h"
#include "../../battle/battle_data.h"
#include "../../battle/battle_dialogue.h"
#include "../../graphics/textbox.h"

// Uncomment this to see what index the dialogue is on
// #define DEBUG

// How much pellets we need allocated in total. 64 is the full circle in the
// original game, but to account for half the screen size we give 32.
#define MAX_FLOWEY_PELLETS 32

// Original top-left positions of flowey and the heart (not accounting for
// half-size shift).
#define FLOWEY_X (PIXEL_WIDTH / 2)
#define FLOWEY_Y (8 * 7 + 25)
#define HEART_X (PIXEL_WIDTH / 2)
#define HEART_Y (19 * 8)

// How many sprite-changes flowey has of being flung
#define THROWN_FRAMES 9

// Various states of the entire scene for logic keeping, we split up what to do
// across them.
typedef enum {
    S_FLOWEY_NOTHING,
    S_FLOWEY_GEN_PELLETS,
    S_FLOWEY_THROW_PELLETS,
    S_FLOWEY_HIT,
    S_FLOWEY_DIE,
    S_FLOWEY_DODGE1,
    S_FLOWEY_DODGE2,
    S_FLOWEY_DODGE3,
    S_FLOWEY_CONFUSED,
    S_TORIEL_ENTER
} flowey_state_t;

/*

Good resource on double checking what the state should be like:

https://nochocolate.tumblr.com/post/152434968515/the-flowey-collection
https://imgur.com/a/722kQ
*/

// Local functions (defined at bottom)
void pellet_animator(Sprite *master);
void helper_dialogue_tick();
void helper_heart_tick();
void helper_battle_tick();
void helper_scene_state();
void helper_flowey_throw();

// ---------------------------- *
//        LOCAL CONSTANTS       |
// ---------------------------- *

// Flowey faces corresponding to dialogues: generated from
// misc/battle/gen_battle_dialogue.py
const u8 faces[25] = {0, 0, 0, 0, 0, 1, 2, 0, 0, 6, 6, 6, 5,
                      3, 3, 4, 0, 5, 5, 1, 0, 0, 0, 0, 0};

// Flowey face animations and "timer" intervals to use for when he goes "wut"
// and gets thrown.

// correspond to "timer" ticks, when it's equal to that amount it passes it.
const u8 throw_anim_t[THROWN_FRAMES] = {60, 70, 76, 79, 82, 86, 91, 97, 101};

/*
    In order to account for flowey's rotation, we have pre-computed rotaated
   frames in his spritesheet. When he is flung by a fireball he rotates until
   its a full 90 degrees.

*/

// MSB correspond to anim frame (y) and LSB correspond to frame (x)
// -- this is extracted out for setAnim and setFrame
const u16 throw_anim_f[THROWN_FRAMES] = {
    0x40,  // Angry
    0x80,  // Confused look for a few frames
    0x81,  // Cry
    0x90,  // Cry -15deg
    0x91,  // Cry -30deg
    0xA0,  // Cry -45deg
    0xA1,  // Cry -60deg
    0xB0,  // Cry -75deg
    0xB1   // Cry -90deg
};

/*
Precomputed velocities for when circle surrounds player. We split it into 8
sections for every cardinal and ordinal direction, diagonals move a bit
faster due to constraints of size and not using floating point. It looks a bit
janky but less laggy and less convoluted than floating points.

i = 0, 1, 30, 31   -> Move to left
i = 2, 3, 4, 5     -> Move to bottom-left
i = 6, 7, 8, 9     -> Move to bottom
i = 10, 11, 12, 13 -> Move to bottom-right
i = 14, 15, 16, 17 -> Move to right
i = 18, 19, 20, 21 -> Move to top-right
i = 22, 23, 24, 25 -> Move to top
i = 26, 27, 28, 29 -> Move to top-left
*/

const s8 circle_vx[MAX_FLOWEY_PELLETS] = {
    -1, -1,          // {0}
    -1, -1, -1, -1,  // {1}
    0,  0,  0,  0,   // {2}
    1,  1,  1,  1,   // {3}
    1,  1,  1,  1,   // {4}
    1,  1,  1,  1,   // {5}
    0,  0,  0,  0,   // {6}
    -1, -1, -1, -1,  // {7}
    -1, -1,          // {0}
};

const s8 circle_vy[MAX_FLOWEY_PELLETS] = {
    0,  0,           // {0}
    -1, -1, -1, -1,  // {1}
    -1, -1, -1, -1,  // {2}
    -1, -1, -1, -1,  // {3}
    0,  0,  0,  0,   // {4}
    1,  1,  1,  1,   // {5}
    1,  1,  1,  1,   // {6}
    1,  1,  1,  1,   // {7}
    0,  0            // {8}
};

/*
    When flowey creates bullets, they move from him to 5 places above him, we
   precompute those places and interpolate betweem flowey's original position
   and them with these constants.

*/
const u16 end_x[5] = {FLOWEY_X - 4 - 50, FLOWEY_X - 4 - 25, FLOWEY_X - 4,
                      FLOWEY_X - 4 + 25, FLOWEY_X - 4 + 50};

const u16 end_y[5] = {FLOWEY_Y - 21, FLOWEY_Y - 41, FLOWEY_Y - 51,
                      FLOWEY_Y - 41, FLOWEY_Y - 21};

// ---------------------------- *
//        LOCAL VARIABLES       |
// ---------------------------- *

struct {
    Sprite *heart;
    Sprite *flowey;
    Sprite *toriel;
    Sprite *fireball;
    Sprite *health;
} spr;

// At what part of sprite change is flowey when he's being
// flung
u8 flowey_thrown_i;

u8 tick;    // General tick used across dialogue
u16 timer;  // Only used for flowey portion

u16 vram_ind;  // Useful for when there's extra tiles loaded other than textbox,
               // we don't want to make assumptions (this could be passed as a
               // parameter by the world state?). Similar functionality can be
               // see in the sample/sonic game.

struct {
    /*
        Which character in bin-char buffer and where to draw it.
    */
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
    // Prevent dialogue from being written. Useful for when we're waiting for
    // bullets to reach bottom of screen or for anything to finish before
    // continuing.
    u8 blocking;
    // If true we exit out of this.
    u8 done;

    u8 speed;
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

    s16 flowey_x;
    s16 flowey_y;

    s16 fireball_x;
    s16 fireball_y;

    s16 toriel_x;
    s16 toriel_y;

    /*


    */
    u8 heart_blocking;
    u8 heart_collide;
    u8 dodge_count;

    // Battle box default [15, 15, 10, 9] -- when flowey gloats it decreases.
    u8 box_x;
    u8 box_y;
    u8 box_w;
    u8 box_h;
} battle;

void flowey_init(state_parameters_t args) {
    /*
        Give everything initial values.
    */

    spr.heart = NULL;
    spr.flowey = NULL;
    spr.toriel = NULL;

    tick = 0;
    timer = 0;

    dialogue.next = FALSE;
    dialogue.press = FALSE;

    dialogue.x = 0;
    dialogue.y = 0;

    dialogue.c = D_FLOWEY_TALK0;

    dialogue.face_frame = 0;

    dialogue.i = 0;
    dialogue.blocking = 0;

    dialogue.done = FALSE;

#ifdef DEBUG
    dialogue.speed = 1;
#else
    dialogue.speed = 5;
#endif

    battle.state = S_FLOWEY_NOTHING;

    battle.dodge_count = 0;

    flowey_thrown_i = 0;

    // Proportions of box
    battle.box_x = 15;
    battle.box_y = 15;
    battle.box_w = 10;
    battle.box_h = 9;

    /*
        For now we load in the font sheet and we set the vram_index after it. In
       the case of this being integrated by world, this would be done much
       differently.

    */
    VDP_loadTileSet(&font_sheet, TILE_USER_INDEX, DMA);

    vram_ind = (u16)args.parameter_data;

    SPR_init();

    battle.pellets = MEM_alloc(sizeof(projectile_data_t) * MAX_FLOWEY_PELLETS);

    /*
        Allocate one bullet, throughout the entire duration bullets are used we
       keep it. It serves as the "base" bullet that all others are batched from.
       This is done so that we can have 32 animated sprites at once.

       All other sprites are made with the addSpriteEx
    */
    battle.pellets[0].spr = SPR_addSprite(&flowey_bullet, 0, 0,
                                          TILE_ATTR(PAL1, TRUE, FALSE, FALSE));

    /*
        We make it hidden, since it's only relevant when they appear, we set
       auto-tile upload to false and give it its own animation callback because
       we want to batch animate all of them.
    */
    SPR_setVisibility(battle.pellets[0].spr, HIDDEN);
    SPR_setAutoTileUpload(battle.pellets[0].spr, FALSE);
    SPR_setFrameChangeCallback(battle.pellets[0].spr, pellet_animator);

    /*
        We load all the possible frames of the pellet where the vram index is
       at, based off of the base sprite's definition and we save number of tiles
       to increment vram index, just incase anything is loaded after this.
    */
    u16 num_tiles;
    battle.pellet_vram = SPR_loadAllFrames(battle.pellets[0].spr->definition,
                                           vram_ind, &num_tiles);
    vram_ind += num_tiles;

    /*
        Go ahead and set up flowey,spr.heartand box that surronds the heart.
    */

    box_draw(battle.box_x, battle.box_y, battle.box_w, battle.box_h, PAL1);

    VDP_drawText("LV1 {| 20/20", battle.box_x - 1, battle.box_y + battle.box_h);

    PAL_setPalette(PAL2, health_sprite.palette->data, DMA);
    spr.health = SPR_addSprite(&health_sprite, (battle.box_x + 5) * 8,
                               (battle.box_y + battle.box_h) * 8,
                               TILE_ATTR(PAL2, TRUE, FALSE, FALSE));

    spr.heart = SPR_addSprite(&heart_sprite, HEART_X - 4, HEART_Y,
                              TILE_ATTR(PAL1, TRUE, FALSE, FALSE));

    battle.heart_x = HEART_X - 4;
    battle.heart_y = HEART_Y;
    battle.heart_vx = 0;
    battle.heart_vy = 0;
    battle.heart_collide = 0;
    battle.heart_blocking = 0;

    battle.flowey_x = PIXEL_WIDTH / 2 - flowey_battle.w / 2;
    battle.flowey_y = 8 * 7;

    spr.flowey = SPR_addSprite(&flowey_battle, battle.flowey_x, battle.flowey_y,
                               TILE_ATTR(PAL1, TRUE, FALSE, FALSE));
}
void flowey_input(u16 changed, u16 state) {
    /*
        If we are waiting for user to continue to next dialogue, A is pressed
       and state isn't in a position where it has to "finish" itself, then it's
       'pressed,' which clears text and moves onto next string in bin segment.
     */
    if (dialogue.next && (state & BUTTON_A) &&
        battle.state != S_FLOWEY_THROW_PELLETS &&
        battle.state != S_FLOWEY_DIE && battle.state != S_FLOWEY_CONFUSED) {
        dialogue.press = TRUE;
    }

    /*
        We set thespr.heartvelocity here instead of moving, the collision
       detection with the box and moving is handled in update sequence.
    */
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
    if (dialogue.done) {
        state_pop();
        return;
    }

    tick++;

    // Extra helper functions in update seqnece so flowey_update() doesn't get
    // bloated: flowey being 'thrown' only happens in confused state.
    helper_heart_tick();
    helper_battle_tick();
    if (battle.state == S_FLOWEY_CONFUSED) helper_flowey_throw();

    if (dialogue.press) {
        dialogue.next = FALSE;
        dialogue.press = FALSE;

        VDP_clearTextArea(0, 0, 22, 4);
        dialogue.x = 0;
        dialogue.y = 0;

        // Move towards next dialogue, if there's a transition with extra things
        // that need to be accounted for, we need to handle it here.
        helper_scene_state();

#ifdef DEBUG
        char buf[3];
        intToStr(dialogue.i, buf, 1);
        VDP_drawText(buf, 30, 0);
#endif
    }
    if (!dialogue.next && !dialogue.blocking &&
        (dialogue.speed == 1 || tick % dialogue.speed)) {
        // Only one will be on screen at a time
        Sprite *focus = (spr.flowey) ? spr.flowey : spr.toriel;

        SPR_setAnim(focus, faces[dialogue.i]);
        helper_dialogue_tick();

        /*
            If dialogue is finished we close flowey's mouth, otherwise
           continue by just going from 0~1 talking.
        */
        if (dialogue.next) {
            SPR_setFrame(focus, 0);
        } else if (tick % 10 == 0) {
            dialogue.face_frame = !dialogue.face_frame;
            SPR_setFrame(focus, dialogue.face_frame);
        }
    }
}
void flowey_clean() {}
void flowey_redraw(state_return_t ret) {}
state_return_t flowey_shutdown() {
    VDP_clearPlane(BG_A, TRUE);
    SPR_clear();

    // Potentially prevent any dangling pointers
    spr.flowey = NULL;
    spr.toriel = NULL;
    spr.fireball = NULL;
    spr.heart = NULL;
    battle.pellets = NULL;

    state_return_t ret;
    return ret;
}

void pellet_animator(Sprite *master) {
    /*
        Callback function for animation batching. Dependent on amount of bellets
       used. We get the tileindex from the pellet vram and go through how many
       are being used, pointing it to those tiles in vram. Only called for the
       "base" sprite, instead of all 32 potentially being called at once, so
       prevents lag massively.
    */

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
        // Very primitive way of having one character load at a time
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

        That means, the left bound is at tile edge of tile 16, right bound is
       at edge of tile 23 (15 + 10 - 2)

       That means, the top bound is at tile edge
       of tile 16, bottom bound is at edge of tile 22 (15 + 9 - 2)
    */
    temp_x = clamp(temp_x, (battle.box_x + 1) * 8,
                   (battle.box_x + battle.box_w - 2) * 8);
    temp_y = clamp(temp_y, (battle.box_x + 1) * 8,
                   (battle.box_x + battle.box_h - 2) * 8);

    battle.heart_x = temp_x;
    battle.heart_y = temp_y;
    SPR_setPosition(spr.heart, battle.heart_x, battle.heart_y);
}

void helper_battle_tick() {
    // Only 'move' bullets every 3 ticks since their velocities can make them go
    // fast otherwise.

    if (tick % 3 != 0) return;

    switch (battle.state) {
        // What's up with ':;' -- C standard doesn't allow labels infront of
        // variable declarations. This is only fixed in C23
        case S_FLOWEY_GEN_PELLETS:;

            //    Pellets come from flowey and go towards the positions they're
            //   set at

            for (u8 i = 0; i < 5; ++i) {
                projectile_lerp(&battle.pellets[i], 14);
                s16 x = battle.pellets[i].x;
                s16 y = battle.pellets[i].y;
                SPR_setPosition(battle.pellets[i].spr, x, y);
            }
            break;
        case S_FLOWEY_THROW_PELLETS:;

            //    Pellets go from where they were resting at the player (OR THEY
            //   ARE SPAWNED THERE WHEN HE SHOOTS AT THE PLAYER MULTIPLE TIMES).

            // In the case that the player dodges all the bullets, this would be
            // zero, since otherwise it would be ORed for any bullet on screen.
            u8 not_clear = 0;
            for (u8 i = 0; i < 5; ++i) {
                if (SPR_getVisibility(battle.pellets[i].spr) != VISIBLE)
                    continue;

                not_clear |= (1 << i);

                battle.pellets[i].x += battle.pellets[i].v_x;
                battle.pellets[i].y += battle.pellets[i].v_y;
                SPR_setPosition(battle.pellets[i].spr, battle.pellets[i].x,
                                battle.pellets[i].y);

                if (circles_collide(battle.pellets[i].x, battle.pellets[i].y, 4,
                                    battle.heart_x, battle.heart_y, 4)) {
                    battle.heart_collide = 1;
                    // Emualate it being pressed to get next state
                    dialogue.press = TRUE;

                    return;
                }

                if (battle.pellets[i].y >= PIXEL_HEIGHT)
                    SPR_setVisibility(battle.pellets[i].spr, HIDDEN);
            }

            // When the player dodges all bullets
            if (!not_clear) {
                battle.heart_collide = 0;
                // Emualate it being pressed to get next state
                dialogue.press = TRUE;
                battle.dodge_count++;
                return;
            }

            break;
        case S_FLOWEY_DIE:;

            //    The ring slowly forms around the player, he says die, then it
            //   encloses the player

            if (battle.pellets_used < MAX_FLOWEY_PELLETS) {
                // Ring is still forming. The positions are already computed, we
                // just have to make them visible.
                SPR_setVisibility(battle.pellets[battle.pellets_used].spr,
                                  VISIBLE);
                battle.pellets_used++;

                // Once all loaded in, we begin the move-in sequence
                if (battle.pellets_used == MAX_FLOWEY_PELLETS) {
                    battle.heart_blocking = FALSE;
                    dialogue.blocking = FALSE;
                }

            } else if (tick % 9 == 0) {
                // Ring moves in

                for (u8 i = 0; i < MAX_FLOWEY_PELLETS; ++i) {
                    battle.pellets[i].x += circle_vx[i];
                    battle.pellets[i].y += circle_vy[i];
                    SPR_setPosition(battle.pellets[i].spr, battle.pellets[i].x,
                                    battle.pellets[i].y);

                    // If hit, go ahead and disappear all bullets, infact - we
                    // can just free them since they're never used after this.
                    if (circles_collide(battle.pellets[i].x,
                                        battle.pellets[i].y, 4, battle.heart_x,
                                        battle.heart_y, 4)) {
                        // Transistion to flowey being confused
                        battle.state = S_FLOWEY_CONFUSED;

                        battle.pellets_used = 0;

                        for (u8 j = 0; j < MAX_FLOWEY_PELLETS; ++j) {
                            SPR_releaseSprite(battle.pellets[j].spr);
                        }
                        MEM_free(battle.pellets);

                        // Go ahead and allocate the fireball but keep it
                        // invisible

                        battle.fireball_x = FLOWEY_X + 75;
                        battle.fireball_y = FLOWEY_Y - 20;
                        spr.fireball =
                            SPR_addSprite(&toriel_fireball, battle.fireball_x,
                                          battle.fireball_y,
                                          TILE_ATTR(PAL1, TRUE, FALSE, FALSE));
                        SPR_setVisibility(spr.fireball, HIDDEN);
                        VDP_drawText("LV1 {| 20/20", 14, 24);
                        SPR_setFrame(spr.health, 0);
                        return;
                    }
                }
            }

            break;
        default:
            break;
    }
}
void helper_scene_state() {
    if (dialogue.i == I_FLOWEY_TALK8 && battle.heart_collide) {
        // If scene was previously pellets being thrown and player got hit
        dialogue.i = I_FLOWEY_HIT1;
        dialogue.c = D_FLOWEY_HIT1;
        dialogue.blocking = FALSE;
    } else if (dialogue.i == I_FLOWEY_TALK8 && !battle.heart_collide) {
        // Otherwise, the player didn't get hit
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
        // Give him default face (note that it does that)
        SPR_setAnim(spr.flowey, 0);
    } else if (dialogue.i == I_FLOWEY_DODGE2_1) {
        dialogue.i = I_FLOWEY_DIE;
        dialogue.c = D_FLOWEY_DIE;
    } else if (dialogue.i == I_FLOWEY_DIE) {
        dialogue.i = I_TORIEL_TALK0;  // Placeholder entry, text never actually
                                      // gets written.
        dialogue.c = D_TORIEL_TALK0;
    } else if (dialogue.i == I_TORIEL_TALK5) {  // Finish everything
        dialogue.done = TRUE;
        dialogue.blocking = TRUE;
        return;
    } else {
        dialogue.i++;  // Otherwise just continue.
    }

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
                SPR_setPosition(battle.pellets[i].spr, FLOWEY_X - 4,
                                FLOWEY_Y - 4);
                SPR_setVisibility(battle.pellets[i].spr, VISIBLE);

                battle.pellets[i].x = FLOWEY_X - 4;
                battle.pellets[i].y = FLOWEY_Y - 4;
                battle.pellets[i].start_x = FLOWEY_X - 4;
                battle.pellets[i].start_y = FLOWEY_Y - 4;

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
            // they spawn at where they moved to instead of moving there, so
            // we need to keep this in mind.
            if (battle.dodge_count > 0) {
                for (u8 i = 0; i < 5; ++i) {
                    SPR_setPosition(battle.pellets[i].spr, end_x[i], end_y[i]);
                    SPR_setVisibility(battle.pellets[i].spr, VISIBLE);

                    battle.pellets[i].x = end_x[i];
                    battle.pellets[i].y = end_y[i];
                }
                battle.pellets_used = 5;
            }

            battle.state = S_FLOWEY_THROW_PELLETS;

            s16 end_x = battle.heart_x + 4;
            s16 end_y = battle.heart_y + 4;

            for (u8 i = 0; i < 5; ++i) {
                s16 d_x = end_x - battle.pellets[i].x + 4;
                s16 d_y = end_y - battle.pellets[i].y + 4;
                // Good speed that is close to how fast they go
                // in the game.
                battle.pellets[i].v_x = d_x / 30;
                battle.pellets[i].v_y = d_y / 30;
            }
            break;
        case I_FLOWEY_HIT1:
            battle.state = S_FLOWEY_HIT;

            battle.pellets_used = 0;
            for (u8 i = 0; i < 5; ++i) {
                SPR_setVisibility(battle.pellets[i].spr, HIDDEN);
            }
            VDP_drawText("LV1 {|  1/20", battle.box_x - 1,
                         battle.box_y + battle.box_h);
            SPR_setFrame(spr.health, 7);
            break;
            /*
            Die!
            */
        case I_FLOWEY_DIE:
            battle.state = S_FLOWEY_DIE;
            // Why do we block? We need a circle of bullets to be created
            // around the player, after which flowey then says die.
            dialogue.blocking = TRUE;
            battle.heart_blocking = TRUE;
            battle.heart_collide = FALSE;

            SPR_setAnim(spr.flowey, 5);

            // Resize the box (I don't know, it does this for some reason?)
            // Heart being put in it is handled by clamp() in update
            // sequence.

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

            SPR_setPosition(spr.heart, battle.heart_x, battle.heart_y);

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
            break;
    }
}

void helper_flowey_throw() {
    /*
    State handler for when flowey gets thrown off the screen by a fireball and
    toriel zooms into the middle.

    */

    timer++;

    if (spr.toriel) {
        if (battle.toriel_x <= PIXEL_WIDTH / 2 - 36) {
            // Now we can actually write dialogue and enter the next state.
            battle.state = S_TORIEL_ENTER;
            dialogue.press = TRUE;
        }
        battle.toriel_x -= 2;

        SPR_setPosition(spr.toriel, battle.toriel_x, battle.toriel_y);

        return;
    }
    // Only do all of this if flowey != nullptr
    if (!spr.flowey) return;

    // If flowey is out of the frame, we move in toriel.
    if (flowey_thrown_i >= THROWN_FRAMES && spr.flowey) {
        SPR_releaseSprite(spr.flowey);
        spr.flowey = NULL;  // Help for choosing which one should talk.

        // Spawn in toriel
        battle.toriel_x = PIXEL_WIDTH;
        battle.toriel_y = FLOWEY_Y - 60;

        spr.toriel =
            SPR_addSprite(&flowey_toriel, battle.toriel_x, battle.toriel_y,
                          TILE_ATTR(PAL1, TRUE, FALSE, FALSE));
        SPR_setAnim(spr.toriel, 1);  // Concerned look
        return;
    }
    if (timer == throw_anim_t[1]) {
        SPR_setVisibility(spr.fireball, VISIBLE);
    }

    if (SPR_getVisibility(spr.fireball) == VISIBLE) {
        battle.fireball_x -= 14;
        SPR_setPosition(spr.fireball, battle.fireball_x, battle.fireball_y);
    }

    if (flowey_thrown_i > 2) {
        battle.flowey_x -= 8;
        battle.flowey_y -= 2;
        SPR_setPosition(spr.flowey, battle.flowey_x, battle.flowey_y);
        SPR_setVisibility(spr.fireball, HIDDEN);
    }

    if (timer >= throw_anim_t[flowey_thrown_i]) {
        SPR_setAnim(spr.flowey, throw_anim_f[flowey_thrown_i] >> 4);
        SPR_setFrame(spr.flowey, throw_anim_f[flowey_thrown_i] & 0x0F);
        flowey_thrown_i++;
    }
}