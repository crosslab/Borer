// Borer.h : main header file for the Borer application
//

#if !defined(AFX_Borer_H__B1B69EC9_9FCE_11D2_8CA4_0080ADB8683C__INCLUDED_)
#define AFX_Borer_H__B1B69EC9_9FCE_11D2_8CA4_0080ADB8683C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CBorerApp:
// See Borer.cpp for the implementation of this class
//

#define TA_FAILED 0
#define TA_SUCCESS_CLEAN 1
#define TA_SUCCESS_KILL 2
#define TA_SUCCESS_16 3

DWORD WINAPI TerminateExe( DWORD dwPID, DWORD dwTimeout ) ;
DWORD WINAPI Terminate16App( DWORD dwPID, DWORD dwThread,
                            WORD w16Task, DWORD dwTimeout );

typedef BOOL (CALLBACK *PROCENUMPROC)( DWORD, WORD, LPSTR,LPARAM ) ;

BOOL WINAPI EnumProcs( PROCENUMPROC lpProc, LPARAM lParam ) ;
BOOL CALLBACK CallbackEnum(DWORD, WORD, LPSTR,LPARAM);

const int	MMM_DEV_REDRAW     = WM_APP + 0x0004;	//发送给窗口的提示信息
const int	MMM_LOAD_FILE      = WM_APP + 0X0005;  //发送给窗口的提示信息
const int	MMM_CALL_DATA      = WM_APP + 0X0006;  //发送给窗口的提示信息
const int	MMM_ERROR_DISPLAY  = WM_APP + 0X0007;  //发送给窗口的提示信息
const int	MMM_SOLOWINDUP     = WM_APP + 0x0009;	//结束的提示信息
const int	MMM_HS_DATA        = WM_APP + 0x0010;	//手机数据包
const int	MMM_MCU_DATA       = WM_APP + 0x0011;	//发送给窗口的提示信息
const int	MMM_BATCH_RUN      = WM_APP + 0x0012;	//发送给窗口的提示信息
const int	MMM_WD_TRACK       = WM_APP + 0x0013;	//发送给窗口的提示信息
const int	MMM_MCU_DATAITEM   = WM_APP + 0x0014;	//发送给窗口的提示信息
const int	MMM_GPS_DATA       = WM_APP + 0x0015;	//发送给窗口的提示信息

UINT AFX_CDECL ProcRunSolo(LPVOID lpScout);
UINT AFX_CDECL ProcRunChorus(LPVOID lpScout);

class CBorerApp : public CWinApp
{
public:
  HANDLE m_hOneInstance;
  CBorerApp();
  void OpenFormView();					  // 打开测试文档
  void OpenPrevProject();					  // 打开上一次打开的工程
  void OpenJCFormView(CString &strname);   // 打开覆盖测试文档
  
  BOOL Authorizated();
  void CreateAuthorFile();
  CString ShowRegisterInfo();
public:
  CString	   m_sAppPath;	  //系统运行的路径
  CString	   m_sIniFile;    //系统参数INI文件
  
  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CBorerApp)
public:
  virtual BOOL InitInstance();
  virtual int ExitInstance();
  //}}AFX_VIRTUAL
  
  // Implementation
  
  //{{AFX_MSG(CBorerApp)
  afx_msg void OnAppAbout();
  //}}AFX_MSG
  afx_msg BOOL MyMRUFileHandler(UINT Uid);
  DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_Borer_H__B1B69EC9_9FCE_11D2_8CA4_0080ADB8683C__INCLUDED_)
