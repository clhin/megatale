#ifndef SAVEDATA_H_
#define SAVEDATA_H_

#define SAVE_VALID 0x42

// TODO: We should try to figure out how to bitpack this in the future,
// problem is, SRAM reads in bytes at minimum, how do we make sure the values
// get to the right places?
typedef struct savedata {
    char name[7];
    u8 love:5;
    u8 hp:6;
    u8 maxhp:6;
    u8 room;
    u8 at:6;
    u8 def:5;
    u8 kills;
    u8 weapon:6;
    u8 armor:6;
    u8 item[8];
    u8 box[20];
    u8 cell:4; // uses flags not a traditional uint_8
    u16 gold:14;
    u16 exp;
    u32 time;
} savedata_t;
#endif
