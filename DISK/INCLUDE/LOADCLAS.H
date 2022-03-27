/* SCCS info:   Module loadclas.h  Version 1.1  Date 11/09/93  Time 15:21:38 */

/* $Header:   T:/hh/include/vcs/loadclas.h_v   1.2   23 Jan 1993 10:45:58   DON  $ */

/****************************************************************************
* LOADCLAS.H                                                                *
*      Copyright(c),1992 by Lotus Development Corporation                   *
*                                                                           *
*      DESCRIPTION:                                                         *
*      This is the header for rpc class routines                            *
*                                                                           *
*                                                                           *
*****************************************************************************
* Version History                                                           *
* 27-Oct-92 EJP  Started.                                                   *
*                                                                           *
****************************************************************************/

/* $Log:   T:/hh/include/vcs/loadclas.h_v  $
 * 
 *    Rev 1.2   23 Jan 1993 10:45:58   DON
 * 
 *    Rev 1.1   23 Jan 1993 08:21:08   DON
 * Converted error codes to include the VIMSTS_CLASS_ERR value.
 * 
 *    Rev 1.0   21 Jan 1993 10:33:24   DON
 * Initial revision.
 *
 */


/* Include Files */
/* ------------- */


/* Defines */
/* ------- */
// These error codes are in the same range (0xF000-0xFFFF) as the RPC codes
// but must be distinct from the general RPC errors.

#ifndef VIMSTS_COMM_ERR
  #define VIMSTS_COMM_ERR      0xF000
#endif

#define LCSTS_SUCCESS         0x0000
#define LCSTS_ERROR_OPEN      (VIMSTS_COMM_ERR | 0x0065)
#define LCSTS_ERROR_READ      (VIMSTS_COMM_ERR | 0x0066)
#define LCSTS_ERROR_MEM       (VIMSTS_COMM_ERR | 0x0067)
#define LCSTS_ERROR_LOAD      (VIMSTS_COMM_ERR | 0x0068)
#define LCSTS_ERROR_CLASS     (VIMSTS_COMM_ERR | 0x0069)
#define LCSTS_ERROR_INVALID   (VIMSTS_COMM_ERR | 0x006A)


/* Prototypes */
/* ---------- */

#if defined (TSR)

int LoadClass(char *szFilename, int nFnameLen, char *szClassName, int nClassLen, unsigned char *npClass, void near *near *npfpLoadAddr);
int UnloadClass(char *szClassName, int nClassLen, void near *near *npfpLoadAddr);

#else

int LoadClass(char *szFilename, int nFnameLen, char *szClassName, int nClassLen, unsigned char *npClass, void far *near *npfpLoadAddr);
int UnloadClass(char *szClassName, int nClassLen, void far *near *npfpLoadAddr);

#endif



