/*****************************************************************************/
/*                                                                           */
/* ERR_WARN.c                                                                */
/* "The Project Utility Functions: err_warn() and err_exit()"                */
/*                                                                           */
/*****************************************************************************/

#include <stdio.h>
#include "STDDEFS.h"
#include "PROJUTIL.h"

#define ESC '\x1b'

/*****************************************************************************/
/*                                                                           */
/* err_warn()                                                                */
/*                                                                           */
/* Displays a two-string diagnostic message on line 24, waits for the user   */
/* to press ESC, and the erases the diagnostic message.                      */
/*                                                                           */
/*****************************************************************************/
void err_warn( first, second )
char first[], second[];             /* two parts of diagnostic message */
{
    IMPORT bflag bell_ok;
    short first_len = strlen( first );
    short second_len = strlen( second );

    CUR_MV( 24, 1 );
    CLR_LINE;
    tput( 24, 1, first );
    tput( 24, 2 + first_len, second );
    tput( 24, 3 + first_len + second_len, "_ (push ESC)\b\b\b\b\b\b\b\b\b\b\b\b" );

    if( bell_ok )
    {
        BELL;
    }

    while( getch() != ESC )         /* Loop until Escape entered. */
    {
        if( bell_ok )
        {
            BELL;
        }
    }

    CUR_MV( 24, 1 );
    CLR_LINE;
}

/*****************************************************************************/
/*                                                                           */
/* err_exit()                                                                */
/*                                                                           */
/* Displays a diagnostic message through err_warn() and calls exit() to      */
/* terminate execution. The two-part message is displayed on line 24. When   */
/* the user presses ESC, the message is erased.                              */
/*                                                                           */
/*****************************************************************************/
void err_exit( first, second )
char first[], second[];             /* two parts of diagnostic message */
{
    char log_buf[ 512 ];

    strcpy( log_buf, first );
    strcat( log_buf, " " );
    strcat( log_buf, second );
    logentry( log_buf );            /* Record the message in the log. */
    err_warn( first, second );      /* Display the message. */
    exit( FAIL );                   /* Terminate program: FAIL status. */
}
