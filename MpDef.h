#ifndef _COMMON_LL_H_
#define _COMMON_LL_H_

//Э�������
const int	HEAD_1st			= 0xeb;
const int	HEAD_2nd			= 0xa8;

const int	ITEM_SHAKEHAND		= 0x55; //����
const int	ITEM_BOOTMOBILE		= 0x77;	//�����ֻ������ֻ�
const int	ITEM_EXCH_INFO		= 0x80; //������Ϣ

#define KEY_KEEP   0X80
#define KEY_DOWN   0X00
#define KEY_UP     0X40

#define CWSTR_M2APP   "Mdm2Test"
#define CWSTR_FLINI   "ItPdk.ini"
#define DLT_SEC_RAW    "DltExRaw"

#define CMINI_BUFFER   "M2inibuf"
#define CMINI_PKTSZ    "M2inipkt"
#define CMINI_BULKPKT  "M2iniblk"

#define CMINI_DFTALL        "512"
#define CMINI_DFTPKT        "256"  //������BYTE

#define CWSTR_DFTNEG         "-1"
#define CWSTR_DFTINT         "0"
#define CWSTR_DFTSTR         ""
#define CWSTR_SPACE          " "
#define CWSTR_DFTTRUE        "1"
#define CWSTR_DFTDATA        "3"
#define CWSTR_DFTXON         "17"
#define CWSTR_DFTXOFF        "19"


#define DQTIP_GETDATA    "��������..."
#define DQTIP_SETDATA    "д������..."
#define DQTIP_SAVEAS    "���浽�ļ�..."
#define DQTIP_BROWS    "���..."
#define DQTIP_OK        "Ӧ������..."
#define DQTIP_CANCEL    "�رնԻ���..."

#define  MBSTR_USERNAMESHORT   "�û���̫��!"
#define  MBSTR_PWSHORT   "����̫��!"
#define  MBSTR_NOUSER    "�û����������벻��ȷ!"
#define  MBSTR_PWCF      "���벻һ�£�"
#define  MBSTR_LONGNM    "�����뵥λ���ƣ�"
#define  MBSTR_EXEBRS    "�����ļ����ɶ���"

#define MAX_WRITE_BUFFER        2048
#define MAX_READ_BUFFER         2048

#define WriteIniString(v1,v2,v3)  WritePrivateProfileString(v1,v2,v3,theApp.m_sIniFile)
#define ReadIniString(v1,v2,v3,v4,v5)  GetPrivateProfileString(v1,v2,v3,v4,v5,theApp.m_sIniFile)
#define ReadIniInt(v1,v2,v3)   GetPrivateProfileInt(v1,v2,v3,theApp.m_sIniFile)


typedef enum _DltPortStages {
  PS_IDEL=1,
    PS_LINKING=2,
    PS_RIGGING=3,
    PS_FIXED=4,
    PS_WORKING=5,
}PS_STATE2;

//Error functions
void  ErrorReporter(char * szMessage);
void  ErrorInComm( char * szMessage);
DWORD ErrorExtender(DWORD, char **);

LPVOID DltAlloc(int daSize);
void   DltFree(LPVOID lpMemory);

bool   AllIsDigit(CString &strTip);
bool   CheckHexData(CString &snumber);
bool   IsFixedHex(CString &strTip,int lenTip);

bool   IsFileSame(CString &strBob,unsigned char *lpMcu,DWORD cMcu);
bool   IsNeglected(CString &strTip,char chNeg);

bool PurgeFile(LPTSTR szReplaced);
bool PurgeFile(CString &szReplaced);

BYTE RTNCRC(BYTE* BArray,int Start,int Length);//CRC��֤������ȡ���

void FillComboBox(HWND hCtrlWnd,char ** szString,WORD wTableLen,
                  DWORD dwCurrentSetting  );

void PcTrace(char *mmm,void *msppp);
void VcTrace(char *mmm,void *msppp);
int PcComSerial(void *msppp);
int PcTraceInfo(void *msppp);
bool Ravelout(CString &roIni,CString &roWif);

extern char * gbl_szParity[];
extern char * gbl_szBaud[];
extern char * gbl_szStopBits[];

extern DWORD   BaudTable[];
extern char    ParityTable[];
extern char    StopBitsTable[];

extern DWORD   DTRControlTable[];
extern DWORD   RTSControlTable[];

#endif
