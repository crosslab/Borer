#if !defined(AFX_PCFDLGATTRIBUTE_H__160A966C_8C84_4F1F_AF1E_970D198EBDE1__INCLUDED_)
#define AFX_PCFDLGATTRIBUTE_H__160A966C_8C84_4F1F_AF1E_970D198EBDE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PcfDlgAttribute.h : header file
//
#include "PropertyList.h"
/////////////////////////////////////////////////////////////////////////////
// CPcfDlgAttribute dialog

class CPcfDlgAttribute : public CDialog
{
// Construction
public:
	CPcfDlgAttribute(CWnd* pParent = NULL);   // standard constructor
	~CPcfDlgAttribute();
// Dialog Data
	//{{AFX_DATA(CPcfDlgAttribute)
	enum { IDD = IDD_DLGPCFATTRIBUTE };
	CPropertyList	m_listkey;

		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPcfDlgAttribute)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPcfDlgAttribute)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CPropertyItem *m_propItem1 ;
	CPropertyItem *m_propItem2 ;
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PCFDLGATTRIBUTE_H__160A966C_8C84_4F1F_AF1E_970D198EBDE1__INCLUDED_)
