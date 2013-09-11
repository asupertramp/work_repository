// ExecParam.h: interface for the CExecParam class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXECPARAM_H__6F332CFD_A5BB_46BD_8A0E_24371E19491B__INCLUDED_)
#define AFX_EXECPARAM_H__6F332CFD_A5BB_46BD_8A0E_24371E19491B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//默认参数文件名
const CString strFileName = "Interface.ini";

//运行参数类型
typedef struct _Paramter_Exec{
	char ProxyAddr[16];			//代理地址
	UINT ProxyPort;			//代理端口
	UINT SysCode;		//子系统代码
	UINT TerNo;		//终端号	
	char DBName[256];	//数据库文件地址
	char BLName[256];	//黑名单文件地址
}PARAM_EXEC;


/************************************************************************/
//运行参数管理类
/************************************************************************/
class CExecParam
{
public:
	CExecParam(void);
	~CExecParam(void);
public:
	//运行参数
	PARAM_EXEC params;
	//参数文件名(带路径)
	CString strParamFileName;
public:
	bool GetLocalParam(void);
	bool SaveParamToLocal(void);
	bool InitParam(void);
};


#endif // !defined(AFX_EXECPARAM_H__6F332CFD_A5BB_46BD_8A0E_24371E19491B__INCLUDED_)
