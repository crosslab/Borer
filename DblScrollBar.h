#if !defined(AFX_DBLSCROLLBAR_H__82827967_08C8_4810_A33A_AA01D1BC6240__INCLUDED_)
#define AFX_DBLSCROLLBAR_H__82827967_08C8_4810_A33A_AA01D1BC6240__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDoubleScrollBar window
class CDoubleScrollBar : public CScrollBar
{
  // Construction
public:
  CDoubleScrollBar();
  
  // Attributes
public:
  
  // Operations
public:
  
  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CDoubleScrollBar)
  //}}AFX_VIRTUAL
  
  // Implementation
public:
  double GetTrackPos();
  void SetPageSize(double dPageSize,bool bRedraw);
  double GetPageSize();
  double GetScrollLimit();
  double GetScrollPos() const;
  double SetScrollPos(double dPos, bool bRedraw = true);
  void GetScrollRange(double * dMinPos, double * dMaxPos);
  void SetScrollRange(double dMinPos, double dMaxPos, bool bRedraw = true);
  virtual ~CDoubleScrollBar();
  
  // Generated message map functions
protected:
  //{{AFX_MSG(CDoubleScrollBar)
		// NOTE - the ClassWizard will add and remove member functions here.
  //}}AFX_MSG
  
  DECLARE_MESSAGE_MAP()
    
private:
  CString csEditText;
  const UINT nPrecision;
  double dCurrentValue;
  double dMaxValue;
  double dMinValue;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBLSCROLLBAR_H__82827967_08C8_4810_A33A_AA01D1BC6240__INCLUDED_)
