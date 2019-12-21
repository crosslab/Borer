#if !defined(AFX_PROJECTTREE_H__CB36E040_D023_4B8E_9D72_C4F0367AB36D__INCLUDED_)
#define AFX_PROJECTTREE_H__CB36E040_D023_4B8E_9D72_C4F0367AB36D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProjectTree.h : header file
//
#include "edittree.h"

/////////////////////////////////////////////////////////////////////////////
// CProjectTree window
class CProjectTree : public CEditTreeCtrl
{
  // Construction
public:
  CProjectTree();
  
  // Attributes
public:
  void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
  BOOL ExecuteTree(HTREEITEM hti, OUTSIDE_PARAM op = OP_NONE);
  BOOL InitializeImageList();
  
  void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
  
  virtual HTREEITEM InsertPie(LPCTSTR lpszItem, 
    HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST);
  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CProjectTree)
  //}}AFX_VIRTUAL
  
  // Implementation
public:
  virtual ~CProjectTree();
  
  CStringArray m_qary;
  CString      m_qmod;
  
  // Generated message map functions
protected:
  //{{AFX_MSG(CProjectTree)
  afx_msg void OnItpExecute();
  afx_msg void OnItpBrowse();
  afx_msg void OnAddCchild();
  afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
  afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
  //}}AFX_MSG
  
  DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROJECTTREE_H__CB36E040_D023_4B8E_9D72_C4F0367AB36D__INCLUDED_)
