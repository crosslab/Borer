#if !defined(AFX_CRYSTALPROTOCOL_H__3086EE19_78DD_46B7_A7DB_6437EF0913F0__INCLUDED_)
#define AFX_CRYSTALPROTOCOL_H__3086EE19_78DD_46B7_A7DB_6437EF0913F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "lock.h"

typedef enum _TestStates {
    TS_IDLE = 1,
    TS_WORKING = 2
}TEST_STATE;

typedef enum _TestMannerStates {
    SM_COM = 0,
    SM_SHAREMEMORY = 1,
    SM_DATABASE = 3
}SEND_MANNER;

#define MCU_LEN				35
#define MCU_HEAD_LEN		13
#define TEST_CMD_MSG_IN		0x02
#define MCU_LEN_FLAG		2		//取值1或2
#define MCU_HSHAKE_LEN		22

#define BBYTEINVERSE		0
#define SEND_CMD_NUMBER		1
#define ANSWER_TIMEOUT      5000
#define IT_PKT_LEN           9 
//pc发给hs的消息包中的dataSent格式
struct mesg 
{
  unsigned char 	dest;
  unsigned char 	type;
  unsigned char	src;
  unsigned char	length;
  unsigned char	content[MCU_LEN-17]; // MCU_LEN=35
};

//pc发给hs的消息包（定长）
struct pc2hsPacket 
{
  unsigned char	head[2];
  unsigned char	length[2];
  unsigned char	item;
  unsigned char	res;
  unsigned char	BeTestTask;
  unsigned char	cmdtype;
  unsigned char	remain;
  unsigned char	content[MCU_LEN-13]; 	// Data sent.
  unsigned char	crcrult[4];
};

enum RxCallerMsgType//根据不同的messageType，进行不同的处理
{
  CALLER_RX_NONE,
    CALLER_RX_WARY,
    CALLER_RX_CTRL,
    CALLER_RX_INIT,
    CALLER_RX_MSG,
    CALLER_RX_VALUE,
    CALLER_RX_MCU
};

#define MAX_WRITE_BUFFER        2048
#define MAX_READ_BUFFER         2048

#define NUM_READSTAT_HANDLES    2
#define STATUS_CHECK_TIMEOUT    2048
#define TIMEOUT			(90*1000)	//命令发送后等待下一消息的超时时间

#define PURGE_FLAGS             (PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR) 
#define PURGE_TXBITS            (PURGE_TXABORT | PURGE_TXCLEAR )

const int	CWSZ_MATBUF    =8192;
const int	CWOFF_LEN      =2;

#define CW_ITCOMSEC "ITSECCOM"

#define CWSTR_DFTNEG         "-1"
#define CWSTR_DFTINT         "0"
#define CWSTR_DFTSTR         ""
#define CWSTR_SPACE          " "
#define CWSTR_DFTTRUE        "1"
#define CWSTR_DFTROLE        "0"
#define CWSTR_DFTBAUD        "12"
#define CWSTR_DFTDATA        "3"
#define CWSTR_DFTXON         "17"
#define CWSTR_DFTXOFF        "19"

#define CWFL_M2APPROLE "M2AppRole"
#define CWFL_M2APPCARE "M2AppCare"
#define CWFL_M2APPVERB "M2AppVerb"
#define CWFL_MCUMAPFILE "MCUMapFile"
#define CWFL_PROJECTFILE "PROJECTFILE"
#define CWFL_CFGATFILE "CFGATFILE"

#define CMINI_BUFFER   "M2inibuf"
#define CMINI_PKTSZ    "M2inipkt"
#define CMINI_BULKPKT  "M2iniblk"

#define CMINI_DFTALL        "512"
#define CMINI_DFTPKT        "256"  //最大包长BYTE
#define CMINI_DFTBUK        "2"  //最大包长BYTE

bool Ravelout(CString &roIni,CString &roWif);

/////////////////////////////////////////////////////////////////////////////
// CCrystalProtocol command target
class CCrystalProtocol : public CSerialPort
{
  DECLARE_DYNAMIC(CCrystalProtocol);
  
  // Construction
public:
  CCrystalProtocol();
  virtual ~CCrystalProtocol();
  
public:
  void SG_Fixup(CString asPersist,int iFixup); //asPersist配置文件名，
  void ClarifyRole(CString &strPersist);
  
  bool SG_StartTask(CWnd  *pWndIndi, 	 //如不为NULL，收到包时向其POSTMESSAGE
    HANDLE  pEnvIndi);	 //如不为NULL，收到包时设置此事件厎
		
  
  bool StopTask(); 	 //停止此任务时。
  
  //Configuration Methods
  bool SG_InquireDevPara();  //弹出对话框，设置端口参数
  bool SG_InquireAppPara();  //弹出对话框，设置应用参数
  
  void IT_Parse(int lenNew,int argLmt);
  
  UINT ProcITest();
  UINT DataSendPort(int len);
  
  UINT TxShakeHand();
  UINT ITHandShake();
  
  UINT TxSendMessage(EM_MESSAGE &pmsg,char *strshow);
  UINT TxBegin(char *str,int nNum,char *strshow);
  UINT TxTrace(char *str,int nNum,int nKind,char *strshow);
  UINT TxEnd();
  UINT TxGetVar(int address,int nlen,int nKind,char *strshow);
  UINT TxSetVar(int address,int nlen,const char *sContent,int nKind,char *strshow);
  bool ShowMsg(char *str,SHOWKIND nKind);
  bool SendMessageToPort(EM_MESSAGE &pmsg,int tsleep,char *str);
  UINT SendATCommand(char *bufferData,int nDataLen);
  BOOL SendAT(char *bufferData,int tsleep);
  
protected:
  bool  StartDevice();
  DWORD StopDevice();
  
  
  int  inline  ExtractPackets(unsigned char *ipBuf,int ipLen,int ipPkt);
  void inline  ExtractITest();
  void inline  IndicateITest(unsigned char* fiBuf,int nLen,RxCallerMsgType nMsgType);
  
  UINT  ProcMainReader();//串口读取数据 测试
  UINT  ProcMemReader();//内存读取数据
  
  DWORD  inline  TL_Utter(unsigned char *soBuf,unsigned long soLen);		//写串口函数
  
  int  inline SniffITest(unsigned char *shBuf,int shLen,int &shOffset,int &shEssence);
  
  int inline PackSendMessage(EM_MESSAGE &pmsg,int nRemain);
  int inline PackTrace(char *str,int nNum,int nKind);
  int inline PackBegin(char *str,int nNum);
  int inline PackEnd();
  int inline PackGetVar(int address,int nlen,int nKind);
  int inline PackSetVar(int address,int nlen,const char *sContent,int nKind);
  
  
  int inline PackSendMessage1(EM_MESSAGE &pmsg,int nRemain);
  int inline PackTrace1(char *str,int nNum,int nKind);
  int inline PackBegin1(char *str,int nNum);
  int inline PackEnd1();
  int inline PackGetVar1(int address,int nlen,int nKind);
  int inline PackSetVar1(int address,int nlen,const char *sContent,int nKind);
  int inline PackShakeHand();
  int PacketATCommand(char *bufferData,int nDataLen,int nRemain);
  
  
public:
  bool m_bBusy;					//判断串口是否忙
  bool m_bSendData;				//是否需要发送数据
  
  CString m_strCfgFile;           //终端参数配置文件
  CString m_strMcuMapFile;
  CString m_strATFile;
  char    m_cFirstChar;
  SEND_MANNER     m_nSendManner;	         //发送方式
  BOOL    m_bWaitPackage;          //是否需要等待回应包
  
  TEST_STATE    m_nTesterState;      // 测试的状态，工作 or 空闲
  int           m_nTesterSeq;		     // 测试的序列号
  int           m_nTestIndex;		     // 测试在列表的顺序号
  
  CView        *UpData_pView;		// 获得VIEW,方便获得文档，以关闭此文档时用。
  
  CTokenMap     m_McuTokenFile;		// Map File 类 MCU
  
  //覆盖测试时数据量大，用“CWND POSTMESSAGE”。	
  
protected:	
  CWnd        *Out_pIndi;     //串口指针
  
  unsigned char  *EXH_Buf;	//串口发送数据
  CString      port_sInf;  //串口配置文件
  char           *buf_Inner;  
  
  
  DWORD       port_dwBaud;		//波特率
  int         port_Parity;		//校验位
  int         port_DataBits;		//数据位
  int         port_StopBits;		//停止位
  
  
  int           port_Packet;		//包大小
  int           port_Bulk;		//突发包
  int           port_Mass;		//缓冲区
  
  COMMTIMEOUTS  port_toOrg; 
  
  
  CRobinBuffer  port_Buf;     //串口接收数据
  HANDLE       In_hAllExit;	//退出事件
  HANDLE       In_hTxExit;	//发送退出事件
  
  HANDLE		In_hEchoEvt;	//pc->hs命令的回应事件
  HANDLE		m_hEvtRecMem;	//接收数据事件
  
  CWinThread   *MT_Work;		//处理线程
  
  
  HANDLE m_hFileDebug;		//接收共享内存句柄
  BYTE * m_pDebug;		    //接收共享内存指针
  
  ManageShareMemory m_ManageShareMemory;
  
};

#endif // !defined(AFX_CRYSTALPROTOCOL_H__3086EE19_78DD_46B7_A7DB_6437EF0913F0__INCLUDED_)
