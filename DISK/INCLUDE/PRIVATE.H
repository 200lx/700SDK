/* SCCS info:   Module private.h  Version 1.1  Date 11/09/93  Time 15:24:06 */

/* $Header:   T:/HH/INCLUDE/VCS/PRIVATE.H_V   1.2   25 Mar 1993 05:41:16   KIM  $ */
/**************************************************************************
 *
 * Name:       PRIVATE.H
 * Date:       01/24/93
 * Abstract:   System Manager: Non-public functions defined here.
 *                             Public functions defined in INTERFAC.H
 *
 * NOTE: This file may be used in conjunction with INTERFAC.H.  This file
 *       compliments INTERFAC.H by defining functions that are not public.
 *
 *       If used with INTERFAC.H, please define INTERFAC_H so it will
 *       have duplicate definition of control variables.
 *
 * -------------------------------------------------------------------------
 *                  Copyright (c) 1992 Lotus Development Corp.
 *                          All rights reserved.
 ***************************************************************************
 *
 * $Log:   T:/HH/INCLUDE/VCS/PRIVATE.H_V  $
 * 
 *    Rev 1.2   25 Mar 1993 05:41:16   KIM
 * Moved entry for ComAutoSet to private.h/mac. Non-public routine.
 * 
 *    Rev 1.1   05 Feb 1993 16:51:56   KIM
 * Added Ovl_m_errmsg.
 * 
 *    Rev 1.0   25 Jan 1993 23:32:38   KIM
 * Initial revision.
 *
 **************************************************************************/
#if !defined(INTERFAC_H)

 #ifdef   API2
   #define  c_service                  c_service2
   #define  c_service_near_ptr         c_service2_near_ptr
   #define  c_service_far_ptr          c_service2_far_ptr

   /**************  Memory block prototypes *********************/

   #define  c_service_based_ptr        c_service2_based_ptr
   #define  c_service_far_mem          c_service2_far_mem
   #define  c_service_reg_based        c_service2_reg_based
   #define  c_service_long_based       c_service2_long_based
   #define  c_service_long_far         c_service2_long_far
   #define  c_service_reg_far          c_service2_reg_far
   #define  c_service_free_static      c_service2_free_static
   #define  c_service_get_avail_mem    c_service2_get_avail_mem

   #define  CLASS_BASE     0x40
   #define  FNCT_BASE      0x01
   #define  SC_APIMGT      (CLASS_BASE + 0)
 #else
   #define  CLASS_BASE     0x0
   #define  FNCT_BASE      0x0
 #endif      


 #if !defined(DISTANCE)
   #define  DISTANCE
 #endif

int DISTANCE c_service(unsigned int,...);
void near * DISTANCE c_service_near_ptr (unsigned int,...);
void far * DISTANCE c_service_far_ptr(unsigned int,...);

/**************  Memory block prototypes *********************/
int  DISTANCE c_service_based_ptr(unsigned int dummy1,_segment *dummy2,unsigned long int dummy3);
int  DISTANCE c_service_far_mem(unsigned int dummy1,void *dummy2,unsigned long int dummy3);
int  DISTANCE c_service_get_static(unsigned int dummy1,void far *dummy2,unsigned long int dummy3);
void DISTANCE c_service_reg_based(unsigned int dummy1, _segment *dummy2 ,unsigned int dummy3);
int  DISTANCE c_service_long_based(unsigned int dummy1,_segment *dummy2,unsigned long int dummy3);
int  DISTANCE c_service_long_far(unsigned int dummy1,void *dummy2,unsigned long int dummy3);
void DISTANCE c_service_reg_far(unsigned int dummy1, void *dummy2 ,unsigned int dummy3, unsigned int dummy4);
int  DISTANCE c_service_free_static(unsigned int dummy1,void far *dummy2);
unsigned long int DISTANCE c_service_get_avail_mem(unsigned int dummy1);

/* assign constants for the service class numbers */
/* SC_MAXNUM is the maximum class number allowed */

#define SC_FP           (CLASS_BASE + 0)
#define SC_EVENT        (CLASS_BASE + 1)
#define SC_MENU         (CLASS_BASE + 2)
#define SC_SCREEN       (CLASS_BASE + 3)
#define SC_EDIT         (CLASS_BASE + 4)
#define SC_FILE         (CLASS_BASE + 5)
#define SC_PM           (CLASS_BASE + 6)
#define SC_CB           (CLASS_BASE + 7)
#define SC_SOUND        (CLASS_BASE + 8)
#define SC_MM           (CLASS_BASE + 9)
#define SC_BG           (CLASS_BASE + 10)
#define SC_DTIME        (CLASS_BASE + 11)
#define SC_PRINTER      (CLASS_BASE + 12)
#define SC_CONFIG       (CLASS_BASE + 13)
#define SC_COMM         (CLASS_BASE + 14)
#define SC_MISC         (CLASS_BASE + 15)
#define SC_VIDVIR       (CLASS_BASE + 16)
#define SC_VIDPHY       (CLASS_BASE + 17) /* not used directly by accessories */
#define SC_GRDISP       (CLASS_BASE + 18)
#define SC_KEY          (CLASS_BASE + 19)
#define SC_RSRC         (CLASS_BASE + 20)
#define SC_HELP         (CLASS_BASE + 21)
#define SC_COL		    (CLASS_BASE + 22)
#define SC_RESV		    (CLASS_BASE + 23) /* Reserved for ccMail use */

#define SC_MAXNUM_JAG   22                  /* for jag error check */

#define SC_RESERVED1    (CLASS_BASE + 25)   /* For Sys Mgr internal use */

 #ifdef XBS
#define SC_XBS_UNIQUE	(CLASS_BASE + 26)   /* Different platform */
 else
#define IT_IS_RESERVED	(CLASS_BASE + 26)   /* Do not use */
 #endif

#endif /* !defined(INTERFAC_H) */

#define F_COMM_AUTOSET   (SC_COMM * 256) + 34 + FNCT_BASE
#define ComAutoSet(a,b)    \
	c_service(F_COMM_AUTOSET,(struct COM_PORT_DATA *)a, (struct COM_SETTINGS *)b)


#define SM_OVL_MESSAGE               (SC_RESERVED1 * 256) +  0 + FNCT_BASE
#define OVL_MESSAGE(a,b,c,d)         \
        c_service(SM_OVL_MESSAGE,(char far *)a,b,(char far *)c,d)

#define SM_OVL_MESSAGE3              (SC_RESERVED1 * 256) +  1 + FNCT_BASE
#define OVL_MESSAGE3(a,b,c,d,e,f)    \
        c_service(SM_OVL_MESSAGE3,(char far *)a,b,(char far *)c,d,(char far *)e,f)

#define SM_OVL_SHOW_SYSERR           (SC_RESERVED1 * 256) +  2 + FNCT_BASE
#define OVL_SHOW_SYSERR(a,b)         \
        c_service(SM_OVL_SHOW_SYSERR,(char far *)a,(char far *)b)

#define SM_OVL_MSG_OFF               (SC_RESERVED1 * 256) +  3 + FNCT_BASE
#define OVL_MSG_OFF()                \
        c_service(SM_OVL_MSG_OFF)

#define SM_OVL_FORCE_CLOSED_LINK     (SC_RESERVED1 * 256) +  4 + FNCT_BASE
#define OVL_FORCE_CLOSED_LINK()      \
        c_service(SM_OVL_FORCE_CLOSED_LINK)

#define SM_OVL_USER_CLOSES_APPS      (SC_RESERVED1 * 256) +  5 + FNCT_BASE
#define OVL_USER_CLOSES_APPS()       \
        c_service(SM_OVL_USER_CLOSES_APPS)

#define SM_OVL_ALARM_DISPLAY         (SC_RESERVED1 * 256) +  6 + FNCT_BASE
#define OVL_ALARM_DISPLAY(a,b)       \
        c_service(SM_OVL_ALARM_DISPLAY,(char *)a,b)

#define SM_OVL_GET_ESC_KEY           (SC_RESERVED1 * 256) +  7 + FNCT_BASE
#define OVL_GET_ESC_KEY()            \
        c_service(SM_OVL_GET_ESC_KEY)

#define SM_OVL_BOXMESSAGE            (SC_RESERVED1 * 256) +  8 + FNCT_BASE
#define OVL_BOXMESSAGE(a,b,c,d,e)    \
        c_service(SM_OVL_BOXMESSAGE,a,(char far *)b,c,(char far *),d,e)

#define SM_OVL_MEMCHECKANDPROMPT     (SC_RESERVED1 * 256) +  9 + FNCT_BASE
#define OVL_MEMCHECKANDPROMPT()      \
        c_service(SM_OVL_MEMCHECKANDPROMPT)

#define SM_OVL_M_NALARM              (SC_RESERVED1 * 256) + 10 + FNCT_BASE
#define OVL_M_NALARM(a,b)             \
        c_service(SM_OVL_M_NALARM,(void far *)a,b)

#define SM_OVL_INIT_SYSMGR_RESOURCES (SC_RESERVED1 * 256) + 11 + FNCT_BASE
#define OVL_INIT_SYSMGR_RESOURCES()  \
        c_service(SM_OVL_INIT_SYSMGR_RESOURCES)

#define SM_OVL_M_ERRMSG              (SC_RESERVED1 * 256) + 12 + FNCT_BASE
#define OVL_M_ERRMSG(a,b,c,d)        \
        c_service(SM_OVL_M_ERRMSG,a,(void far *)b,c,(void far *)d)
