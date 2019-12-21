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
#define MCU_LEN_FLAG		2		//ȡֵ1��2
#define MCU_HSHAKE_LEN		22

#define BBYTEINVERSE		0
#define SEND_CMD_NUMBER		1
#define ANSWER_TIMEOUT      5000
#define IT_PKT_LEN           9 
//pc����hs����Ϣ���е�dataSent��ʽ
struct mesg 
{
  unsigned char 	dest;
  unsigned char 	type;
  unsigned char	src;
  unsigned char	length;
  unsigned char	content[MCU_LEN-17]; // MCU_LEN=35
};

//pc����hs����Ϣ����������
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

enum RxCallerMsgType//���ݲ�ͬ��messageType�����в�ͬ�Ĵ���
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
#define TIMEOUT			(90*1000)	//����ͺ�ȴ���һ��Ϣ�ĳ�ʱʱ��

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
#define CMINI_DFTPKT        "256"  //������BYTE
#define CMINI_DFTBUK        "2"  //������BYTE

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
  void SG_Fixup(CString asPersist,int iFixup); //asPersist�����ļ�����
  void ClarifyRole(CString &strPersist);
  
  bool SG_StartTask(CWnd  *pWndIndi, 	 //�粻ΪNULL���յ���ʱ����POSTMESSAGE
    HANDLE  pEnvIndi);	 //�粻ΪNULL���յ���ʱ���ô��¼��}
		
  
  bool StopTask(); 	 //ֹͣ������ʱ��
  
  //Configuration Methods
  bool SG_InquireDevPara();  //�����Ի������ö˿ڲ���
  bool SG_InquireAppPara();  //�����Ի�������Ӧ�ò���
  
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
  
  UINT  ProcMainReader();//���ڶ�ȡ���� ����
  UINT  ProcMemReader();//�ڴ��ȡ����
  
  DWORD  inline  TL_Utter(unsigned char *soBuf,unsigned long soLen);		//д���ں���
  
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
  bool m_bBusy;					//�жϴ����Ƿ�æ
  bool m_bSendData;				//�Ƿ���Ҫ��������
  
  CString m_strCfgFile;           //�ն˲��������ļ�
  CString m_strMcuMapFile;
  CString m_strATFile;
  char    m_cFirstChar;
  SEND_MANNER     m_nSendManner;	         //���ͷ�ʽ
  BOOL    m_bWaitPackage;          //�Ƿ���Ҫ�ȴ���Ӧ��
  
  TEST_STATE    m_nTesterState;      // ���Ե�״̬������ or ����
  int           m_nTesterSeq;		     // ���Ե����к�
  int           m_nTestIndex;		     // �������б��˳���
  
  CView        *UpData_pView;		// ���VIEW,�������ĵ����Թرմ��ĵ�ʱ�á�
  
  CTokenMap     m_McuTokenFile;		// Map File �� MCU
  
  //���ǲ���ʱ���������á�CWND POSTMESSAGE����	
  
protected:	
  CWnd        *Out_pIndi;     //����ָ��
  
  unsigned char  *EXH_Buf;	//���ڷ�������
  CString      port_sInf;  //���������ļ�
  char           *buf_Inner;  
  
  
  DWORD       port_dwBaud;		//������
  int         port_Parity;		//У��λ
  int         port_DataBits;		//����λ
  int         port_StopBits;		//ֹͣλ
  
  
  int           port_Packet;		//����С
  int           port_Bulk;		//ͻ����
  int           port_Mass;		//������
  
  COMMTIMEOUTS  port_toOrg; 
  
  
  CRobinBuffer  port_Buf;     //���ڽ�������
  HANDLE       In_hAllExit;	//�˳��¼�
  HANDLE       In_hTxExit;	//�����˳��¼�
  
  HANDLE		In_hEchoEvt;	//pc->hs����Ļ�Ӧ�¼�
  HANDLE		m_hEvtRecMem;	//���������¼�
  
  CWinThread   *MT_Work;		//�����߳�
  
  
  HANDLE m_hFileDebug;		//���չ����ڴ���
  BYTE * m_pDebug;		    //���չ����ڴ�ָ��
  
  ManageShareMemory m_ManageShareMemory;
  
};

#endif // !defined(AFX_CRYSTALPROTOCOL_H__3086EE19_78DD_46B7_A7DB_6437EF0913F0__INCLUDED_)
