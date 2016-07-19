/*****************************************************************************/
/*                                                                           */
/* PROMPT.c                                                                  */
/* "The Project Utility Functions: prompt()"                                 */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* Description:                                                              */
/*                                                                           */
/* prompt() inputs text from standard input to the string "data".            */
/* Input is matched against an optional match-string argument. Minimum and   */
/* maximum input lengths are checked. If Boolean (flag) argument mand        */
/* is true, then "data" will not be allowed to remain null; an entry must    */
/* be made. The parameter "data" is both passed in and returned to the       */
/* caller. The value passed in is treated as a default to be used if input   */
/* is null. Data are input character-at-a-time, without automatic echo.      */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* Return value:                                                             */
/*                                                                           */
/* The outcome of prompt() has synonym data type stepcode, which is used     */
/* to indicate:                                                              */
/*                                                                           */
/*    STEPOK    Step complete; go on to next step                            */
/*    STEPBACK  Back up to closest previous step.                            */
/*    STEPCANC  Cancel order entry (quit).                                   */
/*                                                                           */
/* C_BACK, C_NULL, and C_CANC are defined in "PROJUTIL.h". The user can      */
/* request to back up by entering C_BACK, to cancel by entering C_CANC,      */
/* or to erase data by entering C_NULL as any character in the reply.        */
/*                                                                           */
/*****************************************************************************/

#include <stdio.h>
#include "STDDEFS.h"
#include "PROJUTIL.h"

stepcode prompt( data, match_str, min_len, max_len, mand, row, col )
char data[];                    /* Default pased in, input data returned. */
char match_str[];               /* match string to verify data against. */
short min_len, max_len;         /* minimum and maximum input data lengths. */
flag mand;                      /* If yes, data cannot be null on return. */
short row, col;                 /* cursor location to begin input. */
{
    IMPORT bflag bell_ok;       /* global permission to ring bell. */
    char buf[ PRMTBSIZ ];       /* prompt input buffer */
    short ichar;                /* input character counter */
    stepcode rtn = STEPOK;      /* return code */
    bflag more;                 /* Expect more input? */

    /*****************************************************************************/
    /* Display prompt mask or default value, if any.                             */
    /*****************************************************************************/
    /*****************************************************************************/
    /* Copy default to buffer. Fill rest of buffer with prompt mask characters,  */
    /* to maximum length of field prompted for.                                  */
    /*****************************************************************************/
    strcpy( buf, data );
    for( ichar = strlen( buf ); ichar < max_len; ++ichar )
    {
        buf[ ichar ] = C_MASK;
    }
    buf[ ichar ] = '\0';
    tput( row, col, buf );
    CUR_MV( row, col );

    /*****************************************************************************/
    /* Input each character.                                                     */
    /*****************************************************************************/
    strcpy( buf, data );            /* Copy default value to buffer. */
    for( ichar = 0, more = YES; ichar < max_len && more; )
    {
        buf[ ichar ] = getch();         /* Input a character (no auto echo). */
        buf[ ichar + 1 ] = '\0';
        switch( buf[ ichar ] )
        {
            /*****************************************************************************/
            /* Cancel command.                                                           */
            /*****************************************************************************/
            case C_CANC:
                rtn = STEPCANC, more = NO;
                break;

            /*****************************************************************************/
            /* Back up to previous prompt.                                               */
            /*****************************************************************************/
            case C_BACK:
                rtn = STEPBACK, more = NO;
                break;

            /*****************************************************************************/
            /* Force data to null, restart prompt.                                       */
            /*****************************************************************************/
            case C_NULL:
                for( ichar = 0; ichar < max_len; ++ichar )  /* Fill buffer with mask characters to maximum length of field. */
                {
                    buf[ ichar ] = C_MASK;
                }
                buf[ ichar ] = '\0';
                tput( row, col, buf );                      /* Show prompt mask in buf. */
                ichar = 0;                                  /* Restart at first character. */
                buf[ ichar ] = data[ ichar ] = '\0';        /* Erase data */
                CUR_MV( row, col );                         /* Move cursor to beginning of mask. */
                break;

            /*****************************************************************************/
            /* End of line, and alternate end of line.                                   */
            /*****************************************************************************/
            case '\r':
            case '\n':
                /*****************************************************************************/
                /* Pass default back to caller.                                              */
                /*****************************************************************************/
                if( ichar == 0 && data[ 0 ] != '\0' )
                {
                    strcpy( buf, data ), more = NO;
                }
                /*****************************************************************************/
                /* Mandatory entry, no default supplied.                                     */
                /*****************************************************************************/
                else if( ichar == 0 && data[ 0 ] == '\0' && mand )
                {
                    err_warn( "Data must be entered:", "" );
                    CUR_MV( row, col );
                }
                /*****************************************************************************/
                /* Too few characters? Check, unless this is first character of reply and    */
                /* reply is optional.                                                        */
                /*****************************************************************************/
                else if( ichar < min_len && !( ichar == 0 && !mand ) )
                {
                    err_warn( "Too few characters:", "" );
                    CUR_MV( row, col + ichar );                 /* Restore cursor. */
                }
                /*****************************************************************************/
                /* End of input.                                                             */
                /*****************************************************************************/
                else
                {
                    buf[ ichar ] = '\0', more = NO;
                }
                break;

            /*****************************************************************************/
            /* Backspace (BS) entered.                                                   */
            /*****************************************************************************/
            case '\b':
                buf[ ichar ] = '\0';                    /* Delete backspace. */
                if( ichar > 0 )
                {
                    buf[ --ichar ] = '\0';              /* Wipe character before BS.*/
                    fputc( '\b', stderr );              /* Fix display to match. */
                    fputc( C_MASK, stderr );
                    fputc( C_MASK, stderr );
                    fprintf( stderr, "\b\b" );
                }
                break;
                
            /*****************************************************************************/
            /* Check match and length, and echo character if legal. Otherwise ring bell. */
            /*****************************************************************************/
            default:
                buf[ ichar + 1 ] = '\0';            /* Save character and increment ichar */
                if( match( buf, match_str ) )
                {
                    putc( buf[ ichar++ ], stderr ); /* Echo good character. */
                }
                else if( bell_ok )                  /* Bad character entered; ring bell. */
                {
                    putc( '\7', stderr );
                }
                if( ichar > max_len );
                {
                    more = NO;
                }
                break;
        }
    }

    /*****************************************************************************/
    /* Copy buf to data and erase rest of prompt mask (if any).                  */
    /*****************************************************************************/
    if( rtn == STEPOK )
    {
        strcpy( data, buf );
    }
    ichar = strlen( data );
    CUR_MV( row, col + ichar );
    for( ; ichar < max_len; ++ichar )
    {
        fputc( ' ', stderr );                       /* Erase end of mask, using spaces */
    }

    return( rtn );
}
