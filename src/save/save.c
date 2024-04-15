#include "save.h"

void readsave(savedata_t *save) {
    if (save == NULL)
	return;
    save->name[0] = SRAM_readByte(NAMECHAR1);
    save->name[1] = SRAM_readByte(NAMECHAR2);
    save->name[2] = SRAM_readByte(NAMECHAR3);
    save->name[3] = SRAM_readByte(NAMECHAR4);
    save->name[4] = SRAM_readByte(NAMECHAR5);
    save->name[5] = SRAM_readByte(NAMECHAR6);
    save->name[6] = '\0'; // not saved in SRAM
    save->love = SRAM_readByte(LOVE);
    save->hp = SRAM_readByte(HP);
    save->maxhp = SRAM_readByte(MAXHP);
    save->room = SRAM_readByte(ROOM);
    save->at = SRAM_readByte(ATTACK);
    save->def = SRAM_readByte(DEFENCE);
    save->kills = SRAM_readByte(KILLS);
    save->weapon = SRAM_readByte(WEAPON);
    save->armor = SRAM_readByte(ARMOR);
    save->item[0] = SRAM_readByte(ITEM1);
    save->item[1] = SRAM_readByte(ITEM2);
    save->item[2] = SRAM_readByte(ITEM3);
    save->item[3] = SRAM_readByte(ITEM4);
    save->item[4] = SRAM_readByte(ITEM5);
    save->item[5] = SRAM_readByte(ITEM6);
    save->item[6] = SRAM_readByte(ITEM7);
    save->item[7] = SRAM_readByte(ITEM8);
    save->box[0] = SRAM_readByte(BOX1_1);
    save->box[1] = SRAM_readByte(BOX1_2);
    save->box[2] = SRAM_readByte(BOX1_3);
    save->box[3] = SRAM_readByte(BOX1_4);
    save->box[4] = SRAM_readByte(BOX1_5);
    save->box[5] = SRAM_readByte(BOX1_6);
    save->box[6] = SRAM_readByte(BOX1_7);
    save->box[7] = SRAM_readByte(BOX1_8);
    save->box[8] = SRAM_readByte(BOX1_9);
    save->box[9] = SRAM_readByte(BOX1_10);
    save->box[10] = SRAM_readByte(BOX2_1);
    save->box[11] = SRAM_readByte(BOX2_2);
    save->box[12] = SRAM_readByte(BOX2_3);
    save->box[13] = SRAM_readByte(BOX2_4);
    save->box[14] = SRAM_readByte(BOX2_5);
    save->box[15] = SRAM_readByte(BOX2_6);
    save->box[16] = SRAM_readByte(BOX2_7);
    save->box[17] = SRAM_readByte(BOX2_8);
    save->box[18] = SRAM_readByte(BOX2_9);
    save->box[19] = SRAM_readByte(BOX2_10);
    save->cell = SRAM_readByte(CELL);
    save->gold = SRAM_readWord(GOLD);
    save->exp = SRAM_readWord(EXP);
    save->time = SRAM_readLong(TIME);
}

void writesave(savedata_t *save) {
    if (save == NULL)
	return;
    SRAM_writeByte(NAMECHAR1,save->name[0]);
    SRAM_writeByte(NAMECHAR2,save->name[1]);
    SRAM_writeByte(NAMECHAR3,save->name[2]);
    SRAM_writeByte(NAMECHAR4,save->name[3]);
    SRAM_writeByte(NAMECHAR5,save->name[4]);
    SRAM_writeByte(NAMECHAR6,save->name[5]); 
    SRAM_writeByte(LOVE,save->love); 
    SRAM_writeByte(HP,save->hp);
    SRAM_writeByte(MAXHP,save->maxhp);
    SRAM_writeByte(ROOM,save->room);
    SRAM_writeByte(ATTACK,save->at);
    SRAM_writeByte(DEFENCE,save->def);
    SRAM_writeByte(KILLS,save->kills);
    SRAM_writeByte(WEAPON,save->weapon);
    SRAM_writeByte(ARMOR,save->armor);
    SRAM_writeByte(ITEM1,save->item[0]);
    SRAM_writeByte(ITEM2,save->item[1]);
    SRAM_writeByte(ITEM3,save->item[2]);
    SRAM_writeByte(ITEM4,save->item[3]);
    SRAM_writeByte(ITEM5,save->item[4]);
    SRAM_writeByte(ITEM6,save->item[5]);
    SRAM_writeByte(ITEM7,save->item[6]);
    SRAM_writeByte(ITEM8,save->item[7]);
    SRAM_writeByte(BOX1_1,save->box[0]);
    SRAM_writeByte(BOX1_2,save->box[1]);
    SRAM_writeByte(BOX1_3,save->box[2]);
    SRAM_writeByte(BOX1_4,save->box[3]);
    SRAM_writeByte(BOX1_5,save->box[4]);
    SRAM_writeByte(BOX1_6,save->box[5]);
    SRAM_writeByte(BOX1_7,save->box[6]);
    SRAM_writeByte(BOX1_8,save->box[7]);
    SRAM_writeByte(BOX1_9,save->box[8]);
    SRAM_writeByte(BOX1_10,save->box[9]);
    SRAM_writeByte(BOX2_1,save->box[10]);
    SRAM_writeByte(BOX2_2,save->box[11]);
    SRAM_writeByte(BOX2_3,save->box[12]);
    SRAM_writeByte(BOX2_4,save->box[13]);
    SRAM_writeByte(BOX2_5,save->box[14]);
    SRAM_writeByte(BOX2_6,save->box[15]);
    SRAM_writeByte(BOX2_7,save->box[16]);
    SRAM_writeByte(BOX2_8,save->box[17]);
    SRAM_writeByte(BOX2_9,save->box[18]);
    SRAM_writeByte(BOX2_10,save->box[19]);
    SRAM_writeByte(CELL,save->cell);
    SRAM_writeWord(GOLD,save->gold);
    SRAM_writeWord(EXP,save->exp);
    SRAM_writeLong(TIME,save->time);
}
