#pragma once
#include "stdafx.h"
#include "DbSynSvr.h"

class CServiceIniter
{
private:
	CDbSynSvr m_GsccsSvr;
	//����״̬���
	SERVICE_STATUS_HANDLE   m_SvrStatusHandle;
public:
	CServiceIniter(void);
	~CServiceIniter(void);
private:
	//���÷���״̬
	bool SetSvcStatus(DWORD dwState, DWORD dwWait);
public:
	//����������
	bool StartService(void);
	//�رո�����
	bool StopService(void);
	bool InitExecParam(void);
	//���÷���״̬���
	inline void SetStatusHandle(SERVICE_STATUS_HANDLE sHandle)
	{
		m_SvrStatusHandle = sHandle;
	}

};
