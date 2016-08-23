/*****************************************************************************/
/*                                                                           */
/* NTPUT.c                                                                   */
/* "The Project Utility Functions: ntput()"                                  */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* Description:                                                              */
/*                                                                           */
/* ntput() converts a long integer to ASCII and displays it right justified  */
/* in field of specified width. The left side is padded with blanks.         */
/*                                                                           */
/*****************************************************************************/

#include <stdlib.h> /* needed for function ltoa() */
#include "STDDEFS.h"
#include "PROJUTIL.h"

void ntput( row, col, long_val, buf, field_len )
short row, col;                         /* cursor location */
long long_val;                          /* value to be displayed */
char buf[];
short field_len;                        /* length of field to right justify in */
{
    ltoa( long_val, buf, 10 );          /* Convert long to ASCII string. */
    strrjust( buf, field_len );         /* Right justify field. */
    tput( row, col, buf );              /* Display on screen for user. */
}
