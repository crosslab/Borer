#include "stdafx.h"
#include "memmap.h"
#include <winioctl.h>
#include "RobinBuffer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CRobinBuffer,CMemMapFile)

/////////////////////////////////////////////////////////////////////////////
// CRobinBuffer
CRobinBuffer::CRobinBuffer()
{
  rdr_Free=0;
  rdr_Left=0;
}

CRobinBuffer::~CRobinBuffer()
{
}

void CRobinBuffer::Inaugurate(int iLimit)
{
  rdr_Free=0x00;
  rdr_Left=0x00;
  rdr_Limit=iLimit;
}

void CRobinBuffer::TuneupAdded(int tuneAdded)
{
  rdr_Left+=tuneAdded;
  rdr_Free+=tuneAdded;
}

void CRobinBuffer::TuneupLeft(int tuneLeft)
{
  rdr_Left =tuneLeft;
}

int CRobinBuffer::cntleft()
{
  return rdr_Left;
}

int CRobinBuffer::ptrFree()
{
  return rdr_Free;
}

unsigned char *CRobinBuffer::WritingPointer()
{
  if(rdr_Left) {
	   if(rdr_Free>rdr_Limit) {
       memcpy(&m_lpData[0],&m_lpData[rdr_Free-rdr_Left],rdr_Left);
       rdr_Free=rdr_Left;
     }
  }else {
    if(rdr_Free>rdr_Limit) {
	     rdr_Free=0;
    }
  }
  
  return &m_lpData[rdr_Free];
}

unsigned char  *CRobinBuffer::ProcessingPointer()
{
  return &m_lpData[rdr_Free-rdr_Left];
}
