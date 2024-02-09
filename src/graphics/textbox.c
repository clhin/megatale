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

    Other notes: With this in mind the textbox should be 7 tiles vertical in
   total, with 5 being used for the text and 2 for the borders, the textbox
   should be 34 in width. 30 for text, 2 for asterisk and 2 for borders around
   it.
    This ends up being 272*56, which is a close enough size in relation to the
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
        j=1: 1,2,3 (2)
        j=2: 2,3,4 (3)

    */

    for (u8 i = 0; i < text_info.lines_used; ++i) {
        for (u8 j = 0; j < MAX_LINE_SIZE; ++j) {
            if (text_info.lines[i][j] == '\0') break;

            u16 pos = lookup_table[(u8)(text_info.lines[i][j])];
            // 16 pos = lookup_table[97 + j];
            u8 x = pos >> 8;
            u8 y = pos & 0xFF;

            VDP_setTileMapXY(
                BG_A,
                TILE_ATTR_FULL(PAL0, 0, 0, 0, TILE_USER_INDEX + 26 * y + x),
                4 + j, 3 + i);

            VDP_setTileMapXY(BG_A,
                             TILE_ATTR_FULL(PAL0, 0, 0, 0,
                                            TILE_USER_INDEX + 26 * y + x - 26),
                             4 + j, 2 + i);

            VDP_setTileMapXY(BG_A,
                             TILE_ATTR_FULL(PAL0, 0, 0, 0,
                                            TILE_USER_INDEX + 26 * y + x + 26),
                             4 + j, 4 + i);
        }
    }
}
void textbox_clear() {}