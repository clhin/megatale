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
} projectile_data_t;

/*
    Move towards a target point at a given speed.

    Uses floating point calculations in the back-end, so should be used
   liberally.
*/
void projectile_interpolate(projectile_data_t *projectile, s16 start_x,
                            s16 start_y, s16 end_x, s16 end_y, u16 speed);

#endif