#ifndef PORTRAIT_H_
#define PORTRAIT_H_
#include <genesis.h>

#define PORTRAIT_WIDTH 6
#define PORTRAIT_HEIGHT 5

extern u8 portrait_flowey_map[2][PORTRAIT_WIDTH * PORTRAIT_HEIGHT];

u8 portrait_flowey_loadtiles(u16 index);
void portrait_flowey_draw(u8 x, u8 y, u8 pal);
void portrait_flowey_animate(u8 x, u8 y, u8 pal, u8 frame);

#endif