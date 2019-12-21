#if !defined(AFX_TASKDEFINITION_H__F62FF44D_4295_48C5_9DC3_5D917BD553A8__INCLUDED_)
#define AFX_TASKDEFINITION_H__F62FF44D_4295_48C5_9DC3_5D917BD553A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TaskDefinition.h : header file
//
#include "PropertyList.h"
/////////////////////////////////////////////////////////////////////////////
// CTaskDefinition dialog

class CTaskDefinition : public CDialog
{
  // Construction
public:
  CTaskDefinition(CWnd* pParent = NULL);   // standard constructor
  virtual ~CTaskDefinition();
  // Dialog Data
  //{{AFX_DATA(CTaskDefinition)
  enum { IDD = IDD_DLGTASK };
  CPropertyList	m_listTask;
  //}}AFX_DATA
  
  
  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CTaskDefinition)
public:
  virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL
  
  // Implementation
protected:
  
  // Generated message map functions
  //{{AFX_MSG(CTaskDefinition)
  virtual BOOL OnInitDialog();
  afx_msg void OnSize(UINT nType, int cx, int cy);
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
private:
  CPropertyItem *propItem1,*propItem2;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TASKDEFINITION_H__F62FF44D_4295_48C5_9DC3_5D917BD553A8__INCLUDED_)
