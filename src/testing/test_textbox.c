#include "test_textbox.h"
#if defined(TEST_MODE)
#include <genesis.h>
#include <resources.h>

#include "../graphics/textbox.h"
void test_textbox1_init();
void test_textbox1_input(u16, u16);
u8 test_textbox1_update();
void test_textbox1_shutdown();

void test_textbox2_init();

test_case_t textbox_tests[2] = {
    {.text = "T_Normal",
     .init = test_textbox1_init,
     .input = test_textbox1_input,
     .update = test_textbox1_update,
     .shutdown = test_textbox1_shutdown},

    {.text = "T_NoAsterisks",
     .init = test_textbox2_init,
     .input = test_textbox1_input,
     .update = test_textbox1_update,
     .shutdown = test_textbox1_shutdown},
};

u8 counter;

void test_textbox1_init() {
    PAL_setPalette(PAL1, heart_sprite.palette->data, DMA);
    u8 res = VDP_loadTileSet(&font_sheet, TILE_USER_INDEX, DMA);

    textbox_init(TEXT_DIALOGUE_MODE, DIALOGUE_OFFSET,
                 "gjpQ,pgjpQ,p\nabcdefghijk\n012345[/-]", TRUE, TRUE, TRUE);

    counter = 0;
}

void test_textbox2_init() {
    PAL_setPalette(PAL1, heart_sprite.palette->data, DMA);
    u8 res = VDP_loadTileSet(&font_sheet, TILE_USER_INDEX, DMA);
    textbox_init(TEXT_DIALOGUE_MODE, DIALOGUE_OFFSET,
                 "gjpQ,pgjpQ,p\nabcdefghijk\n012345[/-]", FALSE, FALSE, FALSE);

    counter = 0;
}

void test_textbox1_input(u16 changed, u16 state) {}
u8 test_textbox1_update() {
    u8 res = 0;
    if (counter++ >= 10) {
        counter = 0;
        res = textbox_tick();
    }

    if (res == 1) return TEST_CASE_SUCCESS;
    return TEST_CASE_CONTINUE;
}
void test_textbox1_shutdown() {}

#endif