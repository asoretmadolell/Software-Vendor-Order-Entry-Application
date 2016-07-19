/*****************************************************************************/
/*                                                                           */
/* PROJUTIL.h                                                                */
/* "Project Utility Header"                                                  */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* Description:                                                              */
/*                                                                           */
/* Project utility library function header file. #include this file near     */
/* the start of source files containing functions that will call any of the  */
/* project utility functions listed below.                                   */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* Project Utility Function Summary:                                         */
/*                                                                           */
/*    prompt()      Input a string, check match, check length.               */
/*    nprompt()     Prompt for a long int, echo right justified.             */
/*    fprompt()     Prompt for a double, echo right justified.               */
/*    tput()        Print a string at specific screen row and column.        */
/*    ntput()       Print a long integer right justified on screen.          */
/*    ftput()       Print a double right justified on screen.                */
/*    beg_scrn()    Clear screen; print four headings at screen top.         */
/*    match()       Compare a data string against a match string.            */
/*    strrjust()    Right justify a string, padding with blanks.             */
/*    err_warn()    Print a warning message, input Escape.                   */
/*    err_exit()    Call err_warn(), then terminate the program.             */
/*    logentry()    Append message text to log file.                         */
/*                                                                           */
/*****************************************************************************/

#ifndef IMPORT          /* If IMPORT is not already #defined, then do it now. */
#define IMPORT extern
#endif

/*****************************************************************************/
/* Type stepcode is a synonym data type defined below. The typedef statement */
/* makes stepcode equivalent to type char. Type stepcode declares return     */
/* values from the functions prompt(), nprompt(), and fprompt().             */
/*****************************************************************************/
typedef char stepcode;

/*****************************************************************************/
/* Declare project utility function return and argument types. These         */
/* declarations make it possible to call any of these functions from         */
/* anywhere within the source file after this header file is #included.      */
/* The call will be checked for the proper number and types of arguments     */
/* and proper use of the return value.                                       */
/*****************************************************************************/
IMPORT stepcode     prompt( char[], char[], short, short, flag, short, short );
IMPORT stepcode     nprompt( long *, char[], long, long, flag, short, short );
IMPORT stepcode     fprompt( double *, char[], double, double, short, short, flag, short, short );
IMPORT void         tput( short, short, char[] );
IMPORT void         ntput( short, short, long, char[], short );
IMPORT void         ftput( short, short, double, short, char[], short );
IMPORT void         beg_scrn( char[], char[], char[], char[] );
IMPORT flag         match( char[], char[] );
IMPORT void         strrjust( char[], short );
IMPORT void         err_warn( char[], char[] );
IMPORT void         err_exit( char[], char[] );
IMPORT void         logentry( char[] );

/*****************************************************************************/
/* Argument constants and control symbols for prompt().                      */
/*****************************************************************************/
#define PRMTBSIZ    161         /* prompt buffer size */
#define MAND        1           /* for fifth argument: mandatory input */
#define OPT         0           /* for fifth argument: optional input */
#define C_MASK      '_'         /* character to repeat for prompt field */

/*****************************************************************************/
/* User command characters for prompt().                                     */
/*****************************************************************************/
#define C_NULL      '\x05'      /* ERASE ENTRY: '\x05' is control-E. */
#define C_BACK      '\x12'      /* BACK UP: '\x12' is control-R. Move back to previous prompt. */
#define C_CANC      '\x18'      /* CANCEL: '\x18' is control-X. Cancel order and program. */

/*****************************************************************************/
/* These are the possible return values from prompt() that a variable with   */
/* synonym type stepcode may take.                                           */
/*****************************************************************************/
#define STEPOK      0           /* Data were entered; may be null if OPT. */
#define STEPBACK    1           /* C_BACK was entered; back up a prompt. */
#define STEPCANC    2           /* C_CANC was entered; cancel transaction. */

/*****************************************************************************/
/* Note this statement:                                                      */
/*    enum stepcode { STEPOK, STEPBACK, STEPCANC }                           */
/* This enumeration does almost the same job as the typedef synonym type     */
/* stepcode and the symbols STEPOK, STEPBACK, and STEPCANC. The difference   */
/* is that a variable of synonym type stepcode is not an enumerated constant */
/* and so may be incremented and decremented. The increment and decrement    */
/* operators are used here to compute the next step to perform. At some      */
/* future time, ANSI may decide to permit ++ and -- on enumerated type       */
/* variables                                                                 */
/*****************************************************************************/
