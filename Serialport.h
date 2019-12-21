/*
Module : SERIALPORT.H
Purpose: Declaration for an MFC wrapper class for serial ports
Created: PJN / 31-05-1999
History: None

  Copyright (c) 1999 by PJ Naughter.  
  All rights reserved.
  
*/



///////////////////// Macros / Structs etc //////////////////////////

#ifndef __SERIALPORT_H__
#define __SERIALPORT_H__



#define ERR_TXMCUOUT		8L
#define ERR_TXOUTGO			1L
#define ERR_TXHOOKON		2L
#define ERR_TXHOOKOFF		3L
#define ERR_NOMSGOUTGO		4L
#define ERR_NOMSGHOOKOFF	5L
#define ERR_NOMSGHOOKON		6L
#define ERR_WAIT			7L

/////////////////////////// Classes ///////////////////////////////////////////


////// Serial port exception class ////////////////////////////////////////////

void AfxThrowSerialException(DWORD dwError = 0);

class CSerialException : public CException
{
public:
  //Constructors / Destructors
  CSerialException(DWORD dwError);
  ~CSerialException();
  
  //Methods
#ifdef _DEBUG
  virtual void Dump(CDumpContext& dc) const;
#endif
  virtual BOOL GetErrorMessage(LPTSTR lpstrError, UINT nMaxError,	PUINT pnHelpContext = NULL);
  CString GetErrorMessage();
  
  //Data members
  DWORD m_dwError;
  
protected:
  DECLARE_DYNAMIC(CSerialException)
};



//// The actual serial port class /////////////////////////////////////////////
class CSerialPort : public CObject
{
public:
  //Constructors / Destructors
  CSerialPort();
  virtual ~CSerialPort();
  
  //General Methods
  void PJNOpen();
  void PJNClose();
  
  void PJNAttach(HANDLE hComm);
  HANDLE PJNDetach();
  
  operator HANDLE() const { return port_hComm; };
  BOOL IsEngrossed() const { return port_hComm != INVALID_HANDLE_VALUE; };
#ifdef _DEBUG
  void CSerialPort::Dump(CDumpContext& dc) const;
#endif
  
  //Reading / Writing Methods
  DWORD PJNRead(void* lpBuf, DWORD dwCount);
  BOOL PJNRead(void* lpBuf, DWORD dwCount, OVERLAPPED& overlapped);
  void PJNReadEx(void* lpBuf, DWORD dwCount);
  
  DWORD PJNWrite(const void* lpBuf, DWORD dwCount);
  BOOL PJNWrite(const void* lpBuf, DWORD dwCount, OVERLAPPED& overlapped);
  void PJNWriteEx(const void* lpBuf, DWORD dwCount);
  
  void TransmitChar(char cChar);
  void GetOverlappedResult(OVERLAPPED& overlapped, DWORD& dwBytesTransferred, BOOL bWait);
  void PJNCancelIo();
  
  //Configuration Methods
  void GetConfig(COMMCONFIG& config);
  static void GetDefaultConfig(int nPort, COMMCONFIG& config);
  void SetConfig(COMMCONFIG& Config);
  static void SetDefaultConfig(int nPort, COMMCONFIG& config);
  
  //Misc RS232 Methods
  void ClearBreak();
  void SetBreak();
  void ClearError(DWORD& dwErrors);
  void GetStatus(COMSTAT& stat);
  void GetState(DCB& dcb);
  void SetState(DCB& dcb);
  void Escape(DWORD dwFunc);
  void ClearDTR();
  void ClearRTS();
  void SetDTR();
  void SetRTS();
  void SetXOFF();
  void SetXON();
  void GetProperties(COMMPROP& properties);
  void GetModemStatus(DWORD& dwModemStatus); 
  
  //Timeouts
  void SetTimeouts(COMMTIMEOUTS& timeouts);
  void GetTimeouts(COMMTIMEOUTS& timeouts);
  void Set0Timeout();
  void Set0WriteTimeout();
  void Set0ReadTimeout();
  
  //Event Methods
  void SetMask(DWORD dwMask);
  void GetMask(DWORD& dwMask);
  void WaitEvent(DWORD& dwMask);
  void WaitEvent(DWORD& dwMask, OVERLAPPED& overlapped);
  
  //Queue Methods
  void PJNFlush();
  void PJNPurge(DWORD dwFlags);
  void TerminateOutstandingWrites();
  void TerminateOutstandingReads();
  void ClearWriteBuffer();
  void ClearReadBuffer();
  void Setup(DWORD dwInQueue, DWORD dwOutQueue);
  
  //Overridables
  virtual void OnCompletion(DWORD dwErrorCode, DWORD dwCount, LPOVERLAPPED lpOverlapped);
  
public:
  HANDLE port_hComm;       //Handle to the comms port
  
protected:
  BOOL   m_bOverlapped; //Is the port open in overlapped IO
  
  static void WINAPI _OnCompletion(DWORD dwErrorCode, DWORD dwCount, LPOVERLAPPED lpOverlapped); 
  
public:
  DECLARE_DYNAMIC(CSerialPort)
};


#endif //__SERIALPORT_H__