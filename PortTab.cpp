#include "stdafx.h"
//#include "CommonDef.h"
#include "Borer.h"

#include "MainFrm.h"
#include "STabCtrl.h"
#include "PortTab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPortTab
CPortTab::CPortTab()
{
}

CPortTab::~CPortTab()
{
}


BEGIN_MESSAGE_MAP(CPortTab, CSTabCtrl)
//{{AFX_MSG_MAP(CPortTab)
// NOTE - the ClassWizard will add and remove mapping macros here.
//}}AFX_MSG_MAP
ON_NOTIFY(NM_CUSTOMDRAW, IDMC_HARDWARE, OnCustomdrawPortList)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPortTab message handlers
void CPortTab::OnCustomdrawPortList(NMHDR* pNMHDR, LRESULT* pResult)
{
  NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR);
  
  // This is the beginning of an item's paint cycle.
  CMainFrame *pMyFrm=(CMainFrame*)AfxGetApp()->m_pMainWnd;//取主框架窗口指针
  if(pMyFrm==NULL)
  {
    return;
  }
  
  *pResult = 0;
  
  // Request item-specific notifications if this is the
  // beginning of the paint cycle.
  
  if(CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage)
  {
    *pResult = CDRF_NOTIFYITEMDRAW;
  }
  else if(CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage)
  {
    
    LVITEM   lvDrop;
    int      iDrop = static_cast<int>( pLVCD->nmcd.dwItemSpec);
    CDC*     pDC   = CDC::FromHandle(pLVCD->nmcd.hdc);
    
    CRect    rcDrop;
    CRect    rcText;
    
    CString  sText;
    COLORREF crBkgnd;
    
    BOOL     bListHasFocus;
    UINT     uFormat;
    
    bListHasFocus =(pMyFrm->m_PortList.GetSafeHwnd() == ::GetFocus());
    
    // Get the image index and selected/focused state of the
    // item being drawn.
    ZeroMemory(&lvDrop, sizeof(LVITEM));
    lvDrop.mask  = LVIF_IMAGE | LVIF_STATE;
    lvDrop.iItem = iDrop;
    lvDrop.stateMask = LVIS_SELECTED | LVIS_FOCUSED;
    pMyFrm->m_PortList.GetItem(&lvDrop);
    
    // Get the rect that holds the item's icon.
    pMyFrm->m_PortList.GetItemRect(iDrop, &rcDrop, LVIR_ICON);
    
    // Draw the icon.
    uFormat = ILD_TRANSPARENT;
    
    if((lvDrop.state & LVIS_SELECTED) && bListHasFocus)
    {
      uFormat |= ILD_FOCUS;
    }
    
    if(pMyFrm->m_aTestInfo[iDrop]->m_nSendManner==SM_SHAREMEMORY)
    {
      if(pMyFrm->m_aTestInfo[iDrop]->m_nTesterState==TS_WORKING)
      {
        lvDrop.iImage=3;
      }
      else
      {
        lvDrop.iImage=2;
      }
    }
    else
    {
      if(pMyFrm->m_aTestInfo[iDrop]->m_nTesterState==TS_WORKING) 
      {
        lvDrop.iImage=1;
      }
      else 
      {
        lvDrop.iImage=0;
      }
    }
    
    pMyFrm->m_BigImgs.Draw(pDC, lvDrop.iImage, rcDrop.TopLeft(), uFormat);
    
    // Get the rect that bounds the text label.
    pMyFrm->m_PortList.GetItemRect(iDrop, rcDrop, LVIR_LABEL);
    if(lvDrop.state & LVIS_SELECTED) 
    {
      if(bListHasFocus)
      {
        crBkgnd = GetSysColor(COLOR_HIGHLIGHT);
        pDC->SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));
      }
      else 
      {
        crBkgnd = GetSysColor(COLOR_BTNFACE);
        pDC->SetTextColor(GetSysColor(COLOR_BTNTEXT));
        
      }
    }
    else
    {
      crBkgnd = GetSysColor(COLOR_WINDOW);
      pDC->SetTextColor(GetSysColor(COLOR_BTNTEXT));
      
    }
    
    // Draw the background & prep the DC for the text drawing.  Note
    // that the entire item RECT is filled in, so this emulates the full-
    // row selection style of normal lists.
    pDC->FillSolidRect(rcDrop, crBkgnd);
    pDC->SetBkMode(TRANSPARENT);
    
    // Tweak the rect a bit for nicer-looking text alignment.
    rcText = rcDrop;
    rcText.left += 3;
    rcText.top++;
    
    // Draw the text.
    sText = pMyFrm->m_PortList.GetItemText(iDrop, 0);
    pDC->DrawText(sText, rcText, DT_VCENTER | DT_SINGLELINE);
    
    // Draw a focus rect around the item if necessary.
	   if(bListHasFocus &&(lvDrop.state & LVIS_FOCUSED))
     {
       pDC->DrawFocusRect(rcDrop);
     }
     
     *pResult = CDRF_SKIPDEFAULT;    // We've painted everything.
  }
}
