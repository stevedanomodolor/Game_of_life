/*
 *
 * @file visualization_tools.h
 * @brief Header of visualization_tools.c
 *
 * This file is the header of the visualization_tools.c. It contains the defintion of all the functions to enables display with ncurses
 *
 * Project:  Game of Life
 */
#ifndef VISUALIZATION_TOOLS_H
#define VISUALIZATION_TOOLS_H

#include <ncurses.h>
#include <string.h>
#include "common_variable_type.h"
/****coder 2*****/

/* prints a specific menu in a specific window*/
void print_menu(WINDOW *menu_win, int highlight, int n_choices,char **menu_choices,window_property_t win_info);
/*based on the user mouse clock, obtain the choise */
void	obtain_choice_index(int *choice_ptr, char ch, MEVENT *event_ptr,  char** menu, int n_choices,window_property_t win_info, int window_offset);
/* display the helpbox value*/
int helpbox_on(WINDOW* win,bool play, bool mode);
/* turn off helpbox display*/
int helpbox_off(WINDOW* win);
/* clean the content of a window*/
void clean_window(WINDOW* win);
/* initialise ncurses screen with relevenat configuration*/
int initialize_screen(void);
/* end ncuses screen*/
int end_screen(void);
 #endif
