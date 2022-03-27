/*************************************************************************
 *    Filename       :     ASMSERR.H
 *    
 *    Author         :     Soemin Tjong
 *
 *    Revision       :     0.0
 *    
 *    Date Created   :     07/03/95
 *    
 *    Modification   :
 *    history
 *
 *    - Soemin Tjong (10 Jan 1996) [BM1]
 *      The WAIT_OK_ATT is very much affected by the fact that phone can
 *      now hold as many as 25 messages (160 chars each).
 *      AT*T will take much longer when more messages are stored.
 *      Decided to use 30 seconds...
 *      Ideally, AT*T should always return successfully...
 *
 *
 *************************************************************************/

/*******************************************************************
 *
 * Errors & responses indication for error handling
 * Please be reminded that constant number 1 is reserved for PASS
 * constant number 0 is reserved for FAIL through out SMS...
 * Hence the Error response starts from 2 ...
 *
 *******************************************************************/

#define  RESPONSE_INSERT_SMS_COMPLETE         2
#define  RESPONSE_INSERT_SMS_FAILURE          3
#define  RESPONSE_UNABLE_TO_PROCESS           4
#define  RESPONSE_DEL_MESSAGE_COMPLETE        5
#define  RESPONSE_DEL_MESSAGE_FAILURE         6
#define  RESPONSE_END_SMS_MODE                7
#define  RESPONSE_SPOOKY                      8
#define  RESPONSE_GET_MESSAGE_FAILURE         9
#define  RESPONSE_INTERNAL_MSG_FAILURE       10   // Valid msg but invalid internal
                                                  // components like DCS etc.
#define  RESPONSE_UNABLE_TO_INIT_MODEM       11
#define	RESPONSE_OPEN_COMM_FAILED				12
#define  RESPONSE_UNABLE_ENTER_SMS_MODE      13
#define  RESPONSE_FAIL_CHECKSUM              14
#define  RESPONSE_NO_RESPONSE_FETCH          15   // No response from MT during fetch
#define  RESPONSE_SEND_ROUTINE_FAIL          16   // com send() routine failed
#define  RESPONSE_VALID_MESSAGE              17
#define	RESPONSE_REQUEST_CONFIRMED				18	  // MT understood our request.
																  // For Columbia, it will only be
																  // Insert SMS request !

#define	RESPONSE_OLD_EDITED_MESSAGE			19	  // MTI is SUBMIT, an indicator
																  // that message is old edited
																  // message
																  // NOTE: Not an error condition
#define  RESPONSE_NO_RESPONSE_SEND           20   // No response from MT during send

#define  RESPONSE_FETCH_FUNNY_FAIL           22   // To cater for unexpected fetch result
#define  RESPONSE_SEND_FUNNY_FAIL            23   // To cater for unexpected send result

#define  RESPONSE_SENDOK_WITH_WARNING        24    // Non ETSI encountered...

#define  RESPONSE_OPEN_FAILED_BATT           25    // Modem init failed.
                                                   // Prob of Low main batt.

#define  RESPONSE_BOUNDARY                   26


#define	RESPONSE_UNIMPLEMENTED					99


/*******************************************************************
 *
 * GSM 04:11                             
 * RP-ERROR cause values for a mobile    
 *      originated SM-transfer attempt   
 * GSM 04:11, version 3.3.0, Table 8.4   
 *
 *******************************************************************/

#define  SMS_RPE_UNALLOC                 1
#define  SMS_RPE_BARRED                  10
#define  SMS_RPE_CUG_REJECT              11
#define  SMS_RPE_SMT_REJECT              21
#define  SMS_RPE_OUT_OF_SERVICE          27
#define  SMS_RPE_UNIDENTIFIED            28
#define  SMS_RPE_FAC_REJECT              29
#define  SMS_RPE_UNKNOWN                 30
#define  SMS_RPE_NETWORK_FAIL            38
#define  SMS_RPE_TEMP_FAIL               41
#define  SMS_RPE_CONGESTION              42
#define  SMS_RPE_NO_RESOURCES            47
#define  SMS_RPE_NOT_IMPLEMENTED         69
#define  SMS_RPE_BAD_REF_VALUE           81
#define  SMS_RPE_BAD_MSG                 95
#define  SMS_RPE_MISSING                 96
#define  SMS_RPE_BAD_MSG_TYPE            97
#define  SMS_RPE_NOT_COMPATIBLE          98
#define  SMS_RPE_BAD_IE                  99
#define  SMS_RPE_BAD_IE_CONTENTS         100
#define  SMS_RPE_MSG_NOT_OK              101
#define  SMS_RPE_PROT_ERROR              111
#define  SMS_RPE_INTERWORKING            127

/*******************************************************************
 *
 * Cause Values sent between TE & MT     
 * when there is problem.
 * ETSI 07:05 pp 31                      
 *
 *******************************************************************/

#define SMS_CAUSE_NO_SUCH_MSG                   0x00
#define SMS_CAUSE_NO_MEMORY                     0x01
#define SMS_CAUSE_NO_AIR_IF                     0x02
#define SMS_CAUSE_RX_BUSY                       0x03
#define SMS_CAUSE_BAD_CMD                       0x04
#define SMS_CAUSE_DATA_IN                       0x05
#define SMS_CAUSE_USER_EXIT                     0x06
#define SMS_CAUSE_TRANSFER_FAIL                 0x07


