/*****************************************************************************/
/*                                                                           */
/* PNT_SHIP.c                                                                */
/* "The Low Level: pnt_ship_pay()"                                           */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* Description:                                                              */
/*                                                                           */
/* pnt_ship_pay() paints the screen for order entry: ship, tax, pay. This    */
/* function is called exclusively by ship_pay() in "ORDBUILD.c".             */
/*                                                                           */
/*****************************************************************************/

#include "STDDEFS.h"
#include "PROJUTIL.h"

void pnt_ship_pay()
{
    tput( 4, 10, "Customer Name" );
    tput( 6, 10, "Company Name" );
    tput( 9, 10, "Shipping Weight" );
    tput( 11, 19, "Carrier" );
    tput( 11, 51, "Ship Charge" );
    tput( 11, 64, "$" );
    tput( 14, 10, "Sales Tax Percent" );
    tput( 17, 10, "Payment Terms Code" );
    tput( 18, 51, "Item Total" );
    tput( 18, 64, "$" );
    tput( 20, 51, "Order Total" );
    tput( 20, 64, "$" );
    tput( 22, 2, "Comment" );
}
