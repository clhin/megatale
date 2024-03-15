#ifndef STATE_WORLD_H_
#define STATE_WORLD_H_
#include "state_manager.h"

#define TRUE 1
#define FALSE 0

#define FRONT 0
#define FRONT_WALK 1
#define BACK 2
#define BACK_WALK 3
#define SIDE 4
#define SIDE_WALK 5

#define RIGHT_LIMIT 153
#define DOWN_LIMIT 116
#define LEFT_LIMIT 152
#define UP_LIMIT 115

void world_init(state_parameters_t args);
void world_input(u16 changed, u16 state);
void world_update();
void world_clean();
void world_redraw(state_return_t);
state_return_t world_shutdown();

#endif
