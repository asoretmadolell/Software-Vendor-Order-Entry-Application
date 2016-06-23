/*****************************************************************************/
/*                                                                           */
/* NPROMPT.c                                                                 */
/* "The Project Utility Functions: nprompt()"                                */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* Description:                                                              */
/*                                                                           */
/* nprompt() inputs a long integer from standard input. Input is matched     */
/* against an optional match-string argument. Minimum and maximum input      */
/* values are checked. If the Boolean (flag) argument mand is true, then     */
/* data will not be permitted to remain zero; data must be entered. The      */
/* parameter *p_num is both passed in and returned to the caller. The        */
/* value passed in is treated as a default to be used if input is null.      */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* Return value:                                                             */
/*                                                                           */
/* The outcome of nprompt() has synonym data type stepcode, which is used    */
/* to indicate:                                                              */
/*                                                                           */
/*    STEPOK    Step complete; valid number obtained.                        */
/*    STEPBACK  Back up to the previous step.                                */
/*    STEPCANC  Cancel order entry (quit).                                   */
/*                                                                           */
/* C_BACK, C_NULL, and C_CANC are defined in "PROJUTIL.h". The user can      */
/* request to back up by entering C_BACK, to cancel by entering C_CANC,      */
/* or to set *p_num to zero by entering C_NULL as any character in reply.    */
/*                                                                           */
/*****************************************************************************/
