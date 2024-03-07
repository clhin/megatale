#include "level.h"
#include <resources.h>
Map* loadlevel(int8_t roomcode, u16 ind) {
    Map * map;
    u16 tmp = ind;
    switch (roomcode) {
	case 0:
    	    PAL_setPalette(PAL0, ruinspal.data,DMA);
    	    VDP_loadTileSet(&room_1_tiles, ind, DMA);
    	    ind += room_1_tiles.numTile;
    	    map = MAP_create(&room_1, BG_B, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, tmp));
    	    PAL_fadeInPalette(PAL0, ruinspal.data, 15, 1);
	    break;
	case 1:
	    PAL_setPalette(PAL0, ruinspal.data,DMA);
            VDP_loadTileSet(&room_main_tiles, ind, DMA);
            ind += room_main_tiles.numTile;
            map = MAP_create(&room_main, BG_B, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, tmp));
            PAL_fadeInPalette(PAL0, ruinspal.data, 15, 1);
	    break;
    }
    return map;
}
