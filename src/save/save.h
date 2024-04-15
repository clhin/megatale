#ifndef SAVE_H_
#define SAVE_H_
#include <genesis.h>
#include "savedata.h"

/* Our save file, as defined in SGDK, is basically a very long 1D
   array in 2MB, here is the following structure of our data:
   Byte 0: Validation bit (make sure save isn't corrupt/garbage)
   Bytes 1-99: Save data for character, we will have some extra bytes
	       unused as we want to future proof, and we get 2 entire
	       megs of SRAM so we'll be fine.
   Bytes 100-??: Game save variables (have you visited a certain room?
		What dialog options have you picked?
		Genocide or pacifist? etc.
*/

#define NAMECHAR1 1
#define NAMECHAR2 2
#define NAMECHAR3 3
#define NAMECHAR4 4
#define NAMECHAR5 5
#define NAMECHAR6 6
#define LOVE 7
#define HP 8
#define MAXHP 9
#define ROOM 10
#define ATTACK 11
#define DEFENCE 12
#define KILLS 13
#define WEAPON 14
#define ARMOR 15
#define ITEM1 16
#define ITEM2 17
#define ITEM3 18
#define ITEM4 19
#define ITEM5 20
#define ITEM6 21
#define ITEM7 22
#define ITEM8 23
#define BOX1_1 24
#define BOX1_2 25
#define BOX1_3 26
#define BOX1_4 27
#define BOX1_5 28
#define BOX1_6 29
#define BOX1_7 30
#define BOX1_8 31
#define BOX1_9 32
#define BOX1_10 33
#define BOX2_1 34
#define BOX2_2 35
#define BOX2_3 36
#define BOX2_4 37
#define BOX2_5 38
#define BOX2_6 39
#define BOX2_7 40
#define BOX2_8 41
#define BOX2_9 42
#define BOX2_10 43
#define CELL 44
#define GOLD 45
#define EXP 47
#define TIME 49

#define FUN 100
#define FLOWEY_1ST_ENCOUNTER 101

void readsave(savedata_t *);
void writesave(savedata_t *);
#endif
