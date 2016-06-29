/*****************************************************************************/
/*                                                                           */
/* TPUT.c                                                                    */
/* "The Project Utility Functions: tput()"                                   */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* Description:                                                              */
/*                                                                           */
/* tput() displays a string at a specified row and column.                   */
/*                                                                           */
/*****************************************************************************/

#include <stdio.h>
#include "STDDEFS.h"

void tput( row, col, text )
short row, col;                 /* cursor location */
char text[];                    /* text to display */
{
    CUR_MV( row, col );
    fputs( text, stderr );
}