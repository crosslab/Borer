#ifndef _COMMON_LLL_H_
#define _COMMON_LLL_H_
#include "memmap.h"

#include <afxdao.h>
//class CReviewDoc;
class CGrfData;

#define DRAW_HORZ_POINTS        4096
#define DRAW_DIVISOR_BUOY       32
const int	CWSZ_VBBUF     =8192;
#define SM_TABNAME    "TabName%d"

#define CWFMT_COL0          "    "
const int	WIDTH_NMCOL    =80;
const int	WIDTH_HDCOL    =0;

#define MBSTR_DIMOPEN         "δ�ܴ򿪣�"
const int	SM_LST_HIDE    =-2;
const int	SM_LST_SHOW    =-4;

const int	CWMM_OPEN_NOTIFY   = WM_USER + 0x0104;	//���͸����ڵ���ʾ��Ϣ
const int	CWMM_CLOSE_NOTIFY  = WM_USER + 0x0105;	//���͸����ڵ���ʾ��Ϣ
const int	CWMM_SAVE_NOTIFY   = WM_USER + 0x0106;	//���͸����ڵ���ʾ��Ϣ
const int	CWMM_SAVEAS_NOTIFY = WM_USER + 0x0107;	//���͸����ڵ���ʾ��Ϣ
const int	CWMM_IMPORT_NOTIFY = WM_USER + 0x0108;	//���͸����ڵ���ʾ��Ϣ


#define LISTR_CLUE            "codeindex"
#define MDBSTR_MCUFLD         "MCUContent"
#define MDBSTR_TMFLD          "TestTime"
#define MDBSTR_LATITUDE       "Latitude"
#define MDBSTR_LONGITUDE      "Longitude"
#define MDBSTR_SPEED          "Speed"


#define HSMN_VEITEM   "HEItem"
#define HSMN_VWCNT    "HMVwCnt"
#define HSMN_VWITEM   "HMVwItem"

#define HSMN_VINAME   "HMVIName"
#define HSMN_VITYPE   "HMVIType"
#define HSMN_VIEXPR   "HMVIeExpr"

#define HSMN_VOBYTE   "HMVoByte"
#define HSMN_VOBIT    "HMVoBit"

#define HSMN_VIMIN    "HMVIMin"
#define HSMN_VIMAX    "HMVIMax"

#define HSMN_VILEN    "HMViLen"
#define HSMN_CHART    "HMVDkTab"
#define HSMN_TINT     "HMVvTint"
#define HSMN_OPEN     "HMVvOpen"
#define HSMN_VIENUM   "HMViEnum"
#define HSMN_VSState  "HMSubState"
#define HSMN_VSMemo   "HMSubMemo"

#define MBSTR_CFGLOST         "δ�ҵ������ļ�%s!"
#define MBSTR_RAWMARK         "***"
#define MBSTR_READONLY        "�����ļ�%s����д��!"

const int	MMM_LIST_ORDER     = WM_USER + 0x0004;	//���͸����ڵ���ʾ��Ϣ


typedef enum _HS2003_RvwDataTpye {
  SD_NONE=0,
    SD_TXT=1,
    SD_MDB=2,
    SD_DBF=3,
}RS_TYPE;

typedef enum _HsTestDatatypes {
  DT_BIT=0,
    DT_BYTE=1,
    DT_WORD=2,
    DT_DWD=3,
    DT_UF16=4,
    DT_F16=5,
    DT_UF32=6,
    DT_F32=7,
}CM_DATA;

typedef struct _HstViewItem {  
  CString  vi_Name;     //����Ŀ����
  CString  vi_Express;  //��ǿգ�����Ŀֵ�ɴ˱��ʽ����
  
  CString  vi_Chart;    //��ǿգ�����Ŀ���ߵ�ͼ�Ĵ���λ�ã�
  //�硰0,2����ʾ��λ�ڵ�һͼ�Ĵ��ڵĵ�����ǩҳ
  CString  vi_Tint;
  CString  vs_Open;
  bool     vb_Airy;
  
  CM_DATA vi_Type;     //����Ŀ���ͣ��硰BYTE������WORD��
  int     vi_Lenght;    //����Ŀ����
  
  int     Start_Byte;   //����Ŀ�����ݰ��Ŀ�ʼλ��
  int     Start_Bit;
  
  int     vi_cStates;    //����Ŀ״̬��
  DWORD   vi_Value[32];  //����Ŀ�Ϸ�ֵ
  CString vi_Memo[32];   //����Ŀ�Ϸ�ֵ�Ľ���
  
  CString  vi_Min;       //����Ŀ���ֵ
  CString  vi_Max;       //����Ŀ��Сֵ
  
  int    ii_Min;       //����Ŀ���ֵ
  int    ii_Max;       //����Ŀ��Сֵ
  CGrfData  *vi_Propel;   //����Ŀ���ݽ��Ͳ������������͡�ͼ�Ĵ��ڴ�С��
  int        vi_InrNo;    //����Ŀ����������
}HSM_ITEM;


//Error functions
void  ErrorReporter(char * szMessage);
DWORD ErrorExtender(DWORD, char **);
void  ErrorInComm( char * szMessage);

BYTE BCRC(BYTE* BArray,int Start,int Length);//CRC��֤������ȡ���

void FillComboBox(HWND hCtrlWnd,char ** szString,WORD wTableLen,
                  DWORD dwCurrentSetting  );
bool ConfigFileRead(CString &frFile,int &cfCol,HSM_ITEM *cfCfg);

UINT AFX_CDECL ReaderProc( LPVOID );

void closeDatabase(CDaoDatabase **ppDatabase);

int  openDatabase(CDaoDatabase **ppDatabase, CString fileName,
                  BOOL bReportNoOpen = TRUE);

BOOL createDatabase(CDaoDatabase **ppDatabase, CString fileName,
                    int dwOptions = 0);

BOOL createNewTableDef(CDaoDatabase * pDatabase,
                       CDaoTableDef **ppTableDef,
                       CString strTableName);
BOOL appendTableDef(CDaoDatabase *pDatabase, CDaoTableDef *pTableDef);

void AfxSplitPath(const CString& sPath, CString& sTitle, CString& sDir);

void deleteTable(CDaoDatabase *pDatabase, CString strTableName);
BOOL createNewField(CDaoTableDef *pTableDef, CDaoFieldInfo *pFieldInfo);
BOOL deleteField(CDaoTableDef *pTableDef, CString strFieldName);

void setTypeDependentStates(CDaoFieldInfo &infFld);
void SetFieldInfo(CDaoFieldInfo &infFld,HSM_ITEM *lpCtrl);
void fieldInitializer(CDaoFieldInfo &infFld);

void ConcoctTime(CDaoFieldInfo &infFld);
void ConcoctMcu(CDaoFieldInfo &infFld);
void ConcoctClue(CDaoFieldInfo &infFld);
void ConcoctLatitude(CDaoFieldInfo &infFld);
void ConcoctLongitude(CDaoFieldInfo &infFld);
void ConcoctSpeed(CDaoFieldInfo &infFld);
void ConcoctMCUMDM(CDaoFieldInfo &infFld);

bool AlreadyBe(CStringArray &arySire,CString &strTip);
bool AllIsDigit(CString &strTip);
int  GetFileLength(CString &strFile);

void SM_W2A(COleVariant &oleVal,double &flCpr,CString &strCpr);
bool OleParser(HSM_ITEM *opInfo,COleVariant &oleVal,
               double &flCpr,CString &strCpr);

bool ColParser(HSM_ITEM *cpInfo,unsigned char *cpBuf,
               double &flCpr,CString &strCpr);
bool RefParser(HSM_ITEM *rpInfo,double *lpBeen,double &flCpr,
               CString &strInner);
CString FlatterUser(HSM_ITEM *rpInfo,CString &strInner,double flCpr,
                    LV_DISPINFO *lvDisp=NULL);

int  DecipherTypes(char *strType);
COLORREF DecipherColour(CString &strType);
void VariantToStr(COleVariant &var,CString &str);
void ReadFileInfo(CString &filename,CString &titlename,CStringArray &strArray);//��ȡ���ݿ��ļ������Ϣ

extern char * gbl_szParity[];
extern char * gbl_szBaud[];
extern char * gbl_szStopBits[];

extern DWORD   BaudTable[];
extern char    ParityTable[];
extern char    StopBitsTable[];

extern DWORD   DTRControlTable[];
extern DWORD   RTSControlTable[];

extern char *aryProduct[];
extern char *aryVisible[];


#endif