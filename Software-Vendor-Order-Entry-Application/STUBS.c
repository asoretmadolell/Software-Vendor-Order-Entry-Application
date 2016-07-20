/*****************************************************************************/
/*                                                                           */
/* STUBS.c                                                                   */
/* "Stub Functions: stubs.c"                                                 */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* Description:                                                              */
/*                                                                           */
/* Stubs are function prototypes called to test their calles.                */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* Here are inv_find(), pw_find(), order_num(), and logentry()               */
/*                                                                           */
/*****************************************************************************/

#include "STDDEFS.h"

/*****************************************************************************/
/*                                                                           */
/* pw_find()                                                                 */
/*                                                                           */
/* Looks up a user's name and password and returns YES if the user is        */
/* found, NO if not. If the user is found, office ID is also checked.        */
/* User data contain indication of whether to ring bell.                     */
/*                                                                           */
/*****************************************************************************/
flag pw_find( office, user, password )
char office[];                  /* description of user's office (returned) */
char user[];                    /* name, initials, or abbreviation of user to find */
char password[];                /* password to be looked up */
{
    IMPORT bflag bell_ok;

    if( user[ 1 ] == 'S' )      /* OK to ring the bell? */
    {
        bell_ok = NO;           /* No. Silence the bell. */
    }

    return( user[ 0 ] == 'S' && password[ 0 ] == 'S' );
}