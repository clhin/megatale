#ifndef TEXT_BOX_H_
#define TEXT_BOX_H_
#include <genesis.h>

#define MAX_LINE_SIZE 30
#define MAX_TORIEL_LINE_SIZE 20
#define FONT_SHEET_WIDTH 38

#define TEXT_DIALOGUE_OFFSET 20

// Hardcode Toriel as a mode because we only have one dialogue with a portrait.
typedef enum {
    TEXT_DIALOGUE_MODE,
    TEXT_BATTLE_MODE,
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

    // How many letters of the textbox have been written.
    u8 chars_written;

} text_info;

/*
    Show the textbox
*/
void textbox_show(TextBoxMode mode);

/*
    Update the textbox if its in an animated mode of talking.

    Return value is 1 if the textbox is "done" animating.

*/
u8 textbox_tick();

/*
    Update the textbox
*/
void textbox_flush();

/*
    Erase the textbox
*/
void textbox_clear();

#endif