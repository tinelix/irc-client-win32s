# Microsoft Visual C++ Generated NMAKE File, Format Version 2.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Win32 Release" && "$(CFG)" != "Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "TLX_IRC.MAK" CFG="Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

################################################################################
# Begin Project
# PROP Target_Last_Scanned "Win32 Debug"
MTL=MkTypLib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Win32 Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : .\WinRel\TLX_IRC.exe .\WinRel\TLX_IRC.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE CPP /nologo /MT /W3 /GX /YX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /c
# ADD CPP /nologo /MT /W3 /GX /YX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /c
CPP_PROJ=/nologo /MT /W3 /GX /YX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"TLX_IRC.pch" /Fo$(INTDIR)/ /c 
CPP_OBJS=.\WinRel/
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
RSC_PROJ=/l 0x419 /fo$(INTDIR)/"RESOURCE.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"TLX_IRC.bsc" 
BSC32_SBRS= \
	.\WinRel\AboutDlg.sbr \
	.\WinRel\App.sbr \
	.\WinRel\MainWnd.sbr \
	.\WinRel\CONNMDLG.SBR \
	.\WinRel\ETEXTDLG.SBR \
	.\WinRel\PRFSTDLG.SBR \
	.\WinRel\IRCCLNT.SBR

.\WinRel\TLX_IRC.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 oldnames.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:IX86
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib wsock32.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:IX86
# SUBTRACT LINK32 /INCREMENTAL:yes
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib wsock32.lib /NOLOGO\
 /SUBSYSTEM:windows /INCREMENTAL:no /PDB:$(OUTDIR)/"TLX_IRC.pdb" /MACHINE:IX86\
 /DEF:".\src\tlx_irc.def" /OUT:$(OUTDIR)/"TLX_IRC.exe" 
DEF_FILE=.\src\tlx_irc.def
LINK32_OBJS= \
	.\WinRel\AboutDlg.obj \
	.\WinRel\App.obj \
	.\WinRel\MainWnd.obj \
	.\WinRel\RESOURCE.res \
	.\WinRel\CONNMDLG.OBJ \
	.\WinRel\ETEXTDLG.OBJ \
	.\WinRel\PRFSTDLG.OBJ \
	.\WinRel\IRCCLNT.OBJ

.\WinRel\TLX_IRC.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Win32 Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : .\WinDebug\TLX_IRC.exe .\WinDebug\TLX_IRC.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /c
# ADD CPP /nologo /MT /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /c
CPP_PROJ=/nologo /MT /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /FR$(INTDIR)/ /Fp$(OUTDIR)/"TLX_IRC.pch" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"TLX_IRC.pdb" /c 
CPP_OBJS=.\WinDebug/
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
RSC_PROJ=/l 0x419 /fo$(INTDIR)/"RESOURCE.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"TLX_IRC.bsc" 
BSC32_SBRS= \
	.\WinDebug\AboutDlg.sbr \
	.\WinDebug\App.sbr \
	.\WinDebug\MainWnd.sbr \
	.\WinDebug\CONNMDLG.SBR \
	.\WinDebug\ETEXTDLG.SBR \
	.\WinDebug\PRFSTDLG.SBR \
	.\WinDebug\IRCCLNT.SBR

.\WinDebug\TLX_IRC.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 oldnames.lib winsock.lib /NOLOGO /STACK:0x10240 /SUBSYSTEM:windows /DEBUG /MACHINE:IX86
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib wsock32.lib /NOLOGO /STACK:0x10240 /SUBSYSTEM:windows /DEBUG /MACHINE:IX86
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib wsock32.lib /NOLOGO\
 /STACK:0x10240 /SUBSYSTEM:windows /INCREMENTAL:yes /PDB:$(OUTDIR)/"TLX_IRC.pdb"\
 /DEBUG /MACHINE:IX86 /DEF:".\src\tlx_irc.def" /OUT:$(OUTDIR)/"TLX_IRC.exe" 
DEF_FILE=.\src\tlx_irc.def
LINK32_OBJS= \
	.\WinDebug\AboutDlg.obj \
	.\WinDebug\App.obj \
	.\WinDebug\MainWnd.obj \
	.\WinDebug\RESOURCE.res \
	.\WinDebug\CONNMDLG.OBJ \
	.\WinDebug\ETEXTDLG.OBJ \
	.\WinDebug\PRFSTDLG.OBJ \
	.\WinDebug\IRCCLNT.OBJ

.\WinDebug\TLX_IRC.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

SOURCE=.\src\AboutDlg.c
DEP_ABOUT=\
	.\src\AboutDlg.h\
	.\src\Globals.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\AboutDlg.obj :  $(SOURCE)  $(DEP_ABOUT) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\AboutDlg.obj :  $(SOURCE)  $(DEP_ABOUT) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\App.c
DEP_APP_C=\
	.\src\Globals.h\
	.\src\MainWnd.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\App.obj :  $(SOURCE)  $(DEP_APP_C) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\App.obj :  $(SOURCE)  $(DEP_APP_C) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\MainWnd.c
DEP_MAINW=\
	.\src\AboutDlg.h\
	.\src\ETEXTDLG.H\
	.\src\Globals.h\
	.\src\MainWnd.h\
	.\src\CONNMDLG.H\
	.\src\IRCCLNT.H

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\MainWnd.obj :  $(SOURCE)  $(DEP_MAINW) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\MainWnd.obj :  $(SOURCE)  $(DEP_MAINW) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\RESOURCE.RC
DEP_RESOU=\
	.\src\tlx_irc.ver

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\RESOURCE.res :  $(SOURCE)  $(DEP_RESOU) $(INTDIR)
   $(RSC) /l 0x419 /fo$(INTDIR)/"RESOURCE.res" /i "src" /d "NDEBUG"  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\RESOURCE.res :  $(SOURCE)  $(DEP_RESOU) $(INTDIR)
   $(RSC) /l 0x419 /fo$(INTDIR)/"RESOURCE.res" /i "src" /d "_DEBUG"  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\CONNMDLG.C
DEP_CONNM=\
	.\src\CONNMDLG.H\
	.\src\ETEXTDLG.H\
	.\src\Globals.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\CONNMDLG.OBJ :  $(SOURCE)  $(DEP_CONNM) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\CONNMDLG.OBJ :  $(SOURCE)  $(DEP_CONNM) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\ETEXTDLG.C
DEP_ETEXT=\
	.\src\ETEXTDLG.H

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\ETEXTDLG.OBJ :  $(SOURCE)  $(DEP_ETEXT) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\ETEXTDLG.OBJ :  $(SOURCE)  $(DEP_ETEXT) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\PRFSTDLG.C
DEP_PRFST=\
	.\src\PRFSTDLG.H

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\PRFSTDLG.OBJ :  $(SOURCE)  $(DEP_PRFST) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\PRFSTDLG.OBJ :  $(SOURCE)  $(DEP_PRFST) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\IRCCLNT.C
DEP_IRCCL=\
	.\src\IRCCLNT.H\
	.\src\Globals.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\IRCCLNT.OBJ :  $(SOURCE)  $(DEP_IRCCL) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\IRCCLNT.OBJ :  $(SOURCE)  $(DEP_IRCCL) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\tlx_irc.def
# End Source File
# End Group
# End Project
################################################################################
