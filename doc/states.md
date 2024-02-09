
## Idea

We want to abstract different parts of the game into their own 'containers' and only allow them to communicate when creating new ones, where information would need to be passed.

Example: Consider the menu of Undertale sending you to the world map, we don't want these to be differentiated by if-else blocks and instead be seperated from eachother except when the menu "passes" information to the world.

Solution: State manager that words akin to a stack.

States can "replace" themselves and also push ontop of themselves, by pushing, whatever is ontop gets popped and it redirects back to the state before it.

For an example of replacing, look at undertale intro, where it'll play the intro and then cut to the menu. The intro essentially replaces itself with the menu. Also consider the game over screen during battles.

For pushing, consider being in the menu and going into the world, you still want to go back to the menu. Also consider finishing battles, you still want to go to the same world.

We can accomplish this process by making a struct which contains function pointers of events processing each one of these states associated with their own files.

These functions need to be accounted for

- Initialization of state, `void state_init(state_parameters_t args)`
- State input, `void input(u16 changed, u16 state)`
- State update, `void update()`
- State clean, `void clean()`
- State redraw, `void redraw()`
- State shutdown, `state_return_t shutdown()`

Explanation:

Initialization is what's called as we go into the state, the struct `state_parameters_t` provides as a method to allow for previous states or `main.c` to pass information into the state its initializing, consider the world state telling the battle state which monsters need to be placed. It is a void pointer that could be casted to a struct allcoated by `MEM_alloc`.

Input is whats called when the user presses buttons, see defines `BUTTON_%`

Update is what's called per-update cycle.

Clean is whats called when you add a state ontop of this one, it wipes any usage of sprites and also clears text. This is to save memory and because of how the Sega Genesis sprite and text engine works.

When we are coming back to the state after the one we pushed on is done, redraw is the one that is called to restore what is cleared. It takes the possible return value of whatever is on top.

Shutdown is called on a pop on the state manager. Deallocate whatever you use, preferrably by calling clean. (**COULD HANDLE THIS IN STATE MANAGEMENT BUT THIS IS LEFT TO DEV**)
