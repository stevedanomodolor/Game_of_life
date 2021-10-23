#ifndef INITIAL_STRUCTURES_H
#define INITIAL_STRUCTURES_H

#define ALIVE 1
#define DEAD 0
#define NUM_INIT_STRUCT 3

// cell map type
typedef struct cell
{
  int pos_x;
  int pos_y;
  int alive;
}cell_t;
typedef struct window_size
{
  int width;
  int height;
}window_size_t;


window_size_t initial_structures_size[NUM_INIT_STRUCT] = {{5,5}, // R_pentomino
                                                          {5,10}, //Diehard
                                                          {5,9}}; // Acorn
cell_t R_pentomino[5] = { {1,2,ALIVE},
                          {1,3,ALIVE},
                          {2,1,ALIVE},
                          {2,2,ALIVE},
                          {3,2,ALIVE}};
cell_t Diehard[7] = { {1,7,ALIVE},
                      {2,1,ALIVE},
                      {2,2,ALIVE},
                      {3,2,ALIVE},
                      {3,6,ALIVE},
                      {3,7,ALIVE},
                      {3,8,ALIVE}};


cell_t Acorn[7]  = { {1,2,ALIVE},
                    {2,4,ALIVE},
                    {3,1,ALIVE},
                    {3,2,ALIVE},
                    {3,5,ALIVE},
                    {3,6,ALIVE},
                    {3,7,ALIVE}};





#endif
