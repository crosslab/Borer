// GoLine.cpp : implementation file
//

#include "stdafx.h"
#include "Borer.h"
#include "GoLine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGoLine dialog


CGoLine::CGoLine(CWnd* pParent /*=NULL*/)
: CDialog(CGoLine::IDD, pParent)
{
  //{{AFX_DATA_INIT(CGoLine)
  m_nLine = 0;
  //}}AFX_DATA_INIT
}


void CGoLine::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CGoLine)
  DDX_Control(pDX, IDC_EDIT1, m_cCtrlEdit);
  DDX_Text(pDX, IDC_EDIT1, m_nLine);
  DDV_MinMaxInt(pDX, m_nLine, 0, 32765);
  //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGoLine, CDialog)
//{{AFX_MSG_MAP(CGoLine)
ON_WM_SHOWWINDOW()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGoLine message handlers

BOOL CGoLine::OnInitDialog() 
{
  CDialog::OnInitDialog();
  
  // TODO: Add extra initialization here
  
  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}

void CGoLine::OnShowWindow(BOOL bShow, UINT nStatus) 
{
  CDialog::OnShowWindow(bShow, nStatus);
  
  // TODO: Add your message handler code here
  m_cCtrlEdit.SetFocus();
  m_cCtrlEdit.SetSel(0, -1);
}
