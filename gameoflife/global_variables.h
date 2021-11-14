/*
 *
 * @file global_variables.h
 * @brief Header of main.c
 *
 * This file is the header of the global_variablesc. This is where the definittion of all the variables used during the simulation is defined
 *
 * Project:  Game of Life
 */

#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

#include <ncurses.h>
#include <stdbool.h>
#include <string.h>
#include "common_variable_type.h"
#include "conway_functions.h"

#define NUM_WINDOWS                 2
#define NUM_MENU_OPTIONS            3
#define NUM_SETTING_OPTIONS         3
#define NUM_SIM_STRUCT_MENU_OPTIONS 6 // add more TODO:
#define NUM_SIM_MODE_MENU_OPTIONS   2
#define WIDTH_MENU 30
#define HEIGHT_MENU 12
#define WIDTH_HELPBOX 30
#define HEIGHT_HELPBOX 15
/* keep track of the simulation mode*/
#define MANUAL true
#define AUTOMATIC false



/****coder 1*****/

extern window_property_t Helpbox_Win_Prop, Game_Win_Prop, Menu_Win_Prop;
extern WINDOW *Helpbox_Win, *Game_Win;

/*menu options*/
extern char * Main_Menu_Choices[NUM_MENU_OPTIONS];
extern char * Setting_Menu_Choices[NUM_SETTING_OPTIONS];
extern char * Init_Structure_Menu_Choices[NUM_SIM_STRUCT_MENU_OPTIONS];
extern char * Simulation_Mode_Menu_Choices[NUM_SIM_MODE_MENU_OPTIONS];
/*Flags*/
extern bool Start;
extern bool Play;
extern bool Restart;
extern bool Quit;
extern bool Shutdown_Game;
extern bool Game_Mode;
extern bool Previous_Game_Mode;
/*strucuture to simulate*/
extern int structure_to_simulation;
extern simulation_structure_t simulation_structure_property[NUM_SIM_STRUCT_MENU_OPTIONS];


/* game states*/
typedef enum game_state
{
	MAIN_MENU_STATE,
	SETTING_MENU_STATE,
	INIT_STRUCTURE_MENU_STATE,
	SIMULATION_MODE_MENU_STATE,
	INITIALIZE_GAME_STATE,
	START_SIMULATION_STATE,
	END_GAME_STATE
}game_state_t;


/* configures all the window properties*/
void set_window_configuration(void);
/*updates all the boolean flags of the systen*/
void update_game_state_flag(char ch);
/* prints error messga eon top of the game window*/
void print_error_msg(char error_msg[MSG_LEN]);
/* resize the screen window when terminal is resized, only applies to menu screen
 * would not have effect during game simulation*/
bool screen_resized_correctly(game_state_t state, char error_msg[MSG_LEN]);
#endif
