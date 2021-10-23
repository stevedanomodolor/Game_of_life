#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>


#define NUM_STRUCTURES  3
#define CELL_PAD 1
#define ALIVE 1
#define DEAD 0
#define ACTIVATE_DEBUG 1


typedef enum game_structure{
  R_pentomino, Diehard,Acorn}game_structure_t;

// cols -> y lines -> x
/*
 ----------------> y cols
|   **********************
|   *                    *
|   *                    *
|   *                    *
|   *                    *
|   *                    *
x   **********************
 */

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
typedef struct cell {
  int alive;
  int pos_x;
  int pos_y;
}cell_t;

init_struct_t init_struct_info[NUM_STRUCTURES] = {{5,5,5}, // R_pentomino
                                                        {5,10,7}, //Diehard
                                                        {5,9,7}}; // Acorn


// Function declaration
void initialize_state(cell_t ** cell,game_structure_t initial_structure, int * num_alive_cell);
void set_cell(cell_t *cell,int pos, game_structure_t init_struct, int x, int y);
void display_cell(unsigned int x, unsigned int y, bool on);
void updateState(cell_t** current_cell, int *num_alive_cell);
int main(){
  cell_t *cell_map;
  int num_alive_cell = 0; // keep track of number of alive cell;

  int num_simulation = 10000;
  // initscr();
  // we add cell pad to our cell, up, bottom, right and left
  // window_size_t cell_area = {LINES+CELL_PAD*2,COLS+CELL_PAD*2};

   cell_area.height = 10;
   cell_area.width = 10;


  // // Memory allocation
  // current_cell = (char *) calloc(cell_area.height*cell_area.width, sizeof(char));
  // next_cell = (char *) calloc(cell_area.height*cell_area.width,sizeof(char));
  // // for(int i = 0; i < cell_area.height; i++){
  // //   cell[i] = (char *) calloc(cell_area.width, sizeof(char)); // set all values to zero
  // //   next_cell[i] = (char *) calloc(cell_area.width,sizeof(char)); // set all values to zero
  // // }
  // // Initialize state
  // initialize_state(current_cell, cell_area,Acorn);
  initialize_state(&cell_map,R_pentomino, &num_alive_cell);

  // Perform simulation
  for(int i = 0; i < 1; i++){
    updateState(&cell_map, &num_alive_cell);
  }

  // free memory
  // for(int i = 0; i <cell_area.height; i++){
  //   free(cell[i]);
  //   free(next_cell[i]);
  // }
  getch();
  free(cell_map);
  // free(next_cell);
  printf("Memory freed");
  // endwin();
  return 0;
}


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
// displays X if the cell is activated
void display_cell(unsigned int x, unsigned int y, bool on){
  // on ? mvaddch(x, y,'X') : mvaddch(x, y,' ');
  // refresh();
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
//
// void copy_reset_cell(char* current_cell, char* next_cell, window_size_t cell_area){
//   // copy cell and reset
//     memcpy(current_cell,next_cell, sizeof(char)*cell_area.width*cell_area.height);
//     memset(next_cell, DEAD,sizeof(char)*cell_area.width*cell_area.height);// clear all cells
// }
//
//
void updateState(cell_t** current_cell, int* num_alive_cell){


  #if ACTIVATE_DEBUG
    printf("**********************************\n");
    printf("Original cell\n");
    for(int t = 0; t < (*num_alive_cell); t++)
    {
      printf("x:%d\ty:%d\talive:%d\n",(*current_cell)[t].pos_x,(*current_cell)[t].pos_y, (*current_cell)[t].alive );
    }
  #endif

  // loop through to the cell array
  size_t size_cc = *num_alive_cell; // current cell size
  // generate new matrix to put the 8 neighbours and thier cell
  size_t size_nc =size_cc*9;  // size of neighbour_sector vector
  cell_t *neighbour_sector = (cell_t *) calloc(size_nc,sizeof(cell_t)); // everything iniitalizes to zero
  int neighbour_count = 0;
  // compute the 8 neighbour and store everything in an array
  for(int t = 0; t <size_cc; t++){
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

  #if ACTIVATE_DEBUG
    printf("**********************************\n");
    printf("Neighbour cell before sorted\n");
    for(int i = 0; i <size_nc; i++)
    {
      printf("x:%d\ty:%d\tindex:%d\talive:%d\n",neighbour_sector[i].pos_x,neighbour_sector[i].pos_y,(neighbour_sector[i].pos_x*cell_area.width+neighbour_sector[i].pos_y),neighbour_sector[i].alive);
    }
  #endif

  // sort the neighbour_sector vector based on x and y and the alive cell, so the cell from the current_cell vector wit the alive is always first
  qsort(neighbour_sector, size_nc, sizeof(cell_t), compare);
  #if ACTIVATE_DEBUG
    printf("**********************************\n");
    printf("Neighbour cell after sorted\n");

    for(int i = 0; i <size_nc; i++)
    {
      printf("x:%d\ty:%d\tindex:%d\talive:%d\n",neighbour_sector[i].pos_x,neighbour_sector[i].pos_y,(neighbour_sector[i].pos_x*cell_area.width+neighbour_sector[i].pos_y),neighbour_sector[i].alive);
    }
  #endif
  printf("**********************************\n");
  printf("Update process\n");

  int track_ind = (neighbour_sector[0].pos_x*cell_area.width+neighbour_sector[0].pos_y); // first index value
  int cell_count =1;
  int cell_alive = neighbour_sector[0].alive; // check whether the cell is alive
  // printf("Alive:x:%d\ty:%d\tindex:%d\n",neighbour_sector[0].pos_x,neighbour_sector[0].pos_y, track_ind);
  *num_alive_cell = 0;
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
      // apply game of life here
      // TODO: confirm whether it is better to reallocate or loop and allocate
      if(cell_count ==3 || ((cell_count==4) && cell_alive))
      {
        printf("Alive:x:%d\ty:%d\tindex:%d\n",neighbour_sector[i-1].pos_x,neighbour_sector[i-1].pos_y, track_ind);
        (*num_alive_cell)+=1;
        *current_cell = realloc(*current_cell, (*num_alive_cell)* sizeof(cell_t));
        (*current_cell)[(*num_alive_cell)-1].pos_x  = neighbour_sector[i-1].pos_x;
        (*current_cell)[(*num_alive_cell)-1].pos_y  = neighbour_sector[i-1].pos_y;
        (*current_cell)[(*num_alive_cell)-1].alive  = 1;
        display_cell(neighbour_sector[i-1].pos_x,neighbour_sector[i-1].pos_y, ALIVE);
      }
      else
      {
        printf("Dead:x:%d\ty:%d\tindex:%d\n",neighbour_sector[i].pos_x,neighbour_sector[i].pos_y, track_ind);
        display_cell(neighbour_sector[i].pos_x,neighbour_sector[i].pos_y, DEAD);
      }
      cell_count = 1;
      track_ind = ind;
      cell_alive = neighbour_sector[i].alive;
    }
  }

  #if ACTIVATE_DEBUG
    printf("Next generation\n");
    printf("**********************************\n");
    for(int t = 0; t < (*num_alive_cell); t++)
    {
      printf("x:%d\ty:%d\talive:%d\n",(*current_cell)[t].pos_x,(*current_cell)[t].pos_y, (*current_cell)[t].alive );
    }
    printf("num_alive_cell:%d\n", *num_alive_cell);
  #endif
  // free neighbour_sector memory
  free(neighbour_sector);

}

//   // count the amount of time a cell occurs
//   int cell_count = 0;
//   int size_na = 0;
//   int cell_alive = 0; // index and n keep track of the cell that is alive
//   for(int i = 0; i<size_nc; i++)
//   {
//     size_t size = size;
//
//     for(int j = 0; j <size_nc; i++)
//     {
//       if(neighbour_sector[i].pos_x == neighbour_sector[j].pos_x && neighbour_sector[i].pos_y == neighbour_sector[j].pos_y)
//       {
//         cell_count+=1;
//         // know if the cell was previously alive
//         cell_alive+=neighbour_sector[i].alive;
//         // if the cell repeats more that 3 time, dont keep looping
//
//         if(cell_count >4)
//         {
//           display_cell(neighbour_sector[i].pos_x,neighbour_sector[i].pos_y,DEAD);
//           break;
//         }
//       }
//     }
//     // apply the game of life theory
//     if(cell_count == 3)
//     {
//       // insert cell into cell_map
//       display_cell(neighbour_sector[i].pos_x,neighbour_sector[i].pos_y,ALIVE);
//       *next_cell = realloc(*next_cell, number_alive_cell* sizeof(int));
//
//     }
//     else if(cell_count ==4 && cell_alive >= 1)
//     {
//       display_cell(neighbour_sector[i].pos_x,neighbour_sector[i].pos_y,ALIVE);
//       *next_cell = realloc(*next_cell, number_alive_cell* sizeof(int));
//     }
//     else
//     {
//       display_cell(current_cell[].pos_x, current_cell[])
//     }
//     cell_count = 0;
//     cell_alive = 0;
//   }
//
// }
