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
  
  CBorerTextBuffer m_xTextBuffer;  //�ĵ�����
  LOGFONT m_lf;        //����
  int m_nPortIndex;    //�������к�
  
  CString m_strInifile; //�ն������ļ�
  
  int m_nAutoSend; //�Զ�����
  int m_nCreateReport; //�Ƿ����ɱ���
  
  int m_nTestScript;						//�Ƿ��ڽű�����״̬
  int m_nTimeSleep;						//���ýű�����ʱ���ӳ�ʱ��
  int m_nWaitoutTime;						//���õȴ�ʱ��
  int m_nGetValueTime;						//���õȴ���ѯ���ݰ�ʱ��
  int m_nKeepTime;                         //������ʱ��
  
  CString m_strDocFile;					//�ű��ļ�����
  CString m_strHeadPath;					//ͷ�ļ�·��
  CString m_strProjectFile;				//��Ŀ�ļ�����
  
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
