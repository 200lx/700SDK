/* SCCS info:   Module dbapi.h  Version 1.1  Date 11/09/93  Time 15:17:52 */

/* $Header:   T:/HH/INCLUDE/VCS/DBAPI.H_V   1.11   15 Oct 1992 10:49:48   KIM  $ */
/**************************************************************************
 *
 * Name:        DBAPI.H -
 *
 * Date:        Wednesday April 1, 1992
 *
 * Abstract:    Database Application Programmer Interface definitions -
 *              contains the constants, structures, and function prototypes
 *              for interfacing to the database engine.
 *
 * ------------------------------------------------------------------------
 *                   Copyright 1992 Lotus Development Corp.
 *                           All rights reserved.
 **************************************************************************
 *
 * $Log:   T:/HH/INCLUDE/VCS/DBAPI.H_V  $
 * 
 *    Rev 1.11   15 Oct 1992 10:49:48   KIM
 * * * * SERVER DISK CRASH RECOVERY * * *
 *  1) The VCS directory was restored with Build 18 backup tape.
 *  2) This revision is to update files to Build 19.
 *  3) HELP.H has post-Build 19 changes.
 * 
 *    Rev 1.10   11 Sep 1992 15:01:40   ROGER
 * Miscellaneous.
 * 
 *    Rev 1.9   08 Sep 1992 19:29:38   ROGER
 * Added flags for the GOTO search.
 * 
 *    Rev 1.8   27 Aug 1992 15:39:42   ROGER
 * Removed the function DBRenameDatabase from the list of function prototypes.
 * 
 *    Rev 1.7   23 Jul 1992 19:52:16   ROGER
 * Miscellaneous changes to comments regarding searching using inequalities.
 * 
 *    Rev 1.6   15 Jul 1992 00:43:36   ROGER
 * Modified comments only.
 * 
 *    Rev 1.5   13 Jul 1992 14:49:54   ROGER
 * Modified prototype for DBCompareRecords().
 * 
 *    Rev 1.4   11 Jul 1992 23:00:28   ROGER
 * Added new API functon prototypes, added selection level 4, and added
 * another error.
 * 
 *    Rev 1.3   06 Jul 1992 13:51:16   ROGER
 * Added flags for performing different search operations (<, >, <=, etc.).
 * 
 *    Rev 1.2   11 Jun 1992 08:02:36   ROGER
 * o.  Categorized errors so that the application can utilize them more
 * efficiently.  Added a couple of new errors and added the entire class
 * of errors which are just warnings.
 * 
 * o. Modifed the sort specification structure to be an array of individual
 * sort specs rather than a single structure containing primary, secondary,
 * and tertiary sort fields.
 * 
 * o. Modified the index definition structure top include the array of sort
 * specs, a count, and an index attribute element.  The index attribute is
 * used for specifying what should be saved when the index is saved and also
 * whether the index supports mixed records or only a single record type.
 * 
 * o. Enhanced the comments throughout the file.
 * 
 * o. Reduced the MAX_INDEXES in order to lower the static data requirements.
 * 
 * 
 *    Rev 1.1   15 May 1992 11:09:34   ROGER
 * Added prototype for new function DBGetAllFieldIDs and enhanced the
 * comments on the use of undefined database/index/field IDs, a potential
 * source for appliction errors.
 * 
 *    Rev 1.0   06 May 1992 08:49:14   ROGER
 * Initial revision.
 *
 **************************************************************************/

/*
 *                  Database Application Programmer Interface
 *                  -----------------------------------------
 *
 *
 *
 *                                    NOTES
 *                                   =======
 *
 *
 * Packing:
 * --------
 * All database engine data structures are packed on byte boundaries in
 * order to minimize storage requirements.
 *
 *
 * Index, Field, and Database IDs:
 * -------------------------------
 * In the current implementation of the database engine, zero is a valid
 * index, field, and database ID.  This is an unfortunate oversight in the
 * engine implementation that should be fixed in a later version to
 * make the development and debugging of applications a little easier.
 * Applications must make sure that IDs are set to their proper values; the
 * engine will not report an error if the specified ID has a value of zero
 * because that is a valid ID.  As a safety measure, applications could
 * initialize all IDs to -1, a value that the engine will detect as
 * invalid and report an error.  The application should use the appropriate
 * "..._ID_UNDEFINED" constant for this purpose.
 *
 * INTERNAL NOTE:  At some later revision of the engine, zero should also
 * be an invalid field, index, and database ID.  This would be in addition
 * to the value currently used, -1.
 */


#if !defined(DBAPI_H)
#define DBAPI_H

//??? Fileio.h defines M_FILEIO instead of FILEIO_H.  This will be fixed.
#if !defined(M_FILEIO)
#if !defined(FILEIO_H)
#include <fileio.h>         /* include the public file I/O definitions */
#endif
#endif

/* Force data structures to be packed on byte boundaries. */
#pragma pack(1)

/**************************************************************************
 * Miscellaneous Useful Constants and Macros:
 **************************************************************************/

#if !defined(TRUE)
#define TRUE    (1)
#endif

#if !defined(FALSE)
#define FALSE   (0)
#endif

#if !defined(NULL)
#define NULL            ((void *)0)
#endif

#if !defined(offsetof)
#define offsetof(s,m)   (unsigned int)&(((s *)0)->m)
#endif

#if !defined(countof)
#define countof(x)      (sizeof(x)/(sizeof((x)[0]))) 
#endif


/**************************************************************************
 * Limitations:
 **************************************************************************/

/*
 *                                     NOTE
 *                                    ------
 * Some of these limitations might be relaxed in the future as the code is
 * made more flexible; however, for now these limits will be imposed. The
 * application should define its own limits and defined in such a way as to
 * dynamically (at compile time) be less than or equal to the limits imposed
 * here.
 *
 * For example:
 *  #define APP_DESIRED_MAX_FIELDS      50
 *  #if (APP_DESIRED_MAX_FIELDS <= DB_MAX_FIELDS)
 *  #define APP_MAX_FIELDS              APP_DESIRED_MAX_FIELDS
 *  #else
 *  #define APP_MAX_FIELDS              DB_MAX_FIELDS
 *  #endif
 *
 * Also, these constants, for the most part, currently determine the amount
 * of static data the engine requires.  These values should be fine tuned
 * for the production code of each individual application.
 */

/* Maximum length of the name of the owner application. */
#define DB_MAX_OWNER_NAME_LEN   32

/* Maximum length of a field name. */
#define DB_MAX_FIELD_NAME_LEN   32

/* Maximum length of an index name. */
#define DB_MAX_INDEX_NAME_LEN   32

/*
 * Maximum number of indexes.
 *
 * INTERNAL NOTE:  In addition to the application defined indexes, the engine
 * maintains several indexes which are internal to the operation of the
 * database engine.  Internally, a different constant is used as the maximum
 * number of indexes.  The internal constant includes the number of internal
 * indexes that are maintained.
 */
#define DB_MAX_INDEXES          16

/* Maximum number of fields. */
#define DB_MAX_FIELDS           32

/*
 * Maximum number of databases that can be open simultaneously.
 *
 * INTERNAL NOTE:  
//??? do we want an internal note about the temporary database
 */
#define DB_MAX_APP_DATABASES    2

/* Maximum number of sort fields. */
#define DB_MAX_SORT_FIELDS      3


/**************************************************************************
 * Requirements:
 **************************************************************************/

/*
 * Indirect Far Pointer Table Entries:
 *
 * The application must declare an indirect far pointer table with a
 * sufficient number of entries available for the engine, in addition to
 * any entries the application may need for itself.
 *
 * The engine requires a fixed number of entries for its internal operations
 * and one or more additional entries for each index the application builds.
 * The exact number of additional entries per index is defined below as a
 * constant that the application can use for calculating the required number
 * of entries in the indirect far pointer table.
 *
 * To calculate the number required, multiply the number of indexes the
 * application requires by the number of entries required per index, and
 * add that value to the engine's fixed requirements.  In this calculation,
 * the total number of indexes the application requires must include those
 * for all simultaneously open databases.  In other words, it's not the total
 * per open database but the total of all possible simultaneously open
 * databases.  Note, only two simultaneously open databases are currently
 * supported, a sufficient number for the application to perform merge type
 * operations.
 *
 * The application should use the constants defined below for calculating
 * the required size of the indirect far pointer table.  Note, "IFP" is used
 * as shorthand notation for "indirect far pointer".
 *
 * The formula for calculating the size of the IFP entry is as follows:
 *  APP_MAX_INDEXES - maximum number of indexes the application will need.
 *  APP_IFP_ENTRIES - number of IFP entries the app uses for its own purposes.
 *
 *      IFP table size = (APP_MAX_INDEXES * DB_IFP_ENTRIES_PER_INDEX)
 *              + DB_FIXED_IFP_ENTRIES + APP_IFP_ENTRIES
 *
 * INTERNAL NOTE:  For each database (including the internal temporary
 * database state block), the engine requires 2 entries for records, plus 1
 * each for each of the internal indexes -- field, and deleted.  This adds up
 * to a total of 4 for each database state block. (A few extra have been
 * added to the production code just for good measure.)
 */

#if defined(DEBUG)
#define DB_EXTRA_IFP_ENTRIES            0
#else
#define DB_EXTRA_IFP_ENTRIES            4
#endif

/* Total number of internal indexes.  FOR INTERNAL USE ONLY! */
#define DB_TOTAL_INTERNAL_INDEXES       2

/* Total number of internal database state blocks.  FOR INTERNAL USE ONLY! */
#define DB_TOTAL_INTERNAL_DB_BLOCKS     1

/*
 * Number of IFP entries per index.  The app should use this to calculate
 * the required size of the IFP table.
 */
#define DB_IFP_ENTRIES_PER_INDEX        1

/*
 * FOR INTERNAL USE ONLY! Total number of IFP entries per database.
 * Then additional 2 are for the internal copies of records managed by the
 * database engine.
 */
#define DB_IFPs_PER_DATABASE            (DB_EXTRA_IFP_ENTRIES + \
    (DB_TOTAL_INTERNAL_INDEXES * DB_IFP_ENTRIES_PER_INDEX) + 2)

/*
 * Fixed number of IFP entries required.  The app should use this to
 * calculate the required size of the IFP table.
 */
#define DB_FIXED_IFP_ENTRIES \
    ((DB_MAX_APP_DATABASES+DB_TOTAL_INTERNAL_DB_BLOCKS)*DB_IFPs_PER_DATABASE)


/**************************************************************************
 * Constants:
 **************************************************************************/

/*
 * Control Level:  a bit field specifying the level of responsibility or
 * control the engine assumes.  There is currently only one level supported;
 * however, this could be expanded in the future to choose the desired file
 * cleanup method (background, on demand, etc.) or any number of other
 * possible feature enhancements for the future.
 */
#define DB_STANDARD_CONTROL_LEVEL       0

/*
 * Selection Flags:
 *
 * The selection flags determine the level of selection.  There are currently
 * four levels of selection supported.  The application can mark an index
 * entry as selected at any one of the levels and at more than one level at
 * a time.  This provides a significant amount of flexibility to the
 * application for flagging particular sets of entries within an index and
 * for manipulating those sets or entries.
 *
 * For convenience, the DB_SELECTION_ALL_LEVELS constant has been defined.
 * It can be used, for example, to deselect all entries selected at any
 * level of selection.
 *
 * The DB_SELECTION_ALL_ENTRIES constant has been defined for use when all
 * entries of the index are to be affected regardless of whether any are
 * selected at any level or not.
 *
 * Note, be certain to understand the difference between
 * DB_SELECTION_ALL_LEVELS and DB_SELECTION_ALL_ENTRIES.  These definitions
 * can be a little confusing at first and are a common source of errors
 * during development.
 */
#define DB_SELECTION_LEVEL1         0x01
#define DB_SELECTION_LEVEL2         0x02
#define DB_SELECTION_LEVEL3         0x04
#define DB_SELECTION_LEVEL4         0x08
#define DB_SELECTION_ALL_LEVELS     \
    ( DB_SELECTION_LEVEL1 | DB_SELECTION_LEVEL2 \
    | DB_SELECTION_LEVEL3 | DB_SELECTION_LEVEL4)
#define DB_SELECTION_ALL_ENTRIES    0xFFFF

/*
 * The value of an undefined field, index, or database ID.
 *
 * PLEASE READ THE NOTE AT THE VERY TOP OF THIS FILE REGARDING INDEX, FIELD,
 * AND DATABASE IDs.
 *
 * Suggested use: at compile time or when initializing a data structure,
 * initialize appropriate variables with these values.  This will prevent
 * any inadvertent use of one of these variables from going undetected; an
 * error will be generated.  (If it had not been intialized, its value
 * would, in many case, be automatically initialized to zero which,
 * unfortunately, is currently a valid value.)
 *
 * INTERNAL NOTE:  These values are used internally within the engine in
 * addition to being used in the API as a way of signalling that the
 * application's variable has not been properly set; hence, the value
 * should remain equal to -1 in any future version of the engine.
 */
#define DB_FIELD_ID_UNDEFINED           (0xFFFF)
#define DB_INDEX_ID_UNDEFINED           (0xFFFF)
#define DB_DATABASE_ID_UNDEFINED        (0xFFFF)


/**************************************************************************
 * Data Types
 **************************************************************************/

/*
 * The data types refer to how the value is stored within a database
 * file.  The internal representations, within the database engine itself,
 * will be 8, 16, or 32 bit representations, no 24 bit values.  In other
 * words, a data type of 24 bits will be stored as 24 bits in the file but
 * converted to 32 bits when performing any operations on that data.  Other
 * transformations may occur such as converting 8 bit numbers to 16 bit
 * values.
 *
 * In general, these transformations are transparent to the application.  The
 * application specifies the number of bytes the data occupy in the
 * application's domain at the time in which data are copied to or from
 * the application's domain.
 *
 * The application should choose the data type that is most appropriate for
 * its purposes and which occupies the fewest number of bytes of storage
 * within the database file.  Note, the storage size can be less than or
 * equal to the data size the application uses to manipulate that data
 * within its code; the transformation process from the file to the
 * application's data space will expand the data to the desired data size.
 *
 * INTERNAL NOTE:  Any additions, deletions, or changes made to the following
 * list of data types need to have corresponding changes made to the field
 * data type parameter table which is defined in the field manager module.
 */

typedef unsigned char byte;

/*
 * Date Types:
 *
 *  16 bit date -   number of days since 01-JAN-1900.  A value of 0 means
 *                  01-JAN-1900.
 *  24 bit date -   number of days since 01-JAN-0001.  A value of 0 means
 *                  01-JAN-0001.
 *
 *  Note: If all bits are set (0xFFFF for 16 bit, 0xFFFFFF for 24 bit), this
 *  indicates that the value is undefined.
 */
#define DB_16BIT_DATE                   10
#define DB_24BIT_DATE                   11
/* #define DB_32BIT_DATE                   12 */

/*
 * Time Types:
 *
 *  minutes -        number of minutes since midnight.
 *
 *  seconds -        number of seconds since midnight.
 *
 *  hundredths -     number of hundredths of seconds since midnight.
 *
 *  Note: If all bits are set (0xFFFF for 16 bit, 0xFFFFFF for 24 bit), this
 *  indicates that the value is undefined.
 */
#define DB_16BIT_TIME_IN_MINUTES        20
#define DB_24BIT_TIME_IN_SECONDS        21
#define DB_24BIT_TIME_IN_HUNDREDTHS     22
/* #define DB_32BIT_TIME_IN_SECONDS        23 */
/* #define DB_32BIT_TIME_IN_HUNDREDTHS     24 */

/*
 * Fixed Length Text Types:
 */
#define DB_8BIT_FIXED_LEN_TEXT          30
#define DB_16BIT_FIXED_LEN_TEXT         31
/* #define DB_24BIT_FIXED_LEN_TEXT         32 */
/* #define DB_32BIT_FIXED_LEN_TEXT         33 */

/*
 * Variable Length Text Types:
 */
#define DB_8BIT_LEN_TEXT                40
#define DB_16BIT_LEN_TEXT               41
/* #define DB_24BIT_LEN_TEXT               42 */
/* #define DB_32BIT_LEN_TEXT               43 */

/*
 * Fixed Length Binary Types:
 */
#define DB_8BIT_FIXED_LEN_BINARY        50
#define DB_16BIT_FIXED_LEN_BINARY       51
/* #define DB_24BIT_FIXED_LEN_BINARY       52 */
/* #define DB_32BIT_FIXED_LEN_BINARY       53 */

/*
 * Variable Length Binary Types:
 */
#define DB_8BIT_LEN_BINARY              60
#define DB_16BIT_LEN_BINARY             61
/* #define DB_24BIT_LEN_BINARY             62 */
/* #define DB_32BIT_LEN_BINARY             63 */

/*
 * Integer Types:
 */
#define DB_8BIT_UNSIGNED_INT            70
#define DB_8BIT_SIGNED_INT              71
#define DB_16BIT_UNSIGNED_INT           72
#define DB_16BIT_SIGNED_INT             73
/* #define DB_24BIT_UNSIGNED_INT           74 */
/* #define DB_24BIT_SIGNED_INT             75 */
#define DB_32BIT_UNSIGNED_INT           76
#define DB_32BIT_SIGNED_INT             77

/*
 * Floating Point Types:
 */
/* #define DB_4BYTE_IEEE_FLOAT             80 */
/* #define DB_8BYTE_IEEE_FLOAT             81 */
/* #define DB_10BYTE_IEEE_FLOAT            82 */


/**************************************************************************
 * Record Types
 **************************************************************************/

/*
 * Database Record Type Flags
 *
 * 8 bits:
 *  bit 7 - reserved for internal records.  The engine sets this bit for
 *          records that it creates and manages internally.
 *
 *  bit 6 - set for linked records.  Linked records contain next and previous
 *          pointers and are managed as a linked list.
 *
 *  bit 5 - set for raw data records.  A raw data record has no fields
 *          associated with it.  To the engine, it's just a bunch of bytes.
 *
 *  DB_APP_REC_MASK:
 *  bits 4..0  -   application defineable record types.  The application uses
 *          these bits, in conjunction with bits 5 and 6, to define its own
 *          record types.  The application can create additional record types
 *          on its own by embedding a type field within the data of a record.
 */
#define DB_INTERNAL_REC_FLAG        0x80
#define DB_LINKED_REC_FLAG          0x40    /* not supported */
#define DB_RAW_REC_FLAG             0x20
#define DB_APP_REC_MASK             0x1F


/**************************************************************************
 * Data Structures:
 **************************************************************************/

/*
 * Accounting Report Structure
 *
 * The accounting structure is used for ascertaining the engine's resource
 * utilization of system resources (i.e. file handles, allocated memory) and
 * internal resources (i.e. fields, indexes, etc).  It provides a means for
 * the application to perform quick sanity checks on the state of the engine
 * and also for the application to ensure that all necessary operations are
 * being performed and performed in the correct order.  This is most useful
 * during development and debugging.
 *
 * The application should request an accounting report from the engine at
 * key points of operation to ensure that all is well.  The most obvious is
 * the application should check to make sure the appropriate accounting
 * values are zero before exiting.
 *
 * Note, the values reported in the accounting structure are form the
 * engine's "point of view" which will only be accurate if everything is
 * working correctly.
 *
 * Structure Elements
 * ------------------
 *
 * nOpenFiles:  Number of files currently open (number of file handles in
 *              use).
 *
 * nOpenDatabases:  Number of databases currently open (number of database
 *              state blocks in use).
 *
 * nAllocatedMemoryBlocks:  Number of individual memory blocks currently
 *              allocated (via the engine).
 *
 * lnAllocatedMemoryBytes:  Total number of bytes of memory currently
 *              allocated (via the engine).  This is also the sum of the
 *              number of bytes in each of the memory blocks currently
 *              allocated.
 *
 * nFields:     Number of fields currently defined in all of the available
 *              database state blocks.  In the current engine implementation,
 *              a limited number of field definition structures are available.
 *
 * nMaxFields:  Number of field definition structures available in all of
 *              the database state blocks.  The number per database state
 *              block can be obtained by dividing by the total number of
 *              database state blocks available.
 *
 * nIndexes:    Number of indexes currently defined in all of the available
 *              database state blocks.  In the current engine implementation,
 *              a limited number of index definition structures are available.
 *
 * nMaxIndexes: Number of index definition structures available in all of
 *              the database state blocks.  Note, this value contains the
 *              index definition structures set aside for internal
 *              operations.  The number per database state block can be
 *              obtained by dividing by the total number of database state
 *              blocks available.
 *
 * nDatabaseBlocks: Number of database state blocks in use.  In the current
 *              engine implementation, a limited number of database state
 *              blocks are available.
 *
 * nMaxDatabaseBlocks: Total number of database state blocks available.
 */
typedef struct
{
    int nOpenFiles;                 /* number of files open */
    int nOpenDatabases;             /* number of databases open */
    int nAllocatedMemoryBlocks;     /* number of allocated memory blocks */
    long lnAllocatedMemoryBytes;    /* number of bytes of memory allocated */
} DB_ACCOUNTING_REPORT;


/*
 * Field Definition Structure
 *
 * The field definition structure defines a field.  This is the structure
 * to use when creating fields or reading back field definitions that have
 * previously been created.
 *
 * Structure Elements
 * ------------------
 *
 * wDataType:   The data type of the field, chosen from one of the predefined
 *              data type constants.
 *
 * wMaxNameLen: The maximum length of the field name to be returned when
 *              the application is getting the definition of a field.  Note,
 *              this parameter is NOT used when defining a field.
 *              
 * pszFieldName:    Pointer to the field name, a null-terminated string. 
 *              The field name should uniquely identify the field.  The
 *              application can then obtain the ID associated with the
 *              a field by its name and utilize the ID for the operations
 *              which require a field ID as a parameter.
 *
 *              Note, fixed field names, names the user doesn't create
 *              and cannot change, should be resourced.
 *
 *              Note, field names must be unique independent of case and
 *              accent.
 */
typedef struct
{
    unsigned int wDataType;         /* data type of the field */
    unsigned int wMaxNameLen;       /* max length of field name (with NULL) */
    char near *pszFieldName;        /* pointer to field name */
} DB_FIELD_DEFINITION;


/*
 * Field Translation Definition Structure
 *
 * A field translation definition structure defines the mechanism for
 * translating a record in the engine's domain to a record in the
 * application's domain and vice versa.
 *
 * The application can build a table of field translation definitions.  This
 * table can then be used to translate an entire record at a time.  Bit flags
 * are available to selectively translate specific fields of interest.
 *
//??? The descriptions of some of these elements are confusing.
//Describe these better and provide examples.
 *
 * Structure Elements
 * ------------------
 *
 * bFlags:      The flags determine specific translation features.  See the
 *              description of the bits below.
 *
 * wFieldID:    The ID of the field being translated.  If there is no field
 *              with the specified ID in the current record, then nothing
 *              is translated.
 *
 *              Note 1, the application should initialize wFieldID to
 *              DB_FIELD_ID_UNDEFINED at compile time and assign the field
 *              ID after openning a database, at which time the correct
 *              value can be obtained.
 *
 * wMaxLen:     For variable length fields, the maximum length will limit
 *              the amount of data copied to the application's domain,
 *              ensuring that there is no buffer overflow which would corrupt
 *              memory.  In the other direction, copying from the
 *              application's domain to the engine's domain, this field is
 *              ignored.  A value of 0 indicates that there is no limit.
 *
 *              The maximum length value is presumed to include the space
 *              for the zero-byte terminater if one is requested via the
 *              flags.  See the definition of the flags below for more
 *              details.
 *
 * wLenOfLen:   Specifies the number of bytes in the length itself (i.e. the
 *              length is a byte, an int, a long, or not needed).  The values
 *              are 1 for byte, 2 for int, 4 for long, and 0 for not needed.
 *              This structure element is only referenced for those fields
 *              that have been specified as variable length fields via the
 *              flags.  Fields of a fixed length data type do not require a
 *              length and this value should be set to 0.
 *
 *              Note 1, when translating from the engine's domain to the
 *              application's domain, this length will be utilized if the
 *              variable length flag bit is set whether the field is
 *              zero-byte terminated or not; however, it is ignored when
 *              translating zero-byte terminated fields in the other
 *              direction.  To prevent the length from being processed for
 *              zero-byte terminated fields, set this value to 0.
 *
 *              Note 2, the standard C sizeof() operator can be used to
 *              determine the length of a variable.
 *
//??? This is confusing.  Describe this better and provide an example.
 * wLenOfField: The number of bytes in the data field.  This structure
 *              element is used for fixed length fields to indicate how
 *              many bytes the data occupies in the application's data
 *              space.  This allows the application to internally use a
 *              different data type than the one it specifies as the data
 *              type of the field.  It's the data type of the field that
 *              determines the number of bytes of disk space occupied by
 *              the field which needs to be as small as possible; however,
 *              the application may choose a different data type for its
 *              internal use as a matter of convenience.
 *              
 * dwOffsetToField: Offset from beginning of the application's data structure
 *              to the beginning of the field or to a pointer to the field.
 *              Whether it's a pointer or the actual field depends on what
 *              bits are set in the flags.  See the definition of the flags
 *              below for more details.
 *
 * dwOffsetToLen:   Offset from beginning of the application's data structure
 *              to the length of the field.  Indirect reference (a pointer to
 *              the length) is not allowed.
 *
 * Note 1, an offset is the offset from the beginning of the data structure,
 * not the offset relative to the start of the segment in which the data is
 * defined.  The offsetof macro defined above can be used to extract the
 * offset of a particular field within its structure.
 *
 * Note 2, the wMaxLen, wLenOfLen, and dwOffsetToLen structure elements are
 * for use with variable length fields only.
 *
 * Note 3, the nLenOfField structure element is for use with fixed length
 * fields only.
 *
 * Note 4, all values of this structure except wFieldID can be assigned at
 * compile time.  The element wFieldID is a run-time parameter.  In addition,
 * the value of bFlags may change at run time.
 */
typedef struct
{
    unsigned int bFlags;            /* bit flags, see description below */
    unsigned int wFieldID;          /* the field ID */
    unsigned int wMaxLen;           /* maximum # of bytes to be copied */
    unsigned int wLenOfLen;         /* # of bytes in length: 0, 1, 2, or 4 */
    unsigned int wLenOfField;       /* # of bytes in the data field */
    unsigned long dwOffsetToField;  /* offset to start of field value */
    unsigned long dwOffsetToLen;    /* offset to its length */
} DB_TRANSLATE_FIELD_DEF;

/*
 * Flags of the Field Translation Definition Structure
 *
 * 16 bits:
 *  bits 11..15 -   Reserved for future enhancements.
 *
 *  DB_SEARCH_MASK:
 *
//??? document what these flags mean.
 *      - text search flags -
 *  DB_SEARCH_TEXT_EQUIVALENT:
 *  DB_SEARCH_TEXT_GOTO:
 *  DB_SEARCH_TEXT_SUBSTRING:
 *
 *      - arithmetic search flags -
 *  DB_SEARCH_EQUAL:
 *  DB_SEARCH_NOT_EQUAL:
 *  DB_SEARCH_LESS:
 *  DB_SEARCH_GREATER:
 *  DB_SEARCH_LESS_OR_EQUAL:
 *  DB_SEARCH_GREATER_OR_EQUAL:
 *  bits 8..10 -    For searches only, specifies the search relationship:
 *                      - arithmetic (=, !=, <, >, <=, >=)
 *                      - text (equivalent, goto, substring)
 *
 *  DB_SKIP_FIELD:
 *  bit 7 -     If set, the field is not to be translated.  The engine
 *              does nothing with the field if this bit is set.  It is
 *              simply ignored.  This can be used by applications to prevent
 *              unnecessary data from being written out to the database
 *              file, occupying bytes unnecessarily.  For example, fields
 *              that the user has not filled in or fields that have default
 *              values do not need to be written out and some disk space can
 *              be saved.  It can also be used by the application to read
 *              only specific fields of a database record.  Note, the use
 *              of this bit makes the most sense when the application has
 *              defined a table of field definitions, allowing the
 *              application to selectively read and write the fields.
 *
 *              Note, if the skip flag is set, nothing gets copied.  The
 *              destination is not even cleared to all zeros.
 *
 *  DB_VARIABLE_LENGTH:
 *  bit 6 -     If set, the field is variable length and the length must be
 *              determined by the length field or by counting bytes until
 *              a zero-byte is encountered.
 *
 *              If clear, the field is not variable length; it must be
 *              explicitely specified.
 *
 *  DB_ZERO_BYTE_TERMINATED:
 *  bit 5 -     If set, the variable length data is to be treated (converted
 *              to and from) as a zero-byte terminated string.
 *
 *              If clear, the variable length data has a length associated
 *              with it.  The length is accessed via the length offset value
 *              included in the translation structure.
 *
 *              Note 1, the max length value of the translate structure must
 *              include space for the zero-byte.
 *
 *              Note 2, the maximum length of a zero-byte terminated string
 *              is 64K (including the zero-byte).
 *
 *              Note 3, for long strings it is much more efficient to use
 *              a length and not the zero-byte terminater.
 *
 *  bit 4 -     reserved for future enhancements.
 *
 *  DB_ACCESS_MASK:
 *  DB_NOT_INDIRECT:
 *  DB_INDIRECT_NEAR:
 *  DB_INDIRECT_VIA_NEAR_HANDLE:
 *  bits 0..3 - specifies whether access to the field is indirect or not.
 *              There are two types of indirection supported: near indirect
 *              and indirect via a near handle to a far pointer table.  See
 *              constant values defined below.
 *
 *              Note 1, the indirect far pointer is not supported because
 *              far pointers on the target platform must be referenced via
 *              a handle into the indirect far pointer table.
 *
 *              Note 2, the indirect via near handle specifies a handle
 *              into the indirect far pointer table.  It is a near pointer
 *              to a far pointer where the far pointer is one of the entries
 *              within the indirect far pointer table.
 *
 *              Note 3, see the system manager documentation on memory
 *              management for details on using an indirect far pointer table.
 *
 *              Note 4, the indirection is only available for the data itself
 *              and not the length of the data.  The length, if needed, must
 *              be just an offset relative to the start of the data space.
 *
 * Note, the applicaiton MUST use the constants defined below to reference
 * the various bits (set, clear, or test).
 */
#define DB_APP_BITS_MASK            0xF000

#define DB_SEARCH_MASK              0x0700

    /* text search flags */
#define DB_SEARCH_TEXT_EQUIVALENT   0x0000
#define DB_SEARCH_TEXT_GOTO         0x0100
/* #define DB_SEARCH_TEXT_SUBSTRING    0x0200 */    /* not supported */

    /* arithmetic search flags */
#define DB_SEARCH_EQUAL             0x0000
#define DB_SEARCH_NOT_EQUAL         0x0100
#define DB_SEARCH_LESS              0x0200
#define DB_SEARCH_GREATER           0x0300
#define DB_SEARCH_LESS_OR_EQUAL     0x0400
#define DB_SEARCH_GREATER_OR_EQUAL  0x0500

#define DB_SKIP_FIELD               0x0080
#define DB_VARIABLE_LENGTH          0x0040
#define DB_ZERO_BYTE_TERMINATED     0x0020

#define DB_ACCESS_MASK              0x0007
#define DB_DIRECT_ACCESS            0x0000
#define DB_INDIRECT_NEAR            0x0001
/* #define DB_INDIRECT_FAR             0x0002 */    /* not supported */
#define DB_INDIRECT_VIA_NEAR_HANDLE 0x0003
/* #define DB_INDIRECT_VIA_FAR_HANDLE  0x0004 */    /* not supported */


/*
 * Sort Specification Structure
 *
 * The way in which an index is sorted is specified using an array of
 * the sort specification structures.  The first entry in the array specifies
 * the primary sort field, the second array entry specifies the secondary
 * sort field and so on up to the maximum allowed number of sort fields.
 *
 * Structure Elements
 * ------------------
 *
 * bCollateFlags:   The collate flags determine how the sort field is to be
 *              collated (ascending, descending, etc).  See the description
 *              of the flags below.
 *
 * wSortFieldID:    The ID of the field to be used for sorting.  All records
 *              in the index are sorted according to the value of this field
 *              within the record.
 *
 *  Note, the sort specification array should include at least one entry;
 *  however, it may contain none for those rare occassions when an index
 *  does not need to be sorted.
 */
typedef struct
{
    unsigned int bCollateFlags;         /* bit flags, see below */
    unsigned int wSortFieldID;          /* ID of primary sort field */
} DB_SORT_SPECIFICATION;

/*
 * Flags of the Sort Specification Structure
 *
 * 16 bits:
 *
 *  DB_SORT_ASCENDING:
 *  DB_SORT_DESCENDING:
 *  bit 15  -   If set, the fields are sorted in ascending order, lowest
 *              to highest.  If clear, the fields are sorted in descending
 *              order, highest to lowest.
 *
 *  DB_SORT_CASE_SENSITIVE:
 *  DB_SORT_CASE_INSENSITIVE:
 *  bit 14 -    If set, the fields are sorted without regard to the whether
 *              the text is uppercase or lowercase.  If clear, the case
 *              will make a difference.  This is for text fields only.
 *
 *  DB_SORT_ACCENT_SENSITIVE:
 *  DB_SORT_ACCENT_INSENSITIVE:
 *  bit 13 -    If set, the fields are sorted without regard to the accent
 *              of characters.  If clear, the accent will make a difference.
 *              This is for text fields only.
 *
//??? what else needs to go in here.  Note, the engine uses the system
//manager collate driver support; therefore, the collate sequence of the
//system manager collate driver also has to be defined within the collate
//flags.  The system manager collate driver currently only supports case
//and accent insensitive comparisons which is the default values.
//
 *  bits 0..12 -    Reserved for future enhancements.
 *
 *
 * Note, the case sensitive and accent sensitive options are not currently
 * supported.
 */
#define DB_SORT_ASCENDING           0x8000
#define DB_SORT_DESCENDING          0x0000
/* #define DB_SORT_CASE_SENSITIVE      0x4000 */
#define DB_SORT_CASE_INSENSITIVE    0x0000
/* #define DB_SORT_ACCENT_SENSITIVE    0x2000 */
#define DB_SORT_ACCENT_INSENSITIVE  0x0000
#define DB_VALID_SORT_MASK          (DB_SORT_ASCENDING)


/*
 * Index Definition Structure
 *
 * The index definition structure defines an index.  An index can be thought
 * of as a list of records.  This structure is for use when creating new
 * indexes and getting the index definition from an index ID.
 *
 * Structure Elements
 * ------------------
 *
 * bIndexAttributes:    Bit flags for defining attributes of the index.  See
 *              description of flags below.  Note, only the lower 8 bits
 *              are used.
 *
 * wRecordType: The type of the records contained in the index.  See the
 *              definition of the record type bit fields described previously
 *              in this file.  Note, only the lower 8 bits are used.
 *
 *              If the index is for records of mixed types, the mixed records
 *              must all be of the same generic type (i.e. records with
 *              fields, raw records, etc).  The value of this field will be
 *              masked internally so that only the generic type of the record
 *              is maintained for the index.
 *
 * wMaxNameLen: The maximum length of the index name to be returned when
 *              the application is getting the definition of an index.  Note,
 *              this parameter is NOT used when defining an index.
 *              
 * pszIndexName:    Pointer to the index name, a null-terminated string.
 *              Temporary indexes need not have a name as long as the
 *              application saves the index ID and uses that for all index
 *              operations.  However, any index that will be saved in the
 *              database file when the database is closed should be assigned
 *              a name which uniquely identifies the index.
 *
 *              Note, fixed index names, names the user doesn't create
 *              and cannot change, should be resourced.
 *
 *              Note, index names must be unique independent of case and
 *              accent.
 *
 * nSortSpecEntries:    Number of entries in the sort specification table.
 *
 * astSortSpecTable:    The array of sort specifications defines how the
 *              records of the index are to be sorted.  See above for the
 *              definition of the sort structure DB_SORT_SPECIFICATION.  The
 *              first entry in the array is the primary sort field, the
 *              second entry is the secondary sort field, and so on.
 */
//??? should the granularity be included here and let the app choose?
typedef struct
{
    unsigned int bIndexAttributes;  /* see definition of flags below */
    unsigned int wRecordType;       /* type of records in index */
    unsigned int wMaxNameLen;       /* max length of index name (with NULL) */
    char near *pszIndexName;        /* pointer to index name */
    unsigned int nSortSpecEntries;  /* number of entries in sort table */
    DB_SORT_SPECIFICATION astSortSpecTable[DB_MAX_SORT_FIELDS];
} DB_INDEX_DEFINITION;

/*
 * Index Attribute bit flags of the Index Definition Structure
 *
 * 16 bits:         INTERNAL NOTE:  Only 8 bits is stored in the database
 *                  file even though the code references it as a 16 bit
 *                  value.
 *
 *  bits 8..15 -    Not used.
 *
 *  bits 3..7 -     Reserved for future enhancements.
 *
 *  DB_SAVE_SELECT_LEVELS_IN_INDEX
 *  bit 2 -     If set, the selection level is saved with the index when it
 *              is saved to the database file.  If not set, the selection
 *              levels are cleared and will be clear when the index is loaded
 *              again.
 *
 *  DB_SAVE_KEYS_WITH_INDEX
 *  bit 1 -     If set, the sort keys are saved with the index.
 *
 *              Not saving the index keys saves bytes of file space
 *              (currently a long or 4 bytes per sort key per index entry),
 *              but means that access to that database, after opening it
 *              again, may be initially slow until the sort keys are
 *              established again.  Some indexes may not require the keys to
 *              be saved and, for those situations, the bytes saved is worth
 *              the overhead of resetting the keys when needed.
 *
 *  DB_INDEX_OF_MIXED_RECORD_TYPES
 *  bit 0 -     If set, the index is for records of different types, mixed
 *              set of records; however, the records must all be of the same
 *              generic record type (i.e. raw, linked, etc.).
 */
#define DB_INDEX_OF_MIXED_RECORD_TYPES  0x0001
#define DB_SAVE_KEYS_WITH_INDEX         0x0002
#define DB_SAVE_SELECT_LEVELS_IN_INDEX  0x0004
#define DB_VALID_INDEX_ATTRIB_FLAGS     \
    (DB_INDEX_OF_MIXED_RECORD_TYPES | DB_SAVE_KEYS_WITH_INDEX \
    | DB_SAVE_SELECT_LEVELS_IN_INDEX)


/**************************************************************************
 * Warning Ranges and Values:
 **************************************************************************/

/*
 * Warning Ranges
 *
 * All warning values are positive and are less than or equal to 1999 and
 * greater than or equal to 1000.
 */
#define DB_MAX_WARNING_VALUE                    (1999)
#define DB_MIN_WARNING_VALUE                    (1000)


/*
 * Miscellaneous Warnings
 */
#define DB_WARN_INDEX_EMPTY                     (1000)
    /* An operation on an empty index has been requested.  Attempting to
     * select or deselect all entries in an empty idnex will generate this
     * warning. */

#define DB_WARN_MEMORY_GETTING_LOW              (1001)
//??? Is this going to be reported anywhere by the engine?
    /* The allocated memory pool is getting dangerously low.  The application
     * should take measures to increase the memory pool either by freeing
     * any memory that it no longer requires or informing the user to close
     * some applications.  It is much safer to deal with the situation while
     * there is still some memory available rather than waiting until an
     * operation cannot be performed for lack of memory. */

#define DB_WARN_ADJUSTED_LAST_ENTRY             (1002)
    /* The last entry in the index has been deleted or removed; therefore,
     * the current index entry pointer had to be adjusted down by 1. */

#define DB_WARN_SEARCH_FOUND_NOTHING            (1003)
    /* The search operation did not come up with any matches and there is
     * nothing left to search. */


/**************************************************************************
 * Error Ranges and Values:
 **************************************************************************/

//??? add an explanation of each of the errors

/*
 * Error Ranges
 *
 * All error values are negative and are less than or equal to -1000 and are
 * greater than or equal to -1999.  Errors are divided into categories which
 * allows the application to cluster error definitions if so desired. 
 * Constants are defined for each error range.  Applications should ALWAYS
 * refer to errors via the defined name and not using the error value
 * directly.  The error values themselves are not guaranteed to remain the
 * same in future versions of the database engine.
 *
 * Error Ranges:
 * -1000 thru -1099     system errors
 * -1100 thru -1199     invalid arguments to the database engine
 * -1200 thru -1249     illegal operation requested of the database engine
 * -1250 thru -1299     illegal operation or database file corrupt
 * -1300 thru -1399     miscellaneous run-time errors
 * -1400 thru -1449     file I/O errors
 * -1450 thru -1499     memory allocation errors
 *  ...reserved...
 * -1500 thru -1599
 * -1600 thru -1699
 * -1700 thru -1799
 * -1800 thru -1899
 * -1900 thru -1999
 */
#define DB_MAX_ERR_VALUE                        (-1000)
#define DB_MIN_ERR_VALUE                        (-1999)

#define DB_MAX_SYSTEM_ERR                       (-1000)
#define DB_MIN_SYSTEM_ERR                       (-1099)

#define DB_MAX_INVALID_ARG_ERR                  (-1100)
#define DB_MIN_INVALID_ARG_ERR                  (-1199)

#define DB_MAX_INVALID_OPERATION1_ERR           (-1200)
#define DB_MIN_INVALID_OPERATION1_ERR           (-1249)
#define DB_MAX_INVALID_OPERATION2_ERR           (-1250)
#define DB_MIN_INVALID_OPERATION2_ERR           (-1299)

#define DB_MAX_RUNTIME_ERR                      (-1300)
#define DB_MIN_RUNTIME_ERR                      (-1399)

#define DB_MAX_FILE_IO_ERR                      (-1400)
#define DB_MIN_FILE_IO_ERR                      (-1449)

#define DB_MAX_MEMORY_ALLOC_ERR                 (-1450)
#define DB_MIN_MEMORY_ALLOC_ERR                 (-1499)


/*
 * System Errors
 *
 * System errors are reported when an unknown error is detected.  The most
 * likely cause of such errors would be if the system manager reports an
 * error that the engine does not know about and cannot find an appropriate
 * mapping.  These errors can also occur if the internal state that the
 * engine maintains somehow gets corrupted or out of synch with what it
 * should be; however, in general, these errors would seldom be reported; the
 * system would most likely crash beforehand.  System errors should
 * theoretically never occur.  If they do, they should be tracked down
 * immediately, especially during development.
 */
#define DB_ERR_SYSTEM                           (-1000)
#define DB_ERR_INTERNAL                         (-1001)
#define DB_ERR_FUNCTION_NOT_IMPLEMENTED         (-1002)

#define DB_ERR_INDEX_POINTER_CORRUPT            (-1003)
    /* The internal state of an index is not valid.  The current index
     * pointer points beyond the last entry in the index. */

/*
 * Invalid Argument Errors
 *
 * An invalid parmater has been detected in a call to one of the database
 * engine API functions.  Theoretically, these errors should not occur if
 * the application is well behaved.  The application should, at the least,
 * clump all invalid argument errors together and report them to the user
 * as an internal error (internal to the application).
 */
#define DB_ERR_DATABASE_ID_INVALID              (-1100)
#define DB_ERR_DATABASE_NAME_INVALID            (-1101)
#define DB_ERR_OWNER_NAME_INVALID               (-1102)
#define DB_ERR_FIELD_NAME_INVALID               (-1103)
#define DB_ERR_CONTROL_LEVEL_INVALID            (-1104)
#define DB_ERR_FIELD_ID_INVALID                 (-1105)
#define DB_ERR_INDEX_ID_INVALID                 (-1106)
#define DB_ERR_TRANSLATION_SPEC_INVALID         (-1107)
#define DB_ERR_UNKNOWN_DATA_TYPE                (-1108)
#define DB_ERR_NEW_FIELD_INVALID                (-1109)
#define DB_ERR_RECORD_TYPE_INVALID              (-1110)
    /* The application has attempted to create an index using an invalid
     * record type, an internal type or an unsupported type (linked).  Or,
     * the application has attempted to insert a record into an index of
     * the wrong type (eg. inserting a fielded record into an index of raw
     * records or inserting a different record type into an index that
     * doesn't support mixed record types).  Or, the application has
     * attempted a search operation in an index that does not have records
     * with fields. */


#define DB_ERR_INDEX_NAME_INVALID               (-1111)
#define DB_ERR_INDEX_ATTRIB_INVALID             (-1112)
    /* The attribute field of the index definition is not valid. */

#define DB_ERR_NEW_ATTRIB_INCOMPATIBLE          (-1113)
    /* The new index attributes are incompatible with the attributes of the
     * existing index.  This will occur if the existing index is of mixed
     * record types and the new index attributes specify an index that is
     * not of mixed record types. */

#define DB_ERR_SORT_COLLATE_INVALID             (-1114)
    /* Invalid collate flags in an entry of the sort specification table. */

#define DB_ERR_SORT_FIELD_INVALID               (-1115)
    /* Invalid field in an entry of the sort specification table. */

#define DB_ERR_TOO_MANY_SORT_ENTRIES            (-1116)
    /* Too many sort specification entries in the sort spec table. */

#define DB_ERR_SORT_SPEC_INVALID                (-1117)
    /* For one reason or another the sort spec is invalid. */

#define DB_ERR_SELECTION_FLAGS_INVALID          (-1118)
#define DB_ERR_FIELD_DEF_REC_INVALID            (-1119)

/*
 * Invalid Operation Errors
 *
 * An invalid operation has been requested of one of the database engine
 * API functions.  Theoretically, these errors should not occur if the
 * application is well behaved.  The application should, at the least,
 * clump all invalid operation errors together and report them to the user
 * as an internal error (internal to the application).
 */
#define DB_ERR_ENGINE_NOT_INITIALIZED           (-1200)
#define DB_ERR_DATABASE_BLOCK_IN_USE            (-1201)
#define DB_ERR_FILE_HDL_IN_USE                  (-1202)
#define DB_ERR_DATABASE_ALREADY_OPEN            (-1203)
#define DB_ERR_NO_SELECTED_DATABASE             (-1205)
#define DB_ERR_NOT_RECONSTRUCTING               (-1206)
#define DB_ERR_NOT_DELETING_FIELDS              (-1207)

#define DB_ERR_INDEX_EMPTY                      (-1208)
    /* An operation that cannot be peformed on an empty index has been
     * requested such as attempting to select or deselect the current index
     * entry, or get a record through an empty index. */

#define DB_ERR_NOT_SORTING                      (-1209)
#define DB_ERR_NOT_SEARCHING                    (-1210)

#define DB_ERR_BACKGROUND_OPERATION             (-1211)
    /* The requested operation is not allowed while the current background
     * operation is still in progress. */

#define DB_ERR_TOO_MANY_REFERENCES              (-1212)
    /* There are too many duplicate references to the same record. */

#define DB_ERR_TOO_MANY_OPEN_DATABASES          (-1213)
#define DB_ERR_NO_DATABASES_OPEN                (-1214)
#define DB_ERR_DATABASE_NOT_OPEN                (-1215)

/* Memory allocation errors resulting from an invalid operation. */

#define DB_ERR_IFP_TABLE_ENTRY_RANGE            (-1216)
#define DB_ERR_IFP_TABLE_FULL                   (-1217)
#define DB_ERR_IFP_TABLE_NOT_REGISTERED         (-1218)


/*
 * Invalid Operation or File Corruption Errors
 *
 * An invalid operation has most likely been requested of one of the
 * database engine API functions; however, the error could be the result of
 * a corrupt database file as well.  Theoretically, these errors should not
 * occur if the application is well behaved and the file integrity is
 * maintained.  The application should, at the least, clump all invalid
 * operation errors together and report them to the user as an internal
 * error (internal to the application).
 */
#define DB_ERR_TOO_MANY_INDEXES                 (-1250)
#define DB_ERR_TOO_MANY_FIELDS                  (-1251)
#define DB_ERR_WRONG_OWNER                      (-1252)

#define DB_ERR_RAW_RECORD_TOO_BIG               (-1253)
    /* A raw record is too big to fit in the application's data buffer. */

#define DB_ERR_CONFIG_RECORD_MISSING            (-1254)
#define DB_ERR_CONFIG_RECORD_TOO_BIG            (-1255)
#define DB_ERR_CONFIG_RECORD_WRONG_SIZE         (-1256)
#define DB_ERR_RECORDS_OUT_OF_ORDER             (-1257)
#define DB_ERR_DUPLICATE_INDEX                  (-1258)
#define DB_ERR_FIELD_NOT_FOUND                  (-1259)
#define DB_ERR_INDEX_NOT_FOUND                  (-1260)
#define DB_ERR_RECORD_NOT_FOUND                 (-1261)
#define DB_ERR_INDEX_PTR_REC_MISSING            (-1262)

#define DB_ERR_INDEX_PTR_REC_INVALID            (-1263)
    /* This error is reported by the load index function if the index
     * pointer record is marked invalid.  The index pointer record should
     * theoretically only be marked invalid if the system had crashed while
     * it was being updated.  Therefore, the IN-USE bit of the file status
     * should still be set and the application should have requested
     * reconstruction after calling the function to find out if
     * reconstruction is necessary which would have returned TRUE.  The load
     * index function should therefore not have been called.  The only other
     * possibility, a remote one, would be for the file to be corrupted
     * from an external source at which point anything's possible and there's
     * not much that can be done to remedy the situation, although
     * reconstruction may be attempted. */

#define DB_ERR_INDEX_REC_INVALID                (-1264)
    /* This error is reported by the load index function if an index
     * record is marked invalid.  The index records should theoretically
     * only be marked invalid if the system had crashed while one was being
     * updated.  Therefore, the IN-USE bit of the file status
     * should still be set and the application should have requested
     * reconstruction after calling the function to find out if
     * reconstruction is necessary which would have returned TRUE.  The load
     * index function should therefore not have been called.  The only other
     * possibility, a remote one, would be for the file to be corrupted
     * from an external source at which point anything's possible and there's
     * not much that can be done to remedy the situation, although
     * reconstruction may be attempted. */

#define DB_ERR_NO_CORRESPONDING_ENTRY           (-1265)
    /* The DBMatchCurrentAcrossIndexes function did not find a match in the
     * destination index which corresponds to the current index of the source
     * index. */


/*
 * Miscellaneous Run-Time Errors
 */
#define DB_ERR_DATABASE_FILE_CORRUPT            (-1300)
    /* The database file is corrupt and cannot be processed. */

#define DB_ERR_NEWER_FILE_REV                   (-1301)
    /* Forward compatibility error -- the specified database was created
     * with a newer version of the database engine with a format not
     * compatible with the current version that is in use; therefore, the
     * specified database file cannot be accessed. */

#define DB_ERR_CONFIG_REC_INVALID               (-1302)
    /* The configuration record is marked invalid, the application should
     * verify its contents and/or write out a new one. */

#define DB_ERR_NO_SORT_SPEC                     (-1303)
    /* An attempt was made to sort an index that doesn't have a sort spec. */

/*
 * File I/O Errors
 */
#define DB_ERR_FILE_ALREADY_EXIST               (-1400)
#define DB_ERR_FILE_DOES_NOT_EXIST              (-1401)
#define DB_ERR_FILE_NOT_A_DATABASE              (-1402)
#define DB_ERR_HID_FILE_ACCESS_DENIED           (-1403)
#define DB_ERR_SYS_FILE_ACCESS_DENIED           (-1404)
#define DB_ERR_RO_FILE_ACCESS_DENIED            (-1405)
#define DB_ERR_BAD_FILE_NAME                    (-1406)
#define DB_ERR_DISK_FULL                        (-1407)
#define DB_ERR_FILE_NOT_FOUND                   (-1408)
#define DB_ERR_PATH_NOT_FOUND                   (-1409)
#define DB_ERR_TOO_MANY_OPEN_FILES              (-1410)
#define DB_ERR_DEVICE_WRITE_PROTECTED           (-1411)
#define DB_ERR_DEVICE_NOT_READY                 (-1412)
//??? Improve meaning of the following (requires system manager support):
#define DB_ERR_NETWORK                          (-1413)
#define DB_ERR_ACCESS_DENIED                    (-1414)

/*
 * Memory Allocation Errors
 *
 * The database engine performs memory allocation/deallocation to manage
 * the memory resources for a number of different operations.  The memory
 * allocation is accomplished using the system manager services which in
 * turn could generate any one of a number of errors.
 *
 * Note, there are other errors besides the ones listed here which are
 * generated from the internal memory allocation functions but are directly
 * results of invalid operations.  Those errors are categorized with the
 * invalid operation errors.
 */
#define DB_ERR_INSUFFICIENT_MEMORY              (-1450)


/**************************************************************************
 * Function Prototypes By Module
 **************************************************************************/

/* DBACCNT */

int DBAccountingReport(DB_ACCOUNTING_REPORT near *pstAccountingReport);


/* DBALLOC */

    /* none */


/* DBBLCKMG */

    /* none */


/* DBCMPARE */

    /* none */


/* DBCONFIG */

int DBCreateAppConfig(void near *pData, unsigned int wLen);

int DBGetAppConfig(void near *pData, unsigned int wMaxLen);

int DBSetAppConfig(void near *pData, unsigned int wLen);


/* DBFILEHD */

    /* none */


/* DBFILEIO */

    /* These functions have been made accessible for convenience. */

int DBCloseFile(FILE near *pstFileHdl);

int DBCreateFile(char near *pszFileName, FILE near *pstFileHdl);

int DBDeleteFile(char near *pszFileName);

int DBEndFile(FILE near *pstFileHdl);

int DBDoesDirectoryExist(char near *pszDirectoryName);

int DBDoesFileExist(char near *pszFileName);

int DBFileSeek(FILE near *pstFileHdl, unsigned int wSeekMode, \
        unsigned long dwRelativePosition);

int DBFlushFileBuffer(FILE near *pstFileHdl);

int DBGetFileAttr(char near *pszFileName, unsigned int near *pwAttributes);

int DBGetFilePosition(FILE near *pstFileHdl,
        unsigned long near *pdwFilePosition);

int DBGetFileSize(FILE near *pstFileHdl, unsigned long near *pdwFileSize);

int DBOpenFile(char near *pszFileName, FILE near *pstFileHdl);

int DBReadFromFile(FILE near *pstFileHdl, void far *lpData, unsigned int wLen, \
        unsigned int near *pwLenRead);

int DBRenameFile(char near *pszFileName, char near *pszNewName);

int DBRewindFile(FILE near *pstFileHdl);

int DBSetFileAttr(char near *pszFileName, unsigned int wAttributes);

int DBWriteToFile(FILE near *pstFileHdl, void far *lpData, unsigned int wLen);


/* DBFILEMG */

int DBClearDatabaseInUseFlag(void);

int DBCloseDatabase(unsigned int wDatabaseID, char near *pszAppOwnerName);

int DBDeleteDatabase(char near *pszDatabaseName, char near *pszAppOwnerName);

int DBNewDatabase(char near *pszDatabaseName, char near *pszAppOwnerName,
        unsigned int near *pwDatabaseID);

int DBOpenDatabase(char near *pszDatabaseName, char near *pszAppOwnerName, \
        unsigned int near *pwDatabaseID);

int DBSelectDatabase(unsigned int wDatabaseID, char near *pszAppOwnerName);


/* DBFLDMG */

int DBCancelDeleteFieldDefAndData(void);

int DBContinueDeleteFieldDefAndData(unsigned int wFieldID, \
        unsigned int near *pwPercentDone, unsigned int wRecordSetSize);

int DBCreateFieldDefinition(DB_FIELD_DEFINITION near *pstFieldDef, \
        unsigned int near *pwNewFieldID);

int DBDeleteFieldDefAndAllData(unsigned int wFieldID);

int DBGetAllFieldIDs(unsigned int near *pwFieldIDTbl, \
        unsigned int near *pwNumberOfDefinedFields, unsigned int wMax);

int DBGetFieldDefinition(unsigned int wFieldID, \
    DB_FIELD_DEFINITION near *pstFieldDef);

int DBGetFieldIDFromName(char near *pszFieldName, \
      unsigned int near *pwFieldID);

int DBGetNumberOfDefinedFields(unsigned int near *pwNumberOfDefinedFields);

int DBReplaceFieldDefinition(unsigned int wFieldID, \
    DB_FIELD_DEFINITION near *pstFieldDef);

int DBStartDeleteFieldDefAndData(unsigned int wFieldID, \
    unsigned long near *pdwTotalBytes);


/* DBINDXIO */

int DBCreateIndexPtrRec(unsigned int wMaxNumberOfIndexes);

int DBLoadIndexes(void);

int DBSaveIndexes(void);


/* DBINDXMG */

int DBCopyIndexEntry(unsigned int wSrcIndexID, \
        unsigned int wDstIndexID);

int DBCreateCopyOfIndex(unsigned int wIndexID, unsigned int bSelectFlags, \
        char near *pszNewIndexName, unsigned int near *pwNewIndexID);

int DBCreateNewIndex(DB_INDEX_DEFINITION near *pstIndexDef, \
        unsigned int *pwNewIndexID);

int DBDeleteIndex(unsigned int wIndexID);

int DBDeselectAll(unsigned int wIndexID, unsigned int bSelectFlags);

int DBDeselectCurrent(unsigned int wIndexID, unsigned int bSelectFlags);

int DBGetIndexDefinition(unsigned int wIndexID, \
        DB_INDEX_DEFINITION near *pstIndexDef);

int DBGetIndexIDFromName(char near *pszIndexName, \
        unsigned int near *pwIndexID);

int DBGetIndexIDFromRecType(unsigned int wRecordType, \
        unsigned int near *pwIndexID);

int DBGetNumberOfIndexes(unsigned int near *pwNumberOfIndexes);

int DBGetNumberOfRecords(unsigned int wIndexID, unsigned int bSelectFlags, \
        unsigned long near *pdwNumberOfRecords);

int DBGetNumberOfRecordsToCur(unsigned int wIndexID, \
        unsigned int bSelectFlags, unsigned long near *pdwNumberOfRecords);

int DBIsCurrentRecordSelected(unsigned int wIndexID, \
        unsigned int bSelectFlags);

int DBMatchCurrentAcrossIndexes(unsigned int wSrcIndexID, \
        unsigned int wDstIndexId);

int DBRenameIndex(unsigned int wIndexID, char near *pszNewNameName);

int DBReplicateSelectionFlags(unsigned int wSrcIndexID, \
        unsigned int wDstIndexId);

int DBSelectAll(unsigned int wIndexID, unsigned int bSelectFlags);

int DBSelectCurrent(unsigned int wIndexID, unsigned int bSelectFlags);

int DBSetIndexAttributes(unsigned int wIndexID, unsigned int bIndexAttributes);

int DBToBottom(unsigned int wIndexID, unsigned int bSelectFlags);

int DBToLastCurrent(unsigned int wIndexID);

int DBToNext(unsigned int wIndexID, unsigned int bSelectFlags);

int DBToPrevious(unsigned int wIndexID, unsigned int bSelectFlags);

int DBToTop(unsigned int wIndexID, unsigned int bSelectFlags);


/* DBINIT */

int DBInit(unsigned int wControlLevel);

void DBTerminate(void);


/* DBRECIO */

    /* none */


/* DBRECMG */

int DBDeleteRecord(unsigned int wIndexID, unsigned int bSearchAllIndexes);

int DBGetFieldValue(unsigned int wIndexID, void far * near *hData, \
        DB_TRANSLATE_FIELD_DEF near *pstTransDef);

int DBGetRecord(unsigned int wIndexID, void far * near *hData, \
        DB_TRANSLATE_FIELD_DEF near *pastTransTbl, \
        unsigned int wNumOfEntriesOrMaxLen);

int DBInsertRecord(unsigned int wIndexID, void far * near *hData, \
        unsigned int wRecordType, DB_TRANSLATE_FIELD_DEF near *pastTransTbl, \
        unsigned int wNumOfEntriesOrLen);

int DBModifyRecord(unsigned int wIndexID, void far * near *hData, \
        unsigned int wRecordType, DB_TRANSLATE_FIELD_DEF near *pastTransTbl, \
        unsigned int wNumOfEntriesOrLen);

int DBRemoveRecordFromIndex(unsigned int wIndexID);

int DBReplaceRecord(unsigned int wIndexID, void far * near *hData, \
        unsigned int wRecordType, DB_TRANSLATE_FIELD_DEF near *pastTransTbl, \
        unsigned int wNumOfEntriesOrLen, unsigned int bSearchAllIndexes);


/* DBRECON */

int DBCancelIndexReconstruction(void);

int DBContinueIndexReconstruction(unsigned int near *pwPercentDone,
        unsigned int wRecordSetSize);

int DBIsReconstructionNeeded(void);

int DBStartIndexReconstruction(unsigned long near *pdwTotalBytes);


/* DBSEARCH */

int DBCancelSearch(void);

int DBContinueSearch(unsigned int near *pwPercentDone, \
        unsigned int wRecordSetSize);

    /* template functions */

int DBSearchCurrentForTemplateMatch(unsigned int wIndexID, \
        void far * near *hData, DB_TRANSLATE_FIELD_DEF near *pastTransTbl, \
        unsigned int wNumOfEntries);

int DBStartFindNextTemplateMatch(unsigned int wIndexID, \
        void far * near *hData, DB_TRANSLATE_FIELD_DEF near *pastTransTbl, \
        unsigned int wNumOfEntries, unsigned int bSearchSelectFlags, \
        unsigned int bSkipCurrentEntry);

int DBStartFindPrevTemplateMatch(unsigned int wIndexID, \
        void far * near *hData, DB_TRANSLATE_FIELD_DEF near *pastTransTbl, \
        unsigned int wNumOfEntries, unsigned int bSearchSelectFlags, \
        unsigned int bSkipCurrentEntry);

int DBStartSelectAllTemplateMatches(unsigned int wIndexID, \
        void far * near *hData, DB_TRANSLATE_FIELD_DEF near *pastTransTbl, \
        unsigned int wNumOfEntries, unsigned int bSearchSelectFlags, \
        unsigned int bMatchSelectFlags);

        /* text functions */

int DBSearchCurrentForTextMatch(unsigned int wIndexID, char near *pszText);

int DBStartFindNextTextMatch(unsigned int wIndexID, char near *pszText, \
        unsigned int bSearchSelectFlags, unsigned int bSkipCurrentEntry);

int DBStartFindPrevTextMatch(unsigned int wIndexID, char near *pszText, \
        unsigned int bSearchSelectFlags, unsigned int bSkipCurrentEntry);

int DBStartSelectAllTextMatches(unsigned int wIndexID, char near *pszText, \
        unsigned int bSearchSelectFlags, unsigned int bMatchSelectFlags);


/* DBSORT */

int DBCancelSortIndex(void);

int DBContinueSortIndex(unsigned int nRecordSetSize);

int DBCompareRecords(unsigned int wRecordType1, \
        void far * near *hData1, \
        DB_TRANSLATE_FIELD_DEF near *pastTransTbl1, \
        unsigned int wNumOfEntries1, \
        unsigned int wRecordType2, \
        void far * near * hData2, \
        DB_TRANSLATE_FIELD_DEF near *pastTransTbl2, \
        unsigned int wNumOfEntries2, \
        DB_SORT_SPECIFICATION near *pastSortSpecTable, \
        unsigned int nSortSpecEntries, \
        int near *piComparisonResults);

int DBFakeResetSort(unsigned int wIndexID, unsigned int nSortSpecEntries, \
        DB_SORT_SPECIFICATION near *pastSortSpecTable);

int DBStartSortIndex(unsigned int wIndexID, unsigned int nSortSpecEntries, \
        DB_SORT_SPECIFICATION near *pastSortSpecTable);


/* DBSTRING */

    /* These functions have been made accessible for convenience. */

int DBStringCompare(char far *lpszString1, char far *lpszString2);

char far *DBStringCopy(char far *lpszDestination, char far *lpszSource);

char far *DBStringCopyN(char far *lpszDestination, char far *lpszSource,
        unsigned int wMaxLen);

unsigned int DBStringLen(char far *lpszString);


/* DBUTILS */

    /* These functions have been made accessible for convenience. */

int DBExtractFileComponents(char far *lpszSrc, char far *lpszDrive, \
        char far *lpszPath, char far *lpszFName, char far *lpszExt);

void DBFillChar(char cFillChar, char far *lpszDst, unsigned int wLen);

int DBMemoryCompare(void far *lpMem1, void far *lpMem2, \
        unsigned int dwByteCount);

void far *DBMemoryCopy(void far *lpDestination, void far *lpSource, \
        unsigned long dwByteCount);


#pragma pack()                  /* Reinstate default packing. */
#endif

