#include "stdafx.h"
#include "editcmd.h"
#include "Borer.h"

#include "Rijndael.h"
#include "BinRes.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "BorerDoc.h"
#include "BorerView.h"

#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <wtypes.h>

#include "DlgRegister.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define UNIQUE_NAME1 "{B753A5D1-3A13-4b85-A618-24767D485AE4}"

#define IDENTIFY_BUFFER_SIZE	512
#define SENDIDLENGTH			sizeof (SENDCMDOUTPARAMS) + IDENTIFY_BUFFER_SIZE
#define FILE_DEVICE_SCSI		0x0000001b
#define IOCTL_SCSI_MINIPORT_IDENTIFY	((FILE_DEVICE_SCSI << 16) + 0x0501)
#define IOCTL_SCSI_MINIPORT 0x0004D008	//  see NTDDSCSI.H for definition
#define IDE_ATAPI_IDENTIFY  0xA1		//  Returns ID sector for ATAPI.
#define IDE_ATA_IDENTIFY    0xEC		//  Returns ID sector for ATA.
#define DFP_RECEIVE_DRIVE_DATA	0x0007c088
#define DFP_GET_VERSION			0x00074080


enum    {ENCRYPT=0,DECRYPT};

WORD serial[256];
DWORD OldInterruptAddress;
DWORDLONG IDTR;

typedef struct _IDSECTOR
{
  USHORT  wGenConfig;
  USHORT  wNumCyls;
  USHORT  wReserved;
  USHORT  wNumHeads;
  USHORT  wBytesPerTrack;
  USHORT  wBytesPerSector;
  USHORT  wSectorsPerTrack;
  USHORT  wVendorUnique[3];
  CHAR    sSerialNumber[20];
  USHORT  wBufferType;
  USHORT  wBufferSize;
  USHORT  wECCSize;
  CHAR    sFirmwareRev[8];
  CHAR    sModelNumber[40];
  USHORT  wMoreVendorUnique;
  USHORT  wDoubleWordIO;
  USHORT  wCapabilities;
  USHORT  wReserved1;
  USHORT  wPIOTiming;
  USHORT  wDMATiming;
  USHORT  wBS;
  USHORT  wNumCurrentCyls;
  USHORT  wNumCurrentHeads;
  USHORT  wNumCurrentSectorsPerTrack;
  ULONG   ulCurrentSectorCapacity;
  USHORT  wMultSectorStuff;
  ULONG   ulTotalAddressableSectors;
  USHORT  wSingleWordDMA;
  USHORT  wMultiWordDMA;
  BYTE    bReserved[128];
} IDSECTOR, *PIDSECTOR;

typedef struct _DRIVERSTATUS
{
  BYTE  bDriverError;		//  Error code from driver, or 0 if no error.
  BYTE  bIDEStatus;		//  Contents of IDE Error register.
  //  Only valid when bDriverError is SMART_IDE_ERROR.
  BYTE  bReserved[2];		//  Reserved for future expansion.
  DWORD  dwReserved[2];	//  Reserved for future expansion.
} DRIVERSTATUS, *PDRIVERSTATUS, *LPDRIVERSTATUS;

typedef struct _SENDCMDOUTPARAMS
{
  DWORD         cBufferSize;   //  Size of bBuffer in bytes
  DRIVERSTATUS  DriverStatus;  //  Driver status structure.
  BYTE          bBuffer[1];    //  Buffer of arbitrary length in which to store the data read from the drive.
} SENDCMDOUTPARAMS, *PSENDCMDOUTPARAMS, *LPSENDCMDOUTPARAMS;

typedef struct _SRB_IO_CONTROL
{
  ULONG HeaderLength;
  UCHAR Signature[8];
  ULONG Timeout;
  ULONG ControlCode;
  ULONG ReturnCode;
  ULONG Length;
} SRB_IO_CONTROL, *PSRB_IO_CONTROL;

typedef struct _IDEREGS
{
  BYTE bFeaturesReg;       // Used for specifying SMART "commands".
  BYTE bSectorCountReg;    // IDE sector count register
  BYTE bSectorNumberReg;   // IDE sector number register
  BYTE bCylLowReg;         // IDE low order cylinder value
  BYTE bCylHighReg;        // IDE high order cylinder value
  BYTE bDriveHeadReg;      // IDE drive/head register
  BYTE bCommandReg;        // Actual IDE command.
  BYTE bReserved;          // reserved for future use.  Must be zero.
} IDEREGS, *PIDEREGS, *LPIDEREGS;

typedef struct _SENDCMDINPARAMS
{
  DWORD	cBufferSize;	//  Buffer size in bytes
  IDEREGS	irDriveRegs;	//  Structure with drive register values.
  BYTE	bDriveNumber;	//  Physical drive number to send
  //  command to (0,1,2,3).
  BYTE	bReserved[3];	//  Reserved for future expansion.
  DWORD	dwReserved[4];	//  For future use.
  BYTE	bBuffer[1];		//  Input buffer.
} SENDCMDINPARAMS, *PSENDCMDINPARAMS, *LPSENDCMDINPARAMS;

typedef struct _GETVERSIONOUTPARAMS
{
  BYTE bVersion;			// Binary driver version.
  BYTE bRevision;			// Binary driver revision.
  BYTE bReserved;			// Not used.
  BYTE bIDEDeviceMap;		// Bit map of IDE devices.
  DWORD fCapabilities;	// Bit mask of driver capabilities.
  DWORD dwReserved[4];	// For future use.
} GETVERSIONOUTPARAMS, *PGETVERSIONOUTPARAMS, *LPGETVERSIONOUTPARAMS;

static unsigned int WaitHardDiskIde()
{
  BYTE xx;
  
Waiting:
  __asm
  {
    mov dx, 0x1f7
      in al, dx
      cmp al, 0x80
      jb Endwaiting
      jmp Waiting
  }
Endwaiting:
    __asm
    {
      mov xx, al
    }
    
    return(xx);
}

// 中断服务程序
void __declspec(naked) InterruptProcess(void)
{
  int   xx;
  int   i;
  WORD temp;
  
  //保存寄存器值
  __asm
  {
    push eax
      push ebx
      push ecx
      push edx
      push esi
  }
  
  WaitHardDiskIde();		//等待硬盘空闲状态
  
  __asm
  {
    mov dx, 0x1f6
      mov al, 0xa0
      out dx, al
  }
  
  xx = WaitHardDiskIde(); //若直接在Ring3级执行等待命令，会进入死循环
  if ((xx&0x50)!=0x50) goto EndIntrrupt;
  
  __asm
  {
    mov dx, 0x1f6	//命令端口1f6,选择驱动器0
      mov al, 0xa0
      out dx, al
      inc dx
      mov al, 0xec
      out dx, al		//发送读驱动器参数命令
  }
  
  xx = WaitHardDiskIde();
  if ((xx&0x58)!=0x58) goto EndIntrrupt;
  
  //读取硬盘控制器的全部信息
  for (i=0;i<256;i++)
  {
    __asm
    {
      mov dx, 0x1f0
        in ax, dx
        mov temp, ax
    }
    serial[i] = temp;
  }
  
EndIntrrupt:
  // 恢复寄存器
  __asm
  {
    pop esi
      pop edx
      pop ecx
      pop ebx
      pop eax
      iretd
  }
}

int Win9xHDSerialNumRead(WORD * buffer)
{
  _asm
  {
    push eax
      
      // 获取修改的中断的中断描述符(中断门)地址
      sidt IDTR
      mov eax, dword ptr [IDTR+02h]
      add eax, 3*08h+04h
      cli
      
      // 保存原先的中断入口地址
      push ecx
      mov ecx, dword ptr [eax]
      mov cx, word ptr [eax-04h]
      mov dword ptr OldInterruptAddress, ecx
      pop ecx
      
      // 设置修改的中断入口地址为新的中断处理程序入口地址
      push ebx
      lea ebx, InterruptProcess 
      mov word ptr [eax-04h], bx
      shr ebx, 10h
      mov word ptr [eax+02h], bx
      pop ebx
      
      // 执行中断，转到Ring 0(类似CIH病毒原理)
      int 3h
      
      // 恢复原先的中断入口地址
      push ecx
      mov ecx, dword ptr OldInterruptAddress
      mov word ptr [eax-04h], cx
      shr ecx,10h
      mov word ptr [eax+02h], cx
      pop ecx
      sti
      pop eax
  }
  memcpy(buffer, serial, 256*2);
  return(1);
}

int WinNTHDSerialNumAsScsiRead(DWORD* buffer)
{
  HANDLE hScsiDriveIOCTL;
  
  // 尝试打开 SCSI0 设备
  hScsiDriveIOCTL = CreateFile("\\\\.\\Scsi0:",
    GENERIC_READ | GENERIC_WRITE,
    FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
    OPEN_EXISTING, 0, NULL);
  
  if (hScsiDriveIOCTL != INVALID_HANDLE_VALUE)
  {
    int drive;
    
    for (drive=0; drive<2; drive++)
    {
      char buffer[sizeof(SRB_IO_CONTROL) + SENDIDLENGTH];
      SRB_IO_CONTROL *p = (SRB_IO_CONTROL *) buffer;
      SENDCMDINPARAMS *pin = (SENDCMDINPARAMS *)(buffer + sizeof(SRB_IO_CONTROL));
      DWORD dummy;
      
      memset (buffer, 0, sizeof(buffer));
      p->HeaderLength = sizeof(SRB_IO_CONTROL);
      p->Timeout = 10000;
      p->Length = SENDIDLENGTH;
      p->ControlCode = IOCTL_SCSI_MINIPORT_IDENTIFY;
      strncpy ((char*)p->Signature, "SCSIDISK", 8);
      
      pin->irDriveRegs.bCommandReg = IDE_ATA_IDENTIFY;
      pin->bDriveNumber = drive;
      
      if (DeviceIoControl(hScsiDriveIOCTL,
								IOCTL_SCSI_MINIPORT,
                buffer,
                sizeof(SRB_IO_CONTROL) + sizeof(SENDCMDINPARAMS) - 1,
                buffer,
                sizeof(SRB_IO_CONTROL) + SENDIDLENGTH,
                &dummy,
                NULL))
      {
        SENDCMDOUTPARAMS *pOut = (SENDCMDOUTPARAMS*)(buffer + sizeof(SRB_IO_CONTROL));
        IDSECTOR *pId = (IDSECTOR*)(pOut->bBuffer);
        if (pId->sModelNumber[0])
        {
          int ijk = 0;
          USHORT *pIdSector = (USHORT*)pId;
          
          for (ijk = 0; ijk < 256; ijk++)
            buffer[ijk] =(char)pIdSector[ijk];
          
          return(1);
        }
      }
    }
    CloseHandle (hScsiDriveIOCTL);
  }
  
  return(-1);
}

BOOL DoIDENTIFY(HANDLE hPhysicalDriveIOCTL,
                PSENDCMDINPARAMS pSCIP,
                PSENDCMDOUTPARAMS pSCOP,
                BYTE bIDCmd,
                BYTE bDriveNum,
                PDWORD lpcbBytesReturned)
{
  // 为 IDENTITY 命令准备初始数据
  pSCIP->cBufferSize = IDENTIFY_BUFFER_SIZE;
  pSCIP->irDriveRegs.bFeaturesReg = 0;
  pSCIP->irDriveRegs.bSectorCountReg = 1;
  pSCIP->irDriveRegs.bSectorNumberReg = 1;
  pSCIP->irDriveRegs.bCylLowReg = 0;
  pSCIP->irDriveRegs.bCylHighReg = 0;
  
  // 计算驱动器号
  pSCIP->irDriveRegs.bDriveHeadReg = 0xA0 | ((bDriveNum & 1) << 4);
  
  // 这个命令能够支持 IDE 或 ATAPI 接口的硬盘
  pSCIP->irDriveRegs.bCommandReg = bIDCmd;
  pSCIP->bDriveNumber = bDriveNum;
  pSCIP->cBufferSize = IDENTIFY_BUFFER_SIZE;
  
  return(DeviceIoControl(hPhysicalDriveIOCTL, DFP_RECEIVE_DRIVE_DATA,
    (LPVOID)pSCIP,
    sizeof(SENDCMDINPARAMS) - 1,
    (LPVOID)pSCOP,
    sizeof(SENDCMDOUTPARAMS) + IDENTIFY_BUFFER_SIZE - 1,
    lpcbBytesReturned, NULL));
}

int WinNTHDSerialNumAsPhysicalRead(DWORD * buffer)
{
  BYTE IdOutCmd[sizeof(SENDCMDOUTPARAMS) + IDENTIFY_BUFFER_SIZE - 1];
  
  int done = FALSE;
  int drive = 0;
  
  HANDLE hPhysicalDriveIOCTL;
  
  // 尝试打开物理驱动器0
  hPhysicalDriveIOCTL = CreateFile("\\\\.\\PhysicalDrive0",
    GENERIC_READ | GENERIC_WRITE,
    FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
    OPEN_EXISTING, 0, NULL);
  
  if (hPhysicalDriveIOCTL != INVALID_HANDLE_VALUE)
  {
    GETVERSIONOUTPARAMS VersionParams;
    DWORD               cbBytesReturned = 0;
    
    // 取版本信息
    memset((void*) &VersionParams, 0, sizeof(VersionParams));
    if (!DeviceIoControl(hPhysicalDriveIOCTL,
      DFP_GET_VERSION,
      NULL,
      0,
      &VersionParams,
      sizeof(VersionParams),
      &cbBytesReturned, NULL))
    {         
      printf ("DFP_GET_VERSION failed for drive\n");
      return(FALSE);
    }
    
    // If there is a IDE device at number "i" issue commands to the device
    if (VersionParams.bIDEDeviceMap > 0)
    {
      BYTE             bIDCmd = 0;   // IDE or ATAPI IDENTIFY cmd
      SENDCMDINPARAMS  scip;
      
      // Now, get the ID sector for all IDE devices in the system.
      // If the device is ATAPI use the IDE_ATAPI_IDENTIFY command,
      // otherwise use the IDE_ATA_IDENTIFY command
      bIDCmd = (VersionParams.bIDEDeviceMap >> drive & 0x10) ? IDE_ATAPI_IDENTIFY : IDE_ATA_IDENTIFY;
      
      memset (&scip, 0, sizeof(scip));
      memset (IdOutCmd, 0, sizeof(IdOutCmd));
      
      if (DoIDENTIFY(hPhysicalDriveIOCTL,
        &scip,
        (PSENDCMDOUTPARAMS)&IdOutCmd,
        (BYTE) bIDCmd,
        (BYTE) drive,
        &cbBytesReturned))
      {
        int ijk = 0;
        USHORT *pIdSector = (USHORT*)((PSENDCMDOUTPARAMS)IdOutCmd)->bBuffer;
        
        for (ijk = 0; ijk < 256; ijk++)
          buffer[ijk] = pIdSector[ijk];
        
        done = TRUE;
      }
    }
    CloseHandle (hPhysicalDriveIOCTL);
  }
  
  return(done);
}

char* Conver2String(WORD* buffer, int begin, int end)
{
  static char str[256];
  int i, j;
  
  // 把返回的 10 - 19 位置的内容转化为字符串
  // 27 - 47
  j = 0;
  for (i=begin;i<=end;i++)
  {
    str[j] = (char)(buffer[i]/256);
    j++;
    str[j] = (char)(buffer[i]%256);
    j++;
  }
  str[j] = 0;
  
  // 删除行尾空格
  i = j - 1;
  while ((str[i] == 0x20) && (i >= 0))
  {
    str[i] = 0;
    i--;
  }
  return(str);
}

// 获得硬盘信息数据
void GetHDData(WORD* hd_data)
{
  DWORD dhd_data[256];
  OSVERSIONINFO OSVersionInfo;
  
  OSVersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
  GetVersionEx(&OSVersionInfo);
  
  // 判别操作系统，决定采用何种方式
  if (OSVersionInfo.dwPlatformId != VER_PLATFORM_WIN32_NT)
  {
    Win9xHDSerialNumRead(hd_data);
  }
  else
  {
    if (!WinNTHDSerialNumAsPhysicalRead(dhd_data))
      WinNTHDSerialNumAsScsiRead(dhd_data);
    
    for (int i=0;i<256;i++) hd_data[i] = (WORD)dhd_data[i];
  }
}

/////////////////////////////////////////////////////////////////////////////
// CBorerApp

BEGIN_MESSAGE_MAP(CBorerApp, CWinApp)
//{{AFX_MSG_MAP(CBorerApp)
ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
//}}AFX_MSG_MAP
// Standard file based document commands
ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
// Standard print setup command
ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
ON_COMMAND_EX_RANGE(ID_FILE_MRU_FILE1, ID_FILE_MRU_FILE16,MyMRUFileHandler)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBorerApp construction
CBorerApp::CBorerApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CBorerApp object
CBorerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CBorerApp initialization
BOOL CBorerApp::InitInstance()
{
  m_hOneInstance = ::CreateMutex(NULL,FALSE,UNIQUE_NAME1);
  if(GetLastError() == ERROR_ALREADY_EXISTS)
  {
    return FALSE;
  }
  
  // Standard initialization
  // If you are not using these features and wish to reduce the size
  //  of your final executable, you should remove from the following
  //  the specific initialization routines you do not need.
  
  // initialized OLE 2.0 libraries
  if (!AfxOleInit())
  {
    AfxMessageBox(IDS_OLE_INIT_FAILED);
    return FALSE;
  }
  
#ifdef _AFXDLL
  Enable3dControls();			// Call this when using MFC in a shared DLL
#else
  Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
  
  // Initialize the interpreter
  if ( G__INIT_CINT_FAILURE == G__init_cint( "cint" ) )
  {	
    AfxMessageBox( "Failed to initialize CINT" );
    return FALSE;
  } // end if
  
  // Change the registry key under which our settings are stored.
  // You should modify this string to be something appropriate
  // such as the name of your company or organization.
  SetRegistryKey(_T("Wetter IT Applications"));
  
  //获取当前程序运行路径
  GetModuleFileName(NULL,m_sAppPath.GetBuffer(_MAX_PATH),_MAX_PATH); 
  m_sAppPath.ReleaseBuffer();
  m_sAppPath =m_sAppPath.Left(m_sAppPath.ReverseFind ('\\') + 1);
  m_sIniFile=m_sAppPath+CWSTR_FLINI;
  /*
  
    #ifndef _DEBUG
    BOOL bDebug = IsDebuggerPresent();
    if(bDebug)
    {
    AfxMessageBox("不能对程序跟踪，程序将退出!");
    return FALSE;
    }
    #endif
    
      #ifdef PDK_PLATFORM
      // 用户鉴权
      if(!Authorizated())
      {
      CreateAuthorFile();
      return FALSE;
      }
      #endif
      
  */
  LoadStdProfileSettings();  // Load standard INI file options (including MRU)
  
  // Register the application's document templates.  Document templates
  //  serve as the connection between documents, frame windows and views.
  
  CMultiDocTemplate* pDocTemplate;
  pDocTemplate = new CMultiDocTemplate(
    IDR_BorerTYPE,
    RUNTIME_CLASS(CBorerDoc),
    RUNTIME_CLASS(CChildFrame), // custom MDI child frame
    RUNTIME_CLASS(CBorerView));
  AddDocTemplate(pDocTemplate);
  
  // create main MDI Frame window
  CMainFrame* pMainFrame = new CMainFrame;
  if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
    return FALSE;
  m_pMainWnd = pMainFrame;
  
  // Enable drag/drop open
  m_pMainWnd->DragAcceptFiles();
  
  // Enable DDE Execute open
  EnableShellOpen();
  RegisterShellFileTypes(TRUE);
  
  // The main window has been initialized, so show and update it.
  pMainFrame->ShowWindow(SW_MAXIMIZE);
  pMainFrame->UpdateWindow();
  
  OpenFormView();
  OpenPrevProject();
  
  return TRUE;
}

//打开测试文档
void CBorerApp::OpenFormView()
{
  CMainFrame  *pMyFrm =(CMainFrame*)AfxGetApp()->m_pMainWnd;//取主框架窗口指针
  CString str;
  for(int i=0;i<pMyFrm->m_aTestInfo.GetSize();i++) 
  {
    str.Format("任务%d:%d-Borer测试",i+1,pMyFrm->m_aTestInfo[i]->m_nTesterSeq);
    OpenJCFormView(str);//根据测试设置任务打开生成相应的FORMVIEW.
  }	
 	
}

// 打开上一次打开的工程

void CBorerApp::OpenPrevProject()
{
  CMainFrame  *pMyFrm =(CMainFrame*)m_pMainWnd;//取主框架窗口指针
  
  ReadIniString(DLT_SEC_RAW,CWFL_PROJECTFILE,CWSTR_DFTSTR,
    pMyFrm->m_treeProject.m_strFileName.GetBuffer(_MAX_PATH),
    _MAX_PATH);
  
  pMyFrm->m_treeProject.m_strFileName.ReleaseBuffer();
  pMyFrm->OpenProject();
 	
}

//打开集成测试文档
void CBorerApp::OpenJCFormView(CString &strname)
{
  // Searches template list for a document type
  // containing the "Hello" string
  POSITION curTemplatePos = GetFirstDocTemplatePosition();
  
  while(curTemplatePos != NULL)
  {
    CDocTemplate* curTemplate =GetNextDocTemplate(curTemplatePos);
    CString strNH;
    curTemplate->GetDocString(strNH, CDocTemplate::docName);
    
    if(strNH == _T("Borer"))
    {
      //	OnFileNew
      curTemplate->OpenDocumentFile(strname);
      //	curTemplate->CreateNewDocument();
      //	}
      return;
    }
  }
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
  CAboutDlg();
  
  // Dialog Data
  //{{AFX_DATA(CAboutDlg)
  enum { IDD = IDD_ABOUTBOX };
  //}}AFX_DATA
  
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CAboutDlg)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL
  
  // Implementation
protected:
  //{{AFX_MSG(CAboutDlg)
		// No message handlers
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
  //{{AFX_DATA_INIT(CAboutDlg)
  //}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CAboutDlg)
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//{{AFX_MSG_MAP(CAboutDlg)
// No message handlers
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CBorerApp::OnAppAbout()
{
  CAboutDlg aboutDlg;
  aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CBorerApp commands
int CBorerApp::ExitInstance() 
{
  CloseHandle(m_hOneInstance);	
  
  // Release CINT
  G__scratch_all();
  
  return CWinApp::ExitInstance();
}

BOOL CBorerApp::MyMRUFileHandler(UINT nID)
{
  ASSERT_VALID(this);
  ASSERT(m_pRecentFileList != NULL);
  
  ASSERT(nID >= ID_FILE_MRU_FILE1);
  ASSERT(nID < ID_FILE_MRU_FILE1 + (UINT)m_pRecentFileList->GetSize());
  int nIndex = nID - ID_FILE_MRU_FILE1;
  ASSERT((*m_pRecentFileList)[nIndex].GetLength() != 0);
  
  TRACE2("MRU: open file (%d) '%s'.\n", (nIndex) + 1,
    (LPCTSTR)(*m_pRecentFileList)[nIndex]);
  
  CMainFrame  *pMyFrm1 =(CMainFrame*)AfxGetApp()->m_pMainWnd;//取主框架窗口指针
  
  CFrameWnd *pMyFrm=((CMainFrame*)AfxGetMainWnd())->GetActiveFrame();
  if(!pMyFrm)
  {
    return 0;
  }
  
  CView *pMyView=pMyFrm->GetActiveView();
  if(!pMyView) 
  {
    return 0;
  }
  
  CBorerDoc  *pMyDoc=(CBorerDoc*) pMyView->GetDocument();
  
  pMyDoc->m_xTextBuffer.FreeAll();
  pMyDoc->m_xTextBuffer.LoadFromFile((*m_pRecentFileList)[nIndex]);
  pMyDoc->SetPathName((*m_pRecentFileList)[nIndex]);
  
  CString strSec;
  strSec.Format("%s%d",CW_ITCOMSEC,pMyFrm1->m_aTestInfo[pMyDoc->m_nPortIndex]->m_nTesterSeq);
  WriteIniString(strSec,"DOCNAME",(*m_pRecentFileList)[nIndex]);
  
  return TRUE;
} 

bool Des_Go(char *Out,char *In,long datalen,const char *Key,int keylen,bool Type = ENCRYPT);

BOOL CBorerApp::Authorizated()
{
  CFile fFile ;
  char strBuf[29]  ;
  memset(strBuf,0,29);
  int nBufLen =0 ;
  char strKey[]={0,2,0,0,9,3,5,1,9,8,0,0,9,1,7} ;
  
  if( !fFile.Open( theApp.m_sAppPath + "Revert.lic", 
    CFile::modeRead | CFile::typeBinary) )
  {
    return FALSE;
  }
  
  fFile.Read(strBuf,28) ;
  nBufLen = strlen(strBuf);
  if(nBufLen < 1)
  {
    return FALSE;
  }
  fFile.Close();
  
  Des_Go(strBuf, strBuf, nBufLen, strKey, sizeof(strKey), DECRYPT);
  
  if(nBufLen == 28) // 注册日期和有效日期
  {
    // 取系统时间
    char strResponsedate[9];
    char strValidDay[4];
    memset(strResponsedate,0,9);
    memset(strValidDay,0,4);
    
    CTime tNowTime = CTime::GetCurrentTime();
    memcpy(strResponsedate,strBuf+8,8);
    memcpy(strValidDay,strBuf+16,3);
    
    CString strTime = strResponsedate;
    CTime tRespTime(atoi(strTime.Mid(0,4)),atoi(strTime.Mid(4,2)), atoi(strTime.Mid(6,2)),0,0,0);
    
    CTimeSpan ts = tNowTime - tRespTime; 
    int aa = ts.GetDays() ;
    int bb = atoi(strValidDay);
    if(ts.GetDays() > atoi(strValidDay))
    {
      return FALSE;
    }
  }
  
  // 取硬盘的序列号
  WORD hd_data[256];
  GetHDData(hd_data);
  // 返回数据的第 10 - 19 是硬盘的序列号信息
  
  char *strHardwareSerial= new char[9];
  memset(strHardwareSerial,0,9);
  strHardwareSerial = Conver2String(hd_data, 10, 19);
  if(strlen(strHardwareSerial) == 0)
  {
    memset(strHardwareSerial,'0',8);
  }
  
  int i=0 ;
  for(i=0;i < 8;i++)
  {
    if(strHardwareSerial[i] == strBuf[i])
    {
      continue;
    }
    else
    {
      break;
    }
  }
  
  if(i == 8)
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
  delete []strHardwareSerial;
}

void CBorerApp::CreateAuthorFile()
{
  // 取硬盘的序列号
  WORD hd_data[256];
  GetHDData(hd_data);
  // 返回数据的第 10 - 19 是硬盘的序列号信息
  char *strHardwareSerial= new char[9];
  memset(strHardwareSerial,0,9);
  char strSystemdate[9] ;
  strHardwareSerial = Conver2String(hd_data, 10, 19);
  if(strlen(strHardwareSerial) == 0)
  {
    memset(strHardwareSerial,'0',8);
  }
  
  // 取系统时间
  SYSTEMTIME st;
  GetSystemTime(&st); 
  sprintf(strSystemdate,"%4d%02d%02d",st.wYear,st.wMonth,st.wDay) ;
  
  char strKey[]={0,2,0,0,9,3,5,1,9,8,0,0,9,1,7} ;
  char strBuf[17]  ;
  memset(strBuf,0,17);
  strcat(strBuf,strHardwareSerial) ;
  strcat(strBuf,strSystemdate) ;
  
  int i=0 ;
  
  for(i=0;i<16;i++)
  {
    strBuf[i] = strBuf[i] ^ 80 ;
  }
  
  CString strCurRegInfo = ShowRegisterInfo();
  if(strCurRegInfo.GetLength() <1)
  {
    AfxMessageBox("您还有完成注册，请注册!") ;
    return;
  }
  
  CStdioFile fFile;
  if( !fFile.Open( theApp.m_sAppPath + "Selfsow.lic", 
    CFile::modeCreate | CFile::modeWrite | CFile::typeBinary ) )
  {
    AfxMessageBox("不能写入文件!") ;
    return;
  }
  fFile.Write(strBuf,16);
  int nRegLength = strCurRegInfo.GetLength() ;
  if(nRegLength > 0)
  {
    char * strRegister = new char[nRegLength + 2] ;
    memset(strRegister,0,nRegLength + 2);
    memcpy(strRegister,strCurRegInfo.GetBuffer(nRegLength),nRegLength) ;
    
    for(i=0;i<nRegLength;i++)
    {
      strRegister[i] = strRegister[i] ^ 80 ;
    }
    
    fFile.Write(strRegister,nRegLength);
    delete []strRegister;
  }
  fFile.Close() ;
  delete []strHardwareSerial;
}

CString CBorerApp::ShowRegisterInfo()
{
  CDlgRegister CdlgReg ;
  CString strCurRegInfo = _T("");
  CFile fFile ;
  if( !fFile.Open( theApp.m_sAppPath + "Selfsow.lic", 
    CFile::modeRead | CFile::typeBinary) )
  {
    if(CdlgReg.DoModal() == IDOK)
    {
      strCurRegInfo.Format("`%s`%s`%s`%s",CdlgReg.m_strName,CdlgReg.m_strCompany,CdlgReg.m_strTelephone,CdlgReg.m_strMail);
      return strCurRegInfo ;
    }
    else
    {
      return strCurRegInfo ;
    }
  }
  
  DWORD dwFileLen = fFile.GetLength() ;
  int nRegLength = dwFileLen - 16 ;
  if(nRegLength < 1)
  {
    AfxMessageBox("文件不正确!");
    return strCurRegInfo;
  }
  
  // 读取以前的注册信息
  fFile.Seek( 16, CFile::begin );
  char * strRegister = new char[nRegLength+2] ;
  memset(strRegister,0,nRegLength+2) ;
  fFile.Read(strRegister,nRegLength) ;
  fFile.Close();
  
  // 分析注册信息
  int i=0 ;
  int nBeginPos = 0 ;
  int nEndPos = 0;
  CString strName = _T("") ;
  CString strCompany = _T("") ;
  CString strTelephone = _T("") ;
  CString strMail = _T("") ;
  CString strSql = _T("") ;
  BOOL bFindBegin = FALSE;
  BOOL bFindEnd = FALSE;
  int k = 0;
  int j = 0;
  
  for(i=1;i<nRegLength;i++)
  {
    if(! bFindBegin)
    {
      nBeginPos = i ;
      bFindBegin = TRUE ;
    }
    strRegister[i] = strRegister[i] ^ 80 ;
    if((strRegister[i] == '`') || (i==nRegLength-1))
    {
      nEndPos  = i ;
      bFindEnd = TRUE ;
    }
    
    if(bFindBegin && bFindEnd)
    {
      switch(k) 
      {
      case 0:
        for(j=nBeginPos;j<nEndPos;j++)
        {
          strName += strRegister[j] ;
        }
        break;
      case 1:
        for(j=nBeginPos;j<nEndPos;j++)
        {
          strCompany += strRegister[j] ;
        }
        break;
      case 2:
        for(j=nBeginPos;j<nEndPos;j++)
        {
          strTelephone += strRegister[j] ;
        }
        break;
      case 3:
        for(j=nBeginPos;j<=nEndPos;j++)
        {
          strMail += strRegister[j] ;
        }
        break;
      default:
        break;
      }
      k++;
      bFindBegin = FALSE ;
      bFindEnd = FALSE;
    }
  }
  
  CdlgReg.m_strName = strName ;
  CdlgReg.m_strCompany = strCompany ;
  CdlgReg.m_strTelephone = strTelephone ;
  CdlgReg.m_strMail = strMail ;
  
  if(CdlgReg.DoModal() == IDOK)
  {
    strCurRegInfo.Format("`%s`%s`%s`%s",CdlgReg.m_strName,CdlgReg.m_strCompany,CdlgReg.m_strTelephone,CdlgReg.m_strMail);
  }
  
  return strCurRegInfo;
}

