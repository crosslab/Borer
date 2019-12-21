#if !defined(AFX_PORTTAB_H__07AB2331_108B_471A_B23B_7A2A8DF173BC__INCLUDED_)
#define AFX_PORTTAB_H__07AB2331_108B_471A_B23B_7A2A8DF173BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPortTab window
class CPortTab : public CSTabCtrl
{
  // Construction
public:
  CPortTab();
  
  // Attributes
public:
  
  // Operations
public:
  
  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CPortTab)
  //}}AFX_VIRTUAL
  
  // Implementation
public:
  virtual ~CPortTab();
  
  // Generated message map functions
protected:
  //{{AFX_MSG(CPortTab)
		// NOTE - the ClassWizard will add and remove member functions here.
  //}}AFX_MSG
  afx_msg void OnCustomdrawPortList(NMHDR*, LRESULT*);
  DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PORTTAB_H__07AB2331_108B_471A_B23B_7A2A8DF173BC__INCLUDED_)
