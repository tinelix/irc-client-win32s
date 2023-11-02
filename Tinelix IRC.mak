# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Tinelix IRC - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Tinelix IRC - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Tinelix IRC - Win32 Release" && "$(CFG)" !=\
 "Tinelix IRC - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Tinelix IRC.mak" CFG="Tinelix IRC - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Tinelix IRC - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Tinelix IRC - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "Tinelix IRC - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Tinelix IRC - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\tlx_irc.exe"

CLEAN : 
	-@erase ".\Release\tlx_irc.exe"
	-@erase ".\Release\ConnManDlg.obj"
	-@erase ".\Release\Tinelix IRC.pch"
	-@erase ".\Release\Tinelix IRC.obj"
	-@erase ".\Release\TextBoxDlg.obj"
	-@erase ".\Release\ProgressDlg.obj"
	-@erase ".\Release\AboutDlg.obj"
	-@erase ".\Release\AppThreadTab.obj"
	-@erase ".\Release\StatisticsDlg.obj"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\MainDlg.obj"
	-@erase ".\Release\Tinelix IRC.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /Fp"$(INTDIR)/Tinelix IRC.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
RSC_PROJ=/l 0x419 /fo"$(INTDIR)/Tinelix IRC.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Tinelix IRC.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"Release/tlx_irc.exe"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/tlx_irc.pdb" /machine:I386 /out:"$(OUTDIR)/tlx_irc.exe" 
LINK32_OBJS= \
	"$(INTDIR)/ConnManDlg.obj" \
	"$(INTDIR)/Tinelix IRC.obj" \
	"$(INTDIR)/TextBoxDlg.obj" \
	"$(INTDIR)/ProgressDlg.obj" \
	"$(INTDIR)/AboutDlg.obj" \
	"$(INTDIR)/AppThreadTab.obj" \
	"$(INTDIR)/StatisticsDlg.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/MainDlg.obj" \
	"$(INTDIR)/Tinelix IRC.res"

"$(OUTDIR)\tlx_irc.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Tinelix IRC - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\tlx_irc.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\Tinelix IRC.pch"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\tlx_irc.exe"
	-@erase ".\Debug\Tinelix IRC.obj"
	-@erase ".\Debug\TextBoxDlg.obj"
	-@erase ".\Debug\AboutDlg.obj"
	-@erase ".\Debug\AppThreadTab.obj"
	-@erase ".\Debug\ProgressDlg.obj"
	-@erase ".\Debug\ConnManDlg.obj"
	-@erase ".\Debug\MainDlg.obj"
	-@erase ".\Debug\StatisticsDlg.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\Tinelix IRC.res"
	-@erase ".\Debug\tlx_irc.ilk"
	-@erase ".\Debug\tlx_irc.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /Fp"$(INTDIR)/Tinelix IRC.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
RSC_PROJ=/l 0x419 /fo"$(INTDIR)/Tinelix IRC.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Tinelix IRC.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/tlx_irc.exe"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/tlx_irc.pdb" /debug /machine:I386 /out:"$(OUTDIR)/tlx_irc.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Tinelix IRC.obj" \
	"$(INTDIR)/TextBoxDlg.obj" \
	"$(INTDIR)/AboutDlg.obj" \
	"$(INTDIR)/AppThreadTab.obj" \
	"$(INTDIR)/ProgressDlg.obj" \
	"$(INTDIR)/ConnManDlg.obj" \
	"$(INTDIR)/MainDlg.obj" \
	"$(INTDIR)/StatisticsDlg.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/Tinelix IRC.res"

"$(OUTDIR)\tlx_irc.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Tinelix IRC - Win32 Release"
# Name "Tinelix IRC - Win32 Debug"

!IF  "$(CFG)" == "Tinelix IRC - Win32 Release"

!ELSEIF  "$(CFG)" == "Tinelix IRC - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=".\Tinelix IRC.cpp"
DEP_CPP_TINEL=\
	".\dialogs\..\stdafx.h"\
	".\tabs\..\Tinelix IRC.h"\
	".\tabs\..\dialogs\MainDlg.h"\
	

"$(INTDIR)\Tinelix IRC.obj" : $(SOURCE) $(DEP_CPP_TINEL) "$(INTDIR)"\
 "$(INTDIR)\Tinelix IRC.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\dialogs\..\stdafx.h"\
	

!IF  "$(CFG)" == "Tinelix IRC - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS"\
 /Fp"$(INTDIR)/Tinelix IRC.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Tinelix IRC.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tinelix IRC - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /Fp"$(INTDIR)/Tinelix IRC.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Tinelix IRC.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=".\Tinelix IRC.rc"
DEP_RSC_TINELI=\
	".\res\Tinelix IRC.ico"\
	".\res\Tinelix IRC.rc2"\
	

"$(INTDIR)\Tinelix IRC.res" : $(SOURCE) $(DEP_RSC_TINELI) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\dialogs\AboutDlg.cpp
DEP_CPP_ABOUT=\
	".\tabs\..\Tinelix IRC.h"\
	".\dialogs\AboutDlg.h"\
	
NODEP_CPP_ABOUT=\
	".\dialogs\stdafx.h"\
	

"$(INTDIR)\AboutDlg.obj" : $(SOURCE) $(DEP_CPP_ABOUT) "$(INTDIR)"\
 "$(INTDIR)\Tinelix IRC.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\dialogs\MainDlg.cpp
DEP_CPP_MAIND=\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\sys\TIMEB.H"\
	".\tabs\..\Tinelix IRC.h"\
	".\dialogs\..\tabs\AppThreadTab.h"\
	".\dialogs\AboutDlg.h"\
	".\tabs\..\dialogs\MainDlg.h"\
	".\dialogs\ConnManDlg.h"\
	".\dialogs\ProgressDlg.h"\
	".\dialogs\StatisticsDlg.h"\
	
NODEP_CPP_MAIND=\
	".\dialogs\stdafx.h"\
	

"$(INTDIR)\MainDlg.obj" : $(SOURCE) $(DEP_CPP_MAIND) "$(INTDIR)"\
 "$(INTDIR)\Tinelix IRC.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\tabs\AppThreadTab.cpp
DEP_CPP_APPTH=\
	".\tabs\..\Tinelix IRC.h"\
	".\tabs\..\dialogs\MainDlg.h"\
	".\dialogs\..\tabs\AppThreadTab.h"\
	
NODEP_CPP_APPTH=\
	".\tabs\stdafx.h"\
	

"$(INTDIR)\AppThreadTab.obj" : $(SOURCE) $(DEP_CPP_APPTH) "$(INTDIR)"\
 "$(INTDIR)\Tinelix IRC.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\dialogs\ConnManDlg.cpp
DEP_CPP_CONNM=\
	".\tabs\..\Tinelix IRC.h"\
	".\tabs\..\dialogs\MainDlg.h"\
	".\dialogs\ConnManDlg.h"\
	".\dialogs\TextBoxDlg.h"\
	
NODEP_CPP_CONNM=\
	".\dialogs\stdafx.h"\
	

"$(INTDIR)\ConnManDlg.obj" : $(SOURCE) $(DEP_CPP_CONNM) "$(INTDIR)"\
 "$(INTDIR)\Tinelix IRC.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\dialogs\ProgressDlg.cpp
DEP_CPP_PROGR=\
	".\tabs\..\Tinelix IRC.h"\
	".\dialogs\ProgressDlg.h"\
	
NODEP_CPP_PROGR=\
	".\dialogs\stdafx.h"\
	

"$(INTDIR)\ProgressDlg.obj" : $(SOURCE) $(DEP_CPP_PROGR) "$(INTDIR)"\
 "$(INTDIR)\Tinelix IRC.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\dialogs\StatisticsDlg.cpp
DEP_CPP_STATI=\
	".\tabs\..\Tinelix IRC.h"\
	".\tabs\..\dialogs\MainDlg.h"\
	".\dialogs\StatisticsDlg.h"\
	
NODEP_CPP_STATI=\
	".\dialogs\stdafx.h"\
	

"$(INTDIR)\StatisticsDlg.obj" : $(SOURCE) $(DEP_CPP_STATI) "$(INTDIR)"\
 "$(INTDIR)\Tinelix IRC.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\dialogs\TextBoxDlg.cpp
DEP_CPP_TEXTB=\
	".\tabs\..\Tinelix IRC.h"\
	".\dialogs\TextBoxDlg.h"\
	
NODEP_CPP_TEXTB=\
	".\dialogs\stdafx.h"\
	

"$(INTDIR)\TextBoxDlg.obj" : $(SOURCE) $(DEP_CPP_TEXTB) "$(INTDIR)"\
 "$(INTDIR)\Tinelix IRC.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
