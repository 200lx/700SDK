/* SCCS info - Module %M%  Version %I%  Date %G%  Time %U% */
/********************************************************************
 * DB PRIVATE DECLARATIONS -- only database modules should rely on  *
 * these functions/definitions                                      *
 ********************************************************************/

#ifndef _DB_PVT_
#define _DB_PVT_


/* If ANTAGONISTIC is set, db will request a memory change from SysMgr */
/* for every record.  This will thrash much more, and hopefully catch */
/* any illegal uses of far pointers.  If an application grabs a far */
/* pointer and expects it to remain stable between certain calls to */
/* DB functions, this should make that function crash and burn. */

#ifdef ANTAGONISTIC
#define DB_GRANULARITY 1
#else
#define DB_GRANULARITY 40      /* Size of mem chunks allocated by SysMgr */
                               /*   not in bytes, but in whole records */
#endif

#define STACK_SIZE 15          /* Size of the stack used by the fisl interpreter */
                               /* and unparser. */

#define DB_MAXLOOKUPS (DB_GRANULARITY * (65535 / (DB_GRANULARITY * sizeof(LOOKUPENTRY))))

typedef long int SLONG;


typedef struct {
  char SortKey[DB_MAXDIGITS];
  } TempViewptKey;



enum FISLTokens {
ERROR_TOKEN,       /* 00 */
NOT_TOKEN,         /* 01 */
OR_TOKEN,          /* 02 */
AND_TOKEN,         /* 03 */
EQ_TOKEN,          /* 04 */
LE_TOKEN,          /* 05 */
LT_TOKEN,          /* 06 */
GE_TOKEN,          /* 07 */
GT_TOKEN,          /* 08 */
NE_TOKEN,          /* 09 */
IN_TOKEN,          /* 0a */
CONTAINS_TOKEN,    /* 0b */

LPAREN_TOKEN,      /* 0c */
RPAREN_TOKEN,      /* 0d */
SEPARATOR_TOKEN,   /* 0e */
TO_TOKEN,          /* 0f */

NUMBER_TOKEN,      /* 10 */
STRING_TOKEN,      /* 11 */
NAME_TOKEN,        /* 12 */
BOOLNAME_TOKEN,    /* 13 */
TIME_TOKEN,        /* 14 */
DATE_TOKEN,        /* 15 */
CATEGORY_TOKEN,    /* 16 */
USERTYPE_TOKEN,    /* 17 */

/* Special values emitted by parser, not corresponding to strings */
EOL_TOKEN,         /* 18 */
PLACEHOLDER_TOKEN, /* 19 */

/* More regular tokens */
STAR_TOKEN,        /* 1a */
};




/* Quick and simple hash value constructed to try to determine if the */
/* sort order has changed.  If it has, the viewpt tables are invalidated. */
/* Although at first glance, it might seem that a simple XOR of all the */
/* related fields would not catch double/triple changes, the values for */
/* all the fields happen to rarely intersect.            */
/*     Country  - ?                                      */
/*     CodePage - 0x0437,0x0850,0x0856,...               */
/*     Sort     - 0x0000,0x0001,0x0002                   */
/*     Keyboard - 0x0001,0x0002,...,0x8000 (single bits) */
/*     Language - 0x5355,...   (two chars 'US','GR',etc.)*/
/*     KeyBez   - 0x0000, 0xFFFF                         */

#define ConstructMagicSortCode(x) ((x->Country)^(x->CodePage)^(x->Sort)^\
                                   (x->Keyboard)^(x->Language)^KeyBezLoaded)



#define Write(handle, buffer)  {if (_dos_write(handle, &buffer, sizeof(buffer),&xsize) || \
                                    xsize!=sizeof(buffer))  { _dos_close(handle); return DB_WRITE; }}
#define Read(handle, buffer)   {if (_dos_read(handle, &buffer, sizeof(buffer), &xsize) || \
                                    xsize!=sizeof(buffer))  { _dos_close(handle); return DB_READ; }}

#define DebugPoint(chr)  _asm mov ah,2  _asm mov dl,chr  _asm int 21h


//#undef m_get_far_handle
//#define m_get_far_handle(x) m_get_far_block(x,0L)


extern char ViewptRecBuf[2048],ViewptRecBuf2[2048];
extern int xsize;
extern FILEID Signature;
extern char radixpoint;
extern char String[128];
extern char UserField[128];
extern int KeyBezLoaded;


#define FILE_BEGIN sizeof(FILEID)



int qvc_Random(int l,int r);


int far comparenumbers(char far *str1,char far *str2);
int far comparedates(DB_DATE far *date1,DB_DATE far *date2);
int far comparetimes(DB_TIME far *time1,DB_TIME far *time2);
int far contains(char far *string,char far *test);
int far comparecategory(char far *string,char far *test);

int ReadViewptTable(DBBLOCK APP_NEAR *dblk);
int LoadViewptDef(DBBLOCK APP_NEAR *dblk, int viewptnumber);
int LoadViewptDef2(DBBLOCK APP_NEAR *dblk, int viewptnumber);
int InvalidateViewptTable(DBBLOCK APP_NEAR *dblk, int viewptnum);

int AdjustTable(void far * APP_NEAR * APP_NEAR *table, unsigned int actualsize,
                unsigned int APP_NEAR *tablesize,unsigned int granularity,
                long int adjust);

void PackLookup(void far *lookup, int n);
void UnpackLookup(void far *lookup, int n);

int ReadLookup(DBBLOCK APP_NEAR *dblk);
int AppendLookup(DBBLOCK APP_NEAR *dblk);
void RemoveLookupTable(DBBLOCK APP_NEAR *dblk);

int InsertLookupEntry(DBBLOCK APP_NEAR *dblk, char recordtype, int recordnum);


void AbortCleanup(DBBLOCK APP_NEAR *dblk);
int MoveBlock(int handle, long int from_pos, long int to_pos,long int size);
void SortLookup(LOOKUPENTRY far *lookup, int N, int field);

int GetBooleanField(DBBLOCK APP_NEAR *dblk, char far *srcrec, int index);

int EmitToken(int token);
int CheckField(void);
int GetToken(int far *error);
int Match(int token);
int val(void);
int range(void);
int bool(void);
int notexp(void);
int andboolexp(void);
int expr(void);

int AdvanceFISL(char far *fisl);
int PopString(int APP_NEAR *stacktop, char far * APP_NEAR *stack, char far *String, int *top_op);
int PushString(int APP_NEAR *stacktop, char far * APP_NEAR *stack, char far *String, int *top_op);



int FindMemoryRecord(DBBLOCK APP_NEAR *dblk, char far *buffer, char far *searchstring,
                     int flags, int far *field, unsigned int far *pos,
                     int far *startfield, int sfields);
int InitializeMemoryFind(DBBLOCK APP_NEAR *dblk, char far *searchstring, int far *field,
                int far *pos, int flags, int far *startfield, int far *sfields);


void makestring(char far *str, char far *buf, int sig);
int countsig(char far *str);
void TransformPassword(char far *password, char far *storage);

int slstrcat(char far *dest, char far *src);


TempViewptKey far *KeyAddr(int n);
int qvc_Compare(int x,int y);
void VptQuickSort(int l,int r);
void qvc_Swap(int x,int y);
void CompareAutoGoto(DBBLOCK APP_NEAR *dblk,int n,int field,int stringtype,int m,unsigned char far *searchstring,FIELDDEF far *f,char APP_NEAR *usbuf,int ascending);
void JollyGr(char far *str);
int LittleUndoHeaderUpdateFunction(DBBLOCK APP_NEAR *dblk, RECORDOFFSET ofs, RECORDHEADER *rec, int mark, LOOKUPENTRY far *look);
unsigned int _dos_getattr2(char far *filename);



int far _Encode(DBSMPREFIX1  char far *password, char far *record, unsigned int size,unsigned int offset);
#define Encode(password,record,size,offset) \
        (DB_DIRECT(1)? \
        _Encode(DBSMCALL1 (password),(record),(size),(offset)): \
        c_service(F_ENCODE,(void far *)(password),(void far *)(record), (size), (offset)))

int far _AvailLookupEntry(DBSMPREFIX1  DBBLOCK APP_NEAR *dblk, char recordtype);
#define AvailLookupEntry(dblk,recordtype) \
        (DB_DIRECT(1)? \
        _AvailLookupEntry(DBSMCALL1 (dblk),(recordtype)): \
        c_service(F_AVAILLOOKUPENTRY,(void *)(dblk),(recordtype)))

int far comparecategory1(char far *string,char far *test);
int far comparecategory2(char far *string,char far *test);
#define comparecategory(string,test) \
        (DB_OVL==1 ? comparecategory1((string),(test)):comparecategory2((string),(test)))

int far contains1(char far *string,char far *test);
int far contains2(char far *string,char far *test);
#define contains(string,test) \
        (DB_OVL==1 ? contains1((string),(test)):contains2((string),(test)))



#define Decode(password,record,size,offset)  Encode(password,record,size,offset)


#endif
