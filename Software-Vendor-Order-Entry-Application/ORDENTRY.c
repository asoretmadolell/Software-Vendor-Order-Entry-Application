/*****************************************************************************/
/*                                                                           */
/* ORDENTRY.c                                                                */
/* "The Top Level: main()"                                                   */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* Description:                                                              */
/*                                                                           */
/* The main() function for the Software Vendor Order-Entry Program. Each     */
/* case commands a significant step in order entry, such as prompting for    */
/* a screen of data or sending order data to a file.                         */
/*                                                                           */
/* The action after the completion of a step will be one of the following:   */
/*    Cancel the order.                                                      */
/*    Back up to previous step.                                              */
/*    Go on to the next step.                                                */
/*                                                                           */
/* The action is controlled by the user's use of special command characters  */
/* that are described further in the header file "PROJUTIL.h".               */
/*                                                                           */
/*****************************************************************************/
