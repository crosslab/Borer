#if !defined(AFX_LISTHEADER_H__D1019492_718C_471D_832E_ADBC6ACA525F__INCLUDED_)
#define AFX_LISTHEADER_H__D1019492_718C_471D_832E_ADBC6ACA525F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CListHeader window
class CListHeader : public CHeaderCtrl
{
  // Construction
public:
  CListHeader();
  
  // Attributes
public:
  CPoint      m_pt;           // point where right click took place.
  int         m_nSortedCol;   // index of currently selected column
  
  // Operations
public:
  virtual int HitTest(CPoint pt ) const;
  void  SendNotify(int iIndex,int aButton);
  
  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CListHeader)
  //}}AFX_VIRTUAL
  
  // Implementation
public:
  virtual ~CListHeader();
  
  // Generated message map functions
protected:
  //{{AFX_MSG(CListHeader)
  afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnLstAll();
  afx_msg void OnLstHide();
  
  //}}AFX_MSG
  
  DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTHEADER_H__D1019492_718C_471D_832E_ADBC6ACA525F__INCLUDED_)
