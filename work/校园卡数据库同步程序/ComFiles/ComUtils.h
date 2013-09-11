/********************************************************************
	created:	2006/03/06
	created:	6:3:2006   20:23
	file base:	ComUtils
	file ext:	h
	author:		张国华
	
	purpose:	公共函数声明头文件
*********************************************************************/

#pragma once
#include <afx.h>
#include "LogForMe.h"

//输出邮槽
bool WriteMailSlot(LPCSTR lpszMsName, LPCSTR lpszMessage);
//向监控程序输出事件
bool MonEventLog(LPCSTR lpszMessage);



//将无结束符字符串数组(最长9位,否则返回0)转化成数值型
unsigned int CharArrayToUINT(char *pChars, int size);
//时间减法运算,
SYSTEMTIME SubtractTime(SYSTEMTIME tm, UINT nMin);
//时间比较运算
int SysTimeComp(SYSTEMTIME tm1, SYSTEMTIME tm2);
//将字符数组转换成SYSTEMTIME变量
SYSTEMTIME CharAryToSysTime(const char* charyTime, int size);
//将SYSTEMTIME变量转换成字符数组
int SysTimeToCharAry(char* charyTime, int size, SYSTEMTIME systm);

//获取当前程序运行路径
bool GetLocalPath(CString &strPath);
unsigned char WORDToBCD(WORD value);

unsigned short DestDogToBCD(WORD value);
unsigned short LittleToBig(WORD addr_l);

UINT32 LittleToBigAUTH(UINT32 card_id);
