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

#include <stdio.h>
#include "STDDEFS.h"
#include "ORDENTRY.h"

/*****************************************************************************/
/*                                                                           */
/* inv_find()                                                                */
/*                                                                           */
/* Looks up a part's data in inventory and returns YES if the part is        */
/* found, NO if it's not found. Part description, price, and weight are      */
/* passed back.                                                              */
/*                                                                           */
/*****************************************************************************/
flag inv_find( part, part_desc, p_price, p_ship_wt )
char part[];                    /* part number to look up (pass in) */
char part_desc[];               /* description of part (returned) */
money* p_price;                 /* pointer to unit price of part (returned) */
short* p_ship_wt;               /* pointer to shipping weight in ounces (returned) */
{
    /*****************************************************************************/
    /* Return typical data to test inv_find()'s callers.                         */
    /*****************************************************************************/
    strcpy( part_desc, "Order-Entry Software Package" );
    *p_price = 12345L;
    *p_ship_wt = 123;
    return ( part[0] == 'S' );    /* YES if 'S' first, else NO */
}

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