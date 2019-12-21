// MoveBtn.cpp : implementation file
//

#include "stdafx.h"

#include "MoveBtn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMoveBtn

CMoveBtn::CMoveBtn()
:m_IsCurrSelected(FALSE)
{
  m_MoveRect.SetRectEmpty();
}

CMoveBtn::~CMoveBtn()
{
}


BEGIN_MESSAGE_MAP(CMoveBtn, CButton)
//{{AFX_MSG_MAP(CMoveBtn)
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_MOUSEMOVE()
ON_WM_CREATE()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMoveBtn message handlers

void CMoveBtn::OnLButtonDown(UINT nFlags, CPoint point) 
{
  // TODO: Add your message handler code here and/or call default
  m_IsCurrSelected = TRUE;
  
  CWnd* pParent = GetParent();
  if (!pParent) pParent = GetDesktopWindow();
  
  if(m_MoveRect.IsRectNull())
  {
    CRect ParentRect;                                   // Parent client area (Parent coords)
    pParent->GetClientRect(ParentRect);
    
    SetMoveRect(&ParentRect);
  }
  CRect MoveRect(m_MoveRect);
  
  pParent->ClientToScreen(&MoveRect);   
  
  ::SetCursor(LoadCursor(NULL, IDC_CROSS));
  SetCapture();
  ::ClipCursor(MoveRect);
  
  
  CButton::OnLButtonDown(nFlags, point);
}

void CMoveBtn::OnLButtonUp(UINT nFlags, CPoint point) 
{
  // TODO: Add your message handler code here and/or call default
  m_IsCurrSelected = FALSE;
  
  ::SetCursor(LoadCursor(NULL, IDC_ARROW));
  ReleaseCapture();
  ClipCursor(NULL);
  CButton::OnLButtonUp(nFlags, point);
}

void CMoveBtn::OnMouseMove(UINT nFlags, CPoint point) 
{
  // TODO: Add your message handler code here and/or call default
  if(m_IsCurrSelected)
  {
    CWnd* pParent = GetParent();
    if (!pParent) pParent = GetDesktopWindow();
    
    CRect ButtonRect;                                   // Button Dimensions (Parent coords)
    GetWindowRect(ButtonRect);  
    
    pParent->ScreenToClient(ButtonRect);
    
    ClientToScreen(&point);                             // Convert point to parent coords
    pParent->ScreenToClient(&point);
    
    CPoint Center = ButtonRect.CenterPoint();           // Center of button (parent coords)
    
    ButtonRect.top += (point.y - Center.y);
    ButtonRect.bottom += (point.y - Center.y);
    ButtonRect.right += (point.x - Center.x);
    ButtonRect.left += (point.x - Center.x);
    
    MoveWindow(&ButtonRect);
    RedrawWindow();		
  }
  CButton::OnMouseMove(nFlags, point);
}


BOOL CMoveBtn::SetPos(const CRect* rect)
{
  
  return SetWindowPos(NULL,rect->left,rect->top,rect->Width(),rect->Height(),SWP_SHOWWINDOW);
}

BOOL CMoveBtn::SetMoveRect(const CRect* rect)
{
  CWnd* pParent = GetParent();
  if (!pParent) pParent = GetDesktopWindow();
  
  
  CRect ButtonRect;                                  
  GetWindowRect(ButtonRect);
  pParent->ScreenToClient(ButtonRect);
  
  CPoint Center = ButtonRect.CenterPoint();
  
  if(NULL == rect)//²»¿ÉÒÆ¶¯
  {
    m_MoveRect.bottom = Center.y;
    m_MoveRect.top = Center.y;
    
    m_MoveRect.right = Center.x;
    m_MoveRect.left = Center.x;
    
  }
  else
  {
    m_MoveRect.bottom = rect->bottom - (ButtonRect.Height()+1)/2;
    m_MoveRect.top = rect->top + (ButtonRect.Height()+1)/2;
    
    m_MoveRect.right = rect->right - (ButtonRect.Width()+1)/2;
    m_MoveRect.left = rect->top + (ButtonRect.Width()+1)/2;
  }
  return TRUE;
}
