/********************************************************************
	created:	2006/04/18
	created:	18:4:2006   8:54
	filename: 	d:\Works\HKQuerySvr\ComFiles\LogForMe.cpp
	author:		�Ź���
	
	purpose:	��¼������־
*********************************************************************/
#include "LogForMe.h"

//�ٽ���,��֤��־ģ���̰߳�ȫ
CRITICAL_SECTION CSErrorLog;
//��־�ļ�ȫ��
CString LogFileName;
//��־�ļ���
CString LogFileNameWithoutExt;
//��־�ļ���չ��
CString LogExt = ".log";
//��־�ļ�Ŀ¼��
CString LogPath;
//��־�ļ���󳤶�
UINT MaxFileSize = 3 * 1024 * 1024;
//��־�ļ�����
UINT MaxFileReserved = 100;
//��־�������
UINT MinLogLevel = LOG_LEVEL_DEBUG;

/********************************************************************
purpose:    	
Parameters:		FileName:��־�ļ���
Return Value:	����ʼ����ʱ����,ָ����־���ļ���,�������ʼ������־
				����LogForMe.ini�ļ��е����ò���,ȷ����־�������
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
	EventLog("������������"
		"��������������������������");
	EventLog("������������"
		"��������������������������");
	EventLog("------------------"
		"����ʼ����---------------------");
	CString strLogIni = LogPath + "LogForMe.ini";
	MinLogLevel = GetPrivateProfileInt("LOG", "LOGLEVEL", LOG_LEVEL_DEBUG, strLogIni);
	PrintLog(NULL, LOG_LEVEL_TOP, "��־�������:%d", MinLogLevel);
	
}

/********************************************************************
Function Name:	VOID FiniLogFile()	
Parameters:		
Return Values:	
Remark:			�������ʱ����,���������־
*********************************************************************/
VOID FiniLogFile()
{
	MinLogLevel = LOG_LEVEL_TRACE;
	EventLog("------------------"
		"�����������---------------------");
	EventLog("������������"
		"��������������������������");
	EventLog("������������"
		"��������������������������");
	EventLog("                                              ");	
	DeleteCriticalSection(&CSErrorLog);
}

/********************************************************************
purpose:		��¼��־��Ϣ���ļ�    	
Parameters:		msg:��־��Ϣ
				filename:��־�ļ���(Ĭ��ֵΪ��ʼ�ļ�)
				nLogLevel:��־�¼�����(0Ϊ��ʱ������Ϣ,ֵԽ���¼�����Խ��
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
purpose:		��¼��־,Printf��ʽ 	
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
purpose:    	��¼���ٵ�����־
Parameters:		
Return Value: 	
*********************************************************************/
void TraceLog(LPCSTR msg, LPCSTR filename /* = NULL */)
{
	WriteLog(msg, filename, LOG_LEVEL_TRACE);
}
/********************************************************************
purpose:    	��¼���ٵ�����־,��Printf��ʽ
Parameters:		filename:��־�ļ���,Ĭ�ϸ�ֵNULL
				msg:��־��Ϣ,�ܳ���С��512�ֽ�
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
purpose:		��¼������־ 	
Parameters:		
Return Value: 	
*********************************************************************/
void DebugLog(LPCSTR msg, LPCSTR filename /* = NULL */)
{
	WriteLog(msg, filename, LOG_LEVEL_DEBUG);
}
/********************************************************************
purpose:		��¼������־,��Printf��  	
Parameters:		filename:��־�ļ���,Ĭ�ϸ�ֵNULL
				msg:��־��Ϣ,�ܳ���С��512�ֽ�
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
purpose:		��¼�¼���־		   	
Parameters:		
Return Value: 	
*********************************************************************/
void EventLog(LPCSTR msg, LPCSTR filename /*= NULL*/)
{
	WriteLog(msg, filename, LOG_LEVEL_EVENT);
}

/********************************************************************
purpose:		��¼�¼���־,��Printf��	
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
purpose:    	��¼������־	
Parameters:		
Return Value: 	
*********************************************************************/
void ErrorLog(LPCSTR msg, LPCSTR filename /* = NULL */)
{
	WriteLog(msg, filename, LOG_LEVEL_ERROR);
}

/********************************************************************
purpose:    	��¼������־,��Printf��
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
purpose:		��¼ϵͳ������־  	
Parameters:		
Return Value: 	
*********************************************************************/
void SysErrLog(LPCSTR msg, LPCSTR filename /* = NULL */, UINT nLogLevel /* = LOG_LEVEL_SYS */)
{
	CString strMsg;

	//��ȡ�������
	DWORD dwErrorCode;
	dwErrorCode = GetLastError();
	strMsg.Format("****%s --�������(%d)****", msg, dwErrorCode);

	WriteLog(strMsg, filename, nLogLevel); 
	
}
//��¼ϵͳ��־,��Printf��
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

	//��ȡ�������
	DWORD dwErrorCode;
	dwErrorCode = GetLastError();
	strMsg.Format("****%s --�������(%d)****", szBuffer, dwErrorCode);

	WriteLog(strMsg, NULL, LOG_LEVEL_SYS); 
}