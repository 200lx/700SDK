/* SCCS info:   Module dsptbls.h  Version 1.1  Date 11/09/93  Time 15:18:37 */

/****************************************************************************
  $Header:   T:/HH/INCLUDE/VCS/DSPTBLS.H_V   1.2   15 Oct 1992 10:49:58   KIM  $
 ****************************************************************************
  COUGAR / DIAMOND SYSMGR
 
  Copyright(c) 1992
  Lotus Development Corporation
  All Rights Reserved
 
  DspTbls.Mac - New SM API Dispatch Tables Header

  NOTE: This file must stay in sync with DSPTBLS.MAC.
 
 ****************************************************************************
  $Log:   T:/HH/INCLUDE/VCS/DSPTBLS.H_V  $
 * 
 *    Rev 1.2   15 Oct 1992 10:49:58   KIM
 * * * * SERVER DISK CRASH RECOVERY * * *
 *  1) The VCS directory was restored with Build 18 backup tape.
 *  2) This revision is to update files to Build 19.
 *  3) HELP.H has post-Build 19 changes.
 * 
 *    Rev 1.1   29 Jul 1992 12:59:14   HOMI
 * Replaced field Flag with StartAbs
 * 
 *    Rev 1.0   22 Jun 1992 20:02:34   KIM
 * .H version created from DSPTBLS.MAC.  RIB.EXE uses this .H file.
   
      Rev 1.0   09 Jun 1992 10:40:50   HOMI
   Initial revision.
 ****************************************************************************/

typedef struct
{
    unsigned char   FTH_Num;        /* Class number                         */
//  unsigned char   FTH_Flag;       /* Bit 0 set on disables table          */
    unsigned char   FTH_StartAbs;   /* Constant start position              */
    unsigned long   FTH_NextTbl;    /* far pointer to next table            */
    unsigned int    FTH_CS;         /* code segment of functions in table   */
    unsigned char   FTH_RamPg;      /* ram page                             */
    unsigned char   FTH_RomPg;      /* rom page                             */
    unsigned char   FTH_RomDev;     /* rom device id                        */
    unsigned char   FTH_Pages;      /* pages to map                         */
    unsigned char   FTH_Start;      /* first function number in table       */
    unsigned char   FTH_End;        /* last function number in table        */
} FNCTTBLHEADER;
