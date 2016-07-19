/*****************************************************************************/
/*                                                                           */
/* ORDENTRY.h                                                                */
/* "Order-Entry Header"                                                      */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* Description:                                                              */
/*                                                                           */
/* Header file for the order-entry application.                              */
/*                                                                           */
/*****************************************************************************/

/*****************************************************************************/
/* Type money is defined as a synonym of type long for amounts of money in   */
/* cents up to + or - $21,474,836.47.                                        */
/*****************************************************************************/
typedef long money;

/*****************************************************************************/
/* Order data maximum field widths defined for data input by prompt().       */
/*****************************************************************************/
#define L_USER          25
#define L_PASSWORD      8
#define L_OFFICE        25
#define L_CUST_NAME     30
#define L_COMPANY       30
#define L_PHONE         14
#define L_SHIP_NAME     40
#define L_SHIP_CMPY     40
#define L_SHIP_STRT     40
#define L_SHIP_STRT2    40
#define L_SHIP_CITY     15
#define L_SHIP_STATE    2
#define L_SHIP_ZIP      5
#define L_BILL_SAME     1
#define L_BILL_NAME     40
#define L_BILL_CMPY     40
#define L_BILL_STRT     40
#define L_BILL_STRT2    40
#define L_BILL_CITY     15
#define L_BILL_STATE    2
#define L_BILL_ZIP      5
#define L_IS_RESALE     1
#define L_RESALE_ID     17
#define L_ADV_REF       40
#define L_PARTS         15
#define L_PART_DESC     30
#define L_PRICES        11
#define L_TAX_AMT       11
#define L_SHIP_CAR      19
#define L_PAY_TERMS     10
#define L_COMMENT       69

/*****************************************************************************/
/* Maximum number of items on an order.                                      */
/*****************************************************************************/
#define MAX_ITEMS       10

/*****************************************************************************/
/* Maximum numberic values input by nprompt() and fprompt().                 */
/*****************************************************************************/
#define H_QUANTITY      999L
#define H_SHIP_AMT      30000.0
#define H_TAX_PCNT      99.9
