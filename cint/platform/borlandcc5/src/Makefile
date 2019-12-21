CINTSYSDIR =  \cint
############################################################
# platform/borlandcc5
#  Platform dependent information for Borland C++ Compiler 5.5
############################################################

#BCCDIR      = c:\Borland\BCC55
#BCCINC      = -I$(BCCDIR)\Include
#BCCLIB      = -L$(BCCDIR)\Lib

# Tools
RM	    = del 
CP	    = copy
KRCC        = bcc32 $(BCCINC)
CC          = bcc32 $(BCCINC)
CPP         = bcc32 -P $(BCCINC)
LD          = bcc32 $(BCCINC) $(BCCLIB)
CPREP       = cpp32 -Sr -Sc $(BCCINC)
CPPPREP     = cpp32 -Sr -Sc $(BCCINC)

# Compiler and linker option
CCDLLOPT    = 
LDDLLOPT    = -WD
OPTIMIZE    = -O2
LDOPT       = 
SHLIB_OPT   = 
SYSMACRO    = -DG__BORLANDCC5 -DG__NEWSTDHEADER
OTHMACRO    = 
SYSIPATH    =

# libraries
MAINO	    = $(CINTSYSDIR)\main\G__cppmain.obj
CINTLIB     = $(CINTSYSDIR)/libcint.lib
READLINEA   = 
APIO	    = Api.obj Class.obj BaseCls.obj Type.obj DataMbr.obj Method.obj MethodAr.obj CallFunc.obj Typedf.obj Apiif.obj Token.obj
RANLIB	    = 
STDLIBS     = cbstrm.obj v6_stdstrct.obj
PLATFORM    = v6_winnt.obj

# source code postfix
CSRCPOST    = .c
CHDRPOST    = .h
CPPSRCPOST  = .cpp
CPPHDRPOST  = .h
OBJPOST     = .obj
DLLPOST     = .dll










##############################################################
# $CINTSYSDIR\src\Makefile.base
#
# Author                 Masaharu Goto 
# Copyright(c) 1995~2001 Masaharu Goto (MXJ02154@niftyserve.objr.jp)
#
# Description:
#   This file is a base of cint library makefile. There are examples
#  of platform dependent setup information under platform
#  directory. Do following to create a complete Makefile,
#
#  $ cat ..\platform\[YourPlatform] Makefile.base > Makefile
#
##############################################################

#CINTSYSDIR   = ..
IPATH    = -I.. $(SYSIPATH)
MACRO    = $(SYSMACRO) $(OTHMACRO) 

############################################################################
# common variable definition 
############################################################################

SECURITYH =     security.h
DLLREVH =       dllrev.h

HEADERS =       common.h global.h fproto.h memtest.h sunos.h ..\G__ci.h 

OBJECTS = 	$(PLATFORM) \
		$(STDLIBS) \
		$(APIO) \
		v6_auxu.obj \
		v6_cast.obj \
		v6_debug.obj \
		v6_decl.obj \
		v6_disp.obj \
		v6_dump.obj \
		v6_end.obj \
		v6_error.obj \
		v6_expr.obj \
		v6_fread.obj \
		v6_func.obj \
		v6_gcoll.obj \
		v6_global1.obj \
		v6_global2.obj \
		g__cfunc.obj \
		v6_ifunc.obj \
		v6_inherit.obj \
		v6_init.obj \
		v6_input.obj \
		v6_intrpt.obj \
		v6_loadfile.obj \
		v6_macro.obj \
		v6_malloc.obj \
		v6_memtest.obj \
		v6_new.obj \
		v6_newlink.obj \
		v6_oldlink.obj \
		v6_opr.obj \
		v6_parse.obj \
		v6_pause.obj \
		v6_pcode.obj \
		v6_pragma.obj \
		v6_quote.obj \
		v6_scrupto.obj \
		v6_shl.obj \
		v6_sizeof.obj \
		v6_struct.obj \
		v6_stub.obj \
		v6_tmplt.obj \
		v6_typedef.obj \
		v6_val2a.obj \
		v6_value.obj \
		v6_var.obj

# Cint core as static library
#$(CINTSYSDIR)\src\G__ci.a : $(OBJECTS)
#	if test -r $(CINTLIB); then rm $(CINTLIB);fi
#	$(AR) $(AROPT) $@ $(OBJECTS);
#	-if [ -f "$(RANLIB)" ]; then $(RANLIB) $(CINTLIB); fi

# Cint core as shared library on Linux
#$(CINTSYSDIR)\libcint.so : $(OBJECTS)
#	$(LD) $(LDDLLOPT) $(SHLIB_OPT) -o $@ $(OBJECTS)

# Cint core as shared library on Windows
$(CINTSYSDIR)\libcint.dll : $(OBJECTS) $(CINTSYSDIR)\main\G__setup.obj
	$(LD) $(LDDLLOPT) $(SHLIB_OPT) -e$@ $(OBJECTS) ..\main\G__setup.obj
	implib -c $(CINTSYSDIR)\libcint.lib $(CINTSYSDIR)\libcint.dll

#	ldlibcint.bat

# Cint core as shared library on HP-UX
#$(CINTSYSDIR)\libcint.sl : $(OBJECTS)
#	$(LD) $(LDDLLOPT) $(SHLIB_OPT) -o $@ $(OBJECTS)

############################################################################
# iostream library
############################################################################
# Common for many old C++ compilers
libstrm.obj : libstrm.cxx libstrm.h $(HEADERS) ..\lib\stream\iostrm.h
	$(CPP) -I..\lib\stream $(IPATH) $(MACRO) $(OPTIMIZE) -c libstrm.cxx

# Microsoft Visual C++ compiler
vcstrm.obj : vcstrm.cxx vcstrm.h $(HEADERS) ..\lib\vcstream\iostrm.h
	$(CPP) -I..\lib\vcstream $(IPATH) $(MACRO) $(OPTIMIZE) -c vcstrm.cxx

# Borland C++ compiler
bcstrm.obj : bcstrm.cxx bcstrm.h $(HEADERS) ..\lib\bcstream\iostrm.h
	$(CPP) -I..\lib\bcstream $(IPATH) $(MACRO) $(OPTIMIZE) -c bcstrm.cxx

# Borland C++ Builder
cbstrm.obj : cbstrm.cpp cbstrm.h $(HEADERS) 
	$(CPP) -I..\\lib\\cbstream $(IPATH) $(MACRO) $(OPTIMIZE) -c cbstrm.cpp

# KAI C++ compiler
kccstrm.obj : kccstrm.cxx kccstrm.h $(HEADERS)
	$(CPP) -I..\lib\kccstream $(IPATH) $(MACRO) $(OPTIMIZE) -c kccstrm.cxx

# Sun CC5 compiler
sunstrm.obj : sunstrm.cxx sunstrm.h $(HEADERS) ..\lib\snstream\iostrm.h
	$(CPP) -I..\lib\snstream $(IPATH) $(MACRO) $(OPTIMIZE) -c sunstrm.cxx

sun5strm.obj : sun5strm.cxx sunstrm.h $(HEADERS) ..\lib\snstream\iostrm.h
	$(CPP) -I..\lib\snstream $(IPATH) $(MACRO) $(OPTIMIZE) -c sun5strm.cxx

# GNU C++ compiler ver 3.xx
gcc3strm.obj : gcc3strm.cxx gcc3strm.h $(HEADERS) ..\lib\gcc3strm\iostrm.h
	$(CPP) -I..\lib\gcc3strm $(IPATH) $(MACRO) $(OPTIMIZE) -c gcc3strm.cxx

# Intel C++ compiler
iccstrm.obj : iccstrm.cxx iccstrm.h $(HEADERS) ..\lib\gcc3strm\iostrm.h
	$(CPP) -I..\lib\iccstrm $(IPATH) $(MACRO) $(OPTIMIZE) -c iccstrm.cxx

# Use interpreted iostream
fakestrm.obj : fakestrm.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c fakestrm.cxx

# C compiler only
v6_dmystrm.obj : v6_dmystrm.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_dmystrm.cxx

############################################################################
# SunOS 4.1 specific source
############################################################################
v6_sunos.obj : v6_sunos.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -DNONANSI -c v6_sunos.cxx

############################################################################
# NewsOS specific source
############################################################################
v6_new.os.obj : v6_new.os.c $(HEADERS)
	$(CC) $(IPATH) $(MACRO) $(OPTIMIZE) -DNONANSI -c v6_new.os.c

############################################################################
# Windows-NT specific source
############################################################################
v6_winnt.obj : v6_winnt.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_winnt.cxx

############################################################################
# v6_input.cxx depends on GNU readline library
############################################################################
v6_input.obj : v6_input.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_input.cxx

############################################################################
# lconv, div_t, ldiv_t, tm struct
############################################################################
v6_stdstrct.obj : v6_stdstrct.cxx stdstrct.h $(HEADERS)
	$(CPP) -I..\\lib\\stdstrct $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_stdstrct.cxx

v6_dmystrct.obj : v6_dmystrct.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_dmystrct.cxx

############################################################################
# To install cint core as shared library
############################################################################
$(CINTSYSDIR)\main\G__setup.obj : $(CINTSYSDIR)\main\G__setup.c
	cd $(CINTSYSDIR)\main
	$(CC) $(IPATH) $(MACRO) $(OPTIMIZE) -c G__setup.c
	cd $(CINTSYSDIR)\src

############################################################################
# Common sources
############################################################################
v6_auxu.obj : v6_auxu.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_auxu.cxx

v6_cast.obj : v6_cast.cxx $(HEADERS) $(SECURITYH)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_cast.cxx

v6_debug.obj : v6_debug.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_debug.cxx

v6_decl.obj : v6_decl.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_decl.cxx

v6_disp.obj : v6_disp.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_disp.cxx

v6_dmyinit.obj : v6_dmyinit.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_dmyinit.cxx

v6_dump.obj : v6_dump.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_dump.cxx

v6_end.obj : v6_end.cxx $(HEADERS) $(SECURITYH)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_end.cxx

v6_error.obj : v6_error.cxx $(HEADERS) $(SECURITYH)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_error.cxx

v6_expr.obj : v6_expr.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_expr.cxx

v6_fread.obj : v6_fread.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_fread.cxx

v6_func.obj : v6_func.cxx $(HEADERS) $(SECURITYH)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_func.cxx

v6_gcoll.obj : v6_gcoll.cxx $(HEADERS) $(SECURITYH)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_gcoll.cxx

v6_global1.obj : v6_global1.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_global1.cxx

v6_global2.obj : v6_global2.cxx $(HEADERS) $(SECURITYH)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_global2.cxx

g__cfunc.obj : g__cfunc.c $(HEADERS) $(SECURITYH)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c g__cfunc.c

v6_ifunc.obj : v6_ifunc.cxx $(HEADERS) $(SECURITYH)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_ifunc.cxx

v6_inherit.obj : v6_inherit.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_inherit.cxx

v6_init.obj : v6_init.cxx $(HEADERS) $(SECURITYH)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_init.cxx

v6_intrpt.obj : v6_intrpt.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_intrpt.cxx

v6_loadfile.obj : v6_loadfile.cxx $(HEADERS) $(SECURITYH)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_loadfile.cxx

v6_macro.obj : v6_macro.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_macro.cxx

v6_malloc.obj : v6_malloc.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_malloc.cxx

v6_memtest.obj : v6_memtest.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_memtest.cxx

v6_new.obj : v6_new.cxx $(HEADERS) $(SECURITYH) $(SECURITYH)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_new.cxx

v6_newlink.obj : v6_newlink.cxx $(HEADERS) $(DLLREVH)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_newlink.cxx

v6_oldlink.obj : v6_oldlink.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_oldlink.cxx

v6_opr.obj : v6_opr.cxx $(HEADERS) $(SECURITYH)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_opr.cxx

v6_parse.obj : v6_parse.cxx $(HEADERS) $(SECURITYH)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_parse.cxx

v6_pause.obj : v6_pause.cxx $(HEADERS) $(SECURITYH)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_pause.cxx

v6_pcode.obj : v6_pcode.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_pcode.cxx

v6_pragma.obj : v6_pragma.cxx $(HEADERS) $(SECURITYH)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_pragma.cxx

v6_quote.obj : v6_quote.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_quote.cxx

v6_scrupto.obj : v6_scrupto.cxx $(HEADERS) $(SECURITYH)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_scrupto.cxx

v6_sizeof.obj : v6_sizeof.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_sizeof.cxx

v6_shl.obj : v6_shl.cxx $(HEADERS) $(DLLREVH)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_shl.cxx

v6_struct.obj : v6_struct.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_struct.cxx

v6_stub.obj : v6_stub.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_stub.cxx

v6_tmplt.obj : v6_tmplt.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_tmplt.cxx

v6_typedef.obj : v6_typedef.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_typedef.cxx

v6_val2a.obj : v6_val2a.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_val2a.cxx

v6_value.obj : v6_value.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_value.cxx

v6_var.obj : v6_var.cxx $(HEADERS) $(SECURITYH)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_var.cxx

############################################################################
# ERTTI API
############################################################################

APIHEADER = Api.h \
	  Class.h \
	  BaseCls.h \
	  Type.h \
	  DataMbr.h \
	  Method.h \
	  MethodAr.h \
	  CallFunc.h \
	  Typedf.h \
	  Apiif.h \
          Token.h \
	  ..\G__ci.h

Token.obj : $(APIHEADER) Token.cxx
	$(CPP) $(IPATH) $(OPTIMIZE) $(MACRO) -c Token.cxx

Typedf.obj : $(APIHEADER) Typedf.cxx
	$(CPP) $(IPATH) $(OPTIMIZE) $(MACRO) -c Typedf.cxx

Class.obj : $(APIHEADER) Class.cxx
	$(CPP) $(IPATH) $(OPTIMIZE) $(MACRO) -c Class.cxx

BaseCls.obj : $(APIHEADER) BaseCls.cxx
	$(CPP) $(IPATH) $(OPTIMIZE) $(MACRO) -c BaseCls.cxx

Type.obj : $(APIHEADER) Type.cxx
	$(CPP) $(IPATH) $(OPTIMIZE) $(MACRO) -c Type.cxx

DataMbr.obj : $(APIHEADER) DataMbr.cxx
	$(CPP) $(IPATH) $(OPTIMIZE) $(MACRO) -c DataMbr.cxx

Method.obj : $(APIHEADER) Method.cxx
	$(CPP) $(IPATH) $(OPTIMIZE) $(MACRO) -c Method.cxx

MethodAr.obj : $(APIHEADER) MethodAr.cxx
	$(CPP) $(IPATH) $(OPTIMIZE) $(MACRO) -c MethodAr.cxx

CallFunc.obj : $(APIHEADER) CallFunc.cxx
	$(CPP) $(IPATH) $(OPTIMIZE) $(MACRO) -c CallFunc.cxx

Api.obj : $(APIHEADER) Api.cxx
	$(CPP) $(IPATH) $(OPTIMIZE) $(MACRO) -c Api.cxx

Apiif.obj : $(APIHEADER) Apiif.cxx
	$(CPP) $(IPATH) $(OPTIMIZE) $(MACRO) -c Apiif.cxx


############################################################################
# clean
############################################################################
clean :
	$(RM) *.obj
	$(RM) *.dll
	$(RM) ..\libcint.*
	$(RM) ..\main\*.obj

