#include "stdafx.h"
#include "Borer.h"
#include "AutoSendMessage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// AutoSendMessage dialog


AutoSendMessage::AutoSendMessage(CWnd* pParent /*=NULL*/)
	: CDialog(AutoSendMessage::IDD, pParent)
{
	//{{AFX_DATA_INIT(AutoSendMessage)
	propItem1 = NULL ;
	propItem2 = NULL ;

	//}}AFX_DATA_INIT
}
AutoSendMessage::~AutoSendMessage()
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
}

void AutoSendMessage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AutoSendMessage)
	DDX_Control(pDX, IDC_LIST1, m_listautosend);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(AutoSendMessage, CDialog)
	//{{AFX_MSG_MAP(AutoSendMessage)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AutoSendMessage message handlers

BOOL AutoSendMessage::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	propItem1 = new CPropertyItem("发送消息","",PIT_EDIT,"");
	m_listautosend.AddPropItem(propItem1);
	
	propItem2 = new CPropertyItem("发送间隔","",PIT_EDIT,"");
	m_listautosend.AddPropItem(propItem2);	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void AutoSendMessage::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	CRect r;
   	GetClientRect(&r);
	
	if(m_listautosend.m_hWnd)
	{
		m_listautosend.SetWindowPos(&wndTop,10,10,r.Width()-10,r.Height()-20,SWP_SHOWWINDOW);
	}		
}

BOOL AutoSendMessage::PreTranslateMessage(MSG* pMsg) 
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
