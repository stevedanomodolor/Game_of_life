/*
 *
 * @file common_variable_type.h
 *
 * This file contains all the variabels type that is shared ammong all the other files
 *
 * Project:  Game of Life
 */
#ifndef COMMON_VARIABLE_TYPE_H
#define COMMON_VARIABLE_TYPE_H

#define MSG_LEN 50
/****coder 3*****/

/*window properties*/
typedef struct window_property_c
{
  /* initial position of the windows wrt to the parent window
   * game window parent window = stdscr
   * helpbox window parent window = stdscr
   * menu window property parent window = game window
   */
  unsigned int startx;
  unsigned int starty;
  unsigned int height; // dimension of the window
  unsigned int width;
}window_property_t;



#endif
