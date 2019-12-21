#if !defined(AFX_MYLISTBOX_H__0E6246EE_5C2F_46EE_9E03_723236A758AA__INCLUDED_)
#define AFX_MYLISTBOX_H__0E6246EE_5C2F_46EE_9E03_723236A758AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyListBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyListBox window

class CMyListBox : public CListBox
{
  // Construction
public:
  CMyListBox();
  
  // Attributes
public:
  
  // Operations
public:
  
  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CMyListBox)
  //}}AFX_VIRTUAL
  
  // Implementation
public:
  virtual ~CMyListBox();
  virtual int AddString( LPCTSTR lpszItem );
  // Generated message map functions
protected:
  //{{AFX_MSG(CMyListBox)
		// NOTE - the ClassWizard will add and remove member functions here.
  //}}AFX_MSG
  
  DECLARE_MESSAGE_MAP()
private:
  BOOL CompareDataHexHeader(LPCTSTR lpszItem,long AddItem);
  long GetDataHexHeader(LPCTSTR lpszItem );
  
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYLISTBOX_H__0E6246EE_5C2F_46EE_9E03_723236A758AA__INCLUDED_)
