/* SCCS info:   Module jmp.h  Version 1.1  Date 11/09/93  Time 15:20:52 */

/****************************************************************
 *
 *	Copyright(c) 1990  Lotus Development Corporation
 *	All Rights Reserved
 *
 ****************************************************************/

/****************************************************************
jmp.h

Definitions for accessory non-local GOTO's
****************************************************************/
#ifndef	M_JMP

#ifdef MMODEL
  typedef struct { int sp, bp, ip, cs, di, si; } JMP;
#else
  typedef struct { int sp, bp, ip, di, si; } JMP;
#endif

int setjmp(JMP *);
void longjmp(JMP *, int);

#define	M_JMP
#endif
