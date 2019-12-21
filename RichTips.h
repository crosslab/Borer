#if !defined(AFX_RICHTIPS_H__32D79E83_BFA4_48B2_B7F6_B36F2EC2F322__INCLUDED_)
#define AFX_RICHTIPS_H__32D79E83_BFA4_48B2_B7F6_B36F2EC2F322__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef enum SHOW_KIND {
    OUTCONTENT,   //�����򱻲��Ե�ģ�鷢�͵�����
    OUTTRACE,	    //�����Զ��庯��ITTRACE�����ʾ��Ϣ
    INMSG,        // �����Ե�ģ��������͵���Ϣ����
    ININQIURE,    // �����Ե�ģ��������͵Ĳ�ѯ����ֵ
    INTRACE,      // �����Ե�ģ��������͵ĸ�ģ����ʾ��Ϣ
    TIPINFO       //������һЩϵͳ��ʾ��Ϣ
}SHOWKIND;      //������������

#define RTIP_FIND_SUBKEY	_T("RichTip\\Find")
#define RTIP_MATCH_CASE		_T("MatchCase")
#define RTIP_WHOLE_WORD		_T("WholeWord")
#define RTIP_FIND_WHAT		_T("FindWhat")

/////////////////////////////////////////////////////////////////////////////
// CRichTips window
class CRichTips : public CRichEditCtrl
{
  // Construction
public:
  CRichTips();
  
  // Attributes
public:
  
  // Operations
public:
  void SaveLog(CString &logPath);
  
  //	Text search helpers
  BOOL IsSelection();
  long GetSelHeader();
  long GetSelTail();
  
protected:
  void	InternalAppendText(LPCTSTR szInternal,bool bFiery,COLORREF clrFiery);
  
protected:
  CHARFORMAT  m_cfFiery;
  CHARFORMAT  m_cfCommon;
  
  char       *m_sevent; //��ʾ����ָ��
  
  //	Search parameters
  BOOL   m_bLastSeek;
  DWORD  m_dwLastSearchFlags;
  LPTSTR m_pszSought;
  
  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CRichTips)
  //}}AFX_VIRTUAL
  
  // Implementation
public:
  virtual ~CRichTips();
  afx_msg void OnTipClear();
  
  // Generated message map functions
protected:
  //{{AFX_MSG(CRichTips)
  afx_msg void OnTipCopy();
  afx_msg void OnTipCut();
  afx_msg void OnTipPaste();
  afx_msg void OnTipSave();
  afx_msg void OnTipFont();
  afx_msg void OnTipSelectAll();
  afx_msg void OnTipUndo();
  afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
  afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
  afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
  afx_msg void OnEditOutFind();
  afx_msg void OnEditOutRepeat();
  afx_msg void OnEditOutFindPrevious();
  //}}AFX_MSG
  
  LRESULT AddEditShow(WPARAM wParam, LPARAM lParam);
  DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RICHTIPS_H__32D79E83_BFA4_48B2_B7F6_B36F2EC2F322__INCLUDED_)
