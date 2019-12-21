#include "stdafx.h"
#include "MainFrm.h"
#include "Borer.h"

#include "BorerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CBorerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CBorerDoc
IMPLEMENT_DYNCREATE(CBorerDoc, CDocument)

BEGIN_MESSAGE_MAP(CBorerDoc, CDocument)
//{{AFX_MSG_MAP(CBorerDoc)
ON_COMMAND(ID_READ_ONLY, OnReadOnly)
ON_UPDATE_COMMAND_UI(ID_READ_ONLY, OnUpdateReadOnly)
ON_COMMAND(ID_SAVEFILEC, OnSavefilec)
ON_COMMAND(ID_FILESAVEAS, OnFilesaveas)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBorerDoc construction/destruction

#pragma warning(disable:4355)
CBorerDoc::CBorerDoc() : m_xTextBuffer(this)
{
  // TODO: add one-time construction code here
  
  //	Initialize LOGFONT structure
  memset(&m_lf, 0, sizeof(m_lf));
  m_lf.lfWeight = FW_NORMAL;
  m_lf.lfCharSet = ANSI_CHARSET;
  m_lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
  m_lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
  m_lf.lfQuality = DEFAULT_QUALITY;
  m_lf.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
  strcpy(m_lf.lfFaceName, "Courier");
}

CBorerDoc::~CBorerDoc()
{
  
}

BOOL CBorerDoc::OnNewDocument()
{
  if (!CDocument::OnNewDocument())
    return false;
  
  m_xTextBuffer.InitNew();
  return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CBorerDoc serialization
void CBorerDoc::Serialize(CArchive& ar)
{
  if (ar.IsStoring())
  {
    // TODO: add storing code here
  }
  else
  {
    // TODO: add loading code here
  }
}

/////////////////////////////////////////////////////////////////////////////
// CBorerDoc diagnostics

#ifdef _DEBUG
void CBorerDoc::AssertValid() const
{
  CDocument::AssertValid();
}

void CBorerDoc::Dump(CDumpContext& dc) const
{
  CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBorerDoc commands
void CBorerDoc::DeleteContents() 
{
  CDocument::DeleteContents();
  
  m_xTextBuffer.FreeAll();
}

//打开文档，获得测试序列号，读取配置参数
BOOL CBorerDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{	
  CMainFrame  *pMyFrm =(CMainFrame*)AfxGetApp()->m_pMainWnd;//取主框架窗口指针
  
  CString	strFileName,strComPortIndex;
  strFileName=lpszPathName;
  strFileName.MakeUpper();	
  
  int n1 = strFileName.Find("任务");
  int n2 = strFileName.Find(':',n1);
  strComPortIndex=strFileName.Mid(n1+4,n2-n1-4);
  m_nPortIndex=atoi(strComPortIndex)-1;//获得测试序号	
  
  CWaitCursor wc;
  
  
  m_strInifile=pMyFrm->m_aTestInfo[m_nPortIndex]->m_strCfgFile ;
  
  InitRuntime();
  
  //判断文件是否存在，如果不存在创建新的文件，如果存在则加载此文件	
  CFileFind finder;//判断文件是否存在
  BOOL bWorking = finder.FindFile(m_strDocFile, 0 );
  if(bWorking)
  {
    m_xTextBuffer.LoadFromFile(m_strDocFile);
    SetPathName(m_strDocFile);
  }
  else
  {
    m_strDocFile.Format("%s",lpszPathName);
    m_xTextBuffer.InitNew();
  }
  
  SetModifiedFlag(false);
  finder.Close();
  return TRUE;
}

void CBorerDoc::NirvanaData()
{
  CMainFrame  *pMyFrm =(CMainFrame*)AfxGetApp()->m_pMainWnd;//取主框架窗口指针
  
  m_strInifile=pMyFrm->m_aTestInfo[m_nPortIndex]->m_strCfgFile ;
  
  CWaitCursor wc;
  InitRuntime();
  
  SetModifiedFlag(false);
}

//	读取参数，调试方式、发送间隔、等待时间、调试方式（串口或内存）
void CBorerDoc::InitRuntime()
{	
  CString strSec;
  
  CMainFrame  *pMyFrm =(CMainFrame*)AfxGetApp()->m_pMainWnd;//取主框架窗口指针
  strSec.Format("%s%d",CW_ITCOMSEC,pMyFrm->m_aTestInfo[m_nPortIndex]->m_nTesterSeq);
  
  m_nTestScript=ReadIniInt(strSec,"ntestScript",0);
  m_nAutoSend=ReadIniInt(strSec,"nautosend",0);
  m_nCreateReport=ReadIniInt(strSec,"nCreateReport",0);
  
  ReadIniString(strSec,"DOCNAME","",m_strDocFile.GetBuffer(_MAX_PATH),_MAX_PATH);
  m_strDocFile.ReleaseBuffer();
  
  ReadIniString(strSec,"HEADPATH","",m_strHeadPath.GetBuffer(_MAX_PATH),_MAX_PATH);
  m_strHeadPath.ReleaseBuffer();	
  
  m_nTimeSleep=ReadIniInt(strSec,"ntimesleep",1);
  m_nWaitoutTime=ReadIniInt(strSec,"nwaitouttime",30000);
  m_nGetValueTime=ReadIniInt(strSec,"nGetValuetime",30000);
  m_nKeepTime=ReadIniInt(strSec,"nKeyKeeptime",2000);
}

//保存文件
BOOL CBorerDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
  return TRUE;
  //	Note - we didn't call inherited member!
}

//文件只读
void CBorerDoc::OnReadOnly() 
{
  if (! m_xTextBuffer.GetReadOnly())
  {
    m_xTextBuffer.SetReadOnly(TRUE);
    AfxMessageBox("Document now read-only!");
  }
  else
    m_xTextBuffer.SetReadOnly(false);
}

void CBorerDoc::OnUpdateReadOnly(CCmdUI* pCmdUI) 
{
  pCmdUI->SetCheck(m_xTextBuffer.GetReadOnly());
}

void CBorerDoc::OnSavefilec() 
{
  CString strSec;
  char buf_Inner[_MAX_PATH];
  CMainFrame  *pMyFrm =(CMainFrame*)AfxGetApp()->m_pMainWnd;//取主框架窗口指针
  strSec.Format("%s%d",CW_ITCOMSEC,pMyFrm->m_aTestInfo[m_nPortIndex]->m_nTesterSeq);
  
  CFileFind finder;//判断文件是否存在
  BOOL bWorking = finder.FindFile(GetPathName(), 0 );
  if(!bWorking)
  {
    CFileDialog dlg(false,"","",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
      "C Files (*.C)|*.C|");
    if(dlg.DoModal() == IDOK)
    {
      m_xTextBuffer.SaveToFile(dlg.GetPathName());
      SetPathName( dlg.GetPathName(), TRUE );
      sprintf(buf_Inner,"%s",dlg.GetPathName());
      WriteIniString(strSec,"DOCNAME",buf_Inner);
    }
  }
  else
  {
    finder.FindNextFile();
    if(finder.IsReadOnly())
    {
      AfxMessageBox("文件属性是只读的，请先修改文件属性再存盘");
      finder.Close();
      return;
    }
    m_xTextBuffer.SaveToFile(GetPathName());
  }
  finder.Close();
  return ;
}

void CBorerDoc::OnFilesaveas() 
{
  CString strSec;
  char buf_Inner[_MAX_PATH];
  CMainFrame  *pMyFrm =(CMainFrame*)AfxGetApp()->m_pMainWnd;//取主框架窗口指针
  strSec.Format("%s%d",CW_ITCOMSEC,pMyFrm->m_aTestInfo[m_nPortIndex]->m_nTesterSeq);
  
  CFileDialog dlg(false,"","",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
    "C Files (*.C)|*.C|");
  if(dlg.DoModal() == IDOK)
  {
    m_xTextBuffer.SaveToFile(dlg.GetPathName());
    SetPathName( dlg.GetPathName(), TRUE );
    sprintf(buf_Inner,"%s",dlg.GetPathName());
    WriteIniString(strSec,"DOCNAME",buf_Inner);
  }
}

void CBorerDoc::OnCloseDocument() 
{
  //	CDocument::OnCloseDocument();
}

BOOL CBorerDoc::SaveModified() 
{
  if(!IsModified( ))
  {
    return 1;
  }
  
  CString str;
  str.Format("%s文件已经改变，是否要保存？",GetPathName());	
  if(AfxMessageBox(str, MB_YESNO|MB_ICONSTOP)==IDYES)
  {
    CString strSec;
    char buf_Inner[_MAX_PATH];
    CMainFrame  *pMyFrm =(CMainFrame*)AfxGetApp()->m_pMainWnd;//取主框架窗口指针
    strSec.Format("%s%d",CW_ITCOMSEC,pMyFrm->m_aTestInfo[m_nPortIndex]->m_nTesterSeq);
    
    CFileFind finder;//判断文件是否存在
    BOOL bWorking = finder.FindFile(GetPathName(), 0 );
    if(!bWorking)
    {
      CFileDialog dlg(false,"","",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
        "C Files (*.C)|*.C|");
      if(dlg.DoModal() == IDOK)
      {		
        m_xTextBuffer.SaveToFile(dlg.GetPathName());
        SetPathName( dlg.GetPathName(), TRUE );
        sprintf(buf_Inner,"%s",dlg.GetPathName());
        WriteIniString(strSec,"DOCNAME",buf_Inner);
      }
    }
    else
    {
      m_xTextBuffer.SaveToFile(GetPathName());
    }
    finder.Close();
  }
  return 1;
}

BOOL AFXAPI AfxFullPath(LPTSTR lpszPathOut, LPCTSTR lpszFileIn);
UINT AFXAPI AfxGetFileTitle(LPCTSTR lpszPathName, LPTSTR lpszTitle, UINT nMax);

void CBorerDoc::SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU) 
{
  // store the path fully qualified
  TCHAR szFullPath[_MAX_PATH];
  AfxFullPath(szFullPath, lpszPathName);
  m_strPathName = szFullPath;
  ASSERT(!m_strPathName.IsEmpty());       // must be set to something
  m_bEmbedded = FALSE;
  ASSERT_VALID(this);
  
  // set the document title based on path name
  TCHAR szTitle[_MAX_FNAME];
  if (AfxGetFileTitle(szFullPath, szTitle, _MAX_FNAME) == 0)
    SetTitle(szTitle);
  
  CString strFile ;
  strFile = m_strPathName ;
  strFile.MakeLower();
  
  if ((strFile.Find(".c") < 0) && (strFile.Find(".cpp") < 0))
  {
    return;
  }
  
  // add it to the file MRU list
  if (bAddToMRU)
    AfxGetApp()->AddToRecentFileList(m_strPathName);
  
  ASSERT_VALID(this);
}

