#include "state_test.h"
#if defined(TEST_MODE)
#include <genesis.h>
#include <resources.h>

#include "../../testing/test_textbox.h"

test_category_t categories[] = {
    {.text = ": Textbox",
     .amount = sizeof(textbox_tests) / sizeof(test_case_t),
     .tests = {textbox_tests}},  //{.text = ": World"}, //{.text = ": Sound"}
};

u8 category_selection = 0;
u8 case_selection = 0;
Sprite *heart;

void test_init(state_parameters_t args) {
    SPR_init();

    VDP_drawText("Testing Menu", 2, 0);
    VDP_drawText("A_*: Assert (no crash)", 0, 1);
    VDP_drawText("C_*: Assert (crash)", 0, 2);
    VDP_drawText("T_*: Test", 0, 3);

    u8 size = sizeof(categories) / sizeof(categories[0]);

    for (u8 i = 0; i < size; ++i) {
        VDP_drawText(categories[i].text, 1, 4 + i);
    }
    // Use the heart as the selector
    PAL_setPalette(PAL1, heart_sprite.palette->data, DMA);

    heart = SPR_addSprite(&heart_sprite, 0, (4 + category_selection) * 8,
                          TILE_ATTR(PAL1, TRUE, FALSE, FALSE));
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