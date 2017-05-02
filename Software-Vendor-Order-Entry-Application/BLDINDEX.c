/*****************************************************************************/
/*                                                                           */
/* BLDINDEX.c                                                                */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* Description:                                                              */
/*                                                                           */
/* bldindex() constructs an index file for direct access to a data file.     */
/* Each output line has two fields: key and offset. The output is written    */
/* to stdout, so it can be redirected.                                       */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* The function takes one or two command-line arguments:                     */
/*    BLDINDEX datafile [ key_field_number ]                                 */
/*                                                                           */
/*****************************************************************************/

#include <stdio.h>
#include "STDDEFS.h"

#define DELIM '|'               /* delimeter to separate fields of a record */

main( ac, av )
unsigned ac;
char *av[];
{
    IMPORT char *strfld( char[], char[], short ), *strchr();
    char buf[ BUFSIZ ];         /* buffer for data record */
    char key[ BUFSIZ ];         /* key field of data record */
    FILE *p_infile;             /* input file stream */
    long file_pos;              /* return from ftell(): offset */
    short key_field_num = 1;    /* field number that holds key */
    char *end_pos;              /* end-of-record position */

    if( ac < 2 || ac > 3 )
    {
        err_exit( "Use: BLDINDEX data file [ key_field_number ]", "" );
    }
    if( NULL == ( p_infile = fopen( av[ 1 ], "r" ) ) )
    {
        err_exit( "Can't open file: ", av[ 1 ] );
    }
    if( ac >= 3 )                           /* Key field command-line argument? */
    {
        key_field_num = atoi( av[ 2 ] );    /* Yes; get field number. */
    }

    /*****************************************************************************/
    /* Loop for each record (line) of input file.                                */
    /*****************************************************************************/
    file_pos = ftell( p_infile );
    while( fgets( buf, BUFSIZ, p_infile ) )
    {
        if( ( end_pos = strchr( buf, '\n' ) ) )     /* Is there a newline symbol? */
        {
            *end_pos = '\0';                        /* Strip it. */
            strfld( key, buf, key_field_num );
            if( key[ 0 ] != '\0' )                  /* Is there any key? */
            {
                printf( "%s%c%ld\n", key, DELIM, file_pos );
            }
            file_pos = ftell( p_infile );
        }
    }
}
