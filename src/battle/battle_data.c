#include "battle_data.h"

void projectile_lerp(projectile_data_t *p, u8 speed) {
    /*
        Note that this could probably be optimized.
    */

    if (fix16ToInt(p->x) == p->end_x && fix16ToInt(p->y) == p->end_y) return;

    u16 d_x = p->end_x - p->start_x;
    u16 d_y = p->end_y - p->start_y;

    fix16 shift_x;
    fix16 shift_y;

    shift_x = intToFix16(d_x);
    shift_y = intToFix16(d_y);

    fix16 rate = intToFix16(speed);
    rate = fix16Div(rate, FIX16(256.0));

    shift_x = fix16Mul(shift_x, rate);
    shift_y = fix16Mul(shift_y, rate);

    p->x = fix16Add(p->x, shift_x);
    p->y = fix16Add(p->y, shift_y);
}