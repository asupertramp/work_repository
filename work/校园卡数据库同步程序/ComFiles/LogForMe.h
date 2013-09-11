/********************************************************************
	created:	2006/04/18
	created:	18:4:2006   8:54
	filename: 	d:\Works\HKQuerySvr\ComFiles\LogForMe.h
	author:		张国华
	
	purpose:	记录日志
*********************************************************************/

#pragma once
#include <afx.h>

const UINT LOG_LEVEL_TRACE = 0;		//临时跟踪调试日志
const UINT LOG_LEVEL_DEBUG = 1;		//调试事件日志
const UINT LOG_LEVEL_INFO = 2;		//事件通知
const UINT LOG_LEVEL_EVENT = 3;		//事件日志
const UINT LOG_LEVEL_ERROR = 4;		//错误日志
const UINT LOG_LEVEL_SYS = 5;		//系统错误日志
const UINT LOG_LEVEL_TOP = 999;		//最重要的日志,一定要输出


//程序开始运行时初始化日志模块
void InitLogFile(LPCSTR FileName);
//程序结束运行时输出结束日志
void FiniLogFile();
//记录日志
void WriteLog(LPCSTR msg, LPCSTR filename=NULL, UINT nLogLevel=1);
//记录日志,Printf格式
void PrintLog(LPCSTR filename, UINT nLogLevel, LPCSTR msg, ...);

//记录跟踪调试信息
void TraceLog(LPCSTR msg, LPCSTR filename = NULL);
//记录跟踪调试信息,仿Printf版
void PrintTraceLog(LPCSTR msg, ...);

//记录调试日志
void DebugLog(LPCSTR msg, LPCSTR filename = NULL);
//记录调试日志,仿Printf版
void PrintDebugLog(LPCSTR msg, ...);

//记录事件日志
void EventLog(LPCSTR msg, LPCSTR filename = NULL);
//记录事件日志,仿Printf版
void PrintEventLog(LPCSTR msg, ...);

//记录错误日志
void ErrorLog(LPCSTR msg, LPCSTR filename = NULL);
//记录错误日志,仿Printf版
void PrintErrorLog(LPCSTR msg, ...);

//记录系统错误日志
void SysErrLog(LPCSTR msg, LPCSTR filename = NULL, UINT nLogLevel = LOG_LEVEL_SYS);
//记录系统日志,仿Printf版
void PrintSysErrLog(LPCSTR msg, ...);



