/**********************************************************************/
/*                          Em_GlobalStruct.h
/* 
/*LCD,KEYBOARD,MESSAGE ���ݽṹ.
/*
/**********************************************************************/

#ifndef _EM_GLOBAL_
#define _EM_GLOBAL_

#include <stdio.h>
#include <afxwin.h>
#include <afxtempl.h>

/*****************��������************************************/
#define KEY_MAX_NUM		30					//���̰�������
#define KEY_NAME_MAX    10					//������������ַ���
#define KEY_ARRIB_NUM	7					//������������

/*****************��Ϣ����************************************/
#define MAX_MSGCONTENT_SIZE				255     //��Ϣ�������
#define MAX_MESSAGE_SIZE				256     //��Ϣ�������
#define MAX_MSGNAME_SIZE                1024
#define MAX_CONTENT_SIZE				20    //�������
#define MSG_ARRIB_NUM	                10    //������������
#define MAX_POINT_SIZE					30     //���������
#define MAX_MESSAGECONTENT_SIZE			256     //�ű��ļ�����������󳤶�



#define MAX_SECTION_SIZE				256     //��Ϣ�������

#define EMMSG m_MsgAttrib.msg_attrib
#define WM_MSG_ADD	(WM_APP + 0x0100)            //��ӽű�����
#define WM_MSG_INPUT (WM_APP + 0x0101)        //��������������

#define WM_GOODBYE (WM_APP + 0x0102)               //�ֻ�������ʧ
#define WM_CREATHS (WM_APP + 0x0103)                //�ֻ��������
#define WM_SHOWTAB1 (WM_APP + 0x0104)              //��ʾ����TAB�ؼ���TAB1ҳ
#define WM_HIDETAB1 (WM_APP + 0x0105)              //���ز���TAB�ؼ���TAB1ҳ
#define WM_DRAWKEYTREE (WM_APP + 0x0106)


#define WM_SETUP_MAT		(WM_APP + 0x0107)              
#define WM_SETUP_HANDSET    (WM_APP + 0x0108)
#define WM_SETUP_PCF        (WM_APP + 0x0109)

#define MMM_SHOW_GETDATA        (WM_APP + 0x0110)

#define MMM_UPDATE_SET      (WM_APP + 0x0111)

/*****************************���ݽṹ******************************/
/***************************LCD����************************/
typedef struct 
{
  int x;					//LCDλ��
  int y;				 	//LCDλ��
  
  int cx;					//X�ֱ���
  int cy;					//Y�ֱ���
  
  
}LCD_ATTRIB_STRUCT;

typedef CArray<CPoint,CPoint> CPointArray;//���̵�����
/***************************��������************************/
typedef struct 
{	
  char name[KEY_NAME_MAX+1];			//��������
  
  int code;		            		//��������
  
  int hotkey;			            	//�����ȼ�
  
  int pointnum;                       //������
  
  CPoint   point[MAX_POINT_SIZE];     //���㶨��
  
}KEY_ATTRIB_STRUCT;

typedef CArray<KEY_ATTRIB_STRUCT,KEY_ATTRIB_STRUCT> KeyAttribArray;

/***************************�����������************************/

typedef struct 
{
  int x;					//�������Xλ��
  int y;					//�������Yλ��
  int cx;					//�������X�ߴ�
  int cy;					//�������Y�ߴ�
  int bgclr;				//���������ɫ
}KEY_PANEL_STRUCT;


/***************************��������************************/
typedef struct
{
  int allKeys;                             //�����ϰ�������
  
  int gType;                                 //������Ϣ����
  int sid;                                  //������Ϣ����ģ��ID
  int	did;                                  //������Ϣ����ģ��ID
  char keymsgname[MAX_MSGNAME_SIZE];        //��Ϣ����   MMIM_Key
  
  KEY_ATTRIB_STRUCT   attrib[KEY_MAX_NUM];   //��������
}KEYBOARD_ATTRIB_STRUCT;


/***************************��Ϣ����************************/

typedef struct
{
  unsigned char	did;                                  //��Ϣ����ģ��ID
  unsigned char	type;                                 //��Ϣ����
  unsigned char	sid;                                  //��Ϣ����ģ��ID
  unsigned char	length;                               //��Ϣ���ݳ���
  union 
  {
    unsigned	 char	content[MAX_MSGCONTENT_SIZE];     //��Ϣ����
    
  }Union;
} EM_MESSAGE; 

typedef struct
{
  int code;                          //��Ϣ����
  char name[MAX_MSGNAME_SIZE];       //��Ϣ��������
  
}MSG_CONTENT_ATTRIB;

typedef CArray<MSG_CONTENT_ATTRIB,MSG_CONTENT_ATTRIB> MsgContentArray;

typedef struct 
{
  char msgname[MAX_MSGNAME_SIZE];                //��Ϣ����   MMIM_Alarm
  char description[MAX_MSGNAME_SIZE];            //����     Alarm_Type(Ϊ��˵��content������)
  int contenttype;                               //0 ������   1  ��COMBOѡ��    2 ��edit��д
  int conentlength;                              //��Ϣ���ݳ���   256 edit���ַ���ʵ��
  int contenttotalnum;                           //�����ѡ��contenttype ==1��������contenttotalnum��ѡ��
  MSG_CONTENT_ATTRIB content[MAX_CONTENT_SIZE];  //��Ϣ����
  
} MSG_ADDITIONAL_ATTRIB;


typedef struct 
{
  EM_MESSAGE msg;                     //��Ϣ�ṹ
  MSG_ADDITIONAL_ATTRIB attrib;       //��Ϣ����
} MSG_ATTRIB_STRUCT;

typedef CArray<MSG_ATTRIB_STRUCT,MSG_ATTRIB_STRUCT> MsgAttribArray;

typedef struct 
{
  int allMsgs;                                       //��Ϣ����
  MSG_ATTRIB_STRUCT msg_attrib[MAX_MESSAGE_SIZE];     //��Ϣ�ṹ������
} MSG_STRUCT;


/******************************�Ĵ����ṹ**********************************/
typedef struct 
{
  unsigned int startaddr;       //�Ĵ�����ʼ��ַ
  unsigned int endaddr;         //�Ĵ�����ֹ��ַ
  FILE *pffls;                  //��¼�ļ�ָ��
  
} REG_ADDR_STRUCT;

/******************************MAT��ṹ**********************************/

typedef struct
{
  char message[MAX_MESSAGECONTENT_SIZE];        //�ű��ļ�����������
  
}TMessage;

typedef struct
{
 	char content[MAX_MSGNAME_SIZE];       //��Ϣ
  long itimeinterval;      //�Զ����ͼ��
  
}AUTO_SEND;
typedef CArray<AUTO_SEND,AUTO_SEND> AutoSendArray;

typedef struct
{
  char code[MAX_MSGNAME_SIZE];       //ģ�����
  char name[MAX_MSGNAME_SIZE];       //ģ������
  
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
  CString	sEndAddr;  //PCF ������ַ
  CString	sStartAddr; //PCF ��ʼ��ַ
  CString	sName ;    //PCF ���� 
} PCF_ATTRIB_STRUCT;

typedef CArray<PCF_ATTRIB_STRUCT,PCF_ATTRIB_STRUCT> PcfArray;


#endif