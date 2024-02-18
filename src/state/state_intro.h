#ifndef STATE_INTRO_H_
#define STATE_INTRO_H_
#include "state_manager.h"

void intro_init(state_parameters_t args);
void intro_input(u16 changed, u16 state);
void intro_update();
void intro_clean();
void intro_redraw(state_return_t);
state_return_t intro_shutdown();

#endif