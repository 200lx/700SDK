/* SCCS info:   Module ccvrext.h  Version 1.1  Date 11/09/93  Time 15:15:30 */

/* $Header:   T:/hh/include/vcs/ccvrext.h_v   1.13   25 Feb 1993 10:45:02   DON  $ */
/**************************************************************************
 *
 *  Name:       T:\HH\LIB\VIMREQ\CCVREXT.H
 *  Date:       Friday June 19, 1992
 *  Abstract:   Contains headers for the cc:Mail and Lotus extensions 
 *              to VIM.
 *
 * ------------------------------------------------------------------------
 *                   Copyright 1992 Lotus Development Corp.
 *                           All rights reserved.
 **************************************************************************
 *
 * $Log:   T:/hh/include/vcs/ccvrext.h_v  $
 * 
 *    Rev 1.13   25 Feb 1993 10:45:02   DON
 * Added boolean to VimTransferMessage prototype.
 * 
 *    Rev 1.12   19 Feb 1993 14:48:50   DON
 * Added prototype for VIMPing().
 * 
 *    Rev 1.11   30 Jan 1993 12:18:58   DON
 * Added VIMActivate and VIMDeactivate.
 * 
 *    Rev 1.10   23 Jan 1993 08:26:38   DON
 * Moved error code masks to rpc.h and loadclas.h
 * 
 *    Rev 1.9   23 Jan 1993 07:55:50   DON
 * Added VIMSTS_CLASS_ERR.
 * 
 *    Rev 1.8   21 Dec 1992 12:14:26   DON
 * Added 2 system manager call prototypes.
 * 
 *    Rev 1.7   15 Dec 1992 13:26:08   DON
 * Added bit mask for error masking.
 * 
 *    Rev 1.6   24 Nov 1992 14:13:34   DON
 * 
 *    Rev 1.5   24 Nov 1992 14:11:50   DON
 * Added VIMOpenGatewaySession prototype.
 * 
 *    Rev 1.4   24 Nov 1992 14:09:34   EDM
 * No change.
 * 
 *    Rev 1.3   05 Nov 1992 09:38:28   DON
 * Added extension prototype.
 * 
 *    Rev 1.2   30 Oct 1992 15:15:48   DON
 * Added 2 extension prototypes.
 * 
 *    Rev 1.1   26 Oct 1992 14:14:30   DON
 * Added VimTransferMessage prototype.
 * 
 *    Rev 1.0   26 Oct 1992 13:25:24   DON
 * Initial revision.
 * 
 *    Rev 1.5   26 Oct 1992 13:19:02   DON
 * Added several prototypes.
 * 
 *    Rev 1.4   22 Oct 1992 19:38:10   DON
 * Added VIMRemoveCategory prototype
 * 
 *    Rev 1.3   19 Oct 1992 09:18:34   DON
 * Added comm error code mask.
 * 
 *    Rev 1.2   17 Jul 1992 13:07:52   EDM
 * 
 *    Rev 1.0   19 Jun 1992 17:32:10   KENT
 * Initial revision.
 *
 **************************************************************************/

vimStatus VIMAPIENTRY VIMSetMessageCategory(vimMsgContainer msgContr,
                                            vimRef msgRef,
                                            vimStringPtr psCatName);

vimStatus VIMAPIENTRY VIMRemoveMessageCategory(vimMsgContainer msgContr,
                                            vimRef msgRef,
                                            vimStringPtr psCatName);

vimStatus VIMAPIENTRY VIMRemoveCategory(vimMsgContainer msgContr,
                                        vimStringPtr psCatName,
                                        vimBool remIfNotEmpty);

vimStatus VIMAPIENTRY VIMDeliverMessage(  vimMsg message,
                                       vimDataPtr pCallbackParam,
                                       vimSendCallback callBack );

vimStatus VIMAPIENTRY VIMDeleteMessageItem(vimMsg msgID,
                                           vimSelector itemClass);

vimStatus VIMAPIENTRY VIMDeleteMessageRecipient(vimMsg msgID,
                                                vimSelector recipClass);

vimStatus VIMAPIENTRY VIMOpenGatewaySession(	vimStringPtr psPathSpec, 
                                             vimStringPtr psName, 
                                             vimStringPtr psPass, 
                                             vimDWord dwVersion,
                                             vimSelector selCharSet,
                                             vimSesPtr pSession);

vimStatus VimTransferMessage(vimMsgContainer srcMsgContainer,
                                    vimRef srcMsgReference,
                                    vimStringPtr srcCategoryName,
                                    vimMsgContainer targetMsgContainer,
                                    vimStringPtr targetCategoryName,
                                    vimBool msgUnread);

vimStatus VIMAPIENTRY VIMDeleteCategoryRef(vimMsgContainer msgContr, 
                                     vimRef refParent,
                                     vimStringPtr psCatName);

vimStatus VIMAPIENTRY VIMGetParentRef(vimMsgContainer msgContr, 
                                     vimRef refChild,
                                     vimRefPtr prefParent);

vimStatus VIMAPIENTRY VIMReplaceMessage(vimMsgContainer msgContr, 
                                     vimRef msgRef,
                                     vimMsg msgID);

vimStatus VIMAPIENTRY VIMPing();

vimStatus VIMAPIENTRY VIMActivate();

vimStatus VIMAPIENTRY VIMDeactivate();

#define VIMSTS_COMM_MASK   0x0FFF

// Prototypes for wrapper functions that reside in cc:Mail root code.
// These functions are used by overlay modules to make system manager calls.
vimStatus ccmGetFarBlock( void *nearHandle, unsigned long numBytes);
vimStatus ccmSetFarBlock( void *nearHandle, unsigned long int numBytes);

