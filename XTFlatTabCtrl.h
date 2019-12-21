//:Ignore
// XTFlatTabCtrl.h interface for the CXTFlatTabCtrl class.
//
// This file is a part of the Xtreme Toolkit for MFC.
// ©1998-2002 Codejock Software, All Rights Reserved.
//
// This source code can only be used under the terms and conditions 
// outlined in the accompanying license agreement.
//
// support@codejock.com
// http://www.codejock.com
//
//////////////////////////////////////////////////////////////////////
//:End Ignore

#if !defined(__XTFLATTABCTRL_H__)
#define __XTFLATTABCTRL_H__

//:Ignore
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
//:End Ignore

//////////////////////////////////////////////////////////////////////
// XT_TCB_ITEM - helper struct used by CXTTabCtrl and CXTTabView to
// store information for a particular tab item.
//
struct XT_TCB_ITEM
{
  CWnd    *pWnd;            // this points to the window associated with a tab
  CString szTabLabel;       // user specified label for the tab
  CString szToolTipLabel;   // tooltip text for the tab
  UINT    uiToolTipId;      // resource id for tooltip
  CString szCondensedLabel; // for auto-condensing tabs: label actually being displayed
};

//:Associate with "Styles - CXTFlatTabCtrl"
const UINT FTS_XT_BOTTOM           = 0x0001; // Show tabs on bottom
const UINT FTS_XT_HASARROWS        = 0x0002; // Show back and next arrows
const UINT FTS_XT_HASHOMEEND       = 0x0004; // Show home and end arrows, used with FTS_XT_HASARROWS
const UINT FTS_XT_TOOLTIPS         = 0x0008; // Show tooltips
const UINT FTS_XT_DEFAULT          = 0x000F; // Same as FTS_XT_BOTTOM | FTS_XT_HASARROWS | FTS_XT_HASHOMEEND | FTS_XT_TOOLTIPS
const UINT FTS_XT_HSCROLL          = 0x0010; // Show a horizontal scroll bar
const UINT FTS_XT_MASK             = 0x001F;

#define _delete(p) { if(p) { delete p; p=NULL; } }

// Note: afxData.cxBorder and afxData.cyBorder aren't used anymore
#define CX_BORDER   1
#define CY_BORDER   1

typedef struct _MMM1222_AUX_DATA_ {
  COLORREF clr3DFace;           // Face color for three-dimensional display elements.
  COLORREF clr3DShadow;         // Shadow color for three-dimensional display elements.
  COLORREF clr3DDkShadow;       // Dark shadow for three-dimensional display elements.
  COLORREF clr3DHilight;        // Highlight color for three-dimensional display elements.
  COLORREF clr3DLight;          // Light color for three-dimensional display elements.
  COLORREF clrBtnText;          // Text on push buttons.
  COLORREF clrGrayText;         // Grayed (disabled) text.
  COLORREF clrHighlight;        // Item(s) selected in a control.
  COLORREF clrHighlightText;    // Text of item(s) selected in a control.
  COLORREF clrMenu;             // Menu background.
  COLORREF clrMenuText;         // Text in menus.
  COLORREF clrWindow;           // Window background.
  COLORREF clrWindowFrame;      // Window frame.
  COLORREF clrWindowText;       // Text in windows.
  COLORREF clrActiveCaption;    // Active window title bar.
  COLORREF clrInActiveCaption;  // Inactive window title bar.
  COLORREF clrGradActiveCapt;   // Gradient active title bar.
  COLORREF clrGradInActiveCapt; // Gradient inactive title bar.
  COLORREF clrActiveCaptText;   // Active caption text.
  COLORREF clrInactiveCaptText; // Inactive caption text.
  
  HCURSOR hcurDragCopy;  // Drag copy
  HCURSOR hcurDragMove;  // Drag move
  HCURSOR hcurDragNone;  // Drag none
  HCURSOR hcurHand;      // Hand
  HCURSOR hcurHandNone;  // No Hand
  HCURSOR hcurHSplitBar; // Horizontal Splitter 
  HCURSOR hcurVSplitBar; // Vertical Splitter
  HCURSOR hcurMove;      // 4 way move 
}HT_AUX,*HTP_AUX;

/////////////////////////////////////////////////////////////////////////////
// CXTFlatTabCtrl creates an Excel style sheet control. You can define if you
// want the control to have home, end, back and next buttons.
//
class CXTFlatTabCtrl : public CWnd
{
  DECLARE_DYNAMIC(CXTFlatTabCtrl)
    
public:
  
  // Constructs a CXTFlatTabCtrl object.
  //
  CXTFlatTabCtrl();
  
  // Destroys a CXTFlatTabCtrl object, handles cleanup and de-allocation.
  //
  virtual ~CXTFlatTabCtrl();
  
protected:
  
  CToolTipCtrl m_ToolTip;            // Tooltip for the flat tab control.
  DWORD        m_dwStyle;            // Tab control style.
  bool         m_bManagingViews;     // True if the control is managing views.
  int          m_cx;                 // Width for each arrow button.
  int          m_cy;                 // Height for each arrow button.
  CRect        m_rectTabs;           // Area occupied by tabs.
  CRect        m_rectViews;          // Area occupied by managed views.
  int          m_nCurSel;            // Index of the currently selected tab.
  int          m_nClientWidth;       // Width in pixels of the tab control client area.
  int          m_nClientHeight;      // Height in pixels of the tab control client area.
  int          m_nOffset;            // Amount in pixels of the displayed tab offset.
  
  CFont       *m_pNormFont;          // Font that is used for non-selected tabs.
  CFont       *m_pBoldFont;          // Font that is used for selected tabs.
  
  CFont        m_NormFont;          // Font that is used for non-selected tabs.
  CFont        m_BoldFont;          // Font that is used for selected tabs.
  
  CScrollBar   m_ScrollBar_H;        // The horizontal scroll bar (used with FTS_XT_HSCROLL)
  CRect        m_rectSB_H;           // Area occupied by horizontal scroll bar
  CRect        m_rectGripper;        // Area occupied by sizing gripper
  int          m_xGripperPos;        // The current gripper position in pixels (from left).
  int          m_iGripperPosPerCent; // The current gripper position, in percent of the control width.
  
  // pens used by painting code
  HT_AUX       _HtAux;
  CPen         m_penShadow;
  CPen         m_penBackSel;
  CPen         m_penBackNonSel;
  CPen         m_penOutline;
  CPen         m_penWindow;
  //:End Ignore
  
  // template list containing tab information
  CArray <XT_TCB_ITEM*, XT_TCB_ITEM*>  m_tcbItems;
  
  //:Ignore
  // tracking related variables
  bool         m_bTracking;
  int          m_xTrackingDelta;
  CWnd *       m_pWndLastFocus;
  //:End Ignore
  
  enum icon_type
  {
    arrow_left          =   0x0200,
      arrow_left_home     =   0x0201,
      arrow_right         =   0x0000,
      arrow_right_home    =   0x0001
  };
  
  //:Ignore
  // internal structures/variables used to control button information
  class CXTFTButtonState
  {
  public:
    CXTFTButtonState();
    
    void SetInfo(CRect rect, int iCommand, icon_type iconType);
    
    CRect m_rect;
    bool  m_bPressed;
    bool  m_bEnabled;
    int   m_iCommand;
    icon_type m_IconType;
  };
  
  CXTFTButtonState m_buttons[4];     // Array of button information
  int              m_iBtnLeft;       // Index of "left" button in button array
  int              m_iBtnRight;      // Index of "right" button in button array 
  int              m_iBtnHome;       // Index of "home" button in button array   
  int              m_iBtnEnd;        // Index of "end" button in button array  
  //:End Ignore
  
  
  public:
    
    // This member function will return the text of a particular tab, or 
    // NULL if an error occurs
    LPCTSTR GetItemText(
      // The index of the tab who's text is to be retrieved
      int nIndex
      ) const;
    
    // This member function will set the text of a particular tab.  Returns
    // 'true' on success
    bool SetItemText(
      // The index of the tab who's text is to be changed
      int nIndex,
      // The new title for the tab
      LPCTSTR pszText
      );
    
    // This member function returns a pointer to the window that is 
    // associated with a particular tab.  Returns NULL if no window is 
    // associated with (managed by) the tab.
    CWnd *GetItemWindow(
      // The index of the tab who's managed window is to be retrieved
      int nIndex
      ) const;
    
    // This member function will set the fonts to be used by the tab control.
    //
    virtual void SetTabFonts(
      // Represents the font used by non-selected tabs.
      CFont* pNormFont,
      // Represents the font used by selected tabs.
      CFont* pBoldFont);
    
    // This member function will insert a tab into the flat tab control.
    // Returns the index of the tab that has been inserted if successful, otherwise
    // returns -1 on error.
    //
    virtual int AnnexItem(
      // Index of the tab to insert.
      int nItem,
      // String resource ID of the tab label.
      UINT nTextID,
      // optional pointer to managed control
      CWnd *pWndControl = NULL
      );
    
    // This member function will insert a tab into the flat tab control.
    // Returns TRUE if successful; otherwise FALSE.
    //
    virtual BOOL AnnexControl(
      // Index of the tab to insert.
      int nItem,
      // NULL terminated string that represents the tab label.
      LPCTSTR lpszItem,
      // optional pointer to managed control
      CWnd *pWndControl = NULL
      );
    
    // This member function will delete the tab specified by nItem from 
    // the tab control.
    // Returns TRUE if successful; otherwise FALSE.
    //
    virtual BOOL DeleteItem(
      // Index of the tab to delete.
      int nItem);
    
    // This member function will remove all of the tabs from the tab control.
    // Returns TRUE if successful; otherwise FALSE.
    //
    virtual BOOL DeleteAllItems();
    
    // This member function will retrieve the size of the tab specified 
    // by nItem.
    // Returns TRUE if successful; otherwise FALSE.
    //
    virtual BOOL GetItemRect(
      // Index of the tab.
      int nItem,
      // Points to a RECT structure to receive the size of the tab.
      LPRECT lpRect);
    
    // Call this function to determine which tab, if any, is at the 
    // specified screen position.
    // Returns the zero-based index of the tab or  – 1 if no tab is at 
    // the specified position.
    //
    virtual int HitTest(
      // Pointer to a TCHITTESTINFO structure, as 
      // described in the Platform SDK, which specifies 
      // the screen position to test.
      TCHITTESTINFO *pHitTestInfo) const;
    
    // Call this function to retrieve the currently selected tab in a 
    // flat tab control.
    // Returns a zero-based index of the selected tab if successful or  – 1 if 
    // no tab is selected.
    //
    virtual int GetCurSel() const;
    
    // Selects a tab in a flat tab control.
    // Returns a zero-based index of the previously selected tab if successful, 
    // otherwise  – 1.
    //
    virtual int SetCurSel(
      // The zero-based index of the item to be selected.
      int nItem);
    
    // Call this function to retrieve the number of tabs in the tab control.
    // Returns the number of items in the tab control.
    //
    virtual int GetItemCount() const;
    
    // This member function will set the tooltip for the tab specified
    // by nItem.
    //
    virtual void SetTipText(
      // The zero-based index of tab to receive the tooltip text.
      int nItem,
      // A pointer to a string containing the tooltip text.
      LPCTSTR lpszTabTip);
    
    // This member function will return the tooltip text associated with
    // the tab specified by nItem.
    // Returns a CString object containing the text to be used in the tooltip.
    //
    virtual CString GetTipText(
      // The zero-based index of the tab to retrieve the tooltip 
      // text for.
      int nItem);
    
    // This member function will cause the tab control to reposition
    // the tabs to the home position.
    //
    virtual void Home();
    
    // This member function changes the location of the sizing gripper.
    // The function has no effect if the FTS_XT_HSCROLL isn't used.
    //
    void SetGripperPosition(
      // The position for the gripper, relative to the left-hand-side of
      // the control.
      int x, 
      // Indicates that the position is in percent of the control width,
      // as opposed to an absolute location in pixels.
      bool bPercent);
    
    // Returns the location of the sizing gripper, in pixels, relative to the
    // left hand size of the control.
    //
    int GetGripperPosition() const;
    
    // Synchronize the tab control's horizontal scroll bar with the 
    // horizontal scroll bar of the current view.
    // 
    // You should call this function if anything happened in the view that
    // affects the horizontal scroll bar (e.g. a user typing text into an
    // edit control could make the text wider, thus requiring a call to this
    // function).
    void SyncScrollBar();
    
    //:Ignore
    //{{AFX_VIRTUAL(CXTFlatTabCtrl)
    virtual BOOL Create(DWORD dwStyle, const CRect& rect, CWnd* pParentWnd, UINT nID);
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    virtual BOOL OnNotify(WPARAM, LPARAM lParam, LRESULT* pResult);
    //}}AFX_VIRTUAL
    //:End Ignore
    
protected:
  
  // This function to determine which button, if any, is at the specified
  // screen position.
  // Returns the zero-based index of the button withing the buttons array
  // or – 1 if no button is at the specified position.
  //
  virtual int ButtonHitTest(CPoint& pt) const;
  
  // This member function will return the width in pixels of the tab
  // specified by nItem.
  // Returns the width in pixels of the tab.
  //
  int GetTabWidth(
    // The zero-based index of the tab to retrieve the width for.
    int nItem) const;
  
  // This member function will return the total width of all of the tabs
  // in the flat tab control.
  // Returns the total width in pixels of all the tabs in the flat tab
  // control combined.
  //
  int GetTotalTabWidth() const;
  
  // This member function will return the total width of all of the arrow
  // buttons that are visible in the flat tab control.
  // Returns the total width in pixels of all the visible arrow buttons.
  //
  int GetTotalArrowWidth() const;
  
  int GetTotalTabAreaWidth() const;
  
  // This member function will draw a tab to the device context specified
  // by pDC.
  // Returns the x position of the next tab to be drawn.
  //
  int DrawTab(
    // Points to the device context to draw the tab to.
    CDC* pDC,
    // XY location of the top left corner of the tab to draw.
    const CPoint& pt,
    // true if the tab is currently selected.
    bool bSelected,
    // A NULL terminated string that represents the tab label.
    LPCTSTR lpszTabLabel);
  
  void DrawButton(
    // Points to the device context to draw the tab to.
    CDC* pDC,
    // XY location of the top left corner of the tab to draw.
    CXTFTButtonState& button_state
    ) const;
  
  // This member function will force all of the tabs to be repainted.
  //
  void InvalidateTabs();
  
  // This member function will enable / disable the arrow buttons
  // depending on the current tab display state.
  //
  void EnableButtons();
  
  // This member function will free the resources allocated for the
  // icons used by the arrow buttons.
  //
  void FreeButtonIcons();
  
  // This member function will create the icon resources that are
  // used by the arrow buttons.
  //
  void CreateButtonIcons();
  
  // This member function will the horizontal sizing gripper at a specified
  // location.
  //
  void DrawGripper(
    // Points to the device context to draw the gripper to.
    CDC* pDC,
    // Location of gripper
    CRect rect
    ) const;
  
  // The member function is used internally to toggle the state of the
  // sizing-grip tracking mode.
  //
  void SetTracking(bool bTracking);
  
  // This member function frees all memory occupied by the tab items
  // 
  void ClearAllItems();
  
  // This member function is called when the tab control is resized.  It 
  // is responsible for updating internal structures which are dependant
  // on the control's size.
  void RecalcLayout();
  
  // This internal function deletes an item from the tab item list
  //
  virtual BOOL _DeleteItem(
    // Index of the tab to delete.
    int nItem);
  
  // This internal function calculates the overlap between two tabs
  virtual int GetOverlap() const;
  
  
  //:Ignore
  //{{AFX_MSG(CXTFlatTabCtrl)
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnPaint();
  afx_msg BOOL OnEraseBkgnd(CDC* pDC);
  afx_msg void OnLeftArrow();
  afx_msg void OnRightArrow();
  afx_msg void OnHomeArrow();
  afx_msg void OnEndArrow();
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);
  afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
  afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
  afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
  afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
  //}}AFX_MSG
  //:End Ignore
  DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////

AFX_INLINE BOOL CXTFlatTabCtrl::AnnexItem(int nItem, UINT nTextID, CWnd *pWndControl) {
  ASSERT(IsWindow(m_hWnd)); CString strItem; strItem.LoadString(nTextID); 
  return AnnexControl(nItem, strItem, pWndControl);
}
AFX_INLINE int CXTFlatTabCtrl::GetCurSel() const {
  ASSERT(IsWindow(m_hWnd)); return m_nCurSel;
}
AFX_INLINE int CXTFlatTabCtrl::GetItemCount() const {
  ASSERT(IsWindow(m_hWnd)); int iItemCount = (int)m_tcbItems.GetSize(); return iItemCount;
}
AFX_INLINE void CXTFlatTabCtrl::SetTabFonts(CFont* pNormFont, CFont* pBoldFont) {
  if (pNormFont){ m_pNormFont = pNormFont; } if (pBoldFont){ m_pBoldFont = pBoldFont; }
}

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTFLATTABCTRL_H__)
