/*****************************************************************************/
/*                                                                           */
/* STDDEFS.h                                                                 */
/* "Company-Wide Header"                                                     */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* Description:                                                              */
/*                                                                           */
/* Standard defined symbols for general use. The file "stdio.h" should       */
/* be #included with this file if DEBUG macros or screen-control             */
/* definitions will be used.                                                 */
/*                                                                           */
/*****************************************************************************/

/*****************************************************************************/
/*                                                                           */
/* Symbols related to definition and use of shared data. Declarations of     */
/* data with storage class static or external should begin with these        */
/* shared-data modifiers:                                                    */
/*                                                                           */
/*    GLOBAL begins defining declarations for external data; data are        */
/*    shared by all functions that IMPORT the data.                          */
/*                                                                           */
/*    SEMIGLOBAL begins defining declarations for static external data;      */
/*    data are shared by functions in the same source file that IMPORT       */
/*    the data.                                                              */
/*                                                                           */
/*    IMPORT begins non-defining declarations of GLOBAL and SEMIGLOBAL       */
/*    data. A defining declaration allocates new, initialized storage.       */
/*    Non-defining declarations refer to data defined elsewhere, to          */
/*    allow examination or modification of those data.                       */
/*                                                                           */
/*****************************************************************************/
#define GLOBAL
#define SEMIGLOBAL static
#define IMPORT extern

/*****************************************************************************/
/* Data types that are synonyms of other types.                              */
/*****************************************************************************/
typedef unsigned char unchar;       /* unsigned characters */
typedef unsigned short unshort;     /* unsigned short integers */
typedef unsigned long unlong;       /* unisgned long integers */
typedef char byte;                  /* byte: 1-byte number (0 to 127) */
typedef char bflag;                 /* blag: 1-byte true/false flag */
typedef int flag;                   /* flag: int-sized true/false flag */

/*****************************************************************************/
/* Constants for true or false data, to be used in conjunction with synonym  */
/* types flag (int sized) and bflag (char sized).                            */
/*****************************************************************************/
#ifndef YES     /* If not already defined, then define YES, NO. */
#define YES 1
#define NO 0
#endif