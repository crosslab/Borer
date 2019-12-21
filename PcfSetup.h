#if !defined(AFX_PCFSETUP_H__A284C1B3_E70C_45A8_85F5_557545DA4EB4__INCLUDED_)
#define AFX_PCFSETUP_H__A284C1B3_E70C_45A8_85F5_557545DA4EB4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PcfSetup.h : header file
//
#include "HexEdit.h"
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CPcfSetup dialog

class CPcfSetup : public CDialog
{
// Construction
public:
	CPcfSetup(CWnd* pParent = NULL);   // standard constructor
  
	CString m_strFile;

	void ReadPcfs();
	void MarkPcfs();

// Dialog Data
	//{{AFX_DATA(CPcfSetup)
	enum { IDD = IDD_PCF_SETUP };
	CHexEdit	m_StartCtrl;
	CHexEdit	m_EndCtrl;
	CString	m_EndAddr;
	CString	m_StartAddr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPcfSetup)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPcfSetup)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	UINT m_OldEndAddr;
	UINT m_OldStartAddr;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PCFSETUP_H__A284C1B3_E70C_45A8_85F5_557545DA4EB4__INCLUDED_)
