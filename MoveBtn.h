#if !defined(AFX_MOVEBTN_H__32106108_F5B2_4EA7_AB59_CCCB603D4563__INCLUDED_)
#define AFX_MOVEBTN_H__32106108_F5B2_4EA7_AB59_CCCB603D4563__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MoveBtn.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMoveBtn window

class CMoveBtn : public CButton
{
  // Construction
public:
  CMoveBtn();
  
  // Attributes
public:
  
  // Operations
public:
  
  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CMoveBtn)
public:
protected:
  //}}AFX_VIRTUAL
  
  // Implementation
public:
  BOOL SetMoveRect(const CRect* rect);
  BOOL SetPos(const CRect* rect);
  virtual ~CMoveBtn();
  
  // Generated message map functions
protected:
  //{{AFX_MSG(CMoveBtn)
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);
  //}}AFX_MSG
  
  DECLARE_MESSAGE_MAP()
private:
  CRect m_MoveRect;
  BOOL m_IsCurrSelected;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOVEBTN_H__32106108_F5B2_4EA7_AB59_CCCB603D4563__INCLUDED_)
