// ExpertSmsService.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include "ServiceIniter.h"
#include "DbSynService.h"
#include "..\Comfiles\CardControl.h"
#include "..\Comfiles\CardDef.h"
#include "..\Comfiles\LogForMe.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <Winsvc.h>
// The one and only application object

CWinApp theApp;

using namespace std;

//�����ʼ����
CServiceIniter Initer;
//����״̬���
SERVICE_STATUS_HANDLE   SvrStatusHandle; 
//������������
void  WINAPI ExpertSmsSvrStart (DWORD argc, LPTSTR *argv); 
//������������
void  WINAPI ExpertSmsSvrCtrlHandler (DWORD opcode); 

//�������
VOID SvcDebugOut(LPSTR String, DWORD Status) 
{ 
	CHAR  Buffer[1024]; 
	if (strlen(String) < 1000) 
	{ 
		sprintf(Buffer, String, Status); 
		OutputDebugStringA(Buffer); 
		ErrorLog(Buffer);
	} 
} 


/********************************************************************
Purpose:        ������������
Parameters:     OpCode:�����������
Return Value: 	
*********************************************************************/
VOID WINAPI ExpertSmsSvrCtrlHandler (DWORD Opcode) 
{ 
	switch(Opcode) 
	{ 
	case SERVICE_CONTROL_STOP: 
		Initer.StopService();
		return; 

	case SERVICE_CONTROL_INTERROGATE: 
		// Fall through to send current status. 
		break; 
	default: 
		SvcDebugOut(" [MY_SERVICE] Unrecognized opcode %ld\n", 
			Opcode); 
	} 
	return; 
} 


/********************************************************************
Purpose:        ������������
Parameters:     argc:��������
argv:�����ַ���
Return Value: 	
*********************************************************************/
void WINAPI ExpertSmsSvrStart (DWORD argc, LPTSTR *argv) 
{ 
	SvrStatusHandle = RegisterServiceCtrlHandler( 
		"DbSynSvr", 
		(LPHANDLER_FUNCTION)ExpertSmsSvrCtrlHandler); 

	if (SvrStatusHandle == (SERVICE_STATUS_HANDLE)0) 
	{ 		
		return; 
	} 

	Initer.SetStatusHandle(SvrStatusHandle);
	Initer.StartService();		
	return; 
} 


/********************************************************************
Purpose:        ж�ط���
Parameters:     
Return Value: 	
*********************************************************************/
VOID UnInstallService() 
{ 
	SC_HANDLE schSCManager = OpenSCManager(
		NULL ,   // computer name
		NULL ,  // SCM database name
		SC_MANAGER_CREATE_SERVICE    // access type
		);
	if (schSCManager == NULL)
	{
		cout << "OpenSCManager����ʧ��,�������(" << GetLastError() << ")" << endl;
		cout << "�޷����ж��,���¼���������ϵ����֧��!" << endl;	
		return;
	};

	SC_HANDLE schService = OpenService( 
		schSCManager,       // SCManager database 
		"DbSynSvr",       // name of service 
		DELETE);            // only need DELETE access 

	if (schService == NULL) 
	{
		DWORD dwError;
		dwError = GetLastError();
		switch(dwError) {
		case ERROR_SERVICE_DOES_NOT_EXIST:
			cout << "Ҫж�صķ�����ϵͳ�в�����!" << endl;
			break;
		default:
			cout << "OpenService����ʧ��,�������(" << GetLastError() << ")" << endl;
			cout << "�޷����ж��,���¼���������ϵ����֧��!" << endl;
		}		
		return;
	}

	if (! DeleteService(schService)) 
	{
		cout << "DeleteService����ʧ��,�������(" << GetLastError() << ")" << endl; 
		cout << "�޷����ж��,���¼���������ϵ����֧��!" << endl;
	}
	else 
	{
		cout << "����ж�سɹ�,��л����ʹ��!" << endl; 
	}

	CloseServiceHandle(schService); 
	CloseServiceHandle(schSCManager);
} 


/********************************************************************
Purpose:        ��װ����
Parameters:     
Return Value: 	
*********************************************************************/
void InstallService() 
{ 
	char strFilePath[255];
	::GetModuleFileName(NULL, strFilePath, 255);


	SC_HANDLE schSCManager = OpenSCManager(
		NULL ,   // computer name
		NULL ,  // SCM database name
		SC_MANAGER_CREATE_SERVICE    // access type
		);
	if (schSCManager == NULL)
	{
		cout << "OpenSCManager����ʧ��,�������(" << GetLastError() << ")" << endl;
		cout << "�޷���ɰ�װ,���¼���������ϵ����֧��!" << endl;
		return;
	};
	//��������
	SC_HANDLE schService = CreateService( 
		schSCManager,              // SCManager database 
		"DbSynSvr",              // name of service 
		"DbSynSvr",           // service name to display 
		SERVICE_ALL_ACCESS,        // desired access 
		SERVICE_WIN32_OWN_PROCESS, // service type 
		SERVICE_AUTO_START,      // start type 
		SERVICE_ERROR_NORMAL,      // error control type 
		strFilePath,        // service's binary 
		NULL,                      // no load ordering group 
		NULL,                      // no tag identifier 
		NULL,                      // no dependencies 
		NULL,                      // LocalSystem account 
		NULL);                     // no password 

	if (schService == NULL) 
	{
		DWORD dwError = GetLastError();
		switch(dwError) {
		case ERROR_SERVICE_EXISTS:
			cout << "�����Ѵ���ϵͳ��,�޷��ٴΰ�װ!" << endl;
			break;
		default:
			cout << "CreateService����ʧ��,�������(" << GetLastError() << ")" << endl;
			cout << "�޷���ɰ�װ,���¼���������ϵ����֧��!" << endl;
		}		
	}
	else{
		// Set service description
		SERVICE_DESCRIPTION ServiceDesc;
		static TCHAR szDescription[MAX_PATH];

		_tcscpy(szDescription, _T("ר�ҳ�ȡ���ŷ��ͷ������"));

		ServiceDesc.lpDescription = szDescription;

		::ChangeServiceConfig2(schService, SERVICE_CONFIG_DESCRIPTION, &ServiceDesc);


		cout << "����װ�ɹ�,��ͨ�������������������!" << endl;
	}

	CloseServiceHandle(schService); 
	CloseServiceHandle(schSCManager);
} 


int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;
	InitLogFile("ExpertSmsService");
	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: MFC initialization failed\n"));
		nRetCode = 1;
	}
	else
	{
		// TODO: code your application's behavior here.		
		if (argc >= 2)
		{
			string str(argv[1]);
			if ((str == "/i") || (str == "/I"))
			{
				InstallService();
			}
			else if ((str == "/u") || (str == "/U"))
			{
				UnInstallService();
			}
			else
			{
				cout << "��װ��ж��У԰��ͬ������!" << endl;
				cout << endl;
				cout << "DbSynSvr [/I] [/U]" << endl;
				cout << "/I:		��װ����" << endl;
				cout << "/U:		ж�ط���" << endl;
				cout << endl;
			}		
		}
		else
		{
			SERVICE_TABLE_ENTRY   DispatchTable[] = 
			{ 
				{"ExpertSmsSvr", (LPSERVICE_MAIN_FUNCTION)ExpertSmsSvrStart},
				{ NULL,              NULL          } 
			}; 

			if (StartServiceCtrlDispatcher(DispatchTable) == 0) 
			{ 
				SysErrLog("StartServiceCtrlDispatcher����ʧ��");

				cout << "��ͨ���������������У԰��ͬ���������!" << endl;
				cout << endl;
				cout << "DbSynSvr [/I] [/U]" << endl;
				cout << "/I:		��װ����" << endl;
				cout << "/U:		ж�ط���" << endl;
				cout << endl;
			} 
		}		
	}
	FiniLogFile();
	return nRetCode;
}
