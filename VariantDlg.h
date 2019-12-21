#if !defined(AFX_VARIANTDLG_H__384AB1E3_00D1_4869_A75F_E5AA6FB8C1CF__INCLUDED_)
#define AFX_VARIANTDLG_H__384AB1E3_00D1_4869_A75F_E5AA6FB8C1CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VariantDlg.h : header file
//
#include "PropertyList.h"
/////////////////////////////////////////////////////////////////////////////
// CVariantDlg dialog

class CVariantDlg : public CDialog
{
// Construction
public:
	CVariantDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CVariantDlg();
// Dialog Data
	//{{AFX_DATA(CVariantDlg)
	enum { IDD = IDD_DLGVARIANT };
	CPropertyList	m_listvariant;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVariantDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVariantDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CPropertyItem *propItem1,*propItem2,*propItem3,*propItem4,*propItem5;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VARIANTDLG_H__384AB1E3_00D1_4869_A75F_E5AA6FB8C1CF__INCLUDED_)
