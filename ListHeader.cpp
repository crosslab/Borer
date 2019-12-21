#include "stdafx.h"
#include "Borer.h"
#include "ListHeader.h"
#include "CommonDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListHeader
CListHeader::CListHeader()
{
}

CListHeader::~CListHeader()
{
}


BEGIN_MESSAGE_MAP(CListHeader, CHeaderCtrl)
//{{AFX_MSG_MAP(CListHeader)
ON_WM_RBUTTONDOWN()
ON_COMMAND(ID_LST_ALL, OnLstAll)
ON_COMMAND(ID_LST_HIDE, OnLstHide)

//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListHeader message handlers
void CListHeader::OnRButtonDown(UINT nFlags, CPoint point) 
{
  CPoint pt = m_pt = point;
  ClientToScreen(&pt);
  
  // If no sort headers are defined for the parent control or popup menus
  // has been disabled, call the base class and return.
  CMenu menu;	
  VERIFY(menu.LoadMenu(IDR_RIGHT_LIST));
  
  CMenu* pPopup = menu.GetSubMenu(0);	
  ASSERT(pPopup != NULL);
  
  pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
    pt.x, pt.y,this);
  CHeaderCtrl::OnRButtonDown(nFlags, point);
}

int CListHeader::HitTest( CPoint pt ) const
{
  for (int iItem = 0; iItem < GetItemCount(); ++iItem)
  {
    CRect r;
    Header_GetItemRect(m_hWnd, iItem, &r);
    
    if (r.PtInRect(pt))
      return iItem;
  }
  
  return -1;
}

void CListHeader::SendNotify(int iIndex,int aButton)
{
  CWnd* pParentWnd = GetParent();
  if (pParentWnd && (
    pParentWnd->IsKindOf(RUNTIME_CLASS(CListCtrl)) ))
  {
    CWnd* pOwnerWnd = pParentWnd->GetOwner();
    if (pOwnerWnd)
    {
      TCHAR  lpBuffer[256];
      
      HDITEM hdi;
      hdi.mask       = HDI_TEXT|HDI_BITMAP|HDI_FORMAT|HDI_IMAGE|HDI_LPARAM|HDI_ORDER|HDI_WIDTH;
      hdi.pszText    = lpBuffer;
      hdi.cchTextMax = 256;
      
      GetItem(iIndex, &hdi);
      
      NMHEADER nmh;
      nmh.hdr.hwndFrom = m_hWnd;
      nmh.hdr.idFrom   = GetDlgCtrlID();
      nmh.hdr.code     = HDN_ITEMCLICK;
      nmh.iItem        = iIndex;
      nmh.iButton      = aButton;
      nmh.pitem        = &hdi;
      
      // send message to the parent's owner window.
      pOwnerWnd->SendMessage(WM_NOTIFY, 
        (WPARAM)(int)nmh.hdr.idFrom, (LPARAM)(NMHEADER*)&nmh);
      
      // then forward to the descendants.
      pOwnerWnd->SendMessageToDescendants(WM_NOTIFY, 
        (WPARAM)(int)nmh.hdr.idFrom, (LPARAM)(NMHEADER*)&nmh);
    }
  }
}

void CListHeader::OnLstAll() 
{
  int iIndex = HitTest(m_pt);
  if(iIndex !=-1) {
    m_nSortedCol = iIndex;
    SendNotify(iIndex,SM_LST_SHOW);
  }
}

void CListHeader::OnLstHide() 
{
  int iIndex = HitTest(m_pt);
  if(iIndex !=-1) {
    m_nSortedCol = iIndex;
    SendNotify(iIndex,SM_LST_HIDE);
  }
}
