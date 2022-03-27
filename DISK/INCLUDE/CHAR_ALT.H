/* SCCS info:   Module char_alt.h  Version 1.1  Date 11/09/93  Time 15:15:57 */

/* $Header:   T:/HH/INCLUDE/VCS/CHAR_ALT.H_V   1.1   15 Oct 1992 10:48:40   KIM  $ */
/****************************************************************
 *
 *	Copyright(c) 1990  Lotus Development Corporation
 *	All Rights Reserved
 *
 ****************************************************************/

/****************************************************************
TradeWind key data codes for some Alt'd keyboard keys

[Alt'd Function Keys are defined in CHARCODE.H]
****************************************************************/

/*
 * $Log:   T:/HH/INCLUDE/VCS/CHAR_ALT.H_V  $ 
 * 
 *    Rev 1.1   15 Oct 1992 10:48:40   KIM
 * * * * SERVER DISK CRASH RECOVERY * * *
 *  1) The VCS directory was restored with Build 18 backup tape.
 *  2) This revision is to update files to Build 19.
 *  3) HELP.H has post-Build 19 changes.
 * 
 *    Rev 1.0   03 Dec 1991 20:14:34   DAVID
 * Initial revision.
 *
 */


#ifndef	M_CHAR_ALT

#define ALT_1 (-120)
#define ALT_2 (-121)
#define ALT_3 (-122)
#define ALT_4 (-123)
#define ALT_5 (-124)
#define ALT_6 (-125)
#define ALT_7 (-126)
#define ALT_8 (-127)
#define ALT_9 (-128)
#define ALT_0 (-129)

/*	#define ALT_- (-130)	*/	/* Generates compilation error */
#define	ALT_MINUS (-130)
#define	ALT_dash  (-130)		/* ...for Bob */

#define ALT_Q (-16)
#define ALT_W (-17)
#define ALT_E (-18)
#define ALT_R (-19)
#define ALT_T (-20)
#define ALT_Y (-21)
#define ALT_U (-22)
#define ALT_I (-23)
#define ALT_O (-24)
#define ALT_P (-25)
#define ALT_A (-30)
#define ALT_S (-31)
#define ALT_D (-32)
#define ALT_F (-33)
#define ALT_G (-34)
#define ALT_H (-35)
#define ALT_J (-36)
#define ALT_K (-37)
#define ALT_L (-38)
#define ALT_Z (-44)
#define ALT_X (-45)
#define ALT_C (-46)
#define ALT_V (-47)
#define ALT_B (-48)
#define ALT_N (-49)
#define ALT_M (-50)

#define	M_CHAR_ALT
#endif
