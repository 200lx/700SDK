# $Header:   T:/HH/INCLUDE/VCS/COMMON.MAV   1.28   08 Dec 1992 04:02:12   DAVID  $
#-----------------------------------------------------------------------
# COMMON makefile - This is the common make file; it should be included
#                   by each subsystem-specific makefile.
#
# At a minimum, the subsystem makefile should define three variables and
# include COMMON.MAK  The following example will build an executable
# MY_APP.EXE, from the source files MYFILE1.C, MYFILE2.C, MYFILE3.C,
# and MY_UTILS.ASM.  Note that placing COMMON.MAK between "<" and ">"
# allows it to be found in the path specified by the "INCLUDE" environment
# variable.
#
#          # MY_APP.MAK - Sample simple make file using COMMON.MAK
#          
#          TARGET  = my_app
#          EXE_EXT = .exe
#
#          OBJLIST= myfile1.obj \ 
#                   myfile2.obj \
#                   myfile3.obj \
#                   my_utils.obj
#
#          !INCLUDE <COMMON.MAK>
#
# Refer to COMMON.DOC for options.
#-----------------------------------------------------------------------
#          Copyright (C) 1992 Lotus Development Corporation
#                         All Rights Reserved
#-----------------------------------------------------------------------
# Initial version - 2-14-92 - DJG
#=======================================================================

# Default defines (note that individual makefiles can override any of these)

# Default version, if not specified on cmd line, is DEBUG
!IFNDEF BUILDVER                
BUILDVER = DEBUG
!ENDIF

!IFNDEF LOGFILE
LOGFILE=$(TARGET).log
!ENDIF

# Trim out excess spaces from OBJLIST, otherwise we won't be able
# to build the linker/lib response file correctly.

OBJLIST=$(OBJLIST:     = )
OBJLIST=$(OBJLIST:    = )
OBJLIST=$(OBJLIST:   = )
OBJLIST=$(OBJLIST:  = )

# Create default target for creating response file?
LISTDEP=
!IFNDEF RESPFILE
LISTDEP=LINKLIST
!ENDIF

# Need to run E2M if we want .EXM file
!IF "$(EXE_EXT)"=="exm"  || "$(EXE_EXT)"=="EXM"     
E2M = E2M
!ELSE
E2M =
!ENDIF

# Commands for lib (including response file for lib)
!IF "$(EXE_EXT)"=="lib"  || "$(EXE_EXT)"=="LIB"     
!IFNDEF RESPFILE
LISTDEP=LIBLIST
!ENDIF
LINK=LIB
MSYM=
EXEMOD=
!ENDIF

!IFNDEF RESPFILE
RESPFILE=$(TARGET).lrf
!ENDIF

!IFNDEF LINK
LINK=link
!ENDIF

!IFNDEF MASM
MASM=ml /Zm /c /Cx
!ENDIF

!IFNDEF CC
CC=cl
!ENDIF

!IFNDEF CEXTMEM
CEXTMEM=/EM
!ENDIF

!IFNDEF WARNLEVL
WARNLEVL=/W3
!ENDIF


#=========================================================================
# "Command line" makefile options: user defines these when invoking NMAKE
# or by setting up appropriate environment variables


# Copy OBJs to subdirectory?  If SAVEOBJS is set to Y, reset variable 
# SAVEOBJS to the target that accomplishes this: "SAVEOBJS".

!IF "$(SAVEOBJS)"=="Y" || "$(SAVEOBJS)"=="y"
COPYOBJS=COPYOBJS
!ELSE
COPYOBJS=
!ENDIF

# Destination of executable: if defined, set the variable COPYEXE to the
# the target "COPYEXE" that copies the executable to the destination.

!IFDEF TARGDEST
COPYEXE = COPYEXE
!ELSE
COPYEXE =
!ENDIF


# Directory for OBJs (source or target for SAVEOBJS or )

!IFNDEF OBJDIR
OBJDIR = $(BUILDVER)
!ENDIF


# Use old OBJs? (This defines a pseudotarget that will get old objs, e.g.)

!IF "$(DELOBJS)"=="OLD" || "$(DELOBJS)"=="old"
OBJTARGET = USEOLD
!ELSE
!IF "$(DELOBJS)"=="REBUILD" || "$(DELOBJS)"=="REBUILD"
OBJTARGET = CLROBJS
!ENDIF
!ENDIF


# Generate dependencies file unless overridden

!IF "$(DEPENDS)"=="N" || "$(DEPENDS)"=="n"
DEPFILE=
DEPTARGET=
EXITCMDS=EXITCMDS
!ELSE
DEPFILE = $(TARGET).dep
DEPTARGET=BUILDDEP
EXITCMDS=
!ENDIF


# Force NMAKE to assume that dependfile exists & is up to date

!IF "$(DEPENDS)"=="READY"
!INCLUDE $(DEPFILE)
DEPFILE=
DEPTARGET=
EXITCMDS=EXITCMDS
!ENDIF


# Do a GET? (GETALL is a pseudotarget: it'll execute the PVCS get command
# if GETTARGET is defined as this target.)

!IF "$(GETALL)"=="Y" || "$(GETALL)"=="y" || "$(getall)"=="Y" || "$(getall)"=="y"
GETTARGET = GETALL
!ELSE
GETTARGET =
!ENDIF


#===========================================================================
# Set compiler options according to platform: TSR and DEBUG implemented.

# Set a flag to check later for success in finding version
VERFOUND = F

!IFNDEF MEMMODEL
MEMMODEL=S
!ENDIF

# **** TSR VERSION FLAGS ***********************************************
!IF "$(BUILDVER)"=="TSR"

#  MASM Options
!    IFNDEF AOPTS
AOPTS = /Cx /Zi /W2 /DTSR /DAPI2

# Options are:
#
# /Cx Preserves case on non-local names  /Zi Generates symbols for CV
# /W2 Warning level 2
#

!    ENDIF
AOPTS = $(AOPTS) $(ADAOPTS) $(TADAOPTS) $(OPTIONS)


# C Compiler Options
!    IFNDEF COPTS
COPTS = /c /A$(MEMMODEL) /Gs /Os /Zep1 /DTSR /Fm  /DAPI2

# Options are:
#
# /c   compile only            /Gs Suppress stack checking
# /Os  optimize for size       /Zep1  MS extenstions, byte align structs
# /W3  Warning level 3         /Fm Generate linker map file

!    ENDIF
COPTS = $(COPTS) $(ADCOPTS) $(TADCOPTS)  $(OPTIONS)

# Linker Options
!    IFNDEF LOPTS
LOPTS = /Li /MAP /NOE /NOI
!    ENDIF
LOPTS = $(LOPTS) $(ADLOPTS) $(TADLOPTS)

VERFOUND = T

# ***** EMUL VERSION FLAGS ********************************************
!ENDIF
 
!IF "$(BUILDVER)"=="EMUL"

# Depending on memory model add SCRT0.OBJ or MCRT0.OBJ to head of OBJLIST
# MODIFIED 11/23/92 EJP TO ADD DRV SUPPORT
!IF ("$(EXE_EXT)"!="lib"  && "$(EXE_EXT)"!="LIB" && "$(EXE_EXT)"!="DRV" && "$(EXE_EXT)"!="drv")
OBJLIST=..\lib\$(MEMMODEL)crt0.obj \
        $(OBJLIST)
!ENDIF


#  MASM Options
!    IFNDEF AOPTS
AOPTS = /Cx /Zi /W2 /DEMUL /DAPI2

# Options are:
#
# /Cx Preserves case on non-local names  /Zi Generates symbols for CV
# /W2 Warning level 2
#

!    ENDIF
AOPTS = $(AOPTS) $(ADAOPTS) $(TADAOPTS)  $(OPTIONS)


# C Compiler Options
!    IFNDEF COPTS
COPTS = /c /A$(MEMMODEL) /Gs1 /Os /Zep1 /DEMUL /Fm /DAPI2

# Options are:
#
# /c   compile only            /Gs1   Suppress stack checking, 80186 code
# /Os  optimize for size       /Zep1  MS extenstions, byte align structs
# /W3  Warning level 3         /Fm    Generate linker map file

!    ENDIF
COPTS = $(COPTS) $(ADCOPTS) $(TADCOPTS)  $(OPTIONS)

# Linker Options
!    IFNDEF LOPTS
LOPTS = /Li /MAP /NOE /NOI /PACKCODE
!    ENDIF
LOPTS = $(LOPTS) $(ADLOPTS) $(TADLOPTS)

VERFOUND = T
!ENDIF

# ***** ROM VERSION FLAGS ********************************************
# NOTE: "JAGUAR" == "ROM" (ANACHRONISM)
 
!IF "$(BUILDVER)"=="ROM"

# Depending on memory model add SCRT0.OBJ or MCRT0.OBJ to head of OBJLIST
# MODIFIED 11/23/92 EJP TO ADD DRV SUPPORT
!IF ("$(EXE_EXT)"!="lib"  && "$(EXE_EXT)"!="LIB" && "$(EXE_EXT)"!="DRV" && "$(EXE_EXT)"!="drv")
OBJLIST=..\lib\$(MEMMODEL)crt0.obj \
        $(OBJLIST)
!ENDIF

#  MASM Options
!    IFNDEF AOPTS
AOPTS = /Cx /Zi /W2 /DJAGUAR /DAPI2

# Options are:
#
# /Cx Preserves case on non-local names  /Zi Generates symbols for CV
# /W2 Warning level 2
#

!    ENDIF
AOPTS = $(AOPTS) $(ADAOPTS) $(TADAOPTS)  $(OPTIONS)


# C Compiler Options
!    IFNDEF COPTS
COPTS = /c /A$(MEMMODEL) /G1s /Os /Zep1 /Fm /DAPI2

# Options are:
#
# /c   compile only            /Gs Suppress stack checking
# /Os  optimize for size       /Zep1  MS extenstions, byte align structs
# /W3  Warning level 3         /Fm Generate linker map file

!    ENDIF
COPTS = $(COPTS) $(ADCOPTS) $(TADCOPTS)  $(OPTIONS)

# Linker Options
!    IFNDEF LOPTS
LOPTS = /Li /MAP /NOE /NOI /PACKCODE
!    ENDIF
LOPTS = $(LOPTS) $(ADLOPTS) $(TADLOPTS)

VERFOUND = T
!ENDIF


# ***** DEBUG VERSION FLAGS ********************************************
!IF "$(BUILDVER)"=="DEBUG"


# MASM Options
!    IFNDEF AOPTS
AOPTS = /Cx /Zi /W2 /DDEBUG /DTSR

# Options are:
#
# /Cx Preserves case on non-local names  /Zi Generates symbols for CV
# /W2 Warning level 2
#

!    ENDIF
AOPTS = $(AOPTS) $(ADAOPTS) $(DADAOPTS) $(OPTIONS)

# C Compiler Options
!    IFNDEF COPTS
COPTS = /c /A$(MEMMODEL) /Gs1 /Od /Zep1id /DDEBUG /Fm /DAPI2 /DTSR

# Options are:
#
# -c compile only           -Gs1 suppress stack checking, 80186 instructions
# -Od no optimize           -Zep1 MS extenstions, byte align structs
# -Zi Generate sym for CV   -Zd   line num info for SYMDEB
# -W3 warning level 3       -Fm Create linker map file

!    ENDIF
COPTS = $(COPTS) $(ADCOPTS) $(DADCOPTS)  $(OPTIONS)

# Linker Options
!    IFNDEF LOPTS
LOPTS = /NOI /NOE /CO /LI /M 

# Options are:
#
# /NOI Don't ignore case    /NOE Don't use extended dictionary
# /CO  gen CodeView info    /LI Include line numbers in map file
# /M   Create map file

!    ENDIF
LOPTS = $(LOPTS) $(ADLOPTS) $(DADLOPTS) 



VERFOUND = T
!ENDIF

# ***** UNDEFINED VERSION: ERROR *****
!IF "$(VERFOUND)"=="F"
!    ERROR  Don't know how to build this version: $(BUILDVER)
!ENDIF 


# Add define for memory model
AOPTS=$(AOPTS) /D$(MEMMODEL)MODEL
COPTS=$(COPTS) /D$(MEMMODEL)MODEL


#=======================================================================
# Get rid of extra spaces

AOPTS=$(AOPTS:     = )
AOPTS=$(AOPTS:    = )
AOPTS=$(AOPTS:   = )
AOPTS=$(AOPTS:  = )

COPTS=$(COPTS:     = )
COPTS=$(COPTS:    = )
COPTS=$(COPTS:   = )
COPTS=$(COPTS:  = )

#=======================================================================
# If library, need to know the new name (memmodel + target) of target,
# plus we need to clear default link options

!IF "$(LINK)"=="LIB"
MTARGET=$(MEMMODEL)$(TARGET)
LOPTS=
!ELSE
MTARGET=$(TARGET)
!ENDIF

#=======================================================================
# Inference rules:

.asm.obj:
        if exist $@ del $@
        @echo Invoking: $(MASM) $(AOPTS) $*.asm;   >> $(LOGFILE)
	$(MASM) $(AOPTS) $*.asm >> $(LOGFILE)
        echo . >> $(LOGFILE)

.fon.obj:
        if exist $@ del $@
	@echo Invoking: $(MASM) $(AOPTS) $*.fon; >> $(LOGFILE)
	$(MASM) $(AOPTS) $*.fon; >> $(LOGFILE)
        echo . >> $(LOGFILE)

.c.obj:
        if exist $@ del $@
	@echo Invoking: $(CC) $(WARNLEV) $(COPTS) $*.c>>$(LOGFILE)
	$(CC)   $(COPTS) $*.c    >> $(LOGFILE)
        if not exist $@ echo Trying large-model compiler>>$(LOGFILE)
        if not exist $@ $(CC) $(COPTS) $(CEXTMEM) $*.c>>$(LOGFILE)
        echo . >> $(LOGFILE)

.rs.ri:
        if exist $@ del $@
	@echo Invoking: reditor cp850 -x -c $*.rs $*.ri >> $(LOGFILE)
	reditor4 cp850 -x -c $*.rs $*.ri >> $(LOGFILE)
        echo . >> $(LOGFILE)

.h.hhh:
        if exist $@ del $@
        @echo Invoking: h2inc /Fa$*.hhh $*.h     >> $(LOGFILE)
        h2inc /Fa$*.hhh $*.h     >> $(LOGFILE)
        echo . >> $(LOGFILE)

#----------------------------------------------------------------------
# Suffixes:

.SUFFIXES: .obj .c .asm .fon .mak .rs .h .hhh

#======================================================================
# Pseudotargets


# The first three define the process flow:
# Do some initial stuff, build the main target, then do some exit stuff

BUILDALL:  INITCMDS  $(MTARGET).$(EXE_EXT) $(EXITCMDS)
           @if not exist $(MTARGET).$(EXE_EXT) echo NMAKE failed to build $(MTARGET).$(EXE_EXT) >>$(LOGFILE)
           @if not exist $(MTARGET).$(EXE_EXT) echo 
           @if not exist $(MTARGET).$(EXE_EXT) echo NMAKE failed to build $(MTARGET).$(EXE_EXT)
           @if not exist $(MTARGET).$(EXE_EXT) echo Review $(LOGFILE) for errors.
           @if exist $(MTARGET).$(EXE_EXT) echo Built $(MTARGET).$(EXE_EXT) >>$(LOGFILE)
           @if exist $(MTARGET).$(EXE_EXT) echo Built $(MTARGET).$(EXE_EXT)

INITCMDS: NEWLOG $(LISTDEP) $(GETTARGET) $(OBJTARGET) $(DEPTARGET)

EXITCMDS: $(COPYEXE) $(COPYOBJS)


# These do the actual work

NEWLOG:
        if not "$(RESTART)"=="YES" echo $(LOGFILE) > $(LOGFILE)
        @echo ------------------------------->>$(LOGFILE)
        @echo NMAKE invoked for $(TARGET): >>$(LOGFILE)
        @echo.|date          >>$(LOGFILE)
        @echo.|time          >>$(LOGFILE)
        @echo ------------------------------->>$(LOGFILE)
        @echo .               >>$(LOGFILE)

GETALL:
        @echo Getting files from PVCS ...
        GET *.??V

CLROBJS:
        @echo Deleting old OBJS:
        del *.obj

USEOLD:
        @echo Getting old OBJS
        del *.obj
        copy $(OBJDIR)\*.obj 

COPYOBJS:
        @echo Saving objs in $(OBJDIR) 
        copy *.obj $(OBJDIR) 

COPYEXE:
        @echo Copying $(MTARGET).$(EXE_EXT) to $(TARGDEST) 
        copy $(MTARGET).$(EXE_EXT) $(TARGDEST)
        if exist *.RI COPY *.RI $(TARGDEST)
        if "$(BUILDVER)"=="EMUL" if exist *.MAP COPY *.MAP $(TARGDEST)


LINKLIST:
        @echo Creating linker response file: $(TARGET).lrf
        @echo Creating linker response file: $(TARGET).lrf >> $(TARGET).log
        @type <<$(TARGET).lrf > NUL
$(OBJLIST: =+^
)
$(TARGET).$(EXE_EXT)
$(TARGET).MAP
$(COMLIBS);
<<KEEP

LIBLIST:
        @echo Creating lib response file: $(TARGET).lrf
        @echo Creating lib response file: $(TARGET).lrf >> $(TARGET).log
        @type <<$(TARGET).lrf > NUL
$(MTARGET).lib
Y
-+$(OBJLIST: = &^
-+)
$(MTARGET).LST;
<<KEEP

#----------------------------------------------------------------------
# Build real targets

$(MTARGET).$(EXE_EXT):  $(RI_FILES) $(OBJLIST) $(TARGET).mak
        if exist $@ del $@
	if not "$(LINK)"==""   $(LINK) $(LOPTS) @$(RESPFILE) >> $(TARGET).log
	if not "$(EXEMOD)"=="" $(EXEMOD)                     >> $(TARGET).log
	if not "$(MSYM)"==""   $(MSYM)                       >> $(TARGET).log
        if not "$(E2M)"==""    $(E2M)                        >> $(TARGET).log


# build dependency list

BUILDDEP:
        makedeps -f$(TARGET).mak -o$(TARGET).dep >> $(TARGET).log
        @echo .>>$(TARGET).log
        echo Restarting $(MAKE) with rebuilt dependency list ...>> $(TARGET).log
        $(MAKE) -f $(TARGET).MAK -$(MAKEFLAGS) BUILDALL DEPENDS=READY RESTART=YES

#======================================================================



