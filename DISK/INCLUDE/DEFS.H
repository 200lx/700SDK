/* SCCS info:   Module defs.h  Version 1.1  Date 11/09/93  Time 15:18:23 */

/* $Header:   T:/HH/INCLUDE/VCS/DEFS.H_V   1.1   15 Oct 1992 10:49:56   KIM  $ */

/****************************************************************
 *
 *	Copyright(c) 1990  Lotus Development Corporation
 *	All Rights Reserved
 *
 ****************************************************************/


/*  miscellaneous definitions  */
/* note need for near and far pointer versions */

/*
 * $Log:   T:/HH/INCLUDE/VCS/DEFS.H_V  $ 
 * 
 *    Rev 1.1   15 Oct 1992 10:49:56   KIM
 * * * * SERVER DISK CRASH RECOVERY * * *
 *  1) The VCS directory was restored with Build 18 backup tape.
 *  2) This revision is to update files to Build 19.
 *  3) HELP.H has post-Build 19 changes.
 * 
 *    Rev 1.0   03 Dec 1991 20:14:38   DAVID
 * Initial revision.
 *
 */


#define lobyte(x)       (((char *) &(x))[0])
#define hibyte(x)       (((char *) &(x))[1])
#define loword(x)       (((int *) &(x))[0])
#define hiword(x)       (((int *) &(x))[1])
#define lowordf(x)       (((int far *) &(x))[0])
#define hiwordf(x)       (((int far *) &(x))[1])

#define	max(a,b)	( (a)>(b) ? (a) : (b) )
#define	min(a,b)	( (a)<(b) ? (a) : (b) )

#define MAXINT          32767
/*	#define NULL            ((char *) 0)	*/
#define NULL            0L

/****************************************************************
Explicit function declarations for TradeWind kernel
Arg lists are typed for routines requiring far pointers
****************************************************************/
