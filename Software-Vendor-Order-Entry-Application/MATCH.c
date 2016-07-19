/*****************************************************************************/
/*                                                                           */
/* MATCH.c                                                                   */
/* "The Project Utility Functions: match()"                                  */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* Description:                                                              */
/*                                                                           */
/* match() verifies a data string, character by character, against a match   */
/* string. If the match string is shorter than the data string, the          */
/* last match-string character is used to verify the data string.            */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* The match string may be composed of these match characters:               */
/*                                                                           */
/*    A   A-Z                             (uppercase letters)                */
/*    #   0-9 only                        (numbers)                          */
/*    S   0-9 or + or -                   (signs or numbers)                 */
/*    F   0-9 or .                        (floating-point numbers)           */
/*    L   a-z, A-Z, 0-9 or ;:.,/?*-$#()'! (names, addresses)                 */
/*           and non-leading spaces                                          */
/*    U   A-Z, 0-9 or ;:.,/?*-$#()'!      (uppercase names, addresses)       */
/*           and non-leading spaces                                          */
/*    P   0-9 or - or () or space         (phone numbers)                    */
/*    Q   one of "Yy1Nn0"                 (question reply)                   */
/*    X   any printable character         (text)                             */
/*                                                                           */
/* Any other character in the match string is ignored. Spaces are matched    */
/* by L, U, and P. Empty match string matches any data.                      */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* Return value:                                                             */
/*                                                                           */
/* YES = data string matches; NO = no match.                                 */
/*                                                                           */
/*****************************************************************************/

#include "STDDEFS.h"
#include <ctype.h>      /* for isxxx() character-type macro definitions */

flag match( data_str, match_str )
char data_str[];        /* source string to be verified */
char match_str[];       /* match characters to match */
{
    short ichar;        /* input character counter */
    char c_data;        /* character of data string */
    char c_match;       /* character of match string */

    /* Initialize a variable to a function return. */
    short len_match = strlen( match_str );
    bflag matches = YES;

    for( ichar = 0; data_str[ ichar ] != '\0' && matches; ++ichar )
    {
        /*****************************************************************************/
        /* Determine match character.                                                */
        /*****************************************************************************/
        if( ichar < len_match )         /* Use next match character. */
        {
            c_match = match_str[ ichar ];
        }
        else if( len_match == 0 )       /* null match_str */
        {
            c_match = '\0';
        }
        else                            /* Use last character of match string. */
        {
            c_match = match_str[ len_match - 1 ];
        }
        c_data = data_str[ ichar ];

        /*****************************************************************************/
        /* Check match with data.                                                    */
        /*****************************************************************************/
        switch( c_match )
        {
            /*****************************************************************************/
            /* A-Z (uppercase letters)                                                   */
            /*****************************************************************************/
            case 'A':
                if( !isupper( c_data ) )
                {
                    matches = NO;
                }
                break;

            /*****************************************************************************/
            /* 0-9 only (numbers)                                                        */
            /*****************************************************************************/
            case '#':
                if( !isdigit( c_data ) )
                {
                    matches = NO;
                }
                break;

            /*****************************************************************************/
            /* 0-9 or + or - (signs or numbers)                                          */
            /*****************************************************************************/
            case 'S':
                if( !isdigit( c_data ) && !strchr( "+-", c_data ) )
                {
                    matches = NO;
                }
                break;

            /*****************************************************************************/
            /* a-z, A-Z, 0-9 or ;:.,/?*-$#()'! or space (names, addresses)               */
            /*****************************************************************************/
            case 'L':
                if( !isalnum( c_data ) && !strchr( ";:.,/?*-$#()'! ", c_data ) )
                {
                    matches = NO;
                }
                if( ichar == 0 && c_data == ' ' )   /* no leading blanks */
                {
                    matches = NO;
                }
                break;

            /*****************************************************************************/
            /* A-Z, 0-9 or ;:.,/?*-$#()'! or space (upperc. names, addresses)            */
            /*****************************************************************************/
            case 'U':
                if( !isupper( c_data ) && !isdigit( c_data ) && !strchr( ";:.,/?*-$#()'! ", c_data ) )
                {
                    matches = NO;
                }
                if( ichar == 0 && c_data == ' ' )   /* no leading blanks */
                {
                    matches = NO;
                }
                break;

            /*****************************************************************************/
            /* 0-9 or - or () or space (phone numbers)                                   */
            /*****************************************************************************/
            case 'P':
                if( !isdigit( c_data ) && !strchr( "-() ", c_data ) )
                {
                    matches = NO;
                }
                break;

            /*****************************************************************************/
            /* 0-9 or . (floating-point numbers)                                         */
            /*****************************************************************************/
            case 'F':
                if( !isdigit( c_data ) && !strchr( ".", c_data ) )
                {
                    matches = NO;
                }
                break;

            /*****************************************************************************/
            /* one of "Yy1Nn0" (as reply to yes/no question)                             */
            /*****************************************************************************/
            case 'Q':
                if( !strchr( "Yy1Nn0", c_data ) )
                {
                    matches = NO;
                }
                break;

            /*****************************************************************************/
            /* Must be printable (' '-'~')                                               */
            /*****************************************************************************/
            case 'X':
                if( !isprint( c_data ) )
                {
                    matches = NO;
                }
                break;
        }
    }

    return( matches );
}
