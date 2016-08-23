/*****************************************************************************/
/*                                                                           */
/* NPROMPT.c                                                                 */
/* "The Project Utility Functions: nprompt()"                                */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* Description:                                                              */
/*                                                                           */
/* nprompt() inputs a long integer from standard input. Input is matched     */
/* against an optional match-string argument. Minimum and maximum input      */
/* values are checked. If the Boolean (flag) argument mand is true, then     */
/* data will not be permitted to remain zero; data must be entered. The      */
/* parameter *p_num is both passed in and returned to the caller. The        */
/* value passed in is treated as a default to be used if input is null.      */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* Return value:                                                             */
/*                                                                           */
/* The outcome of nprompt() has synonym data type stepcode, which is used    */
/* to indicate:                                                              */
/*                                                                           */
/*    STEPOK    Step complete; valid number obtained.                        */
/*    STEPBACK  Back up to the previous step.                                */
/*    STEPCANC  Cancel order entry (quit).                                   */
/*                                                                           */
/* C_BACK, C_NULL, and C_CANC are defined in "PROJUTIL.h". The user can      */
/* request to back up by entering C_BACK, to cancel by entering C_CANC,      */
/* or to set *p_num to zero by entering C_NULL as any character in reply.    */
/*                                                                           */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h> /* needed for function atol() */
#include "STDDEFS.h"
#include "PROJUTIL.h"

stepcode nprompt( p_num, match_str, min_val, max_val, mand, row, col )
long* p_num;                /* Default passed in, input data returned. */
char match_str[];           /* match string to verify data against */
long min_val, max_val;      /* minimum and maximum input values */
flag mand;                  /* If yes, data cannot be zero on return. */
short row, col;             /* cursor location to begin input */
{
    long atol( char[] );                                    /* Library function atol() returns type long. */
    char buf[ 14 ];                                         /* prompt input buffer */
    bflag more = YES;                                       /* prompt again? */
    long in_num;                                            /* ASCII input number converted to binary */
    short max_len = strlen( ltoa( max_val, buf, 10 ) );
    short min_len = strlen( ltoa( min_val, buf, 10 ) );
    stepcode rtn;                                           /* return code */

    /*****************************************************************************/
    /* Supply as default if p_num points to a non-zero long.                     */
    /*****************************************************************************/
    if( *p_num )                                    /* Non-zero value passed in? */
    {
        ntput( row, col, *p_num, buf, max_len );    /* Display default. */
    }
    else                                            /* no default */
    {
        buf[ 0 ] = '\0';
    }

    /*****************************************************************************/
    /* Loop: Prompt for number in string form, until value entered is in range,  */
    /* or cancel or back up requested.                                           */
    /*****************************************************************************/
    do
    {
        rtn = prompt( buf, match_str, min_len, max_len, mand, row, col );
        if( rtn != STEPOK )
        {
            more = NO;                          /* Done prompting (back up or cancel). */
        }
        else                                    /* Check whether input mandatory and reply in range. */
        {
            in_num = atol( buf );               /* Convert ASCII input to long integer. */

            /*****************************************************************************/
            /* If mandatory and number is zero, this is an error                         */
            /*****************************************************************************/
            if( mand && in_num == 0 )
            {
                err_warn( "Non-zero data mandatory:", "" );
            }
            /*****************************************************************************/
            /* Otherwise, verify in_num is inside specified range, provided prompt is    */
            /* mandatory or number entered is non-zero.                                  */
            /*****************************************************************************/
            else if( ( in_num < min_val || in_num > max_val ) && ( mand || in_num != 0 ) )
            {
                sprintf( buf, "%ld to %ld", min_val, max_val );
                err_warn( "Enter a number from:", buf );
                buf[ 0 ] = '\0';
            }
            /*****************************************************************************/
            /* Got a good value; done prompting.                                         */
            /*****************************************************************************/
            else
            {
                more = NO;
            }
        }
    }
    while( more );

    if( rtn == STEPOK )                             /* Then echo, right justified. */
    {
        *p_num = in_num;                            /* Pass value back to caller. */
        ntput(row, col, in_num, buf, max_len);      /* Echo number right justified in screen field. */
    }

    return( rtn );
}
