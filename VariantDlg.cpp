// VariantDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Borer.h"
#include "VariantDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVariantDlg dialog


CVariantDlg::CVariantDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVariantDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVariantDlg)
	propItem1 = NULL ;
	propItem2 = NULL ;
	propItem3 = NULL ;
	//}}AFX_DATA_INIT
}

CVariantDlg::~CVariantDlg()
{
	if(propItem1)
	{
		delete propItem1;
		propItem1 = NULL ;
	}
		
	if(propItem2)
	{
		delete propItem2;
		propItem2 = NULL ;
	}
		
	if(propItem3)
	{
		delete propItem3;
		propItem3 = NULL ;
	}
}

void CVariantDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVariantDlg)
	DDX_Control(pDX, IDC_LISTVARIANT, m_listvariant);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVariantDlg, CDialog)
	//{{AFX_MSG_MAP(CVariantDlg)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVariantDlg message handlers

BOOL CVariantDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	propItem1 = new CPropertyItem("变量名称","",PIT_EDIT,"");
	m_listvariant.AddPropItem(propItem1);
	
	propItem2 = new CPropertyItem("变量地址","",PIT_EDIT,"");
	m_listvariant.AddPropItem(propItem2);
	
	propItem3 = new CPropertyItem("变量长度","",PIT_EDIT,"");
	m_listvariant.AddPropItem(propItem3);	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CVariantDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	CRect r;
   	GetClientRect(&r);
	
	if(m_listvariant.m_hWnd)
	{
		m_listvariant.SetWindowPos(&wndTop,10,10,r.Width()-10,r.Height()-20,SWP_SHOWWINDOW);
	}	
}

BOOL CVariantDlg::PreTranslateMessage(MSG* pMsg) 
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
