#pragma once
#include "stdafx.h"
#include "DbSynSvr.h"

class CServiceIniter
{
private:
	CDbSynSvr m_GsccsSvr;
	//服务状态句柄
	SERVICE_STATUS_HANDLE   m_SvrStatusHandle;
public:
	CServiceIniter(void);
	~CServiceIniter(void);
private:
	//设置服务状态
	bool SetSvcStatus(DWORD dwState, DWORD dwWait);
public:
	//启动各服务
	bool StartService(void);
	//关闭各服务
	bool StopService(void);
	bool InitExecParam(void);
	//设置服务状态句柄
	inline void SetStatusHandle(SERVICE_STATUS_HANDLE sHandle)
	{
		m_SvrStatusHandle = sHandle;
	}

};
