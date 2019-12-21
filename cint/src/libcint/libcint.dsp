# Microsoft Developer Studio Project File - Name="libcint" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=libcint - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libcint.mak".
!MESSAGE 
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

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libcint - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /w /W0 /GX /O2 /I "..\.." /I ".." /I "..\..\lib\iccstrm" /I "..\..\lib\stdstrct" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "G__NEWSTDHEADER" /D "G__VISUAL" /D "G__WIN32" /D "G__SHAREDLIB" /D "G__REDIRECTIO" /D "G__P2FCAST" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib /nologo /subsystem:windows /dll /machine:I386

!ELSEIF  "$(CFG)" == "libcint - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\.." /I ".." /I "..\..\lib\iccstrm" /I "..\..\lib\stdstrct" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "G__NEWSTDHEADER" /D "G__VISUAL" /D "G__WIN32" /D "G__SHAREDLIB" /D "G__REDIRECTIO" /D "G__P2FCAST" /D "G__ASM_DBG" /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib /nologo /subsystem:windows /dll /debug /machine:I386

!ENDIF 

# Begin Target

# Name "libcint - Win32 Release"
# Name "libcint - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Source File

SOURCE=..\API.CXX
# End Source File
# Begin Source File

SOURCE=..\APIIF.CXX
# End Source File
# Begin Source File

SOURCE=..\V6_AUXU.CXX
# End Source File
# Begin Source File

SOURCE=..\BASECLS.CXX
# End Source File
# Begin Source File

SOURCE=..\BC_ASSIGN.CXX	
# End Source File
# Begin Source File

SOURCE=..\BC_CFUNC.CXX
# End Source File
# Begin Source File

SOURCE=..\BC_EH.CXX	
# End Source File
# Begin Source File

SOURCE=..\BC_INST.CXX	
# End Source File
# Begin Source File

SOURCE=..\BC_READER.CXX	
# End Source File
# Begin Source File

SOURCE=..\BC_VTBL.CXX
# End Source File
# Begin Source File

SOURCE=..\BC_AUTOOBJ.CXX	
# End Source File
# Begin Source File

SOURCE=..\BC_DEBUG.CXX	
# End Source File
# Begin Source File

SOURCE=..\BC_EXEC.CXX	
# End Source File
# Begin Source File

SOURCE=..\BC_PARSE.CXX	
# End Source File
# Begin Source File

SOURCE=..\BC_TYPE.CXX
# End Source File
# Begin Source File

SOURCE=..\CALLFUNC.CXX
# End Source File
# Begin Source File

SOURCE=..\V6_CAST.CXX
# End Source File
# Begin Source File

SOURCE=..\CLASS.CXX
# End Source File
# Begin Source File

SOURCE=..\DATAMBR.CXX
# End Source File
# Begin Source File

SOURCE=..\V6_DEBUG.CXX
# End Source File
# Begin Source File

SOURCE=..\V6_DECL.CXX
# End Source File
# Begin Source File

SOURCE=..\V6_DISP.CXX
# End Source File
# Begin Source File

SOURCE=..\V6_DUMP.CXX
# End Source File
# Begin Source File

SOURCE=..\V6_END.CXX
# End Source File
# Begin Source File

SOURCE=..\V6_ERROR.CXX
# End Source File
# Begin Source File

SOURCE=..\V6_EXPR.CXX
# End Source File
# Begin Source File

SOURCE=..\V6_FREAD.CXX
# End Source File
# Begin Source File

SOURCE=..\V6_FUNC.CXX
# End Source File
# Begin Source File

SOURCE=..\G__CFUNC.CXX
# End Source File
# Begin Source File

SOURCE=..\..\MAIN\G__SETUP.C
# End Source File
# Begin Source File

SOURCE=..\V6_GCOLL.CXX
# End Source File
# Begin Source File

SOURCE=..\V6_GLOBAL1.CXX
# End Source File
# Begin Source File

SOURCE=..\V6_GLOBAL2.CXX
# End Source File
# Begin Source File

SOURCE=..\V6_IFUNC.CXX
# End Source File
# Begin Source File

SOURCE=..\V6_INHERIT.CXX
# End Source File
# Begin Source File

SOURCE=..\V6_INIT.CXX
# End Source File
# Begin Source File

SOURCE=..\V6_INPUT.CXX
# End Source File
# Begin Source File

SOURCE=..\V6_INTRPT.CXX
# End Source File
# Begin Source File

SOURCE=.\libcint.def
# End Source File
# Begin Source File

SOURCE=..\V6_LOADFILE.CXX
# End Source File
# Begin Source File

SOURCE=..\V6_MACRO.CXX
# End Source File
# Begin Source File

SOURCE=..\V6_MALLOC.CXX
# End Source File
# Begin Source File

SOURCE=..\V6_MEMTEST.CXX
# End Source File
# Begin Source File

SOURCE=..\METHOD.CXX
# End Source File
# Begin Source File

SOURCE=..\METHODAR.CXX
# End Source File
# Begin Source File

SOURCE=..\V6_NEW.CXX
# End Source File
# Begin Source File

SOURCE=..\V6_NEWLINK.CXX
# End Source File
# Begin Source File

SOURCE=..\V6_OLDLINK.CXX
# End Source File
# Begin Source File

SOURCE=..\V6_OPR.CXX
# End Source File
# Begin Source File

SOURCE=..\V6_PARSE.CXX
# End Source File
# Begin Source File

SOURCE=..\V6_PAUSE.CXX
# End Source File
# Begin Source File

SOURCE=..\V6_PCODE.CXX
# End Source File
# Begin Source File

SOURCE=..\V6_PRAGMA.CXX
# End Source File
# Begin Source File

SOURCE=..\V6_QUOTE.CXX
# End Source File
# Begin Source File

SOURCE=..\V6_SCRUPTO.CXX
# End Source File
# Begin Source File

SOURCE=..\V6_SHL.CXX
# End Source File
# Begin Source File

SOURCE=..\V6_SIZEOF.CXX
# End Source File
# Begin Source File

SOURCE=..\V6_STDSTRCT.CXX
# End Source File
# Begin Source File

SOURCE=..\V6_STRUCT.CXX
# End Source File
# Begin Source File

SOURCE=..\V6_STUB.CXX
# End Source File
# Begin Source File

SOURCE=..\V6_TMPLT.CXX
# End Source File
# Begin Source File

SOURCE=..\Token.cxx
# End Source File
# Begin Source File

SOURCE=..\TYPE.CXX
# End Source File
# Begin Source File

SOURCE=..\V6_TYPEDEF.CXX
# End Source File
# Begin Source File

SOURCE=..\TYPEDF.CXX
# End Source File
# Begin Source File

SOURCE=..\V6_VAL2A.CXX
# End Source File
# Begin Source File

SOURCE=..\V6_VALUE.CXX
# End Source File
# Begin Source File

SOURCE=..\V6_VAR.CXX
# End Source File
# Begin Source File

SOURCE=..\iccstrm.cxx
# End Source File
# Begin Source File

SOURCE=..\V6_WINNT.CXX
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=..\Api.h
# End Source File
# Begin Source File

SOURCE=..\Apiif.h
# End Source File
# Begin Source File

SOURCE=..\BaseCls.h
# End Source File
# Begin Source File

SOURCE=..\bc_assign.h	
# End Source File
# Begin Source File

SOURCE=..\bc_cfunc.h	
# End Source File
# Begin Source File

SOURCE=..\bc_eh.h		
# End Source File
# Begin Source File

SOURCE=..\bc_exec_asm.h	
# End Source File
# Begin Source File

SOURCE=..\bc_linkdef.h	
# End Source File
# Begin Source File

SOURCE=..\bc_reader.h	
# End Source File
# Begin Source File

SOURCE=..\bc_vtbl.h
# End Source File
# Begin Source File

SOURCE=..\bc_autoobj.h	
# End Source File
# Begin Source File

SOURCE=..\bc_debug.h	
# End Source File
# Begin Source File

SOURCE=..\bc_exec.h	
# End Source File
# Begin Source File

SOURCE=..\bc_inst.h	
# End Source File
# Begin Source File

SOURCE=..\bc_parse.h	
# End Source File
# Begin Source File

SOURCE=..\bc_type.h
# End Source File
# Begin Source File

SOURCE=..\CallFunc.h
# End Source File
# Begin Source File

SOURCE=..\Class.h
# End Source File
# Begin Source File

SOURCE=..\DataMbr.h
# End Source File
# Begin Source File

SOURCE=..\memtest.h
# End Source File
# Begin Source File

SOURCE=..\Method.h
# End Source File
# Begin Source File

SOURCE=..\MethodAr.h
# End Source File
# Begin Source File

SOURCE=..\stdstrct.h
# End Source File
# Begin Source File

SOURCE=..\Token.h
# End Source File
# Begin Source File

SOURCE=..\Type.h
# End Source File
# Begin Source File

SOURCE=..\Typedf.h
# End Source File
# Begin Source File

SOURCE=..\vcstrm.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
