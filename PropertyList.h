#if !defined(AFX_PROPERTYLIST_H__74205380_1B56_11D4_BC48_00105AA2186F__INCLUDED_)
#define AFX_PROPERTYLIST_H__74205380_1B56_11D4_BC48_00105AA2186F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropertyList.h : header file
//
#include <afxtempl.h>
#include <afxdtctl.h>

#define PIT_COMBO	0  //PIT = property item type
#define PIT_EDIT	1
#define PIT_COLOR	2
#define PIT_FONT	3
#define PIT_FILE	4
#define PIT_TIME    5
#define PIT_BINFILE	6

#define IDC_PROPCMBBOX		712
#define IDC_PROPEDITBOX		713
#define IDC_PROPBTNCTRL		714
#define IDC_PROPTIMBOX		715


/////////////////////////////////////////////////////////////////////////////
//CPropertyList Items
class CPropertyItem
{
  // Attributes
public:
  CString m_propName;
  CString m_curValue;
  int m_nItemType;
  CString m_cmbItems;
  
public:
  CPropertyItem(CString propName, CString curValue,
    int nItemType, CString cmbItems)
  {
    m_propName = propName;
    m_curValue = curValue;
    m_nItemType = nItemType;
    m_cmbItems = cmbItems;
  }
};

#define ID_OPEN		 (WM_APP + 200)
#define ID_SAVE      (WM_APP + 201)
#define ID_SAVEAS    (WM_APP + 202)
#define ID_ADD       (WM_APP + 203)
#define ID_INSERT    (WM_APP + 204)
#define ID_DEL       (WM_APP + 205)
#define ID_TREESAVE  (WM_APP + 206)
#define ID_KEYPOINT  (WM_APP + 207)
#define ID_CREATEFLASH  (WM_APP + 208)

/////////////////////////////////////////////////////////////////////////////
// CPropertyList window

class CHsParaDefinition;

class CPropertyList : public CListBox
{
  // Construction
public:
  CPropertyList();
  
  // Attributes
public:
  struct Valuechange
  {
    int curSel;
    CString oriValue;
    CString curValue;
  } tempValuechange;
  typedef CArray<Valuechange,Valuechange> Changearray;
  Changearray Valuechangearray;
  
  int m_iselectcom;
  int m_iselectedit;
  
  // Operations
  public:
    int AddItem(CString txt);
    int AddPropItem(CPropertyItem* pItem);
    
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CPropertyList)
  public:
    virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
  protected:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    virtual void PreSubclassWindow();
    //}}AFX_VIRTUAL
    
    // Implementation
  public:
    virtual ~CPropertyList();
    
    // Generated message map functions
  protected:
    //{{AFX_MSG(CPropertyList)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSelchange();
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnDblclk();
    //}}AFX_MSG
    afx_msg void OnKillfocusCmbBox();
    afx_msg void OnKillfocusEditBox();
    afx_msg void OnChangeEditBox();
    afx_msg void OnButton();
    afx_msg void OnCloseupDatetimepicker(NMHDR* pNMHDR, LRESULT* pResult);
    
    DECLARE_MESSAGE_MAP()
      
      void InvertLine(CDC* pDC,CPoint ptFrom,CPoint ptTo);
    void DisplayButton(CRect region);
    
    
    CComboBox m_cmbBox;
    CEdit m_editBox;
    CButton m_btnCtrl;
    CFont m_SSerif8Font;
    CDateTimeCtrl	m_ctrDate;
    
    int m_curSel,m_prevSel;
    int m_nDivider;
    int m_nDivTop;
    int m_nDivBtm;
    int m_nOldDivX;
    int m_nLastBox;
    BOOL m_bTracking;
    BOOL m_bDivIsSet;
    HCURSOR m_hCursorArrow;
    HCURSOR m_hCursorSize;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTYLIST_H__74205380_1B56_11D4_BC48_00105AA2186F__INCLUDED_)
