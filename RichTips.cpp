#include "stdafx.h"
#include "ParaDefi.h"

#include "Borer.h"
#include "MainFrm.h"
#include "BorerDoc.h"
#include "BorerView.h"

#include "RichTips.h"
#include "CFindTextDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


COLORREF tipsTints [] ={
  RGB(255,0,0),       // RED
    RGB(0,0,128),              // DARK_BLUE
    RGB(153,0,204),       // PURPLE		
    RGB(0,0,255),       // BLUE
    RGB(0,0,0),       // BLACK
    RGB(255,153,51),       // ORANGE
    RGB(255,255,0),       // YELLOW			
    RGB(255,51,153),       // HOT_PINK
    RGB(80,50,0),       // BROWN
    RGB(0,255,255),       // CYAN			
    RGB(255,255,255),       // WHITE
    RGB(199,177,255),       // LAVENDER
    RGB(255,226,177),       // PEACH
    RGB(0,192,0),       // FOREST_GREEN
    RGB(0,255,0),       // GREEN
    RGB(0,192,192),       // TURQUOISE
    RGB(0,0,192),       // ROYAL_BLUE
    RGB(192,192,192),       // GREY
    RGB(128,128,128),       // DARK_GREY
    RGB(255,198,107),       // TAN
    RGB(142,255,255),       // SKY_BLUE 
    RGB(128,0,0),       // MAROON
    RGB(255,143,107),       // DUSK
    RGB(225,225,225),       // LIGHT_GREY
};

/////////////////////////////////////////////////////////////////////////////
// CRichTips
CRichTips::CRichTips()
{
  // Initialise the Comment CHARFORMAT
  DWORD	dwMask	= CFM_COLOR | CFM_FACE | CFM_SIZE;
  
  m_bLastSeek =FALSE;
  m_pszSought =NULL;
  m_sevent =new char[20480];
  
  NONCLIENTMETRICS ncm;
  memset(&ncm, 0, sizeof(NONCLIENTMETRICS));
  ncm.cbSize =sizeof(NONCLIENTMETRICS);
  SystemParametersInfo(SPI_GETNONCLIENTMETRICS,sizeof(NONCLIENTMETRICS),&ncm,0);
  
  m_cfFiery.cbSize		= sizeof(CHARFORMAT);;
  m_cfFiery.dwMask		= dwMask;
  m_cfFiery.dwEffects	= 0;
  m_cfFiery.yHeight		= ncm.lfCaptionFont.lfHeight;
  m_cfFiery.crTextColor	= RGB(0xff,0x00,0x00);
  strcpy(m_cfFiery.szFaceName, ncm.lfCaptionFont.lfFaceName);
  
  m_cfCommon.cbSize		= sizeof(CHARFORMAT);;
  m_cfCommon.dwMask		= dwMask;
  m_cfCommon.dwEffects	= 0;
  m_cfCommon.yHeight		= ncm.lfCaptionFont.lfHeight;
  m_cfCommon.crTextColor	= RGB(0x00,0x00,0xff);
  strcpy(m_cfCommon.szFaceName, ncm.lfMessageFont.lfFaceName);
}

CRichTips::~CRichTips()
{
  delete []m_sevent;
  
}


BEGIN_MESSAGE_MAP(CRichTips, CRichEditCtrl)
//{{AFX_MSG_MAP(CRichTips)
ON_COMMAND(ID_TIP_FONT, OnTipFont)
ON_COMMAND(ID_TIP_SAVE, OnTipSave)
ON_COMMAND(ID_EDIT_COPY, OnTipCopy)
ON_COMMAND(ID_EDIT_SELECT_ALL, OnTipSelectAll)
ON_COMMAND(ID_EDIT_CLEAR, OnTipClear)
ON_WM_CONTEXTMENU()
ON_COMMAND(ID_EDIT_CUT, OnTipCut)
ON_COMMAND(ID_EDIT_PASTE, OnTipPaste)
ON_COMMAND(ID_EDIT_UNDO, OnTipUndo)
ON_WM_SETCURSOR()
ON_COMMAND(ID_EDIT_FIND, OnEditOutFind)
ON_COMMAND(ID_EDIT_REPEAT, OnEditOutRepeat)
ON_COMMAND(ID_EDIT_FIND_PREVIOUS, OnEditOutFindPrevious)
ON_WM_LBUTTONDBLCLK()
//}}AFX_MSG_MAP
ON_MESSAGE(MMM_SHOW_GETDATA, AddEditShow)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRichTips message handlers
void CRichTips::InternalAppendText(LPCTSTR szInternal,
                                   bool bFiery,
                                   COLORREF clrTip)
{
  int lenInternal;
  
  ASSERT(szInternal);
  ASSERT(AfxIsValidString(szInternal));
  
  int	 iTotalInternal = GetWindowTextLength();
  CWnd *focusWnd = GetFocus();
  
  //	Hide any selection and select the end of text marker.
  HideSelection(TRUE, TRUE);
  SetSel(iTotalInternal, iTotalInternal);
  
  //	Now set the character format
  if(bFiery) {
    m_cfFiery.crTextColor	    =clrTip;
    SetSelectionCharFormat(m_cfFiery);
  }else {
    m_cfCommon.crTextColor	=clrTip;
    SetSelectionCharFormat(m_cfCommon);
  }
  
  //	And put the text into the selection
  ReplaceSel(szInternal);
  lenInternal = GetWindowTextLength();
  //	Now select the end of text marker again
  SetSel(lenInternal, lenInternal);
  
  if (iTotalInternal > 125000)
  {
    //	The control's starting to get full so trim off the first 
    //	50,000 bytes....
    SetSel(0, 10000);
    ReplaceSel(_T(""));
    SetSel(iTotalInternal, iTotalInternal);
  }
  
  HideSelection(FALSE, TRUE);
  SendMessage(EM_SCROLLCARET, 0, 0);
  
  if (focusWnd !=(CWnd *) NULL) {
    focusWnd->SetFocus();
  }
  
  ((CXTFlatTabCtrl*)GetParent())->SyncScrollBar();
}

void CRichTips::OnTipClear() 
{
  m_bLastSeek =FALSE;
  
  if(m_pszSought != NULL)
    free(m_pszSought);
  m_pszSought =NULL;
  
  SetReadOnly(false);
  
  // Delete all of the text and copy it to the clipboard.
  SetSel(0, -1);
  Clear();
  
  // Set the rich edit control to be read-only.
  SetReadOnly(true);
  ASSERT(GetStyle() & ES_READONLY);
}

void CRichTips::OnTipCopy() 
{
  Copy();
}

void CRichTips::OnTipSelectAll() 
{
  SetFocus();
  SetSel(0,-1);
}

void CRichTips::OnTipCut() 
{
}

void CRichTips::OnTipPaste() 
{
}

void CRichTips::OnTipUndo() 
{
}

void CRichTips::OnContextMenu(CWnd* pWnd, CPoint point) 
{
  CMenu menu;
  VERIFY(menu.LoadMenu(IDR_RIGHT_TIP));
  
  CMenu* pPopup = menu.GetSubMenu(0);
  ASSERT(pPopup != NULL);
  
  pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x,
    point.y, this);
}

// My callback procedure that reads the rich edit control contents
// from a file.
static DWORD CALLBACK rtcbStreamOut(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
  CFile* pFile = (CFile*) dwCookie;
  
  pFile->Write(pbBuff, cb);
  *pcb = cb;
  
  return 0;
}

void CRichTips::OnTipSave() 
{
  CFrameWnd *pMyFrm=((CMainFrame*)AfxGetMainWnd())->GetActiveFrame();
  if(!pMyFrm)
  {
    return ;
  }
  
  CView *pMyView=pMyFrm->GetActiveView();
  if(!pMyView) 
  {
    return ;
  }
  CBorerDoc  *pMyDoc=(CBorerDoc*) pMyView->GetDocument();
  if(pMyDoc==NULL)
    return;
  CString strFileName = pMyDoc->m_strDocFile ;
  strFileName = strFileName.Left(strFileName.GetLength()-2);
  CFileDialog dlg(FALSE,"",strFileName,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
    "RTF Files (*.RTF)|*.RTF|");
  if(dlg.DoModal() !=IDOK) 
  {		
    return;
  }
  
  // The file to store the contents of the rich edit control.
  CFile cFile(dlg.GetPathName(), CFile::modeCreate|CFile::modeWrite);
  EDITSTREAM es;
  
  es.dwCookie = (DWORD) &cFile;
  es.pfnCallback = rtcbStreamOut; 
  StreamOut(SF_RTF, es);
}

void CRichTips::OnTipFont() 
{
  CFontDialog dlg;
  if (dlg.DoModal() == IDOK)
  {
	   // Create the font using the selected font from CFontDialog.
	   LOGFONT lf;
     memcpy(&lf, dlg.m_cf.lpLogFont, sizeof(LOGFONT));
     
     
     CFont font;
     VERIFY(font.CreateFontIndirect(&lf));
     
     SetFont(&font);
  }
}

void CRichTips::SaveLog(CString &logPath) 
{
  // The file to store the contents of the rich edit control.
  CFile cFile(logPath, CFile::modeCreate|CFile::modeWrite);
  EDITSTREAM es;
  
  es.dwCookie = (DWORD) &cFile;
  es.pfnCallback = rtcbStreamOut; 
  StreamOut(SF_RTF, es);
}

//‘ˆº”œ‘ æƒ⁄»›
LRESULT CRichTips::AddEditShow(WPARAM wParam, LPARAM lParam)
{
  int   ilen=LOWORD(lParam);
  memcpy(m_sevent,(char*)wParam,ilen);
  
  for(int i=0;i<ilen;i++)
  {
    if(m_sevent[i]==0x00)////∑¿÷π◊÷∑˚¥Æ“‚Õ‚÷’÷π£¨ÃÊªª◊÷∑˚¥Æ÷–µƒ÷’÷π∑˚
    {
      m_sevent[i]=0x20;
    }
  }
  if(ilen>0)
  {
    m_sevent[ilen]='\r';
    m_sevent[ilen+1]='\n';
    m_sevent[ilen+2]=0x00;
    
    InternalAppendText(m_sevent,false,tipsTints[HIWORD(lParam)]);
  }
  
  return 1;
}

BOOL CRichTips::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
  
  if(nHitTest==HTCAPTION) {
    ::SetCursor(LoadCursor(NULL, IDC_ARROW));
    return TRUE;
  }
  return CRichEditCtrl::OnSetCursor(pWnd, nHitTest, message);
}
void fnSynch(CString &msggg,int mslll,int msrrr,void *msppp);

void CRichTips::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
  POINTL pt3;
  CString str3,str5;
  int n3;
  
  pt3.x =point.x;
  pt3.y =point.y;
  
  int nFirstVisible =SendMessage(EM_CHARFROMPOS,0,(LPARAM)&pt3);
  n3 = LineLength(nFirstVisible)+8;
  
  nFirstVisible =LineFromChar(nFirstVisible);
  GetLine(nFirstVisible, str3.GetBuffer(n3),n3);
  str3.ReleaseBuffer();
  
  if(str3.Find("Failed at ") !=-1) {
    str3 =str3.Right(str3.GetLength()-str3.Find("Failed at ")-11);
    str5 =str3.Right(str3.GetLength()-str3.Find("--")-2);
    str3 =str3.Left(str3.Find("--")-1);
    
    CView *pMyView=((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveView();
    ((CBorerView*)pMyView)->Inr_glLine=atoi(str5)-1;
    fnSynch(str3,atoi(str5),0,pMyView);
  }
  
  CRichEditCtrl::OnLButtonDblClk(nFlags, point);
}

BOOL CRichTips::IsSelection()
{
  long nStartChar, nEndChar;
  
  GetSel(nStartChar, nEndChar); 
  
  return nStartChar != nEndChar;
}

long CRichTips::GetSelHeader()
{
  long nStartChar, nEndChar;
  
  GetSel(nStartChar, nEndChar); 
  
  return nStartChar==-1 ? 0 : nStartChar;
}

long CRichTips::GetSelTail()
{
  long nStartChar, nEndChar;
  
  GetSel(nStartChar, nEndChar); 
  
  return nEndChar==-1 ? 0 : nEndChar;
}

void CRichTips::OnEditOutFind() 
{
  CWinApp *pApp = AfxGetApp();
  ASSERT(pApp != NULL);
  
  CFindTextDlg dlg(this);
  if(m_bLastSeek)
  {
    //	Get the latest search parameters
    dlg.m_bMatchCase = (m_dwLastSearchFlags & FIND_MATCH_CASE) != 0;
    dlg.m_bWholeWord = (m_dwLastSearchFlags & FIND_WHOLE_WORD) != 0;
    dlg.m_nDirection = (m_dwLastSearchFlags & FIND_DIRECTION_UP) != 0 ? 0 : 1;
    if(m_pszSought != NULL)
      dlg.m_sTarText = m_pszSought;
  }
  else
  {
    //	Take search parameters from registry
    dlg.m_bMatchCase = pApp->GetProfileInt(RTIP_FIND_SUBKEY, RTIP_MATCH_CASE, FALSE);
    dlg.m_bWholeWord = pApp->GetProfileInt(RTIP_FIND_SUBKEY, RTIP_WHOLE_WORD, FALSE);
    dlg.m_nDirection = 1;		//	Search down
    dlg.m_sTarText = pApp->GetProfileString(RTIP_FIND_SUBKEY, RTIP_FIND_WHAT, _T(""));
  }
  
  //	Take the current selection, if any
  if(IsSelection())
  {
    dlg.m_sTarText =GetSelText();
    dlg.m_ptCurPos.x =GetSelTail();		//	Search from cursor position
  }else {
    dlg.m_ptCurPos.x =0x00;		//	Search from cursor position
  }
  
  //	Execute Find dialog
  dlg.DoModal();
  
  //	Save search parameters for 'F3' command
  m_bLastSeek = TRUE;
  if(m_pszSought != NULL)
    free(m_pszSought);
  
  m_pszSought = strdup(dlg.m_sTarText);
  
  m_dwLastSearchFlags = 0;
  if(dlg.m_bMatchCase)
    m_dwLastSearchFlags |= FIND_MATCH_CASE;
  if(dlg.m_bWholeWord)
    m_dwLastSearchFlags |= FIND_WHOLE_WORD;
  if(dlg.m_nDirection == 0)
    m_dwLastSearchFlags |= FIND_DIRECTION_UP;
  
  SetFocus();
  
  //	Save search parameters to registry
  pApp->WriteProfileInt(RTIP_FIND_SUBKEY, RTIP_MATCH_CASE, dlg.m_bMatchCase);
  pApp->WriteProfileInt(RTIP_FIND_SUBKEY, RTIP_WHOLE_WORD, dlg.m_bWholeWord);
  pApp->WriteProfileString(RTIP_FIND_SUBKEY, RTIP_FIND_WHAT, dlg.m_sTarText);
}

void CRichTips::OnEditOutRepeat() 
{
  if(m_bLastSeek)
  {
    // Set the selection to be the first occurrence of the 
    // string lpszmyString, if it is found.   
    FINDTEXTEX ft;
    ft.chrg.cpMin = GetSelTail();
    ft.chrg.cpMax = -1;
    ft.lpstrText = m_pszSought;
    
    long erPos =FindText(m_dwLastSearchFlags,&ft);
    
    if(erPos ==-1)
    {
      CString prompt;
      prompt.Format(IDS_EDIT_TEXT_NOT_FOUND, m_pszSought);
      AfxMessageBox(prompt);
      return;
    }
    
    SetSel(erPos, erPos +lstrlen(m_pszSought));
  }
}
void CRichTips::OnEditOutFindPrevious() 
{
  if(m_bLastSeek)
  {
    // Set the selection to be the first occurrence of the 
    // string lpszmyString, if it is found.   
    FINDTEXTEX ft;
    ft.chrg.cpMin = GetSelHeader();
    ft.chrg.cpMax = 0 ;
    ft.lpstrText = m_pszSought;
    
    long erPos = FindText(m_dwLastSearchFlags,&ft);
    
    if(erPos ==-1)
    {
      CString prompt;
      prompt.Format(IDS_EDIT_TEXT_NOT_FOUND, m_pszSought);
      AfxMessageBox(prompt);
      return;
    }
    
    SetSel(erPos, erPos +lstrlen(m_pszSought));
  }
}