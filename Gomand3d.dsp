# Microsoft Developer Studio Project File - Name="GomanD3D" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=GomanD3D - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "gomand3d.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "gomand3d.mak" CFG="GomanD3D - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GomanD3D - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "GomanD3D - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ""
# PROP Intermediate_Dir ".\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /G5 /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_ITC_D3D_" /D "CDRequired" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 dplayx.lib dsound.lib dinput.lib msacm32.lib d3drm.lib ddraw.lib winmm.lib libc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib version.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"libcd.lib" /out:"C:\dev\GomanD3D\Goman_Rel.exe"
# SUBTRACT LINK32 /profile /map /debug /nodefaultlib

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ""
# PROP Intermediate_Dir ".\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /G5 /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_ITC_D3D_" /D "FREEWARE" /D "USE320" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 dplayx.lib dsound.lib dinput.lib msacm32.lib d3drm.lib ddraw.lib winmm.lib libc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib version.lib /nologo /subsystem:windows /profile /map:".\goman.map" /debug /machine:I386 /nodefaultlib:"libcd.lib" /out:"C:\dev\GomanD3D\Goman.exe"
# SUBTRACT LINK32 /nodefaultlib

!ENDIF 

# Begin Target

# Name "GomanD3D - Win32 Release"
# Name "GomanD3D - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\Source\Binload.c
# End Source File
# Begin Source File

SOURCE=.\Source\Bldgboom.c
# End Source File
# Begin Source File

SOURCE=.\Source\Boink2.c
# End Source File
# Begin Source File

SOURCE=.\Source\Camera.c
# End Source File
# Begin Source File

SOURCE=.\Source\Cars.c
# End Source File
# Begin Source File

SOURCE=.\Source\Clutter.c
# End Source File
# Begin Source File

SOURCE=.\Source\D3code.c
# End Source File
# Begin Source File

SOURCE=.\Source\D3dapp.c
# End Source File
# Begin Source File

SOURCE=.\Source\D3dcalls.c
# End Source File
# Begin Source File

SOURCE=.\Source\Ddcalls.c
# End Source File
# Begin Source File

SOURCE=.\Source\Fly.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Global.c
# End Source File
# Begin Source File

SOURCE=.\Source\Gosys.c
# End Source File
# Begin Source File

SOURCE=.\Source\Ichars.c
# End Source File
# Begin Source File

SOURCE=.\Source\Imisc.c
# End Source File
# Begin Source File

SOURCE=.\Source\Ksbld.c
# End Source File
# Begin Source File

SOURCE=.\Source\Landscap.c
# End Source File
# Begin Source File

SOURCE=.\Source\Lclib.c
# End Source File
# Begin Source File

SOURCE=.\Source\Lhbldg.c
# End Source File
# Begin Source File

SOURCE=.\Source\Lmbldg.c
# End Source File
# Begin Source File

SOURCE=.\Source\Lnbldg.c
# End Source File
# Begin Source File

SOURCE=.\Source\Lrbldg.c
# End Source File
# Begin Source File

SOURCE=.\Source\Lsbldg.c
# End Source File
# Begin Source File

SOURCE=.\Source\Ltbldg.c
# End Source File
# Begin Source File

SOURCE=.\Source\Lxbldg.c
# End Source File
# Begin Source File

SOURCE=.\Source\Mdtex.c
# End Source File
# Begin Source File

SOURCE=.\Source\Misc.c
# End Source File
# Begin Source File

SOURCE=.\Source\Monanim2.c
# End Source File
# Begin Source File

SOURCE=.\Source\Monmove2.c
# End Source File
# Begin Source File

SOURCE=.\Source\Monthink.c
# End Source File
# Begin Source File

SOURCE=.\Source\Mstrconv.c
# End Source File
# Begin Source File

SOURCE=.\Source\Mstrhelp.c
# End Source File
# Begin Source File

SOURCE=.\Source\netinit2.c
# End Source File
# Begin Source File

SOURCE=.\Source\netmenu.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\netplay.c
# End Source File
# Begin Source File

SOURCE=.\Source\Psystem.c
# End Source File
# Begin Source File

SOURCE=.\Source\Radar.c
# End Source File
# Begin Source File

SOURCE=.\Source\Rl2d3d.c
# End Source File
# Begin Source File

SOURCE=.\Source\Rmfull.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Rmstats.cpp
# End Source File
# Begin Source File

SOURCE=.\source\robotani2.c
# End Source File
# Begin Source File

SOURCE=.\include\robotanim.h
# End Source File
# Begin Source File

SOURCE=.\source\robotmov2.c
# End Source File
# Begin Source File

SOURCE=.\include\robotmove.h
# End Source File
# Begin Source File

SOURCE=.\Script1.rc
# End Source File
# Begin Source File

SOURCE=.\Source\Sprite.c
# End Source File
# Begin Source File

SOURCE=.\Source\Spudbmp.c
# End Source File
# Begin Source File

SOURCE=.\Source\Tekanim.c
# End Source File
# Begin Source File

SOURCE=.\Source\tekmath.c
# End Source File
# Begin Source File

SOURCE=.\Source\Texture.c
# End Source File
# Begin Source File

SOURCE=.\Source\Timing.c
# End Source File
# Begin Source File

SOURCE=.\Source\tkinput.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\twist.c
# End Source File
# Begin Source File

SOURCE=.\Source\Wassert.c
# End Source File
# Begin Source File

SOURCE=.\Source\Wave.c
# End Source File
# Begin Source File

SOURCE=.\Source\Wrapper.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Xaf.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Ybjoystk.c
# End Source File
# Begin Source File

SOURCE=.\Source\Ybmid.c
# End Source File
# Begin Source File

SOURCE=.\Source\Ybmm.c
# End Source File
# Begin Source File

SOURCE=.\Source\Ybreg.c
# End Source File
# Begin Source File

SOURCE=.\Source\Ybsnd.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\icon1.ico
# End Source File
# End Group
# End Target
# End Project
