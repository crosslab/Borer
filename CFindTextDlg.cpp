////////////////////////////////////////////////////////////////////////////
//	File:		CFindTextDlg.cpp
//	Version:	1.0.0.0
//	Created:	29-Dec-1998
//
//	Author:		Stcherbatchenko Andrei
//	E-mail:		windfall@gmx.de
//
//	Implementation of the CFindTextDlg dialog, a part of Crystal Edit -
//	syntax coloring text editor.
//
//	You are free to use or modify this code to the following restrictions:
//	- Acknowledge me somewhere in your about box, simple "Parts of code by.."
//	will be enough. If you can't (or don't want to), contact me personally.
//	- LEAVE THIS HEADER INTACT
////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CFindTextDlg.h"
#include "CCrystalTextView.h"
#include "RichTips.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFindTextDlg dialog
CFindTextDlg::CFindTextDlg(CCrystalTextView *pBuddy) : CDialog(CFindTextDlg::IDD, NULL)
{
  m_pChum = pBuddy;
  m_pChap = NULL;
  
  //{{AFX_DATA_INIT(CFindTextDlg)
  m_nDirection = 1;
  m_bMatchCase = FALSE;
  m_bWholeWord = FALSE;
  m_sTarText = _T("");
  //}}AFX_DATA_INIT
  m_ptCurPos = (0, 0);
}

CFindTextDlg::CFindTextDlg(CRichTips *pBuddy) : CDialog(CFindTextDlg::IDD, NULL)
{
  m_pChap = pBuddy;
  m_pChum = NULL;
  
  //{{AFX_DATA_INIT(CFindTextDlg)
  m_nDirection = 1;
  m_bMatchCase = FALSE;
  m_bWholeWord = FALSE;
  m_sTarText = _T("");
  //}}AFX_DATA_INIT
  m_ptCurPos = (0, 0);
}

void CFindTextDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CFindTextDlg)
  DDX_Radio(pDX, IDC_EDIT_DIRECTION_UP, m_nDirection);
  DDX_Check(pDX, IDC_EDIT_MATCH_CASE, m_bMatchCase);
  DDX_Text(pDX, IDC_EDIT_TEXT, m_sTarText);
  DDX_Check(pDX, IDC_EDIT_WHOLE_WORD, m_bWholeWord);
  //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFindTextDlg, CDialog)
//{{AFX_MSG_MAP(CFindTextDlg)
ON_EN_CHANGE(IDC_EDIT_TEXT, OnChangeEditText)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFindTextDlg message handlers

void CFindTextDlg::OnOK() 
{
  if(!UpdateData()) {
    return;
  }
  
  if(m_pChum) {
    DWORD dwSearchFlags = 0;
    if (m_bMatchCase)
      dwSearchFlags |= FIND_MATCH_CASE;
    if (m_bWholeWord)
      dwSearchFlags |= FIND_WHOLE_WORD;
    if (m_nDirection == 0)
      dwSearchFlags |= FIND_DIRECTION_UP;
    
    CPoint ptTextPos;
    if (! m_pChum->DivulgeText(m_sTarText, m_ptCurPos, dwSearchFlags, TRUE, &ptTextPos))
    {
      CString prompt;
      prompt.Format(IDS_EDIT_TEXT_NOT_FOUND, m_sTarText);
      AfxMessageBox(prompt);
      m_ptCurPos = CPoint(0, 0);
      return;
    }
    
    m_pChum->HighlightText(ptTextPos, lstrlen(m_sTarText));
  }else {
    DWORD dwSearchFlags = 0;
    if (m_bMatchCase)
      dwSearchFlags |= FR_MATCHCASE;
    if (m_bWholeWord)
      dwSearchFlags |= FR_WHOLEWORD;
    if (m_nDirection == 0)
      dwSearchFlags |= FR_DOWN;
    
    // Set the selection to be the first occurrence of the 
    // string lpszmyString, if it is found.   
    FINDTEXTEX ft;
    ft.chrg.cpMin = m_ptCurPos.x;
    ft.chrg.cpMax = -1;
    ft.lpstrText = m_sTarText.GetBuffer(m_sTarText.GetLength());
    
    m_ptCurPos.x =m_pChap->FindText(dwSearchFlags,&ft);
    m_sTarText.ReleaseBuffer();
    
    if (m_ptCurPos.x==-1)
    {
      CString prompt;
      prompt.Format(IDS_EDIT_TEXT_NOT_FOUND, m_sTarText);
      AfxMessageBox(prompt);
      m_ptCurPos.x =0x00;
      return;
    }
    
    m_pChap->SetSel(m_ptCurPos.x, m_ptCurPos.x +lstrlen(m_sTarText));
  }
		
  CDialog::OnOK();
}

void CFindTextDlg::OnChangeEditText() 
{
  CString text;
  GetDlgItem(IDC_EDIT_TEXT)->GetWindowText(text);
  GetDlgItem(IDOK)->EnableWindow(text != _T(""));
}

BOOL CFindTextDlg::OnInitDialog() 
{
  CDialog::OnInitDialog();
  
  GetDlgItem(IDOK)->EnableWindow(m_sTarText != _T(""));
  
  return TRUE;
}

void CFindTextDlg::OnCancel() 
{
  VERIFY(UpdateData());
  
  CDialog::OnCancel();
}
