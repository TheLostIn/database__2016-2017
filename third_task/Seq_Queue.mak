# Microsoft Developer Studio Generated NMAKE File, Based on Seq_Queue.dsp
!IF $(CFG)" == "
CFG=Seq_Queue - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Seq_Queue - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Seq_Queue - Win32 Release" && "$(CFG)" != "Seq_Queue - Win32 Debug"
!MESSAGE 指定的配置 "$(CFG)" 无效.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Seq_Queue.mak" CFG="Seq_Queue - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Seq_Queue - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "Seq_Queue - Win32 Debug" (based on "Win32 (x86) Console Application")
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

!IF  "$(CFG)" == "Seq_Queue - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# 开始自定义宏
OutDir=.\Release
# 结束自定义宏

ALL : "$(OUTDIR)\Seq_Queue.exe"


CLEAN :
	-@erase "$(INTDIR)\Seq_Queue.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Seq_Queue.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\Seq_Queue.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Seq_Queue.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\Seq_Queue.pdb" /machine:I386 /out:"$(OUTDIR)\Seq_Queue.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Seq_Queue.obj"

"$(OUTDIR)\Seq_Queue.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Seq_Queue - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# 开始自定义宏
OutDir=.\Debug
# 结束自定义宏

ALL : "$(OUTDIR)\Seq_Queue.exe"


CLEAN :
	-@erase "$(INTDIR)\Seq_Queue.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Seq_Queue.exe"
	-@erase "$(OUTDIR)\Seq_Queue.ilk"
	-@erase "$(OUTDIR)\Seq_Queue.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\Seq_Queue.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Seq_Queue.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\Seq_Queue.pdb" /debug /machine:I386 /out:"$(OUTDIR)\Seq_Queue.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\Seq_Queue.obj"

"$(OUTDIR)\Seq_Queue.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("Seq_Queue.dep")
!INCLUDE "Seq_Queue.dep"
!ELSE 
!MESSAGE Warning: cannot find "Seq_Queue.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Seq_Queue - Win32 Release" || "$(CFG)" == "Seq_Queue - Win32 Debug"
SOURCE=.\Seq_Queue.cpp

"$(INTDIR)\Seq_Queue.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

