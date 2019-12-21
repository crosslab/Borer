#if !defined(AFX_HEXEDIT_H__1BACE790_75CA_436E_91FF_20F6E50C26D9__INCLUDED_)
#define AFX_HEXEDIT_H__1BACE790_75CA_436E_91FF_20F6E50C26D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HexEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHexEdit window

class CHexEdit : public CEdit
{
  // Construction
public:
  CHexEdit();
  
  // Attributes
public:
  void SetMaxNum(int num);
  UINT GetIntValue();
  // Operations
public:
  
  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CHexEdit)
public:
  virtual BOOL PreTranslateMessage(MSG* pMsg);
  //}}AFX_VIRTUAL
  
  // Implementation
public:
  virtual ~CHexEdit();
  
  // Generated message map functions
protected:
  //{{AFX_MSG(CHexEdit)
		// NOTE - the ClassWizard will add and remove member functions here.
  //}}AFX_MSG
  
  DECLARE_MESSAGE_MAP()
private:
  int	m_MaxNum;
  UINT ChangeStrToHex(CString* pstr);
  
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HEXEDIT_H__1BACE790_75CA_436E_91FF_20F6E50C26D9__INCLUDED_)
