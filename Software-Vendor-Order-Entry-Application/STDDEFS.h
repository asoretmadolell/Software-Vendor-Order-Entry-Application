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
typedef unsigned char   unchar;     /* unsigned characters */
typedef unsigned short  unshort;    /* unsigned short integers */
typedef unsigned long   unlong;     /* unisgned long integers */
typedef char            byte;       /* byte: 1-byte number (0 to 127) */
typedef char            bflag;      /* blag: 1-byte true/false flag */
typedef int             flag;       /* flag: int-sized true/false flag */

/*****************************************************************************/
/* Constants for true or false data, to be used in conjunction with synonym  */
/* types flag (int sized) and bflag (char sized).                            */
/*****************************************************************************/
#ifndef YES                         /* If not already defined, then define YES, NO. */
#define YES             1
#define NO              0
#endif

/*****************************************************************************/
/*                                                                           */
/* Symbols related to standard library function.                             */
/*                                                                           */
/*****************************************************************************/

/*****************************************************************************/
/* Status of SUCCEED or FAIL passed to exit(); aborts program.               */
/*****************************************************************************/
#define SUCCEED         0
#define FAIL            1

/*****************************************************************************/
/* File handles (descriptor numbers) for standard files to be used with the  */
/* low level I/O functions read() and write().                               */
/*****************************************************************************/
#define STDIN           0
#define STDOUT          1
#define STDERR          2

/*****************************************************************************/
/*                                                                           */
/* Screen and Cursor-Control commands:                                       */
/*                                                                           */
/*    CUR_MV( r, c )    Move cursor to row r (1-25), column c (1-180).       */
/*    CUR_UP( n )       Move cursor up n lines (ignored if at top).          */
/*    CUR_DN( n )       Move cursor down n lines (ignored if at bottom).     */
/*    CUR_RT( n )       Move cursor right n spaces (ignored at right margin).*/
/*    CUR_LT( n )       Move cursor left n spaces (ignored at left margin).  */
/*    CUR_SKIP          Send newline.                                        */
/*    CUR_SAVE          Save cursor position.                                */
/*    CUR_REST          Restore cursor position.                             */
/*    CLR_SCRN          Clear screen and move cursor to home.                */
/*    CLR_LINE          Erase from cursor to end of line.                    */
/*    CLR_EOS( r, c)    Erase from row r, col c to screen end, leave cursor  */
/*                      at r,c.                                              */
/*    BELL              Ring bell once by sending control-g.                 */
/*                                                                           */
/* NOTE: Definitions below are for ANSI.SYS terminal driver.                 */
/*                                                                           */
/*****************************************************************************/
#define CUR_MV( r, c )  fprintf( stderr, "\33[%d;%dH", row, col )
#define CUR_UP( n )     fprintf( stderr, "\33[%dA", num )
#define CUR_DN( n )     fprintf( stderr, "\33[%dB", num )
#define CUR_RT( n )     fprintf( stderr, "\33[%dC", num )
#define CUR_LT( n )     fprintf( stderr, "\33[%dD", num )
#define CUR_SKIP        fputs( "\n", stderr )
#define CUR_SAVE        fputs( "\33[s", stderr )
#define CUR_REST        fputs( "\33[u", stderr )
#define CLR_SCRN        fputs( "\33[2J", stderr )
#define CLR_LINE        fputs( "\33[K", stderr )
#define CLR_EOS( r, c)  { byte i_; CUR_MV( r, c, ); \
                        for( i_ = r; i_ <= 25; ++i_ ) CLR_LINE, CUR_DN( 1 ); CUR_MV( r, c ); }
#define BELL            fputc( '\7', stderr );