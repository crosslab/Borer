#if !defined(AFX_TESTTASK_H__A769CCCB_2782_43B1_9584_761646BFA39F__INCLUDED_)
#define AFX_TESTTASK_H__A769CCCB_2782_43B1_9584_761646BFA39F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestTask.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestTask dialog

class CTestTask : public CDialog
{
  // Construction
public:
  CTestTask(CWnd* pParent = NULL);   // standard constructor
  
  // Dialog Data
  //{{AFX_DATA(CTestTask)
  enum { IDD = IDD_DLG_TESTTASK };
  CListCtrl	m_listTestTask;
  //}}AFX_DATA
  
  
  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CTestTask)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL
  
  // Implementation
protected:
  
  // Generated message map functions
  //{{AFX_MSG(CTestTask)
  virtual BOOL OnInitDialog();
  virtual void OnOK();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTTASK_H__A769CCCB_2782_43B1_9584_761646BFA39F__INCLUDED_)
