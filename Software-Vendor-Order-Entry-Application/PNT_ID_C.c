/*****************************************************************************/
/*                                                                           */
/* PNT_ID_C.c                                                                */
/* "The Low Level: pnt_id_cust()"                                            */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* Description:                                                              */
/*                                                                           */
/* pnt_id_cust() paints screen for order entry: indetify customer. This      */
/* function is called exclusively by id_cust() in "ORDBUILD.c".              */
/*                                                                           */
/*****************************************************************************/

#include "STDDEFS.h"
#include "PROJUTIL.h"

void pnt_id_cust()
{
    tput( 4, 10, "Customer Name" );
    tput( 6, 10, "Company Name" );
    tput( 7, 10, "Phone Number" );

    tput( 9, 10, "Ship to Name" );
    tput( 10, 18, "Company" );
    tput( 11, 18, "Street" );
    tput( 12, 18, "2nd Street" );
    tput( 13, 18, "City" );
    tput( 13, 49, "State" );
    tput( 13, 60, "Zip" );

    tput( 15, 10, "Bill to Name" );
    tput( 16, 18, "Company" );
    tput( 17, 18, "Street" );
    tput( 18, 18, "2nd Street" );
    tput( 19, 18, "City" );
    tput( 19, 49, "State" );
    tput( 19, 60, "Zip" );

    tput( 21, 10, "Resale?" );
    tput( 21, 30, "Resale Permit Number" );
    tput( 23, 10, "Advertising Ref" );
}
