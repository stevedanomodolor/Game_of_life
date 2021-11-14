/*
 *
 * @file conway_functions.h
 * @brief Header of conway_functions
 *
 * This file is the header of the conway_functions.c. The definition of the conway implementation algorithm
 *
 * Project:  Game of Life
 */
#ifndef CONWAY_FUNCTIONS_H
#define CONWAY_FUNCTIONS_H
#define _GNU_SOURCE // to have access to the q_sort_r function
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include "common_variable_type.h"

#define NUM_STRUCTURES 3
#define ALIVE 1
#define DEAD 0

/****coder 3*****/
/*cell state*/
typedef struct cell
{
   int alive;
   int pos_x;
   int pos_y;
}cell_t;

/*simulation structure*/
typedef struct simulation_structure_c
{
  /* store the property of the simulation structure
  * to help center it in the game window
  */
  int height; 
  int width;
  int num_alive_cell;
}simulation_structure_t;

 /* simulation structure name*/
typedef enum
{
  R_pentomino,
  Diehard,
  Acorn,
  Glider,
  LightWeigth_spaceship,
  Pulsar
}simulation_structure_names;



/*initializes the cellmap*/
bool cellmap_initialized_correctly(cell_t ** cellmap_ptr,simulation_structure_t *simulation_structure,  simulation_structure_names choice, window_property_t game_window, unsigned int* num_alive_cell,WINDOW* window, char *error_msg);
/*place cell in the middel of the game window*/
/* x y is the position in the small strucutr window*/
void set_cell(cell_t *cellmap,unsigned int position, simulation_structure_t sim_stru, window_property_t game_window,unsigned int x, unsigned int y, WINDOW* window);
/* displays cell on screen based on if its dead or alive*/
void display_cell(WINDOW *window, unsigned int x, unsigned int y, bool is_alive);
/*comparision function used for the qsort_r function: ascending order*/
int comparator(const void *a, const void *b, void *param);
/*applys the game of life rules to update the cellmap*/
bool cellmap_updated_successfully(cell_t** current_cell_ptr, unsigned int* num_alive_cell, window_property_t game_window, char error_msg[MSG_LEN], WINDOW *window);

 #endif
