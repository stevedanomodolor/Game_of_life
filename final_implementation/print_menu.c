#include "print_menu.h"


// void print_intial_structures(cell_t cell_map, window_size_t cell_size, int offset_x, int offset_y)
// {
//
// }
int print_menu (int offset_y, int offset_x, int alts, int width,char title[], char entries[][MAX_LEN], int start)
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
    int i, j, k, blankspace1, blankspace2, currow = start, y = offset_y, key;
    char temparray[MAX_LEN];

    if (strlen (title) + 2 > width)    /* "width" cannot be less than */
        width = strlen (title) + 2;    /* the width of the strings    */
                                        /* plus some space. First      */
    for (k = 0; k < alts; k++)          /* check the title, then the   */
    {                                   /* entries.                    */
        if (strlen (&entries[k][0]) + 2 > width)
            width = strlen (&entries[k][0]) + 2;
    }

    k = 0;
    move (y++, offset_x);
    addch (ACS_ULCORNER);           /* Here the program starts to     */
                                    /* print the frame of the menu.   */
    for (i = 0; i < width; i++)     /* ULCORNER is upper left corner, */
        addch (ACS_HLINE);          /* HLINE is horizontal line.      */

    addch (ACS_URCORNER);
    printw ("\n");
    move (y++, offset_x);

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
    move (y++, offset_x);
    addch (ACS_LTEE);           /* LTEE is a left tilted 'T'-like     */
                                /* shape used to connect lines to the */
    for (i = 0; i < width; i++) /* right of, above and underneath it. */
        addch (ACS_HLINE);

    addch (ACS_RTEE);
    printw ("\n");
    move (y++, offset_x);

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
        move (y++, offset_x);
        addch (ACS_LTEE);

        for (i = 0; i < width; i++)
            addch (ACS_HLINE);

        addch (ACS_RTEE);
        printw ("\n");
        move (y++, offset_x);
    }

    addch (ACS_VLINE);
    printw (" %s", &entries[k][0]);
    blankspace1 = width - (strlen (&entries[k][0]) + 1);

    for (i = 0; i < blankspace1; i++)
        printw(" ");

    k++;
    addch (ACS_VLINE);
    printw ("\n");
    move (y++, offset_x);
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
        strcpy (&temparray[1], &entries[currow - 1][0]);
                                /* string will be highlighted.   */
        for (i = strlen (&entries[currow - 1][0]) + 1; i < width; i++)
        {
            temparray[i] = ' ';
        }

        temparray[i] = '\0';    /* The highlighted entry will be  */
        mvprintw ((offset_y + 3) + (currow - 1) * 2, offset_x + 1, "%s", temparray);
        attroff (A_STANDOUT);   /* printed over the corresponding */
        key = getch();          /* non-highlighted entry.         */

        if (key == KEY_UP)
        {
            mvprintw ((offset_y + 3) + (currow - 1) * 2, /* First print the */
                      offset_x + 1, "%s", temparray);      /* non-highlighted */
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
            mvprintw ((offset_y + 3) + (currow - 1) * 2,
                      offset_x + 1, "%s", temparray);

            if (currow == alts)
                currow = 1;

            else
                currow++;
        }

    }
    while (key != '\n' && key != '\r' && key != 4);
    printf("%c", currow);
    return currow;  /* The return is the row-number of the selected */
}
