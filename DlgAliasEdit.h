#if !defined(AFX_DLGALIASEDIT_H__C66329BD_E7AF_4DA3_B43C_E1F2A1789E50__INCLUDED_)
#define AFX_DLGALIASEDIT_H__C66329BD_E7AF_4DA3_B43C_E1F2A1789E50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAliasEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAliasEdit dialog
class CDlgAliasEdit : public CDialog
{
  // Construction
public:
  CDlgAliasEdit(CWnd* pParent = NULL);   // standard constructor
  
  // Dialog Data
  //{{AFX_DATA(CDlgAliasEdit)
  enum { IDD = IDD_SET_ALIAS };
  CString	AE_name;
  //}}AFX_DATA
  
  
  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CDlgAliasEdit)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL
  
  // Implementation
protected:
  
  // Generated message map functions
  //{{AFX_MSG(CDlgAliasEdit)
		// NOTE: the ClassWizard will add member functions here
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALIASEDIT_H__C66329BD_E7AF_4DA3_B43C_E1F2A1789E50__INCLUDED_)
