#ifndef PRINT_MENU_H
#define PRINT_MENU_H
#include <stdio.h>
#include <ncurses.h>

#include <stdlib.h>
#include <string.h>
// #include "initial_structures.h"

#define MAX_LEN 100


typedef struct {
  void *x; // if NULL, this is the last element; defining the pointer as a void, is not possible to call an alement pointed by the pointer without a cast
  void *y; // if NULL, this is the first element
} element_t;
// function containing the print_menu code
extern int print_menu (int sty, int x, int alts, int width,char title[], char entries[][MAX_LEN], int start);

#endif
