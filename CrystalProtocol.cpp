#include "stdafx.h"
#include "io.h"

#include "Borer.h"
#include "MainFrm.h"
#include "BorerDoc.h"
#include "BorerView.h"

#include "CrystalProtocol.h"
#include "crc.h"                /* describes this code */

#include "CommInfo.h"
#include "FutileData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define  ReposeEvent  ResetEvent

extern CBorerApp theApp;

/********************************************************************
GLOBALS for this file
The string arrays are the items in the dialog list controls.
*******************************************************************/
char * gbl_szBaud[] = {
  "110", "300", "600",  "1200","2400",
    "4800","9600","14400","19200","38400",
    "56000","57600","115200","128000","256000"
};
DWORD   BaudTable[] =  {
  CBR_110,CBR_300,CBR_600,CBR_1200,CBR_2400,
    CBR_4800,CBR_9600,CBR_14400,CBR_19200,CBR_38400,
    CBR_56000,CBR_57600,CBR_115200,CBR_128000,CBR_256000
} ;

char * gbl_szParity[] =   {   "None","Even","Odd","Mark","Space" };
char   ParityTable[] = {  NOPARITY,EVENPARITY,ODDPARITY,MARKPARITY,SPACEPARITY  } ;

char * gbl_szStopBits[] =  {  "1","1.5","2"  };
char   StopBitsTable[] =  { ONESTOPBIT,ONE5STOPBITS,TWOSTOPBITS } ;

char * szDTRControlStrings[] = { "Enable", "Disable", "Handshake" };
DWORD   DTRControlTable[] = { DTR_CONTROL_ENABLE, DTR_CONTROL_DISABLE, DTR_CONTROL_HANDSHAKE };
char * szRTSControlStrings[] = { "Enable", "Disable", "Handshake", "Toggle" };
DWORD   RTSControlTable[] = {   RTS_CONTROL_ENABLE, RTS_CONTROL_DISABLE, 
RTS_CONTROL_HANDSHAKE, RTS_CONTROL_TOGGLE };

UINT AFX_CDECL ITestProc( LPVOID );
UINT AFX_CDECL ITestSendData( LPVOID );
BYTE BCRC(BYTE* BArray,int Start,int Length);//CRC验证函数（取异或）

BYTE BCRC(BYTE* BArray,int Start,int Length)//CRC验证函数（取异或）
{
  BYTE BByte = 0;//开始异或计算的计算
  int i;
  for(i=0;i<Length;i++)
  {
    BByte = BByte ^ BArray[i+Start];
  }
  return BByte;
}

LPVOID DltAlloc(int daSize)
{
  LPVOID lpMemory =NULL;       // Pointer to a region of memory
  LPVOID lpPage =NULL;         // Pointer to a page of memory
  
  lpMemory =VirtualAlloc(NULL,daSize,
    MEM_RESERVE | MEM_COMMIT,
    PAGE_READWRITE);
  
  if(!lpMemory) {
    AfxMessageBox("Fail in Virtual Alloc");
  }
  
  // Your code that uses the just-allocated memory goes here.
  // For example:     LPBYTE MyPointer =(LPBYTE)lpMemory;
  //                  memset (MyPointer, 0, THIRTY_K);
  //                  return MyPointer;
  // . . .
  return  lpMemory;
}

void DltFree(LPVOID lpMemory)
{
  // When you are finished with the memory, you must release it.
  if (!VirtualFree (lpMemory, 0, MEM_RELEASE)) {
    // Your error-handling code goes here. You can use the
    // GetLastError function to obtain more information.
  }
  
  // Remember to clear the pointer to prevent reuse.
  lpMemory =NULL;
}

/////////////////////////////////////////////////////////////////////////////
// CCrystalProtocol
CCrystalProtocol::CCrystalProtocol()
{
  UpData_pView=NULL;
  buf_Inner =new char[CWSZ_MATBUF];
  EXH_Buf   =(unsigned char*)DltAlloc(CWSZ_MATBUF*4);
  
  m_nTesterState=TS_IDLE;
  m_bBusy=false;
  m_bSendData=false;
  
  In_hAllExit=::CreateEvent(NULL,true,false,NULL);//初始无信号，手工重置
  In_hTxExit=::CreateEvent(NULL,true,false,NULL);//初始无信号，手工重置
  
  In_hEchoEvt=::CreateEvent(NULL,true,false,NULL);//初始无信号，手工重置
  
  m_hEvtRecMem = CreateEvent(NULL,FALSE,FALSE,"OutDebugEvent");
}

CCrystalProtocol::~CCrystalProtocol()
{
  delete []buf_Inner;
  DltFree(EXH_Buf);
  
  CloseHandle(In_hAllExit);
  CloseHandle(In_hTxExit);
  
  CloseHandle(In_hEchoEvt);
  
  CloseHandle(m_hEvtRecMem);
}

IMPLEMENT_DYNAMIC(CCrystalProtocol, CSerialPort) 

/////////////////////////////////////////////////////////////////////////////
// CSGProtocol message handlers
//弹出对话框，设置端口参数
bool CCrystalProtocol::SG_InquireDevPara()
{
  if(m_nTesterState != TS_IDLE)
  {
    return FALSE;
  }
  
  CCommInfo  dlgCm;
  dlgCm.CUE_port=m_nTesterSeq;
  
  dlgCm.II_baud=port_dwBaud;
  dlgCm.II_parities=port_Parity;
  dlgCm.II_dbits=port_DataBits;
  dlgCm.II_sbits=port_StopBits;
  
  dlgCm.II_mass=port_Mass;
  dlgCm.II_bulk=port_Bulk;
  dlgCm.II_pkt=port_Packet;
  
  if(dlgCm.DoModal()==IDOK) {
    port_dwBaud=dlgCm.II_baud;
    port_Parity=dlgCm.II_parities;
    port_DataBits=dlgCm.II_dbits;
    port_StopBits=dlgCm.II_sbits;
    
    port_Mass=dlgCm.II_mass;
    port_Bulk=dlgCm.II_bulk;
    port_Packet=dlgCm.II_pkt;
    
    CString      strSec,strMmf;
    
    strSec.Format("%s%d",CW_ITCOMSEC,m_nTesterSeq);
    
    
    sprintf(buf_Inner,"%d",port_Mass);
    WriteIniString(strSec,CMINI_BUFFER,buf_Inner);
    sprintf(buf_Inner,"%d",port_Packet);
    WriteIniString(strSec,CMINI_PKTSZ,buf_Inner);
    sprintf(buf_Inner,"%d",port_Bulk);
    WriteIniString(strSec,CMINI_BULKPKT,buf_Inner);
    
    port_Buf.UnMap();
    strMmf.Format("%s%d",MMF_NAME,m_nTesterSeq);
    port_Buf.MapMemory(strMmf,port_Packet*port_Mass);
    return true;
  }
  return false;
}

//弹出对话框，设置应用参数
bool CCrystalProtocol::SG_InquireAppPara()
{
  if(m_nTesterState != TS_IDLE)
  {
    return FALSE;
  }
  
  CFutileData  dlgCm;
  dlgCm.CUE_port=m_nTesterSeq;
  dlgCm.CUE_Index=m_nTestIndex;
  dlgCm.m_sCfgName=m_strCfgFile;
  dlgCm.m_strMcuFile=m_strMcuMapFile;
  dlgCm.m_strATFile=m_strATFile;
  
  
  if(dlgCm.DoModal()==IDOK) {
    
    m_strMcuMapFile=dlgCm.m_strMcuFile;
    m_strATFile=dlgCm.m_strATFile;
    m_strCfgFile=dlgCm.m_sCfgName;
    
    CString      strSec,strMmf;
    strSec.Format("%s%d",CW_ITCOMSEC,m_nTesterSeq);
    
    //ZZZ		sprintf(buf_Inner,"%d",UpData_eRoll);
    WriteIniString(strSec,CWFL_M2APPROLE,
      buf_Inner);
    
    
    
    sprintf(buf_Inner,"%s",m_strCfgFile);
    WriteIniString(strSec,"CFGNAME",
      buf_Inner);
    
    sprintf(buf_Inner,"%s",m_strATFile);
    WriteIniString(strSec,CWFL_CFGATFILE,
      buf_Inner);
    
    sprintf(buf_Inner,"%s",m_strMcuMapFile);
    WriteIniString(strSec,CWFL_MCUMAPFILE,
      buf_Inner);
    
    m_McuTokenFile.MapFile(m_strMcuMapFile);
    
    return true ;
  }
  return false;
}

///读取配置文件配置
void CCrystalProtocol::SG_Fixup(CString asPersist,int iFixup)
{
  port_sInf=asPersist;
  m_nTesterSeq=iFixup;
  ClarifyRole(asPersist);
}

//读取测试配置参数
void CCrystalProtocol::ClarifyRole(CString &strPersist)
{  
  CString strSec,strMmf,strTip;
  char FileName[_MAX_PATH];
  strSec.Format("%s%d",CW_ITCOMSEC,m_nTesterSeq);
  
  m_nSendManner = (SEND_MANNER)ReadIniInt(strSec,"nsendmaner",1);
  
  m_bWaitPackage=ReadIniInt(strSec,"nWaitResPackage",0);
  
  // update buffering policy
  ReadIniString(strSec,CMINI_PKTSZ,CMINI_DFTPKT,buf_Inner,
    _MAX_PATH);
  port_Packet=atoi(buf_Inner);
  
  ReadIniString(strSec,CMINI_BULKPKT,CMINI_DFTBUK,buf_Inner,
    _MAX_PATH);
  port_Bulk=atoi(buf_Inner);
  
  ReadIniString(strSec,CMINI_BUFFER,CMINI_DFTALL,buf_Inner,
    _MAX_PATH);
  port_Mass=atoi(buf_Inner);
  
  strMmf.Format(MMF_NAME,m_nTesterSeq);
  port_Buf.MapMemory(strMmf,port_Packet*port_Mass);	  
  
  //应用设置
  ReadIniString(strSec,CWFL_M2APPROLE,CWSTR_DFTROLE,buf_Inner,
    _MAX_PATH);
  
  ReadIniString(strSec,"CFGNAME","",FileName,
    _MAX_PATH);
  m_strCfgFile.Format("%s",FileName);
  if(!Ravelout(strPersist,m_strCfgFile)) {
  }
  
  ReadIniString(strSec,CWFL_CFGATFILE,"",FileName,
    _MAX_PATH);
  m_strATFile = FileName;
  
  ReadIniString(strSec,CWFL_MCUMAPFILE,"",FileName,
    _MAX_PATH);
  m_strMcuMapFile = FileName;
  m_McuTokenFile.MapFile(m_strMcuMapFile);
  
}

//开始串口工作
bool CCrystalProtocol::StartDevice()
{
  try {
    //Call CreateFile to open up the comms port
    CString sPort;
    sPort.Format(_T("\\\\.\\COM%d"), m_nTesterSeq);
    port_hComm = CreateFile(sPort, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
    if(port_hComm ==INVALID_HANDLE_VALUE)
    {
      return false;
    }
    
    //Get the current state prior to changing it
    DCB dcb;
    GetState(dcb);
    
    // update DCB rate, byte size, parity, and stop bits size
    dcb.BaudRate =BaudTable[port_dwBaud];
    dcb.Parity   =ParityTable[port_Parity];
    dcb.StopBits =StopBitsTable[port_StopBits];
    dcb.ByteSize =port_DataBits+5;
    
    //NoFlowControl 
    {
      dcb.fOutxCtsFlow = FALSE;
      dcb.fOutxDsrFlow = FALSE;
      dcb.fOutX = FALSE;
      dcb.fInX = FALSE;
    }
    
    //Now that we have all the settings in place, make the changes
    SetState(dcb);
    
    //
    // Save original comm timeouts and set new ones
    //
    GetCommTimeouts(port_hComm, &port_toOrg);
    
    
    SetCommMask(port_hComm, 0);
    
    //
    // set new timeouts
    //
    COMMTIMEOUTS gTimeoutsDefault ={ 0x01, 0, 0, 0, 0 };
    SetCommTimeouts(port_hComm, &gTimeoutsDefault);
    
    //
    // set comm buffer sizes
    //
    SetupComm(port_hComm, MAX_READ_BUFFER, MAX_WRITE_BUFFER);
    PurgeComm(port_hComm, PURGE_FLAGS);
    
    return true;
  }
  catch (CSerialException* pEx)
  {
    TRACE(_T("Handle Exception, Message:%s\n"), pEx->GetErrorMessage());
    pEx->Delete();
    if(port_hComm !=INVALID_HANDLE_VALUE) {
      CloseHandle(port_hComm);
      port_hComm=INVALID_HANDLE_VALUE;
    }
    throw;
  }
}

//停止串口工作
DWORD CCrystalProtocol::StopDevice()
{
  try {
    if(!IsEngrossed()) {
      return WAIT_OBJECT_0;
    }
    //
    // restore original comm timeouts
    //
    SetCommTimeouts(port_hComm,  &port_toOrg);
    //
    // Purge reads/writes, input buffer and output buffer
    //
    PurgeComm(port_hComm, PURGE_FLAGS);
    
    CloseHandle(port_hComm);
    port_hComm=INVALID_HANDLE_VALUE;
    
    return WAIT_OBJECT_0;
  }catch(CSerialException* pEx) {
    TRACE(_T("Handle Exception, Message:%s\n"), pEx->GetErrorMessage());
    pEx->Delete();
    if(port_hComm !=INVALID_HANDLE_VALUE) {
      CloseHandle(port_hComm);
      port_hComm=INVALID_HANDLE_VALUE;
    }
    throw;
  }
}


//停止测试任务
bool CCrystalProtocol::StopTask() //！！！！只是移到SG_StartTask后
{
  if(!IsEngrossed()) 
  {
    return true;
  }
  
  // wait for the thread to exit....		
  SetEvent(In_hAllExit);
  WaitForSingleObject(MT_Work->m_hThread, INFINITE);
  
  if(m_nSendManner==SM_SHAREMEMORY)
  {
    UnmapViewOfFile(m_pDebug);
    CloseHandle(m_hFileDebug);
  }
  
  ((CBorerView *)UpData_pView)->OnCsiQuit();
  
  StopDevice();
  
  m_nTesterState=TS_IDLE;
  m_bBusy=false;
  m_bSendData=false;
  Out_pIndi->PostMessage(MMM_DEV_REDRAW,(WPARAM)m_nTesterState,NULL);
  AfxGetApp()->m_pMainWnd->PostMessage(MMM_DEV_REDRAW,(WPARAM)m_nTesterState,NULL);
  
  delete MT_Work;
  MT_Work =NULL;
  return true;
}

//Borer测试线程
UINT AFX_CDECL ITestProc(LPVOID lpV)
{
  CCrystalProtocol *rdPort =(CCrystalProtocol *)lpV;
  return rdPort->ProcITest();
}

//Borer测试
UINT CCrystalProtocol::ProcITest()
{
  if(!StartDevice()) 
  {
    //	AfxMessageBox("打开串口错误！\n请检查串口连接。");
    m_nTesterState = TS_IDLE ;
    return ERROR_OPEN_FAILED;
  }
  
  m_nTesterState=TS_WORKING;
  Out_pIndi->PostMessage(MMM_DEV_REDRAW,(WPARAM)m_nTesterState,NULL);
  AfxGetApp()->m_pMainWnd->PostMessage(MMM_DEV_REDRAW,(WPARAM)m_nTesterState,NULL);
  
  UINT	nRt;
  try {
    if(m_nSendManner==SM_SHAREMEMORY) ///pdk
    {
      nRt=ProcMemReader();
    }
    else
    {
      if(nRt=ProcMainReader())
        AfxThrowSerialException();	
    }
    return nRt;
  }
  catch(CSerialException *e) {
    char* sMsg="Borer测试";
    AfxGetApp()->m_pMainWnd->PostMessage(MMM_ERROR_DISPLAY,(WPARAM)m_nTesterSeq,(LPARAM)sMsg);
    
    StopDevice();
    
    m_nTesterState=TS_IDLE;
    m_bBusy=false;
    m_bSendData=false;
    
    Out_pIndi->PostMessage(MMM_DEV_REDRAW,(WPARAM)m_nTesterState,NULL);
    AfxGetApp()->m_pMainWnd->PostMessage(MMM_DEV_REDRAW,(WPARAM)m_nTesterState,NULL);
    
    e->Delete();
    return ERROR_OPEN_FAILED;
  }		
}

//从共享内存读取数据
UINT CCrystalProtocol::ProcMemReader()
{
  
  m_hFileDebug = CreateFileMapping(
    (HANDLE)0xFFFFFFFF,
    NULL,
    PAGE_READWRITE,
    0,
    1024,
    "DebugContent");
  
  m_pDebug = (BYTE*)  MapViewOfFile(
    m_hFileDebug,
    FILE_MAP_ALL_ACCESS,
    0,
    0,
    0);
  
  HANDLE  hMMFArray[NUM_READSTAT_HANDLES];
  DWORD   dwRev;
  int     lenMMF;
  
  int     rdrLimit=port_Packet*(port_Mass-port_Bulk);
  bool    fMMFRun = true;
  
  hMMFArray[0] =m_hEvtRecMem;
  hMMFArray[1] =In_hAllExit;
  
  port_Buf.Inaugurate(rdrLimit);
  
  m_pDebug[0]=11;
  
  
  while(fMMFRun) {
    dwRev =WaitForMultipleObjects(NUM_READSTAT_HANDLES,hMMFArray,
      false,STATUS_CHECK_TIMEOUT);
    
    switch(dwRev)
    {
      // read completed
    case WAIT_OBJECT_0:
      lenMMF=*(DWORD*)(m_pDebug+1); 
      if(lenMMF>0)
      {
        memcpy(port_Buf.WritingPointer(),m_pDebug+5,lenMMF);				
        IT_Parse(lenMMF,rdrLimit);							
      }
      m_pDebug[0]=11;
      ResetEvent(m_hEvtRecMem);
      break;
      
      // thread exit event
    case WAIT_OBJECT_0 + 1:
      fMMFRun =false;
      break;
      
    case WAIT_TIMEOUT:
      break;                       
      
    default:
      ASSERT(0x00);
      break;
    }
  }
  
  ResetEvent(In_hAllExit);
  return 0;
}

//从串口读取数据
UINT CCrystalProtocol::ProcMainReader()
{
  
  OVERLAPPED osReader = {0};  // overlapped structure for read operations
  HANDLE     hArray[NUM_READSTAT_HANDLES];
  
  DWORD 	   dwRead;          // bytes actually read
  DWORD      dwRes;           // result from WaitForSingleObject
  DWORD      dwError;           // result from WaitForSingleObject
  
  BOOL       fWaitingOnRead = false;
  BOOL       fThreadDone = false;
  
  
  int  rdrRead =port_Packet*port_Bulk;
  int  rdrLimit=port_Packet*(port_Mass-port_Bulk);
  
  
  
  port_Buf.Inaugurate(rdrLimit);
  
  try {
    //
    // create two overlapped structures,one for read events
    // and another for status events
    //
    osReader.hEvent = CreateEvent(NULL,true,false,NULL);
    if(osReader.hEvent ==NULL)
      throw;
    
    //
    // We want to detect the following events:
    //   Read events (from ReadFile)
    //   Status message events (from our UpdateStatus)
    //   Thread exit evetns (from our shutdown functions)
    //
    hArray[0] = osReader.hEvent;
    hArray[1] = In_hAllExit;
    
    //
    // initial check,forces updates
    //
    ClearError(dwError);
    
    while(!fThreadDone) {
      // if no read is outstanding,then issue another one
      if(!fWaitingOnRead) {
        if(ReadFile(port_hComm,
          port_Buf.WritingPointer(),
          rdrRead,
          &dwRead,&osReader)) {
          if(dwRead) {
            {
              IT_Parse(dwRead,rdrLimit);
            }
          }
        }else {    // read completed immediately
          if((dwError=GetLastError()) != ERROR_IO_PENDING) {	  // read not delayed?
            AfxThrowSerialException();
          }
          fWaitingOnRead = true;
        }
      }
      
      //
      // wait for pending operations to complete
      //
      if(fWaitingOnRead) {
        dwRes = WaitForMultipleObjects(NUM_READSTAT_HANDLES,hArray,
          false,STATUS_CHECK_TIMEOUT);
        switch(dwRes)
        {
          //
          // read completed
          //
        case WAIT_OBJECT_0:
          if(!::GetOverlappedResult(port_hComm,&osReader,&dwRead,false)) {
            if((dwError=GetLastError()) !=ERROR_OPERATION_ABORTED) {
              AfxThrowSerialException();
            }
          }else {      // read completed successfully
            if(dwRead) {
              {
                IT_Parse(dwRead,rdrLimit);
              }
            }
          }
          
          fWaitingOnRead = false;
          break;
          
          //
          // thread exit event
          //
        case WAIT_OBJECT_0 + 1:
          fThreadDone = true;
          break;
          
        case WAIT_TIMEOUT:
          ClearError(dwError);
          break;                       
          
        default:
          AfxThrowSerialException();
          break;
        }
      }
    }
    
    //
    // close event handles
    //
    CloseHandle(osReader.hEvent);
    
    //
    // reset thread exit event here
    //
    ReposeEvent(In_hAllExit);
    return ERROR_SUCCESS;
  } 
  catch(CSerialException *e) 
  {
    CloseHandle(osReader.hEvent);
    ReposeEvent(In_hAllExit);
    
    e->Delete();
    return ERROR_OPERATION_ABORTED;
  }
  catch(...) 
  {
    return ERROR_OPERATION_ABORTED;
  }
}

//解析"上次的遗留数据和本次新接收到的数据"，并更新本次处理后遗留数据的长度和下次缓冲区写入的位置偏移。
void CCrystalProtocol::IT_Parse(int lenNew,int argLmt)
{
  port_Buf.TuneupAdded(lenNew);
  
  ExtractITest();	
}

/*
void CCrystalProtocol::SG_Parse(int lenNew,CM_REV &argRev,int argLmt)
{
//	AfxTrace("SG__Parse--%d\r\n",lenNew);

  port_Buf.TuneupAdded(lenNew);
  
    port_Buf.TuneupLeft(ExtractPackets(port_Buf(port_Buf.ptrFree()-port_Buf.cntleft()),port_Buf.cntleft(),port_Packet));
    
      
        return;
        }
*/
int inline CCrystalProtocol::ExtractPackets(unsigned char *ipBuf,int ipLen,int ipPkt)
{
  
		return 0x0000;
    
}


//按"通信协议"提取通话测试中的四类数据：HS回应消息、返回消息数据、返回查询数据和其他无打包数据。
//并更新rdr_Left(本次遗留数据)。
void CCrystalProtocol::ExtractITest()
{
  RxCallerMsgType oRxType=CALLER_RX_NONE;
  int   pBlink =port_Buf.ptrFree()-port_Buf.cntleft();
  int   pFinal =port_Buf.ptrFree()-(IT_PKT_LEN-1);
  int   pTack  =pBlink;
  int   nPacketLen;
  
  m_cFirstChar = port_Buf[0];
  
  while(pBlink <pFinal) { //0xbe 0x8a flag item...
    if((port_Buf[pBlink]!=(unsigned char)0xbe) ||
      (port_Buf[pBlink+1]!=(unsigned char)0x8a)) {
      pBlink++;
      continue;//？？？？For condense displaying.
    }
    
    if((port_Buf[pBlink+2]==(unsigned char)0xff) &&
      (port_Buf[pBlink+3]==(unsigned char)0xff)) { //回应包
      nPacketLen=8+MCU_LEN_FLAG;
      oRxType =CALLER_RX_CTRL;
    }else if((((pc2hsPacket*)port_Buf(pBlink))->item     ==(unsigned char)0xaa) &&
      (((pc2hsPacket*)port_Buf(pBlink))->length[1]==(unsigned char)MCU_HSHAKE_LEN)) { //握手包
      nPacketLen=MCU_LEN;
      oRxType =CALLER_RX_INIT;
    }else if((port_Buf[pBlink+4]==(BYTE) 0x10) &&
      (port_Buf[pBlink+7]==(BYTE) 0x02)) { //发送测试消息
      if(MCU_LEN_FLAG==2) //////////由len字段得出msg的长度
      {
        nPacketLen =MCU_LEN_FLAG+11+
          (BBYTEINVERSE? port_Buf[pBlink+1+MCU_LEN_FLAG]+port_Buf[pBlink+MCU_LEN_FLAG]*0xff
          : *((unsigned short*)(port_Buf(pBlink+MCU_LEN_FLAG))));
      }else {
        nPacketLen =(int) MCU_LEN_FLAG+11+port_Buf[pBlink+2];
      }
      oRxType =CALLER_RX_MSG;
    }else if((port_Buf[pBlink+MCU_LEN_FLAG+2]==0x40) &&
      ((port_Buf[pBlink+7]==0x00) || (port_Buf[pBlink+7]==0x01))) {///查询数据包
      if(MCU_LEN_FLAG==2) //////////由len字段得出msg的长度
      {
        nPacketLen =MCU_LEN_FLAG+11+
          (BBYTEINVERSE? port_Buf[pBlink+1+MCU_LEN_FLAG]+port_Buf[pBlink+MCU_LEN_FLAG]*0xff
          : *((unsigned short*)(port_Buf(pBlink+MCU_LEN_FLAG))));
      }else {
        nPacketLen =(int) MCU_LEN_FLAG+11+port_Buf[pBlink+2];
      }
      oRxType =CALLER_RX_VALUE;
    }else {
      oRxType =CALLER_RX_NONE;
      pBlink+=2;
      continue;
    }
    
    if(pBlink+nPacketLen>port_Buf.ptrFree()) {
      oRxType =CALLER_RX_WARY;
      break;
    }
    
    if(pBlink-pTack>0) {
      IndicateITest(port_Buf(pTack),pBlink-pTack,CALLER_RX_MCU);
    }
    
    IndicateITest(port_Buf(pBlink),nPacketLen,oRxType);		
    pBlink+=nPacketLen;
    pTack =pBlink;
    oRxType =CALLER_RX_NONE;
  }
  
  pFinal =port_Buf.ptrFree();
  
  if(oRxType ==CALLER_RX_NONE) {
    while(pBlink <pFinal) {
      if(port_Buf[pBlink]==(unsigned char)0xbe) {
        oRxType =CALLER_RX_WARY;
        break;
      }
      pBlink++;
    }
  }
  
  if(pBlink-pTack>0) {
    IndicateITest(port_Buf(pTack),pBlink-pTack,CALLER_RX_MCU);
  }
  
  port_Buf.TuneupLeft(port_Buf.ptrFree()-pBlink);
}

//按数据类型不同的不同，给界面发送消息。
void inline CCrystalProtocol::IndicateITest(unsigned char *fiBuf, int nLen, RxCallerMsgType nMsgType)
{
  
  unsigned int crc=0;
  int nLenIndicate=0;
  
  m_cFirstChar = fiBuf[0];
  
  CMainFrame  *pMyFrm =(CMainFrame*)AfxGetApp()->m_pMainWnd;//取主框架窗口指针
  
  //	AfxTrace("CC_Indicate--%d\r\n",nMsgType);
  switch(nMsgType)
  {
  case CALLER_RX_CTRL:
    crc=::crc32(&fiBuf[2+MCU_LEN_FLAG],2,0);//对item，rtnCode校验,第二个参数是待校验的字节数
    if(crc==*(unsigned int*)&fiBuf[nLen-4])
    {
      SetEvent(In_hEchoEvt);
    }
    //		UpData_pView->PostMessage(MMM_HS_DATA,(WPARAM)"ok",MAKELPARAM(2,CALLER_RX_CTRL));
    
    break;
    
  case CALLER_RX_INIT:
    crc=crc32(fiBuf+4,MCU_LEN-8,0);//从item字段开始校验
    if(crc==*(unsigned int*)&fiBuf[nLen-4])
    {
      SetEvent(In_hEchoEvt);
    }
    
    break;
    
  case CALLER_RX_VALUE:
    //////////////指示了长度
    
    if(MCU_LEN_FLAG==2) 
    {
      BYTE nHighByte=fiBuf[1+MCU_LEN_FLAG];
      BYTE nLowByte=fiBuf[1+MCU_LEN_FLAG-1];
      if(BBYTEINVERSE) 
      {
        nLenIndicate=nHighByte+(nLowByte)*0xff;
      }
      else 
      {//高字节，高位；低字节，低位
        nLenIndicate=nLowByte+(nHighByte)*0xff;
      }
    }
    else 
    {
      nLenIndicate=fiBuf[2];
    }
    ////////////////
    crc=::crc32(&fiBuf[2+MCU_LEN_FLAG],(unsigned int)(5+nLenIndicate),0);//从item->dataSent校验
    
    if(crc==*(unsigned int*)&fiBuf[nLen-4])
    {
      UpData_pView->PostMessage(MMM_HS_DATA,(WPARAM)fiBuf,MAKELPARAM(nLen,CALLER_RX_VALUE));
    }
    break;	
    
  case CALLER_RX_MSG:
    //////////////指示了长度
    if(MCU_LEN_FLAG==2) 
    {
      BYTE nHighByte=fiBuf[1+MCU_LEN_FLAG];
      BYTE nLowByte=fiBuf[1+MCU_LEN_FLAG-1];
      if(BBYTEINVERSE) 
      {
        nLenIndicate=nHighByte+(nLowByte)*0xff;
      }
      else 
      {//高字节，高位；低字节，低位
        nLenIndicate=nLowByte+(nHighByte)*0xff;
      }
    }
    else 
    {
      nLenIndicate=fiBuf[2];
    }
    ////////////////
    crc=::crc32(&fiBuf[2+MCU_LEN_FLAG],(unsigned int)(5+nLenIndicate),0);//从item->dataSent校验
    
    if(crc==*(unsigned int*)&fiBuf[nLen-4])
    {
      UpData_pView->PostMessage(MMM_HS_DATA,(WPARAM)fiBuf,MAKELPARAM(nLen,CALLER_RX_MSG));
    }
    break;	
  case CALLER_RX_MCU:
    
    pMyFrm->m_editMcu[m_nTestIndex]->PostMessage(MMM_SHOW_GETDATA,(WPARAM)fiBuf,MAKELPARAM(nLen,INTRACE));
    
    //		UpData_pView->PostMessage(MMM_HS_DATA,(WPARAM)fiBuf,MAKELPARAM(nLen,CALLER_RX_MCU));
    break;
    
  }
}



//功能: 数据输出的函数, 供输出线程调用
DWORD inline CCrystalProtocol::TL_Utter(unsigned char *soBuf,unsigned long owLen)
{
  CBorerView *pView=(CBorerView * )this->UpData_pView;
  
  if(m_nSendManner==SM_SHAREMEMORY) // pdk
  {
    m_ManageShareMemory.SendMsgToShareMem((char *)soBuf,(int) owLen,0,UpData_pView);
  }
  else
  {
    try {
      OVERLAPPED AsyncWriteInfo = { 0 };
      AsyncWriteInfo.hEvent = CreateEvent( NULL, TRUE, FALSE, NULL );
      HANDLE handles[ 2 ] ={AsyncWriteInfo.hEvent,In_hTxExit};
      
      DWORD  OWOK;
      DWORD  OWcount,OWpointer;
      DWORD  result_count;
      
      //
      // Purge reads/writes, input buffer and output buffer
      //
      if(!PurgeComm(port_hComm,PURGE_TXBITS))  //Two-Layer Write
        AfxThrowSerialException();
      
      OWpointer=0;
      OWOK=ERROR_SUCCESS;
      
      while(OWOK==ERROR_SUCCESS) {
        OWcount =(int) min(owLen-OWpointer,500);
        if(OWcount==0) {
          break;
        }
        
        if(!WriteFile( port_hComm, soBuf+OWpointer,OWcount,&result_count,&AsyncWriteInfo)) {
          if(GetLastError()!=ERROR_IO_PENDING) {
            OWOK =ERROR_WRITE_FAULT;
            break;
          }
          
          switch ( WaitForMultipleObjects( 2, handles, FALSE, INFINITE ) ) 
          {
          case 0 : //AsyncWriteInfo.hEvent
            if(!::GetOverlappedResult( port_hComm, &AsyncWriteInfo, &result_count, FALSE ) ||
              (result_count != OWcount)) {
              OWOK = ERROR_WRITE_FAULT;                       
            }else {
              OWpointer+=result_count;
            }
            break;
            
          case 1 : //m_hKillOutputThreadEvent
            OWOK = ERROR_CANCELLED; 
            PurgeComm( port_hComm, PURGE_TXABORT ); 
            break;
          }
        }else {
          if(result_count!=OWcount) {
            OWOK = ERROR_WRITE_FAULT;                        
          }else {
            OWpointer+=result_count;
          }
        }                         
      }
      
      CloseHandle( AsyncWriteInfo.hEvent );
      ReposeEvent(In_hTxExit);  //Two-Layer Write reset thread exit event here
      return OWOK;
    }catch(CSerialException *e) {
      e->Delete();
      return ERROR_OPERATION_ABORTED;
    }
  }
  return 0;
}

int CCrystalProtocol::PackSendMessage(EM_MESSAGE &pmsg,int nRemain)
{
  return PackSendMessage1(pmsg,nRemain);
}

//仿真消息数据打包
int CCrystalProtocol::PackSendMessage1(EM_MESSAGE &pmsg,int nRemain)
{
  int nContLen,nItem,nCmdType,nTestTask;
  unsigned int crc=0;
  char pmsgContent[1000];
  pc2hsPacket* pPacketBuf=(pc2hsPacket*)EXH_Buf;
  ::memset(pPacketBuf,0x00,sizeof(pc2hsPacket)/sizeof(unsigned char));
  
  nItem=0x10;
  nTestTask=pmsg.did;
  nCmdType=0x02;
  if(nRemain>0)
  {
    nContLen=MCU_LEN-MCU_HEAD_LEN;
  }
  else
  {
    nContLen=(4+pmsg.length)%(MCU_LEN-MCU_HEAD_LEN);
    if(nContLen==0)
    {
      nContLen=MCU_LEN-MCU_HEAD_LEN;
    }
  }
  
  pPacketBuf->head[0]=0xbe;
  pPacketBuf->head[1]=0x8a;
  pPacketBuf->length[0]=0x00;
  pPacketBuf->length[1]=(unsigned char)nContLen;
  pPacketBuf->item=(unsigned char)nItem;
  pPacketBuf->BeTestTask=(unsigned char)nTestTask;
  pPacketBuf->cmdtype=(unsigned char)nCmdType;
  pPacketBuf->remain=nRemain;
  
  memcpy(pmsgContent,&pmsg,4+pmsg.length);
  
  memcpy(pPacketBuf->content,pmsgContent+((4+pmsg.length)/(MCU_LEN-MCU_HEAD_LEN)-nRemain)*(MCU_LEN-MCU_HEAD_LEN),nContLen);
  
  crc=crc32(&pPacketBuf->item,MCU_LEN-8,0);//从item字段开始校验
  memcpy(pPacketBuf->crcrult,&crc,4);
  
  return MCU_LEN;
}

////发送仿真消息包
UINT CCrystalProtocol::TxSendMessage(EM_MESSAGE &pmsg,char *strshow)
{
  int xrLen=0;
  ReposeEvent(In_hEchoEvt);
  
  /*TRACE("ITExSendMessage(%cUARTM_SendData(",'\'"');
	 for(int j=0;j<pmsg.length;j++)
   {
   TRACE("0X%02X,",pmsg.Union.content[j]);
   }
   TRACE(")%c,1);\n",'\'"');
  */
  ShowMsg(strshow,OUTCONTENT);
  if((pmsg.length+4)>(MCU_LEN-MCU_HEAD_LEN))
  {
    int nPackNum=(4+pmsg.length)/(MCU_LEN-MCU_HEAD_LEN)+1;
    for(int i=0;i<nPackNum;i++)
    {
      xrLen=PackSendMessage(pmsg,nPackNum-1-i);
      DataSendPort(xrLen);
    }
    return ERROR_SUCCESS;
    
  }
  else
  {
    xrLen=PackSendMessage(pmsg,0);
    return DataSendPort(xrLen);
  }	
}

int CCrystalProtocol::PackBegin(char *str,int nNum)
{
  return PackBegin1(str,nNum);
}

//测试任务开始数据打包
int CCrystalProtocol::PackBegin1(char *str,int nNum)
{
  int nContLen,nItem,nCmdType,nTestTask;
  unsigned int crc=0;
  pc2hsPacket* pPacketBuf=(pc2hsPacket*)EXH_Buf;
  ::memset(pPacketBuf,0x00,sizeof(pc2hsPacket)/sizeof(unsigned char));
  
  nItem=0x10;
  nTestTask=0xFF;
  nCmdType=0x00;
  nContLen=nNum;
  
  pPacketBuf->head[0]=0xbe;
  pPacketBuf->head[1]=0x8a;
  pPacketBuf->length[0]=0x00;
  pPacketBuf->length[1]=(unsigned char)nContLen;
  pPacketBuf->item=(unsigned char)nItem;
  pPacketBuf->BeTestTask=(unsigned char)nTestTask;
  pPacketBuf->cmdtype=(unsigned char)nCmdType;
  
  memcpy(pPacketBuf->content,str,nNum);
  
  crc=crc32(&pPacketBuf->item,MCU_LEN-8,0);//从item字段开始校验
  memcpy(pPacketBuf->crcrult,&crc,4);
  
  return MCU_LEN;
}

//发送测试任务包
UINT CCrystalProtocol::TxBegin(char *str,int nNum,char *strshow)
{
  int xrLen=0;
  ReposeEvent(In_hEchoEvt);
  xrLen=PackBegin(str,nNum);
  ShowMsg(strshow,OUTCONTENT);
  return DataSendPort(xrLen);	
}

int CCrystalProtocol::PackEnd()
{
  return PackEnd1();
}

//Borer测试任务结束数据打包
int CCrystalProtocol::PackEnd1()
{
  int nContLen,nItem,nCmdType,nTestTask;
  unsigned int crc=0;
  pc2hsPacket* pPacketBuf=(pc2hsPacket*)EXH_Buf;
  ::memset(pPacketBuf,0x00,sizeof(pc2hsPacket)/sizeof(unsigned char));
  
  nItem=0x10;
  nTestTask=0xFF;
  nCmdType=0X07;
  nContLen=0;
  
  pPacketBuf->head[0]=0xbe;
  pPacketBuf->head[1]=0x8a;
  pPacketBuf->length[0]=0x00;
  pPacketBuf->length[1]=(unsigned char)nContLen;
  pPacketBuf->item=(unsigned char)nItem;
  pPacketBuf->BeTestTask=(unsigned char)nTestTask;
  pPacketBuf->cmdtype=(unsigned char)nCmdType;
  
  crc=crc32(&pPacketBuf->item,MCU_LEN-8,crc);//从item字段开始校验
  memcpy(pPacketBuf->crcrult,&crc,4);
  
  return MCU_LEN;
}
//发送测试任务结束数据包
UINT CCrystalProtocol::TxEnd()
{
  int xrLen=0;
  ReposeEvent(In_hEchoEvt);
  xrLen=PackEnd();
  ShowMsg("发送结束命令ITExEnd();\r\n",OUTCONTENT);
  return DataSendPort(xrLen);	
}

int CCrystalProtocol::PackGetVar(int address,int nlen,int nKind)
{
  return PackGetVar1(address,nlen,nKind);
}

//获取内存值数据打包
int CCrystalProtocol::PackGetVar1(int address,int nlen,int nKind)
{
  int nContLen,nItem,nCmdType,nTestTask;
  unsigned int crc=0;
  pc2hsPacket* pPacketBuf=(pc2hsPacket*)EXH_Buf;
  ::memset(pPacketBuf,0x00,sizeof(pc2hsPacket)/sizeof(unsigned char));
  
  nItem=0x40;
  nTestTask=0xFF/*TID_?*/;
  nCmdType=nKind;
  nContLen=6;
  
  pPacketBuf->head[0]=0xbe;
  pPacketBuf->head[1]=0x8a;
  pPacketBuf->length[0]=0x00;
  pPacketBuf->length[1]=(unsigned char)nContLen;
  pPacketBuf->item=(unsigned char)nItem;
  pPacketBuf->BeTestTask=(unsigned char)nTestTask;
  pPacketBuf->cmdtype=(unsigned char)nCmdType;
  
  *( (DWORD*)(pPacketBuf->content + 0 ) )  = address;
  pPacketBuf->content[4]=(unsigned char)0x00;
  pPacketBuf->content[5]=(unsigned char)nlen;
  
  
  crc=crc32(&pPacketBuf->item,MCU_LEN-8,0);//从item字段开始校验
  memcpy(pPacketBuf->crcrult,&crc,4);
  
  return MCU_LEN;
}

//发送获取内存值数据包
UINT CCrystalProtocol::TxGetVar(int address,int nlen,int nKind,char *strshow)
{
  int xrLen=0;
  ReposeEvent(In_hEchoEvt);
  xrLen=PackGetVar(address,nlen,nKind);
  ShowMsg(strshow,OUTCONTENT);
  return DataSendPort(xrLen);	
}
/////

int CCrystalProtocol::PackSetVar(int address,int nlen,const char *sContent,int nKind)
{
  return PackSetVar1(address,nlen, sContent,nKind);
}

////设置内存值数据打包
int CCrystalProtocol::PackSetVar1(int address,int nlen,const char *sContent,int nKind)
{
  int nContLen,nItem,nCmdType,nTestTask;
  unsigned int crc=0;
  pc2hsPacket* pPacketBuf=(pc2hsPacket*)EXH_Buf;
  ::memset(pPacketBuf,0x00,sizeof(pc2hsPacket)/sizeof(unsigned char));
  
  nItem=0x10;
  nTestTask=0xFF/*TID_?*/;
  nCmdType=0x01;
  nContLen=6+nlen;
  
  pPacketBuf->head[0]=0xbe;
  pPacketBuf->head[1]=0x8a;
  pPacketBuf->length[0]=0x00;
  pPacketBuf->length[1]=(unsigned char)nContLen;
  pPacketBuf->item=(unsigned char)nItem;
  pPacketBuf->BeTestTask=(unsigned char)nTestTask;
  pPacketBuf->cmdtype=(unsigned char)nCmdType;
  
  *( (DWORD*)(pPacketBuf->content + 0 ) )  = address;
  pPacketBuf->content[4]=0x00;
  pPacketBuf->content[5]=(unsigned char)nlen;
  for(int k=0;k<nlen;k++)
  {
    pPacketBuf->content[6+k]=(unsigned char)sContent[k];
  }	
  
  crc=crc32(&pPacketBuf->item,MCU_LEN-8,crc);//从item字段开始校验
  memcpy(pPacketBuf->crcrult,&crc,4);
  
  return MCU_LEN;
}

//发送设置内存值数据包
UINT CCrystalProtocol::TxSetVar(int address,int nlen,const char *sContent,int nKind,char *strshow)
{
  int xrLen=0;
  ReposeEvent(In_hEchoEvt);
  xrLen=PackSetVar(address,nlen,sContent,nKind);
  ShowMsg(strshow,OUTCONTENT);
  return DataSendPort(xrLen);	
}

int CCrystalProtocol::PackTrace(char *str,int nNum,int nKind)
{
  return PackTrace1(str,nNum,nKind);
}
////终端模块信息显示数据打包
int CCrystalProtocol::PackTrace1(char *str,int nNum,int nKind)
{
  int nContLen,nItem,nCmdType,nTestTask;
  unsigned int crc=0;
  pc2hsPacket* pPacketBuf=(pc2hsPacket*)EXH_Buf;
  ::memset(pPacketBuf,0x00,sizeof(pc2hsPacket)/sizeof(unsigned char));
  
  nItem=0x30;
  nTestTask=0xFF/*TID_?*/;
  nCmdType=nKind;
  nContLen=nNum;
  
  pPacketBuf->head[0]=0xbe;
  pPacketBuf->head[1]=0x8a;
  pPacketBuf->length[0]=0x00;
  pPacketBuf->length[1]=(unsigned char)nContLen;
  pPacketBuf->item=(unsigned char) nItem;
  pPacketBuf->BeTestTask=(unsigned char) nTestTask;
  pPacketBuf->cmdtype=(unsigned char)nCmdType;
  
  memcpy(pPacketBuf->content,str,nNum);
  
  crc=crc32(&pPacketBuf->item,MCU_LEN-8,0);//从item字段开始校验
  memcpy(pPacketBuf->crcrult,&crc,4);
  
  return MCU_LEN;
}


////发送终端模块信息显示数据包
UINT CCrystalProtocol::TxTrace(char *str,int nNum,int nKind,char *strshow)
{
  int xrLen=0;
  ReposeEvent(In_hEchoEvt);
  xrLen=PackTrace(str,nNum,nKind);
  ShowMsg(strshow,OUTCONTENT);
  return DataSendPort(xrLen);	
}

UINT AFX_CDECL ITestSendData(LPVOID lpV)
{
  CCrystalProtocol *rdPort =(CCrystalProtocol *)lpV;
  while(1)
  {
    if(rdPort->m_bSendData)
    {
      if(!rdPort->m_bBusy)
      {
        rdPort->m_bBusy=true;
        rdPort->DataSendPort(35);
        rdPort->m_bBusy=false;
      }
      rdPort->m_bSendData=false;
    }
  }
}

//发送串口数据
UINT CCrystalProtocol::ITHandShake()
{
  int nTxNumber=0;
  while(nTxNumber<SEND_CMD_NUMBER) 
  {
    nTxNumber++;		
    if(TxShakeHand()!=ERROR_SUCCESS) 
    {
      m_nTesterState = TS_IDLE ;
      return ERROR_WRITE_FAULT;
    }
    
    DWORD dwResult=::WaitForSingleObject(In_hEchoEvt,ANSWER_TIMEOUT);
    if(dwResult==WAIT_OBJECT_0)
    {
      ReposeEvent(In_hEchoEvt);
      ShowMsg("握手成功\r\n",TIPINFO);
      return ERROR_SUCCESS;
    }
    else
    {
      ShowMsg("握手超时\r\n",TIPINFO);
    }
  }
  
  return ERROR_WRITE_FAULT;
}

//发送串口数据
UINT CCrystalProtocol::DataSendPort(int len)
{
  int nTxNumber=0;
  CMainFrame  *pMyFrm =(CMainFrame*)AfxGetApp()->m_pMainWnd;//取主框架窗口指针	
  while(nTxNumber<SEND_CMD_NUMBER) 
  {
    nTxNumber++;		
    if(TL_Utter( EXH_Buf,(unsigned long)len)!=ERROR_SUCCESS) 
    {
      return ERROR_WRITE_FAULT;
    }
    
    if(m_bWaitPackage) 
    {
      DWORD dwResult=::WaitForSingleObject(In_hEchoEvt,ANSWER_TIMEOUT);
      if(dwResult==WAIT_OBJECT_0)
      {
        ReposeEvent(In_hEchoEvt);
        //			ShowMsg("发送成功\r\n",TIPINFO);
        return ERROR_SUCCESS;
      }
    }
    else
    {
      return ERROR_SUCCESS;
    }
  }
  return ERROR_WRITE_FAULT;
}

char strShowChar[1000] ;
//显示信息
bool CCrystalProtocol::ShowMsg(char *str,SHOWKIND nKind)
{
  CMainFrame  *pMyFrm =(CMainFrame*)AfxGetApp()->m_pMainWnd;//取主框架窗口指针	
  memset(strShowChar,0,1000);
  sprintf(strShowChar,"——>%s",str);
  pMyFrm->m_editMcu[m_nTestIndex]->PostMessage(MMM_SHOW_GETDATA,(WPARAM)strShowChar,MAKELPARAM(strlen(strShowChar),nKind));
  return true;
}

int PcSleep(int nms,void *sapp);
//发送消息
bool CCrystalProtocol::SendMessageToPort(EM_MESSAGE &pmsg,int tsleep,char *str)
{
  if(PcSleep(tsleep,UpData_pView)>0) {
    return false;
  }
  
  if(TxSendMessage(pmsg,str)==ERROR_SUCCESS)
  {
    return true;
  }
  else
  {
    return false;
  }	
}

////握手数据打包
int CCrystalProtocol::PackShakeHand()
{
  unsigned int crc=0;
  pc2hsPacket* pPacketBuf=(pc2hsPacket*)EXH_Buf;
  ::memset(pPacketBuf,0x00,sizeof(pc2hsPacket)/sizeof(unsigned char));
  
  pPacketBuf->head[0]=0xbe;
  pPacketBuf->head[1]=0x8a;
  pPacketBuf->length[0]=0x00;
  pPacketBuf->length[1]=(unsigned char)MCU_HSHAKE_LEN;
  pPacketBuf->item=(unsigned char) 0xaa;
  pPacketBuf->BeTestTask=(unsigned char) 0xFF;
  pPacketBuf->cmdtype=(unsigned char)0x00;
  
  crc=crc32(&pPacketBuf->item,MCU_LEN-8,0);//从item字段开始校验
  memcpy(pPacketBuf->crcrult,&crc,4);
  
  return MCU_LEN;
}

//发送握手数据包
UINT CCrystalProtocol::TxShakeHand()
{
  int xrLen=0;
  ReposeEvent(In_hEchoEvt);
  xrLen=PackShakeHand();
  ShowMsg("发送握手数据包",OUTCONTENT);
  
  return TL_Utter( EXH_Buf,(unsigned long)xrLen);	
}

//功能: 内部函数, 将数据打包
int CCrystalProtocol::PacketATCommand(char *bufferData,int nDataLen,int nRemain)
{
  memcpy(EXH_Buf, bufferData ,nDataLen ); 	
  EXH_Buf[nDataLen]				= (char) 0x0A; 
  EXH_Buf[nDataLen+1]				= (char) 0x0D; 
  return nDataLen+2;
}

UINT CCrystalProtocol::SendATCommand(char *bufferData,int nDataLen)
{
  int xrLen=0;
  ReposeEvent(In_hEchoEvt);
  xrLen=PacketATCommand(bufferData, nDataLen,0);
  ShowMsg(bufferData,OUTCONTENT);
  
  return TL_Utter( EXH_Buf,(unsigned long)xrLen);	
  
}

BOOL CCrystalProtocol::SendAT(char *bufferData,int tsleep)
{
  if(PcSleep(tsleep,UpData_pView)>0) {
    return false;
  }
  
  if(SendATCommand(bufferData,strlen(bufferData)))
  {
    return true;
  }
  else
  {
    return false;
  }	
}

int ChangeHex(char * strInput,unsigned char * strOutput)
{
  int nStringLen = strlen(strInput);
  if(nStringLen == 0)
  {
    return 0;
  }
  
  int k=0;
  char sss[3];
  memset(sss,0,3);
  char   *stopstring;
  
  for(int i=0;i<nStringLen;)
  {
	   sss[0] = strInput[i];
     sss[1] = strInput[i+1];
     strOutput[k++] = strtoul(sss, &stopstring, 16);
     i+=3;
  }
  
  return k;
}


