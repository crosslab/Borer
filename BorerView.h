// BorerView.h : interface of the CBorerView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BorerVIEW_H__B1B69ED3_9FCE_11D2_8CA4_0080ADB8683C__INCLUDED_)
#define AFX_BorerVIEW_H__B1B69ED3_9FCE_11D2_8CA4_0080ADB8683C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "CCrystalEditView.h"
#include "ParaDefi.h"
#include "WordDrive.h"
#include <string>

class CBorerDoc;
typedef enum _DfgExpectedEvent {
    Y_INIT = 0,      // Init
    Y_IDLE,      // Idle
    Y_RUN,      // Execute
    Y_GO,        // Debug
    Y_STEPINTO,  // F11
    Y_STEPOVER,  // F10
    Y_STEPOUT,   // Shift + F11
    Y_RUNTOEND   // Run to end 
}YEARN;

class CBorerView : public CCrystalEditView
{
  friend class CCrystalProtocol;
  
protected: // create from serialization only
  CBorerView();
  DECLARE_DYNCREATE(CBorerView)
    
    // Attributes
public:
  HANDLE   Inr_hStepOver;   //���ƶϵ����
  YEARN    m_nMenuType;     //�˵����ͣ������Է�ʽѡ��
  int      m_nStopflag;     //�Ƿ�ȴ��¼�
  
  int      Trk_callDepth;   //�ص����������
  int      Snap_callDepth;  //��ǰ���������
  
  CString  Inr_filePC;      //�ļ�����
  CString  Inr_fileGL;      //�ļ�����
  int      Inr_glLine;      //�����ļ����к�
  
  CWinThread   *MT_Eic;		//�����߳�
  CString       MT_log;
  CString       MT_date;
  
  CString       MT_aid;
  CString       MT_leaf;
  
  bool m_bWaitMsg;				//�Ƿ�ȴ���Ϣ
  bool m_bDelMsg;				//ɾ���ȴ���Ϣ
  
  bool m_bWaitValue;				//�Ƿ�ȴ���ѯֵ
  EM_MESSAGE m_waitMsg;			//�ȴ���Ϣ
  CArray<EM_MESSAGE,EM_MESSAGE>  m_aWaitMsg;
  CArray<EM_MESSAGE,EM_MESSAGE>  m_arrReceiveMsg; //���յ�����Ϣ����
  BOOL       m_bNextMsgWaitMsg ;  // ��һ����Ϣ���ǵȴ���Ϣ
  EM_MESSAGE m_waitedMsg;			//�ȴ���Ϣ
  HANDLE m_hGetWaitMsgEvent;		//�ȴ���Ϣ�¼�
  HANDLE m_hGetValueEvent;		//�ȴ���ѯֵ�¼�
  char m_sContent[1000];			//��ѯ����ֵ
  int m_nLen;						//��ѯ��������
  
  CWordDrive m_wdObj;
  bool       m_wdEnd;
  
  
  CBorerDoc* GetDocument();
  bool ShowMsg(char *str);
  
  virtual CCrystalTextBuffer *LocateTextBuffer();
  
protected:
  virtual DWORD ParseLine(DWORD dwCookie, int nLineIndex, TEXTBLOCK *pBuf, int &nActualItems);
  
  // Operations
public:
  void NirvanaView();
  
  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CBorerView)
public:
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
  virtual void OnInitialUpdate();
protected:
  virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
  //}}AFX_VIRTUAL
  
  // Implementation
public:
  virtual ~CBorerView();
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif
 	void ShowError( LPCTSTR pError );
  
  /// Handles CINT error callbacks
  static void CBorerView::CintError( char *msg );
  
  /// Contains errors form CINT
  static std::string	g_sCintLastError;
  
protected:
  
  // Generated message map functions
protected:
  //{{AFX_MSG(CBorerView)
  afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
  afx_msg void OnCsiRunSolo();
  afx_msg void OnCsiGo();
  afx_msg void OnCsiStepInto();
  afx_msg void OnCsiStepout();
  afx_msg void OnCsiStepover();
  afx_msg void OnUpdateCsiStepout(CCmdUI* pCmdUI);
  afx_msg void OnUpdateCsiStepover(CCmdUI* pCmdUI);
  afx_msg void OnUpdateCsiRun(CCmdUI* pCmdUI);
  afx_msg void OnCsiRuntoend();
  afx_msg void OnCsiStop();
  afx_msg void OnUpdateCsiStop(CCmdUI* pCmdUI);
  afx_msg void OnTimer(UINT nIDEvent);
  afx_msg void OnUpdateCsiGo(CCmdUI* pCmdUI);
  afx_msg void OnUpdateFilesaveas(CCmdUI* pCmdUI);
  afx_msg void OnUpdateSavefilec(CCmdUI* pCmdUI);
  afx_msg void OnMnDelaytime();
  afx_msg void OnScriptStrtrace();
  afx_msg void OnScriptMessagebox();
  afx_msg void OnScriptDebugbreak();
  afx_msg void OnUpdateCsiRuntoend(CCmdUI* pCmdUI);
  afx_msg void OnUpdateCsiStepinto(CCmdUI* pCmdUI);
  afx_msg void OnScriptMainframe();
  afx_msg void OnPdkReExcute();
  afx_msg void OnCsiQuit();
  afx_msg void OnUpdateCsiQuit(CCmdUI* pCmdUI);
  afx_msg void OnDebugtest();
  //}}AFX_MSG
  LRESULT AddItem(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnSoloWindup(WPARAM WParam, LPARAM LParam);
  afx_msg LRESULT OnWordTrack(WPARAM WParam, LPARAM LParam);
  afx_msg void OnLoadFile();
  afx_msg LRESULT OnReceiveHSData(WPARAM wpHsData, LPARAM lpHsData);
  
  DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in BorerView.cpp
inline CBorerDoc* CBorerView::GetDocument()
{ return (CBorerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BorerVIEW_H__B1B69ED3_9FCE_11D2_8CA4_0080ADB8683C__INCLUDED_)
