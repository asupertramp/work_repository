// HkSvrMonitor.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "GsccsMonitor.h"
#include "GsccsMonitorDlg.h"
#include "..\ComFiles\ComUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHkSvrMonitorApp

BEGIN_MESSAGE_MAP(CHkSvrMonitorApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CHkSvrMonitorApp ����

CHkSvrMonitorApp::CHkSvrMonitorApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CHkSvrMonitorApp ����

CHkSvrMonitorApp theApp;


// CHkSvrMonitorApp ��ʼ��

BOOL CHkSvrMonitorApp::InitInstance()
{
	HANDLE hMutex;
	hMutex = CreateMutex(NULL, TRUE, "ExpertSMSSvrMonitor");
	if (hMutex == NULL) {
		MessageBox(NULL, "�޷����м��ӳ���,��֪ͨ����Ա!", "����", MB_OK );
		ErrorLog("�޷������������,�޷����г���");
		return FALSE;
	}
	if (hMutex!=NULL) {
		if (GetLastError() == ERROR_ALREADY_EXISTS) {			
			return FALSE;
		}
	}
	InitLogFile("ESSMonitor");
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControls()�����򣬽��޷��������ڡ�
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CHkSvrMonitorDlg dlg;
	if (!dlg.InitMailSlot()) {
		MessageBox(NULL, "�������Ѿ���ϵͳ�����û�����,�޷����ж��ʵ��!", "����", MB_OK);
		return FALSE;
	}
	m_pMainWnd = &dlg;

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ�á�ȷ�������ر�
		//�Ի���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ�á�ȡ�������ر�
		//�Ի���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	// ����������Ӧ�ó������Ϣ�á�
	return FALSE;

	FiniLogFile();
}
