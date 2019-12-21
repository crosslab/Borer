#if !defined(AFX_AUTOSENDMESSAGE_H__1B6C4B82_839B_4193_AA33_080E84D66727__INCLUDED_)
#define AFX_AUTOSENDMESSAGE_H__1B6C4B82_839B_4193_AA33_080E84D66727__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AutoSendMessage.h : header file
//
#include "PropertyList.h"
/////////////////////////////////////////////////////////////////////////////
// AutoSendMessage dialog

class AutoSendMessage : public CDialog
{
// Construction
public:
	AutoSendMessage(CWnd* pParent = NULL);   // standard constructor
	virtual ~AutoSendMessage();
// Dialog Data
	//{{AFX_DATA(AutoSendMessage)
	enum { IDD = IDD_DLGAUTOSEND };
	CPropertyList	m_listautosend;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AutoSendMessage)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CPropertyItem *propItem1,*propItem2;
	// Generated message map functions
	//{{AFX_MSG(AutoSendMessage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOSENDMESSAGE_H__1B6C4B82_839B_4193_AA33_080E84D66727__INCLUDED_)
