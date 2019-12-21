#include "stdafx.h"
#include "Borer.h"
#include "CommInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int	CWCNT_Parities =5;
const int	CWCNT_Bauds    =15;
const int	CWCNT_Stops    =3;

void FillComboBox( HWND hCtrlWnd,char ** szString,WORD wTableLen,
                  DWORD dwCurrentSetting)
{
  WORD wCount,wPosition ;
  
  for (wCount = 0; wCount < wTableLen; wCount++) {
    wPosition = LOWORD( SendMessage( hCtrlWnd,CB_ADDSTRING,0,
      (LPARAM) (LPSTR) szString[wCount])) ;
    
  }
  
  SendMessage( hCtrlWnd,CB_SETCURSEL,(WPARAM) dwCurrentSetting,0L) ;
  return ;
}

/////////////////////////////////////////////////////////////////////////////
// CCommInfo dialog
CCommInfo::CCommInfo(CWnd* pParent /*=NULL*/)
: CDialog(CCommInfo::IDD, pParent)
{
  //{{AFX_DATA_INIT(CCommInfo)
  II_baud = -1;
  II_dbits = -1;
  II_parities = -1;
  II_sbits = -1;
  //}}AFX_DATA_INIT
}


void CCommInfo::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CCommInfo)
  DDX_Control(pDX, IDPS_SIZE, DP_pkt);
  DDX_Control(pDX, IDPS_BULK, DP_bulk);
  DDX_Control(pDX, IDPS_BUFFER, DP_mass);
  DDX_Control(pDX, IDC_STOPBITSCOMBO, CI_sbits);
  DDX_Control(pDX, IDC_BAUDCOMBO, CI_baud);
  DDX_Control(pDX, IDC_DATABITSCOMBO, CI_dbits);
  DDX_Control(pDX, IDC_PARITYCOMBO, CI_parities);
  DDX_CBIndex(pDX, IDC_BAUDCOMBO, II_baud);
  DDX_CBIndex(pDX, IDC_DATABITSCOMBO, II_dbits);
  DDX_CBIndex(pDX, IDC_PARITYCOMBO, II_parities);
  DDX_CBIndex(pDX, IDC_STOPBITSCOMBO, II_sbits);
  //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCommInfo, CDialog)
//{{AFX_MSG_MAP(CCommInfo)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommInfo message handlers
BOOL CCommInfo::OnInitDialog() 
{
  CDialog::OnInitDialog();
  
  FillComboBox(CI_baud.m_hWnd,gbl_szBaud,CWCNT_Bauds,
    II_baud);
  FillComboBox(CI_sbits.m_hWnd,gbl_szStopBits,CWCNT_Stops,
    II_sbits);
  FillComboBox(CI_parities.m_hWnd,gbl_szParity,CWCNT_Parities,
    II_parities);
  
  // fill data bits combo box and make initial selection
  int   wCount;
  char  szBuffer[256];
  
  sprintf(szBuffer,"¶Ë¿ÚÉèÖÃ COM%d",CUE_port);//""""""""""""""
  SetWindowText(szBuffer);
  
  for(wCount = 5; wCount < 9; wCount++) {
    wsprintf( szBuffer, "%d", wCount ) ;
    CI_dbits.AddString(szBuffer);
  }
  CI_dbits.SetCurSel(II_dbits);
  
  DP_pkt.SetRange(1, 4096);
  DP_pkt.SetBase(10);
  DP_pkt.SetPos(II_pkt);
  
  DP_mass.SetRange(24, 1024);
  DP_mass.SetBase(10);
  DP_mass.SetPos(II_mass);
  
  DP_bulk.SetRange(1, 128);
  DP_bulk.SetBase(10);
  DP_bulk.SetPos(II_bulk);
  
  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}

void CCommInfo::OnOK() 
{	 
  UpdateData();
	 
  II_pkt=DP_pkt.GetPos();
  II_bulk=DP_bulk.GetPos();
  II_mass=DP_mass.GetPos();
  CDialog::OnOK();
}
