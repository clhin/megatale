#include "textbox.h"

#include <resources.h>

#include "text.h"

/*
    Local variables
*/

text_info_t text_info;

// Note: if you change MAX_LINE_SIZE, change this
const char empty_block[MAX_LINE_SIZE + 1] =
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";

/*
    Local function headers that are defined lower in the file - help with DRY
   principles
*/

void letter_help(char c, u8 line, u8 position, u8 x, u8 y);
void tile_set(u8 vflip, u8 hflip, u16 tile_id, u16 x, u16 y);
void set_tile(u8 vflip, u8 hflip, u16 tile_x, u16 tile_y, u16 x, u16 y);
void asterisk_show(u8 asterisk_num);
void set_dialogue(const char *text, u8 asterisk_one, u8 asterisk_two,
                  u8 asterisk_three);

#define LEFT_BORDER 151
#define BOTTOM_BORDER 152
#define LEFT_CORNER_BORDER 153
#define LEFT_BORDER_ANIM_1 154
#define LEFT_BORDER_ANIM_2 155
#define ASTERISK 158

void box_draw(u8 x, u8 y, u8 w, u8 h, u8 pal) {
    if (w < 3 || h < 3) return;
    // This just sets the horizontal line borders
    VDP_fillTileMapRect(
        BG_A, TILE_ATTR_FULL(pal, TRUE, 0, 0, TILE_USER_INDEX + BOTTOM_BORDER),
        x + 1, y, w - 2, 1);

    VDP_fillTileMapRect(
        BG_A, TILE_ATTR_FULL(pal, TRUE, 1, 0, TILE_USER_INDEX + BOTTOM_BORDER),
        x + 1, y + h - 1, w - 2, 1);

    // Sets the vertical line borders

    VDP_fillTileMapRect(
        BG_A, TILE_ATTR_FULL(pal, TRUE, 0, 0, TILE_USER_INDEX + LEFT_BORDER), x,
        y + 1, 1, h - 2);

    VDP_fillTileMapRect(
        BG_A, TILE_ATTR_FULL(pal, TRUE, 0, 1, TILE_USER_INDEX + LEFT_BORDER),
        x + w - 1, y + 1, 1, h - 2);

    VDP_fillTileMapRect(BG_A, TILE_ATTR_FULL(pal, TRUE, 0, 0, TILE_USER_INDEX),
                        x + 1, y + 1, w - 2, h - 2);

    tile_set(0, 1, LEFT_CORNER_BORDER, x, y);
    tile_set(0, 0, LEFT_CORNER_BORDER, x + w - 1, y);

    tile_set(1, 1, LEFT_CORNER_BORDER, x, y + h - 1);
    tile_set(1, 0, LEFT_CORNER_BORDER, x + w - 1, y + h - 1);
}

void textbox_init(TextBoxMode mode, u8 y_off, const char *text, u8 asterisk_one,
                  u8 asterisk_two, u8 asterisk_three) {
    text_info.y_off = y_off;

    set_dialogue(text, asterisk_one, asterisk_two, asterisk_three);

    // If we're in portrait mode, we ignore the lines_used done by
    // set_dialogue() and set it to 3.
    if (mode == TEXT_FLOWEY_MODE) text_info.lines_used = 3;

    textbox_show(mode);
}

void textbox_show(TextBoxMode mode) {
    text_info.mode = mode;
    text_info.portrait = NULL;
    text_info.chars_written = 0;

    u8 full_off = text_info.y_off;

    switch (mode) {
        case TEXT_DIALOGUE_MODE:
            text_info.x_off = 6;
            break;
        case TEXT_FLOWEY_MODE:
            text_info.x_off = 12;
            text_info.portrait =
                SPR_addSprite(&portrait_flowey, 4 * 8, (full_off + 1) * 8,
                              TILE_ATTR(PAL1, TRUE, FALSE, FALSE));
            break;
    }

    /*
        Explanation:

        box_draw() includes borders so we need to add them.

        width is lines + 2 asterisks + 2 borders
        height is lines used * 2 * 1 + 2 for borders
    */
    box_draw(3, full_off - 1, MAX_LINE_SIZE + 4, text_info.lines_used * 2 + 3,
             PAL1);
}

u8 textbox_tick() {
    u8 full_off = text_info.y_off;

    // First: get the total amount of characters the textbox encompasses, if the
    // characters written >= then the length, we've finished the dialogue so we
    // just return 1 by default.
    u8 total_len = 0;
    for (u8 i = 0; i < text_info.lines_used; ++i) {
        total_len += strlen(text_info.lines[i]);
    }
    if (text_info.chars_written >= total_len) return 1;

    u8 len = text_info.chars_written;
    u8 write_asterisk = FALSE;
    u8 asterisk = 0;

    /*
        In all of these cases, if we need to continue writing, we defer it to
       the "letter_help" function.

        If it's the beginning of the line and we need to have an asterisk there,
       we mark it off to be drawn.


        First case: we need to draw the first line.

        If the characters written (len) is less than the length of the first
       line, we still need to finish writing it out.

       Second case: we need to draw the second line.

         If the characters written (len) is greater than the length of the first
        line, we need to write it out.

        Third case: we need to draw the third line.
    */
    if (len < strlen(text_info.lines[0])) {
        letter_help(text_info.lines[0][len], 0, len, text_info.x_off + len,
                    full_off);

        if (len == 0 && text_info.asterisks[0]) {
            write_asterisk = TRUE;
            asterisk = 0;
        }

    } else if (len >= strlen(text_info.lines[0]) &&
               len - strlen(text_info.lines[0]) < strlen(text_info.lines[1])) {
        /*
            In other words, if character written is more than
        */

        u8 offset = (len - strlen(text_info.lines[0]));

        letter_help(text_info.lines[1][offset], 1, offset,
                    text_info.x_off + offset, full_off + 2);

        if (offset == 0 && text_info.asterisks[1]) {
            write_asterisk = TRUE;
            asterisk = 1;
        }

    } else {
        u8 offset =
            (len - strlen(text_info.lines[0]) - strlen(text_info.lines[1]));

        letter_help(text_info.lines[2][offset], 2, offset,
                    text_info.x_off + offset, full_off + 4);

        if (offset == 0 && text_info.asterisks[2]) {
            write_asterisk = TRUE;
            asterisk = 2;
        }
    }

    // If we need to have an asterisk written there, we draw it.
    if (write_asterisk) asterisk_show(asterisk);

    text_info.chars_written++;

    /* This section is for portrait animation, if there is any
     */

    switch (text_info.mode) {
        case TEXT_FLOWEY_MODE:
            SPR_nextFrame(text_info.portrait);
            break;
    }

    return 0;
}

void textbox_flush(const char *text, u8 asterisk_one, u8 asterisk_two,
                   u8 asterisk_three) {
    VDP_fillTileMapRect(BG_A, TILE_ATTR_FULL(PAL1, TRUE, 0, 0, TILE_USER_INDEX),
                        4, text_info.y_off, 32, 7);

    set_dialogue(text, asterisk_one, asterisk_two, asterisk_three);

    if (text_info.mode == TEXT_FLOWEY_MODE) text_info.lines_used = 3;

    text_info.chars_written = 0;
}
void textbox_close() {
    SPR_releaseSprite(text_info.portrait);
    text_info.portrait = NULL;

    VDP_clearTileMapRect(BG_A, 3, text_info.y_off - 1, 34,
                         text_info.lines_used * 2 + 3);
}

/*
    Local function to help us write a letter without any stress.
    - c: ascii character
    - line: What line is it on? Used to check line above.
    - position: Where in the string is it at?
    - x: Tile position x
    - y: Tile position y


*/
void letter_help(char c, u8 line, u8 position, u8 x, u8 y) {
    // If we're not on the first line and the position is in the string above,
    // we check for tails. With the tail we then draw the letter.
    // we emptied the lines with \0 beforehand, so no garbage should be
    // possible.
    char above_c = text_info.lines[line - 1][position];

    draw_letter(c, above_c, x, y, TILE_USER_INDEX, BG_A, PAL1);
    // draw_letter(c, x, y, TILE_USER_INDEX, BG_A, PAL1, tail);
}

/*
    Local function for just shorthand writing tiles without having to do the
   entire function
*/

void tile_set(u8 vflip, u8 hflip, u16 tile_id, u16 x, u16 y) {
    VDP_setTileMapXY(
        BG_A,
        TILE_ATTR_FULL(PAL1, TRUE, vflip, hflip, TILE_USER_INDEX + tile_id), x,
        y);
}

// Given an asterisk number, we just need to write it in its specified position.
void asterisk_show(u8 asterisk_num) {
    u8 y_off = text_info.y_off + asterisk_num * 2 + 1;
    tile_set(0, 0, ASTERISK, text_info.x_off - 2, y_off);
    tile_set(0, 1, ASTERISK, text_info.x_off - 1, y_off);
}

void set_dialogue(const char *text, u8 asterisk_one, u8 asterisk_two,
                  u8 asterisk_three) {
    u8 line = 0;

    /*
        Why do we wipe the lines? Helps us down the road and prevents buggy
       string-arithmetic.

       We do this instead of a for-loop to help save possibly rom size.
    */

    memcpy(text_info.lines[0], empty_block, MAX_LINE_SIZE + 1);
    memcpy(text_info.lines[1], empty_block, MAX_LINE_SIZE + 1);
    memcpy(text_info.lines[2], empty_block, MAX_LINE_SIZE + 1);

    const char *src = text;
    char *dst = text_info.lines[line];

    text_info.lines_used = 1;

    while (*src != '\0') {
        if (*src == '\n') {
            line++;
            text_info.lines_used++;
            if (text_info.lines_used >= 4) break;

            (*dst) = '\0';
            dst = text_info.lines[line];

            src++;
        } else {
            *(dst++) = *(src++);
        }
    }
    (*dst) = '\0';

    for (u8 i = text_info.lines_used; i < 3; ++i) {
        strncpy(text_info.lines[i], "", 1);
    }

    text_info.asterisks[0] = asterisk_one;
    text_info.asterisks[1] = asterisk_two;
    text_info.asterisks[2] = asterisk_three;
}
