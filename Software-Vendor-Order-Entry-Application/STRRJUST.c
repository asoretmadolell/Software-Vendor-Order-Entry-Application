/*****************************************************************************/
/*                                                                           */
/* STRRJUST.c                                                                */
/* "The Project Utility Functions: strrjust()"                               */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* Description:                                                              */
/*                                                                           */
/* strrjust() takes a string and a length and right justifies the string in  */
/* a field of that length. If the string is longer than the field, no        */
/* action is taken.                                                          */
/*                                                                           */
/*****************************************************************************/

#include <stdio.h>
#include "STDDEFS.h"

void strrjust( str, fld_len )
char str[];
short fld_len;
{
    short end_char, ichar, move;

    /*****************************************************************************/
    /* Find index of last non-space in str and back up from there toward         */
    /* beginning; then fill left end of str with blanks.                         */
    /*****************************************************************************/
    for( end_char = strlen( str ) - 1; str[ end_char ] == ' ' && end_char > 0; --end_char );

    move = fld_len - end_char - 1; /* number of positions */

    /*****************************************************************************/
    /* Need to move anything?                                                    */
    /*****************************************************************************/
    if( move > 0 && end_char >= 0 )
    {
        /*****************************************************************************/
        /* Copy characters.                                                          */
        /*****************************************************************************/
        for( ichar = end_char; ichar >= 0; --ichar )
        {
            str[ ichar + move ] = str[ ichar ];
        }

        /*****************************************************************************/
        /* Fill left end with blanks.                                                */
        /*****************************************************************************/
        for( ichar = move - 1; ichar >= 0; --ichar )
        {
            str[ ichar ] = ' ';
        }

        /*****************************************************************************/
        /* null terminator.                                                          */
        /*****************************************************************************/
        str[ fld_len ] = '\0';
    }
}