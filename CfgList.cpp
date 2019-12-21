#include "stdafx.h"
#include "Borer.h"
#include "CfgList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCfgList
CCfgList::CCfgList()
{
}

CCfgList::~CCfgList()
{
}


BEGIN_MESSAGE_MAP(CCfgList, CEditList)
	//{{AFX_MSG_MAP(CCfgList)
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCfgList message handlers
void CCfgList::OnContextMenu(CWnd* pWnd, CPoint point) 
{
      CMenu menu;
      VERIFY(menu.LoadMenu(IDR_RIGHT_CFGEDIT));

      CMenu* pPopup = menu.GetSubMenu(0);
      ASSERT(pPopup != NULL);

      CWnd* pWndPopupOwner = this;
      while (pWndPopupOwner->GetStyle() & WS_CHILD)
         pWndPopupOwner = pWndPopupOwner->GetParent();

      pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x,
                             point.y, pWndPopupOwner);
}
