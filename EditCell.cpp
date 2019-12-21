#include "stdafx.h"
#include "Borer.h"

#include "EditCell.h"
#include "ComboItem.h"
#include "EditList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGEditCell

CGEditCell::CGEditCell (CListCtrl* pCtrl, int iItem, int iSubItem, CString sInitText)
:   bEscape (FALSE)
{
  pListCtrl = pCtrl;
  Item = iItem;
  SubItem = iSubItem;
  InitText = sInitText;
}

CGEditCell::~CGEditCell()
{
}

BEGIN_MESSAGE_MAP(CGEditCell, CEdit)
//{{AFX_MSG_MAP(CGEditCell)
ON_WM_KILLFOCUS()
ON_WM_NCDESTROY()
ON_WM_CHAR()
ON_WM_CREATE()
ON_WM_GETDLGCODE()
ON_WM_KEYUP()
ON_WM_KEYDOWN()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGEditCell message handlers

void 
CGEditCell::SetListText()
{
  CString Text;
  GetWindowText (Text);
  
  // Send Notification to parent of ListView ctrl
  LV_DISPINFO dispinfo;
  dispinfo.hdr.hwndFrom = GetParent()->m_hWnd;
  dispinfo.hdr.idFrom = GetDlgCtrlID();
  dispinfo.hdr.code = LVN_ENDLABELEDIT;
  
  dispinfo.item.mask = LVIF_TEXT;
  dispinfo.item.iItem = Item;
  dispinfo.item.iSubItem = SubItem;
  dispinfo.item.pszText = bEscape ? NULL : LPTSTR ((LPCTSTR) Text);
  dispinfo.item.cchTextMax = Text.GetLength();
  
  GetParent()->GetParent()->SendMessage (WM_NOTIFY, GetParent()->GetDlgCtrlID(), (LPARAM) &dispinfo);
}

BOOL 
CGEditCell::PreTranslateMessage (MSG* pMsg) 
{
  if (pMsg->message == WM_KEYDOWN)
  {
    if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_DELETE || 
      pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_TAB || 
      pMsg->wParam == VK_UP || pMsg->wParam == VK_DOWN || GetKeyState (VK_CONTROL))
    {
      ::TranslateMessage (pMsg);
      ::DispatchMessage (pMsg);
      return TRUE;		    	// DO NOT process further
    }
  }
  
  return CEdit::PreTranslateMessage (pMsg);
}

void 
CGEditCell::OnKillFocus (CWnd* pNewWnd) 
{
  CEdit::OnKillFocus(pNewWnd);
  
  SetListText();
  
  DestroyWindow();
}

void 
CGEditCell::OnNcDestroy() 
{
  CEdit::OnNcDestroy();
  
  delete this;
}

void 
CGEditCell::OnKeyDown (UINT nChar, UINT nRepCnt, UINT nFlags) 
{
  // Up and down are in the OnKeyDown so that the user can hold down the arrow
  // keys to scroll through the entries.
  BOOL Control = GetKeyState (VK_CONTROL) < 0;
  switch (nChar)
  {
		case VK_UP :
      {
        if (Item > 0)
          ((CEditList*)pListCtrl)->EditSubItem (Item - 1, SubItem);
        return;
      }
    case VK_DOWN :
      {
        ((CEditList*)pListCtrl)->EditSubItem (Item + 1, SubItem);
        return;
      }
    case VK_HOME :
      {
        if (!Control)
          break;
        
        ((CEditList*)pListCtrl)->EditSubItem (0, SubItem);
        return;
      }
    case VK_END :
      {
        if (!Control)
          break;
        
        int Count = ((CEditList*)pListCtrl)->GetItemCount() - 1;
        ((CEditList*)pListCtrl)->EditSubItem (Count, SubItem);
        return;
      }
  }
  
  CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

void 
CGEditCell::OnKeyUp (UINT nChar, UINT nRepCnt, UINT nFlags) 
{
  switch (nChar)
  {
		case VK_NEXT :
      {
        int Count = ((CEditList*)pListCtrl)->GetItemCount();
        int NewItem = Item + ((CEditList*)pListCtrl)->GetCountPerPage();
        if (Count > NewItem)
          ((CEditList*)pListCtrl)->EditSubItem (NewItem, SubItem);
        else
          ((CEditList*)pListCtrl)->EditSubItem (Count - 1, SubItem);
        return;
      }
    case VK_PRIOR :
      {
        int NewItem = Item - ((CEditList*)pListCtrl)->GetCountPerPage();
        if (NewItem > 0)
          ((CEditList*)pListCtrl)->EditSubItem (NewItem, SubItem);
        else
          ((CEditList*)pListCtrl)->EditSubItem (0, SubItem);
        return;
      }
  }
  
  CEdit::OnKeyUp (nChar, nRepCnt, nFlags);
}

void 
CGEditCell::OnChar (UINT nChar, UINT nRepCnt, UINT nFlags) 
{
  BOOL Shift = GetKeyState (VK_SHIFT) < 0;
  switch (nChar)
  {
		case VK_ESCAPE :
      {
        if (nChar == VK_ESCAPE)
          bEscape = TRUE;
        GetParent()->SetFocus();
        return;
      }
    case VK_RETURN :
      {
        SetListText();
        ((CEditList*)pListCtrl)->EditSubItem (Item + 1, 0);
        return;
      }
    case VK_TAB :
      {
        if (Shift)
        {
          if (SubItem > 0)
            ((CEditList*)pListCtrl)->EditSubItem (Item, SubItem - 1);
          else
          {
            if (Item > 0)
              ((CEditList*)pListCtrl)->EditSubItem (Item - 1, 2);
          }
        }
        else
        {
          if (SubItem < 2)
            ((CEditList*)pListCtrl)->EditSubItem (Item, SubItem + 1);
          else
            ((CEditList*)pListCtrl)->EditSubItem (Item + 1, 0);
        }
        return;
      }
  }
  
  CEdit::OnChar (nChar, nRepCnt, nFlags);
  
  // Resize edit control if needed
  
  // Get text extent
  CString Text;
  
  GetWindowText (Text);
  CWindowDC DC (this);
  CFont *pFont = GetParent()->GetFont();
  CFont *pFontDC = DC.SelectObject (pFont);
  CSize Size = DC.GetTextExtent (Text);
  DC.SelectObject (pFontDC);
  Size.cx += 5;			   	// add some extra buffer
  
  // Get client rect
  CRect Rect, ParentRect;
  GetClientRect (&Rect);
  GetParent()->GetClientRect (&ParentRect);
  
  // Transform rect to parent coordinates
  ClientToScreen (&Rect);
  GetParent()->ScreenToClient (&Rect);
  
  // Check whether control needs to be resized and whether there is space to grow
  if (Size.cx > Rect.Width())
  {
    if (Size.cx + Rect.left < ParentRect.right )
      Rect.right = Rect.left + Size.cx;
    else
      Rect.right = ParentRect.right;
    MoveWindow (&Rect);
  }
}

int 
CGEditCell::OnCreate (LPCREATESTRUCT lpCreateStruct) 
{
  if (CEdit::OnCreate (lpCreateStruct) == -1)
    return -1;
  
  // Set the proper font
  CFont* Font = GetParent()->GetFont();
  SetFont (Font);
  
  SetWindowText (InitText);
  SetFocus();
  SetSel (0, -1);
  return 0;
}

UINT 
CGEditCell::OnGetDlgCode() 
{
  return CEdit::OnGetDlgCode() | DLGC_WANTARROWS | DLGC_WANTTAB;
}