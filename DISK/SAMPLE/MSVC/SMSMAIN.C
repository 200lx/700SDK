/* SCCS info - Module %M%  Version %I%  Date %G%  Time %U% */

/*****************
 **   SMSMAIN   **
 *****************/

/******** Include header files *******/

#include "sms.h"
#include "smserror.h"
#include "event.h"       /* and event types */
#include "cougraph.h"
#include "cmds.h"
#include "dlgs.h"
#include "sysdefs.h"
#include "dosfile.h"


#ifdef TKERNEL
#include "chktsr.c"
#endif

#define  TITLE_HEIGHT 10

/*----------------------------------------------------------------------
* setup sysmgr farptrs for lhapi multiline edit box
*----------------------------------------------------------------------*/

char far *BuffPtrs[5]; /* sysmgr farptrs */

#define MsgBuffer  BuffPtrs[0]
#define EscBuffer  BuffPtrs[1]
#define LineStarts BuffPtrs[2]

char far *msgTestApp="SMS Test";
char far *msgAppTopLine="Sending/Receiving SMS Message";
char far *msgSendDlgTitle="Send SMS Message";
char far *msgFetchDlgTitle="Fetch SMS Message";
char far *msgPhone="&Phone";
char far *msgSendMsg="&Message";
char far *msgSend="&Send";
char far *msgFetchNextMsg="&Next";
char far *msgExit="&Exit";
char far *msgCancel="Cancel";

char far *fkeySend="Send";
char far *fkeyFetch="Fetch";
char far *fkeyNext="Next";
char far *fkeyExit="Exit";
char far *fkeyQuit="Quit";

char far *menuSend="Send\tF2";
char far *menuFetch="Fetch\tF3";
char far *menuOperation="Message";
char far *menuQuit="&Quit";

char far *msgNull="";

char far **StringTable[]={
   &msgTestApp,
   &msgAppTopLine,
   &msgSendDlgTitle,
   &msgFetchDlgTitle,
   &msgPhone,
   &msgSendMsg,
   &msgFetchNextMsg,
   &msgSend,
   &msgCancel,
   &msgExit,
   &fkeySend,
   &fkeyFetch,
   &fkeyNext,
   &fkeyExit,
   &fkeyQuit,
   &menuSend,
   &menuFetch,
   &menuOperation,
   &menuQuit,
};

/**************** Handlers *******************/
int far TopCardHandler(PWINDOW Wnd, WORD Message, WORD Data, WORD Extra);

void far DoQuit(void);
void far DoSendSMS(void);
void Uninitialize(void);

/******** Global state data *******/
EVENT app_event;          /* System manager event struct */
CAPBLOCK CapData;         /* CAP application data block */

BOOL Done;                /* Global flag for program termination */
int err;

FKEY TopFKeys[]= {
 { &fkeySend,     (PFUNC)CMD_SEND,            2, FKEY_SENDMSG },
 { &fkeyFetch,    (PFUNC)CMD_FETCH, 		  3, FKEY_SENDMSG },
 { &fkeyQuit, 	  DoQuit,      	   10+LAST_FKEY, FKEY_SENDMSG }
};

FKEY SendDlgFKeys[] = {
 { &fkeySend, (PFUNC)CMD_SEND,                9, FKEY_SENDMSG },
 { &fkeyExit, (PFUNC)CMD_ESC,      10+LAST_FKEY, FKEY_SENDMSG }
};

FKEY FetchDlgFKeys[] = {
 { &fkeyNext, (PFUNC)CMD_FETCH,               9, FKEY_SENDMSG },
 { &fkeyExit, (PFUNC)CMD_ESC,      10+LAST_FKEY, FKEY_SENDMSG }
};

/******* Menu structures *******/
// Reminder of MENU structure:  (for complete details, refer to CAP.H)
// MENU = { {Title, Handler, HotKey, Style}, ...}
// End of menu indicated by null record.

MENU OpMenu[] = {
 { &menuSend,       (PFUNC)CMD_FETCH, 0, MENU_SENDMSG, NO_HELP},
 { &menuFetch,      (PFUNC)CMD_SEND,  0, MENU_SENDMSG, NO_HELP},
 { 0, 0, 0, 0}
};

/**** TopMenu "hangs" all the previous menus off itself with MENU_PULLDOWN ****/
MENU TopMenu[] = {
 { &menuOperation, (PFUNC) OpMenu,       0, MENU_PULLDOWN },
 { &menuQuit,      DoQuit,               0 },
 { 0, 0, 0, 0}
};

/*** MyCard Dialog Window ***/
WINDOW TopCard={TopCardHandler,
       0,0,640,190,
       &msgAppTopLine,0,
       0,0,
       NULL,TopFKeys,TopMenu,NO_HELP};

LHEDITDATA SendBuff = {
  &MsgBuffer,                 /* main buffer */
  &EscBuffer,                 /* ESC restore buffer */
  (UINT far **)&LineStarts,   /* line pointer storage */
  161,                        /* max lines */
  31,                         /* line length */ 
};
char PhoneNum[21];
char MsgBuff[1024];            /* working buffer in filter/link */
char EscBuff[1024];            /* working buffer in filter/link */
char LineBuff[512];
char FirstTime;

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/******                                                                ******/
/******                END OF STRUCTURES--CODE BELOW                   ******/
/******                                                                ******/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

void FixupFarPtrs(void)
{
  int i;
  int dataseg;

  _asm {
    mov ax,ds
    mov dataseg,ax
  }

  for (i=0; i<countof(StringTable); i++)
      *(((int *)(StringTable[i]))+1) = dataseg;
}

void far DoBeep(void)
{
  m_beep();
}

void far DoQuit(void)
{
  Done = TRUE;
}

void CreateMainView(void)
{
  SendMsg(&TopCard, CREATE, CREATE_FOCUS, 0);
}

int far TopCardHandler(PWINDOW Wnd, WORD Message, WORD Data, WORD Extra)
{
	int result;
	
   	switch (Message) {
    	case DRAW:
         	if (Data&DRAW_FRAME) {
            	ClearRect(Wnd->x,Wnd->y,Wnd->w,Wnd->h);
         	}
         	if (Data&DRAW_TITLE) {
            	Rectangle(Wnd->x, Wnd->y, Wnd->w, TITLE_HEIGHT, 1, G_SOLIDFILL);
            	(DrawText)(Wnd->x+(Wnd->w>>1)-lstrlen(*(Wnd->Title))*(CHAR_WIDTH(FONT_NORM)/2),
               			Wnd->y+1, *(Wnd->Title), DRAW_INVERT, FONT_SMALL);
         	}
         	break;
  	   	case COMMAND:
    		switch (Data) {
            	case CMD_SEND:
  	            	return (SendMsg(&SendMsgDlg, CREATE, CREATE_FOCUS, 0));
            	case CMD_FETCH:
               		FirstTime=TRUE;
               		if ((result = InitModem_and_EnterSMS(sms_comm_port,sms_handle,sms_comm_settings)) != PASS)   
   					{
						if (result != RESPONSE_OPEN_COMM_FAILED)
	   						SMS_CloseComm();
      					return result;
   					}
   					else
  	            		result=(SendMsg(&FetchMsgDlg, CREATE, CREATE_FOCUS, 0));
  	            	return TRUE;
         	}
   	}
   	SubclassMsg(Object, Wnd, Message, Data, Extra);
}


int ProcessEvent(EVENT *app_event)
{
    switch (app_event->kind) {      /* Branch on SysMgr event */
      case E_REFRESH:
      case E_ACTIV:
         FixupFarPtrs();
         ReactivateCAP(&CapData);
         break;

      case E_DEACT:
         DeactivateCAP();
         break;

      case E_TERM:
         FixupFarPtrs();
         Done = TRUE;
         break;

      case E_KEY:
         /* Now send key off to current focus (KeyCode converts gray 101-key */
         /*   arrows/movement scan codes into "normal" scan codes) */
         SendMsg(GetFocus(), KEYSTROKE,
                 Fix101Key(app_event->data,app_event->scan),
                 app_event->scan);   /* Make sure we send the scan code too */
         break;
      }
}

void EventDispatcher(void)
/***
 ***  EventDispatcher grabs events from the System Manager and translates
 ***  them into CAP messages.  Every program will have an Event Dispatcher,
 ***  and the structure should follow this one.
 ***/
{
  Done = FALSE;                    /* Set terminate flag to FALSE */

  while (!Done) {                  /* While loop not terminated */
    app_event.do_event = DO_EVENT;
    m_action(&app_event);           /* Grab system manager event */
    ProcessEvent(&app_event);
  }

}

void Uninitialize(void)
/***
 *** Deinstall CAP and SysMgr
 ***/
{
  m_fini();
}

void Initialize(void)
/***
 *** Initialize CAP, SysMgr and data structures
 ***/
{
  m_init_app(SYSTEM_MANAGER_VERSION);
  InitializeCAP(&CapData);
  m_reg_app_name(msgTestApp);
  m_reg_far(&BuffPtrs, countof(BuffPtrs), 4); 

  MsgBuffer = MsgBuff; 
  EscBuffer = EscBuff;
  LineStarts= LineBuff;

  SetMenuFont(FONT_NORMAL);
  SetFont(FONT_NORMAL);
  
  // Set up ASCII to ETSI translation for active Code Page
  SetupETSICodePage();


  CreateMainView();  /* Now create the index view (it will display itself) */
  EnableClock(TRUE);
}


void main(void)
/***
 *** C main code
 ***/
{
#ifdef TKERNEL
  CheckTSRs();
#endif
  Initialize();           /* Get started */
  EventDispatcher();      /* Do stuff */
  Uninitialize();         /* Get outta there */
}
