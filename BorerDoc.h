// BorerDoc.h : interface of the CBorerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BorerDOC_H__B1B69ED1_9FCE_11D2_8CA4_0080ADB8683C__INCLUDED_)
#define AFX_BorerDOC_H__B1B69ED1_9FCE_11D2_8CA4_0080ADB8683C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "CCrystalTextBuffer.h"
#include "ParaDefi.h"



class CBorerDoc : public CDocument
{
  friend class CBorerView;
  
protected: // create from serialization only
  CBorerDoc();
  DECLARE_DYNCREATE(CBorerDoc)
    
    // Attributes
public:
  class CBorerTextBuffer : public CCrystalTextBuffer
  {
  private:
    CBorerDoc *m_pOwnerDoc;
  public:
    CBorerTextBuffer(CBorerDoc *pDoc) { m_pOwnerDoc = pDoc; };
    virtual void SetModified(BOOL bModified = TRUE)
		  { m_pOwnerDoc->SetModifiedFlag(bModified); };
  };
  
  CBorerTextBuffer m_xTextBuffer;  //文档内容
  LOGFONT m_lf;        //字体
  int m_nPortIndex;    //测试序列号
  
  CString m_strInifile; //终端配置文件
  
  int m_nAutoSend; //自动发送
  int m_nCreateReport; //是否生成报告
  
  int m_nTestScript;						//是否处在脚本调试状态
  int m_nTimeSleep;						//设置脚本调试时的延迟时间
  int m_nWaitoutTime;						//设置等待时间
  int m_nGetValueTime;						//设置等待查询数据包时间
  int m_nKeepTime;                         //长按键时间
  
  CString m_strDocFile;					//脚本文件名称
  CString m_strHeadPath;					//头文件路径
  CString m_strProjectFile;				//项目文件名称
  
  // Operations
  public:
    void InitRuntime();
    void NirvanaData();
    
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CBorerDoc)
  public:
    virtual BOOL OnNewDocument();
    virtual void Serialize(CArchive& ar);
    virtual void DeleteContents();
    virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
    virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
    virtual void OnCloseDocument();
    virtual BOOL SaveModified();
    virtual void SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU = TRUE);
    //}}AFX_VIRTUAL
    
    // Implementation
  public:
    virtual ~CBorerDoc();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
    
  protected:
    
    // Generated message map functions
  protected:
    //{{AFX_MSG(CBorerDoc)
    afx_msg void OnReadOnly();
    afx_msg void OnUpdateReadOnly(CCmdUI* pCmdUI);
    afx_msg void OnSavefilec();
    afx_msg void OnFilesaveas();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BorerDOC_H__B1B69ED1_9FCE_11D2_8CA4_0080ADB8683C__INCLUDED_)
