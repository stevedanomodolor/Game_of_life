#include "global_variables.h"
#include <visualization_tools.h>




/***** coder 1********/
void set_window_configuration(void)
{
   int maxx, __attribute__((unused)) maxy;
    // get terminal screen size
    getmaxyx(stdscr, maxy, maxx);
    Helpbox_Win_Prop.startx = 1; //  helpboc config
    Helpbox_Win_Prop.starty = 1;
    /* menu property*/
    Menu_Win_Prop.startx = (maxx-(Helpbox_Win_Prop.width*2))/2;
    Menu_Win_Prop.starty = (maxy-(Helpbox_Win_Prop.height))/2;
    /*game*/
    Game_Win_Prop.startx = Helpbox_Win_Prop.width+1;
    Game_Win_Prop.starty = 0;
    Game_Win_Prop.height=(maxy-Game_Win_Prop.starty);
    Game_Win_Prop.width=(maxx-Game_Win_Prop.startx);
    start_color(); // activate color use
    /* color pair for visualization*/
    init_pair(1, COLOR_RED,COLOR_BLACK);
    init_pair(2, COLOR_WHITE,COLOR_RED);
    keypad(stdscr, TRUE); // enables the reading of function keys like F1, F2, arrow keys etc.
    // define windows
    Helpbox_Win = newwin(Helpbox_Win_Prop.height, Helpbox_Win_Prop.width, Helpbox_Win_Prop.starty,Helpbox_Win_Prop.startx);
    Game_Win = newwin(Game_Win_Prop.height, Game_Win_Prop.width, Game_Win_Prop.starty,Game_Win_Prop.startx);
    wbkgd(Game_Win, COLOR_PAIR(2)); // add color to game_win
    /* Get all the mouse events */
    mousemask(ALL_MOUSE_EVENTS, NULL);
    werase(Game_Win);
    refresh();
    wrefresh(Game_Win);
    helpbox_on(Helpbox_Win,Play, Game_Mode);
 }
void update_game_state_flag(char ch)
{
  if(ch == 'p' || ch == 'p')
  {
    Play = !Play;
    helpbox_on(Game_Win,Play, Game_Mode);
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
     helpbox_on(Game_Win,Play, Game_Mode);
   }
}
