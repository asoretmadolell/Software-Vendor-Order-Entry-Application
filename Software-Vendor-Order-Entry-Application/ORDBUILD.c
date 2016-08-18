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
/* Semiglobal data shared by functions in this source file only.             */
/* Data items are fields of an order.                                        */
/*                                                                           */
/*****************************************************************************/
SEMIGLOBAL char user[ L_USER + 1 ] = "";
SEMIGLOBAL char office[ L_OFFICE + 1 ] = "";
SEMIGLOBAL char cust_name[ L_CUST_NAME + 1 ] = "";
SEMIGLOBAL char company[ L_COMPANY + 1 ] = "";
SEMIGLOBAL char phone[ L_PHONE +1 ] = "";
SEMIGLOBAL char ship_name[ L_SHIP_NAME + 1 ] = "";
SEMIGLOBAL char ship_cmpy[ L_SHIP_CMPY + 1 ] = "";
SEMIGLOBAL char ship_strt[ L_SHIP_STRT + 1 ] = "";
SEMIGLOBAL char ship_strt2[ L_SHIP_STRT2 + 1 ] = "";
SEMIGLOBAL char ship_city[ L_SHIP_CITY + 1 ] = "";
SEMIGLOBAL char ship_state[ L_SHIP_STATE + 1 ] = "";
SEMIGLOBAL char ship_zip[ L_SHIP_ZIP + 1 ] = "";
SEMIGLOBAL char bill_same[ L_BILL_SAME + 1 ] = "";
SEMIGLOBAL char bill_name[ L_BILL_NAME + 1 ] = "";
SEMIGLOBAL char bill_cmpy[ L_BILL_CMPY + 1 ] = "";
SEMIGLOBAL char bill_strt[ L_BILL_STRT + 1 ] = "";
SEMIGLOBAL char bill_strt2[ L_BILL_STRT2 + 1 ] = "";
SEMIGLOBAL char bill_city[ L_BILL_CITY + 1 ] = "";
SEMIGLOBAL char bill_state[ L_BILL_STATE + 1 ] = "";
SEMIGLOBAL char bill_zip[ L_BILL_ZIP + 1 ] = "";
SEMIGLOBAL char is_resale[ L_IS_RESALE + 1 ] = "";
SEMIGLOBAL char resale_id[ L_RESALE_ID + 1 ] = "";
SEMIGLOBAL char adv_ref[ L_ADV_REF + 1 ] = "";

/*****************************************************************************/
/* Variables "parts" and "part_descs" are 2-dimensional character arrays.    */
/*****************************************************************************/
SEMIGLOBAL char parts[ MAX_ITEMS ][ L_PARTS + 1 ] = { "" };
SEMIGLOBAL char part_descs[ MAX_ITEMS ][ L_PART_DESC + 1 ] = { "" };

SEMIGLOBAL long quantities[ MAX_ITEMS ] = { 0 };
SEMIGLOBAL short ship_weights[ MAX_ITEMS ] = { 0 };
SEMIGLOBAL short tot_weight = 0;
SEMIGLOBAL money prices[ MAX_ITEMS ] = { 0 };
SEMIGLOBAL money part_total = 0;
SEMIGLOBAL char ship_car[ L_SHIP_CAR + 1 ] = "";
SEMIGLOBAL money ship_amt = 0;
SEMIGLOBAL double inp_ship_amt = 0.0;
SEMIGLOBAL double tax_pcnt = 0.0;
SEMIGLOBAL money tax_amt = 0;
SEMIGLOBAL char pay_terms[ L_PAY_TERMS + 1 ] = "";
SEMIGLOBAL char comment[ L_COMMENT + 1 ] = "";
SEMIGLOBAL byte last_part = 0; /* index of last part on order */

/*****************************************************************************/
/* Shared data not part of an order.                                         */
/*****************************************************************************/
SEMIGLOBAL char scrn_title[] = "*** ENTER NEW ORDER ***";

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

/*****************************************************************************/
/*                                                                           */
/* id_cust()                                                                 */
/*                                                                           */
/* Prompts for customer identification information: customer name, company,  */
/* phone, shipping/billing addresses, resale number, and advertising         */
/* reference.                                                                */
/*                                                                           */
/*****************************************************************************/
stepcode id_cust( step_rtn )
/*****************************************************************************/
/* If screen is backed into, step_rtn == STEPBACK;                           */
/* otherwise step_rtn == STEPOK;                                             */
/*****************************************************************************/
stepcode step_rtn;
{
    /*****************************************************************************/
    /* Shared data accessed in this function.                                    */
    /*****************************************************************************/
    IMPORT char office[], user[], cust_name[], company[], ship_name[], ship_cmpy[],
        ship_strt[], ship_strt2[], ship_city[], ship_state[], ship_zip[], bill_name[],
        bill_cmpy[], bill_strt[], bill_strt2[], bill_city[], bill_state[], bill_zip[],
        adv_ref[], is_resale[], resale_id[], scrn_title[];
    stepcode get_addr( stepcode, short, char[], char[], char[], char[], char[], char[], char[] );
    void pnt_id_cust( void );
    short step;

    /*****************************************************************************/
    /* Names of case labels for data-field prompts.                              */
    /*****************************************************************************/
    enum prompts { NAME, COMPANY, PHONE, SHIP_ADDR, BILL_ADDR, RESALE, ADV_REF, ENDSTEPS };

    /*****************************************************************************/
    /* Begin new screen.                                                         */
    /*****************************************************************************/
    beg_scrn( user, scrn_title, office, "IDENTIFY" );
    pnt_id_cust();      /* Paint screen. */
    tput( 4, 30, cust_name );
    tput( 6, 30, company );

    /*****************************************************************************/
    /* Begin at last prompt if screen backed into.                               */
    /*****************************************************************************/
    step = ( step_rtn == STEPOK ) ? 0 : (short)ENDSTEPS - 1;
    /*****************************************************************************/
    /* Note: (short) is a cast operator used to make a type short copy of the    */
    /* value of the enum constants ENDSTEPS. Not using a cast gives a warning    */
    /* message.                                                                  */
    /*****************************************************************************/

    /*****************************************************************************/
    /* Loop: Input each field of this screen.                                    */
    /*****************************************************************************/
    for( step_rtn = STEPOK; step_rtn != STEPCANC && ( step < (short)ENDSTEPS ) && ( step >= 0 ); )
    {
        /*****************************************************************************/
        /* Select next field to prompt for.                                          */
        /*****************************************************************************/
        switch( step )
        {
            /*****************************************************************************/
            /* Get customer name.                                                        */
            /*****************************************************************************/
            case NAME:
                step_rtn = prompt( cust_name, "L", 3, L_CUST_NAME, MAND, 4, 30 );
                break;

            /*****************************************************************************/
            /* Get company name.                                                         */
            /*****************************************************************************/
            case COMPANY:
                step_rtn = prompt( company, "L", 3, L_COMPANY, OPT, 6, 30 );
                break;
                
            /*****************************************************************************/
            /* Get customer phone number.                                                */
            /*****************************************************************************/
            case PHONE:
                step_rtn = prompt( phone, "P", 7, L_PHONE, OPT, 7, 30 );
                break;
                
            /*****************************************************************************/
            /* Get address to ship to.                                                   */
            /*****************************************************************************/
            case SHIP_ADDR:
                /*****************************************************************************/
                /* No address input yet? Then set default name and company.                  */
                /*****************************************************************************/
                if( ship_name[ 0 ] == '\0' )
                {
                    strcpy( ship_name, cust_name );
                    strcpy( ship_cmpy, company );
                }

                /*****************************************************************************/
                /* Prompt for address data. Call get_addr().                                 */
                /*****************************************************************************/
                step_rtn = get_addr( step_rtn, 9, ship_name, ship_cmpy, ship_strt, ship_strt2, ship_city, ship_state, ship_zip );

                break;
                
            /*****************************************************************************/
            /* Get address to send bill to.                                              */
            /*****************************************************************************/
            case BILL_ADDR:
                tput( 15, 30, "Bill same address? <y/n>    " );
                step_rtn = prompt( bill_same, "Q", 1, L_BILL_SAME, MAND, 15, 56 );
                CUR_MV( 15, 30 );               /* Move cursor to erase question. */
                CLR_LINE;

                if( step_rtn == STEPOK && strchr( "Nn0", bill_same[ 0 ] ) )
                {
                    step_rtn = get_addr( step_rtn, 15, bill_name, bill_cmpy, bill_strt, bill_strt2, bill_city, bill_state, bill_zip );
                }
                else if( step_rtn == STEPOK )
                {
                    bill_name[ 0 ] == '\0';     /* Bill same address. */
                }

                break;
                
            /*****************************************************************************/
            /* Is purchase for resale?                                                   */
            /*****************************************************************************/
            case RESALE:
                step_rtn = prompt( is_resale, "Q", 1, L_IS_RESALE, MAND, 21, 25 );

                if( step_rtn == STEPOK && strchr( "Yy1", is_resale[ 0 ] ) )
                {
                    step_rtn = prompt( resale_id, "L", 3, L_RESALE_ID, OPT, 21, 53 );
                }

                break;
                
            /*****************************************************************************/
            /* How did customer hear about product?                                      */
            /*****************************************************************************/
            case ADV_REF:
                step_rtn = prompt( adv_ref, "L", 1, L_ADV_REF, OPT, 23, 30 );
                break;
        }

        /*****************************************************************************/
        /* Determine next step based on return from last one. Last was successful?   */
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

/*****************************************************************************/
/*                                                                           */
/* ord_itms()                                                                */
/*                                                                           */
/* Prompts repeatedly for part numbers and quantities of each item ordered   */
/* by customer. Displays price and shipping weight of each.                  */
/*                                                                           */
/*****************************************************************************/
stepcode ord_itms( step_rtn )
stepcode step_rtn;
{
    IMPORT char user[], office[], scrn_title[];
    IMPORT char parts[][ L_PARTS + 1 ];
    IMPORT char part_descs[][ L_PART_DESC + 1 ];
    IMPORT long quantities[];
    IMPORT short ship_weights[];
    IMPORT money prices[];
    IMPORT byte last_part;
    IMPORT money part_total;
    flag inv_find( char[], char[], money*, short* );
    short step;
    char dbuf[ 14 ];                                    /* dummy string to pass to ftput() and ntput() */
    byte ipart, part_cnt;
    byte row;                                           /* line number on screen */
    bflag part_found, more_items = YES;                 /* part_found not initialized */
    enum prompts { PART_NUM, QUANTITY, ENDSTEPS };

    /*****************************************************************************/
    /* Paint screen.                                                             */
    /*****************************************************************************/
    beg_scrn( user, scrn_title, office, "ENTER ITEMS" );
    tput( 4, 10, "Customer Name" );
    tput( 4, 30, cust_name );
    tput( 6, 10, "Company Name" );
    tput( 6, 30, company );
    tput( 9, 10, "Part Number      Description" );
    tput( 9, 59, "Qty  Unit-Price" );
    tput( 22, 51, "Order Total" );

    /*****************************************************************************/
    /* Initializer for loop.                                                     */
    /*****************************************************************************/
    step = ipart = 0;
    for( step_rtn = STEPOK; step_rtn != STEPCANC && ipart < MAX_ITEMS && ipart >= 0 && more_items; )
    {
        /*****************************************************************************/
        /* Row to prompt on.                                                         */
        /*****************************************************************************/
        row = ipart + 11;
        switch( step )
        {
            /*****************************************************************************/
            /* Get next part number.                                                     */
            /*****************************************************************************/
            case PART_NUM:
                /*****************************************************************************/
                /* While part entered and not found.                                         */
                /*****************************************************************************/
                do
                {
                    step_rtn = prompt( parts[ ipart ], "L", 1, L_PARTS, OPT, row, 10 );

                    /*****************************************************************************/
                    /* Got a part number and it checks out?                                      */
                    /*****************************************************************************/
                    part_found = ( step_rtn == STEPOK ) && inv_find( parts[ ipart ], part_descs[ ipart ], &prices[ ipart ], &ship_weights[ ipart ] );

                    /*****************************************************************************/
                    /* Check for end of order.                                                   */
                    /*****************************************************************************/
                    if( step_rtn == STEPOK && parts[ ipart ][ 0 ] == '\0' )
                    {
                        more_items = NO;
                    }
                    /*****************************************************************************/
                    /* If part not found, then tell user.                                        */
                    /*****************************************************************************/
                    else if( !part_found && step_rtn == STEPOK )
                    {
                        err_warn( "No such part:", parts[ ipart ] );
                    }
                    /*****************************************************************************/
                    /* Show description and price of part.                                       */
                    /*****************************************************************************/
                    else if( part_found )
                    {
                        tput( row, 27, part_descs[ ipart ] );
                        tput( row, 64, "$" );
                        ftput( row, 65, (double)prices[ ipart ] / 100.0, 2, dbuf, L_PRICES );

                        /*****************************************************************************/
                        /* Default quantity is 1.                                                    */
                        /*****************************************************************************/
                        if( !quantities[ ipart ] )
                        {
                            quantities[ ipart ] = 1;
                        }
                    }
                }
                while( step_rtn == STEPOK && !part_found && more_items );

                break;

            /*****************************************************************************/
            /* Get quantity for part ordered.                                            */
            /*****************************************************************************/
            case QUANTITY:
                step_rtn = nprompt( &quantities[ ipart ], "#", 0L, H_QUANTITY, MAND, row, 59 );
                break;
        }

        /*****************************************************************************/
        /* Update total on screen.                                                   */
        /*****************************************************************************/
        if( step_rtn == STEPOK )
        {
            /*****************************************************************************/
            /* Has number of parts on this order increased?                              */
            /*****************************************************************************/
            if( ipart > last_part && ipart < MAX_ITEMS && quantities[ ipart ] > 0 )
            {
                last_part = ipart;      /* Yes, add another part. */
            }

            /*****************************************************************************/
            /* Sum the prices times quantities of parts ordered.                         */
            /*****************************************************************************/
            for( part_total = part_cnt = 0; part_cnt <= last_part; ++part_cnt )
            {
                part_total += prices[ part_cnt ] * quantities[ part_cnt ];
            }
            tput( 22, 64, "$" );
            ftput( 22, 65, (double)part_total / 100.0, 2, dbuf, L_PRICES );
        }

        /*****************************************************************************/
        /* Determine next part to prompt for and next step.                          */
        /*****************************************************************************/
        if( step == (short)PART_NUM )       /* Just got a part number. */
        {
            step = (short)QUANTITY;         /* Next get a quantity. */
            if( step_rtn == STEPBACK )
            {
                --ipart;
            }
        }
        else                                /* Just got a quantity. */
        {
            step = (short)PART_NUM;         /* Next get a part number. */
            if( step_rtn == STEPOK )
            {
                ++ipart;
            }
        }
    }

    return( step_rtn );
}
