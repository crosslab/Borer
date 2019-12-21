#include "stdafx.h"
#include "MpDef.h"

#include "Borer.h"
#include "BinRes.h"
#include <string>
#include <fstream>
#include <iostream>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


BinRes::BinRes()
{
  
}

BinRes::~BinRes()
{
  
}

char *BinRes::WringBinResource(std::string strCustomResName, 
                               int nResourceId, 
                               unsigned char *outWring,
                               DWORD *dwSizeRes)
{
  HGLOBAL hResourceLoaded;		// handle to loaded resource 
  HRSRC hRes;						// handle/ptr. to res. info. 
  char *lpResLock;				// pointer to resource data 
  
  // find location of the resource and get handle to it
  hRes = FindResource( NULL, MAKEINTRESOURCE(nResourceId), strCustomResName.c_str() );
  
  // loads the specified resource into global memory. 
  hResourceLoaded = LoadResource( NULL, hRes ); 
  
  // get a pointer to the loaded resource!
  lpResLock = (char*)LockResource( hResourceLoaded ); 
  
  // determine the size of the resource, so we know how much to write out to file!  
  *dwSizeRes = SizeofResource( NULL, hRes );
  
  if(!outWring) {
    outWring=(unsigned char*)DltAlloc(*dwSizeRes);
  }
 	
  memcpy(outWring,lpResLock,*dwSizeRes);
  return lpResLock;
}

void BinRes::ExtractBinResource( std::string strCustomResName, 
                                int nResourceId,
                                CString strOutputName )
{
  HGLOBAL hResourceLoaded;    // handle to loaded resource 
  HRSRC hRes;                 // handle/ptr. to res. info. 
  char *lpResLock;            // pointer to resource data 
  DWORD dwSizeRes;
  
  // find location of the resource and get handle to it
  hRes = FindResource( NULL, MAKEINTRESOURCE(nResourceId), strCustomResName.c_str() );
  
  // loads the specified resource into global memory. 
  hResourceLoaded = LoadResource( NULL, hRes ); 
  
  // get a pointer to the loaded resource!
  lpResLock = (char*)LockResource( hResourceLoaded ); 
  
  // determine the size of the resource, so we know how much to write out to file!  
  dwSizeRes = SizeofResource( NULL, hRes );
  
  PurgeFile(strOutputName);
  std::ofstream outputFile(strOutputName, std::ios::binary);
  
  outputFile.write((const char*)lpResLock, dwSizeRes);
  outputFile.close();
}
