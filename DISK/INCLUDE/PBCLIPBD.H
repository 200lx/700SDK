/* SCCS info:   Module pbclipbd.h  Version 1.1  Date 11/09/93  Time 15:23:46 */

/* $Header:   T:/HH/INCLUDE/VCS/PBCLIPBD.H_V   1.1   15 Oct 1992 10:52:02   KIM  $ */
/**************************************************************************
 *
 * Name:        PBCLIPBD.H
 *
 * Date:        Thursday October 1, 1992
 *
 * Abstract:    Defines the phonebook clipboard interface constants and
 *              structures.
 *
 * ------------------------------------------------------------------------
 *                   Copyright 1992 Lotus Development Corp.
 *                           All rights reserved.
 **************************************************************************
 *
 * $Log:   T:/HH/INCLUDE/VCS/PBCLIPBD.H_V  $
 * 
 *    Rev 1.1   15 Oct 1992 10:52:02   KIM
 * * * * SERVER DISK CRASH RECOVERY * * *
 *  1) The VCS directory was restored with Build 18 backup tape.
 *  2) This revision is to update files to Build 19.
 *  3) HELP.H has post-Build 19 changes.
 * 
 *    Rev 1.0   01 Oct 1992 10:40:08   ROGER
 * Initial revision.
 *
 **************************************************************************/

#if !defined(PBCLIPBD_H)
#define PBCLIPBD_H


/*
 * The name of a phonebook clipboard representation.  Note, the name cannot
 * be resourced because it needs to be shared by other applications.
 */
#define CB_REP_PBK  "LOTUS PHONEBOOK"


/*
 *                    Phonebook Clipboard Record Structure
 *                  ----------------------------------------
 *
 * The overall record structure of the phonebook clipboard record is as
 * follows:
 *
 *      o. Record Header - contains field count and field offset table.
 *
 *      o. fields - following the record header is a sequence of NULL
 *      terminated strings, one string for each field in a phonebook record.
 *
 * Note, there is not a single data structure to encapsulate this definition.
 * Instead, the structure is a composite of the record header and the
 * sequential NULL terminated strings.
 */


/*
 * Field Offset Sub-Structure:
 *
 * The field offset structure contains one offset for each of the fields
 * in the clipboard record.  The offset is the number of bytes from the
 * beginning of the clipboard record data to the start of the text string
 * for that field.
 *
 * INTERNAL NOTE: Any additions or deletions from this table MUST have
 * corresponding changes made to the phonebook clipboard mapping structure.
 */
struct CBPhonebookOffsetTable
{
    unsigned int wOffsetPersName;
    unsigned int wOffsetPersAddr1;
    unsigned int wOffsetPersAddr2;
    unsigned int wOffsetPersCity;
    unsigned int wOffsetPersState;
    unsigned int wOffsetPersZip;
    unsigned int wOffsetPersPhone;
    unsigned int wOffsetPersNote;

    unsigned int wOffsetBusTitle;
    unsigned int wOffsetBusCompany;
    unsigned int wOffsetBusAddr1;
    unsigned int wOffsetBusAddr2;
    unsigned int wOffsetBusCity;
    unsigned int wOffsetBusState;
    unsigned int wOffsetBusZip;
    unsigned int wOffsetBusPhone;
    unsigned int wOffsetBusFax;
    unsigned int wOffsetBusEmail;
};
#define CB_PBK_OFFSET_TABLE_ENTRIES \
    (sizeof(struct CBPhonebookOffsetTable) / sizeof(unsigned int))


/*
 * Record Header Structure:
 *
 * The record header structure is the first part, the header, of a phonebook
 * clipboard record.  It defines the number of text entries, the total
 * number of bytes of text (including the NULLs) in all of the fields, and
 * a table of offsets to the field data.  Note, the number of text entries
 * is the same as the number of entries in the field offset table.
 */
struct CBPhonebookHdrStruct
{
    unsigned int nTextEntries;
    unsigned int nBytesOfText;
    struct CBPhonebookOffsetTable stFieldTable;
};


#endif

