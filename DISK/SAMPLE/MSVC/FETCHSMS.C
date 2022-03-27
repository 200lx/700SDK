#include "sms.h"
#include "smserror.h"
#include "cmds.h"
#include "cougraph.h"
#include "icons\newphone.ic"

extern char FirstTime;

#define MSGCARD_LINESIZE   13
#define BUFF_SIZE         321

int DisplayMsg(void)
{
   	int i=0,j=0,k,width=0,notelen,lines=0;
   	int x=45,y=29,maxchars=30,maxlines=9;
   	int buscard_x=50,buscard_y=29, buscard_w=400;
	char buf[40];
  	char *bufptr = buf;
  	char *bufptr2;
  	char *noteptr;
  	char *noteptr2;
  	char scrap[BUFF_SIZE];

	/* ************************************************************ */
	/* ************************************************************ */
 	// clear datacard display region, then stuff the icon back where it
 	// belongs.

	// erase prev contents 
	Rectangle(buscard_x+3,y+1,(maxchars)*10,maxlines*MSGCARD_LINESIZE,0,G_SOLIDFILL);    

  	y += MSGCARD_LINESIZE;  /* move drawing loc down a line */
  	G_LineType(0xAAAA);        /* every other pixel on */
  	Line(buscard_x+20, y+10, buscard_w + (buscard_x - 21), y+10, 1);/* thick line */
  	G_LineType(0xFFFF);        /* reset line type */
  	G_ImagePut(buscard_x + 10, 36, newphone, G_FORCE);

   	// Display Phone Number
   	lstrcpy (scrap,"From : ");
   	lstrcpy (scrap+lstrlen(scrap),RecvSMSMsg.OriginAddr);
   	DrawText(buscard_x+55,y-5,scrap,DRAW_NORMAL);           

   	// Display Message
   	x = buscard_x+55;
  	y += MSGCARD_LINESIZE;  /* move drawing loc down a line */
	lmemset(scrap,0,BUFF_SIZE);
   	notelen = lstrlen(RecvSMSMsg.UserData);
	for (i=0, j=0; i<notelen; i++)
	{
		if (RecvSMSMsg.UserData[i] != 0x0A)
			scrap[j++] = RecvSMSMsg.UserData[i];
	}
   
	// Update the message length that is suppose to be parsed.
	// It is different from what read from database because we have taken
	// away all the LineFeed.
	notelen = j;

	noteptr = scrap;        /* point at start of note */
   
	bufptr2=0;                  /* wordwrap: no space to backup to */
	i=0;                        /* needed in check for wordwrap */

   	for (k=0; 1;k++ ) 
	{
   		if ((*noteptr==0x0D) || (k >= notelen)) /* CRLF or done */
		{
    		*bufptr = 0;            /* zero terminate buf before displaying */
			if (*buf)               /* anything to display? */
 				DrawText(x,y,buf,DRAW_NORMAL);
        	if (k >= notelen)       /* if done w/note, break out of loop */
	      		break;
			buf[0] = 0;             /* empty buffer */
			width = 0;              /* reset buffer length*/
			bufptr = buf;           /* reset bufptr to bufstart */
			bufptr2 = 0;
      		y += MSGCARD_LINESIZE;  /* move drawing loc down a line */
      		if (++lines >= maxlines) /* if full display, end altogether */
        		goto endbuscard;

			if (*(++noteptr)==0x0A) 
			{
				noteptr++;           /* skip past LF */
				k++;                 /* inc k one more time since skipping 2 chars */
			}
			
			noteptr2 = noteptr;
		}
		else // not CR or not upto notelen
		{
			if (*noteptr == 0x09)     /* replace TAB w/space */
	      		*noteptr = ' ';
			*bufptr++=*noteptr++;     /* move char from note to buffer */
	    	width++;                  /* add one to width of curr line */

			/* ************************************************************ */
			/* ************************************************************ */
			// If not at line end, prepare for possibility of wrapping line
			// - if char is a space, record its position for future wrap.

			if (*noteptr != 0x0D) /* at line end? */
			{
        		if (*noteptr == ' ') /* no, record position if a space */
				{
	        		noteptr2 = noteptr;
					bufptr2 = bufptr;
   				}
      			if (width>=maxchars) /* line at max len? */
				{
          			if (bufptr2 == 0) /* yes, anyplace to backup up to? */
					{
		  				noteptr2 = noteptr-1; /* no, just wrap right here */
                  		bufptr2=bufptr;
					}
       				k -= noteptr - (noteptr2-1);
        			noteptr = noteptr2; /* yes, reset noteptr for wrap */
	     			*noteptr = 0x0D;      /* force newline */
          			bufptr = bufptr2;     /* reset bufptr to last space */
	      		}
	    	}
	  	}         /* end of handling one note char */
	}           /* end of loop to disp note */
				
endbuscard:
   return TRUE;
}

int DoFetchSMS(void)
{  
   unsigned char result;
   
   
   if (FirstTime)
      	result=SMS_FetchFirstMessage(sms_handle, &RecvSMSMsg);
   else
      	result=SMS_FetchNextMessage(sms_handle, &RecvSMSMsg);  
   return result;
}

int far FetchMessageHandler(PWINDOW Wnd, WORD Message, WORD Data, WORD Extra)
{
	int result;
	
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
      			case CMD_FETCH:
               		result=DoFetchSMS();
            		if (result == RESPONSE_VALID_MESSAGE || 
                   		result == RESPONSE_OLD_EDITED_MESSAGE) {
           				FirstTime = FALSE;
                  		DisplayMsg();
               		}
               		else
               			m_beep();
		  			return TRUE;
      			case CMD_ESC:
      				QuitSMS_and_CloseModem(sms_handle);
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

