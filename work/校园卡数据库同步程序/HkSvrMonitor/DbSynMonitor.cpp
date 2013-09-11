// HkSvrMonitor.cpp : 定义应用程序的类行为。
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


// CHkSvrMonitorApp 构造

CHkSvrMonitorApp::CHkSvrMonitorApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CHkSvrMonitorApp 对象

CHkSvrMonitorApp theApp;


// CHkSvrMonitorApp 初始化

BOOL CHkSvrMonitorApp::InitInstance()
{
	HANDLE hMutex;
	hMutex = CreateMutex(NULL, TRUE, "ExpertSMSSvrMonitor");
	if (hMutex == NULL) {
		MessageBox(NULL, "无法运行监视程序,请通知管理员!", "错误", MB_OK );
		ErrorLog("无法创建互斥变量,无法运行程序");
		return FALSE;
	}
	if (hMutex!=NULL) {
		if (GetLastError() == ERROR_ALREADY_EXISTS) {			
			return FALSE;
		}
	}
	InitLogFile("ESSMonitor");
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControls()。否则，将无法创建窗口。
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CHkSvrMonitorDlg dlg;
	if (!dlg.InitMailSlot()) {
		MessageBox(NULL, "本程序已经被系统其它用户运行,无法运行多个实例!", "警告", MB_OK);
		return FALSE;
	}
	m_pMainWnd = &dlg;

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用“确定”来关闭
		//对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用“取消”来关闭
		//对话框的代码
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	// 而不是启动应用程序的消息泵。
	return FALSE;

	FiniLogFile();
}
