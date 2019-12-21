// TokenMap.cpp : implementation file
//

#include "stdafx.h"
#include "Borer.h"
#include "TokenMap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTokenMap

CTokenMap::CTokenMap()
{
}

CTokenMap::~CTokenMap()
{
}

IMPLEMENT_DYNAMIC(CTokenMap, CMemMapFile)

/////////////////////////////////////////////////////////////////////////////
// CTokenMap message handlers

long CTokenMap::GetAddress(char *sVariableName)
{
  if (strlen(sVariableName)<1)
  {
    return -1 ;
  }
  
  int i=0 ;
  char * pdest,	*stopstring;
  
  pdest = strstr((char*)m_lpData,sVariableName);
  if(pdest ==NULL)
  {
    return -1;
  }
  
  pdest +=strlen(sVariableName);
  
  while( !isxdigit(*pdest))
    pdest++;
  
  return strtoul(pdest,&stopstring,16);
}
