/* SCCS info:   Module vimext.h  Version 1.1  Date 11/09/93  Time 15:26:09 */

/* VIMEXT.H is the public header file for cc:Mail specific VIM extensions */

#ifndef __VIMEXT_H
#define __VIMEXT_H

#define VIMSEL_CATEGORY		256L
#define VIMSEL_LOCATION		257L
#define VIMSEL_DIALIN			259L
#define VIMSEL_REMOTE			260L
#define VIMSEL_FAN				261L
#define VIMSEL_RECIP_STATUS	262L
#define VIMSEL_SENT_TO			263L
#define VIMSEL_SENT_CC			264L
#define VIMSEL_SENT_BCC		265L
#define VIMSEL_MSG_LEN			266L
#define VIMSEL_UNDELIVERED		267L

vimStatus VIMAPIENTRY VIMOpenGatewaySession(	vimStringPtr psPathSpec,
												vimStringPtr psPostOffice,
												vimStringPtr psPass,
												vimDWord dwVersion,
												vimSelector selCharSet,
												vimSesPtr pSession);

vimStatus VIMAPIENTRY VIMRemoveMessageCategory(	vimMsgContainer msgContr,
													vimRef msgRef,
													vimStringPtr psCatName);

vimStatus VIMAPIENTRY VIMSetMessageCategory(	vimMsgContainer msgContr,
												vimRef msgRef,
												vimStringPtr psCatName);

vimStatus VIMAPIENTRY VIMAddressAndSend( 	vimDWord dwUIParam,
											vimDataPtr msg,
											vimDWord dwReserved);
#endif	// __VIMEXT_H

