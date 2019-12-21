// stdafx.cpp : source file that includes just the standard includes
//	Borer.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

#pragma comment( lib, "Imm32.lib" )

#ifdef _DEBUG
#	pragma comment( lib, "cint/libcint/Debug/libcint.lib" )
#else
#	pragma comment( lib, "cint/libcint/Release/libcint.lib" )
#endif