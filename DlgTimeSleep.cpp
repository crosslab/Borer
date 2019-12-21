

// DlgTimeSleep.cpp : implementation file
//

#include "stdafx.h"
#include "Borer.h"
#include "DlgTimeSleep.h"
#include "MainFrm.h"
#include "BorerDoc.h"
#include "BorerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CBorerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// DlgTimeSleep dialog


DlgTimeSleep::DlgTimeSleep(CWnd* pParent /*=NULL*/)
: CDialog(DlgTimeSleep::IDD, pParent)
{
  //{{AFX_DATA_INIT(DlgTimeSleep)
  m_inttimesleep = 0;
  m_intsendtimes = 0;
  m_nGetValue = 0;
  m_nKeepTime = 0;
  //}}AFX_DATA_INIT
}


void DlgTimeSleep::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(DlgTimeSleep)
  DDX_Text(pDX, IDC_EDITTIMESLEEP, m_inttimesleep);
  DDV_MinMaxInt(pDX, m_inttimesleep, 0, 1000000);
  DDX_Text(pDX, IDC_EDITSENDTIMES, m_intsendtimes);
  DDV_MinMaxInt(pDX, m_intsendtimes, 1, 10000000);
  DDX_Text(pDX, IDC_EDITGETVALUE, m_nGetValue);
  DDV_MinMaxInt(pDX, m_nGetValue, 1, 100000000);
  DDX_Text(pDX, IDC_EDIT_KEEPTIME, m_nKeepTime);
  DDV_MinMaxInt(pDX, m_nKeepTime, 0, 2147483647);
  //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgTimeSleep, CDialog)
//{{AFX_MSG_MAP(DlgTimeSleep)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgTimeSleep message handlers
//保存设置参数
void DlgTimeSleep::OnOK() 
{	
  UpdateData(true);
  CMainFrame  *pMyFrm1 =(CMainFrame*)AfxGetApp()->m_pMainWnd;//取主框架窗口指针
  
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
  // TODO: Add extra validation here
  
  pMyDoc->m_nTimeSleep=m_inttimesleep;
  pMyDoc->m_nWaitoutTime=m_intsendtimes;
  pMyDoc->m_nGetValueTime=m_nGetValue;
  pMyDoc->m_nKeepTime=m_nKeepTime;
  
  char buf[255];
  CString strSec;
  strSec.Format("%s%d",CW_ITCOMSEC,pMyFrm1->m_aTestInfo[pMyDoc->m_nPortIndex]->m_nTesterSeq);
  
  WriteIniString(strSec,"ntimesleep",_itoa((int)m_inttimesleep,buf,10));
  WriteIniString(strSec,"nwaitouttime",_itoa((int)m_intsendtimes,buf,10));	
  WriteIniString(strSec,"nGetValuetime",_itoa((int)m_nGetValue,buf,10));	
  WriteIniString(strSec,"nKeyKeeptime",_itoa((int)m_nKeepTime,buf,10));	
  
  CDialog::OnOK();
}

//界面初始化，读取配置参数
BOOL DlgTimeSleep::OnInitDialog() 
{
  CDialog::OnInitDialog();
  CFrameWnd *pMyFrm=((CMainFrame*)AfxGetMainWnd())->GetActiveFrame();
  if(!pMyFrm) 
  {
    return 0;
  }
  
  CView *pMyView=pMyFrm->GetActiveView();
  if(!pMyView) {
    return 0;
  }
  CBorerDoc  *pMyDoc=(CBorerDoc*) pMyView->GetDocument();
  m_inttimesleep=pMyDoc->m_nTimeSleep;
  m_intsendtimes=pMyDoc->m_nWaitoutTime;
  m_nGetValue=pMyDoc->m_nGetValueTime;
  m_nKeepTime=pMyDoc->m_nKeepTime;
  UpdateData(FALSE);
  
  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}
