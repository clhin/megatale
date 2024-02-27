#include "level.h"
#include <resources.h>
Map* loadlevel(int8_t roomcode, u16 ind) {
    Map * map;
    u16 tmp = ind;
    PAL_setPalette(PAL0, ruinspal.data,DMA);
    VDP_loadTileSet(&room_one, ind, DMA);
    ind += room_one.numTile;
map = MAP_create(&room_1, BG_B, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, tmp));
    PAL_fadeInPalette(PAL0, ruinspal.data, 15, 1);
    return map;
}
