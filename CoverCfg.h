#if !defined(AFX_COVERCFG_H__8A5E8DBD_C6AE_4941_BC61_90B914BA1B44__INCLUDED_)
#define AFX_COVERCFG_H__8A5E8DBD_C6AE_4941_BC61_90B914BA1B44__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CoverCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCoverCfg dialog

class CCoverCfg : public CDialog
{
// Construction
public:
	CCoverCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCoverCfg)
	enum { IDD = IDD_DLG_CFG };
	CString	m_sCfgName;
	CString	m_sMapFile;
	int		m_nPwr;
	int		m_nSnr;
	int		m_nSaveTime;
	CString	m_sHOFile;
	CString	m_sPUFile;
	CString	m_sReleaseFile;
	CString	m_sCfgNameMCU;
	int		m_nWarnTime;
	CString	m_sNoDataFile;
	CString	m_sChangeFreqFile;
	CString	m_sScanFreqFile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCoverCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCoverCfg)
	afx_msg void OnHcCfbrs();
	afx_msg void OnMapCfbrs();
	afx_msg void OnHcConfig();
	afx_msg void OnMapConfig();
	afx_msg void OnHoCfbrs();
	afx_msg void OnPuCfbrs();
	afx_msg void OnReleaseCfbrs();
	afx_msg void OnHcCfbrsmcu();
	afx_msg void OnHcConfigmcu();
	afx_msg void OnNodataCfbrs();
	afx_msg void OnScanfreqCfbrs();
	afx_msg void OnChangefreqCfbrs();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COVERCFG_H__8A5E8DBD_C6AE_4941_BC61_90B914BA1B44__INCLUDED_)
