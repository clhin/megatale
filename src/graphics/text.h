#ifndef TEXT_H_
#define TEXT_H_
#include <genesis.h>

typedef enum {
    LETTER_TAIL_NONE,
    LETTER_TAIL_g,
    LETTER_TAIL_p,
    LETTER_TAIL_q,
    LETTER_TAIL_Q,
    LETTER_TAIL_comma
} LetterTail;

void draw_letter(char c, u8 x, u8 y, u16 offset, u8 plane, u8 palette,
                 LetterTail tail);
extern u8 lookup_table[75][8];
u8 *get_char_info(char c);

#endif