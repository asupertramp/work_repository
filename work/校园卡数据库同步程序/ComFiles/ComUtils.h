/********************************************************************
	created:	2006/03/06
	created:	6:3:2006   20:23
	file base:	ComUtils
	file ext:	h
	author:		�Ź���
	
	purpose:	������������ͷ�ļ�
*********************************************************************/

#pragma once
#include <afx.h>
#include "LogForMe.h"

//����ʲ�
bool WriteMailSlot(LPCSTR lpszMsName, LPCSTR lpszMessage);
//���س�������¼�
bool MonEventLog(LPCSTR lpszMessage);



//���޽������ַ�������(�9λ,���򷵻�0)ת������ֵ��
unsigned int CharArrayToUINT(char *pChars, int size);
//ʱ���������,
SYSTEMTIME SubtractTime(SYSTEMTIME tm, UINT nMin);
//ʱ��Ƚ�����
int SysTimeComp(SYSTEMTIME tm1, SYSTEMTIME tm2);
//���ַ�����ת����SYSTEMTIME����
SYSTEMTIME CharAryToSysTime(const char* charyTime, int size);
//��SYSTEMTIME����ת�����ַ�����
int SysTimeToCharAry(char* charyTime, int size, SYSTEMTIME systm);

//��ȡ��ǰ��������·��
bool GetLocalPath(CString &strPath);
unsigned char WORDToBCD(WORD value);

unsigned short DestDogToBCD(WORD value);
unsigned short LittleToBig(WORD addr_l);

UINT32 LittleToBigAUTH(UINT32 card_id);
