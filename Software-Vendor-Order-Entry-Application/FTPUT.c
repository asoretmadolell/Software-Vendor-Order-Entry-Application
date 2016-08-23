/*****************************************************************************/
/*                                                                           */
/* FTPUT.c                                                                   */
/* "The Project Utility Functions: ftput()"                                  */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* Description:                                                              */
/*                                                                           */
/* ftput() converts a double-precision floating-point number to ASCII and    */
/* displays it right justified in field of specified width, with             */
/* specified decimal places.                                                 */
/*                                                                           */
/*****************************************************************************/

#include "STDDEFS.h"
#include "PROJUTIL.h"

void ftput( row, col, double_val, dec_place, buf, field_len )
short row, col;
double double_val;              /* value to be displayed */
short dec_place, field_len;     /* decimal places and length of field */
char buf[];
{
    char* fcvt();               /* fcvt() returns a pointer to a temporary string buffer. */
    short dec, sign;            /* pointers to decimal and sign returned from fcvt() */
    short pos;                  /* position counter for "for" loop */

    /*****************************************************************************/
    /* Copy contents of temporary string buffer to buf.                          */
    /*****************************************************************************/
    strcpy( buf, fcvt( double_val, dec_place, &dec, &sign ) );

    /*****************************************************************************/
    /* Move digits on right of decimal point and '\0' one place to right and     */
    /* insert decimal point.                                                     */
    /*****************************************************************************/
    for( pos = strlen( buf ); pos >= dec; --pos )
    {
        buf[ pos + 1 ] = buf[ pos ];
    }
    buf[ dec ] = '.';
    strrjust( buf, field_len );
    tput( row, col, buf );
}
