#ifndef STATE_GMENU_H_
#define STATE_GMENU_H_
#include "state_manager.h"

void gamemenu_init(state_parameters_t args);
void gamemenu_input(u16 changed, u16 state);
void gamemenu_update();
void gamemenu_clean();
void gamemenu_redraw(state_return_t);
state_return_t gamemenu_shutdown();

#endif
