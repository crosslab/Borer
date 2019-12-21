#if !defined(AFX_ROBINBUFFER_H__9626BB4D_6F7B_4698_8366_8573E4D6B7DA__INCLUDED_)
#define AFX_ROBINBUFFER_H__9626BB4D_6F7B_4698_8366_8573E4D6B7DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CRobinBuffer command target
class CRobinBuffer : public CMemMapFile
{
  // Operations
public:
  CRobinBuffer();
  virtual ~CRobinBuffer();
  
  void Inaugurate(int iLimit);
  void TuneupAdded(int tuneAdded);
  void TuneupLeft(int tuneLeft);
  
  int  cntleft();
  int  ptrFree();
  
  unsigned char  *WritingPointer();
  unsigned char  *ProcessingPointer();
  
private:	  
  int    rdr_Free;      //下次缓冲区写入的位置偏移
  int    rdr_Left;      //测试剩余数据个数
  int    rdr_Limit;
  
  // Implementation
protected:
  DECLARE_DYNAMIC(CRobinBuffer)
};

#endif // !defined(AFX_ROBINBUFFER_H__9626BB4D_6F7B_4698_8366_8573E4D6B7DA__INCLUDED_)
