#if !defined(AFX_DLGREGISTER_H__6B4B78A2_5390_4A63_A9E9_DBAD35FFE7E2__INCLUDED_)
#define AFX_DLGREGISTER_H__6B4B78A2_5390_4A63_A9E9_DBAD35FFE7E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRegister.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRegister dialog

class CDlgRegister : public CDialog
{
  // Construction
public:
  CDlgRegister(CWnd* pParent = NULL);   // standard constructor
  
  // Dialog Data
  //{{AFX_DATA(CDlgRegister)
  enum { IDD = IDD_DLG_REGISTER };
  CString	m_strName;
  CString	m_strCompany;
  CString	m_strTelephone;
  CString	m_strMail;
  //}}AFX_DATA
  
  
  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CDlgRegister)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL
  
  // Implementation
protected:
  
  // Generated message map functions
  //{{AFX_MSG(CDlgRegister)
  virtual void OnOK();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGREGISTER_H__6B4B78A2_5390_4A63_A9E9_DBAD35FFE7E2__INCLUDED_)
