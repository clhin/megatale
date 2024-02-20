#include "../../globals.h"
#if !defined(STATE_TEST_H_) && defined(TEST_MODE)
#define STATE_TEST_H_
#include "../state_manager.h"

typedef struct test_case {
    void (*init)(void);
    void (*input)(u16, u16);
    u8 (*update)(void);
} test_case_t;

typedef struct test_category {
    const char* text;
    u8 amount;
    test_case_t* tests;
} test_category_t;

void test_init(state_parameters_t args);
void test_input(u16 changed, u16 state);
void test_update();
void test_clean();
void test_redraw(state_return_t);
state_return_t test_shutdown();

#endif
