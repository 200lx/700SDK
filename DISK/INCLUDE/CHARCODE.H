/* SCCS info:   Module charcode.h  Version 1.1  Date 11/09/93  Time 15:16:19 */

/* $Header:   T:/HH/INCLUDE/VCS/CHARCODE.H_V   1.14   16 Mar 1993 19:21:42   DARYL  $ */
/****************************************************************
 *
 *	Copyright(c) 1990  Lotus Development Corporation
 *	All Rights Reserved
 *
 ****************************************************************/


/* CHARCODE.H  - character codes for mnemonic and translations to different
                 character sets */
/***************************************************************************
 * $Log:   T:/HH/INCLUDE/VCS/CHARCODE.H_V  $
 * 
 *    Rev 1.14   16 Mar 1993 19:21:42   DARYL
 * Added the SHIFT_MENU keycode definition.
 * 
 *    Rev 1.13   25 Feb 1993 15:27:34   PETERR
 * Changed key code conflict with new shift make code.
 * 
 *    Rev 1.12   25 Feb 1993 09:04:58   PETERR
 * Changed Shift make and break low byte codes from "03" to "83".
 * DOS was incorrectly interpreting the value as a Ctrl'C key.
 * See comment in file ALTSHIFT.ASM for a fuller explanation.
 * 
 *    Rev 1.11   22 Feb 1993 19:50:38   DARYL
 * Changed the SHIFT_MAKE constant from 0x7E33 to 0x7E03 and the SHIFT_BREAK
 * constant from 0xFE33 to 0xFE03.
 * 
 *    Rev 1.10   15 Dec 1992 18:07:42   DARYL
 * Deleted the Tradewind keys and added the Cougar <Cut>, <Copy>, <Paste> keys.
 * 
 *    Rev 1.9   09 Nov 1992 18:23:02   DARYL
 * Added the Special SysMgr SCROLL_LOCK_ON/SCROLL_LOCK_OFF and
 * CAPS_LOCK_ON/CAPS_LOCK_OFF keycodes.
 * 
 *    Rev 1.8   04 Nov 1992 12:56:08   PETERR
 * Changed charcode for special shift make/break keys to remove conflict with
 * DOS mistaking it for Ctrl'C
 * 
 *    Rev 1.7   26 Oct 1992 15:22:34   PETERR
 * Added new key codes for FN key
 * 
 *    Rev 1.6   26 Oct 1992 12:34:22   PETERR
 * Added new keycodes per comm request
 * 
 *    Rev 1.5   23 Oct 1992 15:41:42   PETERR
 * Added Cougar custom high byte key values
 * 
 *    Rev 1.4   15 Oct 1992 10:48:34   KIM
 * * * * SERVER DISK CRASH RECOVERY * * *
 *  1) The VCS directory was restored with Build 18 backup tape.
 *  2) This revision is to update files to Build 19.
 *  3) HELP.H has post-Build 19 changes.
 * 
 *    Rev 1.4   09 Oct 1992 16:39:46   DARYL
 * Changed the ALT_D_ARROW and ALT_U_ARROW keycode defined to their proper
 * values (7Eh in high byte, not 7Fh).
 * 
 *    Rev 1.3   05 Oct 1992 15:59:12   DARYL
 * Changed the high byte of the special SysMgr 3.0 keycodes from 7F/FF to 7E/FE.
 * 
 *    Rev 1.2   25 Sep 1992 18:02:42   DARYL
 * Added the new, special SysMgr keycodes (Alt, Ctrl, Shift make/break, etc.)
 * 
 *    Rev 1.1   04 May 1992 19:27:00   DAVID
 * Changed includes to use angle brackets instead of double quotes
 * 
 *    Rev 1.0   03 Dec 1991 20:14:34   DAVID
 * Initial revision.
 *
 */

/*
Date		Version	   	Changer	Comment
04-08-86  	0.01		MM	Added ALT_Function keys.
					Added new names for special 
					Tradewind keys.
04-28-86	0.02		DAK	INCLUDED new char_alt.h and
					charscan.h
07/16/86	0.03		DAK	Changed REDRAW/KEY_REPAINT to
					ALT_F10 (from F9)
					NOTE that there are many
					redundancies in this file that
					I am reluctant to remove, in
					fear of a bunch of hate (E)mail.
*/

#ifndef	M_CHARCODE


/* REAL characters, those that mean what they mean */
#define SPACE       32
#define BACKSP      8
#define C_BACKSP    127
#define DEL	    ( 83*256)
#define INS	    ( 82*256)
#define TAB         9
#define BACKTAB     ( 15*256)
#define ESC         27
#define COLON       58
#define CTRL_L      12
#define F1	    ( 59*256)
#define F2	    ( 60*256)
#define F3	    ( 61*256)
#define F4	    ( 62*256)
#define F5	    ( 63*256)
#define F6	    ( 64*256)
#define F7	    ( 65*256)
#define F8	    ( 66*256)
#define F9	    ( 67*256)
#define F10	    ( 68*256)
#define F11	    ( 0x8500)


#define SHIFT_F1	( 84*256)
#define SHIFT_F2	( 85*256)
#define SHIFT_F3	( 86*256)
#define SHIFT_F4	( 87*256)
#define SHIFT_F5	( 88*256)
#define SHIFT_F6	( 89*256)
#define SHIFT_F7	( 90*256)
#define SHIFT_F8	( 91*256)
#define SHIFT_F9	( 92*256)
#define SHIFT_F10	( 93*256)
#define CTRL_F1 	( 94*256)
#define CTRL_F2 	( 95*256)
#define CTRL_F3 	( 96*256)
#define CTRL_F4 	( 97*256)
#define CTRL_F5 	( 98*256)
#define CTRL_F6 	( 99*256)
#define CTRL_F7 	( 100*256)
#define CTRL_F8 	( 101*256)
#define CTRL_F9 	( 102*256)
#define CTRL_F10	( 103*256)
#define ALT_F1		( 104*256)
#define ALT_F2	    ( 105*256)
#define ALT_F3	    ( 106*256)
#define ALT_F4	    ( 107*256)
#define ALT_F5	    ( 108*256)
#define ALT_F6	    ( 109*256)
#define ALT_F7	    ( 110*256)
#define ALT_F8	    ( 111*256)
#define ALT_F9	    ( 112*256)
#define ALT_F10     ( 113*256)

#define ENTER       13
#define C_ENTER     10
#define L_ARROW     ( 75*256)
#define CL_ARROW    ( 115*256)
#define R_ARROW     ( 77*256)
#define CR_ARROW    ( 116*256)
#define U_ARROW     ( 72*256)
#define D_ARROW     ( 80*256)
#define HOME_KEY    ( 71*256)
#define END_KEY     ( 79*256)
#define PAGE_UP     ( 73*256)
#define PAGE_DN     ( 81*256)
#define C_PRTSCR    ( 114*256)	    /* Control Print screen */
#define C_HOME_KEY  ( 119*256)
#define C_END_KEY   ( 117*256)
#define C_PAGE_UP   ( 132*256)
#define C_PAGE_DN   ( 118*256)


#define JAG_MENU_KEY 0xC800		/* <Menu> key */
#define SHIFT_MENU   0xC900		/* <Shift+Menu> key */

#define CUT_KEY		0xD400		/* <Cut> key */
#define COPY_KEY	0xD500		/* <Copy> key */
#define PASTE_KEY	0xD600		/* <Paste> key */


/* Special System Manager 3.0 keys */
#define SHIFT_MAKE	( 0x7E83)	/* Make code for <Shift> key */
#define CTRL_MAKE	( 0x7E04)	/* Make code for <Ctrl> key */
#define ALT_MAKE	( 0x7E08)	/* Make code for <Alt> key */
#define SHIFT_BREAK	( 0xFE83)	/* Break code for <Shift> key */
#define CTRL_BREAK	( 0xFE04)	/* Break code for <Ctrl> key */
#define ALT_BREAK	( 0xFE08)	/* Break code for <Alt> key */

#define ALT_D_ARROW	( 0x7E80)	/* <Alt><DownArrow> key */
#define ALT_U_ARROW	( 0x7E81)	/* <Alt><UpArrow> key */

#define ALT_R_ARROW	( 0x7e82)	/* Alt-right key pressed	*/

#define ALT_HOME	( 0x7e84)	/* Alt-home key pressed	*/
#define ALT_PGDN	( 0x7e85)	/* Alt-pgdn key pressed	*/
#define ALT_PGUP	( 0x7e86)	/* Alt-pgup key pressed	*/
#define ALT_END		( 0x7e87)	/* Alt-end  key pressed */
#define FN_MAKE		( 0x7e88)	/* FN key pressed */
#define FN_BREAK	( 0xfe88)	/* FN key released */
#define ALT_L_ARROW	( 0x7e89)	/* Alt-left key pressed */

#define CAPS_LOCK_ON	( 0x7E40)	/* CapsLock enabled key */
#define CAPS_LOCK_OFF	( 0xFE40)	/* CapsLock disabled key */

#define SCROLL_LOCK_ON	( 0x7E10)	/* NumLock enabled key */
#define SCROLL_LOCK_OFF	( 0xFE10)	/* NumLock disabled key */


#define SPECIAL_MAKE_HIGH_BYTE	 0x7e
#define SPECIAL_BREAK_HIGH_BYTE  0xfe



/* Names for ALT'd keys, and for key scan codes			*/
#include <char_alt.h>
#include <charscan.h>

#define	M_CHARCODE
#endif

