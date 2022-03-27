/* SCCS info:   Module rpc.h  Version 1.1  Date 11/09/93  Time 15:24:31 */

/* $Header:   T:/hh/include/vcs/rpc.h_v   1.33   20 Feb 1993 17:51:40   PAUL  $ */

/****************************************************************************
* RPC.H                                                                     *
*      Copyright(c),1992 by Lotus Development Corporation                   *
*                                                                           *
*      USAGE:  RPC Header file.                                             *
*                                                                           *
*      DESCRIPTION:                                                         *
*       Main RPC Transport driver for cc:Mail for Cougar                    *
*                                                                           *
*       This file is to be used with all RPC drivers for Cougar             *
*                                                                           *
*****************************************************************************
* Version History                                                           *
* 12-Jun-92 PJG  Started.                                                   *
*                                                                           *
****************************************************************************/

/* $Log:   T:/hh/include/vcs/rpc.h_v  $
 * 
 *    Rev 1.33   20 Feb 1993 17:51:40   PAUL
 * Made RPCSEL_NEGOTIDLETIMEOUT to be 666 (nice number 'eh?)  This ensures
 * that it is out of the range of VIM selectors.
 * 
 *    Rev 1.32   19 Feb 1993 14:57:34   PAUL
 * Ok, I did need MAXHOSTLENGTH after all.  It's back.
 * 
 *    Rev 1.31   19 Feb 1993 14:48:02   PAUL
 * Removed MAXHOSTNAMELEN and MAXPASSWORDLEN (they weren't used anywhere).
 * 
 *    Rev 1.30   19 Feb 1993 14:40:00   PAUL
 * Added RPCSEL_NEGOTIDLETIMEOUT
 * 
 *    Rev 1.29   12 Feb 1993 15:41:50   PAUL
 * Added RPCSTS_MSGNOTRECV
 * 
 *    Rev 1.28   02 Feb 1993 18:48:50   PAUL
 * Added RPCSTS_BATCHNOTSUPPORTED
 * 
 *    Rev 1.27   27 Jan 1993 19:38:48   PAUL
 * Added RPCSTS_FILTERFAILED, 
 * Added RPCSEL_EXTRA
 * 
 *    Rev 1.26   24 Jan 1993 17:35:18   PAUL
 * Added RPCSTS_BADRESOURCEFILE
 * 
 *    Rev 1.25   23 Jan 1993 09:23:56   DON
 * 
 *    Rev 1.24   23 Jan 1993 08:25:26   DON
 * Changed range of error codes, added RF constant.
 * 
 *    Rev 1.23   18 Jan 1993 18:32:08   PAUL
 * Added RPCSTS_BADPASSWORD
 * 
 *    Rev 1.22   15 Jan 1993 12:53:54   PAUL
 * On second thought, make RPCSTS_DATACONNLOST same as RPCSTS_DATACONNECTIONLOST
 * 
 *    Rev 1.21   15 Jan 1993 12:47:34   PAUL
 * Removed RPCSTS_DATACONNLOST
 * 
 *    Rev 1.20   14 Dec 1992 11:46:32   PAUL
 * New PFMSGPOINTERS (using offsets instead of pointers)
 * 
 *    Rev 1.19   08 Dec 1992 01:03:54   PAUL
 * Replaceable driver changes (major)
 * 
 *    Rev 1.15   30 Oct 1992 14:10:18   PAUL
 * Removed #define OS2 
 * 
 *    Rev 1.14   15 Oct 1992 11:15:42   PAUL
 * No change.
 * 
 *    Rev 1.13   15 Oct 1992 10:52:12   KIM
 * * * * SERVER DISK CRASH RECOVERY * * *
 *  1) The VCS directory was restored with Build 18 backup tape.
 *  2) This revision is to update files to Build 19.
 *  3) HELP.H has post-Build 19 changes.
 * 
 *    Rev 1.13   12 Oct 1992 13:18:24   PAUL
 * QueryCapabilities() had PVOID, changed to PFVOID.
 * 
 *    Rev 1.12   27 Sep 1992 15:46:38   PAUL
 * Send,Recv,Query now take far ptrs.
 * 
 *    Rev 1.11   26 Sep 1992 17:38:34   PAUL
 * Added some status codes
 * 
 *    Rev 1.10   11 Sep 1992 14:42:40   PAUL
 * Added RPCSTS_RECEIVECOMPLETE
 * 
 *    Rev 1.9   10 Sep 1992 15:15:00   PAUL
 * Changed some arguments to far pointers.
 * 
 *    Rev 1.8   10 Sep 1992 10:59:04   PAUL
 * Added direction as parameter in QueryBatchDirection
 * 
 *    Rev 1.7   10 Sep 1992 10:48:32   PAUL
 * Added prototypes for Batch routines.
 * 
 *    Rev 1.6   09 Sep 1992 20:17:38   PAUL
 * Added selector values for Batch sending/receiving.
 * 
 *    Rev 1.5   09 Sep 1992 16:11:52   PAUL
 * Removed duplicate RPCConnect().
 * 
 *    Rev 1.4   09 Sep 1992 16:02:52   PAUL
 * Added UserName and Password to RPCConnect()
 * 
 *    Rev 1.3   02 Sep 1992 17:25:36   PAUL
 * Added RPCSTS_INIERROR
 * 
 *    Rev 1.2   13 Aug 1992 12:19:52   PAUL
 * Fixed MYBOOL for compiling under OS/2
 * 
 *    Rev 1.1   13 Aug 1992 12:13:46   PAUL
 * BOOL -> MYBOOL
 * 
 *    Rev 1.0   07 Aug 1992 16:49:16   PAUL
 * Initial revision.
 *
 */

#ifndef RPC_H    // protection from being included twice
#define RPC_H


/* Include Files */
/* ------------- */


/* Defines */
/* ------- */

#define VOID   void
#define CHAR   char
#define SHORT  short
#define LONG   long

typedef unsigned char  UCHAR;
typedef unsigned short USHORT;
typedef unsigned long  ULONG;
typedef unsigned char  BYTE;
typedef unsigned char  MYBOOL;

typedef CHAR   *PCHAR;
typedef SHORT  *PSHORT;
typedef LONG   *PLONG;
typedef UCHAR  *PUCHAR;
typedef USHORT *PUSHORT;
typedef ULONG  *PULONG;
typedef BYTE   *PBYTE;
typedef VOID   *PVOID;
typedef MYBOOL *PMYBOOL;

typedef CHAR   _far *PFCHAR;
typedef SHORT  _far *PFSHORT;
typedef LONG   _far *PFLONG;
typedef UCHAR  _far *PFUCHAR;
typedef USHORT _far *PFUSHORT;
typedef ULONG  _far *PFULONG;
typedef BYTE   _far *PFBYTE;
typedef VOID   _far *PFVOID;
typedef MYBOOL _far *PFMYBOOL;

#ifndef NULL
#define NULL 0
#endif // NULL

#ifndef FALSE
#define FALSE  0
#endif // FALSE

#ifndef TRUE
#define TRUE   1
#endif // TRUE

#define RPC_FALSE     0
#define RPC_TRUE      1


#define MAXHOSTLENGTH 50


// Macros to get values

#define LOBYTE(w)	LOUCHAR(w)
#define HIBYTE(w)	HIUCHAR(w)
#define LOUCHAR(w)	((UCHAR)(USHORT)(w))
#define HIUCHAR(w)	((UCHAR)(((USHORT)(w) >> 8) & 0xff))
#define LOUSHORT(l)	((USHORT)(ULONG)(l))
#define HIUSHORT(l)	((USHORT)(((ULONG)(l) >> 16) & 0xffff))


// Selector Values

#define RPCSEL_BATCH                 0      // RPCQueryCapabilites() selectors
#define RPCSEL_INTERACTIVE           1
#define RPCSEL_NEGOTIDLETIMEOUT      666    // Make sure this is out of range of VIM selectors.

#define RPCSEL_SENDING               0      // RPCBatchSend/RecvMessage() selectors
#define RPCSEL_RECEIVING             1
#define RPCSEL_EXTRA                 2
#define RPCSEL_COMPLETE              3


// RPC Status values

#ifndef VIMSTS_COMM_ERR
  #define VIMSTS_COMM_ERR            0xF000
#endif

#define RPCSTS_SUCCESS               0x0000
#define RPCSTS_FAILURE               (VIMSTS_COMM_ERR | 0x0001)
#define RPCSTS_FATAL                 (VIMSTS_COMM_ERR | 0x0002)
#define RPCSTS_BADPARAM              (VIMSTS_COMM_ERR | 0x0003)
#define RPCSTS_BUF_TOO_SMALL         (VIMSTS_COMM_ERR | 0x0004)
#define RPCSTS_INVALID_SELECTOR      (VIMSTS_COMM_ERR | 0x0005)
#define RPCSTS_INSUFFICIENT_MEMORY   (VIMSTS_COMM_ERR | 0x0006)
#define RPCSTS_INITIALIZING          (VIMSTS_COMM_ERR | 0x0007)
#define RPCSTS_UNINITIALIZING        (VIMSTS_COMM_ERR | 0x0008)
#define RPCSTS_TIMEOUT               (VIMSTS_COMM_ERR | 0x0009)
#define RPCSTS_NOTSUPPORTED          (VIMSTS_COMM_ERR | 0x000A)
#define RPCSTS_CONNREJECTED          (VIMSTS_COMM_ERR | 0x000B)
#define RPCSTS_CONNECTIONNOTACCEPTED (VIMSTS_COMM_ERR | 0x000C)
#define RPCSTS_BADCRCFIRSTPART       (VIMSTS_COMM_ERR | 0x000D)
#define RPCSTS_BADCRCSECONDPART      (VIMSTS_COMM_ERR | 0x000E)
#define RPCSTS_WRONGPOCALLED         (VIMSTS_COMM_ERR | 0x000F)
#define RPCSTS_DATACONNECTIONLOST    (VIMSTS_COMM_ERR | 0x0010)
#define RPCSTS_VIMIRNOTSUPPORTED     (VIMSTS_COMM_ERR | 0x0011)
#define RPCSTS_DATACONNLOST          RPCSTS_DATACONNECTIONLOST  // Same as RPCSTS_DATACONNECTIONLOST
#define RPCSTS_CANTNEGOTIATE         (VIMSTS_COMM_ERR | 0x0012)
#define RPCSTS_INIERROR              (VIMSTS_COMM_ERR | 0x0013)
#define RPCSTS_RECEIVECOMPLETE       (VIMSTS_COMM_ERR | 0x0014)
#define RPCSTS_MSGNOTSENT            (VIMSTS_COMM_ERR | 0x0015)
#define RPCSTS_NOTSENDING            (VIMSTS_COMM_ERR | 0x0016)
#define RPCSTS_NOTRECVING            (VIMSTS_COMM_ERR | 0x0017)
#define RPCSTS_BADPASSWORD           (VIMSTS_COMM_ERR | 0x0018)
#define RPCSTS_BADRESOURCEFILE       (VIMSTS_COMM_ERR | 0x0019)
#define RPCSTS_FILTERFAILED          (VIMSTS_COMM_ERR | 0x001A)
#define RPCSTS_BATCHNOTSUPPORTED     (VIMSTS_COMM_ERR | 0x001B)
#define RPCSTS_MSGNOTRECV            (VIMSTS_COMM_ERR | 0x001C)




/* Typedefs */
/* -------- */


#pragma pack(1)

//
// Message Pointers 
//

typedef struct _MSGPOINTERS
{
    PFVOID pStart;      // Far pointer to start of message buffer
    USHORT usFrom;      // Offset to From field
    USHORT usDate;      // Offset to Date field
    USHORT usSubject;   // Offset to Subject field
    USHORT usTo;        // Offset to To field
    USHORT usCc;        // Offset to Cc field
    USHORT usBcc;       // Offset to Bcc field
    USHORT usBody;      // Offset to Body field (or filename)
    USHORT usAttach;    // Offset to Attachment filenames field
    MYBOOL fBodyFile;   // TRUE if body in file, FALSE if in msg buffer

} MSGPOINTERS;

typedef MSGPOINTERS *PMSGPOINTERS;
typedef MSGPOINTERS _far *PFMSGPOINTERS;


//
// RPC Handle
//

typedef struct _RPCSTRUCT
{
    CHAR pszHostName[MAXHOSTLENGTH];   // HostName found in MAIL.INI; ex: Lotus-CAD
    void _far **pConnectInfo;     // Driver Specific info retrieved from MAIL.INI
                                  // ConnectInfo will vary with transport driver
} RPCSTRUCT;

typedef RPCSTRUCT _far **RPCHANDLE;
typedef RPCHANDLE _far *PRPCHANDLE;

#pragma pack()



#include <rpcdrv.h>


#endif // RPC_H
