#include "stdafx.h"
#include "MainFrm.h"
#include "Borer.h"
#include "MpDef.h"

#include "editcmd.h"
#include "BorerDoc.h"
#include "BorerView.h"
#include "CrystalProtocol.h"
#include "SelectFlash.h"
#include "HookStdio.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBorerView
IMPLEMENT_DYNCREATE(CBorerView, CCrystalEditView)

BEGIN_MESSAGE_MAP(CBorerView, CCrystalEditView)
//{{AFX_MSG_MAP(CBorerView)
ON_WM_CONTEXTMENU()
ON_COMMAND(ID_CSI_RUN, OnCsiRunSolo)
ON_COMMAND(ID_CSI_GO, OnCsiGo)
ON_COMMAND(ID_CSI_STEPINTO, OnCsiStepInto)
ON_COMMAND(ID_CSI_STEPOUT, OnCsiStepout)
ON_COMMAND(ID_CSI_STEPOVER, OnCsiStepover)
ON_UPDATE_COMMAND_UI(ID_CSI_STEPOUT, OnUpdateCsiStepout)
ON_UPDATE_COMMAND_UI(ID_CSI_STEPOVER, OnUpdateCsiStepover)
ON_UPDATE_COMMAND_UI(ID_CSI_RUN, OnUpdateCsiRun)
ON_COMMAND(ID_CSI_RUNTOEND, OnCsiRuntoend)
ON_COMMAND(ID_CSI_STOP, OnCsiStop)
ON_UPDATE_COMMAND_UI(ID_CSI_STOP, OnUpdateCsiStop)
ON_WM_TIMER()
ON_UPDATE_COMMAND_UI(ID_CSI_GO, OnUpdateCsiGo)
ON_UPDATE_COMMAND_UI(ID_FILESAVEAS, OnUpdateFilesaveas)
ON_UPDATE_COMMAND_UI(ID_SAVEFILEC, OnUpdateSavefilec)
ON_COMMAND(ID_MN_DELAYTIME, OnMnDelaytime)
ON_COMMAND(ID_SCRIPT_STRTRACE, OnScriptStrtrace)
ON_COMMAND(ID_SCRIPT_MESSAGEBOX, OnScriptMessagebox)
ON_COMMAND(ID_SCRIPT_DEBUGBREAK, OnScriptDebugbreak)
ON_UPDATE_COMMAND_UI(ID_CSI_RUNTOEND, OnUpdateCsiRuntoend)
ON_UPDATE_COMMAND_UI(ID_CSI_STEPINTO, OnUpdateCsiStepinto)
ON_COMMAND(ID_SCRIPT_MAINFRAME, OnScriptMainframe)
ON_COMMAND(ID_SCRIPT_PDKREEXCUTE, OnPdkReExcute)
ON_COMMAND(ID_CSI_QUIT, OnCsiQuit)
ON_UPDATE_COMMAND_UI(ID_CSI_QUIT, OnUpdateCsiQuit)
ON_WM_SETFOCUS()
ON_MESSAGE(WM_MSG_ADD,AddItem)
ON_WM_KILLFOCUS()
ON_MESSAGE(MMM_HS_DATA, OnReceiveHSData)
ON_MESSAGE(MMM_WD_TRACK, OnWordTrack)
ON_MESSAGE(MMM_SOLOWINDUP, OnSoloWindup)
ON_COMMAND(MMM_LOAD_FILE, OnLoadFile)
ON_COMMAND(IDM_DEBUGTEST, OnDebugtest)
//}}AFX_MSG_MAP
// Standard printing commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBorerView construction/destruction


//构造函数
CBorerView::CBorerView()
{
  Inr_hStepOver=::CreateEvent(NULL,true,false,NULL);//初始无信号，手工重置
  m_nMenuType  = Y_INIT;
  MT_Eic =NULL;
  Trk_callDepth=-1;
  m_nStopflag=0x00;
}

CBorerView::~CBorerView()
{
  CloseHandle(Inr_hStepOver);
  
}

BOOL CBorerView::PreCreateWindow(CREATESTRUCT& cs)
{
  // TODO: Modify the Window class or styles here by modifying
  //  the CREATESTRUCT cs
  
  return CCrystalEditView::PreCreateWindow(cs);
}


/////////////////////////////////////////////////////////////////////////////
// CBorerView diagnostics

#ifdef _DEBUG
void CBorerView::AssertValid() const
{
  CCrystalEditView::AssertValid();
}

void CBorerView::Dump(CDumpContext& dc) const
{
  CCrystalEditView::Dump(dc);
}

CBorerDoc* CBorerView::GetDocument() // non-debug version is inline
{
  ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBorerDoc)));
  return (CBorerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBorerView message handlers
CCrystalTextBuffer *CBorerView::LocateTextBuffer()
{
  return &GetDocument()->m_xTextBuffer;
}

//界面初始化，参数设置
void CBorerView::OnInitialUpdate() 
{
  CCrystalEditView::OnInitialUpdate();
  
  CMainFrame  *pMyFrm =(CMainFrame*)AfxGetApp()->m_pMainWnd;//取主框架窗口指针
  CBorerDoc  *pMyDoc=(CBorerDoc*) GetDocument();
  SetFont(GetDocument()->m_lf);
  pMyDoc->SetPathName(pMyDoc->m_strDocFile);
  
  m_bWaitMsg=false;
  m_hGetWaitMsgEvent = CreateEvent(NULL,FALSE,FALSE,"GetWaitMsgEvent");
  
  m_bWaitValue=false;
  m_hGetValueEvent = CreateEvent(NULL,FALSE,FALSE,"GetValueEvent");
  
  pMyFrm->m_aTestInfo[pMyDoc->m_nPortIndex]->UpData_pView=this;
  
}

void CBorerView::NirvanaView()
{	
  CMainFrame  *pMyFrm =(CMainFrame*)AfxGetApp()->m_pMainWnd;//取主框架窗口指针
  CBorerDoc  *pMyDoc=(CBorerDoc*) GetDocument();
  
  pMyDoc->NirvanaData();
  
  
  m_bWaitMsg=false;
  ResetEvent(m_hGetWaitMsgEvent);
  
  m_bWaitValue=false;
  ResetEvent(m_hGetValueEvent);
  
}

void CBorerView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
  CMenu menu;
  VERIFY(menu.LoadMenu(IDR_RIGHT_MAIN));
  
  CMenu* pPopup = menu.GetSubMenu(0);
  ASSERT(pPopup != NULL);
  
  pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x,
    point.y, this);
}

//增加脚本内容
LRESULT CBorerView::AddItem(WPARAM wParam, LPARAM lParam)
{
  CBorerDoc  *pMyDoc=(CBorerDoc*) GetDocument();
  char* pMsg = (char*) lParam;		
  //	char *pcLineBuf = new char[nCurrentMax];
  CString str;
  str.Format("%s\r\n",pMsg);
  InsertString(str);
  
  return 1;
}



//载入文件内容，控制光标信息
void CBorerView::OnLoadFile() 
{
  CBorerDoc *pMyDoc =(CBorerDoc *)GetDocument();
  CString     strGL  =Inr_fileGL;
  
  strGL.Replace("/","\\");
  if(strcmp(pMyDoc->GetPathName(),strGL) || (Inr_glLine<0)) {
    pMyDoc->m_xTextBuffer.FreeAll();		
    pMyDoc->m_xTextBuffer.LoadFromFile(strGL);
    pMyDoc->SetPathName(strGL);
  }
  
  if(!m_pTextBuffer) {
    return;
  }
  
  if((Inr_glLine >=m_pTextBuffer->GetLineCount()) || (Inr_glLine<0)) {
    return;
  }
  
  CPoint pt(0, Inr_glLine);
  
  ASSERT_VALIDTEXTPOS(pt);
  SetCursorPos(pt);
  SetSelection(pt, pt);
  SetAnchor(pt);
  EnsureVisible(pt);
  m_pTextBuffer->SetLineFlag(Inr_glLine, LF_EXECUTION, true);
}



char showChar[1000];
/////////////////////////////////////////////////////////////////////////////
//功能: 处理协议通讯对象发送过来的消息
LRESULT CBorerView::OnReceiveHSData(WPARAM wpHsData, LPARAM lpHsData)
{
  unsigned char *ptrHsData=(unsigned char*)wpHsData;
  int            nHsDataLen=LOWORD(lpHsData);
  RxCallerMsgType nKind=(RxCallerMsgType)  HIWORD(lpHsData);
  
  CMainFrame  *pMyFrm =(CMainFrame*)AfxGetApp()->m_pMainWnd;//取主框架窗口指针
  CBorerDoc  *pMyDoc=(CBorerDoc*) GetDocument();
  
  pc2hsPacket* pPacketBuf;
  memset( &m_waitedMsg, '\0', sizeof(EM_MESSAGE));
  CString strMsg,strValue,temp;
  int i=0;
  int k=0;
  
  memset(showChar,0,1000);
  //判断包类型
  
  switch (nKind)
  {
  case CALLER_RX_MSG://消息包
    
    pPacketBuf=(pc2hsPacket*)ptrHsData;
    memcpy(&m_waitedMsg, pPacketBuf->content, nHsDataLen-13);	
    
    if(m_bDelMsg)
    {
      m_arrReceiveMsg.RemoveAll();
      m_bDelMsg=false;
      
    }
    m_arrReceiveMsg.Add(m_waitedMsg);
    //2.查看是否处在等待状态
    if(m_bWaitMsg)
    { 
      //如果是比较消息和等待消息是否一致。
      for(k=0;k<m_aWaitMsg.GetSize();k++)
      {
        //ZZZ		if(CompareMsgArray(m_aWaitMsg[k],m_arrReceiveMsg))
        //ZZZ		{  
        // 触发事件
        //ZZZ			PulseEvent(m_hGetWaitMsgEvent);
        //ZZZ			break;
        //ZZZ		}  
      }
    }
    //3.转化消息到消息宏名称，显示。
    //ZZZ	MsgToCString(m_waitedMsg,strMsg,this);
    
    sprintf(showChar,"%s",strMsg);
    pMyFrm->m_editMcu[pMyDoc->m_nPortIndex]->SendMessage(MMM_SHOW_GETDATA,(WPARAM)showChar,MAKELPARAM(strlen(showChar),INMSG));
    break;
    
  case CALLER_RX_VALUE://查询包，取出查询值显示。
    pPacketBuf=(pc2hsPacket*)ptrHsData;
    //		memcpy(m_sContent, pPacketBuf->content+4, nHsDataLen-13-4);
    strValue="查询变量值为:";
    for(i = 0; i < (nHsDataLen-13-4); i++)
    {
      temp.Format("0x%02x,",pPacketBuf->content[4+i]);
      strValue+=temp;
    }
    //		memcpy(showChar, pPacketBuf->content+4, nHsDataLen-13-4);
    //		strValue.Format("查询变量值为:%s",showChar);
    if(strValue.GetLength()>1000)
    {
      sprintf(showChar,"%s","数据太长，无法显示");
    }
    else
    {
      sprintf(showChar,"%s",strValue);
    }
    pMyFrm->m_editMcu[pMyDoc->m_nPortIndex]->SendMessage(MMM_SHOW_GETDATA,(WPARAM)showChar,MAKELPARAM(strlen(showChar),ININQIURE));
    if(m_bWaitValue)
    {
      PulseEvent(m_hGetValueEvent);
    }
    break;
  case CALLER_RX_MCU:		
    memcpy(showChar, ptrHsData, nHsDataLen);
    pMyFrm->m_editMcu[pMyDoc->m_nPortIndex]->SendMessage(MMM_SHOW_GETDATA,(WPARAM)showChar,MAKELPARAM(nHsDataLen,INTRACE));
    break;
    
  case CALLER_RX_CTRL:		
    memcpy(showChar, ptrHsData, nHsDataLen);
    pMyFrm->m_editMcu[pMyDoc->m_nPortIndex]->SendMessage(MMM_SHOW_GETDATA,(WPARAM)showChar,MAKELPARAM(nHsDataLen,INTRACE));
    break;
    
  default:
    
    memcpy(showChar, ptrHsData, nHsDataLen);
    pMyFrm->m_editMcu[pMyDoc->m_nPortIndex]->SendMessage(MMM_SHOW_GETDATA,(WPARAM)showChar,MAKELPARAM(nHsDataLen,INTRACE));
    break;
  }
  return true;
}

//定时器，进行自动发送功能
void CBorerView::OnTimer(UINT nIDEvent) 
{
  CMainFrame  *pMyFrm =(CMainFrame*)AfxGetApp()->m_pMainWnd;//取主框架窗口指针
  
  CBorerDoc  *pMyDoc=(CBorerDoc*) GetDocument();
  if(!pMyDoc->m_nAutoSend)
  {
    return;
  }
  
  CCrystalEditView::OnTimer(nIDEvent);	
  
}

void CBorerView::OnUpdateCsiStepout(CCmdUI* pCmdUI) 
{
  pCmdUI->Enable((m_nMenuType !=Y_IDLE) && (m_nMenuType !=Y_RUN) && (m_nMenuType !=Y_INIT));
}

void CBorerView::OnUpdateCsiStepover(CCmdUI* pCmdUI) 
{
  pCmdUI->Enable((m_nMenuType !=Y_IDLE) && (m_nMenuType !=Y_RUN) && (m_nMenuType !=Y_INIT));
}

void CBorerView::OnUpdateCsiGo(CCmdUI* pCmdUI) 
{
  pCmdUI->Enable(m_nMenuType == Y_IDLE);
}

void CBorerView::OnUpdateCsiRun(CCmdUI* pCmdUI) 
{
  pCmdUI->Enable(m_nMenuType == Y_IDLE);
}

void CBorerView::OnUpdateCsiQuit(CCmdUI* pCmdUI) 
{
  pCmdUI->Enable(m_nMenuType != Y_IDLE);
  pCmdUI->SetCheck(m_nStopflag);
}

void CBorerView::OnUpdateCsiStop(CCmdUI* pCmdUI) 
{
  pCmdUI->Enable(m_nMenuType != Y_IDLE);
  pCmdUI->SetCheck(m_nStopflag);
}

void CBorerView::OnUpdateFilesaveas(CCmdUI* pCmdUI) 
{
  pCmdUI->Enable(m_nMenuType == Y_IDLE);
}

void CBorerView::OnUpdateSavefilec(CCmdUI* pCmdUI) 
{
  pCmdUI->Enable(m_nMenuType == Y_IDLE);
}

void CBorerView::OnUpdateCsiRuntoend(CCmdUI* pCmdUI) 
{
  pCmdUI->Enable(m_nMenuType == Y_IDLE);
}

void CBorerView::OnUpdateCsiStepinto(CCmdUI* pCmdUI) 
{
  pCmdUI->Enable((m_nMenuType != Y_RUN) && (m_nMenuType != Y_INIT));
}

//从开始位置运行到结束，遇到断点不停，并没有任何光标信息。
void CBorerView::OnCsiRunSolo()
{
  GetDocument()->OnSavefilec();
  GetDocument()->m_xTextBuffer.SetReadOnly(true);
  
  m_nMenuType = Y_RUN;
  Trk_callDepth = 0;
  
  MT_Eic = AfxBeginThread(ProcRunSolo,(void *)this,THREAD_PRIORITY_TIME_CRITICAL,0, CREATE_SUSPENDED);    
  MT_Eic->m_bAutoDelete=false;
  MT_Eic->ResumeThread();
  
  GetDocument()->m_xTextBuffer.SetReadOnly(false);
}

//DEBUG调试，从当前位置运行，遇到断点，停止在断点处，如果没有断点，运行到结束。
void CBorerView::OnCsiGo() 
{ 
  if(m_nMenuType == Y_IDLE) {
    m_nMenuType = Y_GO;	
    Trk_callDepth = 0;
    

    GetDocument()->OnSavefilec();
    GetDocument()->m_xTextBuffer.SetReadOnly(true);
 /* G__stepmode(1);
    G__setautoconsole(1); 
    G__loadfile(GetDocument()->m_strDocFile.GetBuffer(GetDocument()->m_strDocFile.GetLength()));
    G__setbreakpoint("3",GetDocument()->m_strDocFile.GetBuffer(GetDocument()->m_strDocFile.GetLength()));
    GetDocument()->m_strDocFile.ReleaseBuffer(GetDocument()->m_strDocFile.GetLength());
  */
      int more = 0;

   // G__process_cmd("s","",&more,NULL,NULL);
   // G__input("input command > ");
    
 //   MT_Eic = AfxBeginThread(ProcRunSolo,(void *)this,THREAD_PRIORITY_TIME_CRITICAL,0, CREATE_SUSPENDED);    
//    MT_Eic->m_bAutoDelete=false;
 //   MT_Eic->ResumeThread();
    char commandLine[255];
    sprintf(commandLine,"%s %s","L ", GetDocument()->m_strDocFile.GetBuffer(GetDocument()->m_strDocFile.GetLength()));
    GetDocument()->m_strDocFile.ReleaseBuffer(GetDocument()->m_strDocFile.GetLength());

    G__init_process_cmd();
    // G__stepmode(1);
    // G__setautoconsole(1); 
    // G__process_cmd("cint>","",&more,NULL,NULL);
    char step1[10];
    memset(step1,10,0);
    sprintf(step1,"%s","T");
  
  // Hook stdio output
  CHookStdio hs( STD_OUTPUT_HANDLE, 64 * 1024 );
  char buf[ 64 * 1024 ] = "";

    G__process_cmd(commandLine,"",&more,NULL,NULL);
    //G__pause(); 
    G__process_cmd(step1,"",&more,NULL,NULL);

    sprintf(step1,"%s","S");
    
    G__process_cmd(step1,"",&more,NULL,NULL);
  // Get output

  buf[ hs.Read( buf, sizeof( buf ) - 1 ) ] = 0;
 
    G__AllocConsole();

   // G__FreeConsole();
  //  G__process_cmd("8","s",&more,NULL,NULL);

    //G__setbreakpoint("3",GetDocument()->m_strDocFile.GetBuffer(GetDocument()->m_strDocFile.GetLength()));
    //G__FreeConsole();
  }else {
    m_nMenuType = Y_GO;	
 //   SetEvent(Inr_hStepOver);
   // G__stepmode(0);
    if(m_pTextBuffer != NULL)
    {
        int nLine = m_pTextBuffer->FindNextBreakpointLine(GetCursorPos().y);
        char bufLine[8];
        memset(bufLine,0,sizeof(bufLine));
        if(nLine >= 0)
        {
          sprintf(bufLine,"%d",nLine);
       //   G__setbreakpoint(bufLine,GetDocument()->m_strDocFile.GetBuffer(GetDocument()->m_strDocFile.GetLength()));
        }
    }
  }
}

//F11调试 从当前位置一步一步的运行，遇到函数进入到函数中，并一步一步的执行。
void CBorerView::OnCsiStepInto() 
{
  if(m_nMenuType == Y_IDLE) {
    m_nMenuType =Y_STEPINTO;
    Trk_callDepth=0;
    
  //  GetDocument()->OnSavefilec();
  //  GetDocument()->m_xTextBuffer.SetReadOnly(true);
    int more = 0;
    // G__exec_asm(0,0,NULL,0);
    int local_error = 0;
    int rv = G__process_cmd("s\n\r","cint >s\n\r",&more,&local_error,0);
//   if (local_error == 0 && G__get_return(&fExitCode) == G__RETURN_EXIT2) {
    
   // }

//    MT_Eic =AfxBeginThread(ProcRunSolo,(void *)this,THREAD_PRIORITY_TIME_CRITICAL,0, CREATE_SUSPENDED);    
//    MT_Eic->m_bAutoDelete=false;
 //   MT_Eic->ResumeThread();
  }else {
    m_nMenuType = Y_STEPINTO;
    SetEvent(Inr_hStepOver); 
  }
}

//Stepout调试 从当前位置运行出该函数体，但如果函数中存在断点，则停在断点处。
void CBorerView::OnCsiStepout() 
{
  m_nMenuType = Y_STEPOUT;
  Snap_callDepth = Trk_callDepth;
  SetEvent(Inr_hStepOver); 
}

//Stepover调试 从当前位置一步一步的运行，遇到函数不进入到函数体中，但如果函数中存在断点，则停在断点处。
void CBorerView::OnCsiStepover() 
{
  if(m_nMenuType !=Y_STEPOVER) {
    m_nMenuType = Y_STEPOVER;
    Snap_callDepth = Trk_callDepth;
  }
  
  SetEvent(Inr_hStepOver); 
}

//从当前位置运行出结束，遇到断点不停。
void CBorerView::OnCsiRuntoend() 
{
  if(m_nMenuType ==Y_IDLE) 
  {
    m_nMenuType =Y_RUNTOEND;	
    Trk_callDepth=0;
    
    GetDocument()->OnSavefilec();
    GetDocument()->m_xTextBuffer.SetReadOnly(true);
    
    MT_Eic =AfxBeginThread(ProcRunSolo,(void *)this,THREAD_PRIORITY_TIME_CRITICAL,0, CREATE_SUSPENDED);    
    MT_Eic->m_bAutoDelete=false;
    MT_Eic->ResumeThread();
  }
  else
  {
    m_nMenuType = Y_RUNTOEND;
    SetEvent(Inr_hStepOver); 
  }
}

//停止脚本的执行。
void CBorerView::OnCsiStop() 
{
  // wait for the thread to exit....		
  m_nStopflag =0x01;
  WaitForSingleObject(MT_Eic->m_hThread,INFINITE);
}

void CBorerView::OnCsiQuit() 
{
  if(!MT_Eic) {
    return;
  }
  
  m_wdEnd =true;
  
  // wait for the thread to exit....		
  m_nStopflag =0x01;
  WaitForSingleObject(MT_Eic->m_hThread,INFINITE);
}

/////////////////////////////////////////////////////////////////////////////
//功能: 处理协议通讯对象发送过来的消息
LRESULT CBorerView::OnSoloWindup(WPARAM wpHsData, LPARAM lpHsData)
{
  if(lpHsData) {
    Inr_fileGL =*(CString*)wpHsData;
    Inr_glLine =-1;
    OnLoadFile();
  }
  
  delete (CString*)wpHsData;
  m_nStopflag =0x00;
  
  delete MT_Eic;
  MT_Eic =NULL;
  
  m_nMenuType  = Y_IDLE;
  Trk_callDepth=-1;
  
  GetDocument()->m_xTextBuffer.SetReadOnly(false);
  return 0;
}

LRESULT CBorerView::OnWordTrack(WPARAM wpHsData, LPARAM lpHsData)
{
  CMainFrame  *pMyFrm =(CMainFrame*)AfxGetApp()->m_pMainWnd;//取主框架窗口指针
  CWaitCursor wc;
  
  pMyFrm->m_editMcu[GetDocument()->m_nPortIndex]->SaveLog(((WDIINFO*)lpHsData)->wdiResult);
  pMyFrm->m_editMcu[GetDocument()->m_nPortIndex]->OnTipClear();
  
  if(GetDocument()->m_nCreateReport ==1)
  {
    m_wdObj.WDTrack((WDIINFO*)lpHsData);
  }
  
  delete MT_Eic;
  MT_Eic =NULL;
  
  if(!m_wdEnd && pMyFrm->m_treeProject.m_qary.GetSize()) 
  {
    MT_Eic =AfxBeginThread(ProcRunChorus,(void *)this,THREAD_PRIORITY_TIME_CRITICAL,0, CREATE_SUSPENDED);    
    MT_Eic->m_bAutoDelete=false;
    MT_Eic->ResumeThread();
  }
  else
  {
    if(GetDocument()->m_nCreateReport ==1)
    {
      m_wdObj.WDFini();
    }
    
    m_nMenuType  = Y_IDLE;
    Trk_callDepth=-1;
    
    GetDocument()->m_xTextBuffer.SetReadOnly(false);
  }
  
  return 0;
}

void CBorerView::OnMnDelaytime() 
{
  ((CMainFrame*)(AfxGetApp()->m_pMainWnd))->OnMnDelaytime();
}

void CBorerView::OnScriptStrtrace() 
{
  ((CMainFrame*)(AfxGetApp()->m_pMainWnd))->OnScriptStrtrace();
}

void CBorerView::OnScriptMessagebox() 
{
  ((CMainFrame*)(AfxGetApp()->m_pMainWnd))->OnScriptMessagebox();
}

void CBorerView::OnScriptDebugbreak() 
{
  ((CMainFrame*)(AfxGetApp()->m_pMainWnd))->OnScriptDebugbreak();
}

void CBorerView::OnScriptMainframe() 
{
  ((CMainFrame*)(AfxGetApp()->m_pMainWnd))->OnScriptMainframe();
}

void CBorerView::OnPdkReExcute() 
{
  CString strPdk;
  
  //ZZZ	if(dlg.DoModal()==IDOK)
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
    //ZZZ	CString strFileName = dlg.m_strFlashFile ;
    //ZZZ	strFileName.Replace("\\","\\\\");
    //ZZZ	strPdk.Format("%s%s%s","ITResetPDK(\"",strFileName,"\");");
    //ZZZ	pMyView->SendMessage(WM_MSG_ADD,0,(LPARAM) (strPdk.GetBuffer(strPdk.GetLength())));			
    
    //	pMyView->SendMessage(WM_MSG_ADD,0,(LPARAM)lpCMain);
  }
}

void CBorerView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
  CCrystalEditView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

std::string CBorerView::g_sCintLastError;

void CBorerView::CintError(char *msg) 
{
  // Is it an error description?
  if ( !strnicmp( msg, "Error", 5 ) )
  {
    g_sCintLastError += msg;
    g_sCintLastError += "\r\n";
    
  } // end if
}

void CBorerView::ShowError(LPCTSTR pError)
{
  // Set foreground color to orange
  //ZZZ	::SendMessage( m_hwndOutput, SCI_STYLESETFORE, STYLE_DEFAULT, (LPARAM)RGB( 255, 128, 0 ) );
  //ZZZ		::SendMessage( m_hwndOutput, SCI_STYLECLEARALL, 0, 0L );
  
  // Show error message if any
  //ZZZ	if ( pError )
  //ZZZ		::SendMessage( m_hwndOutput, SCI_SETTEXT, 0, (WPARAM)pError );
  if(pError) {
    AfxMessageBox(pError);
  }
}


void func(int a,int b,int *pc)
{
  // You came into the function. 
  
  // Input "v" and return to list source code
  *pc=a+b;
  
  int i;
  double ary[1000];
  for(i=0;i<1000;i++) 
  {
    ary[i] = i;
  }
}

void CBorerView::OnDebugtest() 
{
  // TODO: Add your command handler code here
  int a=1,b=2,c;
  char * pp = "aaaa";
  c = G__first_exam(pp);
  
  G__stepmode(1);
  // Follow the instruction,
  //
  // Input "S" and RETURN to step to next statement
  c=a+b;
  // If you want to step into function, input "s" and RETURN
  func(a,b,&c);
  // You step out from the function
  // Suppose you want to continue upto line 40, input "c 40" and RETURN
  
  c=a-b;
  
  a++;
  b++;
  
  func(b,c,&a);
  
  // You came to line 40.
  
  // Suppose you want to step over the function but want to know
  // what is going on. 
  
  // Input "T" and RETURN to turn on trace mode
  // Then "S" and RETURN" to step over the function.
  func(c,a,&b);
  // You saw the source code is traced.
  
  // Now this time, lets not execute following function.
  // Input "i" and RETURN to ignore the statement.
  func(c,a,&b);
  // Statement (function call) was ignored.
  
  // Input "T" and RETURN to toggle off trace mode 
  // Then "S" and RETURN to step.
  a=c*b;
  
  // Suppose you want to continue to the end
  // Input "c" and RETURN
  
  int i;
  int dmy[20001];
  for(i=0;i<10000;i++) dmy[i]=i;
  
  i=1;
  while(i<20000) { //  This is where you are.
    dmy[i]=i;
    //
    // Now, you know why program does not finish.
    // This is an infinite loop. Very bad.
    // 
    // Lets change i value and exit from the loop
    // Input "p i" and RETURN to monitor i value
    // Input "p i=20000" and RETURN to modify i value
    //
    // Then "c" to continue
  } 
  while(G__pause()==0) ;
}
