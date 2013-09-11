/********************************************************************
	created:	2007/05/10
	created:	10:5:2007   10:36
	filename: 	d:\Works\ExpertSmsSvr\ExpertSmsService\ExpertSelSvr.h
	file path:	d:\Works\ExpertSmsSvr\ExpertSmsService
	file base:	ExpertSelSvr
	file ext:	h
	author:		张国华
	
	purpose:	门禁系统服务
*********************************************************************/

#pragma once
#include <afx.h>
#include <vector>
#include <list>
#include "..\ComFiles\PubDefine.h"
#include "..\ComFiles\LogForMe.h"
#include "..\ComFiles\ExecParam.h"
#import "c:\Program Files\Common Files\System\ADO\msado15.dll" \
	no_namespace rename("EOF", "EndOfFile")



using namespace std;

//默认参数文件名
//const CString strFileName = "ExpertSms.ini";

class CDbSynSvr
{
private:

 
    list<ACCOUNT_MSG> vMsg;
	
	//服务线程句柄
	HANDLE m_hThread;
	//定期清除线程退出事件
	HANDLE m_hEvtExit;

	DBCON_PARAM DBConParam;

	//检测周期
	UINT m_nCheckPeriod;
	//有效任务时间(距到场时间小时数)
	UINT m_nValidTime;

	UINT m_nWaitAnswer;


	//数据库连接
	_ConnectionPtr	m_pConnection;

	CString m_strFlowFile;
	CString m_strControlFile;
	CString m_strListFile;
	CString m_strBranchMapFile;
	CString m_strModulePath;
	CString m_strBlackPath;
	CString m_strDbPath;

public:
	CDbSynSvr(void);
	~CDbSynSvr(void);

	CExecParam m_Params;


	
private:
	//检查是否任务时间是否已经过期
	bool CheckTimeValid(COleDateTime tAtt);
	//服务线程入口函数
	static DWORD WINAPI ThreadFunction(LPVOID param);
	//获取本地参数
	bool GetLocalParam(void);
	//清除m_gateID抽取变量
	void ClearSelectVar();
	//连接数据库
	bool Connect(void);
	//断开数据库连接
	void CloseConnect(void);
	
	//查询数据库种guestmember表中是否有新加入的人员，有的话将需要重写的门控器号放入m_gateID
	bool CheckNewBList();
    //查询是否有带删除人员，有的话


	//将DISPATH接口封装，准备下发
	bool Download();
	
	//服务函数
	DWORD DbSynSvrFun();

	//将下发过的guestmenber表中的人员状态置为2
	void ResetStatus( CString strID, INT status );
   
	//检查临时表
    void ImportControlBin();

    bool ImportMemberList();	
	

public:
	//启动服务线程
	bool Init(void);
	//关闭清除线程,销毁内存库
	void Destroy(void);
};
