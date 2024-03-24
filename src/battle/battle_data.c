#include "battle_data.h"

void projectile_lerp(projectile_data_t *p, u8 slowdown) {
    /*
        Note that this could probably be optimized.
    */

    if (p->x == p->end_x && p->y == p->end_y) return;
    s16 d_x = (p->end_x - p->start_x) / slowdown;
    s16 d_y = (p->end_y - p->start_y) / slowdown;

    if ((p->x + d_x > p->end_x && d_x > 0) ||
        (p->x + d_x < p->end_x && d_x < 0)) {
        p->x = p->end_x;
    } else {
        p->x += d_x;
    }

    if ((p->y + d_y > p->end_y && d_y > 0) ||
        (p->y + d_y < p->end_y && d_y < 0)) {
        p->y = p->end_y;
    } else {
        p->y += d_y;
    }
}

u8 circles_collide(s16 l_x, s16 l_y, s16 l_r, s16 r_x, s16 r_y, s16 r_r) {
    s16 d_x = r_x - l_x;
    s16 d_y = r_y - l_y;

    s16 limit = r_r + l_r;

    if ((d_x * d_x) + (d_y * d_y) < (limit * limit)) return 1;
    return 0;
}