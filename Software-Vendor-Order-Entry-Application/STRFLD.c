/*****************************************************************************/
/*                                                                           */
/* STRFLD.c                                                                  */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* Description:                                                              */
/*                                                                           */
/* strfld() copies a field from a record string to a separate string and     */
/* returns the starting address of the target, to_str. (A record here is a   */
/* string containing fields separated by DELIM.)                             */
/*                                                                           */
/*****************************************************************************/

#define DELIM '|'               /* delimeter to separate fields of a record */

char *strfld( from_rec, fld_num, to_str )
register char from_rec[];       /* record string to copy field from */
short fld_num;                  /* field number to copy */
register char *to_str;          /* target string to copy field to */
{
    /*****************************************************************************/
    /* hold initial value for return.                                            */
    /*****************************************************************************/
    char *p_to_str = to_str;

    /*****************************************************************************/
    /* Skip to field to copy.                                                    */
    /*****************************************************************************/
    while( --fld_num && *from_rec != '\0' )
    {
        while( *from_rec != '\0' && *from_rec != DELIM )
        {
            ++from_rec;
        }
        if( *from_rec == DELIM )
        {
            ++from_rec;
        }
    }

    /*****************************************************************************/
    /* Copy field from from_rec to to_str.                                       */
    /*****************************************************************************/
    while( *from_rec != '\0' && *from_rec != DELIM )
    {
        /*****************************************************************************/
        /* Copy a character to to_str and increment pointers.                        */
        /*****************************************************************************/
        *to_str++ = *from_rec++;
    }

    to_str = '\0';

    return( p_to_str );
}
