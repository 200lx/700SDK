/* SCCS info - Module index.h  Version 1.8  Date 05/05/93  Time 15:05:21 */
/**************************************************************************
***************************************************************************
*** 
***     IIIII   N     N   DDDDD     EEEEEEE   X     X      H     H
***       I     NN    N   D    D    E          X   X       H     H
***       I     N N   N   D     D   E           X X        H     H
***       I     N  N  N   D     D   EEEE         X         HHHHHHH
***       I     N   N N   D     D   E           X X        H     H
***       I     N    NN   D    D    E          X   X   ..  H     H
***     IIIII   N     N   DDDDD     EEEEEEE   X     X  ..  H     H
*** 
***************************************************************************
***************************************************************************
*
* Author: Pat Megowan
* Date:   3/24/92
*
***************************************************************************
***************************************************************************/

#ifndef _INDEX_H

/*----------------------------------------------------------------------
* defines for index cursor
*----------------------------------------------------------------------*/
#define CURSOR_ON    (-1)     /* Used to order DispCursor around */
#define CURSOR_OFF   (-2)
#define CURSOR_UP    (-3)
#define CURSOR_DOWN  (-4)
#define CURSOR_RIGHT (-5)
#define CURSOR_LEFT  (-6)
#define CURSOR_GOTO  (-7)

/*----------------------------------------------------------------------
* values of Style in indexblock
*----------------------------------------------------------------------*/
#define ARRANGE_VIEW   0x0001 /* single column cursor - arrange index view */
#define INDEX_NOCURSOR 0x0002 /* set to suppress cursor in index */
#define APPT_APP       0x0004 /* is this the appt book? (used by link) */
#define PARSE_CARD     0x0008 /* set when parsing desired at carddone */
#define SHIFT_SET      0x0010 /* indicates shift state is set */
#define BINARY_ONLY    0x0020 /* tells clipengine to format binary only */

/*----------------------------------------------------------------------
* misc other defines
*----------------------------------------------------------------------*/
#define SCROLL_UP 2           /* Used to order ScrollIndex around */
#define SCROLL_DOWN 3

#define DRAW_NOERASE 1        /* Redraw index view w/out any erasing first */

#define PRINT_INDEX 1         /* printing styles */
#define PRINT_CUSTOM 2

#define STATUS_ADD 1          /* used to track add/edit status */

#define STATUS_CARDEDITED 2   /* tracks edit status of multipage cards */
#define STATUS_CARDNOTECREATED 1

#define CARD_SETCARDPAGE 0x0400 /* style create card on spec'd page */

#define CURR_ITEM (*I->Db->viewpt)[I->TopItem+I->CursorRow]

#define INDEXCARDSPECSIZE 500
#define SMALLINDEX_W 230
#define BIGINDEX_W 624
#define OFFSET_X 8
#define OFFSET_Y 6
#define buscard_x (OFFSET_X + SMALLINDEX_W + 10)
#define buscard_y 22
#define buscard_w (640 - buscard_x - OFFSET_X)
#define buscard_h (192 - buscard_y - OFFSET_Y)

#define ICONSIZE 200

/*****************************************************************************
******************************************************************************
*
* IndexPrintBlock - controls printing setup of indexstyle apps
*
******************************************************************************
******************************************************************************/
typedef struct {
  int LinesPerPage;             /* total lines per page on printer */
  int TopMargin;                /* top margin for printing */
  int BottomMargin;
  char InitCodes[40];           /* user supplied printer init string */
  char TermCodes[40];           /* user supplied printer terminate string */
  int PrDriver;                 /* printer driver */
} INDEXPRINTBLOCK;

/*****************************************************************************
******************************************************************************
*
* Multi-page card struct and defs
*
******************************************************************************
******************************************************************************/
#define MAX_CARD_PAGES 4
#define PAGE_CHANGE 33

typedef struct {
  PWINDOW cardctrls;                 /* save area for original Card Data */
  int currpage;                      /* used by Card to track current page */
  int pagecount;                     /* number of pages in card */
  int pagestart[MAX_CARD_PAGES];     /* indices of ctrls starting each page */
  int pagesize[MAX_CARD_PAGES];      /* number of controls on each page */
} CARDPAGEDEF;

/*****************************************************************************
******************************************************************************
*
* INDEX - Index control block
*
* An INDEX block is the Data field of an index view window and the basic
* means by which the index handler manages the view.
*
******************************************************************************
******************************************************************************/
typedef struct {
	int x,y,w,h;		/* upper left corner of index on screen */
	int NumRows,NumChars;	/* number of rows/chars shown in index view */
	int TopItem;		/* index into Viewpt Key of item at pagetop */
	int CursorRow;		/* Highlighted line number rel to top */
	int CursorColumn;       /* Used by col arrange */
	COLUMNINFO *Column;     /* ptr to struct defining column arrangement */
	BOOL ShowHeaders;       /* flag: TRUE => show column titles */
	BOOL AddRecord;         /* TRUE if adding a record, false if editing */
	PWINDOW CardWindow;     /* Window that defines card view for index */
	DBBLOCK *Db;            /* database control block */
        char *Record;           /* ptr to buffer for packed record */
	char *CardBuffer;       /* ptr to buffer for unpacked record */
	int RecordSize;         /* size of record and card buffers */
	int NoteRecordNum;      /* record # of note w/curr data record */
	int NoteFieldNum;       /* flddef index of note field; -1 if none */
	GLEDSTUFF *GledStuff;   /* Note control buffer */
	PWINDOW NoteWnd;        /* full screen note window */
	int Style;              /* INDEX_VIEW or ARRANGE_VIEW, NOCURSOR etc. */
	int FirstVarFieldOffset; /* offset to 1st variable len fld in record */
	int (far *GetField)(DBBLOCK *db, char far *rec, int fld, char far *str,
			    int bufsize, int recnum);  
	/* call back for getting custom fields */
	int (far *GetFieldName)(int index, char far *str, int bufsize);
	int AppView;            /* application view e.g. MAP vs. CITY */
	PRES AppName;           /* at app discretion - not used by index */
	int TextOffset;         /* offset to actual text in Index area */
/* if non-NULL, SendMsg DRAW/DRAW_CURSOR on dispcursor */
	PWINDOW CursorCallbackWnd; 
	PWINDOW GotoWnd;        /* window to call when goto initiated */
        PWINDOW DelConfirmWnd;  /* window to call to confirm delete op */
	char *FilterBuffer;     /* scratch buffer used in subset and link */
	char **FldNameList;     /* list widely used show field names */ 
        PWINDOW ClipDlgWnd;     /* ptr to overall clip dialog */
	PWINDOW ClipSpecWnd;    /* ptr to window for creating clipspecs */
        PWINDOW AddClipFldWnd;  /* ptr to dlg for adding fld to clipspec */
	BOOL Done;              /* main loop done flag */
        PWINDOW SaveWnd;        /* save confirmations in notes and cards */
        PWINDOW TopWnd;         /* app indexwnd */
	int (far *MakeFldNameList)(char **PtrList, char *bufptr, 
				   int *indexlist, PWINDOW dwin, int NumWnd);
        PWINDOW FindDlg;        /* Find Dlg window - for repeat last find */
	int UndoTopItem;	/* index into Viewpt Key of item at pagetop */
	int UndoCursorRow;      /* Highlighted line number rel to top */
        char *TitleBuffer;      /* used often to hold titles of objects */
        INDEXPRINTBLOCK *PrintStuff; /* points to index prt setup data */     
        char LinkDefType;       /* tells smartclip the linkdef type */
	int NoteFieldOffset;    /* offset to note recnum in Record */
	BOOL UndoModify;        /* if true there is a db modify to undo */
	BOOL SuppressUndo;      /* temp suppresses undo when inapprop */
        CARDPAGEDEF *CardPageDef;  /* holds cardpagedef if any or null */
        BOOL ShowIndexCard;     /* show bus card in index view if true */
        char *IndexCardSpec;    /* ptr to ram for indexcard spec */
//        BOOL IncludeCategory;   /* tells whether db has category fld */
//	int CategoryCardPtr;    /* position of category in cardef */
//        char *DfltCategory;     /* pointer to default category */
} INDEX;

typedef INDEX *PINDEX;

typedef struct {
	int thickline_linenum;
	int thinline_linenum;
	int icon_linenum;
	int indent;
        char icon[ICONSIZE];
} DATACARDDEF;

/*****************************************************************************
******************************************************************************
*
* index handler prototypes
*
******************************************************************************
******************************************************************************/
int far IndexHandler(PWINDOW Wnd, WORD Message, WORD Data, WORD Extra);
int far ConfirmHandler(PWINDOW Wnd, WORD Message, WORD Data, WORD Extra);
int DoCardView(PWINDOW Wnd, PINDEX I);
int far DelRecordUtil(PINDEX I, UINT recnum);
int DeleteRecord(PINDEX I);
void far ClearCardBuffer(PINDEX I);
int ReadAndUnpack(PINDEX I);
int WriteRecord(PINDEX I, int Size);
int far DBError(int err);
#define WriteError(fred) DBError(fred)
#define ReadError(fred) DBError(fred)
//int far ReadError(int err);
BOOL far ReadRecUtil(int type, int recnum, int *size);
BOOL far WriteRecUtil(int type, int recnum, int size);
int far GetMemUtil(char far ***handleaddr, long int bufsize);
int far EmptyList(PINDEX I);

void DispIndex(PINDEX IBlk);
void far DispRow(PINDEX IndexBlk, int recordnum, int Row);
void far DispCursor(PINDEX I, int Style);
void GetArrangeCoords(PINDEX IndexBlk, int *x1, int *x2);
void InvertBlock(int x1, int y1, int x2, int y2);
void DispHeaders(PINDEX Iblk, PWINDOW wnd);
void ScrollIndex(PINDEX I, int Direction, int NumLines);
void far FormatRecord(PINDEX I, int recordnum, char *Buffer, int Bufsize);
void far FormatHeaders(PINDEX I, char *Buffer, int Bufsize);
void AdjustCursor(PINDEX I, int n);

BOOL CardEdited(PINDEX I, PWINDOW dwin);
int EndCardView(PINDEX I);
void far UnpackRecord(char *Read, PWINDOW dwnd, FIELDDEF far *fdef);
int far PackRecord(PINDEX I, int *nullrec);

void MoveIndexUp(PINDEX I);
void MoveIndexDown(PINDEX I);
void MoveIndexPageUp(PINDEX I);
void MoveIndexHome(PINDEX I);
void MoveIndexPageDown(PINDEX I);
void MoveIndexEnd(PINDEX I);

int CopyToClipboard(PINDEX I);
BOOL CopyToClipGuts(PINDEX I, UINT recnum);
int far IndexSetUndoPtUtil(void);
int far RemoveAmpersand(char far *dest, char far *src, int len);

int ComputeLogicalSize(CARDPAGEDEF *CardPage);
void NullChildren(PWINDOW dlg);
void far DrawDlg(PWINDOW dlgwnd, WORD Data);

int far SetViewpt(DBBLOCK *Db, int sel);
PWINDOW far GetParent(void);
void far SetCapError(int errnum);
int far GetCapError(void);
BOOL far GledError(int errnum);
void far ClearCapError(void);
BOOL far KeyCheckUtil(void);
void far FlushKBUtil(void);
void far RaisedRect(int x, int y, int w, int h, int border);
void far RoundRect(int x, int y, int w, int h, int radius, int pw, int fflag, int color);
void far SetIndexWidth(void);

/*----------------------------------------------------------------------
* This piece of putrid garbage is courtesy of Andrew J. Gryc and the 
* malevolent Whore-ld Time application .
*----------------------------------------------------------------------*/
#define  GMT_FIELD USER_FIELD

#define _INDEX_H
#endif
