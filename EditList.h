#if !defined(AFX_EDITLIST_H__B95AFA75_20E9_4C25_ADF4_9DBC311B872B__INCLUDED_)
#define AFX_EDITLIST_H__B95AFA75_20E9_4C25_ADF4_9DBC311B872B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CEditList window
class CEditList : public CListCtrl
{
  // Construction
public:
  CEditList();
  
  // Attributes
public:
  bool         m_ipDrag;
  
  CStringList  COL_Strings[124];
  
protected:
  int			m_nHotCol;			// if set, columns will have a minimum size requirement.
  int			m_nHotItem;			// if set, columns will have a minimum size requirement.
  
private:
  CString     DefaultText;
  
  // Operations
public:
  CComboBox *MakeCombo( int nItem,  int nSubItem);
  CEdit     *EditSubItem (int Item, int Column);
  
  // returns the number of columns in the list.
  int GetColumnCount() const;
  
  // copies a row to a new location.
  //
  bool CopyRow(int nFrom, int nTo);
  
  // moves a row to a new location.
  //
  bool MoveRow(int nFrom, int nTo);
  
  // adds column after the right most column.
  //
  int AddColumn(
    // the column's heading
    LPCTSTR lpszColHeading,
    // Width of the column, in pixels. If this parameter is -1, 
    // the column width is the same as previous column
    int nWidth = -1,
    // the alignment of the column. Can be LVCFMT_LEFT,
    // LVCFMT_RIGHT, or LVCFMT_CENTER.
    int nFormat=LVCFMT_LEFT);
  
protected:
  // call this member function to determine the row index and column index for a point.
  // returns the row index or -1 if point is not over a row.
  //
  int HitTestEx(
    // point to be tested.
    CPoint &point,
    // to hold the column index
    int *col) const;
  
  int	       InsertItemEx (int Item);
  
  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CEditList)
  //}}AFX_VIRTUAL
  
  // Implementation
public:
  virtual ~CEditList();
  
  // Generated message map functions
protected:
  //{{AFX_MSG(CEditList)
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
  //}}AFX_MSG
  afx_msg LRESULT OnReorder(WPARAM wParam, LPARAM lParam);
  
  DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITLIST_H__B95AFA75_20E9_4C25_ADF4_9DBC311B872B__INCLUDED_)
