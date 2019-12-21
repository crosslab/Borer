// MessageBox.cpp : implementation file
//

#include "stdafx.h"
#include "Borer.h"
#include "MessageBox.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMessageBox dialog


CMessageBox::CMessageBox(CWnd* pParent /*=NULL*/)
: CDialog(CMessageBox::IDD, pParent)
{
  //{{AFX_DATA_INIT(CMessageBox)
  m_strContent = _T("");
  //}}AFX_DATA_INIT
}


void CMessageBox::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CMessageBox)
  DDX_Text(pDX, IDC_EDIT_BOXCONTENT, m_strContent);
  //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMessageBox, CDialog)
//{{AFX_MSG_MAP(CMessageBox)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMessageBox message handlers
//设置显示信息内容
void CMessageBox::OnOK() 
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
  str.Format("ITMessageBox(\"%s\");",m_strContent);
  ::SendMessage(pMyView->m_hWnd,WM_MSG_ADD,0,(LPARAM) str.GetBuffer(str.GetLength()));
  str.ReleaseBuffer();
  
  CDialog::OnOK();
}
