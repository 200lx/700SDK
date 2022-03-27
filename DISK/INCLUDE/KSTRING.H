/* SCCS info:   Module kstring.h  Version 1.1  Date 11/09/93  Time 15:21:05 */

/* $Header:   T:/HH/INCLUDE/VCS/KSTRING.H_V   1.1   15 Oct 1992 10:51:06   KIM  $ */
/****************************************************************
 *
 *	Copyright(c) 1990  Lotus Development Corporation
 *	All Rights Reserved
 *
 ****************************************************************/

/****************************************************************
Explicit function declarations for mdl\kernel\utils\string.asm
****************************************************************/
/*
 * $Log:   T:/HH/INCLUDE/VCS/KSTRING.H_V  $ 
 * 
 *    Rev 1.1   15 Oct 1992 10:51:06   KIM
 * * * * SERVER DISK CRASH RECOVERY * * *
 *  1) The VCS directory was restored with Build 18 backup tape.
 *  2) This revision is to update files to Build 19.
 *  3) HELP.H has post-Build 19 changes.
 * 
 *    Rev 1.0   03 Dec 1991 20:14:46   DAVID
 * Initial revision.
 *
 */


extern	void	fillc( char, void far *, unsigned );
extern	void	fillw( unsigned, void far *, unsigned );
extern	void	copyn( void far *, void far *, int );
extern	void	rcopyn( void far *, void far *, int );
extern	int	index( char, char far *, int );
extern	void	segcopy( int, int, int );
extern  int     strlen(char far *);

