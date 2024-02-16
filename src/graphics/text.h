#ifndef TEXT_H_
#define TEXT_H_
#include <genesis.h>

extern u8 lookup_table[74][8];
u8 *get_char_info(char c);

#define GET_TOP(arr) (arr[0] & 0x3F)
#define GET_TOP_VFLIP(arr) ((arr[0] >> 6) & 1)
#define GET_TOP_HFLIP(arr) (arr[0] >> 7)

#define GET_TOP_g_TAIL(arr) (arr[3])
#define GET_TOP_p_TAIL(arr) (arr[4])
#define GET_TOP_q_TAIL(arr) (arr[5] & 0x7F)
#define GET_TOP_Q_TAIL(arr) (arr[6])
#define GET_TOP_comma_TAIL(arr) (arr[7])

#define GET_q_TAIL_HFLIP(arr) (arr[5] >> 7)

#define GET_MIDDLE(arr) (arr[1] & 0x7F)
#define GET_MIDDLE_HFLIP(arr) (arr[1] >> 7)

#define GET_BOTTOM(arr) (arr[2] & 0x7F)
#define GET_BOTTOM_HFLIP(arr) (arr[2] >> 7)

#define DRAW_LETTER(arr, x, y, offset, plane, palette)                     \
    VDP_setTileMapXY(                                                      \
        plane,                                                             \
        TILE_ATTR_FULL(palette, 0, GET_TOP_VFLIP(arr), GET_TOP_HFLIP(arr), \
                       offset + GET_TOP(arr)),                             \
        x, y);                                                             \
    VDP_setTileMapXY(plane,                                                \
                     TILE_ATTR_FULL(palette, 0, 0, GET_MIDDLE_HFLIP(arr),  \
                                    offset + GET_MIDDLE(arr)),             \
                     x, y + 1);                                            \
    VDP_setTileMapXY(plane,                                                \
                     TILE_ATTR_FULL(palette, 0, 0, GET_BOTTOM_HFLIP(arr),  \
                                    offset + GET_BOTTOM(arr)),             \
                     x, y + 2)

#define DRAW_LETTER_g_TAIL(arr, x, y, offset, plane, palette)             \
    VDP_setTileMapXY(plane,                                               \
                     TILE_ATTR_FULL(palette, 0, 0, GET_TOP_HFLIP(arr),    \
                                    offset + GET_TOP_g_TAIL(arr)),        \
                     x, y);                                               \
    VDP_setTileMapXY(plane,                                               \
                     TILE_ATTR_FULL(palette, 0, 0, GET_MIDDLE_HFLIP(arr), \
                                    offset + GET_MIDDLE(arr)),            \
                     x, y + 1);                                           \
    VDP_setTileMapXY(plane,                                               \
                     TILE_ATTR_FULL(palette, 0, 0, GET_BOTTOM_HFLIP(arr), \
                                    offset + GET_BOTTOM(arr)),            \
                     x, y + 2)

#define DRAW_LETTER_p_TAIL(arr, x, y, offset, plane, palette)                  \
    VDP_setTileMapXY(                                                          \
        plane, TILE_ATTR_FULL(palette, 0, 0, 0, offset + GET_TOP_p_TAIL(arr)), \
        x, y);                                                                 \
    VDP_setTileMapXY(plane,                                                    \
                     TILE_ATTR_FULL(palette, 0, 0, GET_MIDDLE_HFLIP(arr),      \
                                    offset + GET_MIDDLE(arr)),                 \
                     x, y + 1);                                                \
    VDP_setTileMapXY(plane,                                                    \
                     TILE_ATTR_FULL(palette, 0, 0, GET_BOTTOM_HFLIP(arr),      \
                                    offset + GET_BOTTOM(arr)),                 \
                     x, y + 2)

#define DRAW_LETTER_q_TAIL(arr, x, y, offset, plane, palette)             \
    VDP_setTileMapXY(plane,                                               \
                     TILE_ATTR_FULL(palette, 0, 0, GET_q_TAIL_HFLIP(arr), \
                                    offset + GET_TOP_q_TAIL(arr)),        \
                     x, y);                                               \
    VDP_setTileMapXY(plane,                                               \
                     TILE_ATTR_FULL(palette, 0, 0, GET_MIDDLE_HFLIP(arr), \
                                    offset + GET_MIDDLE(arr)),            \
                     x, y + 1);                                           \
    VDP_setTileMapXY(plane,                                               \
                     TILE_ATTR_FULL(palette, 0, 0, GET_BOTTOM_HFLIP(arr), \
                                    offset + GET_BOTTOM(arr)),            \
                     x, y + 2)

#define DRAW_LETTER_Q_TAIL(arr, x, y, offset, plane, palette)                  \
    VDP_setTileMapXY(                                                          \
        plane, TILE_ATTR_FULL(palette, 0, 0, 0, offset + GET_TOP_Q_TAIL(arr)), \
        x, y);                                                                 \
    VDP_setTileMapXY(plane,                                                    \
                     TILE_ATTR_FULL(palette, 0, 0, GET_MIDDLE_HFLIP(arr),      \
                                    offset + GET_MIDDLE(arr)),                 \
                     x, y + 1);                                                \
    VDP_setTileMapXY(plane,                                                    \
                     TILE_ATTR_FULL(palette, 0, 0, GET_BOTTOM_HFLIP(arr),      \
                                    offset + GET_BOTTOM(arr)),                 \
                     x, y + 2)

#define DRAW_LETTER_comma_TAIL(arr, x, y, offset, plane, palette)              \
    VDP_setTileMapXY(                                                          \
        plane,                                                                 \
        TILE_ATTR_FULL(palette, 0, 0, 0, offset + GET_TOP_comma_TAIL(arr)), x, \
        y);                                                                    \
    VDP_setTileMapXY(plane,                                                    \
                     TILE_ATTR_FULL(palette, 0, 0, GET_MIDDLE_HFLIP(arr),      \
                                    offset + GET_MIDDLE(arr)),                 \
                     x, y + 1);                                                \
    VDP_setTileMapXY(plane,                                                    \
                     TILE_ATTR_FULL(palette, 0, 0, GET_BOTTOM_HFLIP(arr),      \
                                    offset + GET_BOTTOM(arr)),                 \
                     x, y + 2)

#endif
