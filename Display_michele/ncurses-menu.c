// #include <curses.h>
#include <stdio.h>
#include <ncurses.h>

#include <stdlib.h>
#include <string.h>

typedef struct {
  void *x; // if NULL, this is the last element; defining the pointer as a void, is not possible to call an alement pointed by the pointer without a cast
  void *y; // if NULL, this is the first element
} element_t;

// Create a new list, with one element newly created with "name"
// void matrix_new1(int **a) {
  // define the size of the matrix
  int m = 5;
  int n = 5;
	// allocate the memory of matrix
  a = (int **) malloc(m * sizeof(int *));
  for(int i=0; i<m; i++)
	{
		a[i] = (int *) malloc(n * sizeof(int));
	}
  // write the elements in the matrix
  int matrix[5][5] = {{0, 0, 0, 0, 0},
                      {0, 0, 1, 1, 0},
                      {0, 1, 1, 0, 0},
                      {0, 0, 1, 0, 0},
                      {0, 0, 0, 0, 0}
                      };

	for(int i=0; i<m; i++)
	{
		for(int j=0; j<n; j++)
		{
            int *x = &matrix[i][j];
            if(*x == 1)
            {
               mvprintw(i+22,j+11,"#");
            }
		}
	}
    mvprintw(21,9,"_________");
    mvprintw(26,9,"_________");
    mvprintw(22,9, "|");
    mvprintw(23,9, "|");
    mvprintw(24,9, "|");
    mvprintw(25,9, "|");
    mvprintw(26,9, "|");
    mvprintw(22,17, "|");
    mvprintw(23,17, "|");
    mvprintw(24,17, "|");
    mvprintw(25,17, "|");
    mvprintw(26,17, "|");

  // deallocate the memory
  for(int i=0; i<m; i++)
	{
		free(a[i]);
	}
	free(a);
}

// void matrix_new2(int **a) {
  // define the size of the matrix
  int m = 5;
  int n = 10;
	// allocate the memory of matrix
  a = (int **) malloc(m * sizeof(int *));
  for(int i=0; i<m; i++)
	{
		a[i] = (int *) malloc(n * sizeof(int));
	}
  // write the elements in the matrix
  int matrix[5][10] = { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
                        {0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 1, 0, 0, 0, 1, 1, 1, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
                      };

	for(int i=0; i<m; i++)
	{
		for(int j=0; j<n; j++)
		{
            int *x = &matrix[i][j];
            if(*x == 1)
            {
                mvprintw(i+22,j+30,"#");
            }
		}
	}
    mvprintw(21,29,"_____________");
    mvprintw(26,29,"_____________");
    mvprintw(22,29, "|");
    mvprintw(23,29, "|");
    mvprintw(24,29, "|");
    mvprintw(25,29, "|");
    mvprintw(26,29, "|");
    mvprintw(22,41, "|");
    mvprintw(23,41, "|");
    mvprintw(24,41, "|");
    mvprintw(25,41, "|");
    mvprintw(26,41, "|");

  // deallocate the memory
  for(int i=0; i<m; i++)
	{
		free(a[i]);
	}
	free(a);
}

// void matrix_new3(int **a) {
  // define the size of the matrix
  int m = 5;
  int n = 9;
	// allocate the memory of matrix
  a = (int **) malloc(m * sizeof(int *));
  for(int i=0; i<m; i++)
	{
		a[i] = (int *) malloc(n * sizeof(int));
	}
  // write the elements in the matrix
  int matrix[5][9] = { {0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 1, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 1, 0, 0, 0, 0},
                        {0, 1, 1, 0, 0, 1, 1, 1, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0}
                    };

	for(int i=0; i<m; i++)
	{
		for(int j=0; j<n; j++)
		{
            int *x = &matrix[i][j];
            if(*x == 1)
            {
                mvprintw(i+22,j+52,"#");
            }
		}
	}
    mvprintw(21,50,"_____________");
    mvprintw(26,50,"_____________");
    mvprintw(22,50, "|");
    mvprintw(23,50, "|");
    mvprintw(24,50, "|");
    mvprintw(25,50, "|");
    mvprintw(26,50, "|");
    mvprintw(22,62, "|");
    mvprintw(23,62, "|");
    mvprintw(24,62, "|");
    mvprintw(25,62, "|");
    mvprintw(26,62, "|");

  // deallocate the memory
  for(int i=0; i<m; i++)
	{
		free(a[i]);
	}
	free(a);
}

/* Calculates the length of a "string" */
// int strlen (char *str)
// {
//     int i = 0;
//
//     while (1)                       /* Loops until the ith element */
//     {                               /* is a string terminator.     */
//         if (*(str + i++) == '\0')   /* i increases even if the     */
//             return --i;             /* element is '\0', so i is    */
//     }                               /* decreased by one.           */
// }

/* Copies string "src" to string "dest" */
void
str_cp (char *dest, char *src)
{
    int i = 0;

    do                                 /* Loops until the ith  */
    {                                  /* element of src is    */
        if (*(src + i) != '\0')        /* '\0'. If the ith     */
        {                              /* element of src is    */
            *(dest + i) = *(src + i);  /* not '\0', copy it to */
            i++;                       /* the ith element of   */
        }                              /* dest, then increase  */
    }                                  /* i by one.            */
    while (*(src + i) != '\0');

    *(dest + i) = '\0'; /* Terminate dest by adding '\0' to its */
                        /* last element (now dest == src).      */
    return;
}


/* Prints a menu according to your arguments/parameters,
   see the README file for more details */
int
print_menu (int sty, int x, int alts, int width,
            char title[], char entries[][100], int start)
{
    /* "i" will be used for printing out a character several times
       in a row by using for-loops. Later it will also be used
       to point to elements in "temparray" in order to assign some
       spaces after the currently selected word, so that the
       entire menu cell will be highlighted. */
    /* "j" will be used once by a for-loop when "i" is used elsewhere. */
    /* "k" is used to point to the different "entries" strings. */
    /* "blankspace1" and 2 are used for formatting the strings
       in the menu cells. */
    /* "currow" contains the currently highlighted row in the menu. */
    /* "y" will be used to move the cursor in the y-axis. */
    /* "key" will hold the keycode of the last key you pressed,
       in order to later compare it for different actions. */
    /* "temparray" will as previously stated contain the currently
       selected word in order to highlight it. */
    int i, j, k, blankspace1, blankspace2, currow = start, y = sty, key;
    char temparray[100];

    if (strlen (title) + 2 > width)    /* "width" cannot be less than */
        width = strlen (title) + 2;    /* the width of the strings    */
                                        /* plus some space. First      */
    for (k = 0; k < alts; k++)          /* check the title, then the   */
    {                                   /* entries.                    */
        if (strlen (&entries[k][0]) + 2 > width)
            width = strlen (&entries[k][0]) + 2;
    }

    k = 0;
    move (y++, x);
    addch (ACS_ULCORNER);           /* Here the program starts to     */
                                    /* print the frame of the menu.   */
    for (i = 0; i < width; i++)     /* ULCORNER is upper left corner, */
        addch (ACS_HLINE);          /* HLINE is horizontal line.      */

    addch (ACS_URCORNER);
    printw ("\n");
    move (y++, x);

    if ((width - strlen (title)) % 2 != 0) /* If it's not possible to */
    {                                       /* perfectly center the    */
        blankspace2 = (width - strlen (title) + 1) / 2;
        blankspace1 = blankspace2 - 1;      /* menu title, it will be  */
    }                                       /* placed slightly left.   */

    else
    {
        blankspace1 = (width - strlen (title)) / 2;
        blankspace2 = blankspace1;
    }

    addch (ACS_VLINE);

    for (i = 0; i < blankspace1; i++)
        printw (" ");

    printw ("%s", title);

    for (i = 0; i < blankspace2; i++)
        printw (" ");

    addch (ACS_VLINE);
    printw ("\n");
    move (y++, x);
    addch (ACS_LTEE);           /* LTEE is a left tilted 'T'-like     */
                                /* shape used to connect lines to the */
    for (i = 0; i < width; i++) /* right of, above and underneath it. */
        addch (ACS_HLINE);

    addch (ACS_RTEE);
    printw ("\n");
    move (y++, x);

    for (j = 0; j < alts - 1; j++)  /* Here, the loop will print all */
    {                               /* except the last entry for the */
        addch (ACS_VLINE);          /* menu.                         */
        printw (" %s", &entries[k][0]);
        blankspace1 = width - (strlen (&entries[k][0]) + 1);
                                    /* The blankspace is after the */
        for (i = 0; i < blankspace1; i++)
            printw(" ");            /* string, since the strings   */
                                    /* will be left fixated.       */
        k++;
        addch (ACS_VLINE);
        printw ("\n");
        move (y++, x);
        addch (ACS_LTEE);

        for (i = 0; i < width; i++)
            addch (ACS_HLINE);

        addch (ACS_RTEE);
        printw ("\n");
        move (y++, x);
    }

    addch (ACS_VLINE);
    printw (" %s", &entries[k][0]);
    blankspace1 = width - (strlen (&entries[k][0]) + 1);

    for (i = 0; i < blankspace1; i++)
        printw(" ");

    k++;
    addch (ACS_VLINE);
    printw ("\n");
    move (y++, x);
    addch (ACS_LLCORNER);       /* The last menu entry is outside the */
                                /* loop because the lower corners are */
    for (i = 0; i < width; i++) /* different. This last entry uses    */
        addch (ACS_HLINE);      /* regular box corners to fulfill the */
                                /* menu.                              */
    addch (ACS_LRCORNER);
    printw ("\n");

    do  /* This loop is terminated when you */
    {   /* select an entry in the menu.     */
        attron (A_STANDOUT);    /* This highlights the current row. */
        blankspace1 = width - (strlen (&entries[currow - 1][0]) + 1);
        temparray[0] = ' ';     /* Also the blankspace after the */
        str_cp (&temparray[1], &entries[currow - 1][0]);
                                /* string will be highlighted.   */
        for (i = strlen (&entries[currow - 1][0]) + 1; i < width; i++)
        {
            temparray[i] = ' ';
        }

        temparray[i] = '\0';    /* The highlighted entry will be  */
        mvprintw ((sty + 3) + (currow - 1) * 2, x + 1, "%s", temparray);
        attroff (A_STANDOUT);   /* printed over the corresponding */
        key = getch();          /* non-highlighted entry.         */


        int **a;

        mvprintw(20 ,4, "1. The R-pentomino");
        for(int i=5; i<=10; i++)
        {
            for(int j=22; j<=27; j++)
            {
                matrix_new1(a);
            }
        }

        mvprintw(20 ,30, "2. Diehard");
        for(int i=30; i<=40; i++)
        {
            for(int j=22; j<=32; j++)
            {
                matrix_new2(a);
            }
        }

        mvprintw(20 ,52, "3. Acorn");
        for(int i=5; i<=59; i++)
        {
            for(int j=22; j<=31; j++)
            {
                matrix_new3(a);
            }
        }

        if (key == KEY_UP)
        {
            mvprintw ((sty + 3) + (currow - 1) * 2, /* First print the */
                      x + 1, "%s", temparray);      /* non-highlighted */
                                                    /* entry over the  */
                                                    /* highlighted one */

            if (currow == 1)
                currow = alts;

            else                /* Change the currently selected entry */
                currow--;       /* according to the direction given by */
        }                       /* the keypress. Going up from the top */
                                /* moves you to the bottom.            */
        else if (key == KEY_DOWN)   /* Works just like KEY_UP above,   */
        {                           /* just in the opposite direction. */
            mvprintw ((sty + 3) + (currow - 1) * 2,
                      x + 1, "%s", temparray);

            if (currow == alts)
                currow = 1;

            else
                currow++;
        }

    }
    while (key != '\n' && key != '\r' && key != 4);
    printf("%c", currow);
    return currow;  /* The return is the row-number of the selected */
}                   /* entry. Can be 1 to "alts" (not 0).           */
