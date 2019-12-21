/*****************************************************************************/
/*                                                                           */
/*    FileName: Em_InitGlobal.c                                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*    Description    : 初始化LCD,KEYBOARD,MESSAGE属性                        */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*    Author         : hanqiyi                                               */
/*    developed on   : 05/16/2003                                            */
/*    last update    : 05/16/2003                                            */
/*                                                                           */
/*****************************************************************************/
#include "stdafx.h"
#include <windows.h>
#include <malloc.h>
#include <stdio.h>

#include <assert.h>
#include "Borer.h"
#include "ParaDefi.h"


#define MAX_BUF_SIZE			10     
#define FLASH_ADDR_VALUE 0
#define MAT_CONST_VALUE  1

unsigned int MATADDRESS;
extern char *Trim(char *UsedStr);

/*****************初始化 MESSAGE属性******************************/
bool CParaDefi::PromptMsgs()
{
/*	int i = 0;
	int j = 0;
	CString strMsgName = _T("");
	
	CXMLProfile xmlProfile(m_fileTrack);
	xmlProfile.loadProfile();

	m_MsgAttrib.allMsgs = xmlProfile.getProfileInt("MESSAGES","MsgTotalNum",0);
	
	if(0 == m_MsgAttrib.allMsgs || m_MsgAttrib.allMsgs > MAX_MESSAGE_SIZE)
	{
		return false;
	}
	
	for(i=0; i<m_MsgAttrib.allMsgs; i++)
	{
		strMsgName.Format("Msg%03d_MsgName",i);
		xmlProfile.getProfileString("MESSAGES",strMsgName,"",EMMSG[i].attrib.msgname,MAX_MSGNAME_SIZE);
		Trim(EMMSG[i].attrib.msgname);
		
		strMsgName.Format("Msg%03d_MsgType",i);
		EMMSG[i].msg.type = (unsigned char)xmlProfile.getProfileInt("MESSAGES",strMsgName,0);
	
		strMsgName.Format("Msg%03d_MsgSId",i);
		EMMSG[i].msg.sid = (unsigned char)xmlProfile.getProfileInt("MESSAGES",strMsgName,0);

		strMsgName.Format("Msg%03d_MsgDId",i);
		EMMSG[i].msg.did = (unsigned char)xmlProfile.getProfileInt("MESSAGES",strMsgName,0);
		
		strMsgName.Format("Msg%03d_ContentType",i);
		EMMSG[i].attrib.contenttype = xmlProfile.getProfileInt("MESSAGES",strMsgName,0);
		
		strMsgName.Format("Msg%03d_Msglength",i);
		EMMSG[i].attrib.conentlength = xmlProfile.getProfileInt("MESSAGES",strMsgName,0);

		strMsgName.Format("Msg%03d_MsgContentTotalNum",i);		
		EMMSG[i].attrib.contenttotalnum = xmlProfile.getProfileInt("MESSAGES",strMsgName,0);
		
		strMsgName.Format("Msg%03d_Description",i);
		xmlProfile.getProfileString("MESSAGES",strMsgName,"",EMMSG[i].attrib.description,MAX_MSGNAME_SIZE);
		Trim(EMMSG[i].attrib.msgname);
	
		if (EMMSG[i].attrib.contenttype ==1)
		{		
			for(j=0; j<EMMSG[i].attrib.contenttotalnum; j++)
			{
				strMsgName.Format("Msg%03d_MsgContentcode%02d",i,j);
				EMMSG[i].attrib.content[j].code = xmlProfile.getProfileInt("MESSAGES",strMsgName,0);
				
				strMsgName.Format("Msg%03d_MsgContentname%02d",i,j);
				xmlProfile.getProfileString("MESSAGES",strMsgName,"",EMMSG[i].attrib.content[j].name,MAX_MSGNAME_SIZE);
				Trim(EMMSG[i].attrib.content[j].name);
	
			}
		}
	}
	*/
	return true;
}


/*****************初始化 KEYBOARD属性******************************/
bool CParaDefi::PromptKeys()
{
/*	
	int i = 0;
	int j = 0;
	CXMLProfile xmlProfile(m_fileTrack);
	xmlProfile.loadProfile();

	CString strMsgName = _T("");
	
	m_KeyAttrib.allKeys = xmlProfile.getProfileInt("KEYS", "KeyTotalNum",0);
	
	if(0 == m_KeyAttrib.allKeys || m_KeyAttrib.allKeys > KEY_MAX_NUM)
	{
		return false;
	}
	
	m_KeyAttrib.gType = xmlProfile.getProfileInt("KEYS", "Type",0);
	m_KeyAttrib.sid = xmlProfile.getProfileInt("KEYS", "SID",0);
	m_KeyAttrib.did = xmlProfile.getProfileInt("KEYS", "DID",0);	
	
	xmlProfile.getProfileString("KEYS", "Name","",m_KeyAttrib.keymsgname,KEY_NAME_MAX);
	Trim(m_KeyAttrib.attrib[i].name);
	sprintf(m_strKey,m_KeyAttrib.keymsgname);
	
	
	for(i=0; i<m_KeyAttrib.allKeys; i++)
	{
		strMsgName.Format("%s%02d%s","Key",i,"_Name");
		xmlProfile.getProfileString("KEYS", strMsgName,"",m_KeyAttrib.attrib[i].name,KEY_NAME_MAX);
		Trim(m_KeyAttrib.attrib[i].name);
		
		strMsgName.Format("%s%02d%s","Key",i,"_Code");
		m_KeyAttrib.attrib[i].code   = xmlProfile.getProfileInt("KEYS", strMsgName,0);
		
		strMsgName.Format("%s%02d%s","Key",i,"_HotKey");
		m_KeyAttrib.attrib[i].hotkey = xmlProfile.getProfileInt("KEYS", strMsgName,0);
		
		//////////////键盘点序列
		strMsgName.Format("%s%02d%s","Key",i,"_PointlistNum");
		m_KeyAttrib.attrib[i].pointnum=xmlProfile.getProfileInt("KEYS", strMsgName,0);
	
		for(int j=0;j<m_KeyAttrib.attrib[i].pointnum;j++)
		{

			strMsgName.Format("%s%02d%s%02d%s","Key",i,"Point",j,"_x");
			m_KeyAttrib.attrib[i].point[j].x=xmlProfile.getProfileInt("KEYS", strMsgName,0);
			
			strMsgName.Format("%s%02d%s%02d%s","Key",i,"Point",j,"_y");
			m_KeyAttrib.attrib[i].point[j].y=xmlProfile.getProfileInt("KEYS", strMsgName,0);
		}
	}
	*/
	return true;

}



//初始化任务定义设置
bool CParaDefi::PromptTasks()
{
	return true;

}

//初始化变量定义设置
bool CParaDefi::PromptVars()
{
	CString str;
	int icount;
	VARIANT_DEFINITION variantDefinition;
	m_VariantArray.RemoveAll();
	CXMLProfile xmlProfile(m_fileTrack);
	xmlProfile.loadProfile();

	icount=	xmlProfile.getProfileInt("VARIANTDEFINITON","VariantTotalNum",0);
    for(int i=0;i<icount;i++)
	{
		str.Format("VariantName%02d",i);
		xmlProfile.getProfileString("VARIANTDEFINITON",str,"",variantDefinition.name,255);

		str.Format("VariantAddress%02d",i);
		xmlProfile.getProfileString("VARIANTDEFINITON",str,"",variantDefinition.address,255);
		Trim(variantDefinition.address);
	
		str.Format("VariantLen%02d",i);
		xmlProfile.getProfileString("VARIANTDEFINITON",str,"",variantDefinition.length,255);
		m_VariantArray.Add(variantDefinition);
	}
	return true;

}
/*****************初始化 MESSAGE属性******************************/
bool CParaDefi::InitMsgAttrib()
{
	int i = 0;
	int j = 0;

	char Key_Name[][30]={"Msg00_MsgName","Msg00_MsgType","Msg00_MsgSId","Msg00_MsgDId",
		"Msg00_ContentType","Msg00_Msglength","Msg00_MsgContentTotalNum",
		"Msg00_MsgContentcode00","Msg00_MsgContentname00",
		"Msg00_Description"};
	
	m_MsgAttrib.allMsgs = ReadIniInt("MSG","MsgTotalNum",0,m_fileTrack);
	
	if(0 == m_MsgAttrib.allMsgs || m_MsgAttrib.allMsgs > MAX_MESSAGE_SIZE)
	{
		//		Message1("Error","Invalid MsgTotalNum!","return..."," Ok ");
		return false;
	}
	
	for(i=0; i<m_MsgAttrib.allMsgs; i++)
	{
		
		ReadIniString("MSG",Key_Name[0],"",EMMSG[i].attrib.msgname,MAX_MSGNAME_SIZE,m_fileTrack);
		Trim(EMMSG[i].attrib.msgname);
		
		EMMSG[i].msg.type = (unsigned char)ReadIniInt("MSG",Key_Name[1],0,m_fileTrack);
		EMMSG[i].msg.sid = (unsigned char)ReadIniInt("MSG",Key_Name[2],0,m_fileTrack);
		EMMSG[i].msg.did = (unsigned char)ReadIniInt("MSG",Key_Name[3],0,m_fileTrack);
		
		EMMSG[i].attrib.contenttype = ReadIniInt("MSG",Key_Name[4],0,m_fileTrack);
		EMMSG[i].attrib.conentlength = ReadIniInt("MSG",Key_Name[5],0,m_fileTrack);
		
		EMMSG[i].attrib.contenttotalnum = ReadIniInt("MSG",Key_Name[6],0,m_fileTrack);
		
		ReadIniString("MSG",Key_Name[9],"",EMMSG[i].attrib.description,MAX_MSGNAME_SIZE,m_fileTrack);
		Trim(EMMSG[i].attrib.msgname);
		
		
		for(j=0; j<EMMSG[i].attrib.contenttotalnum; j++)
		{
			EMMSG[i].attrib.content[j].code = ReadIniInt("MSG",Key_Name[7],0,m_fileTrack);
			
			ReadIniString("MSG",Key_Name[8],"",EMMSG[i].attrib.content[j].name,MAX_MSGNAME_SIZE,m_fileTrack);
			Trim(EMMSG[i].attrib.content[j].name);
			
			Key_Name[7][20] = (char) ( j + 1 ) / 10 + 48;
			Key_Name[7][21] = (char) ( j + 1 ) % 10 + 48;
			
			Key_Name[8][20] = Key_Name[7][20];
			Key_Name[8][21] = Key_Name[7][21];
		}
		
		Key_Name[7][20] = 48;
		Key_Name[7][21] = 48;
		
		Key_Name[8][20] = Key_Name[7][20];
		Key_Name[8][21] = Key_Name[7][21];
		
		
		for(j=0; j<MSG_ARRIB_NUM; j++)
		{
			Key_Name[j][3] =(char)  ( i + 1 ) / 10 + 48;
			Key_Name[j][4] =(char)  ( i + 1 ) % 10 + 48;
		}
	}
	
	return true;
}

/*****************初始化 KEYBOARD属性******************************/
bool CParaDefi::InitKeyAttrib()
{
	
	int i = 0;
	int j = 0;
	
	char Key_Name[][13]={"Key00_x","Key00_y","Key00_cx","Key00_cy","Key00_Name","Key00_Code","Key00_HotKey"};
	
	m_KeyAttrib.allKeys = ReadIniInt("KEY","KeyTotalNum",0,m_fileTrack);
	
	if(0 == m_KeyAttrib.allKeys || m_KeyAttrib.allKeys > KEY_MAX_NUM)
	{
		return false;
	}
	
	m_KeyAttrib.gType = ReadIniInt("KEY","type",0,m_fileTrack);
	m_KeyAttrib.sid = ReadIniInt("KEY","sid",0,m_fileTrack);
	m_KeyAttrib.did = ReadIniInt("KEY","did",0,m_fileTrack);	
	
	ReadIniString("KEY","Name","",m_KeyAttrib.keymsgname,KEY_NAME_MAX,m_fileTrack);
	Trim(m_KeyAttrib.attrib[i].name);
	sprintf(m_strKey,m_KeyAttrib.keymsgname);
	
	
	for(i=0; i<m_KeyAttrib.allKeys; i++)
	{
		ReadIniString("KEY",Key_Name[4],"",m_KeyAttrib.attrib[i].name,KEY_NAME_MAX,m_fileTrack);
		Trim(m_KeyAttrib.attrib[i].name);
		
		m_KeyAttrib.attrib[i].code   = ReadIniInt("KEY",Key_Name[5],0,m_fileTrack);
		m_KeyAttrib.attrib[i].hotkey = ReadIniInt("KEY",Key_Name[6],0,m_fileTrack);
		
		for(j=0; j<KEY_ARRIB_NUM; j++)
		{
			
			Key_Name[j][3] =(char)  ( i + 1 ) / 10 + 48;
			Key_Name[j][4] =(char)  ( i + 1 ) % 10 + 48;
			
		}
		//////////////键盘点序列
		CString strkeylist;
		int ipointnum;
		strkeylist.Format("Key%02dPointlist",i); 
		ipointnum=ReadIniInt(strkeylist,"listnum",0,m_fileTrack);
		m_KeyAttrib.attrib[i].pointnum=ipointnum;
		for(int j=0;j<ipointnum;j++)
		{
			CString  strpointx,strpointy;
			strpointx.Format("point%02d_x",j);
			strpointy.Format("point%02d_y",j);
			m_KeyAttrib.attrib[i].point[j].x=ReadIniInt(strkeylist,strpointx,0,m_fileTrack);
			m_KeyAttrib.attrib[i].point[j].y=ReadIniInt(strkeylist,strpointy,0,m_fileTrack);
		}
	}
	
	return true;

}

//初始化自动发送设置
bool CParaDefi::InitAutoSend()
{
	CString str;
	int icount;
	AUTO_SEND autosend;
	m_autosendarray.RemoveAll();
	icount=	ReadIniInt("TIMER","TimerTotalNum",0,m_fileTrack);
    for(int i=0;i<icount;i++)
	{
		str.Format("TimerMsg%02d",i);
		ReadIniString("TIMER",str,"",autosend.content,255,m_fileTrack);
		str.Format("TimerInterval%02d",i);
		autosend.itimeinterval=ReadIniInt("TIMER",str,0,m_fileTrack);
		m_autosendarray.Add(autosend);
	}
	return true;

}

//初始化任务定义设置
bool CParaDefi::InitTaskDefintion()
{
	CString str;
	int icount;
	TASK_DEFINITION taskDefinition;
	m_TaskDefinitonArray.RemoveAll();
	icount=	ReadIniInt("TASKDEFINITON","TaskTotalNum",0,m_fileTrack);
    for(int i=0;i<icount;i++)
	{
		str.Format("TaskName%02d",i);
		ReadIniString("TASKDEFINITON",str,"",taskDefinition.name,255,m_fileTrack);
		Trim(taskDefinition.name);
	
		str.Format("TaskCode%02d",i);
		ReadIniString("TASKDEFINITON",str,"",taskDefinition.code,255,m_fileTrack);
		m_TaskDefinitonArray.Add(taskDefinition);
	}
	return true;

}

//初始化变量定义设置
bool CParaDefi::InitVariantDefintion()
{
	CString str;
	int icount;
	VARIANT_DEFINITION variantDefinition;
	m_VariantArray.RemoveAll();
	icount=	ReadIniInt("VARIANTDEFINITON","VariantTotalNum",0,m_fileTrack);
    for(int i=0;i<icount;i++)
	{
		str.Format("VariantName%02d",i);
		ReadIniString("VARIANTDEFINITON",str,"",variantDefinition.name,255,m_fileTrack);

		str.Format("VariantAddress%02d",i);
		ReadIniString("VARIANTDEFINITON",str,"",variantDefinition.address,255,m_fileTrack);
		Trim(variantDefinition.address);
	
		str.Format("VariantLen%02d",i);
		ReadIniString("VARIANTDEFINITON",str,"",variantDefinition.length,255,m_fileTrack);
		m_VariantArray.Add(variantDefinition);
	}
	return true;

}

//初始化全部参数设置
bool CParaDefi::InitGlobalVar()
{
	m_MsgAttrib.allMsgs=0x00;
	m_KeyAttrib.allKeys=0x00;
	m_KeyAttrib.keymsgname[0]=0x00;

	m_autosendarray.RemoveAll();
	m_TaskDefinitonArray.RemoveAll();
	m_VariantArray.RemoveAll();

	m_FlashArray.RemoveAll();
	m_MatArray.RemoveAll();
	m_PcfArray.RemoveAll();

	if(m_fileTrack.IsEmpty())
	{
		return false;
	}

	CString igvStr =m_fileTrack;

	igvStr.MakeLower();
	if(igvStr.Find(".xml")==-1)
	{
	  if(!InitKeyAttrib())
	  {
		  return false;
	  }

	  if(!InitMsgAttrib()) 
	  {
		  return false;
	  }

	  InitAutoSend();
	  InitTaskDefintion();
	  InitVariantDefintion();
	}
	else
	{
	  if(!PromptKeys())
	  {
		return false ;
	  }

	  if(!PromptMsgs())
	  {
		return false;
	  }

	  PromptAutos();
	  PromptTasks();
	  PromptVars();
	}

	GetFlashFromIni();	
	GetMatFromIni();
	ReadPcfs();
	return  true;
}

/*****************保存 MESSAGE属性******************************/
bool CParaDefi::SaveMsgAttrib()
{
	if(m_MsgAttrib.allMsgs < 1)
	{
		return false;
	}
	CXMLProfile xmlProfile(m_fileTrack);
	xmlProfile.loadProfile();
    int i = 0;
	int j = 0;

	CString strMsgName = _T("");

	xmlProfile.writeProfileInt("MESSAGES", "MsgTotalNum", m_MsgAttrib.allMsgs);

	for(i=0 ;i<m_MsgAttrib.allMsgs;i++)
	{
		// 消息名称
		strMsgName.Format("Msg%03d_MsgName",i);
		xmlProfile.writeProfileString("MESSAGES", strMsgName, m_MsgAttrib.msg_attrib[i].attrib.msgname);
	
		//消息类型
		strMsgName.Format("Msg%03d_MsgType",i);
		xmlProfile.writeProfileInt("MESSAGES", strMsgName, m_MsgAttrib.msg_attrib[i].msg.type);
		
		//消息发送模块ID
		strMsgName.Format("Msg%03d_MsgSId",i);
		xmlProfile.writeProfileInt("MESSAGES", strMsgName, m_MsgAttrib.msg_attrib[i].msg.sid);
		
		//消息接收模块ID
		strMsgName.Format("Msg%03d_MsgDId",i);
		xmlProfile.writeProfileInt("MESSAGES", strMsgName, m_MsgAttrib.msg_attrib[i].msg.did);

		//消息内容类型
		strMsgName.Format("Msg%03d_ContentType",i);
		xmlProfile.writeProfileInt("MESSAGES", strMsgName, m_MsgAttrib.msg_attrib[i].attrib.contenttype);
		
		//消息内容的长度
		strMsgName.Format("Msg%03d_Msglength",i);
		xmlProfile.writeProfileInt("MESSAGES", strMsgName, m_MsgAttrib.msg_attrib[i].attrib.conentlength);

		// 消息描述
		strMsgName.Format("Msg%03d_Description",i);
		xmlProfile.writeProfileString("MESSAGES", strMsgName, m_MsgAttrib.msg_attrib[i].attrib.description);
	
		//消息内容的数量,如果是选择（contenttype ==1），共有contenttotalnum种选择
		strMsgName.Format("Msg%03d_MsgContentTotalNum",i);
		xmlProfile.writeProfileInt("MESSAGES", strMsgName, m_MsgAttrib.msg_attrib[i].attrib.contenttotalnum);	

		if (m_MsgAttrib.msg_attrib[i].attrib.contenttype ==1)
		{		
			for(j=0;j<m_MsgAttrib.msg_attrib[i].attrib.contenttotalnum;j++)
			{
				// 类型
				strMsgName.Format("Msg%03d_MsgContentcode%02d",i,j);
				xmlProfile.writeProfileInt("MESSAGES", strMsgName, m_MsgAttrib.msg_attrib[i].attrib.content[j].code);	

				// 名称
				strMsgName.Format("Msg%03d_MsgContentname%02d",i,j);
				xmlProfile.writeProfileString("MESSAGES", strMsgName, m_MsgAttrib.msg_attrib[i].attrib.content[j].name);				
			}
		}
	}
	
    xmlProfile.saveProfile();
	
	return true;
}

/*****************保存 KEYBOARD属性******************************/
bool CParaDefi::SaveKeyAttrib()
{
/*	if(m_KeyAttrib.allKeys < 1)
	{
		return false;
	}

	CXMLProfile xmlProfile(m_fileTrack);
	xmlProfile.loadProfile();

    int i = 0;
	int j = 0;

	CString strMsgName = _T("");

	// 键盘总数
	xmlProfile.writeProfileInt("KEYS", "KeyTotalNum", m_KeyAttrib.allKeys);

	// 键盘类型
	xmlProfile.writeProfileInt("KEYS", "Type", m_KeyAttrib.gType);	

	// 按键消息发送模块ID
	xmlProfile.writeProfileInt("KEYS", "SID", m_KeyAttrib.sid);	

	// 按键消息接收模块ID
	xmlProfile.writeProfileInt("KEYS", "DID", m_KeyAttrib.did);	
	
	// 按键消息名称
	xmlProfile.writeProfileString("KEYS","Name",m_KeyAttrib.keymsgname);

	for(i=0 ;i<m_KeyAttrib.allKeys;i++)
	{
		// 按键名称
		strMsgName.Format("%s%02d%s","Key",i,"_Name");
		xmlProfile.writeProfileString("KEYS", strMsgName, m_KeyAttrib.attrib[i].name);	
	
		// 按键键码
		strMsgName.Format("%s%02d%s","Key",i,"_Code");
		xmlProfile.writeProfileInt("KEYS", strMsgName, m_KeyAttrib.attrib[i].code);	

		// 按键热键
		strMsgName.Format("%s%02d%s","Key",i,"_HotKey");
		xmlProfile.writeProfileInt("KEYS", strMsgName, m_KeyAttrib.attrib[i].hotkey);	

		// 按键点总数
		strMsgName.Format("%s%02d%s","Key",i,"_PointlistNum");
		xmlProfile.writeProfileInt("KEYS", strMsgName, m_KeyAttrib.attrib[i].pointnum);
		
		// 所有点的描述

		for(j=0;j<m_KeyAttrib.attrib[i].pointnum ;j++)
		{
			// x
			strMsgName.Format("%s%02d%s%02d%s","Key",i,"Point",j,"_x");
			xmlProfile.writeProfileInt("KEYS", strMsgName, m_KeyAttrib.attrib[i].point[j].x);	
			
			// y
			strMsgName.Format("%s%02d%s%02d%s","Key",i,"Point",j,"_y");
			xmlProfile.writeProfileInt("KEYS", strMsgName, m_KeyAttrib.attrib[i].point[j].y);				
		}

	}
    xmlProfile.saveProfile();
*/
	return true;	
}

/*****************保存 自动发送消息设置******************************/
bool CParaDefi::SaveAutoSend()
{
/*	CString str;
	int icount;
	AUTO_SEND autosend;
	icount=m_autosendarray.GetSize();
	if(icount <1)
	{
		return false;
	}

	CXMLProfile xmlProfile(m_fileTrack);
	xmlProfile.loadProfile();

	xmlProfile.writeProfileInt("TIMER","TimerTotalNum",icount);

    for(int i=0;i<icount;i++)
	{
		autosend=m_autosendarray[i];
		str.Format("TimerMsg%02d",i);
		xmlProfile.writeProfileString("TIMER", str,autosend.content);
		str.Format("TimerInterval%02d",i);
		xmlProfile.writeProfileInt("TIMER", str,autosend.itimeinterval);
	}

	xmlProfile.saveProfile() ;
*/
	return true;

}

//保存查询变量设置
bool CParaDefi::SaveVariantPara()
{
	CString str;
	int icount;
	VARIANT_DEFINITION svpPar;
	icount=m_VariantArray.GetSize();
	if(icount < 1)
	{
		return false;
	}

	CXMLProfile xmlProfile(m_fileTrack);
	xmlProfile.loadProfile();

	xmlProfile.writeProfileInt("VARIANTDEFINITON", "VariantTotalNum",icount);

    for(int i=0;i<icount;i++)
	{
		svpPar=m_VariantArray[i];
		str.Format("VariantName%02d",i);
		xmlProfile.writeProfileString("VARIANTDEFINITON", str,svpPar.name);

		str.Format("VariantAddress%02d",i);
		xmlProfile.writeProfileString("VARIANTDEFINITON", str,svpPar.address);

		str.Format("VariantLen%02d",i);
		xmlProfile.writeProfileString("VARIANTDEFINITON", str,svpPar.length);
	}

	xmlProfile.saveProfile() ;

	return true;
}

//保存任务设置参数
bool CParaDefi::SaveTaskPara()
{
	CString str;
	int icount;
	TASK_DEFINITION taskDefinition;
	icount=m_TaskDefinitonArray.GetSize();
	if(icount < 1)
	{
		return false;
	}

	return true;

}

//保存设置参数
bool CParaDefi::SaveParas()
{
	CString strSP =m_fileTrack;
	
	m_fileTrack =m_fileTrack.Left(m_fileTrack.GetLength()-4);
	m_fileTrack =m_fileTrack +".Xml";

	if(!SaveMsgAttrib()) {
	}

	if(!SaveKeyAttrib()) {
	}

	SaveAutoSend();
	SaveTaskPara();
	SaveVariantPara();
	SaveFlashToIni();
	SaveMatToIni();
	MarkPcfs();

	m_fileTrack =strSP;
	return true;
}

void CParaDefi::ReadPcfs() 
{	
	UINT temp = 0;
	CString strTemp;
	int icount = 0;
	PCF_ATTRIB_STRUCT struPcfAttr;
	m_PcfArray.RemoveAll();

	CString igvStr =m_fileTrack;
	igvStr.MakeLower();
	BOOL bInit = FALSE;
	if(igvStr.Find(".xml")==-1)
	{
		icount=	ReadIniInt("RFC","SECTIONNum",0,m_fileTrack);


		if(icount == 0)
		{
			icount = 1 ;
			struPcfAttr.sName="PCF0" ;
			bInit = TRUE ;
		}
	    for(int i=0;i<icount;i++)
		{
			temp = ReadIniInt("RFC","StartAddr",0,m_fileTrack);
			strTemp.Format("%08X",temp);
			struPcfAttr.sStartAddr = strTemp ;
			
			temp = ReadIniInt("RFC","EndAddr",0,m_fileTrack);
			strTemp.Format("%08X",temp);
			struPcfAttr.sEndAddr = strTemp ;
			
			if(!bInit)
			{
				strTemp.Format("PCF%1d",i);
				char strBuf[50];
				ReadIniString("RFC",strTemp,"",strBuf,50,m_fileTrack);
				struPcfAttr.sName = strBuf;
			}
			m_PcfArray.Add(struPcfAttr);
		}
	}	
	else
	{
		
		CXMLProfile xmlProfile(m_fileTrack);
		xmlProfile.loadProfile();
		
		icount=	xmlProfile.getProfileInt("RFC","SECTIONNum",0);

		if(icount == 0)
		{
			icount = 1 ;
			struPcfAttr.sName="PCF0" ;
			bInit = TRUE ;
		}
	    for(int i=0;i<icount;i++)
		{
			temp = xmlProfile.getProfileInt("RFC","StartAddr",0);
			strTemp.Format("%08X",temp);
			struPcfAttr.sStartAddr = strTemp ;

			temp = xmlProfile.getProfileInt("RFC","EndAddr",0);
			strTemp.Format("%08X",temp);
			struPcfAttr.sEndAddr = strTemp ;

			if(!bInit)
			{
				strTemp.Format("PCF%1d",i);
				char strBuf[50];
				xmlProfile.getProfileString("RFC",strTemp,"",strBuf,50);
				struPcfAttr.sName = strBuf;
			}
					
			m_PcfArray.Add(struPcfAttr);
		}
	}
}

void CParaDefi::MarkPcfs() 
{
	CString str;
	int icount;
	PCF_ATTRIB_STRUCT struPcfAttr;
	icount=m_PcfArray.GetSize();
	if(icount < 1)
	{
		return ;
	}

	CXMLProfile xmlProfile(m_fileTrack);
	xmlProfile.loadProfile();

	xmlProfile.writeProfileInt("RFC","SECTIONNum",icount);

    for(int i=0;i<icount;i++)
	{
		struPcfAttr=m_PcfArray[i];
		char temp[10];
		sprintf(temp,"0x%s",struPcfAttr.sStartAddr);
		xmlProfile.writeProfileString("RFC","StartAddr",temp);

		sprintf(temp,"0x%s",struPcfAttr.sEndAddr);
		xmlProfile.writeProfileString("RFC", "EndAddr",temp);

		str.Format("PCF%1d",i);
		xmlProfile.writeProfileString("RFC", str,struPcfAttr.sName);
	}

	xmlProfile.saveProfile() ;
}

void CParaDefi::GetFlashFromIni()
{
	CString igvStr = m_fileTrack;
	igvStr.MakeLower();
	int Count =0 ;
	unsigned int Len = 0 ;
	FLASH_ATTRIB_STRUCT  FlashAttrib;
	
	if(igvStr.Find(".xml")==-1)
	{
		Count = ReadIniInt("FLASH","SECTIONNum",0,m_fileTrack);
		Len = ReadIniInt("FLASH","Len",0,m_fileTrack);

		char Section_Name[][20]={"FLASH00_Offset","FLASH00_Content","FLASH00_Name"};

		for(int i=0;i<Count;i++)
		{
			FlashAttrib.size = ReadIniInt("FLASH",Section_Name[0],0,m_fileTrack);
			char temp[255];

			ReadIniString("FLASH",Section_Name[1],"",temp,255,m_fileTrack);
			FlashAttrib.content.Format("%s",temp);
			FlashAttrib.content.TrimRight();

			ReadIniString("FLASH",Section_Name[2],"",temp,255,m_fileTrack);
			FlashAttrib.name.Format("%s",temp);
			FlashAttrib.name.TrimRight();

			m_FlashArray.Add(FlashAttrib);

			for(int j=0; j<3; j++)
			{
				Section_Name[j][5] = (char)(( i + 1 ) / 10 + 48);
				Section_Name[j][6] = (char)(( i + 1 ) % 10 + 48);
			}
		}		
	}


	unsigned int temp = 0;

	for(int k=Count-1;k>=0;k--)
	{
	
		FlashAttrib = m_FlashArray.ElementAt(k);
		temp = FlashAttrib.size;

		FlashAttrib.size = Len - FlashAttrib.size;
		m_FlashArray.ElementAt(k).size = FlashAttrib.size ;
		Len = temp;
	}
}


