#include "battle_data.h"

void projectile_interpolate(projectile_data_t *projectile, s16 start_x,
                            s16 start_y, s16 end_x, s16 end_y, u16 speed) {
    if (start_x == end_x && start_y == end_y) return;

    u16 d_x = end_x - start_x;
    u16 d_y = end_y - start_y;

    fix16 shift_x;
    fix16 shift_y;
    fix16 d_y;

    d_x = intToFix16(end_x - start_x);
    d_y = intToFix16(end_y - projectile->y);
}