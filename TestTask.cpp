// TestTask.cpp : implementation file
//

#include "stdafx.h"
#include "Borer.h"
#include "TestTask.h"
#include "MainFrm.h"
#include "BorerDoc.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CBorerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTestTask dialog


CTestTask::CTestTask(CWnd* pParent /*=NULL*/)
: CDialog(CTestTask::IDD, pParent)
{
  //{{AFX_DATA_INIT(CTestTask)
  //}}AFX_DATA_INIT
}


void CTestTask::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CTestTask)
  DDX_Control(pDX, IDC_LISTTESTTASK, m_listTestTask);
  //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestTask, CDialog)
//{{AFX_MSG_MAP(CTestTask)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestTask message handlers
//界面初始化，读取参数
BOOL CTestTask::OnInitDialog() 
{
  CDialog::OnInitDialog();
  
  CMainFrame  *pMyFrm1 =(CMainFrame*)AfxGetApp()->m_pMainWnd;//取主框架窗口指针
  
  CFrameWnd *pMyFrm=((CMainFrame*)AfxGetMainWnd())->GetActiveFrame();
  if(!pMyFrm) {
    return 0;
  }
  
  CView *pMyView=pMyFrm->GetActiveView();
  if(!pMyView) {
    return 0;
  }
  
  CBorerDoc  *pMyDoc=(CBorerDoc*) pMyView->GetDocument();
  
  m_listTestTask.SetExtendedStyle(LVS_EX_HEADERDRAGDROP | LVS_EX_CHECKBOXES | WS_EX_CLIENTEDGE | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
  
  static LV_COLUMN cols[2] = 
  {
    { LVCF_TEXT | LVCF_SUBITEM | LVCF_WIDTH, 0, 50, _T("序号") },
    { LVCF_TEXT | LVCF_SUBITEM | LVCF_WIDTH, 0, 150, _T("任务名称") },
  };	
  const NUMCOLS = sizeof(cols)/sizeof(cols[0]);
  for(int i = 0; i<NUMCOLS; i++) 
  {
    cols[i].iSubItem = i;
    m_listTestTask.InsertColumn(i,&cols[i]);
  }
  
  CString strtemp,strport,str;
  int nSelected=0;
  
  
  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}

//设置测试任务参数
void CTestTask::OnOK() 
{
  UpdateData(true);
  char strId[30];
  
  CMainFrame  *pMyFrm1 =(CMainFrame*)AfxGetApp()->m_pMainWnd;//取主框架窗口指针
  
  CFrameWnd *pMyFrm=((CMainFrame*)AfxGetMainWnd())->GetActiveFrame();
  if(!pMyFrm) {
    return ;
  }
  
  CView *pMyView=pMyFrm->GetActiveView();
  if(!pMyView) {
    return ;
  }
  
  CBorerDoc  *pMyDoc=(CBorerDoc*) pMyView->GetDocument();
  CString str,strtemp,strTask,strport;
  int nNum=0;
  
  str.Format("ITExBegin(\"%s\");",strTask);
  ::SendMessage(pMyView->m_hWnd,WM_MSG_ADD,0,(LPARAM) str.GetBuffer(str.GetLength()));
  str.ReleaseBuffer();	
  if(pMyDoc->m_nTestScript==0)
  {
    pMyFrm1->m_aTestInfo[pMyDoc->m_nPortIndex]->TxBegin(strId,nNum,str.GetBuffer(str.GetLength()));
    str.ReleaseBuffer();
  }
  
  CDialog::OnOK();
}
