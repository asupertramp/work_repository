#pragma once
#include "..\ExpertSmsService\DbSynSvr.h"

class CAppIniter
{
public:
	CDbSynSvr m_DbSynSvr;
public:
	CAppIniter(void);
	~CAppIniter(void);
public:
	//启动各服务
	bool StartService(void);
	//关闭各服务
	bool StopService(void);
	bool InitExecParam(void);
};
