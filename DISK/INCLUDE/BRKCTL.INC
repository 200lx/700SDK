; SCCS info:   Module brkctl.inc  Version 1.1  Date 11/09/93  Time 16:15:42

; $Header:   T:/HH/INCLUDE/VCS/BRKCTL.INV   1.1   15 Oct 1992 10:52:40   KIM  $
;*****************************************************************************
;brkctl.inc - definitions and structure for brkctl
;
;	Copyright (c) 1987-1988, Microsoft Corporation.  All rights reserved.
;
;Purpose:
;	The file contains brkctl command values and structure
;	definitions.
;
;*******************************************************************************
; $Log:   T:/HH/INCLUDE/VCS/BRKCTL.INV  $
;  
;     Rev 1.1   15 Oct 1992 10:52:40   KIM
;  * * * SERVER DISK CRASH RECOVERY * * *
;   1) The VCS directory was restored with Build 18 backup tape.
;   2) This revision is to update files to Build 19.
;   3) HELP.H has post-Build 19 changes.
;  
;     Rev 1.0   03 Dec 1991 20:14:32   DAVID
;  Initial revision.
;

BR_ARGSEG= 1			; specified segment
BR_NEWSEG= 2			; new segment
BR_IMPSEG= 3			; last or new segment

MAXSEG=	20			; maximum brkctl segments for REAL mode
MAXSEG_PM =	64		; maximum brkctl segments for PROTECTED mode

segrec	struc			; defines brkctl segment offsets
	sz	dw      ?
	sg	dw      ?
segrec	ends

heaprec	struc			; defines heap descriptor offsets
	bottom	dw      ?
	roveroff dw      ?
	last	dw      ?
	top	dw      ?
	nextseg	dw      ?
heaprec	ends
