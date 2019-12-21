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

const int	MMM_DEV_REDRAW     = WM_APP + 0x0004;	//���͸����ڵ���ʾ��Ϣ
const int	MMM_LOAD_FILE      = WM_APP + 0X0005;  //���͸����ڵ���ʾ��Ϣ
const int	MMM_CALL_DATA      = WM_APP + 0X0006;  //���͸����ڵ���ʾ��Ϣ
const int	MMM_ERROR_DISPLAY  = WM_APP + 0X0007;  //���͸����ڵ���ʾ��Ϣ
const int	MMM_SOLOWINDUP     = WM_APP + 0x0009;	//��������ʾ��Ϣ
const int	MMM_HS_DATA        = WM_APP + 0x0010;	//�ֻ����ݰ�
const int	MMM_MCU_DATA       = WM_APP + 0x0011;	//���͸����ڵ���ʾ��Ϣ
const int	MMM_BATCH_RUN      = WM_APP + 0x0012;	//���͸����ڵ���ʾ��Ϣ
const int	MMM_WD_TRACK       = WM_APP + 0x0013;	//���͸����ڵ���ʾ��Ϣ
const int	MMM_MCU_DATAITEM   = WM_APP + 0x0014;	//���͸����ڵ���ʾ��Ϣ
const int	MMM_GPS_DATA       = WM_APP + 0x0015;	//���͸����ڵ���ʾ��Ϣ

UINT AFX_CDECL ProcRunSolo(LPVOID lpScout);
UINT AFX_CDECL ProcRunChorus(LPVOID lpScout);

class CBorerApp : public CWinApp
{
public:
  HANDLE m_hOneInstance;
  CBorerApp();
  void OpenFormView();					  // �򿪲����ĵ�
  void OpenPrevProject();					  // ����һ�δ򿪵Ĺ���
  void OpenJCFormView(CString &strname);   // �򿪸��ǲ����ĵ�
  
  BOOL Authorizated();
  void CreateAuthorFile();
  CString ShowRegisterInfo();
public:
  CString	   m_sAppPath;	  //ϵͳ���е�·��
  CString	   m_sIniFile;    //ϵͳ����INI�ļ�
  
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
