#include "save.h"

void readsave(savedata_t *save) {
    if (save == NULL)
	return;
    save->name[0] = SRAM_readByte(1);
    save->name[1] = SRAM_readByte(2);
    save->name[2] = SRAM_readByte(3);
    save->name[3] = SRAM_readByte(4);
    save->name[4] = SRAM_readByte(5);
    save->name[5] = SRAM_readByte(6);
    save->name[6] = '\0';
    save->love = SRAM_readByte(7);
    save->hp = SRAM_readByte(8);
    save->maxhp = SRAM_readByte(9);
    save->room = SRAM_readByte(10);
    save->at = SRAM_readByte(11);
    save->def = SRAM_readByte(12);
    save->kills = SRAM_readByte(13);
    save->weapon = SRAM_readByte(14);
    save->armor = SRAM_readByte(15);
    save->item[0] = SRAM_readByte(16);
    save->item[1] = SRAM_readByte(17);
    save->item[2] = SRAM_readByte(18);
    save->item[3] = SRAM_readByte(19);
    save->item[4] = SRAM_readByte(20);
    save->item[5] = SRAM_readByte(21);
    save->item[6] = SRAM_readByte(22);
    save->item[7] = SRAM_readByte(23);
    save->box[0] = SRAM_readByte(24);
    save->box[1] = SRAM_readByte(25);
    save->box[2] = SRAM_readByte(26);
    save->box[3] = SRAM_readByte(27);
    save->box[4] = SRAM_readByte(28);
    save->box[5] = SRAM_readByte(29);
    save->box[6] = SRAM_readByte(30);
    save->box[7] = SRAM_readByte(31);
    save->box[8] = SRAM_readByte(32);
    save->box[9] = SRAM_readByte(33);
    save->box[10] = SRAM_readByte(34);
    save->box[11] = SRAM_readByte(35);
    save->box[12] = SRAM_readByte(36);
    save->box[13] = SRAM_readByte(37);
    save->box[14] = SRAM_readByte(38);
    save->box[15] = SRAM_readByte(39);
    save->box[16] = SRAM_readByte(40);
    save->box[17] = SRAM_readByte(41);
    save->box[18] = SRAM_readByte(42);
    save->box[19] = SRAM_readByte(43);
    save->cell = SRAM_readByte(44);
    save->extra = SRAM_readByte(45);
    save->gold = SRAM_readWord(46);
    save->exp = SRAM_readWord(48);
    save->time = SRAM_readLong(50);
}

void writesave(savedata_t *save) {
    if (save == NULL)
	return;
    SRAM_writeByte(1,save->name[0]);
    SRAM_writeByte(2,save->name[1]);
    SRAM_writeByte(3,save->name[2]);
    SRAM_writeByte(4,save->name[3]);
    SRAM_writeByte(5,save->name[4]);
    SRAM_writeByte(6,save->name[5]); 
    SRAM_writeByte(7,save->love); 
    SRAM_writeByte(8,save->hp);
    SRAM_writeByte(9,save->maxhp);
    SRAM_writeByte(10,save->room);
    SRAM_writeByte(11,save->at);
    SRAM_writeByte(12,save->def);
    SRAM_writeByte(13,save->kills);
    SRAM_writeByte(14,save->weapon);
    SRAM_writeByte(15,save->armor);
    SRAM_writeByte(16,save->item[0]);
    SRAM_writeByte(17,save->item[1]);
    SRAM_writeByte(18,save->item[2]);
    SRAM_writeByte(19,save->item[3]);
    SRAM_writeByte(20,save->item[4]);
    SRAM_writeByte(21,save->item[5]);
    SRAM_writeByte(22,save->item[6]);
    SRAM_writeByte(23,save->item[7]);
    SRAM_writeByte(24,save->box[0]);
    SRAM_writeByte(25,save->box[1]);
    SRAM_writeByte(26,save->box[2]);
    SRAM_writeByte(27,save->box[3]);
    SRAM_writeByte(28,save->box[4]);
    SRAM_writeByte(29,save->box[5]);
    SRAM_writeByte(30,save->box[6]);
    SRAM_writeByte(31,save->box[7]);
    SRAM_writeByte(32,save->box[8]);
    SRAM_writeByte(33,save->box[9]);
    SRAM_writeByte(34,save->box[10]);
    SRAM_writeByte(35,save->box[11]);
    SRAM_writeByte(36,save->box[12]);
    SRAM_writeByte(37,save->box[13]);
    SRAM_writeByte(38,save->box[14]);
    SRAM_writeByte(39,save->box[15]);
    SRAM_writeByte(40,save->box[16]);
    SRAM_writeByte(41,save->box[17]);
    SRAM_writeByte(42,save->box[18]);
    SRAM_writeByte(43,save->box[19]);
    SRAM_writeByte(44,save->cell);
    SRAM_writeByte(45,save->extra);
    SRAM_writeWord(46,save->gold);
    SRAM_writeWord(48,save->exp);
    SRAM_writeLong(50,save->time);
}
