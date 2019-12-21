// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__B1B69ECD_9FCE_11D2_8CA4_0080ADB8683C__INCLUDED_)
#define AFX_MAINFRM_H__B1B69ECD_9FCE_11D2_8CA4_0080ADB8683C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include "PortTab.h"
#include "CommList.h"
#include "RichTips.h"

#include "CrystalProtocol.h"
#include "ShellTreeCtrl.h"
#include "ProjectTree.h"


const int	CWINT_DOCKS    =2;
const int	CWINT_DTABS    =4;
#define PDK_PLATFORM

class CMainFrame : public CMDIFrameWnd
{
  DECLARE_DYNAMIC(CMainFrame)
public:
  CMainFrame();
  
  // Attributes
public:
  CFont      m_SongFont ;   //����
  CFont      m_TipFont ;		//����
  CImageList m_BigImgs;	  //������ʾͼ�꣬���ݲ������񣬴���״̬��ʾ��ͬ��ͼ��
  //ZZZ  	CImageList m_TabImgs;	  //ͼ����ʾTABͼ��
  CSizingControlBarCF m_wndInfoBar;		//ϵͳ��Ϣ��
  CSizingControlBarCF m_wndTipsBar;		//��Ϣ��ʾ��
  CXTFlatTabCtrl      m_FlatTab;			//ϵͳ��Ϣ���е�TAB�ؼ�
  CArray <CRichTips*, CRichTips*> m_editMcu;
  ////////
  
  CXTFlatTabCtrl  m_TabsVerbose[CWINT_DOCKS];	//ϵͳ��Ϣ���е�TAB�ؼ�
  
  //ZZZ	CSizingControlBarCF m_wndDebugBar;
  
  CString m_sIniFile;
  CString m_sAppPath;
  
  /////////
  
  
  CPortTab   m_TabCtrl;	  //ϵͳ��Ϣ���е�TAB�ؼ�
  CCommList  m_PortList;	  //�����б�	
  CShellTreeCtrl   m_treeBrowser;  //Ŀ¼�ļ���
  CProjectTree     m_treeProject;  //Ŀ¼�ļ���
  
  CStatusBar  m_wndStatusBar;
  CArray <CCrystalProtocol*, CCrystalProtocol*> m_aTestInfo; //���Զ���
  
  BOOL m_bDataNorm;
  BOOL m_bShowHex;			//ʮ��������ʾ
  BOOL m_bStartTask;          //�Ƿ��Ѿ���ʼ��������
  
  static EXTENSION m_apszExtension[FF_MAX_TYPES];
  static HINT_EXT m_aheSave[FF_MAX_TYPES];
  static HINT_EXT m_aheLoad[FF_MAX_TYPES];
  
  friend CBorerView;
  
  // Operations
public:
  bool    VerifyBarState(LPCTSTR lpszProfileName);
  bool    GlobalCreate();     //������Ӧ�Ŀؼ�
  bool    GlobalInitialize(); //������ʼ��
  
  void GetFilter(char sFilter[], HINT_EXT ahe[]);
  void SaveProject();
  void OpenProject();
  void DoOpen(CView* pSender, LPARAM lHint, CObject* pHint); 
  
  void DockControlBarImpl(
    // Points to the control bar to be docked.
    CControlBar* pBar,
    // Points to the dockbar the control bar is docked to.
    CDockBar* pDockBar,
    // Determines, in screen coordinates, where the 
    // control bar will be docked in the nonclient area 
    // of the destination frame window.
    LPCRECT lpRect,
    // Points to the calling frame window.
    CFrameWnd* pFrameWnd);
  
  // Causes a control bar to be docked to the frame window. The control
  // bar will be docked to one of the sides of the frame window 
  // specified in the calls to both CXTDockWindow::EnableDocking and 
  // CXTFrameWnd::EnableDocking. The side chosen is determined by 
  // nDockBarID.
  //
  void DockControlBarImpl(
    // Points to the control bar to be docked.
    CControlBar* pBar,
    // Determines which sides of the frame window to 
    // consider for docking. It can be 0, or one or 
    // more of the following: 
    //[pre]
    // AFX_IDW_DOCKBAR_TOP     Dock to the top side of 
    //                         the frame window.
    // AFX_IDW_DOCKBAR_BOTTOM  Dock to the bottom side 
    //                         of the frame window.
    // AFX_IDW_DOCKBAR_LEFT    Dock to the left side of 
    //                         the frame window.
    // AFX_IDW_DOCKBAR_RIGHT   Dock to the right side of 
    //                         the frame window.
    //[/pre]
    // If 0, the control bar can be docked to any side 
    // enabled for docking in the destination frame window.
    UINT nDockBarID,
    // Determines, in screen coordinates, where the 
    // control bar will be docked in the nonclient area 
    // of the destination frame window.
    LPCRECT lpRect,
    // Points to the calling frame window.
    CFrameWnd* pFrameWnd);
  
  // This member function will dock the control bar passed in 
  // as the first argument, and dock the control bar that is passed 
  // in as the second argument to the left of the first one.
  //
  void DockControlBarLeftOfImpl(
    // Control bar to dock to the right of
    CControlBar* pBar,
    // Already docked control bar
    CControlBar* pBarLeftOf,
    // Points to the calling frame window.
    CFrameWnd* pFrameWnd);
  
  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CMainFrame)
public:
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
  virtual BOOL DestroyWindow();
  //}}AFX_VIRTUAL
  
  // Implementation
public:
  /// Handles CINT error callbacks
  static void intError( char *msg );
  
  /// Contains errors form CINT
  static std::string	g_sCintLastError;
  virtual ~CMainFrame();
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif
  
protected:  // control bar embedded members
  CToolBar    m_wndToolBar;
  CToolBar    m_runToolBar;
  CToolBar    m_CommandToolBar;
  
  // Generated message map functions
protected:
  //{{AFX_MSG(CMainFrame)
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnScriptBegin();
  afx_msg void OnScriptEnd();
  afx_msg void OnScriptMessagebox();
  afx_msg void OnScriptStrtrace();
  afx_msg void OnScriptTrace();
  afx_msg void OnScripttoolbar();
  afx_msg void OnScriptDebugbreak();
  afx_msg void OnScriptMainframe();
  afx_msg void OnPdkReExcute();
  afx_msg void OnComtaskCfg();
  afx_msg void OnComCfg();
  afx_msg void OnComCfg5();
  afx_msg void OnCfgvSynch2();
  afx_msg void OnFileLoad();
  afx_msg void OnTiemSet();
  afx_msg void OnPaneTest();
  afx_msg void OnUpdatePaneTest(CCmdUI* pCmdUI);
  afx_msg void OnScriptTest();
  afx_msg void OnUpdateScriptTest(CCmdUI* pCmdUI);
  afx_msg void OnSendPort();
  afx_msg void OnUpdateSendPort(CCmdUI* pCmdUI);
  afx_msg void OnSendMem();
  afx_msg void OnUpdateSendMem(CCmdUI* pCmdUI);
  afx_msg void OnUpdateScripttoolbar(CCmdUI* pCmdUI);
  afx_msg void OnMnDelaytime();
  afx_msg void OnAutoSend();
  afx_msg void OnUpdateAutoSend(CCmdUI* pCmdUI);
  afx_msg void OnCreateReport();
  afx_msg void OnUpdateCreateReport(CCmdUI* pCmdUI);
  afx_msg void OnWaitResPackage();
  afx_msg void OnUpdateWaitResPackage(CCmdUI* pCmdUI);
  afx_msg void OnMdmStart();
  afx_msg void OnMdmStop();
  afx_msg void OnUpdateMdmStop(CCmdUI* pCmdUI);
  afx_msg void OnUpdateMdmStart(CCmdUI* pCmdUI);
  afx_msg void OnCmdSysinfo();
  afx_msg void OnUpdateCmdSysinfo(CCmdUI* pCmdUI);
  afx_msg void OnCmdShowinfo();
  afx_msg void OnUpdateCmdShowinfo(CCmdUI* pCmdUI);
  afx_msg void OnClose();
  afx_msg void OnRunbar();
  afx_msg void OnUpdateRunbar(CCmdUI* pCmdUI);
  afx_msg void OnMenuheadpath();
  afx_msg void OnMenuitemhelp();
  afx_msg void OnFileNewc();
  afx_msg void OnItpOpen();
  afx_msg void OnItpSave();
  afx_msg void OnItpSaveas();
  afx_msg void OnItpNew();
  afx_msg void OnItpClose();
  afx_msg void OnUpdateItpSave(CCmdUI* pCmdUI);
  afx_msg void OnUpdateItpSaveas(CCmdUI* pCmdUI);
  afx_msg void OnUpdateItpClose(CCmdUI* pCmdUI);
  afx_msg void OnCtrlPdk();
  afx_msg void OnMenuHex();
  afx_msg void OnUpdateMenuHex(CCmdUI* pCmdUI);
  afx_msg void OnMenuDec();
  afx_msg void OnUpdateMenuDec(CCmdUI* pCmdUI);
  afx_msg void OnMenuNorm();
  afx_msg void OnUpdateMenuNorm(CCmdUI* pCmdUI);
  afx_msg void OnSetAlias();
  afx_msg void OnUpdateIndicatorCom(CCmdUI* pCmdUI);
  //}}AFX_MSG
  LONG OnDevRedraw(UINT wParam, LONG lParam);
  LONG OnBatchRun(UINT wParam, LONG lParam);
  DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__B1B69ECD_9FCE_11D2_8CA4_0080ADB8683C__INCLUDED_)
