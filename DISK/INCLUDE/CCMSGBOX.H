/* SCCS info:   Module ccmsgbox.h  Version 1.1  Date 11/09/93  Time 15:15:11 */

//----------------------------------------------------------------------------
//          Copyright (C) 1992 Lotus Development Corporation  
//                     All Rights Reserved                     
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//    ccmsgbox.h - msgbox definitions for Cougar cc:Mail Remote.
//----------------------------------------------------------------------------


/*
 * Dialog Box termination code - used to indicate the user's form of
 * termination during dialog box processing.
 */

#ifndef CMD_USER
#define CMD_USER    256
#endif

#define DB_OK	    0x0001 + CMD_USER
#define DB_CANCEL   0x0002 + CMD_USER
#define DB_YES	    0x0004 + CMD_USER
#define DB_NO	    0x0008 + CMD_USER
#define DB_SAVE     0x0010 + CMD_USER
#define DB_DISCARD  0x0020 + CMD_USER
#define DB_ESC	    0x8000 + CMD_USER

extern unsigned int far MsgBox(char far *, char far *, char far *, char far *, int, int);
extern unsigned int far GetMsgBoxEvent(void);
extern int  far DestroyMsgBox(void);
