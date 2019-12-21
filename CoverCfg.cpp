// CoverCfg.cpp : implementation file
//

#include "stdafx.h"
#include "Borer.h"
#include "CoverCfg.h"
#include "CommonDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCoverCfg dialog


CCoverCfg::CCoverCfg(CWnd* pParent /*=NULL*/)
: CDialog(CCoverCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCoverCfg)
	m_sCfgName = _T("");
	m_sMapFile = _T("");
	m_nPwr = 80;
	m_nSnr = 7;
	m_nSaveTime = 60;
	m_sHOFile = _T("");
	m_sPUFile = _T("");
	m_sReleaseFile = _T("");
	m_sCfgNameMCU = _T("");
	m_nWarnTime = 0;
	m_sNoDataFile = _T("");
	m_sChangeFreqFile = _T("");
	m_sScanFreqFile = _T("");
	//}}AFX_DATA_INIT
}


void CCoverCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCoverCfg)
	DDX_Text(pDX, IDE_CFG_FILE, m_sCfgName);
	DDX_Text(pDX, IDE_MAP_FILE, m_sMapFile);
	DDX_Text(pDX, IDC_EDIT_PWR, m_nPwr);
	DDV_MinMaxInt(pDX, m_nPwr, 1, 99999);
	DDX_Text(pDX, IDC_EDIT_SNR, m_nSnr);
	DDV_MinMaxInt(pDX, m_nSnr, 1, 99999);
	DDX_Text(pDX, IDC_EDIT_SAVEFILE, m_nSaveTime);
	DDV_MinMaxInt(pDX, m_nSaveTime, 1, 99999);
	DDX_Text(pDX, IDE_HO_FILE, m_sHOFile);
	DDX_Text(pDX, IDE_PU_FILE, m_sPUFile);
	DDX_Text(pDX, IDE_RELEASE_FILE, m_sReleaseFile);
	DDX_Text(pDX, IDE_CFG_FILEMCU, m_sCfgNameMCU);
	DDX_Text(pDX, IDC_EDIT_WARNTIME, m_nWarnTime);
	DDV_MinMaxInt(pDX, m_nWarnTime, 1, 999999999);
	DDX_Text(pDX, IDE_NODATA_WARNFILE, m_sNoDataFile);
	DDX_Text(pDX, IDE_CHANGFREQ_FILE, m_sChangeFreqFile);
	DDX_Text(pDX, IDE_SCANFREQ_FILE, m_sScanFreqFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCoverCfg, CDialog)
//{{AFX_MSG_MAP(CCoverCfg)
ON_BN_CLICKED(IDC_HC_CFBRS, OnHcCfbrs)
ON_BN_CLICKED(IDC_MAP_CFBRS, OnMapCfbrs)
ON_BN_CLICKED(IDC_HC_CONFIG, OnHcConfig)
ON_BN_CLICKED(IDC_MAP_CONFIG, OnMapConfig)
ON_BN_CLICKED(IDC_HO_CFBRS, OnHoCfbrs)
ON_BN_CLICKED(IDC_PU_CFBRS, OnPuCfbrs)
ON_BN_CLICKED(IDC_RELEASE_CFBRS, OnReleaseCfbrs)
ON_BN_CLICKED(IDC_HC_CFBRSMCU, OnHcCfbrsmcu)
ON_BN_CLICKED(IDC_HC_CONFIGMCU, OnHcConfigmcu)
ON_BN_CLICKED(IDC_NODATA_CFBRS, OnNodataCfbrs)
	ON_BN_CLICKED(IDC_SCANFREQ_CFBRS, OnScanfreqCfbrs)
	ON_BN_CLICKED(IDC_CHANGEFREQ_CFBRS, OnChangefreqCfbrs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCoverCfg message handlers
//配置文件
void CCoverCfg::OnHcCfbrs() 
{
	UpdateData(true);
	
    CFileDialog dlg(true,"","",NULL,"Txt Files (*.Txt)|*.Txt|Xml Files (*.Xml)|*.Xml|All Files (*.*)|*.*||");
	
	if(dlg.DoModal() == IDOK)
	{
		m_sCfgName = dlg.GetPathName();
		UpdateData(false);
	}	
}

//映射文件
void CCoverCfg::OnMapCfbrs() 
{
	CFileDialog dlg(true,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,_T("INI file|*.INI||"),NULL);
	if(dlg.DoModal()==IDOK)
	{
		m_sMapFile=dlg.GetPathName();
		UpdateData(false);	
	}	
}

//设置配置文件配置内容
void CCoverCfg::OnHcConfig() 
{
	CFlatEditDlg dlgEC;
	UpdateData(true);
	dlgEC.FE_file=m_sCfgName;
	dlgEC.FE_fix=true;
	
	dlgEC.DoModal();	
}

//设置映射文件内容
void CCoverCfg::OnMapConfig() 
{
	UpdateData(true);
	CDlgEditMap dlgMap;
	dlgMap.m_sReadFileName=m_sMapFile;
	dlgMap.DoModal();	
}

//切换报警文件
void CCoverCfg::OnHoCfbrs() 
{
	CFileDialog dlg(true,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,_T("WAV file|*.WAV||"),NULL);
	if(dlg.DoModal()==IDOK)
	{
		m_sHOFile=dlg.GetPathName();
		UpdateData(false);	
	}	
}

//位置报警文件
void CCoverCfg::OnPuCfbrs() 
{
	CFileDialog dlg(true,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,_T("WAV file|*.WAV||"),NULL);	
	if(dlg.DoModal()==IDOK)
	{
		m_sPUFile=dlg.GetPathName();
		UpdateData(false);	
	}		
}

//断链报警文件
void CCoverCfg::OnReleaseCfbrs() 
{
	CFileDialog dlg(true,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,_T("WAV file|*.WAV||"),NULL);
	if(dlg.DoModal()==IDOK)
	{
		m_sReleaseFile=dlg.GetPathName();
		UpdateData(false);	
	}		
}

void CCoverCfg::OnHcCfbrsmcu() 
{
	UpdateData(true);
	
    CFileDialog dlg(true,"","",NULL,"Txt Files (*.Txt)|*.Txt|Xml Files (*.Xml)|*.Xml|All Files (*.*)|*.*||");
	
	if(dlg.DoModal() == IDOK)
	{
		m_sCfgNameMCU = dlg.GetPathName();
		UpdateData(false);
	}	
}

void CCoverCfg::OnHcConfigmcu() 
{
	CFlatEditDlg dlgEC;
	UpdateData(true);
	dlgEC.FE_file=m_sCfgNameMCU;
	dlgEC.FE_fix=true;
	
	dlgEC.DoModal();	
}

void CCoverCfg::OnNodataCfbrs() 
{
	CFileDialog dlg(true,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,_T("WAV file|*.WAV||"),NULL);
	if(dlg.DoModal()==IDOK)
	{
		m_sNoDataFile=dlg.GetPathName();
		UpdateData(false);	
	}		
}

void CCoverCfg::OnScanfreqCfbrs() 
{
	CFileDialog dlg(true,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,_T("WAV file|*.WAV||"),NULL);
	if(dlg.DoModal()==IDOK)
	{
		m_sScanFreqFile=dlg.GetPathName();
		UpdateData(false);	
	}	
}

void CCoverCfg::OnChangefreqCfbrs() 
{
	CFileDialog dlg(true,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,_T("WAV file|*.WAV||"),NULL);
	if(dlg.DoModal()==IDOK)
	{
		m_sChangeFreqFile=dlg.GetPathName();
		UpdateData(false);	
	}	
}
