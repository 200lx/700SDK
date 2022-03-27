/* SCCS info:   Module ini.h  Version 1.1  Date 11/09/93  Time 15:20:20 */

/* $Header:   T:/hh/include/vcs/ini.h_v   1.12   16 Feb 1993 00:53:58   PAUL  $ */

/****************************************************************************
* INI.H                                                                     *
*      Copyright(c),1992 by Lotus Development Corporation                   *
*                                                                           *
*      USAGE:  INI                                                          *
*                                                                           *
*      DESCRIPTION:                                                         *
*      This is the header file for the INI file routines.                   *
*                                                                           *
*      These routines work well on relatively small files.  On larger ini   *
*      files ( >20k ), you will notice a slight delay.                      *
*                                                                           *
*      #define OS2  or                                                      *
*      #define COUGAR                                                       *
*                                                                           *
*****************************************************************************
* Version History                                                           *
* 27-Aug-92 PJG  Started.                                                   *
*                                                                           *
****************************************************************************/

/*
 * $Log:   T:/hh/include/vcs/ini.h_v  $
 * 
 *    Rev 1.12   16 Feb 1993 00:53:58   PAUL
 * Removed GetParameter, and moved everything below it up one.
 * 
 *    Rev 1.11   08 Feb 1993 23:10:38   PAUL
 * Added INISTS_WRITEERROR
 * 
 *    Rev 1.10   07 Jan 1993 14:47:52   ROGER
 * Fixed syntax errors with some of the macros.
 * 
 *    Rev 1.9   05 Jan 1993 22:55:18   ROGER
 * Converted the INI functions to an API system service.
 * 
 *    Rev 1.8   11 Dec 1992 13:51:00   PAUL
 * Added pszTempInifilename
 * 
 *    Rev 1.7   09 Dec 1992 20:10:20   PAUL
 *
 *    Rev 1.6   09 Dec 1992 19:37:04   PAUL
 * Added pszIniFileName as global in ini.c, changed #define
 *
 *    Rev 1.5   18 Oct 1992 16:54:04   PAUL
 * Changed PCHAR's to PFCHAR's on GetValue(), GetSection(), and GetKeyword().
 *
 *    Rev 1.4   15 Oct 1992 10:50:52   KIM
 * * * * SERVER DISK CRASH RECOVERY * * *
 *  1) The VCS directory was restored with Build 18 backup tape.
 *  2) This revision is to update files to Build 19.
 *  3) HELP.H has post-Build 19 changes.
 *
 *    Rev 1.4   10 Oct 1992 12:37:24   DON
 * Added prorotypes for DeleteSection and RenameSection.
 *
 *    Rev 1.3   03 Oct 1992 16:17:18   DON
 * Added text string for temporary file name
 *
 *    Rev 1.2   02 Oct 1992 12:13:56   DON
 * Added prototypes for SetValue, CopySection and AppendKeyword.
 *
 *    Rev 1.1   07 Sep 1992 14:36:58   EDM
 * change strings to far pointers
 *
 *    Rev 1.0   02 Sep 1992 12:40:58   PAUL
 * Initial revision.
 *
 */


#ifndef INI_H    // protection from being included twice
#define INI_H


/* Include Files */
/* ------------- */


/* Defines */
/* ------- */

#define INISTS_SUCCESS          0   // Status values
#define INISTS_OPENERROR        1
#define INISTS_SECTIONNOTFOUND  2
#define INISTS_KEYWORDNOTFOUND  3
#define INISTS_PARAMNOTFOUND    4
#define INISTS_BUFTOOSMALL      5
#define INISTS_READERROR        6
#define INISTS_EOFREACHED       7
#define INISTS_WRITEERROR       8

#define MAXINILINELEN         256


/* System Manager API Interface */
/* ---------------------------- */

#define CCMAIL_CLASS        0x5700

#define CCM_GET_SECTION     (CCMAIL_CLASS + 1)
#define GetSection(pszFileName, pszSection, usSectionOccurrence, usMaxLen) \
        c_service(CCM_GET_SECTION, \
            (char far *)pszFileName, \
            (char far *)pszSection, \
            (unsigned short)usSectionOccurrence, \
            (unsigned short)usMaxLen)

#define CCM_GET_KEYWORD     (CCMAIL_CLASS + 2)
#define GetKeyword(pszFileName, pszSection, usSectionOccurance, pszKeyword, usKeywordOccurance, usMaxLen) \
        c_service(CCM_GET_KEYWORD, \
            (char far *)pszFileName, \
            (char far *)pszSection, \
            (unsigned short)usSectionOccurance, \
            (char far *)pszKeyword, \
            (unsigned short)usKeywordOccurance, \
            (unsigned short)usMaxLen)

#define CCM_GET_VALUE       (CCMAIL_CLASS + 3)
#define GetValue(pszFileName, pszSection, usSectionOccurance, pszKeyword, usKeywordOccurance, pszValue, usMaxLen) \
        c_service(CCM_GET_VALUE, \
            (char far *)pszFileName, \
            (char far *)pszSection, \
            (unsigned short)usSectionOccurance, \
            (char far *)pszKeyword, \
            (unsigned short)usKeywordOccurance, \
            (char far *)pszValue, \
            (unsigned short)usMaxLen)

#define CCM_SET_VALUE       (CCMAIL_CLASS + 4)
#define SetValue(pszFileName, pszSection, usSectionOccurance, pszKeyword, usKeywordOccurance, pszValue) \
        c_service(CCM_SET_VALUE, \
            (char far *)pszFileName, \
            (char far *)pszSection, \
            (unsigned short)usSectionOccurance, \
            (char far *)pszKeyword, \
            (unsigned short)usKeywordOccurance, \
            (char far *)pszValue)

#define CCM_COPY_SECTION    (CCMAIL_CLASS + 5)
#define CopySection(pszFileName, pszSection, usSectionOccurance, pszNewSection) \
        c_service(CCM_COPY_SECTION, \
            (char far *)pszFileName, \
            (char far *)pszSection, \
            (unsigned short)usSectionOccurance, \
            (char far *)pszNewSection)

#define CCM_APPEND_KEYWORD  (CCMAIL_CLASS + 6)
#define AppendKeyword(pszFileName, pszSection, usSectionOccurance, pszNewKeyword) \
        c_service(CCM_APPEND_KEYWORD, \
            (char far *)pszFileName, \
            (char far *)pszSection, \
            (unsigned short)usSectionOccurance, \
            (char far *)pszNewKeyword)

#define CCM_DELETE_SECTION  (CCMAIL_CLASS + 7)
#define DeleteSection(pszFileName, pszSection, usSectionOccurance) \
        c_service(CCM_DELETE_SECTION, \
            (char far *)pszFileName, \
            (char far *)pszSection, \
            (unsigned short)usSectionOccurance)

#define CCM_RENAME_SECTION  (CCMAIL_CLASS + 8)
#define RenameSection(pszFileName, pszSection, usSectionOccurance, pszNewSection) \
        c_service(CCM_RENAME_SECTION, \
            (char far *)pszFileName, \
            (char far *)pszSection, \
            (unsigned short)usSectionOccurance, \
            (char far *)pszNewSection)


#endif // INI_H
