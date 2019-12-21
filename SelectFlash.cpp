// SelectFlash.cpp : implementation file
//

#include "stdafx.h"
#include "Borer.h"
#include "SelectFlash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectFlash dialog


CSelectFlash::CSelectFlash(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectFlash::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelectFlash)
	m_strFlashFile = _T("");
	//}}AFX_DATA_INIT
}


void CSelectFlash::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectFlash)
	DDX_Text(pDX, IDC_EDIT1, m_strFlashFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectFlash, CDialog)
	//{{AFX_MSG_MAP(CSelectFlash)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectFlash message handlers

void CSelectFlash::OnButton1() 
{
	// TODO: Add your control notification handler code here
	
    CFileDialog dlg(true,"","",NULL,"flash Files (*.fls)|*.fls|All Files (*.*)|*.*||");

	if(dlg.DoModal() == IDOK)
	{
		m_strFlashFile = dlg.GetPathName();
		UpdateData(false);
	}		

}
