# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Tinelix IRC Parser - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Tinelix IRC Parser - Win32\
 Debug.
!ENDIF 

!IF "$(CFG)" != "Tinelix IRC Parser - Win32 Release" && "$(CFG)" !=\
 "Tinelix IRC Parser - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Tinelix IRC Parser.mak"\
 CFG="Tinelix IRC Parser - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Tinelix IRC Parser - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Tinelix IRC Parser - Win32 Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "Tinelix IRC Parser - Win32 Debug"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Tinelix IRC Parser - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\ircpars.dll"

CLEAN : 
	-@erase ".\Release\ircpars.dll"
	-@erase ".\Release\IRCParser.obj"
	-@erase ".\Release\ircpars.lib"
	-@erase ".\Release\ircpars.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/Tinelix IRC Parser.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Tinelix IRC Parser.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386 /out:"Release/ircpars.dll"
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/ircpars.pdb" /machine:I386 /def:".\IRCParser.def"\
 /out:"$(OUTDIR)/ircpars.dll" /implib:"$(OUTDIR)/ircpars.lib" 
DEF_FILE= \
	".\IRCParser.def"
LINK32_OBJS= \
	"$(INTDIR)/IRCParser.obj"

"$(OUTDIR)\ircpars.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Tinelix IRC Parser - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Tinelix_"
# PROP BASE Intermediate_Dir "Tinelix_"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Tinelix_"
# PROP Intermediate_Dir "Tinelix_"
# PROP Target_Dir ""
OUTDIR=.\Tinelix_
INTDIR=.\Tinelix_

ALL : "$(OUTDIR)\ircpars.dll"

CLEAN : 
	-@erase ".\Tinelix_\vc40.pdb"
	-@erase ".\Tinelix_\vc40.idb"
	-@erase ".\Debug\ircpars.dll"
	-@erase ".\Tinelix_\IRCParser.obj"
	-@erase ".\Debug\ircpars.ilk"
	-@erase ".\Tinelix_\ircpars.lib"
	-@erase ".\Tinelix_\ircpars.exp"
	-@erase ".\Tinelix_\ircpars.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/Tinelix IRC Parser.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Tinelix_/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Tinelix IRC Parser.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Debug/ircpars.dll"
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/ircpars.pdb" /debug /machine:I386 /def:".\IRCParser.def"\
 /out:"Debug/ircpars.dll" /implib:"$(OUTDIR)/ircpars.lib" 
DEF_FILE= \
	".\IRCParser.def"
LINK32_OBJS= \
	"$(INTDIR)/IRCParser.obj"

"$(OUTDIR)\ircpars.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "Tinelix IRC Parser - Win32 Release"
# Name "Tinelix IRC Parser - Win32 Debug"

!IF  "$(CFG)" == "Tinelix IRC Parser - Win32 Release"

!ELSEIF  "$(CFG)" == "Tinelix IRC Parser - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\IRCParser.h

!IF  "$(CFG)" == "Tinelix IRC Parser - Win32 Release"

!ELSEIF  "$(CFG)" == "Tinelix IRC Parser - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\IRCParser.cpp
DEP_CPP_IRCPA=\
	".\IRCParser.h"\
	

"$(INTDIR)\IRCParser.obj" : $(SOURCE) $(DEP_CPP_IRCPA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\IRCParser.def

!IF  "$(CFG)" == "Tinelix IRC Parser - Win32 Release"

!ELSEIF  "$(CFG)" == "Tinelix IRC Parser - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
