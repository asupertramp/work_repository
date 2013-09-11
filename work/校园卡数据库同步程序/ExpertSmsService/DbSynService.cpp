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

//程序初始化器
CServiceIniter Initer;
//服务状态句柄
SERVICE_STATUS_HANDLE   SvrStatusHandle; 
//服务启动函数
void  WINAPI ExpertSmsSvrStart (DWORD argc, LPTSTR *argv); 
//服务请求处理函数
void  WINAPI ExpertSmsSvrCtrlHandler (DWORD opcode); 

//调试输出
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
Purpose:        服务请求处理函数
Parameters:     OpCode:服务请求代码
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
Purpose:        服务启动函数
Parameters:     argc:参数数量
argv:参数字符串
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
Purpose:        卸载服务
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
		cout << "OpenSCManager调用失败,错误代码(" << GetLastError() << ")" << endl;
		cout << "无法完成卸载,请记录错误代码联系技术支持!" << endl;	
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
			cout << "要卸载的服务在系统中不存在!" << endl;
			break;
		default:
			cout << "OpenService调用失败,错误代码(" << GetLastError() << ")" << endl;
			cout << "无法完成卸载,请记录错误代码联系技术支持!" << endl;
		}		
		return;
	}

	if (! DeleteService(schService)) 
	{
		cout << "DeleteService调用失败,错误代码(" << GetLastError() << ")" << endl; 
		cout << "无法完成卸载,请记录错误代码联系技术支持!" << endl;
	}
	else 
	{
		cout << "服务卸载成功,感谢您的使用!" << endl; 
	}

	CloseServiceHandle(schService); 
	CloseServiceHandle(schSCManager);
} 


/********************************************************************
Purpose:        安装服务
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
		cout << "OpenSCManager调用失败,错误代码(" << GetLastError() << ")" << endl;
		cout << "无法完成安装,请记录错误代码联系技术支持!" << endl;
		return;
	};
	//创建服务
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
			cout << "服务已存在系统中,无法再次安装!" << endl;
			break;
		default:
			cout << "CreateService调用失败,错误代码(" << GetLastError() << ")" << endl;
			cout << "无法完成安装,请记录错误代码联系技术支持!" << endl;
		}		
	}
	else{
		// Set service description
		SERVICE_DESCRIPTION ServiceDesc;
		static TCHAR szDescription[MAX_PATH];

		_tcscpy(szDescription, _T("专家抽取短信发送服务进程"));

		ServiceDesc.lpDescription = szDescription;

		::ChangeServiceConfig2(schService, SERVICE_CONFIG_DESCRIPTION, &ServiceDesc);


		cout << "服务安装成功,请通过服务管理器启动服务!" << endl;
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
				cout << "安装或卸载校园卡同步服务!" << endl;
				cout << endl;
				cout << "DbSynSvr [/I] [/U]" << endl;
				cout << "/I:		安装服务" << endl;
				cout << "/U:		卸载服务" << endl;
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
				SysErrLog("StartServiceCtrlDispatcher调用失败");

				cout << "请通过服务管理器启动校园卡同步服务程序!" << endl;
				cout << endl;
				cout << "DbSynSvr [/I] [/U]" << endl;
				cout << "/I:		安装服务" << endl;
				cout << "/U:		卸载服务" << endl;
				cout << endl;
			} 
		}		
	}
	FiniLogFile();
	return nRetCode;
}
