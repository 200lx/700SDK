#define CONFLICT_FILE1    1
#define CONFLICT_FILE2    2
#define CONFLICT_BOTH     4
#define CONFLICT_NEITHER  8
#define CONFLICT_ALL      (CONFLICT_NEITHER|CONFLICT_FILE1|CONFLICT_FILE2|CONFLICT_BOTH)

#define CONFLICT_ADD      16
#define CONFLICT_DELETE   32
#define CONFLICT_ADD_DELETE (CONFLICT_ADD|CONFLICT_DELETE)

#define CONFLICT_QUERY    0
#define CONFLICT_ABORT    (-1)

#define CONFLICT_ERROR    (-2)

#define METER_CREATE    1
#define METER_DRAW      0
#define METER_DESTROY   2


#ifndef INTUIT
extern LHWINDOW ConflictProgress;
#endif

/******************************** NOTE ********************************/
/* THE CALLING APPLICATION MUST ALLOCATE A LHAPI BLOCK AND INITIALIZE */
/* LHAPI USING InitializeLHAPI BEFORE CALLING ANY OF THESE ROUTINES!  */

int far m_conflict_records(char *filename1,char *filename2,int flags,int fields,
                       char far *fieldlist[],char far *rec1str[],
                       char far *rec2str[],char override[]);

/* Sets default for m_conflict_records--
      CONFLICT_QUERY,CONFLICT_FILE1,CONFLICT_FILE2,CONFLICT_BOTH */
int far m_conflict_default(int which);

int far m_conflict_dialog(char far *title,int messages, char far *message[],
                      int startingfkey,int fkeys,char far *fkey[]);

/* Displays error--may be multiple lines with 1 CR between lines. */
/* Returns CONFLICT_ERROR if too many lines or too large of a message. */
int far m_conflict_error(char far *title,char far *message);

/* Sets return code for calling application--if non-zero, caller terminates */
/* a multiple task sequence. */
void far m_conflict_return_error(unsigned char error);

int far m_conflict_progress(unsigned int numerator,unsigned int denominator,int create);
int far m_initialize_logfile(char *file1, char *file2, char *logfile);


void far m_conflict_getresource(char far *buffer,int formatmsgno,int number);

