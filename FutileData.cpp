#include "stdafx.h"
#include "Borer.h"
#include "FutileData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFutileData dialog
CFutileData::CFutileData(CWnd* pParent /*=NULL*/)
: CDialog(CFutileData::IDD, pParent)
{
  //{{AFX_DATA_INIT(CFutileData)
  m_sCfgName = _T("");
  m_strMcuFile = _T("");
  m_strATFile = _T("");
  //}}AFX_DATA_INIT
}


void CFutileData::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CFutileData)
  DDX_Text(pDX, IDE_CFG_FILE, m_sCfgName);
  DDX_Text(pDX, IDC_EDIT_MCUMAP, m_strMcuFile);
  DDX_Text(pDX, IDE_CFG_ATFILE, m_strATFile);
  //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFutileData, CDialog)
//{{AFX_MSG_MAP(CFutileData)
ON_BN_CLICKED(IDC_HC_CFBRS, OnHcCfbrs)
ON_BN_CLICKED(IDC_HC_CONFIG, OnHcConfig)
ON_BN_CLICKED(IDC_BUTTON1, OnButtonMcu)
ON_BN_CLICKED(IDC_HC_CFBAT, OnHcCfbat)
ON_BN_CLICKED(IDC_HC_CONAT, OnHcConat)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFutileData message handlers
BOOL CFutileData::OnInitDialog() 
{
  CDialog::OnInitDialog();	
  
  char  szBuffer[256];
  
  sprintf(szBuffer,"”¶”√…Ë÷√ %d",CUE_port);//""""""""""""""
  SetWindowText(szBuffer);
  
  ShowRole(CUE_Role);
  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}


void CFutileData::ShowRole(int idBtn)
{
}

int CFutileData::RecceRole()
{
  
  return -1;
}

void CFutileData::OnOK() 
{
  UpdateData(true);
  
  CUE_Role=RecceRole();
  
  
  CDialog::OnOK();
}

void CFutileData::OnHcCfbrs() 
{
  UpdateData(true);
  
  CFileDialog dlg(true,"","",NULL,"XML Files (*.xml)|*.xml|All Files (*.*)|*.*||");
  
  if(dlg.DoModal() == IDOK)
  {
    m_sCfgName = dlg.GetPathName();
    UpdateData(false);
  }		
}

void CFutileData::OnHcConfig() 
{
  UpdateData(true);
  
}



void CFutileData::OnButtonMcu() 
{
  UpdateData(true);
  CFileDialog dlg(true,"","",NULL,"map Files (*.map)|*.map|All Files (*.*)|*.*||");
  
  if(dlg.DoModal() == IDOK)
  {
    m_strMcuFile = dlg.GetPathName();
    UpdateData(false);
  }	
}


void CFutileData::OnHcCfbat() 
{
  UpdateData(true);
  CFileDialog dlg(true,"","",NULL,"INI Files (*.ini)|*.ini|All Files (*.*)|*.*||");
  
  if(dlg.DoModal() == IDOK)
  {
    m_strATFile = dlg.GetPathName();
    UpdateData(false);
  }
}

void CFutileData::OnHcConat() 
{
  UpdateData(true);
  
}
