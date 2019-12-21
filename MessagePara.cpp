#include "stdafx.h"
#include "Borer.h"
#include "MessagePara.h"
#include "MainFrm.h"
#include "BorerDoc.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void middle_string(char *origin,char *from,char *to,char *result);
/////////////////////////////////////////////////////////////////////////////
// CMessagePara dialog
CMessagePara::CMessagePara(CWnd* pParent /*=NULL*/)
: CDialog(CMessagePara::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMessagePara)
	m_strmessage = _T("");
	//}}AFX_DATA_INIT
}


void CMessagePara::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMessagePara)
	DDX_Control(pDX, IDC_EDITMESSAGE, m_EdMessage);
	DDX_Control(pDX, IDC_COMBOMESSAGENAME, m_ComboMessage);
	DDX_Text(pDX, IDC_EDITMESSAGE, m_strmessage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMessagePara, CDialog)
//{{AFX_MSG_MAP(CMessagePara)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMessagePara message handlers

//界面初始化，读取参数
BOOL CMessagePara::OnInitDialog() 
{
	CDialog::OnInitDialog();
	if(1==m_itype)
	{ 
		m_EdMessage.ShowWindow(SW_HIDE);
		m_ComboMessage.ShowWindow(SW_SHOW);
		for(int j=0; j<m_attrib.contenttotalnum; j++)
		{
			m_ComboMessage.AddString(m_attrib.content[j].name);
		}
		if(m_nWaitMsg)
		{
			m_ComboMessage.AddString("*");
		}
		int nCount = m_ComboMessage.GetCount();
		if (nCount > 0)
		{
			m_ComboMessage.SetCurSel(0);
		}
	}
	if(2==m_itype)
	{
		m_EdMessage.ShowWindow(SW_SHOW);
        m_ComboMessage.ShowWindow(SW_HIDE);
	}
	if(3==m_itype)
	{
		m_EdMessage.ShowWindow(SW_SHOW);
        m_ComboMessage.ShowWindow(SW_HIDE);
	}

	if(strlen(m_attrib.description) != 0)
	{
		 GetDlgItem(IDC_DESCRIPTION)->SetWindowText(m_attrib.description);
		 if((m_itype==3)||(m_itype==2))
		 {
			 char strcontent[200];
			 memset(strcontent,0,sizeof(strcontent));
			 middle_string(m_attrib.description,"[","]",strcontent);
			 m_strmessage.Format("%s",strcontent);
			 UpdateData(false);
		 }
	}
	else
	{
		GetDlgItem(IDC_DESCRIPTION)->SetWindowText("");
	}


	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

//设置仿真消息参数
void CMessagePara::OnOK() 
{
	CFrameWnd *pMyFrm=((CMainFrame*)AfxGetMainWnd())->GetActiveFrame();
    if(!pMyFrm) {
	   return ;
	}

	CView *pMyView=pMyFrm->GetActiveView();
    if(!pMyView) {
	   return ;
	}
	
	CBorerDoc  *pMyDoc=(CBorerDoc*) pMyView->GetDocument();
	// TODO: Add extra validation here
	///发消息	
	int ilength;
	int i;
	int tsleep=0;//解析出时间延时
	UpdateData(TRUE);
	if(1==m_itype)
	{
		int iseleted;
		CString tempstr;
		iseleted=m_ComboMessage.GetCurSel();
		if(iseleted<0)
		{
			AfxMessageBox("请选择参数");
			return;
		}
		m_ComboMessage.GetLBText(iseleted,tempstr);
		if(tempstr.Compare("*")==0)
		{
			pMyDoc->m_paraDefi->m_MsgAttrib.msg_attrib[g_CurIndex].msg.Union.content[0]= '*';
			
		}
		else
		{
			pMyDoc->m_paraDefi->m_MsgAttrib.msg_attrib[g_CurIndex].msg.Union.content[0]= m_attrib.content[iseleted].code;
		}
		pMyDoc->m_paraDefi->m_MsgAttrib.msg_attrib[g_CurIndex].msg.length = 1;
	}
	else if(2==m_itype)
	{
		
		ilength=m_strmessage.GetLength();
		if(ilength==0)
		{
			AfxMessageBox("请输入参数");
			return ;
		}
		if((m_strmessage.Find("*")!=-1) && m_nWaitMsg)
		{
			pMyDoc->m_paraDefi->m_MsgAttrib.msg_attrib[g_CurIndex].msg.Union.content[0]='*';
			pMyDoc->m_paraDefi->m_MsgAttrib.msg_attrib[g_CurIndex].msg.length = 1;
		}
		else
		{
			for(i=0;i<ilength;i++)
			{
				if((m_strmessage[i]=='?') && m_nWaitMsg)
				{
					pMyDoc->m_paraDefi->m_MsgAttrib.msg_attrib[g_CurIndex].msg.Union.content[i]='?';
				}
				else
				{
					pMyDoc->m_paraDefi->m_MsgAttrib.msg_attrib[g_CurIndex].msg.Union.content[i]= m_strmessage[i]-48;
				}
			}
			pMyDoc->m_paraDefi->m_MsgAttrib.msg_attrib[g_CurIndex].msg.Union.content[i]=0;
			pMyDoc->m_paraDefi->m_MsgAttrib.msg_attrib[g_CurIndex].msg.length = ilength;
		}
	}
	else if(3==m_itype)
	{
		CString strContent;
		int nStart=0;
		int nFind=-1;
		int nSum=0;
		char   *stopstring;
		int iNumber=m_attrib.conentlength;
		
		m_strmessage.MakeUpper();
		if((m_strmessage.Find("*")!=-1) && m_nWaitMsg)
		{
			pMyDoc->m_paraDefi->m_MsgAttrib.msg_attrib[g_CurIndex].msg.Union.content[0]='*';
			pMyDoc->m_paraDefi->m_MsgAttrib.msg_attrib[g_CurIndex].msg.length = 1;
			
		}
		else
		{
			
			nFind=m_strmessage.Find("0X");
			while(nFind>=0)
			{
				nFind=m_strmessage.Find("0X",nStart);
				if(nFind>=0)
				{
					strContent=m_strmessage.Mid(nFind,4);
					if((strContent.Compare("0X??")==0) && m_nWaitMsg)
					{
						pMyDoc->m_paraDefi->m_MsgAttrib.msg_attrib[g_CurIndex].msg.Union.content[nSum]='?';
					}
					else
					{
						pMyDoc->m_paraDefi->m_MsgAttrib.msg_attrib[g_CurIndex].msg.Union.content[nSum]=(int) strtol(strContent,&stopstring, 0 );
					}
					nStart=nFind+4;
					nSum++;
				}
	    	/*	if(nSum>iNumber)
				{
				nFind=-1;
			}*/
			}
	  /*	if(nSum<iNumber)
			{
			AfxMessageBox("参数不够");
			return ;
		}*/
			pMyDoc->m_paraDefi->m_MsgAttrib.msg_attrib[g_CurIndex].msg.length = nSum;
		}
	}
	CDialog::OnOK();
}

