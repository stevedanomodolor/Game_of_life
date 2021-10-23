#include <locale.h>
#include <stdio.h>
#include <ncurses.h>
#include "ncurses-menu.h"

/* Prints typical menus that you might see in games */
int main (int argc, char *argv[])
{
    int menu_ret = 1, menu_ret2 = 1;
    char alts[][100] = {{"Start Game"},     /* Every menu needs an */     /* array like these to */
                        {"Quit Game"},};   /* hold the entries.   */
    char alts2[][100] = {{"Matrix 1"},
                         {"Matrix 2"},
                         {"Matrix 3"},
                         {"Return"},};

    setlocale (LC_CTYPE, "");

    initscr();                  /* Most of the below initialisers are */
    noecho();                   /* not necessary for this example.    */
    keypad (stdscr, TRUE);      /* It's just a template for a         */
    meta (stdscr, TRUE);        /* hypothetical program that might    */
    nodelay (stdscr, FALSE);    /* need them.                         */
    notimeout (stdscr, TRUE);
    raw();
    curs_set (0);

    do  /* This loop terminates when MAIN MENU returns 3, Quit Game.   */
    {   /* menu_ret is sent as the start value, to make the last entry */
        /* highlighted when you return to the main menu.               */
        menu_ret = print_menu (2, 5, 2, 15,"MAIN MENU", alts, menu_ret);

        int x;
        if (menu_ret == 1)  /* This is just an example program. */
        {                   /* You can't start an actual game.  */
            do                  /* the main menu. */
            {
                menu_ret2 = print_menu (6, 22, 4, 15,"SELECT MATRIX", alts2, 1);
                scanf("%i", &x);  // store the number of matrix selected
                mvprintw(0,0,"%i", x);
            }
            while (menu_ret2 != 4);

            //scanf("%i", &x);  // store the number of matrix selected
            // mvprintw(0,0,"%i", x);
        }

        erase();    /* When you return from the SELECT MATRIX menu,      */
    }               /* everything will be erased and MAIN MENU will be */
    while (menu_ret != 2); /* reprinted.                               */

    endwin();
    return 0;
}
