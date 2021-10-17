#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void begin(int rows, int columns);
char *create(int rows, int columns);
double getRandomDoubleInRange(double min, double max);  // function to create random number between the min and max values defined
void display(int rows, int columns, char* simulation);
int countNeighborhood(int rows, int columns, int x, int y, char* simulation);
char* step(int rows, int columns, char* simulation);

int main(int argc, char* argv[])
{
  int rows = atoi(argv[1]);
  if(rows <= 0)
  {
    printf("Row count must be greater than zero. Was %d\n",rows);
    return 0;
  }
  rows += 2;  // to define the border of the matrix "."

  /*
  . . . .
  . 1 2 .
  . 1 2 . 
  . . . .
  */

  int columns = atoi(argv[2]);
  if(columns <= 0)
  {
    printf(" The number of columns must be greater than 0. Was %d\n", columns);
    return -1;
  }
  columns += 2;
  begin(rows, columns);
}


void display(int rows, int columns, char* simulation)
{
  printf("\n\n\n"); // to separate from the previous simulation
  for (int y=1; y<rows-1; y++)  // 1 and -1 only to print the visible matrix
  {
    for(int x=1; x<columns-1; x++)
    {
      printf("%c ",*(simulation+y*columns+x));
    }
    printf("\n");
  }

}

int countNeighborhood(int rows, int columns, int x, int y, char* simulation)
{
  int count = 0;

  int pivot = y*columns+x;  // to get access to the home cell

   /*
  . . . . . .
  . 1 2 3 4 .
  . 1 2 3 4 . 
  . 1 2 3 4 .
  . 1 2 3 4 .
  . . . . . .
  */

  for(int i = -1; i<=1; i++)  // considering a negative value of y or x, we move up(y) or left(x)
  {
    for(int j = -1; j<=1; j++)
    {
      char c = *(simulation + pivot + (i*columns)+j);
      if(c == '#') count++;
    }
  }
  return count;
}

char* step(int rows, int columns, char* prevSimulation)
{
  char* steppedSimulation = calloc(rows*columns, sizeof(int));
  if(steppedSimulation == NULL) return NULL;

  for(int y=1; y<rows-1; y++)
  {
    for(int x=1; x<columns-1; x++)
    {
      int live = countNeighborhood(rows,columns,x,y,prevSimulation);
      char cell = *(prevSimulation+y*columns+x);
      if(cell == '#') live--;
      *(steppedSimulation+y*columns+x) = cell;
       
      if(live < 2)
      {
        *(steppedSimulation+y*columns+x) = '.';
      }
      else if((live == 2 || live == 3) && cell == '#')
      {
        *(steppedSimulation+y*columns+x) = '#';
      }
      else if(live > 3 && cell == '#')
      {
        *(steppedSimulation+y*columns+x) = '.';
      }
      else if(live == 3 && cell == '.')
      {
        *(steppedSimulation+y*columns+x) = '#';
      }
    }
  }
  
  return steppedSimulation;
}

void begin (int rows, int columns)
{
  puts("Beginning!");
  //char* simulation = (char*)calloc(rows*columns, sizeof(char));
  char* simulation = create(rows, columns);
  if(simulation == NULL) return;
  display(rows, columns, simulation);


  while(1)
  {
    char* newSim = step(rows, columns, simulation);
    if(newSim == NULL) return;

    free(simulation);
    simulation = newSim;
    display(rows, columns,simulation);
    sleep (1); //pause 1 sec each simulation
  }
}

double getRandomDoubleInRange(double min, double max)
{
  return ((double)rand()/RAND_MAX)*(max-min)+min;  //random decimal number
}

char *create(int rows, int columns)
{
  char* simulation = (char*)calloc(rows*columns, sizeof(char));
  if(simulation == NULL) // check if the memory for the simulation exists
  {
    return NULL;
  }

  for(int y=1; y<rows-1; y++)
  {
    for(int x=1; x<columns-1; x++)
    {
      //*(simulation + y*columns + x) = 'A';  print 'A' in the location of memory indicated
      if(getRandomDoubleInRange(0.0,1.0) <= 0.35)
      {
        *(simulation+y*columns+x) = '#'; // live cells
      }
      else
      {
        *(simulation+y*columns+x)= '.'; // dead cells
      }
    }
  }
  return simulation;
}