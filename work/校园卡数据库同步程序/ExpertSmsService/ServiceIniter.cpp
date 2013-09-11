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

//����������
bool CServiceIniter::StartService(void)
{
	//��ʼ�����в���
	SetSvcStatus(SERVICE_START_PENDING, 10000);
	if (m_GsccsSvr.Init()) {
		EventLog("�Ž�ϵͳ���������ɹ�");	
		SetSvcStatus(SERVICE_RUNNING, 0);
		return true;
	}else{
		EventLog("�Ž�ϵͳ��������ʧ��");
		SetSvcStatus(SERVICE_STOPPED, 0);
		return false;
	}
	
}
//�رո�����
bool CServiceIniter::StopService(void)
{
	SetSvcStatus(SERVICE_STOP_PENDING, 10000);
	m_GsccsSvr.Destroy();
	EventLog("�ž�ϵͳ����ر�!");
	SetSvcStatus(SERVICE_STOPPED, 0);
	return true;
}

/********************************************************************
Purpose:        ���÷���״̬(Service������Ҫ���ϻ㱨�Լ�״̬)
Parameters:     dwState:����״̬
dwWait:�ȴ�ʱ��
Return Value: 	�ɹ�:true ʧ��:false
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
		SysErrLog("���÷���״̬����(SetServiceStatus)!");
		return false;
	}
	return true;
}

