#if !defined(AFX_CFutileData_H__92FE2C21_E4A7_11D5_983D_0050BA456CF7__INCLUDED_)
#define AFX_CFutileData_H__92FE2C21_E4A7_11D5_983D_0050BA456CF7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CFutileData.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFutileData dialog
class CFutileData : public CDialog
{
  // Construction
public:
  CFutileData(CWnd* pParent = NULL);   // standard constructor
  
  // Dialog Data
  //{{AFX_DATA(CFutileData)
  enum { IDD = IDD_DLG_HPCFG };
  CString	m_sCfgName;
  CString	m_strMcuFile;
  CString	m_strATFile;
  //}}AFX_DATA
  
  int          CUE_port;
  int          CUE_Index;
  int          CUE_Role;
  
  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CFutileData)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL
  
  // Implementation
protected:
  void  ShowRole(int idBtn);
  int   RecceRole();
  
  // Generated message map functions
  //{{AFX_MSG(CFutileData)
  virtual BOOL OnInitDialog();
  virtual void OnOK();
  afx_msg void OnHcCfbrs();
  afx_msg void OnHcConfig();
  afx_msg void OnButtonMcu();
  afx_msg void OnHcCfbat();
  afx_msg void OnHcConat();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FUTILE_FILE_DATA_H__92FE2C21_E4A7_11D5_983D_0050BA456CF7__INCLUDED_)
