#ifndef TEXT_H_
#define TEXT_H_
#include <genesis.h>

/*
    Text functionality. Since undertale font is not bitmap (i.e. fits on 8x8
   pixel chunks), we have to handle letters with tails such as g or y that
   intersect with letters under it. This handles it.

    The hex data located in text.c is generated by ~/generate_lookup.py and
   copy-pasted here.

    ~/res/font_sheet.png is compressed to account for duplicate tiles with
   additional consideration for vertical and horizontal tiles. This was manually
   done by hand, further additions to ~/res/font_sheet.png in terms of
   alphanumeric position is highly discouraged thereof.

*/

/*

  * ----------- *
  |  IMPORTANT  |
  * ----------- *

  Font sheet must be loaded into VRAM, right on TILE_USER_INDEX, before doing
  any of these functions. This is presumed to be called at the start at the
  game, otherwise it will be buggy. This can be done with 
  "VDP_loadTileSet(&font_sheet, TILE_USER_INDEX, DMA);" with <resources.h> included

*/

#define MAX_LINE_LENGTH 33

/* draw_letter(...)

    Basically draws a letter onto screen with the specified parameters.

    - letter: Which ascii character to draw (doesn't account for all, only ones
   undertale takes account of)
    - above: Which ascii character is above this one. This is for tails. Put
   '\0' if none are above.
    - x: head-tile position
    - y: head-tile position
    - offset: Where into the tileset vram is the font tileset starting?
    - plane: What plane to draw it on? Default should be BG_A
    - palette: Which palette to use?
*/
void draw_letter(char letter, char above, u8 x, u8 y, u16 offset, u8 plane,
                 u8 palette);

/*
    Abstraction for draw_letter that draws multiple lines of at max 32
   characters (33 including \0) and handles having to deal with letters above.

    Note that this does not handle cleaning, this has to be done by the user.

    - lines: An array of n-size supporting 33-size buf character arrays.

   Example input:

   char str[2][MAX_LINE_LENGTH] = {"Hello World!", "This is SGDK."};

    - nums: The amount of lines used in variable "lines."
    - x: The top-left location starting from head-position of first
   letter/whitespace.
    - y: ^
    - offset: Where into the tileset vram is the font tileset starting?
    - plane: What plane to draw it on? Default should be BG_A
    - palette: Which palette to use?


*/
void draw_lines(const char lines[][MAX_LINE_LENGTH], u8 num, u8 x, u8 y,
                u16 offset, u8 plane, u8 palette);

/* get_char_info(...)

    Letter data correlating with ascii characters is stored in a 2-d array,
   return which array contains the information.

    - c: which ascii character to draw
*/
const u8 *get_char_info(char c);

#endif
