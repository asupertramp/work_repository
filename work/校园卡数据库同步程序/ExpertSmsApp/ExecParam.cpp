// ExecParam.cpp: implementation of the CExecParam class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "SiosInterface.h"
#include "ExecParam.h"
#include "..\ComFiles\LogForMe.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CExecParam::CExecParam()
{
	
	sprintf(params.ProxyAddr, "127.0.0.1");
	params.ProxyPort = 8500;
	params.SysCode = 18;
	params.TerNo = 1;
	
}

CExecParam::~CExecParam()
{

}


/********************************************************************
Purpose:        由本地文件中取得运行参数
Parameters:		
Return Value: 	成功:true	失败:false
*********************************************************************/
bool CExecParam::GetLocalParam(void)
{
	//获取运行参数
	memset(params.ProxyAddr, 0, 16);
	GetPrivateProfileString("RUNPARAM", "ProxyIP", "127.0.0.1", params.ProxyAddr, 16, strParamFileName);
	memset(params.DBName, 0, 256);
	GetPrivateProfileString("RUNPARAM", "DBName", "", params.DBName, 256, strParamFileName);
	memset(params.BLName, 0, 256);
	GetPrivateProfileString("RUNPARAM", "BlackName", "", params.BLName, 256, strParamFileName);
	params.ProxyPort = GetPrivateProfileInt("RUNPARAM", "ProxyPort", 8500, strParamFileName);
	params.SysCode = GetPrivateProfileInt("RUNPARAM", "SysCode", 18, strParamFileName);
	params.TerNo = GetPrivateProfileInt("RUNPARAM", "TernimalNo", 1, strParamFileName);
	return true;
}

/********************************************************************
Purpose:        将运行参数保存到本地文件中
Parameters:     
Return Value: 	成功:true	失败:false
*********************************************************************/
bool CExecParam::SaveParamToLocal(void)
{
	char value[64];
	WritePrivateProfileString("RUNPARAM", "ProxyIP", params.ProxyAddr, strParamFileName);	
	itoa(params.ProxyPort, value, 10);
	WritePrivateProfileString("RUNPARAM", "ProxyPort", value, strParamFileName);
	itoa(params.SysCode, value, 10);
	WritePrivateProfileString("RUNPARAM", "SysCode", value, strParamFileName);
	itoa(params.TerNo, value, 10);
	WritePrivateProfileString("RUNPARAM", "TernimalNo", value, strParamFileName);

	WritePrivateProfileString("RUNPARAM", "DBName", params.DBName, strParamFileName);
	WritePrivateProfileString("RUNPARAM", "BlackName", params.BLName, strParamFileName);
	return true;
}

/********************************************************************
Purpose:        初始化运行参数
Parameters:     
Return Value: 	成功:true	失败:false
*********************************************************************/
bool CExecParam::InitParam(void)
{
	char filepath[255];
	memset(filepath,0,255);
	::GetModuleFileName(NULL, filepath, 255);
	strParamFileName = filepath;
	int nPos = strParamFileName.ReverseFind('\\');
	if (nPos == -1) {
		return false;
	}
	strParamFileName = strParamFileName.Left(nPos+1) + strFileNameInterface;
	PrintTraceLog(strParamFileName);

	if (!GetLocalParam())
	{
		return false;
	}
	SaveParamToLocal();	
	return true;
}