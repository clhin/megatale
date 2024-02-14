#include "text.h"

u8 lookup_table[74][3] = {
    {0x0, 0x5, 0x0},   {0x1, 0x6, 0x0},   {0x0, 0x7, 0x0},    {0x1, 0x86, 0x0},
    {0x0, 0x8, 0x0},   {0x2, 0x9, 0x0},   {0x0, 0xa, 0x1d},   {0x1, 0xb, 0x0},
    {0x3, 0xc, 0x0},   {0x1, 0xd, 0x1d},  {0x1, 0xe, 0x0},    {0x4, 0xf, 0x0},
    {0x0, 0x10, 0x0},  {0x0, 0x11, 0x0},  {0x0, 0x12, 0x0},   {0x0, 0x13, 0x1e},
    {0x0, 0x93, 0x9e}, {0x0, 0x14, 0x0},  {0x0, 0x15, 0x0},   {0x3, 0x16, 0x0},
    {0x0, 0x17, 0x0},  {0x0, 0x18, 0x0},  {0x0, 0x19, 0x0},   {0x0, 0x1a, 0x0},
    {0x0, 0x1b, 0x1d}, {0x0, 0x1c, 0x0},  {0x1f, 0x25, 0x0},  {0x20, 0x26, 0x0},
    {0x21, 0x27, 0x0}, {0x20, 0x28, 0x0}, {0x21, 0x29, 0x0},  {0x21, 0x2a, 0x0},
    {0x4, 0x2b, 0x0},  {0x22, 0x25, 0x0}, {0x21, 0xf, 0x0},   {0x84, 0x2c, 0x0},
    {0x22, 0x2d, 0x0}, {0x1, 0x2e, 0x0},  {0x23, 0x2f, 0x0},  {0x22, 0x30, 0x0},
    {0x1f, 0x31, 0x0}, {0x20, 0x32, 0x0}, {0x1f, 0x31, 0x3b}, {0x20, 0x33, 0x0},
    {0x21, 0x34, 0x0}, {0x1f, 0x35, 0x0}, {0x22, 0x31, 0x0},  {0x22, 0x36, 0x0},
    {0x24, 0x37, 0x0}, {0x22, 0x38, 0x0}, {0x22, 0x39, 0x0},  {0x1f, 0x3a, 0x0},
    {0x1f, 0x3f, 0x0}, {0x3, 0x40, 0x0},  {0x1f, 0x41, 0x0},  {0x1f, 0x42, 0x0},
    {0x81, 0x43, 0x0}, {0x21, 0x44, 0x0}, {0x84, 0x45, 0x0},  {0x21, 0x46, 0x0},
    {0x1f, 0x47, 0x0}, {0x1f, 0x48, 0x0}, {0x0, 0x3d, 0x0},   {0x0, 0x3d, 0x4d},
    {0x1f, 0x49, 0x0}, {0x1f, 0xc9, 0x0}, {0x0, 0x4a, 0x0},   {0x3c, 0x4b, 0x0},
    {0x5d, 0x4e, 0x0}, {0x3d, 0x4d, 0x0}, {0x3e, 0x4e, 0x0},  {0x0, 0x4f, 0x0},
    {0x4, 0x50, 0x0},  {0x84, 0xd0, 0x0},
};

u8 *get_char_info(char c) {
    switch (c) {
        case 97:
            return lookup_table[0];
            break;
        case 98:
            return lookup_table[1];
            break;
        case 99:
            return lookup_table[2];
            break;
        case 100:
            return lookup_table[3];
            break;
        case 101:
            return lookup_table[4];
            break;
        case 102:
            return lookup_table[5];
            break;
        case 103:
            return lookup_table[6];
            break;
        case 104:
            return lookup_table[7];
            break;
        case 105:
            return lookup_table[8];
            break;
        case 106:
            return lookup_table[9];
            break;
        case 107:
            return lookup_table[10];
            break;
        case 108:
            return lookup_table[11];
            break;
        case 109:
            return lookup_table[12];
            break;
        case 110:
            return lookup_table[13];
            break;
        case 111:
            return lookup_table[14];
            break;
        case 112:
            return lookup_table[15];
            break;
        case 113:
            return lookup_table[16];
            break;
        case 114:
            return lookup_table[17];
            break;
        case 115:
            return lookup_table[18];
            break;
        case 116:
            return lookup_table[19];
            break;
        case 117:
            return lookup_table[20];
            break;
        case 118:
            return lookup_table[21];
            break;
        case 119:
            return lookup_table[22];
            break;
        case 120:
            return lookup_table[23];
            break;
        case 121:
            return lookup_table[24];
            break;
        case 122:
            return lookup_table[25];
            break;
        case 65:
            return lookup_table[26];
            break;
        case 66:
            return lookup_table[27];
            break;
        case 67:
            return lookup_table[28];
            break;
        case 68:
            return lookup_table[29];
            break;
        case 69:
            return lookup_table[30];
            break;
        case 70:
            return lookup_table[31];
            break;
        case 71:
            return lookup_table[32];
            break;
        case 72:
            return lookup_table[33];
            break;
        case 73:
            return lookup_table[34];
            break;
        case 74:
            return lookup_table[35];
            break;
        case 75:
            return lookup_table[36];
            break;
        case 76:
            return lookup_table[37];
            break;
        case 77:
            return lookup_table[38];
            break;
        case 78:
            return lookup_table[39];
            break;
        case 79:
            return lookup_table[40];
            break;
        case 80:
            return lookup_table[41];
            break;
        case 81:
            return lookup_table[42];
            break;
        case 82:
            return lookup_table[43];
            break;
        case 83:
            return lookup_table[44];
            break;
        case 84:
            return lookup_table[45];
            break;
        case 85:
            return lookup_table[46];
            break;
        case 86:
            return lookup_table[47];
            break;
        case 87:
            return lookup_table[48];
            break;
        case 88:
            return lookup_table[49];
            break;
        case 89:
            return lookup_table[50];
            break;
        case 90:
            return lookup_table[51];
            break;
        case 48:
            return lookup_table[52];
            break;
        case 49:
            return lookup_table[53];
            break;
        case 50:
            return lookup_table[54];
            break;
        case 51:
            return lookup_table[55];
            break;
        case 52:
            return lookup_table[56];
            break;
        case 53:
            return lookup_table[57];
            break;
        case 54:
            return lookup_table[58];
            break;
        case 55:
            return lookup_table[59];
            break;
        case 56:
            return lookup_table[60];
            break;
        case 57:
            return lookup_table[61];
            break;
        case 46:
            return lookup_table[62];
            break;
        case 44:
            return lookup_table[63];
            break;
        case 40:
            return lookup_table[64];
            break;
        case 41:
            return lookup_table[65];
            break;
        case 58:
            return lookup_table[66];
            break;
        case 33:
            return lookup_table[67];
            break;
        case 63:
            return lookup_table[68];
            break;
        case 39:
            return lookup_table[69];
            break;
        case 34:
            return lookup_table[70];
            break;
        case 45:
            return lookup_table[71];
            break;
        case 91:
            return lookup_table[72];
            break;
        case 93:
            return lookup_table[73];
            break;
        default:
            return lookup_table[0];
            break;
    }
}