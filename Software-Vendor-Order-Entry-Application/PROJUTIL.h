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
/* These are the possible return values from prompt() that a variable with   */
/* synonym type stepcode may take.                                           */
/*****************************************************************************/
#define STEPOK 0        /* Data were entered; may be null if OPT. */
#define STEPBACK 1      /* C_BACK was entered; back up a prompt. */
#define STEPCANC 2      /* C_CANC was entered; cancel transaction. */

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
