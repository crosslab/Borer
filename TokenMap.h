#if !defined(AFX_TOKENMAP_H__281ED315_8D30_4758_8845_F0E0EF465260__INCLUDED_)
#define AFX_TOKENMAP_H__281ED315_8D30_4758_8845_F0E0EF465260__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TokenMap.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTokenMap window

class CTokenMap : public CMemMapFile
{
  // Construction
public:
  CTokenMap();
  virtual ~CTokenMap();
  long GetAddress(char *sVariableName);
  
protected:
  DECLARE_DYNAMIC(CTokenMap)
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOKENMAP_H__281ED315_8D30_4758_8845_F0E0EF465260__INCLUDED_)
