/*****************************************************************************/
/*                                                                           */
/* STRFLD.c                                                                  */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* Description:                                                              */
/*                                                                           */
/* strfld() copies a field from a record to a separate string and returns    */
/* the starting address of the target, to_str.                               */
/*                                                                           */
/*****************************************************************************/

#define DELIM '|'               /* delimeter to separate fields of a record */

char *strfld( to_str, from_rec, fld_num )
char to_str[];                  /* target string to copy field to */
char from_rec[];                /* record string to copy field from */
short fld_num;                  /* field number to copy */
{
    /*****************************************************************************/
    /* indices into from_rec and to_str                                          */
    /*****************************************************************************/
    short ifrom, ito;

    /*****************************************************************************/
    /* Skip over ( fld_num - 1 ) delimeters to the field to copy.                */
    /*****************************************************************************/
    for( ifrom = 0; --fld_num && from_rec[ ifrom ] != '\0'; )
    {
        while( from_rec[ ifrom ] != '\0' && from_rec[ ifrom ] != DELIM )
        {
            ++ifrom;
        }
        if( from_rec[ ifrom ] == DELIM )
        {
            ++ifrom;
        }
    }

    /*****************************************************************************/
    /* Copy field from from_rec to to_str.                                       */
    /*****************************************************************************/
    for( ito = 0; from_rec[ ifrom ] != '\0' && from_rec[ ifrom ] != '\n' && from_rec[ ifrom ] != DELIM; ++ifrom, ++ito )
    {
        /*****************************************************************************/
        /* Copy a character to to_str                                                */
        /*****************************************************************************/
        to_str[ ito ] = from_rec[ ifrom ];
    }
    to_str[ ito ] = '\0';

    return( &to_str[ 0 ] );
}
