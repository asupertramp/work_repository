// ExpertSmsApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "DbSynApp.h"
#include "AppIniter.h"
#include <conio.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;
	InitLogFile("DbSynApp");
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
		CAppIniter Initer;			
		if(Initer.StartService())
		{
			cout<< "**********************************" << endl;
			cout<< "*   门禁系统服务程序             *" << endl;
			cout<< "*   X: Exit                      *" << endl;								
			cout<< "**********************************" << endl;

			while(true)
			{
				char c = getch();
				if (c=='x' || c=='X')
					break;
				else if (c=='S' || c=='s')
				{

				}
				else
				{
					system("cls");
					cout<< "**********************************" << endl;
					cout<< "*   门禁系统服务程序             *" << endl;
					cout<< "*   X: Exit                      *" << endl;								
					cout<< "**********************************" << endl;

				}
			}
			Initer.StopService();
		}

	}
	FiniLogFile();
}
