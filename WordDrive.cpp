#include "stdafx.h"
#include "Borer.h"
#include "WordDrive.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWordDrive
CWordDrive::CWordDrive()
{
}

CWordDrive::~CWordDrive()
{
}

IMPLEMENT_DYNCREATE(CWordDrive, CObject)

/////////////////////////////////////////////////////////////////////////////
// CVariantDlg message handlers
bool CWordDrive::WDInit(CString &wdiPath,CString &wdiExe)
{
  if(!CopyFile(wdiExe+"���Ա���.Doc",wdiPath+"\\���Ա���.Doc",false)) 
  {
    AfxMessageBox("�����ڲ��Ա���ģ�壬�����!", MB_SETFOREGROUND);
    return false;
  }
  
  COleVariant vOpt(DISP_E_PARAMNOTFOUND, VT_ERROR);  //For optional args
  
  //Start Word
  if(!(m_oWord.CreateDispatch("Word.Application", NULL)))
  {
    AfxMessageBox("Error starting Word.", MB_SETFOREGROUND);
    return false;
  }
  
  Options opWDI;
  opWDI =m_oWord.GetOptions();
  opWDI.SetAutoFormatApplyLists(false);
  opWDI.SetAutoFormatApplyBulletedLists(false);
  opWDI.SetAutoFormatAsYouTypeApplyNumberedLists(false);
  opWDI.SetAutoFormatAsYouTypeApplyBulletedLists(false);
  
  //Open a document
  m_aryDoc = m_oWord.GetDocuments();
  m_oDoc   = m_aryDoc.Open(COleVariant(wdiPath+"\\���Ա���.Doc"), vOpt, vOpt, vOpt, 
    vOpt, vOpt, vOpt, vOpt, vOpt, vOpt, vOpt, vOpt);
  
  m_clueTbl   = 5 ;
  m_nTotalRow = 2 ;
  
  return true;
}

bool CWordDrive::WDTrack(WDIINFO *lsParam)
{
  Tables tblsWDT;
  Table tblWDT; // �������
  
  Cell  cellWDT; 
  Range rngWDT;
  
  ListFormat  lfWDT;
  _Font       ftWDT;
  
  CString strWDT;
  CString strFileName;
  strFileName = lsParam->wdiScript.Right(lsParam->wdiScript.GetLength()-lsParam->wdiScript.ReverseFind('/')-1);
  
  tblsWDT = m_oDoc.GetTables();
  
  // д�ܼƱ��
  tblWDT = tblsWDT.Item(4);
  Rows clsRows = tblWDT.GetRows();
  VARIANT cc;
  cc.vt = VT_DISPATCH ;
  cc.pdispVal = clsRows.Item(m_nTotalRow) ;
 	clsRows.Add(&cc) ;
  
  cellWDT = tblWDT.Cell(m_nTotalRow,1);
  rngWDT =cellWDT.GetRange();
  rngWDT.InsertAfter(strFileName);
  
  cellWDT = tblWDT.Cell(m_nTotalRow,2);
  rngWDT =cellWDT.GetRange();
  rngWDT.InsertAfter(lsParam->wdiItem);
  
  cellWDT = tblWDT.Cell(m_nTotalRow,3);
  rngWDT =cellWDT.GetRange();
  if(lsParam->wdiResult.Find("Failed_") ==-1) 
  {
    rngWDT.InsertAfter("OK");	
  }
  else
  {
    rngWDT.InsertAfter("NO");	
  }
  
  m_nTotalRow++;
  
  // д������
  tblWDT = tblsWDT.Item(5);
  rngWDT =tblWDT.GetRange();
  rngWDT.Copy();
  
  // �������
  tblWDT = tblsWDT.Item(m_clueTbl);
  rngWDT =tblWDT.GetRange();
  rngWDT.Collapse(COleVariant(0L)); // 0=wdCollapseEnd,1=wdCollapseStart
  
  strWDT.Format("5.1.%d  %s\r\n",m_clueTbl-4,lsParam->wdiItem);
  rngWDT.InsertAfter(strWDT);
  rngWDT.MoveEnd(COleVariant(1L),COleVariant(-2L));//1=wdCharacter
  rngWDT.SetStyle(COleVariant(-4L));
  
  lfWDT =rngWDT.GetListFormat();
  lfWDT.RemoveNumbers(COleVariant(1L)); //1=wdNumberParagraph
  rngWDT.Collapse(COleVariant(0L)); // 0=wdCollapseEnd,1=wdCollapseStart
  
  rngWDT.Paste();
  
  m_clueTbl++;
  tblWDT = tblsWDT.Item(m_clueTbl);
  
  cellWDT =tblWDT.Cell(1,2);
  rngWDT =cellWDT.GetRange();
  if(lsParam->wdiModule.IsEmpty()) 
  {
    lsParam->wdiScript=lsParam->wdiScript.Left(lsParam->wdiScript.ReverseFind('/'));
    lsParam->wdiScript=lsParam->wdiScript.Right(lsParam->wdiScript.GetLength()-lsParam->wdiScript.ReverseFind('/')-1);
    rngWDT.InsertAfter(lsParam->wdiScript);
  }
  else
  {
    rngWDT.InsertAfter(lsParam->wdiModule);
  }
  
  cellWDT =tblWDT.Cell(2,2);
  rngWDT =cellWDT.GetRange();
  rngWDT.InsertAfter(lsParam->wdiItem);
  
  cellWDT =tblWDT.Cell(3,2);
  rngWDT =cellWDT.GetRange();
  rngWDT.InsertAfter(lsParam->wdiOperator);
  
  cellWDT =tblWDT.Cell(3,4);
  rngWDT =cellWDT.GetRange();
  rngWDT.InsertAfter(lsParam->wdiDate);
  
  cellWDT =tblWDT.Cell(4,2);
  rngWDT =cellWDT.GetRange();
  rngWDT.InsertAfter(lsParam->wdiVersion);
  
  cellWDT =tblWDT.Cell(5,2);
  rngWDT =cellWDT.GetRange();
  rngWDT.InsertAfter(strFileName);
  
  cellWDT =tblWDT.Cell(6,2);
  rngWDT =cellWDT.GetRange();
  strWDT =lsParam->wdiResult.Right(lsParam->wdiResult.GetLength()-lsParam->wdiResult.ReverseFind('\\')-1);
  rngWDT.InsertAfter(strWDT);
  
  cellWDT =tblWDT.Cell(9,2);
  rngWDT =cellWDT.GetRange();
  ftWDT =rngWDT.GetFont();
  
  // ����ͨ�����ߴ���
  if(lsParam->wdiResult.Find("Failed_") ==-1) 
  {
    rngWDT.MoveEnd(COleVariant(1L),COleVariant(-8L));//1=wdCharacter
    ftWDT.SetColor(0xff0000);  //0xff0000 =wdColorBlue
    rngWDT.SetFont(ftWDT);
    
    rngWDT.MoveStart(COleVariant(1L),COleVariant(32L));//1=wdCharacter
    rngWDT.MoveEnd(COleVariant(1L),COleVariant(32L));//1=wdCharacter
    ftWDT.SetColor(0);
    rngWDT.SetFont(ftWDT);
  }
  else
  {
    rngWDT.MoveEnd(COleVariant(1L),COleVariant(-8L));//1=wdCharacter
    ftWDT.SetColor(0);
    rngWDT.SetFont(ftWDT);
    
    rngWDT.MoveStart(COleVariant(1L),COleVariant(32L));//1=wdCharacter
    rngWDT.MoveEnd(COleVariant(1L),COleVariant(32L));//1=wdCharacter
    ftWDT.SetColor(0xff0000);  //0xff0000 =wdColorBlue
    rngWDT.SetFont(ftWDT);
  }
  
  delete lsParam;
  return true;
}

bool CWordDrive::WDFini()
{
  COleVariant vOpt(DISP_E_PARAMNOTFOUND, VT_ERROR);  //For optional args
  
  Tables tblsWDF;
  Table tblWDF;
  
  // ɾ��Copy�ı��
  tblsWDF = m_oDoc.GetTables();
  tblWDF = tblsWDF.Item(5);
  tblWDF.Delete();
  
  // ɾ�������ӵ�һ��
  tblWDF = tblsWDF.Item(4);
  Rows clsRows = tblWDF.GetRows();
  Row  clsOneRow = clsRows.Item(m_nTotalRow);
  clsOneRow.Delete();
  
  m_oDoc.Save();
  m_oDoc.Close(COleVariant((short)false), vOpt, vOpt);
  
  m_oDoc.ReleaseDispatch();
  m_aryDoc.ReleaseDispatch();
  
  //Quit Word
  m_oWord.Quit(COleVariant((short)false), vOpt, vOpt);
  m_oWord.m_lpDispatch=NULL;
  return true;
}
