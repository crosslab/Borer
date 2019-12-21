#if !defined(AFX_COMMINFO_H__E9AD083C_4CDE_45D8_85AE_7B1C8BB56DD8__INCLUDED_)
#define AFX_COMMINFO_H__E9AD083C_4CDE_45D8_85AE_7B1C8BB56DD8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

extern char * gbl_szParity[];
extern char * gbl_szBaud[];
extern char * gbl_szStopBits[];

extern DWORD   BaudTable[];
extern char    ParityTable[];
extern char    StopBitsTable[];

extern DWORD   DTRControlTable[];
extern DWORD   RTSControlTable[];

/////////////////////////////////////////////////////////////////////////////
// CCommInfo dialog
class CCommInfo : public CDialog
{
  // Construction
public:
  CCommInfo(CWnd* pParent = NULL);   // standard constructor
  
  // Dialog Data
  //{{AFX_DATA(CCommInfo)
  enum { IDD = IDD_DIALOG_CFG };
  CSpinButtonCtrl	DP_pkt;
  CSpinButtonCtrl	DP_bulk;
  CSpinButtonCtrl	DP_mass;
  CComboBox	CI_sbits;
  CComboBox	CI_baud;
  CComboBox	CI_dbits;
  CComboBox	CI_parities;
  int		II_baud;
  int		II_dbits;
  int		II_parities;
  int		II_sbits;
  //}}AFX_DATA
  
  int CUE_port;
  int	II_mass;
  int	II_bulk;
  int	II_pkt;
  
  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CCommInfo)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL
  
  // Implementation
protected:
  
  // Generated message map functions
  //{{AFX_MSG(CCommInfo)
  virtual BOOL OnInitDialog();
  virtual void OnOK();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMINFO_H__E9AD083C_4CDE_45D8_85AE_7B1C8BB56DD8__INCLUDED_)
