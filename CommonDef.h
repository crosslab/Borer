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

#define MBSTR_DIMOPEN         "未能打开！"
const int	SM_LST_HIDE    =-2;
const int	SM_LST_SHOW    =-4;

const int	CWMM_OPEN_NOTIFY   = WM_USER + 0x0104;	//发送给窗口的提示信息
const int	CWMM_CLOSE_NOTIFY  = WM_USER + 0x0105;	//发送给窗口的提示信息
const int	CWMM_SAVE_NOTIFY   = WM_USER + 0x0106;	//发送给窗口的提示信息
const int	CWMM_SAVEAS_NOTIFY = WM_USER + 0x0107;	//发送给窗口的提示信息
const int	CWMM_IMPORT_NOTIFY = WM_USER + 0x0108;	//发送给窗口的提示信息


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

#define MBSTR_CFGLOST         "未找到配置文件%s!"
#define MBSTR_RAWMARK         "***"
#define MBSTR_READONLY        "配置文件%s不能写入!"

const int	MMM_LIST_ORDER     = WM_USER + 0x0004;	//发送给窗口的提示信息


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
  CString  vi_Name;     //此条目名称
  CString  vi_Express;  //如非空，此条目值由此表达式计算
  
  CString  vi_Chart;    //如非空，此条目曲线的图文窗口位置，
  //如“0,2”表示其位于第一图文窗口的第三标签页
  CString  vi_Tint;
  CString  vs_Open;
  bool     vb_Airy;
  
  CM_DATA vi_Type;     //此条目类型，如“BYTE”、“WORD”
  int     vi_Lenght;    //此条目长度
  
  int     Start_Byte;   //此条目在数据包的开始位置
  int     Start_Bit;
  
  int     vi_cStates;    //此条目状态数
  DWORD   vi_Value[32];  //此条目合法值
  CString vi_Memo[32];   //此条目合法值的解释
  
  CString  vi_Min;       //此条目最大值
  CString  vi_Max;       //此条目最小值
  
  int    ii_Min;       //此条目最大值
  int    ii_Max;       //此条目最小值
  CGrfData  *vi_Propel;   //此条目数据解释参数，依其类型、图文窗口大小等
  int        vi_InrNo;    //此条目在数组的序号
}HSM_ITEM;


//Error functions
void  ErrorReporter(char * szMessage);
DWORD ErrorExtender(DWORD, char **);
void  ErrorInComm( char * szMessage);

BYTE BCRC(BYTE* BArray,int Start,int Length);//CRC验证函数（取异或）

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
void ReadFileInfo(CString &filename,CString &titlename,CStringArray &strArray);//读取数据库文件相关信息

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