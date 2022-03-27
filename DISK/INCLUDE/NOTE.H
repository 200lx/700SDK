/* SCCS info - Module note.h  Version 1.2  Date 03/03/93  Time 08:54:12 */
/**************************************************************************
***************************************************************************
*                                                                    
*     N     N    OOOOO   TTTTTTT  EEEEEEE      H     H
*     NN    N   O     O     T     E            H     H
*     N N   N   O     O     T     E            H     H
*     N  N  N   O     O     T     EEEE         HHHHHHH
*     N   N N   O     O     T     E            H     H
*     N    NN   O     O     T     E        ..  H     H
*     N     N    OOOOO      T     EEEEEEE  ..  H     H
*                                                          
***************************************************************************
***************************************************************************
*
* Author: Pat Megowan
* Date:   5/22/92
*
***************************************************************************
**************************************************************************/

#ifndef _NOTE_H

#define NOTE_BIGCARDNOTE 0x0008
#define CARDNOTE_NOBOX   0x0010
#define NOTE_KEEPMEM     0x0020 /* noteedit: don't release mem on destroy */
#define SAVE_NOTE 1            /* save note to file */
#define INSERT_NOTE 2          /* insert file into note */

extern GLEDSTUFF GStuff;
extern WINDOW NoteWnd;

int far NoteHandler(PWINDOW Wnd, WORD Message, WORD Data, WORD Extra);
int far CardNoteHandler(PWINDOW Wnd, WORD Message, WORD Data, WORD Extra);

int far SetupNote(DBBLOCK *db, int noterecnum, GLEDSTUFF *gstuff, 
	       char far ***notehandleaddr);
int far WriteNote(DBBLOCK *db, int *noterecnum, GLEDSTUFF *gstuff, 
	       char far *notebuffer);
int far FinishNote(char far **notehandle);
int far GetNoteAppFld(DBBLOCK *db, char far *rec, int fld, char far *str,
			    int bufsize, int recnum);
int far GetNoteAppFldName(int index, char far *str, int bufsize);
int SaveNote(PWINDOW Wnd, char far *filename);
unsigned int InsertNote(PWINDOW Wnd, char far *fname, UCHAR *bufptr, UINT buflen);

#define _NOTE_H
#endif

