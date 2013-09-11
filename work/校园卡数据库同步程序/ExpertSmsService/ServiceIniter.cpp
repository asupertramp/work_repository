#include "stdafx.h"
#include "..\ComFiles\logforme.h"
#include ".\serviceiniter.h"

CServiceIniter::CServiceIniter(void)
{
	m_SvrStatusHandle = NULL;
}

CServiceIniter::~CServiceIniter(void)
{
}

//启动各服务
bool CServiceIniter::StartService(void)
{
	//初始化运行参数
	SetSvcStatus(SERVICE_START_PENDING, 10000);
	if (m_GsccsSvr.Init()) {
		EventLog("门禁系统服务启动成功");	
		SetSvcStatus(SERVICE_RUNNING, 0);
		return true;
	}else{
		EventLog("门禁系统服务启动失败");
		SetSvcStatus(SERVICE_STOPPED, 0);
		return false;
	}
	
}
//关闭各服务
bool CServiceIniter::StopService(void)
{
	SetSvcStatus(SERVICE_STOP_PENDING, 10000);
	m_GsccsSvr.Destroy();
	EventLog("门径系统服务关闭!");
	SetSvcStatus(SERVICE_STOPPED, 0);
	return true;
}

/********************************************************************
Purpose:        设置服务状态(Service程序需要不断汇报自己状态)
Parameters:     dwState:服务状态
dwWait:等待时间
Return Value: 	成功:true 失败:false
*********************************************************************/
bool CServiceIniter::SetSvcStatus(DWORD dwState, DWORD dwWait)
{
	ASSERT(m_SvrStatusHandle != NULL);
	SERVICE_STATUS	SvrStatus;
	SvrStatus.dwServiceType        = SERVICE_WIN32; 
	SvrStatus.dwControlsAccepted   = SERVICE_ACCEPT_STOP ; 
	SvrStatus.dwWin32ExitCode      = 0; 
	SvrStatus.dwServiceSpecificExitCode = 0; 
	SvrStatus.dwCheckPoint    = 0; 	
	SvrStatus.dwCurrentState  = dwState; 	
	SvrStatus.dwWaitHint      = dwWait; 
	if (!SetServiceStatus (m_SvrStatusHandle,  &SvrStatus))
	{ 
		SysErrLog("设置服务状态出错(SetServiceStatus)!");
		return false;
	}
	return true;
}

