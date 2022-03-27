/* SCCS info:   Module boxchrs.h  Version 1.1  Date 11/09/93  Time 15:14:24 */

/* $Header:   T:/HH/INCLUDE/VCS/BOXCHRS.H_V   1.1   15 Oct 1992 10:48:22   KIM  $ */
/****************************************************************
 *
 *	Copyright(c) 1990  Lotus Development Corporation
 *	All Rights Reserved
 *
 ****************************************************************/
/* Define the window line drawing characters */
/* This version uses of line drawing chars for cross bars and
     removes the vertical bars from the status region */

/****************************************************************
 * $Log:   T:/HH/INCLUDE/VCS/BOXCHRS.H_V  $
 * 
 *    Rev 1.1   15 Oct 1992 10:48:22   KIM
 * * * * SERVER DISK CRASH RECOVERY * * *
 *  1) The VCS directory was restored with Build 18 backup tape.
 *  2) This revision is to update files to Build 19.
 *  3) HELP.H has post-Build 19 changes.
 * 
 *    Rev 1.0   03 Dec 1991 20:14:24   DAVID
 * Initial revision.
 *
 */


   
/* define empty space char */
#define SPACE   32

/* define the cornerstone pieces */
#define UR_CORN   219
#define LR_CORN   219
#define LL_CORN   219
#define UL_CORN   219

/* define vertical bar drawing pieces */
#define V_BAR_L   219 
#define V_BAR_R   219

/* define the box's Horizontal bars */
/* top, bottom, menu bottom, and status top */
#define H_BAR_T   223
#define H_BAR_B   220
#define H_BAR_M   205
#define H_BAR_S   205

/* define the "T" junctions for "between" horizontal bars */
#define T_MENU_L  219
#define T_MENU_R  219
#define T_STAT_L  219
#define T_STAT_R  219
                     
/* define the vertical bars for the status line */
#define V_BAR_1   32
#define V_BAR_2   32

/* define the "T" bars for the lines above and below the status line */
#define T_DOWN_1  205
#define T_DOWN_2  205
#define T_UP_1    220
#define T_UP_2    220


