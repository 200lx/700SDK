/* SCCS info:   Module charscan.h  Version 1.1  Date 11/09/93  Time 15:16:37 */

/* $Header:   T:/HH/INCLUDE/VCS/CHARSCAN.H_V   1.1   15 Oct 1992 10:48:38   KIM  $ */
/****************************************************************
 *
 *	Copyright(c) 1990  Lotus Development Corporation
 *	All Rights Reserved
 *
 ****************************************************************/

/****************************************************************
Keyboard scan codes (as returned by TradeWind event calls)
****************************************************************/
/*
 * $Log:   T:/HH/INCLUDE/VCS/CHARSCAN.H_V  $
 * 
 *    Rev 1.1   15 Oct 1992 10:48:38   KIM
 * * * * SERVER DISK CRASH RECOVERY * * *
 *  1) The VCS directory was restored with Build 18 backup tape.
 *  2) This revision is to update files to Build 19.
 *  3) HELP.H has post-Build 19 changes.
 * 
 *    Rev 1.0   03 Dec 1991 20:14:34   DAVID
 * Initial revision.
 *
 */

#ifndef	M_CHARSCAN

#define SWEDISH_KEYBOARD 1

#if SWEDISH_KEYBOARD
#define SCAN_1 59
#define SCAN_2 60
#define SCAN_3 61
#define SCAN_4 62
#define SCAN_5 63
#define SCAN_6 64
#define SCAN_7 65
#define SCAN_8 66
#define SCAN_9 67
#define SCAN_0 68
#else
#define SCAN_1 2
#define SCAN_2 3
#define SCAN_3 4
#define SCAN_4 5
#define SCAN_5 6
#define SCAN_6 7
#define SCAN_7 8
#define SCAN_8 9
#define SCAN_9 10
#define SCAN_0 11
#endif

#define SCAN_Q 16
#define SCAN_W 17
#define SCAN_E 18
#define SCAN_R 19
#define SCAN_T 20
#define SCAN_Y 21
#define SCAN_U 22
#define SCAN_I 23
#define SCAN_O 24
#define SCAN_P 25
#define SCAN_A 30
#define SCAN_S 31
#define SCAN_D 32
#define SCAN_F 33
#define SCAN_G 34
#define SCAN_H 35
#define SCAN_J 36
#define SCAN_K 37
#define SCAN_L 38
#define SCAN_Z 44
#define SCAN_X 45
#define SCAN_C 46
#define SCAN_V 47
#define SCAN_B 48
#define SCAN_N 49
#define SCAN_M 50
#define SCAN_ESC 1
#define SCAN_SPACE 57
#define SCAN_F1 59
#define SCAN_F2 60
#define SCAN_F3 61
#define SCAN_F4 62
#define SCAN_F5 63
#define SCAN_F6 64
#define SCAN_F7 65
#define SCAN_F8 66
#define SCAN_F9 67
#define SCAN_F10 68
#define SCAN_DASH 12
#define SCAN_EQUAL 13
#define SCAN_BS 14
#define SCAN_TAB 15
#define SCAN_N7 71
#define SCAN_N8 72
#define SCAN_N9 73
#define SCAN_GREY_DASH 74
#define SCAN_N4 75
#define SCAN_N5 76
#define SCAN_N6 77
#define SCAN_GREY_PLUS 78
#define SCAN_N1 79
#define SCAN_N2 80
#define SCAN_N3 81
#define SCAN_INS 82
#define SCAN_DEL 83

#define	M_CHARSCAN
#endif
