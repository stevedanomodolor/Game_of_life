/*
 *
 * @file conway_functions.c
 * @brief Implementation of conway_functions
 *
 * This file contains the implementation of the game of life: cell initialization, and cell update and display
 * Project: Game of life
 *
 */

#include "conway_functions.h"


bool cellmap_initialized_correctly(cell_t ** cellmap_ptr,simulation_structure_t *simulation_structure,  simulation_structure_names choice, window_property_t game_window, unsigned int* num_alive_cell,WINDOW* window, char *error_msg)
{
  /****coder 3*****/
  switch (choice)
  {
    case R_pentomino:
      *cellmap_ptr = (cell_t*)malloc(simulation_structure[choice].num_alive_cell*sizeof(cell_t));
      set_cell(*cellmap_ptr,0,simulation_structure[choice],game_window,2,3, window);
      set_cell(*cellmap_ptr,1,simulation_structure[choice],game_window,2,4,window);
      set_cell(*cellmap_ptr,2,simulation_structure[choice],game_window,3,2,window);
      set_cell(*cellmap_ptr,3,simulation_structure[choice],game_window,3,3,window);
      set_cell(*cellmap_ptr,4,simulation_structure[choice],game_window,4,3,window);
      *num_alive_cell = simulation_structure[choice].num_alive_cell;
      break;
    case Diehard:
      *cellmap_ptr = (cell_t*)malloc(simulation_structure[choice].num_alive_cell*sizeof(cell_t));
      set_cell(*cellmap_ptr,0,simulation_structure[choice],game_window,2,8,window);
      set_cell(*cellmap_ptr,1,simulation_structure[choice],game_window,3,2,window);
      set_cell(*cellmap_ptr,2,simulation_structure[choice],game_window,3,3,window);
      set_cell(*cellmap_ptr,3,simulation_structure[choice],game_window,4,3,window);
      set_cell(*cellmap_ptr,4,simulation_structure[choice],game_window,4,7,window);
      set_cell(*cellmap_ptr,5,simulation_structure[choice],game_window,4,8,window);
      set_cell(*cellmap_ptr,6,simulation_structure[choice],game_window,4,9,window);
      *num_alive_cell = simulation_structure[choice].num_alive_cell;
      break;
    case Acorn:
      *cellmap_ptr = (cell_t*)malloc(simulation_structure[choice].num_alive_cell*sizeof(cell_t));
      set_cell(*cellmap_ptr,0,simulation_structure[choice],game_window,2,3,window);
      set_cell(*cellmap_ptr,1,simulation_structure[choice],game_window,3,5,window);
      set_cell(*cellmap_ptr,2,simulation_structure[choice],game_window,4,2,window);
      set_cell(*cellmap_ptr,3,simulation_structure[choice],game_window,4,3,window);
      set_cell(*cellmap_ptr,4,simulation_structure[choice],game_window,4,6,window);
      set_cell(*cellmap_ptr,5,simulation_structure[choice],game_window,4,7,window);
      set_cell(*cellmap_ptr,6,simulation_structure[choice],game_window,4,8,window);
      *num_alive_cell = simulation_structure[choice].num_alive_cell;
      break;
   case Glider:
      *cellmap_ptr = (cell_t*)malloc(simulation_structure[choice].num_alive_cell*sizeof(cell_t));
      set_cell(*cellmap_ptr,0,simulation_structure[choice],game_window,2,3,window);
      set_cell(*cellmap_ptr,1,simulation_structure[choice],game_window,3,4,window);
      set_cell(*cellmap_ptr,2,simulation_structure[choice],game_window,4,2,window);
      set_cell(*cellmap_ptr,3,simulation_structure[choice],game_window,4,3,window);
      set_cell(*cellmap_ptr,4,simulation_structure[choice],game_window,4,4,window);
      *num_alive_cell = simulation_structure[choice].num_alive_cell;
      break;
  case LightWeigth_spaceship:
      *cellmap_ptr = (cell_t*)malloc(simulation_structure[choice].num_alive_cell*sizeof(cell_t));
      set_cell(*cellmap_ptr,0,simulation_structure[choice],game_window,2,3,window);
      set_cell(*cellmap_ptr,1,simulation_structure[choice],game_window,2,6,window);
      set_cell(*cellmap_ptr,2,simulation_structure[choice],game_window,3,7,window);
      set_cell(*cellmap_ptr,3,simulation_structure[choice],game_window,4,3,window);
      set_cell(*cellmap_ptr,4,simulation_structure[choice],game_window,4,7,window);
      set_cell(*cellmap_ptr,5,simulation_structure[choice],game_window,5,4,window);
      set_cell(*cellmap_ptr,6,simulation_structure[choice],game_window,5,5,window);
      set_cell(*cellmap_ptr,7,simulation_structure[choice],game_window,5,6,window);
      set_cell(*cellmap_ptr,8,simulation_structure[choice],game_window,5,7,window);
      *num_alive_cell = simulation_structure[choice].num_alive_cell;

    break;
  case Pulsar:
    *cellmap_ptr = (cell_t*)malloc(simulation_structure[choice].num_alive_cell*sizeof(cell_t));
    set_cell(*cellmap_ptr,0,simulation_structure[choice],game_window,6,2,window);
    set_cell(*cellmap_ptr,1,simulation_structure[choice],game_window,6,3,window);
    set_cell(*cellmap_ptr,2,simulation_structure[choice],game_window,6,4,window);
    set_cell(*cellmap_ptr,3,simulation_structure[choice],game_window,7,4,window);
    set_cell(*cellmap_ptr,4,simulation_structure[choice],game_window,12,2,window);
    set_cell(*cellmap_ptr,5,simulation_structure[choice],game_window,12,3,window);
    set_cell(*cellmap_ptr,6,simulation_structure[choice],game_window,12,4,window);
    set_cell(*cellmap_ptr,7,simulation_structure[choice],game_window,11,4,window);


    set_cell(*cellmap_ptr,8,simulation_structure[choice],game_window,2,6,window);
    set_cell(*cellmap_ptr,9,simulation_structure[choice],game_window,3,6,window);
    set_cell(*cellmap_ptr,10,simulation_structure[choice],game_window,4,6,window);
    set_cell(*cellmap_ptr,11,simulation_structure[choice],game_window,4,7,window);

    set_cell(*cellmap_ptr,12,simulation_structure[choice],game_window,2,12,window);
    set_cell(*cellmap_ptr,13,simulation_structure[choice],game_window,3,12,window);
    set_cell(*cellmap_ptr,14,simulation_structure[choice],game_window,4,12,window);
    set_cell(*cellmap_ptr,15,simulation_structure[choice],game_window,4,11,window);
    //
    set_cell(*cellmap_ptr,16,simulation_structure[choice],game_window,14,6,window);
    set_cell(*cellmap_ptr,17,simulation_structure[choice],game_window,15,6,window);
    set_cell(*cellmap_ptr,18,simulation_structure[choice],game_window,16,6,window);
    set_cell(*cellmap_ptr,19,simulation_structure[choice],game_window,14,7,window);
    set_cell(*cellmap_ptr,20,simulation_structure[choice],game_window,14,12,window);
    set_cell(*cellmap_ptr,21,simulation_structure[choice],game_window,15,12,window);
    set_cell(*cellmap_ptr,22,simulation_structure[choice],game_window,16,12,window);
    set_cell(*cellmap_ptr,23,simulation_structure[choice],game_window,14,11,window);



    set_cell(*cellmap_ptr,24,simulation_structure[choice],game_window,6,15,window);
    set_cell(*cellmap_ptr,25,simulation_structure[choice],game_window,6,16,window);
    set_cell(*cellmap_ptr,26,simulation_structure[choice],game_window,6,14,window);
    set_cell(*cellmap_ptr,27,simulation_structure[choice],game_window,7,14,window);
    set_cell(*cellmap_ptr,28,simulation_structure[choice],game_window,12,15,window);
    set_cell(*cellmap_ptr,29,simulation_structure[choice],game_window,12,16,window);
    set_cell(*cellmap_ptr,30,simulation_structure[choice],game_window,12,14,window);
    set_cell(*cellmap_ptr,31,simulation_structure[choice],game_window,11,14,window);

    set_cell(*cellmap_ptr,32,simulation_structure[choice],game_window,6,7,window);
    set_cell(*cellmap_ptr,33,simulation_structure[choice],game_window,6,8,window);
    set_cell(*cellmap_ptr,34,simulation_structure[choice],game_window,6,10,window);
    set_cell(*cellmap_ptr,35,simulation_structure[choice],game_window,6,11,window);
    set_cell(*cellmap_ptr,36,simulation_structure[choice],game_window,7,6,window);
    set_cell(*cellmap_ptr,37,simulation_structure[choice],game_window,7,8,window);
    set_cell(*cellmap_ptr,38,simulation_structure[choice],game_window,7,10,window);
    set_cell(*cellmap_ptr,39,simulation_structure[choice],game_window,7,12,window);
    set_cell(*cellmap_ptr,40,simulation_structure[choice],game_window,8,6,window);
    set_cell(*cellmap_ptr,41,simulation_structure[choice],game_window,8,7,window);
    set_cell(*cellmap_ptr,42,simulation_structure[choice],game_window,8,11,window);
    set_cell(*cellmap_ptr,43,simulation_structure[choice],game_window,8,12,window);


    set_cell(*cellmap_ptr,44,simulation_structure[choice],game_window,10,6,window);
    set_cell(*cellmap_ptr,45,simulation_structure[choice],game_window,10,7,window);
    set_cell(*cellmap_ptr,46,simulation_structure[choice],game_window,10,11,window);
    set_cell(*cellmap_ptr,47,simulation_structure[choice],game_window,10,12,window);
    set_cell(*cellmap_ptr,48,simulation_structure[choice],game_window,11,6,window);
    set_cell(*cellmap_ptr,49,simulation_structure[choice],game_window,11,8,window);
    set_cell(*cellmap_ptr,50,simulation_structure[choice],game_window,11,10,window);
    set_cell(*cellmap_ptr,51,simulation_structure[choice],game_window,11,12,window);
    set_cell(*cellmap_ptr,52,simulation_structure[choice],game_window,12,7,window);
    set_cell(*cellmap_ptr,53,simulation_structure[choice],game_window,12,8,window);
    set_cell(*cellmap_ptr,54,simulation_structure[choice],game_window,12,10,window);
    set_cell(*cellmap_ptr,55,simulation_structure[choice],game_window,12,11,window);

    *num_alive_cell = simulation_structure[choice].num_alive_cell;
    break;
    default:
      strcpy(error_msg,"invalid game type");
      return false;
  }
  return true;
}
void set_cell(cell_t *cellmap,unsigned int pos, simulation_structure_t sim_stru, window_property_t game_window,unsigned int x, unsigned int y, WINDOW *window)
{
  /****coder 3*****/
    unsigned int offset_width = (game_window.width - sim_stru.width)/2;
    unsigned int offset_height = (game_window.height - sim_stru.height)/2;
    cellmap[pos].pos_x = x + offset_height;
    cellmap[pos].pos_y = y + offset_width;
    cellmap[pos].alive = 1;
    display_cell(window, cellmap[pos].pos_x , cellmap[pos].pos_y, ALIVE);
}
void display_cell(WINDOW *window, unsigned int x, unsigned int y, bool is_alive)
{
  /****coder 3*****/
  is_alive ? mvwaddch(window,x, y,'X') : mvwaddch(window,x, y,' ');
  wrefresh(window);
}
int comparator(const void *a, const void *b, void *param)
{
  /****coder 3*****/
  window_property_t* game_window = (window_property_t*)param;
  cell_t f1 = *((cell_t*) a);
  cell_t f2 = *((cell_t*) b);
  // convert 3d to 2d
  int ind1 = f1.pos_x*game_window->width+f1.pos_y;
  int ind2 = f2.pos_x*game_window->width+f2.pos_y;
  return (ind1 - ind2);
}
bool cellmap_updated_successfully(cell_t** current_cell_ptr, unsigned int* num_alive_cell, window_property_t game_window, char error_msg[MSG_LEN], WINDOW *window)
{
  /****coder 1*****/
  /*create an array of cells containing the neighbours of each all cell and the cell itself*/
  unsigned int size_nc =(*num_alive_cell)*9;  // size of neighbour_sector vector
  cell_t *neighbour_cellmap = (cell_t *) calloc(size_nc,sizeof(cell_t)); // allocate and initialize array value to zero
  /*check that memory was allocated correctly*/
  if(neighbour_cellmap== NULL)
  {
    strcpy(error_msg,"could not allocate neighbour array memory correctly");
    return false;
  }
  unsigned int neighbour_count = 0;
  /*find the position of each of the eight neighbour and the cell itself and store everything in the  array*/
  for(int t = 0; t <(*num_alive_cell); t++)
	{
    for(int x = -1; x <= 1; x++ )
    {
      for(int y = -1; y<=1; y++)
      {
          neighbour_cellmap[neighbour_count].pos_x = (*current_cell_ptr)[t].pos_x+x;
          neighbour_cellmap[neighbour_count].pos_y =(*current_cell_ptr)[t].pos_y+y;
          if((x == 0 )& (y == 0))
          {
            neighbour_cellmap[neighbour_count].alive = 1;
          }
          neighbour_count+=1;
      }
    }
  }
	/* sort cellmap based on the 2d indexing, index refering to the 1d position of a cell from a 2d array*/
  qsort_r(neighbour_cellmap, size_nc, sizeof(cell_t), comparator, &game_window);

  unsigned int track_ind = (neighbour_cellmap[0].pos_x*game_window.width+neighbour_cellmap[0].pos_y); // first index value
  unsigned int cell_count =1;
  unsigned int cell_alive = neighbour_cellmap[0].alive; // check whether the cell is alive
  unsigned int ind = 0; // current index
  *num_alive_cell = 0;

	/* loop to count the number of alive cells in the next generation and display turn on/off cell on display*/
  for(int i = 1; i < size_nc; i++)
  {
    ind  = (neighbour_cellmap[i].pos_x*game_window.width+neighbour_cellmap[i].pos_y);
    /* count untill the index changes and then apply the conway rule*/
    if((track_ind == ind))
    {
      cell_count +=1;
      cell_alive += neighbour_cellmap[i].alive;
    }
    else
    {
      /*APPLICATION OF THE GAME OF LIDE RULES
       * The rules based on the neighbour_count is as follows:
       * Rule 1: a cells is alive in the next generation when it shares 3 neighbours
       * Rule 2: a cell is alive in the next generation when it shares 4 neighbour and it is alive
       */
       if(cell_count ==3 || ((cell_count==4) && cell_alive))
			    {
				     (*num_alive_cell)+=1;
             display_cell(window,neighbour_cellmap[i-1].pos_x,neighbour_cellmap[i-1].pos_y, ALIVE);
          }
        else
          {
            display_cell(window,neighbour_cellmap[i-1].pos_x,neighbour_cellmap[i-1].pos_y, DEAD);
      }
      cell_count = 1;
      track_ind = ind;
      cell_alive = neighbour_cellmap[i].alive;
    }
  }
	/* loop again and  create the new cellmap and store the value inside */
	*current_cell_ptr = (cell_t *) calloc(*num_alive_cell,sizeof(cell_t)); // everything iniitalizes to zero
  /* make sure we can allocate memory*/
  if(current_cell_ptr== NULL)
  {
    strcpy(error_msg,"could not allocate cellmap array memory correctly");
    return false;
  }
	track_ind = (neighbour_cellmap[0].pos_x*game_window.width+neighbour_cellmap[0].pos_y); // first index value
	cell_count =1;
	cell_alive = neighbour_cellmap[0].alive; // check whether the cell is alive
	unsigned int current_cell_index = 0;
  ind = 0;
	for(int i = 1; i < size_nc; i++)
	{
		ind  = (neighbour_cellmap[i].pos_x*game_window.width+neighbour_cellmap[i].pos_y);
		if((track_ind == ind))
		{
			cell_count +=1;
			cell_alive += neighbour_cellmap[i].alive;
		}
		else
		{
			if(cell_count ==3 || ((cell_count==4) && cell_alive))
			{
				current_cell_index+=1;
				(*current_cell_ptr)[(current_cell_index)-1].pos_x  = neighbour_cellmap[i-1].pos_x;
				(*current_cell_ptr)[(current_cell_index)-1].pos_y  = neighbour_cellmap[i-1].pos_y;
				(*current_cell_ptr)[(current_cell_index)-1].alive  = 1;
				if(current_cell_index == (*num_alive_cell))
				{
          /* to prevent looping through the whole code if we found all the alive cells before finishing the loop*/
					break;
				}
			}
			cell_count = 1;
			track_ind = ind;
			cell_alive = neighbour_cellmap[i].alive;
		}
	}


  // free neighbour_sector memory
  free(neighbour_cellmap);
  return true;

}
