/*****************************************************************************/
/*                                                                           */
/* ORDENTRY.c                                                                */
/* "The Top Level: main()"                                                   */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* Description:                                                              */
/*                                                                           */
/* The main() function for the Software Vendor Order-Entry Program. Each     */
/* case commands a significant step in order entry, such as prompting for    */
/* a screen of data or sending order data to a file.                         */
/*                                                                           */
/* The action after the completion of a step will be one of the following:   */
/*    Cancel the order.                                                      */
/*    Back up to previous step.                                              */
/*    Go on to the next step.                                                */
/*                                                                           */
/* The action is controlled by the user's use of special command characters  */
/* that are described further in the header file "PROJUTIL.h".               */
/*                                                                           */
/*****************************************************************************/

#include "STDDEFS.h"    /* needed for GLOBAL, IMPORT, and YES */
#include "PROJUTIL.h"   /* needed for prompt() symbols STEPOK, STEPBACK, and STEPCANC, and synonym type stepcode */

/*****************************************************************************/
/* Declare data shared among functions in all source files (GLOBAL).         */
/*****************************************************************************/
GLOBAL bflag bell_ok = YES;     /* It's OK to ring bell. */

main( )
{
    /*****************************************************************************/
    /* Declare subfunction return and parameter types.                           */
    /*****************************************************************************/
    IMPORT stepcode id_user( void ), id_cust( stepcode );
    IMPORT stepcode ord_itms( stepcode ), ship_pay( stepcode );
    IMPORT stepcode wrt_ord( void );
    short step;
    stepcode step_rtn;
    /*****************************************************************************/
    /* step_rtn is the return value from a step. It is passed to the next step.  */
    /* It may equal:                                                             */
    /*    STEPOK Step complete; go on to next step.                              */
    /*    STEPBACK  Back up to closest previous step.                            */
    /*    STEPCANC  Cancel order entry (quit).                                   */
    /*****************************************************************************/

    enum prompts { ID_USER, ID_CUST, ORD_ITMS, SHIP_PAY, WRT_ORD, ENDSTEPS };

    for( step = 0, step_rtn = STEPOK; step != (short)ENDSTEPS && step_rtn != STEPCANC; )
    {
        switch( step )
        {
            case ID_USER:                           /* Identify user (salesperson). */
                step_rtn = id_user( );
                break;
            case ID_CUST:                           /* Identify customer. */
                step_rtn = id_cust( step_rtn );
                break;
            case ORD_ITMS:                          /* Input order detail items. */
                step_rtn = ord_itms( step_rtn );
                break;
            case SHIP_PAY:                          /* Input shipping info, tax, pay terms. */
                step_rtn = ship_pay( step_rtn );
                break;
            case WRT_ORD:                           /* Write order; update files. */
                step_rtn = wrt_ord( );
                break;
        }

        /*****************************************************************************/
        /* Determine next step based on return from last one.                        */
        /*****************************************************************************/
        if( step_rtn == STEPOK )    /* Was last step successful? */
        {
            ++step;                 /* Yes; go on to next step. */
        }
        else if( step_rtn == STEPBACK && step > 0 )
        {
            --step;                 /* No; back up to previous step.*/
        }
    }
}
