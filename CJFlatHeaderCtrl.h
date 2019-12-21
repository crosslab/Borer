// CJFlatHeaderCtrl.h : header file
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
* $Revision: 10 $
* $Archive: /CodeJockey/Include/CJFlatHeaderCtrl.h $
*
* $History: CJFlatHeaderCtrl.h $
* 
* *****************  Version 10  *****************
* User: Kirk Stowell Date: 6/23/99    Time: 12:04a
* Updated in $/CodeJockey/Include
* 
* *****************  Version 9  *****************
* User: Kirk Stowell Date: 7/25/99    Time: 12:42a
* Updated in $/CodeJockey/Include
* 
* *****************  Version 8  *****************
* User: Kirk Stowell Date: 7/18/99    Time: 10:17p
* Updated in $/CodeJockey/Include
* Cleaned up inline functions, and import/export macro so that class will
* be imported when linked to, and exported at compile time.
* 
* *****************  Version 7  *****************
* User: Kirk Stowell Date: 6/14/99    Time: 10:43p
* Updated in $/CodeJockey/Include
* Cleaned up code to eliminate level 4 compilier warnings.
* 
* *****************  Version 6  *****************
* User: Kirk Stowell Date: 5/17/99    Time: 8:00p
* Updated in $/CodeJockey/Include
* Added popup menu support and vc5 compatibility.
* 
* *****************  Version 5  *****************
* User: Kirk Stowell Date: 4/15/99    Time: 4:27p
* Updated in $/CodeJockey/Include
* Igor Ostriz [iostriz@usa.net] - fixed bug with drag/drop and changing
* column order.
* 
* *****************  Version 4  *****************
* User: Kirk Stowell Date: 4/03/99    Time: 4:26p
* Updated in $/CodeJockey/Include
* Added comments and cleaned up code.
* 
* *****************  Version 3  *****************
* User: Kirk Stowell Date: 2/24/99    Time: 4:26p
* Updated in $/CodeJockey/Include
* Fixed repainting problem when header is moved or window is resized. The
* class now uses log font instead of hard coded Tahoma font.
* 
* *****************  Version 2  *****************
* User: Kirk Stowell Date: 1/31/99    Time: 4:27p
* Updated in $/CodeJockey/Include
* Fixed problem with sort arrow drawn. If hditem has an associated
* bitmap, the arrow is not drawn.
* 
* *****************  Version 1  *****************
* User: Kirk Stowell Date: 1/16/99    Time: 4:26p
* Created in $/CodeJockey/Include
* Initial release.
*
***************************************************************************/
/////////////////////////////////////////////////////////////////////////////

#ifndef __CJFLATHEADERCTRL_H__
#define __CJFLATHEADERCTRL_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "CJMenu.h"        // CCJMenu class declaration

// CCJFlatHeaderCtrl is a CHeaderCtrl derived class which is simular
// to the listbox flat header controls seen in Visual Studio and Outlook.
class CCJFlatHeaderCtrl : public CHeaderCtrl
{
  
public:
  
  // Default constructor
  //
  CCJFlatHeaderCtrl();
  
  // Virtual destructor
  //
  virtual ~CCJFlatHeaderCtrl();
  
protected:
  UINT	m_popToolbarID;	// popup menu toolbar resource id, associates 
  // toolbar icons with the popup menu.
  
  UINT	m_popupMenuID;	// popup menu resource id
  CCJMenu	m_popupMenu;	// popup menu
  int		m_nPos;			// index of the pop-up menu contained in the menu
  BOOL	m_bBoldFont;	// true for bold fonts see SetFontBold(...)
  BOOL	m_bLBtnDown;	// true if left mouse button is pressed
  BOOL	m_bSortAsc;		// used when column is pressed to draw sort arrow.
  CFont	m_Font;			// font the header will use
  int		m_nOffset;		// ammount to offset the sort arrow.
  int		m_nSortCol;		// last column pressed during sort.
  
public:
  
  // this member function is called to associate a menu and toolbar
  // resource with the context menu.
  //
  void SetMenuID(UINT popupMenuID, UINT popToolbarID=0, int nPos=0);
  
  // this member function returns the menu resource associated with
  // the tab control.
  //
  UINT GetMenuID();
  
  // this member function must be called after creation to initialize the
  // font the header will use.
  //
  void InitializeHeader(bool bBoldFont);
  
  // this member function can be used to toggle the font from bold to
  // normal.
  //
  void SetFontBold(BOOL bBoldFont = TRUE);
  
  // this member function is called by the header during sort
  // operations
  //
  int SetSortImage( int nCol, BOOL bAsc );
  
protected:
  
  // this member function is called by the header during paint
  // operations.
  //
  void DrawFlatBorder();
  
#ifdef _VC_VERSION_5
  // this member function was added for vc5 support. It returns the number
  // of columns currently in the header.
  //
  int CCJFlatHeaderCtrl::GetItemCount() const;
  BOOL GetOrderArray(LPINT piArray, int iCount= -1);
#endif
  
  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CCJFlatHeaderCtrl)
public:
  virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
  //}}AFX_VIRTUAL
  
  // Generated message map functions
protected:
  //{{AFX_MSG(CCJFlatHeaderCtrl)
  afx_msg void OnPaint();
  afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
  afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
  afx_msg LRESULT OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu);
  afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
  //}}AFX_MSG
  
  DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
//	Inline Functions
/////////////////////////////////////////////////////////////////////////////
#ifndef _CJXLIB_INLINE
#define _CJXLIB_INLINE inline
#endif // _AFXCMN_INLINE

_CJXLIB_INLINE void CCJFlatHeaderCtrl::SetMenuID(UINT popupMenuID, UINT popToolbarID, int nPos)
{ ASSERT(::IsWindow(m_hWnd)); m_popupMenuID=popupMenuID; m_popToolbarID=popToolbarID; m_nPos=nPos; }

_CJXLIB_INLINE UINT CCJFlatHeaderCtrl::GetMenuID()
{ ASSERT(::IsWindow(m_hWnd)); return m_popupMenuID; }

_CJXLIB_INLINE void CCJFlatHeaderCtrl::SetFontBold(BOOL bBoldFont)
{ ASSERT(::IsWindow(m_hWnd)); m_bBoldFont = bBoldFont; }

#ifdef _VC_VERSION_5
_CJXLIB_INLINE int CCJFlatHeaderCtrl::GetItemCount() const
{ ASSERT(::IsWindow(m_hWnd)); return (int) ::SendMessage(m_hWnd, HDM_GETITEMCOUNT, 0, 0L); }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // __CJFLATHEADERCTRL_H__
