#if !defined(AFX_TABTAB__CBE5CAE1_A0C7_478C_8F24_26978808159B__INCLUDED_)
#define AFX_TABTAB__CBE5CAE1_A0C7_478C_8F24_26978808159B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>

class CSTabCtrl : public CTabCtrl
{
  // Construction
public:
  CSTabCtrl();
  
  // Attributes
public:
  
  // Operations
public:
  bool    AddControl(CWnd *_pControl,CString &pszTabItems,
    INT _nIcon);
  bool    AddControl(CWnd *_pControl,char *pszLabel,
    INT _nIcon);
protected:
  
  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CSTabCtrl)
  //}}AFX_VIRTUAL
  
  // Implementation
public:
  virtual ~CSTabCtrl();
  virtual SetCurSel(int nItem);
  
  // Generated message map functions
protected:
  //{{AFX_MSG(CSTabCtrl)
  afx_msg BOOL OnSelchange(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnDestroy();
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnSize(UINT nType, int cx, int cy);
  //}}AFX_MSG
  
  DECLARE_MESSAGE_MAP()
    
private:
  CMap <INT, INT&,CList <CWnd *, CWnd *> *, CList<CWnd *, CWnd *> *> m_PageToCtrlListMap;
};

/////////////////////////////////////////////////////////////////////////////
#endif