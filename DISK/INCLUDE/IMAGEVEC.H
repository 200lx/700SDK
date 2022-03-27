/* SCCS info:   Module imagevec.h  Version 1.1  Date 11/09/93  Time 15:20:08 */

/* $Header:   T:/HH/INCLUDE/VCS/IMAGEVEC.H_V   1.1   15 Oct 1992 10:50:50   KIM  $ */
/***************************************************************************
 *
 *  Name:       IMAGEVEC.H
 *  Date:       04/17/92
 *  Abstract:   ROM Image Vector definition
 *              This file is shared by the System Manager and the RIB.
 *
 * -------------------------------------------------------------------------
 *                  Copyright 1992 Lotus Development Corp.
 *                          All rights reserved.
 ***************************************************************************
 *
 * $Log:   T:/HH/INCLUDE/VCS/IMAGEVEC.H_V  $
 * 
 *    Rev 1.1   15 Oct 1992 10:50:50   KIM
 * * * * SERVER DISK CRASH RECOVERY * * *
 *  1) The VCS directory was restored with Build 18 backup tape.
 *  2) This revision is to update files to Build 19.
 *  3) HELP.H has post-Build 19 changes.
 * 
 *    Rev 1.0   17 Apr 1992 21:09:12   KIM
 * Initial revision.
 *
 ***************************************************************************/

#ifndef IMAGEVEC_H
#define IMAGEVEC_H

/*
 * Definitions for: IMAGEVEC.fType (bit flags are additive)
 */
#define IV_TYPE_NONE    0x00
#define IV_TYPE_CODE	0x01
#define IV_TYPE_DATA    0x02
#define IV_TYPE_RAM     0x10
#define IV_TYPE_RSRC    0x20
#define IV_TYPE_123     0x40
#define IV_TYPE_SYSMGR  0x80

/*
 * Image Vector structure.  This must match IMAGEVEC.MAC.
 */

typedef struct IMAGEVEC {
    unsigned char fType;            /* Image vector type. See IV_TYPE_?     */
	unsigned char fDataCmp;         /* 0: data seg not compressed; else 1   */
	unsigned long dwRS_StartCode;   /* ROM space code start location        */
	unsigned int  wRS_SizeCode;     /* ROM space code image size (para)     */
	unsigned long dwRS_StartData;   /* ROM space data start location        */
	unsigned int  wRS_SizeData;     /* ROM space data image size (para)     */
	unsigned int  wRS_SizeDataCmp;  /* ROM space data image cmp size (para) */
	unsigned long dwRS_StartFixUp;  /* ROM space fixup table location       */
	unsigned int  wNumFixUps;	    /* Number of fixed up                   */
	unsigned int  wFreeMemoryReq;   /* Free memory after image in paras     */
	unsigned int  wAS_Bank;		    /* Addr Space bank (segment)            */
	unsigned int  wAS_StartCode;	/* Addr Space code start (segment)      */
	unsigned int  wAS_StackOff;	    /* Addr Space stack offset              */
	unsigned int  wAS_StackSeg;	    /* Addr Space stack (segment)           */
	unsigned int  wAS_StartOff;	    /* Addr Space code start offset         */
	unsigned int  wAS_StartSeg;	    /* Addr Space code start (segment)      */
	unsigned int  wAS_RAMResv;	    /* Addr Space RAM to reserve (segment)  */
	unsigned int  wHotKey;		    /* Hot key                              */
	unsigned int  wExeDataSeg;      /* Data Seg from EXE header             */
	unsigned int  wCheckSum;		/* For Data Seg before run fixups       */
	char	      szName[13];		/* Image name (null terminated)         */
	unsigned char fPersistent;	    /* 0 normal, 1 if persistent            */
    unsigned int  wAS_PhyPage;      /* Addr Space: Page Id for Int 63h      */
    unsigned int  wRS_LogicalPage;  /* ROM  Space: Page Id for Int 63h      */
    unsigned int  wRS_PageCount;    /* ROM  Space: Page count for Int 63h   */
} IMAGEVEC;

#endif
