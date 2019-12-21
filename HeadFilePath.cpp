#include "stdafx.h"
#include "Borer.h"
#include "HeadFilePath.h"
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
// CHeadFilePath dialog
CHeadFilePath::CHeadFilePath(CWnd* pParent /*=NULL*/)
: CDialog(CHeadFilePath::IDD, pParent)
{
  //{{AFX_DATA_INIT(CHeadFilePath)
  m_strHeadPath = _T("");
  //}}AFX_DATA_INIT
}


void CHeadFilePath::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CHeadFilePath)
  DDX_Text(pDX, IDC_EDITHEADPATH, m_strHeadPath);
  //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHeadFilePath, CDialog)
//{{AFX_MSG_MAP(CHeadFilePath)
ON_BN_CLICKED(IDC_BTNHEADPATH, OnBtnheadpath)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHeadFilePath message handlers
BOOL GetSelPath(CString& strPath)
{
  char szPath[256];
  BROWSEINFO bi;
  LPITEMIDLIST pIDL;
  bi.hwndOwner = NULL;
  bi.pidlRoot = NULL;
  bi.pszDisplayName = szPath; 
  bi.lpszTitle = "请选择文件路径";
  bi.ulFlags = BIF_RETURNONLYFSDIRS;
  bi.lpfn = NULL;
  bi.lParam = 0;
  bi.iImage = 0;
  pIDL = SHBrowseForFolder( &bi );
  if( SHGetPathFromIDList( pIDL, szPath ) )
  {
	   strPath = szPath;
     return TRUE;
  }
  
  return FALSE;
}

BOOL CHeadFilePath::OnInitDialog() 
{
  CDialog::OnInitDialog();
  
  UpdateData(true);
  
  CFrameWnd *pMyFrm=((CMainFrame*)AfxGetMainWnd())->GetActiveFrame();
  if(!pMyFrm) {
    return FALSE;
  }
  
  CView *pMyView=pMyFrm->GetActiveView();
  if(!pMyView) {
    return FALSE;
  }
  
  CBorerDoc  *pMyDoc=(CBorerDoc*) pMyView->GetDocument();
  // TODO: Add extra validation here
  
  m_strHeadPath=pMyDoc->m_strHeadPath;
  
  UpdateData(false);
  
  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}

void CHeadFilePath::OnBtnheadpath() 
{
  if(GetSelPath(m_strHeadPath)==TRUE)
  {
    UpdateData(false);
  }	
}

void CHeadFilePath::OnOK() 
{
  UpdateData(true);
  
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
  pMyDoc->m_strHeadPath=m_strHeadPath;
  
  CString strSec;
  strSec.Format("%s%d",CW_ITCOMSEC,pMyFrm1->m_aTestInfo[pMyDoc->m_nPortIndex]->m_nTesterSeq);
  WriteIniString(strSec,"HEADPATH",m_strHeadPath);
  
  CDialog::OnOK();
}
