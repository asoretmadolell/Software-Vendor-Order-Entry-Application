/*****************************************************************************/
/*                                                                           */
/* INVMAINT.c                                                                */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* Description:                                                              */
/*                                                                           */
/* Inventory file maintenance: lists and adds parts to inventory.            */
/*                                                                           */
/*****************************************************************************/

#include <stdio.h>
#include <fcntl.h>
#include <sys\types.h>
#include <sys\stat.h>
#include <io.h>
#include "STDDEFS.h"

/*****************************************************************************/
/* Macros PROMPT and ERR_EXIT use read() and write() to perform user I/O     */
/*****************************************************************************/
#define PROMPT( msg, mlen, ans, alen ) write( STDOUT, msg, mlen ), \
    ans[ read( STDIN, ans, alen ) -1 ] = '\0'
#define ERR_EXIT( sl ) write( STDERR, sl, strlen( sl ) ), \
    write( STDERR, "\7\n", 2 ), exit( FAIL )

main()
{
    IMPORT long atol( char[] );
    int fh_inv;                     /* invntory.dat file handle */
    long part_num;                  /* integer part number */
    char cmd;                       /* command to add or list part */
    char reply[ 81 ];               /* user input buffer to hold replies */
    char buf[ 20 ];                 /* buffer for binary-to-ASCII conversions */
    struct s_inv_rec                /* Declare structure type; define tag. */
    {
        long price;                 /* price to charge for part, in cents */
        short weight;               /* shipping weight, in ounces */
        char desc[ 31 ];            /* description of part */
    };
    struct s_inv_rec inv_rec;       /* Declare record struct inv-rec */

    /*****************************************************************************/
    /* Open inventory file invntory.dat for reading and writing. Create the      */
    /* file if it does not exist, and open it in binary mode.                    */
    /*****************************************************************************/
    if( -1 == ( fh_inv = open( "INVNTORY.DAT", O_RDWR | O_CREAT | O_BINARY ) ) )
    {
        ERR_EXIT( "No file: invntory.dat" );
    }

    while( 1 )                      /* Infinite loop; exit is in loop body. */
    {
        /*****************************************************************************/
        /* Prompt for command: Add or List? <a/l>                                    */
        /*****************************************************************************/
        PROMPT( "\nInventory Maint: Add or List? <a/l>", 37, reply, 80 );
        cmd = reply[ 0 ];

        /*****************************************************************************/
        /* No cmd, so we're done.                                                    */
        /*****************************************************************************/
        if( cmd != 'a' && cmd != '1' )
        {
            close( fh_inv ), exit( SUCCEED );
        }

        /*****************************************************************************/
        /* Prompt for part number to add or list.                                    */
        /*****************************************************************************/
        PROMPT( "\nPart #: ", 9, reply, 80 );
        part_num = atol( reply );   /* Convert from ASCII to binary */

        /*****************************************************************************/
        /* Position file pointer at start of record part.                            */
        /*****************************************************************************/
        lseek( fh_inv, (long)part_num * sizeof inv_rec, 0 );

        /*****************************************************************************/
        /* Add a part.                                                               */
        /*****************************************************************************/
        if( cmd == 'a' )
        {
            /*****************************************************************************/
            /* Prompt for part_desc, price, and ship_weight.                             */
            /*****************************************************************************/
            PROMPT( "\nDesc: ", 7, inv_rec.desc, 30 );
            PROMPT( "\nPrice: ", 8, reply, 80 );
            inv_rec.price = atol( reply );                  /* ASCII to binary */
            PROMPT( "\nWeight (oz.): ", 14, reply, 80 );
            inv_rec.weight = atoi( reply );                 /* ASCII to binary */

            /*****************************************************************************/
            /* Output record from structure inv_rec.                                     */
            /*****************************************************************************/
            write( fh_inv, &inv_rec, sizeof inv_rec );
        }
        /*****************************************************************************/
        /* Read record and list part.                                                */
        /*****************************************************************************/
        else if( cmd == '1' )
        {
            /*****************************************************************************/
            /* Got whole record? Then list part_desc, price, and ship_weight.            */
            /*****************************************************************************/
            if( read( fh_inv, &inv_rec, sizeof inv_rec ) == sizeof inv_rec )
            {
                write( STDOUT, "\nDesc: ", 7 );
                write( STDOUT, inv_rec.desc, strlen( inv_rec.desc ) );
                write( STDOUT, "\nPrice: ", 8 );
                ltoa( inv_rec.price, buf, 10 );         /* Convert price and output. */
                write( STDOUT, buf, strlen( buf ) );
                write( STDOUT, "\nWeight: ", 9 );
                itoa( inv_rec.weight, buf, 10 );        /* Convert weight and output. */
                write( STDOUT, buf, strlen( buf ) );
                write( STDOUT, "\n\n", 2 );             /* Skip two lines. */
            }
        }
    }
}
