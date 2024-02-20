#include "textbox.h"

#include "text.h"

/*
    Local function headers that are defined lower in the file
*/

void letter_help(char c, u8 line, u8 position, u8 x, u8 y);
void tile_set(u8 vflip, u8 hflip, u16 tile_id, u16 x, u16 y);
void set_tile(u8 vflip, u8 hflip, u16 tile_x, u16 tile_y, u16 x, u16 y);
void asterisk_show(u8 asterisk_num);

#define LEFT_BORDER 150
#define BOTTOM_BORDER 151
#define LEFT_CORNER_BORDER 152
#define LEFT_BORDER_ANIM_1 153
#define LEFT_BORDER_ANIM_2 154
#define ASTERISK 155

#define DIALOGUE_OFFSET 19

void textbox_show(TextBoxMode mode) {
    text_info.chars_written = 0;

    // For now we only handle Dialogue, gotta handle Portrait mode and Battle
    // mode soon
    u8 full_off = DIALOGUE_OFFSET;
    u8 x_off = 0;

    // This just sets the horizontal line borders
    VDP_fillTileMapRect(
        BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TILE_USER_INDEX + BOTTOM_BORDER), 4,
        full_off - 1, MAX_LINE_SIZE + 2, 1);

    VDP_fillTileMapRect(
        BG_A, TILE_ATTR_FULL(PAL1, 0, 1, 0, TILE_USER_INDEX + BOTTOM_BORDER), 4,
        full_off + 1 + text_info.lines_used * 2, MAX_LINE_SIZE + 2, 1);

    // Sets the vertical line borders

    VDP_fillTileMapRect(
        BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TILE_USER_INDEX + LEFT_BORDER), 3,
        full_off, 1, text_info.lines_used * 2 + 1);

    VDP_fillTileMapRect(
        BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 1, TILE_USER_INDEX + LEFT_BORDER), 36,
        full_off, 1, text_info.lines_used * 2 + 1);

    // Fill body
    VDP_fillTileMapRect(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TILE_USER_INDEX), 4,
                        full_off, 32, text_info.lines_used * 2 + 1);

    // Corner pieces
    tile_set(0, 1, LEFT_CORNER_BORDER, 3, full_off - 1);
    tile_set(0, 0, LEFT_CORNER_BORDER, 36, full_off - 1);
    tile_set(1, 0, LEFT_CORNER_BORDER, 36,
             full_off + text_info.lines_used * 2 + 1);
    tile_set(1, 1, LEFT_CORNER_BORDER, 3,
             full_off + text_info.lines_used * 2 + 1);
}

u8 textbox_tick() {
    u8 full_off = DIALOGUE_OFFSET;

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
        letter_help(text_info.lines[0][len], 0, len, 6 + len, full_off);

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

        letter_help(text_info.lines[1][offset], 1, offset, 6 + offset,
                    full_off + 2);

        if (offset == 0 && text_info.asterisks[1]) {
            write_asterisk = TRUE;
            asterisk = 1;
        }

    } else {
        u8 offset =
            (len - strlen(text_info.lines[0]) - strlen(text_info.lines[1]));

        letter_help(text_info.lines[2][offset], 2, offset, 6 + offset,
                    full_off + 4);

        if (offset == 0 && text_info.asterisks[2]) {
            write_asterisk = TRUE;
            asterisk = 2;
        }
    }

    // If we need to have an asterisk written there, we draw it.
    if (write_asterisk) asterisk_show(asterisk);

    text_info.chars_written++;

    return 0;
}

void textbox_flush() {
    VDP_clearTileMapRect(BG_A, 4, DIALOGUE_OFFSET, 32,
                         text_info.lines_used * 2 + 1);
}
void textbox_close() {
    VDP_clearTileMapRect(BG_A, 3, DIALOGUE_OFFSET - 1, 34,
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
    LetterTail tail = LETTER_TAIL_NONE;

    // If we're not on the first line and the position is in the string above,
    // we check for tails. With the tail we then draw the letter.
    if (line > 0 && position < strlen(text_info.lines[line - 1])) {
        char above_c = text_info.lines[line - 1][position];

        switch (above_c) {
            case 'g':
            case 'j':
            case 'y':
                tail = LETTER_TAIL_g;
                break;
            case 'p':
                tail = LETTER_TAIL_p;
                break;
            case 'q':
                tail = LETTER_TAIL_q;
                break;
            case 'Q':
                tail = LETTER_TAIL_Q;
                break;
            case ',':
                tail = LETTER_TAIL_comma;
                break;
        }
    }
    draw_letter(c, x, y, TILE_USER_INDEX, BG_A, PAL1, tail);
}

/*
    Local function for just shorthand writing tiles without having to do the
   entire function
*/

void tile_set(u8 vflip, u8 hflip, u16 tile_id, u16 x, u16 y) {
    VDP_setTileMapXY(
        BG_A, TILE_ATTR_FULL(PAL1, 0, vflip, hflip, TILE_USER_INDEX + tile_id),
        x, y);
}

// Given an asterisk number, we just need to write it in its specified position.
void asterisk_show(u8 asterisk_num) {
    u8 y_off = DIALOGUE_OFFSET + asterisk_num * 2 + 1;
    tile_set(0, 0, ASTERISK, 4, y_off);
    tile_set(0, 1, ASTERISK, 5, y_off);
}