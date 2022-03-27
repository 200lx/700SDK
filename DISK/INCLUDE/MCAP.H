/* SCCS info:   Module mcap.h  Version 1.1  Date 11/09/93  Time 15:22:42 */

/* $Header:   T:/hh/include/vcs/mcap.h_v   1.28   03 Mar 1993 23:56:50   DON  $ */
/**************************************************************************
 *
 *  Name:       T:\HH\LIB\MCAP\MCAP.H
 *  Date:       Wednesday June 17, 1992
 *  Abstract:   Types and defines for local mail database management.
 *
 * ------------------------------------------------------------------------
 *                   Copyright 1992 Lotus Development Corp.
 *                           All rights reserved.
 **************************************************************************
 *
 * $Log:   T:/hh/include/vcs/mcap.h_v  $
 * 
 *    Rev 1.28   03 Mar 1993 23:56:50   DON
 * Increased MCAP buffer size to 21K, to match VR buffer size.
 * 
 *    Rev 1.27   16 Feb 1993 14:36:20   ROGER
 * Added the routine prototype MCAPGetNewMsgRef().
 * 
 *    Rev 1.26   10 Jan 1993 16:14:34   ROGER
 * Added a new variable to the container structure.  This variable is
 * used for tracking new messages for use by the QueryNewMessages function.
 * 
 *    Rev 1.25   16 Dec 1992 16:38:16   ROGER
 * Added structures for MCAP internal representation of VIM recipients.
 * 
 *    Rev 1.24   12 Dec 1992 03:31:32   ROGER
 * Modified the container structures to fix problems with folder management.
 * 
 *    Rev 1.23   19 Nov 1992 10:38:04   ROGER
 * Added countof macro.
 * 
 *    Rev 1.22   17 Nov 1992 05:02:56   ROGER
 * Lots of miscellaneous changes.
 * 
 *    Rev 1.21   02 Nov 1992 16:54:22   ROGER
 * Added function prototypes for new local functions and the new MCAP function
 * MCAPReplaceMessage().
 * 
 *    Rev 1.20   30 Oct 1992 13:41:36   WEI-LEE
 * Removed def_container variable.
 * 
 *    Rev 1.19   30 Oct 1992 11:51:56   ROGER
 * Added function prototypes for MCAPGetParentRef & MCAPDeleteCategoryRef.
 * 
 *    Rev 1.18   30 Oct 1992 11:28:12   WEI-LEE
 * Added function prototype.
 * 
 *    Rev 1.17   30 Oct 1992 09:35:00   ROGER
 * Added function prototypes for new utiltiy functions.
 * 
 *    Rev 1.16   28 Oct 1992 16:19:02   ROGER
 * Changed the lengths of the message and item types back
 * to 32 and 20 respectively.
 * 
 *    Rev 1.15   28 Oct 1992 15:45:28   WEI-LEE
 * Modified function prototypes.
 * 
 *    Rev 1.14   28 Oct 1992 11:33:10   ROGER
 * Moved definition of VIM_MSGTYPE_LEN and VIM_ITEMTYPE_LEN from VIMLCL.H
 * into this module.  Changed the value of these constants to be identical
 * (required for QueryCapabilities) and set = to 64 for VIM conformance.
 * Added the VIM_MAX_TYPE_LEN to use in the capabilities table.  Also, moved
 * MCAP_SUBJECT_LEN from VIMLCL.H to this module.
 * 
 *    Rev 1.13   26 Oct 1992 10:46:10   ROGER
 * Added function prototypes for MCAPDeleteMessageItem and
 * MCAPDeleteMessageRecipient.
 * 
 *    Rev 1.12   26 Oct 1992 10:19:46   WEI-LEE
 * Changed MCAP_MSG_MAXLEN and MCAP_ITEM_MAXLEN to 20K.
 * Added some function prototypes.
 * 
 *    Rev 1.10   05 Oct 1992 13:32:00   MIKE
 * changes to make message buffer FAR
 * 
 *    Rev 1.9   21 Sep 1992 11:38:58   MIKE
 * removed VIM_FAR from return type of FindFolderStr()
 * 
 *    Rev 1.8   21 Sep 1992 07:26:56   MIKE
 * add MCAPRemoveCategory, internal prototypes
 * 
 *    Rev 1.6   17 Aug 1992 12:59:56   MIKE
 * new arguments to functions.
 * 
 *    Rev 1.4   26 Jul 1992 12:22:22   KENT
 * Add MCAPSetMessageCategory and MCAPRemoveMessageCategory declarations.
 * 
 *    Rev 1.3   10 Jul 1992 13:16:54   KENT
 * removed "contr" from name of EnumerateMsgAttrValues
 * 
 *    Rev 1.2   30 Jun 1992 17:15:52   MIKE
 * added copydata field to mcapIndexRec to support multiple categories
 * per message
 * 
 *    Rev 1.0   19 Jun 1992 18:02:22   KENT
 * Initial revision.
 *
 **************************************************************************/


#ifndef __MCAP_INCLUDED
#define __MCAP_INCLUDED

#include <vim.h>
#include <cchandle.h>
#include <interfac.h>
#include <fileio.h>


#define NULL        ((void *)0)
#define SEEK_SET	0

#if !defined(countof)
#define countof(x)      (sizeof(x)/(sizeof((x)[0]))) 
#endif


/**************************************************************************
 * VIM Constants
 **************************************************************************/

/*
 * The lengths of a message and item type:
 *
 * Note 1, the maximum type length must be the same for both messages and
 * items.  This is required because the VIM specification for
 * VIMQueryCapability has only one selector, VIMSEL_MAX_TYPE_LEN, for the
 * type length which applies to both the message and item.
 *
 * Note 2, the current VIM specification requires the size of the item type
 * to be 64; therefore, the message type must also be 64.
 *
 * NONCOMPLIANCE - the previous notes are disregarded.  The lengths are set
 * to 32 for the message type and 20 for the item type.  This was done for
 * historical precedence and to keep the message file size down.
 */
#define VIM_MSGTYPE_LEN     32
#define VIM_ITEMTYPE_LEN    20
#define VIM_MAX_TYPE_LEN    32

/*
 * Subject Length:
 *
 * This is the maximum length (including the NULL) of the subject field in
 * a message.  Anything longer than this will be truncated.
 */
#define MCAP_SUBJECT_LEN	60



/* arbitrary limits */

#define MAX_MCAP_SESSIONS	1
#define MAX_MCAP_CONTAINERS	1
#define MCAP_MSG_MAXLEN		21 * 1024
#define MCAP_ITEM_MAXLEN	21 * 1024


/* 
 * index 0 on session and container arrays reserved.
 * valid indices are > 0
 */

#define INVALID_SESSION		((unsigned short)0x0)
#define INVALID_CONTAINER	((unsigned short)0x0)


#define MAXFNAME            80

/* pre-defined folder values */
#define MAX_MCAP_FOLDERS        255
#define MCAP_FOLDERNAME_LEN     32
#define MCAP_FOLDERSPACE_MAX    2048

#define INBOX_FOLDER		0
#define FIRST_USER_FOLDER	1

#define NEW_MSG_ID	0x80000000L


#define MCAP_HANDLES_PER_SESSION	6
/*
 * 1) the session itself
 * 2) the container
 * 3) a message
 * 4) message item
 * 5) extra
 */


/* 
 * MCAPSessionParamsRec
 * Data stored on a per session basis.
 */

typedef struct  {
	HANDLE base_session_handle;		/* used to get handles for this session */
	vimMsgContainer container;		/* default container, a HANDLE */
} MCAPSessionParamsRec;


typedef struct {
	char buffer[MCAP_FOLDERSPACE_MAX];
	char *first_free;
    vimWord bytes_free;
} MCAPFolderHeap;


typedef struct {
	vimBool deliv_rep : 1;
	vimBool nondeliv_rep : 1;
	vimBool nondeliv_cont : 1;
	vimBool encrypt : 1;
	vimBool sign : 1;
	vimBool unread : 1;
	vimBool draft : 1;
	vimBool sent : 1;
	vimBool ret_receipt : 1;
	vimBool deleted : 1;
} MCAPHdrFlags;


/*
 * MCAPContainerHdr -
 *
 * The header of a container file.
 *
 * Message reference numbers are generated sequentially starting from zero
 * on up to 2**31, more message reference numbers than one person can
 * possibly exhaust in a life time.  A new message reference number is
 * generated each time a new message is created and each time a new folder
 * or category reference is created.  The high order bit is reserved as an
 * indicator, if set, that the reference is a folder reference in which case
 * the reference is a child to another reference, its parent.  Note, the high
 * order bit is never set in the header, only in the individual container
 * records.
 */
typedef struct {
    vimDWord last_msg_ref_num;
        /* The last message reference number used -- high bit always clear. */
} MCAPContainerHdr;

#define MCAP_MSG_REF_NUM_MASK   (0x7FFFFFFF)

#define MCAP_CHILD_REF          (0x80000000)

#define MCAP_INDEX_OFFSET       (sizeof(MCAPContainerHdr))


/*
 * MCAPIndexRec - 
 *
 * The container file is a stream of these.  The container file can be
 * thought of as an array or index of these records and each record is an
 * individual message reference.
 *
 * Note 1, a message reference can be either a parent reference or a child
 * reference.  Child references point to the parent reference to which
 * they belong.  When a message is copied into a folder or catergory, a
 * second file is not created.  A child reference is created instead.
 *
 * Note 2, the high order bit of the priority indicates whether the message
 * was generated locally or remote.  It is set if it is generated locally.
 * Attachment files of messages generated remote are temporary files and
 * need to be deleted along with the message.
 *
 * Note 3, the high order bit of the message number, if set, indicates that
 * the message is a child reference.
 */
typedef struct {
	vimWord wFolderId;
        /* Identifies the folder to which the message reference belongs. */

	vimWord wPriority;
        /* The message priority.  Note, the high order bit, if set, indicates
         * that the message was generated locally.  */

	MCAPHdrFlags flags;
        /* Duplicate copy of message header flags. */

	vimDWord dwCopyData;
        /* If the message is a parent reference, this is the number of
         * child references.  When the value reaches zero and it's no
         * longer in the inbox, then it needs to be deleted.  If the
         * message is a child reference, this is the parent message reference
         * number. */

    vimDWord msg_ref_num;
        /* The message reference number is a unique number identifying this
         * message reference.  Note, the high order bit, if set, indicates
         * that this reference is a child to another reference. */

    vimDate stCreationDT;
        /* The date and time the message was created.  This is the creation
         * date/time of the original message and not the date/time this
         * record or message reference is created. */

} MCAPIndexRec;

typedef MCAPIndexRec VIM_FAR * MCAPIndexRecPtr;

#define MAX_CONTR_RECS  (0xFFFF / sizeof(MCAPIndexRec))

/*
 * Memory for the container records is allocated on a granularity so that
 * space is available for adding records without having to allocate
 * additional space with each new record.
 */
#define CONTR_REC_ALLOC_GRAN    50


/* 
 * MCAPContainerParamsRec
 * Data stored on a per container basis.
 */

typedef struct  {
    vimWord wSessionIndex;              /* back reference to session */
    char VIM_FAR **hContr;              /* handle to in-memory container file */
    vimWord wCurrentContrRec;           /* index of current container rec */
    vimWord nContrRecs;                 /* number of records in container */
    vimWord nAllocContrRecs;            /* space allocated for N records */
    MCAPContainerHdr stContrHdr;        /* copy of container file hdr */
    vimBool bModified;                  /* set if container has been modified */
    vimBool bNewMessagesArrived;        /* used for QueryNewMessages() */
	FILE *pstFile;                      /* always open for now */
	char sFName[MAXFNAME];              /* name used to open fileptr */
	MCAPIndexRec cr;					/* copy of current container record */
//???RFD Can this be reduced in size at all?  It's currently 2K per
//container (2 containers, one's waisted).
	MCAPFolderHeap stFolderHeap;        /* space for folder names */
//???RFD This uses up .5K.  Is it really needed?  Can't they be obtained by
//scanning the heap.
	char *apsFolderNames[MAX_MCAP_FOLDERS];/* indexed pointers to those names */
} MCAPContainerParamsRec;


/*
 * MCAPMsgRec: memory image of header of an individual message.
 * Disk storage is the same except that strings are stored 
 * length prefixed.
 */

typedef struct {
	vimWord priority;
	MCAPHdrFlags flags;

	vimDate composeDate;
	vimWord recipcount;
	vimWord itemcount;
	vimDWord totalsize;

	vimString msgtype[VIM_MSGTYPE_LEN];
	vimString subject[MCAP_SUBJECT_LEN];

} MCAPMsgRec;

typedef MCAPMsgRec VIM_FAR * MCAPMsgRecPtr;


/* 
 * Following MsgRec is a stream of MCAPItemDesc records. If the Offset
 * field of the ItemDesc is 0, the contents of the Item follows 
 * immediately in memory.  Otherwise, the contents must be retrieved
 * from the file at the given offset.
 */

typedef struct {
	vimSelector class;
	vimDWord Size;
	vimDWord Offset;
	vimString itemtype[VIM_ITEMTYPE_LEN];
} MCAPItemDesc;

typedef MCAPItemDesc VIM_FAR * MCAPItemDescPtr;


/*
 * The data of a recipient item (immediately following the item descriptor)
 * consists of a header portion followed by the variable length portions.
 * Refer to the vimRecipient structure definition.  The header portion
 * contains all of the type fields.  The variable length portion consists
 * of the following null terminated strings in order:
 *  vimDistinguishedName.AddressBook
 *  vimDistinguishedName.Value
 *  vimAddress.Value
 *
 * The vimRecipient structure could not be used directly because it
 * requires too much memory.  A message with more than 8 recipients
 * could not have otherwise been created in the 20K buffer currently used.
 */
typedef struct {
    vimDWord dwRecipType;
    vimDWord dwRecipDistNameType;
    vimDWord dwRecipAddrType;
} MCAPRecipHdr;

typedef MCAPRecipHdr VIM_FAR *MCAPRecipHdrPtr;

/* # of variable length strings following the MCAP RecipHdr. */
#define MCAP_RECIP_STRINGS  3


extern MCAPSessionParamsRec Sessions[];
extern MCAPContainerParamsRec Containers[MAX_MCAP_CONTAINERS+1];
extern vimDWord message_in_buffer;


/*
	Function Prototypes
*/

vimStatus VIMAPIENTRY MCAPAddGroupMember(
    vimAddressBook addressBook,
    vimRef entryRef,
    vimStringPtr entryName,
    vimDistinguishedNamePtr pDisName);

vimStatus VIMAPIENTRY MCAPCloseAddressBook(
    vimAddressBook addrBook);

vimStatus VIMAPIENTRY MCAPCloseMessage(
    vimMsg message);

vimStatus VIMAPIENTRY MCAPCloseMessageContainer(
    vimMsgContainer msgContainer);

vimStatus VIMAPIENTRY MCAPCloseMessageItem(
    vimMsgItem msgItem);

vimStatus VIMAPIENTRY MCAPCloseSession(
    vimSes session);

vimStatus VIMAPIENTRY MCAPCreateAddressBookEntry(
    vimAddressBook addressBook,
    vimSelector entryType,
    vimWord attrCount,
    vimAttrDescPtr pAttrDesc);

vimStatus VIMAPIENTRY MCAPCreateDerivedMailMessage(
    vimMsg message,
    vimSelector selMsgType, 
    vimDWord dwFlags, 
    vimMsgPtr pMessage);

vimStatus VIMAPIENTRY MCAPCreateMessage(
    vimSes session, 
    vimStringPtr psType,
    vimMsgPtr pMessage);

vimStatus MCAPDeleteCategoryRef(
    vimMsgContainer msgContr, 
    vimRef refParent,
    vimStringPtr psCatName);

vimStatus VIMAPIENTRY MCAPDeleteMessageItem(
    vimMsg message,
    vimSelector class);

vimStatus VIMAPIENTRY MCAPDeleteMessageRecipient(
    vimMsg message,
    vimSelector class);

vimStatus VIMAPIENTRY MCAPEnumerateABEntryAttrNames(
    vimAddressBook addressBook,
    vimRef entryRef,
    vimStringPtr entryName,
    vimEnumRefPtr pPos, 
    vimInt skipCount, 
    vimWord buffEntrySize, 
    vimStringPtr pBuffArray,
    vimWordPtr pCount, 
    vimBoolPtr pMore);

vimStatus VIMAPIENTRY MCAPEnumerateAddressBookEntries(
    vimAddressBook addressBook,
    vimRef subtreeRef,
    vimStringPtr subtreeName,
    vimEnumRefPtr pPos, 
    vimInt skipCount, 
    vimWord attrCount,
    vimAttrDescPtr pAttrDesc, 
    vimWordPtr pCount, 
    vimSelector selFiltType,
    vimDataPtr pFiltData,
    vimBoolPtr pMore);

vimStatus VIMAPIENTRY MCAPEnumerateAddressBooks(
    vimSes session,
    vimEnumRefPtr pPos, 
    vimInt skipCount,
    vimWord attrCount,
    vimAttrDescPtr pAttrDesc,
    vimWordPtr pCount, 
    vimBoolPtr pMore);

vimStatus VIMAPIENTRY MCAPEnumerateGroupMembers(
    vimAddressBook addressBook,
    vimRef entryRef,
    vimStringPtr entryName,
    vimEnumRefPtr pPos, 
    vimInt skipCount, 
    vimWord attrCount,
    vimAttrDescPtr pAttrDesc, 
    vimWordPtr pCount, 
    vimBoolPtr pMore);

vimStatus VIMAPIENTRY MCAPEnumerateMessages(
    vimMsgContainer msgContainer,
    vimEnumRefPtr pPos, 
    vimInt skipCount, 
    vimWord attribCount,
    vimAttrDescPtr pAttribDesc, 
    vimWordPtr pMsgCount,
    vimSelector selFiltType,
    vimDataPtr pFiltData,
    vimSelector flags, 
    vimBoolPtr pMore);

vimStatus VIMAPIENTRY MCAPEnumerateMessageHeaderAttrs(
    vimMsg msg,
    vimSelector selAttr,
    vimEnumRefPtr pPos,
    vimInt skipCount,
    vimWord buffEntrySize,
    vimStringPtr pBuffArray,
    vimWordPtr pCount,
    vimBoolPtr pMore);

vimStatus VIMAPIENTRY MCAPEnumerateMessageItems(
    vimMsg message,
    vimEnumRefPtr pPos, 
    vimInt skipCount, 
    vimWordPtr pCount,
    vimItemDescPtr pDesc, 
    vimSelector selFiltType,
    vimDataPtr pFiltData,
    vimBoolPtr pMore);

vimStatus VIMAPIENTRY MCAPEnumerateMessageRecipients(
    vimMsg message,
    vimSelector selType, 
    vimEnumRefPtr pPos, 
    vimInt skipCount, 
    vimWord attrCount,
    vimAttrDescPtr pAttrDesc, 
    vimWordPtr pCount, 
    vimBoolPtr pMore);


vimStatus VIMAPIENTRY MCAPEnumerateMsgAttrValues(
    vimMsgContainer msgContr,
    vimSelector selAttr,
    vimEnumRefPtr pPos, 
    vimInt skipCount, 
    vimWord buffEntrySize,
    vimStringPtr pBuffArray, 
    vimWordPtr pCount,
    vimBoolPtr pMore);

vimStatus VIMAPIENTRY MCAPExtractMessage(
    vimMsg msg,
    vimDWord dwFlags,
    vimStringPtr strFileSpec);

vimStatus VIMAPIENTRY MCAPGetABEntryAttributes(
    vimAddressBook addressBook,
    vimRef entryRef,
    vimStringPtr entryName,
    vimWord attrCount, 
    vimAttrDescPtr pAttrDesc);

vimStatus VIMAPIENTRY MCAPGetABEntryNamedAttributes(
    vimAddressBook addressBook,
    vimRef entryRef,
    vimStringPtr entryName,
    vimWord attrCount, 
    vimNamedAttrDescPtr pAttrDesc);

vimStatus VIMAPIENTRY MCAPGetCurrentSubtree(
    vimAddressBook addressBook,
    vimRefPtr pRef,
    vimWord wNameSize,
    vimStringPtr psName);

vimStatus VIMAPIENTRY MCAPGetDefaultSessionInfo(
    vimWord sizePath,
    vimStringPtr psPathSpec,
    vimWord sizeName,
    vimStringPtr psName);

vimStatus VIMAPIENTRY MCAPGetEntityName(
    vimSes session, 
    vimDistinguishedNamePtr pDistName);

vimStatus VIMAPIENTRY MCAPGetMessageHeader(
    vimMsg message, 
    vimWord attrCount,
    vimAttrDescPtr pAttrDesc);

vimStatus VIMAPIENTRY MCAPGetMessageItem(
    vimMsg message,
    vimRef refItem,
    vimStringPtr psConvertType,
    vimSelector selFlags,
    vimBuffFileDescPtr pBuffFileDesc);

vimStatus VIMAPIENTRY MCAPGetNewMsgRef(
	vimMsgContainer msgContr, 
    vimRefPtr prefMsg);

vimStatus MCAPGetParentRef(
    vimMsgContainer msgContr, 
    vimRef refChild,
    vimRefPtr prefParent);

vimStatus VIMAPIENTRY MCAPInitialize( vimVoid );

vimStatus VIMAPIENTRY MCAPMarkMessageAsRead(
    vimMsgContainer msgContainer,
    vimRef msgRef);

vimStatus VIMAPIENTRY MCAPMatchAddressBook(
    vimAddressBook addressBook,
    vimRef subtreeRef,
    vimStringPtr subtreeName,
    vimSelector selAttr,
    vimDataPtr pData, 
    vimSelector ft, 
    vimRefPtr pRef,
    vimEnumRefPtr pEnumRef);

vimStatus VIMAPIENTRY MCAPOpenAddressBook(
    vimSes session, 
    vimStringPtr psName,
    vimAddressBookPtr pAddressBook);

vimStatus VIMAPIENTRY MCAPOpenExtractedMessage(
    vimSes session,
    vimStringPtr strFileSpec,
    vimMsgPtr pMsg);

vimStatus VIMAPIENTRY MCAPOpenMessage(
    vimMsgContainer msgContainer, 
    vimRef refMessage,
    vimStringPtr key,
    vimMsgPtr pMessage);

vimStatus VIMAPIENTRY MCAPOpenMessageContainer(
    vimSes session,
    vimStringPtr psContainerName, 
    vimMsgContainerPtr pMsgContainer);

vimStatus VIMAPIENTRY MCAPOpenMessageItem(
    vimMsg message,
    vimRef refMsgItem,
    vimStringPtr psConvertType,
    vimSelector selFlags,
    vimMsgItemPtr pMsgItem);

vimStatus VIMAPIENTRY MCAPOpenNestedMessage(
    vimMsg message, 
    vimRef refNested,
    vimMsgPtr pNestedMessage);

vimStatus VIMAPIENTRY MCAPOpenSession(
    vimStringPtr psPathSpec, 
    vimStringPtr psName, 
    vimStringPtr psPass, 
    vimDWord dwVersion,
    vimSelector selCharSet,
    vimSesPtr pSession);

vimStatus VIMAPIENTRY MCAPQueryCapability(
    vimSelector selType, 
    vimWord sizeData,
    vimDataPtr pData);

vimStatus VIMAPIENTRY MCAPQueryNewMessages(
    vimMsgContainer msgContainer,
    vimBoolPtr pbNewMessages);

vimStatus VIMAPIENTRY MCAPQueryUnreadMailCount(
    vimMsgContainer inbox,
    vimDWordPtr pdwNumUnread);

vimStatus VIMAPIENTRY MCAPReadMessageItem(
    vimMsgItem msgItem, 
    vimBuffFileDescPtr pBuffFileDesc);

vimStatus VIMAPIENTRY MCAPRemoveAddressBookEntry(
    vimAddressBook addressBook,
    vimRef entryRef,
    vimStringPtr entryName);

vimStatus VIMAPIENTRY MCAPRemoveGroupMember(
    vimAddressBook addressBook,
    vimRef entryRef,
    vimStringPtr entryName,
    vimDistinguishedNamePtr pDisName);

vimStatus VIMAPIENTRY MCAPRemoveMessage(
    vimMsgContainer msgContainer, 
    vimRef msgRef);


vimStatus VIMAPIENTRY MCAPRemoveMessageCategory(
    vimMsgContainer msgContr,
    vimRef msgRef,
    vimStringPtr psCatName);

vimStatus VIMAPIENTRY MCAPRemoveCategory(
    vimMsgContainer msgContr,
    vimStringPtr psCatName,
    vimBool remIfNotEmpty);

vimStatus MCAPReplaceMessage(
    vimMsgContainer msgContr, 
    vimRef refMsg,
    vimMsg message);

vimStatus VIMAPIENTRY MCAPSendMessage(
    vimMsg message,
    vimDataPtr pCallbackParam,
    vimSendCallback callBack);

vimStatus VIMAPIENTRY MCAPDeliverMessage(	
    vimMsg message,
    vimDataPtr pCallbackParam,
    vimSendCallback callBack);

vimStatus VIMAPIENTRY MCAPSetABEntryAttributes(
    vimAddressBook addressBook,
    vimRef entryRef,
    vimStringPtr entryName,
    vimWord attrCount, 
    vimAttrDescPtr pAttrDesc);

vimStatus VIMAPIENTRY MCAPSetABEntryNamedAttributes(
    vimAddressBook addressBook,
    vimRef entryRef,
    vimStringPtr entryName,
    vimWord attrCount, 
    vimNamedAttrDescPtr pAttrDesc);

vimStatus VIMAPIENTRY MCAPSetCurrentSubtree(
    vimAddressBook addressBook,
    vimRef subtreeRef,
    vimStringPtr subtreeName);

vimStatus VIMAPIENTRY MCAPSetMessageCategory(
    vimMsgContainer msgContr,
    vimRef msgRef,
    vimStringPtr psCatName);

vimStatus VIMAPIENTRY MCAPSetMessageHeader(
    vimMsg message,
    vimSelector selAttr, 
    vimWord wAttrSize,
    vimDataPtr pAttr);

vimStatus VIMAPIENTRY MCAPSetMessageItem(
    vimMsg message,
    vimSelector selClass,
    vimStringPtr strType,
    vimSelector selFlags,
    vimStringPtr strName,
    vimBuffFileDescPtr pDesc);

vimStatus VIMAPIENTRY MCAPSetMessageRecipient(
    vimMsg message,
    vimSelector selClass,
    vimRecipientPtr pRecip);

vimStatus VIMAPIENTRY MCAPStatusText(
    vimStatus status,
    vimWord wTextSize,
    vimStringPtr pText,
    vimWord wExtTextSize,
    vimStringPtr pExtText);

vimStatus VIMAPIENTRY MCAPTerminate( vimVoid );

vimStatus VIMAPIENTRY MCAPVerifyMessageSignature(
    vimMsg message,
    vimWord attrCount, 
    vimAttrDescPtr pAttrDesc);


/*********************************************************************/


vimDWord GetParentReference(
    vimWord loc_cont,
    vimDWord dwMsgId);

FILE *fopen(char VIM_FAR * fname, char VIM_FAR * mode);
int fclose(FILE *f);
int fflush(FILE *f);
int fseek(FILE *f,long dest, int mode);
unsigned int fread(void VIM_FAR *buffer,unsigned int objsize, unsigned int objcount,FILE *f);
unsigned int fwrite(void VIM_FAR *buffer,unsigned int objsize, unsigned int objcount,FILE *f);
int remove(char _far *);

unsigned short VerifyMCAPSession(vimSes session);
unsigned short NewMCAPSessionIndex(void);
void ConstructMsgName(char *fname, vimDWord dwMsgId, vimWord loc_cont);
vimStatus CreateMsgFile(MCAPMsgRecPtr msg, long *msgid,unsigned short loc_cont);
vimStatus NewMsgFile(MCAPMsgRecPtr msg, long idnum, unsigned short loc_cont);
vimStatus ReplaceMsgFile(MCAPMsgRecPtr msg, long msgid, unsigned short loc_cont);
vimStatus AddIndexRec(MCAPMsgRecPtr msg, unsigned short folder_id,long msgid,
                            unsigned short loc);

int GetFileSize(FILE *pstFile, vimDWord *plwFileSize);

vimStatus AddIndexCopy(
	vimWord folder_id,
	vimDWord src_msgid,
    vimWord loc_cont);

vimStatus RetrieveCurrentMsg(unsigned short loc_cont);
vimStatus RetrieveMsgFromFile(MCAPMsgRecPtr msg,  long idnum,
                            unsigned short loc_cont);
vimDWord GetNewMsgId(vimWord loc_cont);
unsigned short VerifyMCAPContainer(vimMsgContainer container);
int ReadContainerRec(vimWord loc_cont, vimWord next_rec);
vimStatus CommitContainerRec(vimWord loc_cont);
vimStatus FillEnumAttribs(vimWord loc_cont, vimWord attribCount,
	vimAttrDescPtr pAttribDesc,short msgIndex, vimBool bMsgInMemory);

MCAPItemDescPtr GetNthRecipAddr(MCAPMsgRecPtr msg,unsigned short n);
MCAPItemDescPtr GetNextRecipAddr(MCAPMsgRecPtr msg,MCAPItemDescPtr itemdesc,unsigned short *n);
MCAPItemDescPtr GetNthItemAddr(MCAPMsgRecPtr msg,unsigned short n);
MCAPItemDescPtr GetNextItemAddr(MCAPMsgRecPtr msg,MCAPItemDescPtr itemdesc,unsigned short *n);
char * FindFolderStr(vimWord id, vimWord loc_cont);
short FindFolderId(char VIM_FAR *foldername, unsigned short loc_cont);

void SetVimDateToNow(vimDatePtr pDate);

int InitFolders(unsigned int loc_cont);
int SaveFolders(unsigned int loc_cont);
int write_string(char VIM_FAR * str, FILE *f);
int read_string(char VIM_FAR * str, FILE *f);
void strcpyItemContents(char VIM_FAR *dest,MCAPItemDesc VIM_FAR *itemdesc);
void memcpyItemContents(char VIM_FAR *dest,MCAPItemDesc VIM_FAR *itemdesc);
void memcpyItemContentsWOffset(char VIM_FAR *dest,
	MCAPItemDescPtr itemdesc,vimDWord offsetlen,unsigned short copylen);

int ConvertSenderToRecipient(MCAPMsgRecPtr msg);
int ConvertTotoCC(MCAPMsgRecPtr msg);
int RemoveContents(MCAPMsgRecPtr msg);
int RemoveItemClass(MCAPMsgRecPtr msg, vimSelector Class);
int RemoveRecipientClass(MCAPMsgRecPtr msg, vimSelector Class);
int RemoveRecipients(MCAPMsgRecPtr msg);
int RemoveFromRecord(MCAPMsgRecPtr msg);
void InitExtractStrings(void);
char VIM_FAR *msgbufferP(void);
int InitMCAPBuffer(void);
int ReleaseMCAPBuffer(void);

vimStatus GetContainerId(vimMsg message, unsigned short *loc);

char *format_date( unsigned long, char *, int );
void format_time( unsigned long, char * );

int GetRecNumFromMsgID(
    vimWord loc_cont,
    vimDWord MsgID,
    unsigned int *pwRecNum);

vimStatus WriteContainer(unsigned short loc_cont);

vimBool FileExist(char VIM_FAR * fname);


#endif		/* end of #IFNDEF __MCAP_INCLUDED */


/* EOF: mcap.h */

