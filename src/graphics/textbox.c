#include "textbox.h"

/*
    Intuitions on how the textbox is styled.

    The textbox used in undertale handles up to 3 lines, each going as far as
   around 30 charaters. Each line has an asterisk that takes up two characters
   to indicate a new dialogue line. We can take advantage of that when designing
   this.

    Undertale letters don't fit in 8x8 blocks.
    Each character takes up to 3 tiles, with most of it centered on the middle.
   No tile that is above or below the centered on goes as far as half of the
   tile down. We can take advantage of that and create tiles that account for
   characters with extra space under them unioned with tiles that go above.

   Because the amount of tiles that "go under" are relatively low, [q, p, y, j,
   g, Q], this is not that troublesome and doesn't take that much space.

   Fontsheet overlay by 8-pixel rows:

   Row (0-indexed)
   0-2: a-z (Middle:1)
   3-5: A-Z (Middle:4)
   6-8: 0-9.,():!?'"-[] (Middle: 7)
   9-11: for [g, y, j], 3 rows enumerating top selections of [1-3, 4-6, 7-9]
   12-14: for [p], enumerating top selections of [1-3, 4-6, 7-9]
   15-17: for [q], enumerating top selections of [1-3, 4-6, 7-9]
   18-20: for [Q], enumerating top selections of [1-3, 4-6, 7-9]

   21: misc. data just to help construct the box and give animation (when in
   battle it horizontally snaps into a box)

    Other notes: With this in mind the textbox should be 9 tiles vertical in
   total, with 7 being used for the text and 2 for the borders, the textbox
   should be 34 in width. 30 for text, 2 for asterisk and 2 for borders around
   it.
    This ends up being 272*72, which is a close enough size in relation to the
   original game's box.



    Algorithm:

    For every line that is committed we note the following:

    If line above is written to and text in same location is of set [g, y, j, p,
   q, Q] then we switch tile of "top" to where the text "union" is handled




    ASCII Mapping:
    A-Z ~ 65-90
    a-z ~ 97-122
    0-9 ~ 48-57

    .   ~ 46
    ,   ~ 44
    (   ~ 40
    )   ~ 41
    :   ~ 58
    !   ~ 33
    ?   ~ 63
    '   ~ 39
    "   ~ 34
    -   ~ 45
    [   ~ 91
    ]   ~ 93


   Addendum: If this turns out to be a memory issue in the long run,
   experimenting into tile-unions as ORing both is a possibility.
*/

/* Python script to generate this can be found on src/generate_lookup.py


Using a pregenerated static array, takes space but I think is computationally
faster as it's just a lookup table. The location corresponds to the "middle" of
the character

123 elements * 2 bytes, 246 bytes.
*/

const u16 lookup_table[123] = {
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

void textbox_flush() {
    /*
        5 lines:
        j=0: 0,1,2 (1)
        j=1: 2,3,4 (3)
        j=2: 4,5,6 (5)

    */

    for (u8 j = 0; j < MAX_LINE_SIZE; ++j) {
        VDP_setTileMapXY(
            BG_A,
            TILE_ATTR_FULL(PAL0, 0, 0, 0, TILE_USER_INDEX + (26 * 25 + 1)),
            4 + j, 2);

        VDP_setTileMapXY(
            BG_A,
            TILE_ATTR_FULL(PAL0, 0, 1, 0, TILE_USER_INDEX + (26 * 25 + 1)),
            4 + j, 6 + text_info.lines_used);
    }

    for (u8 j = 0; j < text_info.lines_used + 3; ++j) {
        VDP_setTileMapXY(
            BG_A, TILE_ATTR_FULL(PAL0, 0, 0, 0, TILE_USER_INDEX + (26 * 25)), 3,
            3 + j);
    }

    for (u8 i = 0; i < text_info.lines_used; ++i) {
        for (u8 j = 0; j < MAX_LINE_SIZE; ++j) {
            u16 y_off = 1 + (i * 2);

            if (text_info.lines[i][j] == '\0') {
                VDP_setTileMapXY(BG_A,
                                 TILE_ATTR_FULL(PAL0, 0, 0, 0, TILE_USER_INDEX),
                                 4 + j, 3 + y_off - 1);
                VDP_setTileMapXY(BG_A,
                                 TILE_ATTR_FULL(PAL0, 0, 0, 0, TILE_USER_INDEX),
                                 4 + j, 3 + y_off);
                VDP_setTileMapXY(BG_A,
                                 TILE_ATTR_FULL(PAL0, 0, 0, 0, TILE_USER_INDEX),
                                 4 + j, 3 + y_off + 1);

                continue;
            }

            u16 pos = lookup_table[(u8)(text_info.lines[i][j])];
            // 16 pos = lookup_table[97 + j];

            u8 x = pos >> 8;
            u8 y = pos & 0xFF;

            u16 top = TILE_USER_INDEX + 26 * (y - 1) + x;
            u16 middle = TILE_USER_INDEX + 26 * y + x;
            u16 bottom = TILE_USER_INDEX + 26 * (y + 1) + x;

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

                top = TILE_USER_INDEX + (26 * top) + x;
            } else if (c_above == 'p') {
                if (y == 1)
                    top = 13;
                else if (y == 4)
                    top = 14;
                else if (y == 7)
                    top = 15;

                top = TILE_USER_INDEX + (26 * top) + x;
            } else if (c_above == 'q') {
                if (y == 1)
                    top = 16;
                else if (y == 4)
                    top = 17;
                else if (y == 7)
                    top = 18;

                top = TILE_USER_INDEX + (26 * top) + x;
            } else if (c_above == 'Q') {
                if (y == 1)
                    top = 19;
                else if (y == 4)
                    top = 20;
                else if (y == 7)
                    top = 21;

                top = TILE_USER_INDEX + (26 * top) + x;
            }

            if (text_info.lines[i][j] == ' ') {
                top = TILE_USER_INDEX;
                bottom = TILE_USER_INDEX;
            }

            VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL0, 0, 0, 0, top), 4 + j,
                             3 + y_off - 1);

            VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL0, 0, 0, 0, middle), 4 + j,
                             3 + y_off);

            VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL0, 0, 0, 0, bottom), 4 + j,
                             3 + y_off + 1);
        }
    }
}
void textbox_clear() {}