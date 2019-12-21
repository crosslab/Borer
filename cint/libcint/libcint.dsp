# Microsoft Developer Studio Project File - Name="libcint" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libcint - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libcint.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libcint.mak" CFG="libcint - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libcint - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libcint - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
RSC=rc.exe

!IF  "$(CFG)" == "libcint - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "../" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "libcint - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "../" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "libcint - Win32 Release"
# Name "libcint - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\Api.cxx
# End Source File
# Begin Source File

SOURCE=..\src\Apiif.cxx
# End Source File
# Begin Source File

SOURCE=..\src\BaseCls.cxx
# End Source File
# Begin Source File

SOURCE=..\src\bc_assign.cxx
# End Source File
# Begin Source File

SOURCE=..\src\bc_autoobj.cxx
# End Source File
# Begin Source File

SOURCE=..\src\bc_cfunc.cxx
# End Source File
# Begin Source File

SOURCE=..\src\bc_debug.cxx
# End Source File
# Begin Source File

SOURCE=..\src\bc_eh.cxx
# End Source File
# Begin Source File

SOURCE=..\src\bc_exec.cxx
# End Source File
# Begin Source File

SOURCE=..\src\bc_inst.cxx
# End Source File
# Begin Source File

SOURCE=..\src\bc_item.cxx
# End Source File
# Begin Source File

SOURCE=..\src\bc_parse.cxx
# End Source File
# Begin Source File

SOURCE=..\src\bc_reader.cxx
# End Source File
# Begin Source File

SOURCE=..\src\bc_type.cxx
# End Source File
# Begin Source File

SOURCE=..\src\bc_vtbl.cxx
# End Source File
# Begin Source File

SOURCE=..\src\CallFunc.cxx
# End Source File
# Begin Source File

SOURCE=..\src\Class.cxx
# End Source File
# Begin Source File

SOURCE=..\src\DataMbr.cxx
# End Source File
# Begin Source File

SOURCE=..\src\g__cfunc.c
# End Source File
# Begin Source File

SOURCE=..\main\G__setup.c
# End Source File
# Begin Source File

SOURCE=..\src\Method.cxx
# End Source File
# Begin Source File

SOURCE=..\src\MethodAr.cxx
# End Source File
# Begin Source File

SOURCE=..\src\Token.cxx
# End Source File
# Begin Source File

SOURCE=..\src\Type.cxx
# End Source File
# Begin Source File

SOURCE=..\src\Typedf.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_auxu.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_cast.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_debug.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_decl.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_disp.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_dmystrm.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_dump.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_end.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_error.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_expr.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_fread.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_func.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_gcoll.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_global1.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_global2.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_ifunc.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_inherit.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_init.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_input.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_intrpt.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_loadfile.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_macro.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_malloc.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_memtest.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_new.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_newlink.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_newsos.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_oldlink.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_opr.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_parse.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_pause.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_pcode.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_pragma.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_quote.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_scrupto.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_shl.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_sizeof.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_stdstrct.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_struct.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_stub.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_sunos.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_tmplt.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_typedef.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_val2a.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_value.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_var.cxx
# End Source File
# Begin Source File

SOURCE=..\src\v6_winnt.cxx
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\src\Api.h
# End Source File
# Begin Source File

SOURCE=..\src\Apiif.h
# End Source File
# Begin Source File

SOURCE=..\src\BaseCls.h
# End Source File
# Begin Source File

SOURCE=..\src\bc_assign.h
# End Source File
# Begin Source File

SOURCE=..\src\bc_autoobj.h
# End Source File
# Begin Source File

SOURCE=..\src\bc_cfunc.h
# End Source File
# Begin Source File

SOURCE=..\src\bc_debug.h
# End Source File
# Begin Source File

SOURCE=..\src\bc_eh.h
# End Source File
# Begin Source File

SOURCE=..\src\bc_exec.h
# End Source File
# Begin Source File

SOURCE=..\src\bc_exec_asm.h
# End Source File
# Begin Source File

SOURCE=..\src\bc_inst.h
# End Source File
# Begin Source File

SOURCE=..\src\bc_item.h
# End Source File
# Begin Source File

SOURCE=..\src\bc_linkdef.h
# End Source File
# Begin Source File

SOURCE=..\src\bc_parse.h
# End Source File
# Begin Source File

SOURCE=..\src\bc_reader.h
# End Source File
# Begin Source File

SOURCE=..\src\bc_type.h
# End Source File
# Begin Source File

SOURCE=..\src\bc_vtbl.h
# End Source File
# Begin Source File

SOURCE=..\src\CallFunc.h
# End Source File
# Begin Source File

SOURCE=..\src\Class.h
# End Source File
# Begin Source File

SOURCE=..\src\DataMbr.h
# End Source File
# Begin Source File

SOURCE=..\src\Method.h
# End Source File
# Begin Source File

SOURCE=..\src\MethodAr.h
# End Source File
# Begin Source File

SOURCE=..\src\Token.h
# End Source File
# Begin Source File

SOURCE=..\src\Type.h
# End Source File
# Begin Source File

SOURCE=..\src\Typedf.h
# End Source File
# End Group
# End Target
# End Project
