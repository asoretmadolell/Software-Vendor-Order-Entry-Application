/*****************************************************************************/
/*                                                                           */
/* ORDERNUM.c                                                                */
/* "The Low Level: order_num()"                                              */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* Description:                                                              */
/*                                                                           */
/* order_num() returns the order number to use for the next order. The       */
/* order number is a counter that increases by one with each order. It is    */
/* stored in the file ordernum.dat.                                          */
/*                                                                           */
/*****************************************************************************/

#include <stdio.h>

#define FRSTONUM 10001
#define LASTONUM 99999

long order_num()
{
    static FILE* p_ordernum = NULL;
    long order_cnt;

    /*****************************************************************************/
    /* Open ordernum, if it isn't already open.                                  */
    /*****************************************************************************/
    if( !p_ordernum && !( p_ordernum = fopen( "ORDERNUM.DAT", "r+" ) ) )
    {                                           /* Is this the first call to pw_find()? */
        err_exit( "No file:", "ordernum.dat" );
    }
    
    rewind( p_ordernum );                       /* before switching from writing to reading. */
    fscaf( p_ordernum, "%ld", &order_cnt );     /* Input old number. */
    rewind( p_ordernum );                       /* before switching from reading to writing. */

    if( order_cnt >= LASTONUM )                 /* Highest order number? */
    {
        order_cnt = FRSTONUM;                   /* Yes; start over again. */
    }
    else
    {
        ++order_cnt;                            /* Increment order number. */
    }

    fprintf( p_ordernum, "%ld\n", order_cnt );  /* Save new number. */
    return( order_cnt );
}
