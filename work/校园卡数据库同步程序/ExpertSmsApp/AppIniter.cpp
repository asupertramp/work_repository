#include "stdafx.h"
#include ".\appiniter.h"

CAppIniter::CAppIniter(void)
{
	
}

CAppIniter::~CAppIniter(void)
{
}

//����������
bool CAppIniter::StartService(void)
{
	if (m_DbSynSvr.Init()) {
		EventLog("�Ž�ϵͳ������������ɹ�");
		return true;
	}else{
		ErrorLog("�Ž�ϵͳ�����������ʧ��");
		return false;
	}
	
}
//�رո�����
bool CAppIniter::StopService(void)
{
	m_DbSynSvr.Destroy();
	return true;
}
bool CAppIniter::InitExecParam(void)
{
	return false;
}
