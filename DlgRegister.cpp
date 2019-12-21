// DlgRegister.cpp : implementation file
//

#include "stdafx.h"
#include "Borer.h"
#include "DlgRegister.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRegister dialog


CDlgRegister::CDlgRegister(CWnd* pParent /*=NULL*/)
: CDialog(CDlgRegister::IDD, pParent)
{
  //{{AFX_DATA_INIT(CDlgRegister)
  m_strName = _T("");
  m_strCompany = _T("");
  m_strTelephone = _T("");
  m_strMail = _T("");
  //}}AFX_DATA_INIT
}


void CDlgRegister::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CDlgRegister)
  DDX_Text(pDX, IDC_EDIT1, m_strName);
  DDX_Text(pDX, IDC_EDIT3, m_strCompany);
  DDX_Text(pDX, IDC_EDIT4, m_strTelephone);
  DDX_Text(pDX, IDC_EDIT5, m_strMail);
  //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRegister, CDialog)
//{{AFX_MSG_MAP(CDlgRegister)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRegister message handlers

void CDlgRegister::OnOK() 
{
  // TODO: Add extra validation here
  UpdateData(TRUE);
  if(m_strName.GetLength() < 1)
  {
    AfxMessageBox("姓名不能为空!") ;
    return;
  }
  if(m_strCompany.GetLength() < 1)
  {
    AfxMessageBox("单位不能为空!") ;
    return;
  }
  if(m_strTelephone.GetLength() < 1)
  {
    AfxMessageBox("电话不能为空!") ;
    return;
  }
  if(m_strMail.GetLength() < 1)
  {
    AfxMessageBox("Mail不能为空!") ;
    return;
  }
  
  CDialog::OnOK();
}
