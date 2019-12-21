#include "stdafx.h"
#include "Borer.h"
#include "ProjectTree.h"
#include <io.h>
#include "mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProjectTree
CProjectTree::CProjectTree()
{
}

CProjectTree::~CProjectTree()
{
}

BEGIN_MESSAGE_MAP(CProjectTree, CEditTreeCtrl)
//{{AFX_MSG_MAP(CProjectTree)
ON_COMMAND(ID_ITP_EXECUTE, OnItpExecute)
ON_COMMAND(ID_ITP_BROWSE, OnItpBrowse)
ON_WM_CONTEXTMENU()
ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
ON_NOTIFY_REFLECT(TVN_ENDLABELEDIT, OnEndlabeledit)
ON_WM_RBUTTONDOWN()
ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
ON_COMMAND(ID_ADD_CCHILD, OnAddCchild)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProjectTree message handlers
void CProjectTree::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
  TV_DISPINFO *ptvinfo;
  
  // Called at exit from Edit Mode
  ptvinfo = (TV_DISPINFO *)pNMHDR;
  if (ptvinfo->item.pszText != NULL)
  {
    ptvinfo->item.mask = TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
    CString j8 =ptvinfo->item.pszText;
    j8.MakeLower();
    
    if((j8.Right(2)==".c") || (j8.Right(4)==".cpp") || (j8.Right(2)==".h")) {
      ptvinfo->item.iImage =2;
      ptvinfo->item.iSelectedImage =3;
    }else {
      ptvinfo->item.iImage =0;
      ptvinfo->item.iSelectedImage =1;
    }
    
    SetItem(&ptvinfo->item);
    m_bsave =true;
  }
  if (m_bInsertionMode) // VK_INSERT was pressed in course of editing
    OnAddSibling();
  else
    m_bInsertionMode = false;
  *pResult = TRUE; // TRUE => Accept the label
}

HTREEITEM CProjectTree::InsertPie(LPCTSTR szIIAST, 
                                  HTREEITEM hParent /*= TVI_ROOT*/, HTREEITEM hInsertAfter /*= TVI_LAST*/)
{
  HTREEITEM htiSon = InsertItem(szIIAST, hParent, hInsertAfter);
  
  CString k8 = szIIAST;
  k8.MakeLower();
  
  if((k8.Right(2)==".c") || (k8.Right(4)==".cpp") || (k8.Right(2)==".h")) 
  {
    SetItemImage(htiSon, 2, 3);
  }
  else
  {
    SetItemImage(htiSon, 0, 1);
  }
  
  SetItemData(htiSon, (DWORD)htiSon);
  m_bsave =true;
  
  return htiSon;
}

void CProjectTree::OnAddCchild() 
{
  CFileDialog dlg(true,"","",OFN_ALLOWMULTISELECT,"C Files (*.C)|*.C|All Files (*.*)|*.*||");
  dlg.m_ofn.nMaxFile = MAXFILE;
  char* pc = new char[MAXFILE];
  dlg.m_ofn.lpstrFile = pc;
  dlg.m_ofn.lpstrFile[0] = NULL;
  
  if(dlg.DoModal()!=IDOK)
  {
    delete []pc; 
    return;
  }
  
  POSITION pos = dlg.GetStartPosition();
  HTREEITEM hti, htiChild;
  HTREEITEM hHeadNode = NULL;
  HTREEITEM hTailNode = NULL;
  
  hti = GetSelectedItem();
  
  while (pos != NULL) 
  {
		  htiChild = InsertPie(dlg.GetNextPathName(pos), hti, TVI_LAST);
      if((hHeadNode == NULL) && (hTailNode ==NULL))
      {
        hHeadNode = htiChild ;
      }
      if(pos==NULL)
      {
        hTailNode = htiChild ;
      }
      EnsureVisible(htiChild);
      EditLabel(htiChild);
      Select(htiChild, TVGN_CARET);
  }
  
  delete []pc; 
}

/**************************************************************************************
Execute a tree.
**************************************************************************************/
BOOL CProjectTree::ExecuteTree(HTREEITEM hti, OUTSIDE_PARAM op /* = OP_NONE */)
{
  CString j9;
  
  if (op ==OP_NONE)
  {
    j9 = GetItemText(hti);
    j9.MakeLower();
    
    if((j9.Right(2)==".c") || (j9.Right(4)==".cpp") || (j9.Right(2)==".h"))
    {
      if(_access(j9,0x00) !=-1)
      {
        m_qary.Add(j9);
      }
    }
    
    hti = GetChildItem(hti); 
  }
  
  while(hti != NULL)
  {
    ExecuteTree(hti);
    
    if (op == OP_SUBTREE)
    {
      return true;
    }
    else
    {
      hti = GetNextSiblingItem(hti);
    }
  }
  return true;
}

void CProjectTree::OnItpExecute() 
{
  CMainFrame  *pMyFrm =(CMainFrame*)AfxGetApp()->m_pMainWnd;//取主框架窗口指针
  int intCm=pMyFrm->m_PortList.GetNextItem(-1,LVNI_SELECTED);
  if(intCm<0) {
    return;
  }
  
  if(!pMyFrm->m_aTestInfo[intCm]->IsEngrossed()) {
    return;
  }
  
  HTREEITEM hti;
  hti = GetSelectedItem();
  if(!hti)
  {
    return;
  }
  
  m_qary.RemoveAll();
  ExecuteTree(hti,OP_SUBTREE);
  
  m_qmod =GetItemText(hti);
  m_qmod.MakeLower();
  if((m_qmod.Right(2)==".c") || (m_qmod.Right(4)==".cpp") || (m_qmod.Right(2)==".h")) {
	   m_qmod.Empty();
  }else {
    m_qmod =GetItemText(hti);
  }
  
  if(m_qary.GetSize()) {
    AfxGetApp()->m_pMainWnd->PostMessage(MMM_BATCH_RUN,0,0);//取主框架窗口指针
  }
}

void CProjectTree::OnItpBrowse() 
{
  HTREEITEM hti;
  hti = GetSelectedItem();
  if(!hti) {
    return;
  }
  
  CFileDialog dlg(true,"","",NULL,"C Files (*.C)|*.C|All Files (*.*)|*.*||");
  if(dlg.DoModal()!=IDOK) {
    return;
  }
  
		TVITEM  item5;
    item5.mask = TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
    item5.hItem = hti;
    
    CString j8 =dlg.GetPathName();
    j8.MakeLower();
    
    if((j8.Right(2)==".c") || (j8.Right(4)==".cpp") || (j8.Right(2)==".h")) {
      item5.iImage =2;
      item5.iSelectedImage =3;
    }else {
      item5.iImage =0;
      item5.iSelectedImage =1;
    }
    
    item5.pszText =j8.GetBuffer(j8.GetLength());
    SetItem(&item5);
    j8.ReleaseBuffer();
    
    m_bsave =true;
}

void CProjectTree::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
  //Work out the position of where the context menu should be
  CPoint p(GetCurrentMessage()->pt);
  CPoint pt(p);
  ScreenToClient(&pt);
  Select(HitTest(pt), TVGN_CARET);
  OnContextMenu(NULL, p);
  *pResult = 0;
}

void CProjectTree::OnContextMenu(CWnd* pWnd, CPoint point) 
{
  // TODO: Add your message handler code here
  CMenu menu;
  VERIFY(menu.LoadMenu(IDR_RIGHT_PRJTREE));
  CMenu* pPopup = menu.GetSubMenu(0);
  ASSERT(pPopup != NULL);
  pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
  
}

BOOL CProjectTree::InitializeImageList()
{
  CBitmap bmap;
  BITMAP bm;
  
  bmap.LoadBitmap(IDB_EDIT_TREE);
  bmap.GetBitmap(&bm);
  
  m_imageET.Create(bm.bmWidth / 4, bm.bmHeight, ILC_COLORDDB, 2, 0);
  m_imageET.Add(&bmap, (COLORREF)0);
  bmap.DeleteObject();
  SetImageList(&m_imageET, TVSIL_NORMAL);
  
  return true;
}

void fnSynch(CString &msggg,int mslll,int msrrr,void *msppp);

void CProjectTree::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
  HTREEITEM hti = GetSelectedItem();
  
  CFrameWnd *pMyFrm=((CMainFrame*)AfxGetMainWnd())->GetActiveFrame();
  if(!pMyFrm) {
	   return ;
  }
  
  CView *pMyView=pMyFrm->GetActiveView();
  if(!pMyView) {
	   return ;
  }
  
  fnSynch(GetItemText(hti),-1,0,pMyView);
  *pResult = 0;
}


