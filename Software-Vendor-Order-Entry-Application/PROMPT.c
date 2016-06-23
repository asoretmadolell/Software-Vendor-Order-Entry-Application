/*****************************************************************************/
/*                                                                           */
/* PROMPT.c                                                                  */
/* "The Project Utility Functions: prompt()"                                 */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* Description:                                                              */
/*                                                                           */
/* prompt() inputs text from standard input to the string "data".            */
/* Input is matched against an optional match-string argument. Minimum and   */
/* maximum input lengths are checked. If Boolean (flag) argument mand        */
/* is true, then "data" will not be allowed to remain null; an entry must    */
/* be made. The parameter "data" is both passed in and returned to the       */
/* caller. The value passed in is treated as a default to be used if input   */
/* is null. Data are input character-at-a-time, without automatic echo.      */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* Return value:                                                             */
/*                                                                           */
/* The outcome of prompt() has synonym data type stepcode, which is used     */
/* to indicate:                                                              */
/*                                                                           */
/*    STEPOK    Step complete; go on to next step                            */
/*    STEPBACK  Back up to closest previous step.                            */
/*    STEPCANC  Cancel order entry (quit).                                   */
/*                                                                           */
/* C_BACK, C_NULL, and C_CANC are defined in "PROJUTIL.h". The user can      */
/* request to back up by entering C_BACK, to cancel by entering C_CANC,      */
/* or to erase data by entering C_NULL as any character in the reply.        */
/*                                                                           */
/*****************************************************************************/
