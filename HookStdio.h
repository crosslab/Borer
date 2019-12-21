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
// HookStdio.h: interface for the CHookStdio class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HOOKSTDIO_H__ED80AE58_E23C_400A_AC53_2A1E7ECB35A7__INCLUDED_)
#define AFX_HOOKSTDIO_H__ED80AE58_E23C_400A_AC53_2A1E7ECB35A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//==================================================================
// CHookStdio
//
/// Hooks the specified standard stream
/**
	Use this to hook the standard i/o streams

	Example:

	\code

	CHookStdio hs( STD_OUTPUT_HANDLE );

	printf( "Hello World!" );

	char buf[ 256 ];
	buf[ hs.Read( buf, sizeof( buf ) - 1 ) ] = 0;

	TRACE( buf );

	\endcode
	
*/
//==================================================================
class CHookStdio  
{
public:
	

	//==============================================================
	// Write()
	//==============================================================
	/// Writes data to the stream
	/**
		\param [in] pBuf		-	Buffer containing data to write
		\param [in] dwSize		-	Number of bytes to write
		
		\return Number of bytes actuall written or zero if error.
	
		\see 
	*/
	DWORD Write( LPVOID pBuf, DWORD dwSize );

	//==============================================================
	// Read()
	//==============================================================
	/// Reads data from the stream
	/**
		\param [in] pBuf		-	Buffer that receives the data
		\param [in] dwSize		-	Size of buffer in pBuf
		
		\return Number of bytes actually read
	
		\see 
	*/
	DWORD Read( LPVOID pBuf, DWORD dwSize );

	//==============================================================
	// Stop()
	//==============================================================
	/// Unhooks any stream
	void Stop();

	//==============================================================
	// Start()
	//==============================================================
	///	Hooks the specified stream
	/**
		\param [in] dwStreamId		-	Standard stream ID
											- STD_INPUT_HANDLE		=	Standard input handle 
											- STD_OUTPUT_HANDLE		=	Standard output handle 
											- STD_ERROR_HANDLE		=	Standard error handle 
		\param [in] dwBufferSize	-	The size buffer to use.
		
		\return Non-zero if success
	
		\see CHookStdio(), Stop()
	*/
	BOOL Start( DWORD dwStreamId, DWORD dwBufferSize = 0 );

	//==============================================================
	// CHookStdio()
	//==============================================================
	/// Constructor
	/**
		\param [in] dwStreamId	-	Standard stream ID
										- STD_INPUT_HANDLE		=	Standard input handle 
										- STD_OUTPUT_HANDLE		=	Standard output handle 
										- STD_ERROR_HANDLE		=	Standard error handle 
		\param [in] dwBufferSize	-	The size buffer to use.

		The default argument of zero, will not hook any stream

		\see Start(), Stop
	*/
	CHookStdio( DWORD dwStreamId = 0, DWORD dwBufferSize = 0  );

	/// Destructor
	virtual ~CHookStdio();

	//==============================================================
	// GetReadHandle()
	//==============================================================
	/// Returns the read handle
	HANDLE GetReadHandle() { return m_hRead; }

	//==============================================================
	// GetReadHandle()
	//==============================================================
	/// Returns the read handle
	HANDLE GetWriteHandle() { return m_hRead; }

private:

	/// The stream that is hooked
	DWORD					m_dwStreamId;

	/// Write handle
	HANDLE					m_hWrite;

	/// Read handle
	HANDLE					m_hRead;

	/// Original handle
	HANDLE					m_hOriginal;

};

#endif // !defined(AFX_HOOKSTDIO_H__ED80AE58_E23C_400A_AC53_2A1E7ECB35A7__INCLUDED_)
