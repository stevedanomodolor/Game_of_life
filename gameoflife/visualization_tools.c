/*
 *
 * @file visualization_tools.c
 * @brief Implementation of visualization_tools
 *
 * This file contains the implementation of the functions needed to display the game on the screen
 * Project: Game of life
 *
 */

#include "visualization_tools.h"

void print_menu(WINDOW *menu_win, int highlight, int n_choices,char **menu_choices,window_property_t win_info)
{
	/****coder 2*****/
	int x, y, i;
	x = win_info.startx;
	y = win_info.starty;
  /* goes through the choices and prints them on the screen on ontop of the other*/
	for(i = 0; i < n_choices; ++i)
	{	if(highlight == i + 1)
		{	wattron(menu_win, A_REVERSE);
			mvwprintw(menu_win, y, x, "%s", menu_choices[i]);
			wattroff(menu_win, A_REVERSE);
		}
		else
			mvwprintw(menu_win, y, x, "%s", menu_choices[i]);
		++y;
	}
	wrefresh(menu_win); // refresh the screen to show the changes
}
void	obtain_choice_index(int *choice_ptr, char ch, MEVENT *event_ptr,  char** menu, int n_choices,window_property_t win_info, int window_offset)
{
	/****coder 2*****/
	int i,j, choice;
	i = window_offset + win_info.startx+ 2;
	j = win_info.starty;
	*choice_ptr = -1;
	if(ch == -103)
{
	if(getmouse(event_ptr) == OK)
	{
		/* When the user clicks left mouse button */
		if(event_ptr->bstate &  (BUTTON1_PRESSED||BUTTON1_CLICKED))
		{
				/* loop through choice and find the one in the box the mouse clocked*/
				for(choice = 0; choice < n_choices; ++choice)
			  /* checks whether the mouse position is within the area of the menu choices*/
				if((event_ptr->y == j + choice) && (event_ptr->x >= i) && (event_ptr->x <= i + strlen(menu[choice])+5))
					{
						*choice_ptr = choice;

					}
				refresh();
		}
	}
}
}

int helpbox_on(WINDOW* win, bool play, bool mode)
{
	/****coder 2*****/
  clean_window(win);
  wbkgd(win, COLOR_PAIR(1));
  char * a = "activated";
  char *  d = "deactivated";
  char *m = "manual";
  char * am = "automatic";
	wprintw(win, "HelpBox\nq - quit\nr - restart\np - play:  %s \ns - play mode: %s\nArrow right(->) - \nUpdate state(manual mode)\n\n'p' to start the simulation ", (play?a:d), (mode?m:am));  // Michele correction!!!!!
  wrefresh(win);
  return 0;
}
int helpbox_off(WINDOW* win)
{
	/****coder 2*****/
  clean_window(win);
  return 0;
}
void clean_window(WINDOW* win)
{
	/****coder 2*****/
	werase(win);
	wrefresh(win);
}
int initialize_screen(void)
{
	/****coder 2*****/
  initscr(); //intialize ncurses screen
	noecho(); //routines control whether characters typed by the user are echoed by getch as they are typed.
	cbreak();	//Line buffering disabled. pass on everything
  return 0;
}
int end_screen(void)
{
	/****coder 2*****/
  endwin(); // end ncurses screen
  return 0;
}
