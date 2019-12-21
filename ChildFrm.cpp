#include "stdafx.h"
#include "Borer.h"

#include "ChildFrm.h"
#include "BorerDoc.h"
#include "BorerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame
IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
//{{AFX_MSG_MAP(CChildFrame)
ON_WM_SIZE()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
  // TODO: add member initialization code here
  
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
  // TODO: Modify the Window class or styles here by modifying
  //  the CREATESTRUCT cs
  
  return CMDIChildWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
  CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
  CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers

BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
  return m_wndSplitter.Create(this, 2, 2, CSize(30, 30), pContext);
}

#define		ID_EDIT_FIND_PREVIOUS		37126

BOOL CChildFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
  if((((nID>=ID_EDIT_CLEAR) && (nID<=ID_EDIT_REDO)) || (nID==ID_EDIT_FIND_PREVIOUS)) && !nCode && !pExtra && !pHandlerInfo) {
    CWnd *pRT=GetFocus();
    if(pRT &&
      pRT->IsKindOf(RUNTIME_CLASS(CRichEditCtrl)) &&
      pRT->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo)) {
      return TRUE;
    }
  }
  
  return CMDIChildWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}
