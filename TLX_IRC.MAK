# Microsoft Visual C++ Generated NMAKE File, Format Version 2.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Win32 Debug" && "$(CFG)" != "Win32 Release" && "$(CFG)" !=\
 "Win32 Prerelease"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "TLX_IRC.MAK" CFG="Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Win32 Prerelease" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

################################################################################
# Begin Project
# PROP Target_Last_Scanned "Win32 Prerelease"
MTL=MkTypLib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : $(OUTDIR)/TLX_IRC.exe $(OUTDIR)/TLX_IRC.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

MTL_PROJ=
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"TLX_IRC.pch" /Yu"stdafx.h" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"TLX_IRC.pdb" /c 
CPP_OBJS=.\Debug/
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG" /c1251
RSC_PROJ=/l 0x419 /fo$(INTDIR)/"TLX_IRC.res" /d "_DEBUG" /c1251 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"TLX_IRC.bsc" 
BSC32_SBRS= \
	$(INTDIR)/STDAFX.SBR \
	$(INTDIR)/TLX_IRC.SBR \
	$(INTDIR)/MAINWIN.SBR \
	$(INTDIR)/CNMANDLG.SBR \
	$(INTDIR)/ENTERTXT.SBR \
	$(INTDIR)/SETGDLG.SBR \
	$(INTDIR)/STATSDLG.SBR \
	$(INTDIR)/PARSSDLG.SBR \
	$(INTDIR)/MENTIONW.SBR

$(OUTDIR)/TLX_IRC.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=/NOLOGO /SUBSYSTEM:windows /INCREMENTAL:yes\
 /PDB:$(OUTDIR)/"TLX_IRC.pdb" /DEBUG /MACHINE:I386 /OUT:$(OUTDIR)/"TLX_IRC.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/STDAFX.OBJ \
	$(INTDIR)/TLX_IRC.OBJ \
	$(INTDIR)/MAINWIN.OBJ \
	$(INTDIR)/TLX_IRC.res \
	$(INTDIR)/CNMANDLG.OBJ \
	$(INTDIR)/ENTERTXT.OBJ \
	$(INTDIR)/SETGDLG.OBJ \
	$(INTDIR)/STATSDLG.OBJ \
	$(INTDIR)/PARSSDLG.OBJ \
	$(INTDIR)/MENTIONW.OBJ

$(OUTDIR)/TLX_IRC.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
OUTDIR=.\Release
INTDIR=.\Release

ALL : $(OUTDIR)/TLX_IRC.exe $(OUTDIR)/TLX_IRC.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

MTL_PROJ=
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"TLX_IRC.pch" /Yu"stdafx.h" /Fo$(INTDIR)/ /c\
 
CPP_OBJS=.\Release/
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
RSC_PROJ=/l 0x419 /fo$(INTDIR)/"TLX_IRC.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"TLX_IRC.bsc" 
BSC32_SBRS= \
	$(INTDIR)/STDAFX.SBR \
	$(INTDIR)/TLX_IRC.SBR \
	$(INTDIR)/MAINWIN.SBR \
	$(INTDIR)/CNMANDLG.SBR \
	$(INTDIR)/ENTERTXT.SBR \
	$(INTDIR)/SETGDLG.SBR \
	$(INTDIR)/STATSDLG.SBR \
	$(INTDIR)/PARSSDLG.SBR \
	$(INTDIR)/MENTIONW.SBR

$(OUTDIR)/TLX_IRC.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=/NOLOGO /SUBSYSTEM:windows /INCREMENTAL:no\
 /PDB:$(OUTDIR)/"TLX_IRC.pdb" /MACHINE:I386 /OUT:$(OUTDIR)/"TLX_IRC.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/STDAFX.OBJ \
	$(INTDIR)/TLX_IRC.OBJ \
	$(INTDIR)/MAINWIN.OBJ \
	$(INTDIR)/TLX_IRC.res \
	$(INTDIR)/CNMANDLG.OBJ \
	$(INTDIR)/ENTERTXT.OBJ \
	$(INTDIR)/SETGDLG.OBJ \
	$(INTDIR)/STATSDLG.OBJ \
	$(INTDIR)/PARSSDLG.OBJ \
	$(INTDIR)/MENTIONW.OBJ

$(OUTDIR)/TLX_IRC.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Win32 Prerelease"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Win32_Pr"
# PROP BASE Intermediate_Dir "Win32_Pr"
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "PreRel"
# PROP Intermediate_Dir "PreRel"
OUTDIR=.\PreRel
INTDIR=.\PreRel

ALL : $(OUTDIR)/TLX_IRC.exe $(OUTDIR)/TLX_IRC.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE CPP /nologo /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MT /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /c
CPP_PROJ=/nologo /MT /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"TLX_IRC.pch" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"TLX_IRC.pdb" /c 
CPP_OBJS=.\PreRel/
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
RSC_PROJ=/l 0x419 /fo$(INTDIR)/"TLX_IRC.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"TLX_IRC.bsc" 
BSC32_SBRS= \
	$(INTDIR)/STDAFX.SBR \
	$(INTDIR)/TLX_IRC.SBR \
	$(INTDIR)/MAINWIN.SBR \
	$(INTDIR)/CNMANDLG.SBR \
	$(INTDIR)/ENTERTXT.SBR \
	$(INTDIR)/SETGDLG.SBR \
	$(INTDIR)/STATSDLG.SBR \
	$(INTDIR)/PARSSDLG.SBR \
	$(INTDIR)/MENTIONW.SBR

$(OUTDIR)/TLX_IRC.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
# ADD LINK32 /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
LINK32_FLAGS=/NOLOGO /SUBSYSTEM:windows /INCREMENTAL:yes\
 /PDB:$(OUTDIR)/"TLX_IRC.pdb" /DEBUG /MACHINE:I386 /OUT:$(OUTDIR)/"TLX_IRC.exe" 
DEF_FILE=
LINK32_OBJS= \
	$(INTDIR)/STDAFX.OBJ \
	$(INTDIR)/TLX_IRC.OBJ \
	$(INTDIR)/MAINWIN.OBJ \
	$(INTDIR)/TLX_IRC.res \
	$(INTDIR)/CNMANDLG.OBJ \
	$(INTDIR)/ENTERTXT.OBJ \
	$(INTDIR)/SETGDLG.OBJ \
	$(INTDIR)/STATSDLG.OBJ \
	$(INTDIR)/PARSSDLG.OBJ \
	$(INTDIR)/MENTIONW.OBJ

$(OUTDIR)/TLX_IRC.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Group "Source Files"

################################################################################
# Begin Source File

SOURCE=.\STDAFX.CPP
DEP_STDAF=\
	.\STDAFX.H

!IF  "$(CFG)" == "Win32 Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

$(INTDIR)/STDAFX.OBJ :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MT /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"TLX_IRC.pch" /Yc"stdafx.h" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"TLX_IRC.pdb" /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

$(INTDIR)/STDAFX.OBJ :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"TLX_IRC.pch" /Yc"stdafx.h" /Fo$(INTDIR)/ /c\
  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Prerelease"

$(INTDIR)/STDAFX.OBJ :  $(SOURCE)  $(DEP_STDAF) $(INTDIR)
   $(CPP) /nologo /MT /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"TLX_IRC.pch" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"TLX_IRC.pdb" /c  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TLX_IRC.CPP
DEP_TLX_I=\
	.\STDAFX.H\
	.\TLX_IRC.H\
	.\MAINWIN.H\
	.\STATSDLG.H

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/TLX_IRC.OBJ :  $(SOURCE)  $(DEP_TLX_I) $(INTDIR) $(INTDIR)/STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/TLX_IRC.OBJ :  $(SOURCE)  $(DEP_TLX_I) $(INTDIR) $(INTDIR)/STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Prerelease"

$(INTDIR)/TLX_IRC.OBJ :  $(SOURCE)  $(DEP_TLX_I) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MAINWIN.CPP
DEP_MAINW=\
	.\STDAFX.H\
	.\TLX_IRC.H\
	.\MAINWIN.H\
	.\CNMANDLG.H\
	.\SETGDLG.H\
	.\STATSDLG.H

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/MAINWIN.OBJ :  $(SOURCE)  $(DEP_MAINW) $(INTDIR) $(INTDIR)/STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/MAINWIN.OBJ :  $(SOURCE)  $(DEP_MAINW) $(INTDIR) $(INTDIR)/STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Prerelease"

$(INTDIR)/MAINWIN.OBJ :  $(SOURCE)  $(DEP_MAINW) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TLX_IRC.RC
DEP_TLX_IR=\
	.\RES\TLX_IRC.ICO\
	.\RES\TLX_IRC.RC2

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/TLX_IRC.res :  $(SOURCE)  $(DEP_TLX_IR) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/TLX_IRC.res :  $(SOURCE)  $(DEP_TLX_IR) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Prerelease"

$(INTDIR)/TLX_IRC.res :  $(SOURCE)  $(DEP_TLX_IR) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CNMANDLG.CPP
DEP_CNMAN=\
	.\STDAFX.H\
	.\TLX_IRC.H\
	.\CNMANDLG.H\
	.\ENTERTXT.H\
	.\MAINWIN.H\
	.\STATSDLG.H

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/CNMANDLG.OBJ :  $(SOURCE)  $(DEP_CNMAN) $(INTDIR)\
 $(INTDIR)/STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/CNMANDLG.OBJ :  $(SOURCE)  $(DEP_CNMAN) $(INTDIR)\
 $(INTDIR)/STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Prerelease"

$(INTDIR)/CNMANDLG.OBJ :  $(SOURCE)  $(DEP_CNMAN) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ENTERTXT.CPP
DEP_ENTER=\
	.\STDAFX.H\
	.\TLX_IRC.H\
	.\ENTERTXT.H

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/ENTERTXT.OBJ :  $(SOURCE)  $(DEP_ENTER) $(INTDIR)\
 $(INTDIR)/STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/ENTERTXT.OBJ :  $(SOURCE)  $(DEP_ENTER) $(INTDIR)\
 $(INTDIR)/STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Prerelease"

$(INTDIR)/ENTERTXT.OBJ :  $(SOURCE)  $(DEP_ENTER) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SETGDLG.CPP
DEP_SETGD=\
	.\STDAFX.H\
	.\TLX_IRC.H\
	.\SETGDLG.H\
	.\MAINWIN.H\
	.\PARSSDLG.H\
	.\STATSDLG.H

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/SETGDLG.OBJ :  $(SOURCE)  $(DEP_SETGD) $(INTDIR) $(INTDIR)/STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/SETGDLG.OBJ :  $(SOURCE)  $(DEP_SETGD) $(INTDIR) $(INTDIR)/STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Prerelease"

$(INTDIR)/SETGDLG.OBJ :  $(SOURCE)  $(DEP_SETGD) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STATSDLG.CPP
DEP_STATS=\
	.\STDAFX.H\
	.\TLX_IRC.H\
	.\STATSDLG.H

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/STATSDLG.OBJ :  $(SOURCE)  $(DEP_STATS) $(INTDIR)\
 $(INTDIR)/STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/STATSDLG.OBJ :  $(SOURCE)  $(DEP_STATS) $(INTDIR)\
 $(INTDIR)/STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Prerelease"

$(INTDIR)/STATSDLG.OBJ :  $(SOURCE)  $(DEP_STATS) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PARSSDLG.H
# End Source File
################################################################################
# Begin Source File

SOURCE=.\PARSSDLG.CPP
DEP_PARSS=\
	.\STDAFX.H\
	.\TLX_IRC.H\
	.\PARSSDLG.H

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/PARSSDLG.OBJ :  $(SOURCE)  $(DEP_PARSS) $(INTDIR)\
 $(INTDIR)/STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/PARSSDLG.OBJ :  $(SOURCE)  $(DEP_PARSS) $(INTDIR)\
 $(INTDIR)/STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Prerelease"

$(INTDIR)/PARSSDLG.OBJ :  $(SOURCE)  $(DEP_PARSS) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MENTIONW.CPP
DEP_MENTI=\
	.\STDAFX.H\
	.\TLX_IRC.H\
	.\mentionw.h

!IF  "$(CFG)" == "Win32 Debug"

$(INTDIR)/MENTIONW.OBJ :  $(SOURCE)  $(DEP_MENTI) $(INTDIR)\
 $(INTDIR)/STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Release"

$(INTDIR)/MENTIONW.OBJ :  $(SOURCE)  $(DEP_MENTI) $(INTDIR)\
 $(INTDIR)/STDAFX.OBJ

!ELSEIF  "$(CFG)" == "Win32 Prerelease"

$(INTDIR)/MENTIONW.OBJ :  $(SOURCE)  $(DEP_MENTI) $(INTDIR)

!ENDIF 

# End Source File
# End Group
# End Project
################################################################################
