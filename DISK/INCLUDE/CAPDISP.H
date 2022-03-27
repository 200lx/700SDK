/* SCCS info - Module capdisp.h  Version 1.1  Date 01/08/93  Time 16:58:49 */
#define NEW_DRAW -1

#define PULLDOWN_LINE_SPACE 4
#define BAR_SPACE 6
#define CHARWD CHAR_WIDTH(FONT_NORM)
#define CHARHT CHAR_HEIGHT(FONT_NORM)
#define TOPMENU_HEIGHT (CHARHT+(2*BORDER_THICKNESS)+SHADOW_HEIGHT+YFILLER)
#define FILLER (CHARWD/2-1)
#define YFILLER 2
#define	BLOCKOFFSET  (SHADOW_HEIGHT+2*CHARWD)
#define LINE_SPACE (CHARHT+YFILLER)
#define TITLE_HEIGHT (CHAR_HEIGHT(FONT_NORMAL)+2)

/*----------------------------------------------------------------------
* high bit of this word used to signify small font, so watch how high
* the values get here.
*----------------------------------------------------------------------*/
#define TITLE_INDEX 0
#define TITLE_CARD 1
#define TITLE_PAGECARD 2
#define TITLE_DEFINEDB 3
#define TITLE_NOFILE 4
#define TITLE_INDEX_UPDATE 5
#define TITLE_MODIFYDB 6

void far DispTitle(PLHWINDOW Wnd);
void far DispIndexTitle(PWINDOW Wnd, int view);
void far DispCustomTitle(PWINDOW Wnd, int page, int totpages, int style);
void far AddTitleNumbers(char *titlebuf, int num1, int num2);

