#include "stdafx.h"
#include "Borer.h"

#include "CommonDef.h"
#include "MainFrm.h"

#include "ButtonGrp.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CButtonGrp
CButtonGrp::CButtonGrp()
{
  // Create the image list used by frame buttons.
  m_ImgTool.Create(IDB_BUTTONS,14, 1, RGB(255,0,255));
}

CButtonGrp::~CButtonGrp()
{
}

BEGIN_MESSAGE_MAP(CButtonGrp, CStatic)
//{{AFX_MSG_MAP(CButtonGrp)
ON_WM_CREATE()
//}}AFX_MSG_MAP
ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CButtonGrp message handlers

int CButtonGrp::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
  if (CStatic::OnCreate(lpCreateStruct) == -1)
  {
    return -1;
  }
  
  return 0;
}

void CButtonGrp::PreSubclassWindow() 
{
  CStatic::PreSubclassWindow();
  
  CRect rc;
  GetWindowRect(&rc);
  ScreenToClient(&rc);
  rc.top+=1; rc.bottom-=1;
  rc.right-=1;
  rc.left = rc.right-24;
  
  // TODO: Add your specialized creation code here
  if (!m_btn4.Create(NULL, WS_VISIBLE|BS_ICON|BS_OWNERDRAW|BS_CENTER|BS_VCENTER,
    rc, this, IDC_BUTTON4))
  {
    TRACE0("Unable to create button.\n");
    return;
  }
  m_btn4.SetIcon(m_ImgTool.ExtractIcon(3), CSize(14,12));
  rc.OffsetRect(-25,0);
  
  // TODO: Add your specialized creation code here
  if (!m_btn3.Create(NULL, WS_VISIBLE|BS_ICON|BS_OWNERDRAW|BS_CENTER|BS_VCENTER,
    rc, this, IDC_BUTTON3))
  {
    TRACE0("Unable to create button.\n");
    return;
  }
  m_btn3.SetIcon(m_ImgTool.ExtractIcon(2), CSize(14,12));
  rc.OffsetRect(-25,0);
  
  // TODO: Add your specialized creation code here
  if (!m_btn2.Create(NULL, WS_VISIBLE|BS_ICON|BS_OWNERDRAW|BS_CENTER|BS_VCENTER,
    rc, this, IDC_BUTTON2))
  {
    TRACE0("Unable to create button.\n");
    return;
  }
  m_btn2.SetIcon(m_ImgTool.ExtractIcon(1), CSize(14,12));
  rc.OffsetRect(-25,0);
  
  // TODO: Add your specialized creation code here
  if (!m_btn1.Create(NULL, WS_VISIBLE|BS_ICON|BS_OWNERDRAW|BS_CENTER|BS_VCENTER,
    rc, this, IDC_BUTTON1))
  {
    TRACE0("Unable to create button.\n");
    return;
  }
  m_btn1.SetIcon(m_ImgTool.ExtractIcon(0), CSize(14,12));
  rc.OffsetRect(-25,0);
  
  // Create the ToolTip control.
  m_tooltip.Create(this);
  m_tooltip.Activate(TRUE);
  
  // TODO: Use one of the following forms to add controls:
  if(m_filefix) {
    m_tooltip.AddTool(GetDlgItem(IDC_BUTTON1), IDS_BUTTON5);
  }else {
    m_tooltip.AddTool(GetDlgItem(IDC_BUTTON1), IDS_BUTTON1);
  }
  m_tooltip.AddTool(GetDlgItem(IDC_BUTTON2), IDS_BUTTON2);
  m_tooltip.AddTool(GetDlgItem(IDC_BUTTON3), IDS_BUTTON3);
  m_tooltip.AddTool(GetDlgItem(IDC_BUTTON4), IDS_BUTTON4);
}

void CButtonGrp::OnButton1() 
{
  if(m_filefix) {
    GetParent()->PostMessage(CWMM_IMPORT_NOTIFY,0,0);
  }else {
    GetParent()->PostMessage(CWMM_OPEN_NOTIFY,0,0);
  }
}

void CButtonGrp::OnButton2() 
{
  GetParent()->PostMessage(CWMM_SAVE_NOTIFY,0,0);
}

void CButtonGrp::OnButton3() 
{
  GetParent()->PostMessage(CWMM_SAVEAS_NOTIFY,0,0);
}

void CButtonGrp::OnButton4() 
{
  GetParent()->PostMessage(CWMM_CLOSE_NOTIFY,0,0);
}

BOOL CButtonGrp::PreTranslateMessage(MSG* pMsg) 
{
  // Let the ToolTip process this message.
  m_tooltip.RelayEvent(pMsg);
  return CStatic::PreTranslateMessage(pMsg);
}
