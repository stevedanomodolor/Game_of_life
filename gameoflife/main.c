/*
 *
 * @file main.c
 *
 * This file contains the implementation of the state machine of the whole game. It manages all the processes from the display to the update of the game of life.
 * Project: Game of life
 *
 *
 * In order to implement the code, for the simulation of the structures proposed in the assignment,
 *the team-work strategy is that to divide the implemetation between:
 * implementation of the functions to handle initialization and setting of the cellmap strucutre(coder 3),
 *  display/visualization (coder2) and the creation of the menu options and state mahcine   and the optimized method of resolution to check the live/dead cells (coder1).
 *
 * For the options menu, the idea is  to provide the options to choose the structure to simulate,
 *before starting the simulation, the default mode setting are:
 * play = false
 * mode  = manual
 * Game structure = R_pentomino
 * quit = false
 *!!! For the selection of the options, please use the touch-pad(it works betteer compared to cliciking the mouse)!!!
 *
 *During the simulation a legend is provided (HelpBox) on the left side ofthe window, in which are specified
 *the buttons to select the several options available: quit game (q), restart game (r), play/pause (p)
 *(please press "p" to start the simulation) and the modality of running that can be automatic or manual
 *(please press the right arrow on the keybord (->) to make a step forward in the simulation when mode is manual, automatic mode updates the state automatically).
 * You can tell when the play is activated/deactivated or which simulation mode because it is shown in the helpbox
*/

/* **************************Method for updating the cellmap state update*******************************************************
 * The strategy used is as follows, a struct cell_t is used to store the x y position and the state of each cell
 * typedef struct cell_c{ Definition in the conway_functions.h file
 * int pos_x;
 * int pos_y;
 * int alive;
 *}cell_t;
 * To save memory and increase speed, only the live cell is stored in a dynamic array of type cell_t.
 * To advance to the next generation, a new array with size 8*num_alive_cell + num_alive_cell is created where we store the position and state of the alive cell of the previous generation
 * and the neighbours of each of this alive cells.
 * Then we count the number of times each cell appears in this new array, then the following rule is applied to determine which cell remains alive and is stored for the next generation
 * Cells(DEAD or ALIVE) that appear more that 3 times(share 3 neighbours)
 * Any alive cell that appears 3 times in the newly generated array
 */
#include <stdio.h>
#include <string.h>
#include "global_variables.h"
#include "conway_functions.h"
#include "visualization_tools.h"

/* ----------------------------x maxx width
*|
*|
*|
*| y maxy height */


/****coder 1*****/
/* global varibales initialization*/
/* flags*/
bool Start              = false;
bool Play               = false;
bool Restart            = false;
bool Quit               = false;
bool Shutdown_Game      = false;
bool Game_Mode          = MANUAL;
bool Previous_Game_Mode = false;
int structure_to_simulation = 0;

/* menu optins*/
char * Main_Menu_Choices[NUM_MENU_OPTIONS] = { 	"Start Game",
                																"Setting",
                																"Quit game"};
char * Setting_Menu_Choices[NUM_SETTING_OPTIONS] =  { "Choose structure",
                    																	"Simulation Mode",
                    																	"Return"};
char * Init_Structure_Menu_Choices[NUM_SIM_STRUCT_MENU_OPTIONS] =  { "R_pentomino",
                                      															"Diehard",
                                      															"Acorn",
                                                                     "Glider", // todo add
                                                                    "LightWeigth_spaceship",
                                                                      "Pulsar"};
char * Simulation_Mode_Menu_Choices[NUM_SIM_MODE_MENU_OPTIONS] =  { "Manual",
                                                                    "Automatic"};

// window characterisitics
window_property_t Helpbox_Win_Prop = {0,0,HEIGHT_HELPBOX,WIDTH_HELPBOX};
window_property_t Game_Win_Prop = {0,0,0,0};
window_property_t Menu_Win_Prop = {0,0,HEIGHT_MENU,WIDTH_HELPBOX};
WINDOW *Helpbox_Win = NULL;
WINDOW *Game_Win = NULL;
/* simulation strucuture characterisitics*/
simulation_structure_t simulation_structure_property[NUM_SIM_STRUCT_MENU_OPTIONS] = {{5,5,5}, // R_pentomino
                                                                                     {5,10,7}, //Diehard
                                                                                     {5,9,7},  // Acorn
                                                                                     {5,5,5}, // Glider
                                                                                     {7,9,9}, // LightWeigth_spaceship
                                                                                     {17,17,56}}; // pulsar
int main(int argc, char const *argv[])
{
  cell_t *cell_map = NULL;
  game_state_t my_state = MAIN_MENU_STATE;
  unsigned int num_alive_cell = 0;
  int menu_choice = 0;
  MEVENT event; // keep track of the mouse event
  int user_input;
  char error_msg[MSG_LEN];
  initialize_screen();
  set_window_configuration();
  print_menu(Game_Win, 1, NUM_MENU_OPTIONS, Main_Menu_Choices, Menu_Win_Prop);
  keypad(stdscr, TRUE); // enables the reading of function keys like F1, F2, arrow keys etc.
  /* Get all the mouse events */
  mousemask(ALL_MOUSE_EVENTS, NULL);
  nodelay(stdscr,false); // block getch function

  /*start state machine*/
  while(!Shutdown_Game)
  {
    user_input = getch();
    update_game_state_flag(user_input);
    /****************screen resizing********************/
    if(user_input==KEY_RESIZE)
    {
     if(!screen_resized_correctly(my_state, error_msg))
     {
       print_error_msg(error_msg);
     }
    }
    /****************screen resizing********************/
    /* main state machine*/
    switch (my_state)
    {
      case MAIN_MENU_STATE:
        obtain_choice_index(&menu_choice, user_input, &event, Main_Menu_Choices,NUM_MENU_OPTIONS,Menu_Win_Prop, Helpbox_Win_Prop.width);
        /* quit game*/
        if(menu_choice == 2)
        {
          my_state = END_GAME_STATE;
        }
        /*start game*/
        else if(menu_choice == 0)
        {
          my_state = INITIALIZE_GAME_STATE;
          clean_window(Game_Win);
          goto initialize_state_jump; // Not advised goto statement but used because of the getch() blociking property
          break;
        }
        /*setting*/
        else if(menu_choice == 1)
        {
          clean_window(Game_Win);
          my_state = SETTING_MENU_STATE;
          print_menu(Game_Win, 1, NUM_SETTING_OPTIONS, Setting_Menu_Choices, Menu_Win_Prop);
          break;
        }
        print_menu(Game_Win, 1, NUM_MENU_OPTIONS, Main_Menu_Choices, Menu_Win_Prop);
        break;
      case SETTING_MENU_STATE:
        obtain_choice_index(&menu_choice, user_input, &event, Setting_Menu_Choices,NUM_SETTING_OPTIONS,Menu_Win_Prop, Helpbox_Win_Prop.width);
        /*Return to main menu*/
        if(menu_choice == 2)
        {
          clean_window(Game_Win);
          my_state = MAIN_MENU_STATE;
          print_menu(Game_Win, 1, NUM_MENU_OPTIONS, Main_Menu_Choices, Menu_Win_Prop);
          break;
        }
        /*simulation_structure option*/
        else if(menu_choice == 0)
        {
          clean_window(Game_Win);
          my_state = INIT_STRUCTURE_MENU_STATE;
          print_menu(Game_Win, 1, NUM_SIM_STRUCT_MENU_OPTIONS, Init_Structure_Menu_Choices, Menu_Win_Prop);
          break;
        }
        /* simulation mode option*/
        else if(menu_choice == 1)
        {
          clean_window(Game_Win);
          my_state = SIMULATION_MODE_MENU_STATE;
          print_menu(Game_Win, 1, NUM_SIM_MODE_MENU_OPTIONS, Simulation_Mode_Menu_Choices, Menu_Win_Prop);
          break;
        }
        print_menu(Game_Win, 1, NUM_SETTING_OPTIONS, Setting_Menu_Choices, Menu_Win_Prop);
        break;
      case INIT_STRUCTURE_MENU_STATE:
        obtain_choice_index(&menu_choice, user_input, &event, Init_Structure_Menu_Choices,NUM_SIM_STRUCT_MENU_OPTIONS,Menu_Win_Prop, Helpbox_Win_Prop.width);
        /*simulation strucutre options*/
        if(menu_choice >= 0 && menu_choice <= (NUM_SIM_STRUCT_MENU_OPTIONS-1))
        {
          structure_to_simulation =menu_choice ;
          clean_window(Game_Win);
          my_state = SETTING_MENU_STATE;
          print_menu(Game_Win, 1, NUM_SETTING_OPTIONS, Setting_Menu_Choices, Menu_Win_Prop);
          break;
        }
        print_menu(Game_Win, 1, NUM_SIM_STRUCT_MENU_OPTIONS, Init_Structure_Menu_Choices, Menu_Win_Prop);
        break;
      case SIMULATION_MODE_MENU_STATE:
        obtain_choice_index(&menu_choice, user_input, &event, Simulation_Mode_Menu_Choices,NUM_SETTING_OPTIONS,Menu_Win_Prop, Helpbox_Win_Prop.width);
        /*simulation mode choices*/
        if(menu_choice >= 0 && menu_choice <= (NUM_SIM_MODE_MENU_OPTIONS-1))
        {
          if(menu_choice == 0) // this way the user can change to automatic before strating the game
          {
            if(Game_Mode ==AUTOMATIC )
            {
              Game_Mode = AUTOMATIC;
            }

          }
          else if(menu_choice == 1)
          {
            if(Game_Mode == MANUAL)
            {
              Game_Mode = MANUAL;
            }
          }
          // Game_Mode = (menu_choice == 0) ? MANUAL : AUTOMATIC;
          helpbox_on(Helpbox_Win,Play, Game_Mode);
          clean_window(Game_Win);
          my_state = SETTING_MENU_STATE;
          print_menu(Game_Win, 1, NUM_SETTING_OPTIONS, Setting_Menu_Choices, Menu_Win_Prop);
          break;
        }
        print_menu(Game_Win, 1, NUM_SIM_MODE_MENU_OPTIONS, Simulation_Mode_Menu_Choices, Menu_Win_Prop);
        break;
      case INITIALIZE_GAME_STATE:
          /*initialize game only when it is possible*/
          if(structure_to_simulation <= (NUM_SIM_STRUCT_MENU_OPTIONS-1))
          {
            initialize_state_jump: // Not advised goto statement but used because of the getch() blociking property
            if(!cellmap_initialized_correctly(&cell_map,simulation_structure_property,  structure_to_simulation, Game_Win_Prop, &num_alive_cell,Game_Win,error_msg))
            {
              print_error_msg(error_msg);
              my_state = INITIALIZE_GAME_STATE;// mantain state until user chooses a correct state
            }
            my_state = START_SIMULATION_STATE;
            goto start_game_jump; // Not advised goto statement but used because of the getch() blociking property
          }
          break;
      case START_SIMULATION_STATE:
        /*if quit flag activated*/
        /* initialize the game immediately*/

        start_game_jump: // Not advised goto statement but used because of the getch() blociking property
        if(Quit)
        {
          my_state = MAIN_MENU_STATE;
          nodelay(stdscr, FALSE);
          Quit = false;
          clean_window(Game_Win);
          print_menu(Game_Win, 1, NUM_MENU_OPTIONS, Main_Menu_Choices, Menu_Win_Prop);
        }
        else
        {
          if(Restart)
          {
              clean_window(Game_Win);
              cellmap_initialized_correctly(&cell_map,simulation_structure_property,  structure_to_simulation, Game_Win_Prop, &num_alive_cell,Game_Win,error_msg);
              // nodelay(game_win, FALSE);
              Restart = false;
          }
          else
          {
            if(Play)
            {
              if(Game_Mode == MANUAL)
              {
                /* activate getch blocking only when previously it was not activated(automatic mode)*/
                if(Previous_Game_Mode == AUTOMATIC)
                {
                  nodelay(stdscr, FALSE);
                }
                if(user_input == KEY_RIGHT)
                {
                  // update manually
                  if(!cellmap_updated_successfully(&cell_map, &num_alive_cell, Game_Win_Prop, error_msg, Game_Win))
                  {
                    print_error_msg(error_msg);
                  }

                }
              }
              else
              // automatic simulation
              {
                if(Previous_Game_Mode == MANUAL)
                {
                  nodelay(stdscr, TRUE);
                }
                if(!cellmap_updated_successfully(&cell_map, &num_alive_cell, Game_Win_Prop, error_msg, Game_Win))
                {
                  print_error_msg(error_msg);
                }
              }
            }
          }
        }
        break;
      case END_GAME_STATE:
        Shutdown_Game = true;
        break;
    }
  }
  end_screen();
  // free memory when necessary
  // if(cell_map!=NULL)
  // {
  free(cell_map);
  // }
  return 0;
}
void set_window_configuration(void)
{
    int maxx, maxy;
     // get terminal screen size
     getmaxyx(stdscr, maxy, maxx);
     Helpbox_Win_Prop.startx = 1; //  helpboc config
     Helpbox_Win_Prop.starty = 1;
     /*game*/
     Game_Win_Prop.startx = Helpbox_Win_Prop.width+1;
     Game_Win_Prop.starty = 0;
     Game_Win_Prop.width=(maxx-Game_Win_Prop.startx);
     Game_Win_Prop.height=maxy-Game_Win_Prop.starty;//-Game_Win_Prop.starty);
     /* menu property wrt the game window*/
     Menu_Win_Prop.startx = (Game_Win_Prop.width)/2;
     Menu_Win_Prop.starty = (Game_Win_Prop.height)/2;
     start_color(); // activate color use
     /* color pair for visualization*/
     init_pair(1, COLOR_WHITE,COLOR_BLACK);
     init_pair(2, COLOR_WHITE,COLOR_RED);
     // define windows
     Helpbox_Win = newwin( Helpbox_Win_Prop.height,Helpbox_Win_Prop.width, Helpbox_Win_Prop.starty,Helpbox_Win_Prop.startx);
     Game_Win = newwin(Game_Win_Prop.height,Game_Win_Prop.width, Game_Win_Prop.starty,Game_Win_Prop.startx);
     wbkgd(Game_Win, COLOR_PAIR(2)); // add color to game_win

     werase(Game_Win);
     refresh();
     helpbox_on(Helpbox_Win,Play, Game_Mode);
     wrefresh(Game_Win);

  }
void update_game_state_flag(char ch)
{
   if(ch == 'p' || ch == 'p')
   {
     Play = !Play;
     helpbox_on(Helpbox_Win,Play, Game_Mode);
   }
   else if(ch == 'r' || ch == 'R')
   {
     Restart = true;
   }
   else if(ch == 'q'|| ch =='Q')
   {
      Quit = !Quit;
   }
    else if(ch == 's' || ch == 'S')
    {
        Previous_Game_Mode = Game_Mode;
        Game_Mode = !Game_Mode;
        helpbox_on(Helpbox_Win,Play, Game_Mode);
    }
 }
bool screen_resized_correctly(game_state_t state, char error_msg[MSG_LEN])
{
  end_screen();
  initialize_screen();
  erase();
  set_window_configuration();
  /* limit resize to menu */
  if(state == MAIN_MENU_STATE)
  {
    print_menu(Game_Win, 1, NUM_MENU_OPTIONS, Main_Menu_Choices, Menu_Win_Prop);
  }
  else if(state == SETTING_MENU_STATE)
  {
    print_menu(Game_Win, 1, NUM_SETTING_OPTIONS, Setting_Menu_Choices, Menu_Win_Prop);
  }
  else if(state == INIT_STRUCTURE_MENU_STATE)
  {
    print_menu(Game_Win, 1, NUM_SIM_STRUCT_MENU_OPTIONS, Init_Structure_Menu_Choices, Menu_Win_Prop);
  }
  else if(state == SIMULATION_MODE_MENU_STATE)
  {
    print_menu(Game_Win, 1, NUM_SIM_MODE_MENU_OPTIONS, Simulation_Mode_Menu_Choices, Menu_Win_Prop);
  }
  else
  {
     stpcpy(error_msg,"don't modify during game :)\n press q to go to the main menu");
     wrefresh(Game_Win);
     return false;
  }

  return true;

}
void print_error_msg(char error_msg[MSG_LEN])
{
  mvwprintw(Game_Win, 0, 0, error_msg);
  wrefresh(Game_Win);
}
