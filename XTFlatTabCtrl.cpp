// XTFlatTabCtrl.cpp : implementation of the CXTFlatTabCtrl class.
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
#include "stdafx.h"
#include "MpDef.h"
#include "Borer.h"
#include "XTFlatTabCtrl.h"

#include "XTMemDC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CBorerApp theApp;
static const int GRIPPER_WIDTH = 6;

#define BUTTON_COUNT (sizeof(m_buttons)/sizeof(m_buttons[0]))

CXTFlatTabCtrl::CXTFTButtonState::CXTFTButtonState() :
m_rect(0, 0, 0, 0), m_bPressed(false), m_bEnabled(true) {}

void CXTFlatTabCtrl::CXTFTButtonState::SetInfo(CRect rect, 
                                               int iCommand, icon_type iconType)
{
  m_rect = rect;
  m_iCommand = iCommand;
  m_IconType = iconType;
}



/////////////////////////////////////////////////////////////////////////////
// CXTFlatTabCtrl
/////////////////////////////////////////////////////////////////////////////
CXTFlatTabCtrl::CXTFlatTabCtrl()
{
  m_dwStyle		 = NULL;
  m_nCurSel		 =-1;
  m_nOffset		 = 0;
  m_nClientWidth	 = 0;
  m_nClientHeight  = 0;
  
  //  Create a font for the combobox
  NONCLIENTMETRICS ncm;
  memset(&ncm, 0, sizeof(NONCLIENTMETRICS));
  ncm.cbSize =sizeof(NONCLIENTMETRICS);
  SystemParametersInfo(SPI_GETNONCLIENTMETRICS,sizeof(NONCLIENTMETRICS),&ncm,0);
  
  m_NormFont.CreateFontIndirect(&ncm.lfMessageFont);
  ncm.lfMessageFont.lfWeight=ncm.lfMessageFont.lfWeight*2;
  m_BoldFont.CreateFontIndirect(&ncm.lfMessageFont);
  
  m_pNormFont 	 = &m_NormFont;
  m_pBoldFont 	 = &m_BoldFont;
  
  m_bManagingViews = false;
  m_rectGripper	 = CRect(0, 0, 0, 0);
  m_bTracking 	 = false;
  m_pWndLastFocus  = NULL;
  m_iGripperPosPerCent = 0;
  m_xGripperPos	 = -1;
  
  // Initialize the width and height for the left, right, home 
  // and end buttons. 
  m_cy = ::GetSystemMetrics(SM_CYHSCROLL);
  m_cx = ::GetSystemMetrics(SM_CXHSCROLL)-1;
  
  // Create the icons used by the left, right, home and end buttons.
  CreateButtonIcons();
}

CXTFlatTabCtrl::~CXTFlatTabCtrl()
{
  // Cleanup 
  ClearAllItems();
  FreeButtonIcons();
}

IMPLEMENT_DYNAMIC(CXTFlatTabCtrl, CWnd)

BEGIN_MESSAGE_MAP(CXTFlatTabCtrl, CWnd)
//{{AFX_MSG_MAP(CXTFlatTabCtrl)
ON_WM_CREATE()
ON_WM_PAINT()
ON_WM_ERASEBKGND()
ON_BN_CLICKED(XT_IDC_BTN_LEFT, OnLeftArrow)
ON_BN_CLICKED(XT_IDC_BTN_RIGHT, OnRightArrow)
ON_BN_CLICKED(XT_IDC_BTN_HOME, OnHomeArrow)
ON_BN_CLICKED(XT_IDC_BTN_END, OnEndArrow)
ON_WM_SIZE()
ON_WM_LBUTTONDOWN()
ON_WM_MOUSEMOVE()
ON_WM_SETCURSOR()
ON_WM_LBUTTONUP()
ON_WM_LBUTTONDBLCLK()
ON_WM_HSCROLL()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CXTFlatTabCtrl::Create(DWORD dwStyle, const CRect& rect, CWnd* pParentWnd, UINT nID) 
{
  ASSERT(pParentWnd != NULL); // must be valid.
  
  // Call the base class for creation.
  if(!CWnd::Create(NULL, NULL, dwStyle, rect, pParentWnd, nID))
  {
    TRACE0( "Failed to create flat tab control.\n" );
    return FALSE;
  }
  
  return TRUE;
}

int CXTFlatTabCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
  if (CWnd::OnCreate(lpCreateStruct) == -1) {
    return -1;
  }
  
  _HtAux.clr3DShadow=GetSysColor(COLOR_3DSHADOW);
  _HtAux.clr3DLight=GetSysColor(COLOR_3DLIGHT);
  _HtAux.clr3DFace=GetSysColor(COLOR_3DFACE);
  _HtAux.clr3DHilight=GetSysColor(COLOR_3DHIGHLIGHT);
  
  _HtAux.clrBtnText=GetSysColor(COLOR_BTNTEXT);
  _HtAux.clrWindow=GetSysColor(COLOR_WINDOW);
  _HtAux.clrWindowText=GetSysColor(COLOR_WINDOWTEXT);
  
  // create the required pens
  m_penShadow.	CreatePen(PS_SOLID, 1, _HtAux.clr3DShadow);
  m_penOutline.	CreatePen(PS_SOLID, 1, _HtAux.clrBtnText);
  m_penWindow.	CreatePen(PS_SOLID, 1, _HtAux.clr3DLight);
  m_penBackSel.	CreatePen(PS_SOLID, 1, _HtAux.clrWindow);
  m_penBackNonSel.CreatePen(PS_SOLID, 1, _HtAux.clr3DFace);
  
  _HtAux.hcurHSplitBar =theApp.LoadCursor(MAKEINTRESOURCE(XT_IDC_HSPLITBAR));
  ASSERT(_HtAux.hcurHSplitBar != NULL);
  
  // Save the window style.
  m_dwStyle = lpCreateStruct->style;
  if (m_dwStyle & FTS_XT_HASHOMEEND) m_dwStyle |= FTS_XT_HASARROWS;
  
  m_nClientWidth	= lpCreateStruct->cx;
  m_nClientHeight = lpCreateStruct->cy;
  
  // If we use tooltips, create the control.
  if (m_dwStyle & FTS_XT_TOOLTIPS)
  {
    CString string;
    string.LoadString(XT_IDS_TIPTEXT);
    
    m_ToolTip.Create(this);
    m_ToolTip.Activate(TRUE);
    m_ToolTip.AddTool(this, string);
    m_ToolTip.SendMessage(TTM_SETMAXTIPWIDTH, 0, SHRT_MAX); // Allow multiline tooltips
  }
  
  CRect rectDummy(0, 0, 0, 0);
  
  // If we use arrow buttons, create the buttons.
  if (m_dwStyle & FTS_XT_HASARROWS)
  {
    int nIndex = 0;
    
    //		CRect btnRects[] =
    //		{
    //			CRect(0,	  m_rectTabs.top + 1, m_cx,   m_rectTabs.bottom),
    //			CRect(m_cx,   m_rectTabs.top + 1, m_cx*2, m_rectTabs.bottom),
    //			CRect(m_cx*2, m_rectTabs.top + 1, m_cx*3, m_rectTabs.bottom),
    //			CRect(m_cx*3, m_rectTabs.top + 1, m_cx*4, m_rectTabs.bottom) 
    //		};
    
    // Create the home button.
    if (m_dwStyle & FTS_XT_HASHOMEEND)
    {
      m_buttons[nIndex].SetInfo(rectDummy, XT_IDC_BTN_HOME, 
        arrow_left_home);
      m_iBtnHome = nIndex;
      ++nIndex;
    }
    else
    {
      m_iBtnHome = 3;
    }
    
    // Create the left button.
    m_buttons[nIndex].SetInfo(rectDummy, XT_IDC_BTN_LEFT, arrow_left);
    m_iBtnLeft = nIndex;
    ++nIndex;
    
    // Create the right button.
    m_buttons[nIndex].SetInfo(rectDummy, XT_IDC_BTN_RIGHT, arrow_right);
    m_iBtnRight = nIndex;
    ++nIndex;
    
    // Create the end button.
    if (m_dwStyle & FTS_XT_HASHOMEEND)
    {
      m_buttons[nIndex].SetInfo(rectDummy, XT_IDC_BTN_END,
        arrow_right_home);
      m_iBtnEnd = nIndex;
      ++nIndex;
    }
    else
    {
      m_iBtnEnd = 3;
    }
    
  }
  
  RecalcLayout();
  
  if (m_dwStyle & FTS_XT_HSCROLL)
  {
    m_ScrollBar_H.Create(WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), 
      this, 1);
    SetGripperPosition(60, true);
  }
  else
  {
    m_rectSB_H = CRect(0, 0, 0, 0);
  }
  
  return 0;
}

void CXTFlatTabCtrl::SetGripperPosition(int x, bool bPercent)
{
  // only valid for tabs with horizontal scroll bars
  if (!(m_dwStyle & FTS_XT_HSCROLL)) return;
  
  int x_percent;
  if (bPercent)
  {
    x_percent = x;
    x = m_nClientWidth * x / 100;
  }
  else
  {
    x_percent = x * 100 / m_nClientWidth;
  }
  
  // too far to the left?
  const int arrowWidth = 0; //GetTotalArrowWidth();
  if (x < arrowWidth) x = arrowWidth;
  
  // too far to the right?
  const int sbExtreme = (m_nClientWidth - 4 * m_cx - m_cy);
  if (x > sbExtreme) x = sbExtreme;
  
  m_xGripperPos = x;
  m_iGripperPosPerCent = x_percent;
  
  m_rectGripper = m_rectTabs;
  m_rectGripper.left += x;
  m_rectGripper.right = m_rectGripper.left + GRIPPER_WIDTH;
  
  const int isbottom = ((m_dwStyle & FTS_XT_BOTTOM) == FTS_XT_BOTTOM);
  m_rectSB_H = CRect(
    m_rectGripper.right, 
    m_rectTabs.top - !isbottom, 
    m_rectTabs.right - m_cy, 
    m_rectTabs.bottom + isbottom);
  m_ScrollBar_H.MoveWindow(m_rectSB_H);
  
  EnableButtons();
  InvalidateRect(m_rectTabs);
}

int CXTFlatTabCtrl::GetGripperPosition() const
{
  return m_xGripperPos;
}


BOOL CXTFlatTabCtrl::OnEraseBkgnd(CDC* pDC) 
{
  if (GetItemCount() == 0)
  {
    pDC->FillSolidRect(m_rectViews, _HtAux.clr3DFace);
  }
  return TRUE;
}

void CXTFlatTabCtrl::CreateButtonIcons()
{
  // obsolete
}

void CXTFlatTabCtrl::FreeButtonIcons()
{
  // obsolete
}

int CXTFlatTabCtrl::GetTabWidth(int nItem) const
{
  CDC *pDC = CDC::FromHandle(::GetDC(m_hWnd));
  
  CFont* pOldFont = pDC->SelectObject((m_nCurSel == nItem)?
m_pBoldFont : m_pNormFont);
  
  CSize size = pDC->GetTextExtent(m_tcbItems[nItem]->szTabLabel);
  pDC->SelectObject(pOldFont);
  
  ::ReleaseDC(m_hWnd, pDC->m_hDC);
  
  return size.cx + m_cy + (m_cy / 2);
}

int CXTFlatTabCtrl::GetTotalTabWidth() const
{
  int iWidth = 0;
  const int cItems = GetItemCount();
  const int iOverlap = GetOverlap();
  for (int i = 0; i < cItems; i++)
  {
    iWidth += GetTabWidth(i);
    if (i != 0) {
      iWidth -= iOverlap;
    }
  }
  return iWidth;
}

int CXTFlatTabCtrl::GetTotalArrowWidth() const
{
  int iWidth = 0;
  
  if (m_dwStyle & FTS_XT_HASARROWS)
    iWidth += (m_cx*2);
  
  if (m_dwStyle & FTS_XT_HASHOMEEND)
    iWidth += (m_cx*2);
  
  return iWidth;
}

int CXTFlatTabCtrl::GetTotalTabAreaWidth() const
{
  int iWidth;
  if (m_dwStyle & FTS_XT_HSCROLL)
  {
    iWidth = m_xGripperPos;
  }
  else
  {
    iWidth = m_nClientWidth;
  }
  iWidth -= GetTotalArrowWidth();
  return iWidth;
}

void CXTFlatTabCtrl::InvalidateTabs()
{
  if (GetSafeHwnd())
  {
    // invalidate the visible tab area
    // to minimise flicker - don't erase the background
    CRect rcTabs;
    
    rcTabs.left = GetTotalArrowWidth();
    rcTabs.top = m_rectTabs.top;
    rcTabs.right = rcTabs.left + (GetTotalTabWidth() - m_nOffset);
    rcTabs.bottom = m_rectTabs.bottom;
    InvalidateRect(&rcTabs, FALSE);
    
    // invalidate the blank area to the right of the tabs
    if (rcTabs.right < m_nClientWidth)
    {
      rcTabs.left = rcTabs.right;
      rcTabs.right = m_nClientWidth;
      InvalidateRect(&rcTabs, TRUE);
    }
  }
}

void CXTFlatTabCtrl::EnableButtons()
{
  if (m_dwStyle & FTS_XT_HASARROWS)
  {
    m_buttons[m_iBtnLeft].m_bEnabled = (m_nOffset > 0);
    m_buttons[m_iBtnRight].m_bEnabled = 
      (GetTotalTabWidth() - m_nOffset > GetTotalTabAreaWidth() - 1);
    
    if (m_dwStyle & FTS_XT_HASHOMEEND)
    {
      m_buttons[m_iBtnHome].m_bEnabled = m_buttons[m_iBtnLeft].m_bEnabled;
      m_buttons[m_iBtnEnd]. m_bEnabled = m_buttons[m_iBtnRight].m_bEnabled;
    }
    
    CRect rc = m_buttons[m_iBtnLeft].m_rect;
    rc.left  = 0;
    rc.right = GetTotalArrowWidth();
    InvalidateRect(rc);
  }
  else
  {
    InvalidateRect(CRect(0, 0, GetTotalArrowWidth(), m_nClientHeight));
  }
}

BOOL CXTFlatTabCtrl::GetItemRect(int nItem, LPRECT lpRect)
{
  const int cItems = GetItemCount();
  if (nItem < 0 || nItem >= cItems)
    return FALSE;
  
  const int iOverlap = GetOverlap();
  int x = GetTotalArrowWidth();
  for (int i = 0; i < nItem; i++)
  {
    x += GetTabWidth(i) - iOverlap;
  }
  lpRect->left = x - m_nOffset;
  lpRect->top = m_rectTabs.top;
  lpRect->right = lpRect->left + GetTabWidth(nItem);
  lpRect->bottom = m_rectTabs.bottom;
  return TRUE;
}

int CXTFlatTabCtrl::ButtonHitTest(CPoint& pt) const
{
  for (int i = 0; i < BUTTON_COUNT; ++i)
  {
    if (m_buttons[i].m_rect.PtInRect(pt))
    {
      return i;
    }
  }
  return -1;
}

int CXTFlatTabCtrl::HitTest(TCHITTESTINFO *pHitTestInfo) const
{
  // ignore hits on the buttons
  int iHitX = pHitTestInfo->pt.x;
  if (iHitX < GetTotalArrowWidth())
    return -1;
  
  // on or to the right of the the scroll bar/gripper?
  if ((m_dwStyle & FTS_XT_HSCROLL)  &&  iHitX > m_rectGripper.left)
  {
    return -1;
  }
  
  const int iOverlap = GetOverlap();
  
  // check if any tabs were hit
  int x = GetTotalArrowWidth() - m_nOffset;
  const int cItems = GetItemCount();
  for (int i = 0; i < cItems; i++)
  {
    int iTabWidth = GetTabWidth(i);
    if (i != cItems - 1)
    {
      iTabWidth -= iOverlap;
    }
    if ((x <= iHitX) && (iHitX <= x + iTabWidth))
    {
      return i;
    }
    x += iTabWidth;
  }
  
  // hit point is right of rightmost tab
  return -1;
}

void CXTFlatTabCtrl::OnLeftArrow()
{
  // Move the tabs right, ensuring that we move right by one
  // whole tab each time ala Microsoft Access
  
  CPoint Point(GetTotalArrowWidth() + 1 + GetOverlap(), 1);
  
  TCHITTESTINFO htInfo;
  htInfo.pt = Point;
  int iTab = HitTest(&htInfo);
  
  if (iTab != -1)
  {
    m_nOffset = 0;
    RECT rect;
    if (GetItemRect(iTab - 1, &rect))
    {
      m_nOffset += rect.left;
      m_nOffset -= GetTotalArrowWidth();
      EnableButtons();
      InvalidateTabs();
    }
  }
}

void CXTFlatTabCtrl::OnRightArrow() 
{
  // Move the tabs left, ensuring that we move left by one
  // whole tab each time ala Microsoft Access
  
  CPoint Point(GetTotalArrowWidth()+ 1 + GetOverlap(), 1);
  
  TCHITTESTINFO htInfo;
  htInfo.pt = Point;
  int iTab = HitTest(&htInfo);
  
  if (iTab != -1)
  {
    RECT rect;
    if (GetItemRect(iTab + 1, &rect))
    {
      m_nOffset += rect.left - GetTotalArrowWidth();
      EnableButtons();
      InvalidateTabs();
    }
  }
}

void CXTFlatTabCtrl::OnHomeArrow() 
{
  m_nOffset = 0;
  EnableButtons();
  InvalidateTabs();
}

void CXTFlatTabCtrl::OnEndArrow() 
{
  m_nOffset = GetTotalTabWidth() - GetTotalTabAreaWidth() + 1;
  EnableButtons();
  InvalidateTabs();
}

void CXTFlatTabCtrl::OnSize(UINT nType, int cx, int cy) 
{
  CWnd::OnSize(nType, cx, cy);
  
  m_nClientWidth	 = cx;
  m_nClientHeight  = cy;
  
  RecalcLayout();
  SetGripperPosition(m_iGripperPosPerCent, true);
  SyncScrollBar();
}

int CXTFlatTabCtrl::AnnexControl(int nItem, LPCTSTR lpszItem, CWnd *pWndControl)
{
  const int cItems = GetItemCount();
  if (nItem < 0 || nItem > cItems)
    return -1;
  
  if (pWndControl)
  {
    ASSERT(::IsWindow(pWndControl->m_hWnd));
    
    // managed view should be a hidden child
    ASSERT((pWndControl->GetStyle() & (WS_VISIBLE | WS_CHILD)) == WS_CHILD);
    
    // can't have both managed and non-managed tabs
    ASSERT(m_bManagingViews  ||  cItems == 0);
    
    m_bManagingViews = true;
    
    pWndControl->SetParent(this);
    pWndControl->SetWindowPos(NULL, m_rectViews.left, m_rectViews.top,
      m_rectViews.Width(), m_rectViews.Height(), 
      SWP_NOZORDER | SWP_NOREDRAW);
  }
  
  // Allocate a new XT_TCB_ITEM object.
  XT_TCB_ITEM* pMember = new XT_TCB_ITEM;
  if (pMember == NULL)
    return -1;
  
  pMember->pWnd			= pWndControl;
  pMember->szTabLabel 	= lpszItem;
  pMember->szToolTipLabel = lpszItem;
  pMember->uiToolTipId	= GetItemCount();
  
  if (nItem <= m_nCurSel) ++m_nCurSel;
  
  // Add the new XT_TCB_ITEM to the tab item list.
  m_tcbItems.InsertAt(nItem, pMember);
  
  if (m_nCurSel < 0) m_nCurSel = 0;
  EnableButtons();
  InvalidateTabs();
  SetCurSel(nItem);
  
  return nItem;
}

BOOL CXTFlatTabCtrl::_DeleteItem(int nItem)
{
  const int cItems = m_tcbItems.GetSize();
  if (nItem < 0 || nItem >= cItems)
    return FALSE;
  
  // Remove the item from the string arrays.
  CWnd *pWndControl = m_tcbItems[nItem]->pWnd;
  if (::IsWindow(pWndControl->GetSafeHwnd()))
  {
    pWndControl->ShowWindow(SW_HIDE);
    pWndControl->SetParent(NULL);
  }
  _delete(m_tcbItems[nItem]);
  m_tcbItems.RemoveAt(nItem);
  if (m_tcbItems.GetSize() == 0)
  {
    m_bManagingViews = false;
  }
  return TRUE;
}

BOOL CXTFlatTabCtrl::DeleteItem(int nItem)
{
  if (!_DeleteItem(nItem))
  {
    return FALSE;
  }
  
  const int cItems = GetItemCount();
  ASSERT(cItems >= 0);
  
  if (cItems == 0)
  {
    m_nCurSel = -1;
  }
  else
  {
    if (nItem == m_nCurSel)
    {
      m_nCurSel = 0;
      SetCurSel(0);
    }
    else if (m_nCurSel > nItem)
    {
      --m_nCurSel;
    }
  }
  
  EnableButtons();
  InvalidateTabs();
  
  return TRUE;
}

void CXTFlatTabCtrl::ClearAllItems()
{
  while (_DeleteItem(0)) {};
}

BOOL CXTFlatTabCtrl::DeleteAllItems()
{
  ClearAllItems();
  
  // Reset the currently selected tab to -1 as we have no tabs in our list now.
  m_nCurSel = -1;
  
  EnableButtons();
  InvalidateTabs();
  
  return TRUE;
}

int CXTFlatTabCtrl::SetCurSel(int nItem)
{
  const int cItems = GetItemCount();
  if (nItem < 0 || nItem >= cItems)
    return -1;
  
  int iPrevSel = m_nCurSel;
  m_nCurSel = nItem;
  
  // test if we need to center on the selected tab
  CRect rcItem;
  if (GetItemRect(nItem, &rcItem))
  {
    // test if the tab is off on the left
    int iTotalArrowWidth = GetTotalArrowWidth();
    rcItem.left -= iTotalArrowWidth;
    if (rcItem.left <= 0)
      m_nOffset += rcItem.left;
    else
    {
      // test if the tab is off on the right
      rcItem.right -= iTotalArrowWidth;
      int iTabAreaWidth = GetTotalTabAreaWidth();
      if (rcItem.right > iTabAreaWidth)
        m_nOffset += (rcItem.right - iTabAreaWidth);
    }
  }
  
  // hide/show managed controls
  ASSERT(iPrevSel >= 0);
  if (iPrevSel < cItems  &&  m_tcbItems[iPrevSel]->pWnd->GetSafeHwnd())
  {
    m_tcbItems[iPrevSel]->pWnd->ShowWindow(SW_HIDE);
  }
  if (m_tcbItems[m_nCurSel]->pWnd->GetSafeHwnd())
  {
    m_tcbItems[m_nCurSel]->pWnd->ShowWindow(SW_SHOW);
  }
  
  // reset scroll bar position
  SyncScrollBar();
  
  EnableButtons();
  InvalidateTabs();
  
  return iPrevSel;
}

void CXTFlatTabCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
  TCHITTESTINFO tchtinfo;
  tchtinfo.pt = point;
  
  // sizing grip?
  if (m_rectGripper.PtInRect(point))
  {
    ASSERT(m_bTracking == false);
    SetTracking(true);
    return;
  }
  
  // on a button?
  int iButton = ButtonHitTest(point);
  if (iButton >= 0)
  {
    CXTFTButtonState& b = m_buttons[iButton];
    if (b.m_bEnabled)
    {
      b.m_bPressed = true;
      RedrawWindow(b.m_rect);
      SetCapture();
    }
    return;
  }
  
  int iTab = HitTest(&tchtinfo);
  if ((iTab != -1) && (iTab != m_nCurSel))
  {
    // warn parent that the selection is about to change
    int id = GetDlgCtrlID();
    NMHDR hdr;
    hdr.hwndFrom = m_hWnd;
    hdr.idFrom = id;
    hdr.code = TCN_SELCHANGING;
    if (GetOwner()->SendMessage(WM_NOTIFY, id, (LPARAM)&hdr) == 0)
    {
      // parent has given permission for the selection to change
      SetCurSel(iTab);
      InvalidateTabs();
      
      // notify parent that the selection has changed
      hdr.hwndFrom = m_hWnd;
      hdr.idFrom = id;
      hdr.code = TCN_SELCHANGE;
      GetOwner()->SendMessage(WM_NOTIFY, id, (LPARAM)&hdr);
    }
  }
  
  CWnd::OnLButtonDown(nFlags, point);
}

void CXTFlatTabCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
  if (m_bTracking)
  {
    SetTracking(false);
  }
  
  // on a button?
  for (int i = 0; i < BUTTON_COUNT; ++i)
  {
    CXTFTButtonState& b = m_buttons[i];
    if (b.m_bEnabled & b.m_bPressed)
    {
      PostMessage(WM_COMMAND, b.m_iCommand, NULL);
      b.m_bPressed = false;
      RedrawWindow(b.m_rect);
      ReleaseCapture();
      return;
    }
  }
  
  CWnd::OnLButtonUp(nFlags, point);
}

void CXTFlatTabCtrl::OnPaint() 
{
  CPaintDC dc(this);
  
  // Get the client rect.
  CRect rectPaint(m_rectTabs);  // this the only part we care about
  
  CRect rectClip, r;
  dc.GetClipBox(rectClip);
  
  if (m_dwStyle & FTS_XT_HSCROLL)
  {
		  dc.ExcludeClipRect(&m_rectSB_H);
  }
  
  // Exclude the arrow buttons from being repainted.
  const int iTotalArrowWidth = GetTotalArrowWidth();
  CRect rcArrows(rectPaint);
  rcArrows.top  += 1;
  rcArrows.right = rcArrows.left+iTotalArrowWidth-1;
  
  // Paint to a memory device context to help
  // eliminate screen flicker.
  CXTMemDC memDC(&dc, rectPaint);
  
  memDC.FillSolidRect(0, 0, rectPaint.Width(), rectPaint.Height(),
    _HtAux.clr3DFace);
  
  // Draw a dark (shadow) line along the top of the control.
  CPen* pOldPen = memDC.SelectObject(&m_penShadow);
  memDC.MoveTo(-2,0);
  memDC.LineTo(rectPaint.Width(),0);
  memDC.SelectObject(pOldPen);
  
  int i;
  for (i = 0; i < sizeof(m_buttons)/sizeof(m_buttons[0]); ++i)
  {
    if (r.IntersectRect(rectClip, m_buttons[i].m_rect))
    {
      DrawButton(&memDC, m_buttons[i]);
    }
  }
  
  if (rectClip.right >= rcArrows.right)
  {
    const int nTotalTabWidth = GetTotalTabWidth();
    
    // Draw the tabs to an offscreen device context, this is done
    // so that we can "scroll" the entire tab group left or right whenever
    // any of the arrow buttons are pressed.
    CDC tabDC; tabDC.CreateCompatibleDC(&memDC);
    CBitmap bitmap; bitmap.CreateCompatibleBitmap(&memDC, nTotalTabWidth, m_cy);
    CBitmap* pOldBitmap = tabDC.SelectObject(&bitmap);
    
    // Fill the background color.
    CRect rcTabs(0,0,nTotalTabWidth,m_cy);
    tabDC.FillSolidRect(rcTabs, _HtAux.clr3DFace);
    
    // Define xy coordinates to draw each tab.
    const int iOverlap = GetOverlap();
    int x     = 0;
    int iSelX = 0;
    int y     = 0;
    
    // Draw all of the non-selected tabs first...
    const int cItems = GetItemCount();
    for (i = 0; i < cItems; i++)
    {
      if (i != m_nCurSel) {
        const int cx = DrawTab(&tabDC, CPoint(x,y), 
          false, m_tcbItems[i]->szTabLabel);
#ifdef _DEBUG
        CRect rcTab(0, 0, cx, m_cy), rcActual;
        rcTab.OffsetRect(x + iTotalArrowWidth - m_nOffset, y);
        ASSERT(cx == GetTabWidth(i));
        GetItemRect(i, rcActual);
        rcActual -= m_rectTabs.TopLeft();
        ASSERT(rcTab == rcActual);
#endif
        x += cx;
      }
      else {
        iSelX = x;
        x += GetTabWidth(i);
      }
      x -= iOverlap;
    }
    
    // then draw the selected tab. Make sure that m_TabList is not empty.
    if (m_nCurSel >= 0 && cItems > 0) {
      DrawTab(&tabDC, CPoint(iSelX,y), true, m_tcbItems[m_nCurSel]->szTabLabel);
    }
    
    // blit the bitmap onto the memDC.
    memDC.BitBlt(iTotalArrowWidth, 0, GetTotalTabAreaWidth(),
      m_cy, &tabDC, m_nOffset, 0, SRCCOPY);
    // cleanup.
    tabDC.SelectObject(pOldBitmap);
    tabDC.DeleteDC();
    bitmap.DeleteObject();
  }
  if (m_dwStyle & FTS_XT_HSCROLL)
  {
    r = m_rectGripper;
    r.OffsetRect(0, -m_rectTabs.top);
    DrawGripper(&memDC, r);
  }
}

void CXTFlatTabCtrl::DrawGripper(CDC* pDC, CRect rect) const
{
  pDC->Draw3dRect(rect, _HtAux.clr3DLight, _HtAux.clr3DShadow);
  rect.InflateRect(-CX_BORDER, -CY_BORDER);
  
  // fill the middle
  pDC->FillSolidRect(rect, _HtAux.clr3DFace);
}

/*
*    Height ************************
*         \*| |                  |  *
*         *\| |xxxxxxxxxxxxxxxxxx|   *
*        *  | |         |        |    *
*       *---+-+         |        +-----*
*          |  \       Text       
*        Base  \                 
*               Margin
*   
*     Base   = Height / 2
*     Margin = Base / 2
*/
int CXTFlatTabCtrl::DrawTab(CDC* pDC, const CPoint& pt, bool bSelected, 
                            LPCTSTR lpszTabLabel)
{
  // Saves the current state of the device context, we will
  // restore the state when the method looses scope. This will
  // simplify selecting objects.
  const int nSavedDC = pDC->SaveDC();
  
  const int iHeight = m_cy;
  const int iBase   = iHeight / 2;
  const int iWidth  = iHeight + iHeight / 2; // 2 bases + 2 margins
  
  const bool bBottom = (m_dwStyle & FTS_XT_BOTTOM) == FTS_XT_BOTTOM;
  
  pDC->SelectObject(bSelected ? m_pBoldFont : m_pNormFont);
  const CSize szText = pDC->GetTextExtent(lpszTabLabel);
  
  CRect rcText;
  rcText.left   = pt.x + iBase + iBase / 2;
  rcText.top    = pt.y + ((iHeight - szText.cy)/2)-1;
  rcText.right  = rcText.left + szText.cx;
  rcText.bottom = rcText.top  + szText.cy;
  
  COLORREF crBack;
  COLORREF crFore;
  CPen *pPenBack;
  if (bSelected)
  {
    crBack = _HtAux.clrWindow;
    crFore = _HtAux.clrWindowText;
    pPenBack = &m_penBackSel;
  }
  else
  {
    crBack = _HtAux.clr3DFace;
    crFore = _HtAux.clrBtnText;
    pPenBack = &m_penBackNonSel;
  }
  
  CBrush brush;
  brush.CreateSolidBrush(crBack);
  
  POINT points[] =
  {
    { pt.x,                                  pt.y + iHeight - 1 },
    { pt.x + iBase - 1,                      pt.y               },
    { pt.x + szText.cx + iWidth - iBase - 1, pt.y               },
    { pt.x + szText.cx + iWidth - 1,         pt.y + iHeight - 1 }
  };
  
  // swap vertical coordinates
  if (bBottom)
  {
    points[0].y = points[1].y;
    points[2].y = points[3].y;
    points[1].y = points[2].y;
    points[3].y = points[0].y;
  }
  
  pDC->SelectObject(&m_penOutline);
  pDC->SetBkColor(crBack);
  pDC->SelectObject(&brush);
  pDC->Polygon(points, 4);
  pDC->SetTextColor(crFore);
  pDC->DrawText(lpszTabLabel, rcText, DT_CENTER);
  pDC->SelectObject(&m_penShadow);
  
  if (bSelected)
  {
    pDC->MoveTo(pt.x + iBase, points[1].y);
    pDC->LineTo(pt.x + iBase * 2 + szText.cx - 1, points[1].y);
    pDC->SelectObject(pPenBack);
    pDC->MoveTo(pt.x + 1, points[0].y);
    pDC->LineTo(pt.x + szText.cx + iWidth - 1, points[0].y);
  }
  else
  {
    // highlight line on left
    pDC->SelectObject(&m_penWindow);
    pDC->MoveTo(pt.x + 1, points[0].y);
    pDC->LineTo(pt.x + 1 + iBase, points[0].y + iHeight);
    
    // shadow line on top
    pDC->SelectObject((CPen *)&m_penShadow);
    pDC->MoveTo(pt.x, points[0].y);
    pDC->LineTo(pt.x + szText.cx + iWidth, points[0].y);
    
    // shadow line on bottom
    pDC->MoveTo(pt.x + iBase, points[1].y);
    pDC->LineTo(pt.x + szText.cx + iHeight - 1, points[1].y);
  }
  
  // Cleanup.
  pDC->RestoreDC(nSavedDC);
  brush.DeleteObject();
  
  return szText.cx + iWidth;
}

void CXTFlatTabCtrl::DrawButton(CDC* pDC, CXTFTButtonState& button_state) const
{
  CRect r(button_state.m_rect);
  if (r.IsRectEmpty()) return;
  r.OffsetRect(0, -m_rectTabs.top);
  if (button_state.m_bPressed)
  {
    pDC->Draw3dRect(r, _HtAux.clr3DShadow, _HtAux.clr3DLight);
  }
  else
  {
    pDC->Draw3dRect(r, _HtAux.clr3DLight, _HtAux.clr3DShadow);
  }
  r.DeflateRect(1, 1);
  pDC->FillSolidRect(r, _HtAux.clr3DFace);
  
  CPen *pOldPen = pDC->SelectObject((CPen *)(button_state.m_bEnabled?
    &m_penOutline : &m_penShadow));
  
  int direction = 1 - ((button_state.m_IconType & 0xFF00) >> 8);
  int x = (direction < 0)? r.right : r.left, y;
  
  const int arrow_cy = r.Width() / 2 + 2;
  const int arrow_cx = (arrow_cy + 1) / 2 + 1;
  const int top      = r.top + (r.Height() - arrow_cy) / 2;
  
  x += (((r.Width() - arrow_cx) / 2) * direction);
  y = top;
  
  // draw arrow
  int height = arrow_cy;
  while (height > 0)
  {
    pDC->MoveTo(x, y);
    pDC->LineTo(x, y + height);
    y += 1;
    x += direction;
    height -= 2;
  }
  
  if (button_state.m_IconType & 0xFF)
  {
    x += (1 * direction);
    pDC->MoveTo(x, top);
    pDC->LineTo(x, top + arrow_cy);
  }
  
  pDC->SelectObject(pOldPen);
}

BOOL CXTFlatTabCtrl::PreTranslateMessage(MSG* pMsg) 
{
  ASSERT_VALID(this);
  if (pMsg->message == WM_KEYDOWN)
  {
    if (m_bTracking  &&  pMsg->wParam == VK_ESCAPE)
    {
      SetTracking(false);
      return TRUE;
    }
  }
  if (::IsWindow(m_ToolTip.m_hWnd))
  {
    if(pMsg->message == WM_MOUSEMOVE && pMsg->hwnd == m_hWnd)
    {
      CPoint Point(LOWORD(pMsg->lParam), HIWORD(pMsg->lParam));
      
      TCHITTESTINFO htInfo;
      htInfo.pt = Point;
      int iTab = HitTest(&htInfo);
      
      if (iTab >= 0)
      {
        static CString strOldTipText;
        CString strNewTipText = m_tcbItems[iTab]->szToolTipLabel;
        
        m_ToolTip.GetText(strOldTipText, this);
        
        // If the tip text differs, update the tooltip control.
        if (strNewTipText != strOldTipText)
        {
          m_ToolTip.UpdateTipText(strNewTipText, this);
          strOldTipText = strNewTipText;
        }
        
        // Pass on to tooltip.
        m_ToolTip.RelayEvent(pMsg);
      }
      else  {
        m_ToolTip.SendMessage(TTM_POP, 0, 0L);
      }
    }
    else {
      m_ToolTip.SendMessage(TTM_POP, 0, 0L);
    }
  }
  
  return CWnd::PreTranslateMessage(pMsg);
}

void CXTFlatTabCtrl::SetTipText(int nItem, LPCTSTR lpszTabTip)
{
  const int cItems = GetItemCount();
  if (nItem < 0 || nItem >= cItems)
  {
    ASSERT(0);
    return;
  }
  m_tcbItems[nItem]->szToolTipLabel = lpszTabTip;
}

CString CXTFlatTabCtrl::GetTipText(int nItem)
{
  const int cItems = GetItemCount();
  if (nItem < 0 || nItem >= cItems)
  {
    ASSERT(0);
    return _T("");
  }
  return m_tcbItems[nItem]->szToolTipLabel;
}

void CXTFlatTabCtrl::Home()
{
  OnHomeArrow();
}

void CXTFlatTabCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
  if (m_bTracking)
  {
    // resize
    SetGripperPosition(point.x + m_xTrackingDelta, false);
  }
  
  CWnd::OnMouseMove(nFlags, point);
}

BOOL CXTFlatTabCtrl::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
  if (m_bTracking  &&  GetCapture() != this)
  {
    m_bTracking = FALSE;
  }
  
  POINT pt;
  GetCursorPos(&pt);
  ScreenToClient(&pt);
  if (m_bTracking  ||  m_rectGripper.PtInRect(pt))
  {
    ::SetCursor(_HtAux.hcurHSplitBar);
    return TRUE;
  }
  
  return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

void CXTFlatTabCtrl::SetTracking(bool bTracking)
{
  if (m_bTracking == bTracking)
  {
    return;
  }
  
  m_bTracking = bTracking;
  if (bTracking)
  {
    SetCapture();
    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(&pt);
    m_xTrackingDelta = GetGripperPosition() - pt.x;
    m_pWndLastFocus = SetFocus();
  }
  else
  {
    ReleaseCapture();
    if (::IsWindow(m_pWndLastFocus->GetSafeHwnd()))
    {
      m_pWndLastFocus->SetFocus();
    }
    else
    {
      m_pWndLastFocus = NULL;
    }
  }
}

void CXTFlatTabCtrl::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
  // on a button?
  int iButton = ButtonHitTest(point);
  if (iButton >= 0)
  {
    CXTFTButtonState& b = m_buttons[iButton];
    if (b.m_bEnabled)
    {
      SetCapture();
      b.m_bPressed = true;
      RedrawWindow(b.m_rect);
    }
    return;
  }
  
  CWnd::OnLButtonDblClk(nFlags, point);
}

void CXTFlatTabCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
  UNUSED_ALWAYS(pScrollBar);
  
  CWnd *pWndControl = m_tcbItems[m_nCurSel]->pWnd;
  if (pWndControl->GetSafeHwnd())
  {
    if (nSBCode == SB_THUMBPOSITION || nSBCode == SB_THUMBTRACK)
    {
      int dx = nPos - pWndControl->GetScrollPos(SB_HORZ);
      if (dx)
      {
        pWndControl->SendMessage(LVM_SCROLL, dx, 0);
      }
    }
    
    // pass message to control's scroll bar
    _AFX_THREAD_STATE* pThreadState = AfxGetThreadState();
    pWndControl->SendMessage(
      pThreadState->m_lastSentMsg.message,
      pThreadState->m_lastSentMsg.wParam, 
      (LPARAM)pWndControl->GetScrollBarCtrl(SB_HORZ)->GetSafeHwnd());
    
    // reflect changes in our scroll bar
    SyncScrollBar();
  }
}

void CXTFlatTabCtrl::SyncScrollBar()
{
  if (!m_ScrollBar_H.m_hWnd)
  {
    return;
  }
  
  CWnd *pWndControl = NULL;
  if (m_nCurSel >= 0)
  {
    pWndControl = m_tcbItems[m_nCurSel]->pWnd;
  }
  if (pWndControl->GetSafeHwnd())
  {
    pWndControl->ShowScrollBar(SB_HORZ, FALSE);
    pWndControl->ModifyStyle(WS_HSCROLL, 0, SWP_DRAWFRAME);
    
    SCROLLINFO si;
    ZeroMemory(&si, sizeof(si));
    si.cbSize = sizeof(si);
    si.fMask = SIF_ALL;
    
    if (!pWndControl->GetScrollInfo (SB_HORZ, &si) ||
      si.nPage == 0  ||
      si.nMin + (int) si.nPage >= si.nMax)
    {
      m_ScrollBar_H.EnableScrollBar (ESB_DISABLE_BOTH);
    }
    else
    {
      m_ScrollBar_H.EnableScrollBar (ESB_ENABLE_BOTH);
      m_ScrollBar_H.SetScrollInfo (&si);
    }
  }
  else
  {
    m_ScrollBar_H.EnableScrollBar (ESB_DISABLE_BOTH);
  }
}

BOOL CXTFlatTabCtrl::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
  NMHDR* pNMHDR = (NMHDR*)lParam;
  ASSERT (pNMHDR != NULL);
  
  BOOL bRetVal = CWnd::OnNotify(wParam, lParam, pResult);
  
  if (pNMHDR->code == HDN_ITEMCHANGED)
  {
    SyncScrollBar();
  }
  
  return bRetVal;
}

void CXTFlatTabCtrl::RecalcLayout()
{
  m_rectViews.left  = m_rectTabs.left  = 0;
  m_rectViews.right = m_rectTabs.right = m_nClientWidth;
  if (m_dwStyle & FTS_XT_BOTTOM)
  {
    m_rectTabs.top = m_nClientHeight - m_cy;
    m_rectViews.top = 0;
  }
  else
  {
    m_rectTabs.top = 0;
    m_rectViews.top = m_cy;
  }
  m_rectTabs. bottom = m_rectTabs.top  + m_cy;
  m_rectViews.bottom = m_rectViews.top + m_nClientHeight - m_cy;
  
  int nIndex;
  
  // update managed view positions
  if (m_bManagingViews)
  {
    const int cItems = GetItemCount();
    for (nIndex = 0; nIndex < cItems; ++nIndex)
    {
      ASSERT(m_tcbItems[nIndex]->pWnd->GetSafeHwnd());
      m_tcbItems[nIndex]->pWnd->SetWindowPos(NULL, 
        m_rectViews.left, m_rectViews.top,
        m_rectViews.Width(), m_rectViews.Height(), 
        SWP_NOZORDER | SWP_NOREDRAW);
    }
  }
  
  // update arrow buttons if we have them
  if (m_dwStyle & FTS_XT_HASARROWS)
  {
    CRect btnRects[] =
    {
      CRect(0,      m_rectTabs.top + 1, m_cx,   m_rectTabs.bottom),
        CRect(m_cx,   m_rectTabs.top + 1, m_cx*2, m_rectTabs.bottom),
        CRect(m_cx*2, m_rectTabs.top + 1, m_cx*3, m_rectTabs.bottom),
        CRect(m_cx*3, m_rectTabs.top + 1, m_cx*4, m_rectTabs.bottom) 
    };
    
    const int cButtons = (m_dwStyle & FTS_XT_HASHOMEEND)? 4 : 2;
    for (nIndex = 0; nIndex < cButtons; ++nIndex)
    {
      m_buttons[nIndex].m_rect = btnRects[nIndex];
    }
  }
  
  EnableButtons();
}

LPCTSTR CXTFlatTabCtrl::GetItemText(int nIndex) const
{
  if (nIndex < 0  ||  nIndex >= GetItemCount())
  {
    return NULL;
  }
  
  return m_tcbItems[nIndex]->szTabLabel;
}

bool CXTFlatTabCtrl::SetItemText(int nIndex, LPCTSTR pszText)
{
  if (nIndex < 0  ||  nIndex >= GetItemCount())
  {
    return false;
  }
  
  m_tcbItems[nIndex]->szTabLabel = pszText;
  RecalcLayout();
  InvalidateTabs();
  return true;
}

CWnd *CXTFlatTabCtrl::GetItemWindow(int nIndex) const
{
  if (nIndex < 0  ||  nIndex >= GetItemCount())
  {
    return NULL;
  }
  
  return m_tcbItems[nIndex]->pWnd;
}

int CXTFlatTabCtrl::GetOverlap() const
{
  return ((m_cy / 2) + 2);
}
