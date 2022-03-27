
option expr32

; Begin of file lhapi.h
;  SCCS info:   Module lhapi.h  Version 1.1  Date 11/09/93  Time 15:21:16 
; ****************************************************************************
; ** $Header:   T:/hh/include/vcs/lhapi.h_v   1.48   09 Mar 1993 12:33:18   DARYL  $
; **
; ** 'C' Header File for LHAPI and LHAPI-compliant applications.
; **
; **
; ** Copyright(c) 1992
; ** Lotus Development Corporation
; ** All Rights Reserved
; **
; **
; ** Date created: December 18, 1991
; **
; ** Description:	This header contains the various structure, contant and
; **				macro definitions used by LHAPI-compliant applications,
; **				and by LHAPI itself.
; **
; *****************************************************************************
; ** $Log:   T:/hh/include/vcs/lhapi.h_v  $
;  * 
;  *    Rev 1.48   09 Mar 1993 12:33:18   DARYL
;  * Build 45.
;  * 
;  * - Added the SyncLHAPIKeyState() service to help HP try to correct a
;  * problem with the keyboard state getting out of sync when their
;  * applications enter an interuptible loop.
;  * 
;  *    Rev 1.47   26 Feb 1993 18:10:54   DARYL
;  * Build 42.
;  * 
;  *    Rev 1.46   24 Feb 1993 19:57:04   DARYL
;  * Build 41.
;  * 
;  *    Rev 1.45   22 Feb 1993 20:25:08   DARYL
;  * Build 40.
;  * 
;  *    Rev 1.44   17 Feb 1993 20:05:34   DARYL
;  * Build 39.
;  * 
;  *    Rev 1.43   15 Feb 1993 18:14:38   DARYL
;  * Build 38.
;  * 
;  *    Rev 1.42   09 Feb 1993 07:06:36   DARYL
;  * Build 36.
;  * 
;  *    Rev 1.41   01 Feb 1993 21:06:48   DARYL
;  * Build 35.
;  * 
;  * - Removed the PathEdit window class.
;  * 
;  *    Rev 1.40   25 Jan 1993 23:57:16   DARYL
;  * Build 34.
;  * 
;  * - Added the PathText window class, to be used by the FileOpen
;  * dialogbox handler in order to truncate the current Directory path
;  * text when it exceeds the the window length.
;  * (SPR #28948)
;  * - Removed the StatusBar window class constants.
;  * 
;  *    Rev 1.39   11 Jan 1993 21:02:40   DARYL
;  * Build 32.
;  * 
;  *    Rev 1.38   05 Jan 1993 02:16:26   DARYL
;  * Build 31.
;  * 
;  * - Changed the name of the SetHelpKey service to SetHelpFkey and the
;  * name of the LHAPIBLOCK HelpKey field to HelpFkey.
;  * 
;  *    Rev 1.37   29 Dec 1992 01:54:16   DARYL
;  * Build 30.
;  * 
;  * - Removed the StatusBar class handler, due to lack of interest by the
;  * applications.  No known applications are currently using, or planning
;  * to use, this window type.
;  * - Added the SetHelpKey() service, to be used by any application in
;  * which the "Help" function-key is not <F1>.  The HelpKeycode field was
;  * added to the LHAPIBLOCK structure to hold the defined help key.
;  * 
;  *    Rev 1.36   21 Dec 1992 18:38:14   DARYL
;  * Build 29.
;  * 
;  * - Added the FILEOPEN_WILDCARDS_OK window style bit, to be used by the
;  * FileOpen dialogbox handler.  When this style is used, any <Enter>
;  * KEYSTROKE messages will be passed to the DialogBox class handler and
;  * not supressed if the "File name" edit buffer has been changed somehow
;  * (either directly by the user or via an update to another dialog
;  * control).
;  * 
;  *    Rev 1.35   15 Dec 1992 18:19:22   DARYL
;  * Build 28.
;  * 
;  * - Added support to the FileOpen dialogbox handler for the Filename
;  * edit window to be updated when the Files or Directory listbox is
;  * changed.  This required the addition of the CMD_PUSHB_ACTIVATE
;  * sub-message and to the PushButton handler so that it no longer traps
;  * thge <Enter> key (it's now the responsibility of the DialogBox
;  * handler to manage the activation of all pushbuttons).
;  * (SPR #27309, #29687)
;  * - Redefined the STATUS_NOT_EDITED bit constant to 0x04, the STATUS_INSERT
;  * bit to 0x01 and the STATUS_CURSORON bit to 0x02.
;  * 
;  *    Rev 1.34   08 Dec 1992 10:04:46   DARYL
;  * Build 27.
;  * 
;  * - Fixed a bug introduced in Build 26 with the wrong help screen being
;  * displayed when <F1> is pressed while a menu window is active.  This
;  * bug was caused by the menu window automatically being destroyed
;  * before the function-key is processed.
;  * - Added the DrawNChars service.
;  * - Redefined STYLE_NOSHADOW to 0x00004000L, MSG_CENTER_LINES to 0x0010L
;  * and DLG_PRESELECT to 0x0001L.
;  * 
;  *    Rev 1.33   08 Dec 1992 05:57:38   DARYL
;  * 
;  *    Rev 1.32   08 Dec 1992 05:55:40   DARYL
;  * Build 27.
;  * 
;  *    Rev 1.31   01 Dec 1992 05:53:22   DARYL
;  * Build 26.
;  * 
;  * - Added support to the Edit window handlers for the EDIT_NOCURSOR
;  * style.
;  * - Redefine the COMBO_ styles to account for the fact that a ComboBox
;  * is really a subclass of a single-line edit window.
;  * - Redefine the MSG_ styles to account for the fact that in some ways
;  * a MessageBox is a subclass of the multi-line edit window class.
;  * - Reassign the space in the LHAPIBLOCK structure previously used by
;  * the FontsUsed field to the DefaultFont field.
;  * 
;  *    Rev 1.30   24 Nov 1992 14:00:30   DARYL
;  * Build 25.
;  * 
;  * - Fixed a bug with the cursor from the LHAPI edit windows bleeding
;  * through into the menus.  The LOSEFOCUS_MENU sub-message was added in
;  * order to aid in the fixing of this bug.
;  * 
;  *    Rev 1.29   17 Nov 1992 00:04:12   DARYL
;  * Build 24.
;  * 
;  * - Removed the STATUS_FN_PRESS bit constant from LHAPI.H since this
;  * key will no longer be monitored by LHAPI.
;  * - Added the STATUS_CTRL_PRESS bit constant to LHAPI.H since this key
;  * will now be monitored by LHAPI.
;  * - Removed the DoTopMenu and MonitorAlt services.
;  * - Removed the DRAW_BOLD style.
;  * 
;  *    Rev 1.28   09 Nov 1992 21:39:36   DARYL
;  * Build 23.
;  * 
;  * - Added the DRAW_CLIENT_CHAR style for use by the LHAPI edit window
;  * classes.
;  * - Removed the DRAW_CLIENT_UPDATE and DRAW_CLIENT_CHAR bits from the
;  * DRAW_ALL style.
;  * - Add the SetCurrentFont(), GetCurrentFont(), SetRepRule() and
;  * ResetRepRule() services.
;  * - Reordered the DRAW_ sub-messages so that DRAW_CLIENT_CHAR is next
;  * to DRAW_CLIENT_UPDATE.
;  * 
;  *    Rev 1.27   30 Oct 1992 16:05:22   DARYL
;  * Build 22.
;  * 
;  *    Rev 1.26   26 Oct 1992 14:38:40   DARYL
;  * Build 21.
;  * 
;  *    Rev 1.25   19 Oct 1992 16:01:04   DARYL
;  * Build 20.
;  * 
;  *    Rev 1.24   16 Oct 1992 13:43:04   DARYL
;  * Build 19A.
;  * Checked-in source code after the server crash.
;  * This module contains changes from the official Build 19 version.
;  * 
;  *    Rev 1.23   12 Oct 1992 19:34:00   DARYL
;  * Build 19.
;  * 
;  * - Changed the SHADOW_W constant from 4 to 6 (pixels) to make the
;  * shadow on the right-side of rectangles wider.
;  * - Renamed the FILEOPEN_NODEFPUSHB style to FILEOPEN_NODEFAULT.  When
;  * this bit is set, the fileopen dialogbox handler will not set the
;  * position or the size of any of the fileopen dialog controls; it is
;  * the responsibility of the application to initialize them in this
;  * case.
;  * - Added the DRAW_TAB_TERM style, which will cause the DrawText()
;  * service to treat a "Tab" character (0x09) in a string the same as a
;  * null-termination character (0x00) -- as the end of the string.  All
;  * characters in the string up to the terminator will be displayed.
;  * 
;  *    Rev 1.22   05 Oct 1992 16:09:22   DARYL
;  * Build 18.
;  * 
;  * - Redefined the SETFOCUS_NOLOSE message value from 2 to 1.  Changed
;  * the SETFOCUS_SELECT to a tertiary-message (Extra parameter) from a
;  * sub-message (Data parameter).
;  * - Redefined the SETFOCUS_SELECT sub-message as a tertiary-message so
;  * that it be used in conjuction with any of the the sub-messages.
;  * 
;  *    Rev 1.21   28 Sep 1992 18:56:06   DARYL
;  * Build 17.
;  * 
;  *    Rev 1.20   21 Sep 1992 14:30:04   DARYL
;  * Build 16.
;  * 
;  *    Rev 1.19   14 Sep 1992 15:31:32   DARYL
;  * Build 15.
;  * 
;  * - Added the ResetVideo() service for HP.
;  * - Added the CMD_DIALOGFOCUS sub-message for dialogboxes.
;  * 
;  *    Rev 1.18   08 Sep 1992 13:10:14   DARYL
;  * Build 14.
;  * 
;  * - Added the DLG_PRESELECT style.
;  * 
;  *    Rev 1.17   31 Aug 1992 13:16:12   DARYL
;  * Build 13.
;  * 
;  * - Added support for the StatusBar window class.
;  * - Added both the TEXT_CENTER and TEXT_RIGHT StaticText window styles.
;  * 
;  *    Rev 1.16   31 Aug 1992 13:12:06   DARYL
;  * Build 13.
;  * 
;  *    Rev 1.15   24 Aug 1992 19:10:40   DARYL
;  * Build 12.
;  * 
;  *    Rev 1.14   17 Aug 1992 13:00:26   DARYL
;  * Build 11.
;  * 
;  *    Rev 1.13   10 Aug 1992 14:46:24   DARYL
;  * Build 10.
;  * 
;  * - Added the MenuFont field to the LHAPIBLOCK structure.
;  * - Added a Reserved field to the LHAPIBLOCK structure for use by
;  * HP's database engine.
;  * - Added the GetLHAPIBlockPtr() service, which returns a near pointer
;  * to the currently defined LHAPIBLOCK structure.
;  * 
;  *    Rev 1.12   03 Aug 1992 14:53:10   DARYL
;  * Build 9.
;  * 
;  * - Enclosed the "1" and "0" in the LHAPI.H TRUE and FALSE defines in
;  * order to make it compatible with DIP's use of Borland C.
;  * 
;  * - Added the STYLE_NO_PARENT_KEY Style that prevents Object from
;  * passing any unused keystrokes on to the window's parent.
;  * 
;  *    Rev 1.11   27 Jul 1992 14:17:04   DARYL
;  * Build 8.
;  * 
;  * - The Style field in the LHWINDOW structure was changed to a ULONG. 
;  * Reordered the STYLE_ bit definitions.  Moved the Font field in the
;  * LHWINDOW structure.
;  * 
;  *    Rev 1.10   20 Jul 1992 12:39:36   DARYL
;  * Build 7.
;  * 
;  * - Added the calling distance modifier constant "DISTANCE" to each
;  * LHAPI service to allow for mixed-model programming.  This constant
;  * definition is located in the LHAPI.H filer directly before the
;  * function prototypes.
;  * 
;  * - Added support for STYLE_COMBOLIST, which will be set by an
;  * application in the window structure corresponding to the listbox
;  * portion of a ComboBox.  This allows the listbox window structure to
;  * be allocated in the dialog box control field array because the
;  * DialogBox handler will not CREATE this window with all the other
;  * windows in the dialogbox control field array when they are
;  * automatically created.
;  * 
;  * - Implemented the GetError(), SetError(), ClearError,
;  * SetErrorHandler() and the GetErrorHandler() services.
;  * 
;  * - Added the GetLocalClipping() and the IntersectLocalClipping()
;  * services.
;  * 
;  *    Rev 1.9   13 Jul 1992 14:20:00   DARYL
;  * Build 6.
;  * Made DrawFkeys() a public service routine.
;  * 
;  *    Rev 1.8   06 Jul 1992 12:32:44   DARYL
;  * Build 5.
;  * Fixed bugs in Multi-line Edit and MessageBox windows.
;  * 
;  *    Rev 1.7   29 Jun 1992 11:57:46   DARYL
;  * Build 4.
;  * Made slight changes to be compatible with Microsoft C 7.0.
;  * Added support for Multi-line Edit and MessageBox windows.
;  * 
;  *    Rev 1.6   15 Jun 1992 14:28:42   DARYL
;  * "Build 3.  Checked in the wrong version last time"
;  * 
;  *    Rev 1.4   04 Jun 1992 11:37:46   DARYL
;  * "Build 2 - changes to be compatible with SysMgr's graphics routines"
;  * 
;  *    Rev 1.3   01 Jun 1992 13:27:18   DARYL
;  * Build 2.  Changes too many and varied for exact descriptions at this point.
;  * 
;  *    Rev 1.2   18 May 1992 10:55:06   DARYL
;  * Changed the Style field in the LHMENU structure from an UCHAR to an UINT.
;  * 
;  *    Rev 1.0   29 Apr 1992 17:01:54   DARYL
;  * Initial revision.
; **
; ****************************************************************************
; ***************************************************************************
; *****************************************************************************
; **
; **		Interface to LHAPI
; **
; *****************************************************************************
; ****************************************************************************
;  terminated at the end of this module.	
;  Pack all structures defined in this
; 								** module on a Byte boundary. 
; **************************************************************************
; ** General typdefs for easier definition
; ***************************************************************************
FALSE		EQU		000000000h
TRUE		EQU		000000001h
;  As defined in MSC 6.0.  NULL is only used
; 								** with pointers.  Set any other variable to
; 								** 0 in order to clear it. 
BOOL		TYPEDEF		SWORD

UCHAR		TYPEDEF		BYTE

UINT		TYPEDEF		WORD

ULONG		TYPEDEF		DWORD

;  Bit defintions for the Shift Status value returned by both the
; ** BIOS and the System Manager.  The LHAPI layer relies on these
; ** bit masks. 
LHSHIFTSTATUS		TYPEDEF		UINT

SHIFT_STATE		EQU		000000002h
CTRL_STATE		EQU		000000004h
ALT_STATE		EQU		000000008h
SCROLL_LOCK_STATE		EQU		000000010h
NUM_LOCK_STATE		EQU		000000020h
CAPS_LOCK_STATE		EQU		000000040h
INSERT_STATE		EQU		000000080h
; ----------------------------------------------------------------------------
; **** Data pointer definitions for each of the different data types used.
; **** These typedefs should be used in the LHAPI-compatible applications. ***
PLHDATA		TYPEDEF		NEAR PTR UCHAR

;  Pointer to near data in RAM 
PLHFARDATA		TYPEDEF		NEAR PTR FAR PTR UCHAR

;  Pointer to far data in RAM 
PLHRES		TYPEDEF		NEAR PTR FAR PTR UCHAR

;  Pointer to resourced string 
; --------------------------------------------------------------------------
; *** Function pointer definitions ***
; *************************************
@proto_0		TYPEDEF		PROTO FAR C 
LHFUNC		TYPEDEF		@proto_0

;  A menu or function key handler 
@proto_1		TYPEDEF		PROTO FAR C 
PLHFUNC		TYPEDEF		FAR PTR @proto_1

;  Pointer to a function 
@proto_2		TYPEDEF		PROTO FAR C :NEAR PTR LHsWindow, :UINT, :UINT, :UINT
LHCLASS		TYPEDEF		@proto_2

;  A window class handler 
; ***************************************************************************
; ** The following unused typedef is needed in order to work around a
; ** Microsoft acknowledged bug in version 1.00 of the H2INC utility.
; ***************************************************************************
@proto_3		TYPEDEF		PROTO C 
H2INCDummyFunc		TYPEDEF		@proto_3

@proto_4		TYPEDEF		PROTO FAR C :NEAR PTR LHsWindow, :WORD, :WORD, :WORD
PLHCLASS		TYPEDEF		FAR PTR @proto_4

;  Pointer to a window class handler 
; ***************************************************************************
; *****************************************************************************
; **
; **				FKEY - Function key structure
; **
; ** Function key sets are compressed, i.e. only the function keys that have
; ** definitions need be present.  The KeyNum field indicates which function
; ** key the definition is for.
; ** Valid numbers are: 1..12, FKEY_SHIFT+(1..12), FKEY_ALT+(1..12) and
; **					  FKEY_CTRL+(1..12).
; ** The last function key in the set should have FKEY_LAST added to it's
; ** function key number.
; **
; *****************************************************************************
; ****************************************************************************
;  Function key label (text string) 
;  Function key procedure or command handle 
;  Function key number (see below) 
;  Style
; 					 	**	 0 = execute procedure as usual
; 					 	**	 FKEY_SENDMSG = send COMMAND message to the
; 						**		window with the focus.
; 					 	**	 FKEY_CREATEWND = Handler is actually a pointer
; 					 	**	 	to a window structure -- automatically create
; 						**		and set the focus to the window (via a CREATE,
; 						**		CREATE_FOCUS, SETFOCUS_NORMAL message).
; 						**		Typically, the window is a DialogBox. 
LHsFKey		STRUCT 1t
Title		PLHRES		?
Handler		PLHFUNC		?
KeyNum		UCHAR		?
Style		UCHAR		?
LHsFKey		ENDS

LHFKEY		TYPEDEF		LHsFKey

PLHFKEYS		TYPEDEF		NEAR PTR LHFKEY

; 	Pointer to a function keys structure.  Can also used as a
; 	**	pointer to an array of LHFKEY structures (hence the 'S' at
; 	**	the end of the name), which defines all of the function keys
; 	**	for a particular window. 
; *** KeyNum field defintions.  These values are added to the
; ***** actual function key number (1-12). ***
FKEY_ALONE		EQU		000000000h
FKEY_CTRL		EQU		000000010h
FKEY_ALT		EQU		000000020h
FKEY_SHIFT		EQU		000000040h
FKEY_LAST		EQU		000000080h
; *** LHFKEY structure Style field definitions ***
FKEY_SENDMSG		EQU		000000001h
FKEY_CREATEWND		EQU		000000002h
; ***************************************************************************
; *****************************************************************************
; **
; **				MENU - CUA style menu structure.
; **
; ** An application menu is an array of MENU structs, where each struct 
; ** describes one menu item. The top menu and each popdown menu are seperate 
; ** arrays. Each array must end with a menu struct filled with 0.
; **
; ** Title: Displayed name of item.  Characters preceded by "&" specify
; **		  the menu item's mneumonic and appear underlined.
; **
; ** Handler: For pulldown menus, a near pointer to a menu structure.
; **			For menu actions (i.e. not pop-downs), either a near pointer
; **			to code associated with the menu item or an integer ID number.
; **			For window creations, a near pointer to a window structure.
; **			(See Style below).
; **
; ** HotKey: Scan code of key that will execute the function directly without
; **		   going through the menu.
; **
; ** Style: Style bits defined as follows:
; **   MENU_GRAY -- Menu item is "grayed", meaning cannot be selected.
; **   MENU_INVISIBLE -- Menu item doesn't display; Used to support different
; **   	menu choices embedded in the same menu structure.
; **   MENU_CHECKED -- Menu item displays with a checkmark before it.
; **   MENU_BARBEFORE -- A separator bar is inserted before the item.
; **   MENU_SENDMSG -- Instead of the Handler being directly called by the menu
; **      system, a COMMAND message is sent to the menu's parent window, with
; **      the Data parameter set to the LHMENU Handler field.  This allows the
; **      flexibility of placing code inside a switch, and lets a window handler
; **      manage menu options that may be modal in that window.
; **   MENU_PULLDOWN -- The menu is a pop-down menu; Handler points to the
; **	 	array of pop-down menu structures.
; **   MENU_CREATEWND -- Handler is a pointer to a window structure; this
; **      window is automatically created and given the focus
; **		(via a CREATE, CREATE_FOCUS, SETFOCUS_NORMAL message) when the
; **		corresponding menu item is selected.  This would typically be a
; **		DialogBox, but it does not have to be.
; **   MENU_ELLIPSIS -- Appends the "..." text string to the menu item when
; **		displayed to indicate a dialog is initiated by that menu item.
; **	 MENU_USER -- Values of the Style field at and after this value are
; **		reserved for application-specific uses.
; **
; ** Help: Context sensitive help index number for this menu item.
; **		 A value of NO_HELP means that this menu item does not have
; **		 any help text associated with it.
; **
; *****************************************************************************
; ****************************************************************************
LHsMenu		STRUCT 1t
Title		PLHRES		?
Handler		PLHFUNC		?
HotKey		UINT		?
Style		UINT		?
Help		UCHAR		?
LHsMenu		ENDS

LHMENU		TYPEDEF		LHsMenu

PLHMENU		TYPEDEF		NEAR PTR LHMENU

; 	Pointer to a LHMENU structure.  It can also be used as a
; 	**	pointer to an array of LHMENU structures which defines all
; 	**	of the items in a menu window. 
; *** MENU structure Style field definitions ***
MENU_USER		EQU		000000400h
MENU_GRAY		EQU		000000080h
MENU_INVISIBLE		EQU		000000040h
MENU_CHECKED		EQU		000000020h
MENU_BARBEFORE		EQU		000000010h
MENU_SENDMSG		EQU		000000008h
MENU_PULLDOWN		EQU		000000004h
MENU_CREATEWND		EQU		000000002h
MENU_ELLIPSIS		EQU		000000001h
; *** This value is saved in the Help field of the LHMENU and LHWINDOW
; ***** structure to signify that this menu item or window does not have
; ***** any specific help index associated with it. ***
; ***************************************************************************
; *****************************************************************************
; **
; **				LHWINDOW - Window Structure
; **
; ** The Window is the basic unit of interface construction; at any one time
; ** one window has focus and determines how keys are handled, and what menu 
; ** and function keys are available. Either by itself or with other windows
; ** it creates the display presented to the user.
; **
; ** The application defines each of its windows in a WINDOW struct. Most
; ** windows are completely defined before execution, but some are filled in
; ** on the fly by the LHAPI (e.g. menus and error messages). All windows, 
; ** whether filled in by application or LHAPI must be supplied by the 
; ** application; LHAPI does not allocate any memory for window creation.
; **
; ** Portions of the WINDOW structure are accessible from the application, 
; ** and parts should only be modified by LHAPI.
; **
; ** The fields of this structure are defined as follows:
; **
; **  Class: Either 1) A near pointer to the class handler code for the window,
; **             or 2) An int (>0FF80h) that is a handle into an internal
; **                   table of LHAPI provided classes.  See LHAPI provided base
; **                   classes below.
; **
; **  x,y: The screen position of the upper-left corner of the window.
; **		 If STYLE_XYRELATIVE (see below) is being used, then the signed
; **		 values in these fields specify the relative pixel offset from
; **		 the window's parent of the upper-left corner of the window.  In
; **		 this case, the Object class handler converts the relative
; **		 position of the window to the corresponding absolute position
; **		 when it receives an APPEAR message, storing the resulting value
; **		 in these same fields.  It then converts the position back
; **		 when it receives a DISAPPEAR message.  If STYLE_XYRELATIVE is
; **		 not being used, the x & y fields contain the absolute pixel
; **		 position of the start of the window.
; **
; **	w,h: The size of window area.  If STYLE_WHCHAR is being used, the
; **		 values in these fields specify the size, in terms of text
; **		 characters, of the client portion of the window only.  In
; **		 this case, each sub-class window handler is resposible for
; **		 converting the window text character size to pixel size when
; **		 it receives an APPEAR message, storing the resulting values in
; **		 these same fields.  Each handler must then convert the size
; **		 back again when it receives a DISAPPEAR message.  All of the
; **		 LHAPI-provided window classes automatically perform this service.
; **
; **  Title: Resource Pointer (a "far" ptr to a string) that "names" the
; **         field for the user.  Normally, this name will show on screen, but
; **         it is not required for all window types.
; **
; **  Data: Ptr to the data area that the window should modify.  The meaning and
; **        format of this data area is different for each window.
; **
; **  LogicalSize: The size of the data area for the window. The meaning of this
; **			 	 field varies.
; **
; **  Style: A word of bit flags.  Styles for a window should be ORed together.
; **		   Style consists of two parts: global styles that apply to all
; **		   windows and local styles that apply to a specific window class.
; **		   The global window styles:
; **			 STYLE_XYRELATIVE -- The window position specified in the
; **				 x and y fields is relative to the parent window.  If the
; **				 STATUS_XY_ABS bit in the window Status field is not set,
; **				 the Object class handler will convert the relative offset
; **				 to the corresponding absolute display coordinates when it
; **				 receives a CREATE message.
; **			 STYLE_WHCHAR -- The window size specified in the w and h fields
; **				 is specified in terms if text characters, not pixels.  In
; **				 addition the size specified only includes the client portion
; **				 of the window, not any window title or border.  The LHAPI
; **				 provided base class handlers, except the Object handler,
; **				 will convert the window character size to the corresponding
; **				 window pixel size when they receive a CREATE message.
; **           STYLE_NOBORDER -- The window will be displayed without a border.
; **			 STYLE_PUSHBUTTON -- Set for PushButtons so that the DialogBox
; **				 handler will correctly perform special pushbutton handling.
; **				 Note that the application is responsible for setting this
; **				 bit, as it will not be set by the PushButton handler.  The
; **				 reason for this is that the DialogBox handler looks at this
; **				 bit before the PushButton handler would get an opportunity to
; **				 set it.
; **           STYLE_RADIO -- Automatically set for RadioButton windows so that
; **               the DialogBox handler will correctly perform special handling
; **               for them.
; **           STYLE_CHECKBOX -- Automatically set for CheckBox windows so that
; **               the DialogBox handler will correctly perform special handling
; **               for them.
; **           STYLE_DATETIME -- Automatically set by the DateTime window
; **               handler so that the displayed date & time can be kept
; **               updated to the current system date & time.
; **           STYLE_COMBOLIST -- Set by the application in the window
; **               structure for the ListBox portion of a ComboBox.  This style
; **               signals to the DialogBox handler not to CREATE this window
; **               when it automatically creates all the others in the dialog
; **               box control field array.  The window is however, sent a
; **               DESTROY message when the dialog box itself is destroyed.
; **               This style should be used if the window structure for the
; **               listbox portion of a comboxbox is defined in the dialog
; **               control field array.
; **           STYLE_COMBOEDIT -- Automaticlly set by the ComboBox handler to
; **               signal that the combobox LHWINDOW structure is actually the
; **               window structure for the edit portion of the combobox.
; **           STYLE_GRAY -- Indicates that the window should be displayed as
; **               gray.  Used for dialog controls that should not be accessed.
; **           STYLE_LEAF -- For dialog controls or other terminal windows.
; **               Prevents DESTROY messages from cascading any further down
; **               the window chain to child windows, and causes the Menu
; **               field in this LHWINDOW structure to be ignored.
; **               NOTE: ONLY USE STYLE_LEAF WHEN SAFE.
; **                 Improper use of STYLE_LEAF can foul up the window chain.
; **                 The DialogBox handler automatically sets STYLE_LEAF in
; **                 any child windows, so it is not necessary to explicitly
; **                 employ it.
; **           STYLE_NOTIFY -- For a child window, tells the window to
; **               notify the parent when it changes state via
; **               NOTIFY_CHILDKILLED and NOTIFY_CHILDCHANGED messages.
; **           STYLE_NOFOCUS -- The window cannot receive the focus.
; **           STYLE_SAVEUNDER -- The window will save the background underneath
; **               and restore it upon termination.
; **           STYLE_INVISIBLE -- The window will not display itself.
; **           STYLE_PUSHB_WIDTH -- Set by an application if it wants the
; **               DialogBox handler to automatically calculate and set the
; **               width of each of the PushButtons in the dialogbox.  The
; **               pushbutton width will be calculated based on the longest
; **               label that will appear in any of the pushbuttons.  Note that
; **               this Style bit is to be set in the DialogBox window
; **               structure, not each of the PushButton window structure.
; **           STYLE_NO_PARENT_KEY -- Object will not send any unused keystrokes
; **               it receives to a window's Parent.  This bit is usually
; **               temporarily set by a window handler before it passes
; **               keystrokes on to Object in order to allow Object to check
; **               for menu or function keys, but not allow it to do anything
; **               else.
; **           STYLE_NOSHADOW -- For DialogBoxes and MessageBoxes, the window
; **               border will be drawn without a shadow around it.
; **
; **         Local window styles are explained where they appear.
; **
; **  Parent:	The window that "owns" this window.  The parent relationship is
; **			used to:
; **				1) send messages that are not understood back through the
; **				   chain of windows.
; **				2) to stack menus and function keys.
; **				3) to provide levels of windows that can be acted upon all at
; **				   once (e.g. by destroying a parent window, all its children
; **				   are destroyed).
; **
; **  Fkey: Either a pointer to a FKEYS structure that defines the active
; **		  function keys if this window gets the focus, PARENT_FKEYS,
; **		  or NO_FKEYS.  PARENT_FKEYS means "look to my parent window for
; **		  function-key definitions", and NO_FKEYS means that no function-keys
; **		  are supplied.
; **
; **  Menu: Either a pointer to the array of MENU structures which will be
; **		  activated by pressing the MENU key, PARENT_MENU, or NO_MENU.
; **		  PARENT_MENU means "look at my parent for a menu", and NO_MENU
; **		  means disables the menu.
; **		  NOTE: For dialog controls (or any other windows with the
; **		  STYLE_LEAF bit set) the Menu field is ignored, and the parent's
; **		  is looked at automatically.
; **
; **  Help: Help screen number, used to show context sensitive help.
; **		  A value of NO_HELP means that this window does not have
; **		  any help text associated with it.
; **
; **  Status: Byte for window status.  Used by Edit control for insert/overwrite,
; **			and first key flag and reserved for other windows.
; **
; **  Selection: The current cursor selection.  This means different things
; **			   in different windows.  For edit windows, it is the cursor
; **			   position, for list/combo boxes, it is the current line, etc.
; **
; **  WindowTop: The top of the area being displayed.  For single-line scrolling
; **			   edit windows, it is the first character to show in the window.
; **			   For multi-line edit windows, it is the first line to show in
; **			   the box.  For list boxes, it is the first string showing at the
; **			   top of the box, etc.
; **
; **  Font: Bitmapped ID of the default font type for this window.  This
; **		  is the font type which LHAPI will use for all of the drawing
; **		  which it does within this window.  The possible values are:
; **		  FONT_DEFAULT -- Use the whatever the currently selected default
; **			 font is (as specified by a prior call to SetDefaultFont) when
; **			 the window is DRAWn.  This use of FONT_DEFAULT does not hold
; **			 true for the TitleBar window class, which will always use
; **			 FONT_SMALL, unless a particular font type is specified in the
; **			 titlebar window structure.
; **		  FONT_PARENT -- Use the same font the window's Parent is using.
; **		  FONT_SMALL, FONT_NORMAL, FONT_LARGE  --  Use the specified font.
; **
; **  NextWnd,PrevWnd: Internally maintained pointers to the next/prev window
; **					 in the window list.  This is used by the LHAPI to
; **					 traverse the list.
; **
; *****************************************************************************
; ****************************************************************************
; *** "External" information provided by application ***
@t_0		TYPEDEF		NEAR PTR LHsWindow
; *** "Internal" information filled in and managed by LHAPI ***
@t_1		TYPEDEF		NEAR PTR LHsWindow
@t_2		TYPEDEF		NEAR PTR LHsWindow
LHsWindow		STRUCT 1t
Class		PLHCLASS		?
x		SWORD		?
y		SWORD		?
w		SWORD		?
h		SWORD		?
Title		PLHRES		?
Data		PLHDATA		?
LogicalSize		UINT		?
Style		ULONG		?
Parent		@t_0		?
Fkey		PLHFKEYS		?
Menu		PLHMENU		?
Help		UCHAR		?
Status		UCHAR		?
Selection		UINT		?
WindowTop		UINT		?
Font		UINT		?
NextWnd		@t_1		?
PrevWnd		@t_2		?
LHsWindow		ENDS

LHWINDOW		TYPEDEF		LHsWindow

PLHWINDOW		TYPEDEF		NEAR PTR LHWINDOW

;  Near pointer to a window structure 
; *******************************************************
; ** Special Menu and Fkey pointer values
; ********************************************************
NO_FKEYS		EQU		0ffffffffh
NO_MENU		EQU		0ffffffffh
; **********************************************************
; ** Styles -- Global (handled by the Object Class Handler)
; ***********************************************************
STYLE_NOSHADOW		EQU		000004000h
STYLE_COMBOEDIT		EQU		000008000h
STYLE_DATETIME		EQU		000010000h
STYLE_CHECKBOX		EQU		000020000h
STYLE_NO_PARENT_KEY		EQU		000040000h
STYLE_PUSHB_WIDTH		EQU		000080000h
STYLE_PUSHBUTTON		EQU		000100000h
STYLE_COMBOLIST		EQU		000200000h
STYLE_RADIO		EQU		000400000h
STYLE_GRAY		EQU		000800000h
STYLE_XYRELATIVE		EQU		001000000h
STYLE_WHCHAR		EQU		002000000h
STYLE_NOBORDER		EQU		004000000h
STYLE_LEAF		EQU		008000000h
STYLE_NOTIFY		EQU		010000000h
STYLE_NOFOCUS		EQU		020000000h
STYLE_SAVEUNDER		EQU		040000000h
STYLE_INVISIBLE		EQU		080000000h
; **********************************************************
; ** Styles -- Local (defined for each window separately)
; ***********************************************************
; **************************************************************************
; **** DRAW styles -- Used by DrawText and StaticText windows				***
;  Show the text normally, black on white,
; 								** without any special formatting. 
DRAW_NORMAL		EQU		0t
;  Show the text as white on black 
DRAW_INVERSE		EQU		000000001h
;  Underline the whole string 
DRAW_UNDERLINE		EQU		000000002h
;  Gray the whole string 
DRAW_GRAY		EQU		000000004h
;  Interpret & as "Underline next char" 
DRAW_AMPERSAND		EQU		000000010h
;  The <Tab> character (0x09) is considered
; 								** a string-terminator.  Like the
; 								** null-termination character (0x00), all
; 								** characters up to it are displayed. 
DRAW_TAB_TERM		EQU		000000020h
; **************************************************************************
; **** TEXT styles -- Used by StaticText dialog control					****
; **** Note that StaticText also uses the DRAW_x styles					***
;  Center dynamic text in window region 
TEXT_CENTER		EQU		000000040h
;  Right-justify dynamic text in window 
TEXT_RIGHT		EQU		000000080h
; **************************************************************************
; **** RECT styles -- Used by StaticRect (rectangle) dialog control		***
;  Displayed with a shadow 
RECT_SHADOW		EQU		000000001h
; **************************************************************************
; **** EDIT styles -- Used by the Edit controls							***
;  Initial state of edit is text "overtype". 
EDIT_OVERWRITE		EQU		000000000h
;  Initial state of edit is "insert" mode. 
EDIT_INSERT		EQU		000000001h
;  Never display the cursor. 
EDIT_NOCURSOR		EQU		000000002h
;  The edit window contains multiple lines. 
EDIT_MULTI		EQU		000000004h
;  The multi-line edit text wrap will be
;                                 ** disabled. 
EDIT_NOWRAP		EQU		000000008h
; **************************************************************************
; **** COMBO styles -- Used by the ComboBox control						****
; ****	Note: These style bits MUST begin after the EDIT_ styles due to	****
; ****	the fact that the combobox is a subclass of the edit class.		***
;  The default combo box style 
COMBO_EDIT		EQU		000000000h
;  Drop-down list; no editing 
COMBO_NOEDIT		EQU		000000010h
;  Auto drops upon receiving focus 
COMBO_AUTODROP		EQU		000000020h
; **************************************************************************
; **** MESSAGEBOX styles													****
; ****	Note: These style bits MUST begin after the EDIT_ styles due to	****
; ****	the fact that in some ways the MessageBox is a subclass of the	****
; ****	multi-line edit class.											***
MSG_NOSHADOW		EQU		000004000h
;  Center each of the lines in the
; 										** MessageBox window. 
MSG_CENTER_LINES		EQU		000000010h
; **************************************************************************
; **** PushButton styles -- Used by PushButon control to determine what to do
; ****                      when the pushbutton is "pressed". 
;  Send a COMMAND Message to the pushbutton
;                                 ** window's parent. 
PUSHB_SENDMSG		EQU		000000001h
;  CREATE and give the focus to the specified
;                                 ** window (via a CREATE, CREATE_FOCUS,
;                                 ** SETFOCUS_NORMAL message).
; 
; 	/* NOTE: If neither of these styles is selected, the specified routine
; 	**       will be directly called when the pushbutton is "pressed". 
PUSHB_CREATEWND		EQU		000000002h
; **************************************************************************
; **** DIALOGBOX styles													***
DLG_NOSHADOW		EQU		000004000h
;  The DialogBox class handler will NOT clear
; 								** the selection field during the CREATE
; 								** message processing.  It is the
; 								** responsibility of the application to set
; 								** the selection to the proper control prior
; 								** to issuing a CREATE_FOCUS message. 
DLG_PRESELECT		EQU		000000001h
; **************************************************************************
; **** FILEOPEN DIALOGBOX styles											***
FILEOPEN_NODEFAULT		EQU		000000004h
;  The LHAPI FileOpen dialogbox handler does not initialize any of the
; 		** fields the dialog control windows.  It is the responsibility of the
; 		** application to properly define these values. 
FILEOPEN_WILDCARDS_OK		EQU		000000008h
;  The LHAPI FileOpen dialogbox handler will pass any <Enter>
; 		** KEYSTROKE messages on to the DialogBox class handler instead of
; 		** suppressing them if the "File name" edit data has not been updated
; 		** (either directly by the user or via an update to another dialog
; 		** control).  This style is to be used by applications in which file
; 		** specifications that contain wildcards are acceptable to it. 
; **************************************************************************
; **** Main application TITLEBAR styles									***
;  Don't display the current system
; 										** date and time. 
TITLE_NODATETIME		EQU		000000001h
; **************************************************************************
; **** DATE/TIME styles
; **** These styles are only valid for the DateTime window class, not the
; **** DateEdit nor TimeEdit window classes.
; **** If no style is specified, the default style of SHOW_DATETIME is
; **** used so that both the current system date and time are displayed
; **** and updated in the window. ***
;  Display both date & time 
;  Show the text as white on black 
DATETIME_INVERSE		EQU		000000001h
;  Display current date only 
DATETIME_DATE		EQU		000000002h
;  Display current time only 
DATETIME_TIME		EQU		000000004h
;  Right-justify date/time string 
DATETIME_RIGHT		EQU		000000008h
; **************************************************************************
; **** ProgressMeter styles												***
;  Don't write the number representing
; 										** the percent completed (which is
; 										** drawn inside the progress meter). 
PROGRESS_NOPERCENT		EQU		000000001h
; **************************************************************************
; ** Status bits -- Global bits for window's Status field.
; ** Application-defined window handlers may use the rest of the status bits
; ** for their own use.
; ***************************************************************************
;  Set when the window is currently being
; 									** displayed on the screen. 
STATUS_VISIBLE		EQU		000000080h
;  Set when the display image underneath
; 									** the window was saved in an internal
; 									** LHAPI buffer. 
STATUS_SAVEUNDER		EQU		000000040h
;  Set when the x and y fields are
; 									** converted from a relative offset from
; 									** the parent window to the corresponding
; 									** absolute display coordinates (when
; 									** STYLE_XYRELATIVE is being used). 
STATUS_XY_ABS		EQU		000000020h
;  Set when the w and h fields are
; 									** converted from text-character based to
; 									** pixel based (when STYLE_WHCHAR is
; 									** being used). 
STATUS_WH_PIXEL		EQU		000000010h
;  Set by the Object class handler before
; 									** issuing a SETFOCUS message as part of
; 									** the CREATE_FOCUS message processing.
; 									** This is used by window handlers that
; 									** need to differentiate this case from
; 									** the other times it can receive a
; 									** SETFOCUS message. 
STATUS_INCREATE		EQU		000000008h
;  If set, data has yet to be edited.
; 									** Cleared each time the edit window is
; 									** used in some way. 
STATUS_NOT_EDITED		EQU		000000004h
; **************************************************************************
; **** Edit Status bits -- Used by the Edit window class handler
; **** (these aren't considered to be global status bits). ***
;  Set when in edit insert mode,
; 									** cleared when in overtype mode. 
STATUS_INSERT		EQU		000000001h
;  Set when cursor is currently visible. 
STATUS_CURSORON		EQU		000000002h
; **************************************************************************
; **** PushButton status bits ***
STATUS_DEF_PUSHB		EQU		000000001h
; ** If set, the PushButton window is considered to be the "default"
; 	**** pushbutton (i.e. <ENTER> will activate it).  This bits is managed by
; 	**** the DialogBox handler and is checked by the pushbutton handler. **
; **********************************************************
; ** Font type IDs (also used by the DrawText service).
; ** The high byte of Font is the width of the font in
; ** pixels while the low byte is the height of the font.
; ***********************************************************
FONT_DEFAULT		EQU		0t
FONT_PARENT		EQU		1t
FONT_SMALL_W		EQU		8t
FONT_SMALL_H		EQU		8t
FONT_SMALL		EQU		000000808h
FONT_NORMAL_W		EQU		10t
FONT_NORMAL_H		EQU		11t
FONT_NORMAL		EQU		000000a0bh
FONT_LARGE_W		EQU		16t
FONT_LARGE_H		EQU		12t
FONT_LARGE		EQU		00000100ch
; ***************************************************************************
; *****************************************************************************
; **
; **			LHEDITDATA - Multi-line edit window Data field structure
; **
; ** This structure contains the definition of the LHWINDOW Data field for a
; ** Multi-line Edit window.  This structure is needed because the standard
; ** LHWINDOW structure is not sufficient for use by the LHAPI-provided
; ** multi-line edit class handler.  All the fields specified in the LHWINDOW
; ** structure are still valid and used in a multi-line edit window.
; **
; ** The fields of this structure are defined as follows:
; ** ----------------------------------------------------
; **		Buffer: Pointer to the text data buffer, in RAM, which will
; **			actually be edited.
; **
; **		Buffer: Pointer to the data buffer in which a copy of the original
; **			edit text will be saved when the user begins editing it, and from
; **			which it will be restored when the user presses the <ESC> key.
; **			If this pointer is set to NULL, the original edit text will not
; **			be saved anywhere by LHAPI, and thus it also cannot be restored
; **			by it.
; **
; **		LineStarts: Indirect pointer to the array which will hold the offset
; **			into the edit text buffer of the start of each of the lines in the
; **			buffer.  If all of the available entries in this array are used,
; **			the user will be unable to enter any data past the end of the last
; **			line.  An entry in this array is used for each line, regardless of
; **			whether or not that line is currently visible on the screen (the
; **			multi-line edit buffer can contain more data than is visible at
; **			any one time with the edit window being scrollable up and down).
; **			These fields are initialized and maintained by the LHAPI
; **			multi-line edit handler.
; **
; **		MaxLines: Maximum number of lines in the entire edit buffer.  This
; **			number differs from the number of lines which is seen in the
; **			edit window at any one time.  This field is also the total size,
; **			in entries, of the LineStarts array.
; **
; **		WrapLen: The number of text characters to word wrap each line in
; **			the multi-line edit window at.  If this field is initialized
; **			to 0 by an application before a CREATE message is issued,
; **			LHAPI will automatically adjust it to the total width of the
; **			multi-line edit window box.  The word wrap can be changed on the
; **			fly by an application by first updating this field to the desired
; **			value and then issuing a NOTIFY,NOTIFY_UPDATE message to
; **			the multi-line edit window handler.
; **
; **		CurrentLine, CurrentCol: The line and column, relative to the start
; **			of the edit data text, the cursor is currently on.  A line,column
; **			of 0,0 signifies that the cursor is currently on the first
; **			character in the edit data buffer.  These fields are initialized
; **			and maintained by the LHAPI multi-line edit handler.
; **
; **		NumLines: Number of lines of data currently in the edit buffer.
; **			This field has a value in the range of 1 to MaxLines and is
; **			initialized and maintained by the LHAPI multi-line edit handler.
; **
; **		TextLen: Length, in characters, of the text string being edited, not
; **			inluding the null-termination character at the end the edit text
; **			string.  This thus also represents the character offset into the
; **			edit buffer of the null-terminator.  This field is initialized
; **			and maintained by the LHAPI multi-line edit handler.
; **
; *****************************************************************************
; ****************************************************************************
@t_3		TYPEDEF		NEAR PTR FAR PTR UINT
LHsEditData		STRUCT 1t
Buffer		PLHFARDATA		?
SaveBuffer		PLHFARDATA		?
LineStarts		@t_3		?
MaxLines		UINT		?
WrapLen		UINT		?
CurrentCol		UINT		?
CurrentLine		UINT		?
NumLines		UINT		?
TextLen		UINT		?
LHsEditData		ENDS

LHEDITDATA		TYPEDEF		LHsEditData

PLHEDITDATA		TYPEDEF		NEAR PTR LHEDITDATA

;  Near pointer to a LHsEditData structure 
; ***************************************************************************
; *****************************************************************************
; **
; **				LHAPIBLOCK - Application Window Management Struct
; **
; ** Each application must define one LHAPIBLOCK with which LHAPI keeps track of
; ** that application's windowing.  The LHAPI is notified of the
; ** block's location during application initialization, and after context
; ** switching back to the application.
; **
; ** The application itself should not modify or peek into the structure of
; ** the LHAPIBLOCK, as the LHAPIBLOCK structure is subject to change.
; ** If the application needs info (such as who has focus) it should get it
; ** through calls to LHAPI functions (such as GetFocus()).
; **
; ** The fields in this structure are:
; **
; ** FirstWnd: The first window in the LHAPI window list.  The LHAPI can
; **			 traverse all windows by starting at FirstWnd, and following
; **			 the window's NextWnd pointer.  If a window's NextWnd pointer is
; **			 NULL, the end of the list has been reached.
; **
; ** LastWnd:	The last window in the window list.  If windows are added
; **			to the screen, they are chained on to this LastWnd.
; **
; ** FocusWnd: The window that has focus--i.e. will get user keystrokes.
; **
; ** BeginHighlight: Pointer to the begin of the highlighted (user selected)
; **				   area to be cut/copied/pasted over/deleted.  This may mean
; **				   different things to different window classes, but it is
; **				   reset by LHAPI each time a different window receives the
; **				   focus.  For edit windows, this is the offset into the edit
; **				   data buffer of the first text character which is
; **				   highlighted.
; **
; ** EndHighlight: Similar to BeginHighlight, but indicates end of highlight.
; **				 For edit windows, this is the offset into the edit data
; **				 buffer of the character immediately following the last
; **				 text character which is highlighted.  Thus, the number of
; **				 characters highlighted is (EndHighLight - BeginHighlight),
; **				 with nothing highlighted if (EndHighLight = BeginHighlight).
; **
; ** Status: Not used at this time.
; **
; ** UndoBuffer: Buffer for one-level undo of edit text.  A default
; **			   UndoBuffer is allocated by LHAPI.  An application
; **			   can define a larger buffer by allocating one itself
; **			   and passing it to the SetUndoBuffer service.
; **
; ** FkeyPtr: Pointer to current FKey structure so that the LHAPI can
; **			determine whether or not to redisplay the function keys.
; **
; ** ScreenSave: Far pointer to screen stack area--gets set by InitializeLHAPI.
; **			   The Screen Stack is used by Object to save the contents of
; **			   the screen underneath windows that employ STYLE_SAVEUNDER.
; **			   This buffer is allocated by LHAPI itself.  Once this pointer
; **			   is initialized, it is never changed.
; **
; ** ScreenSaveStart: Offset into the ScreenSave buffer of the next available
; **					memory.  It is used by Object to maintain the screen
; **					stack for windows that employ STYLE_SAVEUNDER.  This
; **					index is updated every time a screen are is saved or
; **					restored.
; **
; ** ScreenSaveEnd: Total size, in bytes, of the ScreenSave buffer.  It is
; **				  used by Object to maintain the screen stack for windows
; **				  that employ STYLE_SAVEUNDER.  Once this index is set
; **				  by InitializeLHAPI, it is never changed.
; **
; ** ErrorNum: Error number with which to create error window.
; **
; ** ErrorHandler: Routine to be executed by Error functions.
; **
; ** TopMenuWnd: Window structure for top level menu window - gets
; **			   automatically filled in when menu key is intercepted.
; **
; ** PopMenuWnd: Window structure for popdown menu window - filled in by the
; **			   menu window class handler when traversing the menus.
; **
; ** CurrentDialog: PLHWINDOW pointing to the current dialog if one is
; **				  created.
; **
; ** DefaultFont: ID of the currently defined "default" application font to be
; **				used in windows that specify a font type of FONT_DEFAULT.
; **				This field is set by the SetDefaultFont service.
; **
; ** HelpFkey: Keycode of the application-defined "Help" function-key sequence.
; **           This field is used internally by LHAPI and is set via the
; **           SetHelpFKey service.
; **          If an application does not explicitly set the help key, the
; **          default of <F1> is used.
; **
; *****************************************************************************
; ****************************************************************************
@t_4		TYPEDEF		FAR PTR UCHAR
LHAPIsBlock		STRUCT 1t
FirstWnd		PLHWINDOW		?
LastWnd		PLHWINDOW		?
FocusWnd		PLHWINDOW		?
BeginHighlight		UINT		?
EndHighlight		UINT		?
Status		UINT		?
UndoBuffer		UCHAR		128t DUP (?)
FkeyPtr		PLHFKEYS		?
ScreenSave		@t_4		?
ScreenSaveStart		UINT		?
ScreenSaveEnd		UINT		?
ErrorNum		SWORD		?
ErrorHandler		PLHFUNC		?
MenuFont		UINT		?
DefaultFont		UINT		?
HelpFkey		UINT		?
CurrentDialog		PLHWINDOW		?
TopMenuWnd		LHWINDOW		<>
PopMenuWnd1		LHWINDOW		<>
PopMenuWnd2		LHWINDOW		<>
Reserved		UINT		?
LHAPIsBlock		ENDS

LHAPIBLOCK		TYPEDEF		LHAPIsBlock

PLHAPIBLOCK		TYPEDEF		NEAR PTR LHAPIBLOCK

;  Pointer to a LHAPIBLOCK structure 
; *** LHAPIBLOCK Status field bit defintions ***
STATUS_ALT_MENU		EQU		000000001h
;  If set, the next <Alt> key release will cause the top menubar to be
; 	** activated.  If clear, the next <Alt> release will be ignored. 
STATUS_ALT_PRESS		EQU		000000002h
;  Flag for last shift state of the <Alt> key: 0=Up, 1=Pressed.
; 	** This bit is set when the <Alt> key is pressed (make) and cleared when
; 	** the <Alt> key is released (break). 
STATUS_SHIFT_PRESS		EQU		000000004h
;  Flag for last shift state of the <Shift> key: 0=Up, 1=Pressed.
; 	** This bit is set when a <Shift> key is pressed (make) and cleared when
; 	** a <Shift> key is released (break).  Note that these values are set
; 	** according to what the BIOS tells us.  If the BIOS implements a "sticky"
; 	** key, we do not actually realize that the key has been released until
; 	** the next key has been struck and the BIOS tells us then that the prior
; 	** keys has been released. 
STATUS_CTRL_PRESS		EQU		000000008h
;  Flag for last shift state of the <Ctrl> key: 0=Up, 1=Pressed.
; 	** This bit is set when the <Ctrl> key is pressed (make) and cleared when
; 	** the <Ctrl> key is released (break). 
STATUS_CAPSLOCK		EQU		000000010h
;  Flag for the current state of <CapsLock>: 0=Off, 1=On.
; 	** This bit is set when the CapsLock state toggles on, and cleared when
; 	** the CapsLock state toggles off. 
STATUS_SCROLLLOCK		EQU		000000020h
;  Flag for the current state of <ScrollLock>: 0=Off, 1=On.
; 	** This bit is set when the ScrollLock state toggles on, and cleared when
; 	** the ScrollLock state toggles off. 
STATUS_KEYPAD_PRESS		EQU		000000040h
;  Flag which is set when the user presses an <Alt-UpArrow> or an
; 	** <Alt-DownArrow> keystroke in a ComboBox.  The subsequent <Alt-Keypad>
; 	** hex character code which will be generated by the BIOS will then be
; 	** ignored. 
STATUS_EDIT_UNDO		EQU		000000080h
;  Flag which signals whether or not the edit text has been modified
; 	** since the edit window received the focus (1=modified; 0=unchanged).
; 	** If this bit is set, the next <Esc> key press will cause the original
; 	** copy of the edit text to be restored from the save buffer. 
STATUS_SUBMENUS		EQU		000008000h
;  Set when the sub-menus below the top menubar items are displayed while
; 	** the user navigates through the top menubar items.  This is needed when
; 	** the menubar item selection is moved from an item that has a sub-menu
; 	** to one that doesn't.  In this case, the appropriate sub-menu will
; 	** automatically be activated by LHAPI when the top menubar selection
; 	** returns to an item that has a sub-menu. 
; ***************************************************************************
; *****************************************************************************
; **
; **				LHAPI Provided Base Classes
; **
; ** These classes are used as handlers for windows having standard behaviours.
; ** They can also be subclassed if they are partly suited to a given task.
; **
; **	To use a built-in base class, use one of the following values in the
; **	Class field in the LHWINDOW structure.  LHAPI distiguises between
; **	the ID of base classes and window handler addresses by the value of this
; **	field.  If it is above 0xFF80, a base class is being used, but if the
; **	value is below 0xFF80, the Class field specifies the near address
; **	(within the application's default code segment) of the handler to be
; **	used with the window.
; **
; *****************************************************************************
; ****************************************************************************
; *** Object is the mother of all other window classes.
; ***** All other window classes are subclasses of the this class ***
Object		EQU		000000000h
; *** Dialog control window classes ***
Edit		EQU		000000001h
RadioButton		EQU		000000002h
ListBox		EQU		000000003h
ComboBox		EQU		000000004h
CheckBox		EQU		000000005h
StaticText		EQU		000000006h
GroupBox		EQU		000000007h
StaticRect		EQU		000000008h
PushButton		EQU		000000009h
; *** Menu window classes ***
MenuBar		EQU		00000000ah
MenuPopdown		EQU		00000000bh
; *** Specialized control window sub-classes ***
DateEdit		EQU		00000000ch
TimeEdit		EQU		00000000dh
DirListBox		EQU		00000000eh
FileListBox		EQU		00000000fh
PathText		EQU		000000010h
; *** High level window classes ***
DialogBox		EQU		000000011h
MessageBox		EQU		000000012h
MultiEdit		EQU		000000013h
FileOpenDialogBox		EQU		000000014h
; *** Miscellaneous window classes ***
TitleBar		EQU		000000015h
ProgressMeter		EQU		000000016h
DateTime		EQU		000000017h
; *** IDs of the first and last LHAPI-provided base window classes.
; ***** NOTE: These need to be updated each time a base class is added
; ***** or deleted. ***
FIRST_CLASS		EQU		0t
LAST_CLASS		EQU		23t
; ***************************************************************************
; *****************************************************************************
; **
; **				Messages.
; **
; ** The messages are the way for the program to communicate with the various
; ** classes of window.  Window classes in the LHAPI and in the application are
; ** treated the same.  All windows do not respond to all messages, but those
; ** messages that are not going to be acknowledged should be passed on to
; ** the parent class.
; **
; ** Note that although not all messages have a meaningful return value,
; ** return values are provided for windows to give feedback to the caller.
; ** This happens for DESTROY, LOSEFOCUS, and other messages that the window
; ** may wish to reply to; these two messages allow a FALSE return value to
; ** abort the process.  The return value TRUE is used for most messages.
; **
; ** Messages have optional components Data and Extra that are needed in
; ** some cases to give specifics about the type/meaning of the sent message.
; ** This would be a key char for KEYSTROKE, a command number for COMMAND, etc.
; **
; ** The messages are:
; **
; **		KEYSTROKE:	Sent to the focus window when a key is pressed.
; **		DRAW:		A message for the window to redraw itself.  The Data field
; **					is set to an bit mask indicating the requested draw area.
; **					See the DRAW_ submessages below.
; **		CREATE:		To create a window, a CREATE message is sent to that window.
; **		DESTROY:	Likewise to destroy a window.
; **		TERMINATE:	Sent to all windows when the application is terminated.
; **		ACTIVATE:	Sent to all windows when returning from a context switch.
; **		DEACTIVATE:	Sent to all windows when the app is being switched away.
; **		SETFOCUS: 	Sent to the window that is going to get the focus.
; **					The message's Data field can be set to SETFOCUS_SELECT to
; **					force the window to respond with an implicit selection
; **					(i.e. "check" itself).
; **		LOSEFOCUS:	Sent to the window about to lose the focus.  This is
; **					automatically done by the system when another window
; **					receives a SETFOCUS message.
; **		NULL:		Sent for E_NONE or "NULL" messages.  The type of
; **					E_NONE event is specified in the Data field--see NULL_
; **					submessages below.
; **		NOTIFY:		Used to notify either the child or parent window.
; **					The Data field is set to the submessage; for details
; **					see NOTIFY_	messages below.
; **		COMMAND:	Sent to a window that does not register a menu or function
; **					key handler, and uses the FKEY/MENU_SENDCOMMAND style bit.
; **		APPEAR:		Sent to a window to make it visible.
; **		DISAPPEAR:	Send to a window to make it invisible.
; **
; *****************************************************************************
; ****************************************************************************
KEYSTROKE		EQU		0t
DRAW		EQU		1t
CREATE		EQU		2t
DESTROY		EQU		3t
TERMINATE		EQU		4t
ACTIVATE		EQU		5t
DEACTIVATE		EQU		6t
SETFOCUS		EQU		7t
LOSEFOCUS		EQU		8t
NULLEVENT		EQU		9t
NOTIFY		EQU		10t
COMMAND		EQU		11t
APPEAR		EQU		12t
DISAPPEAR		EQU		13t
; ***************************************************************************
; ** SUBMESSAGES:
; **		All submessages are passed to window handlers via the Data paramater.
; ****************************************************************************
; ***************************************************************************
; **	CREATE submesssages
; **		CREATE_NORMAL: The window is created normally, i.e. it is is not
; **			sent a SETFOCUS message by the Object class handler.
; **		CREATE_FOCUS: The Object handler will automatically send a SETFOCUS
; **			message to the window after it is created.  If the 
; **			tertiary-message (the Extra parameter of the window handler
; **			inputs) is not SETFOCUS_NOLOSE, then the previous focus window
; **			will be sent a LOSEFOCUS message BEFORE the new window is sent
; **			the APPEAR message.  This is to allow, for instance, the
; **			previous focus window to redraw part of it's window area in
; **			order to show that it no longer has the focus before the new
; **			window is drawn, thereby preventing the possibility that part
; **			of the new window will be overwritten by the previous focus
; **			window.  The possible values for the Extra parameter of the
; **			CREATE message are the same as the SETFOCUS sub-messages (see
; **			the SETFOCUS sub-messages description for more information about
; **			these sub-messages).
; ****************************************************************************
CREATE_NORMAL		EQU		0t
CREATE_FOCUS		EQU		1t
; ***************************************************************************
; **	DESTROY submessages
; **		DESTROY_NORMAL: The window is destroyed normally in that the
; **			Object class handler will cause all the other windows
; **			currently visible to be redrawn if this window does not
; **			employ STYLE_SAVEUNDER.  It accomplishes this by sending
; **			a DISAPPEAR_NORMAL message to this window's handler.
; **		DESTROY_NODRAW: The Object class handler will send a
; **			DISAPPEAR_NODRAW message to the window in order to
; **			prevent all the other visible windows from being redrawn
; **			(if STYLE_SAVEUNDER is not being used).  This is useful
; **			when a parent window (like a dialog box) is destroyed, in
; **			which case we want to prevent all of it's child windows
; **			from causing all the other visible windows from being
; **			redrawn when each of them are destroyed.
; ****************************************************************************
DESTROY_NORMAL		EQU		0t
DESTROY_NODRAW		EQU		1t
; ***************************************************************************
; **	DISAPPEAR submessages
; **		DISAPPEAR_NORMAL: If the window is not employing the
; **			STYTLE_SAVEUNDER style, the Object class handler will
; **			send a DRAW_ALL message to all the other active, visible
; **			windows in order to remove this window from the screen.
; **		DISAPPEAR_NODRAW: If the window is not employing the
; **			STYTLE_SAVEUNDER style, the Object class handler will NOT
; **			send a DRAW_ALL message to all the other active, visible
; **			windows.  This is useful when each of the children of a
; **			parent window are sent a DISAPPEAR message.
; ****************************************************************************
DISAPPEAR_NORMAL		EQU		0t
DISAPPEAR_NODRAW		EQU		1t
; ***************************************************************************
; **	NOTIFY submessages (passed in Data)
; **		NOTIFY_CHILDKILLED: Sent to a parent window when a child is killed if
; **			it needs to report something in particular.  Note that the Window
; **			parameter which the parent window's handler receives actually
; **			points to the child window that was destroyed.
; **		NOTIFY_UPDATE: Sent to a window handler by an application to tell the
; **			window to notice a change in it's data.  This forces the handler
; **			to reinitialize any pertinent variables and redraw itself.
; **		NOTIFY_CHILDCHANGED: Sent to a parent window when a child changes
; **			state. This way the parent can keep track of a child window's
; **			processing.  Note that the Extra parameter of this message is set
; **			to the address of the child window's LHWINDOW structure.
; **		NOTIFY_SORT: Sent to ListBox windows to have them sort their contents.
; **			The extra field specifies the sort order (=0 : ascending,
; **			!=0 : descending).  The window will redraw itself as a result.
; **		NOTIFY_USER: Any applicaton defined submessages should have values
; **			starting at NOTIFY_USER.  Application defined submessages can
; **			be used for inter-window communications, i.e., as a way for
; **			various window handlers to converse with one another.  Any
; **			application specific notify messages should be defined like:
; **			#define NOTIFY_?????  NOTIFY_USER + x;  (where x starts at 0).
; ****************************************************************************
NOTIFY_CHILDCHANGED		EQU		0t
NOTIFY_CHILDKILLED		EQU		1t
NOTIFY_UPDATE		EQU		2t
NOTIFY_SORT		EQU		3t
NOTIFY_USER		EQU		256t
; ***************************************************************************
; **	COMMAND submesssages -- Used in PushButton controls
; **		These values are usually set as the command code in PushButton
; **		LHWINDOW structures in order to get the DialogBox handler to
; **		recognize common actions.
; **
; **		CMD_DONE: This sub-message is only recognized by the DialogBox
; **			handler, in which case it will automatically send the dialogbox
; **			window an (KEYSTROKE, F10, 0) message.
; **		CMD_ESC: This sub-message is only recognized by the DialogBox
; **			handler to automatically DESTROY itself.
; **		CMD_DIALOGFOCUS: This sub-message is only recognized by the DialogBox
; **			handler to set the focus to the dialog control corresponding to
; **			the field value specified in the Extra parameter.
; **		CMD_PUSHB_ACTIVATE: Sent to PushButton windows to have them
; **			activate themselves and perform the application-specified action.
; **		CMD_USER: Any applicaton defined submessages shouldhace values
; **			starting at CMD_USER.
; ****************************************************************************
CMD_DONE		EQU		0t
CMD_ESC		EQU		1t
CMD_DIALOGFOCUS		EQU		2t
CMD_PUSHB_ACTIVATE		EQU		3t
CMD_USER		EQU		256t
; ***************************************************************************
; **	DRAW submessages -- Bitmask value passed in the Data parameter.
; **		To display multiple regions of the window, OR the bit values for
; **		the desired window regions together.
; **		Note that not all DRAW_ regions make sense for all windows.
; **
; **      DRAW_TITLE: Draw the window title.
; **      DRAW_FKEYS: Draw the function keys bar.  This sub-message is managed
; **              entirely by the Object class handler.  It is sent by Object
; **              when a different window receives the focus.
; **      DRAW_CLIENT: Draw the entire window client area or workspace.
; **      DRAW_CLIENT_UPDATE: Draw that portion of the window client area which
; **              is after the current cursor position (as defined by the
; **              Selection field in the LHWINDOW structure).  This message is
; **              used, for instance, when text in an edit window is deleted or
; **              inserted.  In this case, the deleted/inserted text should be
; **              removed/added to the edit buffer before this message is sent.
; **		DRAW_CLIENT_CHAR: For edit windows, draw only the character at the
; **              current cursor position.
; **      DRAW_FRAME: Outline the window by displaying the window frame.
; **      DRAW_CURSOR: Show the window's cursor.
; **      DRAW_USER: Any applicaton defined areas should be bits starting at
; **              DRAW_USER.
; **      DRAW_ALL: Mask for all regions of the window.  This message is
; **				automatically sent by the Object class handler when a window
; **				is created.
; ****************************************************************************
;  0000 0000 0000 0001 
DRAW_TITLE		EQU		000000001h
;  0000 0000 0000 0010 
DRAW_FKEYS		EQU		000000002h
;  0000 0000 0000 0100 
DRAW_CLIENT		EQU		000000004h
;  0000 0000 0000 1000 
DRAW_CLIENT_UPDATE		EQU		000000008h
;  0000 0000 0001 0000 
DRAW_CLIENT_CHAR		EQU		000000010h
;  0000 0000 0010 0000 
DRAW_FRAME		EQU		000000020h
;  0000 0000 0100 0000 
DRAW_CURSOR		EQU		000000040h
;  1111 1111 1110 0111 
DRAW_ALL		EQU		00000ffe7h
;  0000 0001 0000 0000 
DRAW_USER		EQU		000000100h
; ***************************************************************************
; **	SETFOCUS submesssages
; **		SETFOCUS_NORMAL: A LOSEFOCUS message is sent to the old focus window
; **          AFTER the new focus window receives this SETFOCUS message.
; **		SETFOCUS_NOLOSE: Supresses a LOSEFOCUS message being sent to the
; **			old focus window.
; **	SETFOCUS tertiary-messsages
; **		SETFOCUS_SELECT: Window receives the focus, and does an implicit
; **			selection.  This submessage is onlu used for CheckBoxes, and is
; **          equivalent to pressing <Space> immediately after the checkbox
; **          receives the focus.
; ****************************************************************************
SETFOCUS_NORMAL		EQU		0t
SETFOCUS_NOLOSE		EQU		1t
SETFOCUS_SELECT		EQU		2t
; ***************************************************************************
; **	LOSEFOCUS submesssages
; **		LOSEFOCUS_NORMAL: The LOSEFOCUS message was sent under normal
; **			circumstances.
; **		LOSEFOCUS_MENU: The LOSEFOCUS message was sent prior to a menu
; **			window being created and given the focus.  This is provided in
; **			order to allow a window handler to behave differently depending
; **			on whether or not a LOSEFOCUS message is received because the
; **			menus are being activated.
; ****************************************************************************
LOSEFOCUS_NORMAL		EQU		0t
LOSEFOCUS_MENU		EQU		1t
; ***************************************************************************
; *****************************************************************************
; **
; **						LHAPI Function Prototypes
; **
; *****************************************************************************
; ****************************************************************************
; ****************************************************************************
; ** Each of the LHAPI services is prefaced with the following constant in	**
; ** order to allow for mixed-memory model applications.  A developer can		**
; ** selectively set this constant to either "_near" or "_far", or leave it	**
; ** as NULL in order to have all the calls to LHAPI use the same model as	**
; ** that specified to the compiler.											**
; ****************************************************************************
; ************************************************************************
; **		Global LHAPI Control functions
; *************************************************************************
@proto_5		TYPEDEF		PROTO C :PTR LHAPIBLOCK
InitializeLHAPI		PROTO		@proto_5

;  First time initialization by applications to point to a
; 	** LHAPIBLOCK structure allocated by the application.
; 	** The DataPtrType parameter specifies what type of data pointers
; 	** are being used by the application (near, far or based).  This
; 	** service set the current font type to FONT_NORMAL. 
@proto_6		TYPEDEF		PROTO C 
DeactivateLHAPI		PROTO		@proto_6

;  Application tells LHAPI that it is switching out. 
@proto_7		TYPEDEF		PROTO C :PTR LHAPIBLOCK
ReactivateLHAPI		PROTO		@proto_7

;  Application reestablishes LHAPI's LHAPIBLOCK data structure
; 	** after being switched back in.  This routine first sends a
; 	** REACTIVATE message to all the currently defined windows,
; 	** followed by an APPEAR message. 
@proto_8		TYPEDEF		PROTO C 
UninitializeLHAPI		PROTO		@proto_8

;  Application tells LHAPI it is terminating. 
@proto_9		TYPEDEF		PROTO C 
GetLHAPIBlockPtr		PROTO		@proto_9

;  Return the offset address of the currently defined LHAPIBLOCK
; 	** structure. 
@proto_10		TYPEDEF		PROTO C 
SyncLHAPIKeyState		PROTO		@proto_10

;  Re-sync the LHAPI keyboard state flags in the LHAPIBLOCK structure
; 	** with the current BIOS state. 
; ************************************************************************
; **		Messaging functions
; *************************************************************************
@proto_11		TYPEDEF		PROTO C :UINT, :UINT, :UINT
SendAllMsg		PROTO		@proto_11

;  Sends all windows in the active application the specified Message 
@proto_12		TYPEDEF		PROTO C :UINT, :UINT, :UINT
SendFocusMsg		PROTO		@proto_12

;  Sends the focus window a message 
@proto_13		TYPEDEF		PROTO C :PLHWINDOW, :UINT, :UINT, :UINT
SendMsg		PROTO		@proto_13

;  Sends the given window a message 
@proto_14		TYPEDEF		PROTO C :PLHCLASS, :PLHWINDOW, :UINT, :UINT, :UINT
SubclassMsg		PROTO		@proto_14

;  Sends the given window a message using a different class handler
; 	** than the one specified in the LHWINDOW structure 
; ************************************************************************
; **		Menu functions
; *************************************************************************
@proto_15		TYPEDEF		PROTO C 
ResetAlt		PROTO		@proto_15

;  Called before dispatching System Manager E_KEY events from an
; 	** application's event loop.  This call resets an internal flag so
; 	** that MonitorAlt() will not generate a <Menu> KEYSTROKE message
; 	** when the <Alt> key is subsequently released (because DoTopMenu()
; 	** already determined if a menu should be activated if an
; 	** <Alt-letter> key was pressed). 
; ************************************************************************
; **		Focus functions
; *************************************************************************
@proto_16		TYPEDEF		PROTO C 
GetFocus		PROTO		@proto_16

;  Returns a pointer to the current window with focus 
; ************************************************************************
; **		Error Handling functions
; *************************************************************************
@proto_17		TYPEDEF		PROTO C :SWORD
SetError		PROTO		@proto_17

;  Saves the specified value in the ErrorNum in the LHAPIBLOCK structure
; 	** if one is not already saved there.  Thie routine returns TRUE if the
; 	** specified error number was saved, FALSE if a previous errorr prevented
; 	** setting.
; 	** Handler is an optional routine to be given control when error is
; 	** acknowledged. 
@proto_18		TYPEDEF		PROTO C 
GetError		PROTO		@proto_18

;  Returns ErrorNum 
@proto_19		TYPEDEF		PROTO C 
ClearError		PROTO		@proto_19

;  Clears both the ErrorNum and the Handler field in the LHAPIBLOCK
; 	** structure. 
@proto_20		TYPEDEF		PROTO C :PLHFUNC
SetErrorHandler		PROTO		@proto_20

;  Sets Handler for Error (NULL means "use Std Error Handler") 
@proto_21		TYPEDEF		PROTO C 
GetErrorHandler		PROTO		@proto_21

;  Gets current error handler 
; ************************************************************************
; **		LHAPI specialized text display routine
; *************************************************************************
@proto_22		TYPEDEF		PROTO C :SWORD, :SWORD, :FAR PTR SBYTE, :UINT, :UINT
DrawText		PROTO		@proto_22

;  Draws text on the screen using the Style word.  If the Buffer pointer
; 	** is NULL, or the string starts with a null-terminator, this routine
; 	** just returns without displaying anything.  The pointer can be
; 	** considered NULL in one of two ways: either the entire pointer (both
; 	** the segment and offset address parts) is set to NULL; or the offset
; 	** portion of the pointer is NULL and the segment portion is set to
; 	** the application's default data segment.  The later method is provided
; 	** in order to validate near pointers which are "cast" to far pointers
; 	** by compilers.  For the meaning of the bits in the style word, see the
; 	** TEXT_ style definitions under WindowStruct.  The supported styles are:
; 	**		DRAW_NORMAL
; 	**		DRAW_INVERSE
; 	**		DRAW_UNDERLINE
; 	**		DRAW_GRAY
; 	**		DRAW_AMPERSAND.
; 	** The supported font values are:
; 	**		FONT_DEFAULT
; 	**		FONT_SMALL
; 	**		FONT_NORMAL
; 	**		FONT_LARGE
; 	** The text displayed is one line only, and is terminated by a NULL.
; 	** This service returns the width of the displayed string, in pixels. 
@proto_23		TYPEDEF		PROTO C :SWORD, :SWORD, :FAR PTR SBYTE, :UINT, :UINT, :UINT
DrawNChars		PROTO		@proto_23

;  Similar to DrawText, except that MaxChars specifies the maximum
; 	** number of characters in the text string to display.  That is, if the
; 	** total string length is greater than MaxChars, only the first MaxChars
; 	** characters will be displayed. 
@proto_24		TYPEDEF		PROTO C :SWORD, :SWORD, :UCHAR, :UINT, :UINT
DrawChar		PROTO		@proto_24

;  Displays a single character on the screen at the given location and
; 	** in the specified Draw style and font. 
@proto_25		TYPEDEF		PROTO C :PLHWINDOW, :UINT
DrawFKeys		PROTO		@proto_25

;  Displays the function-key labels for the given window at the bottom
; 	** of the display.  ShiftState refers to the "shift" (<Ctrl>, <Alt>,
; 	** <Shift>) key state to display the defined function keys for.
; 	** ShiftState uses the same values as those previously defined for the
; 	** KeyNum field the LHFKEY structure and are:
; 	**			FKEY_ALONE
; 	**			FKEY_CTRL
; 	**			FKEY_ALT
; 	**			FKEY_SHIFT  
; ************************************************************************
; **
; ** Graphics functions--(shells around the 5Fh graphics calls)
; **
; ** Currently, the system assumes it is in the following state:
; **     Mode    = REP_RULE     (Replace screen pixels)
; **     Color   = 1            (Black)
; **     Pattern = Checkerboard (055h,0AAh,055h,0AAh,...)
; **
; ** All LHAPI provided functions will return with the graphics parameters set
; ** this way, and any functions that change these parameters should restore
; ** them.
; *************************************************************************
; **** Color field definitions. ****
;  Black text on a white background. 
COLOR_NORMAL		EQU		1t
;  White text on a black background. 
COLOR_INVERSE		EQU		0t
; **** Box components size definitions. ****
SHADOW_W		EQU		6t
SHADOW_H		EQU		4t
BORDER_W		EQU		2t
BORDER_H		EQU		2t
@proto_26		TYPEDEF		PROTO C :SWORD, :SWORD, :SWORD, :SWORD, :UINT, :UINT
Rectangle		PROTO		@proto_26

;  Rectangle draws a rectangle using the specified color and flags.
; 	** Flags: 0 = Outline only;
; 	**        1 = Solidfill interior;
; 	**        2 = Patternfill interior with "gray" pattern;
; 	** Exits with COLOR=Color. 
G_OUTLINE		EQU		0t
G_SOLIDFILL		EQU		1t
G_PATTERNFILL		EQU		2t
@proto_27		TYPEDEF		PROTO C :SWORD, :SWORD, :SWORD, :SWORD
Panel		PROTO		@proto_27

;  Draws a rectangle with a black border and white inside.
; 	** Exits with COLOR=COLOR_NORMAL. 
@proto_28		TYPEDEF		PROTO C :SWORD, :SWORD, :SWORD, :SWORD
Outline		PROTO		@proto_28

;  Outlines a rectangle in black, does not touch inside.
; 	** Exits with COLOR=COLOR_NORMAL. 
@proto_29		TYPEDEF		PROTO C :SWORD, :SWORD, :SWORD, :SWORD
ShadowBox		PROTO		@proto_29

;  Draws a Panel box with a shadow to the right and underneath.
; 	   Note that the width and height include the shadowed area. 
@proto_30		TYPEDEF		PROTO C :SWORD, :SWORD, :SWORD, :SWORD
ClearRect		PROTO		@proto_30

;  ClearRect clears a section of the screen to white.
; 	** Exits with COLOR=COLOR_NORMAL. 
@proto_31		TYPEDEF		PROTO C :SWORD, :SWORD, :SWORD, :SWORD, :UINT
Line		PROTO		@proto_31

;  Draw line from (x1,y1) to (x2,y2), exits with COLOR=Color. 
@proto_32		TYPEDEF		PROTO C :UINT
RegisterFont		PROTO		@proto_32

;  Register the given font as one of those whic will be used by the
; 	** application.  This routine is used by LHAPI to arrange the font
; 	** bitmap stack such that the fonts to be used by an application are
; 	** on the top of the stack, thereby avoiding the problem of fonts
; 	** being constantly removed and added to the bitmap stack.  This
; 	** service should be called immediately after InitializeLHAPI(). The
; 	** possible Font values are:
; 	**		FONT_DEFAULTS,
; 	**		FONT_SMALL,
; 	**		FONT_NORMAL,
; 	**		FONT_LARGE.
; 	** Using FONT_DEFAULTS will cause all of the default system
; 	** fonts - FONT_SMALL, FONT_NORMAL and FONT_LARGE (if there's enough
; 	** room) - to be placed on the font bitmap stack. 
FONT_DEFAULTS		EQU		2t
@proto_33		TYPEDEF		PROTO C :UINT
SetDefaultFont		PROTO		@proto_33

;  Sets the default font to use to the given type.  This is the font
; 	** that will be used if any windows strcuture contain FONT_DEFAULT in the
; 	** Font field, or if FONT_DEFAULT is specified as an input parameter to
; 	** any of the text drawing services.
; 	** The possible font values are:
; 	** 		FONT_SMALL
; 	**		FONT_NORMAL
; 	**		FONT_LARGE	
@proto_34		TYPEDEF		PROTO C 
GetDefaultFont		PROTO		@proto_34

;  Returns the current default font (see above).
; 	** The possible return values are:
; 	**		FONT_SMALL
; 	**		FONT_NORMAL
; 	**		FONT_LARGE  
@proto_35		TYPEDEF		PROTO C :UINT
SetCurrentFont		PROTO		@proto_35

;  Sets the current system font to to the given type.  This service
; 	** should only be used when an application directly calls the low-level
; 	** graphics layer rather than using the DrawText/DrawChar services to
; 	** output text to the display.
; 	** The possible font values are:
; 	** 		FONT_SMALL
; 	**		FONT_NORMAL
; 	**		FONT_LARGE	
@proto_36		TYPEDEF		PROTO C 
GetCurrentFont		PROTO		@proto_36

;  Returns the currently defined system font that was set with the
; 	** SetCurrentFont servcice. 
@proto_37		TYPEDEF		PROTO C :UINT
SetMenuFont		PROTO		@proto_37

;  Set the system font to be use for the menus. 
@proto_38		TYPEDEF		PROTO C :SWORD, :SWORD, :SWORD, :SWORD
SetGlobalClipping		PROTO		@proto_38

;  Sets master clipping against which all local clip regions are clipped.
; 	** Calling this will also reset the local clipping region. 
@proto_39		TYPEDEF		PROTO C :SWORD, :SWORD, :SWORD, :SWORD
SetLocalClipping		PROTO		@proto_39

;  Sets clipping region within a particular window. 
@proto_40		TYPEDEF		PROTO C :PTR SWORD, :PTR SWORD, :PTR SWORD, :PTR SWORD
GetLocalClipping		PROTO		@proto_40

;  Returns the currently defined local clipping region. 
@proto_41		TYPEDEF		PROTO C :SWORD, :SWORD, :SWORD, :SWORD
IntersectLocalClipping		PROTO		@proto_41

;  Set the Local clipping region to the intersection of the specified
; 	** rectangular region and the currently defined Local clipping region. 
@proto_42		TYPEDEF		PROTO C :SWORD, :SWORD, :UINT
ShowSymbol		PROTO		@proto_42

;  Displays a special symbol at the given location.
; 	   Symbols IDs are listed below. 
RADIO_OPEN		EQU		1t
RADIO_FILLED		EQU		2t
CHECK_OPEN		EQU		3t
CHECK_FILLED		EQU		4t
COMBO_ICON		EQU		5t
@proto_43		TYPEDEF		PROTO C 
ResetVideo		PROTO		@proto_43

;  Reset the internal LHAPI video state variables.  This routine allows
; 	** LHAPI to reset the display to the mode it wants it in and should be
; 	** called by an application after it finshes directly calling any of the
; 	** low-level graphics functions. 
@proto_44		TYPEDEF		PROTO C :UCHAR
SetRepRule		PROTO		@proto_44

;  Set the low-level graphics pixel replacement rule.
; 	** The valid replacement rules are: 
REP_FORCE		EQU		0t
REP_AND		EQU		1t
REP_OR		EQU		2t
REP_XOR		EQU		3t
REP_NOTFORCE		EQU		4t
REP_NOTAND		EQU		5t
REP_NOTOR		EQU		6t
REP_NOTXOR		EQU		7t
REP_BITBLT		EQU		8t
@proto_45		TYPEDEF		PROTO C 
ResetRepRule		PROTO		@proto_45

;  Reset the low-level graphics pixel replacement rule to the
; 	** LHAPI-defined default. 
@proto_46		TYPEDEF		PROTO C :UINT
SetHelpFkey		PROTO		@proto_46

;  Set the application-wide "Help" function-key sequence.  The help key
; 	** is used internally by LHAPI.  If an application does not explicitly
; 	** set the help key, the default of <F1> is used.  This service need only
; 	** be called after InitializeLHAPI() is. 
; ***********************************************************************
;  Macros to get the width and height, in pixels, of the specified font. 
; ***************************************************************************
; **
; **		Display constants.
; **
; ****************************************************************************
;  Total width and height, in pixels, of the entire screen display area. 
DISPLAY_W		EQU		640t
DISPLAY_H		EQU		200t
; ***************************************************************************
; **
; **		TitleBar window class constants.
; **
; ****************************************************************************
; *** Titlebar window font type. ***
TITLEBAR_FONT		EQU		000000808h
; *** Starting column and row, in pixels, of the start of the TitleBar
; ***** window. ***
TITLEBAR_X		EQU		0t
TITLEBAR_Y		EQU		0t
; *** Width and height, in pixels, of the TitleBar window. ***
TITLEBAR_W		EQU		000000280h
TITLEBAR_H		EQU		000000008h
; ***************************************************************************
; **
; **		Function-key row display constants.
; **
; ****************************************************************************
; *** Titlebar window font type. ***
FKEYS_FONT		EQU		000000808h
; *** Width and height, in pixels, of the entire function key label row. ***
FKEYS_H		EQU		00000000ah
;  Starting row, in pixels, of the function key label row.  Note that
; ** FKEYS_START_Y refers to the starting column of the box surroundong each
; ** function key label, not the actual text inside of each box. 
FKEYS_START_Y		EQU		0000000beh
;  Revert structure packing back to default 
;  #if !defined(LHAPI_H) at top of module 
; End of file lhapi.h
