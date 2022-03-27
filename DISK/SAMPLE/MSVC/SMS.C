/*****************************************************************************
 *
 *      Filename:       sms.c
 *
 *      Author:         Christopher Koh
 *
 *      Description:    This file contains variable declarations for SMS API
 *                      routines usage. You may modify the variable names.
 *
 *      Revision:       0.0
 *
 *      Date Created:   01/04/96
 *
 *      Modification History:
 *
 *****************************************************************************/

#include "sms.h"

SEND_PACKET    SendSMSMsg;       // Buffer to hold SMS Message to be sent
RECEIVE_PACKET RecvSMSMsg;       // Buffer to hold SMS Message received

/*******************************************************************
 *
 * Comm port parameters.
 *
 *******************************************************************/


int            sms_comm_port=COM_LINE_3;       // Com port number
com_handle     sms_handle;          // Handle set by ComOpen() routine.
ComSettings_t  sms_comm_settings=
               { 0,
                 COM_BR_9600,
                 COM_PTY_NO,
                 COM_STOP_1,
                 COM_DATA_8,
                 COM_FLOW_NONE,
                 COM_IR_OFF};   // Com port setting.
// WORD           ComChoice;       // Com port choice


/*******************************************************************
 *
 * SMS receive buffer settings.
 * SMS_RxMessage may contain valid message with 
 * header, footer, stuffbyte, MSB checksum and LSB checksum
 * stripped off.   
 * The checksum is stored in SMS_MSB and SMS_LSB.
 *
 *******************************************************************/


char     SMS_RxMessage[SMS_RX_MESSAGE_LENGTH];   

int      SMS_RxMessage_head;     // point to where new char is to be put 

