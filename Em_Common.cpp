#include "stdafx.h"
#include "io.h"

#include "Borer.h"
#include "MpDef.h"

#include "MainFrm.h"
#include "BorerDoc.h"
#include "BorerView.h"

#include "CrystalProtocol.h"
#include "WordDrive.h"
#include "HookStdio.h"

extern CBorerApp theApp;

/*******************去除零结尾字符串开头，结尾不可见字符***********************/
char *Trim(char *UsedStr)
{
  int i;
  int StrLength;
  int StrBegin=-1,StrEnd=-1;
  
  StrLength=strlen(UsedStr);
  if (StrLength==0)		return UsedStr;
  
  for(i=0;i<StrLength;i=i+1)
    if (UsedStr[i]!=9 && UsedStr[i]!=10 && UsedStr[i]!=13 && UsedStr[i]!=32)
    {
      StrBegin=i;
      break;
    }
    for(i=StrLength-1;i>=0;i=i-1)
      if (UsedStr[i]!=9 && UsedStr[i]!=10 && UsedStr[i]!=13 && UsedStr[i]!=32)
      {
        StrEnd=i;
        break;
      }
      if (StrBegin>=0 && StrEnd>=0)
      {
        memcpy(UsedStr, UsedStr+StrBegin, StrEnd-StrBegin+1);
        *(UsedStr+StrEnd-StrBegin+1)='\0';
        return UsedStr;
      }
      else
      {
        *UsedStr='\0';
        return UsedStr;
      }
}

bool Ravelout(CString &roIni,CString &roWif)
{
  CString roStr=roIni;
  CString roOrg=roWif;
  
  while(true) 
  {
    if(roWif.IsEmpty()) 
    {
      break;
    }
    
    roStr=roStr.Left(roStr.ReverseFind('\\'));
    
    if(roWif.Find(":\\")==-1)
    {
      roWif=roStr+"\\"+roOrg;
    }else {
      break;
    }
    
    if(_access(roWif,0x00)!=-1) {
      break;
    }
    
    roStr=roStr.Left(roStr.ReverseFind('\\'));
    
    roWif=roStr+"\\ini\\"+roOrg;
    if(_access(roWif,0x00)!=-1) {
      break;
    }
    
    roWif=roStr+"\\bmp\\"+roOrg;
    if(_access(roWif,0x00)!=-1) {
      break;
    }
    
    roWif=roStr+"\\binfile\\"+roOrg;
    if(_access(roWif,0x00)!=-1) {
      break;
    }
    
    roWif=roStr+"\\flash\\"+roOrg;
    break;
  }
  return (_access(roWif,0x00)!=-1);
}

void head_string(char *origin,char *end,char *result)//
{
  int i;
  char *pend;
  pend=NULL;
  pend=strstr(origin,end);
  if(pend== NULL)
  {
    sprintf(result,origin);
  }
  else
  {
    if(pend-origin>1)
    {
      for(i=0;i<pend-origin;i++)
      {
        result[i]=origin[i];	
      }
      result[i]='\0';
    }
  }
}

void middle_string(char *origin,char *from,char *to,char *result)//
{
  int i;
  int ip;
  char *pstart;
  char *pend;
  
  pstart = strstr( origin, from );
  
  if(pstart == NULL)
  {
    return;
  }
  pend=strstr(origin,to);
  if(pend== NULL)
  {
    return;
  }
  if(pend-pstart>1)
  {
    for(i=0;i<pend-pstart-1;i++)
    {
      ip=pstart+i+1-origin;			
      result[i]=origin[ip];	
    }
    result[i]='\0';
  }
}

//从模块名称获得模块代号
int FindModule(CString &str,void *msppp)
{
  CMainFrame  *pMyFrm =(CMainFrame*)AfxGetApp()->m_pMainWnd;//取主框架窗口指针
  CBorerDoc  *pMyDoc=(CBorerDoc*) ((CBorerView*)msppp)->GetDocument();
  int nIndex=-1;
  
  return -1;
}

//从字符内容中解析出模块名称
bool GetModuleId(char *str,char *strId,int &nSum,void *msppp)
{
  CString strStr,strContent;
  strStr.Format("%s,",str);
  int nStart=0;
  int nFind=-1;
  nSum=0;
  
  nFind=strStr.Find(",");
  while(nFind>=0)
  {
    nFind=strStr.Find(",",nStart);
    if(nFind>=0)
    {	
      strContent=strStr.Mid(nStart,nFind-nStart);
      if(FindModule(strContent,msppp)>-1)
      {
        strId[nSum]=(char)FindModule(strContent,msppp);				
      }
      else
      {
        return false;
      }
      nStart=nFind+1;
      nSum++;
    }		
  }	
  return true;
}

//得到一区间的任意值
int RandomRange(int start,int end)
{
  if(end<start)
  {
    return start;
  }
  int n=rand();
  int  nResult=n%((end-start)+1) +start;
  return nResult;
}



//信息提示
void PcResetPDK(char *mmm,void *msppp)
{
  CString flFlash("flash.fls");
  if(strlen(mmm) >1)
  {
    if(Ravelout(theApp.m_sIniFile,flFlash))
    {
      if(CopyFile(mmm,flFlash,false))
      {
        VcTrace("拷贝文件成功!",msppp);
      }
      else
      {
        VcTrace("拷贝文件失败!",msppp);
      }
    }
  }
  EnumProcs(&CallbackEnum,(LPARAM)msppp);
  ShellExecute(NULL,"open",theApp.m_sAppPath+"PDK.EXE", NULL, NULL, SW_SHOWNORMAL);
}

//char showBuffer[1000];
//信息提示
void PcTrace(char *mmm,void *msppp)
{
  CMainFrame  *pMyFrm =(CMainFrame*)AfxGetApp()->m_pMainWnd;//取主框架窗口指针
  CBorerDoc  *pMyDoc=(CBorerDoc*) ((CBorerView*)msppp)->GetDocument();
  char *showBuffer=new char[strlen(mmm)+12];
  memset(showBuffer,0,strlen(mmm)+12);
  sprintf(showBuffer,"显示信息:%s",mmm);
  
  pMyFrm->m_editMcu[pMyDoc->m_nPortIndex]->PostMessage(MMM_SHOW_GETDATA,(WPARAM)showBuffer,MAKELPARAM(strlen(showBuffer),OUTTRACE));
  
  
}

//char showVCBuffer[1000];
void VcTrace(char *mmm,void *msppp)
{
  CMainFrame  *pMyFrm =(CMainFrame*)AfxGetApp()->m_pMainWnd;//取主框架窗口指针
  CBorerDoc  *pMyDoc=(CBorerDoc*) ((CBorerView*)msppp)->GetDocument();
  
  char *showVCBuffer=new char[strlen(mmm)+12];
  memset(showVCBuffer,0,strlen(mmm)+12);
  sprintf(showVCBuffer,"显示信息:%s",mmm);
  
  pMyFrm->m_editMcu[pMyDoc->m_nPortIndex]->PostMessage(MMM_SHOW_GETDATA,(WPARAM)showVCBuffer,MAKELPARAM(strlen(showVCBuffer),OUTTRACE));
  
  
}


//信息提示
int PcComSerial(void *msppp)
{
  int  mmm;
  
  CMainFrame  *pMyFrm =(CMainFrame*)AfxGetApp()->m_pMainWnd;//取主框架窗口指针
  
  int intCm = pMyFrm->m_PortList.GetNextItem(-1,LVNI_SELECTED);
  if(intCm<0)
  {
    return -1;
  }
  mmm = pMyFrm->m_aTestInfo[intCm]->m_nSendManner;
  return mmm ;
}


//从Trace中挖掘信息
int PcTraceInfo(void *msppp)
{
  int mmm;
  
  CMainFrame  *pMyFrm =(CMainFrame*)AfxGetApp()->m_pMainWnd;//取主框架窗口指针
  
  int intCm = pMyFrm->m_PortList.GetNextItem(-1,LVNI_SELECTED);
  if(intCm<0)
  {
    return -1;
  }
  
  char stemp[2];
  stemp[0] = pMyFrm->m_aTestInfo[intCm]->m_cFirstChar;
  stemp[1] = '@';
  mmm = atoi(stemp);
  
  return mmm;
} 

//向被测试的模块发送消息
BOOL PcSendMessage(char *str,int ntime,void *msppp)
{
  CMainFrame  *pMyFrm =(CMainFrame*)AfxGetApp()->m_pMainWnd;//取主框架窗口指针
  CBorerDoc  *pMyDoc=(CBorerDoc*) ((CBorerView*)msppp)->GetDocument();
  EM_MESSAGE msg;
  ((CBorerView*)msppp)->m_bDelMsg=true;
  //ZZZ	if(!StrToMsg(str,msg,msppp))
  //ZZZ	{
  //ZZZ		VcTrace("消息解析失败",msppp);
  //ZZZ		return false;
  //ZZZ	}
  
  if(pMyFrm->m_aTestInfo[pMyDoc->m_nPortIndex]->SendMessageToPort(msg,ntime,str))
  {
    return true;
  }
  else
  {
    return false;
  }
}

//向被测试的模块发送AT指令
BOOL PcSendAT(char *strAT,int ntime,void *msppp)
{
  CMainFrame  *pMyFrm =(CMainFrame*)AfxGetApp()->m_pMainWnd;//取主框架窗口指针
  CBorerDoc  *pMyDoc=(CBorerDoc*) ((CBorerView*)msppp)->GetDocument();
  
  if(pMyFrm->m_aTestInfo[pMyDoc->m_nPortIndex]->SendAT(strAT,ntime))
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

//测试任务开始
BOOL PcBegin(char *mmm,void *msppp)
{
  char strId[30];
  int num;
  char strshow[1000];
  CMainFrame  *pMyFrm =(CMainFrame*)AfxGetApp()->m_pMainWnd;//取主框架窗口指针
  CBorerDoc  *pMyDoc=(CBorerDoc*) ((CBorerView*)msppp)->GetDocument();
  sprintf(strshow,"ITExBegin(\"%s\")",mmm);
  if(!GetModuleId(mmm,strId,num,msppp))
  {
    sprintf(strshow,"模块%s解析失败",mmm);
    VcTrace(strshow,msppp);
    return false;
  }
  if(pMyFrm->m_aTestInfo[pMyDoc->m_nPortIndex]->TxBegin(strId,num,strshow)==ERROR_SUCCESS)
  {
    return true;
  }
  else
  {
    return false;
  }
}

//测试任务结束
BOOL PcEnd(void *msppp)
{
  CMainFrame  *pMyFrm =(CMainFrame*)AfxGetApp()->m_pMainWnd;//取主框架窗口指针
  CBorerDoc  *pMyDoc=(CBorerDoc*) ((CBorerView*)msppp)->GetDocument();
  if(pMyFrm->m_aTestInfo[pMyDoc->m_nPortIndex]->TxEnd()==ERROR_SUCCESS)
  {
    return true;
  }
  else
  {
    return false;
  }
}

//模块调试信息显示
BOOL PcModuleTrace(char *sModule,int nKind,void *sapp)
{
  char strId[30];
  char strshow[1000];
  int num;
  CMainFrame  *pMyFrm =(CMainFrame*)AfxGetApp()->m_pMainWnd;//取主框架窗口指针
  CBorerDoc  *pMyDoc=(CBorerDoc*) ((CBorerView*)sapp)->GetDocument();
  
  if(!GetModuleId(sModule,strId,num,sapp))
  {
    sprintf(strshow,"模块%s解析失败",sModule);
    VcTrace(strshow,sapp);
    return false;
  }
  sprintf(strshow,"ITExModuleTrace(\"%s\")",sModule);
  if(pMyFrm->m_aTestInfo[pMyDoc->m_nPortIndex]->TxTrace(strId,num,nKind,strshow)==ERROR_SUCCESS)
  {
    return true;
  }
  else
  {
    return false;
  }
}

//显示信息
void PcDisplay(char *msg)
{
  AfxMessageBox(msg);
}

extern "C" {
  extern char g_strErrorInfo[255] ;
  void dodefine(char *);
  
  void EiC_init_EiC(void);
  int  EiC_insertpath(char *);
  int  EiC_Resolve_file(char *e, char *nnn,  int mode);
  
  int  EiC_run(int argc, char **argv);
  int  EiC_settrace(int  ttTrace);
  
  void EiC_setMessageDisplay(void (*)(char *));
  void EiC_setDbgBreak(void (*)(void*),void *ppp);
  void EiC_setUiSynch(void (*)(char *,int,int,void*),void *ppp);
  
  void EiC_setCurrentTime(BOOL (*)(char *,void*),void *ppp);	
  void EiC_setTimeSpan(BOOL (*)(char *,char *,char *,void*),void *ppp);
  
  void EiC_setATCom(BOOL (*)(char *,int,void*),void *ppp);
  void EiC_setPPP(BOOL (*)(char *,int,void*),void *ppp);	
  void EiC_setsay(BOOL (*)(char *,int,void*),void *ppp);
  void EiC_sethear(BOOL (*)(char *,int,void*),void *ppp);
  void EiC_setWaitContent(BOOL (*)(char *,char *,int *,int,void*),void *ppp);
  void EiC_setlaunch(BOOL (*)(char *,void*),void *ppp);
  void EiC_setlstop(BOOL (*)(void*),void *ppp);
  void EiC_getComSerial(int (*)(void*),void *ppp);
  void EiC_getTraceInfo(int (*)(void*),void *ppp);
  void EiC_setDbgTrace(void (*)(char *,void*),void *ppp);
  void EiC_setResetPDK(void (*)(char *,void*),void *ppp);
  void EiC_setGetvar(BOOL (*)(char *nnn,void(*)(char*),
    int sss,int eee,char *STR,int nKind,int nTime,void *elpPara),void*ppp);
  void EiC_setSetvar(BOOL (*)(char *nnn,int sss,int eee,char *STR,int nKind,void *elpPara),void*ppp);
  
  void EiC_sethot(BOOL (*)(char*,int,void*),void *ppp);
  void EiC_setsleep(int (*)(int,void*),void *ppp);
  void EiC_setstop(int (*)(int,void*),void *ppp);
  void EiC_setfile(char *(*)(void*),void *ppp);
  
  void EiCp_setResetStart(void);
  void EiCp_ResetStart(void);
  
  void module_stdio(void);
  void module_stdlib(void);
  void module_string(void);
  extern __declspec( thread ) int *EiC_brake;
  
}


#define str(x)  #x
#define xstr(x) str(x)

BOOL AFXAPI AfxFullPath(LPTSTR lpszPathOut, LPCTSTR lpszFileIn);
#define modestWAIT	while(!*EiC_brake) { \
  if(WaitForSingleObject(((CBorerView*)msppp)->Inr_hStepOver,1024)==WAIT_OBJECT_0) { \
  break;   \
  } \
}

#define modest2WAIT	while(!*EiC_brake) {\
  rev =WaitForSingleObject(((CBorerView*)msppp)->m_hGetWaitMsgEvent,1024);\
  if(rev==WAIT_OBJECT_0) {\
  break;\
  }\
  \
  npwmTime-=1024;\
  if(npwmTime<0) {\
  break;   \
  }\
}

//等待消息
BOOL PcWaitMessage(char *str,int npwmTime,void *msppp)
{
  CMainFrame  *pMyFrm =(CMainFrame*)AfxGetApp()->m_pMainWnd;//取主框架窗口指针
  CBorerDoc  *pMyDoc=(CBorerDoc*) ((CBorerView*)msppp)->GetDocument();
  ((CBorerView*)msppp)->m_bWaitMsg=false; 
  ((CBorerView*)msppp)->m_aWaitMsg.RemoveAll();
  DWORD rev;
  
  CString strMsg,strMsgSingle;
  int nStart=0;
  strMsg.Format("%s",str);
  int	nFind=strMsg.Find(";");
  while(nFind>=0)
  {
    nFind=strMsg.Find(";",nStart);
    if(nFind>=0)
    {	
      strMsgSingle=strMsg.Left(nFind);
      strMsg.Delete(0,nFind+1);
      
      nStart=nFind+1;
    }
  }
  
  if(strMsg.GetLength()>0)
  {
    ResetEvent( ((CBorerView*)msppp)->m_hGetWaitMsgEvent );
  }
  
  char strshow[1000];
  if(((CBorerView*)msppp)->m_aWaitMsg.GetSize()>0)
  {
    ((CBorerView*)msppp)->m_bWaitMsg=true; 
     modest2WAIT;
    if(WAIT_OBJECT_0 == rev)
    {
      ((CBorerView*)msppp)->m_bWaitMsg=false;
      sprintf(strshow,"等待消息%s成功",str);
      VcTrace(strshow,msppp);
    }
    else
    {
      //ZZZ			for(int k=0;k<((CBorerView*)msppp)->m_aWaitMsg.GetSize();k++)
      //ZZZ			{
      //ZZZ				if(CompareMsgArray(((CBorerView*)msppp)->m_aWaitMsg[k],((CBorerView*)msppp)->m_arrReceiveMsg))
      //ZZZ				{
      //ZZZ					sprintf(strshow,"等待消息%s成功",str);
      
      //ZZZ				VcTrace(strshow,msppp);
      //ZZZ			return true;					
      //ZZZ		}
      //ZZZ		}
      
      ((CBorerView*)msppp)->m_bWaitMsg=false;
      sprintf(strshow,"等待%s超时,没有得到等待消息",str);
      VcTrace(strshow,msppp);
      return false;
    }
  }
  return true;	
}

//获取当前时间
BOOL PcCurrentTime(char *sTime,void *msppp)
{
  CTime t=CTime::GetCurrentTime();
  CString strTime(t.Format("%Y-%m-%d-%H-%M-%S"));
  memcpy(sTime,strTime.GetBuffer(strTime.GetLength()),strTime.GetLength());
  strTime.ReleaseBuffer();
  sTime[strTime.GetLength()]=0x00;
  return true;				
}

BOOL PcTimeSpan(char *sTimeStart,char *sTimeEnd,char *sTimeSpan,void *msppp)
{
  CString strTime;
  strTime.Format("%s",sTimeStart);
  if(strTime.GetLength()<14)
  {
    return -1;
  }
  
  CTime timeStart(atoi(strTime.Mid(0,4)), atoi(strTime.Mid(5,2)), atoi(strTime.Mid(8,2)), atoi(strTime.Mid(11,2)), atoi(strTime.Mid(14,2)), atoi(strTime.Mid(17,2)) ); 
  strTime.Format("%s",sTimeEnd);
  if(strTime.GetLength()<14)
  {
    return -1;
  }
  CTime timeEnd(atoi(strTime.Mid(0,4)), atoi(strTime.Mid(5,2)), atoi(strTime.Mid(8,2)), atoi(strTime.Mid(11,2)), atoi(strTime.Mid(14,2)), atoi(strTime.Mid(17,2)) ); 
  
  CTimeSpan ts = timeEnd - timeStart;  
  
  strTime.Format("%d-days %d-hours %d-minutes %d-seconds",ts.GetDays(),ts.GetHours(),ts.GetMinutes(),ts.GetSeconds());
  
  memcpy(sTimeSpan,strTime.GetBuffer(strTime.GetLength()),strTime.GetLength());
  
  
  return true;				
}


//等待消息内容和消息长度
BOOL PcWaitMessageContent(char *sMessage,char *sContent,int* nConLength,int npwmTime,void *msppp)
{
  
  CMainFrame  *pMyFrm =(CMainFrame*)AfxGetApp()->m_pMainWnd;//取主框架窗口指针
  CBorerDoc  *pMyDoc=(CBorerDoc*) ((CBorerView*)msppp)->GetDocument();
  ((CBorerView*)msppp)->m_aWaitMsg.RemoveAll();
  DWORD rev;
  
  CString strMsg,strMsgSingle;
  int nStart=0;
  strMsg.Format("%s",sMessage);
  int	nFind=strMsg.Find(";");
  while(nFind>=0)
  {
    nFind=strMsg.Find(";",nStart);
    if(nFind>=0)
    {	
      strMsgSingle=strMsg.Left(nFind);
      strMsg.Delete(0,nFind+1);
      
      nStart=nFind+1;
    }
  }
  
  char strshow[1000];
  if(((CBorerView*)msppp)->m_aWaitMsg.GetSize()>0)
  {
    //	((CBorerView*)msppp)->m_waitMsg=msg;
    //	((CBorerView*)msppp)->m_aWaitMsg.Add(msg);
    ((CBorerView*)msppp)->m_bWaitMsg=true;
    
    //进行消息比较，
    //如果有一消息一致，触发得到消息事件，否则继续等待到超时
    ResetEvent( ((CBorerView*)msppp)->m_hGetWaitMsgEvent );
    
    modest2WAIT;
    
    if(WAIT_OBJECT_0 == rev)
    {
      ((CBorerView*)msppp)->m_bWaitMsg=false;
      
      nConLength[0]=((CBorerView*)msppp)->m_waitedMsg.length;
      memcpy(sContent,((CBorerView*)msppp)->m_waitedMsg.Union.content,nConLength[0]);
      /*
      for(int k=0;k<((CBorerView*)msppp)->m_aWaitMsg.GetSize();k++)
      {
      if(CompareMsg(((CBorerView*)msppp)->m_aWaitMsg[k],((CBorerView*)msppp)->m_waitedMsg))
      {
      return true;					
      }
      }
      
        if(k ==((CBorerView*)msppp)->m_aWaitMsg.GetSize())
        {
        sprintf(strshow,"等待消息%s失败,没有得到等待消息",sMessage);
        PcTrace(strshow,msppp);
        return false;
        }
      else   */
      {
        sprintf(strshow,"等待消息%s成功",sMessage);
        VcTrace(strshow,msppp);
      }
      
    }
    else
    {	
      ((CBorerView*)msppp)->m_bWaitMsg=false;
      sprintf(strshow,"等待%s超时,没有得到等待消息",sMessage);
      VcTrace(strshow,msppp);
      return false;
    }
  }
  
  return true;	
  
}

//导入函数库
void stdClib(void)
{
  module_stdio();
  module_stdlib();
  module_string();
}

int PcStop(int nms,void *sapp)
{
  ((CBorerView*)sapp)->m_nStopflag=0x01;
  return 0;
}

char *PcFile(void *sapp)
{
  ((CBorerView*)sapp)->Inr_filePC.ReleaseBuffer();
  ((CBorerView*)sapp)->Inr_filePC=((CBorerView*)sapp)->GetDocument()->GetPathName();
  return ((CBorerView*)sapp)->Inr_filePC.GetBuffer(((CBorerView*)sapp)->Inr_filePC.GetLength());
}


//睡眠时间
int PcSleep(int nms,void *sapp)
{
  while(nms>0) { 
    if(((CBorerView*)sapp)->m_nStopflag) {
      break;
    }
    
    Sleep(min(256,nms));
    nms-=256;
  }
  return nms;
}


//找文件名称，行号
void fnSynch(char *msggg,int mslll,int msrrr,void *msppp)
{
  AfxFullPath(((CBorerView*)msppp)->Inr_fileGL.GetBuffer(_MAX_PATH),msggg);
  ((CBorerView*)msppp)->Inr_fileGL.ReleaseBuffer();	
  
  if(_access(((CBorerView*)msppp)->Inr_fileGL,0x00) ==-1) {
    if(EiC_Resolve_file(msggg,((CBorerView*)msppp)->Inr_fileGL.GetBuffer(_MAX_PATH),0)<0) {
      ((CBorerView*)msppp)->Inr_fileGL.ReleaseBuffer();
      return;
    }
    ((CBorerView*)msppp)->Inr_fileGL.ReleaseBuffer();	   
  }
  
  if(_access(((CBorerView*)msppp)->Inr_fileGL,0x00) ==-1) {
    return;
  }
  
  ((CBorerView*)msppp)->PostMessage(WM_COMMAND,MMM_LOAD_FILE,NULL);
}

//封装函数
void fnSynch(CString &msggg,int mslll,int msrrr,void *msppp)
{
  fnSynch(msggg.GetBuffer(msggg.GetLength()),mslll,msrrr,msppp);
  msggg.ReleaseBuffer();
}

//对应用程序来说，执行指令的位置（文件、行号）变化时、脚本中调用ITBreak,
//可能会导致界面同步。mySynch处理执行指令的位置变化。PcBreak处理ITBreak。////
//。
void mySynch(char *msggg,int mslll,int msrrr,void *msppp)
{
  ((CBorerView*)msppp)->Inr_glLine = mslll-1;
  ((CBorerView*)msppp)->Inr_fileGL = msggg;
  ((CBorerView*)msppp)->Trk_callDepth =msrrr;
  
  if(((CBorerView*)msppp)->m_nMenuType ==Y_STEPOVER)
  {
    if(((CBorerView*)msppp)->Snap_callDepth < ((CBorerView*)msppp)->Trk_callDepth) {
      return;
    }
  }else if(((CBorerView*)msppp)->m_nMenuType ==Y_STEPOUT)
  {
    if(((CBorerView*)msppp)->Snap_callDepth ==((CBorerView*)msppp)->Trk_callDepth) {
      return;
    }
  }
  
  fnSynch(msggg,mslll,msrrr,msppp);
  
  if(((CBorerView*)msppp)->m_nMenuType ==Y_STEPINTO) {
    modestWAIT;
    ResetEvent(((CBorerView*)msppp)->Inr_hStepOver);
  }else if(((CBorerView*)msppp)->m_nMenuType ==Y_STEPOVER) {
    if(((CBorerView*)msppp)->Snap_callDepth ==((CBorerView*)msppp)->Trk_callDepth) {
      modestWAIT;
      ResetEvent(((CBorerView*)msppp)->Inr_hStepOver);
    }
  }else if(((CBorerView*)msppp)->m_nMenuType ==Y_STEPOUT) {
    if(((CBorerView*)msppp)->Snap_callDepth >((CBorerView*)msppp)->Trk_callDepth) {
      modestWAIT;
      ResetEvent(((CBorerView*)msppp)->Inr_hStepOver);
    }
  }
}


//断点处理
void PcBreak(void *msppp)
{	
  if(((CBorerView*)msppp)->m_nMenuType == Y_GO) 
  {
    modestWAIT;
    ResetEvent(((CBorerView*)msppp)->Inr_hStepOver);
  }
  else if((((CBorerView*)msppp)->m_nMenuType == Y_STEPOVER) ||
    (((CBorerView*)msppp)->m_nMenuType == Y_STEPOUT))
  {
    fnSynch(((CBorerView*)msppp)->Inr_fileGL,((CBorerView*)msppp)->Inr_glLine,((CBorerView*)msppp)->Trk_callDepth,msppp);
    ((CBorerView*)msppp)->m_nMenuType =Y_GO;
    
    modestWAIT;
    ResetEvent(((CBorerView*)msppp)->Inr_hStepOver);
  }
}

//关联函数,建立起工程函数和脚本文件中命令之间的关系
void ConFunction(void *msppp)
{
  EiC_setMessageDisplay(PcDisplay);
  EiC_setDbgBreak(PcBreak,msppp);
  EiC_setsay(PcSendMessage,msppp);
  EiC_setATCom(PcSendAT,msppp);
  EiC_setCurrentTime(PcCurrentTime,msppp);
  EiC_setTimeSpan(PcTimeSpan,msppp);
  EiC_sethear(PcWaitMessage,msppp);
  EiC_setWaitContent(PcWaitMessageContent,msppp);
  EiC_setlaunch(PcBegin,msppp);
  EiC_setlstop(PcEnd,msppp);
  
  EiC_getTraceInfo(PcTraceInfo,msppp);
  EiC_getComSerial(PcComSerial,msppp);
  EiC_setDbgTrace(PcTrace,msppp);
  EiC_setResetPDK(PcResetPDK,msppp);
  
  EiC_sethot(PcModuleTrace,msppp);
  EiC_setsleep(PcSleep,msppp);
  EiC_setstop(PcStop,msppp);
  EiC_setfile(PcFile,msppp);
}

//关联函数,建立起工程函数和EIC中命令之间的关系
void ConFunction2(void *msppp)
{
  EiC_setUiSynch(mySynch,msppp);	
}

int inline HELP_insertpath(CString &ppp)
{
  int hipRet =EiC_insertpath(ppp.GetBuffer(ppp.GetLength()));
  ppp.ReleaseBuffer();
  return hipRet;
}

#define C2RTF(strcc) 	 strcc.Replace(".c",".rtf"); \
  strcc.Replace(".h",".rtf"); \
  strcc.Replace(".cpp",".rtf");

//运行脚本测试
UINT AFX_CDECL ProcRunChorus(LPVOID lpScout)
{
  CMainFrame  *pMyFrm =(CMainFrame*)AfxGetApp()->m_pMainWnd;//取主框架窗口指针
  CBorerView *prcView =(CBorerView*)lpScout;
  
  char     *argvCC[1];
  CString   argvChorus;
  WDIINFO  *logChorus;
  BOOL     bRunScriptError = FALSE;
  
  union { int i; char c[4]; } u;
  
  /* initiate EiC */
  EiC_init_EiC();
  
  //  prcView->m_nStopflag =0x01;
  EiC_brake =&prcView->m_nStopflag;
  
  /* add in the standard C library */
  stdClib();
  
  dodefine("_EiC");
  dodefine(&(xstr(PLATFORM)[1]));
  
  u.i = 1;
  if (u.c[0] == 1) {
    dodefine("__LITTLE_ENDIAN__=1");
  } else {
    dodefine("__LITTLE_ENDIAN__=0");
  }
  
  if (sizeof (void *) == 8) {
    dodefine("__LP64__=1");
  } else {
    dodefine("__ILP32__=1");
  }
  
  if(_access(prcView->GetDocument()->m_strHeadPath,0x00) !=-1)
  {
    HELP_insertpath(prcView->GetDocument()->m_strHeadPath);
  }
  
  HELP_insertpath(theApp.m_sAppPath);
  
  /* you can also set the function used to display EiC's error and warning
  messages */
  ConFunction(prcView);
  ConFunction2(prcView);
  
  EiCp_setResetStart();
  EiC_settrace(prcView->m_nMenuType!=Y_RUN);
  
  while(pMyFrm->m_treeProject.m_qary.GetSize()) 
  {
    logChorus = new WDIINFO;
    bRunScriptError = FALSE;
    
    argvChorus =pMyFrm->m_treeProject.m_qary.GetAt(0);
    if(_access(argvChorus,0x00) ==-1) 
    {
      pMyFrm->m_treeProject.m_qary.RemoveAt(0);
      continue;
    }
    
    argvChorus.SetAt(argvChorus.GetLength() - prcView->GetDocument()->GetTitle().GetLength(),0x00);
    HELP_insertpath(argvChorus);
    
    argvChorus = pMyFrm->m_treeProject.m_qary.GetAt(0);
    fnSynch(argvChorus,-1,0,prcView);
    Sleep(1024);
    
    argvChorus.Replace("\\","/");
    argvCC[0] = argvChorus.GetBuffer(argvChorus.GetLength());
    
    int nReturnFlag = 0 ;
    for(int j=0;j<3;j++)
    {
      //			EiCp_ResetStart();

      nReturnFlag = EiC_run(1, argvCC) ;
      if( nReturnFlag == 0 )
      {
        //语法错误
        VcTrace(g_strErrorInfo,prcView);
        bRunScriptError = TRUE;
        break;
      }
      
      if(prcView->m_nStopflag == 0 )
      {
        //运行正确
        bRunScriptError = FALSE;
        break;
      }
      
    }
    
    argvChorus.ReleaseBuffer();
    
    EiCp_ResetStart();
    pMyFrm->m_treeProject.m_qary.RemoveAt(0);
    
    if((prcView->m_nStopflag) || bRunScriptError)
    {
      logChorus->wdiResult =prcView->MT_log+"\\Failed_"+argvChorus.Right(argvChorus.GetLength()-argvChorus.ReverseFind('/')-1);
    }
    else
    {
      logChorus->wdiResult =prcView->MT_log+"\\Passed_"+argvChorus.Right(argvChorus.GetLength()-argvChorus.ReverseFind('/')-1);
    }
    
    C2RTF(logChorus->wdiResult);
    logChorus->wdiScript=argvChorus;
    
    logChorus->wdiModule=pMyFrm->m_treeProject.m_qmod;
    logChorus->wdiDate=prcView->MT_date;
    
    logChorus->wdiOperator=prcView->MT_aid;
    logChorus->wdiVersion=prcView->MT_leaf;
    
    
    CStdioFile fFile;
    CString sTempBuf;
    
    if (!fFile.Open(argvChorus,CFile::modeRead | CFile::typeText))
    {
      ASSERT("Could not open file");
      return ERROR_FILE_NOT_FOUND;
    }
    fFile.ReadString(sTempBuf);
    
    int nTemp = sTempBuf.Find("测试项") ;
    if(nTemp ==-1)
    {
      sTempBuf="";
    }
    else
    {
      sTempBuf = sTempBuf.Mid(nTemp + 8);
    }
    
    logChorus->wdiItem = sTempBuf ;
    fFile.Close();
    
    prcView->PostMessage(MMM_WD_TRACK,(WPARAM)0,(LPARAM)logChorus);
    prcView->m_nStopflag=0x00;
    break;
  }
  
  return NO_ERROR;
}

//运行脚本测试
UINT AFX_CDECL ProcRunSolo(LPVOID context)
{
  CMainFrame  *pMyFrm =(CMainFrame*)AfxGetApp()->m_pMainWnd;//取主框架窗口指针
  CBorerView *pView =(CBorerView*)context;
  CBorerDoc  *pMyDoc = pView->GetDocument();
  char    *argvv[1];
  CString  *argv0 = new CString;
  
  if(!pMyDoc->GetPathName().GetLength()) {
    return NO_ERROR;
  }
  
  int nLineCount = pView->GetLineCount();
  CPoint ptCursorPos;
  ptCursorPos.x = pView->GetLineLength(nLineCount - 1);
  ptCursorPos.y = nLineCount - 1;
  CString in_textString;
  CString out_textString;
  pView->GetText(CPoint(0, 0),ptCursorPos,in_textString);
  
  // Reset CINT
  G__scratch_all();
  pView->g_sCintLastError = "";
  pView->OnClearAllSyntaxErrors();  

  // Must add to get proper line number
  in_textString = "#line 0\r\n" + in_textString;
  // Hook stdio output
  CHookStdio hs( STD_OUTPUT_HANDLE, 64 * 1024 );
  
  // Set error callback function
  G__set_errmsgcallback( &pView->CintError );
  
  // Execute the program
  if ( !G__int( G__exec_text( (LPCTSTR)in_textString ) ) )
  {
    // Set error marker to proper line
    int nErrLine = G__lasterror_linenum();
    pView->OnToggleSyntaxError(nErrLine - 1);
    char outbuf[300];
    sprintf(outbuf,"Line: %d , Error: %s",nErrLine,pView->g_sCintLastError.c_str());
    VcTrace(outbuf,pView);
    return ERROR;
  } // end if
  
  // Get output
  char buf[ 64 * 1024 ] = "";
  buf[ hs.Read( buf, sizeof( buf ) - 1 ) ] = 0;
  
  pMyFrm->m_editMcu[pMyDoc->m_nPortIndex]->PostMessage(MMM_SHOW_GETDATA,(WPARAM)buf,MAKELPARAM(strlen(buf),OUTTRACE));

  pView->m_nStopflag =0x00;
  EiC_brake =&pView->m_nStopflag;
  
  
  if(_access(pView->GetDocument()->m_strHeadPath,0x00) !=-1)
  {
    HELP_insertpath(pView->GetDocument()->m_strHeadPath);
  }
  
  *argv0 =pView->GetDocument()->GetPathName();
  argv0->SetAt(argv0->GetLength() - pView->GetDocument()->GetTitle().GetLength(),0x00);
  HELP_insertpath(*argv0);
  
  HELP_insertpath(theApp.m_sAppPath);
  
  *argv0 =pView->GetDocument()->GetPathName();
  argv0->Replace("\\","/");
  argvv[0]=argv0->GetBuffer(argv0->GetLength());
  
  EiC_settrace(pView->m_nMenuType != Y_RUN);
  
  argv0->ReleaseBuffer();
  
  pView->PostMessage(MMM_SOLOWINDUP,(WPARAM)argv0,pView->m_nStopflag);
  
  return NO_ERROR;
}

//******************
//Source
//******************
#include <vdmdbg.h>

typedef struct
{
  DWORD   dwID ;
  DWORD   dwThread ;
} TERMINFO ;

// Declare Callback Enum Functions.
BOOL CALLBACK TerminateAppEnum( HWND hwnd, LPARAM lParam ) ;

BOOL CALLBACK Terminate16AppEnum( HWND hwnd, LPARAM lParam ) ;

/*----------------------------------------------------------------
DWORD WINAPI TerminateApp( DWORD dwPID, DWORD dwTimeout )

    Purpose:
    Shut down a 32-Bit Process (or 16-bit process under Windows 95)

    Parameters:
    dwPID
    Process ID of the process to shut down.

    dwTimeout
    Wait time in milliseconds before shutting down the process.

    Return Value:
    TA_FAILED - If the shutdown failed.
    TA_SUCCESS_CLEAN - If the process was shutdown using WM_CLOSE.
    TA_SUCCESS_KILL - if the process was shut down with
    TerminateProcess().
    NOTE:  See header for these defines.
----------------------------------------------------------------*/ 
DWORD WINAPI TerminateExe( DWORD dwPID, DWORD dwTimeout )
{
  HANDLE   hProc ;
  DWORD   dwRet ;
  
  // If we can't open the process with PROCESS_TERMINATE rights,
  // then we give up immediately.
  hProc = OpenProcess(SYNCHRONIZE|PROCESS_TERMINATE, FALSE,
    dwPID);
  
  if(hProc == NULL)
  {
    return TA_FAILED ;
  }
  
  // TerminateAppEnum() posts WM_CLOSE to all windows whose PID
  // matches your process's.
  EnumWindows((WNDENUMPROC)TerminateAppEnum, (LPARAM) dwPID) ;
  
  // Wait on the handle. If it signals, great. If it times out,
  // then you kill it.
  if(WaitForSingleObject(hProc, dwTimeout)!=WAIT_OBJECT_0)
    dwRet=(TerminateProcess(hProc,0)?TA_SUCCESS_KILL:TA_FAILED);
  else
    dwRet = TA_SUCCESS_CLEAN ;
  
  CloseHandle(hProc) ;
  
  return dwRet ;
}

/*----------------------------------------------------------------
DWORD WINAPI Terminate16App( DWORD dwPID, DWORD dwThread,
WORD w16Task, DWORD dwTimeout )

  Purpose:
  Shut down a Win16 APP.
  
    Parameters:
    dwPID
    Process ID of the NTVDM in which the 16-bit application is
    running.
    
      dwThread
      Thread ID of the thread of execution for the 16-bit
      application.
      
        w16Task
        16-bit task handle for the application.
        
          dwTimeout
          Wait time in milliseconds before shutting down the task.
          
            Return Value:
            If successful, returns TA_SUCCESS_16
            If unsuccessful, returns TA_FAILED.
            NOTE:  These values are defined in the header for this
            function.
            
              NOTE:
              You can get the Win16 task and thread ID through the
              VDMEnumTaskWOW() or the VDMEnumTaskWOWEx() functions.
----------------------------------------------------------------*/ 
DWORD WINAPI Terminate16App( DWORD dwPID, DWORD dwThread,
                            WORD w16Task, DWORD dwTimeout )
{
  HINSTANCE      hInstLib ;
  TERMINFO      info ;
  
  // You will be calling the functions through explicit linking
  // so that this code will be binary compatible across
  // Win32 platforms.
  BOOL (WINAPI *lpfVDMTerminateTaskWOW)(DWORD dwProcessId,
    WORD htask) ;
  
  hInstLib = LoadLibraryA( "VDMDBG.DLL" ) ;
  if( hInstLib == NULL )
    return TA_FAILED ;
  
  // Get procedure addresses.
  lpfVDMTerminateTaskWOW = (BOOL (WINAPI *)(DWORD, WORD ))
    GetProcAddress( hInstLib, "VDMTerminateTaskWOW" ) ;
  
  if( lpfVDMTerminateTaskWOW == NULL )
  {
    FreeLibrary( hInstLib ) ;
    return TA_FAILED ;
  }
  
  // Post a WM_CLOSE to all windows that match the ID and the
  // thread.
  info.dwID = dwPID ;
  info.dwThread = dwThread ;
  EnumWindows((WNDENUMPROC)Terminate16AppEnum, (LPARAM) &info) ;
  
  // Wait.
  Sleep( dwTimeout ) ;
  
  // Then terminate.
  lpfVDMTerminateTaskWOW(dwPID, w16Task) ;
  
  FreeLibrary( hInstLib ) ;
  return TA_SUCCESS_16 ;
}

BOOL CALLBACK TerminateAppEnum( HWND hwnd, LPARAM lParam )
{
  DWORD dwID ;
  
  GetWindowThreadProcessId(hwnd, &dwID) ;
  
  if(dwID == (DWORD)lParam)
  {
    PostMessage(hwnd, WM_CLOSE, 0, 0) ;
  }
  
  return TRUE ;
}

BOOL CALLBACK Terminate16AppEnum( HWND hwnd, LPARAM lParam )
{
  DWORD      dwID ;
  DWORD      dwThread ;
  TERMINFO   *termInfo ;
  
  termInfo = (TERMINFO *)lParam ;
  
  dwThread = GetWindowThreadProcessId(hwnd, &dwID) ;
  
  if(dwID == termInfo->dwID && termInfo->dwThread == dwThread )
  {
    PostMessage(hwnd, WM_CLOSE, 0, 0) ;
  }
  
  return TRUE ;
} 

/*********************
EnumProc.c (or .cpp)
*********************/ 
#include <tlhelp32.h>
#include <vdmdbg.h>

typedef struct
{
  DWORD          dwPID ;
  PROCENUMPROC   lpProc ;
  DWORD          lParam ;
  BOOL           bEnd ;
} EnumInfoStruct ;

BOOL WINAPI Enum16( DWORD dwThreadId, WORD hMod16, WORD hTask16,
                   PSZ pszModName, PSZ pszFileName, LPARAM lpUserDefined ) ;

BOOL CALLBACK CallbackEnum(DWORD l1, WORD l2, LPSTR l3, LPARAM l4)
{
  CString l5 =l3;
  l5.MakeUpper();
  
  if(l5.Find("PDK.EXE")!=-1) {
    TerminateExe(l1,2048);
  }
  return 1;
}

// The EnumProcs function takes a pointer to a callback function
// that will be called once per process in the system providing
// process EXE file name and process ID.
// Callback function definition:
// BOOL CALLBACK Proc( DWORD dw, LPCSTR lpstr, LPARAM lParam ) ;
// 
// lpProc -- Address of callback routine.
// 
// lParam -- A user-defined LPARAM value to be passed to
//           the callback routine.
BOOL WINAPI EnumProcs( PROCENUMPROC lpProc, LPARAM lParam )
{
  OSVERSIONINFO  osver ;
  HINSTANCE      hInstLib ;
  HINSTANCE      hInstLib2 ;
  HANDLE         hSnapShot ;
  PROCESSENTRY32 procentry ;
  BOOL           bFlag ;
  LPDWORD        lpdwPIDs ;
  DWORD          dwSize, dwSize2, dwIndex ;
  HMODULE        hMod ;
  HANDLE         hProcess ;
  char           szFileName[ MAX_PATH ] ;
  EnumInfoStruct sInfo ;
  
  // ToolHelp Function Pointers.
  HANDLE (WINAPI *lpfCreateToolhelp32Snapshot)(DWORD,DWORD) ;
  BOOL (WINAPI *lpfProcess32First)(HANDLE,LPPROCESSENTRY32) ;
  BOOL (WINAPI *lpfProcess32Next)(HANDLE,LPPROCESSENTRY32) ;
  
  // PSAPI Function Pointers.
  BOOL (WINAPI *lpfEnumProcesses)( DWORD *, DWORD cb, DWORD * );
  BOOL (WINAPI *lpfEnumProcessModules)( HANDLE, HMODULE *,
    DWORD, LPDWORD );
  DWORD (WINAPI *lpfGetModuleFileNameEx)( HANDLE, HMODULE,
    LPTSTR, DWORD );
  
  // VDMDBG Function Pointers.
  INT (WINAPI *lpfVDMEnumTaskWOWEx)( DWORD,
    TASKENUMPROCEX  fp, LPARAM );
  
  
  // Check to see if were running under Windows95 or
  // Windows NT.
  osver.dwOSVersionInfoSize = sizeof( osver ) ;
  if( !GetVersionEx( &osver ) )
  {
    return FALSE ;
  }
  
  // If Windows NT:
  if( osver.dwPlatformId == VER_PLATFORM_WIN32_NT )
  {
    
    // Load library and get the procedures explicitly. We do
    // this so that we don't have to worry about modules using
    // this code failing to load under Windows 95, because
    // it can't resolve references to the PSAPI.DLL.
    hInstLib = LoadLibraryA( "PSAPI.DLL" ) ;
    if( hInstLib == NULL )
      return FALSE ;
    
    hInstLib2 = LoadLibraryA( "VDMDBG.DLL" ) ;
    if( hInstLib2 == NULL )
      return FALSE ;
    
    // Get procedure addresses.
    lpfEnumProcesses = (BOOL(WINAPI *)(DWORD *,DWORD,DWORD*))
      GetProcAddress( hInstLib, "EnumProcesses" ) ;
    lpfEnumProcessModules = (BOOL(WINAPI *)(HANDLE, HMODULE *,
      DWORD, LPDWORD)) GetProcAddress( hInstLib,
      "EnumProcessModules" ) ;
    lpfGetModuleFileNameEx =(DWORD (WINAPI *)(HANDLE, HMODULE,
      LPTSTR, DWORD )) GetProcAddress( hInstLib,
      "GetModuleFileNameExA" ) ;
    lpfVDMEnumTaskWOWEx =(INT(WINAPI *)( DWORD, TASKENUMPROCEX,
      LPARAM))GetProcAddress( hInstLib2, "VDMEnumTaskWOWEx" );
    if( lpfEnumProcesses == NULL ||
      lpfEnumProcessModules == NULL ||
      lpfGetModuleFileNameEx == NULL ||
      lpfVDMEnumTaskWOWEx == NULL)
    {
      FreeLibrary( hInstLib ) ;
      FreeLibrary( hInstLib2 ) ;
      return FALSE ;
    }
    
    // Call the PSAPI function EnumProcesses to get all of the
    // ProcID's currently in the system.
    // NOTE: In the documentation, the third parameter of
    // EnumProcesses is named cbNeeded, which implies that you
    // can call the function once to find out how much space to
    // allocate for a buffer and again to fill the buffer.
    // This is not the case. The cbNeeded parameter returns
    // the number of PIDs returned, so if your buffer size is
    // zero cbNeeded returns zero.
    // NOTE: The "HeapAlloc" loop here ensures that we
    // actually allocate a buffer large enough for all the
    // PIDs in the system.
    dwSize2 = 256 * sizeof( DWORD ) ;
    lpdwPIDs = NULL ;
    do
    {
      if( lpdwPIDs )
      {
        HeapFree( GetProcessHeap(), 0, lpdwPIDs ) ;
        dwSize2 *= 2 ;
      }
      lpdwPIDs = (LPDWORD)HeapAlloc( GetProcessHeap(), 0, dwSize2 );
      if( lpdwPIDs == NULL )
      {
        FreeLibrary( hInstLib ) ;
        FreeLibrary( hInstLib2 ) ;
        return FALSE ;
      }
      if( !lpfEnumProcesses( lpdwPIDs, dwSize2, &dwSize ) )
      {
        HeapFree( GetProcessHeap(), 0, lpdwPIDs ) ;
        FreeLibrary( hInstLib ) ;
        FreeLibrary( hInstLib2 ) ;
        return FALSE ;
      }
    }while( dwSize == dwSize2 ) ;
    
    // How many ProcID's did we get?
    dwSize /= sizeof( DWORD ) ;
    
    // Loop through each ProcID.
    for( dwIndex = 0 ; dwIndex < dwSize ; dwIndex++ )
    {
      szFileName[0] = 0 ;
      // Open the process (if we can... security does not
      // permit every process in the system).
      hProcess = OpenProcess(
        PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
        FALSE, lpdwPIDs[ dwIndex ] ) ;
      if( hProcess != NULL )
      {
        // Here we call EnumProcessModules to get only the
        // first module in the process this is important,
        // because this will be the .EXE module for which we
        // will retrieve the full path name in a second.
        if( lpfEnumProcessModules( hProcess, &hMod,
          sizeof( hMod ), &dwSize2 ) )
        {
          // Get Full pathname:
          if( !lpfGetModuleFileNameEx( hProcess, hMod,
            szFileName, sizeof( szFileName ) ) )
          {
            szFileName[0] = 0 ;
          }
        }
        CloseHandle( hProcess ) ;
      }
      // Regardless of OpenProcess success or failure, we
      // still call the enum func with the ProcID.
      if(!lpProc( lpdwPIDs[dwIndex], 0, szFileName, lParam))
        break ;
      
      // Did we just bump into an NTVDM?
      if( _stricmp( szFileName+(strlen(szFileName)-9),
        "NTVDM.EXE")==0)
      {
        // Fill in some info for the 16-bit enum proc.
        sInfo.dwPID = lpdwPIDs[dwIndex] ;
        sInfo.lpProc = lpProc ;
        sInfo.lParam = lParam ;
        sInfo.bEnd = FALSE ;
        // Enum the 16-bit stuff.
        lpfVDMEnumTaskWOWEx( lpdwPIDs[dwIndex],
          (TASKENUMPROCEX) Enum16,
          (LPARAM) &sInfo);
        
        // Did our main enum func say quit?
        if(sInfo.bEnd)
          break ;
      }
    }
    
    HeapFree( GetProcessHeap(), 0, lpdwPIDs ) ;
    FreeLibrary( hInstLib2 ) ;
    
    // If Windows 95:
   }else if( osver.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS )
   {
     
     
     hInstLib = LoadLibraryA( "Kernel32.DLL" ) ;
     if( hInstLib == NULL )
       return FALSE ;
     
     // Get procedure addresses.
     // We are linking to these functions of Kernel32
     // explicitly, because otherwise a module using
     // this code would fail to load under Windows NT,
     // which does not have the Toolhelp32
     // functions in the Kernel 32.
     lpfCreateToolhelp32Snapshot=
       (HANDLE(WINAPI *)(DWORD,DWORD))
       GetProcAddress( hInstLib,
       "CreateToolhelp32Snapshot" ) ;
     lpfProcess32First=
       (BOOL(WINAPI *)(HANDLE,LPPROCESSENTRY32))
       GetProcAddress( hInstLib, "Process32First" ) ;
     lpfProcess32Next=
       (BOOL(WINAPI *)(HANDLE,LPPROCESSENTRY32))
       GetProcAddress( hInstLib, "Process32Next" ) ;
     if( lpfProcess32Next == NULL ||
       lpfProcess32First == NULL ||
       lpfCreateToolhelp32Snapshot == NULL )
     {
       FreeLibrary( hInstLib ) ;
       return FALSE ;
     }
     
     // Get a handle to a Toolhelp snapshot of the systems
     // processes.
     hSnapShot = lpfCreateToolhelp32Snapshot(
       TH32CS_SNAPPROCESS, 0 ) ;
     if( hSnapShot == INVALID_HANDLE_VALUE )
     {
       FreeLibrary( hInstLib ) ;
       return FALSE ;
     }
     
     // Get the first process' information.
     procentry.dwSize = sizeof(PROCESSENTRY32) ;
     bFlag = lpfProcess32First( hSnapShot, &procentry ) ;
     
     // While there are processes, keep looping.
     while( bFlag )
     {
       // Call the enum func with the file name and ProcID.
       if(lpProc( procentry.th32ProcessID, 0,
         procentry.szExeFile, lParam ))
       {
         procentry.dwSize = sizeof(PROCESSENTRY32) ;
         bFlag = lpfProcess32Next( hSnapShot, &procentry );
       }else
         bFlag = FALSE ;
     }
     
     
   }else
     return FALSE ;
   
   // Free the library.
   FreeLibrary( hInstLib ) ;
   
   return TRUE ;
}

BOOL WINAPI Enum16( DWORD dwThreadId, WORD hMod16, WORD hTask16,
                   PSZ pszModName, PSZ pszFileName, LPARAM lpUserDefined )
{
  BOOL bRet ;
  
  EnumInfoStruct *psInfo = (EnumInfoStruct *)lpUserDefined ;
  
  bRet = psInfo->lpProc( psInfo->dwPID, hTask16, pszFileName,
    psInfo->lParam ) ;
  
  if(!bRet)
  {
    psInfo->bEnd = TRUE ;
  }
  
  return !bRet;
} 
