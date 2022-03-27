/* SCCS info:   Module cchandle.h  Version 1.1  Date 11/09/93  Time 15:14:56 */

/***********************************************************
 *  Name:       T:\HH\INCLUDE\CCHANDLE.H
 *  Date:       Tuesday April 14, 1992
 *  Legal:      Copyright 1992 Lotus Development Corp.
 *              All rights reserved.
 *  Abstract:   header file for the handle service
 *  History:    
 *      KJQ 4/14/1992  Created.
 *
 *  $Log:   T:/HH/INCLUDE/VCS/CCHANDLE.H_V  $
 * 
 *    Rev 1.2   30 Oct 1992 11:37:30   WEI-LEE
 * Added macros GET_SESSION and GET_INDEX.
 * 
 *    Rev 1.1   15 Oct 1992 10:48:32   KIM
 * * * * SERVER DISK CRASH RECOVERY * * *
 *  1) The VCS directory was restored with Build 18 backup tape.
 *  2) This revision is to update files to Build 19.
 *  3) HELP.H has post-Build 19 changes.
 * 
 *    Rev 1.0   22 Sep 1992 16:15:52   DON
 * Initial revision.
 ***********************************************************/
#if !defined(CCHANDLE_H)
#define CCHANDLE_H

typedef long HANDLE;

#define FAR _far

HANDLE HSGetSessionHandle(int nHandles);
HANDLE HSRegisterSessionHandle(HANDLE handle);
HANDLE HSGetHandle(vimVoidPtr pointer, HANDLE handle);
HANDLE HSGetSession(HANDLE handle);
HANDLE HSGetPointer(HANDLE handle, vimVoidPtr *pptr);
HANDLE HSReleaseHandle(HANDLE handle);
HANDLE HSReleaseSessionHandle(HANDLE handle);

void SaveAsHandle(vimVoidPtr *p, HANDLE session);

#if defined(SERVER)
#define CC_HFIRSTSESSION 0x00010000L
#define ISLOCAL(handle) ((((long)handle) & 0x08000000L) == 0L)
#else
#define CC_HFIRSTSESSION 0x08010000L
#define ISLOCAL(handle) ((((long)handle) & 0x08000000L) != 0L)
#endif

#define GET_SESSION(h)      (h & 0xFFFF0000L)
#define GET_INDEX(h)        (h & 0x0000FFFFL)

#define HS_OUT_OF_SESSIONS  -1L
#define HS_NOSPACE          -2L
#define HS_SESSION_CONFLICT -3L
#define HS_NOHANDLES        -4L
#define HS_BADHANDLE        -5L
#define HS_NOT_FOUND        -6L

#endif
