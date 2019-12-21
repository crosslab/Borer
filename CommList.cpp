#include "stdafx.h"
//#include "CommonDef.h"
#include "Borer.h"
#include "CommList.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommList
CCommList::CCommList()
{
}

CCommList::~CCommList()
{
}


BEGIN_MESSAGE_MAP(CCommList, CListCtrl)
//{{AFX_MSG_MAP(CCommList)
ON_WM_SIZE()
ON_WM_CONTEXTMENU()
ON_WM_WINDOWPOSCHANGED()
ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommList message handlers
void CCommList::OnSize(UINT nType, int cx, int cy) 
{
  CListCtrl::OnSize(nType, cx, cy);
  SetColumnWidth(0,cx);
}

void CCommList::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
  CListCtrl::OnWindowPosChanged(lpwndpos);
  
  ShowScrollBar(SB_HORZ, FALSE);
  ModifyStyle(WS_HSCROLL, 0, SWP_DRAWFRAME);
}

void CCommList::OnContextMenu(CWnd* pWnd, CPoint point) 
{
  CMenu menu;
  VERIFY(menu.LoadMenu(IDR_RIGHT_COMM));
  
  CMenu* pPopup = menu.GetSubMenu(0);
  ASSERT(pPopup != NULL);
  
  CWnd* pWndPopupOwner = this;
  while (pWndPopupOwner->GetStyle() & WS_CHILD)
    pWndPopupOwner = pWndPopupOwner->GetParent();
  
  pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x,
    point.y, pWndPopupOwner);
}

void CCommList::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
  *pResult = 0;
  
  CMainFrame *pMyFrm=(CMainFrame*)AfxGetApp()->m_pMainWnd;//取主框架窗口指针
  
  int intCm=GetNextItem(-1,LVNI_SELECTED);
  if(intCm<0) {
	   return;
  }
  
  CView *dcView=pMyFrm->m_aTestInfo[intCm]->UpData_pView;
  CWnd  *dcWnd=dcView->GetParent();
  
  while(!dcWnd->IsKindOf(RUNTIME_CLASS(CMDIChildWnd))) {
    dcWnd=dcWnd->GetParent();
  }
  
  pMyFrm->MDIActivate(dcWnd);
  
}