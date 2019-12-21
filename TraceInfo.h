#if !defined(AFX_TRACEINFO_H__6DD79BA2_90D8_4288_AD77_F4B553501363__INCLUDED_)
#define AFX_TRACEINFO_H__6DD79BA2_90D8_4288_AD77_F4B553501363__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TraceInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTraceInfo dialog

class CTraceInfo : public CDialog
{
  // Construction
public:
  CTraceInfo(CWnd* pParent = NULL);   // standard constructor
  
  // Dialog Data
  //{{AFX_DATA(CTraceInfo)
  enum { IDD = IDD_DLG_TRACEINFO };
  CString	m_strTraceInfo;
  //}}AFX_DATA
  
  
  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CTraceInfo)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL
  
  // Implementation
protected:
  
  // Generated message map functions
  //{{AFX_MSG(CTraceInfo)
  virtual void OnOK();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRACEINFO_H__6DD79BA2_90D8_4288_AD77_F4B553501363__INCLUDED_)
