#include "stdafx.h"
#include  <io.h>

#include "CommonDef.h"
#include "Borer.h"
#include "MainFrm.h"
#include "VbhExpression.h"

//extern CM2TestApp theApp;

/********************************************************************
GLOBALS for this file
The string arrays are the items in the dialog list controls.
*******************************************************************/

char *aryProduct[] ={"BIT",
"BYTE",
"WORD",
"DWD",
"UF16",
"F16",
"UF32",
"F32"
};

char *aryVisible[] ={"",
"显示",
"隐藏"
};


bool AlreadyBe(CStringArray &arySire,CString &strTip)
{
  for(int abLop=0;abLop<arySire.GetSize();abLop++) {
    if(arySire.GetAt(abLop)==strTip) {
      return true;
    }
  }
  
  return false;
}


bool ConfigV32Read(CString &feFile,int &v32Col,HSM_ITEM *v32Pro)
{
  char    bufV32[_MAX_PATH];
  CString sjSec,sjKey;
  int     sfLop,sjLop;
  
  CString sjStr,mmStr;
  CString sbStr,mbStr;
  
  GetPrivateProfileString(CWSTR_M2APP,HSMN_VWCNT,CWSTR_DFTINT,
    bufV32,_MAX_PATH,feFile);
  v32Col=atoi(bufV32);
  
  for(sfLop=0;sfLop<v32Col;sfLop++)	{
    sjSec.Format("%s%d",HSMN_VWITEM,sfLop);
    GetPrivateProfileString(sjSec,HSMN_VINAME,CWSTR_DFTSTR,
      v32Pro[sfLop].vi_Name.GetBuffer(_MAX_PATH),
      _MAX_PATH,feFile);
    v32Pro[sfLop].vi_Name.ReleaseBuffer();
    GetPrivateProfileString(sjSec,HSMN_VITYPE,CWSTR_DFTSTR,
      bufV32,_MAX_PATH,feFile);
    v32Pro[sfLop].vi_Type=(CM_DATA)DecipherTypes(bufV32);
    
    GetPrivateProfileString(sjSec,HSMN_VIEXPR,CWSTR_DFTSTR,
      v32Pro[sfLop].vi_Express.GetBuffer(_MAX_PATH),
      _MAX_PATH,feFile);
    v32Pro[sfLop].vi_Express.ReleaseBuffer();
    
    GetPrivateProfileString(sjSec,HSMN_VOBYTE,CWSTR_DFTSTR,
      bufV32,_MAX_PATH,feFile);
    v32Pro[sfLop].Start_Byte=atoi(bufV32);
    GetPrivateProfileString(sjSec,HSMN_VOBIT,CWSTR_DFTSTR,
      bufV32,_MAX_PATH,feFile);
    v32Pro[sfLop].Start_Bit=atoi(bufV32);
    
    GetPrivateProfileString(sjSec,HSMN_VILEN,CWSTR_DFTSTR,
      bufV32,_MAX_PATH,feFile);
    v32Pro[sfLop].vi_Lenght=atoi(bufV32);
    GetPrivateProfileString(sjSec,HSMN_VIENUM,CWSTR_DFTSTR,
      bufV32,_MAX_PATH,feFile);
    v32Pro[sfLop].vi_cStates=atoi(bufV32);
    
    GetPrivateProfileString(sjSec,HSMN_CHART,CWSTR_DFTSTR,
      v32Pro[sfLop].vi_Chart.GetBuffer(_MAX_PATH),_MAX_PATH,feFile);
    v32Pro[sfLop].vi_Chart.ReleaseBuffer();
	   
    GetPrivateProfileString(sjSec,HSMN_TINT,CWSTR_DFTSTR,
      v32Pro[sfLop].vi_Tint.GetBuffer(_MAX_PATH),_MAX_PATH,feFile);
    v32Pro[sfLop].vi_Tint.ReleaseBuffer();
    GetPrivateProfileString(sjSec,HSMN_OPEN,CWSTR_DFTSTR,
      v32Pro[sfLop].vs_Open.GetBuffer(_MAX_PATH),_MAX_PATH,feFile);
    v32Pro[sfLop].vs_Open.ReleaseBuffer();
    v32Pro[sfLop].vb_Airy=(v32Pro[sfLop].vs_Open==aryVisible[2]);
	   
    GetPrivateProfileString(sjSec,HSMN_VIMIN,CWSTR_DFTSTR,
      v32Pro[sfLop].vi_Min.GetBuffer(_MAX_PATH),_MAX_PATH,feFile);
    v32Pro[sfLop].vi_Min.ReleaseBuffer();
    v32Pro[sfLop].ii_Min=atoi(v32Pro[sfLop].vi_Min);
    
    GetPrivateProfileString(sjSec,HSMN_VIMAX,CWSTR_DFTSTR,
      v32Pro[sfLop].vi_Max.GetBuffer(_MAX_PATH),_MAX_PATH,feFile);
    v32Pro[sfLop].vi_Max.ReleaseBuffer();
    v32Pro[sfLop].ii_Max=atoi(v32Pro[sfLop].vi_Max);
    
    GetPrivateProfileString(sjSec,HSMN_VSState,CWSTR_DFTSTR,
      sjStr.GetBuffer(_MAX_PATH),_MAX_PATH,feFile);
    sjStr.ReleaseBuffer();
    GetPrivateProfileString(sjSec,HSMN_VSMemo,CWSTR_DFTSTR,
      mmStr.GetBuffer(_MAX_PATH),_MAX_PATH,feFile);
    mmStr.ReleaseBuffer();
    
    for(sjLop=0;sjLop<v32Pro[sfLop].vi_cStates;sjLop++){
      if(sjStr.Find(",")==-1) {
        sbStr=sjStr;
        sjStr.Empty();
      }else {
        sbStr=sjStr.Left(sjStr.Find(","));
        sjStr=sjStr.Right(sjStr.GetLength()-sjStr.Find(",")-1);
      }
      
      if(mmStr.Find(",")==-1) {
        mbStr=mmStr;
        mmStr.Empty();
      }else {
        mbStr=mmStr.Left(mmStr.Find(","));
        mmStr=mmStr.Right(mmStr.GetLength()-mmStr.Find(",")-1);
      }
      
      v32Pro[sfLop].vi_Value[sjLop]=atoi(sbStr);
      v32Pro[sfLop].vi_Memo[sjLop]=mbStr;
    }
  }
  
  for(sfLop=0;sfLop<v32Col;sfLop++)	{
    v32Pro[sfLop].vi_InrNo=sfLop;
  }
  return true;
}

bool ConfigV31Read(CString &v31File,int &v31Col,HSM_ITEM *v31Cfg)
{
  char  bufV31[_MAX_PATH];
  FILE *fpCfr;
  
  int   iLop;
  int   iNull;
  
  fpCfr =fopen(v31File,"r");
  
  //读入数据：
  fscanf(fpCfr,"%d",&v31Col);//设置的数据个数
  if(v31Col>DRAW_HORZ_POINTS) {
    v31Col-=DRAW_HORZ_POINTS;
  }else {
	   fscanf(fpCfr,"%d",&iLop);//设置的数据个数
     fscanf(fpCfr,"%d",&iLop);//设置的数据个数
  }
  
  for(iLop=0;iLop<v31Col;iLop++)	{
    v31Cfg[iLop].vi_Chart=CWSTR_DFTSTR;
    v31Cfg[iLop].vi_Tint=CWSTR_DFTSTR;
    v31Cfg[iLop].vs_Open=CWSTR_DFTSTR;
    v31Cfg[iLop].vb_Airy=false;
    
    v31Cfg[iLop].vi_Express=CWSTR_DFTSTR;
    v31Cfg[iLop].vi_Min=CWSTR_DFTSTR;
    v31Cfg[iLop].vi_Max=CWSTR_DFTSTR;
    
    fscanf(fpCfr,"%s",v31Cfg[iLop].vi_Name.GetBuffer(_MAX_PATH));
    v31Cfg[iLop].vi_Name.ReleaseBuffer();
    
    fscanf(fpCfr,"%s %d %d %d %d %s",
      bufV31,
      &(v31Cfg[iLop].Start_Byte),
      &(v31Cfg[iLop].Start_Bit),
      &(v31Cfg[iLop].vi_Lenght),
      &(v31Cfg[iLop].vi_cStates),
      &iNull);
    v31Cfg[iLop].vi_Type=(CM_DATA)DecipherTypes(bufV31);
    
    for(int j=0;j<v31Cfg[iLop].vi_cStates;j++)
    {
      fscanf(fpCfr,"%x %s",&(v31Cfg[iLop].vi_Value[j]),
			    	v31Cfg[iLop].vi_Memo[j].GetBuffer(_MAX_PATH));
      v31Cfg[iLop].vi_Memo[j].ReleaseBuffer();
    }
  }
  
  fclose(fpCfr);
  
  for(iLop=0;iLop<v31Col;iLop++)	{
    v31Cfg[iLop].vi_InrNo=iLop;
  }
  return true;
}

inline void TESTHR( HRESULT _hr )
{ if FAILED(_hr) throw(_hr); }

bool ReadXmlConfig(CString &feFile,int &xmlCols,HSM_ITEM *v32Cfg)
{
/*	int xmlCnt,xmlLop;

  try{
		IXMLDOMDocumentPtr      pXMLDoc;
    IXMLDOMNodeListPtr      pNodeList;
    IXMLDOMNodePtr          pViewNode;
    
      IXMLDOMNamedNodeMapPtr  pIXMLNodeMap;
      IXMLDOMNodePtr          pAttrNode;
      
        VARIANT varValue;
        HRESULT hr;
        
          CString sjStr,mmStr;
          CString sbStr,mbStr;
          
            hr =pXMLDoc.CreateInstance(__uuidof(DOMDocument));
            TESTHR(hr);
            
              pXMLDoc->async = false; // default - true,
              pXMLDoc->validateOnParse = true;		
              
                _variant_t varXml(feFile);
                hr =pXMLDoc->load(varXml);
                if(hr!=VARIANT_TRUE) {
                return false;
                }
                
                  pNodeList = pXMLDoc->documentElement->selectNodes(HSXML_XPATH);
                  xmlCols = pNodeList->Getlength();
                  
                    xmlCnt=0;
                    for(pViewNode =pNodeList->nextNode(); pViewNode;pViewNode= pNodeList->nextNode()) {
                    hr =pViewNode->get_attributes(&pIXMLNodeMap);
                    TESTHR(hr);
                    
                      pAttrNode=pIXMLNodeMap->getNamedItem(HSXML_VINAME);
                      pAttrNode->get_nodeValue(&varValue);
                      v32Cfg[xmlCnt].vi_Name.Format("%s",(char*)_bstr_t(varValue));
                      
                        pAttrNode=pIXMLNodeMap->getNamedItem(HSXML_VITYPE);
                        pAttrNode->get_nodeValue(&varValue);
                        v32Cfg[xmlCnt].vi_Type=(CM_DATA)DecipherTypes((char*)_bstr_t(varValue));
                        
                          pAttrNode=pIXMLNodeMap->getNamedItem(HSXML_VIEXPR);
                          pAttrNode->get_nodeValue(&varValue);
                          v32Cfg[xmlCnt].vi_Express.Format("%s",(char*)_bstr_t(varValue));
                          
                            pAttrNode=pIXMLNodeMap->getNamedItem(HSXML_VOBYTE);
                            pAttrNode->get_nodeValue(&varValue);
                            v32Cfg[xmlCnt].Start_Byte=atoi((char*)_bstr_t(varValue));
                            
                              pAttrNode=pIXMLNodeMap->getNamedItem(HSXML_VOBIT);
                              pAttrNode->get_nodeValue(&varValue);
                              v32Cfg[xmlCnt].Start_Bit=atoi((char*)_bstr_t(varValue));
                              
                                pAttrNode=pIXMLNodeMap->getNamedItem(HSXML_VILEN);
                                pAttrNode->get_nodeValue(&varValue);
                                v32Cfg[xmlCnt].vi_Lenght=atoi((char*)_bstr_t(varValue));
                                
                                  pAttrNode=pIXMLNodeMap->getNamedItem(HSXML_VIENUM);
                                  pAttrNode->get_nodeValue(&varValue);
                                  v32Cfg[xmlCnt].vi_cStates=atoi((char*)_bstr_t(varValue));
                                  
                                    pAttrNode=pIXMLNodeMap->getNamedItem(HSXML_GRAPH);
                                    pAttrNode->get_nodeValue(&varValue);
                                    v32Cfg[xmlCnt].vi_Chart.Format("%s",(char*)_bstr_t(varValue));
                                    
                                      pAttrNode=pIXMLNodeMap->getNamedItem(HSXML_TINGE);
                                      pAttrNode->get_nodeValue(&varValue);
                                      v32Cfg[xmlCnt].vi_Tint.Format("%s",(char*)_bstr_t(varValue));
                                      
                                        pAttrNode=pIXMLNodeMap->getNamedItem(HSXML_VISIBLE);
                                        pAttrNode->get_nodeValue(&varValue);
                                        v32Cfg[xmlCnt].vs_Open.Format("%s",(char*)_bstr_t(varValue));
                                        v32Cfg[xmlCnt].vb_Airy=(v32Cfg[xmlCnt].vs_Open==aryVisible[2]);
                                        
                                          pAttrNode=pIXMLNodeMap->getNamedItem(HSXML_VIMIN);
                                          pAttrNode->get_nodeValue(&varValue);
                                          v32Cfg[xmlCnt].vi_Min=(char*)_bstr_t(varValue);
                                          v32Cfg[xmlCnt].ii_Min=atoi(v32Cfg[xmlCnt].vi_Min);
                                          
                                            pAttrNode=pIXMLNodeMap->getNamedItem(HSXML_VIMAX);
                                            pAttrNode->get_nodeValue(&varValue);
                                            v32Cfg[xmlCnt].vi_Max=(char*)_bstr_t(varValue);
                                            v32Cfg[xmlCnt].ii_Max=atoi(v32Cfg[xmlCnt].vi_Max);
                                            
                                              pAttrNode=pIXMLNodeMap->getNamedItem(HSXML_VSState);
                                              pAttrNode->get_nodeValue(&varValue);
                                              sjStr.Format("%s",(char*)_bstr_t(varValue));
                                              
                                                pAttrNode=pIXMLNodeMap->getNamedItem(HSXML_VSMemo);
                                                pAttrNode->get_nodeValue(&varValue);
                                                mmStr.Format("%s",(char*)_bstr_t(varValue));
                                                
                                                  for(xmlLop=0;xmlLop<v32Cfg[xmlCnt].vi_cStates;xmlLop++){
                                                  if(sjStr.Find(",")==-1) {
                                                  sbStr=sjStr;
                                                  sjStr.Empty();
                                                  }else {
                                                  sbStr=sjStr.Left(sjStr.Find(","));
                                                  sjStr=sjStr.Right(sjStr.GetLength()-sjStr.Find(",")-1);
                                                  }
                                                  
                                                    if(mmStr.Find(",")==-1) {
                                                    mbStr=mmStr;
                                                    mmStr.Empty();
                                                    }else {
                                                    mbStr=mmStr.Left(mmStr.Find(","));
                                                    mmStr=mmStr.Right(mmStr.GetLength()-mmStr.Find(",")-1);
                                                    }
                                                    
                                                      v32Cfg[xmlCnt].vi_Value[xmlLop]=atoi(sbStr);
                                                      v32Cfg[xmlCnt].vi_Memo[xmlLop]=mbStr;
                                                      }
                                                      
                                                        xmlCnt++;
                                                        }
                                                        }catch(_com_error &e) {
                                                        dump_com_error(e);
                                                        return false;
                                                        }
                                                        
                                                          for(xmlLop=0;xmlLop<xmlCnt;xmlLop++)	{
                                                          v32Cfg[xmlLop].vi_InrNo=xmlLop;
  }*/
return true;
}

bool ConfigFileRead(CString &frFile,int &cfCol,HSM_ITEM *cfCfg)
{
  CFileFind findfile;
  if( !findfile.FindFile( frFile, 0 ))
  {
    CString strTip;
    strTip.Format(MBSTR_CFGLOST,frFile);
    AfxMessageBox(strTip);
    return false;
  }
  if((_access(frFile, 0x04)) ==-1) {
    CString strTip;
    
    strTip.Format(MBSTR_CFGLOST,frFile);
    AfxMessageBox(strTip);
    return false;
  }
  
  frFile.MakeUpper();
  if(frFile.Find(".XML")!=-1) {
    return ReadXmlConfig(frFile,cfCol,cfCfg);
  }
  
  char bufCR[_MAX_PATH];
  GetPrivateProfileString(CWSTR_M2APP,HSMN_VWCNT,CWSTR_DFTNEG,
    bufCR,_MAX_PATH,frFile);
  
  if(!lstrcmp(bufCR,CWSTR_DFTNEG)) {
    return ConfigV31Read(frFile,cfCol,cfCfg);
  }else {
    return ConfigV32Read(frFile,cfCol,cfCfg);
  }
}

void SM_W2A(COleVariant &oleVal,double &flCpr,CString &strCpr)
{
  switch(oleVal.vt) {
  case VT_I2:
    flCpr=oleVal.iVal;
    strCpr.Format("%d",oleVal.iVal);
    break;
    
  case VT_I4:
    flCpr=oleVal.lVal;
    strCpr.Format("%d",oleVal.lVal);
    break;
    
  case VT_R8:
    flCpr=oleVal.dblVal;
    strCpr.Format("%-.9f",oleVal.dblVal);
    break;
    
  case VT_DATE:
		  {
        CTime  time7;
        COleDateTime codt(oleVal.date);
        
        flCpr=oleVal.date;
        strCpr=codt.Format("%Y-%m-%d %H:%M:%S");
      }
      break;
      
  case VT_NULL:
		  {
        flCpr=0x00;
        strCpr.Empty();
      }
      break;
      
  case VT_BSTR:
		  {
        flCpr=0x00;
        strCpr=oleVal.bstrVal;
      }
      break;
      
  default :
    AfxMessageBox("Unexpected ole data");
    break;
  }
}

//bool m_HexText=true;
bool OleParser(HSM_ITEM *opInfo,COleVariant &oleVal,
               double &flCpr,CString &strCpr)
{
		CMainFrame  *pMyFrm =(CMainFrame*)AfxGetApp()->m_pMainWnd;//取主框架窗口指针
    
    switch(oleVal.vt) {
    case VT_I2:
      flCpr=oleVal.iVal;
      break;
      
    case VT_I4:
      flCpr=oleVal.lVal;
      break;
      
    case VT_DATE:
      {
        CTime  time7;
        COleDateTime codt(oleVal.date);
        
        flCpr=oleVal.date;
        strCpr=codt.Format("%Y-%m-%d %H:%M:%S");
        return true;
      }
      break;
      
    case VT_NULL:
      {
        flCpr=0x00;
        strCpr.Empty();
        return true;
      }
      break;
      
    case VT_BSTR:
      {
        flCpr=0x00;
        strCpr=oleVal.bstrVal;
        return true;
      }
      break;
      
    default :
      AfxMessageBox("Unexpected ole data");
      return false;
      break;
    }
    
    if((opInfo->vi_Type==DT_BYTE) || (opInfo->vi_Type==DT_BIT) ||
      (opInfo->vi_Type==DT_WORD) || (opInfo->vi_Type==DT_DWD)) {
      if(pMyFrm->m_bShowHex) {
        strCpr.Format("%-8x ",(int)flCpr);
      }else {
        strCpr.Format("%-8d ",(int)flCpr);
      }
    }else if(opInfo->vi_Type==DT_UF16) {
      strCpr.Format("%-.8f ",flCpr);
    }else if(opInfo->vi_Type==DT_F16) {
      strCpr.Format("%-.8f ",flCpr);
    }else if(opInfo->vi_Type==DT_UF32) {
      strCpr.Format("%-.9f",flCpr);
    }else if(opInfo->vi_Type==DT_F32) {
      strCpr.Format("%-.9f",flCpr);
    }else {
      return false;
    }
    
    return true;
}

bool ColParser(HSM_ITEM *cpInfo,unsigned char *cpBuf,
               double &flCpr,CString &strCpr)
{
  CMainFrame  *pMyFrm =(CMainFrame*)AfxGetApp()->m_pMainWnd;//取主框架窗口指针
  
  int    c_byte;
  int    ddLop;
  DWORD  dwCpr;
  
  __int16  c_int16;
  __int32  c_int32;
  BYTE    *pData;
  
  if(cpInfo->vi_Type==DT_BYTE) {
	   dwCpr =cpBuf[cpInfo->Start_Byte+3];
     
     if(pMyFrm->m_bShowHex)
     {
       strCpr.Format("%-8x ",dwCpr);
     }
     else 
     {
       strCpr.Format("%-8d ",dwCpr);
     }
     flCpr=dwCpr;
  }else if(cpInfo->vi_Type==DT_WORD) {
	   dwCpr =cpBuf[cpInfo->Start_Byte+3];//(-1+5)
     dwCpr =dwCpr*256;
     dwCpr =dwCpr + cpBuf[cpInfo->Start_Byte+4];
     
     if(pMyFrm->m_bShowHex) {
	      strCpr.Format("%-8x ",dwCpr);
     }else {
	      strCpr.Format("%-8d ",dwCpr);
     }
     flCpr=dwCpr;
  }else if(cpInfo->vi_Type==DT_BIT) {
	   dwCpr =cpBuf[cpInfo->Start_Byte+3];
     
     //移位操作
     c_byte =0;
     int Length =cpInfo->vi_Lenght;
     for(ddLop=0;ddLop<Length;ddLop++) {
       c_byte =c_byte*2+1;
     }
     
     Length =8-cpInfo->vi_Lenght-cpInfo->Start_Bit;
     for(ddLop=0;ddLop<Length;ddLop++) {
       c_byte =c_byte*2;
     }
     
     dwCpr=dwCpr&c_byte;
     for(ddLop=0;ddLop<Length;ddLop++) {
       dwCpr=dwCpr/2;
     }
     
     if(pMyFrm->m_bShowHex) {
	      strCpr.Format("%-8x ",dwCpr);
     }else {
	      strCpr.Format("%-8d ",dwCpr);
     }
     flCpr=dwCpr;
  }else if(cpInfo->vi_Type==DT_DWD) {
	   dwCpr =cpBuf[cpInfo->Start_Byte+3];
     dwCpr =dwCpr*256;
     dwCpr =cpBuf[cpInfo->Start_Byte+4];
     dwCpr =dwCpr*256;
     dwCpr =dwCpr+cpBuf[cpInfo->Start_Byte+5];
     dwCpr =dwCpr*256;
     dwCpr =dwCpr+cpBuf[cpInfo->Start_Byte+6];
     
     if(pMyFrm->m_bShowHex) {
	      strCpr.Format("%-8x ",dwCpr);
     }else {
	      strCpr.Format("%-8d ",dwCpr);
     }
     flCpr=dwCpr;
  }else if(cpInfo->vi_Type==DT_UF16) {
    dwCpr =cpBuf[cpInfo->Start_Byte+3];//(-1+5)
    dwCpr =dwCpr*256;
    dwCpr =dwCpr + cpBuf[cpInfo->Start_Byte+4];
    flCpr= (double)dwCpr;
    flCpr= flCpr/32768.0;
    
    strCpr.Format("%-.8f ",flCpr);
  }else if(cpInfo->vi_Type==DT_F16) {
    pData    =(BYTE*)&c_int16;
    pData[0] =cpBuf[cpInfo->Start_Byte+4];
    pData[1] =cpBuf[cpInfo->Start_Byte+3];
    flCpr =c_int16/32768.0;//=2^15
    
    strCpr.Format("%-.8f ",flCpr);
  }else if(cpInfo->vi_Type==DT_UF32) {
    dwCpr =cpBuf[cpInfo->Start_Byte+3];
    dwCpr =dwCpr*256;
    dwCpr =dwCpr+cpBuf[cpInfo->Start_Byte+4];
    dwCpr =dwCpr*256;
    dwCpr =dwCpr+cpBuf[cpInfo->Start_Byte+5];
    dwCpr =dwCpr*256;
    dwCpr =dwCpr+cpBuf[cpInfo->Start_Byte+6];
    flCpr= dwCpr/2147483648.0;//=2^31
    
    strCpr.Format("%-.9f",flCpr);
  }else if(cpInfo->vi_Type==DT_F32) {
    pData    =(BYTE*)&c_int32;
    pData[0] =cpBuf[cpInfo->Start_Byte+6];
    pData[1] =cpBuf[cpInfo->Start_Byte+5];
    pData[2] =cpBuf[cpInfo->Start_Byte+4];
    pData[3] =cpBuf[cpInfo->Start_Byte+3];
    flCpr =c_int32/2147483648.0;//=2^31
    
    strCpr.Format("%-.9f",flCpr);
  }else {
    return false;
  }
  
  return true;
}


bool RefParser(HSM_ITEM *rpInfo,double *lpBeen,double &flCpr,
               CString &strInner)
{
  CMainFrame  *pMyFrm =(CMainFrame*)AfxGetApp()->m_pMainWnd;//取主框架窗口指针
  flCpr=DblParser(rpInfo->vi_Express,lpBeen);
  
  if((rpInfo->vi_Type==DT_DWD) || (rpInfo->vi_Type==DT_WORD) ||
	   (rpInfo->vi_Type==DT_BIT) || (rpInfo->vi_Type==DT_BYTE)) {
		  if(pMyFrm->m_bShowHex ) {
        strInner.Format("%-8x ",(int)flCpr);
      }else {
        strInner.Format("%-8d ",(int)flCpr);
      }
  }else if(rpInfo->vi_Type==DT_UF16) {
	   strInner.Format("%-.8f ",flCpr);
  }else if(rpInfo->vi_Type==DT_F16) {
	   strInner.Format("%-.8f ",flCpr);
  }else if(rpInfo->vi_Type==DT_UF32) {
	   strInner.Format("%-.9f",flCpr);
  }else if(rpInfo->vi_Type==DT_F32) {
	   strInner.Format("%-.9f",flCpr);
  }else {
    return false;
  }
  
  return true;
}

CString FlatterUser(HSM_ITEM *rpInfo,CString &strInner,double flCpr,
                    LV_DISPINFO *lvDisp)
{
  //数据状态转换
  CString strUser;
  
  strUser =strInner+MBSTR_RAWMARK;
  for(int jLop=0;jLop<rpInfo->vi_cStates;jLop++) {
    if(flCpr ==rpInfo->vi_Value[jLop]) {
      strUser =rpInfo->vi_Memo[jLop];
    }
  }
  
  if(lvDisp) {
		  int iLen=min(strUser.GetLength(),lvDisp->item.cchTextMax-1);
      memcpy(lvDisp->item.pszText,strUser,iLen);
      lvDisp->item.pszText[iLen]=0x00;
  }
  return strUser;
}



