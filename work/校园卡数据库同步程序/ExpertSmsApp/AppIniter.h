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
	//����������
	bool StartService(void);
	//�رո�����
	bool StopService(void);
	bool InitExecParam(void);
};
