/* SCCS info:   Module syshelp.h  Version 1.1  Date 11/09/93  Time 15:25:34 */

/* $Header:   T:/HH/INCLUDE/VCS/SYSHELP.H_V   1.1   15 Oct 1992 10:52:22   KIM  $ */
/*
;****************************************************************************
; SYSTEM MANAGER HELP SERVICES MAIN HEADER FILE
;
; copyright(c) 1990
; Lotus Development Corporation
; All Rights Reserved, Confidential and Proprietary Information
;
;****************************************************************************
;
; The functions in the help system are called using C conventions.  The
; functions are listed below:
;
;	int m_help_init(
;		struct help_state far *h_state,
;		char far *help_file_name,
;		int help_handle )
;
;	void m_help_term(
;		struct help_state far *h_state )
;
;	int m_help_display(
;		struct help_state far *h_state )
;
;	int m_help_key(
;		struct help_state far *h_state,
;		int key )
;
;
;****************************************************************************
*/

/* 
 * $Log:   T:/HH/INCLUDE/VCS/SYSHELP.H_V  $
 * 
 *    Rev 1.1   15 Oct 1992 10:52:22   KIM
 * * * * SERVER DISK CRASH RECOVERY * * *
 *  1) The VCS directory was restored with Build 18 backup tape.
 *  2) This revision is to update files to Build 19.
 *  3) HELP.H has post-Build 19 changes.
 * 
 *    Rev 1.0   03 Dec 1991 20:14:30   DAVID
 * Initial revision.
 * 
 */


/* Help Revision Number */
#define	HELP_REV		0


/* Error Messages & Exit Status */
#define HLP_DONE		1
#define HLP_NO_ERROR		0
#define HLP_ERR_OPEN_FAILURE	-1
#define HLP_ERR_BAD_HANDLE	-2
#define HLP_ERR_READ_FAILURE	-3
#define HLP_ERR_WRONG_REV	-4

/* Help State Structure Size (bytes) */
#define HLP_STATE_SIZE		1500

/*
NOTE, the help state structure size will eventually be reduced to under
500.  However, for now, you must declare a char array using this rather
large size.
*/

