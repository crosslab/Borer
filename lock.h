#if !defined _MY_LOCK_
#define _MY_LOCK_
#include "ParaDefi.h"

class LockableObject
{
public:
  LockableObject() {};
  virtual ~LockableObject() {};
  virtual void Lock() = 0;
  virtual void Unlock() = 0;
};
class CriticalSection : public LockableObject
{
public:
  CriticalSection();
  virtual ~CriticalSection();
  virtual void Lock();
  virtual void Unlock();
private:
  CRITICAL_SECTION m_CritSect;
};



class Lock
{
public:
  Lock(LockableObject* pLockable);//
  ~Lock();
private:
  LockableObject* m_pLockable;
};


/****************************************************************/


class ManageShareMemory
{
public:
  ManageShareMemory();
  ~ManageShareMemory();
  void SendMsgToShareMem(char* pmsg,int Len,int Tsleep,void *pView);
private:
  //	HANDLE m_hEvent1;
  HANDLE m_hFileMapping;
  BYTE * m_pMap;
  CriticalSection m_Critical;
  
};


#endif