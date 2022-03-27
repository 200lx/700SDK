/* SCCS info:   Module video.h  Version 1.1  Date 11/09/93  Time 15:25:45 */

/* $Header:   T:/HH/INCLUDE/VCS/VIDEO.H_V   1.2   12 Nov 1992 18:40:56   KIM  $ */
/***************************************************************************
 *                  Copyright 1992 Lotus Development Corp.
 *                          All rights reserved.
 ***************************************************************************
 * $Log:   T:/HH/INCLUDE/VCS/VIDEO.H_V  $
 * 
 *    Rev 1.2   12 Nov 1992 18:40:56   KIM
 * I will attempt to centralize all video related information into this file.
 * Currently, it contains info from sysmgr\vidphy.mac.  I hope to have the
 * various parts of Sys Mgr and Task0 use this file instead of hardcoding
 * various constants and/or defining new equates for video constants.
 * 
 *    Rev 1.1   15 Oct 1992 10:52:26   KIM
 * * * * SERVER DISK CRASH RECOVERY * * *
 *  1) The VCS directory was restored with Build 18 backup tape.
 *  2) This revision is to update files to Build 19.
 *  3) HELP.H has post-Build 19 changes.
 * 
 *    Rev 1.0   17 Aug 1992 17:04:50   VAISHALI
 * Initial revision.
 * 
 */

#define VIRTSCREENCOLS          80
#define VIRTSCREENROWS	        25

#define NUMSCREENCOLS	        80
#define NUMSCREENROWS	        25

#define PHYSSCREENCOLS	        80
#define ATTRDIRTY	            0x80
#define GR_BYTES_PER_LINE       80

#define DT_TEXT                 1
#define DT_GRAPH                2
#define AT_MDA                  0
#define AT_CGA                  1
#define MDA_SEG                 0x0B000
#define CGA_SEG                 0x0B800
#define VGA_SEG                 0x0A000

#ifdef TSR
    #define VIDEOGRSEG          VGA_SEG
    #define VIDEOBASE           ((void far *)VGA_SEG << 16)
#else
 #ifdef EMUL
    #define VIDEOGRSEG          CGA_SEG
    #define VIDEOBASE           ((void far *)CGA_SEG << 16)
 #else
    #define VIDEOGRSEG          CGA_SEG
    #define VIDEOBASE           ((void far *)CGA_SEG << 16)
 #endif
#endif
