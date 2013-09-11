/********************************************************************
	created:	2006/03/06
	created:	6:3:2006   21:05
	filename: 	d:\Newwork\Hkquerysvr\ComFiles\ComUtils.cpp
	file path:	d:\Newwork\Hkquerysvr\ComFiles
	file base:	ComUtils
	file ext:	cpp
	author:		�Ź���
	
	purpose:	������������
*********************************************************************/

#include "ComUtils.h"
#include <math.h>
#include <string>
#include <sstream> 
#include <WinSock2.h>

using namespace std;




/*************************************************************************
Function Name:	unsigned int CharArrayToUINT(char *pChars, int size)
Parameters:		pChars:Ҫת�����ַ�����(�޽����ַ�)
				size:�ַ�����Ĵ�С
Return Values:	����ת�������ֵ
Remark:			���޽��������ַ�����ת�����޷�������
**************************************************************************/
unsigned int CharArrayToUINT(char *pChars, int size)
{
	unsigned int num = 0;
	if( size < 10 )
	{
		for (int i=0; i<size; i++)
		{
			num += (*(pChars+i) - '0') * (unsigned int)pow(10, size-1-i);
		}
	}
	else
	{
		PrintErrorLog("CharArrayToUINT�������,��󳤶�Ϊ10,�����ַ�����Ϊ%d", size);
	}
	return num;
}

/*************************************************************************
Function Name:	SYSTEMTIME SubtractTime(SYSTEMTIME tm, UINT nMin)
Parameters:		tm:����ʱ��
				nMin:Ҫ��ȥ�ķ�����
Return Values:	������
Remark:			��ָ����ʱ��tm,��ȥ������nMin.
**************************************************************************/
SYSTEMTIME SubtractTime(SYSTEMTIME tm, UINT nMin)
{

	FILETIME tmTemp;
	SystemTimeToFileTime(&tm, &tmTemp); 

	ULARGE_INTEGER ntm, ntmdif;
	memcpy(&ntm, &tmTemp, sizeof(ULARGE_INTEGER));

	ntmdif.QuadPart = UInt32x32To64(nMin, 600000000);

	ntm.QuadPart -= ntmdif.QuadPart;

	memcpy(&tmTemp, &ntm, sizeof(FILETIME));
	FileTimeToSystemTime(&tmTemp, &tm);

	return tm;
}

/*************************************************************************
Function Name:	int SysTimeComp(SYSTEMTIME tm1, SYSTEMTIME tm2)
Parameters:		tm1,tm2���бȽϵ�ʱ��
Return Values:	1:tm1>tm2
				0:tm1==tm2
				-1:tm1<tm2
Remark:			����SYSTEMTIME�����ıȽ�
**************************************************************************/
int SysTimeComp(SYSTEMTIME tm1, SYSTEMTIME tm2)
{
	FILETIME tmf1, tmf2;
	SystemTimeToFileTime(&tm1, &tmf1);
	SystemTimeToFileTime(&tm2, &tmf2);
	ULARGE_INTEGER ntm1, ntm2;
	memcpy(&ntm1, &tmf1, sizeof(FILETIME));
	memcpy(&ntm2, &tmf2, sizeof(FILETIME));
	if (ntm1.QuadPart > ntm2.QuadPart)
	{
		return 1;
	}
	else if (ntm1.QuadPart ==  ntm2.QuadPart)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

/********************************************************************
Function Name:	SYSTEMTIME CharAryToSysTime(const char* charyTime, int size)
Parameters:     charyTime:�ַ�����(YYYYMMDDHHMMSS)
				size:�ַ������С,ӦΪ14
Return Value: 	ת�����SYSTEMTIME����
Remark:		
*********************************************************************/
SYSTEMTIME CharAryToSysTime(const char* charyTime, int size)
{
	SYSTEMTIME tmResult;
	memset(&tmResult, 0, sizeof(SYSTEMTIME));
	ASSERT(size == 14);
	char sTime[15];
	memset(sTime, 0, sizeof(sTime));
	memcpy(sTime, charyTime, size);
	string strTime = sTime;
	tmResult.wYear = atoi(strTime.substr(0, 4).c_str());
	tmResult.wMonth = atoi(strTime.substr(4, 2).c_str());
	tmResult.wDay = atoi(strTime.substr(6, 2).c_str());
	tmResult.wHour = atoi(strTime.substr(8, 2).c_str());
	tmResult.wMinute = atoi(strTime.substr(10, 2).c_str());
	tmResult.wSecond = atoi(strTime.substr(12, 2).c_str());
	return tmResult;
}


/********************************************************************
Function Name:	int SysTimeToCharAry(const char* charyTime, int size, SYSTEMTIME systm)
Parameters:     charyTime:�ַ�����(YYYYMMDDHHMMSS)
				size:�ַ������С,ӦΪ14
				systm:��Ҫת����ϵͳʱ��
Return Value: 	ת������ַ�������
Remark:		
*********************************************************************/
int SysTimeToCharAry(char* charyTime, int size, SYSTEMTIME systm)
{

	int nlength = 14;
	ASSERT(size >= nlength);
	char sTime[15];
	memset(sTime, 0, sizeof(sTime));
	sprintf(sTime, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d", 
		systm.wYear, systm.wMonth, systm.wDay, systm.wHour, systm.wMinute, systm.wSecond);
	memcpy(charyTime, sTime, nlength);
	return nlength;
}
bool WriteMailSlot(LPCSTR lpszMsName, LPCSTR lpszMessage)
{
	BOOL fResult; 
	HANDLE hFile; 
	DWORD cbWritten; 
	try{
		hFile = CreateFile(lpszMsName, 
			GENERIC_WRITE, 
			FILE_SHARE_READ,  // required to write to a mailslot 
			(LPSECURITY_ATTRIBUTES) NULL, 
			OPEN_EXISTING, 
			FILE_ATTRIBUTE_NORMAL, 
			(HANDLE) NULL); 

		if (hFile == INVALID_HANDLE_VALUE) 
		{ 
			SysErrLog("�����¼��ʲ�ʧ��", NULL, LOG_LEVEL_TRACE);
			return false; 
		} 

		fResult = WriteFile(hFile, 
			lpszMessage, 
			(DWORD) lstrlen(lpszMessage) + 1,  // include terminating null 
			&cbWritten, 
			(LPOVERLAPPED) NULL); 

		if (!fResult) 
		{ 
			SysErrLog("���¼��ʲ����ʧ��", NULL, LOG_LEVEL_TRACE);
			return false; 
		} 
		
		fResult = CloseHandle(hFile);
		if (!fResult) 
		{ 
			SysErrLog("�ر��¼��ʲ�ʧ��", NULL, LOG_LEVEL_TRACE);
			return false; 
		} 
	}
	catch (...) {
		return false;
	}
	return true;
}


bool MonEventLog(LPCSTR lpszMessage)
{
	EventLog(lpszMessage);
	return WriteMailSlot("\\\\.\\mailslot\\ExpertSMSMonitor_Event", lpszMessage);
}



/********************************************************************
purpose:		��ȡ��ǰ��������·��	
Parameters:		��ǰ��������·��(����\��)	
Return Value:	true:�ɹ� false:ʧ��
*********************************************************************/
bool GetLocalPath(CString &strPath)
{
	char filepath[255];
	memset(filepath,0,255);
	::GetModuleFileName(NULL, filepath, 255);
	strPath.Format("%s", filepath);
	int nPos  = strPath.ReverseFind('\\');
	if (nPos < 0 ){
		return false;
	}
	strPath = strPath.Left(nPos+1);	
	return true;
}
/********************************************************************
purpose:    	��Word��ֵ�������λת��ΪBCD��,��1989,��89���BCD��
Parameters:		
Return Value:	BCD��
*********************************************************************/
unsigned char WORDToBCD(WORD value)
{
	value = value % 100;
	unsigned char r =  (value / 10) * 16 + value % 10;
	return r;
}

/********************************************************************
purpose:    	��Word��ֵ���ſ�����ת��Ϊ���ֽ�BCD��,�������ֽ�˳���ȴ���λ�󴫵�λ

Parameters:		
Return Value:	BCD��
*********************************************************************/
unsigned short DestDogToBCD(WORD value)
{   
	WORD value1,value2;

	value1 = value % 100;
	unsigned short r1 =  (value1 / 10) * 16 + value1 % 10;//����ʮ������������λר��BCD��

	value2 = value / 100;
	unsigned short r2 =  (value2 / 10) * 16 + value2 % 10;//����ʮ��������ǰ��λר��BCD��



	unsigned short r=(r2|(r1<<8));  //��������ѭ���ȴ��ߺ󴫵�

	return r;
}

/*********************************************************************
purpose:    	��Word��ֵ�ļ�¼��ŵ���˳���Ա���λ��ʶ���ȴ��ߺ󴫵�
Parameters:		
Return Value:	ʮ�����Ƶ�ַ
*********************************************************************/
unsigned short LittleToBig(WORD addr_l)
{
	WORD temp1,temp2,temp;
	temp1=addr_l&0x00ff;
	temp2=addr_l&0xff00;
	temp=(temp1<<8)|(temp2>>8);
	return temp;

}

/*********************************************************************
purpose:    	��Word��ֵ�Ŀ��źŵ���˳���Ա���λ��ʶ���ȴ��ߺ󴫵�
Parameters:		
Return Value:	ʮ�����ƿ���
*********************************************************************/
UINT32 LittleToBigAUTH(UINT32 card_id)
{
	UINT32 temp1,temp2,temp3,temp4,temp;
	temp1=card_id&0x000000ff;
	temp2=card_id&0x0000ff00;
    temp3=card_id&0x00ff0000;
	temp4=card_id&0xff000000;


	temp=(temp3>>8)|(temp4>>24)|(temp1<<24)|(temp2<<8);
	return temp;

}
