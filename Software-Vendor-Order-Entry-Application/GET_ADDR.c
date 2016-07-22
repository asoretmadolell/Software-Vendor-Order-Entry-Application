/*****************************************************************************/
/*                                                                           */
/* GET_ADDR.c                                                                */
/* "The Low Level: get_addr()"                                               */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* Description:                                                              */
/*                                                                           */
/* get_addr() prompts for address data for order-entry programs. All data    */
/* are returned to the caller by arguments 3-9 (yes, 9 is rather high).      */
/*                                                                           */
/*****************************************************************************/

#include "STDDEFS.h"
#include "PROJUTIL.h"
#include "ORDENTRY.h"

stepcode get_addr( step_rtn, row, name, company, street, street2, city, state, zip )
stepcode step_rtn;          /* step_rtn is passed in and returned. */
short row;                  /* screen row to begin prompting. */
char name[], company[], street[], street2[], city[], state[], zip[];
{
    short step;
    enum prompts { NAME, COMPANY, STREET, STREET2, CITY, STATE, ZIP, ENDSTEPS };

    /*****************************************************************************/
    /* Begin at last prompt if screen backed into.                               */
    /*****************************************************************************/
    step = ( step_rtn == STEPOK ) ? 0 : (short)ENDSTEPS - 1;

    /*****************************************************************************/
    /* Loop: Input each field of this screen.                                    */
    /*****************************************************************************/
    for( step_rtn = STEPOK; step_rtn != STEPCANC && ( step != (short)ENDSTEPS ) && ( step >= 0 ); )
    {
        /*****************************************************************************/
        /* Select next field to prompt for.                                          */
        /*****************************************************************************/
        switch( step )
        {
            /*****************************************************************************/
            /* Get name.                                                                 */
            /*****************************************************************************/
            case NAME:
                step_rtn = prompt( name, "L", 3, L_SHIP_NAME, MAND, row, 30 );
                break;

            /*****************************************************************************/
            /* Get company name.                                                         */
            /*****************************************************************************/
            case COMPANY:
                step_rtn = prompt( company, "L", 3, L_SHIP_CMPY, OPT, row + 1, 30 );
                break;

            /*****************************************************************************/
            /* Get first line of street address.                                         */
            /*****************************************************************************/
            case STREET:
                step_rtn = prompt( street, "L", 3, L_SHIP_STRT, MAND, row + 2, 30 );
                break;

            /*****************************************************************************/
            /* Get second line of street address.                                        */
            /*****************************************************************************/
            case STREET2:
                step_rtn = prompt( street2, "L", 3, L_SHIP_STRT2, OPT, row + 3, 30 );
                break;

            /*****************************************************************************/
            /* Get city.                                                                 */
            /*****************************************************************************/
            case CITY:
                step_rtn = prompt( city, "L", 2, L_SHIP_CITY, MAND, row + 4, 30 );
                break;

            /*****************************************************************************/
            /* Get state's two-letter abbreviation.                                      */
            /*****************************************************************************/
            case STATE:
                step_rtn = prompt( state, "A", L_SHIP_STATE, L_SHIP_STATE, MAND, row + 4, 56 );
                break;

            /*****************************************************************************/
            /* Get zip code.                                                             */
            /*****************************************************************************/
            case ZIP:
                step_rtn = prompt( zip, "#", L_SHIP_ZIP, L_SHIP_ZIP, MAND, row + 4, 65 );
                break;
        }

        /*****************************************************************************/
        /* Determine next step based on return from last one. Was last successful?   */
        /*****************************************************************************/
        if( step_rtn == STEPOK )
        {
            ++step;                     /* Yes; go on to next step. */
        }
        else if( step_rtn == STEPBACK )
        {
            --step;                     /* No; back up to last step. */
        }
    }

    return( step_rtn );
}
