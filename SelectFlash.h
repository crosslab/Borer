#if !defined(AFX_SELECTFLASH_H__08BAE430_87D0_4782_BC19_FC5AE830B589__INCLUDED_)
#define AFX_SELECTFLASH_H__08BAE430_87D0_4782_BC19_FC5AE830B589__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectFlash.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelectFlash dialog

class CSelectFlash : public CDialog
{
  // Construction
public:
  CSelectFlash(CWnd* pParent = NULL);   // standard constructor
  
  // Dialog Data
  //{{AFX_DATA(CSelectFlash)
  enum { IDD = IDD_DLG_REEXCUTEPDK };
  CString	m_strFlashFile;
  //}}AFX_DATA
  
  
  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CSelectFlash)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL
  
  // Implementation
protected:
  
  // Generated message map functions
  //{{AFX_MSG(CSelectFlash)
  afx_msg void OnButton1();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTFLASH_H__08BAE430_87D0_4782_BC19_FC5AE830B589__INCLUDED_)
