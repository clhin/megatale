#include "state_manager.h"

static state_info_t game_states[MAX_STATES];
static uint32_t state_on = 0;

void state_push(state_info_t state, state_parameters_t args) {
    if (state_on == MAX_STATES) {
        return;
    }

    if (state_on > 0) {
        game_states[0].clean();
    }
    game_states[state_on] = state;
    game_states[state_on].init(args);

    state_on++;
}

void state_replace(state_info_t state, state_parameters_t args) {
    if (state_on == 0) {  // if there's no state on top just push instead.
        state_push(state, args);
        return;
    }

    state_top()->shutdown();
    game_states[state_on - 1] = state;
    game_states[state_on - 1].init(args);
}

void state_pop() {
    if (state_on == 0) return;

    state_info_t *top = state_top();
    state_return_t ret = top->shutdown();

    if (--state_on == 0) return;
    state_top()->redraw(ret);
}

state_info_t *state_top() {
    if (state_on == 0) return 0;

    return &game_states[state_on - 1];
}