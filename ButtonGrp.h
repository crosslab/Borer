#if !defined(AFX_BUTTONGRP_H__CBFE342E_B0B1_11D2_AB9F_C08456C10000__INCLUDED_)
#define AFX_BUTTONGRP_H__CBFE342E_B0B1_11D2_AB9F_C08456C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ButtonGrp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CButtonGrp window
#include "CJFlatButton.h"

class CButtonGrp : public CStatic
{
  // Construction
public:
  CButtonGrp();
  
  // Attributes
public:
  CCJFlatButton m_btn1;
  CCJFlatButton m_btn2;
  CCJFlatButton m_btn3;
  CCJFlatButton m_btn4;
  
  CImageList   m_ImgTool;
  CToolTipCtrl m_tooltip;
  bool         m_filefix;
  
  // Operations
public:
  
  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CButtonGrp)
public:
  virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
  virtual void PreSubclassWindow();
  //}}AFX_VIRTUAL
  
  // Implementation
public:
  virtual ~CButtonGrp();
  
  // Generated message map functions
protected:
  //{{AFX_MSG(CButtonGrp)
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnButton1();
  afx_msg void OnButton2();
  afx_msg void OnButton3();
  afx_msg void OnButton4();
  //}}AFX_MSG
  
  DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUTTONGRP_H__CBFE342E_B0B1_11D2_AB9F_C08456C10000__INCLUDED_)
