/* SCCS info:   Module mystr.h  Version 1.1  Date 11/09/93  Time 15:23:24 */

/* $Header:   T:/hh/include/vcs/mystr.h_v   1.6   16 Nov 1992 10:04:20   PAUL  $
 */

/****************************************************************************
* MYSTR.H                                                                   *
*      Copyright(c),1992 by Lotus Development Corporation                   *
*                                                                           *
*      USAGE:  MYSTR                                                        *
*                                                                           *
*      DESCRIPTION:                                                         *
*      This module contains some functions normally found in C run          *
*      time library routines.                                               *
*                                                                           *
*                                                                           *
*****************************************************************************
* Version History                                                           *
* 23-Jun-92 PJG  Started.                                                   *
*                                                                           *
****************************************************************************/

/*
 * $Log:   T:/hh/include/vcs/mystr.h_v  $
 * 
 *    Rev 1.6   16 Nov 1992 10:04:20   PAUL
 * Added MyStrcmpi() prototype
 * 
 *    Rev 1.5   23 Oct 1992 15:05:48   PAUL
 * Added MyStrncmp()
 * 
 *    Rev 1.4   21 Oct 1992 15:12:00   PAUL
 * Added MyStrncpy()
 * 
 *    Rev 1.3   15 Oct 1992 10:51:40   KIM
 * * * * SERVER DISK CRASH RECOVERY * * *
 *  1) The VCS directory was restored with Build 18 backup tape.
 *  2) This revision is to update files to Build 19.
 *  3) HELP.H has post-Build 19 changes.
 * 
 *    Rev 1.2   08 Sep 1992 09:28:58   PAUL
 * Changes all pointers to be far
 * 
 *    Rev 1.1   07 Sep 1992 14:53:40   EDM
 * Changed Trim function to accept far pointers
 * 
 *    Rev 1.0   02 Sep 1992 12:41:02   PAUL
 * Initial revision.
 * 
 */

#ifndef MYSTR_H    // protection from being included twice
#define MYSTR_H


/* Include Files */
/* ------------- */


/* Defines */
/* ------- */

#define Myislower(c)  (((c) >= 'a') && ((c) <= 'z'))
#define Myisupper(c)  (((c) >= 'A') && ((c) <= 'Z'))

#define Mytolower(c)  ((Myislower(c)) ? (c) : ((c)-'A'+'a'))
#define Mytoupper(c)  ((Myisupper(c)) ? (c) : ((c)-'a'+'A'))




/* Prototypes */
/* ---------- */

int    MyStrlen(PFCHAR s);
PFCHAR MyStrcpy(PFCHAR pchDest, PFCHAR pchSrc);
PFCHAR MyStrncpy(PFCHAR pchDest, PFCHAR pchSrc, USHORT usCount);
PFCHAR MyStrcat(PFCHAR pchDest, PFCHAR pchSrc);
int    MyStrcmp(PFCHAR s1, PFCHAR s2);
int    MyStrncmp(PFCHAR s1, PFCHAR s2, USHORT usCount);
int    MyStrncmpi(PFCHAR s1, PFCHAR s2, USHORT usCount);
int    MyStrcmpi(PFCHAR s1, PFCHAR s2);
PFCHAR MyStrlower(PFCHAR pch);
PFCHAR MyStrupper(PFCHAR pch);
PFCHAR MyMemcpy(PFCHAR pDest, PFCHAR pSrc, USHORT usLen);
PFCHAR MyMemset(PFCHAR pDest, CHAR chValue, USHORT usLen);
USHORT MyAtoi(PFCHAR pch);
ULONG  MyAtol(PFCHAR pch);
PFCHAR  TrimLeft(PFCHAR pch);
PFCHAR  TrimRight(PFCHAR pch);
PFCHAR  TrimLeftAndRight(PFCHAR pch);


/* Global Variables */
/* ---------------- */


#endif // MYSTR_H
