#include "utils.h"
#include <genesis.h>

/* This is O(n), as opposed to using strreplacechar ten times,
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
