#ifndef BATTLE_DATA_H_
#define BATTLE_DATA_H_
#include <genesis.h>

/*
    Due to extra information by projectile, these should be dynamically
   allocated.
*/
typedef struct projectile_data {
    Sprite *spr;
    f16 x, y;
    s16 start_x, start_y;
    s16 end_x, end_y;
} projectile_data_t;

/*
    Move towards a target point at a given speed.

    Uses floating point calculations in the back-end, so should be used
   liberally.
*/
void projectile_lerp(projectile_data_t *projectile, u8 speed);

#endif