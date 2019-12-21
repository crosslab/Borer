// TaskDefinition.cpp : implementation file
//

#include "stdafx.h"
#include "Borer.h"
#include "TaskDefinition.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTaskDefinition dialog


CTaskDefinition::CTaskDefinition(CWnd* pParent /*=NULL*/)
: CDialog(CTaskDefinition::IDD, pParent)
{
  //{{AFX_DATA_INIT(CTaskDefinition)
  propItem1 = NULL;
  propItem2 = NULL;
  //}}AFX_DATA_INIT
}

CTaskDefinition::~CTaskDefinition()
{
  if(propItem1)
  {
    delete propItem1;
    propItem1 = NULL;
  }
		
  if(propItem2)
  {
    delete propItem2;
    propItem2 = NULL;
  }
}

void CTaskDefinition::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CTaskDefinition)
  DDX_Control(pDX, IDC_LISTTASK, m_listTask);
  //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTaskDefinition, CDialog)
//{{AFX_MSG_MAP(CTaskDefinition)
ON_WM_SIZE()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTaskDefinition message handlers

BOOL CTaskDefinition::OnInitDialog() 
{
  CDialog::OnInitDialog();
  
  propItem1 = new CPropertyItem("模块名称","",PIT_EDIT,"");
  m_listTask.AddPropItem(propItem1);
  
  propItem2 = new CPropertyItem("模块代码","",PIT_EDIT,"");
  m_listTask.AddPropItem(propItem2);	
  return TRUE;   // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}

void CTaskDefinition::OnSize(UINT nType, int cx, int cy) 
{
  CDialog::OnSize(nType, cx, cy);
  
  CRect r;
  GetClientRect(&r);
  
  if(m_listTask.m_hWnd)
  {
    m_listTask.SetWindowPos(&wndTop,10,10,r.Width()-10,r.Height()-20,SWP_SHOWWINDOW);
  }	
}

BOOL CTaskDefinition::PreTranslateMessage(MSG* pMsg) 
{
  if (pMsg->message == WM_KEYDOWN &&
    pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
  {
    if (1)
    {
      return TRUE;
    }
  }	
  return CDialog::PreTranslateMessage(pMsg);
}
