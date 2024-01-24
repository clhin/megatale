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

void state_replace(state_info_t state, state_parameters_t args) {}

state_info_t *state_top() {
    if (state_on == 0) return 0;

    return &game_states[state_on - 1];
}