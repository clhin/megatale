#ifndef STATE_MANAGER_H_
#define STATE_MANAGER_H_
#include <types.h>

#define MAX_STATES 3

/* If we need to pass any state-specific information, we do it with this void
 * ptr. Consider a battle state, we need to pass what enemies will be there.
 */
typedef struct state_parameters {
    void *parameter_data;
} state_parameters_t;

/* When we're done with the state we give any specific information that might be
 * useful.
 */
typedef struct state_return {
    void *return_data;
} state_return_t;

/* Per-state info. Functions for the game to call.
 * init: Initializes everything needs it and loads it into the world.
 * update: Pre-draw call check
 * clean: When another state is added, everything needs to be momentarily
 * cleared only to be restored later, this does that.
 * redraw: When coming back to this state, redraw everything you previously got
 * rid of. state_return_t is given back from the previous state's shutdown.
 * shutdown: Finish, the state_return_t variable just gives some possible info
 * needed by preceding state.
 *
 */
typedef struct state_info {
    void (*init)(state_parameters_t);
    void (*input)(u16, u16);
    void (*update)(void);
    void (*clean)(void);
    void (*redraw)(state_return_t);
    state_return_t (*shutdown)(void);
} state_info_t;

/* Main difference between them is that state_push functions like a stack, it'll
 * push a state ontop of another, so that you can return to it when you're done.
 * State replace, on the other hand, replaces the state on top. This is useful
 * for when the player loses a battle and the game over state essentially
 * 'overwrites' the battle state.
 *
 * Note that clean is not called alongside shutdown, clean should be used in
 * shutdown. Keep this in mind for future reference.
 */
void state_push(state_info_t state, state_parameters_t args);
void state_replace(state_info_t state, state_parameters_t args);
void state_pop();
state_info_t *state_top();

#endif
