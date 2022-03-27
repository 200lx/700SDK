/* SCCS info - Module link.h  Version 1.3  Date 04/08/93  Time 12:59:49 */
/**************************************************************************
***************************************************************************
*                                                                    
*   L       LLLLL   N     N   K    K
*   L         L     NN    N   K   K 
*   L         L     N N   N   K  K
*   L         L     N  N  N   KKK
*   L         L     N   N N   K  K
*   L         L     N    NN   K   K
*   LLLLLL  LLLLL   N     N   K    K
*                                                          
***************************************************************************
***************************************************************************
*
* Authors: Pat Megowan
* Date:   3/24/92
*
***************************************************************************
**************************************************************************/

#ifndef _LINK_H

typedef struct {
char startmarker;
UCHAR len;            /* length from this fld to end */
char blocktype;       /* 0x40 for visible blocks, 0x41 for invisible */
char extendfcnid;     /* id of fcn to process this block */
char id;              /* app specific id of this block */
UCHAR outputlen;      /* length of output (set by gled) */
/* here starts clip-specific info */
UCHAR fldnum;
UCHAR width;
UCHAR flags;

UCHAR backlen;        /* backwards traversing len = len - 1 */
char endmarker;
} GLEDEXTENDERBLOCK;

/*----------------------------------------------------------------------
* perverted little struct for interpreting resourced clipflds. The
* resource editor does not allow embedded zeros, to read the following
* to interpret these properly.
*----------------------------------------------------------------------*/
typedef struct {
UCHAR fldnum_r;       /* fldnum */
UCHAR width_r;        /* width */
UCHAR flags_r;        /* flags */
} RESOURCEDCLIPFLD;

/*----------------------------------------------------------------------
* flags for gled extender block. Low three bits used for info on
* justification w/in width
*----------------------------------------------------------------------*/
//#define CLIP_NOFLAGS 0x80       /* resourced clipflds can't contain zeros */
#define CLIP_OPTLINE 0x08
#define CLIP_REVERSEFIELD 0x10

//#define FORMSPECSIZE 1024
#define FORMSPECSIZE (2048 - (sizeof(LINKDEF) + sizeof(RECORDHEADER)))
#define GLED_IDCLIP 111

#define FLDLIST_SORT 1

/*----------------------------------------------------------------------
* prototypes
*----------------------------------------------------------------------*/
int far FormSpecHandler(PWINDOW Wnd, WORD Message, WORD Data, WORD Extra);
int far LinkDlgHandler(PWINDOW Wnd, WORD Message, WORD Data, WORD Extra);
int far LinkNameHandler(PWINDOW Wnd, WORD Message, WORD Data, WORD Extra);
int far MakeFldNameList(char **PtrList, char *bufptr, int *indexlist,
		    PWINDOW Dlg, int NumWnd, int Style);
int MakeLinkList(int sel);
int far GetLinks(void);
int far LinkCount(DBBLOCK *db);
int far WriteDfltClipStart(char far *dest, char far *clipname);
void far WriteDfltClipEnd(char far *ClipStart, int ClipSize);
int far WriteClipFld(char far *dest, RESOURCEDCLIPFLD far *thing, 
		     int fldnamelen);
int far ConstructClip(char far *dest, char far *src, 
		      FIELDDEF far *f,char far *clipname);
BOOL far SetupSmartClip(void);

int far AddClipFldHandler(PWINDOW Wnd, WORD Message, WORD Data, WORD Extra);
void far ClipEngine(GLEDSTUFF far *GS, WORD fcnnum, char far *src, 
		    char far *dest, UCHAR boldflg, WORD curcol, 
		    char far **notejmpaddr, WORD jmplen);
void ReverseField(char *src, int len);
int far GetLinks(void);
int far SetupIndexCard(void);

#define _LINK_H
#endif
