#ifndef STATE_MENU_H_
#define STATE_MENU_H_
#include "state_manager.h"

void menu_init(state_parameters_t args);
void menu_input(u16 changed, u16 state);
void menu_update();
void menu_clean();
void menu_redraw(state_return_t);
state_return_t menu_shutdown();



#endif