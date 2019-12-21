/*******************************************************************
//	Copyright (c) 2000, Robert Umbehant
//	mailto:rumbehant@wheresjames.com
//	All rights reserved.
// 
//	Redistribution and use in source and binary forms for
//	commercial and non-commercial purposes, and with or 
//	without modification, are permitted provided that the 
//	following conditions are met:
//
//	* Redistributions of source code must retain the 
//	  above copyright notice, this list of conditions 
//	  and the following disclaimer.
//
//	* Neither the name of the authors nor the names 
//	  of its contributors may be used to endorse or 
//	  promote products derived from this software 
//	  without specific prior written permission.
//
//	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS 
//	AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED 
//	WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
//	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
//	FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
//	SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE 
//	FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
//	EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
//	NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
//	SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
//	INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
//	LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR 
//	TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN 
//	ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
//	ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
*******************************************************************/
// HookStdio.cpp: implementation of the CHookStdio class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HookStdio.h"

#include "io.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHookStdio::CHookStdio( DWORD dwStreamId, DWORD dwBufferSize )
{
  m_hRead = NULL;
  m_hWrite = NULL;
  m_hOriginal = NULL;
  
  // Hook stream if needed
  if ( dwStreamId ) Start( dwStreamId, dwBufferSize );
}

CHookStdio::~CHookStdio()
{	
  Stop();
}

BOOL CHookStdio::Start( DWORD dwStreamId, DWORD dwBufferSize )
{
  // Kill any current hook
  Stop();
  
  // Verify valid stream
  if (	STD_INPUT_HANDLE != dwStreamId &&
    STD_OUTPUT_HANDLE != dwStreamId &&
    STD_ERROR_HANDLE != dwStreamId )
    return FALSE;
  
  // Save stream id
  m_dwStreamId = dwStreamId;
  
  // Create pipe
  if ( !CreatePipe( &m_hRead, &m_hWrite, NULL, dwBufferSize ) )
  {	Stop(); return FALSE; }
  
  // Save current stream handle
  m_hOriginal = GetStdHandle( dwStreamId );
  
  // Set new stream handle
  if ( !SetStdHandle( dwStreamId, m_hWrite ) )
  {	Stop(); return FALSE; }
  
  // Associate stream handle
  int nStream = _open_osfhandle( (long)GetStdHandle( dwStreamId ), 0 );
  
  // Associate stream handle
  FILE* hfStream = _fdopen( nStream, "w" );
  
  // Hook appropriate stream
  switch ( dwStreamId )
  {
		case STD_INPUT_HANDLE :
      
      // Switch streams
      *stdin = *hfStream;
      
      break;
      
    case STD_OUTPUT_HANDLE :
      
      // Switch streams
      *stdout = *hfStream;
      
      // Disable stream buffering
      setvbuf( stdout, NULL, _IONBF, 0 );
      
      break;
      
    case STD_ERROR_HANDLE :
      
      // Switch streams
      *stderr = *hfStream;
      
      // Disable stream buffering
      setvbuf( stderr, NULL, _IONBF, 0 );
      
      break;
      
  } // end switch
  
  return TRUE;
}

void CHookStdio::Stop()
{
  if ( m_hOriginal )
  {
    SetStdHandle( m_dwStreamId, m_hOriginal );
    m_hOriginal = NULL;
  } // end if
  
  if ( m_hWrite )
  {
    // old   CloseHandle( m_hWrite );
    if(FindClose( m_hWrite )){
       m_hWrite = NULL;
    }
    
  } // end if
  
  if ( m_hRead )
  {
    CloseHandle( m_hRead );
    m_hRead = NULL;
  } // end if
}

DWORD CHookStdio::Read(LPVOID pBuf, DWORD dwSize)
{
  // Punt if no read handle
  if ( NULL == m_hRead || !pBuf || !dwSize )
  {
    return 0;
  }
  
  DWORD dwRead = 0;
  
  // Ensure there is data to read
  if ( !PeekNamedPipe( m_hRead, NULL, NULL, NULL, &dwRead, NULL ) || !dwRead )
    return 0;
  
  // Attempt to read from the stream
  if ( !ReadFile( m_hRead, pBuf, dwSize, &dwRead, NULL ) ) 
    return 0;
  
  // Check for error
  if ( !dwRead || dwRead > dwSize )
    return 0;
  
  // Return the number of bytes read
  return dwRead;
}

DWORD CHookStdio::Write(LPVOID pBuf, DWORD dwSize)
{
  // Punt if no write handle
  if ( NULL == m_hWrite || !pBuf || !dwSize ) 
  {
    return 0;
  }
  
  DWORD dwWritten = 0;
  
  // Attempt to write to the stream
  if ( !WriteFile( m_hWrite, pBuf, dwSize, &dwWritten, NULL ) ) 
    return 0;
  
  // Check for error
  if ( !dwWritten || dwWritten > dwSize )
    return 0;
  
  // Return the number of bytes written
  return dwWritten;
}
