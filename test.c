#include <stdio.h>
#include <curses.h>


if (getch() == '\033') { // if the first value is esc
    getch(); // skip the [
    switch(getch()) { // the real value
        case 'A':
            printf("up");
            break;
        case 'B':
            // code for arrow down
	    printf("down");
            break;
        case 'C':
            // code for arrow right
	    printf("right");
            break;
        case 'D':
            // code for arrow left
	    printf("left");
            break;
    }
}
