/********************************************************************
	created:	2006/04/18
	created:	18:4:2006   8:54
	filename: 	d:\Works\HKQuerySvr\ComFiles\LogForMe.cpp
	author:		张国华
	
	purpose:	记录进程日志
*********************************************************************/
#include "LogForMe.h"

//临界区,保证日志模块线程安全
CRITICAL_SECTION CSErrorLog;
//日志文件全名
CString LogFileName;
//日志文件名
CString LogFileNameWithoutExt;
//日志文件扩展名
CString LogExt = ".log";
//日志文件目录名
CString LogPath;
//日志文件最大长度
UINT MaxFileSize = 3 * 1024 * 1024;
//日志文件数量
UINT MaxFileReserved = 100;
//日志输出级别
UINT MinLogLevel = LOG_LEVEL_DEBUG;

/********************************************************************
purpose:    	
Parameters:		FileName:日志文件名
Return Value:	程序开始运行时调用,指定日志的文件名,并输出开始运行日志
				读入LogForMe.ini文件中的配置参数,确定日志输出级别
*********************************************************************/
void InitLogFile(LPCSTR FileName)
{
	char filepath[255];
	memset(filepath,0,255);
	::GetModuleFileName(NULL, filepath, 255);
	LogPath = filepath;
	int index = LogPath.ReverseFind('\\');
	if(index != -1)
	{
		LogPath = LogPath.Left(index+1);
	}
	LogFileName = LogPath + FileName + LogExt;
	LogFileNameWithoutExt = LogPath + FileName;
	InitializeCriticalSection(&CSErrorLog);
	
	MinLogLevel = LOG_LEVEL_TRACE;
	EventLog("                                              ");
	EventLog("◆◆◆◆◆◆"
		"◆◆◆◆◆◆◆◆◆◆◆◆◆");
	EventLog("◆◆◆◆◆◆"
		"◆◆◆◆◆◆◆◆◆◆◆◆◆");
	EventLog("------------------"
		"程序开始运行---------------------");
	CString strLogIni = LogPath + "LogForMe.ini";
	MinLogLevel = GetPrivateProfileInt("LOG", "LOGLEVEL", LOG_LEVEL_DEBUG, strLogIni);
	PrintLog(NULL, LOG_LEVEL_TOP, "日志输出级别:%d", MinLogLevel);
	
}

/********************************************************************
Function Name:	VOID FiniLogFile()	
Parameters:		
Return Values:	
Remark:			程序结束时调用,输出结束日志
*********************************************************************/
VOID FiniLogFile()
{
	MinLogLevel = LOG_LEVEL_TRACE;
	EventLog("------------------"
		"程序结束运行---------------------");
	EventLog("◆◆◆◆◆◆"
		"◆◆◆◆◆◆◆◆◆◆◆◆◆");
	EventLog("◆◆◆◆◆◆"
		"◆◆◆◆◆◆◆◆◆◆◆◆◆");
	EventLog("                                              ");	
	DeleteCriticalSection(&CSErrorLog);
}

/********************************************************************
purpose:		记录日志信息到文件    	
Parameters:		msg:日志信息
				filename:日志文件名(默认值为初始文件)
				nLogLevel:日志事件级别(0为临时调试信息,值越高事件级别越高
Return Value: 	
*********************************************************************/
void WriteLog(LPCSTR msg, LPCSTR filename, UINT nLogLevel/* =1 */)
{
	if (nLogLevel < MinLogLevel)
	{
		return;
	}
	SYSTEMTIME curtime;
	::GetLocalTime(&curtime);
	CString str;
	str.Format("[%d] %04d-%02d-%02d %02d:%02d:%02d.%03d", nLogLevel, 
		curtime.wYear,
		curtime.wMonth,curtime.wDay,curtime.wHour,curtime.wMinute,
		curtime.wSecond,
		curtime.wMilliseconds);
	str = str + ": " + msg + "\r\n";

#ifdef _CONSOLE_APP
	printf("%s\n", str);
#endif

	CString sFileFullName;
	CString sFileName;
	if (filename==NULL)
	{
		sFileFullName = LogFileName;
		sFileName = LogFileNameWithoutExt;
	}
	else
	{
		sFileFullName.Format("%s%s%s",LogPath, filename, LogExt);
		sFileName.Format("%s%s",LogPath, filename);
	}
	CString NewName,OldName;
	CFile logfile;
	EnterCriticalSection(&CSErrorLog);
	try 
	{
		if(logfile.Open(sFileFullName,
			CFile::shareDenyWrite | CFile::modeNoTruncate|CFile::modeCreate|CFile::modeWrite))
		{
			logfile.SeekToEnd();
			logfile.Write(str,str.GetLength());
			ULONG64 FileSize = logfile.GetLength();
			logfile.Close();

			if(FileSize > MaxFileSize) 
			{
				NewName.Format("%s%d%s",sFileName,MaxFileReserved,LogExt);
				DeleteFile(NewName);
				for(int i = MaxFileReserved-1;i>=0;i--)
				{
					if (i == 0)
					{
						OldName = sFileFullName;
					}
					else
					{
						OldName.Format("%s%d%s",sFileName,i,LogExt);
					}	
					MoveFile(OldName, NewName);
					NewName = OldName;				
				}

			}	
		}
	}
	catch (...) {

	}
	// Release ownership of the critical section.
	LeaveCriticalSection(&CSErrorLog);  
}

/********************************************************************
purpose:		记录日志,Printf格式 	
Parameters:		
Return Value: 	
*********************************************************************/
void PrintLog(LPCSTR filename, UINT nLogLevel, LPCSTR msg, ...)
{
	va_list args;
	va_start(args, msg);

	int nBuf;
	TCHAR szBuffer[512];

	nBuf = _vsntprintf(szBuffer, sizeof(szBuffer), msg, args);

	// was there an error? was the expanded string too long?
	ASSERT(nBuf >= 0);
	va_end(args);

	WriteLog(szBuffer, filename, nLogLevel);
}

/********************************************************************
purpose:    	记录跟踪调试日志
Parameters:		
Return Value: 	
*********************************************************************/
void TraceLog(LPCSTR msg, LPCSTR filename /* = NULL */)
{
	WriteLog(msg, filename, LOG_LEVEL_TRACE);
}
/********************************************************************
purpose:    	记录跟踪调试日志,仿Printf格式
Parameters:		filename:日志文件名,默认赋值NULL
				msg:日志信息,总长度小于512字节
Return Value: 	
*********************************************************************/
void PrintTraceLog(LPCSTR msg, ...)
{
	va_list args;
	va_start(args, msg);

	int nBuf;
	TCHAR szBuffer[512];

	nBuf = _vsntprintf(szBuffer, sizeof(szBuffer), msg, args);

	// was there an error? was the expanded string too long?
	ASSERT(nBuf >= 0);
	va_end(args);

	WriteLog(szBuffer, NULL, LOG_LEVEL_TRACE);
}

/********************************************************************
purpose:		记录调试日志 	
Parameters:		
Return Value: 	
*********************************************************************/
void DebugLog(LPCSTR msg, LPCSTR filename /* = NULL */)
{
	WriteLog(msg, filename, LOG_LEVEL_DEBUG);
}
/********************************************************************
purpose:		记录调试日志,仿Printf版  	
Parameters:		filename:日志文件名,默认赋值NULL
				msg:日志信息,总长度小于512字节
Return Value: 	
*********************************************************************/
void PrintDebugLog(LPCSTR msg, ...)
{
	va_list args;
	va_start(args, msg);

	int nBuf;
	TCHAR szBuffer[512];

	nBuf = _vsntprintf(szBuffer, sizeof(szBuffer), msg, args);

	// was there an error? was the expanded string too long?
	ASSERT(nBuf >= 0);
	va_end(args);
	WriteLog(szBuffer, NULL, LOG_LEVEL_DEBUG);
}

/********************************************************************
purpose:		记录事件日志		   	
Parameters:		
Return Value: 	
*********************************************************************/
void EventLog(LPCSTR msg, LPCSTR filename /*= NULL*/)
{
	WriteLog(msg, filename, LOG_LEVEL_EVENT);
}

/********************************************************************
purpose:		记录事件日志,仿Printf版	
Parameters:		
Return Value: 	
*********************************************************************/
void PrintEventLog(LPCSTR msg, ...)
{
	va_list args;
	va_start(args, msg);

	int nBuf;
	TCHAR szBuffer[512];

	nBuf = _vsntprintf(szBuffer, sizeof(szBuffer), msg, args);

	// was there an error? was the expanded string too long?
	ASSERT(nBuf >= 0);
	va_end(args);
	WriteLog(szBuffer, NULL, LOG_LEVEL_EVENT);
}


/********************************************************************
purpose:    	记录错误日志	
Parameters:		
Return Value: 	
*********************************************************************/
void ErrorLog(LPCSTR msg, LPCSTR filename /* = NULL */)
{
	WriteLog(msg, filename, LOG_LEVEL_ERROR);
}

/********************************************************************
purpose:    	记录错误日志,仿Printf版
Parameters:		
Return Value: 	
*********************************************************************/
void PrintErrorLog(LPCSTR msg, ...)
{
	va_list args;
	va_start(args, msg);

	int nBuf;
	TCHAR szBuffer[512];

	nBuf = _vsntprintf(szBuffer, sizeof(szBuffer), msg, args);

	// was there an error? was the expanded string too long?
	ASSERT(nBuf >= 0);
	va_end(args);

	WriteLog(szBuffer, NULL, LOG_LEVEL_ERROR);
}

/********************************************************************
purpose:		记录系统错误日志  	
Parameters:		
Return Value: 	
*********************************************************************/
void SysErrLog(LPCSTR msg, LPCSTR filename /* = NULL */, UINT nLogLevel /* = LOG_LEVEL_SYS */)
{
	CString strMsg;

	//获取错误代码
	DWORD dwErrorCode;
	dwErrorCode = GetLastError();
	strMsg.Format("****%s --错误代码(%d)****", msg, dwErrorCode);

	WriteLog(strMsg, filename, nLogLevel); 
	
}
//记录系统日志,仿Printf版
void PrintSysErrLog(LPCSTR msg, ...)
{
	va_list args;
	va_start(args, msg);

	int nBuf;
	TCHAR szBuffer[512];

	nBuf = _vsntprintf(szBuffer, sizeof(szBuffer), msg, args);

	// was there an error? was the expanded string too long?
	ASSERT(nBuf >= 0);
	va_end(args);

	CString strMsg;

	//获取错误代码
	DWORD dwErrorCode;
	dwErrorCode = GetLastError();
	strMsg.Format("****%s --错误代码(%d)****", szBuffer, dwErrorCode);

	WriteLog(strMsg, NULL, LOG_LEVEL_SYS); 
}