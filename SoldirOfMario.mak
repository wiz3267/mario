# Microsoft Developer Studio Generated NMAKE File, Based on SoldirOfMario.dsp
!IF "$(CFG)" == ""
CFG=SoldirOfMario - Win32 Debug
!MESSAGE No configuration specified. Defaulting to SoldirOfMario - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "SoldirOfMario - Win32 Release" && "$(CFG)" != "SoldirOfMario - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SoldirOfMario.mak" CFG="SoldirOfMario - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SoldirOfMario - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SoldirOfMario - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SoldirOfMario - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : ".\SoldirOfMario2011_release.exe" "$(OUTDIR)\SoldirOfMario.bsc"


CLEAN :
	-@erase "$(INTDIR)\Debug.obj"
	-@erase "$(INTDIR)\Debug.sbr"
	-@erase "$(INTDIR)\Keyboard.obj"
	-@erase "$(INTDIR)\Keyboard.sbr"
	-@erase "$(INTDIR)\Level.obj"
	-@erase "$(INTDIR)\Level.sbr"
	-@erase "$(INTDIR)\Log.obj"
	-@erase "$(INTDIR)\Log.sbr"
	-@erase "$(INTDIR)\Mario.obj"
	-@erase "$(INTDIR)\Mario.sbr"
	-@erase "$(INTDIR)\Mario1.obj"
	-@erase "$(INTDIR)\Mario1.sbr"
	-@erase "$(INTDIR)\Mario2.obj"
	-@erase "$(INTDIR)\Mario2.sbr"
	-@erase "$(INTDIR)\Mario3.obj"
	-@erase "$(INTDIR)\Mario3.sbr"
	-@erase "$(INTDIR)\Mario4.obj"
	-@erase "$(INTDIR)\Mario4.sbr"
	-@erase "$(INTDIR)\Mouse.obj"
	-@erase "$(INTDIR)\Mouse.sbr"
	-@erase "$(INTDIR)\Moveobj.obj"
	-@erase "$(INTDIR)\Moveobj.sbr"
	-@erase "$(INTDIR)\Person.obj"
	-@erase "$(INTDIR)\Person.sbr"
	-@erase "$(INTDIR)\Rects.obj"
	-@erase "$(INTDIR)\Rects.sbr"
	-@erase "$(INTDIR)\Screen.obj"
	-@erase "$(INTDIR)\Screen.sbr"
	-@erase "$(INTDIR)\SoldirOfMario.obj"
	-@erase "$(INTDIR)\SoldirOfMario.pch"
	-@erase "$(INTDIR)\SoldirOfMario.res"
	-@erase "$(INTDIR)\SoldirOfMario.sbr"
	-@erase "$(INTDIR)\SoldirOfMarioDlg.obj"
	-@erase "$(INTDIR)\SoldirOfMarioDlg.sbr"
	-@erase "$(INTDIR)\Sound.obj"
	-@erase "$(INTDIR)\Sound.sbr"
	-@erase "$(INTDIR)\Sprite.obj"
	-@erase "$(INTDIR)\Sprite.sbr"
	-@erase "$(INTDIR)\SriteEditor.obj"
	-@erase "$(INTDIR)\SriteEditor.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\Timer.obj"
	-@erase "$(INTDIR)\Timer.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\SoldirOfMario.bsc"
	-@erase ".\SoldirOfMario2011_release.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\SoldirOfMario.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x419 /fo"$(INTDIR)\SoldirOfMario.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SoldirOfMario.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Debug.sbr" \
	"$(INTDIR)\Keyboard.sbr" \
	"$(INTDIR)\Log.sbr" \
	"$(INTDIR)\Mouse.sbr" \
	"$(INTDIR)\Moveobj.sbr" \
	"$(INTDIR)\Rects.sbr" \
	"$(INTDIR)\Screen.sbr" \
	"$(INTDIR)\Sound.sbr" \
	"$(INTDIR)\Sprite.sbr" \
	"$(INTDIR)\SriteEditor.sbr" \
	"$(INTDIR)\Timer.sbr" \
	"$(INTDIR)\Level.sbr" \
	"$(INTDIR)\Mario.sbr" \
	"$(INTDIR)\Mario1.sbr" \
	"$(INTDIR)\Mario2.sbr" \
	"$(INTDIR)\Mario3.sbr" \
	"$(INTDIR)\Mario4.sbr" \
	"$(INTDIR)\Person.sbr" \
	"$(INTDIR)\SoldirOfMario.sbr" \
	"$(INTDIR)\SoldirOfMarioDlg.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\SoldirOfMario.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=ddraw.lib dsound.lib winmm.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\SoldirOfMario2011_release.pdb" /machine:I386 /out:"SoldirOfMario2011_release.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Debug.obj" \
	"$(INTDIR)\Keyboard.obj" \
	"$(INTDIR)\Log.obj" \
	"$(INTDIR)\Mouse.obj" \
	"$(INTDIR)\Moveobj.obj" \
	"$(INTDIR)\Rects.obj" \
	"$(INTDIR)\Screen.obj" \
	"$(INTDIR)\Sound.obj" \
	"$(INTDIR)\Sprite.obj" \
	"$(INTDIR)\SriteEditor.obj" \
	"$(INTDIR)\Timer.obj" \
	"$(INTDIR)\Level.obj" \
	"$(INTDIR)\Mario.obj" \
	"$(INTDIR)\Mario1.obj" \
	"$(INTDIR)\Mario2.obj" \
	"$(INTDIR)\Mario3.obj" \
	"$(INTDIR)\Mario4.obj" \
	"$(INTDIR)\Person.obj" \
	"$(INTDIR)\SoldirOfMario.obj" \
	"$(INTDIR)\SoldirOfMarioDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SoldirOfMario.res"

".\SoldirOfMario2011_release.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SoldirOfMario - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\SoldirOfMario2011_debug.exe" "$(OUTDIR)\SoldirOfMario.bsc"


CLEAN :
	-@erase "$(INTDIR)\Debug.obj"
	-@erase "$(INTDIR)\Debug.sbr"
	-@erase "$(INTDIR)\Keyboard.obj"
	-@erase "$(INTDIR)\Keyboard.sbr"
	-@erase "$(INTDIR)\Level.obj"
	-@erase "$(INTDIR)\Level.sbr"
	-@erase "$(INTDIR)\Log.obj"
	-@erase "$(INTDIR)\Log.sbr"
	-@erase "$(INTDIR)\Mario.obj"
	-@erase "$(INTDIR)\Mario.sbr"
	-@erase "$(INTDIR)\Mario1.obj"
	-@erase "$(INTDIR)\Mario1.sbr"
	-@erase "$(INTDIR)\Mario2.obj"
	-@erase "$(INTDIR)\Mario2.sbr"
	-@erase "$(INTDIR)\Mario3.obj"
	-@erase "$(INTDIR)\Mario3.sbr"
	-@erase "$(INTDIR)\Mario4.obj"
	-@erase "$(INTDIR)\Mario4.sbr"
	-@erase "$(INTDIR)\Mouse.obj"
	-@erase "$(INTDIR)\Mouse.sbr"
	-@erase "$(INTDIR)\Moveobj.obj"
	-@erase "$(INTDIR)\Moveobj.sbr"
	-@erase "$(INTDIR)\Person.obj"
	-@erase "$(INTDIR)\Person.sbr"
	-@erase "$(INTDIR)\Rects.obj"
	-@erase "$(INTDIR)\Rects.sbr"
	-@erase "$(INTDIR)\Screen.obj"
	-@erase "$(INTDIR)\Screen.sbr"
	-@erase "$(INTDIR)\SoldirOfMario.obj"
	-@erase "$(INTDIR)\SoldirOfMario.pch"
	-@erase "$(INTDIR)\SoldirOfMario.res"
	-@erase "$(INTDIR)\SoldirOfMario.sbr"
	-@erase "$(INTDIR)\SoldirOfMarioDlg.obj"
	-@erase "$(INTDIR)\SoldirOfMarioDlg.sbr"
	-@erase "$(INTDIR)\Sound.obj"
	-@erase "$(INTDIR)\Sound.sbr"
	-@erase "$(INTDIR)\Sprite.obj"
	-@erase "$(INTDIR)\Sprite.sbr"
	-@erase "$(INTDIR)\SriteEditor.obj"
	-@erase "$(INTDIR)\SriteEditor.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\Timer.obj"
	-@erase "$(INTDIR)\Timer.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\SoldirOfMario.bsc"
	-@erase "$(OUTDIR)\SoldirOfMario2011_debug.pdb"
	-@erase ".\SoldirOfMario2011_debug.exe"
	-@erase ".\SoldirOfMario2011_debug.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\SoldirOfMario.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x419 /fo"$(INTDIR)\SoldirOfMario.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SoldirOfMario.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Debug.sbr" \
	"$(INTDIR)\Keyboard.sbr" \
	"$(INTDIR)\Log.sbr" \
	"$(INTDIR)\Mouse.sbr" \
	"$(INTDIR)\Moveobj.sbr" \
	"$(INTDIR)\Rects.sbr" \
	"$(INTDIR)\Screen.sbr" \
	"$(INTDIR)\Sound.sbr" \
	"$(INTDIR)\Sprite.sbr" \
	"$(INTDIR)\SriteEditor.sbr" \
	"$(INTDIR)\Timer.sbr" \
	"$(INTDIR)\Level.sbr" \
	"$(INTDIR)\Mario.sbr" \
	"$(INTDIR)\Mario1.sbr" \
	"$(INTDIR)\Mario2.sbr" \
	"$(INTDIR)\Mario3.sbr" \
	"$(INTDIR)\Mario4.sbr" \
	"$(INTDIR)\Person.sbr" \
	"$(INTDIR)\SoldirOfMario.sbr" \
	"$(INTDIR)\SoldirOfMarioDlg.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\SoldirOfMario.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=ddraw.lib dsound.lib winmm.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\SoldirOfMario2011_debug.pdb" /debug /machine:I386 /out:"SoldirOfMario2011_debug.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\Debug.obj" \
	"$(INTDIR)\Keyboard.obj" \
	"$(INTDIR)\Log.obj" \
	"$(INTDIR)\Mouse.obj" \
	"$(INTDIR)\Moveobj.obj" \
	"$(INTDIR)\Rects.obj" \
	"$(INTDIR)\Screen.obj" \
	"$(INTDIR)\Sound.obj" \
	"$(INTDIR)\Sprite.obj" \
	"$(INTDIR)\SriteEditor.obj" \
	"$(INTDIR)\Timer.obj" \
	"$(INTDIR)\Level.obj" \
	"$(INTDIR)\Mario.obj" \
	"$(INTDIR)\Mario1.obj" \
	"$(INTDIR)\Mario2.obj" \
	"$(INTDIR)\Mario3.obj" \
	"$(INTDIR)\Mario4.obj" \
	"$(INTDIR)\Person.obj" \
	"$(INTDIR)\SoldirOfMario.obj" \
	"$(INTDIR)\SoldirOfMarioDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SoldirOfMario.res"

".\SoldirOfMario2011_debug.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("SoldirOfMario.dep")
!INCLUDE "SoldirOfMario.dep"
!ELSE 
!MESSAGE Warning: cannot find "SoldirOfMario.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "SoldirOfMario - Win32 Release" || "$(CFG)" == "SoldirOfMario - Win32 Debug"
SOURCE=.\MY.LIB\Debug.cpp

"$(INTDIR)\Debug.obj"	"$(INTDIR)\Debug.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SoldirOfMario.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\MY.LIB\Keyboard.cpp

"$(INTDIR)\Keyboard.obj"	"$(INTDIR)\Keyboard.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SoldirOfMario.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\MY.LIB\Log.cpp

"$(INTDIR)\Log.obj"	"$(INTDIR)\Log.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SoldirOfMario.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\MY.LIB\Mouse.cpp

"$(INTDIR)\Mouse.obj"	"$(INTDIR)\Mouse.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SoldirOfMario.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\MY.LIB\Moveobj.cpp

"$(INTDIR)\Moveobj.obj"	"$(INTDIR)\Moveobj.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SoldirOfMario.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\MY.LIB\Rects.cpp

"$(INTDIR)\Rects.obj"	"$(INTDIR)\Rects.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SoldirOfMario.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\MY.LIB\Screen.cpp

"$(INTDIR)\Screen.obj"	"$(INTDIR)\Screen.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SoldirOfMario.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\MY.LIB\Sound.cpp

"$(INTDIR)\Sound.obj"	"$(INTDIR)\Sound.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SoldirOfMario.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\MY.LIB\Sprite.cpp

"$(INTDIR)\Sprite.obj"	"$(INTDIR)\Sprite.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SoldirOfMario.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\MY.LIB\SriteEditor.cpp

"$(INTDIR)\SriteEditor.obj"	"$(INTDIR)\SriteEditor.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SoldirOfMario.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\MY.LIB\Timer.cpp

"$(INTDIR)\Timer.obj"	"$(INTDIR)\Timer.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SoldirOfMario.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\MY.LIB\Level.cpp

"$(INTDIR)\Level.obj"	"$(INTDIR)\Level.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SoldirOfMario.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\MY.LIB\Mario.cpp

"$(INTDIR)\Mario.obj"	"$(INTDIR)\Mario.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SoldirOfMario.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\MY.LIB\Mario1.cpp

"$(INTDIR)\Mario1.obj"	"$(INTDIR)\Mario1.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SoldirOfMario.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\MY.LIB\Mario2.cpp

"$(INTDIR)\Mario2.obj"	"$(INTDIR)\Mario2.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SoldirOfMario.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\MY.LIB\Mario3.cpp

"$(INTDIR)\Mario3.obj"	"$(INTDIR)\Mario3.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SoldirOfMario.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\MY.LIB\Mario4.cpp

"$(INTDIR)\Mario4.obj"	"$(INTDIR)\Mario4.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SoldirOfMario.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\MY.LIB\Person.cpp

"$(INTDIR)\Person.obj"	"$(INTDIR)\Person.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SoldirOfMario.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\SoldirOfMario.cpp

"$(INTDIR)\SoldirOfMario.obj"	"$(INTDIR)\SoldirOfMario.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SoldirOfMario.pch"


SOURCE=.\SoldirOfMario.rc

"$(INTDIR)\SoldirOfMario.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\SoldirOfMarioDlg.cpp

"$(INTDIR)\SoldirOfMarioDlg.obj"	"$(INTDIR)\SoldirOfMarioDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SoldirOfMario.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "SoldirOfMario - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\SoldirOfMario.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\SoldirOfMario.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "SoldirOfMario - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\SoldirOfMario.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\SoldirOfMario.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

