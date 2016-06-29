/*****************************************************************************/
/*                                                                           */
/* BEG_SCRN.c                                                                */
/* "The Project Utility Functions: beg_scrn()"                               */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* Description:                                                              */
/*                                                                           */
/* beg_scrn() clears the screen and displays screen heading strings. Four    */
/* headings may be shown: left, center, right, below. The first three        */
/* headings appear on the top line, the last is centered on the next line.   */
/*                                                                           */
/*****************************************************************************/

#include "STDDEFS.h"        /* for CLR_SCRN (clear screen) */
#include <stdio.h>          /* for stderr for screen control */
#include "PROJUTIL.h"       /* for declarations of tput() */

#define SCRNWDTH    80      /* screen width */

void beg_scrn( left, center, right, below )
char left[], center[], right[], below[];    /* headings or null */
{
    CLR_SCRN;
    tput( 1, 1, left );
    tput( 1, ( SCRNWDTH - strlen( center ) ) / 2, center ); /* Center heading. */
    tput( 1, 1 + SCRNWDTH - strlen( right ), right );
    tput( 2, ( SCRNWDTH - strlen( below ) ) / 2, below ); /* Center heading. */
}
