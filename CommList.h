#if !defined(AFX_COMMLIST_H__A08AF1B7_190E_4429_8E58_9C9728A69BB7__INCLUDED_)
#define AFX_COMMLIST_H__A08AF1B7_190E_4429_8E58_9C9728A69BB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CommList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCommList window

class CCommList : public CListCtrl
{
  // Construction
public:
  CCommList();
  
  // Attributes
public:
  
  // Operations
public:
  
  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CCommList)
  //}}AFX_VIRTUAL
  
  // Implementation
public:
  virtual ~CCommList();
  
  // Generated message map functions
protected:
  //{{AFX_MSG(CCommList)
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
  afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
  afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
  //}}AFX_MSG
  
  DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMLIST_H__A08AF1B7_190E_4429_8E58_9C9728A69BB7__INCLUDED_)
