#include "test_textbox.h"

void test_textbox1_init();
void test_textbox1_input(u16, u16);
u8 test_textbox1_update();
void test_textbox1_shutdown();

test_case_t textbox_tests[1] = {
    {.text = "T_Normal",
     .init = test_textbox1_init,
     .input = test_textbox1_input,
     .update = test_textbox1_update,
     .shutdown = test_textbox1_shutdown},
};

void test_textbox1_init() {}
void test_textbox1_input(u16 changed, u16 state) {}
u8 test_textbox1_update() { return TEST_CASE_SUCCESS; }
void test_textbox1_shutdown() {}