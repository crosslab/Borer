#if !defined(AFX_CFGLIST_H__DFE79B5E_C1F5_4664_9492_C2FF33C13337__INCLUDED_)
#define AFX_CFGLIST_H__DFE79B5E_C1F5_4664_9492_C2FF33C13337__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CfgList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCfgList window
#include "EditList.h"
class CCfgList : public CEditList
{
// Construction
public:
	CCfgList();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCfgList)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCfgList();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCfgList)
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CFGLIST_H__DFE79B5E_C1F5_4664_9492_C2FF33C13337__INCLUDED_)
