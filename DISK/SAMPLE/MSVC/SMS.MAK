# Microsoft Visual C++ generated build script - Do not modify

PROJ = SMS
DEBUG = 0
PROGTYPE = 6
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\COLOMBIA\SMS\CPLUS\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC = FETCHSMS.C  
FIRSTCPP =             
RC = rc
CFLAGS_D_DEXE = /nologo /G1 /Zi /Od /D "_DEBUG" /D "_DOS" /FR /Fd"SMS.PDB"
CFLAGS_R_DEXE = /nologo /Gs /G1 /Ow /Ol /Os /D "_DOS" /D "API2" /FR 
LFLAGS_D_DEXE = /NOLOGO /NOD /NOI /STACK:5120 /ONERROR:NOEXE /CO /MAP /CP:0xffff
LFLAGS_R_DEXE = /NOLOGO /NOE /NOI /STACK:5120 /ONERROR:NOEXE /MAP /LINE /CP:0xffff
LIBS_D_DEXE = sms bb caprea mlhstub oldnames mrsbld longmath 
LIBS_R_DEXE = sms caprea tsr mlhstub oldnames mrsbld longmath 
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_DEXE)
LFLAGS = $(LFLAGS_D_DEXE)
LIBS = $(LIBS_D_DEXE)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_DEXE)
LFLAGS = $(LFLAGS_R_DEXE)
LIBS = $(LIBS_R_DEXE)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = DLGS.SBR \
		FETCHSMS.SBR \
		SENDSMS.SBR \
		SMS.SBR \
		SMSMAIN.SBR


DLGS_DEP = c:\colombia\sms\cplus\cmds.h \
	d:\felix\include\cap2.h \
	d:\felix\include\lhapi.h \
	d:\felix\include\keytab.h \
	d:\felix\include\interfac.h \
	d:\felix\include\xbs_inte.h \
	c:\colombia\sms\cplus\dialogs\sendmsg.rc \
	c:\colombia\sms\cplus\dialogs\fetchmsg.rc


FETCHSMS_DEP = c:\colombia\sms\cplus\sms.h \
	d:\felix\include\cap2.h \
	d:\felix\include\lhapi.h \
	d:\felix\include\keytab.h \
	d:\felix\include\interfac.h \
	d:\felix\include\xbs_inte.h \
	d:\felix\include\lstring.h \
	d:\felix\include\comio.h \
	d:\felix\include\comerrs.h \
	d:\felix\include\sysdefs.h \
	c:\colombia\sms\cplus\smserror.h \
	c:\colombia\sms\cplus\cmds.h \
	d:\felix\include\cougraph.h \
	c:\colombia\sms\cplus\icons\newphone.ic


SENDSMS_DEP = c:\colombia\sms\cplus\cmds.h \
	c:\colombia\sms\cplus\sms.h \
	d:\felix\include\cap2.h \
	d:\felix\include\lhapi.h \
	d:\felix\include\keytab.h \
	d:\felix\include\interfac.h \
	d:\felix\include\xbs_inte.h \
	d:\felix\include\lstring.h \
	d:\felix\include\comio.h \
	d:\felix\include\comerrs.h \
	d:\felix\include\sysdefs.h \
	c:\colombia\sms\cplus\smserror.h


SMS_DEP = c:\colombia\sms\cplus\sms.h \
	d:\felix\include\cap2.h \
	d:\felix\include\lhapi.h \
	d:\felix\include\keytab.h \
	d:\felix\include\interfac.h \
	d:\felix\include\xbs_inte.h \
	d:\felix\include\lstring.h \
	d:\felix\include\comio.h \
	d:\felix\include\comerrs.h \
	d:\felix\include\sysdefs.h


SMSMAIN_DEP = c:\colombia\sms\cplus\sms.h \
	d:\felix\include\cap2.h \
	d:\felix\include\lhapi.h \
	d:\felix\include\keytab.h \
	d:\felix\include\interfac.h \
	d:\felix\include\xbs_inte.h \
	d:\felix\include\lstring.h \
	d:\felix\include\comio.h \
	d:\felix\include\comerrs.h \
	d:\felix\include\sysdefs.h \
	c:\colombia\sms\cplus\smserror.h \
	d:\felix\include\event.h \
	d:\felix\include\cougraph.h \
	c:\colombia\sms\cplus\cmds.h \
	d:\felix\include\dosfile.h \
	c:\colombia\sms\cplus\chktsr.c


all:	$(PROJ).EXE $(PROJ).BSC

DLGS.OBJ:	DLGS.C $(DLGS_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c DLGS.C

FETCHSMS.OBJ:	FETCHSMS.C $(FETCHSMS_DEP)
	$(CC) $(CFLAGS) $(CCREATEPCHFLAG) /c FETCHSMS.C

SENDSMS.OBJ:	SENDSMS.C $(SENDSMS_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c SENDSMS.C

SMS.OBJ:	SMS.C $(SMS_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c SMS.C

SMSMAIN.OBJ:	SMSMAIN.C $(SMSMAIN_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c SMSMAIN.C

$(PROJ).EXE::	DLGS.OBJ FETCHSMS.OBJ SENDSMS.OBJ SMS.OBJ SMSMAIN.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
DLGS.OBJ +
FETCHSMS.OBJ +
SENDSMS.OBJ +
SMS.OBJ +
SMSMAIN.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
.\+
c:\msvc\lib\+
c:\msvc\mfc\lib\+
d:\felix\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
