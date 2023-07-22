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
MTL=mktyplib.exe
RSC=rc.exe

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

ALL : "$(OUTDIR)\Tinelix IRC.exe"

CLEAN : 
	-@erase ".\Release\Tinelix IRC.exe"
	-@erase ".\Release\AppThreadTab.obj"
	-@erase ".\Release\Tinelix IRC.pch"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\MainDlg.obj"
	-@erase ".\Release\Tinelix IRC.obj"
	-@erase ".\Release\AboutDlg.obj"
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
# ADD LINK32 /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Tinelix IRC.pdb" /machine:I386 /out:"$(OUTDIR)/Tinelix IRC.exe"\
 
LINK32_OBJS= \
	"$(INTDIR)/AppThreadTab.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/MainDlg.obj" \
	"$(INTDIR)/Tinelix IRC.obj" \
	"$(INTDIR)/AboutDlg.obj" \
	"$(INTDIR)/Tinelix IRC.res"

"$(OUTDIR)\Tinelix IRC.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

ALL : "$(OUTDIR)\Tinelix IRC.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\Tinelix IRC.pch"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\Tinelix IRC.exe"
	-@erase ".\Debug\MainDlg.obj"
	-@erase ".\Debug\AboutDlg.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\AppThreadTab.obj"
	-@erase ".\Debug\Tinelix IRC.obj"
	-@erase ".\Debug\Tinelix IRC.res"
	-@erase ".\Debug\Tinelix IRC.ilk"
	-@erase ".\Debug\Tinelix IRC.pdb"

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
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/Tinelix IRC.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/Tinelix IRC.exe" 
LINK32_OBJS= \
	"$(INTDIR)/MainDlg.obj" \
	"$(INTDIR)/AboutDlg.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/AppThreadTab.obj" \
	"$(INTDIR)/Tinelix IRC.obj" \
	"$(INTDIR)/Tinelix IRC.res"

"$(OUTDIR)\Tinelix IRC.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "Tinelix IRC - Win32 Release"

!ELSEIF  "$(CFG)" == "Tinelix IRC - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=".\Tinelix IRC.cpp"
DEP_CPP_TINEL=\
	".\tabs\..\stdafx.h"\
	".\tabs\..\Tinelix IRC.h"\
	".\dialogs\MainDlg.h"\
	

"$(INTDIR)\Tinelix IRC.obj" : $(SOURCE) $(DEP_CPP_TINEL) "$(INTDIR)"\
 "$(INTDIR)\Tinelix IRC.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\tabs\..\stdafx.h"\
	

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
	".\tabs\..\Tinelix IRC.h"\
	".\dialogs\..\tabs\AppThreadTab.h"\
	".\dialogs\AboutDlg.h"\
	".\dialogs\MainDlg.h"\
	
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
	".\dialogs\..\tabs\AppThreadTab.h"\
	
NODEP_CPP_APPTH=\
	".\tabs\stdafx.h"\
	

"$(INTDIR)\AppThreadTab.obj" : $(SOURCE) $(DEP_CPP_APPTH) "$(INTDIR)"\
 "$(INTDIR)\Tinelix IRC.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
