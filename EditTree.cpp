#include "stdafx.h"
#include "io.h"

#include "Borer.h"
#include "MainFrm.h"
#include "EditTree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CBorerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CEditTreeCtrl
CEditTreeCtrl::CEditTreeCtrl() 
{
  int aid[] =
  {
    IDC_DROP_COPY_ROOT,
      IDC_DROP_COPY_SON,
      IDC_DROP_MOVE_ABOVE,
      IDC_DROP_COPY_ABOVE,
      IDC_DROP_MOVE_ROOT,
      IDC_DROP_MOVE_SON,
      IDC_NODROP,
  }, k;
  
  ASSERT(ARRAY_SIZE(aid) == CUR_COUNT);
  
  m_uLimitText = 0;
  m_bDragging = FALSE;
  
  m_bInsertionMode = false;
  m_hCursor = NULL;
  m_bsave =false;
  
  for (k = 0; k < CUR_COUNT; k++)
    m_ahCursor[k] = theApp.LoadCursor(aid[k]);
}

BEGIN_MESSAGE_MAP(CEditTreeCtrl, CTreeCtrl)
//{{AFX_MSG_MAP(CEditTreeCtrl)
ON_COMMAND(ID_COLLAPSE_ALL_ENTIRE_TREE, OnCollapseAllEntireTree)
ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnBegindrag)
ON_WM_MOUSEMOVE()
ON_WM_LBUTTONUP()
ON_WM_DESTROY()
ON_WM_SETCURSOR()
ON_WM_TIMER()
ON_COMMAND(IDC_COUNT_ENTIRE_TREE, OnCountEntireTree)
ON_COMMAND(IDC_COUNT_SUBTREE, OnCountSubtree)
ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnItemexpanded)
ON_COMMAND(ID_CALCULATE_LEVEL, OnCalculateLevel)
ON_COMMAND(ID_SORT_SUBTREE_ALPHABETIC, OnSortSubtreeAlphabetic)
ON_COMMAND(ID_SORT_SUBTREE_NUMERIC, OnSortSubtreeNumeric)
ON_NOTIFY_REFLECT(TVN_BEGINLABELEDIT, OnBeginlabeledit)
ON_NOTIFY_REFLECT(TVN_ENDLABELEDIT, OnEndlabeledit)
ON_WM_CONTEXTMENU()
ON_COMMAND(ID_RENAME, OnRename)
ON_COMMAND(ID_ADD_CHILD, OnAddChild)
ON_COMMAND(ID_ADD_SIBLING, OnAddSibling)
ON_COMMAND(ID_DELETE_ITEM, OnDeleteItem)
ON_COMMAND(ID_DELETE_ALL_ITEMS, OnDeleteAllItems)
ON_COMMAND(IDC_EXPAND_ALL_TREE, OnExpandAllTree)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditTreeCtrl message handlers

/***********************************************************************************
* Keyboard Handling
***********************************************************************************/

BOOL CEditTreeCtrl::PreTranslateMessage(MSG* pMsg) 
{
  // When an item is being edited make sure the edit control
  // receives certain important key strokes
  
  if(GetEditControl())
  {
    if(pMsg->message == WM_KEYDOWN) 
    {
      if(pMsg->wParam == VK_INSERT)
      {
        // If VK_INSERT was preessed in course of editing, we want to cause
        // the program to add another sibling. Therefore, we simulate pressing of
        // VK_RETURN.
        m_bInsertionMode = true;
        pMsg->wParam = VK_RETURN;
      }
      else
        m_bInsertionMode = false;
    }
    ::TranslateMessage(pMsg);
    ::DispatchMessage(pMsg);
    return TRUE; // DO NOT process further
  }
  if(m_bDragging &&
    (pMsg->message == WM_KEYDOWN || pMsg->message == WM_KEYUP))
  {
    if(pMsg->wParam == VK_ESCAPE)
    {	// Cancel Drag Mode
      m_bDragging = false;
      ReleaseCapture();
      SelectDropTarget(NULL);
   			m_hCursor = NULL;
    }
    POINT pt;
    GetCursorPos(&pt);
    // Cause MouseMove() (and as a result OnSetCursor()) to be called.
    SetCursorPos(pt.x, pt.y);
    return true;
  }
  if(pMsg->message == WM_KEYDOWN) 
  {
    switch(pMsg->wParam)
    {
    case 'C':
      if(GetKeyState(VK_CONTROL) & 0x80000000) 
        OnSaveSubtree();
      break;
    case 'A':
      // Ctrl+A Paste m_ttTransfer above current item
      if(GetKeyState(VK_CONTROL) & 0x80000000) 
        OnLoadAbove(GetSelectedItem());
      break;
    case 'V':
      // Ctrl+V Paste m_ttTransfer as a son of current item
      // Ctrl+Shift+V Paste m_ttTransfer as a new root
      if(GetKeyState(VK_CONTROL) & 0x80000000) 
      {
        if(GetKeyState(VK_SHIFT) & 0x80000000) 
          OnLoadSubtree(TVI_ROOT);
        else
          OnLoadSubtree(GetSelectedItem());
      }
      break;
    case 'X':
      if(GetKeyState(VK_CONTROL) & 0x80000000) 
        CutSubtree();
      break;
    case 'N':
      // Ctrl+N Count Subtree
      // Ctrl+Shift+N Count entire tree
      if(GetKeyState(VK_CONTROL) & 0x80000000) 
      {
        if(GetKeyState(VK_SHIFT) & 0x80000000) 
          OnCountEntireTree();
        else
          OnCountSubtree();
      }
      break;
    case 'T':
      // Ctrl+T Sort Subtree Alphabetic
      // Ctrl+Shift+T Sort Subtree Numeric
      if(GetKeyState(VK_CONTROL) & 0x80000000) 
      {
        if(GetKeyState(VK_SHIFT) & 0x80000000) 
          OnSortSubtreeNumeric();
        else
          OnSortSubtreeAlphabetic();
      }
      break;
    case 'L':
      if(GetKeyState(VK_CONTROL) & 0x80000000) 
        OnCalculateLevel();
      break;
    case VK_SPACE:
    case VK_RETURN: 
      OnAddSibling();
      break;
    case VK_INSERT:
      if(GetKeyState(VK_CONTROL) & 0x80000000) 
        OnSaveEntireTree(FF_CLIPBOARD_TYPE, m_qtt);
      else if(GetKeyState(VK_SHIFT) & 0x80000000) 
        OnLoadEntireTree(FF_CLIPBOARD_TYPE, m_qtt);
      else
        OnAddChild();
      break;
    case VK_F2:
      OnRename();
      break;
    case VK_DELETE:
      if(GetKeyState(VK_CONTROL) & 0x80000000) 
        OnDeleteAllItems();
      else
        OnDeleteItem();
      break;
    default:
      // Default behaviour for other keys such as arrows
      return CTreeCtrl::PreTranslateMessage(pMsg);
    }
    return TRUE; // DO NOT process further
  }
  return CTreeCtrl::PreTranslateMessage(pMsg);
}

/***********************************************************************************
* Functions to handle Drag and drop to Copy/Move/Paste items
***********************************************************************************/

void CEditTreeCtrl::OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
  CPoint ptAction;
  NMTREEVIEW *pnmtv;
  
  GetCursorPos(&ptAction);
  ScreenToClient(&ptAction);
  ASSERT(!m_bDragging);
  m_bDragging = TRUE;
  m_bTimerABOVE_Active = false;
  m_bTimerBELOW_Active = false;
  m_uOldFlags = 0;
  
  // determine the item being dragged:
  pnmtv = (NMTREEVIEW*)pNMHDR;
  m_hitemDrag = pnmtv->itemNew.hItem;
  m_hitemDrop = NULL;
  
  SetCapture();
  SelectDropCursor();
}

void CEditTreeCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
  HTREEITEM	hitem;
  
  if(m_bDragging)
  {
    hitem = SelectDropCursor(&point);
    if(hitem != NULL)
    {
      SelectDropTarget(hitem);
      m_hitemDrop = hitem;
      
    }
  }
  CTreeCtrl::OnMouseMove(nFlags, point);
}

void CEditTreeCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
  OnButtonUp();
  CTreeCtrl::OnLButtonUp(nFlags, point);
}

void CEditTreeCtrl::OnButtonUp()
{
/************************************************************************************
Ensure m_ttTransfer is always allocated and deallocated correctly:
*************************************************************************************
1) This function allocates a CTreeType.
2) The CTreeType is used to save data from the TreeControl. This is done
in SaveTreeData()
3) At the end of the function, the CTreeType is deallocated.
  ************************************************************************************/
  int iCount;
  
  if(m_bDragging)
  {
    m_bDragging = FALSE;
    
    if(m_bTimerABOVE_Active)
    {
      KillTimer(TVHT_ABOVE);
      m_bTimerABOVE_Active = false;
    }
    if(m_bTimerBELOW_Active)
    {
      KillTimer(TVHT_BELOW);
      m_bTimerBELOW_Active = false;
    }
    
    iCount = GetCount();
    if(!m_ttTransfer.AllocateTree(iCount))
    {
      AfxMessageBox("Out of memory");
      return;
    }
    if(m_hCursor == m_ahCursor[CUR_COPY_ROOT] || 
      m_hCursor == m_ahCursor[CUR_MOVE_ROOT])
    {
      SaveTreeData(m_ttTransfer, m_hitemDrag, OP_SUBTREE);
      if(m_hCursor == m_ahCursor[CUR_MOVE_ROOT])
        DeleteItemM(m_hitemDrag);
      LoadTreeDataR(m_ttTransfer, TVI_ROOT, OP_SUBTREE);
      SelectVisibleItem(m_ttTransfer.m_pnt[1].hti);
		    ExpandM(m_hitemDrop, TVE_EXPAND);
    }
    // Dragging an item to itself or to a node of its subtree is
    // not allowed 
    else if(m_hitemDrag != m_hitemDrop && !IsChildNodeOf(m_hitemDrop, m_hitemDrag))
    {
      if(m_hCursor == m_ahCursor[CUR_MOVE_SON] ||
        m_hCursor == m_ahCursor[CUR_COPY_SON])
      {
        SaveTreeData(m_ttTransfer, m_hitemDrag, OP_SUBTREE);
        if(m_hCursor == m_ahCursor[CUR_MOVE_SON])
          DeleteItemM(m_hitemDrag);
        LoadTreeDataR(m_ttTransfer, m_hitemDrop, OP_SUBTREE);
        SelectVisibleItem(m_ttTransfer.m_pnt[1].hti);
        ExpandM(m_hitemDrop, TVE_EXPAND);
      }
      if(m_hCursor == m_ahCursor[CUR_MOVE_ABOVE] ||
        m_hCursor == m_ahCursor[CUR_COPY_ABOVE])
      {
        SaveTreeData(m_ttTransfer, m_hitemDrag, OP_SUBTREE);
        if(m_hCursor == m_ahCursor[CUR_MOVE_ABOVE])
        {
          DeleteItemM(m_hitemDrag);
        }
        OnLoadAbove(m_hitemDrop);
      }
    }
    else
    {
      MessageBeep(0);
      SelectVisibleItem(m_hitemDrag);
    } 
    
    ReleaseCapture();
    SelectDropTarget(NULL);
    m_hCursor = NULL;
    m_ttTransfer.DeAllocateTree();
  }
}

// Timer function to handle scrolling while dragging.
void CEditTreeCtrl::OnTimer(UINT nIDEvent) 
{
  if(nIDEvent == TVHT_ABOVE ) {
    SendMessage(WM_VSCROLL, SB_LINEUP, NULL);
  }else if(nIDEvent == TVHT_BELOW ) {
    SendMessage(WM_VSCROLL, SB_LINEDOWN, NULL);
  }
  CTreeCtrl::OnTimer(nIDEvent);
}

// Selects the appropriate cursor in dragging mode
// F3										- MOVE as a new root
// Ctrl+F3									- COPY as a new root
// Cursor on the right of an item			- MOVE as a son to the right of dropped item.
// Ctrl + Cursor on the right of an item	- COPY as a son to the right of dropped item.
// Cursor on an item or to its left			- MOVE above dropped item.
// Ctrl + Cursor on an item or to its left	- COPY above dropped item.

HTREEITEM CEditTreeCtrl::SelectDropCursor(CPoint *pPoint /*= NULL*/)
{
  HCURSOR hOldCursor = m_hCursor;
  UINT uFlags;
  HTREEITEM hitem = NULL;
  CString str;
  int nKey = 0;
  
  if(m_bDragging)
  {
    if(pPoint != NULL)
    {
      if(GetKeyState(VK_F3) & 0x80000000) 
        nKey = VK_F3;
      hitem = HitTest(*pPoint, &uFlags);
      
      // Set a Timer to scroll periodically, while dragging, if mouse cursor is 
      // either below or above the control.
      
      // The timer must be set only if the flags have changed since the last call.
      if(m_uOldFlags != uFlags)
      {
        m_uOldFlags = uFlags;
        if(uFlags & TVHT_ABOVE)
        {
          SetTimer(TVHT_ABOVE, SCROLL_SPEED, NULL);
          m_bTimerABOVE_Active = true;
        }
        else if(uFlags & TVHT_BELOW)
        {
          SetTimer(TVHT_BELOW, SCROLL_SPEED, NULL);
          m_bTimerBELOW_Active = true;
        }
        else
        {
          if(m_bTimerABOVE_Active)
          {
            KillTimer(TVHT_ABOVE);
            m_bTimerABOVE_Active = false;
          }
          if(m_bTimerBELOW_Active)
          {
            KillTimer(TVHT_BELOW);
            m_bTimerBELOW_Active = false;
          }
        }
      }
      
      // Dragging an item to itself or to a node of its subtree is
      // not allowed 
      if((m_hitemDrag == hitem || IsChildNodeOf(hitem, m_hitemDrag) 
        || hitem == NULL) && nKey != VK_F3)
      {
        m_hCursor = m_ahCursor[CUR_NODROP];
        SetCursor(m_hCursor);
        return NULL;
      }
    }
    if(nKey == VK_F3)
    {
      if(GetKeyState(VK_CONTROL) & 0x80000000) 
        m_hCursor = m_ahCursor[CUR_COPY_ROOT];
      else
        m_hCursor = m_ahCursor[CUR_MOVE_ROOT];
    }
    else if(uFlags & (TVHT_ONITEM | TVHT_ONITEMINDENT | TVHT_ONITEMBUTTON))
    {
      if(GetKeyState(VK_CONTROL) & 0x80000000) 
        m_hCursor = m_ahCursor[CUR_COPY_ABOVE];
      else
        m_hCursor = m_ahCursor[CUR_MOVE_ABOVE];
    }
    else if(GetKeyState(VK_CONTROL) & 0x80000000) 
      m_hCursor = m_ahCursor[CUR_COPY_SON];
    else
      m_hCursor = m_ahCursor[CUR_MOVE_SON];
    if(hOldCursor != m_hCursor)
      SetCursor(m_hCursor);
  }
  return hitem;
}

/***********************************************************************************
* Cursor Functions
***********************************************************************************/
BOOL CEditTreeCtrl::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
  if(m_hCursor == NULL)
    return CTreeCtrl::OnSetCursor(pWnd, nHitTest, message);
  SelectDropCursor();
  SetCursor(m_hCursor);
  return 0;
}

/***********************************************************************************
* Edit Functions
***********************************************************************************/

void CEditTreeCtrl::OnRename() 
{
  HTREEITEM hti;
  
  hti = GetSelectedItem();
  EditLabel(hti);
}

// Called when a item is being edited, when  we call the function
// 	EditLabel(hti); (See OnRename())

void CEditTreeCtrl::OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
  TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;
  CEdit *pEdit;
  
  pEdit = GetEditControl();
  pEdit->SetLimitText(m_uLimitText);
  *pResult = 0;
}

void CEditTreeCtrl::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
  TV_DISPINFO *ptvinfo;
  
  // Called at exit from Edit Mode
  ptvinfo = (TV_DISPINFO *)pNMHDR;
  if(ptvinfo->item.pszText != NULL)
  {
    ptvinfo->item.mask = TVIF_TEXT;
    
    SetItem(&ptvinfo->item);
    m_bsave =true;
  }
  if(m_bInsertionMode) // VK_INSERT was pressed in course of editing
    OnAddSibling();
  else
    m_bInsertionMode = false;
  *pResult = TRUE; // TRUE => Accept the label
}

// Set the maximum size of an edited item.
void CEditTreeCtrl::SetLimitText(UINT uLimitText)
{
  m_uLimitText = uLimitText;
}

/***********************************************************************************
* Add Child, Add Sibling and delete Functions
***********************************************************************************/ 

void CEditTreeCtrl::OnAddChild() 
{
  HTREEITEM hti, htiChild;
  hti = GetSelectedItem();
  htiChild = InsertPie("New Item", hti, TVI_LAST);
  EnsureVisible(htiChild);
  EditLabel(htiChild);
  Select(htiChild, TVGN_CARET);
}

void CEditTreeCtrl::OnAddSibling() 
{
  HTREEITEM hti, htiParent, htiChild;
  hti = GetSelectedItem();
  htiParent = GetParentItem(hti);
  htiChild = InsertPie("New Item", htiParent, TVI_LAST);
  EnsureVisible(htiChild);
  EditLabel(htiChild);
  Select(htiChild, TVGN_CARET);
}

void CEditTreeCtrl::OnDeleteItem() 
{
  HTREEITEM hti;
  
  hti = GetSelectedItem();
  if(hti != NULL)
  {
    if(AfxMessageBox("确认要删除吗？", MB_YESNO|MB_ICONSTOP)==IDYES)
    { 
      DeleteItemM(hti);
    }
 	}
}

void CEditTreeCtrl::OnDeleteAllItems() 
{
  if(AfxMessageBox("确认要删除整稞树吗？", MB_YESNO|MB_ICONSTOP)!=IDYES) {
    return;
  }
  
  int iCount = GetCount();
  RemovePie(TVI_ROOT);
  if(iCount > 0)  {
    m_bsave =true;
  }
}

/***********************************************************************************
* Functions to handle Ctrl+C, Ctrl+X, Ctrl+V, Ctrl+Shift+V
***********************************************************************************/

// Called when the user presses either Ctrl+C or Ctrl+X
void CEditTreeCtrl::OnSaveSubtree() 
{
  int iCount;
  
  iCount = GetCount();
  try
  {
    if(!m_ttTransfer.AllocateTree(iCount))
      throw TTE_MEMORY;
    m_hitemDrag = GetSelectedItem();
    if(!SaveTreeData(m_ttTransfer, m_hitemDrag, OP_SUBTREE))
      throw TTE_MEMORY;
  }
  catch(TREE_TYPE_ERROR fe)
  {
    if(fe == TTE_MEMORY)
		    AfxMessageBox("Out of memory");
  }
}

// Called when the user presses Ctrl+X
void CEditTreeCtrl::CutSubtree()
{
  OnSaveSubtree();
  OnDeleteItem();
}

// Called when the user presses Ctrl+V, Ctrl+Shift+V
void CEditTreeCtrl::OnLoadSubtree(HTREEITEM hti)
{
  if(m_ttTransfer.m_pnt != NULL)
  {
    LoadTreeDataR(m_ttTransfer, hti, OP_SUBTREE);
    hti = m_ttTransfer.m_pnt[1].hti;
    SelectVisibleItem(hti);
    ExpandM(hti, TVE_EXPAND);
  }
}

/***********************************************************************************
* Functions to handle Load Above 
***********************************************************************************/
// Called when the user presses Ctrl+A or when drop occurs while the above cursor is
// shown (see OnButtonUp())
//
//	1) LoadTreeDataR() is called to copy the dragged item (or the item selected when
//		    Ctrl+C or Ctrl+X was pressed), as the LAST child of the PARENT of:
//		- The dropped item in case of Drag and Drop
//		- The Selected item in case of Ctrl+A
//
//	2) A LOAD_ABOVE structure is built. It contains:
//		- The dragged item:										HTREEITEM htiLoadedItem;	
//		- The item above which the MOVE/COPY must be performed:	HTREEITEM hti;
//		- An array containing all the children of the parent	HTREEITEM *pChildrenOfParent;
//		- The size of this array:								int iSizeChildrenOfParent;
//
//	3) InsertLoadItemBeforeHti() is called to change the sibling orders in the array
//	   so that Load item stands above hti.
//	   
//    4) To sort the sibling in the order of the indices of
//	   the array.

void CEditTreeCtrl::OnLoadAbove(HTREEITEM hti)
{
  LOAD_ABOVE la;
  HTREEITEM htiParent;
  int iCount = GetCount();
  TVSORTCB tvscb;
  
  if(m_ttTransfer.m_pnt != NULL)
  {
    htiParent = GetParentItem(hti);
    LoadTreeDataR(m_ttTransfer, htiParent, OP_SUBTREE);
    SelectVisibleItem(hti);
    ExpandM(hti, TVE_EXPAND);
  }
  
  la.pChildrenOfParent = new HTREEITEM[iCount];
  if(la.pChildrenOfParent == NULL)
  {
    AfxMessageBox("Out of memory");
    return;
  }
  
  la.pChildrenOfParent[0] = GetChildItem(htiParent);
  for (la.iSizeChildrenOfParent = 1; 
  la.pChildrenOfParent[la.iSizeChildrenOfParent - 1] != NULL; 
  la.iSizeChildrenOfParent++)
    
  {
    la.pChildrenOfParent[la.iSizeChildrenOfParent] = 
      GetNextSiblingItem(la.pChildrenOfParent[la.iSizeChildrenOfParent-1]);
	 }
  
  la.iSizeChildrenOfParent--;
  la.hti = hti;
  la.htiLoadedItem = m_ttTransfer.m_pnt[1].hti;
  InsertLoadItemBeforeHti(la);
  
  tvscb.hParent = htiParent;
  tvscb.lpfnCompare = CompareForLoadAbove;
  tvscb.lParam = (LPARAM)&la;
  SortChildrenCB(&tvscb);
  SelectVisibleItem(la.htiLoadedItem);
  
  //	delete [] la.pChildrenOfParent;
  m_bsave = true;
}

//	Change the sibling orders in the array so that Load item stands above hti.
void CEditTreeCtrl::InsertLoadItemBeforeHti(LOAD_ABOVE &la)
{
  HTREEITEM htiLoadItem = la.htiLoadedItem;
  int idxLoadItem = SearchLoadAboveItem(la, la.htiLoadedItem);
  int idxHti = SearchLoadAboveItem(la, la.hti);
  
  if(idxHti < idxLoadItem)
  {
    memmove(la.pChildrenOfParent + idxHti + 1, la.pChildrenOfParent + idxHti,
      (idxLoadItem - idxHti) * sizeof(HTREEITEM));
    la.pChildrenOfParent[idxHti] = htiLoadItem;
  }
  else	// idxHti > idxLoadItem _ Should NOT happen if this function was called
  {		// from Load Above since idxLoadItem is the sibling which has the
    // greatest index. 	
    memmove(la.pChildrenOfParent + idxLoadItem, la.pChildrenOfParent + idxLoadItem + 1,
      (idxHti - idxLoadItem - 1) * sizeof(HTREEITEM));
    la.pChildrenOfParent[idxHti - 1] = htiLoadItem;
  }
}

// Searches an item in the la.pChildrenOfParent array and returns its index.
int SearchLoadAboveItem(LOAD_ABOVE &la, HTREEITEM hti)
{
  int k;
  
  for (k = 0; k <= la.iSizeChildrenOfParent; k++)
  {
    if(la.pChildrenOfParent[k] == hti)
      return k;
  }
  return -1; // Not found (should not happen)
}

int CALLBACK CompareForLoadAbove(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
  int i1, i2;
  LOAD_ABOVE *pla = (LOAD_ABOVE *)lParamSort;
  
  HTREEITEM hti1 = (HTREEITEM)lParam1;
  HTREEITEM hti2 = (HTREEITEM)lParam2;
  i1 = SearchLoadAboveItem(*pla, hti1);
  i2 = SearchLoadAboveItem(*pla, hti2);
  if(i1 > i2)
    return 1;
  if(i1 < i2)
    return -1;
  return 0;
}

/***********************************************************************************
* Functions to handle Expand/Collapse
***********************************************************************************/

/**************************************************************************************
//    ParseTree is a function, that do the folowing:
//        - Parse a SubTree in DFS (Depth First Search) (or parse all the tree if hti = TVI_ROOT)
//        - For every node visited, call the callback function pf.
//    (This is useful in order not to deal each time with the problem of writing a recursive
//     function to scan the tree. Same idea as qsort())
//     
//     This function is used here to handle Expand/Collapse but can be reused for other
//	   purposes.
**************************************************************************************/
void CEditTreeCtrl::ParseTree(PARSING_FUNCTION pf, HTREEITEM hti /* = TVI_ROOT */,
                              void *pvParam /* = NULL */)
{
  if(hti == TVI_ROOT)
    hti = GetRootItem(); 
  else
  {
    hti = GetChildItem(hti); 
  }
  while(hti != NULL)
  {
    (this->*pf)(hti, pvParam);
    ParseTree(pf, hti, pvParam);
    hti = GetNextSiblingItem(hti);
  }
}

// Called when the user selects Expand All from the context menu.
void CEditTreeCtrl::OnExpandAllTree() 
{
  ParseTree(pfExpand);
}


// Called when the user selects Collapse All from the context menu.
void CEditTreeCtrl::OnCollapseAllEntireTree() 
{
  ParseTree(pfCollapse);
}

// Note the second parameter must be present to comply with the definition
// of the PARSING_FUNCTION, but there is no need to give it a name as it's not used.
void CEditTreeCtrl::pfExpand(HTREEITEM hti, void *)
{
  ExpandM(hti, TVE_EXPAND);
}

// Note the second parameter must be present to comply with the definition
// of the PARSING_FUNCTION, but there is no need to give it a name as it's not used.
void CEditTreeCtrl::pfCollapse(HTREEITEM hti, void *)
{
  ExpandM(hti, TVE_COLLAPSE);
}

/***********************************************************************************
* Load Functions
***********************************************************************************/

//	1) Loads a tree from:
//		- A Directory to a CTreeType structure.
//		- A TRE file to a CTreeType structure.
//		- A IDT file to a CTreeType structure.
//		- A CSV file to a CTreeType structure.
//		- The Clipboard to a CTreeType structure.
//	2) If the loading ended successfully, LoadTreeDataR() is called then to transfer the tree
//		from the CTreeType structure to the Tree Control.

void CEditTreeCtrl::OnLoadEntireTree(FILE_FORMAT ff, CTreeType &tt)
{
/************************************************************************************
Ensure tt is always allocated and deallocated correctly:
*************************************************************************************
1) This function allocates a CTreeType.
The allocation is done in the functions:
- LoadTreeFromFile()
- LoadIndentTreeFromFile()
- LoadCsvTreeFromFile()
(These functions are never called from elsewhere)
2) The CTreeType is used to load data to the TreeControl. This is done
in LoadTreeDataR()
3) At the end of this function, the CTreeType is not neeeded anymore and
is deallocated.
  ************************************************************************************/
  WORD wTotalNbItems;
  CString str;
  BOOL rc;
  
  BeginWaitCursor(); // display the hourglass cursor
  if(m_strFileName.GetLength() < 1 )
  {
    return;
  }
  
  try
  {
    switch(ff)
    {
    case FF_DIRECTORY_TYPE:
      rc = LoadTreeFromDirectory(m_strFileName, tt);
      break;
    case FF_TREE_TYPE:
      rc = LoadTreeFromFile(m_strFileName, tt);
      break;
    case FF_INDENT_TYPE:
		    rc = LoadIndentTreeFromFile(m_strFileName, tt);
        break;
    case FF_CSV_TYPE:
		    rc = LoadCsvTreeFromFile(m_strFileName, tt);
        break;
    case FF_CLIPBOARD_TYPE:
      rc = PasteEntireTreeFromCliboard(tt);
      break;
    default:
      AfxMessageBox("Unknown file format!");
      return;
    }
    if(rc)
    {
      wTotalNbItems = tt.m_wTotalNbItems;
      rc = LoadTreeDataR(tt, GetRootItem(), OP_ENTIRE_TREE);
      if(tt.m_wTotalNbItems != wTotalNbItems || !rc)
        throw TTE_INVALID_FILE;
      if(ff == FF_DIRECTORY_TYPE)
      {   // Expand only one level, since these trees may be very big.
        ParseTree(pfCollapseAndSort);
        Expand(GetRootItem(), TVE_EXPAND);
      }
    }
  }
  catch(TREE_TYPE_ERROR fe)
  {
    if(ff != FF_CLIPBOARD_TYPE)
    {
      // If Pasting from a clipboard, which contains invalid data, do nothing
      // but don't display any error message.
      switch(fe)
      {
      case TTE_EMPTY_FILE:
        str.Format("Input file %s is empty", m_strFileName);
        break;
      case TTE_MEMORY:
        str = "Out of memory";
        break;
      case TTE_INVALID_FILE:
        str.Format("Invalid Input File %s", m_strFileName);
        break;
      case TTE_INVALID_CSV_FILE:
        str.Format("Invalid CSV File %s", m_strFileName);
        break;
      case TTE_OPEN:
        str.Format("Cannot open input file %s: %s", m_strFileName,  strerror(errno));
        break;
      case TTE_READ:
        str.Format("Cannot read from file %s: %s", m_strFileName,  strerror(errno));
        break;
      case TTE_CLOSE:
        str.Format("Cannot close input file %s: %s", m_strFileName,  strerror(errno));
        break;
      case TTE_INVALID_DIRECTORY:
        str.Format("Cannot find directory %s: %s", m_strFileName,  strerror(errno));
        break;
      }
      tt.m_wTotalNbItems = wTotalNbItems;
      OnDeleteAllItems();	
      AfxMessageBox(str);
    }
  }
  if(ff == FF_DIRECTORY_TYPE)
  {
    // Title is "Untitled"
    //		m_strFileName is used as the default file name , when the Save 
    //		function (Ctrl+S) is called. If Ctrl+D was called, we cannot, of course, 
    //		giving the tree name we built, the name of an existing directory. So, we reset
    //		m_strFileName to force the user to choose a name, when he saves the tree.
    m_strFileName.Empty();
  }
  tt.DeAllocateTree();
  if(rc)
    m_bsave =false;  
  EndWaitCursor(); // remove the hourglass cursor
}

// Load the directory (just the directory paths, not the file names), whose name
// is indicated by the parameter pszFileName, to a CTreeType structure.
BOOL CEditTreeCtrl::LoadTreeFromDirectory(const char *pszFileName, CTreeType &tt)
{
  CSTRING_VECTOR cv, cvFirstDirRecords;
  TREE_RECORD_VECTOR vtr;
  TREE_RECORD tr;
  int iSize, ifrSize, iMaxLevel = -1, j, k, rc;
  char szRecord[MAX_ASCII_RECORD];
  char lpszSaveDir[_MAX_PATH];
  
  GetCurrentDirectory(_MAX_PATH, lpszSaveDir);
  
  if(SetCurrentDirectory(pszFileName) == -1)
    throw TTE_INVALID_DIRECTORY;
  
  CFileFind ff;
  CString str;
  k = ff.FindFile(pszFileName);
  if(!k)
    FindPath(NULL, cv, true);
  else
    FindPath(pszFileName, cv, true);
  
  iSize = cv.size();
  GenerateFirstDirectoryRecords(pszFileName, cvFirstDirRecords);
  ifrSize = cvFirstDirRecords.size();
  for (j = 0, k = 0; k < iSize;)
  {
    if(j < ifrSize)
    {
      strcpy(szRecord, LPCTSTR(cvFirstDirRecords[j]));
      j++;
    }
    else
    {
      strcpy(szRecord, LPCTSTR(cv[k]));
      k++;
    }
    tr.iLevel = CalculateIndentLevel(szRecord, '\\');
    ValidCsvRecord(szRecord, iMaxLevel, m_szDelimiter, tr.iLevel);
	   // Dynamically allocated vector begins with 0 elements.
    tr.str = szRecord;
    vtr.push_back(tr);
  }
  rc = LoadCsvTreeFromMemory(vtr, tt, iMaxLevel, FF_DIRECTORY_TYPE);
  SetCurrentDirectory(lpszSaveDir);
  ff.Close();
  return rc;
}

/**************************************************************************************
Load tree from a TRE file.
If the tree was successfully read, a CTreeType structure is allocated, containing
the tree.
return true if successful
**************************************************************************************/
BOOL CEditTreeCtrl::LoadTreeFromFile(const char *pszFileName, CTreeType &tt)
{
  FILE *fp;
  CString str;
  WORD wTotalNbItems;
  int iCount;
  BOOL rc = true;
  NODE_TYPE *pnt;
  
  fp = fopen(pszFileName, "rb");
  if(fp == NULL)
    throw TTE_OPEN;
  if(fread(&wTotalNbItems, 1, sizeof(WORD), fp) == 0)
    throw TTE_EMPTY_FILE;
  if(wTotalNbItems == 0)
    throw TTE_EMPTY_FILE;
  if(!tt.AllocateTree(wTotalNbItems))
    throw TTE_MEMORY;
  for (iCount = 0; iCount <= wTotalNbItems; iCount++)
  {
    pnt = &tt.m_pnt[iCount];
    fread(&pnt->wNbItems, 1, sizeof(pnt->wNbItems), fp);
    if(feof(fp))
      throw TTE_INVALID_FILE; // Unexpected end of file
    if(ferror(fp))
      throw TTE_READ;
    fread(&pnt->wBufSize, 1, sizeof(pnt->wBufSize), fp);
    if(feof(fp))
      throw TTE_INVALID_FILE; // Unexpected end of file
    if(ferror(fp))
      throw TTE_READ;
    if(pnt->wBufSize > 0)
    {
      pnt->buf = new char[pnt->wBufSize + 1];
      if(pnt->buf == NULL)
        throw TTE_MEMORY;
      fread(pnt->buf, pnt->wBufSize, sizeof(char), fp);
      pnt->buf[pnt->wBufSize] = 0;
      if(feof(fp))
        throw TTE_INVALID_FILE; // Unexpected end of file
		    if(ferror(fp))
          throw TTE_READ;
    }
    fread(&pnt->uState, 1, sizeof(pnt->uState), fp);
    if(ferror(fp))
      throw TTE_READ;
  }
  fclose(fp);
  if(feof(fp))
    throw TTE_CLOSE;
  tt.m_wTotalNbItems = wTotalNbItems;
  return true;
}

/**************************************************************************************
Load tree from a IDT file.
If the tree was successfully read, a CTreeType structure is allocated, containing
the tree.
return true if successful
**************************************************************************************/
BOOL CEditTreeCtrl::LoadIndentTreeFromFile(const char *pszFileName, CTreeType &tt)
{
  FILE *fp;
  CString str;
  WORD wTotalNbItems = 0;
  BOOL rc = true;
  char seps[] = "\t\n";
  char *token;
  int n, j, iMaxLevel;
  TREE_RECORD_VECTOR vtr;
  TREE_RECORD tr;
  int *piLastAtLevel = NULL;
  NODE_TYPE *pnt;
  char szRecord[MAX_ASCII_RECORD];
  
  try
  {
    fp = fopen(pszFileName, "rt");
    if(fp == NULL)
		    throw TTE_OPEN;
    for (;;)
    {
      token = fgets(szRecord, MAX_ASCII_RECORD, fp);
      if(token == NULL && feof(fp))
        break;
      if(ferror(fp))
        throw TTE_READ;
      // Ignore first record (title)  blank lines
      for (n=0, token = strtok(szRecord, seps); token != NULL; 
      token = strtok(NULL, seps), n++)
      {
        // Dynamically allocated vector begins with 0 elements.
        switch(n)
        {
        case 0:
          tr.iLevel = CalculateIndentLevel(token, '.');
          break;
        case 1:
          tr.str = token;
          vtr.push_back(tr);
          break;
        }
      }
    }
    wTotalNbItems = vtr.size();
    if(wTotalNbItems == 0)
      throw TTE_INVALID_FILE;
    if(!tt.AllocateTree(wTotalNbItems))
      throw TTE_MEMORY;
    for (n = 0, iMaxLevel = 0; n < wTotalNbItems; n++)
      iMaxLevel = max(vtr[n].iLevel, iMaxLevel);
    piLastAtLevel = new int[iMaxLevel + 1];
    if(piLastAtLevel == NULL)
      throw TTE_MEMORY;
    
    tt.m_wTotalNbItems = wTotalNbItems;
    for (n = 0, piLastAtLevel[0] = 0; n < wTotalNbItems; n++)
    {
      j = vtr[n].iLevel;
      tt.m_pnt[piLastAtLevel[j - 1]].wNbItems++;				
      piLastAtLevel[j] = n + 1;
      pnt = &tt.m_pnt[n + 1];
      pnt->wBufSize = vtr[n].str.GetLength();
      pnt->buf = new char[pnt->wBufSize + 1];
      if(pnt->buf == NULL)
        throw TTE_MEMORY;
      if(pnt->wBufSize > 0)
        strcpy(pnt->buf, (LPCSTR)vtr[n].str);
      else
        *pnt->buf = 0;
    }
  }
  catch(TREE_TYPE_ERROR fe)
  {
    switch(fe)
    {
    case TTE_EMPTY_FILE:
      str.Format("Input IDT file %s is empty", m_strFileName);
      break;
    case TTE_MEMORY:
      str.Format("Out of memory");
      break;
    case TTE_READ:
		    str.Format("Cannot read from IDT file %s: %s", pszFileName,  strerror(errno));
        break;
    case TTE_CLOSE:
		    str.Format("Cannot close input IDT file %s: %s", pszFileName,  strerror(errno));
        break;
    case TTE_INVALID_FILE:
      str.Format("Input IDT file: %s is invalid or empty", pszFileName);
      break;
    case TTE_OPEN:
		    str.Format("Cannot open input IDT file %s: %s", pszFileName,  strerror(errno));
        break;
    }
    AfxMessageBox(str);
    rc = false;
  }
  if(fp != NULL)
  {
    fclose(fp);
    if(feof(fp))
      throw TTE_CLOSE;
  }
  if(piLastAtLevel != NULL)
    delete [] piLastAtLevel;
  return rc;
}

/**************************************************************************************
Load tree from a CSV file.
If the tree was successfully read, a CTreeType structure is allocated, containing
the tree.
return true if successful
**************************************************************************************/
BOOL CEditTreeCtrl::LoadCsvTreeFromFile(const char *pszFileName, CTreeType &tt)
{
  FILE *fp;
  TREE_RECORD_VECTOR vtr;
  TREE_RECORD tr;
  char szRecord[MAX_ASCII_RECORD], *p;
  int iMaxLevel = -1;
  CString str;
  int rc = true;
  
  try
  {
    fp = fopen(pszFileName, "rt");
    if(fp == NULL)
		    throw TTE_OPEN;
    for (;;) 
    {
      p = fgets(szRecord, MAX_ASCII_RECORD, fp);
      if(p == NULL && feof(fp))
        break;
      if(ferror(fp))
        throw TTE_READ;
      
      p = strchr(szRecord, '\n');
      if(p != NULL)
        *p = 0;
      if(*szRecord == 0) // Empty lines are ignored
        continue;
      tr.iLevel = strspn(szRecord, m_szDelimiter) + 1;
      ValidCsvRecord(szRecord, iMaxLevel, m_szDelimiter, tr.iLevel);
      // Dynamically allocated vector begins with 0 elements.
      tr.str = szRecord;
      vtr.push_back(tr);
    }
    rc = LoadCsvTreeFromMemory(vtr, tt, iMaxLevel, FF_CSV_TYPE);
  }
  catch(TREE_TYPE_ERROR fe)
  {
    switch(fe)
    {
    case TTE_READ:
		    str.Format("Cannot read from CSV file %s: %s", pszFileName,  strerror(errno));
        break;
    case TTE_CLOSE:
		    str.Format("Cannot close input CSV file %s: %s", pszFileName,  strerror(errno));
        break;
    case TTE_INVALID_FILE:
      str.Format("Input CSV file: %s is invalid", pszFileName);
      break;
    case TTE_INVALID_CSV_FILE:
      str.Format("Invalid CSV File %s", m_strFileName);
      break;
    case TTE_OPEN:
		    str.Format("Cannot open input CSV file %s: %s", pszFileName,  strerror(errno));
        break;
    }
    AfxMessageBox(str);
    rc = false;
  }
  if(fp != NULL)
  {
    fclose(fp);
    if(feof(fp))
      throw TTE_CLOSE;
  }
  return rc;
}

// Called when a tree was pasted from the Clipboard (When the user presses SHIFT+INS)
// We do the same work that is done when a file is opened (Warning if the current file 
// has been modified, deleting all items, copy from the clipboard to the CTreeType structure,
// and finally loading this structure to the Tree Control.

BOOL CEditTreeCtrl::PasteEntireTreeFromCliboard(CTreeType &tt)
{
  CString fromClipboard;
  char seps[] = "\r\n";
  char *token;
  TREE_RECORD_VECTOR vtr;
  TREE_RECORD tr;
  int iMaxLevel = -1;
  int n;
  
  m_bsave =true; // When loading other types, this function is called in
  
  RemovePie(TVI_ROOT);	// When loading other types, this function is called in
  // void CTreeEditorView::OnUpdate()
  
  GetFromClipboard(fromClipboard);
  try
  {
    for (n=0, token = strtok((char *)(LPCTSTR)fromClipboard, seps); token != NULL; 
    token = strtok(NULL, seps), n++)
    {
      tr.iLevel = strspn(token, "\t") + 1;
      ValidCsvRecord(token, iMaxLevel, "\t", tr.iLevel);
      // Dynamically allocated vector begins with 0 elements.
      tr.str = token;
      vtr.push_back(tr);
    }
    tt.m_wTotalNbItems = 0;
    tt.m_pnt = NULL;
    LoadCsvTreeFromMemory(vtr, tt, iMaxLevel, FF_CLIPBOARD_TYPE);
  }
  catch(TREE_TYPE_ERROR)
  {
    //		We don't give display an error when the clipboard is empty, or doesn't
    //		a valid tree, but we do retun false to handle this case correctly.
    return false;			
  }
  if(tt.m_wTotalNbItems == 0 || tt.m_pnt == NULL)
    return false;
  return true;
}

/**************************************************************************************
Loads a tree from a CTreeType structure to the Tree Control
**************************************************************************************/

BOOL CEditTreeCtrl::LoadTreeDataR(CTreeType &tt, HTREEITEM hti, 
                                  OUTSIDE_PARAM op /* = OP_NONE */)
{
  SetRedraw(false); // To speed up and avoid flickering
  if(!LoadTreeData(tt, hti, op))
    return false;
  RestoreStates(tt); // Restores the Expand/Item states as it was in the CTreeType structure
  SetRedraw(true); 
  return true;
}

// Restores the Expand/Item states as it was in the CTreeType structure
void CEditTreeCtrl::RestoreStates(CTreeType &tt)
{
  int iCount;
  
  for (iCount = 1; iCount <= tt.m_wTotalNbItems; iCount++)
    ExpandM(tt.m_pnt[iCount].hti, 
    tt.m_pnt[iCount].uState & TVIS_EXPANDED ? TVE_EXPAND :TVE_COLLAPSE);
}

BOOL CEditTreeCtrl::LoadTreeData(CTreeType &tt, HTREEITEM hti, OUTSIDE_PARAM op /* = OP_NONE */)
{
  int iCount;
  WORD wCurrentNode;
  HTREEITEM htiSon;
  NODE_TYPE *pnt;
  static HTREEITEM htiSave;
  static wTotalAllocatedtems = 0;
  static rc = true;
  
  // op indicates if the function was called recursively (OP_NONE)
  // or from the outside (OP_ENTIRE_TREE or OP_SUBTREE)
  if(op != OP_NONE)
  {
    wTotalAllocatedtems = tt.m_wTotalNbItems;
    tt.m_wTotalNbItems = 0;
  }
  wCurrentNode = tt.m_wTotalNbItems;
  
  //	tt.m_wTotalNbItems contains the number of items currently loaded. It is initialized 
  //  to zero. 
  //  At the end of the recursive function, if all run fine, it contains 
  //  the total number of items in the tree.
  
  for (iCount = 0; iCount < tt.m_pnt[wCurrentNode].wNbItems; iCount++)
  {
    if(op == OP_SUBTREE && wTotalAllocatedtems == tt.m_wTotalNbItems)
      return true;
    tt.m_wTotalNbItems++;
    
    // Ensure, we won't use unallocated space even if the data file contains
    // corrupted data.
    if(tt.m_wTotalNbItems > wTotalAllocatedtems)
    {
      tt.m_wTotalNbItems = wTotalAllocatedtems;
      rc = false;
      return rc;
    }
    pnt = &tt.m_pnt[tt.m_wTotalNbItems];
    htiSon = InsertPie(pnt->buf, hti);
    DilatePie(htiSon,pnt->dwTurd);
    
    pnt->hti = htiSon;
    rc = LoadTreeData(tt, htiSon);
    if(!rc) // If an error occurs return from all levels of recursion.
      return false;
  }
  return true;
}

/***********************************************************************************
* Save Functions
***********************************************************************************/

//	1) Calls SaveTreeData() to transfer the tree from the Tree Control to a CTreeType 
//	   structure
//	2) Saves a tree:
//		- From a CTreeType structure to a TRE file 
//		- From a CTreeType structure to an IDT file 
//		- From a CTreeType structure to a CSV file 
//		- From a CTreeType structure to the Clipboard

void CEditTreeCtrl::OnSaveEntireTree(FILE_FORMAT ff, CTreeType &tt)
{
/************************************************************************************
Ensure tt is always allocated and deallocated correctly:
*************************************************************************************
1) This function allocates a CTreeType.
2) The CTreeType is used to save data from the TreeControl. This is done
in SaveTreeData()
3) At the end of this function, the CTreeType is not neeeded anymore and
is deallocated.
  ************************************************************************************/
  
  int iCount;
  CString str;
  
  try
  {
    iCount = GetCount();
    if(iCount == 0)
      return;
    if(!tt.AllocateTree(iCount))
      throw TTE_MEMORY;
    if(!SaveTreeData(tt, GetRootItem(), OP_ENTIRE_TREE))
      throw TTE_MEMORY;
    if(tt.m_wTotalNbItems != iCount)
      throw TTE_INVALID_FILE;
    switch(ff)
    {
    case FF_TREE_TYPE:
      SaveTreeToFile(m_strFileName, tt);
      break;
    case FF_INDENT_TYPE:
		    SaveIndentTreeToFile(m_strFileName, tt);
        break;
    case FF_CSV_TYPE:
      SaveCsvTreeToFile(m_strFileName, tt);
      break;
    case FF_CLIPBOARD_TYPE:
      SaveCsvTabTreeToClipboard(tt);
      break;
    }
    if(ff != FF_CLIPBOARD_TYPE)
      m_bsave =false;
  }
  catch(TREE_TYPE_ERROR fe)
  {
    switch(fe)
    {
    case TTE_MEMORY:
      str = "Out of memory";
      break;
    case TTE_INVALID_FILE:
      str.Format("Nb of items found(%d) is different from GetCount(%d)",
        tt.m_wTotalNbItems, iCount);
      break;
    case TTE_OPEN:
      str.Format("Cannot open output file %s: %s", m_strFileName,  strerror(errno));
      break;
    case TTE_WRITE:
    		str.Format("Cannot write to file %s: %s", m_strFileName,  strerror(errno));
        break;
    case TTE_CLOSE:
    		str.Format("Cannot close output file %s: %s", m_strFileName,  strerror(errno));
        break;
    }
    AfxMessageBox(str);
  }
  tt.DeAllocateTree();
}

/**************************************************************************************
Save a tree from the Tree Control to a CTreeType structure.
**************************************************************************************/
BOOL CEditTreeCtrl::SaveTreeData(CTreeType &tt, HTREEITEM hti, OUTSIDE_PARAM op /* = OP_NONE */)
{
  CString str;
  WORD wCurrentNode = 0;
  NODE_TYPE *pnt;
  int rc = true;
  
  if(op != OP_NONE)
  {
    tt.m_wTotalNbItems = 0;
    tt.m_pnt[0].hti = 0;
  }
  else
  {
    str = GetItemText(hti);
    if(tt.m_pnt != NULL)
    {
      tt.m_wTotalNbItems++;
      pnt = &tt.m_pnt[tt.m_wTotalNbItems];
      pnt->wBufSize = strlen(str);
      pnt->hti = hti;
      pnt->buf = new char[pnt->wBufSize + 1];
      if(pnt->buf == NULL)
        return false;
      
      strcpy(pnt->buf, str);	
      EffulgePie(hti,pnt->dwTurd);
      
      pnt->uState = GetItemState(hti, TVIF_STATE);
      wCurrentNode = tt.m_wTotalNbItems;
      tt.m_pnt[wCurrentNode].wNbItems = 0;
    }
    hti = GetChildItem(hti); 
  }
  
  while(hti != NULL)
  {
    tt.m_pnt[wCurrentNode].wNbItems++;
    SaveTreeData(tt, hti);
    if(!rc) // If an error occurs return from all levels of recursion.
      return false;
    if(op == OP_SUBTREE)
      return true;
    else
      hti = GetNextSiblingItem(hti);
  }
  return true;
}

// Save the file from a CTreeType structure to a TRE file.
void CEditTreeCtrl::SaveTreeToFile(const char *pszFileName, CTreeType &tt)
{
  FILE *fp;
  int iCount;
  CString str;
  NODE_TYPE *pnt;
  
  fp = fopen(pszFileName, "wb");
  if(fp == NULL)
    throw TTE_MEMORY;
  fwrite(&tt.m_wTotalNbItems, 1, sizeof(WORD), fp);
  if(feof(fp))
    throw TTE_WRITE;
  for (iCount = 0; iCount <= tt.m_wTotalNbItems; iCount++)
  {
    pnt = &tt.m_pnt[iCount];
    fwrite(&pnt->wNbItems, 1, sizeof(pnt->wNbItems), fp);
    if(ferror(fp))
      throw TTE_WRITE;
    fwrite(&pnt->wBufSize, 1, sizeof(pnt->wBufSize), fp);
    if(ferror(fp))
      throw TTE_WRITE;
    if(pnt->wBufSize > 0)
    {
      fwrite(pnt->buf, pnt->wBufSize, sizeof(char), fp);
      if(ferror(fp))
        throw TTE_WRITE;
    }
    fwrite(&pnt->uState, 1, sizeof(pnt->uState), fp);
    if(ferror(fp))
      throw TTE_WRITE;
  }
  fclose(fp);
  if(feof(fp))
    throw TTE_CLOSE;
}

// Save a tree from a CTreeType structure to an IDT file
BOOL CEditTreeCtrl::SaveIndentTreeToFile(const char *pszFileName, CTreeType &tt)
{
  FILE *fp;
  CString str;
  BOOL rc = true;
  int iMaxLevel = CalculateMaxLevel(tt), iLevel, iCount, *piCurrentLevels, k;
  int iPreviousLevel = -1;
  char szRecord[MAX_ASCII_RECORD];
  
  try
  {
    if(iMaxLevel > MAX_LEVELS)
      throw TTE_MAX_LEVEL;
    piCurrentLevels = new int[iMaxLevel];
    if(piCurrentLevels == NULL)
      throw TTE_MEMORY;
    for (k = 0; k < iMaxLevel; k++)
      piCurrentLevels[k] = 0;
    
    fp = fopen(pszFileName, "wt");
    if(fp == NULL)
		    throw TTE_OPEN;
    for (iCount = 1; iCount <= tt.m_wTotalNbItems; iCount++)
    {
      *szRecord = 0;
      iLevel = GetLevelTree(tt.m_pnt[iCount].hti);
      if(iLevel < iPreviousLevel)
      {
        for (k=iLevel; k<iMaxLevel; k++)
          piCurrentLevels[k] = 0;
      }
      piCurrentLevels[iLevel - 1]++;
      iPreviousLevel = iLevel;
      for (k=0; k<iLevel; k++)
      {
        str.Format("%d", piCurrentLevels[k]);
        strcat(szRecord, str);
        strcat(szRecord, ".");
      }
      if(iLevel != 1)
        szRecord[strlen(szRecord) - 1] = 0;
      strcat(szRecord, "\t");
      strcat(szRecord, tt.m_pnt[iCount].buf);
      fprintf(fp, "%s\n", szRecord);
      if(ferror(fp))
        throw TTE_WRITE;
    }
    fclose(fp);
    if(feof(fp))
      throw TTE_CLOSE;
  }
  catch(TREE_TYPE_ERROR fe)
  {
    switch(fe)
    {
    case TTE_MAX_LEVEL:
      str.Format("Up to %d levels are supported!", MAX_LEVELS);
      break;
    case TTE_EMPTY_FILE:
      str.Format("Output file %s is empty", m_strFileName);
      break;
    case TTE_MEMORY:
      str.Format("Out of memory");
      break;
    case TTE_WRITE:
		    str.Format("Cannot write to IDT file %s: %s", pszFileName,  strerror(errno));
        break;
    case TTE_CLOSE:
		    str.Format("Cannot close output IDT file %s: %s", pszFileName,  strerror(errno));
        break;
    case TTE_INVALID_FILE:
      str.Format("Output IDT file: %s is invalid", pszFileName);
      break;
    case TTE_OPEN:
		    str.Format("Cannot open output IDT file %s: %s", pszFileName,  strerror(errno));
        break;
    }
    AfxMessageBox(str);
    rc = false;
  }
  if(piCurrentLevels != NULL)
    delete [] piCurrentLevels;
  return rc;
}

// Save a file from a CTreeType structure to a CSV file.
BOOL CEditTreeCtrl::SaveCsvTreeToFile(const char *pszFileName, CTreeType &tt)
{
  FILE *fp;
  CString str;
  BOOL rc = true;
  int iMaxLevel = CalculateMaxLevel(tt), iLevel, iCount, k;
  char szRecord[MAX_ASCII_RECORD];
  
  try
  {
    fp = fopen(pszFileName, "wt");
    if(fp == NULL)
		    throw TTE_OPEN;
    for (iCount = 1; iCount <= tt.m_wTotalNbItems; iCount++)
    {
      *szRecord = 0;
      iLevel = GetLevelTree(tt.m_pnt[iCount].hti);
      for (k=1; k<=iMaxLevel; k++)
      {
        if(k == iLevel)
          strcat(szRecord, tt.m_pnt[iCount].buf);
        if(k != iMaxLevel)
          strcat(szRecord, m_szDelimiter);
      }
      fprintf(fp, "%s\n", szRecord);
      if(ferror(fp))
        throw TTE_WRITE;
    }
    fclose(fp);
    if(feof(fp))
      throw TTE_CLOSE;
  }
  catch(TREE_TYPE_ERROR fe)
  {
    switch(fe)
    {
    case TTE_EMPTY_FILE:
      str.Format("Output file %s is empty", m_strFileName);
      break;
    case TTE_MEMORY:
      str.Format("Out of memory");
      break;
    case TTE_WRITE:
		    str.Format("Cannot write to CSV file %s: %s", pszFileName,  strerror(errno));
        break;
    case TTE_CLOSE:
		    str.Format("Cannot close output CSV file %s: %s", pszFileName,  strerror(errno));
        break;
    case TTE_INVALID_FILE:
      str.Format("Output CSV file: %s is invalid", pszFileName);
      break;
    case TTE_OPEN:
		    str.Format("Cannot open output CSV file %s: %s", pszFileName,  strerror(errno));
        break;
    }
    AfxMessageBox(str);
    rc = false;
  }
  return rc;
}

// Save a tree from a CTreeType structure to the Clipboard.
void CEditTreeCtrl::SaveCsvTabTreeToClipboard(CTreeType &tt)
{
  int iCount, iLevel;
  CString *pstrData;
  char szRecord[MAX_ASCII_RECORD];
  int iMaxLevel = CalculateMaxLevel(tt), k;
  
  pstrData = new CString[tt.m_wTotalNbItems];
  if(pstrData == NULL)
    throw TTE_MEMORY;
  for (iCount = 1; iCount <= tt.m_wTotalNbItems; iCount++)
  {
    *szRecord = 0;
    iLevel = GetLevelTree(tt.m_pnt[iCount].hti);
    for (k=1; k<=iMaxLevel; k++)
    {
      if(k == iLevel)
        strcat(szRecord, tt.m_pnt[iCount].buf);
      if(k != iMaxLevel)
        strcat(szRecord, "\t");
    }
    pstrData[iCount - 1] = szRecord;
  }
  Add2Clipboard(pstrData, tt.m_wTotalNbItems);
  if(pstrData != NULL)
    delete [] pstrData;
}

/***********************************************************************************
* Sort Functions
***********************************************************************************/

// Called when the user presses Ctrl+T 
void CEditTreeCtrl::OnSortSubtreeAlphabetic() 
{
  m_SortType = ST_ALPHABETIC;
  SortSubtree();
}

// Called when the user presses Ctrl+Shift+T 
void CEditTreeCtrl::OnSortSubtreeNumeric() 
{
  m_SortType = ST_NUMERIC;
  SortSubtree();
}

// Sort a Subtree using a callback function. 
void CEditTreeCtrl::SortSubtree() 
{
  HTREEITEM hti;
  TVSORTCB tvscb;
  BOOL bRc;
  
  hti = GetSelectedItem();
  if(hti != NULL)
  {
    tvscb.hParent = hti;
    tvscb.lpfnCompare = CompareFunc;
    tvscb.lParam = (LPARAM)this;
    bRc = SortChildrenCB(&tvscb);
    m_bsave =true;
  }
}

int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
  CString str1, str2;
  int i1, i2;
  CEditTreeCtrl *petc= (CEditTreeCtrl *)lParamSort;
  
  str1 = petc->GetItemText((HTREEITEM)lParam1);
  str2 = petc->GetItemText((HTREEITEM)lParam2);
  switch(petc->m_SortType)
  {
  case ST_NUMERIC:
    i1 = atoi((LPCTSTR)str1);
    i2 = atoi((LPCTSTR)str2);
    if(i1 > i2)
      return 1;
    if(i2 > i1)
      return -1;
    return 0;
  case ST_ALPHABETIC:
    if(str1 > str2)
      return 1;
    if(str2 > str1)
      return -1;
    return 0;
  default:
    return 0;
  }
}

/***********************************************************************************
* Utility Functions
***********************************************************************************/

// Called by LoadTreeFromDirectory() to search a directory
void CEditTreeCtrl::FindPath(const char *lpszPath, CSTRING_VECTOR &cv, BOOL bCalledFromOutside /* = false */)
{
  CFileFind ff;
  BOOL bRC;
  static CString str;
  
  for (bRC = ff.FindFile(lpszPath); bRC;)
  {
    bRC = ff.FindNextFile();
    str = ff.GetFilePath();
    if(ff.IsDirectory() && !ff.IsDots() && !ff.IsHidden()) 
    {
      cv.push_back(str);
      SetCurrentDirectory(str);
      FindPath(NULL, cv);
      if(!bCalledFromOutside)
        SetCurrentDirectory("..");
    }
  }
  ff.Close();
}

// Checks if a CSV record is valid
BOOL CEditTreeCtrl::ValidCsvRecord(char *psz, int &iMaxLevel, char *pszDelimiter, int iLevel)
{
  int j;
  const char *p, *token;
  char szRecord[MAX_ASCII_RECORD];
  
  //	If the tree is valid, the level can:
  //		- decrease to any level down to 1 (the lowest)
  //		- stay the same
  //		- increase by 1
  
  static iPreviousLevel;
  
  if(iMaxLevel == -1) // First time, the function is called for a given tree
    iPreviousLevel = 0;
  if(iPreviousLevel + 1 < iLevel)
    throw TTE_INVALID_CSV_FILE;
  iPreviousLevel = iLevel;
  
  for (j=0, p=psz;; j++, p++)
  {
    token = p;
    p = strchr(p, *pszDelimiter);
    if(p == NULL)
    {
      if(*token != 0)
        strcpy(szRecord, token);
      break;
    }
    if(*token != *pszDelimiter)
    {
      strcpy(szRecord, token);
      szRecord[p - token] = 0;
    }
  }
  if(j + 1 > iMaxLevel)
    iMaxLevel = j + 1;
  strcpy(psz, szRecord);
  return true;
}

int CEditTreeCtrl::CalculateIndentLevel(char *psz, char ch)
{
  //	The level is the number of tokens separeted by the 'ch' character
  //	(independently of their value)
  //	Examples:
  //		CalculateIndentLevel("1.", '.')		= 1
  //		CalculateIndentLevel("3.4", '.')		= 2
  //		CalculateIndentLevel("13.24.5.2", '.')	= 4
  
  // This function is called from LoadTreeFromDirectory() with ch == '\\'
  //					   and from LoadIndentTreeFromFile() with ch == '.'
  int k, n;
  
  for (k = 0, n = 1; psz[k] != 0; k++)
  {
    if(psz[k] == ch && psz[k+1] != 0)
      n++;
  }
  return n;
}

// Return true if the second parameter is an ancester of the first one.
BOOL CEditTreeCtrl::IsChildNodeOf(HTREEITEM hitemChild, HTREEITEM hitemSuspectedParent)
{
  do
  {
    if(hitemChild == hitemSuspectedParent)
      break;
  }
  while ((hitemChild = GetParentItem(hitemChild)) != NULL);
  
  return (hitemChild != NULL);
}

// Called when the user presses Ctrl+Shift+N
void CEditTreeCtrl::OnCountEntireTree() 
{
  CString str;
  int iCount;
  
  iCount = GetCount();	
  // An alternative is: iCount = CountSubtree(GetRootItem(), OP_ENTIRE_TREE);
  str.Format("Number of item in Entire Tree: %d", iCount);
  AfxMessageBox(str);
}

// Called when the user presses Ctrl+N
void CEditTreeCtrl::OnCountSubtree() 
{
  CString str;
  int iCount;
  HTREEITEM hti;
  
  hti = GetSelectedItem();
  iCount = CountSubtree(hti, OP_SUBTREE);
  str.Format("Number of item in Subtree: %d", iCount);
  AfxMessageBox(str);
}

// Called when the user presses Ctrl+Shift+N Count entire tree
int CEditTreeCtrl::CountSubtree(HTREEITEM hti, OUTSIDE_PARAM op /* = OP_NONE */)
{
  static int iCount;
  if(op != OP_NONE)
    iCount = 0;
  else
  {
    iCount++;
    hti = GetChildItem(hti); 
  }
  
  while(hti != NULL)
  {
    CountSubtree(hti);
    if(op == OP_SUBTREE)
      return iCount;
    else
    {
      hti = GetNextSiblingItem(hti);
    }
  }
  return iCount;
}

// Called when the user presses Ctrl+L
void CEditTreeCtrl::OnCalculateLevel()
{
  int iLevel;
  HTREEITEM hti;
  CString str;
  
  hti = GetSelectedItem();
  if(hti != NULL)
  {
    iLevel = GetLevelTree(hti);
    str.Format("Item Level: %d", iLevel);
    AfxMessageBox(str);
  }
}

// Calculates the level from an item (Level = 1, 2, ... = distance from the root)
int CEditTreeCtrl::GetLevelTree(HTREEITEM hti)
{
  int iCount;
  {
    for (iCount = 0; hti != NULL; iCount++)
      hti = GetParentItem(hti);
  }
  return iCount;
}

// Calculates the maximum level in the tree
int CEditTreeCtrl::CalculateMaxLevel(CTreeType &tt)
{
  int iCount, iMaxLevel = 0;
  
  for (iCount = 1; iCount <= tt.m_wTotalNbItems; iCount++)
    iMaxLevel = max(iMaxLevel, GetLevelTree(tt.m_pnt[iCount].hti));
  return iMaxLevel;
}

/***********************************************************************************
* Wrapper to the basic Tree Control member functions.
***********************************************************************************/
HTREEITEM CEditTreeCtrl::InsertPie(LPCTSTR lpszItem, 
                                   HTREEITEM hParent /*= TVI_ROOT*/, HTREEITEM hInsertAfter /*= TVI_LAST*/)
{
  HTREEITEM htiSon = InsertItem(lpszItem, hParent, hInsertAfter);
  SetItemImage(htiSon, 0, 1);
  
  SetItemData(htiSon, (DWORD)htiSon);
  m_bsave =true;
  
  DilatePie(htiSon,NULL);
  return htiSon;
}

BOOL CEditTreeCtrl::RemovePie(HTREEITEM hRP)
{
  CrimplePie(hRP);
  return DeleteItem(hRP);
}

void CEditTreeCtrl::DilatePie(HTREEITEM hDilated,void* dwDilate)
{
}

void CEditTreeCtrl::EffulgePie(HTREEITEM hDilated,void*& rValue)
{
}

void CEditTreeCtrl::CrimplePie(HTREEITEM hCP)
{
}

// Wrapper to the SelectItem function
BOOL CEditTreeCtrl::SelectVisibleItem(HTREEITEM hti)
{
  EnsureVisible(hti);
  return SelectItem(hti);
}

BOOL CEditTreeCtrl::InitializeImageList()
{
  CBitmap bmap;
  BITMAP bm;
  
  bmap.LoadBitmap(IDB_EDIT_TREE);
  bmap.GetBitmap(&bm);
  
  m_imageET.Create(bm.bmWidth / 2, bm.bmHeight, ILC_COLORDDB, 2, 0);
  m_imageET.Add(&bmap, (COLORREF)0);
  bmap.DeleteObject();
  SetImageList(&m_imageET, TVSIL_NORMAL);
  
  return true;
}

// Wrapper to the Expand function
BOOL CEditTreeCtrl::ExpandM(HTREEITEM hItem, UINT nCode)
{
  BOOL b;
  
  b = Expand(hItem, nCode);	// Since we save the expand/collapse state into the file,
  if(b)						// we consider this as a modification;
    m_bsave =true; 
  return b;
}

BOOL CEditTreeCtrl::DeleteItemM(HTREEITEM hItem)
{
  BOOL b;
  
  b = RemovePie(hItem);
  if(b)
    m_bsave =true;  
  return b;
}

// Notification handler called when the user causes an Expand/Collapse
void CEditTreeCtrl::OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult) 
{
  NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
  m_bsave =true;	// We consider this as a modification, since we save 
  *pResult = 0;				// the expand/collapse state into the file,
}

// Called by these functions:
//	- PasteEntireTreeFromCliboard()
//	- LoadTreeFromDirectory()
//	- LoadCsvTreeFromMemory()
//
// Load a CSV file from a vector of struct TREE_RECORD to a CTreeType structure
// iMaxLevel is the maximum level of the tree. 
// ff is a flag to allow special processing according to the file type.
//
// A vector is nothing but an array, whose size can changes at running time. (See
// STL documentation about vectors)

BOOL CEditTreeCtrl::LoadCsvTreeFromMemory(TREE_RECORD_VECTOR &vtr, CTreeType &tt, 
                                          int iMaxLevel, FILE_FORMAT ff)
{
  CString str;
  WORD wTotalNbItems = 0;
  BOOL rc = true;
  int n, j;
  int *piLastAtLevel = NULL;
  NODE_TYPE *pnt;
  
  try
  {
    wTotalNbItems = vtr.size();
    if(wTotalNbItems == 0)
      throw TTE_EMPTY_FILE;
    if(!tt.AllocateTree(wTotalNbItems))
      throw TTE_MEMORY;
    piLastAtLevel = new int[iMaxLevel + 1];
    if(piLastAtLevel == NULL)
      throw TTE_MEMORY;
    
    tt.m_wTotalNbItems = wTotalNbItems;
    for (n = 0, piLastAtLevel[0] = 0; n < wTotalNbItems; n++)
    {
      j = vtr[n].iLevel;
      tt.m_pnt[piLastAtLevel[j - 1]].wNbItems++;				
      piLastAtLevel[j] = n + 1;
      pnt = &tt.m_pnt[n + 1];
      pnt->wBufSize = vtr[n].str.GetLength();
      pnt->buf = new char[pnt->wBufSize + 1];
      if(pnt->buf == NULL)
        throw TTE_MEMORY;
      if(pnt->wBufSize > 0)
        strcpy(pnt->buf, (LPCSTR)vtr[n].str);
      else
        *pnt->buf = 0;
    }
  }
  catch(TREE_TYPE_ERROR fe)
  {
    if(ff != FF_CLIPBOARD_TYPE)
    {
      // If Pasting from a clipboard, which contains invalid data, do nothing
      // but don't display any error message.
      switch(fe)
      {
      case TTE_EMPTY_FILE:
        if(ff == FF_DIRECTORY_TYPE)
          str.Format("Directory %s is empty", m_strFileName);
        else
          str.Format("Input CSV file %s is empty", m_strFileName);
        break;
      case TTE_MEMORY:
        str.Format("Out of memory");
        break;
      }
      AfxMessageBox(str);
    }
    rc = false;
  }
  if(piLastAtLevel != NULL)
    delete [] piLastAtLevel;
  return rc;
}

//	When LoadTreeFromDirectory() is called to load a directory, such as:
//	d:\subdir1\...\subdirN, a CSTRING_VECTOR is generated containing all the directories
//	founds, whose path begin by: D:\subdir1\...\subdirN. 
//
//	The following function is used to generate the first records from the root, i.e:
//		- (d:\)
//		- subdir1
//		- ...
//		- subdirN
//
void CEditTreeCtrl::GenerateFirstDirectoryRecords(const char *pszFirstRecord,
                                                  CSTRING_VECTOR &cvFirstDirRecords)
{
  int k;
  BOOL bFirstTime = true;
  char szRecord[MAX_ASCII_RECORD];
  char str[MAX_ASCII_RECORD];
  
  for (k = 0; pszFirstRecord[k] != 0; k++)
  {
    if(pszFirstRecord[k] == '\\')
    {
      memcpy(szRecord, pszFirstRecord, k);
      szRecord[k] = 0;
      if(bFirstTime)
      {
        bFirstTime = false;
        strcpy(str, szRecord);
        *str = toupper(*str);
        sprintf(szRecord, "(%s)", str);
      }
      cvFirstDirRecords.push_back(szRecord);
    }
  }
}

// Called at the end of the process of loading a directory, to collapse the tree and
// to sort the items as Explorer does.
void CEditTreeCtrl::pfCollapseAndSort(HTREEITEM hti, void *)
{
  ExpandM(hti, TVE_COLLAPSE);
  SortChildren(hti);
}

/**************************************************************************************
*	Name:				Add2Clipboard()	 
*	Type:				void
*	Parameter List:		pstrData    - array of strings to copy to the clipboard.
*                       iSize       - size of array
*	Description:		Copy strings to the clipboard.
*	Return value:		none.
/****************************************************************************************/
void CEditTreeCtrl::Add2Clipboard(CString *pstrData, int iSize)
{
  int k, iTotalSize;
  
  if(OpenClipboard())
  {
    EmptyClipboard();
    HGLOBAL hClipboardData;
    for (k = 0, iTotalSize = 0; k < iSize; k++)
      iTotalSize += pstrData[k].GetLength() + 2;
    hClipboardData = GlobalAlloc(GMEM_DDESHARE, iTotalSize);
    
    char * pchData;
    pchData = (char*)GlobalLock(hClipboardData);
    
    strcpy(pchData, LPCSTR(pstrData[0]));
    for (k = 1; k < iSize; k++)
    {
      strcat(pchData, "\r\n");
      strcat(pchData, LPCSTR(pstrData[k]));
    }
    GlobalUnlock(hClipboardData);
    SetClipboardData(CF_TEXT,hClipboardData);
    CloseClipboard();
  }
}

// Get the Cipboard content into a CString
void CEditTreeCtrl::GetFromClipboard(CString &fromClipboard)
{
  HGLOBAL hClipboardData;
  char *buffer;
  
  if(OpenClipboard())
  {
    hClipboardData = GetClipboardData(CF_TEXT);
    buffer = (char*)GlobalLock(hClipboardData);
    fromClipboard = buffer;
    GlobalUnlock(hClipboardData);
    CloseClipboard();
  }
}

BOOL CEditTreeCtrl::PreCreateWindow(CREATESTRUCT& cs) 
{
  cs.style |=TVS_SHOWSELALWAYS | TVS_EDITLABELS | TVS_HASBUTTONS | 
    TVS_LINESATROOT | TVS_HASLINES;
  
  return CTreeCtrl::PreCreateWindow(cs);
}
