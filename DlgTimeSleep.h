#if !defined(AFX_DLGTIMESLEEP_H__AC45A011_F6EB_4796_A38A_FC28D95D2F33__INCLUDED_)
#define AFX_DLGTIMESLEEP_H__AC45A011_F6EB_4796_A38A_FC28D95D2F33__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTimeSleep.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgTimeSleep dialog

class DlgTimeSleep : public CDialog
{
	// Construction
public:
	DlgTimeSleep(CWnd* pParent = NULL);   // standard constructor
	
	// Dialog Data
	//{{AFX_DATA(DlgTimeSleep)
	enum { IDD = IDD_DIALOGTIMESLEEP };
	int		m_inttimesleep;
	int		m_intsendtimes;
	int		m_nGetValue;
	int		m_nKeepTime;
	//}}AFX_DATA
	
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgTimeSleep)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(DlgTimeSleep)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTIMESLEEP_H__AC45A011_F6EB_4796_A38A_FC28D95D2F33__INCLUDED_)
