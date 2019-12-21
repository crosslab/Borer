############################################################
# platform/msdos/Makefile
#  Platform dependent information for MS-DOS DJGPP
############################################################

# Tools
RM          = rm -f
CP          = cp
AR          = ar
AROPT       = clq
KRCC        = gcc -traditional -I$(DJGPPDIR)/include
CC          = gcc -I$(DJGPPDIR)/include
CPP         = gxx -I$(DJGPPDIR)/include
LD          = gxx -I$(DJGPPDIR)/include
CPREP       = gcc -E -I$(DJGPPDIR)/include
CPPPREP     = gxx -E -I$(DJGPPDIR)/include

# Compiler and linker option
CCDLLOPT    =
LDDLLOPT    =
OPTIMIZE    = -O
LDOPT       = -L$(DJGPPDIR)/lib -lm
SYSMACRO    =
OTHMACRO    = -DG__DJGPP
SYSIPATH    = 

# libraries
MAINO       = $(CINTSYSDIR)/main/cppmain.o
CINTLIB     = $(CINTSYSDIR)/src/G__ci.a
READLINEA   =
APIO        = Api.o Class.o BaseCls.o Type.o DataMbr.o Method.o MethodAr.o CallFunc.o Typedf.o Apiif.o Token.o
RANLIB      = ranlib
STDLIBS     = v6_dmystrm.o v6_stdstrct.o
PLATFORM    =

# source code postfix
CSRCPOST    = .c
CHDRPOST    = .h
CPPSRCPOST  = .cxx
CPPHDRPOST  = .h
OBJPOST     = .o
DLLPOST     =



##############################################################
# $CINTSYSDIR/src/Makefile.base
#
# Description:
#   This file is a base of cint library makefile. There are examples
#  of platform dependent setup information under platform
#  directory. Do following to create a complete Makefile,
#
#  $ cat ../platform/[YourPlatform] Makefile.base > Makefile
#
##############################################################

CINTSYSDIR   = ..
IPATH    = -I.. $(SYSIPATH) 
MACRO    = $(SYSMACRO) $(OTHMACRO)

############################################################################
# common variable definition
############################################################################

SECURITYH =     security.h
DLLREVH =       dllrev.h

HEADERS =       common.h global.h fproto.h memtest.h sunos.h ../G__ci.h

OBJECTS =       $(PLATFORM) \
                $(STDLIBS) \
                $(APIO) \
                v6_auxu.o \
                v6_cast.o \
                v6_debug.o \
                v6_decl.o \
                v6_disp.o \
                v6_dump.o \
                v6_end.o \
                v6_error.o \
                v6_expr.o \
                v6_fread.o \
                v6_func.o \
                v6_gcoll.o \
                v6_global1.o \
                v6_global2.o \
                g__cfunc.o \
                v6_ifunc.o \
                v6_inherit.o \
                v6_init.o \
                v6_input.o \
                v6_intrpt.o \
                v6_loadfile.o \
                v6_macro.o \
                v6_malloc.o \
                v6_memtest.o \
                v6_new.o \
                v6_newlink.o \
                v6_oldlink.o \
                v6_opr.o \
                v6_parse.o \
                v6_pause.o \
                v6_pcode.o \
                v6_pragma.o \
                v6_quote.o \
                v6_scrupto.o \
                v6_shl.o \
                v6_sizeof.o \
                v6_struct.o \
                v6_stub.o \
                v6_tmplt.o \
                v6_typedef.o \
                v6_val2a.o \
                v6_value.o \
                v6_var.o

CINTEXE  = $(CINTSYSDIR)/cint.exe
MAKECINTEXE  = $(CINTSYSDIR)/makecint.exe


done : $(CINTEXE) $(MAKECINTEXE)
	echo > done

$(MAKECINTEXE) : ../tool/makecint.c
	$(CC) $(IPATH) $(MACRO) $(OPTIMIZE) -c ../tool/makecint.c -o ../tool/makecint.o
	$(LD) -o $(MAKECINTEXE) ../tool/makecint.o $(LDOPT)

$(CINTEXE) : $(CINTLIB) ../main/cppmain.cxx ../main/g__setup.c
	$(CC) $(IPATH) $(MACRO) $(OPTIMIZE) -c ../main/g__setup.c
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c ../main/cppmain.cxx -o ../main/cppmain.o
	$(LD) -o $(CINTEXE) ../main/cppmain.o g__setup.o $(CINTLIB) $(OPTIMIZE) $(LDOPT)

$(CINTLIB) : $(OBJECTS)
	$(RM) $@
	$(AR) $(AROPT) $@ $(OBJECTS)
	$(RANLIB) $(CINTLIB)

############################################################################
# iostream library
############################################################################
libstrm.o : libstrm.cxx libstrm.h $(HEADERS)
	$(CPP) -I../lib/stream $(IPATH) $(MACRO) $(OPTIMIZE) -c libstrm.cxx

v6_dmystrm.o : v6_dmystrm.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_dmystrm.cxx

# Visual C++
vcstrm.o : vcstrm.cxx vcstrm.h $(HEADERS)
	$(CPP) -I../lib/vcstream $(IPATH) $(MACRO) $(OPTIMIZE) -c vcstrm.cxx

# Borland C++
bcstrm.o : bcstrm.cxx bcstrm.h $(HEADERS)
	$(CPP) -I../lib/bcstream $(IPATH) $(MACRO) $(OPTIMIZE) -c bcstrm.cxx

############################################################################
# SunOS 4.1 specific source
############################################################################
v6_sunos.o : v6_sunos.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -DNONANSI -c v6_sunos.cxx

############################################################################
# NewsOS specific source
############################################################################
v6_new.os.o : v6_new.os.c $(HEADERS)
	$(CC) $(IPATH) $(MACRO) $(OPTIMIZE) -DNONANSI -c v6_new.os.c

############################################################################
# Windows-NT specific source
############################################################################
v6_winnt.o : v6_winnt.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_winnt.cxx

############################################################################
# v6_input.cxx depends on GNU readline library
############################################################################
v6_input.o : v6_input.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_input.cxx

############################################################################
# lconv, div_t, ldiv_t, tm struct
############################################################################
v6_stdstrct.o : v6_stdstrct.cxx stdstrct.h $(HEADERS)
	$(CPP) -I../lib/stdstrct $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_stdstrct.cxx

v6_dmystrct.o : v6_dmystrct.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_dmystrct.cxx

############################################################################
# Common sources
############################################################################
v6_auxu.o : v6_auxu.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_auxu.cxx

v6_cast.o : v6_cast.cxx $(HEADERS) $(SECURITYH)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_cast.cxx

v6_debug.o : v6_debug.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_debug.cxx

v6_decl.o : v6_decl.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_decl.cxx

v6_disp.o : v6_disp.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_disp.cxx

v6_dump.o : v6_dump.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_dump.cxx

v6_end.o : v6_end.cxx $(HEADERS) $(SECURITYH)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_end.cxx

v6_error.o : v6_error.cxx $(HEADERS) $(SECURITYH)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_error.cxx

v6_expr.o : v6_expr.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_expr.cxx

v6_fread.o : v6_fread.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_fread.cxx

v6_func.o : v6_func.cxx $(HEADERS) $(SECURITYH)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_func.cxx

v6_gcoll.o : v6_gcoll.cxx $(HEADERS) $(SECURITYH)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_gcoll.cxx

v6_global1.o : v6_global1.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_global1.cxx

v6_global2.o : v6_global2.cxx $(HEADERS) $(SECURITYH)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_global2.cxx

g__cfunc.o : g__cfunc.c $(HEADERS) $(SECURITYH)
	$(CC) $(IPATH) $(MACRO) $(OPTIMIZE) -c g__cfunc.c

v6_ifunc.o : v6_ifunc.cxx $(HEADERS) $(SECURITYH)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_ifunc.cxx

v6_inherit.o : v6_inherit.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_inherit.cxx

v6_init.o : v6_init.cxx $(HEADERS) $(SECURITYH)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_init.cxx

v6_intrpt.o : v6_intrpt.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_intrpt.cxx

v6_loadfile.o : v6_loadfile.cxx $(HEADERS) $(SECURITYH)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_loadfile.cxx

v6_macro.o : v6_macro.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_macro.cxx

v6_malloc.o : v6_malloc.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_malloc.cxx

v6_memtest.o : v6_memtest.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_memtest.cxx

v6_new.o : v6_new.cxx $(HEADERS) $(SECURITYH) $(SECURITYH)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_new.cxx

v6_newlink.o : v6_newlink.cxx $(HEADERS) $(DLLREVH)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_newlink.cxx

v6_oldlink.o : v6_oldlink.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_oldlink.cxx

v6_opr.o : v6_opr.cxx $(HEADERS) $(SECURITYH)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_opr.cxx

v6_parse.o : v6_parse.cxx $(HEADERS) $(SECURITYH)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_parse.cxx

v6_pause.o : v6_pause.cxx $(HEADERS) $(SECURITYH)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_pause.cxx

v6_pcode.o : v6_pcode.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_pcode.cxx

v6_pragma.o : v6_pragma.cxx $(HEADERS) $(SECURITYH)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_pragma.cxx

v6_quote.o : v6_quote.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_quote.cxx

v6_scrupto.o : v6_scrupto.cxx $(HEADERS) $(SECURITYH)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_scrupto.cxx

v6_sizeof.o : v6_sizeof.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_sizeof.cxx

v6_shl.o : v6_shl.cxx $(HEADERS) $(DLLREVH)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_shl.cxx

v6_struct.o : v6_struct.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_struct.cxx

v6_stub.o : v6_stub.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_stub.cxx

v6_tmplt.o : v6_tmplt.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_tmplt.cxx

v6_typedef.o : v6_typedef.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_typedef.cxx

v6_val2a.o : v6_val2a.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_val2a.cxx

v6_value.o : v6_value.cxx $(HEADERS)
	$(CPP) $(IPATH) $(MACRO) $(OPTIMIZE) -c v6_value.cxx

v6_var.o : v6_var.cxx $(HEADERS) $(SECURITYH)
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
          ../G__ci.h

Token.o : $(APIHEADER) Token.cxx
	$(CPP) $(IPATH) $(OPTIMIZE) $(MACRO) -c Token.cxx

Typedf.o : $(APIHEADER) Typedf.cxx
	$(CPP) $(IPATH) $(OPTIMIZE) $(MACRO) -c Typedf.cxx

Class.o : $(APIHEADER) Class.cxx
	$(CPP) $(IPATH) $(OPTIMIZE) $(MACRO) -c Class.cxx

BaseCls.o : $(APIHEADER) BaseCls.cxx
	$(CPP) $(IPATH) $(OPTIMIZE) $(MACRO) -c BaseCls.cxx

Type.o : $(APIHEADER) Type.cxx
	$(CPP) $(IPATH) $(OPTIMIZE) $(MACRO) -c Type.cxx

DataMbr.o : $(APIHEADER) DataMbr.cxx
	$(CPP) $(IPATH) $(OPTIMIZE) $(MACRO) -c DataMbr.cxx

Method.o : $(APIHEADER) Method.cxx
	$(CPP) $(IPATH) $(OPTIMIZE) $(MACRO) -c Method.cxx

MethodAr.o : $(APIHEADER) MethodAr.cxx
	$(CPP) $(IPATH) $(OPTIMIZE) $(MACRO) -c MethodAr.cxx

CallFunc.o : $(APIHEADER) CallFunc.cxx
	$(CPP) $(IPATH) $(OPTIMIZE) $(MACRO) -c CallFunc.cxx

Api.o : $(APIHEADER) Api.cxx
	$(CPP) $(IPATH) $(OPTIMIZE) $(MACRO) -c Api.cxx

Apiif.o : $(APIHEADER) Apiif.cxx
	$(CPP) $(IPATH) $(OPTIMIZE) $(MACRO) -c Apiif.cxx


############################################################################
# clean
############################################################################
clean :
	$(RM) $(OBJECTS) $(CINTLIB) core

