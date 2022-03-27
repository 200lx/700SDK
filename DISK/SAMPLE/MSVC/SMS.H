/************************************************************************
 *
 *      Filename:       sms.h
 *
 *      Author:         Christopher Koh
 *
 *      Description:    This file contains structure declarations for API
 *                      usage. DO NOT MODIFY.
 *                      Value enclosed in <> indicates default value.
 *
 *      Revision:       0.0
 *
 *      Date Created:   01/04/96
 *
 *      Modification History:
 *          - 1/4/96: Added SMS_SEND_PACKET and SMS_RECEIVE_PACKET
 *
 ************************************************************************/

#include "cap2.h"
#include "interfac.h"
#include "lstring.h"
#include "comio.h"

/*******************************************************************
 *
 * SCRAP VARIABLES-MUST BE REMOVED AFTER DEVELOPMENT
 *
 *******************************************************************/

// #define  LOGDEBUG

/* SMS Settings Variable */
extern char MsgCenterPhn[];
extern WORD ValidPeriod;
extern WORD ReplyPathOK;
extern WORD PhoneMsgDel;
extern char far *msgMsgSetting;

/*******************************************************************
 *
 * Structure Declaration for SEND_PACKET
 *
 *******************************************************************/

typedef struct {
      int   SendType;         // Message Send Type:
                              //    1 =Send Message to Phone
                              //   <2>=Send Message to SMSC
                              //    3 =Send Message to Both Phone & SMSC
      char  DestAddr[21];     // Destination Address, Max 20 digits
      char  SMSCAddr[21];     // SMSC Address, Max 20 digits. NULL means
                              // use Phone's SMSC
      char  DCS;              // Data Coding Scheme: 
                              //    <0>=7-bit, 
                              //     1 =8-bit
      char  PID;              // Protocol ID
                              //    <0>=SMS
                              //     1 =Fax
                              //     2 =Paging
      unsigned int RP;        // Reply Path
                              //    <0>= Reply Path enabled
                              //     1 = Reply Path disabled
      unsigned int SR;        // Status Report
                              //    <0>= Disable Status Report
                              //     1 = Enable Status Report
      unsigned int VP;        // Validity Period
                              //    <0>= 1 hr
                              //     1 = 6 hr
                              //     2 = 1 day
                              //     3 = 1 week
                              //     4 = Max (63 weeks)
      char  UserData[161];    // User Data, maximum 160 characters
} SEND_PACKET;

typedef SEND_PACKET _near *PSEND_PACKET;

/*******************************************************************
 *
 * Structure Declaration for RECEIVE_PACKET
 *
 *******************************************************************/

typedef struct {
      unsigned char   MRN;              // Message Reference Number
      unsigned char   MS;               // Message Status
      unsigned char   SMSCAType;        // Service Centre Address Type
      char            SMSCAddr[21];     // SMSC Address, Max 20 digits
      unsigned char   MTI;              // Message Type Indicator
      unsigned char   MMS;              // More message to send => Pending messages
                                        // in SMSC
      unsigned char   RP;               // Reply Path Availability
      unsigned char   OAType;           // Originator Address Type
      char  OriginAddr[21];             // Originator Address, 20 digits max
      unsigned char   PID;              // Protocol ID
                                        //   <0> = SMS
                                        //    1  = Fax
                                        //    2  = Paging
      unsigned char   DCS;              // Data Coding Scheme
                                        //   <0> = 7-bit
                                        //    1  = 8-bit
      char  SCTS[7];                    // SMSC Time Stamp
      char  UserData[161];              // User Data, maximum 160 characters
} RECEIVE_PACKET;

typedef RECEIVE_PACKET _near *PRECEIVE_PACKET;
        
extern SEND_PACKET    SendSMSMsg;
extern RECEIVE_PACKET RecvSMSMsg;
extern int            sms_comm_port;       // Com port number
extern com_handle     sms_handle;          // Handle set by ComOpen() routine.
extern ComSettings_t  sms_comm_settings;   // Com port setting.

#ifndef FIRST_MESSAGE
	#define FIRST_MESSAGE 1		// Indication for Get message to do GetFirstMessage
#endif

#ifndef NOT_FIRST_MESSAGE
	#define NOT_FIRST_MESSAGE 0 // Indication to do GetNextMessage
#endif

#define  SMS_RX_MESSAGE_LENGTH         500   // Length of received message.
#define  SMS_TX_MESSAGE_LENGTH         500
#define  SMS_USER_MESSAGE_MAX_LENGTH   512   // 160 chars max

/*******************************************************************
 *
 * Miscellaneous Definitions
 *
 *******************************************************************/

#define  null  0x00  // Termination of string.
#define  PASS  1
#define  FAIL  0
#define  EOL   0xFF  // Effort to terminate fields that may contain 0x00
                     // For example, in SCTS fields of SMS_PACKET structure.

#define  WAIT_OK_ATZ        5L		//  3   seconds for OK after ATZ.
#define  WAIT_OK_ATT       10L		//  30  seconds for OK after AT*T
#define  WAIT_OK_ENDSMS     8L		//  8   seconds for OK after End SMS Mode
#define  WAIT_VALID_MSG     8L      //  8   seconds for a valid message during fetch
#define  WAIT_RESP_MSG     10L      //  30  seconds for a response message in


/*******************************************************************
 *
 * Message specific declarations.
 *
 *******************************************************************/

#define  DLE         0x10  // Delimiter of SMS message.
#define  STX         0x02  // Start of message indicator.
#define  ETX         0x03  // End of message indicator.
#define  STUFF_BYTE  0X00  // Stuff byte used in SMS packets.


/*******************************************************************
 *
 *  SMS state as used in SMS_Mode_Processor()
 *
 *******************************************************************/

#define SMS_WAITING_FOR_STX            1
#define SMS_WAITING_FOR_ETX            2
#define SMS_WAITING_FOR_BCSMSB         3
#define SMS_WAITING_FOR_BCSLSB         4
#define SMS_MESSAGE_FOUND              5

/*******************************************************************
 *
 * SMS Transmitted Message Types         
 * Commands issued by Terminal Equipment 
 * to Mobile Termination.
 * ETSI 07:05 pp 15                      
 *
 *******************************************************************/

#define SMS_TX_ListRequest                      0x00
#define SMS_TX_GetMessage                       0x01
#define SMS_TX_GetFirstMessage                  0x02
#define SMS_TX_GetNextMessage                   0x03
#define SMS_TX_TransferIncSMS                   0x04
#define SMS_TX_IndicateIncSMS                   0x05
#define SMS_TX_TransferIncCBS                   0x06
#define SMS_TX_InsertMessage                    0x07
#define SMS_TX_DeleteMessage                    0x08
#define SMS_TX_UnableToProcess                  0x09
#define SMS_TX_EndSMSMode                       0x1E

/*******************************************************************
 *
 * Type of address                       
 * ETSI 03:40 pp 33                      
 *
 *******************************************************************/

#define SMS_TOA_UNKNOWN         0  
#define SMS_TOA_INT             1  /* International no           */
#define SMS_TOA_NAT             2  /* National no                */
#define SMS_TOA_NET             3  /* Network Specific no        */
#define SMS_TOA_SUB             4  /* Subscriber no              */
#define SMS_TOA_ALP             5  /* Alphanumeric               */
#define SMS_TOA_ABB             6  /* Abbreviated no             */
#define SMS_TOA_RES             7  /* Reserved for extension     */


/*******************************************************************
 *
 * Type of address                       
 * ETSI 03:40 pp 33                      
 *
 *******************************************************************/

#define SMS_TOA_UNKNOWN         0  
#define SMS_TOA_INT             1  /* International no           */
#define SMS_TOA_NAT             2  /* National no                */
#define SMS_TOA_NET             3  /* Network Specific no        */
#define SMS_TOA_SUB             4  /* Subscriber no              */
#define SMS_TOA_ALP             5  /* Alphanumeric               */
#define SMS_TOA_ABB             6  /* Abbreviated no             */
#define SMS_TOA_RES             7  /* Reserved for extension     */


/*******************************************************************
 *
 * Numbering Plan Identification         
 * ETSI 04:11 pp 39                      
 *
 *******************************************************************/

#define SMS_NPI_UNKNOWN         0                          
#define SMS_NPI_ISDN            1  /* ISDN / Telephone numbering plan */
#define SMS_NPI_DATA            3  /* Data Numbering Plan             */
#define SMS_NPI_TELEX           4  /* Telex Numbering Plan            */
#define SMS_NPI_NAT             8  /* National Numbering Plan         */
#define SMS_NPI_PRI             9  /* Private Numbering Plan          */
#define SMS_NPI_ERMES           10 /* ERMES numbering plan            */
#define SMS_NPI_RES             15 /* Reserved for extension          */

                                                                      
/*******************************************************************
 *
 * Message-Type-Indicator                
 *
 *******************************************************************/

#define SMS_MTI_DELIVER    		0
#define SMS_MTI_SUBMIT     		1

                                                                      

/*******************************************************************
 *
 * Validity-Period-Format                
 *
 *******************************************************************/

#define SMS_VPF_NOTPRESENT 0  
#define SMS_VPF_RESERVED   1
#define SMS_VPF_INTEGER    2  /* Integer represented (relative)
#define SMS_VPF_SEMIOCTET  3  /* semi-octet represented (absolute)



/*******************************************************************
 *
 * Status-report-Indication              
 *
 *******************************************************************/

#define SMS_SRI_YES        0  /* Status report will not be returned to the SME



/*******************************************************************
 *
 * Status report request                 
 *
 *******************************************************************/

#define SMS_SRR_NOTREQUESTED  0
#define SMS_SRR_REQUESTED     1



/*******************************************************************
 *
 * Protocol-Identifier                   
 * ETSI 3:40 pp 45                       
 *
 *******************************************************************/

#define SMS_PID_DEFAULT         0       /* Simple MS to SC message transfer */



/*******************************************************************
 *
 * Reply Path                            
 *
 *******************************************************************/

#define SMS_RP_NOTSET           0
#define SMS_RP_SET              1


/*******************************************************************
 *
 * Data Coding Scheme                    
 * ETSI 03:38 pp 8                       
 *
 *******************************************************************/

#define SMS_DCS_DEFAULT         0        /* Default alphabet; 7bit encoding */
#define SMS_DCS_USERDEFINED     244      /* User defined; 8 bit encoding    */ 
                                         /* 1111-01xx */
                                         //        ^^ 
                                         //        ||
                                         //     don't care.



/*******************************************************************
 *
 * Service Centre Time Stamp             
 *
 *******************************************************************/

#define SMS_SCTS_LENGTH         7        /* 7 bytes for SCTS */



/*******************************************************************
 *
 *  SMS state as used in SMS_Mode_Processor()
 *
 *******************************************************************/

#define SMS_WAITING_FOR_STX            1
#define SMS_WAITING_FOR_ETX            2
#define SMS_WAITING_FOR_BCSMSB         3
#define SMS_WAITING_FOR_BCSLSB         4
#define SMS_MESSAGE_FOUND              5

/*******************************************************************
 *
 * SMS Received Message Types.            
 * Response or Indication issued by      
 * Mobile temination to Terminal Equipment.
 * ETSI 07:05 pp 18                      
 *
 *******************************************************************/

#define SMS_RX_MessageList                      0x20
#define SMS_RX_Message                          0x21
#define SMS_RX_GetMessageFailure                0x22
#define SMS_RX_IncMessage                       0x23
#define SMS_RX_MessageArrived                   0x24
#define SMS_RX_InsertSMSComplete                0x25
#define SMS_RX_InsertSMSFailure                 0x26
#define SMS_RX_DeleteMessageComplete            0x27
#define SMS_RX_DeleteMessageFailure             0x28
#define SMS_RX_UnableToProcess                  0x29
#define SMS_RX_RequestConfirmed                 0x2A
#define SMS_RX_EndSMSMode                       0x3F

/*******************************************************************
 *
 * Information Element Identifier        
 * Usually Octet number 2 of SMS Packet  
 * ETSI 07:05 pp 23 - 34                 
 *
 *******************************************************************/

#define SMS_ID_SMS_REFERENCE                    0x00
#define SMS_ID_TRANSFER_TYPE                    0x01
#define SMS_ID_INDICATION_TYPE                  0x02
#define SMS_ID_INSERT_TYPE                      0x03
#define SMS_ID_SMS_INDEX                        0x04
#define SMS_ID_CBS_INDEX                        0x05
#define SMS_ID_SMS_DATA                         0x06 // <<-- SMS deliver...
#define SMS_ID_CBS_DATA                         0x07
#define SMS_ID_CAUSE                            0x08
#define SMS_ID_INDEX_COUNT                      0x09
#define SMS_ID_CBS_TRANSFER_TYPE                0x0A
#define SMS_ID_PAGE_INDEX                       0x0B
#define SMS_ID_LAST_SMS                         0x0C
#define SMS_ID_CONFIRM_TYPE                     0x0D



