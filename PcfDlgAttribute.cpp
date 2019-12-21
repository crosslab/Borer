// PcfDlgAttribute.cpp : implementation file
//

#include "stdafx.h"
#include "Borer.h"
#include "PcfDlgAttribute.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPcfDlgAttribute dialog


CPcfDlgAttribute::CPcfDlgAttribute(CWnd* pParent /*=NULL*/)
	: CDialog(CPcfDlgAttribute::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPcfDlgAttribute)
	m_propItem1 = NULL;
	m_propItem2 = NULL;
	//}}AFX_DATA_INIT
}

CPcfDlgAttribute::~CPcfDlgAttribute()
{
	if(m_propItem1)
	{
		delete m_propItem1;
		m_propItem1 = NULL;
	}
		
	if(m_propItem2)
	{
		delete m_propItem2;
		m_propItem2 = NULL;
	}
}

void CPcfDlgAttribute::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPcfDlgAttribute)
	DDX_Control(pDX, IDC_LISTKEY, m_listkey);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPcfDlgAttribute, CDialog)
	//{{AFX_MSG_MAP(CPcfDlgAttribute)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPcfDlgAttribute message handlers

BOOL CPcfDlgAttribute::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_propItem1 = new CPropertyItem("开始地址 0X","",PIT_EDIT,"");
	m_listkey.AddPropItem(m_propItem1);
	
	m_propItem2 = new CPropertyItem("结束地址 0X","",PIT_EDIT,"");
	m_listkey.AddPropItem(m_propItem2);	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPcfDlgAttribute::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	CRect r;
   	GetClientRect(&r);
	
	if(m_listkey.m_hWnd)
	{
		m_listkey.SetWindowPos(&wndTop,10,10,r.Width()-10,r.Height()-20,SWP_SHOWWINDOW);
	}	
}

BOOL CPcfDlgAttribute::PreTranslateMessage(MSG* pMsg) 
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
