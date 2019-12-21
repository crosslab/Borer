#include "stdafx.h"
#include "PcfSetup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPcfSetup dialog
CPcfSetup::CPcfSetup(CWnd* pParent /*=NULL*/)
	: CDialog(CPcfSetup::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPcfSetup)
	m_EndAddr = _T("");
	m_StartAddr = _T("");
	//}}AFX_DATA_INIT
}

void CPcfSetup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPcfSetup)
	DDX_Control(pDX, IDC_EDIT_STARTADDR, m_StartCtrl);
	DDX_Control(pDX, IDC_EDIT_ENDADDR, m_EndCtrl);
	DDX_Text(pDX, IDC_EDIT_ENDADDR, m_EndAddr);
	DDX_Text(pDX, IDC_EDIT_STARTADDR, m_StartAddr);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPcfSetup, CDialog)
	//{{AFX_MSG_MAP(CPcfSetup)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPcfSetup message handlers
BOOL CPcfSetup::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_StartCtrl.SetMaxNum(8);
	m_EndCtrl.SetMaxNum(8);

	ReadPcfs();

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPcfSetup::ReadPcfs() 
{	
	UINT temp = 0;

	temp = ReadIniInt("RFC","StartAddr",0,m_strFile);
	m_StartAddr.Format("%08X",temp);
	m_OldStartAddr = temp;

	temp = ReadIniInt("RFC","EndAddr",0,m_strFile);
	m_EndAddr.Format("%08X",temp);
	m_OldEndAddr = temp;
}

void CPcfSetup::MarkPcfs() 
{
	char temp[10];

	sprintf(temp,"0x%X",m_OldStartAddr);
	WritePrivateProfileString("RFC","StartAddr",temp,m_strFile);

	sprintf(temp,"0x%X",m_OldEndAddr);
	WritePrivateProfileString("RFC","EndAddr",temp,m_strFile);
}

void CPcfSetup::OnCancel() 
{
	if((m_OldEndAddr != m_EndCtrl.GetIntValue()) ||
	   (m_OldStartAddr != m_StartCtrl.GetIntValue())) {
	   if(m_StartCtrl.GetIntValue() >  m_EndCtrl.GetIntValue()) {
			AfxMessageBox("注意起始地址小于终止地址 !");
			return;
	   }

	   CFileDialog dlg(false,"",m_strFile,OFN_HIDEREADONLY,"ini Files (*.ini)|*.ini|All Files (*.*)|*.*||");
	   dlg.m_ofn.lpstrTitle ="保存修改？";

	   if(dlg.DoModal() == IDOK) {
			m_strFile=dlg.GetPathName();
            m_OldStartAddr =m_StartCtrl.GetIntValue();
            m_OldEndAddr =m_EndCtrl.GetIntValue();
			MarkPcfs();
	   }
	}

	CDialog::OnCancel();
}

