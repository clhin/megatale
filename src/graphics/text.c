#include "text.h"

/*
    Preprcessor aid for bit-unpacking.

    Layout of 8-byte structure:

    [0]
    - bit 7: top horizontal flip
    - bit 6: top vertical flip
    - bit 5-0: top index
    [1]
    - bit 7: middle horizontal flip
    - bit 6-0: middle index
    [2]
    - bit 7: bottom horizontal flip
    - bit 6-0: bottom index
    [3]
    - bit 7-0: g-tail top index
    [4]
    - bit 7-0: p-tail top index
    [5]
    - bit 7: q-tail horizontal flip
    - bit 6-0: q-tail index
    [6]
    - bit 7-0: Q-tail top index
    [7]
    - bit 7-0: comma-tail top index
*/

#define GET_TOP(arr) (arr[0] & 0x3F)
#define GET_TOP_VFLIP(arr) ((arr[0] >> 6) & 1)
#define GET_TOP_HFLIP(arr) (arr[0] >> 7)

#define GET_TOP_g_TAIL(arr) (arr[3])
#define GET_TOP_p_TAIL(arr) (arr[4])
#define GET_TOP_q_TAIL(arr) (arr[5] & 0x7F)
#define GET_TOP_Q_TAIL(arr) (arr[6])
#define GET_TOP_comma_TAIL(arr) (arr[7])

#define GET_q_TAIL_HFLIP(arr) (arr[5] >> 7)

#define GET_MIDDLE(arr) (arr[1] & 0x7F)
#define GET_MIDDLE_HFLIP(arr) (arr[1] >> 7)

#define GET_BOTTOM(arr) (arr[2] & 0x7F)
#define GET_BOTTOM_HFLIP(arr) (arr[2] >> 7)

void draw_letter(char letter, char above, u8 x, u8 y, u16 offset, u8 plane,
                 u8 palette) {
    const u8 *arr = get_char_info(letter);

    // Handle the top of the letter base on character
    switch (above) {
        case 'g':
        case 'j':
        case 'y':
            VDP_setTileMapXY(
                plane,
                TILE_ATTR_FULL(palette, TRUE, 0, GET_TOP_HFLIP(arr),
                               offset + GET_TOP_g_TAIL(arr)),
                x, y);
            break;
        case 'p':
            VDP_setTileMapXY(plane,
                             TILE_ATTR_FULL(palette, TRUE, 0, 0,
                                            offset + GET_TOP_p_TAIL(arr)),
                             x, y);
            break;
        case 'q':
            VDP_setTileMapXY(
                plane,
                TILE_ATTR_FULL(palette, TRUE, 0, GET_q_TAIL_HFLIP(arr),
                               offset + GET_TOP_q_TAIL(arr)),
                x, y);
            break;
        case 'Q':
            VDP_setTileMapXY(plane,
                             TILE_ATTR_FULL(palette, TRUE, 0, 0,
                                            offset + GET_TOP_Q_TAIL(arr)),
                             x, y);
            break;
        case ',':
            VDP_setTileMapXY(plane,
                             TILE_ATTR_FULL(palette, TRUE, 0, 0,
                                            offset + GET_TOP_comma_TAIL(arr)),
                             x, y);
            break;

        default:
            VDP_setTileMapXY(
                plane,
                TILE_ATTR_FULL(palette, 0, GET_TOP_VFLIP(arr),
                               GET_TOP_HFLIP(arr), offset + GET_TOP(arr)),
                x, y);
            break;
    }

    VDP_setTileMapXY(plane,
                     TILE_ATTR_FULL(palette, 0, 0, GET_MIDDLE_HFLIP(arr),
                                    offset + GET_MIDDLE(arr)),
                     x, y + 1);
    // Bottom of Letter
    VDP_setTileMapXY(plane,
                     TILE_ATTR_FULL(palette, 0, 0, GET_BOTTOM_HFLIP(arr),
                                    offset + GET_BOTTOM(arr)),
                     x, y + 2);
}

void draw_lines(const char lines[][MAX_LINE_LENGTH], u8 num, u8 x, u8 y,
                u16 offset, u8 plane, u8 palette) {
    for (u8 i = 0; i < num; ++i) {
        u8 size = strlen(lines[i]);
        // Size of line above
        u8 size_above = (i > 0) ? strlen(lines[i - 1]) : 0;
        for (u8 j = 0; j < size; ++j) {
            // \0 e.g. nothing above.
            char above = (j < size_above) ? lines[i - 1][j] : '\0';

            draw_letter(lines[i][j], above, x + j, y + i * 2, offset, BG_A,
                        PAL1);
        }
    }
}

const u8 lookup_table[76][8] = {
    {0x0, 0x5, 0x0, 0x1d, 0x1e, 0x9e, 0x3b, 0x4d},     // a
    {0x1, 0x6, 0x0, 0x52, 0x60, 0xe1, 0x77, 0x87},     // b
    {0x0, 0x7, 0x0, 0x1d, 0x1e, 0x9e, 0x3b, 0x4d},     // c
    {0x81, 0x86, 0x0, 0x52, 0x61, 0xe0, 0x78, 0x88},   // d
    {0x0, 0x8, 0x0, 0x1d, 0x1e, 0x9e, 0x3b, 0x4d},     // e
    {0x2, 0x9, 0x0, 0x53, 0x62, 0x70, 0x79, 0x89},     // f
    {0x0, 0xa, 0x1d, 0x1d, 0x1e, 0x9e, 0x3b, 0x4d},    // g
    {0x1, 0xb, 0x0, 0x52, 0x60, 0xe1, 0x77, 0x87},     // h
    {0x3, 0xc, 0x0, 0x54, 0x63, 0xe3, 0x7a, 0x8a},     // i
    {0x81, 0xd, 0x1d, 0x52, 0x61, 0xe0, 0x78, 0x88},   // j
    {0x1, 0xe, 0x0, 0x52, 0x60, 0xe1, 0x77, 0x87},     // k
    {0x4, 0xf, 0x0, 0x55, 0x64, 0xe9, 0x7b, 0x8b},     // l
    {0x0, 0x10, 0x0, 0x1d, 0x1e, 0x9e, 0x3b, 0x4d},    // m
    {0x0, 0x11, 0x0, 0x1d, 0x1e, 0x9e, 0x3b, 0x4d},    // n
    {0x0, 0x12, 0x0, 0x1d, 0x1e, 0x9e, 0x3b, 0x4d},    // o
    {0x0, 0x13, 0x1e, 0x1d, 0x1e, 0x9e, 0x3b, 0x4d},   // p
    {0x0, 0x93, 0x9e, 0x1d, 0x1e, 0x9e, 0x3b, 0x4d},   // q
    {0x0, 0x14, 0x0, 0x1d, 0x1e, 0x9e, 0x3b, 0x4d},    // r
    {0x0, 0x15, 0x0, 0x1d, 0x1e, 0x9e, 0x3b, 0x4d},    // s
    {0x3, 0x16, 0x0, 0x54, 0x63, 0xe3, 0x7a, 0x8a},    // t
    {0x0, 0x17, 0x0, 0x1d, 0x1e, 0x9e, 0x3b, 0x4d},    // u
    {0x0, 0x18, 0x0, 0x1d, 0x1e, 0x9e, 0x3b, 0x4d},    // v
    {0x0, 0x19, 0x0, 0x1d, 0x1e, 0x9e, 0x3b, 0x4d},    // w
    {0x0, 0x1a, 0x0, 0x1d, 0x1e, 0x9e, 0x3b, 0x4d},    // x
    {0x0, 0x1b, 0x1d, 0x1d, 0x1e, 0x9e, 0x3b, 0x4d},   // y
    {0x0, 0x1c, 0x0, 0x1d, 0x1e, 0x9e, 0x3b, 0x4d},    // z
    {0x1f, 0x25, 0x0, 0x56, 0x65, 0xe5, 0x7c, 0x8c},   // A
    {0x20, 0x26, 0x0, 0x57, 0x66, 0x71, 0x7d, 0x8d},   // B
    {0x1f, 0x27, 0x0, 0x56, 0x65, 0xe5, 0x7c, 0x8c},   // C
    {0x20, 0x28, 0x0, 0x57, 0x66, 0x71, 0x7d, 0x8d},   // D
    {0x21, 0x29, 0x0, 0x58, 0x67, 0xe7, 0x7e, 0x8e},   // E
    {0x21, 0x2a, 0x0, 0x58, 0x67, 0xe7, 0x7e, 0x8e},   // F
    {0x1f, 0x2b, 0x0, 0x56, 0x65, 0xe5, 0x7c, 0x8c},   // G
    {0x22, 0x25, 0x0, 0x59, 0x68, 0xe8, 0x7f, 0x8f},   // H
    {0x21, 0xf, 0x0, 0x58, 0x67, 0xe7, 0x7e, 0x8e},    // I
    {0x84, 0x2c, 0x0, 0x55, 0x69, 0xe4, 0x80, 0x90},   // J
    {0x22, 0x2d, 0x0, 0x59, 0x68, 0xe8, 0x7f, 0x8f},   // K
    {0x1, 0x2e, 0x0, 0x52, 0x60, 0xe1, 0x77, 0x87},    // L
    {0x23, 0x2f, 0x0, 0x5a, 0x6a, 0x72, 0x81, 0x91},   // M
    {0x22, 0x30, 0x0, 0x59, 0x68, 0xe8, 0x7f, 0x8f},   // N
    {0x1f, 0x31, 0x0, 0x56, 0x65, 0xe5, 0x7c, 0x8c},   // O
    {0x20, 0x32, 0x0, 0x57, 0x66, 0x71, 0x7d, 0x8d},   // P
    {0x1f, 0x31, 0x3b, 0x56, 0x65, 0xe5, 0x7c, 0x8c},  // Q
    {0x20, 0x33, 0x0, 0x57, 0x66, 0x71, 0x7d, 0x8d},   // R
    {0x1f, 0x34, 0x0, 0x56, 0x65, 0xe5, 0x7c, 0x8c},   // S
    {0x21, 0x35, 0x0, 0x58, 0x67, 0xe7, 0x7e, 0x8e},   // T
    {0x22, 0x31, 0x0, 0x59, 0x68, 0xe8, 0x7f, 0x8f},   // U
    {0x22, 0x36, 0x0, 0x59, 0x68, 0xe8, 0x7f, 0x8f},   // V
    {0x24, 0x37, 0x0, 0x5b, 0x6b, 0x73, 0x82, 0x92},   // W
    {0x22, 0x38, 0x0, 0x59, 0x68, 0xe8, 0x7f, 0x8f},   // X
    {0x22, 0x39, 0x0, 0x59, 0x68, 0xe8, 0x7f, 0x8f},   // Y
    {0x21, 0x3a, 0x0, 0x58, 0x67, 0xe7, 0x7e, 0x8e},   // Z
    {0x1f, 0x3f, 0x0, 0x56, 0x65, 0xe5, 0x7c, 0x8c},   // 0
    {0x3, 0x40, 0x0, 0x54, 0x63, 0xe3, 0x7a, 0x8a},    // 1
    {0x1f, 0x41, 0x0, 0x56, 0x65, 0xe5, 0x7c, 0x8c},   // 2
    {0x1f, 0x42, 0x0, 0x56, 0x65, 0xe5, 0x7c, 0x8c},   // 3
    {0x81, 0x43, 0x0, 0x52, 0x61, 0xe0, 0x78, 0x88},   // 4
    {0x21, 0x44, 0x0, 0x58, 0x67, 0xe7, 0x7e, 0x8e},   // 5
    {0x84, 0x45, 0x0, 0x55, 0x69, 0xe4, 0x80, 0x90},   // 6
    {0x21, 0x46, 0x0, 0x58, 0x67, 0xe7, 0x7e, 0x8e},   // 7
    {0x1f, 0x47, 0x0, 0x56, 0x65, 0xe5, 0x7c, 0x8c},   // 8
    {0x1f, 0x48, 0x0, 0x56, 0x65, 0xe5, 0x7c, 0x8c},   // 9
    {0x0, 0x3d, 0x0, 0x1d, 0x1e, 0x9e, 0x3b, 0x4d},    // .
    {0x0, 0x3d, 0x4d, 0x1d, 0x1e, 0x9e, 0x3b, 0x4d},   // ,
    {0x3, 0x49, 0x0, 0x54, 0x63, 0xe3, 0x7a, 0x8a},    // (
    {0x3, 0xc9, 0x0, 0x54, 0x63, 0xe3, 0x7a, 0x8a},    // )
    {0x0, 0x4a, 0x0, 0x1d, 0x1e, 0x9e, 0x3b, 0x4d},    // :
    {0x3c, 0x4b, 0x0, 0x5c, 0x6c, 0x74, 0x83, 0x93},   // !
    {0x5d, 0x4c, 0x0, 0x5d, 0x6d, 0xed, 0x84, 0x94},   // ?
    {0x3d, 0x4d, 0x0, 0x5e, 0x6e, 0x75, 0x85, 0x95},   // '
    {0x3e, 0x4e, 0x0, 0x5f, 0x6f, 0x76, 0x86, 0x96},   // "
    {0x0, 0x4f, 0x0, 0x1d, 0x1e, 0x9e, 0x3b, 0x4d},    // -
    {0x4, 0x50, 0x0, 0x55, 0x64, 0xe9, 0x7b, 0x8b},    // [
    {0x84, 0xd0, 0x0, 0x55, 0x69, 0xe4, 0x80, 0x90},   // ]
    {0x0, 0x0, 0x0, 0x1d, 0x1e, 0x9e, 0x3b, 0x4d},     //
    {0x81, 0x51, 0x0, 0x52, 0x61, 0xe0, 0x78, 0x88},   // /
};
/* Note: we are relying on the compiler to optimize this either by sorting
   it or by sorting it into a lookup table.

   (The least amount of optimization takes O(logn))


*/
const u8 *get_char_info(char c) {
    switch (c) {
        case 'a':
            return lookup_table[0];
            break;
        case 'b':
            return lookup_table[1];
            break;
        case 'c':
            return lookup_table[2];
            break;
        case 'd':
            return lookup_table[3];
            break;
        case 'e':
            return lookup_table[4];
            break;
        case 'f':
            return lookup_table[5];
            break;
        case 'g':
            return lookup_table[6];
            break;
        case 'h':
            return lookup_table[7];
            break;
        case 'i':
            return lookup_table[8];
            break;
        case 'j':
            return lookup_table[9];
            break;
        case 'k':
            return lookup_table[10];
            break;
        case 'l':
            return lookup_table[11];
            break;
        case 'm':
            return lookup_table[12];
            break;
        case 'n':
            return lookup_table[13];
            break;
        case 'o':
            return lookup_table[14];
            break;
        case 'p':
            return lookup_table[15];
            break;
        case 'q':
            return lookup_table[16];
            break;
        case 'r':
            return lookup_table[17];
            break;
        case 's':
            return lookup_table[18];
            break;
        case 't':
            return lookup_table[19];
            break;
        case 'u':
            return lookup_table[20];
            break;
        case 'v':
            return lookup_table[21];
            break;
        case 'w':
            return lookup_table[22];
            break;
        case 'x':
            return lookup_table[23];
            break;
        case 'y':
            return lookup_table[24];
            break;
        case 'z':
            return lookup_table[25];
            break;
        case 'A':
            return lookup_table[26];
            break;
        case 'B':
            return lookup_table[27];
            break;
        case 'C':
            return lookup_table[28];
            break;
        case 'D':
            return lookup_table[29];
            break;
        case 'E':
            return lookup_table[30];
            break;
        case 'F':
            return lookup_table[31];
            break;
        case 'G':
            return lookup_table[32];
            break;
        case 'H':
            return lookup_table[33];
            break;
        case 'I':
            return lookup_table[34];
            break;
        case 'J':
            return lookup_table[35];
            break;
        case 'K':
            return lookup_table[36];
            break;
        case 'L':
            return lookup_table[37];
            break;
        case 'M':
            return lookup_table[38];
            break;
        case 'N':
            return lookup_table[39];
            break;
        case 'O':
            return lookup_table[40];
            break;
        case 'P':
            return lookup_table[41];
            break;
        case 'Q':
            return lookup_table[42];
            break;
        case 'R':
            return lookup_table[43];
            break;
        case 'S':
            return lookup_table[44];
            break;
        case 'T':
            return lookup_table[45];
            break;
        case 'U':
            return lookup_table[46];
            break;
        case 'V':
            return lookup_table[47];
            break;
        case 'W':
            return lookup_table[48];
            break;
        case 'X':
            return lookup_table[49];
            break;
        case 'Y':
            return lookup_table[50];
            break;
        case 'Z':
            return lookup_table[51];
            break;
        case '0':
            return lookup_table[52];
            break;
        case '1':
            return lookup_table[53];
            break;
        case '2':
            return lookup_table[54];
            break;
        case '3':
            return lookup_table[55];
            break;
        case '4':
            return lookup_table[56];
            break;
        case '5':
            return lookup_table[57];
            break;
        case '6':
            return lookup_table[58];
            break;
        case '7':
            return lookup_table[59];
            break;
        case '8':
            return lookup_table[60];
            break;
        case '9':
            return lookup_table[61];
            break;
        case '.':
            return lookup_table[62];
            break;
        case ',':
            return lookup_table[63];
            break;
        case '(':
            return lookup_table[64];
            break;
        case ')':
            return lookup_table[65];
            break;
        case ':':
            return lookup_table[66];
            break;
        case '!':
            return lookup_table[67];
            break;
        case '?':
            return lookup_table[68];
            break;
        case '\'':
            return lookup_table[69];
            break;
        case '"':
            return lookup_table[70];
            break;
        case '-':
            return lookup_table[71];
            break;
        case '[':
            return lookup_table[72];
            break;
        case ']':
            return lookup_table[73];
            break;
        case ' ':
            return lookup_table[74];
            break;
        case '/':
            return lookup_table[75];
            break;
        default:
            return lookup_table[0];
            break;
    }
}
