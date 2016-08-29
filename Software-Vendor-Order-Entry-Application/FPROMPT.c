/*****************************************************************************/
/*                                                                           */
/* FPROMPT.c                                                                 */
/* "The Project Utility Functions: fprompt()"                                */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* Description:                                                              */
/*                                                                           */
/* fprompt() inputs a double-precision floating-point number from standard   */
/* input. It behaves the same as nprompt(), except that the arguments        */
/* width and precision must be passed to fprompt() to indicate the width     */
/* of the field and the number of digits to prompt for on the right of the   */
/* decimal point.                                                            */
/*                                                                           */
/*****************************************************************************/

#include <stdio.h>
#include "STDDEFS.h"
#include "PROJUTIL.h"

stepcode fprompt( d_num, match_str, min_dval, max_dval, width, precision, mand, row, col )
double* d_num;                              /* Default passed in, input data returned. */
char match_str[];
double min_dval, max_dval;                  /* minimum and maximum input values */
short width, precision;                     /* field width and decimal places */
flag mand;                                  /* If yes, data cannot be zero on return. */
short row, col;                             /* cursor location to begin input */
{
    short dec, sign;                        /* dummy arguments to pass to fcvt() */
    double atof( char[] );                  /* Library function atof() returns type double. */
    char buf[ 14 ], format[ 14 ];           /* prompt input buffer and format string */
    bflag more = YES;
    double in_dnum;                         /* ASCII input number converted to double */
    short max_len = width;
    short min_len = strlen( fcvt( min_dval, precision, &dec, &sign ) ) - precision;
    stepcode rtn;

    /*****************************************************************************/
    /* Supply as default if d_num points to non-zero double.                     */
    /*****************************************************************************/
    if( *d_num != 0.0 )                                         /* Non-zero value passed in? */
    {
        ftput( row, col, *d_num, precision, buf, max_len );     /* Display default. */
    }
    else
    {
        buf[ 0 ] = '\0';
    }

    do
    {
        rtn = prompt( buf, match_str, min_len, max_len, mand, row, col );
        if( rtn != STEPOK )
        {
            more = NO;
        }
        else
        {
            in_dnum = atof( buf );          /* Convert ASCII to double. */
            if( mand && in_dnum == 0.0 )
            {
                err_warn( "Non-zero data mandatory:", "" );
            }
            else if( ( in_dnum < min_dval || in_dnum > max_dval ) && ( mand || in_dnum != 0.0 ) )
            {
                /*****************************************************************************/
                /* Create string to pass to err_warn().                                      */
                /*****************************************************************************/
                sprintf( buf, "%.*f to %.*f", precision, min_dval, precision, max_dval );
                err_warn( "Enter a number from:", buf );
                buf[ 0 ] = '\0';
                CUR_MV( row, col );
            }
            else
            {
                more = NO;
            }
        }
    }
    while( more );

    if( rtn == STEPOK )             /* Then echo, right justified. */
    {
        *d_num = in_dnum;           /* Pass value back to caller. */
        ftput( row, col, *d_num, precision, buf, max_len );
    }

    return( rtn );
}
