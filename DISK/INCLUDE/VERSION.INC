; SCCS info:   Module version.inc  Version 1.1  Date 11/09/93  Time 16:16:18

; $Header:   T:/HH/INCLUDE/VCS/VERSION.INV   1.1   15 Oct 1992 10:52:58   KIM  $
;***
;version.inc - defines current memory model
;
;	Copyright (c) 1987-1988, Microsoft Corporation.  All rights reserved.
;
;Purpose:
;	This file defines the current memory model being used.
;
;*******************************************************************************
; $Log:   T:/HH/INCLUDE/VCS/VERSION.INV  $
;  
;     Rev 1.1   15 Oct 1992 10:52:58   KIM
;  * * * SERVER DISK CRASH RECOVERY * * *
;   1) The VCS directory was restored with Build 18 backup tape.
;   2) This revision is to update files to Build 19.
;   3) HELP.H has post-Build 19 changes.
;  
;     Rev 1.0   03 Dec 1991 20:14:32   DAVID
;  Initial revision.
;


?PLM=	0
?WIN=	0

ifdef	mem_s
	memS	equ	1	; small model
endif

ifdef	mem_m
	memM	equ	1	; medium model
endif

ifdef	mem_c
	memC	equ	1	; compact model
endif

ifdef	mem_l
	memL	equ	1	; large model
endif
