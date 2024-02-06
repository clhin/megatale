#ifndef TEXT_BOX_H_
#define TEXT_BOX_H_
#include "genesis.h"

#define MAX_LINE_SIZE 30

struct {
    union {
        struct {
            u8 asterisk_one : 1;
            u8 asterisk_two : 1;
            u8 asterisk_three : 1;

            u8 line_one : 1;
            u8 line_two : 1;
            u8 line_three : 1;

            u8 box_size : 2;
        };

        u8 data;
    } parameters;

    char line_one[MAX_LINE_SIZE + 1];
    char line_two[MAX_LINE_SIZE + 1];
    char line_three[MAX_LINE_SIZE + 1];

} text_info;

#endif