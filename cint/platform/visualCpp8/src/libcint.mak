# Microsoft Developer Studio Generated NMAKE File, Based on libcint.dsp
!IF "$(CFG)" == ""
CFG=libcint - Win32 Release
!MESSAGE No configuration specified. Defaulting to libcint - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "libcint - Win32 Release" && "$(CFG)" != "libcint - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libcint.mak" CFG="libcint - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libcint - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "libcint - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "libcint - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\libcint.dll"


CLEAN :
	-@erase "$(INTDIR)\API.OBJ"
	-@erase "$(INTDIR)\APIIF.OBJ"
	-@erase "$(INTDIR)\V6_AUXU.OBJ"
	-@erase "$(INTDIR)\BASECLS.OBJ"
	-@erase "$(INTDIR)\bc_assign.obj"
   	-@erase "$(INTDIR)\bc_cfunc.OBJ"
	-@erase "$(INTDIR)\bc_eh.obj"
	-@erase "$(INTDIR)\bc_inst.obj"
	-@erase "$(INTDIR)\bc_reader.OBJ"
	-@erase "$(INTDIR)\bc_vtbl.obj"
	-@erase "$(INTDIR)\bc_autoobj.OBJ"
	-@erase "$(INTDIR)\bc_debug.OBJ"
	-@erase "$(INTDIR)\bc_exec.OBJ"
	-@erase "$(INTDIR)\bc_parse.OBJ"
	-@erase "$(INTDIR)\bc_type.obj"
	-@erase "$(INTDIR)\CALLFUNC.OBJ"
	-@erase "$(INTDIR)\V6_CAST.OBJ"
	-@erase "$(INTDIR)\CLASS.OBJ"
	-@erase "$(INTDIR)\DATAMBR.OBJ"
	-@erase "$(INTDIR)\v6_DEBUG.OBJ"
	-@erase "$(INTDIR)\V6_DECL.OBJ"
	-@erase "$(INTDIR)\V6_DISP.OBJ"
	-@erase "$(INTDIR)\V6_DUMP.OBJ"
	-@erase "$(INTDIR)\V6_END.OBJ"
	-@erase "$(INTDIR)\V6_ERROR.OBJ"
	-@erase "$(INTDIR)\V6_EXPR.OBJ"
	-@erase "$(INTDIR)\V6_FREAD.OBJ"
	-@erase "$(INTDIR)\V6_FUNC.OBJ"
	-@erase "$(INTDIR)\G__CFUNC.OBJ"
	-@erase "$(INTDIR)\G__SETUP.OBJ"
	-@erase "$(INTDIR)\V6_GCOLL.OBJ"
	-@erase "$(INTDIR)\V6_GLOBAL1.OBJ"
	-@erase "$(INTDIR)\V6_GLOBAL2.OBJ"
	-@erase "$(INTDIR)\V6_IFUNC.OBJ"
	-@erase "$(INTDIR)\V6_INHERIT.OBJ"
	-@erase "$(INTDIR)\V6_INIT.OBJ"
	-@erase "$(INTDIR)\V6_INPUT.OBJ"
	-@erase "$(INTDIR)\V6_INTRPT.OBJ"
	-@erase "$(INTDIR)\V6_LOADFILE.OBJ"
	-@erase "$(INTDIR)\V6_MACRO.OBJ"
	-@erase "$(INTDIR)\V6_MALLOC.OBJ"
	-@erase "$(INTDIR)\V6_MEMTEST.OBJ"
	-@erase "$(INTDIR)\METHOD.OBJ"
	-@erase "$(INTDIR)\METHODAR.OBJ"
	-@erase "$(INTDIR)\V6_NEW.OBJ"
	-@erase "$(INTDIR)\V6_NEWLINK.OBJ"
	-@erase "$(INTDIR)\V6_OLDLINK.OBJ"
	-@erase "$(INTDIR)\V6_OPR.OBJ"
	-@erase "$(INTDIR)\V6_PARSE.OBJ"
	-@erase "$(INTDIR)\V6_PAUSE.OBJ"
	-@erase "$(INTDIR)\V6_PCODE.OBJ"
	-@erase "$(INTDIR)\V6_PRAGMA.OBJ"
	-@erase "$(INTDIR)\V6_QUOTE.OBJ"
	-@erase "$(INTDIR)\V6_SCRUPTO.OBJ"
	-@erase "$(INTDIR)\V6_SHL.OBJ"
	-@erase "$(INTDIR)\V6_SIZEOF.OBJ"
	-@erase "$(INTDIR)\V6_STDSTRCT.OBJ"
	-@erase "$(INTDIR)\V6_STRUCT.OBJ"
	-@erase "$(INTDIR)\V6_STUB.OBJ"
	-@erase "$(INTDIR)\V6_TMPLT.OBJ"
	-@erase "$(INTDIR)\Token.obj"
	-@erase "$(INTDIR)\TYPE.OBJ"
	-@erase "$(INTDIR)\V6_TYPEDEF.OBJ"
	-@erase "$(INTDIR)\TYPEDF.OBJ"
	-@erase "$(INTDIR)\V6_VAL2A.OBJ"
	-@erase "$(INTDIR)\V6_VALUE.OBJ"
	-@erase "$(INTDIR)\V6_VAR.OBJ"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\iccstrm.obj"
	-@erase "$(INTDIR)\V6_WINNT.OBJ"
	-@erase "$(INTDIR)\SHADOW.OBJ"
	-@erase "$(INTDIR)\RFLX_GENDICT.OBJ"
	-@erase "$(INTDIR)\RFLX_GENSRC.OBJ"
	-@erase "$(INTDIR)\RFLX_TOOLS.OBJ"
	-@erase "$(OUTDIR)\libcint.dll"
	-@erase "$(OUTDIR)\libcint.exp"
	-@erase "$(OUTDIR)\libcint.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPPMAIN_PROJ=/nologo /MT /w /W0 /EHsc /I "..\.." /I ".." /I "..\..\lib\iccstrm" /I "..\..\lib\stdstrct" /D _CRT_SECURE_NO_DEPRECATE /D _SECURE_SCL /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "G__NEWSTDHEADER" /D "G__VISUAL" /D "G__WIN32" /D "G__SHAREDLIB" /D "G__REDIRECTIO" /D "G__P2FCAST" /Fp"$(INTDIR)\libcint.pch" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_PROJ=/O2 $(CPPMAIN_PROJ)
CPPO1_PROJ=/O1 $(CPPMAIN_PROJ)

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

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\libcint.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\libcint.pdb" /machine:I386 /def:".\libcint.def" /out:"$(OUTDIR)\libcint.dll" /implib:"$(OUTDIR)\libcint.lib" 
DEF_FILE= \
	".\libcint.def"
LINK32_OBJS= \
	"$(INTDIR)\API.OBJ" \
	"$(INTDIR)\APIIF.OBJ" \
	"$(INTDIR)\V6_AUXU.OBJ" \
	"$(INTDIR)\BASECLS.OBJ" \
	"$(INTDIR)\bc_assign.obj" \
   	"$(INTDIR)\bc_cfunc.OBJ" \
	"$(INTDIR)\bc_eh.obj" \
	"$(INTDIR)\bc_inst.obj" \
	"$(INTDIR)\bc_reader.OBJ" \
	"$(INTDIR)\bc_vtbl.obj" \
	"$(INTDIR)\bc_autoobj.OBJ" \
	"$(INTDIR)\bc_debug.OBJ" \
	"$(INTDIR)\bc_exec.OBJ" \
	"$(INTDIR)\bc_parse.OBJ" \
	"$(INTDIR)\bc_type.obj" \
	"$(INTDIR)\CALLFUNC.OBJ" \
	"$(INTDIR)\V6_CAST.OBJ" \
	"$(INTDIR)\CLASS.OBJ" \
	"$(INTDIR)\DATAMBR.OBJ" \
	"$(INTDIR)\V6_DEBUG.OBJ" \
	"$(INTDIR)\V6_DECL.OBJ" \
	"$(INTDIR)\V6_DISP.OBJ" \
	"$(INTDIR)\V6_DUMP.OBJ" \
	"$(INTDIR)\V6_END.OBJ" \
	"$(INTDIR)\V6_ERROR.OBJ" \
	"$(INTDIR)\V6_EXPR.OBJ" \
	"$(INTDIR)\V6_FREAD.OBJ" \
	"$(INTDIR)\V6_FUNC.OBJ" \
	"$(INTDIR)\G__CFUNC.OBJ" \
	"$(INTDIR)\G__SETUP.OBJ" \
	"$(INTDIR)\V6_GCOLL.OBJ" \
	"$(INTDIR)\V6_GLOBAL1.OBJ" \
	"$(INTDIR)\V6_GLOBAL2.OBJ" \
	"$(INTDIR)\V6_IFUNC.OBJ" \
	"$(INTDIR)\V6_INHERIT.OBJ" \
	"$(INTDIR)\V6_INIT.OBJ" \
	"$(INTDIR)\V6_INPUT.OBJ" \
	"$(INTDIR)\V6_INTRPT.OBJ" \
	"$(INTDIR)\V6_LOADFILE.OBJ" \
	"$(INTDIR)\V6_MACRO.OBJ" \
	"$(INTDIR)\V6_MALLOC.OBJ" \
	"$(INTDIR)\V6_MEMTEST.OBJ" \
	"$(INTDIR)\METHOD.OBJ" \
	"$(INTDIR)\METHODAR.OBJ" \
	"$(INTDIR)\V6_NEW.OBJ" \
	"$(INTDIR)\V6_NEWLINK.OBJ" \
	"$(INTDIR)\V6_OLDLINK.OBJ" \
	"$(INTDIR)\V6_OPR.OBJ" \
	"$(INTDIR)\V6_PARSE.OBJ" \
	"$(INTDIR)\V6_PAUSE.OBJ" \
	"$(INTDIR)\V6_PCODE.OBJ" \
	"$(INTDIR)\V6_PRAGMA.OBJ" \
	"$(INTDIR)\V6_QUOTE.OBJ" \
	"$(INTDIR)\V6_SCRUPTO.OBJ" \
	"$(INTDIR)\V6_SHL.OBJ" \
	"$(INTDIR)\V6_SIZEOF.OBJ" \
	"$(INTDIR)\V6_STDSTRCT.OBJ" \
	"$(INTDIR)\V6_STRUCT.OBJ" \
	"$(INTDIR)\V6_STUB.OBJ" \
	"$(INTDIR)\V6_TMPLT.OBJ" \
	"$(INTDIR)\Token.obj" \
	"$(INTDIR)\TYPE.OBJ" \
	"$(INTDIR)\V6_TYPEDEF.OBJ" \
	"$(INTDIR)\TYPEDF.OBJ" \
	"$(INTDIR)\V6_VAL2A.OBJ" \
	"$(INTDIR)\V6_VALUE.OBJ" \
	"$(INTDIR)\V6_VAR.OBJ" \
	"$(INTDIR)\iccstrm.obj" \
	"$(INTDIR)\V6_WINNT.OBJ" \
	"$(INTDIR)\SHADOW.OBJ" \
	"$(INTDIR)\RFLX_GENDICT.OBJ" \
	"$(INTDIR)\RFLX_GENSRC.OBJ" \
	"$(INTDIR)\RFLX_TOOLS.OBJ"

"$(OUTDIR)\libcint.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "libcint - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\libcint.dll"


CLEAN :
	-@erase "$(INTDIR)\API.OBJ"
	-@erase "$(INTDIR)\APIIF.OBJ"
	-@erase "$(INTDIR)\V6_AUXU.OBJ"
	-@erase "$(INTDIR)\BASECLS.OBJ"
	-@erase "$(INTDIR)\bc_assign.obj"
   	-@erase "$(INTDIR)\bc_cfunc.OBJ"
	-@erase "$(INTDIR)\bc_eh.obj"
	-@erase "$(INTDIR)\bc_inst.obj"
	-@erase "$(INTDIR)\bc_reader.OBJ"
	-@erase "$(INTDIR)\bc_vtbl.obj"
	-@erase "$(INTDIR)\bc_autoobj.OBJ"
	-@erase "$(INTDIR)\bc_debug.OBJ"
	-@erase "$(INTDIR)\bc_exec.OBJ"
	-@erase "$(INTDIR)\bc_parse.OBJ"
	-@erase "$(INTDIR)\bc_type.obj"
	-@erase "$(INTDIR)\CALLFUNC.OBJ"
	-@erase "$(INTDIR)\V6_CAST.OBJ"
	-@erase "$(INTDIR)\CLASS.OBJ"
	-@erase "$(INTDIR)\DATAMBR.OBJ"
	-@erase "$(INTDIR)\V6_DEBUG.OBJ"
	-@erase "$(INTDIR)\V6_DECL.OBJ"
	-@erase "$(INTDIR)\V6_DISP.OBJ"
	-@erase "$(INTDIR)\V6_DUMP.OBJ"
	-@erase "$(INTDIR)\V6_END.OBJ"
	-@erase "$(INTDIR)\V6_ERROR.OBJ"
	-@erase "$(INTDIR)\V6_EXPR.OBJ"
	-@erase "$(INTDIR)\V6_FREAD.OBJ"
	-@erase "$(INTDIR)\V6_FUNC.OBJ"
	-@erase "$(INTDIR)\G__CFUNC.OBJ"
	-@erase "$(INTDIR)\G__SETUP.OBJ"
	-@erase "$(INTDIR)\V6_GCOLL.OBJ"
	-@erase "$(INTDIR)\V6_GLOBAL1.OBJ"
	-@erase "$(INTDIR)\V6_GLOBAL2.OBJ"
	-@erase "$(INTDIR)\V6_IFUNC.OBJ"
	-@erase "$(INTDIR)\V6_INHERIT.OBJ"
	-@erase "$(INTDIR)\V6_INIT.OBJ"
	-@erase "$(INTDIR)\V6_INPUT.OBJ"
	-@erase "$(INTDIR)\V6_INTRPT.OBJ"
	-@erase "$(INTDIR)\V6_LOADFILE.OBJ"
	-@erase "$(INTDIR)\V6_MACRO.OBJ"
	-@erase "$(INTDIR)\V6_MALLOC.OBJ"
	-@erase "$(INTDIR)\V6_MEMTEST.OBJ"
	-@erase "$(INTDIR)\METHOD.OBJ"
	-@erase "$(INTDIR)\METHODAR.OBJ"
	-@erase "$(INTDIR)\V6_NEW.OBJ"
	-@erase "$(INTDIR)\V6_NEWLINK.OBJ"
	-@erase "$(INTDIR)\V6_OLDLINK.OBJ"
	-@erase "$(INTDIR)\V6_OPR.OBJ"
	-@erase "$(INTDIR)\V6_PARSE.OBJ"
	-@erase "$(INTDIR)\V6_PAUSE.OBJ"
	-@erase "$(INTDIR)\V6_PCODE.OBJ"
	-@erase "$(INTDIR)\V6_PRAGMA.OBJ"
	-@erase "$(INTDIR)\V6_QUOTE.OBJ"
	-@erase "$(INTDIR)\V6_SCRUPTO.OBJ"
	-@erase "$(INTDIR)\V6_SHL.OBJ"
	-@erase "$(INTDIR)\V6_SIZEOF.OBJ"
	-@erase "$(INTDIR)\V6_STDSTRCT.OBJ"
	-@erase "$(INTDIR)\V6_STRUCT.OBJ"
	-@erase "$(INTDIR)\V6_STUB.OBJ"
	-@erase "$(INTDIR)\V6_TMPLT.OBJ"
	-@erase "$(INTDIR)\Token.obj"
	-@erase "$(INTDIR)\TYPE.OBJ"
	-@erase "$(INTDIR)\V6_TYPEDEF.OBJ"
	-@erase "$(INTDIR)\TYPEDF.OBJ"
	-@erase "$(INTDIR)\V6_VAL2A.OBJ"
	-@erase "$(INTDIR)\V6_VALUE.OBJ"
	-@erase "$(INTDIR)\V6_VAR.OBJ"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\iccstrm.obj"
	-@erase "$(INTDIR)\V6_WINNT.OBJ"
	-@erase "$(INTDIR)\SHADOW.OBJ"
	-@erase "$(INTDIR)\RFLX_GENDICT.OBJ"
	-@erase "$(INTDIR)\RFLX_GENSRC.OBJ"
	-@erase "$(INTDIR)\RFLX_TOOLS.OBJ"
	-@erase "$(OUTDIR)\libcint.dll"
	-@erase "$(OUTDIR)\libcint.exp"
	-@erase "$(OUTDIR)\libcint.ilk"
	-@erase "$(OUTDIR)\libcint.lib"
	-@erase "$(OUTDIR)\libcint.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /EHsc /ZI /Od /I "..\.." /I ".." /I "..\..\lib\iccstrm" /I "..\..\lib\stdstrct" /D _CRT_SECURE_NO_DEPRECATE /D _SECURE_SCL /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "G__NEWSTDHEADER" /D "G__VISUAL" /D "G__WIN32" /D "G__SHAREDLIB" /D "G__REDIRECTIO" /D "G__P2FCAST" /D "G__ASM_DBG" /Fp"$(INTDIR)\libcint.pch" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPPO1_PROJ=$(CPP_PROJ)

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

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\libcint.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\libcint.pdb" /debug /machine:I386 /def:".\libcint.def" /out:"$(OUTDIR)\libcint.dll" /implib:"$(OUTDIR)\libcint.lib" 
DEF_FILE= \
	".\libcint.def"
LINK32_OBJS= \
	"$(INTDIR)\API.OBJ" \
	"$(INTDIR)\APIIF.OBJ" \
	"$(INTDIR)\V6_AUXU.OBJ" \
	"$(INTDIR)\BASECLS.OBJ" \
	"$(INTDIR)\bc_assign.obj" \
   	"$(INTDIR)\bc_cfunc.OBJ" \
	"$(INTDIR)\bc_eh.obj" \
	"$(INTDIR)\bc_inst.obj" \
	"$(INTDIR)\bc_reader.OBJ" \
	"$(INTDIR)\bc_vtbl.obj" \
	"$(INTDIR)\bc_autoobj.OBJ" \
	"$(INTDIR)\bc_debug.OBJ" \
	"$(INTDIR)\bc_exec.OBJ" \
	"$(INTDIR)\bc_parse.OBJ" \
	"$(INTDIR)\bc_type.obj" \
	"$(INTDIR)\CALLFUNC.OBJ" \
	"$(INTDIR)\V6_CAST.OBJ" \
	"$(INTDIR)\CLASS.OBJ" \
	"$(INTDIR)\DATAMBR.OBJ" \
	"$(INTDIR)\V6_DEBUG.OBJ" \
	"$(INTDIR)\V6_DECL.OBJ" \
	"$(INTDIR)\V6_DISP.OBJ" \
	"$(INTDIR)\V6_DUMP.OBJ" \
	"$(INTDIR)\V6_END.OBJ" \
	"$(INTDIR)\V6_ERROR.OBJ" \
	"$(INTDIR)\V6_EXPR.OBJ" \
	"$(INTDIR)\V6_FREAD.OBJ" \
	"$(INTDIR)\V6_FUNC.OBJ" \
	"$(INTDIR)\G__CFUNC.OBJ" \
	"$(INTDIR)\G__SETUP.OBJ" \
	"$(INTDIR)\V6_GCOLL.OBJ" \
	"$(INTDIR)\V6_GLOBAL1.OBJ" \
	"$(INTDIR)\V6_GLOBAL2.OBJ" \
	"$(INTDIR)\V6_IFUNC.OBJ" \
	"$(INTDIR)\V6_INHERIT.OBJ" \
	"$(INTDIR)\V6_INIT.OBJ" \
	"$(INTDIR)\V6_INPUT.OBJ" \
	"$(INTDIR)\V6_INTRPT.OBJ" \
	"$(INTDIR)\V6_LOADFILE.OBJ" \
	"$(INTDIR)\V6_MACRO.OBJ" \
	"$(INTDIR)\V6_MALLOC.OBJ" \
	"$(INTDIR)\V6_MEMTEST.OBJ" \
	"$(INTDIR)\METHOD.OBJ" \
	"$(INTDIR)\METHODAR.OBJ" \
	"$(INTDIR)\V6_NEW.OBJ" \
	"$(INTDIR)\V6_NEWLINK.OBJ" \
	"$(INTDIR)\V6_OLDLINK.OBJ" \
	"$(INTDIR)\V6_OPR.OBJ" \
	"$(INTDIR)\V6_PARSE.OBJ" \
	"$(INTDIR)\V6_PAUSE.OBJ" \
	"$(INTDIR)\V6_PCODE.OBJ" \
	"$(INTDIR)\V6_PRAGMA.OBJ" \
	"$(INTDIR)\V6_QUOTE.OBJ" \
	"$(INTDIR)\V6_SCRUPTO.OBJ" \
	"$(INTDIR)\V6_SHL.OBJ" \
	"$(INTDIR)\V6_SIZEOF.OBJ" \
	"$(INTDIR)\V6_STDSTRCT.OBJ" \
	"$(INTDIR)\V6_STRUCT.OBJ" \
	"$(INTDIR)\V6_STUB.OBJ" \
	"$(INTDIR)\V6_TMPLT.OBJ" \
	"$(INTDIR)\Token.obj" \
	"$(INTDIR)\TYPE.OBJ" \
	"$(INTDIR)\V6_TYPEDEF.OBJ" \
	"$(INTDIR)\TYPEDF.OBJ" \
	"$(INTDIR)\V6_VAL2A.OBJ" \
	"$(INTDIR)\V6_VALUE.OBJ" \
	"$(INTDIR)\V6_VAR.OBJ" \
	"$(INTDIR)\iccstrm.obj" \
	"$(INTDIR)\V6_WINNT.OBJ" \
	"$(INTDIR)\SHADOW.OBJ" \
	"$(INTDIR)\RFLX_GENDICT.OBJ" \
	"$(INTDIR)\RFLX_GENSRC.OBJ" \
	"$(INTDIR)\RFLX_TOOLS.OBJ"

"$(OUTDIR)\libcint.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("libcint.dep")
!INCLUDE "libcint.dep"
!ELSE 
!MESSAGE Warning: cannot find "libcint.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "libcint - Win32 Release" || "$(CFG)" == "libcint - Win32 Debug"
SOURCE=..\API.CXX

"$(INTDIR)\API.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\APIIF.CXX

"$(INTDIR)\APIIF.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_AUXU.CXX

"$(INTDIR)\V6_AUXU.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE=..\bc_assign.cxx

"$(INTDIR)\bc_assign.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\bc_cfunc.cxx

"$(INTDIR)\bc_cfunc.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\bc_eh.cxx

"$(INTDIR)\bc_eh.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\bc_inst.cxx

"$(INTDIR)\bc_inst.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\bc_reader.cxx

"$(INTDIR)\bc_reader.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\bc_vtbl.cxx

"$(INTDIR)\bc_vtbl.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\bc_autoobj.cxx

"$(INTDIR)\bc_autoobj.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\bc_debug.cxx

"$(INTDIR)\bc_debug.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\bc_exec.cxx

"$(INTDIR)\bc_exec.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\bc_parse.cxx

"$(INTDIR)\bc_parse.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\bc_type.cxx

"$(INTDIR)\bc_type.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



SOURCE=..\BASECLS.CXX

"$(INTDIR)\BASECLS.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\CALLFUNC.CXX

"$(INTDIR)\CALLFUNC.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_CAST.CXX

"$(INTDIR)\V6_CAST.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\CLASS.CXX

"$(INTDIR)\CLASS.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\DATAMBR.CXX

"$(INTDIR)\DATAMBR.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_DEBUG.CXX

"$(INTDIR)\V6_DEBUG.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_DECL.CXX

"$(INTDIR)\V6_DECL.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_DISP.CXX

"$(INTDIR)\V6_DISP.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_DUMP.CXX

"$(INTDIR)\V6_DUMP.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_END.CXX

"$(INTDIR)\V6_END.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_ERROR.CXX

"$(INTDIR)\V6_ERROR.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_EXPR.CXX

"$(INTDIR)\V6_EXPR.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_FREAD.CXX

"$(INTDIR)\V6_FREAD.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_FUNC.CXX

"$(INTDIR)\V6_FUNC.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\G__CFUNC.C

"$(INTDIR)\G__CFUNC.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPPO1_PROJ) $(SOURCE)


SOURCE=..\..\MAIN\G__SETUP.C

"$(INTDIR)\G__SETUP.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_GCOLL.CXX

"$(INTDIR)\V6_GCOLL.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_GLOBAL1.CXX

"$(INTDIR)\V6_GLOBAL1.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_GLOBAL2.CXX

"$(INTDIR)\V6_GLOBAL2.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_IFUNC.CXX

"$(INTDIR)\V6_IFUNC.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_INHERIT.CXX

"$(INTDIR)\V6_INHERIT.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_INIT.CXX

"$(INTDIR)\V6_INIT.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_INPUT.CXX

"$(INTDIR)\V6_INPUT.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_INTRPT.CXX

"$(INTDIR)\V6_INTRPT.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_LOADFILE.CXX

"$(INTDIR)\V6_LOADFILE.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_MACRO.CXX

"$(INTDIR)\V6_MACRO.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_MALLOC.CXX

"$(INTDIR)\V6_MALLOC.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_MEMTEST.CXX

"$(INTDIR)\V6_MEMTEST.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\METHOD.CXX

"$(INTDIR)\METHOD.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\METHODAR.CXX

"$(INTDIR)\METHODAR.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_NEW.CXX

"$(INTDIR)\V6_NEW.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_NEWLINK.CXX

"$(INTDIR)\V6_NEWLINK.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_OLDLINK.CXX

"$(INTDIR)\V6_OLDLINK.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_OPR.CXX

"$(INTDIR)\V6_OPR.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_PARSE.CXX

"$(INTDIR)\V6_PARSE.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_PAUSE.CXX

"$(INTDIR)\V6_PAUSE.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_PCODE.CXX

"$(INTDIR)\V6_PCODE.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_PRAGMA.CXX

"$(INTDIR)\V6_PRAGMA.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_QUOTE.CXX

"$(INTDIR)\V6_QUOTE.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_SCRUPTO.CXX

"$(INTDIR)\V6_SCRUPTO.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_SHL.CXX

"$(INTDIR)\V6_SHL.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_SIZEOF.CXX

"$(INTDIR)\V6_SIZEOF.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_STDSTRCT.CXX

"$(INTDIR)\V6_STDSTRCT.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_STRUCT.CXX

"$(INTDIR)\V6_STRUCT.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_STUB.CXX

"$(INTDIR)\V6_STUB.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_TMPLT.CXX

"$(INTDIR)\V6_TMPLT.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Token.cxx

"$(INTDIR)\Token.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\TYPE.CXX

"$(INTDIR)\TYPE.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_TYPEDEF.CXX

"$(INTDIR)\V6_TYPEDEF.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\TYPEDF.CXX

"$(INTDIR)\TYPEDF.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_VAL2A.CXX

"$(INTDIR)\V6_VAL2A.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_VALUE.CXX

"$(INTDIR)\V6_VALUE.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_VAR.CXX

"$(INTDIR)\V6_VAR.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\iccstrm.cxx

"$(INTDIR)\iccstrm.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\V6_WINNT.CXX

"$(INTDIR)\V6_WINNT.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\SHADOW.CXX

"$(INTDIR)\SHADOW.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\RFLX_GENDICT.CXX

"$(INTDIR)\RFLX_GENDICT.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\RFLX_GENSRC.CXX

"$(INTDIR)\RFLX_GENSRC.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\RFLX_TOOLS.CXX

"$(INTDIR)\RFLX_TOOLS.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

