/* SCCS info:   Module m_locks.h  Version 1.1  Date 11/09/93  Time 15:22:20 */

/* $Header:   T:/HH/INCLUDE/VCS/M_LOCKS.H_V   1.1   15 Oct 1992 10:51:50   KIM  $ */
/****************************************************************
 *
 *	Copyright(c) 1990  Lotus Development Corporation
 *	All Rights Reserved
 *
 ****************************************************************/

/****************************************************************
m_locks.h

Include file to declare kernel entry points for setting and
reading the state of the keyboard "locks".

WARNING: Accessories should NOT explicitly set the "Scroll Lock"
state!  The kernel will place the accessory in "Move Window" mode
until the user enters the proper keystroke to terminate.
****************************************************************/

/*
 * $Log:   T:/HH/INCLUDE/VCS/M_LOCKS.H_V  $ 
 * 
 *    Rev 1.1   15 Oct 1992 10:51:50   KIM
 * * * * SERVER DISK CRASH RECOVERY * * *
 *  1) The VCS directory was restored with Build 18 backup tape.
 *  2) This revision is to update files to Build 19.
 *  3) HELP.H has post-Build 19 changes.
 * 
 *    Rev 1.0   03 Dec 1991 20:14:26   DAVID
 * Initial revision.
 *
 */


#ifndef	M_LOCKS

/* Definitions for the meaningful lock bits */
#define CAPLK           0x40        /*  caps-lock bit */
#define NUMLK           0x20        /*  num-lock bit  */
#define SCRLK           0x10        /*  scroll-lock bit  */

extern  unsigned        m_getlocks();		/* returns lock bit mask */
extern  void            m_setlocks( unsigned );	/* sets ... */

#define	M_LOCKS
#endif
