// HexEdit.cpp : implementation file
//

#include "stdafx.h"

#include "HexEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHexEdit

CHexEdit::CHexEdit()
:m_MaxNum(4)

{
}

CHexEdit::~CHexEdit()
{
}

BEGIN_MESSAGE_MAP(CHexEdit, CEdit)
//{{AFX_MSG_MAP(CHexEdit)
// NOTE - the ClassWizard will add and remove mapping macros here.
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHexEdit message handlers

BOOL CHexEdit::PreTranslateMessage(MSG* pMsg) 
{
  // TODO: Add your specialized code here and/or call the base class
  CString temp;
  if(pMsg->message==WM_KEYDOWN)
  {
    
    if((pMsg->wParam >=0x23 && pMsg->wParam <= 0x28) ||pMsg->wParam == VK_TAB||pMsg->wParam == VK_DELETE||pMsg->wParam == VK_BACK)
      return CEdit::PreTranslateMessage(pMsg);
    
    if((pMsg->wParam >= 30 && pMsg->wParam <= 0x39) ||
      (pMsg->wParam >=0x41 && pMsg->wParam <= 0x46))
    {
      GetWindowText(temp);
      if(m_MaxNum > temp.GetLength())
        return CEdit::PreTranslateMessage(pMsg);
    }
    
    return 1;
  }	
  return CEdit::PreTranslateMessage(pMsg);
}

void CHexEdit::SetMaxNum(int num)
{
  m_MaxNum = num;
}
UINT CHexEdit::ChangeStrToHex(CString* pstr)
{
  
  char NumStr[255];
  
  char   *stopstring;
  
  sprintf(NumStr,"%s",*pstr);
  
  return strtoul(NumStr, &stopstring, 16);
}
UINT CHexEdit::GetIntValue()
{
  CString temp;
  GetWindowText(temp);
  if(temp.GetLength() <= 8 )
    return ChangeStrToHex(&temp);
  return 0;
}