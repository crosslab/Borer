#if !defined(AFX_GOLINE_H__681C4F20_9B8E_4E18_A28C_CAD58A0BC2E5__INCLUDED_)
#define AFX_GOLINE_H__681C4F20_9B8E_4E18_A28C_CAD58A0BC2E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GoLine.h : header file
//
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CGoLine dialog

class CGoLine : public CDialog
{
  // Construction
public:
  CGoLine(CWnd* pParent = NULL);   // standard constructor
  
  // Dialog Data
  //{{AFX_DATA(CGoLine)
  enum { IDD = IDD_DLG_GOLINE };
  CEdit	m_cCtrlEdit;
  int		m_nLine;
  //}}AFX_DATA
  
  
  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CGoLine)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL
  
  // Implementation
protected:
  
  // Generated message map functions
  //{{AFX_MSG(CGoLine)
  virtual BOOL OnInitDialog();
  afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GOLINE_H__681C4F20_9B8E_4E18_A28C_CAD58A0BC2E5__INCLUDED_)
