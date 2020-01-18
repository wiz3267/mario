# Microsoft Developer Studio Project File - Name="SoldirOfMario" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=SoldirOfMario - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SoldirOfMario.mak".
!MESSAGE 
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

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SoldirOfMario - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 ddraw.lib dsound.lib winmm.lib /nologo /subsystem:windows /machine:I386 /out:"SoldirOfMario2011_release.exe"

!ELSEIF  "$(CFG)" == "SoldirOfMario - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ddraw.lib dsound.lib winmm.lib /nologo /subsystem:windows /debug /machine:I386 /out:"SoldirOfMario2011_debug.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "SoldirOfMario - Win32 Release"
# Name "SoldirOfMario - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "MY.LIBRARY"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MY.LIB\Debug.cpp
# End Source File
# Begin Source File

SOURCE=.\MY.LIB\Keyboard.cpp
# End Source File
# Begin Source File

SOURCE=.\MY.LIB\Log.cpp
# End Source File
# Begin Source File

SOURCE=.\MY.LIB\Mouse.cpp
# End Source File
# Begin Source File

SOURCE=.\MY.LIB\Moveobj.cpp
# End Source File
# Begin Source File

SOURCE=.\MY.LIB\Rects.cpp
# End Source File
# Begin Source File

SOURCE=.\MY.LIB\Screen.cpp
# End Source File
# Begin Source File

SOURCE=.\MY.LIB\Sound.cpp
# End Source File
# Begin Source File

SOURCE=.\MY.LIB\Sprite.cpp
# End Source File
# Begin Source File

SOURCE=.\MY.LIB\SriteEditor.cpp
# End Source File
# Begin Source File

SOURCE=.\MY.LIB\Timer.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\MY.LIB\Level.cpp
# End Source File
# Begin Source File

SOURCE=.\MY.LIB\Mario.cpp
# End Source File
# Begin Source File

SOURCE=.\MY.LIB\Mario1.cpp
# End Source File
# Begin Source File

SOURCE=.\MY.LIB\Mario2.cpp
# End Source File
# Begin Source File

SOURCE=.\MY.LIB\Mario3.cpp
# End Source File
# Begin Source File

SOURCE=.\MY.LIB\Mario4.cpp
# End Source File
# Begin Source File

SOURCE=.\MY.LIB\Person.cpp
# End Source File
# Begin Source File

SOURCE=.\SoldirOfMario.cpp
# End Source File
# Begin Source File

SOURCE=.\SoldirOfMario.rc
# End Source File
# Begin Source File

SOURCE=.\SoldirOfMarioDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "MY.LIB"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MY.LIB\DEBUG.H
# End Source File
# Begin Source File

SOURCE=.\MY.LIB\IDSound.h
# End Source File
# Begin Source File

SOURCE=.\MY.LIB\Idsprite.h
# End Source File
# Begin Source File

SOURCE=.\MY.LIB\Keyboard.h
# End Source File
# Begin Source File

SOURCE=.\MY.LIB\Level.h
# End Source File
# Begin Source File

SOURCE=.\MY.LIB\Log.h
# End Source File
# Begin Source File

SOURCE=.\MY.LIB\Mario.h
# End Source File
# Begin Source File

SOURCE=.\MY.LIB\Mouse.h
# End Source File
# Begin Source File

SOURCE=.\MY.LIB\Moveobj.h
# End Source File
# Begin Source File

SOURCE=.\MY.LIB\Person.h
# End Source File
# Begin Source File

SOURCE=.\MY.LIB\Rects.h
# End Source File
# Begin Source File

SOURCE=.\MY.LIB\Screen.h
# End Source File
# Begin Source File

SOURCE=.\MY.LIB\Sound.h
# End Source File
# Begin Source File

SOURCE=.\MY.LIB\Sprite.h
# End Source File
# Begin Source File

SOURCE=.\MY.LIB\SpriteEditor.h
# End Source File
# Begin Source File

SOURCE=.\MY.LIB\Timer.h
# End Source File
# Begin Source File

SOURCE=.\MY.LIB\Total.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SoldirOfMario.h
# End Source File
# Begin Source File

SOURCE=.\SoldirOfMarioDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SoldirOfMario.ico
# End Source File
# Begin Source File

SOURCE=.\res\SoldirOfMario.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
