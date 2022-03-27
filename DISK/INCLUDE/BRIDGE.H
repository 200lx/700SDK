/* SCCS info:   Module bridge.h  Version 1.1  Date 11/09/93  Time 15:14:34 */

/* $Header:   T:/HH/INCLUDE/VCS/BRIDGE.H_V   1.1   15 Oct 1992 10:48:24   KIM  $ */

/****************************************************************
 *
 *	Copyright(c) 1990  Lotus Development Corporation
 *	All Rights Reserved
 *
 ****************************************************************/
/*
 * $Log:   T:/HH/INCLUDE/VCS/BRIDGE.H_V  $ 
 * 
 *    Rev 1.1   15 Oct 1992 10:48:24   KIM
 * * * * SERVER DISK CRASH RECOVERY * * *
 *  1) The VCS directory was restored with Build 18 backup tape.
 *  2) This revision is to update files to Build 19.
 *  3) HELP.H has post-Build 19 changes.
 * 
 *    Rev 1.0   03 Dec 1991 20:14:32   DAVID
 * Initial revision.
 *
 */

#define BRIDGE_TEST 	0
#define BRIDGE_GETRANGE 1
#define BRIDGE_GETRANGE_ADDR 2
#define BRIDGE_SETRANGE_ADDR 3
#define BRIDGE_GETRANGE_DATA 4
#define BRIDGE_SETRANGE_DATA 5
#define BRIDGE_RECALC 6
#define BRIDGE_GET_CURSOR 7
#define BRIDGE_SET_CURSOR 8
#define BRIDGE_REDISPLAY 9
#define BRIDGE_CELLTYPE 10


typedef struct BRIDGE_BP {
	int bpb_funcode;
	int bpb_retcode;
	char bpb_rangename[16];
	int bpb_startcol;
	int bpb_startrow;
	int bpb_endcol;
	int bpb_endrow;
	int bpb_order;
	int bpb_bufsize;
	char near * bpb_buffer;
} BRIDGE_BP;

	
