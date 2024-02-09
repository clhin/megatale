#ifndef TEXT_BOX_H_
#define TEXT_BOX_H_
#include <genesis.h>

#define MAX_LINE_SIZE 30

struct {
    /*
        I don't think there's ever a case where the third line is used and first
       two aren't or second line is used and first isn't.
    */
    u8 lines_used;
    u8 asterisks[3];

    char lines[3][MAX_LINE_SIZE + 1];

} text_info;

/*
    Update the textbox
*/
void textbox_flush();

/*
    Erase the textbox
*/
void textbox_clear();

#endif