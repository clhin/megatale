#include "level.h"
#include <resources.h>

extern short levelxlimit, levelylimit;
extern short frisk_x, frisk_y;

Map* loadlevel(u8 roomcode, u16 ind) {
    Map * map;
    u16 tmp = ind;
    switch (roomcode) {
	case 0:
	    levelxlimit = 680;
	    levelylimit = 240;
    	    PAL_setPalette(PAL0, ruinspal.data,DMA);
    	    VDP_loadTileSet(&room_1_tiles, ind, DMA);
    	    ind += room_1_tiles.numTile;
    	    map = MAP_create(&room_1, BG_B, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, tmp));
	    frisk_x = 610;
            frisk_y = 150;
    	    PAL_fadeInAll(ruinspal.data, 15, 1);
	    break;
	case 1:
	    levelxlimit = 320;
	    levelylimit = 416;
	    PAL_setPalette(PAL0, ruinspal.data,DMA);
            VDP_loadTileSet(&room_main_tiles, ind, DMA);
            ind += room_main_tiles.numTile;
            map = MAP_create(&room_main, BG_B, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, tmp));
//	    MAP_scrollTo(map,0,0);
//	    waitMs(2000);
	    frisk_x = 140;
	    frisk_y = 200;
            PAL_fadeInAll(ruinspal.data, 15, 1);
	    break;
    }
    return map;
}
