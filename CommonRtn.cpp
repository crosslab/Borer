#include "stdafx.h"
#include  <io.h>

#include "CommonDef.h"
#include "Borer.h"
#include "MainFrm.h"
//#include "VbhExpression.h"

void AfxSplitPath(const CString& sPath, CString& sTitle, CString& sDir)
{
  char drive[_MAX_DRIVE];
  char dir[_MAX_DIR];
  char fname[_MAX_FNAME];
  char ext[_MAX_EXT];
  
  _splitpath(sPath, drive, dir, fname, ext );
  sTitle= fname;
  sDir= drive;
  sDir+= dir;
  int sLen= sDir.GetLength();
  sDir.SetAt(sLen-1, 0);
}

// close the database and destruct it
// IN/OUT:: ppDatabase--pointer to pointer to database to close and
// destruct
void closeDatabase(CDaoDatabase **ppDatabase)
{
  // only process if the database object exists
  if(*ppDatabase != NULL)
  {
    if((*ppDatabase)->IsOpen())
      (*ppDatabase)->Close();
    
    // closing doesn't delete the object
    delete *ppDatabase;
    *ppDatabase = NULL;
  }
}

// create the database file (close any open database)
// IN/OUT: ppDatabase--pointer to pointer to database object
// IN: fileName--name of .mdb file to open
// IN: dwOptions--info like version and encryption settings
//     0 by default
// RETURN: TRUE if success, FALSE if failure
BOOL createDatabase(CDaoDatabase **ppDatabase, CString fileName,
                    int dwOptions /* = 0 */)
{
  // initialize success indicator
  BOOL bSuccess = TRUE;
  
  // construct new database
  *ppDatabase = new CDaoDatabase;
  
  // failed to allocate
  if(ppDatabase == NULL)
    return FALSE; // error
  
  // now create the database object with error checking
  try
  {
    // default language specified
    (*ppDatabase)->Create(fileName, dbLangGeneral, dwOptions);
  }
  catch (CDaoException *e)
  {
    // create a message to display
    CString message = _T("Couldn't create database--Exception: ");
    message += e->m_pErrorInfo->m_strDescription;
    
    // output status
    AfxMessageBox(message);
    
    // not rethrowing, so delete exception
    e->Delete();
    
    delete *ppDatabase;
    *ppDatabase = NULL;
    
    // failure
    bSuccess = FALSE;
  }
  catch (CMemoryException *e)
  {
    // output status
    AfxMessageBox(_T("Failed to create database--Memory exception thrown."));
    
    // not rethrowing, so delete exception
    e->Delete();
    
    delete *ppDatabase;
    *ppDatabase = NULL;
    
    // failure
    bSuccess = FALSE;
  }
  
  return bSuccess;
}

// open the database from a file (close if necessary)
// IN/OUT: ppDatabase--pointer to pointer to database object
// IN: fileName--name of .mdb file to open
// IN: bReportNoOpen--TRUE by default, if true, if open fails
//     because the specified MDB file doesn't exist, report that
//     fact to the user.  Note: other errors are reported always
// RETURN: 1 if success, 0 if non-fatal failure, -1 if fatal failure
int openDatabase(CDaoDatabase **ppDatabase, CString fileName,
                 BOOL bReportNoOpen /* = TRUE */)
{
  // initialize success indicator
  int nReturnCode = 1;
  
  // close and delete if necessary
  if(*ppDatabase != NULL)
  {
    if((*ppDatabase)->IsOpen())
      closeDatabase(ppDatabase);
    delete *ppDatabase;
  }
  
  // construct new database
  *ppDatabase = new CDaoDatabase;
  
  // failed to allocate
  if(ppDatabase == NULL)
    return -1; // fatal error
  
  // now open the database object with error checking
  try
  {
    (*ppDatabase)->Open(fileName);
  }
  catch (CDaoException *e)
  {
    // special case--couldn't find the file, so it may be because
    // user specified a new file to open
    if(e->m_pErrorInfo->m_lErrorCode == 3024)
    {
      if(bReportNoOpen)
      {
        // create a message to display
        CString message = _T("Couldn't open database--Exception: ");
        message += e->m_pErrorInfo->m_strDescription;
        
        // output status
        AfxMessageBox(message);
      }
      
      // indicate failure but not fatal
      nReturnCode = 0;
    }
    else // other type of DAO exception--always report
    {
      // create a message to display
      CString message = _T("Couldn't open database--Exception: ");
      message += e->m_pErrorInfo->m_strDescription;
      
      // output status
      AfxMessageBox(message);
      
      // indicate fatal error
      nReturnCode = -1;
    }
    
    // not rethrowing, so delete exception
    e->Delete();
    
    delete *ppDatabase;
    *ppDatabase = NULL;
  }
  catch (CMemoryException *e)
  {
    // output status
    AfxMessageBox(_T("Failed to open database--Memory exception thrown."));
    
    // not rethrowing, so delete exception
    e->Delete();
    
    delete *ppDatabase;
    *ppDatabase = NULL;
    
    // indicate fatal error
    nReturnCode = -1;
  }
  
  return nReturnCode;
}

// check for duplicate field name in field collection
// of tabledef object
// IN: pTableDef--the tabledef whose fields collection we access
// IN: strFieldName--the name of the field to check for existence
// RETURN: TRUE if field already exists in collection, FALSE otherwise
BOOL IsExistentField(CDaoTableDef *pTableDef, CString strFieldName)
{
  // if the tabledef is non-existent, then the answer is obvious
  if(pTableDef == NULL)
    return FALSE;
  
  // initialize status indicator
  BOOL bDuplicateFieldName = TRUE;
  
  // see if there is a field by this name already--duplicate
  // named fields are not accepted
  CDaoFieldInfo fieldInfo;    // only needed for the call
  
  // MFC exception handler macros used
  TRY
  {
    // this call will throw an exception if there is no
    // field by the specified name--test for duplication
    pTableDef->GetFieldInfo(strFieldName, fieldInfo);
  }
  CATCH (CDaoException, e)
  {
    // if this is an 'Item not found' exception, we are
    // cleared to create the field -- else this is
    // a duplicate field name and we got another exception
    // which is irrelevant for our purposes
    if(e->m_pErrorInfo->m_lErrorCode == 3265)
      bDuplicateFieldName = FALSE;
  }
  AND_CATCH (CMemoryException, e)
  {
    // do nothing--no need to process errors since this is
    // just a duplicate checker
  }
  END_CATCH
    
    return bDuplicateFieldName;
}
// wraps the CreateField DAO call in an exception handler
// IN: pTableDef--the tabledef whose fields collection we access
// IN: pFieldInfo--information used to create field
// RETURN: TRUE if creation succeeds, FALSE if it fails
BOOL createNewField(CDaoTableDef *pTableDef, CDaoFieldInfo *pFieldInfo)
{
  // if the tabledef is non-existent, then the answer is obvious
  if(pTableDef == NULL)
    return FALSE;
  
  // check for existing field with this name just to be safe
  if(IsExistentField(pTableDef, pFieldInfo->m_strName))
  {
    AfxMessageBox(_T("A field by that name already exists."));
    
    // return FALSE since can't create duplicate field
    return FALSE;
  }
  
  // initialize failure indicators
  BOOL bCreateFailed = FALSE;
  
  // create a field with the specified properties
  // it is automatically appended to field collection
  // of the tabledef
  TRY
  {
    pTableDef->CreateField(*pFieldInfo);
  }
  CATCH (CDaoException, e)
  {
    // construct a meaningful message
    CString message = _T("Couldn't create field--Exception: ");
    message += e->m_pErrorInfo->m_strDescription;
    
    // display message
    AfxMessageBox(message);
    
    // indicate failure
    bCreateFailed = TRUE;
  }
  AND_CATCH (CMemoryException, e)
  {
    AfxMessageBox(_T("Failed to create field--Memory exception thrown."));
    
    // indicate failure
    bCreateFailed = TRUE;
  }
  END_CATCH
    
    // return TRUE if creation succeeds
    return (!bCreateFailed);
}

// check for duplicate table name in tabledef collection
// of database object
// IN: pDatabase--pointer to database object whose tabledef collection we will
//     access
// IN: strTableName--name of the table whose existence we want to check
// RETURN: TRUE if the table already exists, FALSE otherwise
BOOL IsExistentTable(CDaoDatabase *pDatabase, CString strTableName)
{
  // if the database is non-existent, then the answer is obvious
  if(pDatabase == NULL)
    return FALSE;
  
  // initialize status indicator
  BOOL bDuplicateTableName = TRUE;
  
  // see if there is a table by this name already--duplicate
  // named tables are not accepted
  CDaoTableDefInfo tableInfo; // only needed for the call
  
  // MFC exception handler macros used
  TRY
  {
    // this call will throw an exception if there is no
    // table by the specified name--test for duplication
    pDatabase->GetTableDefInfo(strTableName, tableInfo);
  }
  CATCH (CDaoException, e)
  {
    // if this is an 'Item not found' exception, we are
    // cleared to create the table -- else this is
    // a duplicate tablename and we got another exception
    // which is irrelevant for our purposes
    if(e->m_pErrorInfo->m_lErrorCode == 3265)
      bDuplicateTableName = FALSE;
  }
  AND_CATCH (CMemoryException, e)
  {
    // do nothing
    ;
  }
  END_CATCH
    
    return bDuplicateTableName;
}

// wraps the CreateTableDef call with an exception handler and duplicate
// name check
// IN: pDatabase--pointer to database object whose tabledef collection we will
//     access
// OUT: ppTableDef--pointer to pointer to tabledef we are creating
// IN: strTableName--name of the table we want to create
// RETURN: TRUE if creation succeeds, FALSE otherwise
BOOL createNewTableDef(CDaoDatabase * pDatabase,
                       CDaoTableDef **ppTableDef,
                       CString strTableName)
{
  // if the database is non-existent, then the answer is obvious
  if(pDatabase == NULL)
    return FALSE;
  
  // check for existing table with this name just to be safe
  if(IsExistentTable(pDatabase, strTableName))
  {
    AfxMessageBox(_T("A table by that name already exists."));
    
    // return FALSE since can't create duplicate table
    return FALSE;
  }
  
  // initialize creation failure indicator
  BOOL bCreateFailed = FALSE;
  
  // construct tabledef
  *ppTableDef = new CDaoTableDef(pDatabase);
  
  // failed to allocate so exit
  if((*ppTableDef) == NULL)
    return FALSE;
  
  // no duplication, so create the tabledef if possible
  TRY
  {
    (*ppTableDef)->Create(strTableName);
  }
  CATCH (CDaoException, e)
  {
    // construct a meaningful message
    CString strMessage = _T("Couldn't create tabledef--Exception: ");
    strMessage += e->m_pErrorInfo->m_strDescription;
    
    AfxMessageBox(strMessage);
    
    // indicate failure
    bCreateFailed = TRUE;
    
    // delete the tabledef on failure
    if(*ppTableDef != NULL)
    {
      delete *ppTableDef;
      *ppTableDef = NULL;
    }
  }
  AND_CATCH (CMemoryException, e)
  {
    // output status
    AfxMessageBox(_T("Failed to create tabledef--Memory exception thrown."));
    
    // indicate failure
    bCreateFailed = TRUE;
    
    // delete the tabledef on failure
    if(*ppTableDef != NULL)
    {
      delete *ppTableDef;
      *ppTableDef = NULL;
    }
  }
  END_CATCH
    
    // return TRUE if creation succeeds
    return (!bCreateFailed);
}

// detete the specified table from the collection of tables
// IN: pDatabase--pointer to database object whose tabledef collection we will
//     access
// IN: strTableName--name of the table we want to delete
void deleteTable(CDaoDatabase *pDatabase, CString strTableName)
{
  // if the database is non-existent, then the answer is obvious
  if(pDatabase == NULL)
    return;
  
  // see if there is a table by this name -- if not, can't proceed
  if(!IsExistentTable(pDatabase, strTableName))
    return;
  
  // MFC exception handler macros used
  TRY
  {
    pDatabase->DeleteTableDef(strTableName);
  }
  CATCH (CDaoException, e)
  {
    // construct a meaningful message if request
    CString strMessage = _T("Couldn't delete the table--Exception: ");
    strMessage += e->m_pErrorInfo->m_strDescription;
    
    AfxMessageBox(strMessage);
  }
  AND_CATCH (CMemoryException, e)
  {
    // output status if requested
    AfxMessageBox(_T("Failed to delete the table--Memory exception thrown."));
  }
  END_CATCH
    
    return;
}

// append the tabledef to the database collection
// IN: pDatabase--pointer to database object whose tabledef collection we will
//     access
// IN: pTableDef--pointer tabledef we are appending to the collection
// RETURN: TRUE if append succeeds, FALSE otherwise
BOOL appendTableDef(CDaoDatabase *pDatabase, CDaoTableDef *pTableDef)
{
  // if the database is non-existent, then the answer is obvious
  if(pDatabase == NULL)
    return FALSE;
  
  // initialize success indicator
  BOOL bSuccess = TRUE;
  
  // append the tabledef to the collection
  TRY
  {
    pTableDef->Append();
  }
  CATCH (CDaoException, e)
  {
    // construct informative message
    CString strMessage = _T("Couldn't append TableDef--Exception: ");
    strMessage += e->m_pErrorInfo->m_strDescription;
    
    // output status
    AfxMessageBox(strMessage);
    
    // failure
    bSuccess = FALSE;
  }
  AND_CATCH (CMemoryException, e)
  {
    // output status
    AfxMessageBox(_T("Failed to append tabledef--Memory exception thrown."));
    
    // failure
    bSuccess = FALSE;
  }
  END_CATCH
    
    // return status
    return bSuccess;
}

// wrap field deletion with exception handlers
// IN: pTableDef--the tabledef whose fields collection we access
// IN: strFieldName--name of field to delete
// RETURN: TRUE if deletion succeeded, FALSE otherwise
BOOL deleteField(CDaoTableDef *pTableDef, CString strFieldName)
{
  // if the tabledef is non-existent, then the answer is obvious
  if(pTableDef == NULL)
    return FALSE;
  
  // initialize success indicator
  BOOL bSuccess = TRUE;
  
  // MFC exception handler macros used
  TRY
  {
    // this call will throw an exception if there is no
    // field by the specified name--test for duplication
    pTableDef->DeleteField(strFieldName);
  }
  CATCH (CDaoException, e)
  {
    CString strMessage = _T("Couldn't delete the field--Exception: ");
    strMessage += e->m_pErrorInfo->m_strDescription;
    
    AfxMessageBox(strMessage);
    
    // indicate failure
    bSuccess = FALSE;
  }
  AND_CATCH (CMemoryException, e)
  {
    AfxMessageBox(_T("Failed to delete the field--Memory exception thrown."));
    
    // indicate failure
    bSuccess = FALSE;
  }
  END_CATCH
    
    return bSuccess;
}

// control availability depends on two things--the type of the field and
// whether this is an existing field or new.  Some controls only make
// sense for certain types (like autoincrement for longs only).  Existing
// fields have primarily read-only properties.  This function takes both
// into account when setting control states
//
// Note: since disabled is acceptable for existing field controls, you will
//       not see the bExisting taken into consideration if we are disabling
//       a control based on type
//
// IN: theType--the type of the current field (long, text, etc.)
// IN: bExistingField--TRUE if this is an existing field, else false
void setTypeDependentStates(CDaoFieldInfo &infFld)
{
  // In general, the selected type determines the following:
  //   * the size of the field (in bytes)
  //   * whether the size is user modifiable or not
  //   * what the setting for field variability is by default
  switch(infFld.m_nType)
  {
		case dbBoolean:
    case dbByte:
						infFld.m_lSize = 1;
            // set to fixed field type
            infFld.m_lAttributes &= ~dbVariableField;
            infFld.m_lAttributes |= dbFixedField;
            break;
    case dbInteger:
						infFld.m_lSize = 2;
            // set to fixed field type
            infFld.m_lAttributes &= ~dbVariableField;
            infFld.m_lAttributes |= dbFixedField;
            break;
    case dbLong:
    case dbSingle:
						infFld.m_lSize = 4;
            // set to fixed field type
            infFld.m_lAttributes &= ~dbVariableField;
            infFld.m_lAttributes |= dbFixedField;
            break;
    case dbCurrency:
    case dbDate:
    case dbDouble:
						infFld.m_lSize = 8;
            // set to fixed field type
            infFld.m_lAttributes &= ~dbVariableField;
            infFld.m_lAttributes |= dbFixedField;
            break;
    case dbText:
		// set to variable field type
		infFld.m_lAttributes &= ~dbFixedField;
		infFld.m_lAttributes |= dbVariableField;
		break;
    case dbLongBinary:
		// set to variable field type
		infFld.m_lAttributes &= ~dbFixedField;
		infFld.m_lAttributes |= dbVariableField;
		break;
    case dbMemo:
		// set to variable field type
		infFld.m_lAttributes &= ~dbFixedField;
		infFld.m_lAttributes |= dbVariableField;
            break;
  } // end of switch
}

// initialize the field information to a default state.
// IN: bInitOrdPos -- The ordinal position is conditionally initialized
// to allow for it autoincrementing with each addition of a field to the
// tabledef--TRUE by default
void fieldInitializer(CDaoFieldInfo &infFld)
{
  // always initialize the rest
  infFld.m_strName = _T("");
  infFld.m_nType = -1;      // initialized for the benefit of the combox
  infFld.m_lSize = 0;
  infFld.m_strDefaultValue = _T("");
  infFld.m_bRequired = FALSE;
  infFld.m_lAttributes = dbUpdatableField;
#if _MFC_VER == 0x400
  infFld.m_bAllowZeroLength = TRUE;
#else
  infFld.m_bAllowZeroLength = FALSE;
#endif;
  infFld.m_strValidationRule = _T("");
  infFld.m_strValidationText = _T("");
}

COLORREF DecipherColour(CString &strType)
{
  return 0;
}

int DecipherTypes(char *strType) 
{
  // insert string elements  for the ComboBox : 
  for(int iLop=0 ; iLop < 8 ; iLop++) {
    if(!lstrcmp(strType,aryProduct[iLop])) {
      return iLop;
    }
  }
  return 0;
}

int GetFileLength(CString &flFile)
{
  CFile flOpen;
  int   lenCm;
  
  if(!flOpen.Open(flFile,CFile::modeRead)) {
	   return 0;
  }
  
  lenCm =flOpen.GetLength();
  flOpen.Close();
  return lenCm;
}

void SetFieldInfo(CDaoFieldInfo &infFld,HSM_ITEM *cgInfo)
{
  infFld.m_strName=cgInfo->vi_Name;
  
  if(cgInfo->vi_Type==DT_BIT) {
    infFld.m_nType=dbInteger;
  }else if(cgInfo->vi_Type==DT_BYTE) {
    infFld.m_nType=dbInteger;
  }else if(cgInfo->vi_Type==DT_WORD) {
    infFld.m_nType=dbLong;
  }else if(cgInfo->vi_Type==DT_DWD) {
    infFld.m_nType=dbDouble;
  }else if(cgInfo->vi_Type==DT_UF16) {
    infFld.m_nType=dbDouble;
  }else if(cgInfo->vi_Type==DT_F16) {
    infFld.m_nType=dbDouble;
  }else if(cgInfo->vi_Type==DT_UF32) {
    infFld.m_nType=dbDouble;
  }else if(cgInfo->vi_Type==DT_F32) {
    infFld.m_nType=dbDouble;
  }
  setTypeDependentStates(infFld);
}

void ConcoctClue(CDaoFieldInfo &ccTime)
{
  fieldInitializer(ccTime);
  ccTime.m_strName=LISTR_CLUE;
  
  ccTime.m_nType=dbDouble;
  setTypeDependentStates(ccTime);
}

void ConcoctTime(CDaoFieldInfo &ccTime)
{
  fieldInitializer(ccTime);
  ccTime.m_strName=MDBSTR_TMFLD;
  
  ccTime.m_nType=dbDate;
  setTypeDependentStates(ccTime);
}

void ConcoctMcu(CDaoFieldInfo &ccMcu)
{
  fieldInitializer(ccMcu);
  ccMcu.m_strName=MDBSTR_MCUFLD;
  
  ccMcu.m_nType=dbMemo;
  setTypeDependentStates(ccMcu);
}

void ConcoctLatitude(CDaoFieldInfo &ccLatitude)
{
  fieldInitializer(ccLatitude);
  ccLatitude.m_strName=MDBSTR_LATITUDE;
  
  ccLatitude.m_nType=dbDouble;
  setTypeDependentStates(ccLatitude);
}

void ConcoctLongitude(CDaoFieldInfo &ccLongitude)
{
  fieldInitializer(ccLongitude);
  ccLongitude.m_strName=MDBSTR_LONGITUDE;
  
  ccLongitude.m_nType=dbDouble;
  setTypeDependentStates(ccLongitude);
}

void ConcoctSpeed(CDaoFieldInfo &ccSpeed)
{
  fieldInitializer(ccSpeed);
  ccSpeed.m_strName=MDBSTR_SPEED;
  
  ccSpeed.m_nType=dbDouble;
  setTypeDependentStates(ccSpeed);
}

void ConcoctMCUMDM(CDaoFieldInfo &ccMcuMdm)
{
  fieldInitializer(ccMcuMdm);
  
  ccMcuMdm.m_nType=dbInteger;
  setTypeDependentStates(ccMcuMdm);
}
//COleVariant类型的数据转化成字符串类型
void VariantToStr(COleVariant &var,CString &str)
{
  switch (var.vt) 
  {
  case VT_BSTR:
    str = (LPCSTR) var.bstrVal; // narrow characters in DAO
    break;
  case VT_I2:
    str.Format("%d", (int) var.iVal);
    break;
  case VT_I4:
    str.Format("%d", var.lVal);
    break;
  case VT_R4:
    str.Format("%10.2f", (double) var.fltVal);
    break;
  case VT_R8:
    str.Format("%2.6f", var.dblVal);
    break;
  case VT_CY:
    str = COleCurrency(var).Format();
    break;
  case VT_DATE:
    str = COleDateTime(var).Format();
    break;
  case VT_BOOL:
    str = (var.boolVal == 0) ? "FALSE" : "TRUE";
    break;
  case VT_NULL:
    str =  "";
    break;
  default:
    str.Format("Unk type %d\n", var.vt);
    TRACE("Unknown type %d\n", var.vt);
  }			
}

//读取数据库文件相关信息
void ReadFileInfo(CString &filename,CString &titlename,CStringArray &strArray)
{
  CFileFind findfile;
  if( !findfile.FindFile( filename, 0 ))
  {
    return;
  }
  CDaoDatabase database;
  CDaoRecordset* pRecordset;	
  CDaoFieldInfo tdi;	///取列名
  
  CString strCondition;
  COleVariant var;
  
  database.Open(filename);
  pRecordset=new CDaoRecordset(&database);
  
  strCondition.Format("select * from %s",titlename);
  pRecordset->Open(dbOpenDynaset,strCondition);//dbAppendOnly
  if (!pRecordset->IsBOF()) {
    pRecordset->MoveLast(); // to validate record count
		}
  int nField=pRecordset->GetFieldCount();
  
  strArray.RemoveAll();
  for(int n=0;n<nField;n++)
  {
    pRecordset->GetFieldInfo(n,tdi);
    if(tdi.m_strName.Left(4)!="MSys"){
      strArray.Add(tdi.m_strName);		
    }
  }	
  
  pRecordset->Close();
  delete pRecordset;
  database.Close();
}