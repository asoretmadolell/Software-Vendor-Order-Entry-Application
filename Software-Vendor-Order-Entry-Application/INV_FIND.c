/*****************************************************************************/
/*                                                                           */
/* INV_FIND.c                                                                */
/* "The Low Level: inv_find()"                                               */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* Description:                                                              */
/*                                                                           */
/* inv_find() looks up a part's data in inventory and returns YES if the     */
/* part is found, NO if it's not found. Part description, price, and         */
/* weight are passed back.                                                   */
/*                                                                           */
/*****************************************************************************/

#include <stdio.h>
#include <fcntl.h>
#include <sys\types.h>
#include <sys\stat.h>
#include <io.h>
#include "STDDEFS.h"
#include "ORDENTRY.h"

/*****************************************************************************/
/* Declare structure type and define tag.                                    */
/*****************************************************************************/
struct s_inv_rec
{
    money price;                    /* price to charge for part, in cents */
    short weight;                   /* shipping weight, in ounces */
    char desc[ 31 ];                /* description of part */
};
struct s_inv_link
{
    struct s_inv_link* p_next;      /* next link in list pointer */
    struct s_inv_rec rec;           /* inventory record, nested structure in link */
};

flag inv_find( part, part_desc, p_price, p_ship_wt )
char part[];                        /* part number to look up (pass in) */
char part_desc[];                   /* description of part (returned) */
money* p_price;                     /* pointer to unit price of part (returned) */
short* p_ship_wt;                   /* pointer to shipping weight in ounces (returned) */
{
    IMPORT long atol( char[] );
    static struct s_inv_link* head = NULL, *tail = NULL;
    static long num_links = 0;
    struct s_inv_link* temp;
    static int fh_inv = 0;              /* inventory file handle */
    long part_num = atol( part );       /* numeric part number; 0 for first part */

    /*****************************************************************************/
    /* This is the first call, so build the linked list of inventory data now.   */
    /*****************************************************************************/
    if( !fh_inv )
    {
        /*****************************************************************************/
        /* Open inventory file for binary reading.                                   */
        /*****************************************************************************/
        if( -1 == ( fh_inv = open( "INVNTORY.DAT", O_RDONLY | O_BINARY ) ) )
        {
            perror( "No file: invntory.dat" ), abort();
        }

        /*****************************************************************************/
        /* Initialize list pointers.                                                 */
        /*****************************************************************************/
        head = tail = temp = ( struct s_inv_link* )malloc( sizeof( struct s_inv_link ) );
        /*****************************************************************************/
        /* No next link yet.                                                         */
        /*****************************************************************************/
        head->p_next = NULL;

        /*****************************************************************************/
        /* Loop for records.                                                         */
        /*****************************************************************************/
        while( read( fh_inv, &( temp->rec ), sizeof( temp->rec ) ) == sizeof( temp->rec ) )
        {
            ++num_links;
            tail = temp;
            temp = ( struct s_inv_link* )malloc( sizeof( struct s_inv_link ) );
            tail->p_next = temp;        /* Make previous link point to new. */
            tail->p_next = NULL;        /* no next link from new yet */
        }

        /*****************************************************************************/
        /* If no list, then no head or tail.                                         */
        /*****************************************************************************/
        if( num_links == 0 )
        {
            head = tail = NULL;
        }

        /*****************************************************************************/
        /* Look up data for part whose number was passed in, by moving part_num-1    */
        /* links down the chain.                                                     */
        /*****************************************************************************/
        if( part_num >= num_links )
        {
            return( NO );
        }
        for( temp = head; part_num--; temp = temp->p_next );

        /*****************************************************************************/
        /* Return part data to calling function.                                     */
        /*****************************************************************************/
        strcpy( part_desc, temp->rec.desc );
        *p_price = temp->rec.price;
        *p_ship_wt = temp->rec.weight;
        return( YES );
    }
}
