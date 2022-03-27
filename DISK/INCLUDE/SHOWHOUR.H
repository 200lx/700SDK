/* SCCS info:   Module showhour.h  Version 1.1  Date 11/09/93  Time 15:25:08 */

/* $Header:   T:/HH/INCLUDE/VCS/SHOWHOUR.H_V   1.0   11 Jan 1993 16:03:36   WEI-LEE  $ */
/**************************************************************************
 *
 *  Name:       C:\HH\TERM\SHOWHOUR.H
 *
 *  Date:       Monday January 11, 1993
 *
 *  Legal:      Copyright 1993 Lotus Development Corp.
 *              All rights reserved.
 *
 *  Abstract:   Show hourglass (from HP)
 *
 *  History:
 *      WLH 1/11/1993  Created.
 *
 ***********************************************************
 *
 * $Log:   T:/HH/INCLUDE/VCS/SHOWHOUR.H_V  $
 * 
 *    Rev 1.0   11 Jan 1993 16:03:36   WEI-LEE
 * Initial revision.
 * 
 **************************************************************************/
#if !defined(SHOWHOUR_H)
#define SHOWHOUR_H

/* Hourglass */

/* General notes:
   The hourglass functions are display only--HourglassOn and HourglassOff
   do not need to be matched to work properly.  HourglassOn saves the
   screen underneath where it appears so that HourglassOff can restore 
   it. This means that you need to be careful about calling HourglassOff 
   if you've updated the screen.  For example, if you call HourglassOn 
   to put up the hourglass, then repaint the screen, *don't* call 
   HourglassOff, or you'll put the old image back over your screen.
*/


/* HourglassOn takes a screen coordinate to display the image--
   using HourglassOn(-1,-1) displays the hourglass in the middle
   of the screen.
*/
void far HourglassOn(int x,int y);


/* Removes the hourglass */
void far HourglassOff(void);
#endif
