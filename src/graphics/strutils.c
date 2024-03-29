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
	    return "Croquet Roll";
	case 3:
	    return "Stick";
	case 4:
	    return "Bandage";
	case 5:
	    return "Rock Candy";
	case 6:
	    return "Pumpkin Rings";
	case 7:
	    return "Spider Donut";
	case 8:
	    return "Stoic Onion";
	case 9:
	    return "Ghost Fruit";
	case 10:
	    return "Spider Cider";
	case 11:
	    return "Butterscotch Pie";
	case 12:    
	    return "Faded Ribbon";
	case 13:
	    return "Toy Knife";
	case 14:
	    return "Tough Glove";
	case 15:
	    return "Manly Bandanna";
	case 16:
	    return "Snowman Piece";
	case 17:
	    return "Nice Cream";
	case 18:
	    return "Puppydough Icecream";
	case 19:
	    return "Bisicle";
	case 20:
	    return "Unisicle";
	case 21:
	    return "Cinnamon Bun";
	case 22:
	    return "Temmie Flakes";
	case 23:
	    return "Abandoned Quiche";
	case 24:
	    return "Old Tutu";
	case 25:
	    return "Ballet Shoes";
	case 26:
	    return "Punch Card";
	case 27:
	    return "Annoying Dog";
	case 28:
	    return "Dog Salad";
	case 29:
	case 30:
	case 31:
	case 32:
	case 33:
	case 34:
	    return "Dog Residue";
	case 35:
	    return "Astronaut Food";
	case 36:
	    return "Instant Noodles";
	case 37:
	    return "Crab Apple";
	case 38:
	    return "Hot Dog...?";
	case 39:
	    return "Hot Cat";
	case 40:
	    return "Glamburger";
	case 41:
	    return "Sea Tea";
	case 42:
	    return "Starfait";
	case 43:
	    return "Legendary Hero";
	case 44:
	    return "Butty Glasses";
	case 45:
	    return "Torn Notebook";
	case 46:
	    return "Stained Apron";
	case 47:
	    return "Burnt Pan";
	case 48:
	    return "Cowboy Hat";
	case 49:
	    return "Empty Gun";
	case 50:
	    return "Heart Locket";
	case 51:
	    return "Worn Dagger";
	case 52:
	    return "Real Knife";
	case 53:
	    return "The Locket";
	case 54:
	    return "Bad Memory";
	case 55:
	    return "Dream";
	case 56:
	    return "Undyne's Letter";
	case 57:
	   return "Undyne's Letter EX";
	case 58:
	    return "Popato Chisps";
	case 59:
	    return "Junk Food";
	case 60:
	    return "Mystery Key";
	case 61:
	    return "Face Steak";
	case 62:
	    return "Hush Puppy";
	case 63:
	    return "Snail Pie";
	case 64:
	    return "temy armor";
    }
    return NULL;
}
