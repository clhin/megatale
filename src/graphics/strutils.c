#include "strutils.h"
#include <genesis.h>

/* Format string into correct font for crypt of tomorrow text,
   found in the menus and title screen text. We need to do this
   because we share the default font with MNC for the battles.
   This is O(n), as opposed to using strreplacechar ten times,
   which is 10*O(n), at the cost of a slightly bigger binary */
void strconvert(char* str) {
    char *s = str;
    while (*s) {
	switch (*s) {
	    case '0':
		*s = 'O';
		++s;
		continue;
	    case '1':
		*s = ';';
		++s;
		continue;
	    case '2':
		*s = '<';
		++s;
		continue;
	    case '3':
		*s = '=';
		++s;
		continue;
	    case '4':
		*s = '>';
		++s;
		continue;
	    case '5':
		*s = 'S';
		++s;
		continue;
	    case '6':
		*s = '@';
		++s;
		continue;
	    case '7':
		*s = '^';
		++s;
		continue;
	    case '8':
		*s = 'B';
		++s;
		continue;
	    case '9':
		*s = '`';
		++s;
		continue;
	    default:
		++s;
		continue;
	}
    }
}

// Codes based off of this:
// https://tomat.dev/undertale/items
const char * getitemname(u8 itemcode) {
    switch (itemcode) {
	case 1:
	    return "Monster Candy";
	case 2:
	    return "Stick";
	case 3:
	    return "Bandage";
	case 4:
	    return "Spider Donut";
	case 5:
	    return "Spider Cider";
	case 6:
	    return "Butterscotch Pie";
	case 7:    
	    return "Faded Ribbon";
	case 8:
	    return "Toy Knife";
	case 9:
	    return "Tough Glove";
	case 10:
	    return "Manly Bandanna";
	case 11:
	    return "Snowman Piece";
	case 12:
	    return "Nice Cream";
	case 13:
	    return "Bisicle";
	case 14:
	    return "Unisicle";
	case 15:
	    return "Cinnamon Bun";
	case 16:
	    return "Temmie Flakes";
	case 17:
	    return "Abandoned Quiche";
	case 18:
	    return "Old Tutu";
	case 19:
	    return "Ballet Shoes";
	case 20:
	    return "Punch Card";
	case 21:
	    return "Annoying Dog";
	case 22:
	    return "Dog Salad";
	case 23:
	case 24:
	case 25:
	case 26:
	case 27:
	case 28:
	    return "Dog Residue";
	case 29:
	    return "Astronaut Food";
	case 30:
	    return "Instant Noodles";
	case 31:
	    return "Crab Apple";
	case 32:
	    return "Hot Dog...?";
	case 33:
	    return "Hot Cat";
	case 34:
	    return "Glamburger";
	case 35:
	    return "Sea Tea";
	case 36:
	    return "Starfait";
	case 37:
	    return "Legendary Hero";
	case 38:
	    return "Butty Glasses";
	case 39:
	    return "Torn Notebook";
	case 40:
	    return "Stained Apron";
	case 41:
	    return "Burnt Pan";
	case 42:
	    return "Cowboy Hat";
	case 43:
	    return "Empty Gun";
	case 44:
	    return "Heart Locket";
	case 45:
	    return "Worn Dagger";
	case 46:
	    return "Real Knife";
	case 47:
	    return "The Locket";
	case 48:
	    return "Bad Memory";
	case 49:
	    return "Dream";
	case 50:
	    return "Undyne's Letter";
	case 51:
	   return "Undyne's Letter EX";
	case 52:
	    return "Popato Chisps";
	case 53:
	    return "Junk Food";
	case 54:
	    return "Mystery Key";
	case 55:
	    return "Face Steak";
	case 56:
	    return "Hush Puppy";
	case 57:
	    return "Snail Pie";
	case 58:
	    return "temy armor";
    }
    return NULL;
}

u8 parse_dialog(const char * dialog, u16* textpos, u8 * asterisks, u8 size) {
    for (int i = 0; i < size; i++) {
	if (dialog[i] == '*') {
	    ++*asterisks;
	    continue;
	}
	++textpos;
	if (dialog[i] == '\0') {
	    if (i == size -1)
		return TRUE;
	    return FALSE;
	}
    }
    return TRUE;
}
