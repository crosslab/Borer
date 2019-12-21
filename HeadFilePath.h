#if !defined(AFX_HEADFILEPATH_H__DBA84111_4025_4147_A86C_E0D1B6EBAFEB__INCLUDED_)
#define AFX_HEADFILEPATH_H__DBA84111_4025_4147_A86C_E0D1B6EBAFEB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HeadFilePath.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHeadFilePath dialog

class CHeadFilePath : public CDialog
{
  // Construction
public:
  CHeadFilePath(CWnd* pParent = NULL);   // standard constructor
  
  // Dialog Data
  //{{AFX_DATA(CHeadFilePath)
  enum { IDD = IDD_DLGHEADPATH };
  CString	m_strHeadPath;
  //}}AFX_DATA
  
  
  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CHeadFilePath)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL
  
  // Implementation
protected:
  
  // Generated message map functions
  //{{AFX_MSG(CHeadFilePath)
  afx_msg void OnBtnheadpath();
  virtual BOOL OnInitDialog();
  virtual void OnOK();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HEADFILEPATH_H__DBA84111_4025_4147_A86C_E0D1B6EBAFEB__INCLUDED_)
