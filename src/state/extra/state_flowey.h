#ifndef STATE_FLOWEY_H_
#define STATE_FLOWEY_H_
#include "../state_manager.h"

/*
    Why have a state for flowey when we have battle?

    Flowey's battle scene modifies how the battle system works. This just saves
   us time from having to hackishly split up the battle into flowey mode (which
   happens once) and normal mode.

   ~/misc/battle/gen_battle_dialogue.py generates .bin file for dialogue, header
   and face locations. We need to move them to ~/res/battle and ~/src/battle and
   write the face const into state_flowey.c accordingly.

*/

/*
    Important usage notes:

    The following SGDK states are modified, be sure to keep this in mind when
   loading in this state and restoring it.

    - SPR_init() is called, make sure to clear your sprite engine and rebuild it
   when entering and re-exiting your state.
   - PAL2 is modified. Be sure to save it and restore it afterwards
   - PAL1 is used by this, it expects PAL1 to be set to the default palette as
   set by Chase.
   - Anything after [TILE_USER_INDEX + number of tiles in the font map] is
   potentially modified by this state, be sure to restore anything loaded after
   this.
*/

void flowey_init(state_parameters_t args);
void flowey_input(u16 changed, u16 state);
void flowey_update();
void flowey_clean();
void flowey_redraw(state_return_t);
state_return_t flowey_shutdown();

#endif