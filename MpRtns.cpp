#include "stdafx.h"
#include "mpdef.h"

#include "Borer.h"
#include "MainFrm.h"
//#include "PreQuit.h"

/********************************************************************
GLOBALS for this file
The string arrays are the items in the dialog list controls.
*******************************************************************/


// close the database and destruct it
// IN/OUT:: ppDatabase--pointer to pointer to database to close and
// destruct


BYTE RTNCRC(BYTE* BArray,int Start,int Length)//CRC验证函数（取异或）
{
  BYTE BByte = 0;//开始异或计算的计算
  int i;
  for(i=0;i<Length;i++)
  {
    BByte = BByte ^ BArray[i+Start];
  }
  return BByte;
}

void ErrorInComm(char * szMessage)
{
  ErrorReporter(szMessage);
  //ExitProcess(0);
}

void ErrorReporter(char * szMessage)
{
  char * szFormat ="Error %d: %s.\n\r%s\r\n";    // format for wsprintf
  char * szExtended;      // error string translated from error code
  char * szFinal;         // final string to report
  DWORD dwExtSize;
  DWORD dwErr;
  
  dwErr =GetLastError();
  
  /*
  Get error string from system
  */
  dwExtSize =ErrorExtender(dwErr, &szExtended);
  
  /*
  allocate buffer for error string from system, passed in string
  and extra stuff from the szFormat string
  */
  szFinal =(char*)LocalAlloc(LPTR, strlen(szMessage) + dwExtSize + 30);
  
  if(szFinal == NULL)	// if no final buffer, then can't format error
    AfxMessageBox("Cannot properly report error.");
  else {	
    wsprintf(szFinal, szFormat, dwErr, szMessage, szExtended);
    OutputDebugString(szFinal);
    AfxMessageBox(szFinal);
    LocalFree(szFinal);                  // free final buffer
  }
  
  /*
  free extended string buffer
  */
  LocalFree(szExtended);
  
  return;
}

DWORD ErrorExtender(DWORD dwError, char ** szBuffer)
{
  DWORD dwRes =0;
  
  dwRes =FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | 80 ,
    NULL, dwError,
    MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
    (LPTSTR) szBuffer, 0, NULL);
  
  if(dwRes == 0) {
    *szBuffer =(char*)LocalAlloc(LPTR, 1);
    return 1;
  }
  
  return dwRes;
}





bool AllIsDigit(CString &strTip)
{
  for(int abLop=0;abLop<strTip.GetLength();abLop++) {
    if(!isdigit(strTip[abLop])) {
      return false;
    }
  }
  
  return true;
}

bool IsNeglected(CString &flNeg,char chNeg)
{
  CFile    negFile;
  char    *negTip;
  DWORD    negLen;
  
  negFile.Open(flNeg,CFile::modeRead|CFile::shareDenyNone);
  negLen =negFile.GetLength();
  
  negTip=(char*)DltAlloc(negLen);
  negFile.Read(negTip,negLen);
  
  for(DWORD abLop=0;abLop<negLen/2;abLop++) {
    if(negTip[abLop]!=chNeg) {
      DltFree(negTip);
      negFile.Close();
      return false;
    }
  }
  
  DltFree(negTip);
  negFile.Close();
  return true;
}

bool IsFileSame(CString &strPob,unsigned char *lpMcu,DWORD cMcu)
{
  return false;
}

bool PurgeFile(CString &szReplaced)
{
  bool pfbRet =PurgeFile(szReplaced.GetBuffer(szReplaced.GetLength()));
  szReplaced.ReleaseBuffer();
  return pfbRet;
}

bool PurgeFile(LPTSTR szReplaced) 
{
  HANDLE hReplaced = INVALID_HANDLE_VALUE;
  bool   fSuccess  = false;
  
  WIN32_FILE_ATTRIBUTE_DATA fad;
  
  __try {
    
    // Validate parameters.
    if (szReplaced == NULL) {
      SetLastError(ERROR_INVALID_PARAMETER);
      __leave;
    }
    
    // Retrieve attributes from the file to be replaced.
    if (!GetFileAttributesEx(szReplaced, GetFileExInfoStandard, &fad))
      __leave;
    
    // Try to preserve the following attributes from the original file:
    fad.dwFileAttributes &=~(FILE_ATTRIBUTE_HIDDEN|
      FILE_ATTRIBUTE_READONLY|
      FILE_ATTRIBUTE_SYSTEM|
      FILE_ATTRIBUTE_TEMPORARY);
    if (!SetFileAttributes(szReplaced, fad.dwFileAttributes))
      __leave;
    
    // Delete the file that is being replaced.
    if (!DeleteFile(szReplaced))
      __leave;
    
    // This is enough to report success.
    fSuccess = true;
  } __finally {
    
    if (hReplaced != INVALID_HANDLE_VALUE)
      CloseHandle(hReplaced);
  }
  
  return fSuccess;
}

bool IsFixedHex(CString &strTip,int lenTip)
{
  int ptrTip=0;
  
 	strTip.MakeUpper();
  if(strTip.Left(2)=="0X") {
    ptrTip=2;
  }
  
  if(strTip.GetLength()!=(lenTip+ptrTip)) {
    return false;
  }
  
  for(int abLop=ptrTip;abLop<strTip.GetLength();abLop++) {
    if(!isxdigit(strTip[abLop])) {
      return false;
    }
  }
  
  return true;
}

//功能：校验是否是十六进制数字
bool CheckHexData(CString &snumber)
{
  snumber.MakeUpper();
  if ( snumber.Left(2) != "0X" )
    snumber = "0X" + snumber;
  
  for(int i=2; i<snumber.GetLength(); i++)
  {
    if ( isxdigit(snumber[i]) == 0 )
      return FALSE;
  }
  return TRUE;
}
