/* SCCS info:   Module mdit.h  Version 1.1  Date 11/09/93  Time 15:22:57 */

/* $Header:   T:/HH/INCLUDE/VCS/MDIT.H_V   1.1   15 Oct 1992 10:51:22   KIM  $ */
/****************************************************************
 *
 *	Copyright(c) 1990  Lotus Development Corporation
 *	All Rights Reserved
 *
 ****************************************************************/
/*
 * $Log:   T:/HH/INCLUDE/VCS/MDIT.H_V  $ 
 * 
 *    Rev 1.1   15 Oct 1992 10:51:22   KIM
 * * * * SERVER DISK CRASH RECOVERY * * *
 *  1) The VCS directory was restored with Build 18 backup tape.
 *  2) This revision is to update files to Build 19.
 *  3) HELP.H has post-Build 19 changes.
 * 
 *    Rev 1.0   03 Dec 1991 20:14:46   DAVID
 * Initial revision.
 *
 */




#ifndef MDITDATADEF

#ifndef EOL
/*
 *  multi-line edit data structure
 *
 */

typedef struct {
	char    far *m_buffer;    /*  user-supplied edit buffer  */
	int     m_length;         /*  length of buffer  */
	int     m_pos;            /*  current cursor position  */
	int     m_row, m_col;     /*  location of edit area  */
	int     m_nrows, m_ncols; /*  dimensions of edit area  */
	int	m_yoff,m_disprows;/*  current top row, number of rows displayable */
	char    m_ccol;           /*  cursor column  */
	char    m_modified;       /*  1 -> buffer has been modified  */
        char    m_xoff;           /*  1st disp. col (for ticker fields only)*/
        char    wrapflag;         /*  1 -> wordwrap enabled,-1 ticker field */
	int     far *m_line;      /*  pointer to array used for line starts */
				  /*     must be at least m_nrows+1 long */
	char 	markon;		  /* currenty marking? */
	char	spec_flag;
	int	markst;		  /* offset of start of mark, inclusive */
	int	markend;	  /* offset of end of mark, inclusive */
        int     m_dispcols;       /*  displayable columns */
} MDITDATA;


#define EOL       0
#endif

#define MDITDATADEF
#endif
