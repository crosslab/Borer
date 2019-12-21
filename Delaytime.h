#if !defined(AFX_DELAYTIME_H__2DA56650_BDE4_425D_9463_ACD633E09126__INCLUDED_)
#define AFX_DELAYTIME_H__2DA56650_BDE4_425D_9463_ACD633E09126__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Delaytime.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDelaytime dialog

class CDelaytime : public CDialog
{
  // Construction
public:
  CDelaytime(CWnd* pParent = NULL);   // standard constructor
  
  // Dialog Data
  //{{AFX_DATA(CDelaytime)
  enum { IDD = IDD_DLG_DELAYTIME };
  int		m_nDelayTime; //—” ± ±º‰
  //}}AFX_DATA
  
  
  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CDelaytime)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL
  
  // Implementation
protected:
  
  // Generated message map functions
  //{{AFX_MSG(CDelaytime)
  virtual void OnOK();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DELAYTIME_H__2DA56650_BDE4_425D_9463_ACD633E09126__INCLUDED_)
