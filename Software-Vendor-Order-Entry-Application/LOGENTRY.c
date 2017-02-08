/*****************************************************************************/
/*                                                                           */
/* LOGENTRY.c                                                                */
/* "The Low Level: logentry()"                                               */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* Description:                                                              */
/*                                                                           */
/* logentry() appends message text to the end of the log file, typically     */
/* for audit, error detection, and security purposes.                        */
/*                                                                           */
/*****************************************************************************/

#include <stdio.h>

void logentry( msg )
char msg[];
{
    static FILE* p_logfile = NULL;
    long long_time;

    /*****************************************************************************/
    /* Open logfile, if it isn't already open.                                   */
    /*****************************************************************************/
    if( !p_logfile && !( p_logfile = fopen( "LOGFILE.DAT", "a" ) ) )
    {
        /*****************************************************************************/
        /* We can't call err_exit() because it tries to update log.                  */
        /*****************************************************************************/
        err_warn( "No file:", "logfile.dat" );
        abort();
    }
    time( &long_time );
    fprintf( p_logfile, "%s %s\n", ctime( &long_time ), msg );
}
