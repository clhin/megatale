#ifndef COLLISIONS_H_
#define COLLISIONS_H_
#include <genesis.h>

/* Basically just AABB to be used for sprites. The width is 1 byte
 * because I can't think of a case we would need to check for collisions for
 * anything greater than 256x256. The position is 2 bytes worth. In the case
 * that a map is >2^16 in size, we could probably change this, but this is
 * highly unoptimal (1. memory saved 2. Sega Genesis ALU needs extra
 * instructions for 32-bit integers).
 *
 * Note: x, y, w,h correspond to pixel-location and not 8x8 locations. If this
 * isn't good in the long run, optimizations can be done.
 */
extern const u8 startcollision[408];
extern const u8 maincollision[336];
extern const u8 ruins1_collision[384];
extern const u8 ruins2_collision [192];
extern const u8 ruins3_collision[432];

u8 collides(BoxCollision lhs, BoxCollision rhs);
#endif
