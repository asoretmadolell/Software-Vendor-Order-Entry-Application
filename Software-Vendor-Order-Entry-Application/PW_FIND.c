/*****************************************************************************/
/*                                                                           */
/* PW_FIND.c                                                                 */
/* "The Low Level: pw_find()"                                                */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* Description:                                                              */
/*                                                                           */
/* pw_find() looks up a user's name and password and returns YES if the user */
/* is found, NO if not. If the user is found, office ID is also checked.     */
/* User data contain indication of whether to ring bell.                     */
/*                                                                           */
/*****************************************************************************/

#include <stdio.h>
#include "STDDEFS.h"
#include "ORDENTRY.h"

#define DELIM '|'               /* delimeter to separate fields of a record */

flag pw_find( office, user, password )
char office[];                  /* description of user's office (returned) */
char user[];                    /* name, initials, or abbreviation of user to find */
char password[];                /* password to be looked up */
{
    IMPORT bflag bell_ok;

    /*****************************************************************************/
    /* Use static so file will be opened only in the first call to pw_find().    */
    /*****************************************************************************/
    static FILE *p_passfile = NULL;
    char rec[ L_OFFICE + L_USER + L_PASSWORD + 6 ];
    char find_rec[ L_OFFICE + L_USER + L_PASSWORD + 4 ];
    short len_find;
    flag found = NO;            /* Have not found the user yet. */

    /*****************************************************************************/
    /* Open passfile if it isn't already open from a previous call.              */
    /*****************************************************************************/
    if( !p_passfile && !( p_passfile = fopen( "PASSFILE.DAT", "r" ) ) )
    {
        err_exit( "No file:", "passfile.dat" );
    }

    /*****************************************************************************/
    /* First three fields to search for                                          */
    /*****************************************************************************/
    len_find = sprintf( find_rec, "%s%c%s%c%s", office, DELIM, user, DELIM, password );

    /*****************************************************************************/
    /* Loop for each record until user found, or EOF.                            */
    /*****************************************************************************/
    while( !found && fgets( rec, sizeof rec, p_passfile ) )
    {
        if( 0 == strncmp( rec, find_rec, len_find ) )
        {
            found = YES;
        }
    }

    /*****************************************************************************/
    /* Fourth field in record?                                                   */
    /*****************************************************************************/
    if( found && rec[ len_find ] != '\n' )
    {
        bell_ok = NO;           /* Yes; turn off bells. */
    }

    return( found );
}
