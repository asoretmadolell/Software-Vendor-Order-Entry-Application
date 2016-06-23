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
