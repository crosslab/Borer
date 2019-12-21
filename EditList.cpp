#include "stdafx.h"
#include "Borer.h"

#include "EditCell.h"
#include "ComboItem.h"
#include "EditList.h"
#include "CommonDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditList
CEditList::CEditList()
{
  m_ipDrag =false;
}

CEditList::~CEditList()
{
}

BEGIN_MESSAGE_MAP(CEditList, CListCtrl)
//{{AFX_MSG_MAP(CEditList)
ON_WM_LBUTTONDOWN()
ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, OnEndlabeledit)
//}}AFX_MSG_MAP
ON_MESSAGE(MMM_LIST_ORDER, OnReorder)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditList message handlers
void CEditList::OnLButtonDown(UINT nFlags, CPoint Point) 
{
  CListCtrl::OnLButtonDown (nFlags, Point);
  if(m_ipDrag) {
    return;
  }
  
  int RowHit;
  int ColHit;
  
  if((RowHit = HitTestEx (Point, &ColHit)) !=-1) {
    if(GetWindowLong (m_hWnd, GWL_STYLE) & LVS_EDITLABELS) {
      if((m_nHotCol==ColHit) && (m_nHotItem==RowHit)) {
        if(!COL_Strings[m_nHotCol].IsEmpty()) {
          MakeCombo (RowHit, ColHit);
        }else {
          EditSubItem (RowHit, ColHit);
        }
      }else {
        m_nHotItem=RowHit;
        m_nHotCol=ColHit;
      }
    }
  }
}

void CEditList::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
  LV_DISPINFO *plvDispInfo = (LV_DISPINFO *)pNMHDR;
  LV_ITEM	*plvItem = &plvDispInfo->item;
  
  if (plvItem->pszText != NULL)
  {
    SetItemText (plvItem->iItem, plvItem->iSubItem, plvItem->pszText);
  }
  *pResult = FALSE;
}

BOOL hexNumberToInt1 (CString HexNumber, int& Number)
{
  char* pStopString;
  Number = strtoul (HexNumber, &pStopString, 16);
  return Number != ULONG_MAX;
} // hexNumberToInt

int CEditList::InsertItemEx (int Item)
{
  int Result = InsertItem (Item + 1, DefaultText);
  CString ItemVal, Temp;
  if (Item == 0)
    ItemVal = "1000";
  else
  {
    int HexVal;
    Temp = GetItemText (Item - 1, 1);
    hexNumberToInt1 (Temp, HexVal);
    ItemVal.Format ("%x", HexVal + 1);
  }
  
  SetItemText (Item, 1, ItemVal);
  
  CListCtrl::SetColumnWidth (2, LVSCW_AUTOSIZE_USEHEADER);
  
  return Result;
}

CEdit* CEditList::EditSubItem (int Item, int Column)
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

CComboBox * CEditList::MakeCombo(int comboItem, int comboCol)
{
#define IDC_COMBOBOXINLISTVIEW 0x1235
  
  CString strFind = GetItemText(comboItem, comboCol);
  
  //basic code start
  CRect rect;
  int offset = 0;
  // Make sure that the item is visible
  if( !EnsureVisible(comboItem, TRUE)) 
    return NULL;
  
  GetSubItemRect(comboItem, comboCol, LVIR_BOUNDS, rect);
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
  rect.right = rect.left + GetColumnWidth(comboCol);
  if(rect.right > rcClient.right) 
	   rect.right = rcClient.right;
  //basic code end
  
  rect.bottom += 30 * rect.Height();//dropdown area
  
  DWORD dwStyle =  WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL|CBS_DROPDOWNLIST | CBS_DISABLENOSCROLL;
  CComboBox *pList = new CComboItem(comboItem, comboCol, &COL_Strings[comboCol]);
  pList->Create(dwStyle, rect, this, IDC_COMBOBOXINLISTVIEW);
  pList->ModifyStyleEx(0,WS_EX_CLIENTEDGE);//can we tell at all
  
  pList->ShowDropDown();
  pList->SelectString(-1, strFind.GetBuffer(1));
  // The returned pointer should not be saved
  return pList;
}

// Taken from: Detecting column index of the item clicked by Zafir Anjum.
// http://www.codeguru.com/listview/col_index.shtml

// HitTestEx	- Determine the row index and column index for a point
// Returns		- the row index or -1 if point is not over a row
// point		- point to be tested.
// nCol			- to hold the column index
int CEditList::HitTestEx(CPoint& point, int* nCol) const
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

// Taken from: Adding a column by Zafir Anjum.
// http://www.codeguru.com/listview/add_column.shtml

// AddColumn      - adds column after the right most column
// Returns        - the index of the new column if successful or -1 otherwise.
// lpszColHeading - the column's heading
// nWidth         - Width of the column, in pixels. If this parameter is -1, 
//                  the column width is the same as previous column
// nFormat        - the alignment of the column. Can be LVCFMT_LEFT,
//                  LVCFMT_RIGHT, or LVCFMT_CENTER.
int CEditList::AddColumn(LPCTSTR lpszColHeading, int nWidth/*=-1*/, int nFormat/*=LVCFMT_LEFT*/)
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

// Taken from: Getting the number of columns in report view by Zafir Anjum.
// http://www.codeguru.com/listview/num_cols.shtml
int CEditList::GetColumnCount() const
{
  CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);
  return pHeader->GetItemCount();
}

// Taken from: Copying/Moving Rows in CListCtrl by James Spibey [spib@bigfoot.com]. 
// http://www.codeguru.com/listview/moving_rows.html
bool CEditList::CopyRow(int nFrom, int nTo)
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

// Taken from: Copying/Moving Rows in CListCtrl by James Spibey [spib@bigfoot.com]. 
// http://www.codeguru.com/listview/moving_rows.html
bool CEditList::MoveRow(int nFrom, int nTo)
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

/////////////////////////////////////////////////////////////////////////////
//功能: 处理协议通讯对象发送过来的消息
LRESULT CEditList::OnReorder(WPARAM wpMcu, LPARAM lpMcu)
{
  SetItemState(lpMcu, 0, LVIS_DROPHILITED);
  MoveRow(wpMcu,lpMcu);
  
  if((int)wpMcu > lpMcu) {
    SetItemState(lpMcu, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
  }else {
    SetItemState(lpMcu-1, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
  }
  return 0;
}
