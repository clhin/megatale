#ifndef STATE_INTRO_H_
#define STATE_INTRO_H_
#include "state_manager.h"
#include <genesis.h>

void intro_helper(u8,u16,u16,const MapDefinition, const TileSet);
void intro_init(state_parameters_t args);
void intro_input(u16 changed, u16 state);
void intro_update();
void intro_clean();
void intro_redraw(state_return_t);
state_return_t intro_shutdown();

#endif
