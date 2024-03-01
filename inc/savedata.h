#ifndef SAVEDATA_H_
#define SAVEDATA_H_

#define SAVE_VALID 0x42

// TODO: We should try to figure out how to bitpack this in the future,
// problem is, SRAM reads in bytes at minimum, how do we make sure the values
// get to the right places?
typedef struct savedata {
    char name[7];
    u8 love;
    u8 hp;
    u8 maxhp;
    u8 room;
    u8 at;
    u8 def;
    u8 kills;
    u8 weapon;
    u8 armor;
    u8 item[8];
    u8 box[20];
    u8 cell;
    u8 extra;
    u16 gold;
    u16 exp;
    u32 time;
} savedata_t;
#endif
