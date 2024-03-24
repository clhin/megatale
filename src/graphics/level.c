#include "level.h"
#include <resources.h>

extern short levelxlimit, levelylimit;
extern short frisk_x, frisk_y;


// Note: level loads need to have asyncronous fading as the MAP_scrollTo call is in the
// camera movement function
Map* loadlevel(u8 prevroom, u8 nextroom, u16 ind) {
    Map * map;
    u16 tmp = ind;
    u16 palettebuf[64];
    switch (nextroom) {
	case 0:
	    levelxlimit = 680;
	    levelylimit = 240;
    	    VDP_loadTileSet(&room_1_tiles, ind, DMA);
    	    map = MAP_create(&room_1, BG_B, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, tmp));
	    if (nextroom < prevroom) {
	    	frisk_x = 610;
            	frisk_y = 140;
	    } else {
		frisk_x = 140;
		frisk_y = 108;
	    }
    	    memcpy(&palettebuf[0], ruinspal.data, 16*2);
	    memcpy(&palettebuf[16], heart_sprite.palette->data, 16*2);
	    PAL_fadeInAll(palettebuf, 15, TRUE);
	    break;
	case 1:
	    levelxlimit = 320;
	    levelylimit = 416;
            VDP_loadTileSet(&room_main_tiles, ind, DMA);
            map = MAP_create(&room_main, BG_B, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, tmp));
	    if (nextroom > prevroom) {
		frisk_x = 152;
		frisk_y = 376;//168;
	    } else {
		frisk_x = 152;
		frisk_y = 168;
	    }
	    memcpy(&palettebuf[0], ruinspal.data, 16*2);
            memcpy(&palettebuf[16], heart_sprite.palette->data, 16*2);
            PAL_fadeInAll(palettebuf, 15, TRUE);
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
	    memcpy(&palettebuf[0], ruinspal.data, 16*2);
	    memcpy(&palettebuf[16], heart_sprite.palette->data, 16*2);
	    palettebuf[3] = RGB24_TO_VDPCOLOR(0xA098EB);
	    PAL_fadeInAll(palettebuf, 15, TRUE);
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
	    memcpy(&palettebuf[0], ruinspal.data, 16*2);
            memcpy(&palettebuf[16], heart_sprite.palette->data, 16*2);
            palettebuf[3] = RGB24_TO_VDPCOLOR(0xA098EB);
            PAL_fadeInAll(palettebuf, 15, TRUE);
	    break;
    }
    return map;
}
