#ifndef STATE_BATTLE_H_
#define STATE_BATTLE_H_
#include "state_manager.h"

void battle_init(state_parameters_t args);
void battle_input(u16 changed, u16 state);
void battle_update();
void battle_clean();
void battle_redraw();
state_return_t battle_shutdown();

#endif