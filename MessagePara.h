#if !defined(AFX_MESSAGEPARA_H__07BD14C8_6643_4797_BDD7_75F6925D502D__INCLUDED_)
#define AFX_MESSAGEPARA_H__07BD14C8_6643_4797_BDD7_75F6925D502D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MessagePara.h : header file
//
#include "ParaDefi.h"
/////////////////////////////////////////////////////////////////////////////
// CMessagePara dialog

class CMessagePara : public CDialog
{
	// Construction
public:
	CMessagePara(CWnd* pParent = NULL);   // standard constructor
  	bool m_nWaitMsg;                 //是否为等待消息 
	int m_itype;                    //消息类型
	MSG_ADDITIONAL_ATTRIB m_attrib; //消息属性
	int g_CurIndex;                 //选中序列号


	// Dialog Data
	//{{AFX_DATA(CMessagePara)
	enum { IDD = IDD_DLGMESSAGEPARA };
	CEdit	m_EdMessage;
	CComboBox	m_ComboMessage;
	CString	m_strmessage;
	//}}AFX_DATA
	
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMessagePara)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CMessagePara)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESSAGEPARA_H__07BD14C8_6643_4797_BDD7_75F6925D502D__INCLUDED_)
