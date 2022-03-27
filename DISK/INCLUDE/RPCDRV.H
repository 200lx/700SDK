/* SCCS info:   Module rpcdrv.h  Version 1.1  Date 11/09/93  Time 15:24:44 */

/* $Header:   T:/hh/include/vcs/rpcdrv.h_v   1.5   12 Feb 1993 13:54:40   PAUL  $ */

/****************************************************************************
* RPCDRV.H                                                                  *
*      Copyright(c),1992 by Lotus Development Corporation                   *
*                                                                           *
*      DESCRIPTION:                                                         *
*      This is the header file for the RPC stub                             *
*                                                                           *
*                                                                           *
*****************************************************************************
* Version History                                                           *
* 05-Nov-92 EJP  Started.                                                   *
*                                                                           *
****************************************************************************/

/* $Log:   T:/hh/include/vcs/rpcdrv.h_v  $
 * 
 *    Rev 1.5   12 Feb 1993 13:54:40   PAUL
 * Ok, so we don't really need pszDescription.  We're going to just re-use 
 * pBuffer instead (on the RPCBatchSendMessage(), and RPCBatchReceiveMessage().
 * 
 *    Rev 1.4   12 Feb 1993 13:47:10   PAUL
 * Added pszDescription to both RPCBatchSend/ReceiveMessage()
 * 
 *    Rev 1.3   29 Jan 1993 10:54:08   PAUL
 * Added RPCActivate() and RPCDeactivate()
 * 
 *    Rev 1.2   27 Jan 1993 20:29:52   PAUL
 * 
 *    Rev 1.1   27 Jan 1993 19:39:52   PAUL
 * Added RPCBatchExtra()
 * 
 *    Rev 1.0   08 Dec 1992 01:11:06   PAUL
 * Initial revision.
 *
 */

#ifndef RPCDRV_H    // protection from being included twice
#define RPCDRV_H

/* Include Files */
/* ------------- */


#ifndef DSPTBLS_H   // protection from being included twice (it doesn't so we do)
#define DSPTBLS_H
#include <dsptbls.h>
#endif


/* Defines */
/* ------- */

#define RPC_CLASS_NAME     "RPC"    // class identifier
#define RPC_CLASS_LEN      3        // length of identifier

//
// replaceable function macros
//
#define RPC_FUNC_ID       0x0
#define RPC_FUNC_REMV     0x1
#define RPC_FUNC_INIT     0x2
#define RPC_FUNC_TERM     0x3
#define RPC_FUNC_QC       0x4
#define RPC_FUNC_CONN     0x5
#define RPC_FUNC_DISC     0x6
#define RPC_FUNC_SEND     0x7
#define RPC_FUNC_RECV     0x8
#define RPC_FUNC_BQD      0x9
#define RPC_FUNC_BSM      0xA
#define RPC_FUNC_BRM      0xB
#define RPC_FUNC_EXTRA    0xC
#define RPC_FUNC_ACTIV    0xD
#define RPC_FUNC_DEACT    0xE

#define RPC_CLASS_FUNCS   0xF      // number of functions in table

#define RPC_CLASS_BASE    gRpcFTnum * 256

#define RPC_CLASS_ID      RPC_CLASS_BASE + RPC_FUNC_ID
#define RPC_CLASS_REMV    RPC_CLASS_BASE + RPC_FUNC_REMV
#define RPC_CLASS_INIT    RPC_CLASS_BASE + RPC_FUNC_INIT
#define RPC_CLASS_TERM    RPC_CLASS_BASE + RPC_FUNC_TERM
#define RPC_CLASS_QC      RPC_CLASS_BASE + RPC_FUNC_QC
#define RPC_CLASS_CONN    RPC_CLASS_BASE + RPC_FUNC_CONN
#define RPC_CLASS_DISC    RPC_CLASS_BASE + RPC_FUNC_DISC
#define RPC_CLASS_SEND    RPC_CLASS_BASE + RPC_FUNC_SEND
#define RPC_CLASS_RECV    RPC_CLASS_BASE + RPC_FUNC_RECV
#define RPC_CLASS_BQD     RPC_CLASS_BASE + RPC_FUNC_BQD
#define RPC_CLASS_BSM     RPC_CLASS_BASE + RPC_FUNC_BSM
#define RPC_CLASS_BRM     RPC_CLASS_BASE + RPC_FUNC_BRM
#define RPC_CLASS_EXTRA   RPC_CLASS_BASE + RPC_FUNC_EXTRA
#define RPC_CLASS_ACTIV   RPC_CLASS_BASE + RPC_FUNC_ACTIV
#define RPC_CLASS_DEACT   RPC_CLASS_BASE + RPC_FUNC_DEACT

#define RPCClassId(pszId, nLen) \
         c_service(RPC_CLASS_ID, (char far *)pszId, (int)nLen)

#define RPCRemoveClass() \
         c_service(RPC_CLASS_REMV)

#define RPCInitialize(PRPCHandle, pszHostName) \
         c_service(RPC_CLASS_INIT, (PRPCHANDLE)PRPCHandle, (PFCHAR)pszHostName)

#define RPCTerminate(RPCHandle)               \
         c_service(RPC_CLASS_TERM, (RPCHANDLE)RPCHandle)

#define RPCQueryCapabilities(RPCHandle, usSelector, pData, usLen, pusReturnedLen) \
         c_service(RPC_CLASS_QC, (RPCHANDLE)RPCHandle, (USHORT)usSelector, (PFVOID)pData, (USHORT)usLen, (PFUSHORT)pusReturnedLen)

#define RPCConnect(RPCHandle, pszUserName, pszPassword, bMode) \
         c_service(RPC_CLASS_CONN, (RPCHANDLE)RPCHandle, (PFCHAR)pszUserName, (PFCHAR)pszPassword, (BYTE)bMode)

#define RPCDisconnect(RPCHandle)                     \
         c_service(RPC_CLASS_DISC, (RPCHANDLE)RPCHandle)

#define RPCSend(RPCHandle, pSendData, usSendSize, usBytesWritten) \
         c_service(RPC_CLASS_SEND, (RPCHANDLE)RPCHandle, (PFVOID)pSendData, (USHORT)usSendSize, (PFUSHORT)usBytesWritten)

#define RPCRecv(RPCHandle, pRecvData, usRecvSize, usBytesRead) \
         c_service(RPC_CLASS_RECV, (RPCHANDLE)RPCHandle, (PFVOID)pRecvData, (USHORT)usRecvSize, (PFUSHORT)usBytesRead)

#define RPCBatchQueryDirection(RPCHandle, usDirection) \
         c_service(RPC_CLASS_BQD, (RPCHANDLE)RPCHandle, (PFUSHORT)usDirection)

#define RPCBatchSendMessage(RPCHandle, pMsgPointers, pMsgBuffer) \
         c_service(RPC_CLASS_BSM, (RPCHANDLE)RPCHandle, (PFCHAR)pMsgPointers, (PFCHAR)pMsgBuffer)

#define RPCBatchReceiveMessage(RPCHandle, pMsgPointers, pMsgBuffer, usMsgBufferSize) \
         c_service(RPC_CLASS_BRM, (RPCHANDLE)RPCHandle, (PFCHAR)pMsgPointers, (PFCHAR)pMsgBuffer, (USHORT)usMsgBufferSize)

#define RPCBatchExtra(RPCHandle) \
         c_service(RPC_CLASS_EXTRA, (RPCHANDLE)RPCHandle)

#define RPCActivate(RPCHandle) \
         c_service(RPC_CLASS_ACTIV, (RPCHANDLE)RPCHandle)

#define RPCDeactivate(RPCHandle) \
         c_service(RPC_CLASS_DEACT, (RPCHANDLE)RPCHandle)


/* Typedefs */
/* -------- */

//
// replaceable function table
//
typedef struct
{
   FNCTTBLHEADER Hdr;
   int (near *Func[RPC_CLASS_FUNCS])(void);

} FUNCTION_TABLE;


//
// replaceable function stack adjustment for C routines
//
typedef struct
{
   UCHAR Dummy[18];

} STACK_ADJ;


extern UCHAR gRpcFTnum;  // must be allocated by calling app


#endif  // RPCDRV_H

