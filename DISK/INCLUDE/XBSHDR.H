/* SCCS info:   Module xbshdr.h  Version 1.1  Date 11/09/93  Time 15:26:43 */

#pragma pack(1)
/*
;The following structure describes the format of the DIAMOND
;view registration.
*/
typedef struct {
	vw_owner	unsigned char;	   /* TCB # of register of view */
	vw_index	unsigned char;	   /* View index set by owner.	*/
	vw_descr	unsigned char[32]; /* View description set by owner */
} S_VIEW;

#pragma pack()
