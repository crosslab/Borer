// MyListBox.cpp : implementation file
//

#include "stdafx.h"

#include "MyListBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyListBox

CMyListBox::CMyListBox()
{
}

CMyListBox::~CMyListBox()
{
}


BEGIN_MESSAGE_MAP(CMyListBox, CListBox)
//{{AFX_MSG_MAP(CMyListBox)
// NOTE - the ClassWizard will add and remove mapping macros here.
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyListBox message handlers
int CMyListBox::AddString( LPCTSTR lpszItem )
{
  int Count = this->GetCount();
  CString temp;
  
  
  if(Count > 0)
  {
    long AddItem = GetDataHexHeader(lpszItem );
    for(int i=0; i<Count;i++)
    {
      CString NumStr;
      GetText(i,NumStr);
      if(CompareDataHexHeader(NumStr, AddItem))
        return InsertString(i,lpszItem);
    }
  }
  
  return CListBox::AddString(lpszItem);
}

BOOL CMyListBox::CompareDataHexHeader(LPCTSTR lpszItem,long AddItem)
{
  return (GetDataHexHeader(lpszItem) >= AddItem);
}
long CMyListBox::GetDataHexHeader(LPCTSTR lpszItem )
{
  CString temp;
  char NumStr[255];
  
  char   *stopstring;
  temp.Format("%s",lpszItem);
  
  sprintf(NumStr,"%s",temp.Left(temp.Find(" ")));
  
  return strtol(NumStr, &stopstring, 16);
}
