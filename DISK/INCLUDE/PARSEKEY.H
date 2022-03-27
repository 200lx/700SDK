/* SCCS info:   Module parsekey.h  Version 1.1  Date 11/09/93  Time 15:23:34 */

/* $Header:   T:/HH/INCLUDE/VCS/PARSEKEY.H_V   1.5   09 Feb 1993 00:30:48   DAVID  $ */
/**************************************************************************
 *
 *  Name:       C:\COUGAR\LSETUP\PARSEKEY.H
 *  Date:       Tuesday April 7, 1992
 *  Abstract:   Header file/public interface for key parsing functions
 *
 * ------------------------------------------------------------------------
 *                   Copyright 1992 Lotus Development Corp.
 *                           All rights reserved.
 **************************************************************************
 *
 * $Log:   T:/HH/INCLUDE/VCS/PARSEKEY.H_V  $
 * 
 *    Rev 1.5   09 Feb 1993 00:30:48   DAVID
 * Increased MAX_MNEMONIC_LEN 'cause it was a bit too close to the truth for
 * comfort.
 * 
 *    Rev 1.4   03 Feb 1993 20:28:06   DAVID
 * Added defines for column number in scantable for shift states
 * 
 *    Rev 1.3   15 Oct 1992 10:51:58   KIM
 * * * * SERVER DISK CRASH RECOVERY * * *
 *  1) The VCS directory was restored with Build 18 backup tape.
 *  2) This revision is to update files to Build 19.
 *  3) HELP.H has post-Build 19 changes.
 * 
 *    Rev 1.2   23 Jul 1992 21:52:42   DAVID
 * removed extraneous function prototypes
 * 
 *    Rev 1.1   15 Jul 1992 22:58:54   DAVID
 * Changed near to far in GetScanCode and GetScanLabel
 * 
 *    Rev 1.0   15 Jul 1992 22:44:34   DAVID
 * Initial revision.
 * 
 *    Rev 1.3   07 Jul 1992 16:38:38   HOMI
 * New API changes.
 * 
 *    Rev 1.2   04 May 1992 17:02:54   DAVID
 * Changed "get_resource_ptr" macro to diirect function call Rsrcget_ptr
 * 
 *    Rev 1.1   08 Apr 1992 23:44:08   DAVID
 * Provide "fake" prototypes for public API
 * 
 *    Rev 1.0   08 Apr 1992 18:17:54   DAVID
 * Initial revision.
 *
 **************************************************************************/

#if !defined(PARSEKEY_H)
#define PARSEKEY_H

/**************************************************************************
 *  Defines for key parsing functions 
 */

#define KEY_MAP_ERROR     -1     /* init resource file results */
#define KEY_MAP_OK         0
#define MAX_MNEMONIC_LEN  16     /* Ctrl-BackSp, e.g., plus margin */

/* column numbers in scan table for shift state */
#define KEY_SHIFT_NOMATCH     -1
#define KEY_SHIFT_NONE         0
#define KEY_SHIFT_SHIFT	       1
#define KEY_SHIFT_CTRL         2
#define KEY_SHIFT_ALT          3

#endif
