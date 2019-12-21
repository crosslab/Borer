#if !defined(AFX_WORDDRIVE_H__2D30405E_C217_4FD6_80E3_A018295F99E7__INCLUDED_)
#define AFX_WORDDRIVE_H__2D30405E_C217_4FD6_80E3_A018295F99E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct _wdinfoopli{
  CString wdiModule;
  CString wdiOperator;
  CString wdiDate;
  CString wdiVersion;
  CString wdiScript;
  CString wdiResult;
  CString wdiItem;
}WDIINFO;

/////////////////////////////////////////////////////////////////////////////
// CWordDrive command target
class CWordDrive : public CObject
{
  // Operations
public:
  DECLARE_DYNCREATE(CWordDrive)
    
    CWordDrive();
  virtual ~CWordDrive();
  
  bool WDInit(CString &wdhPath,CString &wdiExe);
  bool WDTrack(WDIINFO *lsParam);
  bool WDFini();
  
  // Implementation
protected:
  _Application m_oWord ;
  Documents m_aryDoc;
  _Document m_oDoc;
  int   m_clueTbl;  // 标题编号
  int   m_nTotalRow;  // 总计有多少行记录
  
};

#endif // !defined(AFX_WORDDRIVE_H__2D30405E_C217_4FD6_80E3_A018295F99E7__INCLUDED_)
