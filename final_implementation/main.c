#include <locale.h>
#include <stdio.h>
#include <ncurses.h>
#include "print_menu.h"
#include "initial_structures.h"


void display_cell(unsigned int x, unsigned int y, bool on){
  on ? mvaddch(x, y,'X') : mvaddch(x, y,' ');
  refresh();
}

void print_cell(cell_t *cell, int offset_x, int offset_y, int size)
{
  for(int i = 0; i < size; i++)
  {
    display_cell(cell[i].pos_x+offset_x,cell[i].pos_y+offset_y,ALIVE);
  }

}
int main(int argc, char const *argv[]) {
  int menu_ret = 1, menu_ret2 = 1;
  char alts[][100] = {{"Start Game"},     /* Every menu needs an */     /* array like these to */
                      {"Config"},
                      {"Quit Game"},};   /* hold the entries.   */
  char alts2[][100] = {{"Matrix 1"},
                       {"Matrix 2"},
                       {"Matrix 3"},
                       {"User define matrix"},
                       {"Return"}};

  setlocale (LC_CTYPE, "");

  initscr();
  keypad (stdscr, TRUE);
  curs_set (0);

  do  /* This loop terminates when MAIN MENU returns 3, Quit Game.   */
  {   /* menu_ret is sent as the start value, to make the last entry */
      /* highlighted when you return to the main menu.               */

      mvprintw(22 ,4, "1. The R-pentomino");
      mvprintw(22 ,30, "2. Diehard");
      mvprintw(22 ,52, "3. Acorn");
      print_cell(R_pentomino,24,11,5);
      print_cell(Diehard, 24, 30,7);
      print_cell(Acorn, 24, 52,7);

      menu_ret = print_menu (2, 6, 3, 15,"MAIN MENU", alts, menu_ret);
      // printf("%d\n", menu_ret);

      int x;
      if (menu_ret == 1)  /* This is just an example program. */
      {                   /* You can't start an actual game.  */
          do                  /* the main menu. */
          {
              menu_ret2 = print_menu (6, 22, 5, 15,"SELECT MATRIX", alts2, 1);
              // scanf("%i", &x);  // store the number of matrix selected
              // mvprintw(0,0,"%i", x);

          }
          while (menu_ret2 != 5);

          //scanf("%i", &x);  // store the number of matrix selected
          // mvprintw(0,0,"%i", x);
      }

      erase();    /* When you return from the SELECT MATRIX menu,      */
  }               /* everything will be erased and MAIN MENU will be */
  while (menu_ret != 3); /* reprinted.                               */
  printf("here");

  endwin();
  return 0;
}
