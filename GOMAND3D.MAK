# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=GomanD3D - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to GomanD3D - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "GomanD3D - Win32 Release" && "$(CFG)" !=\
 "GomanD3D - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "GomanD3D.mak" CFG="GomanD3D - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GomanD3D - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "GomanD3D - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "GomanD3D - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ""
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.
INTDIR=.\Release

ALL : "$(OUTDIR)\Goman_Rel.exe" "$(OUTDIR)\GomanD3D.bsc"

CLEAN : 
	-@erase "$(INTDIR)\Binload.obj"
	-@erase "$(INTDIR)\Binload.sbr"
	-@erase "$(INTDIR)\Bldgboom.obj"
	-@erase "$(INTDIR)\Bldgboom.sbr"
	-@erase "$(INTDIR)\Boink2.obj"
	-@erase "$(INTDIR)\Boink2.sbr"
	-@erase "$(INTDIR)\Camera.obj"
	-@erase "$(INTDIR)\Camera.sbr"
	-@erase "$(INTDIR)\Cars.obj"
	-@erase "$(INTDIR)\Cars.sbr"
	-@erase "$(INTDIR)\Clutter.obj"
	-@erase "$(INTDIR)\Clutter.sbr"
	-@erase "$(INTDIR)\D3code.obj"
	-@erase "$(INTDIR)\D3code.sbr"
	-@erase "$(INTDIR)\D3dapp.obj"
	-@erase "$(INTDIR)\D3dapp.sbr"
	-@erase "$(INTDIR)\D3dcalls.obj"
	-@erase "$(INTDIR)\D3dcalls.sbr"
	-@erase "$(INTDIR)\Ddcalls.obj"
	-@erase "$(INTDIR)\Ddcalls.sbr"
	-@erase "$(INTDIR)\Fly.obj"
	-@erase "$(INTDIR)\Fly.sbr"
	-@erase "$(INTDIR)\Global.obj"
	-@erase "$(INTDIR)\Global.sbr"
	-@erase "$(INTDIR)\Gosys.obj"
	-@erase "$(INTDIR)\Gosys.sbr"
	-@erase "$(INTDIR)\Ichars.obj"
	-@erase "$(INTDIR)\Ichars.sbr"
	-@erase "$(INTDIR)\Imisc.obj"
	-@erase "$(INTDIR)\Imisc.sbr"
	-@erase "$(INTDIR)\Ksbld.obj"
	-@erase "$(INTDIR)\Ksbld.sbr"
	-@erase "$(INTDIR)\Landscap.obj"
	-@erase "$(INTDIR)\Landscap.sbr"
	-@erase "$(INTDIR)\Lclib.obj"
	-@erase "$(INTDIR)\Lclib.sbr"
	-@erase "$(INTDIR)\Lhbldg.obj"
	-@erase "$(INTDIR)\Lhbldg.sbr"
	-@erase "$(INTDIR)\Lmbldg.obj"
	-@erase "$(INTDIR)\Lmbldg.sbr"
	-@erase "$(INTDIR)\Lnbldg.obj"
	-@erase "$(INTDIR)\Lnbldg.sbr"
	-@erase "$(INTDIR)\Lrbldg.obj"
	-@erase "$(INTDIR)\Lrbldg.sbr"
	-@erase "$(INTDIR)\Lsbldg.obj"
	-@erase "$(INTDIR)\Lsbldg.sbr"
	-@erase "$(INTDIR)\Ltbldg.obj"
	-@erase "$(INTDIR)\Ltbldg.sbr"
	-@erase "$(INTDIR)\Lxbldg.obj"
	-@erase "$(INTDIR)\Lxbldg.sbr"
	-@erase "$(INTDIR)\Mdtex.obj"
	-@erase "$(INTDIR)\Mdtex.sbr"
	-@erase "$(INTDIR)\Misc.obj"
	-@erase "$(INTDIR)\Misc.sbr"
	-@erase "$(INTDIR)\Monanim2.obj"
	-@erase "$(INTDIR)\Monanim2.sbr"
	-@erase "$(INTDIR)\Monmove2.obj"
	-@erase "$(INTDIR)\Monmove2.sbr"
	-@erase "$(INTDIR)\Monthink.obj"
	-@erase "$(INTDIR)\Monthink.sbr"
	-@erase "$(INTDIR)\Mstrconv.obj"
	-@erase "$(INTDIR)\Mstrconv.sbr"
	-@erase "$(INTDIR)\Mstrhelp.obj"
	-@erase "$(INTDIR)\Mstrhelp.sbr"
	-@erase "$(INTDIR)\netinit2.obj"
	-@erase "$(INTDIR)\netinit2.sbr"
	-@erase "$(INTDIR)\netmenu.obj"
	-@erase "$(INTDIR)\netmenu.sbr"
	-@erase "$(INTDIR)\netplay.obj"
	-@erase "$(INTDIR)\netplay.sbr"
	-@erase "$(INTDIR)\Psystem.obj"
	-@erase "$(INTDIR)\Psystem.sbr"
	-@erase "$(INTDIR)\Radar.obj"
	-@erase "$(INTDIR)\Radar.sbr"
	-@erase "$(INTDIR)\Rl2d3d.obj"
	-@erase "$(INTDIR)\Rl2d3d.sbr"
	-@erase "$(INTDIR)\Rmfull.obj"
	-@erase "$(INTDIR)\Rmfull.sbr"
	-@erase "$(INTDIR)\Rmstats.obj"
	-@erase "$(INTDIR)\Rmstats.sbr"
	-@erase "$(INTDIR)\robotani2.obj"
	-@erase "$(INTDIR)\robotani2.sbr"
	-@erase "$(INTDIR)\robotmov2.obj"
	-@erase "$(INTDIR)\robotmov2.sbr"
	-@erase "$(INTDIR)\Script1.res"
	-@erase "$(INTDIR)\Sprite.obj"
	-@erase "$(INTDIR)\Sprite.sbr"
	-@erase "$(INTDIR)\Spudbmp.obj"
	-@erase "$(INTDIR)\Spudbmp.sbr"
	-@erase "$(INTDIR)\Tekanim.obj"
	-@erase "$(INTDIR)\Tekanim.sbr"
	-@erase "$(INTDIR)\tekmath.obj"
	-@erase "$(INTDIR)\tekmath.sbr"
	-@erase "$(INTDIR)\Texture.obj"
	-@erase "$(INTDIR)\Texture.sbr"
	-@erase "$(INTDIR)\Timing.obj"
	-@erase "$(INTDIR)\Timing.sbr"
	-@erase "$(INTDIR)\tkinput.obj"
	-@erase "$(INTDIR)\tkinput.sbr"
	-@erase "$(INTDIR)\twist.obj"
	-@erase "$(INTDIR)\twist.sbr"
	-@erase "$(INTDIR)\Wassert.obj"
	-@erase "$(INTDIR)\Wassert.sbr"
	-@erase "$(INTDIR)\Wave.obj"
	-@erase "$(INTDIR)\Wave.sbr"
	-@erase "$(INTDIR)\Wrapper.obj"
	-@erase "$(INTDIR)\Wrapper.sbr"
	-@erase "$(INTDIR)\Xaf.obj"
	-@erase "$(INTDIR)\Xaf.sbr"
	-@erase "$(INTDIR)\Ybjoystk.obj"
	-@erase "$(INTDIR)\Ybjoystk.sbr"
	-@erase "$(INTDIR)\Ybmid.obj"
	-@erase "$(INTDIR)\Ybmid.sbr"
	-@erase "$(INTDIR)\Ybmm.obj"
	-@erase "$(INTDIR)\Ybmm.sbr"
	-@erase "$(INTDIR)\Ybreg.obj"
	-@erase "$(INTDIR)\Ybreg.sbr"
	-@erase "$(INTDIR)\Ybsnd.obj"
	-@erase "$(INTDIR)\Ybsnd.sbr"
	-@erase "$(OUTDIR)\Goman_Rel.exe"
	-@erase "$(OUTDIR)\GomanD3D.bsc"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /G5 /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_ITC_D3D_" /D "CDRequired" /FR /YX /c
CPP_PROJ=/nologo /G5 /ML /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_ITC_D3D_" /D "CDRequired" /FR"$(INTDIR)/" /Fp"$(INTDIR)/GomanD3D.pch" /YX\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\Release/
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Script1.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/GomanD3D.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Binload.sbr" \
	"$(INTDIR)\Bldgboom.sbr" \
	"$(INTDIR)\Boink2.sbr" \
	"$(INTDIR)\Camera.sbr" \
	"$(INTDIR)\Cars.sbr" \
	"$(INTDIR)\Clutter.sbr" \
	"$(INTDIR)\D3code.sbr" \
	"$(INTDIR)\D3dapp.sbr" \
	"$(INTDIR)\D3dcalls.sbr" \
	"$(INTDIR)\Ddcalls.sbr" \
	"$(INTDIR)\Fly.sbr" \
	"$(INTDIR)\Global.sbr" \
	"$(INTDIR)\Gosys.sbr" \
	"$(INTDIR)\Ichars.sbr" \
	"$(INTDIR)\Imisc.sbr" \
	"$(INTDIR)\Ksbld.sbr" \
	"$(INTDIR)\Landscap.sbr" \
	"$(INTDIR)\Lclib.sbr" \
	"$(INTDIR)\Lhbldg.sbr" \
	"$(INTDIR)\Lmbldg.sbr" \
	"$(INTDIR)\Lnbldg.sbr" \
	"$(INTDIR)\Lrbldg.sbr" \
	"$(INTDIR)\Lsbldg.sbr" \
	"$(INTDIR)\Ltbldg.sbr" \
	"$(INTDIR)\Lxbldg.sbr" \
	"$(INTDIR)\Mdtex.sbr" \
	"$(INTDIR)\Misc.sbr" \
	"$(INTDIR)\Monanim2.sbr" \
	"$(INTDIR)\Monmove2.sbr" \
	"$(INTDIR)\Monthink.sbr" \
	"$(INTDIR)\Mstrconv.sbr" \
	"$(INTDIR)\Mstrhelp.sbr" \
	"$(INTDIR)\netinit2.sbr" \
	"$(INTDIR)\netmenu.sbr" \
	"$(INTDIR)\netplay.sbr" \
	"$(INTDIR)\Psystem.sbr" \
	"$(INTDIR)\Radar.sbr" \
	"$(INTDIR)\Rl2d3d.sbr" \
	"$(INTDIR)\Rmfull.sbr" \
	"$(INTDIR)\Rmstats.sbr" \
	"$(INTDIR)\robotani2.sbr" \
	"$(INTDIR)\robotmov2.sbr" \
	"$(INTDIR)\Sprite.sbr" \
	"$(INTDIR)\Spudbmp.sbr" \
	"$(INTDIR)\Tekanim.sbr" \
	"$(INTDIR)\tekmath.sbr" \
	"$(INTDIR)\Texture.sbr" \
	"$(INTDIR)\Timing.sbr" \
	"$(INTDIR)\tkinput.sbr" \
	"$(INTDIR)\twist.sbr" \
	"$(INTDIR)\Wassert.sbr" \
	"$(INTDIR)\Wave.sbr" \
	"$(INTDIR)\Wrapper.sbr" \
	"$(INTDIR)\Xaf.sbr" \
	"$(INTDIR)\Ybjoystk.sbr" \
	"$(INTDIR)\Ybmid.sbr" \
	"$(INTDIR)\Ybmm.sbr" \
	"$(INTDIR)\Ybreg.sbr" \
	"$(INTDIR)\Ybsnd.sbr"

"$(OUTDIR)\GomanD3D.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 dplayx.lib dsound.lib dinput.lib msacm32.lib d3drm.lib ddraw.lib winmm.lib libc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib version.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"libcd.lib" /out:"C:\dev\GomanD3D\Goman_Rel.exe"
# SUBTRACT LINK32 /profile /map /debug /nodefaultlib
LINK32_FLAGS=dplayx.lib dsound.lib dinput.lib msacm32.lib d3drm.lib ddraw.lib\
 winmm.lib libc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib version.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Goman_Rel.pdb" /machine:I386 /nodefaultlib:"libcd.lib"\
 /out:"$(OUTDIR)/Goman_Rel.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Binload.obj" \
	"$(INTDIR)\Bldgboom.obj" \
	"$(INTDIR)\Boink2.obj" \
	"$(INTDIR)\Camera.obj" \
	"$(INTDIR)\Cars.obj" \
	"$(INTDIR)\Clutter.obj" \
	"$(INTDIR)\D3code.obj" \
	"$(INTDIR)\D3dapp.obj" \
	"$(INTDIR)\D3dcalls.obj" \
	"$(INTDIR)\Ddcalls.obj" \
	"$(INTDIR)\Fly.obj" \
	"$(INTDIR)\Global.obj" \
	"$(INTDIR)\Gosys.obj" \
	"$(INTDIR)\Ichars.obj" \
	"$(INTDIR)\Imisc.obj" \
	"$(INTDIR)\Ksbld.obj" \
	"$(INTDIR)\Landscap.obj" \
	"$(INTDIR)\Lclib.obj" \
	"$(INTDIR)\Lhbldg.obj" \
	"$(INTDIR)\Lmbldg.obj" \
	"$(INTDIR)\Lnbldg.obj" \
	"$(INTDIR)\Lrbldg.obj" \
	"$(INTDIR)\Lsbldg.obj" \
	"$(INTDIR)\Ltbldg.obj" \
	"$(INTDIR)\Lxbldg.obj" \
	"$(INTDIR)\Mdtex.obj" \
	"$(INTDIR)\Misc.obj" \
	"$(INTDIR)\Monanim2.obj" \
	"$(INTDIR)\Monmove2.obj" \
	"$(INTDIR)\Monthink.obj" \
	"$(INTDIR)\Mstrconv.obj" \
	"$(INTDIR)\Mstrhelp.obj" \
	"$(INTDIR)\netinit2.obj" \
	"$(INTDIR)\netmenu.obj" \
	"$(INTDIR)\netplay.obj" \
	"$(INTDIR)\Psystem.obj" \
	"$(INTDIR)\Radar.obj" \
	"$(INTDIR)\Rl2d3d.obj" \
	"$(INTDIR)\Rmfull.obj" \
	"$(INTDIR)\Rmstats.obj" \
	"$(INTDIR)\robotani2.obj" \
	"$(INTDIR)\robotmov2.obj" \
	"$(INTDIR)\Script1.res" \
	"$(INTDIR)\Sprite.obj" \
	"$(INTDIR)\Spudbmp.obj" \
	"$(INTDIR)\Tekanim.obj" \
	"$(INTDIR)\tekmath.obj" \
	"$(INTDIR)\Texture.obj" \
	"$(INTDIR)\Timing.obj" \
	"$(INTDIR)\tkinput.obj" \
	"$(INTDIR)\twist.obj" \
	"$(INTDIR)\Wassert.obj" \
	"$(INTDIR)\Wave.obj" \
	"$(INTDIR)\Wrapper.obj" \
	"$(INTDIR)\Xaf.obj" \
	"$(INTDIR)\Ybjoystk.obj" \
	"$(INTDIR)\Ybmid.obj" \
	"$(INTDIR)\Ybmm.obj" \
	"$(INTDIR)\Ybreg.obj" \
	"$(INTDIR)\Ybsnd.obj"

"$(OUTDIR)\Goman_Rel.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ""
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.
INTDIR=.\Debug

ALL : "$(OUTDIR)\Goman.exe" "$(OUTDIR)\GomanD3D.bsc"

CLEAN : 
	-@erase "$(INTDIR)\Binload.obj"
	-@erase "$(INTDIR)\Binload.sbr"
	-@erase "$(INTDIR)\Bldgboom.obj"
	-@erase "$(INTDIR)\Bldgboom.sbr"
	-@erase "$(INTDIR)\Boink2.obj"
	-@erase "$(INTDIR)\Boink2.sbr"
	-@erase "$(INTDIR)\Camera.obj"
	-@erase "$(INTDIR)\Camera.sbr"
	-@erase "$(INTDIR)\Cars.obj"
	-@erase "$(INTDIR)\Cars.sbr"
	-@erase "$(INTDIR)\Clutter.obj"
	-@erase "$(INTDIR)\Clutter.sbr"
	-@erase "$(INTDIR)\D3code.obj"
	-@erase "$(INTDIR)\D3code.sbr"
	-@erase "$(INTDIR)\D3dapp.obj"
	-@erase "$(INTDIR)\D3dapp.sbr"
	-@erase "$(INTDIR)\D3dcalls.obj"
	-@erase "$(INTDIR)\D3dcalls.sbr"
	-@erase "$(INTDIR)\Ddcalls.obj"
	-@erase "$(INTDIR)\Ddcalls.sbr"
	-@erase "$(INTDIR)\Fly.obj"
	-@erase "$(INTDIR)\Fly.sbr"
	-@erase "$(INTDIR)\Global.obj"
	-@erase "$(INTDIR)\Global.sbr"
	-@erase "$(INTDIR)\Gosys.obj"
	-@erase "$(INTDIR)\Gosys.sbr"
	-@erase "$(INTDIR)\Ichars.obj"
	-@erase "$(INTDIR)\Ichars.sbr"
	-@erase "$(INTDIR)\Imisc.obj"
	-@erase "$(INTDIR)\Imisc.sbr"
	-@erase "$(INTDIR)\Ksbld.obj"
	-@erase "$(INTDIR)\Ksbld.sbr"
	-@erase "$(INTDIR)\Landscap.obj"
	-@erase "$(INTDIR)\Landscap.sbr"
	-@erase "$(INTDIR)\Lclib.obj"
	-@erase "$(INTDIR)\Lclib.sbr"
	-@erase "$(INTDIR)\Lhbldg.obj"
	-@erase "$(INTDIR)\Lhbldg.sbr"
	-@erase "$(INTDIR)\Lmbldg.obj"
	-@erase "$(INTDIR)\Lmbldg.sbr"
	-@erase "$(INTDIR)\Lnbldg.obj"
	-@erase "$(INTDIR)\Lnbldg.sbr"
	-@erase "$(INTDIR)\Lrbldg.obj"
	-@erase "$(INTDIR)\Lrbldg.sbr"
	-@erase "$(INTDIR)\Lsbldg.obj"
	-@erase "$(INTDIR)\Lsbldg.sbr"
	-@erase "$(INTDIR)\Ltbldg.obj"
	-@erase "$(INTDIR)\Ltbldg.sbr"
	-@erase "$(INTDIR)\Lxbldg.obj"
	-@erase "$(INTDIR)\Lxbldg.sbr"
	-@erase "$(INTDIR)\Mdtex.obj"
	-@erase "$(INTDIR)\Mdtex.sbr"
	-@erase "$(INTDIR)\Misc.obj"
	-@erase "$(INTDIR)\Misc.sbr"
	-@erase "$(INTDIR)\Monanim2.obj"
	-@erase "$(INTDIR)\Monanim2.sbr"
	-@erase "$(INTDIR)\Monmove2.obj"
	-@erase "$(INTDIR)\Monmove2.sbr"
	-@erase "$(INTDIR)\Monthink.obj"
	-@erase "$(INTDIR)\Monthink.sbr"
	-@erase "$(INTDIR)\Mstrconv.obj"
	-@erase "$(INTDIR)\Mstrconv.sbr"
	-@erase "$(INTDIR)\Mstrhelp.obj"
	-@erase "$(INTDIR)\Mstrhelp.sbr"
	-@erase "$(INTDIR)\netinit2.obj"
	-@erase "$(INTDIR)\netinit2.sbr"
	-@erase "$(INTDIR)\netmenu.obj"
	-@erase "$(INTDIR)\netmenu.sbr"
	-@erase "$(INTDIR)\netplay.obj"
	-@erase "$(INTDIR)\netplay.sbr"
	-@erase "$(INTDIR)\Psystem.obj"
	-@erase "$(INTDIR)\Psystem.sbr"
	-@erase "$(INTDIR)\Radar.obj"
	-@erase "$(INTDIR)\Radar.sbr"
	-@erase "$(INTDIR)\Rl2d3d.obj"
	-@erase "$(INTDIR)\Rl2d3d.sbr"
	-@erase "$(INTDIR)\Rmfull.obj"
	-@erase "$(INTDIR)\Rmfull.sbr"
	-@erase "$(INTDIR)\Rmstats.obj"
	-@erase "$(INTDIR)\Rmstats.sbr"
	-@erase "$(INTDIR)\robotani2.obj"
	-@erase "$(INTDIR)\robotani2.sbr"
	-@erase "$(INTDIR)\robotmov2.obj"
	-@erase "$(INTDIR)\robotmov2.sbr"
	-@erase "$(INTDIR)\Script1.res"
	-@erase "$(INTDIR)\Sprite.obj"
	-@erase "$(INTDIR)\Sprite.sbr"
	-@erase "$(INTDIR)\Spudbmp.obj"
	-@erase "$(INTDIR)\Spudbmp.sbr"
	-@erase "$(INTDIR)\Tekanim.obj"
	-@erase "$(INTDIR)\Tekanim.sbr"
	-@erase "$(INTDIR)\tekmath.obj"
	-@erase "$(INTDIR)\tekmath.sbr"
	-@erase "$(INTDIR)\Texture.obj"
	-@erase "$(INTDIR)\Texture.sbr"
	-@erase "$(INTDIR)\Timing.obj"
	-@erase "$(INTDIR)\Timing.sbr"
	-@erase "$(INTDIR)\tkinput.obj"
	-@erase "$(INTDIR)\tkinput.sbr"
	-@erase "$(INTDIR)\twist.obj"
	-@erase "$(INTDIR)\twist.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\Wassert.obj"
	-@erase "$(INTDIR)\Wassert.sbr"
	-@erase "$(INTDIR)\Wave.obj"
	-@erase "$(INTDIR)\Wave.sbr"
	-@erase "$(INTDIR)\Wrapper.obj"
	-@erase "$(INTDIR)\Wrapper.sbr"
	-@erase "$(INTDIR)\Xaf.obj"
	-@erase "$(INTDIR)\Xaf.sbr"
	-@erase "$(INTDIR)\Ybjoystk.obj"
	-@erase "$(INTDIR)\Ybjoystk.sbr"
	-@erase "$(INTDIR)\Ybmid.obj"
	-@erase "$(INTDIR)\Ybmid.sbr"
	-@erase "$(INTDIR)\Ybmm.obj"
	-@erase "$(INTDIR)\Ybmm.sbr"
	-@erase "$(INTDIR)\Ybreg.obj"
	-@erase "$(INTDIR)\Ybreg.sbr"
	-@erase "$(INTDIR)\Ybsnd.obj"
	-@erase "$(INTDIR)\Ybsnd.sbr"
	-@erase "$(OUTDIR)\Goman.exe"
	-@erase "$(OUTDIR)\goman.map"
	-@erase "$(OUTDIR)\GomanD3D.bsc"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /G5 /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_ITC_D3D_" /D "FREEWARE" /D "USE320" /FR /YX /c
CPP_PROJ=/nologo /G5 /MLd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_ITC_D3D_" /D "FREEWARE" /D "USE320" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/GomanD3D.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Script1.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/GomanD3D.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Binload.sbr" \
	"$(INTDIR)\Bldgboom.sbr" \
	"$(INTDIR)\Boink2.sbr" \
	"$(INTDIR)\Camera.sbr" \
	"$(INTDIR)\Cars.sbr" \
	"$(INTDIR)\Clutter.sbr" \
	"$(INTDIR)\D3code.sbr" \
	"$(INTDIR)\D3dapp.sbr" \
	"$(INTDIR)\D3dcalls.sbr" \
	"$(INTDIR)\Ddcalls.sbr" \
	"$(INTDIR)\Fly.sbr" \
	"$(INTDIR)\Global.sbr" \
	"$(INTDIR)\Gosys.sbr" \
	"$(INTDIR)\Ichars.sbr" \
	"$(INTDIR)\Imisc.sbr" \
	"$(INTDIR)\Ksbld.sbr" \
	"$(INTDIR)\Landscap.sbr" \
	"$(INTDIR)\Lclib.sbr" \
	"$(INTDIR)\Lhbldg.sbr" \
	"$(INTDIR)\Lmbldg.sbr" \
	"$(INTDIR)\Lnbldg.sbr" \
	"$(INTDIR)\Lrbldg.sbr" \
	"$(INTDIR)\Lsbldg.sbr" \
	"$(INTDIR)\Ltbldg.sbr" \
	"$(INTDIR)\Lxbldg.sbr" \
	"$(INTDIR)\Mdtex.sbr" \
	"$(INTDIR)\Misc.sbr" \
	"$(INTDIR)\Monanim2.sbr" \
	"$(INTDIR)\Monmove2.sbr" \
	"$(INTDIR)\Monthink.sbr" \
	"$(INTDIR)\Mstrconv.sbr" \
	"$(INTDIR)\Mstrhelp.sbr" \
	"$(INTDIR)\netinit2.sbr" \
	"$(INTDIR)\netmenu.sbr" \
	"$(INTDIR)\netplay.sbr" \
	"$(INTDIR)\Psystem.sbr" \
	"$(INTDIR)\Radar.sbr" \
	"$(INTDIR)\Rl2d3d.sbr" \
	"$(INTDIR)\Rmfull.sbr" \
	"$(INTDIR)\Rmstats.sbr" \
	"$(INTDIR)\robotani2.sbr" \
	"$(INTDIR)\robotmov2.sbr" \
	"$(INTDIR)\Sprite.sbr" \
	"$(INTDIR)\Spudbmp.sbr" \
	"$(INTDIR)\Tekanim.sbr" \
	"$(INTDIR)\tekmath.sbr" \
	"$(INTDIR)\Texture.sbr" \
	"$(INTDIR)\Timing.sbr" \
	"$(INTDIR)\tkinput.sbr" \
	"$(INTDIR)\twist.sbr" \
	"$(INTDIR)\Wassert.sbr" \
	"$(INTDIR)\Wave.sbr" \
	"$(INTDIR)\Wrapper.sbr" \
	"$(INTDIR)\Xaf.sbr" \
	"$(INTDIR)\Ybjoystk.sbr" \
	"$(INTDIR)\Ybmid.sbr" \
	"$(INTDIR)\Ybmm.sbr" \
	"$(INTDIR)\Ybreg.sbr" \
	"$(INTDIR)\Ybsnd.sbr"

"$(OUTDIR)\GomanD3D.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 dplayx.lib dsound.lib dinput.lib msacm32.lib d3drm.lib ddraw.lib winmm.lib libc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib version.lib /nologo /subsystem:windows /profile /map:"goman.map" /debug /machine:I386 /nodefaultlib:"libcd.lib" /out:"C:\dev\GomanD3D\Goman.exe"
# SUBTRACT LINK32 /nodefaultlib
LINK32_FLAGS=dplayx.lib dsound.lib dinput.lib msacm32.lib d3drm.lib ddraw.lib\
 winmm.lib libc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib version.lib /nologo /subsystem:windows /profile /map:"goman.map"\
 /debug /machine:I386 /nodefaultlib:"libcd.lib" /out:"$(OUTDIR)/Goman.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Binload.obj" \
	"$(INTDIR)\Bldgboom.obj" \
	"$(INTDIR)\Boink2.obj" \
	"$(INTDIR)\Camera.obj" \
	"$(INTDIR)\Cars.obj" \
	"$(INTDIR)\Clutter.obj" \
	"$(INTDIR)\D3code.obj" \
	"$(INTDIR)\D3dapp.obj" \
	"$(INTDIR)\D3dcalls.obj" \
	"$(INTDIR)\Ddcalls.obj" \
	"$(INTDIR)\Fly.obj" \
	"$(INTDIR)\Global.obj" \
	"$(INTDIR)\Gosys.obj" \
	"$(INTDIR)\Ichars.obj" \
	"$(INTDIR)\Imisc.obj" \
	"$(INTDIR)\Ksbld.obj" \
	"$(INTDIR)\Landscap.obj" \
	"$(INTDIR)\Lclib.obj" \
	"$(INTDIR)\Lhbldg.obj" \
	"$(INTDIR)\Lmbldg.obj" \
	"$(INTDIR)\Lnbldg.obj" \
	"$(INTDIR)\Lrbldg.obj" \
	"$(INTDIR)\Lsbldg.obj" \
	"$(INTDIR)\Ltbldg.obj" \
	"$(INTDIR)\Lxbldg.obj" \
	"$(INTDIR)\Mdtex.obj" \
	"$(INTDIR)\Misc.obj" \
	"$(INTDIR)\Monanim2.obj" \
	"$(INTDIR)\Monmove2.obj" \
	"$(INTDIR)\Monthink.obj" \
	"$(INTDIR)\Mstrconv.obj" \
	"$(INTDIR)\Mstrhelp.obj" \
	"$(INTDIR)\netinit2.obj" \
	"$(INTDIR)\netmenu.obj" \
	"$(INTDIR)\netplay.obj" \
	"$(INTDIR)\Psystem.obj" \
	"$(INTDIR)\Radar.obj" \
	"$(INTDIR)\Rl2d3d.obj" \
	"$(INTDIR)\Rmfull.obj" \
	"$(INTDIR)\Rmstats.obj" \
	"$(INTDIR)\robotani2.obj" \
	"$(INTDIR)\robotmov2.obj" \
	"$(INTDIR)\Script1.res" \
	"$(INTDIR)\Sprite.obj" \
	"$(INTDIR)\Spudbmp.obj" \
	"$(INTDIR)\Tekanim.obj" \
	"$(INTDIR)\tekmath.obj" \
	"$(INTDIR)\Texture.obj" \
	"$(INTDIR)\Timing.obj" \
	"$(INTDIR)\tkinput.obj" \
	"$(INTDIR)\twist.obj" \
	"$(INTDIR)\Wassert.obj" \
	"$(INTDIR)\Wave.obj" \
	"$(INTDIR)\Wrapper.obj" \
	"$(INTDIR)\Xaf.obj" \
	"$(INTDIR)\Ybjoystk.obj" \
	"$(INTDIR)\Ybmid.obj" \
	"$(INTDIR)\Ybmm.obj" \
	"$(INTDIR)\Ybreg.obj" \
	"$(INTDIR)\Ybsnd.obj"

"$(OUTDIR)\Goman.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "GomanD3D - Win32 Release"
# Name "GomanD3D - Win32 Debug"

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Source\Ybsnd.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_YBSND=\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\wassert.h"\
	{$(INCLUDE)}"\wave.h"\
	{$(INCLUDE)}"\ybsnd.h"\
	
NODEP_CPP_YBSND=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Ybsnd.obj" : $(SOURCE) $(DEP_CPP_YBSND) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Ybsnd.sbr" : $(SOURCE) $(DEP_CPP_YBSND) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_YBSND=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmerror.h"\
	{$(INCLUDE)}"\wassert.h"\
	{$(INCLUDE)}"\wave.h"\
	{$(INCLUDE)}"\ybsnd.h"\
	
NODEP_CPP_YBSND=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Ybsnd.obj" : $(SOURCE) $(DEP_CPP_YBSND) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Ybsnd.sbr" : $(SOURCE) $(DEP_CPP_YBSND) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Bldgboom.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_BLDGB=\
	{$(INCLUDE)}"\bldgboom.h"\
	{$(INCLUDE)}"\building.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\landscap.h"\
	{$(INCLUDE)}"\lclib.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\mybuild.h"\
	{$(INCLUDE)}"\psystem.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\spritlib.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\wassert.h"\
	{$(INCLUDE)}"\wave.h"\
	{$(INCLUDE)}"\wrapper.h"\
	{$(INCLUDE)}"\ybsnd.h"\
	
NODEP_CPP_BLDGB=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Bldgboom.obj" : $(SOURCE) $(DEP_CPP_BLDGB) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Bldgboom.sbr" : $(SOURCE) $(DEP_CPP_BLDGB) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_BLDGB=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\bldgboom.h"\
	{$(INCLUDE)}"\building.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\landscap.h"\
	{$(INCLUDE)}"\lclib.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\mybuild.h"\
	{$(INCLUDE)}"\psystem.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmerror.h"\
	{$(INCLUDE)}"\spritlib.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\wassert.h"\
	{$(INCLUDE)}"\wave.h"\
	{$(INCLUDE)}"\wrapper.h"\
	{$(INCLUDE)}"\ybsnd.h"\
	
NODEP_CPP_BLDGB=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Bldgboom.obj" : $(SOURCE) $(DEP_CPP_BLDGB) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Bldgboom.sbr" : $(SOURCE) $(DEP_CPP_BLDGB) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Boink2.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_BOINK=\
	{$(INCLUDE)}"\binload.h"\
	{$(INCLUDE)}"\bldgboom.h"\
	{$(INCLUDE)}"\boink.h"\
	{$(INCLUDE)}"\building.h"\
	{$(INCLUDE)}"\clutter.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\imisc.h"\
	{$(INCLUDE)}"\keycom.h"\
	{$(INCLUDE)}"\landscap.h"\
	{$(INCLUDE)}"\lclib.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\monanim.h"\
	{$(INCLUDE)}"\monmove.h"\
	{$(INCLUDE)}"\netplay.h"\
	{$(INCLUDE)}"\plasma.h"\
	{$(INCLUDE)}"\psystem.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\spritlib.h"\
	{$(INCLUDE)}"\spudbmp.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\timing.h"\
	{$(INCLUDE)}"\wassert.h"\
	{$(INCLUDE)}"\wave.h"\
	{$(INCLUDE)}"\wrapper.h"\
	{$(INCLUDE)}"\ybsnd.h"\
	
NODEP_CPP_BOINK=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\Source\Robotanim.h"\
	".\Source\Robotmove.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Boink2.obj" : $(SOURCE) $(DEP_CPP_BOINK) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Boink2.sbr" : $(SOURCE) $(DEP_CPP_BOINK) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_BOINK=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\binload.h"\
	{$(INCLUDE)}"\bldgboom.h"\
	{$(INCLUDE)}"\boink.h"\
	{$(INCLUDE)}"\building.h"\
	{$(INCLUDE)}"\clutter.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\imisc.h"\
	{$(INCLUDE)}"\keycom.h"\
	{$(INCLUDE)}"\landscap.h"\
	{$(INCLUDE)}"\lclib.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\monanim.h"\
	{$(INCLUDE)}"\monmove.h"\
	{$(INCLUDE)}"\netplay.h"\
	{$(INCLUDE)}"\plasma.h"\
	{$(INCLUDE)}"\psystem.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmerror.h"\
	{$(INCLUDE)}"\spritlib.h"\
	{$(INCLUDE)}"\spudbmp.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\timing.h"\
	{$(INCLUDE)}"\wassert.h"\
	{$(INCLUDE)}"\wave.h"\
	{$(INCLUDE)}"\wrapper.h"\
	{$(INCLUDE)}"\ybsnd.h"\
	
NODEP_CPP_BOINK=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	".\Source\Robotanim.h"\
	".\Source\Robotmove.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Boink2.obj" : $(SOURCE) $(DEP_CPP_BOINK) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Boink2.sbr" : $(SOURCE) $(DEP_CPP_BOINK) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Camera.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_CAMER=\
	{$(INCLUDE)}"\binload.h"\
	{$(INCLUDE)}"\boink.h"\
	{$(INCLUDE)}"\building.h"\
	{$(INCLUDE)}"\byglobal.h"\
	{$(INCLUDE)}"\camera.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\ichars.h"\
	{$(INCLUDE)}"\landscap.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\monanim.h"\
	{$(INCLUDE)}"\monmove.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\timing.h"\
	{$(INCLUDE)}"\wrapper.h"\
	
NODEP_CPP_CAMER=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\Source\Robotanim.h"\
	".\Source\Robotmove.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Camera.obj" : $(SOURCE) $(DEP_CPP_CAMER) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Camera.sbr" : $(SOURCE) $(DEP_CPP_CAMER) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_CAMER=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\binload.h"\
	{$(INCLUDE)}"\boink.h"\
	{$(INCLUDE)}"\building.h"\
	{$(INCLUDE)}"\byglobal.h"\
	{$(INCLUDE)}"\camera.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\ichars.h"\
	{$(INCLUDE)}"\landscap.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\monanim.h"\
	{$(INCLUDE)}"\monmove.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmerror.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\timing.h"\
	{$(INCLUDE)}"\wrapper.h"\
	
NODEP_CPP_CAMER=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	".\Source\Robotanim.h"\
	".\Source\Robotmove.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Camera.obj" : $(SOURCE) $(DEP_CPP_CAMER) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Camera.sbr" : $(SOURCE) $(DEP_CPP_CAMER) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Cars.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_CARS_=\
	{$(INCLUDE)}"\binload.h"\
	{$(INCLUDE)}"\boink.h"\
	{$(INCLUDE)}"\building.h"\
	{$(INCLUDE)}"\camera.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\imisc.h"\
	{$(INCLUDE)}"\landscap.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\psystem.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\spritlib.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\timing.h"\
	{$(INCLUDE)}"\wassert.h"\
	{$(INCLUDE)}"\wave.h"\
	{$(INCLUDE)}"\ybsnd.h"\
	
NODEP_CPP_CARS_=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\Source\Robotanim.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Cars.obj" : $(SOURCE) $(DEP_CPP_CARS_) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Cars.sbr" : $(SOURCE) $(DEP_CPP_CARS_) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_CARS_=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\binload.h"\
	{$(INCLUDE)}"\boink.h"\
	{$(INCLUDE)}"\building.h"\
	{$(INCLUDE)}"\camera.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\imisc.h"\
	{$(INCLUDE)}"\landscap.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\psystem.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmerror.h"\
	{$(INCLUDE)}"\spritlib.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\timing.h"\
	{$(INCLUDE)}"\wassert.h"\
	{$(INCLUDE)}"\wave.h"\
	{$(INCLUDE)}"\ybsnd.h"\
	
NODEP_CPP_CARS_=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	".\Source\Robotanim.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Cars.obj" : $(SOURCE) $(DEP_CPP_CARS_) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Cars.sbr" : $(SOURCE) $(DEP_CPP_CARS_) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Clutter.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_CLUTT=\
	{$(INCLUDE)}"\binload.h"\
	{$(INCLUDE)}"\boink.h"\
	{$(INCLUDE)}"\byglobal.h"\
	{$(INCLUDE)}"\camera.h"\
	{$(INCLUDE)}"\clutter.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\imisc.h"\
	{$(INCLUDE)}"\landscap.h"\
	{$(INCLUDE)}"\lclib.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\netplay.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmfull.h"\
	{$(INCLUDE)}"\rmfullrc.h"\
	{$(INCLUDE)}"\spritlib.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\wassert.h"\
	{$(INCLUDE)}"\wave.h"\
	{$(INCLUDE)}"\wrapper.h"\
	{$(INCLUDE)}"\ybsnd.h"\
	
NODEP_CPP_CLUTT=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Clutter.obj" : $(SOURCE) $(DEP_CPP_CLUTT) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Clutter.sbr" : $(SOURCE) $(DEP_CPP_CLUTT) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_CLUTT=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\binload.h"\
	{$(INCLUDE)}"\boink.h"\
	{$(INCLUDE)}"\byglobal.h"\
	{$(INCLUDE)}"\camera.h"\
	{$(INCLUDE)}"\clutter.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\imisc.h"\
	{$(INCLUDE)}"\landscap.h"\
	{$(INCLUDE)}"\lclib.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\netplay.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmerror.h"\
	{$(INCLUDE)}"\rmfull.h"\
	{$(INCLUDE)}"\rmfullrc.h"\
	{$(INCLUDE)}"\spritlib.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\wassert.h"\
	{$(INCLUDE)}"\wave.h"\
	{$(INCLUDE)}"\wrapper.h"\
	{$(INCLUDE)}"\ybsnd.h"\
	
NODEP_CPP_CLUTT=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Clutter.obj" : $(SOURCE) $(DEP_CPP_CLUTT) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Clutter.sbr" : $(SOURCE) $(DEP_CPP_CLUTT) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\D3code.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_D3COD=\
	{$(INCLUDE)}"\d3code.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\D3code.obj" : $(SOURCE) $(DEP_CPP_D3COD) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\D3code.sbr" : $(SOURCE) $(DEP_CPP_D3COD) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_D3COD=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\d3code.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmerror.h"\
	
NODEP_CPP_D3COD=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\D3code.obj" : $(SOURCE) $(DEP_CPP_D3COD) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\D3code.sbr" : $(SOURCE) $(DEP_CPP_D3COD) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\D3dapp.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_D3DAP=\
	{$(INCLUDE)}"\byglobal.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\lclib.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmfull.h"\
	{$(INCLUDE)}"\rmfullrc.h"\
	{$(INCLUDE)}"\wrapper.h"\
	
NODEP_CPP_D3DAP=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\D3dapp.obj" : $(SOURCE) $(DEP_CPP_D3DAP) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\D3dapp.sbr" : $(SOURCE) $(DEP_CPP_D3DAP) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_D3DAP=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\byglobal.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\lclib.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmerror.h"\
	{$(INCLUDE)}"\rmfull.h"\
	{$(INCLUDE)}"\rmfullrc.h"\
	{$(INCLUDE)}"\wrapper.h"\
	
NODEP_CPP_D3DAP=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\D3dapp.obj" : $(SOURCE) $(DEP_CPP_D3DAP) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\D3dapp.sbr" : $(SOURCE) $(DEP_CPP_D3DAP) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\D3dcalls.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_D3DCA=\
	{$(INCLUDE)}"\byglobal.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\ybmm.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\D3dcalls.obj" : $(SOURCE) $(DEP_CPP_D3DCA) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\D3dcalls.sbr" : $(SOURCE) $(DEP_CPP_D3DCA) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_D3DCA=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\byglobal.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\lclib.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\ybmm.h"\
	
NODEP_CPP_D3DCA=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\D3dcalls.obj" : $(SOURCE) $(DEP_CPP_D3DCA) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\D3dcalls.sbr" : $(SOURCE) $(DEP_CPP_D3DCA) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Ddcalls.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_DDCAL=\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\lclib.h"\
	{$(INCLUDE)}"\wrapper.h"\
	
NODEP_CPP_DDCAL=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Ddcalls.obj" : $(SOURCE) $(DEP_CPP_DDCAL) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Ddcalls.sbr" : $(SOURCE) $(DEP_CPP_DDCAL) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_DDCAL=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\lclib.h"\
	{$(INCLUDE)}"\wrapper.h"\
	
NODEP_CPP_DDCAL=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Ddcalls.obj" : $(SOURCE) $(DEP_CPP_DDCAL) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Ddcalls.sbr" : $(SOURCE) $(DEP_CPP_DDCAL) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Fly.cpp

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_FLY_C=\
	{$(INCLUDE)}"\binload.h"\
	{$(INCLUDE)}"\bldgboom.h"\
	{$(INCLUDE)}"\boink.h"\
	{$(INCLUDE)}"\building.h"\
	{$(INCLUDE)}"\byglobal.h"\
	{$(INCLUDE)}"\camera.h"\
	{$(INCLUDE)}"\cars.h"\
	{$(INCLUDE)}"\clutter.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\dinput.h"\
	{$(INCLUDE)}"\fly.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\ichars.h"\
	{$(INCLUDE)}"\imisc.h"\
	{$(INCLUDE)}"\keycom.h"\
	{$(INCLUDE)}"\landscap.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\monanim.h"\
	{$(INCLUDE)}"\monmove.h"\
	{$(INCLUDE)}"\monthink.h"\
	{$(INCLUDE)}"\mybuild.h"\
	{$(INCLUDE)}"\netplay.h"\
	{$(INCLUDE)}"\plasma.h"\
	{$(INCLUDE)}"\psystem.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmfull.h"\
	{$(INCLUDE)}"\rmfullrc.h"\
	{$(INCLUDE)}"\robotanim.h"\
	{$(INCLUDE)}"\robotmove.h"\
	{$(INCLUDE)}"\spritlib.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\timing.h"\
	{$(INCLUDE)}"\tkinput.h"\
	{$(INCLUDE)}"\wrapper.h"\
	
NODEP_CPP_FLY_C=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Fly.obj" : $(SOURCE) $(DEP_CPP_FLY_C) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Fly.sbr" : $(SOURCE) $(DEP_CPP_FLY_C) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_FLY_C=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\binload.h"\
	{$(INCLUDE)}"\bldgboom.h"\
	{$(INCLUDE)}"\boink.h"\
	{$(INCLUDE)}"\building.h"\
	{$(INCLUDE)}"\byglobal.h"\
	{$(INCLUDE)}"\camera.h"\
	{$(INCLUDE)}"\cars.h"\
	{$(INCLUDE)}"\clutter.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\dinput.h"\
	{$(INCLUDE)}"\fly.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\ichars.h"\
	{$(INCLUDE)}"\imisc.h"\
	{$(INCLUDE)}"\keycom.h"\
	{$(INCLUDE)}"\landscap.h"\
	{$(INCLUDE)}"\lclib.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\monanim.h"\
	{$(INCLUDE)}"\monmove.h"\
	{$(INCLUDE)}"\monthink.h"\
	{$(INCLUDE)}"\mybuild.h"\
	{$(INCLUDE)}"\netplay.h"\
	{$(INCLUDE)}"\plasma.h"\
	{$(INCLUDE)}"\psystem.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmerror.h"\
	{$(INCLUDE)}"\rmfull.h"\
	{$(INCLUDE)}"\rmfullrc.h"\
	{$(INCLUDE)}"\robotanim.h"\
	{$(INCLUDE)}"\robotmove.h"\
	{$(INCLUDE)}"\spritlib.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\timing.h"\
	{$(INCLUDE)}"\tkinput.h"\
	{$(INCLUDE)}"\wrapper.h"\
	
NODEP_CPP_FLY_C=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Fly.obj" : $(SOURCE) $(DEP_CPP_FLY_C) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Fly.sbr" : $(SOURCE) $(DEP_CPP_FLY_C) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Global.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_GLOBA=\
	{$(INCLUDE)}"\camera.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\plasma.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\spritlib.h"\
	{$(INCLUDE)}"\tekanim.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Global.obj" : $(SOURCE) $(DEP_CPP_GLOBA) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Global.sbr" : $(SOURCE) $(DEP_CPP_GLOBA) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_GLOBA=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\camera.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\plasma.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmerror.h"\
	{$(INCLUDE)}"\spritlib.h"\
	{$(INCLUDE)}"\tekanim.h"\
	
NODEP_CPP_GLOBA=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Global.obj" : $(SOURCE) $(DEP_CPP_GLOBA) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Global.sbr" : $(SOURCE) $(DEP_CPP_GLOBA) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Gosys.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_GOSYS=\
	{$(INCLUDE)}"\binload.h"\
	{$(INCLUDE)}"\bldgboom.h"\
	{$(INCLUDE)}"\boink.h"\
	{$(INCLUDE)}"\building.h"\
	{$(INCLUDE)}"\byglobal.h"\
	{$(INCLUDE)}"\camera.h"\
	{$(INCLUDE)}"\cars.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\ichars.h"\
	{$(INCLUDE)}"\keycom.h"\
	{$(INCLUDE)}"\landscap.h"\
	{$(INCLUDE)}"\lclib.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\monanim.h"\
	{$(INCLUDE)}"\monmove.h"\
	{$(INCLUDE)}"\monthink.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmfull.h"\
	{$(INCLUDE)}"\rmfullrc.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\wassert.h"\
	{$(INCLUDE)}"\wave.h"\
	{$(INCLUDE)}"\wrapper.h"\
	{$(INCLUDE)}"\ybreg.h"\
	{$(INCLUDE)}"\ybsnd.h"\
	
NODEP_CPP_GOSYS=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\Source\Robotmove.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Gosys.obj" : $(SOURCE) $(DEP_CPP_GOSYS) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Gosys.sbr" : $(SOURCE) $(DEP_CPP_GOSYS) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_GOSYS=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\binload.h"\
	{$(INCLUDE)}"\bldgboom.h"\
	{$(INCLUDE)}"\boink.h"\
	{$(INCLUDE)}"\building.h"\
	{$(INCLUDE)}"\byglobal.h"\
	{$(INCLUDE)}"\camera.h"\
	{$(INCLUDE)}"\cars.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\ichars.h"\
	{$(INCLUDE)}"\keycom.h"\
	{$(INCLUDE)}"\landscap.h"\
	{$(INCLUDE)}"\lclib.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\monanim.h"\
	{$(INCLUDE)}"\monmove.h"\
	{$(INCLUDE)}"\monthink.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmerror.h"\
	{$(INCLUDE)}"\rmfull.h"\
	{$(INCLUDE)}"\rmfullrc.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\wassert.h"\
	{$(INCLUDE)}"\wave.h"\
	{$(INCLUDE)}"\wrapper.h"\
	{$(INCLUDE)}"\ybreg.h"\
	{$(INCLUDE)}"\ybsnd.h"\
	
NODEP_CPP_GOSYS=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	".\Source\Robotmove.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Gosys.obj" : $(SOURCE) $(DEP_CPP_GOSYS) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Gosys.sbr" : $(SOURCE) $(DEP_CPP_GOSYS) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Ichars.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_ICHAR=\
	{$(INCLUDE)}"\binload.h"\
	{$(INCLUDE)}"\boink.h"\
	{$(INCLUDE)}"\building.h"\
	{$(INCLUDE)}"\camera.h"\
	{$(INCLUDE)}"\cars.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\ichars.h"\
	{$(INCLUDE)}"\landscap.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\monanim.h"\
	{$(INCLUDE)}"\monmove.h"\
	{$(INCLUDE)}"\psystem.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\spritlib.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\timing.h"\
	{$(INCLUDE)}"\ybsnd.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Ichars.obj" : $(SOURCE) $(DEP_CPP_ICHAR) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Ichars.sbr" : $(SOURCE) $(DEP_CPP_ICHAR) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_ICHAR=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\binload.h"\
	{$(INCLUDE)}"\boink.h"\
	{$(INCLUDE)}"\building.h"\
	{$(INCLUDE)}"\camera.h"\
	{$(INCLUDE)}"\cars.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\ichars.h"\
	{$(INCLUDE)}"\landscap.h"\
	{$(INCLUDE)}"\lclib.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\monanim.h"\
	{$(INCLUDE)}"\monmove.h"\
	{$(INCLUDE)}"\psystem.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmerror.h"\
	{$(INCLUDE)}"\spritlib.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\timing.h"\
	{$(INCLUDE)}"\wassert.h"\
	{$(INCLUDE)}"\wave.h"\
	{$(INCLUDE)}"\ybsnd.h"\
	
NODEP_CPP_ICHAR=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Ichars.obj" : $(SOURCE) $(DEP_CPP_ICHAR) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Ichars.sbr" : $(SOURCE) $(DEP_CPP_ICHAR) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Imisc.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_IMISC=\
	{$(INCLUDE)}"\binload.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\imisc.h"\
	{$(INCLUDE)}"\lclib.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\tekmath.h"\
	
NODEP_CPP_IMISC=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Imisc.obj" : $(SOURCE) $(DEP_CPP_IMISC) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Imisc.sbr" : $(SOURCE) $(DEP_CPP_IMISC) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_IMISC=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\binload.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\imisc.h"\
	{$(INCLUDE)}"\lclib.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmerror.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\tekmath.h"\
	
NODEP_CPP_IMISC=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Imisc.obj" : $(SOURCE) $(DEP_CPP_IMISC) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Imisc.sbr" : $(SOURCE) $(DEP_CPP_IMISC) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Ksbld.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_KSBLD=\
	{$(INCLUDE)}"\building.h"\
	{$(INCLUDE)}"\byglobal.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\landscap.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\mybuild.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\viewer.h"\
	
NODEP_CPP_KSBLD=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Ksbld.obj" : $(SOURCE) $(DEP_CPP_KSBLD) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Ksbld.sbr" : $(SOURCE) $(DEP_CPP_KSBLD) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_KSBLD=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\building.h"\
	{$(INCLUDE)}"\byglobal.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\landscap.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\mybuild.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmerror.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\viewer.h"\
	
NODEP_CPP_KSBLD=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Ksbld.obj" : $(SOURCE) $(DEP_CPP_KSBLD) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Ksbld.sbr" : $(SOURCE) $(DEP_CPP_KSBLD) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Landscap.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_LANDS=\
	{$(INCLUDE)}"\building.h"\
	{$(INCLUDE)}"\clutter.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\landscap.h"\
	{$(INCLUDE)}"\lclib.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\psystem.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmfull.h"\
	{$(INCLUDE)}"\rmfullrc.h"\
	{$(INCLUDE)}"\spritlib.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\wassert.h"\
	{$(INCLUDE)}"\wave.h"\
	{$(INCLUDE)}"\ybsnd.h"\
	
NODEP_CPP_LANDS=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Landscap.obj" : $(SOURCE) $(DEP_CPP_LANDS) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Landscap.sbr" : $(SOURCE) $(DEP_CPP_LANDS) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_LANDS=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\building.h"\
	{$(INCLUDE)}"\clutter.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\landscap.h"\
	{$(INCLUDE)}"\lclib.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\psystem.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmerror.h"\
	{$(INCLUDE)}"\rmfull.h"\
	{$(INCLUDE)}"\rmfullrc.h"\
	{$(INCLUDE)}"\spritlib.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\wassert.h"\
	{$(INCLUDE)}"\wave.h"\
	{$(INCLUDE)}"\ybsnd.h"\
	
NODEP_CPP_LANDS=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Landscap.obj" : $(SOURCE) $(DEP_CPP_LANDS) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Landscap.sbr" : $(SOURCE) $(DEP_CPP_LANDS) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Lclib.c
DEP_CPP_LCLIB=\
	{$(INCLUDE)}"\lclib.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Lclib.obj" : $(SOURCE) $(DEP_CPP_LCLIB) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Lclib.sbr" : $(SOURCE) $(DEP_CPP_LCLIB) "$(INTDIR)"
   $(BuildCmds)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Lhbldg.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_LHBLD=\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\tekanim.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Lhbldg.obj" : $(SOURCE) $(DEP_CPP_LHBLD) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Lhbldg.sbr" : $(SOURCE) $(DEP_CPP_LHBLD) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_LHBLD=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\tekanim.h"\
	
NODEP_CPP_LHBLD=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Lhbldg.obj" : $(SOURCE) $(DEP_CPP_LHBLD) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Lhbldg.sbr" : $(SOURCE) $(DEP_CPP_LHBLD) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Lmbldg.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_LMBLD=\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\tekanim.h"\
	
NODEP_CPP_LMBLD=\
	".\Source\imode.h"\
	".\Source\rl.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Lmbldg.obj" : $(SOURCE) $(DEP_CPP_LMBLD) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Lmbldg.sbr" : $(SOURCE) $(DEP_CPP_LMBLD) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_LMBLD=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\tekanim.h"\
	
NODEP_CPP_LMBLD=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	".\Source\imode.h"\
	".\Source\rl.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Lmbldg.obj" : $(SOURCE) $(DEP_CPP_LMBLD) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Lmbldg.sbr" : $(SOURCE) $(DEP_CPP_LMBLD) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Lnbldg.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_LNBLD=\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\tekanim.h"\
	
NODEP_CPP_LNBLD=\
	".\Source\imode.h"\
	".\Source\rl.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Lnbldg.obj" : $(SOURCE) $(DEP_CPP_LNBLD) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Lnbldg.sbr" : $(SOURCE) $(DEP_CPP_LNBLD) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_LNBLD=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\tekanim.h"\
	
NODEP_CPP_LNBLD=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	".\Source\imode.h"\
	".\Source\rl.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Lnbldg.obj" : $(SOURCE) $(DEP_CPP_LNBLD) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Lnbldg.sbr" : $(SOURCE) $(DEP_CPP_LNBLD) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Lrbldg.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_LRBLD=\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\tekanim.h"\
	
NODEP_CPP_LRBLD=\
	".\Source\imode.h"\
	".\Source\rl.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Lrbldg.obj" : $(SOURCE) $(DEP_CPP_LRBLD) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Lrbldg.sbr" : $(SOURCE) $(DEP_CPP_LRBLD) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_LRBLD=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\tekanim.h"\
	
NODEP_CPP_LRBLD=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	".\Source\imode.h"\
	".\Source\rl.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Lrbldg.obj" : $(SOURCE) $(DEP_CPP_LRBLD) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Lrbldg.sbr" : $(SOURCE) $(DEP_CPP_LRBLD) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Lsbldg.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_LSBLD=\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\tekanim.h"\
	
NODEP_CPP_LSBLD=\
	".\Source\imode.h"\
	".\Source\rl.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Lsbldg.obj" : $(SOURCE) $(DEP_CPP_LSBLD) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Lsbldg.sbr" : $(SOURCE) $(DEP_CPP_LSBLD) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_LSBLD=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\tekanim.h"\
	
NODEP_CPP_LSBLD=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	".\Source\imode.h"\
	".\Source\rl.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Lsbldg.obj" : $(SOURCE) $(DEP_CPP_LSBLD) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Lsbldg.sbr" : $(SOURCE) $(DEP_CPP_LSBLD) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Ltbldg.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_LTBLD=\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\tekanim.h"\
	
NODEP_CPP_LTBLD=\
	".\Source\imode.h"\
	".\Source\rl.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Ltbldg.obj" : $(SOURCE) $(DEP_CPP_LTBLD) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Ltbldg.sbr" : $(SOURCE) $(DEP_CPP_LTBLD) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_LTBLD=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\tekanim.h"\
	
NODEP_CPP_LTBLD=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	".\Source\imode.h"\
	".\Source\rl.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Ltbldg.obj" : $(SOURCE) $(DEP_CPP_LTBLD) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Ltbldg.sbr" : $(SOURCE) $(DEP_CPP_LTBLD) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Lxbldg.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_LXBLD=\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\tekanim.h"\
	
NODEP_CPP_LXBLD=\
	".\Source\imode.h"\
	".\Source\rl.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Lxbldg.obj" : $(SOURCE) $(DEP_CPP_LXBLD) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Lxbldg.sbr" : $(SOURCE) $(DEP_CPP_LXBLD) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_LXBLD=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\tekanim.h"\
	
NODEP_CPP_LXBLD=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	".\Source\imode.h"\
	".\Source\rl.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Lxbldg.obj" : $(SOURCE) $(DEP_CPP_LXBLD) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Lxbldg.sbr" : $(SOURCE) $(DEP_CPP_LXBLD) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Mdtex.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_MDTEX=\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\wrapper.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Mdtex.obj" : $(SOURCE) $(DEP_CPP_MDTEX) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Mdtex.sbr" : $(SOURCE) $(DEP_CPP_MDTEX) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_MDTEX=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\lclib.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmerror.h"\
	{$(INCLUDE)}"\wrapper.h"\
	
NODEP_CPP_MDTEX=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Mdtex.obj" : $(SOURCE) $(DEP_CPP_MDTEX) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Mdtex.sbr" : $(SOURCE) $(DEP_CPP_MDTEX) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Misc.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_MISC_=\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\tekanim.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Misc.obj" : $(SOURCE) $(DEP_CPP_MISC_) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Misc.sbr" : $(SOURCE) $(DEP_CPP_MISC_) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_MISC_=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\lclib.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\tekanim.h"\
	
NODEP_CPP_MISC_=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Misc.obj" : $(SOURCE) $(DEP_CPP_MISC_) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Misc.sbr" : $(SOURCE) $(DEP_CPP_MISC_) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Monanim2.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_MONAN=\
	{$(INCLUDE)}"\binload.h"\
	{$(INCLUDE)}"\boink.h"\
	{$(INCLUDE)}"\config.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\ichars.h"\
	{$(INCLUDE)}"\keycom.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\monanim.h"\
	{$(INCLUDE)}"\monmove.h"\
	{$(INCLUDE)}"\plasma.h"\
	{$(INCLUDE)}"\psystem.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\spritlib.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\timing.h"\
	{$(INCLUDE)}"\wassert.h"\
	{$(INCLUDE)}"\wave.h"\
	{$(INCLUDE)}"\ybsnd.h"\
	
NODEP_CPP_MONAN=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\Source\Robotanim.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Monanim2.obj" : $(SOURCE) $(DEP_CPP_MONAN) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Monanim2.sbr" : $(SOURCE) $(DEP_CPP_MONAN) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_MONAN=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\binload.h"\
	{$(INCLUDE)}"\boink.h"\
	{$(INCLUDE)}"\config.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\ichars.h"\
	{$(INCLUDE)}"\keycom.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\monanim.h"\
	{$(INCLUDE)}"\monmove.h"\
	{$(INCLUDE)}"\plasma.h"\
	{$(INCLUDE)}"\psystem.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmerror.h"\
	{$(INCLUDE)}"\spritlib.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\timing.h"\
	{$(INCLUDE)}"\wassert.h"\
	{$(INCLUDE)}"\wave.h"\
	{$(INCLUDE)}"\ybsnd.h"\
	
NODEP_CPP_MONAN=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	".\Source\Robotanim.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Monanim2.obj" : $(SOURCE) $(DEP_CPP_MONAN) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Monanim2.sbr" : $(SOURCE) $(DEP_CPP_MONAN) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Monmove2.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_MONMO=\
	{$(INCLUDE)}"\boink.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\keycom.h"\
	{$(INCLUDE)}"\monanim.h"\
	{$(INCLUDE)}"\monmove.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\spudbmp.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\timing.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Monmove2.obj" : $(SOURCE) $(DEP_CPP_MONMO) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Monmove2.sbr" : $(SOURCE) $(DEP_CPP_MONMO) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_MONMO=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\boink.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\keycom.h"\
	{$(INCLUDE)}"\monanim.h"\
	{$(INCLUDE)}"\monmove.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\spudbmp.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\timing.h"\
	
NODEP_CPP_MONMO=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Monmove2.obj" : $(SOURCE) $(DEP_CPP_MONMO) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Monmove2.sbr" : $(SOURCE) $(DEP_CPP_MONMO) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Monthink.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_MONTH=\
	{$(INCLUDE)}"\boink.h"\
	{$(INCLUDE)}"\building.h"\
	{$(INCLUDE)}"\cars.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\keycom.h"\
	{$(INCLUDE)}"\landscap.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\monanim.h"\
	{$(INCLUDE)}"\monmove.h"\
	{$(INCLUDE)}"\monthink.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\timing.h"\
	{$(INCLUDE)}"\wrapper.h"\
	
NODEP_CPP_MONTH=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\Source\Robotanim.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Monthink.obj" : $(SOURCE) $(DEP_CPP_MONTH) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Monthink.sbr" : $(SOURCE) $(DEP_CPP_MONTH) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_MONTH=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\boink.h"\
	{$(INCLUDE)}"\building.h"\
	{$(INCLUDE)}"\cars.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\keycom.h"\
	{$(INCLUDE)}"\landscap.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\monanim.h"\
	{$(INCLUDE)}"\monmove.h"\
	{$(INCLUDE)}"\monthink.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmerror.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\timing.h"\
	{$(INCLUDE)}"\wrapper.h"\
	
NODEP_CPP_MONTH=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	".\Source\Robotanim.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Monthink.obj" : $(SOURCE) $(DEP_CPP_MONTH) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Monthink.sbr" : $(SOURCE) $(DEP_CPP_MONTH) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Mstrconv.c
DEP_CPP_MSTRC=\
	{$(INCLUDE)}"\midstuff.h"\
	{$(INCLUDE)}"\mstream.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Mstrconv.obj" : $(SOURCE) $(DEP_CPP_MSTRC) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Mstrconv.sbr" : $(SOURCE) $(DEP_CPP_MSTRC) "$(INTDIR)"
   $(BuildCmds)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Mstrhelp.c
DEP_CPP_MSTRH=\
	{$(INCLUDE)}"\midstuff.h"\
	{$(INCLUDE)}"\mstream.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Mstrhelp.obj" : $(SOURCE) $(DEP_CPP_MSTRH) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Mstrhelp.sbr" : $(SOURCE) $(DEP_CPP_MSTRH) "$(INTDIR)"
   $(BuildCmds)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Psystem.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_PSYST=\
	{$(INCLUDE)}"\boink.h"\
	{$(INCLUDE)}"\clutter.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\lclib.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\monmove.h"\
	{$(INCLUDE)}"\psystem.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\spritlib.h"\
	{$(INCLUDE)}"\tekanim.h"\
	
NODEP_CPP_PSYST=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\Source\Robotmove.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Psystem.obj" : $(SOURCE) $(DEP_CPP_PSYST) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Psystem.sbr" : $(SOURCE) $(DEP_CPP_PSYST) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_PSYST=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\boink.h"\
	{$(INCLUDE)}"\clutter.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\lclib.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\monmove.h"\
	{$(INCLUDE)}"\psystem.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmerror.h"\
	{$(INCLUDE)}"\spritlib.h"\
	{$(INCLUDE)}"\tekanim.h"\
	
NODEP_CPP_PSYST=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	".\Source\Robotmove.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Psystem.obj" : $(SOURCE) $(DEP_CPP_PSYST) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Psystem.sbr" : $(SOURCE) $(DEP_CPP_PSYST) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Radar.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_RADAR=\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\radar.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\tekanim.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Radar.obj" : $(SOURCE) $(DEP_CPP_RADAR) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Radar.sbr" : $(SOURCE) $(DEP_CPP_RADAR) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_RADAR=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\radar.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\tekanim.h"\
	
NODEP_CPP_RADAR=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Radar.obj" : $(SOURCE) $(DEP_CPP_RADAR) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Radar.sbr" : $(SOURCE) $(DEP_CPP_RADAR) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Rl2d3d.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_RL2D3=\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\tekanim.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Rl2d3d.obj" : $(SOURCE) $(DEP_CPP_RL2D3) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Rl2d3d.sbr" : $(SOURCE) $(DEP_CPP_RL2D3) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_RL2D3=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\tekanim.h"\
	
NODEP_CPP_RL2D3=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Rl2d3d.obj" : $(SOURCE) $(DEP_CPP_RL2D3) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Rl2d3d.sbr" : $(SOURCE) $(DEP_CPP_RL2D3) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Rmfull.cpp

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_RMFUL=\
	{$(INCLUDE)}"\binload.h"\
	{$(INCLUDE)}"\byglobal.h"\
	{$(INCLUDE)}"\clutter.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\dinput.h"\
	{$(INCLUDE)}"\fly.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\imisc.h"\
	{$(INCLUDE)}"\input.h"\
	{$(INCLUDE)}"\keycom.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\midstuff.h"\
	{$(INCLUDE)}"\netinit2.h"\
	{$(INCLUDE)}"\netmenu.h"\
	{$(INCLUDE)}"\netplay.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmfull.h"\
	{$(INCLUDE)}"\rmfullrc.h"\
	{$(INCLUDE)}"\spritlib.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\tkinput.h"\
	{$(INCLUDE)}"\wrapper.h"\
	{$(INCLUDE)}"\ybjoystk.h"\
	{$(INCLUDE)}"\ybmid.h"\
	{$(INCLUDE)}"\ybmm.h"\
	{$(INCLUDE)}"\ybreg.h"\
	
NODEP_CPP_RMFUL=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Rmfull.obj" : $(SOURCE) $(DEP_CPP_RMFUL) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Rmfull.sbr" : $(SOURCE) $(DEP_CPP_RMFUL) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_RMFUL=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\binload.h"\
	{$(INCLUDE)}"\byglobal.h"\
	{$(INCLUDE)}"\clutter.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\dinput.h"\
	{$(INCLUDE)}"\fly.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\imisc.h"\
	{$(INCLUDE)}"\input.h"\
	{$(INCLUDE)}"\keycom.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\midstuff.h"\
	{$(INCLUDE)}"\netinit2.h"\
	{$(INCLUDE)}"\netmenu.h"\
	{$(INCLUDE)}"\netplay.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmerror.h"\
	{$(INCLUDE)}"\rmfull.h"\
	{$(INCLUDE)}"\rmfullrc.h"\
	{$(INCLUDE)}"\spritlib.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\tkinput.h"\
	{$(INCLUDE)}"\wrapper.h"\
	{$(INCLUDE)}"\ybjoystk.h"\
	{$(INCLUDE)}"\ybmid.h"\
	{$(INCLUDE)}"\ybmm.h"\
	{$(INCLUDE)}"\ybreg.h"\
	
NODEP_CPP_RMFUL=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Rmfull.obj" : $(SOURCE) $(DEP_CPP_RMFUL) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Rmfull.sbr" : $(SOURCE) $(DEP_CPP_RMFUL) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Rmstats.cpp

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_RMSTA=\
	{$(INCLUDE)}"\byglobal.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmfull.h"\
	{$(INCLUDE)}"\rmfullrc.h"\
	{$(INCLUDE)}"\wrapper.h"\
	
NODEP_CPP_RMSTA=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Rmstats.obj" : $(SOURCE) $(DEP_CPP_RMSTA) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Rmstats.sbr" : $(SOURCE) $(DEP_CPP_RMSTA) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_RMSTA=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\byglobal.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmerror.h"\
	{$(INCLUDE)}"\rmfull.h"\
	{$(INCLUDE)}"\rmfullrc.h"\
	{$(INCLUDE)}"\wrapper.h"\
	
NODEP_CPP_RMSTA=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Rmstats.obj" : $(SOURCE) $(DEP_CPP_RMSTA) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Rmstats.sbr" : $(SOURCE) $(DEP_CPP_RMSTA) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Sprite.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_SPRIT=\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\lclib.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\spritlib.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\tekmath.h"\
	
NODEP_CPP_SPRIT=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Sprite.obj" : $(SOURCE) $(DEP_CPP_SPRIT) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Sprite.sbr" : $(SOURCE) $(DEP_CPP_SPRIT) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_SPRIT=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\lclib.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmerror.h"\
	{$(INCLUDE)}"\spritlib.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\tekmath.h"\
	
NODEP_CPP_SPRIT=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Sprite.obj" : $(SOURCE) $(DEP_CPP_SPRIT) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Sprite.sbr" : $(SOURCE) $(DEP_CPP_SPRIT) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Spudbmp.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_SPUDB=\
	{$(INCLUDE)}"\boink.h"\
	{$(INCLUDE)}"\building.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\keycom.h"\
	{$(INCLUDE)}"\landscap.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\spudbmp.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\wassert.h"\
	{$(INCLUDE)}"\wave.h"\
	{$(INCLUDE)}"\ybsnd.h"\
	
NODEP_CPP_SPUDB=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Spudbmp.obj" : $(SOURCE) $(DEP_CPP_SPUDB) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Spudbmp.sbr" : $(SOURCE) $(DEP_CPP_SPUDB) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_SPUDB=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\boink.h"\
	{$(INCLUDE)}"\building.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\keycom.h"\
	{$(INCLUDE)}"\landscap.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmerror.h"\
	{$(INCLUDE)}"\spudbmp.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\wassert.h"\
	{$(INCLUDE)}"\wave.h"\
	{$(INCLUDE)}"\ybsnd.h"\
	
NODEP_CPP_SPUDB=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Spudbmp.obj" : $(SOURCE) $(DEP_CPP_SPUDB) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Spudbmp.sbr" : $(SOURCE) $(DEP_CPP_SPUDB) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Tekanim.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_TEKAN=\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\tekanim.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Tekanim.obj" : $(SOURCE) $(DEP_CPP_TEKAN) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Tekanim.sbr" : $(SOURCE) $(DEP_CPP_TEKAN) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_TEKAN=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\tekanim.h"\
	
NODEP_CPP_TEKAN=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Tekanim.obj" : $(SOURCE) $(DEP_CPP_TEKAN) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Tekanim.sbr" : $(SOURCE) $(DEP_CPP_TEKAN) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Texture.c
DEP_CPP_TEXTU=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\lclib.h"\
	
NODEP_CPP_TEXTU=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Texture.obj" : $(SOURCE) $(DEP_CPP_TEXTU) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Texture.sbr" : $(SOURCE) $(DEP_CPP_TEXTU) "$(INTDIR)"
   $(BuildCmds)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Timing.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_TIMIN=\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\keycom.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\timing.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Timing.obj" : $(SOURCE) $(DEP_CPP_TIMIN) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Timing.sbr" : $(SOURCE) $(DEP_CPP_TIMIN) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_TIMIN=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\keycom.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\timing.h"\
	
NODEP_CPP_TIMIN=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Timing.obj" : $(SOURCE) $(DEP_CPP_TIMIN) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Timing.sbr" : $(SOURCE) $(DEP_CPP_TIMIN) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\twist.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_TWIST=\
	{$(INCLUDE)}"\binload.h"\
	{$(INCLUDE)}"\bldgboom.h"\
	{$(INCLUDE)}"\building.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\landscap.h"\
	{$(INCLUDE)}"\lclib.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\mybuild.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\tekanim.h"\
	
NODEP_CPP_TWIST=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\twist.obj" : $(SOURCE) $(DEP_CPP_TWIST) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\twist.sbr" : $(SOURCE) $(DEP_CPP_TWIST) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_TWIST=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\binload.h"\
	{$(INCLUDE)}"\bldgboom.h"\
	{$(INCLUDE)}"\building.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\landscap.h"\
	{$(INCLUDE)}"\lclib.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\mybuild.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmerror.h"\
	{$(INCLUDE)}"\tekanim.h"\
	
NODEP_CPP_TWIST=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\twist.obj" : $(SOURCE) $(DEP_CPP_TWIST) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\twist.sbr" : $(SOURCE) $(DEP_CPP_TWIST) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Wassert.c
DEP_CPP_WASSE=\
	{$(INCLUDE)}"\wassert.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Wassert.obj" : $(SOURCE) $(DEP_CPP_WASSE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Wassert.sbr" : $(SOURCE) $(DEP_CPP_WASSE) "$(INTDIR)"
   $(BuildCmds)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Wave.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_WAVE_=\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\wassert.h"\
	{$(INCLUDE)}"\wave.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Wave.obj" : $(SOURCE) $(DEP_CPP_WAVE_) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Wave.sbr" : $(SOURCE) $(DEP_CPP_WAVE_) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_WAVE_=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\wassert.h"\
	{$(INCLUDE)}"\wave.h"\
	
NODEP_CPP_WAVE_=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Wave.obj" : $(SOURCE) $(DEP_CPP_WAVE_) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Wave.sbr" : $(SOURCE) $(DEP_CPP_WAVE_) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Wrapper.cpp

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_WRAPP=\
	{$(INCLUDE)}"\byglobal.h"\
	{$(INCLUDE)}"\camera.h"\
	{$(INCLUDE)}"\d3code.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\dinput.h"\
	{$(INCLUDE)}"\fly.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\keycom.h"\
	{$(INCLUDE)}"\midstuff.h"\
	{$(INCLUDE)}"\monanim.h"\
	{$(INCLUDE)}"\mstream.h"\
	{$(INCLUDE)}"\netinit2.h"\
	{$(INCLUDE)}"\netmenu.h"\
	{$(INCLUDE)}"\netplay.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmfull.h"\
	{$(INCLUDE)}"\rmfullrc.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\timing.h"\
	{$(INCLUDE)}"\tkinput.h"\
	{$(INCLUDE)}"\wrapdata.h"\
	{$(INCLUDE)}"\wrapper.h"\
	{$(INCLUDE)}"\ybjoystk.h"\
	{$(INCLUDE)}"\ybmid.h"\
	{$(INCLUDE)}"\ybmm.h"\
	{$(INCLUDE)}"\ybreg.h"\
	{$(INCLUDE)}"\ybsnd.h"\
	
NODEP_CPP_WRAPP=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Wrapper.obj" : $(SOURCE) $(DEP_CPP_WRAPP) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Wrapper.sbr" : $(SOURCE) $(DEP_CPP_WRAPP) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_WRAPP=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\byglobal.h"\
	{$(INCLUDE)}"\camera.h"\
	{$(INCLUDE)}"\d3code.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\dinput.h"\
	{$(INCLUDE)}"\fly.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\keycom.h"\
	{$(INCLUDE)}"\lclib.h"\
	{$(INCLUDE)}"\midstuff.h"\
	{$(INCLUDE)}"\monanim.h"\
	{$(INCLUDE)}"\mstream.h"\
	{$(INCLUDE)}"\netinit2.h"\
	{$(INCLUDE)}"\netmenu.h"\
	{$(INCLUDE)}"\netplay.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmerror.h"\
	{$(INCLUDE)}"\rmfull.h"\
	{$(INCLUDE)}"\rmfullrc.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\timing.h"\
	{$(INCLUDE)}"\tkinput.h"\
	{$(INCLUDE)}"\wassert.h"\
	{$(INCLUDE)}"\wave.h"\
	{$(INCLUDE)}"\wrapdata.h"\
	{$(INCLUDE)}"\wrapper.h"\
	{$(INCLUDE)}"\ybjoystk.h"\
	{$(INCLUDE)}"\ybmid.h"\
	{$(INCLUDE)}"\ybmm.h"\
	{$(INCLUDE)}"\ybreg.h"\
	{$(INCLUDE)}"\ybsnd.h"\
	
NODEP_CPP_WRAPP=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Wrapper.obj" : $(SOURCE) $(DEP_CPP_WRAPP) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Wrapper.sbr" : $(SOURCE) $(DEP_CPP_WRAPP) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Xaf.cpp

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_XAF_C=\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\tekanim.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Xaf.obj" : $(SOURCE) $(DEP_CPP_XAF_C) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Xaf.sbr" : $(SOURCE) $(DEP_CPP_XAF_C) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_XAF_C=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\tekanim.h"\
	
NODEP_CPP_XAF_C=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Xaf.obj" : $(SOURCE) $(DEP_CPP_XAF_C) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Xaf.sbr" : $(SOURCE) $(DEP_CPP_XAF_C) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Ybjoystk.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_YBJOY=\
	{$(INCLUDE)}"\byglobal.h"\
	{$(INCLUDE)}"\camera.h"\
	{$(INCLUDE)}"\d3code.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\keycom.h"\
	{$(INCLUDE)}"\lclib.h"\
	{$(INCLUDE)}"\midstuff.h"\
	{$(INCLUDE)}"\Mmddk.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmfull.h"\
	{$(INCLUDE)}"\rmfullrc.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\wassert.h"\
	{$(INCLUDE)}"\wave.h"\
	{$(INCLUDE)}"\wrapper.h"\
	{$(INCLUDE)}"\ybjoystk.h"\
	{$(INCLUDE)}"\ybmid.h"\
	{$(INCLUDE)}"\ybsnd.h"\
	
NODEP_CPP_YBJOY=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Ybjoystk.obj" : $(SOURCE) $(DEP_CPP_YBJOY) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Ybjoystk.sbr" : $(SOURCE) $(DEP_CPP_YBJOY) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_YBJOY=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\byglobal.h"\
	{$(INCLUDE)}"\camera.h"\
	{$(INCLUDE)}"\d3code.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\keycom.h"\
	{$(INCLUDE)}"\lclib.h"\
	{$(INCLUDE)}"\midstuff.h"\
	{$(INCLUDE)}"\Mmddk.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmerror.h"\
	{$(INCLUDE)}"\rmfull.h"\
	{$(INCLUDE)}"\rmfullrc.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\wassert.h"\
	{$(INCLUDE)}"\wave.h"\
	{$(INCLUDE)}"\wrapper.h"\
	{$(INCLUDE)}"\ybjoystk.h"\
	{$(INCLUDE)}"\ybmid.h"\
	{$(INCLUDE)}"\ybsnd.h"\
	
NODEP_CPP_YBJOY=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Ybjoystk.obj" : $(SOURCE) $(DEP_CPP_YBJOY) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Ybjoystk.sbr" : $(SOURCE) $(DEP_CPP_YBJOY) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Ybmid.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_YBMID=\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\midstuff.h"\
	{$(INCLUDE)}"\mstream.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\ybmid.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Ybmid.obj" : $(SOURCE) $(DEP_CPP_YBMID) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Ybmid.sbr" : $(SOURCE) $(DEP_CPP_YBMID) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_YBMID=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\midstuff.h"\
	{$(INCLUDE)}"\mstream.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\ybmid.h"\
	
NODEP_CPP_YBMID=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Ybmid.obj" : $(SOURCE) $(DEP_CPP_YBMID) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Ybmid.sbr" : $(SOURCE) $(DEP_CPP_YBMID) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Ybmm.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_YBMM_=\
	{$(INCLUDE)}"\byglobal.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\lclib.h"\
	{$(INCLUDE)}"\ybmm.h"\
	
NODEP_CPP_YBMM_=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Ybmm.obj" : $(SOURCE) $(DEP_CPP_YBMM_) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Ybmm.sbr" : $(SOURCE) $(DEP_CPP_YBMM_) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_YBMM_=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\byglobal.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\lclib.h"\
	{$(INCLUDE)}"\ybmm.h"\
	
NODEP_CPP_YBMM_=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Ybmm.obj" : $(SOURCE) $(DEP_CPP_YBMM_) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Ybmm.sbr" : $(SOURCE) $(DEP_CPP_YBMM_) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Ybreg.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_YBREG=\
	{$(INCLUDE)}"\byglobal.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\ybreg.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Ybreg.obj" : $(SOURCE) $(DEP_CPP_YBREG) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Ybreg.sbr" : $(SOURCE) $(DEP_CPP_YBREG) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_YBREG=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\byglobal.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\ybreg.h"\
	
NODEP_CPP_YBREG=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Ybreg.obj" : $(SOURCE) $(DEP_CPP_YBREG) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Ybreg.sbr" : $(SOURCE) $(DEP_CPP_YBREG) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\Binload.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_BINLO=\
	{$(INCLUDE)}"\binload.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\tekanim.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Binload.obj" : $(SOURCE) $(DEP_CPP_BINLO) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Binload.sbr" : $(SOURCE) $(DEP_CPP_BINLO) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_BINLO=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\binload.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\tekanim.h"\
	
NODEP_CPP_BINLO=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Binload.obj" : $(SOURCE) $(DEP_CPP_BINLO) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Binload.sbr" : $(SOURCE) $(DEP_CPP_BINLO) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\tkinput.cpp

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_TKINP=\
	{$(INCLUDE)}"\byglobal.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\dinput.h"\
	{$(INCLUDE)}"\lclib.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmfull.h"\
	{$(INCLUDE)}"\rmfullrc.h"\
	{$(INCLUDE)}"\tkinput.h"\
	{$(INCLUDE)}"\wrapper.h"\
	{$(INCLUDE)}"\ybmm.h"\
	
NODEP_CPP_TKINP=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\tkinput.obj" : $(SOURCE) $(DEP_CPP_TKINP) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\tkinput.sbr" : $(SOURCE) $(DEP_CPP_TKINP) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_TKINP=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\byglobal.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\dinput.h"\
	{$(INCLUDE)}"\lclib.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmerror.h"\
	{$(INCLUDE)}"\rmfull.h"\
	{$(INCLUDE)}"\rmfullrc.h"\
	{$(INCLUDE)}"\tkinput.h"\
	{$(INCLUDE)}"\wrapper.h"\
	{$(INCLUDE)}"\ybmm.h"\
	
NODEP_CPP_TKINP=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\tkinput.obj" : $(SOURCE) $(DEP_CPP_TKINP) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\tkinput.sbr" : $(SOURCE) $(DEP_CPP_TKINP) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\netplay.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_NETPL=\
	{$(INCLUDE)}"\boink.h"\
	{$(INCLUDE)}"\building.h"\
	{$(INCLUDE)}"\byglobal.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\keycom.h"\
	{$(INCLUDE)}"\landscap.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\monanim.h"\
	{$(INCLUDE)}"\netplay.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\tekanim.h"\
	
NODEP_CPP_NETPL=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\netplay.obj" : $(SOURCE) $(DEP_CPP_NETPL) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\netplay.sbr" : $(SOURCE) $(DEP_CPP_NETPL) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_NETPL=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\boink.h"\
	{$(INCLUDE)}"\building.h"\
	{$(INCLUDE)}"\byglobal.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\keycom.h"\
	{$(INCLUDE)}"\landscap.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\monanim.h"\
	{$(INCLUDE)}"\netplay.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmerror.h"\
	{$(INCLUDE)}"\tekanim.h"\
	
NODEP_CPP_NETPL=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\netplay.obj" : $(SOURCE) $(DEP_CPP_NETPL) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\netplay.sbr" : $(SOURCE) $(DEP_CPP_NETPL) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\netinit2.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_NETIN=\
	{$(INCLUDE)}"\byglobal.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\keycom.h"\
	{$(INCLUDE)}"\lclib.h"\
	{$(INCLUDE)}"\midstuff.h"\
	{$(INCLUDE)}"\netinit2.h"\
	{$(INCLUDE)}"\netmenu.h"\
	{$(INCLUDE)}"\netplay.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmfull.h"\
	{$(INCLUDE)}"\rmfullrc.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\wassert.h"\
	{$(INCLUDE)}"\wave.h"\
	{$(INCLUDE)}"\wrapper.h"\
	{$(INCLUDE)}"\ybmid.h"\
	{$(INCLUDE)}"\ybsnd.h"\
	
NODEP_CPP_NETIN=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\netinit2.obj" : $(SOURCE) $(DEP_CPP_NETIN) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\netinit2.sbr" : $(SOURCE) $(DEP_CPP_NETIN) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_NETIN=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\byglobal.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\keycom.h"\
	{$(INCLUDE)}"\lclib.h"\
	{$(INCLUDE)}"\midstuff.h"\
	{$(INCLUDE)}"\netinit2.h"\
	{$(INCLUDE)}"\netmenu.h"\
	{$(INCLUDE)}"\netplay.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmerror.h"\
	{$(INCLUDE)}"\rmfull.h"\
	{$(INCLUDE)}"\rmfullrc.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\wassert.h"\
	{$(INCLUDE)}"\wave.h"\
	{$(INCLUDE)}"\wrapper.h"\
	{$(INCLUDE)}"\ybmid.h"\
	{$(INCLUDE)}"\ybsnd.h"\
	
NODEP_CPP_NETIN=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\netinit2.obj" : $(SOURCE) $(DEP_CPP_NETIN) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\netinit2.sbr" : $(SOURCE) $(DEP_CPP_NETIN) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\netmenu.cpp

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_NETME=\
	{$(INCLUDE)}"\byglobal.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\lclib.h"\
	{$(INCLUDE)}"\netinit2.h"\
	{$(INCLUDE)}"\netmenu.h"\
	{$(INCLUDE)}"\netplay.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmfull.h"\
	{$(INCLUDE)}"\rmfullrc.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\wrapper.h"\
	
NODEP_CPP_NETME=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\netmenu.obj" : $(SOURCE) $(DEP_CPP_NETME) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\netmenu.sbr" : $(SOURCE) $(DEP_CPP_NETME) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_NETME=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\byglobal.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dapp.h"\
	{$(INCLUDE)}"\d3dappi.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\lclib.h"\
	{$(INCLUDE)}"\netinit2.h"\
	{$(INCLUDE)}"\netmenu.h"\
	{$(INCLUDE)}"\netplay.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmerror.h"\
	{$(INCLUDE)}"\rmfull.h"\
	{$(INCLUDE)}"\rmfullrc.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\wrapper.h"\
	
NODEP_CPP_NETME=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\netmenu.obj" : $(SOURCE) $(DEP_CPP_NETME) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\netmenu.sbr" : $(SOURCE) $(DEP_CPP_NETME) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Script1.rc
DEP_RSC_SCRIP=\
	".\icon1.ico"\
	

"$(INTDIR)\Script1.res" : $(SOURCE) $(DEP_RSC_SCRIP) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Source\tekmath.c
DEP_CPP_TEKMA=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dmacs.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	
NODEP_CPP_TEKMA=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\tekmath.obj" : $(SOURCE) $(DEP_CPP_TEKMA) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\tekmath.sbr" : $(SOURCE) $(DEP_CPP_TEKMA) "$(INTDIR)"
   $(BuildCmds)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\source\robotmov2.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_ROBOT=\
	{$(INCLUDE)}"\bldgboom.h"\
	{$(INCLUDE)}"\boink.h"\
	{$(INCLUDE)}"\building.h"\
	{$(INCLUDE)}"\clutter.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\keycom.h"\
	{$(INCLUDE)}"\landscap.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\spudbmp.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\timing.h"\
	{$(INCLUDE)}"\wassert.h"\
	{$(INCLUDE)}"\wave.h"\
	{$(INCLUDE)}"\ybsnd.h"\
	
NODEP_CPP_ROBOT=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\Source\Robotanim.h"\
	".\Source\Robotmove.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\robotmov2.obj" : $(SOURCE) $(DEP_CPP_ROBOT) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\robotmov2.sbr" : $(SOURCE) $(DEP_CPP_ROBOT) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_ROBOT=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\bldgboom.h"\
	{$(INCLUDE)}"\boink.h"\
	{$(INCLUDE)}"\building.h"\
	{$(INCLUDE)}"\clutter.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\keycom.h"\
	{$(INCLUDE)}"\landscap.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmerror.h"\
	{$(INCLUDE)}"\spudbmp.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\timing.h"\
	{$(INCLUDE)}"\wassert.h"\
	{$(INCLUDE)}"\wave.h"\
	{$(INCLUDE)}"\ybsnd.h"\
	
NODEP_CPP_ROBOT=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	".\Source\Robotanim.h"\
	".\Source\Robotmove.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\robotmov2.obj" : $(SOURCE) $(DEP_CPP_ROBOT) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\robotmov2.sbr" : $(SOURCE) $(DEP_CPP_ROBOT) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\source\robotani2.c

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

DEP_CPP_ROBOTA=\
	{$(INCLUDE)}"\binload.h"\
	{$(INCLUDE)}"\boink.h"\
	{$(INCLUDE)}"\clutter.h"\
	{$(INCLUDE)}"\config.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\ichars.h"\
	{$(INCLUDE)}"\imisc.h"\
	{$(INCLUDE)}"\keycom.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\monanim.h"\
	{$(INCLUDE)}"\plasma.h"\
	{$(INCLUDE)}"\psystem.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\spritlib.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\timing.h"\
	{$(INCLUDE)}"\wassert.h"\
	{$(INCLUDE)}"\wave.h"\
	{$(INCLUDE)}"\wrapper.h"\
	{$(INCLUDE)}"\ybsnd.h"\
	
NODEP_CPP_ROBOTA=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\Source\Robotanim.h"\
	".\Source\Robotmove.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\robotani2.obj" : $(SOURCE) $(DEP_CPP_ROBOTA) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\robotani2.sbr" : $(SOURCE) $(DEP_CPP_ROBOTA) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

DEP_CPP_ROBOTA=\
	"..\..\Dxsdk\sdk\inc\d3dvec.inl"\
	{$(INCLUDE)}"\binload.h"\
	{$(INCLUDE)}"\boink.h"\
	{$(INCLUDE)}"\clutter.h"\
	{$(INCLUDE)}"\config.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmdef.h"\
	{$(INCLUDE)}"\d3drmobj.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\global.h"\
	{$(INCLUDE)}"\gosys.h"\
	{$(INCLUDE)}"\ichars.h"\
	{$(INCLUDE)}"\imisc.h"\
	{$(INCLUDE)}"\keycom.h"\
	{$(INCLUDE)}"\mdtex.h"\
	{$(INCLUDE)}"\monanim.h"\
	{$(INCLUDE)}"\plasma.h"\
	{$(INCLUDE)}"\psystem.h"\
	{$(INCLUDE)}"\rl2d3d.h"\
	{$(INCLUDE)}"\rmdemo.h"\
	{$(INCLUDE)}"\rmerror.h"\
	{$(INCLUDE)}"\spritlib.h"\
	{$(INCLUDE)}"\tekanim.h"\
	{$(INCLUDE)}"\timing.h"\
	{$(INCLUDE)}"\wassert.h"\
	{$(INCLUDE)}"\wave.h"\
	{$(INCLUDE)}"\wrapper.h"\
	{$(INCLUDE)}"\ybsnd.h"\
	
NODEP_CPP_ROBOTA=\
	".\..\..\DXSDK\sdk\inc\d3dcom.h"\
	".\..\..\DXSDK\sdk\inc\subwtype.h"\
	".\Source\Robotanim.h"\
	".\Source\Robotmove.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\robotani2.obj" : $(SOURCE) $(DEP_CPP_ROBOTA) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\robotani2.sbr" : $(SOURCE) $(DEP_CPP_ROBOTA) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\include\robotmove.h

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\include\robotanim.h

!IF  "$(CFG)" == "GomanD3D - Win32 Release"

!ELSEIF  "$(CFG)" == "GomanD3D - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
