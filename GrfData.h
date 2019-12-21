#if !defined(AFX_GRFDATA_H__9F5D9FC5_5B54_4A90_BE03_24D508C29AE2__INCLUDED_)
#define AFX_GRFDATA_H__9F5D9FC5_5B54_4A90_BE03_24D508C29AE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CommonDef.h"
/////////////////////////////////////////////////////////////////////////////
// CGrfData - used for docking serialization
class CGrfData : public CObject
{
  DECLARE_SERIAL(CGrfData)
    CGrfData();
  
public:
  // Attributes
  //曲线当前的绘制位置（绘制到第几个点）
  double   VW_vMult;  //Y = Data*Draw_ky
  double   VW_hStep;  //Y = Data*Draw_ky
  CPen     grf_Pen;
  
  int      VW_hPtr;
  int      VW_Data[DRAW_HORZ_POINTS];
  
  HSM_ITEM    *VW_Item;
  int          VW_Doc;
  
public:
  // Operations
  
  // Implementation
protected:
  
public:
  ~CGrfData();
  virtual void Serialize(CArchive& ar);
};

#endif // !defined(AFX_GRFDATA_H__9F5D9FC5_5B54_4A90_BE03_24D508C29AE2__INCLUDED_)
