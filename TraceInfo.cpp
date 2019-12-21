// TraceInfo.cpp : implementation file
//

#include "stdafx.h"
#include "Borer.h"
#include "TraceInfo.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTraceInfo dialog


CTraceInfo::CTraceInfo(CWnd* pParent /*=NULL*/)
: CDialog(CTraceInfo::IDD, pParent)
{
  //{{AFX_DATA_INIT(CTraceInfo)
  m_strTraceInfo = _T("");
  //}}AFX_DATA_INIT
}


void CTraceInfo::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CTraceInfo)
  DDX_Text(pDX, IDC_EDIT_BOXCONTENT, m_strTraceInfo);
  //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTraceInfo, CDialog)
//{{AFX_MSG_MAP(CTraceInfo)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTraceInfo message handlers
//设置提示信息
void CTraceInfo::OnOK() 
{
  UpdateData(true);
  CFrameWnd *pMyFrm=((CMainFrame*)AfxGetMainWnd())->GetActiveFrame();
  if(!pMyFrm) {
	   return ;
  }
  
  CView *pMyView=pMyFrm->GetActiveView();
  if(!pMyView) {
	   return ;
  }
  
  CString str;
  str.Format("ITTrace(\"%s\");",m_strTraceInfo);
  ::SendMessage(pMyView->m_hWnd,WM_MSG_ADD,0,(LPARAM) str.GetBuffer(str.GetLength()));
  str.ReleaseBuffer();
  CDialog::OnOK();
}
