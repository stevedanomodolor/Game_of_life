#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

#define WIDTH_MENU 30
#define HEIGHT_MENU 10
#define WIDTH_HELPBOX 30
#define HEIGHT_HELPBOX 15
#define NUM_STRUCTURES 3
#define ALIVE 1
#define DEAD 0
#define MANUAL true
#define AUTOMATIC false
// flags
bool game_start = false;
bool stop = true;
bool next = false;
bool main_menu = false;
bool start_game = false;
bool game_mode = MANUAL;
bool previous_game_mode = MANUAL;
int init_structrue_choice = 0;
bool shutdown_grame = false;
// bool show_helpbox = true;
bool play = false;
bool restart = false;
bool quit = false;
WINDOW *menu_win, *helpbox, *game_win;
// int helpboxon(void); // turn HelpBox on
int helpboxoff(void); // turn HelpBox off


int startx = 0;
int starty = 0;

// menu options
char * main_menu_choices[] = { 	"Start Game",
																"Setting",
																"Quit game"};
char * setting_menu_choices[] = { "Choose structure",      // Michele correction!!!!!!
																	"Simulation mode",       // Michele correction!!!!!!
																	"Return"};               // Michele correction!!!!!!
char * init_structe_menu_choices[] = { "R_pentomino",
															          "Diehard",
															          "Acorn"};
char * simulation_mode_menu_choices[] = { "Manual",        // Michele correction!!!!!!
															            "Automatic"};    // Michele correction!!!!!!


typedef enum game_state
{
	MAIN_MENU,
	SETTING_MENU,
	INIT_STRUCTURE_MENU,
	SIMULATION_MODE_MENU,
	INITIALIZE_GAME,
	START_SIMULATION,
	END_GAME
}game_state_t;
typedef enum game_structure{R_pentomino, Diehard, Acorn, user_defined}game_structure_t; // initialize game strucutre

typedef struct cell {
  int alive;
  int pos_x;
  int pos_y;
}cell_t; // cell state

typedef struct init_struct{
  int height;
  int width;
  int num_alive_cell;
}init_struct_t;

typedef struct window_size{
  int height;
  int width;
}window_size_t;
window_size_t cell_area;

// infomation about the initial strucutres
init_struct_t init_struct_info[NUM_STRUCTURES] = {{5,5,5}, // R_pentomino
                                                        {5,10,7}, //Diehard
                                                        {5,9,7}}; // Acorn


// function declaration
void print_menu(WINDOW *menu_win, int highlight, int n_choices,char **menu_choices,int startx, int starty);
void report_choice(int mouse_x, int mouse_y, int *p_choice,int n_choices, char ** menu_choices, int startx, int starty);
void	obtain_choice_index(int *choice_ptr, char ch, MEVENT *event_ptr,  char** menu, int n_choices,int startx, int starty);
void update_flag(char ch, int *hb);
void clean_window(WINDOW* window);
int helpboxon(bool play, bool mode);
// game of life specific functions
void initialize_state(cell_t ** cell,game_structure_t initial_structure, int * num_alive_cell);
void set_cell(cell_t *cell,int pos, game_structure_t init_struct, int x, int y);
void display_cell(unsigned int x, unsigned int y, bool on);
void display_all_cell(cell_t *cell_map, int cell_size, int shift_x, int shift_y, float ratio_x, float ratio_y);
int compare(const void *a, const void *b);
void updateState(cell_t** current_cell, int* num_alive_cell);

// void report_choice(int mouse_x, int mouse_y, int *p_choice);

int main()
{
	cell_t *cell_map = NULL;
	int num_alive_cell = 0; // keep track of number of alive cell;
	int display_shift_x=0.0, display_shift_y=0.0;
	float ratio_x = 0.0, ratio_y = 0.0;

	int c, choice = -1;
	MEVENT event;
	int maxx, __attribute__((unused)) maxy, startx_menu, starty_menu, startx_game, starty_game,startx_helpbox, starty_helpbox;
	int ch, j, hb =1;
	/* Initialize curses */
	initscr();
	noecho();
	cbreak();	//Line buffering disabled. pass on everything
	getmaxyx(stdscr, maxy, maxx);
	startx_helpbox = 1;
	starty_helpbox = 1;
	startx_menu = ((maxx-42)/2);
	starty_menu = (maxy-HEIGHT_MENU)/2;
	startx_game =20;// (maxx-38)/2;
	if(hb == 1 && startx_game < 20) startx_game = 20;
	starty_game = 0;
	int height_game = maxy;
	int width_game = maxx;
	start_color();
	init_pair(1, COLOR_WHITE,COLOR_BLACK);
	init_pair(2, COLOR_WHITE,COLOR_RED);
	cell_area.height = (maxy-starty_game);
	cell_area.width = (maxx-startx_game);

	keypad(stdscr, TRUE);
	// menu_win = newwin(HEIGHT_MENU, WIDTH_MENU, starty_menu, startx_menu);
	helpbox = newwin(WIDTH_HELPBOX,HEIGHT_HELPBOX,startx_helpbox,startx_helpbox);
	game_win = newwin(cell_area.height, cell_area.width, starty_game,startx_game);
	// wbkgd(menu_win, COLOR_PAIR(1));
	// wbkgd(helpbox, COLOR_PAIR(1));
	wbkgd(game_win, COLOR_PAIR(2));

	werase(game_win);
	refresh();
	wrefresh(game_win);
	print_menu(game_win, 1, 3, main_menu_choices, startx_menu,starty_menu);

	// helpboxon();
	helpboxon(play, game_mode);

	// wmove(menu_win, 2, 2);
	// wrefresh(menu_win);
	// game window area

	// nodelay(stdscr, TRUE);// does not wait for the user to clock
	// Initialize game state
	/* Get all the mouse events */
	mousemask(ALL_MOUSE_EVENTS, NULL);
	nodelay(stdscr,false);
	game_state_t state = MAIN_MENU;
		while(shutdown_grame == false)
		{
			// get user input
			ch = getch();
			update_flag(ch,&hb);
			// if the terminal size change, modify the screen
			if(ch == KEY_RESIZE)
			{
				window_size_t previos_cell_area;
				previos_cell_area.height = cell_area.height;
				previos_cell_area.width = cell_area.width;

				endwin();
				initscr();
				erase();
				getmaxyx(stdscr, maxy, maxx);
				noecho();
				startx_helpbox = 1;
				starty_helpbox = 1;
				startx_menu = ((maxx-42)/2);
				starty_menu = (maxy-HEIGHT_MENU)/2;
				startx_game =20;// (maxx-38)/2;
				if(hb == 1 && startx_game < 20) startx_game = 20;
				starty_game = 0;
				int height_game = maxy;
				int width_game = maxx;
				start_color();
				init_pair(1, COLOR_RED,COLOR_BLACK);
				init_pair(2, COLOR_WHITE,COLOR_RED);

				keypad(stdscr, TRUE);
				// menu_win = newwin(HEIGHT_MENU, WIDTH_MENU, starty_menu, startx_menu);
				helpbox = newwin(WIDTH_HELPBOX,HEIGHT_HELPBOX,startx_helpbox,startx_helpbox);
				// wbkgd(menu_win, COLOR_PAIR(1));
				// wbkgd(helpbox, COLOR_PAIR(1));
				cell_area.height = (maxy-starty_game);
				cell_area.width = (maxx-startx_game);
				game_win = newwin(cell_area.height, cell_area.width, starty_game,startx_game);

				wbkgd(game_win, COLOR_PAIR(2));
				werase(game_win);
				refresh();
				helpboxon(play, game_mode);

				wrefresh(game_win);

				if(state == MAIN_MENU || state ==SETTING_MENU || state == INIT_STRUCTURE_MENU || state == SIMULATION_MODE_MENU )
				{
					if(state == MAIN_MENU)
					{
						print_menu(game_win, 1, 3, main_menu_choices, startx_menu,starty_menu);
					}
					else if(state == SETTING_MENU)
					{
								print_menu(game_win, choice,3, setting_menu_choices,startx_menu,starty_menu);
					}
					else if(state == INIT_STRUCTURE_MENU)
					{
								print_menu(game_win, choice,3, init_structe_menu_choices,startx_menu,starty_menu);

					}
					else if(state == SIMULATION_MODE_MENU)
					{
								print_menu(game_win, choice,2, simulation_mode_menu_choices,startx_menu,starty_menu);

					}
				}
				else // we are in game window
				{
					// display_all_cell

					// if(num_alive_cell >0)
					// {
					// 	display_shift_x = previos_cell_area.height;//(cell_area.height);///previos_cell_area.height);
					// 	display_shift_y = previos_cell_area.width;//(cell_area.width);///previos_cell_area.width);
					// 	ratio_x = -(cell_area.height-previos_cell_area.height);
					// 	ratio_y = -(cell_area.width-previos_cell_area.width);
					// 	// clean_window(game_win);
					// 	mvwprintw(game_win, 2, 0, "ratio: %d",cell_area.height);//cell_map[i].pos_x );
					// 	mvwprintw(game_win, 2, 15, "ratio: %d",cell_area.width);//cell_map[i].pos_y );
					// 	mvwprintw(game_win, 4, 0, "h before: %d",previos_cell_area.height);//cell_map[i].pos_x );
					// 	mvwprintw(game_win, 4, 15, "w before: %d",previos_cell_area.width);//cell_map[i].pos_y );
					// 	display_all_cell(cell_map, num_alive_cell, display_shift_x, display_shift_y, ratio_x, ratio_y);
					//
					// }
						mvwprintw(game_win, 0, 0, "don't modify during game :)\n press q to go to the main menu");//cell_map[i].pos_y );
						wrefresh(game_win);
						// sleep(3);
						// state = MAIN_MENU;



				}

				// helpboxon();
			}

			switch (state) {
				case MAIN_MENU:
					obtain_choice_index(&choice, ch, &event, main_menu_choices,3,startx_menu, starty_menu);
					if(choice == 2)
					{
						//TODO: remove
						state = END_GAME;
					}
					else if(choice == 0)
					{
						state = INITIALIZE_GAME;
						game_start = true;
						clean_window(game_win);
						break;
					}
					else if(choice == 1)
					{
						clean_window(game_win);
						state = SETTING_MENU;
						print_menu(game_win, choice,3, setting_menu_choices,startx_menu, starty_menu);
						break;
					}
					print_menu(game_win, choice,3, main_menu_choices,startx_menu,starty_menu);
					break;
				case SETTING_MENU:

					obtain_choice_index(&choice, ch, &event, setting_menu_choices,3,startx_menu, starty_menu);
					if(choice == 2)
					{
						state = MAIN_MENU;
						clean_window(game_win);
						print_menu(game_win, choice,3, main_menu_choices,startx_menu, starty_menu);
						break;
					}
					else if(choice == 0)
					{
						state = INIT_STRUCTURE_MENU;
						clean_window(game_win);
						print_menu(menu_win, choice,3, init_structe_menu_choices,startx_menu, starty_menu);
						break;
					}
					else if(choice == 1)
					{
						state = SIMULATION_MODE_MENU;
						clean_window(game_win);
						print_menu(menu_win, choice,2, simulation_mode_menu_choices,startx_menu, starty_menu);
						break;
					}
					print_menu(game_win, choice,3, setting_menu_choices,startx_menu, starty_menu);
					break;
				case INIT_STRUCTURE_MENU:
					obtain_choice_index(&choice, ch, &event, init_structe_menu_choices,3,startx_menu, starty_menu);
					if(choice >= 0 && choice <= 3)
					{
						init_structrue_choice = choice;
						state = SETTING_MENU;
						clean_window(game_win);
						print_menu(game_win, choice,3, setting_menu_choices,startx_menu, starty_menu);
						break;
					}
					print_menu(game_win, choice,3, init_structe_menu_choices,startx_menu, starty_menu);
					break;
				case SIMULATION_MODE_MENU:
					obtain_choice_index(&choice, ch, &event, simulation_mode_menu_choices,2,startx_menu, starty_menu);
					if(choice >= 0 && choice <= 1)
					{
						game_mode = (choice == 0) ? true : false;
						state = SETTING_MENU;
						clean_window(game_win);
						print_menu(game_win, choice,3, setting_menu_choices,startx_menu, starty_menu);
						helpboxon(play, game_mode);
						break;
					}
					print_menu(game_win, choice,2, simulation_mode_menu_choices,startx_menu, starty_menu);
					break;
				case INITIALIZE_GAME:
					// wclear(game_win);
					// wrefresh(game_win);
					if(init_structrue_choice <= 2)
					{
						initialize_state(&cell_map,init_structrue_choice, &num_alive_cell);
						state = START_SIMULATION;

					}
					// if(restart)
					// {
					// 	initialize_state(&cell_map,init_structrue_choice, &num_alive_cell);
					// 	state = START_SIMULATION;
					//
					// }
					// user defined option: TODO later

					break;
				case START_SIMULATION:
				if(quit)
				{
					state = MAIN_MENU;
					nodelay(game_win, FALSE);
					quit = false;
					clean_window(game_win);
					print_menu(game_win, choice,3, main_menu_choices,startx_menu,starty_menu);
				}
				else
				{
					if(restart)
					{
							clean_window(game_win);
							// state = INITIALIZE_GAME;
							initialize_state(&cell_map,init_structrue_choice, &num_alive_cell);
							// nodelay(game_win, FALSE);
							restart = false;


					}
					else
					{
						if(play)
						{
							if(game_mode == MANUAL)
							{
								if(previous_game_mode == AUTOMATIC)
								{
									nodelay(game_win, FALSE);


								}
								if(ch == KEY_RIGHT)
								{
									// update manually
									updateState(&cell_map, &num_alive_cell);
								}
							}
							else
							// automatic simulation
							{
								// helpboxoff();
								if(previous_game_mode == MANUAL)
								// activate no delay
								{
									nodelay(stdscr, TRUE);
								}
								updateState(&cell_map, &num_alive_cell);


							}
						}
					}
				}

					break;
				case END_GAME:

					shutdown_grame = true;

					break;
			// 	// default:
			//
			}
			//
		}
	end:

		// free memcpy
		endwin();
		if(cell_map!=NULL)
		{
			free(cell_map);
		}
	return 0;
}


void print_menu(WINDOW *menu_win, int highlight, int n_choices,char **menu_choices,int startx, int starty)
{
	int x, y, i;

	x = startx+ 2;
	y = starty +2;
	// box(menu_win, 0, 0);
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
	wrefresh(menu_win);
}

/* Report the choice according to mouse position */
void report_choice(int mouse_x, int mouse_y, int *p_choice,int n_choices, char ** menu_choices, int startx, int starty)
{
		int i,j, choice;

	i = startx+ 2+16;
	j = starty+ 3;

	// printf("%d:%d:%d\n", j + 0, j+1, j+2);
	// printf("%d\n", mouse_y);
	// printf("%d:%d:%d\n", j + 0, j+1, j+2);
	// printf("%d:%d:%ld\n", mouse_x, i,i+ strlen(menu_choices[0]));
	for(choice = 0; choice < n_choices; ++choice)


	// printw("%d:%d:%d\n",(mouse_y == j + choice),(mouse_x >= i),(mouse_x <= i + strlen(menu_choices[choice])));
		if((mouse_y == j + choice) && (mouse_x >= i) && (mouse_x <= i + strlen(menu_choices[choice])+5))
		{
			// if(choice == n_choices - 1)
			// 	*p_choice = -1;
			// else
			// 	*p_choice = choice + 1;
			*p_choice = choice;
		}
}



int helpboxon(bool play, bool mode)
	{
		clean_window(helpbox);
	wbkgd(helpbox, COLOR_PAIR(1));  // Michele correction!!!!!
	char * a = "activated";
	char * d = "deactivated";
	char *m = "manual";
	char * am = "automatic";
	wprintw(helpbox, "HelpBox\nq - quit\nr - restart\np - play:  \n %s \ns - play mode:\n %s", (play?a:d), (mode?m:am));  // Michele correction!!!!!
	wrefresh(helpbox);

	return 0;
}

int helpboxoff(void)
	{
	werase(helpbox);
	wrefresh(helpbox);
	return 0;
	}

void	obtain_choice_index(int *choice_ptr, char ch, MEVENT *event_ptr,  char** menu, int n_choices,int startx, int starty)
{
	*choice_ptr = -1;
	if(ch == -103)
	{
		if(getmouse(event_ptr) == OK)
		{
			/* When the user clicks left mouse button */
			if(event_ptr->bstate & BUTTON1_PRESSED)
			{
					report_choice(event_ptr->x + 1, event_ptr->y + 1, choice_ptr,n_choices, menu, startx, starty);
					refresh();
			}
		}
	}
}

void update_flag(char ch,int *hb)
{
	// mvwprintw(stdscr, 0,0, "game mode: %c: %d", ch, game_mode);
	// mvwprintw(stdscr, 1,0, "play: %c: %d", ch, play);
	// mvwprintw(stdscr, 2,0, "restart: %c: %d", ch, restart);

	if(ch == 'h')
	{
		if(*hb == 1)
		{
			helpboxoff();
			*hb = 0;
		}
		else
		{
			// helpboxon();
			helpboxon(play, game_mode);

			*hb = 1;
		}
	}
	if(ch == 'p')
	{
		play = !play;
		helpboxon(play, game_mode);

	}
	else if(ch == 'r')
	{
		restart = true;
	}
	else if(ch == 'q')
	{
		quit = !quit;
	}
	else if(ch == 's')
	{
		// helpboxoff();
		previous_game_mode = game_mode;
		game_mode = !game_mode;
		helpboxon(play, game_mode);

		// game_mode = MANUAL ? MANUAL : AUTOMATIC;
	}

	// mvwprintw(stdscr, 2,0, "game mode: %c: %d", ch, game_mode);
	// mvwprintw(stdscr, 1,0, "play: %c: %d", ch, play);
	// mvwprintw(stdscr, 2,0, "restart: %c: %d", ch, restart);
}

//cell map functions

void initialize_state(cell_t **cell,game_structure_t init_struct, int* num_alive_cell){
  // Cell intialized at the center of the screen
  switch (init_struct) {
    case R_pentomino:
      *cell = (cell_t*)malloc(init_struct_info[init_struct].num_alive_cell*sizeof(cell_t));
      set_cell(*cell,0,init_struct,2,3);
      set_cell(*cell,1,init_struct,2,4);
      set_cell(*cell,2,init_struct,3,2);
      set_cell(*cell,3,init_struct,3,3);
      set_cell(*cell,4,init_struct,4,3);
      *num_alive_cell = 5;

      break;
    case Diehard:
      *cell = (cell_t*)malloc(init_struct_info[init_struct].num_alive_cell*sizeof(cell_t));
      set_cell(*cell,0,init_struct,2,8);
      set_cell(*cell,1,init_struct,3,2);
      set_cell(*cell,2,init_struct,3,3);
      set_cell(*cell,3,init_struct,4,3);
      set_cell(*cell,4,init_struct,4,7);
      set_cell(*cell,5,init_struct,4,8);
      set_cell(*cell,6,init_struct,4,9);
      *num_alive_cell = 7;


      break;
    case Acorn:
      *cell = (cell_t*)malloc(init_struct_info[init_struct].num_alive_cell*sizeof(cell_t));
      set_cell(*cell,0,init_struct,2,3);
      set_cell(*cell,1,init_struct,3,5);
      set_cell(*cell,2,init_struct,4,2);
      set_cell(*cell,3,init_struct,4,3);
      set_cell(*cell,4,init_struct,4,6);
      set_cell(*cell,5,init_struct,4,7);
      set_cell(*cell,6,init_struct,4,8);
      *num_alive_cell = 7;
      break;
		case user_defined:
		// while(ch!=q)
		// {
		//
		// }
			break;

    default:
      printf("Invalid game type");
  }
}

void set_cell(cell_t *cell,int pos, game_structure_t init_struct, int x, int y){

  // put the cell in the middle
  unsigned int offset_width = (cell_area.width - init_struct_info[init_struct].width)/2;
  unsigned int offset_height = (cell_area.height - init_struct_info[init_struct].height)/2;
  cell[pos].pos_x = x + offset_height;
  cell[pos].pos_y = y + offset_width;
  cell[pos].alive = 1;
  display_cell(cell[pos].pos_x , cell[pos].pos_y, ALIVE);
}

void display_cell(unsigned int x, unsigned int y, bool on){
	on ? mvwaddch(game_win,x, y,'O') : mvwaddch(game_win,x, y,' ');
  wrefresh(game_win);
}

// TODO fix
void display_all_cell(cell_t *cell_map, int cell_size, int shift_x, int shift_y, float ratio_x, float ratio_y)
{


	int offset_x =  (int)(cell_map[0].pos_x * ratio_x/(float)shift_x);     // we find offset of one position and use that value to shift other position to prevent floating issue
	int offset_y =  (int)(cell_map[0].pos_y * ratio_y/(float)shift_y);
	for(int i = 0; i <1; i++)

	{
		cell_map[i].pos_x= cell_map[i].pos_x+offset_x;
		cell_map[i].pos_y= cell_map[i].pos_y+offset_y;
		mvwprintw(game_win, 0, 0, "%.2f",ratio_x);//cell_map[i].pos_x );
		mvwprintw(game_win, 0, 5, "%.2f",ratio_y);//cell_map[i].pos_y );

		wrefresh(game_win);

		// display_cell(0, 0, ALIVE);
	}

}

void clean_window(WINDOW* win_)
{
	werase(win_);
	wrefresh(win_);
}

int compare(const void *a, const void *b)
{
  cell_t f1 = *((cell_t*) a);
  cell_t f2 = *((cell_t*) b);
  // convert 3d to 2d
  int ind1 = f1.pos_x*cell_area.width+f1.pos_y;
  int ind2 = f2.pos_x*cell_area.width+f2.pos_y;


  return (ind1 - ind2);

}


void updateState(cell_t** current_cell, int* num_alive_cell)
{

  // loop through to the cell array
  size_t size_cc = *num_alive_cell; // current cell size
  // generate new matrix to put the 8 neighbours and thier cell
  size_t size_nc =size_cc*9;  // size of neighbour_sector vector
  cell_t *neighbour_sector = (cell_t *) calloc(size_nc,sizeof(cell_t)); // everything iniitalizes to zero
  int neighbour_count = 0;
  // compute the 8 neighbour and store everything in an array
  for(int t = 0; t <size_cc; t++)
	{
    for(int x = -1; x <= 1; x++ )
    {
      for(int y = -1; y<=1; y++)
      {
          neighbour_sector[neighbour_count].pos_x = (*current_cell)[t].pos_x+x;
          neighbour_sector[neighbour_count].pos_y =(*current_cell)[t].pos_y+y;
          if((x == 0 )& (y == 0))
          {
            neighbour_sector[neighbour_count].alive = 1;
          }
          neighbour_count+=1;
      }
    }
  }
  // sort the neighbour_sector vector based on x and y and the alive cell, so the cell from the current_cell vector wit the alive is always first
	// sort cellmao based on index, index refering to the 1d position of a cell from a 2d array
  qsort(neighbour_sector, size_nc, sizeof(cell_t), compare);

  int track_ind = (neighbour_sector[0].pos_x*cell_area.width+neighbour_sector[0].pos_y); // first index value
  int cell_count =1;
  int cell_alive = neighbour_sector[0].alive; // check whether the cell is alive
  // printf("Alive:x:%d\ty:%d\tindex:%d\n",neighbour_sector[0].pos_x,neighbour_sector[0].pos_y, track_ind);
  *num_alive_cell = 0;
	// loop to count the number of alive cells in the next generation and display
  for(int i = 1; i < size_nc; i++)
  {
    int ind  = (neighbour_sector[i].pos_x*cell_area.width+neighbour_sector[i].pos_y);
			// mvwprintw(game_win, i, 0, "%d",ind);//cell_map[i].pos_x );
			// mvwprintw(game_win, i, 9, "%d",neighbour_sector[i].alive);//cell_map[i].pos_x );

			wrefresh(game_win);
    if((track_ind == ind))
    {
      cell_count +=1;
      cell_alive += neighbour_sector[i].alive;
			// mvwprintw(game_win, i, 11, "%d:%d",cell_count,cell_alive);//cell_map[i].pos_x );
			// getch();
    }
    else
    {
      // apply game of life here
      // TODO: confirm whether it is better to reallocate or loop and allocate
      if(cell_count ==3 || ((cell_count==4) && cell_alive))
			{
				(*num_alive_cell)+=1;
				// mvwprintw(game_win, i-1, 0, "ALIVE:%d", *num_alive_cell);//cell_map[i].pos_x );
				// wrefresh(game_win);




      // {
			// 	mvwprintw(game_win, i, 15, "ALIVE");//cell_map[i].pos_x );
			//
      //   (*num_alive_cell)+=1;
      //   *current_cell = realloc(*current_cell, (*num_alive_cell)* sizeof(cell_t));
      //   (*current_cell)[(*num_alive_cell)-1].pos_x  = neighbour_sector[i-1].pos_x;
      //   (*current_cell)[(*num_alive_cell)-1].pos_y  = neighbour_sector[i-1].pos_y;
      //   (*current_cell)[(*num_alive_cell)-1].alive  = 1;
        display_cell(neighbour_sector[i-1].pos_x,neighbour_sector[i-1].pos_y, ALIVE);
      }
      else
      {
        display_cell(neighbour_sector[i-1].pos_x,neighbour_sector[i-1].pos_y, DEAD);
				// mvwprintw(game_win, i-1, 15, "DEAD");//cell_map[i].pos_x );
				// wrefresh(game_win);

      }
      cell_count = 1;
      track_ind = ind;
      cell_alive = neighbour_sector[i].alive;
			// mvwprintw(game_win, i, 11, "%d:%d",cell_count,cell_alive);//cell_map[i].pos_x );
			// wrefresh(game_win);

    }
  }
	// mvwprintw(game_win, size_nc, 11, "stop");//cell_map[i].pos_x );
	// wrefresh(game_win);
	// getch();


	// loop again and  create the new cellmap and store the value inside
	*current_cell = (cell_t *) calloc(*num_alive_cell,sizeof(cell_t)); // everything iniitalizes to zero
	track_ind = (neighbour_sector[0].pos_x*cell_area.width+neighbour_sector[0].pos_y); // first index value
	cell_count =1;
	cell_alive = neighbour_sector[0].alive; // check whether the cell is alive
	int current_cell_index = 0;
	for(int i = 1; i < size_nc; i++)
	{
		int ind  = (neighbour_sector[i].pos_x*cell_area.width+neighbour_sector[i].pos_y);
		if((track_ind == ind))
		{
			cell_count +=1;
			cell_alive += neighbour_sector[i].alive;
		}
		else
		{
			if(cell_count ==3 || ((cell_count==4) && cell_alive))
			{
				current_cell_index+=1;
				(*current_cell)[(current_cell_index)-1].pos_x  = neighbour_sector[i-1].pos_x;
				(*current_cell)[(current_cell_index)-1].pos_y  = neighbour_sector[i-1].pos_y;
				(*current_cell)[(current_cell_index)-1].alive  = 1;
				if(current_cell_index == (*num_alive_cell))
				{
					break;
				}
			}

			cell_count = 1;
			track_ind = ind;
			cell_alive = neighbour_sector[i].alive;
		}
	}


  // free neighbour_sector memory
  free(neighbour_sector);

}