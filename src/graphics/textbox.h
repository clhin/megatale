#ifndef TEXT_BOX_H_
#define TEXT_BOX_H_
#include <genesis.h>

#define MAX_LINE_SIZE 30
#define MAX_TORIEL_LINE_SIZE 20
#define FONT_SHEET_WIDTH 38

#define DIALOGUE_OFFSET 19
// The dialogue box for flowey is on the top...
#define FLOWEY_OFFSET 2

/*
    Pipeline flow:

    When you want a textbox to pop up,

    1. call textbox_init() (or fill the elements it does and call
   textbox_show())
    2. Then call textbox_tick(), it will return 1 once the dialogue is finished,
   0 otherwise.
    3. Once 1 is returned, do textbox_flush() if you want another set of
   dialogue to appear.
    4. Go back to step 2. and keep repeating 2.->3. until the dialogue is
   finished, then call textbox_close()
*/

typedef enum {
    TEXT_DIALOGUE_MODE,
    TEXT_BATTLE_MODE,
    TEXT_FLOWEY_MODE
} TextBoxMode;

struct {
    /*
        How much lines are used. This is automatically filled by textbox_init()
       or textbox_flush(). This gives indication on how big the dialogue box
       should be (This is ignored in TEXT_FLOWEY_MODE or TEXT_TORIEL_MODE).
    */
    u8 lines_used;

    /*
        Asterisks to enable. They are written when text appears on the line. In
       the case the dialogue box is only 1-2 lines, the asterisks on omitted
       lines are ignored.
    */
    u8 asterisks[3];

    /*
        Line buffer data.
    */
    char lines[3][MAX_LINE_SIZE + 1];
    TextBoxMode mode;

    // How many letters of the textbox have been written. <= sum(lines[0, 1, 2])
    u8 chars_written;
    /*
        Offset positions.

        Note: They are the position of the text, not the entire box. Thus the
       top border is y_off - 1, the asterisks are x_off - 2 and x_off - 1 and
       the left border is x_off - 3.

       The offset for x_off is for when we want to insert dialogue portraits and
       the offset for y_off is when we want the dialogue box to be in different
       locations (consider flowey's dialogue which appears on the top).
    */
    u8 y_off;
    u8 x_off;

    Sprite *portrait;
} text_info;

/*
    Helper function to draw a box with these specifics
*/
void box_draw(u8 x, u8 y, u8 w, u8 h, u8 pal);

/*
    Handler for textbox_show that also handles setting up structure for you. You
   give it the text with newline seperation and it'll fill it for you and call
   textbox_show().
*/
void textbox_init(TextBoxMode mode, u8 y_off, const char *text, u8 asterisk_one,
                  u8 asterisk_two, u8 asterisk_three);

/*
    Show the textbox. Before you call this function, you should set the
   values of "lines," "lines_used" and "asterisks" to initialize the
   textbox.
*/
void textbox_show(TextBoxMode mode);

/*
    Update the textbox if its in an animated mode of talking.

    Return value is 1 if the textbox is "done" animating.

*/
u8 textbox_tick();

/*
    Clear the text from the box and supply it with more text. Continue to call
   textbox_tick() to progress the dialogue.
*/
void textbox_flush(const char *text, u8 asterisk_one, u8 asterisk_two,
                   u8 asterisk_three);

/*
    Erase the textbox completely
*/
void textbox_close();

#endif