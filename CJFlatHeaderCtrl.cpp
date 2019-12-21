// CJFlatHeaderCtrl.cpp : implementation file
//
// Copyright © 1998-99 Kirk W. Stowell
//		mailto:kstowell@codejockeys.com
//		http://www.codejockeys.com/kstowell/
//
// This source code may be used in compiled form in any way you desire.
// Source file(s) may be redistributed unmodified by any means PROVIDING 
// they ARE NOT sold for profit without the authors expressed written 
// consent, and providing that this notice and the authors name and all 
// copyright notices remain intact. This software is by no means to be 
// included as part of any third party components library, or as part any
// development solution that offers MFC extensions that are sold for profit. 
// 
// If the source code is used in any commercial applications then a statement 
// along the lines of:
// 
// "Portions Copyright © 1998-99 Kirk Stowell" must be included in the startup 
// banner, "About" box or printed documentation. This software is provided 
// "as is" without express or implied warranty. Use it at your own risk! The 
// author(s) accepts no liability for any damage/loss of business that this 
// product may cause.
//
/////////////////////////////////////////////////////////////////////////////
/****************************************************************************
*
* $Date: 6/23/99 12:04a $
* $Revision: 14 $
* $Archive: /CodeJockey/CJLibrary/CJFlatHeaderCtrl.cpp $
*
* $History: CJFlatHeaderCtrl.cpp $
* 
* *****************  Version 14  *****************
* User: Kirk Stowell Date: 6/23/99    Time: 12:04a
* Updated in $/CodeJockey/CJLibrary
* 
* *****************  Version 13  *****************
* User: Kirk Stowell Date: 7/25/99    Time: 10:00p
* Updated in $/CodeJockey/CJLibrary
* 
* *****************  Version 12  *****************
* User: Kirk Stowell Date: 7/25/99    Time: 12:30a
* Updated in $/CodeJockey/CJLibrary
* 
* *****************  Version 11  *****************
* User: Kirk Stowell Date: 7/25/99    Time: 12:15a
* Updated in $/CodeJockey/CJLibrary
* 
* *****************  Version 10  *****************
* User: Kirk Stowell Date: 6/23/99    Time: 12:33a
* Updated in $/CodeJockey/CJLibrary
* 
* *****************  Version 9  *****************
* User: Kirk Stowell Date: 7/18/99    Time: 10:27p
* Updated in $/CodeJockey/CJLibrary
* Added vc5 compatibility.
* 
* *****************  Version 8  *****************
* User: Kirk Stowell Date: 6/14/99    Time: 10:43p
* Updated in $/CodeJockey/CJ60Lib
* Cleaned up code to eliminate level 4 compilier warnings.
* 
* *****************  Version 7  *****************
* User: Kirk Stowell Date: 5/17/99    Time: 8:00p
* Updated in $/CodeJockey/CJ60Lib
* Added popup menu support and vc5 compatibility.
* 
* *****************  Version 6  *****************
* User: Kirk Stowell Date: 5/12/99    Time: 5:32a
* Updated in $/CodeJockey/CJ60Lib
* Added support for vc5 compatibility
* 
* *****************  Version 5  *****************
* User: Kirk Stowell Date: 4/15/99    Time: 4:27p
* Updated in $/CodeJockey/CJ60Lib
* Igor Ostriz [iostriz@usa.net] - fixed bug with drag/drop and changing
* column order.
* 
* *****************  Version 4  *****************
* User: Kirk Stowell Date: 4/03/99    Time: 4:26p
* Updated in $/CodeJockey/CJ60Lib
* Added comments and cleaned up code.
* 
* *****************  Version 3  *****************
* User: Kirk Stowell Date: 2/24/99    Time: 4:26p
* Updated in $/CodeJockey/CJ60Lib
* Fixed repainting problem when header is moved or window is resized. The
* class now uses log font instead of hard coded Tahoma font.
* 
* *****************  Version 2  *****************
* User: Kirk Stowell Date: 1/31/99    Time: 4:27p
* Updated in $/CodeJockey/CJ60Lib
* Fixed problem with sort arrow drawn. If hditem has an associated
* bitmap, the arrow is not drawn.
* 
* *****************  Version 1  *****************
* User: Kirk Stowell Date: 1/16/99    Time: 4:26p
* Created in $/CodeJockey/CJ60Lib
* Initial release.
*
***************************************************************************/
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CJFlatHeaderCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCJFlatHeaderCtrl

CCJFlatHeaderCtrl::CCJFlatHeaderCtrl()
{
  m_nSortCol		= -1;
  m_bBoldFont		= FALSE;
  m_nOffset		= 6;
  m_bLBtnDown		= FALSE;
  m_popupMenuID	= 0;
  m_popToolbarID	= 0;
  m_nPos			= 0;
}

CCJFlatHeaderCtrl::~CCJFlatHeaderCtrl()
{
}

BEGIN_MESSAGE_MAP(CCJFlatHeaderCtrl, CHeaderCtrl)
//{{AFX_MSG_MAP(CCJFlatHeaderCtrl)
ON_WM_PAINT()
ON_WM_WINDOWPOSCHANGING()
ON_WM_RBUTTONDOWN()
ON_WM_MEASUREITEM()
ON_WM_MENUCHAR()
ON_WM_INITMENUPOPUP()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCJFlatHeaderCtrl message handlers

void CCJFlatHeaderCtrl::InitializeHeader(bool bBoldFont)
{
  m_Font.DeleteObject();
  NONCLIENTMETRICS ncm;
  ncm.cbSize = sizeof(ncm);
  SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(ncm), &ncm, 0);
  if(bBoldFont)
    ncm.lfMessageFont.lfWeight = 700;
  VERIFY(m_Font.CreateFontIndirect(&ncm.lfMessageFont));
  SetFont(&m_Font);
  
  m_bBoldFont = bBoldFont;
}

int CCJFlatHeaderCtrl::SetSortImage(int nCol, BOOL bAsc)
{
  int nPrevCol = m_nSortCol;
  
  m_nSortCol = nCol;
  m_bSortAsc = bAsc;
  
  // Change the item to ownder drawn
  HD_ITEM hditem;
  
  hditem.mask = HDI_BITMAP | HDI_FORMAT;
  GetItem( nCol, &hditem );
  if (hditem.hbm == NULL)
  {
    hditem.fmt |= HDF_OWNERDRAW;
    SetItem( nCol, &hditem );
    
    // Invalidate header control so that it gets redrawn
    Invalidate();
  }
  
  return nPrevCol;
}

void CCJFlatHeaderCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
  CDC dc;
  
  dc.Attach( lpDrawItemStruct->hDC );
  
  // Get the column rect
  CRect rcLabel( lpDrawItemStruct->rcItem );
  
  // Save DC
  int nSavedDC = dc.SaveDC();
  
  // Set clipping region to limit drawing within column
  CRgn rgn;
  rgn.CreateRectRgnIndirect( &rcLabel );
  dc.SelectObject( &rgn );
  rgn.DeleteObject();
  
  // Draw the background
  COLORREF clr = ::GetSysColor( COLOR_3DFACE );
  CBrush brush( clr );
  dc.FillRect( rcLabel, &brush );
  dc.SetBkMode(TRANSPARENT);
  
  // Get the column text and format
  TCHAR buf[256];
  HD_ITEM hditem;
  
  hditem.mask = HDI_TEXT | HDI_FORMAT;
  hditem.pszText = buf;
  hditem.cchTextMax = 255;
  
  GetItem( lpDrawItemStruct->itemID, &hditem );
  
  // Determine format for drawing column label
  UINT uFormat = DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP 
    | DT_VCENTER | DT_END_ELLIPSIS ;
  
  if( hditem.fmt & HDF_CENTER)
    uFormat |= DT_CENTER;
  else if( hditem.fmt & HDF_RIGHT)
    uFormat |= DT_RIGHT;
  else
    uFormat |= DT_LEFT;
  
  // Adjust the rect if the mouse button is pressed on it
  if( lpDrawItemStruct->itemState == ODS_SELECTED )
  {
    rcLabel.left++;
    rcLabel.top += 2;
    rcLabel.right++;
  }
  
  // Adjust the rect further if Sort arrow is to be displayed
  if( lpDrawItemStruct->itemID == (UINT)m_nSortCol )
  {
    rcLabel.right -= 3 * m_nOffset;
  }
  
  rcLabel.left += m_nOffset;
  rcLabel.right -= m_nOffset;
  
  // Draw column label
  if( rcLabel.left < rcLabel.right )
  {
    if (m_bBoldFont) {
      dc.SelectObject(&m_Font);
    }
    dc.DrawText(buf,-1,rcLabel, uFormat);
  }
  
  // Draw the Sort arrow
  if( lpDrawItemStruct->itemID == (UINT)m_nSortCol )
  {
    CRect rcIcon( lpDrawItemStruct->rcItem );
    
    // Set up pens to use for drawing the triangle
    CPen penLite(PS_SOLID, 1, ::GetSysColor(COLOR_3DHILIGHT));
    CPen penShad(PS_SOLID, 1, ::GetSysColor(COLOR_3DSHADOW));
    CPen *pOldPen = dc.SelectObject( &penLite );
    
    if( m_bSortAsc )
    {
      // Draw triangle pointing upwards
      dc.MoveTo( rcIcon.right - 2*m_nOffset, m_nOffset-1);
      dc.LineTo( rcIcon.right - 3*m_nOffset/2, rcIcon.bottom - m_nOffset );
      dc.LineTo( rcIcon.right - 5*m_nOffset/2-2, rcIcon.bottom - m_nOffset );
      dc.MoveTo( rcIcon.right - 5*m_nOffset/2-1, rcIcon.bottom - m_nOffset-1 );
      
      dc.SelectObject( &penShad );
      dc.LineTo( rcIcon.right - 2*m_nOffset, m_nOffset-2);
    }
    else
    {
      // Draw triangle pointing downwords
      dc.MoveTo( rcIcon.right - 3*m_nOffset/2, m_nOffset-1);
      dc.LineTo( rcIcon.right - 2*m_nOffset-1, rcIcon.bottom - m_nOffset + 1 );
      dc.MoveTo( rcIcon.right - 2*m_nOffset-1, rcIcon.bottom - m_nOffset );
      
      dc.SelectObject( &penShad );
      dc.LineTo( rcIcon.right - 5*m_nOffset/2-1, m_nOffset -1 );
      dc.LineTo( rcIcon.right - 3*m_nOffset/2, m_nOffset -1);
    }
    
    // Restore the pen
    dc.SelectObject( pOldPen );
  }
  
  // Restore dc
  dc.RestoreDC( nSavedDC );
  
  // Detach the dc before returning
  dc.Detach();
}

void CCJFlatHeaderCtrl::OnPaint() 
{
  Default();
  DrawFlatBorder();
}

void CCJFlatHeaderCtrl::DrawFlatBorder()
{
  CDC* pDC = GetDC();
  
  CRect rci;
  GetWindowRect(&rci);
  ScreenToClient(&rci);
  
  // Cover up thick 3D border.
  pDC->Draw3dRect(rci, ::GetSysColor(COLOR_3DFACE),
    ::GetSysColor(COLOR_3DFACE));
  rci.DeflateRect(1,1);
  pDC->Draw3dRect(rci, ::GetSysColor(COLOR_3DFACE),
    ::GetSysColor(COLOR_3DFACE));
  
  // Draw flat style border around entire header.
  rci.InflateRect(1,1);
  pDC->Draw3dRect(rci, ::GetSysColor(COLOR_3DHILIGHT),
    ::GetSysColor(COLOR_3DSHADOW));
  
  // Create the pens for further cover-up.
  CPen penLite(PS_SOLID, 1, ::GetSysColor(COLOR_3DHILIGHT));
  CPen penShad(PS_SOLID, 1, ::GetSysColor(COLOR_3DSHADOW));
  CPen penFace(PS_SOLID, 1, ::GetSysColor(COLOR_3DFACE));
  CPen *pOldPen = pDC->SelectObject( &penLite );
  
  pDC->SelectObject(&penFace);
  pDC->MoveTo(rci.right-1, 2);
  pDC->LineTo(rci.right-1, rci.bottom-2);
  
  // Set up the header item struct.
  HD_ITEM hdi;
  memset (&hdi, 0, sizeof(HD_ITEM));
  hdi.fmt  = HDF_STRING | HDF_LEFT | HDF_OWNERDRAW;
  hdi.mask = HDI_WIDTH | HDI_TEXT | HDI_FORMAT;
  int cx = 0;
  
  int ic = GetItemCount();
  int *pioArray = new int[ic];
  GetOrderArray( pioArray, ic ); // get appearing order
  
  // must not omit second parameter: bug in 
  // WINCTRL6.CPP, mixed iCount and nCount
  
  // For each header item found, do further cover up.
  for (int i = 0; i < GetItemCount(); ++i)
  {
    GetItem(pioArray[i], &hdi);
    cx += hdi.cxy;
    
    pDC->SelectObject(&penShad);
    pDC->MoveTo(cx, 2);
    pDC->LineTo(cx, rci.bottom-2);
    
    pDC->SelectObject(&penLite);
    pDC->MoveTo(cx+1, 2);
    pDC->LineTo(cx+1, rci.bottom-2);
    
    pDC->SelectObject(&penFace);
    pDC->MoveTo(cx-1, 2);
    pDC->LineTo(cx-1, rci.bottom-2);
    
    pDC->SelectObject(&penFace);
    pDC->MoveTo(cx-2, 2);
    pDC->LineTo(cx-2, rci.bottom-2);
  } // end for loop
  
  delete [] pioArray; //clean up
  
  // Restore the pen and release device context.
  pDC->SelectObject( pOldPen );
  ReleaseDC(pDC);
}

void CCJFlatHeaderCtrl::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos) 
{
  lpwndpos->cx += 3;	// Stefan Belopotocan, 1999.5.11
  CHeaderCtrl::OnWindowPosChanging(lpwndpos);
  Invalidate();
}

void CCJFlatHeaderCtrl::OnRButtonDown(UINT /*nFlags*/, CPoint point) 
{
  // No menu was defined...
  if (!m_popupMenuID) {
    TRACE0(_T("Warning: No menu resource was associated with CCJTabCtrl.\n")); 
    return;
  }
  
  // Since we are using the main window as the
  // parent, we need to convert the point to screen
  // coordinates...
  CPoint pt = point;
  ClientToScreen(&pt);
  
  // Load the popup menu.
  VERIFY(m_popupMenu.LoadMenu(m_popupMenuID));
  CCJMenu* pPopup = (CCJMenu*)m_popupMenu.GetSubMenu(m_nPos);
  ASSERT(pPopup != NULL);
  
  // Load toolbar resource if any for menu icons.
  if (m_popToolbarID) {
    pPopup->LoadToolbar(m_popToolbarID);
  }
  
  // Display the popup menu, use the main window as its parent.
  pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
    pt.x, pt.y, AfxGetMainWnd());
  
  m_popupMenu.DestroyMenu();
}

void CCJFlatHeaderCtrl::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
  if (lpMeasureItemStruct->CtlType == ODT_MENU) 
  {
    if (IsMenu((HMENU)lpMeasureItemStruct->itemID)) {
      CMenu* pMenu = CMenu::FromHandle((HMENU)lpMeasureItemStruct->itemID);
      
      if (m_popupMenu.IsMenu(pMenu)) {
        m_popupMenu.MeasureItem(lpMeasureItemStruct);
        return;
      }
    }
  }
  
  CHeaderCtrl::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

LRESULT CCJFlatHeaderCtrl::OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu) 
{
  if (m_popupMenu.IsMenu(pMenu)) {
    return CCJMenu::FindKeyboardShortcut(nChar, nFlags, pMenu);
  }
  
  return CHeaderCtrl::OnMenuChar(nChar, nFlags, pMenu);
}

void CCJFlatHeaderCtrl::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu) 
{
  CHeaderCtrl::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
  
  if(!bSysMenu) {
    if (m_popupMenu.IsMenu(pPopupMenu)) {
      CCJMenu::UpdateMenu(pPopupMenu);
    }
  }
}

#ifdef _VC_VERSION_5
BOOL CCJFlatHeaderCtrl::GetOrderArray(LPINT piArray, int iCount /* = -1 */)
{
  ASSERT(::IsWindow(m_hWnd));
  
  // if -1 was passed, find the count ourselves
  
  int nCount = iCount;
  if (nCount == -1)
  {
    nCount = GetItemCount();
    
    if (nCount == -1)
      return FALSE;
  }
  
  ASSERT(AfxIsValidAddress(piArray, iCount * sizeof(int)));
  
  return (BOOL) ::SendMessage(m_hWnd, HDM_GETORDERARRAY,
    (WPARAM) iCount, (LPARAM) piArray);
}
#endif // _VC_VERSION_5