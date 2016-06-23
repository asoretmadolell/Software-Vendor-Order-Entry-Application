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
