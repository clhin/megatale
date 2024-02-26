#ifndef TEXT_BOX_H_
#define TEXT_BOX_H_
#include <genesis.h>

#define MAX_LINE_SIZE 30
#define MAX_TORIEL_LINE_SIZE 20
#define FONT_SHEET_WIDTH 38

#define DIALOGUE_OFFSET 19

// Hardcode Toriel as a mode because we only have one dialogue with a portrait.
typedef enum {
    TEXT_DIALOGUE_MODE,
    TEXT_BATTLE_MODE,
    TEXT_FLOWEY_MODE,
    TEXT_TORIEL_MODE
} TextBoxMode;

struct {
    /*
        I don't think there's ever a case where the third line is used and first
       two aren't or second line is used and first isn't.
    */
    u8 lines_used;
    u8 asterisks[3];

    char lines[3][MAX_LINE_SIZE + 1];
    TextBoxMode mode;

    // How many letters of the textbox have been written. <= sum(lines[0, 1, 2])
    u8 chars_written;
    u8 y_off;
    u8 x_off;

    Sprite *portrait;
} text_info;

/*
    Handler for textbox_show that also handles setting up structure for you.
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
    Clear the text from the box and supply it with more text.
*/
void textbox_flush(const char *text, u8 asterisk_one, u8 asterisk_two,
                   u8 asterisk_three);

/*
    Erase the textbox completely
*/
void textbox_close();

#endif