#include "state_test.h"
#if defined(TEST_MODE)

#include <genesis.h>

test_category_t categories[] = {
    {.text = ": Textbox"}, {.text = ": World"}, {.text = ": Sound"}};

void test_init(state_parameters_t args) {
    VDP_drawText("Testing Menu", 2, 0);
    VDP_drawText("A_*: Assert (no crash)", 0, 1);
    VDP_drawText("C_*: Assert (crash)", 0, 2);
    VDP_drawText("T_*: Test (one way)", 0, 3);

    u8 size = sizeof(categories) / sizeof(categories[0]);

    for (u8 i = 0; i < size; ++i) {
        VDP_drawText(categories[i].text, 1, 4 + i);
    }
}
void test_input(u16 changed, u16 state) {}
void test_update() {}
void test_clean() { VDP_clearTextArea(0, 0, 40, 28); }
void test_redraw(state_return_t ret) {}
state_return_t test_shutdown() {
    state_return_t ret;
    return ret;
}

#endif