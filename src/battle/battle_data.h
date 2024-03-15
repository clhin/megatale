#ifndef BATTLE_DATA_H_
#define BATTLE_DATA_H_
#include <genesis.h>

/*
    Due to extra information by projectile, these should be dynamically
   allocated.
*/

typedef struct projectile_data {
    Sprite *spr;
    s16 x, y;
    s8 v_x, v_y, a_x, a_y;
} projectile_data_t;

#endif