// CJListCtrl.cpp : implementation file
// Based on the CListView articles from http://www.codeguru.com/listview
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
* $Date: 7/25/99 12:30a $
* $Revision: 6 $
* $Archive: /CodeJockey/CJLibrary/CJListCtrl.cpp $
*
* $History: CJListCtrl.cpp $
* 
* *****************  Version 6  *****************
* User: Kirk Stowell Date: 7/25/99    Time: 12:30a
* Updated in $/CodeJockey/CJLibrary
* 
* *****************  Version 5  *****************
* User: Kirk Stowell Date: 6/23/99    Time: 12:33a
* Updated in $/CodeJockey/CJLibrary
* 
* *****************  Version 4  *****************
* User: Kirk Stowell Date: 6/12/99    Time: 2:29a
* Updated in $/CodeJockey/CJ60Lib
* Cleaned up initialization, sorting and column info saving. Removed sort
* functions, which were replaced with the virtual function SortList(...).
* Override this function in your derived class to perform custom sorting.
* See CCJShellList for an implementation of this virtual function.
* 
* *****************  Version 3  *****************
* User: Kirk Stowell Date: 4/03/99    Time: 8:38p
* Updated in $/CodeJockey/CJ60Lib
* Added comments and cleaned up code.
* 
* *****************  Version 2  *****************
* User: Kirk Stowell Date: 3/03/99    Time: 8:37p
* Updated in $/CodeJockey/CJ60Lib
* Added InitializeFlatHeader() in order to initialize the list control
* manually.
* 
* *****************  Version 1  *****************
* User: Kirk Stowell Date: 1/16/99    Time: 8:37p
* Created in $/CodeJockey/CJ60Lib
* Initial release.
*
***************************************************************************/
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CJListCtrl.h"
#include "CJFlatHeaderCtrl.h"
#include "EditCell.h"
#include "ComboItem.h"
#include "CommonDef.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCJListCtrl
CCJListCtrl::CCJListCtrl()
{
  m_nMinSize		= 0;
  m_nMinColWidth	= 50;
  m_nMaxColWidth	= 500;
  m_nSortedCol	= -1;
  m_bAscending	= true;
  m_bAutoSave		= false;	
  m_bNoColSizing	= false;
  m_pHeaderCtrl	= NULL;
  m_clrText		= ::GetSysColor(COLOR_WINDOWTEXT);
  m_clrTextBk 	= ::GetSysColor(COLOR_WINDOW);
  
  m_ipDrag =false;
}

CCJListCtrl::~CCJListCtrl()
{
}

IMPLEMENT_DYNAMIC(CCJListCtrl, CListCtrl)

BEGIN_MESSAGE_MAP(CCJListCtrl, CListCtrl)
//{{AFX_MSG_MAP(CCJListCtrl)
ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
ON_WM_DESTROY()
ON_WM_HSCROLL()
ON_WM_VSCROLL()
ON_WM_LBUTTONDOWN()
ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, OnEndlabeledit)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCJListCtrl message handlers

// Taken from: Copying/Moving Rows in CListCtrl by James Spibey [spib@bigfoot.com]. 
// http://www.codeguru.com/listview/moving_rows.html
bool CCJListCtrl::MoveRow(int nFrom, int nTo)
{
  //Can't move to the same place, or from or to a negative index
  if(nFrom == nTo || nFrom < 0 || nTo < 0)
    return false;
  
  //First Copy the row to the new location
  if(CopyRow(nFrom, nTo))
  {
    //If we have just inserted a row before
    //this one in the list, we need to increment
    //our index.
    if(nFrom > nTo)
      DeleteItem(nFrom + 1);
    else
      DeleteItem(nFrom);
    
    return true;
  }
  else
    return false;
}

// Taken from: Copying/Moving Rows in CListCtrl by James Spibey [spib@bigfoot.com]. 
// http://www.codeguru.com/listview/moving_rows.html
bool CCJListCtrl::CopyRow(int nFrom, int nTo)
{
  //Can't move to the same place, or from or to a negative index
  if(nFrom == nTo || nFrom < 0 || nTo < 0)
    return false;
  
  //Copy the row to the new index
  InsertItem(nTo, GetItemText(nFrom, 0));
  
  //If row has been inserted before original
  //increment the original
  if(nFrom > nTo)
    nFrom++;
  
  //Loop through subitems
  for(int i = 1; i < GetColumnCount(); i++)
  {
    SetItemText(nTo, i, GetItemText(nFrom, i));
  }
  
  return true;
}

// Taken from: Getting the number of columns in report view by Zafir Anjum.
// http://www.codeguru.com/listview/num_cols.shtml
int CCJListCtrl::GetColumnCount() const
{
  CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);
  return pHeader->GetItemCount();
}

// Taken from: Simpler way to do this (using new version of Comctl32.dll) by Vidas [vibal@lrtc.lt].
// http://www.codeguru.com/mfc/comments/6432.shtml
void CCJListCtrl::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult) 
{
  LPNMLVCUSTOMDRAW lplvcd = (LPNMLVCUSTOMDRAW)pNMHDR;
  
  switch(lplvcd->nmcd.dwDrawStage)
  {
  case CDDS_PREPAINT:
    // Request prepaint notifications for each item.
    *pResult = CDRF_NOTIFYITEMDRAW;
    break;
    
  case CDDS_ITEMPREPAINT: // Requested notification
    if(lplvcd->nmcd.dwItemSpec % 2)
    {
      lplvcd->clrText   = m_clrText;
      lplvcd->clrTextBk = m_clrTextBk;
    }
    *pResult = CDRF_DODEFAULT;
    break;
  }
}

BOOL CCJListCtrl::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
  HD_NOTIFY *pHDNotify = (HD_NOTIFY*)lParam;
  
  switch( pHDNotify->hdr.code )
  {
    // Sorting the list when user clicks on column header by Zafir Anjum.
    // http://www.codeguru.com/listview/sort_on_col_click.shtml
  case HDN_ITEMCLICKA:
  case HDN_ITEMCLICKW:
    {
      if( pHDNotify->iButton == 0 )
      {
        // set the sort order.
        if( pHDNotify->iItem == m_nSortedCol )
          m_bAscending = !m_bAscending;
        else
          m_bAscending = true;
        
        // save the column index.
        m_nSortedCol = pHDNotify->iItem;
        
        // virtual call to sort list.
        SortList( m_nSortedCol, m_bAscending );
        
        // set the sort image in the header control.
        if( m_pHeaderCtrl && m_pHeaderCtrl->GetSafeHwnd( ))
          m_pHeaderCtrl->SetSortImage( m_nSortedCol, m_bAscending );
      }
    }
    break;
    
    // How to force a minimum column width Cees Mechielsen.
    // http://www.codeguru.com/mfc/comments/866.shtml
  case HDN_ITEMCHANGINGA:
  case HDN_ITEMCHANGINGW:
  case HDN_ENDTRACK:
    {
      if( pHDNotify->pitem->mask & HDI_WIDTH &&
        pHDNotify->pitem->cxy < m_nMinSize &&
        pHDNotify->pitem->cxy >= 0 )
      {
        pHDNotify->pitem->cxy = m_nMinSize;	// Set the column width
      }
    }
    break;
    
    // Prevent CListCtrl column resizing by Zafir Anjum.
    // http://www.codeguru.com/listview/no_col_resize.shtml
  case HDN_DIVIDERDBLCLICKA:
  case HDN_DIVIDERDBLCLICKW:
  case HDN_BEGINTRACKW:
  case HDN_BEGINTRACKA:
    {
      if(m_bNoColSizing)
      {
        *pResult = TRUE;                // disable tracking
        return TRUE;                    // Processed message
      }
      break;
    }
  }
  
  return CListCtrl::OnNotify(wParam, lParam, pResult);
}

bool CCJListCtrl::SortList(int nCol, bool bAscending)
{
  TRACE2("Column sort on column index %d, ascending=%d", nCol, bAscending);
  return true;
}

// Taken from: Adding a column by Zafir Anjum.
// http://www.codeguru.com/listview/add_column.shtml

// AddColumn      - adds column after the right most column
// Returns        - the index of the new column if successful or -1 otherwise.
// lpszColHeading - the column's heading
// nWidth         - Width of the column, in pixels. If this parameter is -1, 
//                  the column width is the same as previous column
// nFormat        - the alignment of the column. Can be LVCFMT_LEFT,
//                  LVCFMT_RIGHT, or LVCFMT_CENTER.
int CCJListCtrl::AddColumn(LPCTSTR lpszColHeading, int nWidth/*=-1*/, int nFormat/*=LVCFMT_LEFT*/)
{
  CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);
  int nColumnCount = pHeader->GetItemCount();
  
  if( nWidth == -1 )
  {
    // The line below return zero for ICON views
    //nWidth = GetColumnWidth( nColumnCount - 1 );
    
    // Get the column width of the previous column from header control
    HD_ITEM hd_item;
    hd_item.mask = HDI_WIDTH;               //indicate that we want the width
    pHeader->GetItem( nColumnCount - 1, &hd_item );
    nWidth = hd_item.cxy;
  }
  return InsertColumn( nColumnCount, lpszColHeading, nFormat, nWidth, nColumnCount );
}

bool CCJListCtrl::BuildColumns(int nCols, int* nWidth, int* nColString)
{
  for( int i = 0; i < nCols; ++i ) {
    CString	strTemp; strTemp.LoadString( nColString[i] );
    if(AddColumn(strTemp, nWidth[i])==-1)
      return false;
  }
  
  return true;
}

bool CCJListCtrl::BuildColumns(int nCols, int* nWidth, CString* strColString)
{
  for( int i = 0; i < nCols; ++i ) {
    if(AddColumn(strColString[i], nWidth[i])==-1)
      return false;
  }
  
  return true;
}

// Taken from: Detecting column index of the item clicked by Zafir Anjum.
// http://www.codeguru.com/listview/col_index.shtml

// HitTestEx	- Determine the row index and column index for a point
// Returns		- the row index or -1 if point is not over a row
// point		- point to be tested.
// nCol			- to hold the column index
int CCJListCtrl::HitTestEx(CPoint& point, int* nCol) const
{
  int colnum = 0;
  int row = HitTest( point, NULL );
  
  if( nCol ) *nCol = 0;
  
  // Make sure that the ListView is in LVS_REPORT
  if( (GetWindowLong(m_hWnd, GWL_STYLE) & LVS_TYPEMASK) != LVS_REPORT )
    return row;
  
  // Get the top and bottom row visible
  row = GetTopIndex();
  int bottom = row + GetCountPerPage();
  if( bottom > GetItemCount() )
    bottom = GetItemCount();
  
  // Get the number of columns
  CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);
  int nColumnCount = pHeader->GetItemCount();
  
  // Loop through the visible rows
  for( ;row <= bottom;row++)
  {
    // Get bounding rect of item and check whether point falls in it.
    CRect rect;
    GetItemRect( row, &rect, LVIR_BOUNDS );
    if( rect.PtInRect(point) )
    {
      // Now find the column
      for( colnum = 0; colnum < nColumnCount; colnum++ )
      {
        int colwidth = GetColumnWidth(colnum);
        if( point.x >= rect.left 
          && point.x <= (rect.left + colwidth ) )
        {
          if( nCol ) *nCol = colnum;
          return row;
        }
        rect.left += colwidth;
      }
    }
  }
  return -1;
}

bool CCJListCtrl::SubclassHeader(bool bBoldFont/*=false*/)
{
  // allocate memory for the flat header.
  m_pHeaderCtrl = new CCJFlatHeaderCtrl;
  ASSERT( m_pHeaderCtrl );
  
  // get the window handle to the existing header
  // control.
  HWND hWnd = GetDlgItem(0)->GetSafeHwnd();
  ASSERT( hWnd );
  
  // subclass the flat header control.
  if( !m_pHeaderCtrl->SubclassWindow( hWnd ))
    return false;
  
  // finish header initialization.
  m_pHeaderCtrl->InitializeHeader( bBoldFont );
  
  return true;
}

void CCJListCtrl::AutoSaveColumns(LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszDefault)
{
  m_bAutoSave = true;
  
  // initialize registry strings.
  if( lpszSection == NULL ) m_strSection = _T("Settings");
  else m_strSection = lpszSection;
  
  if( lpszEntry == NULL ) m_strEntry = _T("Column Info");
  else m_strEntry = lpszEntry;
  
  if( lpszDefault == NULL ) m_strDefault = _T("");
  else m_strDefault = lpszDefault;
  
  LoadColumnWidths();
}

void CCJListCtrl::SaveColumnWidths()
{
  // get a pointer to the header control.
  CHeaderCtrl* pHeader = DYNAMIC_DOWNCAST(CHeaderCtrl, GetDlgItem(0));
  ASSERT_KINDOF( CHeaderCtrl, pHeader );
  
  CString strValue;
  for( int i = 0; i < pHeader->GetItemCount(); ++i )
  {
    CString strTemp;
    strTemp.Format(_T("%d,"), GetColumnWidth( i ));
    strValue += strTemp;
  }
  
  AfxGetApp()->WriteProfileString( m_strSection, m_strEntry, strValue );
}

void CCJListCtrl::LoadColumnWidths()
{
  // get a pointer to the header control.
  CHeaderCtrl* pHeader = DYNAMIC_DOWNCAST(CHeaderCtrl, GetDlgItem(0));
  ASSERT_KINDOF( CHeaderCtrl, pHeader );
  
  for( int i = 0; i < pHeader->GetItemCount(); ++i )
    SetColumnWidth(i);
}

void CCJListCtrl::SetColumnWidth(int nCol)
{
  int nWidth = GetStoredWidth( nCol );
  if( nWidth > m_nMinColWidth )
    CListCtrl::SetColumnWidth( nCol, nWidth );
  else
    AutoSizeColumn( nCol );
}

int CCJListCtrl::GetStoredWidth(int nCol)
{
  // get the value from the registry.
  CString strValue = AfxGetApp()->GetProfileString(
    m_strSection, m_strEntry, m_strDefault );
  
  // extract the sub string to get the column width.
  CString strSubString;
  AfxExtractSubString( strSubString, strValue, nCol, _T(','));
  
  // return the width from the registry.
  return _ttoi( strSubString );
}

void CCJListCtrl::OnDestroy() 
{
  if( m_bAutoSave ) SaveColumnWidths();
  CListCtrl::OnDestroy();
}

// Taken from: Autosize a column to fit its content by Roger Onslow.
// http://www.codeguru.com/listview/autosize_col.shtml
// If you don't supply a column number, it will resize all columns.
void CCJListCtrl::AutoSizeColumn(int nCol/*=-1*/)
{
  // Call this after your list control is filled
  SetRedraw( false );
  
  int nMinCol = nCol < 0 ? 0 : nCol;
  int nMaxCol = nCol < 0 ? GetColumnCount()-1 : nCol;
  
  for (nCol = nMinCol; nCol <= nMaxCol; nCol++)
  {
    CListCtrl::SetColumnWidth( nCol, LVSCW_AUTOSIZE );
    int wc1 = GetColumnWidth( nCol );
    
    CListCtrl::SetColumnWidth( nCol, LVSCW_AUTOSIZE_USEHEADER );
    int wc2 = GetColumnWidth( nCol );
    int wc = max( m_nMinColWidth, max( wc1, wc2 ));
    
    if( wc > m_nMaxColWidth )
      wc = m_nMaxColWidth;
    
    // set the column width.
    CListCtrl::SetColumnWidth( nCol,wc );
  }
  
  SetRedraw();
}

BOOL hexNumberToInt (CString HexNumber, int& Number)
{
  char* pStopString;
  Number = strtoul (HexNumber, &pStopString, 16);
  return Number != ULONG_MAX;
} // hexNumberToInt

int CCJListCtrl::InsertItemEx (int Item)
{
  int Result = InsertItem (Item + 1, DefaultText);
  CString ItemVal, Temp;
  if (Item == 0)
    ItemVal = "1000";
  else
  {
    int HexVal;
    Temp = GetItemText (Item - 1, 1);
    hexNumberToInt (Temp, HexVal);
    ItemVal.Format ("%x", HexVal + 1);
  }
  
  SetItemText (Item, 1, ItemVal);
  
  CListCtrl::SetColumnWidth (2, LVSCW_AUTOSIZE_USEHEADER);
  
  return Result;
}

void CCJListCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
  if (GetFocus() != this) 
    SetFocus();
  
  CListCtrl::OnHScroll (nSBCode, nPos, pScrollBar);
}

void CCJListCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
  if (GetFocus() != this) 
    SetFocus();
  
  CListCtrl::OnVScroll (nSBCode, nPos, pScrollBar);
}

CComboBox * CCJListCtrl::MakeCombo(int nItem, int nSubItem)
{
#define IDC_COMBOBOXINLISTVIEW 0x1235
  
  CString strFind = GetItemText(nItem, nSubItem);
  
  //basic code start
  CRect rect;
  int offset = 0;
  // Make sure that the item is visible
  if( !EnsureVisible(nItem, TRUE)) 
    return NULL;
  
  GetSubItemRect(nItem, nSubItem, LVIR_BOUNDS, rect);
  // Now scroll if we need to expose the column
  CRect rcClient;
  GetClientRect(rcClient);
  if( offset + rect.left < 0 || offset + rect.left > rcClient.right )
  {
    CSize size;
    size.cx = offset + rect.left;
    size.cy = 0;
    Scroll(size);
    rect.left -= size.cx;
  }
  
  rect.left += offset;	
  rect.right = rect.left + GetColumnWidth(nSubItem);
  if(rect.right > rcClient.right) 
	   rect.right = rcClient.right;
  //basic code end
  
  rect.bottom += 30 * rect.Height();//dropdown area
  
  DWORD dwStyle =  WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL|CBS_DROPDOWNLIST | CBS_DISABLENOSCROLL;
  CComboBox *pList = new CComboItem(nItem, nSubItem, &m_strList);
  pList->Create(dwStyle, rect, this, IDC_COMBOBOXINLISTVIEW);
  pList->ModifyStyleEx(0,WS_EX_CLIENTEDGE);//can we tell at all
  
  pList->ShowDropDown();
  pList->SelectString(-1, strFind.GetBuffer(1));
  // The returned pointer should not be saved
  return pList;
}

CEdit* CCJListCtrl::EditSubItem (int Item, int Column)
{
  // The returned pointer should not be saved
  
  // Make sure that the item is visible
  if (!EnsureVisible (Item, TRUE)) 
  {
    InsertItemEx (Item);
    if (!EnsureVisible (Item, TRUE)) 
      return NULL;
  }
  
  // Make sure that nCol is valid
  CHeaderCtrl* pHeader = (CHeaderCtrl*) GetDlgItem(0);
  int nColumnCount = pHeader->GetItemCount();
  if (Column >= nColumnCount || GetColumnWidth (Column) < 5)
    return NULL;
  
  // Get the column offset
  int Offset = 0;
  for (int iColumn = 0; iColumn < Column; iColumn++)
    Offset += GetColumnWidth (iColumn);
  
  CRect Rect;
  GetItemRect (Item, &Rect, LVIR_BOUNDS);
  
  // Now scroll if we need to expose the column
  CRect ClientRect;
  GetClientRect (&ClientRect);
  if (Offset + Rect.left < 0 || Offset + Rect.left > ClientRect.right)
  {
    CSize Size;
    if (Offset + Rect.left > 0)
      Size.cx = -(Offset - Rect.left);
    else
      Size.cx = Offset - Rect.left;
    Size.cy = 0;
    Scroll (Size);
    Rect.left -= Size.cx;
  }
  
  // Get Column alignment
  LV_COLUMN lvCol;
  lvCol.mask = LVCF_FMT;
  GetColumn (Column, &lvCol);
  DWORD dwStyle;
  if ((lvCol.fmt & LVCFMT_JUSTIFYMASK) == LVCFMT_LEFT)
    dwStyle = ES_LEFT;
  else if ((lvCol.fmt & LVCFMT_JUSTIFYMASK) == LVCFMT_RIGHT)
    dwStyle = ES_RIGHT;
  else dwStyle = ES_CENTER;
  
  Rect.left += Offset+4;
  Rect.right = Rect.left + GetColumnWidth (Column) - 3;
  if (Rect.right > ClientRect.right)
    Rect.right = ClientRect.right;
  
  dwStyle |= WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL;
  CEdit *pEdit = new CGEditCell (this, Item, Column, GetItemText (Item, Column));
  pEdit->Create (dwStyle, Rect, this, IDC_EDITCELL);
  
  return pEdit;
}

void CCJListCtrl::OnLButtonDown(UINT nFlags, CPoint Point) 
{
  CListCtrl::OnLButtonDown (nFlags, Point);
  if(m_ipDrag) {
    return;
  }
  
  int Index;
  int ColNum;
  if((Index = HitTestEx (Point, &ColNum)) !=-1) {
    if(GetWindowLong (m_hWnd, GWL_STYLE) & LVS_EDITLABELS) {
      if((m_nColHit==ColNum) && (m_nItemHit==Index)) {
        if(m_nColHit==1) {
          MakeCombo (Index, ColNum);
        }else {
          EditSubItem (Index, ColNum);
        }
      }else {
        m_nItemHit=Index;
        m_nColHit=ColNum;
      }
    }
  }
}

void CCJListCtrl::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
  LV_DISPINFO *plvDispInfo = (LV_DISPINFO *)pNMHDR;
  LV_ITEM	*plvItem = &plvDispInfo->item;
  
  if (plvItem->pszText != NULL)
  {
    SetItemText (plvItem->iItem, plvItem->iSubItem, plvItem->pszText);
  }
  *pResult = FALSE;
}
