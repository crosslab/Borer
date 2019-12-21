#include "stdafx.h"
#include "Borer.h"
#include "DlgAliasEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAliasEdit dialog
CDlgAliasEdit::CDlgAliasEdit(CWnd* pParent /*=NULL*/)
: CDialog(CDlgAliasEdit::IDD, pParent)
{
  //{{AFX_DATA_INIT(CDlgAliasEdit)
  AE_name = _T("");
  //}}AFX_DATA_INIT
}


void CDlgAliasEdit::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CDlgAliasEdit)
  DDX_Text(pDX, IDC_EDIT_ALIAS, AE_name);
  //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAliasEdit, CDialog)
//{{AFX_MSG_MAP(CDlgAliasEdit)
// NOTE: the ClassWizard will add message map macros here
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAliasEdit message handlers
