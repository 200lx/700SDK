/* SCCS info:   Module edit.h  Version 1.1  Date 11/09/93  Time 15:18:48 */

/* $Header:   T:/HH/INCLUDE/VCS/EDIT.H_V   1.2   15 Oct 1992 10:50:02   KIM  $ */
/****************************************************************
 *
 *	Copyright(c) 1990  Lotus Development Corporation
 *	All Rights Reserved
 *
 ****************************************************************/

/* EDIT.H  - edit manager for SINGLE line editing */

/* ASSUME: the maximum number of cols in an edit area is 80 */

/*
 * $Log:   T:/HH/INCLUDE/VCS/EDIT.H_V  $ 
 * 
 *    Rev 1.2   15 Oct 1992 10:50:02   KIM
 * * * * SERVER DISK CRASH RECOVERY * * *
 *  1) The VCS directory was restored with Build 18 backup tape.
 *  2) This revision is to update files to Build 19.
 *  3) HELP.H has post-Build 19 changes.
 * 
 *    Rev 1.1   04 May 1992 19:26:30   DAVID
 * Changed includes to use angle brackets instead of double quotes
 * 
 *    Rev 1.0   03 Dec 1991 20:14:38   DAVID
 * Initial revision.
 *
 */



#ifndef EDITDATADEF


#include <mdit.h>

/* EDIT_KEY returns "1" if user has accepted the edit buffer contents
     and returns "0" otherwise */

typedef struct {
	int edit_length; 	/* current length of the edit buffer */
	char first_time;      	/* flag for special processing on first char */
	char spec_flags;	/* bit 0 is tab handling */
     	int prompt_window;      /* whether this belongs to the prompt window */
	char far *message_line; /* the top line message for prompt */
	int message_line_length;/* length of same */
	char far *prompt_line;  /* second line of prompt window */
	int prompt_line_length; /* length of same */
	char edit_buffer[80];   /* work space for the buffer */
	int  line_array[2];	/* line array needed by mdit */
	MDITDATA mdit;          /* multi-line edit structure */
	int e_dispcols;
} EDITDATA;



#define EDITDATADEF 0
#endif

