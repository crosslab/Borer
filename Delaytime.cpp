// Delaytime.cpp : implementation file
//

#include "stdafx.h"
#include "Borer.h"
#include "Delaytime.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDelaytime dialog


CDelaytime::CDelaytime(CWnd* pParent /*=NULL*/)
: CDialog(CDelaytime::IDD, pParent)
{
  //{{AFX_DATA_INIT(CDelaytime)
  m_nDelayTime = 0;
  //}}AFX_DATA_INIT
}


void CDelaytime::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CDelaytime)
  DDX_Text(pDX, IDC_EDIT_DELAYTIME, m_nDelayTime);
  DDV_MinMaxInt(pDX, m_nDelayTime, 0, 999999999);
  //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDelaytime, CDialog)
//{{AFX_MSG_MAP(CDelaytime)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDelaytime message handlers
//设置延时时间
void CDelaytime::OnOK() 
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
  str.Format("BTSleep(%d);",m_nDelayTime);
  ::SendMessage(pMyView->m_hWnd,WM_MSG_ADD,0,(LPARAM) str.GetBuffer(str.GetLength()));
  str.ReleaseBuffer();
  
  CDialog::OnOK();
  
}
