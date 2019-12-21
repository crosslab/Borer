#include "stdafx.h"
#include "STabCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSTabCtrl
CSTabCtrl::CSTabCtrl()
{
}

CSTabCtrl::~CSTabCtrl()
{
}


BEGIN_MESSAGE_MAP(CSTabCtrl, CTabCtrl)
//{{AFX_MSG_MAP(CSTabCtrl)
ON_NOTIFY_REFLECT_EX(TCN_SELCHANGE, OnSelchange)
ON_WM_DESTROY()
ON_WM_CREATE()
ON_WM_SIZE()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSTabCtrl message handlers
int CSTabCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
  if (CTabCtrl::OnCreate(lpCreateStruct) == -1)
    return -1;
  
  return 0;
}

int CSTabCtrl::SetCurSel( int nItem )
{
  int  retSel=CTabCtrl::SetCurSel(nItem);
  
  OnSelchange(NULL,NULL);
  return retSel;
}

bool CSTabCtrl::AddControl(CWnd *_pControl,char *pszLabel,
                           INT _nIcon)
{
  // STabCtrl initialization
  TC_ITEM tcItem;
  int _nItem;
  
  _nItem=GetItemCount();
  
  tcItem.mask = TCIF_TEXT|TCIF_IMAGE;
  tcItem.cchTextMax = lstrlen(pszLabel);
  tcItem.pszText = pszLabel;
  tcItem.iImage  = _nIcon;
  InsertItem(_nItem,&tcItem);
  
  CList <CWnd *, CWnd *> * _pCtrlList = NULL;
  
  _pCtrlList = new CList <CWnd *, CWnd *>;
  m_PageToCtrlListMap.SetAt(_nItem, _pCtrlList);
  
  _pCtrlList -> AddTail(_pControl);
  
  return TRUE;
}

bool CSTabCtrl::AddControl(CWnd *_pControl,CString &pszTabItems,
                           INT _nIcon)
{
  bool bRet =AddControl(_pControl,pszTabItems.GetBuffer(pszTabItems.GetLength()),_nIcon);
  pszTabItems.ReleaseBuffer();
  return bRet;
}

BOOL CSTabCtrl::OnSelchange(NMHDR* pSelHDR, LRESULT* pSelRet) 
{
  INT _nCurrSel = GetCurSel();
  
  // show controls on current page.
  
  POSITION _rPos[2] = { m_PageToCtrlListMap.GetStartPosition(), NULL };
  CList <CWnd *, CWnd *> * _pCtrlList = NULL;
  CWnd * _pCtrl = NULL;
  INT _rKey (0);
  
  CRect rSel;
  GetClientRect(rSel);
  
  while(_rPos[0])
  {
    m_PageToCtrlListMap.GetNextAssoc(_rPos[0],_rKey,_pCtrlList);
    
    _rPos[1] = _pCtrlList -> GetHeadPosition();
    
    while(_rPos[1])
    {
      _pCtrl = _pCtrlList -> GetNext(_rPos[1]);
      ::MoveWindow(_pCtrl -> GetSafeHwnd(),1,1,
        rSel.Width()-2,
        rSel.Height()-26,
					   false);
      
      ::ShowWindow(_pCtrl -> GetSafeHwnd(), _nCurrSel == _rKey ? SW_SHOW : SW_HIDE );
      // cannot use because using this call with the MS WebBrowser
      // control destroys the control's window.
      //_pCtrl -> ShowWindow(_nCurrSel == _rKey);
    }
  }
  
  if(pSelRet) {
    *pSelRet = 0;
  }
  return FALSE;	// allow control to handle as well.
}

void CSTabCtrl::OnSize(UINT nType, int cx, int cy) 
{
  CTabCtrl::OnSize(nType, cx, cy);
  SetCurSel(GetCurSel());
}

void CSTabCtrl::OnDestroy() 
{
  CTabCtrl::OnDestroy();
  
  // clean up map.
  POSITION _rPos = m_PageToCtrlListMap.GetStartPosition();
  CList <CWnd *, CWnd *> * _pValue = NULL;
  INT _rKey;
  
  while(_rPos)
  {
    m_PageToCtrlListMap.GetNextAssoc(_rPos,_rKey,_pValue);
    _pValue -> RemoveAll();
    delete _pValue;
  }
  m_PageToCtrlListMap.RemoveAll();
}
