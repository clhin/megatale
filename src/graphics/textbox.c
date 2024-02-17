#include "textbox.h"

#include "text.h"

/*
    Local function headers that are defined lower in the file
*/

void letter_help(char c, u8 line, u8 position, u8 x, u8 y);
void tile_set(u8 vflip, u8 hflip, u16 tile_id, u16 x, u16 y);
void set_tile(u8 vflip, u8 hflip, u16 tile_x, u16 tile_y, u16 x, u16 y);
void show_dialogue(TextBoxMode mode);
void show_battle();
void show_toriel();

const u16 lookup_table_old[123] = {
    0xf07,  0xf07,  0xf07,  0xf07,  0xf07,  0xf07,  0xf07,  0xf07,  0xf07,
    0xf07,  0xf07,  0xf07,  0xf07,  0xf07,  0xf07,  0xf07,  0xf07,  0xf07,
    0xf07,  0xf07,  0xf07,  0xf07,  0xf07,  0xf07,  0xf07,  0xf07,  0xf07,
    0xf07,  0xf07,  0xf07,  0xf07,  0xf07,  0x0,    0xe07,  0x1107, 0xf07,
    0xf07,  0xf07,  0xf07,  0x1007, 0xb07,  0xc07,  0xf07,  0xf07,  0xa07,
    0x1207, 0x907,  0xf07,  0x7,    0x107,  0x207,  0x307,  0x407,  0x507,
    0x607,  0x707,  0x807,  0x907,  0xd07,  0xf07,  0xf07,  0xf07,  0xf07,
    0xf07,  0xf07,  0x4,    0x104,  0x204,  0x304,  0x404,  0x504,  0x604,
    0x704,  0x804,  0x904,  0xa04,  0xb04,  0xc04,  0xd04,  0xe04,  0xf04,
    0x1004, 0x1104, 0x1204, 0x1304, 0x1404, 0x1504, 0x1604, 0x1704, 0x1804,
    0x1904, 0x1307, 0xf07,  0x1407, 0xf07,  0xf07,  0xf07,  0x1,    0x101,
    0x201,  0x301,  0x401,  0x501,  0x601,  0x701,  0x801,  0x901,  0xa01,
    0xb01,  0xc01,  0xd01,  0xe01,  0xf01,  0x1001, 0x1101, 0x1201, 0x1301,
    0x1401, 0x1501, 0x1601, 0x1701, 0x1801, 0x1901,
};

#define LEFT_BORDER 150
#define BOTTOM_BORDER 151
#define LEFT_CORNER_BORDER 152
#define LEFT_BORDER_ANIM_1 153
#define LEFT_BORDER_ANIM_2 154
#define ASTERISK 155

void textbox_show(TextBoxMode mode) {
    text_info.chars_written = 0;

    u8 full_off = 14;
    u8 x_off = 0;
    // This just sets the horizontal line borders

    VDP_fillTileMapRect(
        BG_A, TILE_ATTR_FULL(PAL0, 0, 0, 0, TILE_USER_INDEX + BOTTOM_BORDER), 4,
        full_off - 1, MAX_LINE_SIZE + 2, 1);

    VDP_fillTileMapRect(
        BG_A, TILE_ATTR_FULL(PAL0, 0, 1, 0, TILE_USER_INDEX + BOTTOM_BORDER), 4,
        full_off + 1 + text_info.lines_used * 2, MAX_LINE_SIZE + 2, 1);

    // Sets the vertical line borders

    VDP_fillTileMapRect(
        BG_A, TILE_ATTR_FULL(PAL0, 0, 0, 0, TILE_USER_INDEX + LEFT_BORDER), 3,
        full_off, 1, text_info.lines_used * 2 + 1);

    VDP_fillTileMapRect(
        BG_A, TILE_ATTR_FULL(PAL0, 0, 0, 1, TILE_USER_INDEX + LEFT_BORDER), 36,
        full_off, 1, text_info.lines_used * 2 + 1);

    for (u8 j = 0; j < text_info.lines_used * 2 + 1; ++j) {
        // Asterisks

        u8 i = (j - 1) / 2;
        if ((j - 1) % 2 == 0 && i < 3 && text_info.asterisks[i]) {
            tile_set(0, 0, ASTERISK, 4 + x_off, full_off + j);
            tile_set(0, 1, ASTERISK, 5 + x_off, full_off + j);
        } else {
            tile_set(0, 0, 0, 4 + x_off, full_off + j);
            tile_set(0, 0, 0, 5 + x_off, full_off + j);
        }
    }

    // Fill body
    VDP_fillTileMapRect(BG_A, TILE_ATTR_FULL(PAL0, 0, 0, 0, TILE_USER_INDEX), 6,
                        full_off, 30, text_info.lines_used * 2 + 1);

    // Corner pieces
    tile_set(0, 1, LEFT_CORNER_BORDER, 3, full_off - 1);
    tile_set(0, 0, LEFT_CORNER_BORDER, 36, full_off - 1);
    tile_set(1, 0, LEFT_CORNER_BORDER, 36,
             full_off + text_info.lines_used * 2 + 1);
    tile_set(1, 1, LEFT_CORNER_BORDER, 3,
             full_off + text_info.lines_used * 2 + 1);
}

u8 textbox_tick() {
    u8 total_len = 0;
    for (u8 i = 0; i < text_info.lines_used; ++i) {
        total_len += strlen(text_info.lines[i]);
    }
    if (text_info.chars_written >= total_len) return 1;

    /*
        First case: we need to draw the first line.
    */

    u8 len = text_info.chars_written;

    if (len < strlen(text_info.lines[0])) {
        letter_help(text_info.lines[0][len], 0, len, 6 + len, 14);

    } else if (len >= strlen(text_info.lines[0]) &&
               len - strlen(text_info.lines[0]) < strlen(text_info.lines[1])) {
        u8 offset = (len - strlen(text_info.lines[0]));

        letter_help(text_info.lines[1][offset], 1, offset, 6 + offset, 16);

    } else {
        u8 offset =
            (len - strlen(text_info.lines[0]) - strlen(text_info.lines[1]));

        letter_help(text_info.lines[2][offset], 2, offset, 6 + offset, 18);
    }

    text_info.chars_written++;

    return 0;
}

/*
    Show the textbox with the specific mode.

    Why use modes? The battle textbox happens a bit higher than normal

*/

void textbox_show_old(TextBoxMode mode) {
    text_info.mode = mode;

    u8 full_off;
    u8 x_off = 0;

    /*
        Go ahead and render the dialogue, then afterwards this switch
       statement we render the box around it
    */
    switch (mode) {
        // They share the same offset
        case TEXT_DIALOGUE_MODE:
            full_off = TEXT_DIALOGUE_OFFSET;
            show_dialogue(TEXT_DIALOGUE_MODE);
            break;
        case TEXT_TORIEL_MODE:
            full_off = TEXT_DIALOGUE_OFFSET;
            show_dialogue(TEXT_TORIEL_MODE);
            show_toriel();
            x_off = 7;
            break;
        case TEXT_BATTLE_MODE:
            full_off = 14;
            break;
    }

    // This just sets the horizontal line borders
    for (u8 j = 0; j < MAX_LINE_SIZE + 2; ++j) {
        set_tile(0, 0, 1, 25, 4 + j, full_off - 1);
        set_tile(1, 0, 1, 25, 4 + j, full_off + 1 + text_info.lines_used * 2);
    }

    // This sets everything vertical
    for (u8 j = 0; j < text_info.lines_used * 2 + 1; ++j) {
        // Vertical line borders
        set_tile(0, 0, 0, 25, 3, full_off + j);
        set_tile(0, 1, 0, 25, 36, full_off + j);
        /*
                This sets the asterisks or space, since there's a max of 3
           lines we set them accordingly to where the text starts If the
           position where they are at is divisible by 0 and they are
           enabled, otherwise just write space

           Note that asterisks for Toriel starts at a different offset.
            */

        u8 i = (j - 1) / 2;
        if ((j - 1) % 2 == 0 && i < 3 && text_info.asterisks[i]) {
            set_tile(0, 0, 24, 25, 4 + x_off, full_off + j);
            set_tile(0, 0, 25, 25, 5 + x_off, full_off + j);
        } else {
            set_tile(0, 0, 0, 0, 4 + x_off, full_off + j);
            set_tile(0, 0, 0, 0, 5 + x_off, full_off + j);
        }
    }
}

void textbox_flush() {}
void textbox_clear() {}

/*
    Local function for just shorthand writing tiles without having to do the
   entire function
*/

void letter_help(char c, u8 line, u8 position, u8 x, u8 y) {
    LetterTail tail = LETTER_TAIL_NONE;

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
    draw_letter(c, x, y, TILE_USER_INDEX, BG_A, PAL0, tail);
}

void tile_set(u8 vflip, u8 hflip, u16 tile_id, u16 x, u16 y) {
    VDP_setTileMapXY(
        BG_A, TILE_ATTR_FULL(PAL0, 0, vflip, hflip, TILE_USER_INDEX + tile_id),
        x, y);
}

void set_tile(u8 vflip, u8 hflip, u16 tile_x, u16 tile_y, u16 x, u16 y) {
    VDP_setTileMapXY(
        BG_A,
        TILE_ATTR_FULL(PAL0, 0, vflip, hflip,
                       TILE_USER_INDEX + (FONT_SHEET_WIDTH * tile_y + tile_x)),
        x, y);
}

void show_dialogue(TextBoxMode mode) {
    u8 x_off = (mode == TEXT_DIALOGUE_MODE) ? 0 : 7;

    for (u8 i = 0; i < text_info.lines_used; ++i) {
        for (u8 j = 0; j < MAX_LINE_SIZE - x_off; ++j) {
            u16 y_off = 1 + (i * 2);

            // If no information, just flush with emptness
            if (text_info.lines[i][j] == '\0') {
                set_tile(0, 0, 0, 0, 6 + j + x_off,
                         TEXT_DIALOGUE_OFFSET + y_off - 1);
                set_tile(0, 0, 0, 0, 6 + j + x_off,
                         TEXT_DIALOGUE_OFFSET + y_off);
                set_tile(0, 0, 0, 0, 6 + j + x_off,
                         TEXT_DIALOGUE_OFFSET + y_off + 1);

                continue;
            }

            /*
                We bit-unpack the position the letter has in the spritesheet
               from the lookup table and then we get the y-position for 3
               possible spaces the letter take.
            */
            u16 pos = lookup_table_old[(u8)(text_info.lines[i][j])];
            u8 x = pos >> 8;
            u8 y = pos & 0xFF;

            u16 top = y - 1;
            u16 middle = y;
            u16 bottom = y + 1;

            // If there's a character above, make it that character.
            // Otherwise make it NUL
            char c_above = (i > 0 && strlen(text_info.lines[i - 1]) >= j)
                               ? text_info.lines[i - 1][j]
                               : '\0';

            // [g, y, j, p, q, Q]
            // Handling union cases, could probably be optimized but fine
            // for now
            if (c_above == 'g' || c_above == 'y' || c_above == 'j') {
                if (y == 1)
                    top = 10;
                else if (y == 4)
                    top = 11;
                else if (y == 7)
                    top = 12;

            } else if (c_above == 'p') {
                if (y == 1)
                    top = 13;
                else if (y == 4)
                    top = 14;
                else if (y == 7)
                    top = 15;

            } else if (c_above == 'q') {
                if (y == 1)
                    top = 16;
                else if (y == 4)
                    top = 17;
                else if (y == 7)
                    top = 18;

            } else if (c_above == 'Q') {
                if (y == 1)
                    top = 19;
                else if (y == 4)
                    top = 20;
                else if (y == 7)
                    top = 21;
            }

            if (text_info.lines[i][j] == ' ') {
                top = 0;
                bottom = 0;
            }

            // Now write the letter
            set_tile(0, 0, x, top, 6 + j + x_off,
                     TEXT_DIALOGUE_OFFSET + y_off - 1);
            set_tile(0, 0, x, middle, 6 + j + x_off,
                     TEXT_DIALOGUE_OFFSET + y_off);
            set_tile(0, 0, x, bottom, 6 + j + x_off,
                     TEXT_DIALOGUE_OFFSET + y_off + 1);
        }
    }
}

void show_toriel() {
    /*
        What a mess.
    */

    // Top space section
    set_tile(0, 0, 0, 0, 4, TEXT_DIALOGUE_OFFSET);
    set_tile(0, 0, 0, 0, 5, TEXT_DIALOGUE_OFFSET);
    set_tile(0, 0, 0, 0, 6, TEXT_DIALOGUE_OFFSET);
    set_tile(0, 0, 0, 0, 7, TEXT_DIALOGUE_OFFSET);
    set_tile(0, 0, 0, 0, 8, TEXT_DIALOGUE_OFFSET);
    set_tile(0, 0, 0, 0, 9, TEXT_DIALOGUE_OFFSET);
    set_tile(0, 0, 0, 0, 10, TEXT_DIALOGUE_OFFSET);

    // Left space section + Toriel ipse
    for (u8 i = 0; i < 5; ++i) {
        set_tile(0, 0, 0, 0, 4, TEXT_DIALOGUE_OFFSET + i + 1);
        set_tile(0, 0, 26, i, 5, TEXT_DIALOGUE_OFFSET + i + 1);
        set_tile(0, 0, 27, i, 6, TEXT_DIALOGUE_OFFSET + i + 1);
        set_tile(0, 0, 28, i, 7, TEXT_DIALOGUE_OFFSET + i + 1);
        set_tile(0, 0, 29, i, 8, TEXT_DIALOGUE_OFFSET + i + 1);
        set_tile(0, 0, 30, i, 9, TEXT_DIALOGUE_OFFSET + i + 1);
        set_tile(0, 0, 31, i, 10, TEXT_DIALOGUE_OFFSET + i + 1);
    }

    // Bottom space section
    set_tile(0, 0, 0, 0, 4, TEXT_DIALOGUE_OFFSET + 6);
    set_tile(0, 0, 0, 0, 5, TEXT_DIALOGUE_OFFSET + 6);
    set_tile(0, 0, 0, 0, 6, TEXT_DIALOGUE_OFFSET + 6);
    set_tile(0, 0, 0, 0, 7, TEXT_DIALOGUE_OFFSET + 6);
    set_tile(0, 0, 0, 0, 8, TEXT_DIALOGUE_OFFSET + 6);
    set_tile(0, 0, 0, 0, 9, TEXT_DIALOGUE_OFFSET + 6);
    set_tile(0, 0, 0, 0, 10, TEXT_DIALOGUE_OFFSET + 6);
}