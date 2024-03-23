#include "level.h"
#include <resources.h>

extern short levelxlimit, levelylimit;
extern short frisk_x, frisk_y;

Map* loadlevel(u8 prevroom, u8 nextroom, u16 ind) {
    Map * map;
    u16 tmp = ind;
    switch (nextroom) {
	case 0:
	    levelxlimit = 680;
	    levelylimit = 240;
    	    VDP_loadTileSet(&room_1_tiles, ind, DMA);
//    	    ind += room_1_tiles.numTile;
    	    map = MAP_create(&room_1, BG_B, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, tmp));
	    if (nextroom < prevroom) {
	    	frisk_x = 610;
            	frisk_y = 140;
	    } else {
		frisk_x = 140;
		frisk_y = 108;
	    }
    	    PAL_fadeInAll(ruinspal.data, 15, 1);
	    break;
	case 1:
	    levelxlimit = 320;
	    levelylimit = 416;
            VDP_loadTileSet(&room_main_tiles, ind, DMA);
//          ind += room_main_tiles.numTile;
            map = MAP_create(&room_main, BG_B, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, tmp));
//	    MAP_scrollTo(map,0,0);
//	    waitMs(2000);
	    if (nextroom > prevroom) {
		frisk_x = 152;
		frisk_y = 376;//168;
	    } else {
		frisk_x = 152;
		frisk_y = 168;
	    }
            PAL_fadeInAll(ruinspal.data, 15, 1);
	    break;
	case 2:
	    levelxlimit = 320;
	    levelylimit = 480;
            VDP_loadTileSet(&room_ruins1_tiles, ind, DMA);
	    map = MAP_create(&room_ruins1, BG_B, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, tmp));
	    if (nextroom > prevroom) {
	    	frisk_x = 150;
            	frisk_y = 420;//420;
	    } else {
		frisk_x = 156;
		frisk_y = 110;
	    }
            PAL_fadeInAll(ruinspal.data, 15, 1);
	    break;
	case 3:
	    levelxlimit = 320;
	    levelylimit = 240;
	    VDP_loadTileSet(&room_ruins2_tiles, ind, DMA);
	    map = MAP_create(&room_ruins2, BG_B, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, tmp));
	    if (nextroom > prevroom) {
	    	frisk_x = 152;
            	frisk_y = 160;
	    } else {
		frisk_x = 136;
		frisk_y = 80;
	    }
	    PAL_fadeInAll(ruinspal.data, 15, 1);
	    break;
    }
    return map;
}
