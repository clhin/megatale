#include "portrait.h"

#include <resources.h>

u8 portrait_flowey_map[2][PORTRAIT_WIDTH * PORTRAIT_HEIGHT] = {
    {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 14, 15, 16,
     17, 18, 14, 14, 21, 22, 23, 24, 14, 14, 14, 25, 26, 14, 14},
    {0,  1,  2,  3,  4,  5,  6,  7,  12, 13, 10, 11, 14, 15, 19,
     20, 18, 14, 14, 21, 22, 23, 24, 14, 14, 14, 25, 26, 14, 14}};

u16 flowey_index;

u8 portrait_flowey_loadtiles(u16 index) {
    flowey_index = index;

    return VDP_loadTileSet(&portrait_flowey, index, DMA);
}

void portrait_flowey_draw(u8 x, u8 y, u8 pal) {
    for (u8 i = 0; i < PORTRAIT_WIDTH; ++i) {
        for (u8 j = 0; j < PORTRAIT_HEIGHT; ++j) {
            VDP_setTileMapXY(
                BG_A,
                TILE_ATTR_FULL(
                    pal, 0, 0, 0,
                    flowey_index +
                        portrait_flowey_map[0][PORTRAIT_WIDTH * j + i]),
                x + i, y + j);
        }
    }
}
void portrait_flowey_animate(u8 x, u8 y, u8 pal, u8 frame) {
    frame = frame % 2;

    VDP_setTileMapXY(
        BG_A,
        TILE_ATTR_FULL(
            pal, 0, 0, 0,
            flowey_index + portrait_flowey_map[frame][PORTRAIT_WIDTH * 1 + 2]),
        x + 2, y + 1);

    VDP_setTileMapXY(
        BG_A,
        TILE_ATTR_FULL(
            pal, 0, 0, 0,
            flowey_index + portrait_flowey_map[frame][PORTRAIT_WIDTH * 1 + 3]),
        x + 3, y + 1);

    VDP_setTileMapXY(
        BG_A,
        TILE_ATTR_FULL(
            pal, 0, 0, 0,
            flowey_index + portrait_flowey_map[frame][PORTRAIT_WIDTH * 2 + 2]),
        x + 2, y + 2);

    VDP_setTileMapXY(
        BG_A,
        TILE_ATTR_FULL(
            pal, 0, 0, 0,
            flowey_index + portrait_flowey_map[frame][PORTRAIT_WIDTH * 2 + 3]),
        x + 3, y + 2);
}
