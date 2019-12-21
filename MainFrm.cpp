#include "stdafx.h"
#include <io.h>

#include "Borer.h"
#include "MainFrm.h"
#include "BorerDoc.h"
#include "BorerView.h"

#include "editcmd.h"
#include "TestTask.h"
#include "TraceInfo.h"
#include "MessageBox.h"
#include "BorerDoc.h"
#include "DlgTimeSleep.h"
#include "Delaytime.h"
#include "HeadFilePath.h"
#include "WordDrive.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CBorerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame
IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
//{{AFX_MSG_MAP(CMainFrame)
ON_WM_CREATE()
ON_COMMAND(ID_SCRIPT_BEGIN, OnScriptBegin)
ON_COMMAND(ID_SCRIPT_END, OnScriptEnd)
ON_COMMAND(ID_SCRIPT_MESSAGEBOX, OnScriptMessagebox)
ON_COMMAND(ID_SCRIPT_STRTRACE, OnScriptStrtrace)
ON_COMMAND(ID_SCRIPTTOOLBAR, OnScripttoolbar)
ON_COMMAND(ID_SCRIPT_DEBUGBREAK, OnScriptDebugbreak)
ON_COMMAND(ID_SCRIPT_MAINFRAME, OnScriptMainframe)
ON_COMMAND(ID_SCRIPT_PDKREEXCUTE, OnPdkReExcute)
ON_COMMAND(ID_COMTASK_CFG, OnComtaskCfg)
ON_COMMAND(ID_COM_CFG, OnComCfg)
ON_COMMAND(ID_COM_CFG5, OnComCfg5)
ON_COMMAND(ID_CFGV_SYNCH2, OnCfgvSynch2)
ON_COMMAND(ID_FILE_LOAD, OnFileLoad)
ON_COMMAND(ID_TIEM_SET, OnTiemSet)
ON_COMMAND(ID_PaneTest, OnPaneTest)
ON_UPDATE_COMMAND_UI(ID_PaneTest, OnUpdatePaneTest)
ON_COMMAND(ID_ScriptTest, OnScriptTest)
ON_UPDATE_COMMAND_UI(ID_ScriptTest, OnUpdateScriptTest)
ON_COMMAND(ID_SEND_PORT, OnSendPort)
ON_UPDATE_COMMAND_UI(ID_SEND_PORT, OnUpdateSendPort)
ON_COMMAND(ID_SEND_MEM, OnSendMem)
ON_UPDATE_COMMAND_UI(ID_SEND_MEM, OnUpdateSendMem)
ON_UPDATE_COMMAND_UI(ID_SCRIPTTOOLBAR, OnUpdateScripttoolbar)
ON_COMMAND(ID_MN_DELAYTIME, OnMnDelaytime)
ON_COMMAND(ID_AUTO_SEND, OnAutoSend)
ON_UPDATE_COMMAND_UI(ID_AUTO_SEND, OnUpdateAutoSend)
ON_COMMAND(ID_CREATE_REPORT, OnCreateReport)
ON_UPDATE_COMMAND_UI(ID_CREATE_REPORT, OnUpdateCreateReport)
ON_COMMAND(ID_WAITRESPONSE, OnWaitResPackage)
ON_UPDATE_COMMAND_UI(ID_WAITRESPONSE, OnUpdateWaitResPackage)
ON_COMMAND(ID_MDM_START, OnMdmStart)
ON_COMMAND(ID_MDM_STOP, OnMdmStop)
ON_UPDATE_COMMAND_UI(ID_MDM_STOP, OnUpdateMdmStop)
ON_UPDATE_COMMAND_UI(ID_MDM_START, OnUpdateMdmStart)
ON_COMMAND(ID_CMD_SYSINFO, OnCmdSysinfo)
ON_UPDATE_COMMAND_UI(ID_CMD_SYSINFO, OnUpdateCmdSysinfo)
ON_COMMAND(ID_CMD_SHOWINFO, OnCmdShowinfo)
ON_UPDATE_COMMAND_UI(ID_CMD_SHOWINFO, OnUpdateCmdShowinfo)
ON_WM_CLOSE()
ON_COMMAND(ID_RUNBAR, OnRunbar)
ON_UPDATE_COMMAND_UI(ID_RUNBAR, OnUpdateRunbar)
ON_COMMAND(ID_MENUHEADPATH, OnMenuheadpath)
ON_COMMAND(ID_MENUITEMHELP, OnMenuitemhelp)
ON_COMMAND(ID_FILE_NEWC, OnFileNewc)
ON_COMMAND(ID_ITP_OPEN, OnItpOpen)
ON_COMMAND(ID_ITP_SAVE, OnItpSave)
ON_COMMAND(ID_ITP_SAVEAS, OnItpSaveas)
ON_COMMAND(ID_ITP_NEW, OnItpNew)
ON_COMMAND(ID_ITP_CLOSE, OnItpClose)
ON_UPDATE_COMMAND_UI(ID_ITP_SAVE, OnUpdateItpSave)
ON_UPDATE_COMMAND_UI(ID_ITP_SAVEAS, OnUpdateItpSaveas)
ON_UPDATE_COMMAND_UI(ID_ITP_CLOSE, OnUpdateItpClose)
ON_COMMAND(ID_CTRL_PDK, OnCtrlPdk)
//}}AFX_MSG_MAP
ON_UPDATE_COMMAND_UI(ID_INDICATOR_COM, OnUpdateIndicatorCom)
ON_MESSAGE(MMM_DEV_REDRAW, OnDevRedraw)
ON_MESSAGE(MMM_BATCH_RUN, OnBatchRun)
END_MESSAGE_MAP()

static UINT indicators[] =
{
  
  ID_SEPARATOR,               // status line indicator 
    ID_EDIT_INDICATOR_POSITION,	 
    ID_EDIT_INDICATOR_COL,
    ID_EDIT_INDICATOR_CRLF,
    ID_INDICATOR_OVR,
    ID_EDIT_INDICATOR_READ,
    ID_INDICATOR_CAPS,
    ID_INDICATOR_NUM,
    ID_INDICATOR_SCRL,
    ID_INDICATOR_COM,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
  m_bStartTask = FALSE ;
}

CMainFrame::~CMainFrame()
{
  int i = 0;
  for(i=0;i<m_aTestInfo.GetSize();i++)
  {
    delete m_aTestInfo[i];
    m_aTestInfo[i] =NULL ;
  }	
  m_aTestInfo.RemoveAll();
  
  for(i=0;i<m_editMcu.GetSize();i++)
  {
    delete m_editMcu[i];
    m_editMcu[i] =NULL ;
  }
  m_editMcu.RemoveAll();
  
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
  if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
    return -1;
  /////////////////////////////
  
  ///////////////////////////
  int      cfLop;
  CString  cfStr;
  
  
  if(!GlobalInitialize()) {
    return -1;
  }
  
  if(!GlobalCreate()) {
    return -1;
  }
  
  
  //创建控制条
  if(!m_wndTipsBar.Create(_T("输出信息"), this, CSize(230,150),
    TRUE,IDMD_TIPS)) {
    TRACE0("生成系统信息栏失败\n");
    return false;
  }
  m_wndTipsBar.SetSCBStyle(m_wndTipsBar.GetSCBStyle()|SCBS_SIZECHILD);
  
  //创建TAB Control，并把它加入到ControlBar中
  m_FlatTab.Create(WS_CHILD|WS_VISIBLE|FTS_XT_DEFAULT|FTS_XT_HSCROLL,CRect(0,0,100,100),
    &m_wndTipsBar,IDMT_TIPS);
  m_FlatTab.SetFont(&m_SongFont);
  
  m_wndTipsBar.SetBarStyle(m_wndTipsBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
  
  //编辑控件,显示系统信息, 加入TAB Control中
  for(cfLop=0;cfLop<m_editMcu.GetSize();cfLop++) {
    
    if(!m_editMcu[cfLop]->Create(WS_CHILD | WS_TABSTOP | WS_CLIPCHILDREN | WS_VSCROLL |
      WS_HSCROLL | WS_VSCROLL | ES_READONLY|ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL  ,
      CRect(0,0,0,0),&m_FlatTab,ID_START_TIPS+cfLop)) {
      return false;
    }
    m_editMcu[cfLop]->SetFont(&m_TipFont);
    
    cfStr.Format("输出%d",cfLop+1);
    m_FlatTab.AnnexControl(cfLop,cfStr,m_editMcu[cfLop]);		//第一页:系统信息
  }
  m_FlatTab.SetCurSel(0);
  
  //创建控制条
  //ZZZ	if(!m_wndDebugBar.Create(_T("MDMDEBUG信息"), this, CSize(230,150),
  //ZZZ		TRUE,IDC_DEBUGBAR)) {
  //ZZZ		TRACE0("生成MDMDEBUG信息栏失败\n");
  //ZZZ		return false;
  //ZZZ	}
  //ZZZ	m_wndDebugBar.SetSCBStyle(m_wndDebugBar.GetSCBStyle()|SCBS_SIZECHILD);
  
  
  //ZZZ	m_wndDebugBar.SetBarStyle(m_wndDebugBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
  
  
  
  
  //创建控制条
  if(!m_wndInfoBar.Create(_T("系统状态"), this, CSize(230,260),
    TRUE,IDMD_SYSTEM)) {
    TRACE0("生成系统信息栏失败\n");
    return -1;
  }
  m_wndInfoBar.SetSCBStyle(m_wndInfoBar.GetSCBStyle()|SCBS_SIZECHILD);
  
  //创建TAB Control，并把它加入到ControlBar中
  m_TabCtrl.Create(TCS_BOTTOM|WS_CHILD|WS_VISIBLE,CRect(0,0,100,100),
    &m_wndInfoBar,IDMT_SYSTEM);
  m_TabCtrl.SetFont(&m_SongFont);
  //ZZZ   m_TabCtrl.SetImageList(&m_TabImgs);
  
  if(!m_treeBrowser.Create(WS_CHILD, 
    CRect(0,0,0,0), &m_TabCtrl, IDMC_HARDBROWSER)) {
    TRACE0( "Failed to create sheet2.\n");
    return -1;
  }
  m_treeBrowser.AddRootFolderContent(NULL,STCF_INCLUDEALL);
  
  if(!m_treeProject.Create(WS_CHILD, 
    CRect(0,0,0,0), &m_TabCtrl, IDMC_HARDBROWSER)) {
    TRACE0( "Failed to create sheet2.\n");
    return -1;
  }
  m_treeProject.SetLimitText(1000);
  m_treeProject.InitializeImageList();
  
  if(!m_PortList.Create(WS_CHILD|LVS_REPORT|LVS_NOCOLUMNHEADER|LVS_SINGLESEL|LVS_SHOWSELALWAYS, 
    CRect(0,0,0,0), &m_TabCtrl, IDMC_HARDWARE)) {
    TRACE0( "Failed to create sheet1.\n");
    return -1;
  }
  ListView_SetExtendedListViewStyleEx(m_PortList.m_hWnd,LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
  
  m_TabCtrl.AddControl(&m_PortList,"端口" ,0);//第一页
  m_TabCtrl.AddControl(&m_treeBrowser,"脚本" ,3);//第二页
  m_TabCtrl.AddControl(&m_treeProject,"项目" ,2);//第二页
  m_TabCtrl.UpdateWindow();
  
  m_PortList.SetImageList(&m_BigImgs, LVSIL_SMALL);
  m_PortList.InsertColumn(0, _T(""), LVCFMT_LEFT, 128, 0);
  
  // And set up the list items.
  for(cfLop=0;cfLop<m_aTestInfo.GetSize();cfLop++) {
    cfStr.Format("Test%d",m_aTestInfo[cfLop]->m_nTesterSeq);
    m_PortList.InsertItem (cfLop,cfStr,0);
  }
  
  m_PortList.SetExtendedStyle(LVS_EX_FULLROWSELECT);
  m_PortList.SetItemState(0,LVNI_SELECTED, LVNI_SELECTED);
  //停靠控件
  m_wndInfoBar.SetBarStyle(m_wndInfoBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
  
  
  
  // TODO: Remove this if you don't want tool tips or a resizeable toolbar
  m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
    CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
  m_runToolBar.SetBarStyle(m_runToolBar.GetBarStyle() |
    CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
  m_CommandToolBar.SetBarStyle(m_CommandToolBar.GetBarStyle() |
    CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
  // TODO: Delete these three lines if you don't want the toolbar to
  //  be dockable
  m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
  m_runToolBar.EnableDocking(CBRS_ALIGN_ANY);
  m_CommandToolBar.EnableDocking(CBRS_ALIGN_ANY);
  m_wndTipsBar.EnableDocking(CBRS_ALIGN_ANY);
  //ZZZ	m_wndDebugBar.EnableDocking(CBRS_ALIGN_ANY);
  m_wndInfoBar.EnableDocking(CBRS_ALIGN_ANY);
  
  CRect    rBar;
  EnableDocking(CBRS_ALIGN_ANY);
  DockControlBar(&m_wndToolBar);
  DockControlBarLeftOfImpl(&m_runToolBar,&m_wndToolBar,this);	
  DockControlBarLeftOfImpl(&m_CommandToolBar,&m_runToolBar,this);	
  
  DockControlBar(&m_wndTipsBar, AFX_IDW_DOCKBAR_BOTTOM);
  //ZZZ	DockControlBar(&m_wndDebugBar, AFX_IDW_DOCKBAR_BOTTOM);
  DockControlBar(&m_wndInfoBar, AFX_IDW_DOCKBAR_LEFT);
  
  
  RecalcLayout();
  //ZZZ	ShowControlBar(&m_wndDebugBar, FALSE, FALSE);
  
  CString sProfile = _T("ITPDKBarState");
  if (VerifyBarState(sProfile))
  {
    CSizingControlBar::GlobalLoadState(this, sProfile);
    LoadBarState(sProfile);
  }
  
  return 0;
}

bool CMainFrame::VerifyBarState(LPCTSTR lpszProfileName)
{
  CDockState state;
  state.LoadState(lpszProfileName);
  
  for (int i = 0; i < state.m_arrBarInfo.GetSize(); i++)
  {
    CControlBarInfo* pInfo = (CControlBarInfo*)state.m_arrBarInfo[i];
    ASSERT(pInfo != NULL);
    int nDockedCount = pInfo->m_arrBarID.GetSize();
    if (nDockedCount > 0)
    {
      // dockbar
      for (int j = 0; j < nDockedCount; j++)
      {
        UINT nID = (UINT) pInfo->m_arrBarID[j];
        if (nID == 0)  continue; // row separator
        if (nID > 0xFFFF)
          nID &= 0xFFFF; // placeholder - get the ID
        if (GetControlBar(nID) == NULL)
          return FALSE;
      }
    }
    
    if (!pInfo->m_bFloating) // floating dockbars can be created later
    {
      
      if (GetControlBar(pInfo->m_nBarID) == NULL)
        return FALSE; // invalid bar ID
    }
  }
  
  return TRUE;
}


bool CMainFrame::GlobalCreate()
{
  HICON    hStan, hKyle, hCartman, hKenny;
  
  // Set up the image list.
  m_BigImgs.Create(48, 48, ILC_COLOR16 | ILC_MASK, 4, 1);
  
  hStan =reinterpret_cast<HICON>(
    ::LoadImage(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_ICONIDLE),
    IMAGE_ICON, 48, 48, LR_DEFAULTCOLOR));
  hKyle =reinterpret_cast<HICON>(
    ::LoadImage(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_ICONBUSY),
    IMAGE_ICON, 48, 48, LR_DEFAULTCOLOR));	
  hCartman =reinterpret_cast<HICON>(
    ::LoadImage(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_PDKIDLE),
    IMAGE_ICON, 48, 48, LR_DEFAULTCOLOR));
  hKenny =reinterpret_cast<HICON>(
    ::LoadImage(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_PDKACT),
    IMAGE_ICON, 48, 48, LR_DEFAULTCOLOR));	
  
  m_BigImgs.Add(hStan);
  m_BigImgs.Add(hKyle);
  m_BigImgs.Add(hCartman);
  m_BigImgs.Add(hKenny);
  
  // Set up the image list.
  //ZZZ      m_TabImgs.Create(16, 16, ILC_COLOR16 | ILC_MASK, 4, 1);
  
  hStan =reinterpret_cast<HICON>(
    ::LoadImage(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_ICONDEV),
    IMAGE_ICON, 48, 48, LR_DEFAULTCOLOR));
  hCartman =reinterpret_cast<HICON>(
    ::LoadImage(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_ICONPRJ),
    IMAGE_ICON, 48, 48, LR_DEFAULTCOLOR));
  hKyle =reinterpret_cast<HICON>(
    ::LoadImage(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_ICONGRF),
    IMAGE_ICON, 48, 48, LR_DEFAULTCOLOR));
  hKenny =reinterpret_cast<HICON>(
    ::LoadImage(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_ICONNPAD),
    IMAGE_ICON, 48, 48, LR_DEFAULTCOLOR));
  
  //ZZZ      m_TabImgs.Add(hStan);
  //ZZZ      m_TabImgs.Add(hKyle);
  //ZZZ     m_TabImgs.Add(hCartman);
  //ZZZ     m_TabImgs.Add(hKenny);
  
  //  Create a font for the combobox
  NONCLIENTMETRICS ncm;
  memset(&ncm, 0, sizeof(NONCLIENTMETRICS));
  ncm.cbSize =sizeof(NONCLIENTMETRICS);
  SystemParametersInfo(SPI_GETNONCLIENTMETRICS,sizeof(NONCLIENTMETRICS),&ncm,0);
  m_SongFont.CreateFontIndirect(&ncm.lfMessageFont);
  m_TipFont.CreateFontIndirect(&ncm.lfCaptionFont);
  
  if(!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP
    | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
    !m_wndToolBar.LoadToolBar(IDR_MAINFRAME2))
  {
    TRACE0("Failed to create toolbar\n");
    return false;      // fail to create
  }
  m_wndToolBar.SetDlgCtrlID(0x101);
  
		
  if (!m_runToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP
    | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
    !m_runToolBar.LoadToolBar(IDR_TB_CSIRUN))
  {
    TRACE0("Failed to create toolbar\n");
    return false;      // fail to create
    
  }
  m_runToolBar.SetDlgCtrlID(0x102);
  if (!m_CommandToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_ALIGN_LEFT
    | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC)||
    !m_CommandToolBar.LoadToolBar(IDR_TOOLBAR_SCRIPT))
  {
    TRACE0("Failed to create toolbar\n");
    return false;      // fail to create
    
  }
  m_runToolBar.SetDlgCtrlID(0x103);
  
  if(!m_wndStatusBar.Create(this) ||
    !m_wndStatusBar.SetIndicators(indicators,
    sizeof(indicators)/sizeof(UINT)))
  {
    TRACE0("Failed to create status bar\n");
    return false;      // fail to create
  }
  return true;
}


BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
  // TODO: Modify the Window class or styles here by modifying
  //  the CREATESTRUCT cs
  
  return CMDIFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
  CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
  CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

// CMainFrame message handlers
//参数初始化
bool CMainFrame::GlobalInitialize()
{	
  CString  strSec,strKey,strTip,strMmf;
  int      giLop;
  int      nCount = ReadIniInt("System","TotalCount",2);
  
  for(giLop=0;giLop<nCount;giLop++) 
  {
    CCrystalProtocol *pPortData=new CCrystalProtocol;
    pPortData->m_nTestIndex=m_aTestInfo.GetSize();
    pPortData->m_nTesterSeq=giLop+1;
    pPortData->SG_Fixup(theApp.m_sIniFile,giLop+1);///读取配置文件配置
    
#ifndef PDK_PLATFORM
    pPortData->m_nSendManner=SM_COM;
#endif
    
    m_aTestInfo.Add(pPortData);
    
    CRichTips *peditMcu =new CRichTips;
    m_editMcu.Add(peditMcu);
    
  }
  
  //获取当前程序运行路径
  GetModuleFileName(NULL,m_sAppPath.GetBuffer(_MAX_PATH),_MAX_PATH); 
  m_sAppPath.ReleaseBuffer();
  m_sAppPath =m_sAppPath.Left(m_sAppPath.ReverseFind ('\\') + 1);
  m_sIniFile=m_sAppPath+CWSTR_FLINI;
  
  return true;
}

LONG CMainFrame::OnDevRedraw(UINT wParam, LONG lParam)
{
  m_PortList.RedrawWindow();
  return 0;
} 

LONG CMainFrame::OnBatchRun(UINT wParam, LONG lParam)
{
  CFrameWnd *pMyFrm=((CMainFrame*)AfxGetMainWnd())->GetActiveFrame();
  if(!pMyFrm)
  {
    return 0;
  }
  
  CBorerView *pMyView =(CBorerView *)pMyFrm->GetActiveView();
  if(!pMyView)
  {
    return 0;
  }
  
  if(pMyView->m_nMenuType !=Y_IDLE) 
  {
    return 0;
  }
  
  
  
  CWaitCursor wc;
  
  pMyView->m_nMenuType   = Y_RUN;
  pMyView->Trk_callDepth = 0;
  
  // Example for CTime::GetCurrentTime
  CTime   time3= CTime::GetCurrentTime();
  pMyView->MT_log.Format("%sITLOG%s",theApp.m_sAppPath,time3.Format("%Y%m%d—%H：%M：%S"));
  pMyView->MT_date =time3.Format("%m/%d/%Y");
  
  if(!CreateDirectory(pMyView->MT_log, NULL)) 
  { 
    pMyView->MT_log = pMyView->MT_log+"Couldn't be created.";
    AfxMessageBox(pMyView->MT_log); 
    return 0;
  } 
  
  CBorerDoc  *pMyDoc=(CBorerDoc*) pMyView->GetDocument();
  
  if(	pMyDoc->m_nCreateReport==1)
  {
    if(!pMyView->m_wdObj.WDInit(pMyView->MT_log,theApp.m_sAppPath))
    {
      pMyView->m_nMenuType =Y_IDLE;
      return false ;
    }
  }
  
  pMyView->m_wdEnd =false;
  m_editMcu[pMyView->GetDocument()->m_nPortIndex]->OnTipClear();
  
  pMyView->MT_Eic =AfxBeginThread(ProcRunChorus,(void *)pMyView,THREAD_PRIORITY_TIME_CRITICAL,0, CREATE_SUSPENDED);    
  pMyView->MT_Eic->m_bAutoDelete=false;
  pMyView->MT_Eic->ResumeThread();
  
  return 0;
}

//弹出测试任务开始自定义命令设置窗体
void CMainFrame::OnScriptBegin() 
{
  CTestTask dlg;
  dlg.DoModal();	
}

//编写测试任务结束自定义命令
void CMainFrame::OnScriptEnd() 
{
  CFrameWnd *pMyFrm=((CMainFrame*)AfxGetMainWnd())->GetActiveFrame();
  
  if(!pMyFrm) {
    return ;
  }
  
  CView *pMyView=pMyFrm->GetActiveView();
  if(!pMyView) {
    return ;
  }
  
  CBorerDoc  *pMyDoc=(CBorerDoc*) pMyView->GetDocument();
  
  CString strname;
  strname="ITExEnd();";
  ::SendMessage(pMyView->m_hWnd,WM_MSG_ADD,0,(LPARAM) strname.GetBuffer(strname.GetLength()));
  strname.ReleaseBuffer();
  if(pMyDoc->m_nTestScript==0)
  {
    m_aTestInfo[pMyDoc->m_nPortIndex]->TxEnd();
  }
  
}

//弹出信息显示自定义命令设置窗体
void CMainFrame::OnScriptMessagebox() 
{
  CMessageBox dlg;
  dlg.DoModal();
}

//弹出信息提示自定义命令设置窗体
void CMainFrame::OnScriptStrtrace() 
{
  CTraceInfo dlg;
  dlg.DoModal();
  
}

//显示自定义命令工具栏
void CMainFrame::OnScripttoolbar() 
{
  if(m_CommandToolBar.IsWindowVisible()==TRUE)
  {
    ShowControlBar(&m_CommandToolBar,FALSE,FALSE);
  }
  else
  {
    ShowControlBar(&m_CommandToolBar,TRUE,TRUE);
  }
  
}

void CMainFrame::OnUpdateScripttoolbar(CCmdUI* pCmdUI) 
{
  pCmdUI->SetCheck(m_CommandToolBar.IsWindowVisible());
}

//设置断点自定义命令
void CMainFrame::OnScriptDebugbreak() 
{
  CFrameWnd *pMyFrm=((CMainFrame*)AfxGetMainWnd())->GetActiveFrame();
  if(!pMyFrm) {
    return ;
  }
  
  CView *pMyView=pMyFrm->GetActiveView();
  if(!pMyView) {
    return ;
  }
  CString strname;
  strname="ITBreak();";
  ::SendMessage(pMyView->m_hWnd,WM_MSG_ADD,0,(LPARAM) strname.GetBuffer(strname.GetLength()));
  strname.ReleaseBuffer();
}


static char *lpCMain="//测试项：\r\n\
                                  #include \"ITCommon.h\"\r\n\
                                  \r\n\
                                  #ifndef _ITEST_MAIN_ENTRY_\r\n\
                                  #define _ITEST_MAIN_ENTRY_\r\n\
                                  ////ADD YOUR HEADFILE\r\n\
                                  \r\n\
                                  int main(void)\r\n\
                                  #else\r\n\
                                  ////ADD YOUR HEADFILE\r\n\
                                  \r\n\
                                  int subFunction(void)\r\n\
                                  #endif\r\n\
                                  {\r\n\
                                  //////////////////////////////////\r\n\
                                  char ccc[256];\r\n\
                                  \r\n\
                                  sprintf(ccc,\"Enter %s\",_ThisFile_());\r\n\
                                  ITTrace(ccc);\r\n\
                                  \
                                  ///////////////////////////////////\r\n\
                                  //// Add your specialized code here\r\n\
                                  \r\n\
                                  \r\n\
                                  \r\n\
                                  ///////////////////////////////////\r\n\
                                  sprintf(ccc,\"Sucess! Leave %s\",_ThisFile_());\r\n\
                                  ITTrace(ccc);\r\n\
                                  \
                                  ///////////////////////////////////\r\n\
                                  return 0;\r\n\
                                  }\r\n\
                                  ";

//生成脚本文件主框架
void CMainFrame::OnScriptMainframe() 
{
  CFrameWnd *pMyFrm=((CMainFrame*)AfxGetMainWnd())->GetActiveFrame();
  if(!pMyFrm) {
    return ;
  }
  
  CView *pMyView=pMyFrm->GetActiveView();
  if(!pMyView) {
    return ;
  }
  
  pMyView->SendMessage(WM_MSG_ADD,0,(LPARAM)lpCMain);
}

void CMainFrame::OnPdkReExcute() 
{
  
}

void CMainFrame::DockControlBarImpl(CControlBar* pBar, 
                                    CDockBar* pDockBar, 
                                    LPCRECT lpRect, 
                                    CFrameWnd* pFrameWnd)
{
  ASSERT(pBar != NULL);
  // make sure CControlBar::EnableDocking has been called
  ASSERT(pBar->m_pDockContext != NULL);
  
  if (pDockBar == NULL)
  {
    for (int i = 0; i < 4; i++)
    {
      if ((dwDockBarMap[i][1] & CBRS_ALIGN_ANY) ==
        (pBar->m_dwStyle & CBRS_ALIGN_ANY))
      {
        pDockBar = (CDockBar*)GetControlBar(dwDockBarMap[i][0]);
        ASSERT(pDockBar != NULL);
        // assert fails when initial CBRS_ of bar does not
        // match available docking sites, as set by EnableDocking()
        break;
      }
    }
    
  }
  
  // if this assertion occurred it is because the parent of pBar was not initially
  // this CFrameWnd when pBar's OnCreate was called
  // i.e. this control bar should have been created with a different parent initially
  pDockBar->DockControlBar(pBar, lpRect);
}

void CMainFrame::DockControlBarImpl(CControlBar* pBar, UINT nDockBarID, LPCRECT lpRect, CFrameWnd* pFrameWnd)
{
  CControlBar* pDockBar = (nDockBarID == 0) ? NULL:GetControlBar(nDockBarID);
  DockControlBarImpl(pBar, (CDockBar*)pDockBar, lpRect, pFrameWnd);
}

void CMainFrame::DockControlBarLeftOfImpl(CControlBar* Bar, 
                                          CControlBar* LeftOf, 
                                          CFrameWnd* pFrameWnd)
{
  CRect rect;
  DWORD dw;
  UINT n;
  
  // get MFC to adjust the dimensions of all docked ToolBars
  // so that GetWindowRect will be accurate
  RecalcLayout(TRUE);
  
  LeftOf->GetWindowRect(&rect);
  rect.OffsetRect(5,0);
  dw=LeftOf->GetBarStyle();
  n = 0;
  n = (dw&CBRS_ALIGN_TOP)				 ? AFX_IDW_DOCKBAR_TOP		: n;
  n = (dw&CBRS_ALIGN_BOTTOM	&& n==0) ? AFX_IDW_DOCKBAR_BOTTOM	: n;
  n = (dw&CBRS_ALIGN_LEFT		&& n==0) ? AFX_IDW_DOCKBAR_LEFT		: n;
  n = (dw&CBRS_ALIGN_RIGHT	&& n==0) ? AFX_IDW_DOCKBAR_RIGHT	: n;
  
  // When we take the default parameters on rect, DockControlBar will dock
  // each Toolbar on a seperate line. By calculating a rectangle, we in effect
  // are simulating a Toolbar being dragged to that location and docked.
  DockControlBarImpl(Bar, n, &rect, pFrameWnd);
}

//设置测试任务及配置参数
void CMainFrame::OnComtaskCfg() 
{
  int        intCm;
  intCm=m_PortList.GetNextItem(-1,LVNI_SELECTED);
  if(intCm<0) {
    return;
  }
  m_aTestInfo[intCm]->SG_Fixup(theApp.m_sIniFile,m_aTestInfo[intCm]->m_nTesterSeq);
  
  if(m_aTestInfo[intCm]->SG_InquireAppPara())	
  {
    ((CBorerView*)m_aTestInfo[intCm]->UpData_pView)->NirvanaView();
  }
}

void CMainFrame::OnUpdateIndicatorCom(CCmdUI* pCmdUI)
{
  int        intCm;
  intCm=m_PortList.GetNextItem(-1,LVNI_SELECTED);
  if(intCm<0) {
    pCmdUI->SetText(_T(""));
    return;
  }
  
  CBorerDoc*  pMyDoc=(CBorerDoc*)(GetActiveFrame()->GetActiveDocument());
  if(pMyDoc) {
    CString    strCom;
    strCom.Format("任务%d：Test%dBorer测试",pMyDoc->m_nPortIndex+1,m_aTestInfo[pMyDoc->m_nPortIndex]->m_nTesterSeq);
    pCmdUI->SetText(strCom);
  }
}

//设置测试参数
void CMainFrame::OnComCfg() 
{
  int        intCm;
  intCm=m_PortList.GetNextItem(-1,LVNI_SELECTED);
  if(intCm<0) {
    return;
  }
  
  m_aTestInfo[intCm]->SG_Fixup(theApp.m_sIniFile,m_aTestInfo[intCm]->m_nTesterSeq);
  m_aTestInfo[intCm]->SG_InquireDevPara();
}

void CMainFrame::OnComCfg5() 
{
  int        intCm;
  intCm=m_PortList.GetNextItem(-1,LVNI_SELECTED);
  if(intCm<0) {
    return;
  }
  
  m_aTestInfo[intCm]->SG_Fixup(theApp.m_sIniFile,m_aTestInfo[intCm]->m_nTesterSeq);
  m_aTestInfo[intCm]->SG_InquireDevPara();	
}

//前置测试对应界面
void CMainFrame::OnCfgvSynch2() 
{
  int intCm=m_PortList.GetNextItem(-1,LVNI_SELECTED);
  if(intCm<0) {
    return;
  }
  
  
  CWnd  *dcWnd=m_aTestInfo[intCm]->UpData_pView->GetParent();
  while(!dcWnd->IsKindOf(RUNTIME_CLASS(CMDIChildWnd))) {
    dcWnd=dcWnd->GetParent();
  }
  
  MDIActivate(dcWnd);	
}

//读入文件
void CMainFrame::OnFileLoad() 
{
  CString strSec;
  char buf_Inner[_MAX_PATH];
  
  CFrameWnd *pMyFrm=((CMainFrame*)AfxGetMainWnd())->GetActiveFrame();
  if(!pMyFrm) {
    return ;
  }
  
  CView *pMyView=pMyFrm->GetActiveView();
  if(!pMyView) {
    return ;
  }
  CBorerDoc  *pMyDoc=(CBorerDoc*) pMyView->GetDocument();
  
  strSec.Format("%s%d",CW_ITCOMSEC,m_aTestInfo[pMyDoc->m_nPortIndex]->m_nTesterSeq);
  
  CFileDialog dlg(true,"","",NULL,"C Files (*.C)|*.C|All Files (*.*)|*.*||");
  
  if(dlg.DoModal() == IDOK)
  {
    pMyDoc->m_xTextBuffer.FreeAll();
    pMyDoc->m_xTextBuffer.LoadFromFile(dlg.GetPathName());
    pMyDoc->SetPathName(dlg.GetPathName());
    pMyDoc->m_strDocFile=dlg.GetPathName();
    sprintf(buf_Inner,"%s",dlg.GetPathName());
    WriteIniString(strSec,"DOCNAME",buf_Inner);
    UpdateData(false);
  }	
}

//弹出延时时间设置窗体
void CMainFrame::OnTiemSet() 
{
  DlgTimeSleep timesleep;
  timesleep.DoModal();	
}

//置系统为面板调试
void CMainFrame::OnPaneTest() 
{
  CFrameWnd *pMyFrm=((CMainFrame*)AfxGetMainWnd())->GetActiveFrame();
  if(!pMyFrm) {
    return ;
  }
  
  CView *pMyView=pMyFrm->GetActiveView();
  if(!pMyView) {
    return ;
  }
  CBorerDoc  *pMyDoc=(CBorerDoc*) pMyView->GetDocument();
  
  pMyDoc->m_nTestScript=0;
  
  char buf[10];
  CString strSec;
  strSec.Format("%s%d",CW_ITCOMSEC,m_aTestInfo[pMyDoc->m_nPortIndex]->m_nTesterSeq);
  WriteIniString(strSec,"ntestScript",_itoa((int)pMyDoc->m_nTestScript,buf,10));	
}

void CMainFrame::OnUpdatePaneTest(CCmdUI* pCmdUI) 
{
  CFrameWnd *pMyFrm=((CMainFrame*)AfxGetMainWnd())->GetActiveFrame();
  if(!pMyFrm) {
    return ;
  }
  
  CView *pMyView=pMyFrm->GetActiveView();
  if(!pMyView) {
    return ;
  }
  CBorerDoc  *pMyDoc=(CBorerDoc*) pMyView->GetDocument();
  
  pCmdUI->SetCheck(!pMyDoc->m_nTestScript);
}

//置系统为脚本调试
void CMainFrame::OnScriptTest() 
{
  CFrameWnd *pMyFrm=((CMainFrame*)AfxGetMainWnd())->GetActiveFrame();
  if(!pMyFrm) {
    return ;
  }
  
  CView *pMyView=pMyFrm->GetActiveView();
  if(!pMyView) {
    return ;
  }
  CBorerDoc  *pMyDoc=(CBorerDoc*) pMyView->GetDocument();
  
  pMyDoc->m_nTestScript=1;
  
  char buf[10];
  CString strSec;
  strSec.Format("%s%d",CW_ITCOMSEC,m_aTestInfo[pMyDoc->m_nPortIndex]->m_nTesterSeq);
  WriteIniString(strSec,"ntestScript",_itoa((int)pMyDoc->m_nTestScript,buf,10));	
}

void CMainFrame::OnUpdateScriptTest(CCmdUI* pCmdUI) 
{
  CFrameWnd *pMyFrm=((CMainFrame*)AfxGetMainWnd())->GetActiveFrame();
  if(!pMyFrm) {
    return ;
  }
  
  CView *pMyView=pMyFrm->GetActiveView();
  if(!pMyView) {
    return ;
  }
  CBorerDoc  *pMyDoc=(CBorerDoc*) pMyView->GetDocument();
  pCmdUI->SetCheck(pMyDoc->m_nTestScript);
}

//置系统为测试发送
void CMainFrame::OnSendPort() 
{
  int intCm = m_PortList.GetNextItem(-1,LVNI_SELECTED);
  if(intCm<0) 
  {
    return;
  }
  
  m_aTestInfo[intCm]->m_nSendManner=SM_COM;
  
  char buf[10];
  CString strSec;
  strSec.Format("%s%d",CW_ITCOMSEC,m_aTestInfo[intCm]->m_nTesterSeq);
  WriteIniString(strSec,"nsendmaner",_itoa((int)m_aTestInfo[intCm]->m_nSendManner,buf,10));
  
  m_PortList.RedrawWindow();
  
}

void CMainFrame::OnUpdateSendPort(CCmdUI* pCmdUI) 
{
  int        intCm;
  intCm=m_PortList.GetNextItem(-1,LVNI_SELECTED);
  if(intCm<0)
  {
    return;
  }
  
  pCmdUI->SetCheck(!m_aTestInfo[intCm]->m_nSendManner);
  if (m_bStartTask)
  {
    pCmdUI->Enable(false);
  }
  else
  {
    pCmdUI->Enable(true);
  }
}

//置系统为共享内存发送
void CMainFrame::OnSendMem() 
{	
  int intCm = m_PortList.GetNextItem(-1,LVNI_SELECTED);
  if(intCm<0) {
    return;
  }
  
  m_aTestInfo[intCm]->m_nSendManner=SM_SHAREMEMORY;
  
  char buf[10];
  CString strSec;
  strSec.Format("%s%d",CW_ITCOMSEC,m_aTestInfo[intCm]->m_nTesterSeq);
  WriteIniString(strSec,"nsendmaner",_itoa((int)m_aTestInfo[intCm]->m_nSendManner,buf,10));	
  
  m_PortList.RedrawWindow();
}

void CMainFrame::OnUpdateSendMem(CCmdUI* pCmdUI) 
{
#ifndef PDK_PLATFORM
		pCmdUI->Enable(false);
    return;
#endif
    
    int        intCm;
    intCm=m_PortList.GetNextItem(-1,LVNI_SELECTED);
    if(intCm<0) {
      return;
    }
    
    pCmdUI->SetCheck(m_aTestInfo[intCm]->m_nSendManner == SM_SHAREMEMORY);
    
    if (m_bStartTask)
    {
      pCmdUI->Enable(false);
    }
    else
    {
      pCmdUI->Enable(true);
    }
    
}


//弹出设置延时时间设置窗体
void CMainFrame::OnMnDelaytime() 
{
  CDelaytime dlg;
  dlg.DoModal();	
}

//设置系统是否自动发送
void CMainFrame::OnAutoSend() 
{
  CFrameWnd *pMyFrm=((CMainFrame*)AfxGetMainWnd())->GetActiveFrame();
  if(!pMyFrm)
  {
    return ;
  }
  
  CView *pMyView=pMyFrm->GetActiveView();
  if(!pMyView) 
  {
    return ;
  }
  CBorerDoc  *pMyDoc=(CBorerDoc*) pMyView->GetDocument();
  
  if(	pMyDoc->m_nAutoSend==1)
  {
    pMyDoc->m_nAutoSend=0;
  }
  else
  {
    pMyDoc->m_nAutoSend=1;
  }
  
  char buf[10];
  CString strSec;
  strSec.Format("%s%d",CW_ITCOMSEC,m_aTestInfo[pMyDoc->m_nPortIndex]->m_nTesterSeq);
  WriteIniString(strSec,"nautosend",_itoa((int)pMyDoc->m_nAutoSend,buf,10));	
}

//设置系统是否生成报告
void CMainFrame::OnCreateReport() 
{
  CFrameWnd *pMyFrm=((CMainFrame*)AfxGetMainWnd())->GetActiveFrame();
  if(!pMyFrm) 
  {
    return ;
  }
  
  CView *pMyView=pMyFrm->GetActiveView();
  if(!pMyView)
  {
    return ;
  }
  CBorerDoc  *pMyDoc=(CBorerDoc*) pMyView->GetDocument();
  
  if(	pMyDoc->m_nCreateReport==1)
  {
    pMyDoc->m_nCreateReport=0;
  }
  else
  {
    pMyDoc->m_nCreateReport=1;
  }
  
  char buf[10];
  CString strSec;
  strSec.Format("%s%d",CW_ITCOMSEC,m_aTestInfo[pMyDoc->m_nPortIndex]->m_nTesterSeq);
  WriteIniString(strSec,"nCreateReport",_itoa((int)pMyDoc->m_nCreateReport,buf,10));	
}

//设置系统需要等待终端的回应包
void CMainFrame::OnWaitResPackage() 
{
  int intCm = m_PortList.GetNextItem(-1,LVNI_SELECTED);
  if(intCm<0) {
    return;
  }
  
  CString strSec;
  strSec.Format("%s%d",CW_ITCOMSEC,m_aTestInfo[intCm]->m_nTesterSeq);
  
  if(m_aTestInfo[intCm]->m_bWaitPackage)
  {
    m_aTestInfo[intCm]->m_bWaitPackage	= FALSE;
    WriteIniString(strSec,"nWaitResPackage","0");	
  }
  else
  {
    m_aTestInfo[intCm]->m_bWaitPackage	= TRUE ;
    WriteIniString(strSec,"nWaitResPackage","1");	
  }
}

void CMainFrame::OnUpdateAutoSend(CCmdUI* pCmdUI) 
{
  CFrameWnd *pMyFrm=((CMainFrame*)AfxGetMainWnd())->GetActiveFrame();
  if(!pMyFrm)
  {
    return ;
  }
  
  CView *pMyView=pMyFrm->GetActiveView();
  if(!pMyView)
  {
    return ;
  }
  CBorerDoc  *pMyDoc=(CBorerDoc*) pMyView->GetDocument();
  
  pCmdUI->SetCheck(pMyDoc->m_nAutoSend);
}


void CMainFrame::OnUpdateCreateReport(CCmdUI* pCmdUI) 
{
  CFrameWnd *pMyFrm=((CMainFrame*)AfxGetMainWnd())->GetActiveFrame();
  if(!pMyFrm) {
    return ;
  }
  
  CView *pMyView=pMyFrm->GetActiveView();
  if(!pMyView) {
    return ;
  }
  CBorerDoc  *pMyDoc=(CBorerDoc*) pMyView->GetDocument();
  
  pCmdUI->SetCheck(pMyDoc->m_nCreateReport);
  
  m_bStartTask = FALSE ;
}

void CMainFrame::OnUpdateWaitResPackage(CCmdUI* pCmdUI) 
{
  
  int        intCm;
  intCm=m_PortList.GetNextItem(-1,LVNI_SELECTED);
  if(intCm<0)
  {
    return;
  }
  
  pCmdUI->SetCheck(m_aTestInfo[intCm]->m_bWaitPackage);
}





//程序退出保存控件状态。
BOOL CMainFrame::DestroyWindow() 
{
  
  return CMDIFrameWnd::DestroyWindow();
}

//显示测试列表项
void CMainFrame::OnCmdSysinfo() 
{
  ShowControlBar(&m_wndInfoBar, !m_wndInfoBar.IsVisible(), FALSE);
}

void CMainFrame::OnUpdateCmdSysinfo(CCmdUI* pCmdUI) 
{
  pCmdUI->Enable();
  pCmdUI->SetCheck(m_wndInfoBar.IsVisible());	
}

//显示信息显示框
void CMainFrame::OnCmdShowinfo() 
{
  ShowControlBar(&m_wndTipsBar, !m_wndTipsBar.IsVisible(), FALSE);
}

void CMainFrame::OnUpdateCmdShowinfo(CCmdUI* pCmdUI) 
{
  pCmdUI->Enable();
  pCmdUI->SetCheck(m_wndTipsBar.IsVisible());	
}

void CMainFrame::OnClose() 
{
  
  CWaitCursor wc;
  
  for(int intCm=0;intCm<m_aTestInfo.GetSize();intCm++) {
    m_aTestInfo[intCm]->StopTask();
  }
  
  CString sProfile = _T("ITPDKBarState");
  CSizingControlBar::GlobalSaveState(this, sProfile);
  SaveBarState(sProfile);	
  
  CMDIFrameWnd::OnClose();
}

void CMainFrame::OnRunbar() 
{
  if(m_runToolBar.IsWindowVisible()==TRUE)
  {
    ShowControlBar(&m_runToolBar,FALSE,FALSE);
  }
  else
  {
    ShowControlBar(&m_runToolBar,TRUE,TRUE);
  }
  
}

void CMainFrame::OnUpdateRunbar(CCmdUI* pCmdUI) 
{
  pCmdUI->SetCheck(m_runToolBar.IsWindowVisible());
}

void CMainFrame::OnMenuheadpath() 
{
  CHeadFilePath	dlg;
  dlg.DoModal();
}

void CMainFrame::OnMenuitemhelp() 
{
  // TODO: Add your command handler code here
  
}

void CMainFrame::OnFileNewc() 
{
  CString strSec;
  
  CFrameWnd *pMyFrm=((CMainFrame*)AfxGetMainWnd())->GetActiveFrame();
  if(!pMyFrm) {
    return ;
  }
  
  CView *pMyView=pMyFrm->GetActiveView();
  if(!pMyView) {
    return ;
  }
  CBorerDoc  *pMyDoc=(CBorerDoc*) pMyView->GetDocument();
  
  pMyDoc->m_xTextBuffer.FreeAll();		
  pMyDoc->SetPathName("c:\\fsdf.c");
  
  
}

EXTENSION CMainFrame::m_apszExtension[] =
{
  EXTENSION("tre", "Tree Files"),
    EXTENSION("idt", "Indent Files"),
    EXTENSION("csv", "Comma Delimited Files"),
};

HINT_EXT CMainFrame::m_aheSave[] =
{
  HINT_EXT(HINT_SAVE_TREE_TYPE,  FF_TREE_TYPE),
    HINT_EXT(HINT_SAVE_IDENT_TYPE, FF_INDENT_TYPE),
    HINT_EXT(HINT_SAVE_CSV_TYPE,   FF_CSV_TYPE),
};

HINT_EXT CMainFrame::m_aheLoad[] =
{
  HINT_EXT(HINT_LOAD_TREE_TYPE,  FF_TREE_TYPE),
    HINT_EXT(HINT_LOAD_IDENT_TYPE, FF_INDENT_TYPE),
    HINT_EXT(HINT_LOAD_CSV_TYPE,   FF_CSV_TYPE),
};

void CMainFrame::GetFilter(char sFilter[], HINT_EXT ahe[])
{
  int k;
  char *name[FF_MAX_TYPES];
  char *text[FF_MAX_TYPES];
  
  for (k = 0; k < FF_MAX_TYPES; k++)
  {
    name[k] = m_apszExtension[ahe[k].m_ff].m_name;
    text[k] = m_apszExtension[ahe[k].m_ff].m_text;
  }
  
  sprintf(sFilter, 
    "%s (*.%s)|*.%s|"
    "%s (*.%s)|*.%s|"
    "%s (*.%s)|*.%s|"
    "All Files (*.*)|*.*||", 
    name[FF_TREE_TYPE],  text[FF_TREE_TYPE],  text[FF_TREE_TYPE], 
    name[FF_INDENT_TYPE], text[FF_INDENT_TYPE], text[FF_INDENT_TYPE],
    name[FF_CSV_TYPE],   text[FF_CSV_TYPE],   text[FF_CSV_TYPE]);
  
  for (k = 0; sFilter[k] != 0; k++){
    sFilter[k] = sFilter[k] == '|' ? '\0' : sFilter[k];
  }
}

BOOL CALLBACK DelimiterHookProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
  static CMainFrame  *pMyFrm =NULL;//取主框架窗口指针
  LPOFNOTIFY lpon;
  BOOL bIsCsvSelected;
  
  static int aid[] =
  {
    IDC_STATIC_GROUP,
      IDC_TAB,
      IDC_COMMA,
      IDC_OTHER,
      IDC_DELIMITER,
  }, k;
  static HWND ahCtrl[ARRAY_SIZE(aid)];
  
  switch(uMessage)
  {
  case WM_INITDIALOG:
    for (k = 0; k < ARRAY_SIZE(aid); k++)
    {
      ahCtrl[k] = GetDlgItem(hWnd, aid[k]);
      EnableWindow(ahCtrl[k], false);
    }
    
    pMyFrm =(CMainFrame*)AfxGetApp()->m_pMainWnd;
    SendDlgItemMessage(hWnd, IDC_DELIMITER, EM_LIMITTEXT, 1, 0);
    SendDlgItemMessage(hWnd, IDC_DELIMITER, WM_SETTEXT, 0,(LPARAM)pMyFrm->m_treeProject.m_szDelimiter); 
    CheckRadioButton(hWnd, IDC_TAB, IDC_OTHER, IDC_COMMA);
    break;
    
  case WM_COMMAND: 
    if(HIWORD (wParam) == EN_CHANGE && LOWORD(wParam) == IDC_DELIMITER)
    {
      // Get the character
      SendDlgItemMessage(hWnd, IDC_DELIMITER, EM_GETLINE,0,(LPARAM) pMyFrm->m_treeProject.m_szDelimiter); 
      pMyFrm->m_treeProject.m_szDelimiter[1] = 0;
    }
    if (HIWORD (wParam) == BN_CLICKED)
      EnableWindow(ahCtrl[4], LOWORD(wParam) == IDC_OTHER);
    break;
    
  case WM_NOTIFY:
    lpon = (LPOFNOTIFY) lParam; 
    if (lpon->hdr.code == CDN_FILEOK)
    {
      if (IsDlgButtonChecked(hWnd, IDC_TAB))
        strcpy(pMyFrm->m_treeProject.m_szDelimiter, "\t");
      else if (IsDlgButtonChecked(hWnd, IDC_COMMA))
        strcpy(pMyFrm->m_treeProject.m_szDelimiter, ",");
    }
    if (lpon->hdr.code == CDN_TYPECHANGE)
    {
      bIsCsvSelected = lpon->lpOFN->nFilterIndex == FF_CSV_TYPE + 1;
      for (k = 0; aid[k] != IDC_DELIMITER; k++)
        EnableWindow(ahCtrl[k], bIsCsvSelected);
    }
    break;
  }
  return FALSE;
}

void CMainFrame::OnUpdateItpSave(CCmdUI* pCmdUI) 
{
  pCmdUI->Enable(m_treeProject.GetCount() && m_treeProject.m_bsave);
}

void CMainFrame::OnUpdateItpSaveas(CCmdUI* pCmdUI) 
{
  pCmdUI->Enable(m_treeProject.GetCount());
}

void CMainFrame::OnUpdateItpClose(CCmdUI* pCmdUI) 
{
  pCmdUI->Enable(m_treeProject.GetCount());
}

//测试任务开始
void CMainFrame::OnMdmStart() 
{
  int        intCm;
  intCm = m_PortList.GetNextItem(-1,LVNI_SELECTED);
  if(intCm<0) 
  {
    return;
  }
  
  Sleep(1000);
  
  if(m_aTestInfo[intCm]->m_nSendManner == SM_COM){
    if(m_aTestInfo[intCm]->ITHandShake()!=ERROR_SUCCESS) 
    {
      PostMessage(WM_COMMAND,ID_MDM_STOP,0);
      //		AfxMessageBox("握手错误！");
      return ;
    }
  }else if(m_aTestInfo[intCm]->m_nSendManner == SM_SHAREMEMORY){
    m_aTestInfo[intCm]->ShowMsg("共享内存建立成功",OUTCONTENT);
  }
  
  CFrameWnd *pMyFrm=((CMainFrame*)AfxGetMainWnd())->GetActiveFrame();
  if(!pMyFrm) {
    return ;
  }
  
  CBorerView *pMyView = (CBorerView *)pMyFrm->GetActiveView();
  if(!pMyView) {
    return ;
  }
  pMyView->m_nMenuType = Y_IDLE;
  m_bStartTask = TRUE ;
  m_aTestInfo[intCm]->m_nTesterState = TS_WORKING;
}

//测试任务结束
void CMainFrame::OnMdmStop() 
{
  int        intCm;
  intCm=m_PortList.GetNextItem(-1,LVNI_SELECTED);
  if(intCm<0) {
    return;
  }
  
  m_aTestInfo[intCm]->StopTask();
  m_aTestInfo[intCm]->m_nTesterState = TS_IDLE;
  CFrameWnd *pMyFrm=((CMainFrame*)AfxGetMainWnd())->GetActiveFrame();
  if(!pMyFrm) {
    return ;
  }
  
  CBorerView *pMyView = (CBorerView *)pMyFrm->GetActiveView();
  if(!pMyView) {
    return ;
  }
  pMyView->m_nMenuType = Y_INIT;
}

void CMainFrame::OnUpdateMdmStop(CCmdUI* pCmdUI) 
{
  int     intCm ;
  intCm = m_PortList.GetNextItem(-1,LVNI_SELECTED);
  if(intCm<0)
  {
    return;
  }
  pCmdUI->Enable( m_aTestInfo[intCm]->m_nTesterState == TS_WORKING );
}

void CMainFrame::OnUpdateMdmStart(CCmdUI* pCmdUI) 
{
  int      intCm ;
  intCm  = m_PortList.GetNextItem(-1,LVNI_SELECTED);
  if(intCm<0) 
  {
    return;
  }
  pCmdUI->Enable( m_aTestInfo[intCm]->m_nTesterState != TS_WORKING );
  
}

void CMainFrame::OpenProject()
{
  char dir[_MAX_DIR];
  char drive[_MAX_DRIVE];
  char ext[_MAX_EXT];
  char fname[_MAX_FNAME];
  int k;
  long lHint = HINT_LOAD_TREE_TYPE;
  
  if(_access(m_treeProject.m_strFileName,0x00)==-1) {
    return;
  }
  
  _splitpath(m_treeProject.m_strFileName, drive, dir, fname, ext);
  
  for(k = 0; k < ARRAY_SIZE(m_aheLoad); k++)
  {
    if(strcmp(m_apszExtension[m_aheLoad[k].m_ff].m_text, ext + 1) == 0)
    {
      lHint = m_aheLoad[k].m_hint;
      DoOpen(NULL,lHint,NULL);
      break;
    }
  }
}

void CMainFrame::SaveProject()
{
  char dir[_MAX_DIR];
  char drive[_MAX_DRIVE];
  char ext[_MAX_EXT];
  char fname[_MAX_FNAME];
  int k;
  long lHint = HINT_LOAD_TREE_TYPE;
  
  if(!m_treeProject.m_strFileName.IsEmpty())
  {
    _splitpath(m_treeProject.m_strFileName, drive, dir, fname, ext);
    
    for(k = 0; k < ARRAY_SIZE(m_aheSave); k++)
    {
      if (stricmp(m_apszExtension[m_aheSave[k].m_ff].m_text, ext + 1) == 0)
      {
        lHint = m_aheSave[k].m_hint;
        DoOpen(NULL,lHint,NULL);
        break;
      }
    }
  }
}

void CMainFrame::DoOpen(CView* pSender, LPARAM lHint, CObject* pHint) 
{
  switch(lHint)
  {
  case HINT_NEW:
    m_treeProject.DeleteAllItems();	
    break;
  case HINT_LOAD_DIRECTORY:
    m_treeProject.DeleteAllItems();	
    m_treeProject.OnLoadEntireTree(FF_DIRECTORY_TYPE, m_treeProject.m_qtt);
    break;
  case HINT_LOAD_TREE_TYPE:
    m_treeProject.DeleteAllItems();	
    m_treeProject.OnLoadEntireTree(FF_TREE_TYPE, m_treeProject.m_qtt);
    break;
  case HINT_LOAD_IDENT_TYPE:
    m_treeProject.DeleteAllItems();	
    m_treeProject.OnLoadEntireTree(FF_INDENT_TYPE, m_treeProject.m_qtt);
    break;
  case HINT_LOAD_CSV_TYPE:
    m_treeProject.DeleteAllItems();	
    m_treeProject.OnLoadEntireTree(FF_CSV_TYPE, m_treeProject.m_qtt);
    break;
  case HINT_SAVE_TREE_TYPE:
    m_treeProject.OnSaveEntireTree(FF_TREE_TYPE, m_treeProject.m_qtt);
    break;
  case HINT_SAVE_IDENT_TYPE:
    m_treeProject.OnSaveEntireTree(FF_INDENT_TYPE, m_treeProject.m_qtt);
    break;
  case HINT_SAVE_CSV_TYPE:
    m_treeProject.OnSaveEntireTree(FF_CSV_TYPE, m_treeProject.m_qtt);
    break;
  }
}

void CMainFrame::OnItpOpen() 
{
  // Customize the common dialog.
  OPENFILENAME   ofn;
  char sFilter[256];
  char sPJName[256];
  
  char szFile[MAX_PATH] = TEXT("");
  
  GetFilter(sFilter, m_aheLoad);
  
  ZeroMemory(&ofn, sizeof(ofn));
  ofn.lStructSize         = sizeof(ofn);
  ofn.hwndOwner           = NULL;
  ofn.hInstance           = GetModuleHandle(NULL);
  ofn.lpstrFilter         = sFilter;
  ofn.lpstrCustomFilter   = NULL;
  ofn.nMaxCustFilter      = 0;
  ofn.nFilterIndex        = 1;
  ofn.nMaxFile            = _MAX_PATH;
  ofn.lpstrFileTitle      = NULL;
  ofn.nMaxFileTitle       = 0;
  ofn.lpstrInitialDir     = theApp.m_sAppPath;
  ofn.lpstrDefExt			= m_apszExtension[m_aheLoad[0].m_ff].m_text;
  ofn.lpstrTitle          = "Open";
  ofn.lpTemplateName      = MAKEINTRESOURCE(IDD_OPEN_DELIM_DIALOG);
  ofn.lpfnHook            = (LPOFNHOOKPROC)DelimiterHookProc;
  ofn.lCustData           = (DWORD)this;
  ofn.Flags               = OFN_EXPLORER | OFN_OVERWRITEPROMPT | OFN_FILEMUSTEXIST |
    OFN_HIDEREADONLY | OFN_ENABLEHOOK | OFN_ENABLETEMPLATE | 0;
  ofn.lpstrFile = szFile;
  
  if (GetOpenFileName(&ofn))
  {
    m_treeProject.m_strFileName = ofn.lpstrFile;
    OpenProject();
    m_TabCtrl.SetCurSel(2);
    
    // add by yanliang  add project filename to ini file
    sprintf(sPJName,"%s",m_treeProject.m_strFileName);		
    WriteIniString(DLT_SEC_RAW,CWFL_PROJECTFILE,sPJName);
  }
}

void CMainFrame::OnItpSave() 
{
  if(m_treeProject.GetCount() && m_treeProject.m_bsave){
    if (m_treeProject.m_strFileName.IsEmpty())
      OnItpSaveas();
    else
      SaveProject();
  }
}

void CMainFrame::OnItpSaveas() 
{
  OPENFILENAME   ofn;
  char szFile[MAX_PATH] = TEXT("");
  char sFilter[256];
  
  GetFilter(sFilter, m_aheLoad);
  
  ZeroMemory(&ofn, sizeof(ofn));
  ofn.lStructSize         = sizeof(ofn);
  ofn.hwndOwner           = NULL;
  ofn.hInstance           = GetModuleHandle(NULL);
  ofn.lpstrFilter         = sFilter;
  ofn.lpstrCustomFilter   = NULL;
  ofn.nMaxCustFilter      = 0;
  ofn.nFilterIndex        = 1;
  ofn.nMaxFile            = _MAX_PATH;
  ofn.lpstrFileTitle      = NULL;
  ofn.nMaxFileTitle       = 0;
  ofn.lpstrInitialDir     = theApp.m_sAppPath;
  ofn.lpstrDefExt			= m_apszExtension[m_aheSave[0].m_ff].m_text;
  ofn.lpstrTitle          = "Save As";
  ofn.lpTemplateName      = MAKEINTRESOURCE(IDD_OPEN_DELIM_DIALOG);
  ofn.lpfnHook            = (LPOFNHOOKPROC)DelimiterHookProc;
  ofn.lCustData           = (DWORD)this;
  ofn.Flags               = OFN_EXPLORER | OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY | 
    OFN_ENABLEHOOK | OFN_ENABLETEMPLATE | 0;
  ofn.lpstrFile = szFile;
  
  if (GetSaveFileName(&ofn))
  {
    m_treeProject.m_strFileName = ofn.lpstrFile;
    SaveProject();
  }
}

void CMainFrame::OnItpNew() 
{
  OnItpSave();	
  m_treeProject.DeleteAllItems();	
  
  m_TabCtrl.SetCurSel(2);
}

void CMainFrame::OnItpClose() 
{
  OnItpSave();	
  m_treeProject.DeleteAllItems();	
}

void CMainFrame::OnCtrlPdk() 
{
  EnumProcs(&CallbackEnum,(LPARAM)this);
  
  CFileFind finder;
  BOOL bFound = finder.FindFile(theApp.m_sAppPath+"PDK.EXE");
  if(!bFound)
  {
    AfxMessageBox("PDK.exe 和 Borer.exe 不在同一个目录下!");
    return;
  }
  ShellExecute(NULL,"open",theApp.m_sAppPath+"PDK.EXE", NULL, NULL, SW_SHOWNORMAL);
}

std::string CMainFrame::g_sCintLastError;

void CMainFrame::intError(char *msg) 
{
  // Is it an error description?
  if ( !strnicmp( msg, "Error", 5 ) )
  {
    g_sCintLastError += msg;
    g_sCintLastError += "\r\n";
    
  } // end if
}
