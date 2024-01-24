#include "collisions.h"

// Algorithm from:
// https://developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection
u8 collides(box_t lhs, box_t rhs) {
    if (lhs.x < rhs.x + rhs.w && lhs.x + lhs.w > rhs.x &&
        lhs.y < rhs.y + rhs.h && lhs.y + lhs.h > lhs.y) {
        return 1;
    } else {
        return 0;
    }
}
