#include "stdafx.h"
#include ".\appiniter.h"

CAppIniter::CAppIniter(void)
{
	
}

CAppIniter::~CAppIniter(void)
{
}

//启动各服务
bool CAppIniter::StartService(void)
{
	if (m_DbSynSvr.Init()) {
		EventLog("门禁系统服务程序启动成功");
		return true;
	}else{
		ErrorLog("门禁系统服务程序启动失败");
		return false;
	}
	
}
//关闭各服务
bool CAppIniter::StopService(void)
{
	m_DbSynSvr.Destroy();
	return true;
}
bool CAppIniter::InitExecParam(void)
{
	return false;
}
