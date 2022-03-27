/* SCCS info - Module cmds.h  Version 1.2  Date 01/22/93  Time 11:25:40 */
/**************************************************************************
***************************************************************************
*** 
***      CCCCC    M     M   DDDDD     SSSSS       H     H
***     C     C   MM   MM   D    D   S     S      H     H
***     C         M M M M   D     D  S            H     H
***     C         M  M  M   D     D   SSSSS       HHHHHHH
***     C         M     M   D     D        S      H     H
***     C     C   M     M   D    D   S     S  ..  H     H
***      CCCCC    M     M   DDDDD     SSSSS   ..  H     H
*** 
***************************************************************************
***************************************************************************
*
* Author: Pat Megowan,
* Date:   4/28/92
*
***************************************************************************
***************************************************************************/

#ifndef _CMDS_H

/*----------------------------------------------------------------------
* commands to index handler
*----------------------------------------------------------------------*/
#define CMD_EDIT          0xFF    /* edit a record (ENTER KEY) */
#define CMD_ADD           0xFE    /* Add a record */
#define CMD_DELETE        0xFD    /* delete a record */
#define CMD_TOGGLE_TITLES 0xFC    /* toggles the show col headers state */
#define CMD_FETCH         0xFB    /* Fetch an SMS Message */
#define CMD_SEND 			  0xFA    /* Send SMS Messages */
#define CMD_CUT           0xF9    /* clipboard CUT */
#define CMD_COPY          0xF8    /* clipboard COPY */
#define CMD_PASTE         0xF7    /* clipboard PASTE */
#define CMD_SELECT        0xF6    /* select a record */
#define CMD_SELECT_ALL    0xF5    /* select all records */
#define CMD_DESELECT_ALL  0xF4    /* de-select all records */
#define CMD_NEXT          0xF3    /* goto next record (in card view) */
#define CMD_PREV          0xF2    /* goto prev record (in card view) */
#define CMD_PHNBK 		  0xF1    /* Display Phone Book in SMS Send */
#define CMD_QUIT_APP      0xF0    /* used for menu Quit or menu File Exit */ 
#define CMD_WRITECARD     0xEF    /* cardhandler tells parent to write rec */
#define CMD_LINK          0xEE    /* link operation specific to app */
#define CMD_UNDO          0xED    /* perform an undo operation */
#define CMD_SHOWNOTE      0xEC    /* show associated note full screen */
#define CMD_FILTER        0xEB    /* bring up filter screen */
#define CMD_NO            0xEA    /* "no" option chosen in dialog */
#define CMD_NOTEDONE      0xE9    /* note handler received CMD_DONE */
#define CMD_FILTERDONE    0xE8    /* filter dlg is finished */
#define CMD_NAME          0xE7
#define CMD_PARSE         0xE6    /* issued by card if I->Style & PARSE_CARD */
#define CMD_REPEAT        0xE5    /* issued to find wnd for repeat last find */
#define CMD_SAVE          0xE4    /* initiate save action (used in note) */
#define CMD_INSERT        0xE3    /* initiate insert action (used in note */
#define CMD_F10KEY        0xE2
#define CMD_SHOWINDEXCARD 0xE1    /* toggles disp of bus card in index */
/*----------------------------------------------------------------------
* cmds used only by arrange column handler
*----------------------------------------------------------------------*/
#define CMD_WIDTHPLUS  90
#define CMD_WIDTHMINUS 91
#define CMD_RESET      92
#define CMD_MOVERIGHT  93
#define CMD_MOVELEFT   94


#define NOTIFY_CARDDONE   0x9090
#define NOTIFY_CARDESC    0x9091
#define NOTIFY_DRAWCURSOR 0x9092
#define NOTIFY_VPTCHANGED 0x9093

#define NOTIFY_DELETEYES  0x9094  /* delete confirmation notifies */
#define NOTIFY_DELETENO   0x9095
#define NOTIFY_DELETEESC  0x9096
#define NOTIFY_DELETEDONE 0x9097
#define NOTIFY_DONE       0x9098
#define NOTIFY_ESC        0x9099
#define NOTIFY_SAVEYES    NOTIFY_DELETEYES
#define NOTIFY_SAVENO     NOTIFY_DELETENO
#define NOTIFY_SAVEESC    NOTIFY_DELETEESC
#define NOTIFY_FILEOPEN   0x909D

/*----------------------------------------------------------------------*/

#define CMD_WORLD         0x1234   /* Just start at some crappy high value */


/************************************************************************
 *
 * Added in by Soemin Tjong (06/04/1995)
 * For generic message box implementation.
 *
 ************************************************************************/


#define CMD_YES           0x2828   
#define CMD_STDMSG		  0x2829
#define CMD_NONE			  0x2830
#define CMD_GOTO			  0x2831	


/* TO MUTE OR NOT TO MUTE... THAT IS THE QUESTION. */
#define CMD_MUTE          0X2832

#define _CMDS_H
#endif
