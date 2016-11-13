# Microsoft Developer Studio Generated NMAKE File, Based on SeqenceQueue.dsp
!IF $(CFG)" == "
CFG=SeqenceQueue - Win32 Debug
!MESSAGE No configuration specified. Defaulting to SeqenceQueue - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "SeqenceQueue - Win32 Release" && "$(CFG)" != "SeqenceQueue - Win32 Debug"
!MESSAGE 指定的配置 "$(CFG)" 无效.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SeqenceQueue.mak" CFG="SeqenceQueue - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SeqenceQueue - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "SeqenceQueue - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF $(OS)" == "Windows_NT
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SeqenceQueue - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# 开始自定义宏
OutDir=.\Release
# 结束自定义宏

ALL : "$(OUTDIR)\SeqenceQueue.exe"


CLEAN :
	-@erase "$(INTDIR)\SeqenceQueue.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\SeqenceQueue.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\SeqenceQueue.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SeqenceQueue.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\SeqenceQueue.pdb" /machine:I386 /out:"$(OUTDIR)\SeqenceQueue.exe" 
LINK32_OBJS= \
	"$(INTDIR)\SeqenceQueue.obj"

"$(OUTDIR)\SeqenceQueue.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SeqenceQueue - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# 开始自定义宏
OutDir=.\Debug
# 结束自定义宏

ALL : "$(OUTDIR)\SeqenceQueue.exe"


CLEAN :
	-@erase "$(INTDIR)\SeqenceQueue.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\SeqenceQueue.exe"
	-@erase "$(OUTDIR)\SeqenceQueue.ilk"
	-@erase "$(OUTDIR)\SeqenceQueue.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\SeqenceQueue.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SeqenceQueue.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\SeqenceQueue.pdb" /debug /machine:I386 /out:"$(OUTDIR)\SeqenceQueue.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\SeqenceQueue.obj"

"$(OUTDIR)\SeqenceQueue.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("SeqenceQueue.dep")
!INCLUDE "SeqenceQueue.dep"
!ELSE 
!MESSAGE Warning: cannot find "SeqenceQueue.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "SeqenceQueue - Win32 Release" || "$(CFG)" == "SeqenceQueue - Win32 Debug"
SOURCE=.\SeqenceQueue.cpp

"$(INTDIR)\SeqenceQueue.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

