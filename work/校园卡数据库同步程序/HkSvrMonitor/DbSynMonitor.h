// HkSvrMonitor.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CHkSvrMonitorApp:
// �йش����ʵ�֣������ HkSvrMonitor.cpp
//

class CHkSvrMonitorApp : public CWinApp
{
public:
	CHkSvrMonitorApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CHkSvrMonitorApp theApp;
