#include "state_test.h"
#if defined(TEST_MODE)
#include <genesis.h>
#include <resources.h>

#include "../../testing/test_textbox.h"

test_category_t categories[] = {
    {.text = ": Textbox",
     .amount = 0,
     .tests = {textbox_tests}},  //{.text = ": World"}, //{.text = ": Sound"}
};

u8 at_category = TRUE;
u8 running_test = FALSE;

u8 category_selection = 0;
u8 case_selection = 0;
Sprite *test_heart;

void test_init(state_parameters_t args) {
    categories[0].amount = 2;

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

    test_heart = SPR_addSprite(&heart_sprite, 0, (4 + category_selection) * 8,
                               TILE_ATTR(PAL1, TRUE, FALSE, FALSE));
}
void test_input(u16 changed, u16 state) {
    if (running_test) {
        test_case_t *cases = categories[category_selection].tests;
        cases[case_selection].input(changed, state);
        return;
    }

    if ((changed & BUTTON_DOWN) && (state & BUTTON_DOWN) && at_category) {
        category_selection = (category_selection + 1) %
                             (sizeof(categories) / sizeof(categories[0]));

        SPR_setPosition(heart, 0, (4 + category_selection) * 8);
    } else if ((changed & BUTTON_DOWN) && (state & BUTTON_DOWN)) {
        case_selection =
            (case_selection + 1) % categories[category_selection].amount;
        SPR_setPosition(test_heart, 0, (4 + case_selection) * 8);
    }

    if (changed & BUTTON_A && state & BUTTON_A && at_category) {
        VDP_clearTextArea(0, 4, 40, 28);

        test_case_t *cases = categories[category_selection].tests;
        u8 size = categories[category_selection].amount;

        for (u8 i = 0; i < size; ++i) {
            VDP_drawText(cases[i].text, 1, 4 + i);
        }
        SPR_setPosition(test_heart, 0, (4 + case_selection) * 8);

        at_category = FALSE;
    } else if (changed & BUTTON_B && state & BUTTON_B && !at_category) {
        VDP_clearTextArea(0, 4, 40, 28);

        u8 size = sizeof(categories) / sizeof(categories[0]);

        for (u8 i = 0; i < size; ++i) {
            VDP_drawText(categories[i].text, 1, 4 + i);
        }
        SPR_setPosition(test_heart, 0, (4 + category_selection) * 8);

        at_category = TRUE;
    } else if (changed & BUTTON_A && state & BUTTON_A && !at_category) {
        running_test = TRUE;

        test_case_t *cases = categories[category_selection].tests;
        SPR_setVisibility(test_heart, HIDDEN);
        VDP_clearTextArea(0, 4, 40, 28);
        cases[case_selection].init();
    }
}
void test_update() {
    if (running_test) {
        test_case_t *cases = categories[category_selection].tests;
        u8 result = cases[case_selection].update();

        if (result != TEST_CASE_CONTINUE) {
            running_test = FALSE;
            cases[case_selection].shutdown();

            VDP_clearTextArea(0, 4, 40, 28);

            test_case_t *cases = categories[category_selection].tests;
            u8 size = categories[category_selection].amount;

            for (u8 i = 0; i < size; ++i) {
                VDP_drawText(cases[i].text, 1, 4 + i);
            }
            SPR_setVisibility(test_heart, VISIBLE);
            SPR_setPosition(test_heart, 0, (4 + case_selection) * 8);
        }
    }
}
void test_clean() { VDP_clearTextArea(0, 0, 40, 28); }
void test_redraw(state_return_t ret) {}
state_return_t test_shutdown() {
    state_return_t ret;
    return ret;
}

#endif
