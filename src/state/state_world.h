#ifndef STATE_WORLD_H_
#define STATE_WORLD_H_
#include "state_manager.h"

void world_init(state_parameters_t args);
void world_input(u16 changed, u16 state);
void world_update();
void world_clean();
void world_redraw();
state_return_t world_shutdown();

#endif