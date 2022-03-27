#include "cmds.h"
#include "sms.h"
#include "smserror.h"

extern char PhoneNum[];
extern LHEDITDATA SendBuff;

void far DoSendSMS(void)
{
   unsigned char result;

   SMS_InitSendPacket(&SendSMSMsg);
   lstrcpy (SendSMSMsg.DestAddr, PhoneNum);
   lstrcpyto (SendSMSMsg.UserData, *SendBuff.Buffer, SendBuff.TextLen+1); // Grab User Data

   if ((result = InitModem_and_EnterSMS(sms_comm_port,sms_handle,sms_comm_settings)) != PASS)   
   {
		if (result != RESPONSE_OPEN_COMM_FAILED)
	      SMS_CloseComm();
      return;
   }

   if ((result = SMS_SendOneMessage(sms_handle, &SendSMSMsg)) != PASS)
   {
      SMS_CloseComm();
      return;

   }
   result = SMS_FetchResponse(sms_handle);

	// New Card correctly implemented the send sequence, in which
	// a request confirmed message is sent out to TE before any actual 
	// result of sending.
	// However, since our implementation need to be able to cater for the 
	// older generation of the card, the RESPONSE CONFIRMED is thought of to
	//	optional in this case.
	//	Meaning :   If there is a response confirmed, then fine, otherwise
	//					also fine ..

	if (result == RESPONSE_REQUEST_CONFIRMED)
	   result = SMS_FetchResponse(sms_handle);

   QuitSMS_and_CloseModem(sms_handle);

}

int far SendMessageHandler(PWINDOW Wnd, WORD Message, WORD Data, WORD Extra)
{
   PWINDOW dwin = (PWINDOW)Wnd->Data;
	char	display[20] ;
	unsigned char i;
	int	size;
	

	
	switch (Message) {
		case DRAW:
			break;

    	case KEYSTROKE:
			switch (Data) 
			{
				case ESCKEY:
      			return SendMsg(Wnd, COMMAND, CMD_ESC, 0);
				default:
					break;
      	}
    	case COMMAND:
			switch (Data) {
      		case CMD_SEND:
            	DoSendSMS();
		  			return TRUE;
      		case CMD_ESC:
				   SendMsg(Wnd, DESTROY, 0, 0);
					return TRUE;
				default:
					break;
      	}
		default:
			break;
  	}	 	

  	return SubclassMsg(DialogBox, Wnd, Message, Data, Extra);
}

