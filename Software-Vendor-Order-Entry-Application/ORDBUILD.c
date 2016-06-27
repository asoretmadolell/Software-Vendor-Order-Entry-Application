/*****************************************************************************/
/*                                                                           */
/* ORDBUILD.c                                                                */
/* "The Middle Level: ordbuild.c"                                            */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* Description:                                                              */
/*                                                                           */
/* Functions for order-entry prompt screens and for saving data. These are   */
/* the middle-level functions that call the low-level display and prompt     */
/* functions to input screens of order data. They are in one source file     */
/* to permit order data in memory to be shared by them, but not by other     */
/* functions linked into the order-entry program.                            */
/*                                                                           */
/*****************************************************************************/

#include <stdio.h>
#include "STDDEFS.h"
#include "PROJUTIL.h"
#include "ORDENTRY.h"

/*****************************************************************************/
/*                                                                           */
/* id_user()                                                                 */
/*                                                                           */
/* Identifies the user (salesperson or data-entry clerk). The user enters    */
/* office code, name, and password. The password is then verified.           */
/*                                                                           */
/*****************************************************************************/
stepcode id_user()
{
    IMPORT char user[];
    IMPORT char office[];
    IMPORT char scrn_title[];
    /*****************************************************************************/
    /* pwfind() is called to verify user and look up user data.                  */
    /*****************************************************************************/
    flag pw_find( char *, char *, char * );
    char password[ L_PASSWORD + 1 ];
    stepcode step_rtn;
    short ichar;

    /*****************************************************************************/
    /* Paint screen: Show headings for data to prompt for.                       */
    /*****************************************************************************/
    beg_scrn( "", scrn_title, "", "SALESPERSON" );
    tput( 10, 20, "Office" );
    tput( 12, 20, "Salesperson" );
    tput( 14, 20, "Password" );

    /*****************************************************************************/
    /* Loop until data entered or order canceled.                                */
    /*****************************************************************************/
    do
    {
        /*****************************************************************************/
        /* Input name of office seller is working in.                                */
        /*****************************************************************************/
        step_rtn = prompt( office, "L", 3, L_OFFICE, MAND, 10, 32 );

        if( step_rtn == STEPBACK )
        {
            err_warn( "Office must be supplied:", "" );
        }
    }
    while( step_rtn == STEPBACK );

    /*****************************************************************************/
    /* Prompt for user.                                                          */
    /*****************************************************************************/
    if( step_rtn != STEPBACK )
    {
        /*****************************************************************************/
        /* Loop until data entered or order canceled.                                */
        /*****************************************************************************/
        do
        {
            user[ 0 ] = '\0';   /* DON'T show last user id. */
            step_rtn = prompt( user, "L", 2, L_USER, MAND, 12, 32 );
            if( step_rtn == STEPBACK )
            {
                err_warn( "I must know who you are:", "" );
            }
        }
        while( step_rtn == STEPBACK );
    }

    /*****************************************************************************/
    /* Input password without echo.                                              */
    /*****************************************************************************/
    if( step_rtn != STEPCANC )
    {
        CUR_MV( 14, 32 );

        for( ichar = 0; ichar < L_PASSWORD && ( password[ ichar ] = getch() ) >= ' '; ++ichar )
        {
        }

        if( password[ ichar ] >= ' ' )
        {
            ++ichar;
        }

        password[ ichar ] = '\0';

        if( !pw_find( office, user, password ) )
        {
            err_warn( "Access denied:", user );
            step_rtn = STEPCANC;
        }
        else    /* Display instructions. */
        {
            tput( 17, 17, "Instructions for Commands Available at Prompts:" );
            tput( 19, 29, "^R = (control-R) Re-prompt for previous." );
            tput( 20, 20, "^E = Erase data field, make it empty." );
            tput( 21, 20, "^X = Exit and cancel order." );
            tput( 23, 17, "Press ^X to exit, or another key to continue: _\b" );

            if( getch() == C_CANC )
            {
                step_rtn = STEPCANC;
            }
        }
    }

    return( step_rtn );
}
