# Microsoft Developer Studio Project File - Name="Borer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Borer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Borer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Borer.mak" CFG="Borer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Borer - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Borer - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/‘¥¬Î/ºØ≥…≤‚ ‘_program/ITest", XHDAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Borer - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 CsiLibRelease.lib /nologo /subsystem:windows /machine:I386 /out:"Release/pdkem.exe"

!ELSEIF  "$(CFG)" == "Borer - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 CsiLib.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Borer - Win32 Release"
# Name "Borer - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Edit"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CCrystalEditView.cpp
# End Source File
# Begin Source File

SOURCE=.\CCrystalTextBuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\CCrystalTextView.cpp
# End Source File
# Begin Source File

SOURCE=.\CCrystalTextView2.cpp
# End Source File
# Begin Source File

SOURCE=.\CEditReplaceDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CFindTextDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CJFlatButton.cpp
# End Source File
# Begin Source File

SOURCE=.\CJFlatHeaderCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\CJListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\CJMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\cplusplus.cpp
# End Source File
# Begin Source File

SOURCE=.\scbarcf.cpp
# End Source File
# Begin Source File

SOURCE=.\scbarg.cpp
# End Source File
# Begin Source File

SOURCE=.\ShellContextMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\ShellPidl.cpp
# End Source File
# Begin Source File

SOURCE=.\ShellString.cpp
# End Source File
# Begin Source File

SOURCE=.\ShellTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\sizecbar.cpp
# End Source File
# Begin Source File

SOURCE=.\XTFlatTabCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\XTMemDC.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\BinRes.cpp
# End Source File
# Begin Source File

SOURCE=.\Borer.cpp
# End Source File
# Begin Source File

SOURCE=.\Borer.rc
# End Source File
# Begin Source File

SOURCE=.\BorerDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\BorerView.cpp
# End Source File
# Begin Source File

SOURCE=.\ButtonGrp.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\color.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ComboItem.cpp
# End Source File
# Begin Source File

SOURCE=.\CommInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\CommList.cpp
# End Source File
# Begin Source File

SOURCE=.\CommonRtn.cpp
# End Source File
# Begin Source File

SOURCE=.\crc.cpp
# End Source File
# Begin Source File

SOURCE=.\CrystalProtocol.cpp
# End Source File
# Begin Source File

SOURCE=.\DblScrollBar.cpp
# End Source File
# Begin Source File

SOURCE=.\Delaytime.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAliasEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRegister.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTimeSleep.cpp
# End Source File
# Begin Source File

SOURCE=.\EditCell.cpp
# End Source File
# Begin Source File

SOURCE=.\EditList.cpp
# End Source File
# Begin Source File

SOURCE=.\EditTree.cpp
# End Source File
# Begin Source File

SOURCE=.\Em_Common.cpp
# End Source File
# Begin Source File

SOURCE=.\FutileData.cpp
# End Source File
# Begin Source File

SOURCE=.\GoLine.cpp
# End Source File
# Begin Source File

SOURCE=.\GrfData.cpp
# End Source File
# Begin Source File

SOURCE=.\HeadFilePath.cpp
# End Source File
# Begin Source File

SOURCE=.\HexEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\HookStdio.cpp
# End Source File
# Begin Source File

SOURCE=.\itword9.cpp
# End Source File
# Begin Source File

SOURCE=.\ListHeader.cpp
# End Source File
# Begin Source File

SOURCE=.\Lock.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Memmap.cpp
# End Source File
# Begin Source File

SOURCE=.\MessageBox.cpp
# End Source File
# Begin Source File

SOURCE=.\MoveBtn.cpp
# End Source File
# Begin Source File

SOURCE=.\MpRtns.cpp
# End Source File
# Begin Source File

SOURCE=.\MyListBox.cpp
# End Source File
# Begin Source File

SOURCE=.\ParserRtn.cpp
# End Source File
# Begin Source File

SOURCE=.\PortTab.cpp
# End Source File
# Begin Source File

SOURCE=.\ProjectTree.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertyList.cpp
# End Source File
# Begin Source File

SOURCE=.\RichTips.cpp
# End Source File
# Begin Source File

SOURCE=.\RobinBuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\Serialport.cpp
# End Source File
# Begin Source File

SOURCE=.\STabCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TaskDefinition.cpp
# End Source File
# Begin Source File

SOURCE=.\TestTask.cpp
# End Source File
# Begin Source File

SOURCE=.\TokenMap.cpp
# End Source File
# Begin Source File

SOURCE=.\TraceInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeType.cpp
# End Source File
# Begin Source File

SOURCE=.\VbhExpression.cpp
# End Source File
# Begin Source File

SOURCE=.\WaitingTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\WjcDes.cpp
# End Source File
# Begin Source File

SOURCE=.\WordDrive.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BinRes.h
# End Source File
# Begin Source File

SOURCE=.\Borer.h
# End Source File
# Begin Source File

SOURCE=.\BorerDoc.h
# End Source File
# Begin Source File

SOURCE=.\BorerView.h
# End Source File
# Begin Source File

SOURCE=.\ButtonGrp.h
# End Source File
# Begin Source File

SOURCE=.\CCrystalEditView.h
# End Source File
# Begin Source File

SOURCE=.\CCrystalTextBuffer.h
# End Source File
# Begin Source File

SOURCE=.\CCrystalTextView.h
# End Source File
# Begin Source File

SOURCE=.\CEditReplaceDlg.h
# End Source File
# Begin Source File

SOURCE=.\CFindTextDlg.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\CJFlatButton.h
# End Source File
# Begin Source File

SOURCE=.\CJFlatHeaderCtrl.h
# End Source File
# Begin Source File

SOURCE=.\CJListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\CJMenu.h
# End Source File
# Begin Source File

SOURCE=.\color.h
# End Source File
# Begin Source File

SOURCE=.\ColorListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ComboItem.h
# End Source File
# Begin Source File

SOURCE=.\CommInfo.h
# End Source File
# Begin Source File

SOURCE=.\CommList.h
# End Source File
# Begin Source File

SOURCE=.\CommonDef.h
# End Source File
# Begin Source File

SOURCE=.\crc.h
# End Source File
# Begin Source File

SOURCE=.\CrystalProtocol.h
# End Source File
# Begin Source File

SOURCE=.\DblScrollBar.h
# End Source File
# Begin Source File

SOURCE=.\Delaytime.h
# End Source File
# Begin Source File

SOURCE=.\DlgAliasEdit.h
# End Source File
# Begin Source File

SOURCE=.\DlgRegister.h
# End Source File
# Begin Source File

SOURCE=.\EditCell.h
# End Source File
# Begin Source File

SOURCE=.\editcmd.h
# End Source File
# Begin Source File

SOURCE=.\EditList.h
# End Source File
# Begin Source File

SOURCE=.\editreg.h
# End Source File
# Begin Source File

SOURCE=.\EditTree.h
# End Source File
# Begin Source File

SOURCE=.\FutileData.h
# End Source File
# Begin Source File

SOURCE=.\GoLine.h
# End Source File
# Begin Source File

SOURCE=.\GrfData.h
# End Source File
# Begin Source File

SOURCE=.\HeadFilePath.h
# End Source File
# Begin Source File

SOURCE=.\HexEdit.h
# End Source File
# Begin Source File

SOURCE=.\itword9.h
# End Source File
# Begin Source File

SOURCE=.\ListHeader.h
# End Source File
# Begin Source File

SOURCE=.\lock.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Memmap.h
# End Source File
# Begin Source File

SOURCE=.\MessageBox.h
# End Source File
# Begin Source File

SOURCE=.\MoveBtn.h
# End Source File
# Begin Source File

SOURCE=.\MpDef.h
# End Source File
# Begin Source File

SOURCE=.\MyBitmap.h
# End Source File
# Begin Source File

SOURCE=.\MyListBox.h
# End Source File
# Begin Source File

SOURCE=.\ParaDefi.h
# End Source File
# Begin Source File

SOURCE=.\PortTab.h
# End Source File
# Begin Source File

SOURCE=.\ProjectTree.h
# End Source File
# Begin Source File

SOURCE=.\PropertyList.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RichTips.h
# End Source File
# Begin Source File

SOURCE=.\Rijndael.h
# End Source File
# Begin Source File

SOURCE=.\RobinBuffer.h
# End Source File
# Begin Source File

SOURCE=.\scbarcf.h
# End Source File
# Begin Source File

SOURCE=.\scbarg.h
# End Source File
# Begin Source File

SOURCE=.\SelectFlash.h
# End Source File
# Begin Source File

SOURCE=.\Serialport.h
# End Source File
# Begin Source File

SOURCE=.\ShellContextMenu.h
# End Source File
# Begin Source File

SOURCE=.\ShellPidl.h
# End Source File
# Begin Source File

SOURCE=.\ShellString.h
# End Source File
# Begin Source File

SOURCE=.\ShellTreeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ShellWrappers.h
# End Source File
# Begin Source File

SOURCE=.\sizecbar.h
# End Source File
# Begin Source File

SOURCE=.\SmartInterfacePtr.h
# End Source File
# Begin Source File

SOURCE=.\STabCtrl.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TaskDefinition.h
# End Source File
# Begin Source File

SOURCE=.\TestTask.h
# End Source File
# Begin Source File

SOURCE=.\TokenMap.h
# End Source File
# Begin Source File

SOURCE=.\TraceInfo.h
# End Source File
# Begin Source File

SOURCE=.\TreeType.h
# End Source File
# Begin Source File

SOURCE=.\VbhExpression.h
# End Source File
# Begin Source File

SOURCE=.\WaitingTreeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\WordDrive.h
# End Source File
# Begin Source File

SOURCE=.\XTFlatTabCtrl.h
# End Source File
# Begin Source File

SOURCE=.\XTMemDC.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Borer.rc2
# End Source File
# Begin Source File

SOURCE=.\res\BorerDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\buttons.bmp
# End Source File
# Begin Source File

SOURCE=.\res\catalog.ico
# End Source File
# Begin Source File

SOURCE=.\res\CONFIG.ICO
# End Source File
# Begin Source File

SOURCE=.\res\cur00001.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00002.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00004.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\DQ.bin
# End Source File
# Begin Source File

SOURCE=.\res\Dragmove.cur
# End Source File
# Begin Source File

SOURCE=.\res\drop_mov.cur
# End Source File
# Begin Source File

SOURCE=.\res\GatherDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\GPS1.ico
# End Source File
# Begin Source File

SOURCE=.\res\GPS2.ico
# End Source File
# Begin Source File

SOURCE=.\res\GRAPH03.ico
# End Source File
# Begin Source File

SOURCE=.\res\H_MOVE.CUR
# End Source File
# Begin Source File

SOURCE=.\res\H_POINT.CUR
# End Source File
# Begin Source File

SOURCE=.\res\handcur.cur
# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon3.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon4.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon5.ico
# End Source File
# Begin Source File

SOURCE=.\res\iconthre.ico
# End Source File
# Begin Source File

SOURCE=.\res\ITest.ico
# End Source File
# Begin Source File

SOURCE=.\res\List.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mainfram.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Mycomp.ico
# End Source File
# Begin Source File

SOURCE=.\res\nodrop.cur
# End Source File
# Begin Source File

SOURCE=.\res\PDK1.ico
# End Source File
# Begin Source File

SOURCE=.\res\PDK2.ico
# End Source File
# Begin Source File

SOURCE=.\res\splith.cur
# End Source File
# Begin Source File

SOURCE=.\res\tfdropcopy.cur
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar2.bmp
# End Source File
# End Group
# End Target
# End Project
