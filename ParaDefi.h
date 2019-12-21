/**********************************************************************/
/*                          Em_GlobalStruct.h
/* 
/*LCD,KEYBOARD,MESSAGE 数据结构.
/*
/**********************************************************************/

#ifndef _EM_GLOBAL_
#define _EM_GLOBAL_

#include <stdio.h>
#include <afxwin.h>
#include <afxtempl.h>

/*****************键盘属性************************************/
#define KEY_MAX_NUM		30					//键盘按键总数
#define KEY_NAME_MAX    10					//按键名称最大字符数
#define KEY_ARRIB_NUM	7					//按键属性总数

/*****************消息属性************************************/
#define MAX_MSGCONTENT_SIZE				255     //消息最大数量
#define MAX_MESSAGE_SIZE				256     //消息最大数量
#define MAX_MSGNAME_SIZE                1024
#define MAX_CONTENT_SIZE				20    //最大数量
#define MSG_ARRIB_NUM	                10    //按键属性总数
#define MAX_POINT_SIZE					30     //点最大数量
#define MAX_MESSAGECONTENT_SIZE			256     //脚本文件命令名称最大长度



#define MAX_SECTION_SIZE				256     //消息最大数量

#define EMMSG m_MsgAttrib.msg_attrib
#define WM_MSG_ADD	(WM_APP + 0x0100)            //添加脚本命令
#define WM_MSG_INPUT (WM_APP + 0x0101)        //添加输入类表内容

#define WM_GOODBYE (WM_APP + 0x0102)               //手机界面消失
#define WM_CREATHS (WM_APP + 0x0103)                //手机界面出现
#define WM_SHOWTAB1 (WM_APP + 0x0104)              //显示参数TAB控件的TAB1页
#define WM_HIDETAB1 (WM_APP + 0x0105)              //隐藏参数TAB控件的TAB1页
#define WM_DRAWKEYTREE (WM_APP + 0x0106)


#define WM_SETUP_MAT		(WM_APP + 0x0107)              
#define WM_SETUP_HANDSET    (WM_APP + 0x0108)
#define WM_SETUP_PCF        (WM_APP + 0x0109)

#define MMM_SHOW_GETDATA        (WM_APP + 0x0110)

#define MMM_UPDATE_SET      (WM_APP + 0x0111)

/*****************************数据结构******************************/
/***************************LCD属性************************/
typedef struct 
{
  int x;					//LCD位置
  int y;				 	//LCD位置
  
  int cx;					//X分辨率
  int cy;					//Y分辨率
  
  
}LCD_ATTRIB_STRUCT;

typedef CArray<CPoint,CPoint> CPointArray;//键盘点序列
/***************************按键属性************************/
typedef struct 
{	
  char name[KEY_NAME_MAX+1];			//按键名称
  
  int code;		            		//按键键码
  
  int hotkey;			            	//按键热键
  
  int pointnum;                       //点总数
  
  CPoint   point[MAX_POINT_SIZE];     //各点定义
  
}KEY_ATTRIB_STRUCT;

typedef CArray<KEY_ATTRIB_STRUCT,KEY_ATTRIB_STRUCT> KeyAttribArray;

/***************************键盘面板属性************************/

typedef struct 
{
  int x;					//键盘面板X位置
  int y;					//键盘面板Y位置
  int cx;					//键盘面板X尺寸
  int cy;					//键盘面板Y尺寸
  int bgclr;				//键盘面板颜色
}KEY_PANEL_STRUCT;


/***************************键盘属性************************/
typedef struct
{
  int allKeys;                             //键盘上按键数量
  
  int gType;                                 //按键消息类型
  int sid;                                  //按键消息发送模块ID
  int	did;                                  //按键消息接收模块ID
  char keymsgname[MAX_MSGNAME_SIZE];        //消息名称   MMIM_Key
  
  KEY_ATTRIB_STRUCT   attrib[KEY_MAX_NUM];   //按键属性
}KEYBOARD_ATTRIB_STRUCT;


/***************************消息属性************************/

typedef struct
{
  unsigned char	did;                                  //消息接收模块ID
  unsigned char	type;                                 //消息类型
  unsigned char	sid;                                  //消息发送模块ID
  unsigned char	length;                               //消息内容长度
  union 
  {
    unsigned	 char	content[MAX_MSGCONTENT_SIZE];     //消息内容
    
  }Union;
} EM_MESSAGE; 

typedef struct
{
  int code;                          //消息内容
  char name[MAX_MSGNAME_SIZE];       //消息内容名称
  
}MSG_CONTENT_ATTRIB;

typedef CArray<MSG_CONTENT_ATTRIB,MSG_CONTENT_ATTRIB> MsgContentArray;

typedef struct 
{
  char msgname[MAX_MSGNAME_SIZE];                //消息名称   MMIM_Alarm
  char description[MAX_MSGNAME_SIZE];            //描述     Alarm_Type(为了说明content的意义)
  int contenttype;                               //0 无内容   1  由COMBO选择    2 由edit填写
  int conentlength;                              //消息内容长度   256 edit中字符串实长
  int contenttotalnum;                           //如果是选择（contenttype ==1），共有contenttotalnum种选择
  MSG_CONTENT_ATTRIB content[MAX_CONTENT_SIZE];  //消息内容
  
} MSG_ADDITIONAL_ATTRIB;


typedef struct 
{
  EM_MESSAGE msg;                     //消息结构
  MSG_ADDITIONAL_ATTRIB attrib;       //消息属性
} MSG_ATTRIB_STRUCT;

typedef CArray<MSG_ATTRIB_STRUCT,MSG_ATTRIB_STRUCT> MsgAttribArray;

typedef struct 
{
  int allMsgs;                                       //消息总数
  MSG_ATTRIB_STRUCT msg_attrib[MAX_MESSAGE_SIZE];     //消息结构和属性
} MSG_STRUCT;


/******************************寄存器结构**********************************/
typedef struct 
{
  unsigned int startaddr;       //寄存器起始地址
  unsigned int endaddr;         //寄存器终止地址
  FILE *pffls;                  //纪录文件指针
  
} REG_ADDR_STRUCT;

/******************************MAT表结构**********************************/

typedef struct
{
  char message[MAX_MESSAGECONTENT_SIZE];        //脚本文件中命令名称
  
}TMessage;

typedef struct
{
 	char content[MAX_MSGNAME_SIZE];       //消息
  long itimeinterval;      //自动发送间隔
  
}AUTO_SEND;
typedef CArray<AUTO_SEND,AUTO_SEND> AutoSendArray;

typedef struct
{
  char code[MAX_MSGNAME_SIZE];       //模块代码
  char name[MAX_MSGNAME_SIZE];       //模块名称
  
}TASK_DEFINITION;
typedef CArray<TASK_DEFINITION,TASK_DEFINITION> TaskDefinitonArray;

typedef struct
{
 	char name[MAX_MSGNAME_SIZE];      
  char address[MAX_MSGNAME_SIZE];       
  char length[MAX_MSGNAME_SIZE];     
  
}VARIANT_DEFINITION;
typedef CArray<VARIANT_DEFINITION,VARIANT_DEFINITION> VariantDefinitonArray;

typedef struct 
{
  unsigned int size;                    
  CString content;   
  CString name;
  
} FLASH_ATTRIB_STRUCT;

typedef CArray<FLASH_ATTRIB_STRUCT,FLASH_ATTRIB_STRUCT> FlashArray;

typedef struct 
{
  unsigned int utype;              
  unsigned int begin_pos;
  unsigned int end_pos;
  int nIndex;
  CString svalue;   
  CString sname;
  
} MAT_ATTRIB_STRUCT;

typedef CArray<MAT_ATTRIB_STRUCT,MAT_ATTRIB_STRUCT> MatArray;

typedef struct 
{
  CString	sEndAddr;  //PCF 结束地址
  CString	sStartAddr; //PCF 开始地址
  CString	sName ;    //PCF 名称 
} PCF_ATTRIB_STRUCT;

typedef CArray<PCF_ATTRIB_STRUCT,PCF_ATTRIB_STRUCT> PcfArray;


#endif