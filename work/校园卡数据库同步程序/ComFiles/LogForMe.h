/********************************************************************
	created:	2006/04/18
	created:	18:4:2006   8:54
	filename: 	d:\Works\HKQuerySvr\ComFiles\LogForMe.h
	author:		�Ź���
	
	purpose:	��¼��־
*********************************************************************/

#pragma once
#include <afx.h>

const UINT LOG_LEVEL_TRACE = 0;		//��ʱ���ٵ�����־
const UINT LOG_LEVEL_DEBUG = 1;		//�����¼���־
const UINT LOG_LEVEL_INFO = 2;		//�¼�֪ͨ
const UINT LOG_LEVEL_EVENT = 3;		//�¼���־
const UINT LOG_LEVEL_ERROR = 4;		//������־
const UINT LOG_LEVEL_SYS = 5;		//ϵͳ������־
const UINT LOG_LEVEL_TOP = 999;		//����Ҫ����־,һ��Ҫ���


//����ʼ����ʱ��ʼ����־ģ��
void InitLogFile(LPCSTR FileName);
//�����������ʱ���������־
void FiniLogFile();
//��¼��־
void WriteLog(LPCSTR msg, LPCSTR filename=NULL, UINT nLogLevel=1);
//��¼��־,Printf��ʽ
void PrintLog(LPCSTR filename, UINT nLogLevel, LPCSTR msg, ...);

//��¼���ٵ�����Ϣ
void TraceLog(LPCSTR msg, LPCSTR filename = NULL);
//��¼���ٵ�����Ϣ,��Printf��
void PrintTraceLog(LPCSTR msg, ...);

//��¼������־
void DebugLog(LPCSTR msg, LPCSTR filename = NULL);
//��¼������־,��Printf��
void PrintDebugLog(LPCSTR msg, ...);

//��¼�¼���־
void EventLog(LPCSTR msg, LPCSTR filename = NULL);
//��¼�¼���־,��Printf��
void PrintEventLog(LPCSTR msg, ...);

//��¼������־
void ErrorLog(LPCSTR msg, LPCSTR filename = NULL);
//��¼������־,��Printf��
void PrintErrorLog(LPCSTR msg, ...);

//��¼ϵͳ������־
void SysErrLog(LPCSTR msg, LPCSTR filename = NULL, UINT nLogLevel = LOG_LEVEL_SYS);
//��¼ϵͳ��־,��Printf��
void PrintSysErrLog(LPCSTR msg, ...);



