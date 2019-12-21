#include "stdafx.h"
#include "lock.h"

#include "MainFrm.h"
#include "BorerDoc.h"
#include "BorerView.h"

HANDLE m_hEvent1;

CriticalSection::CriticalSection()
{
  InitializeCriticalSection(&m_CritSect);
}

CriticalSection::~CriticalSection()
{
  DeleteCriticalSection(&m_CritSect);
  
}
void CriticalSection::Lock()
{
  
}
void CriticalSection::Unlock()
{
}
Lock::Lock(LockableObject* pLockable)
{
  m_pLockable = pLockable;
  m_pLockable->Lock();
}
Lock::~Lock()
{
  m_pLockable->Unlock();
}
/*******************************/
ManageShareMemory::ManageShareMemory()
{
  m_hFileMapping=NULL;
  m_pMap=NULL;
  m_hFileMapping = CreateFileMapping(
    (HANDLE)0xFFFFFFFF,
    NULL,
    PAGE_READWRITE,
    0,
    sizeof(EM_MESSAGE)+1,
    "Msg");
  m_pMap = (BYTE*) MapViewOfFile(
    m_hFileMapping,
    FILE_MAP_ALL_ACCESS,
    0,
    0,
    0);
  
}

ManageShareMemory::~ManageShareMemory()
{
  UnmapViewOfFile(m_pMap);
  CloseHandle(m_hFileMapping);
  
  
}

void ManageShareMemory::SendMsgToShareMem(char* pmsg,int Len,int Tsleep,void *pView)
{
  CBorerDoc  *pMyDoc=(CBorerDoc*) ((CBorerView*)pView)->GetDocument();
  
  Lock a(&m_Critical);
  
  if(Tsleep==-17)
  {////测试命令,Tsleep==-17只是为了表示此是测试任务命令
    m_pMap[0] = 9;
    m_pMap[1] = 0x02;
    *((DWORD*)(m_pMap + 2 ))	= 17;		
  }
  else
  {//消息
    m_pMap[0] = 9;
    m_pMap[1] = 0x01;
    *((DWORD*)(m_pMap + 2 ))	= Len;		
  }
  memcpy(m_pMap+6,pmsg,Len);
}


