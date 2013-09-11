/********************************************************************
	created:	2006/03/06
	created:	6:3:2006   19:16
	filename: 	d:\Newwork\Hkquerysvr\ComFiles\PubDefine.h
	file path:	d:\Newwork\Hkquerysvr\ComFiles
	file base:	PubDefine
	file ext:	h
	author:		�Ź���
	
	purpose:	��������,���Ͷ��� 
*********************************************************************/
#pragma once 

#if !defined(PUBDEFINE_H_)
#define PUBDEFINE_H_

#include <string>
#include <vector>
#include <afxdisp.h>
using namespace std;





//���ݿ����Ӳ����ṹ
typedef struct _DBConnect_Param{
	char	DRIVER[128];
	char	DSN[128];
	char	USER[64];
	char	PASS[64];
}DBCON_PARAM;


typedef struct {
	CString ID;
	CString CardID;
	int status;
}ACCOUNT_MSG;




#define  NORMAL	     0 	//����
#define  LOST        1  //��ʧ
#define  ADDED        2  //����
#define  MODIFIED         3  //�޸�
#define  DELETED         3  //�޸�


#define  NOT_IN_PROCECCING        0   //δʹ����
#define  IN_PROCECCING            1   //ʹ����



typedef struct
{
	UINT8 minute;
	UINT8 hour;
	UINT8 day;
	UINT8 month;
	UINT8 year;
}Matt_Time;//���ڱ�ʾ��Ȩ��Чʱ��Ľṹ


typedef struct _ROOMMEMBER{
    UINT id;
	Matt_Time   begintime;
	Matt_Time   endtime;
	UINT   room_id;
	DWORD  user_id;
	UINT   curstate;
	//UINT    membertype;
}ROOMMEMBER;







typedef unsigned char	UINT8;
typedef unsigned short	UINT16;

//ʱ�䣬BCD���ʽ
typedef struct
{
	UINT8 Seconds;
	UINT8 Minutes;
	UINT8 Hours;
	UINT8 Days;
	UINT8 WeekDays;
	UINT8 Months;
	UINT8 Years;
}Dog_Time;				

typedef struct
{
	UINT8 Type;
	UINT8 Secter;           //������
	UINT16 Index;
	UINT8  Length;			//��Index�ĺ�8λ��Ӳ�Ҫ����128�ֽ�(д��ʱ�򣬶���ʱ������ν��
	UINT8  Data[128];		//Time ��flash�����ݷ�������
}Dog_Command;

typedef struct
{
	UINT16 DestAddress;
	//UINT16 SourceAddress;
	Dog_Command Command;
	UINT8 Pad;	
}Dog_CommPackage;



typedef struct
{
	//UINT8 Type;		//��Ƶ������00
	UINT32 CodeID;
	Matt_Time start_tm; //��Ȩ��ʼʱ��
	Matt_Time end_tm;   //��Ȩ����ʱ��
	BYTE  daycheck;     //���ֽ�����ʾ��ÿ����Ч����������00000101��ʾ����Ȩ��һ��������Ч
	UINT8 remark;       //����
	//UINT8 Pad[3];		//���
}Dog_AuthorEntry;			//��Ȩ�Ŵ���0x4000��ʼ�ĵط�


typedef struct
{
	UINT8 Status;
	UINT8 Type;
	UINT32 CodeID;
	UINT8 Time[7];
	UINT8 Pad[3];
}Dog_RecordEntry;			//��¼�����0x8000��ʼ�ĵط�






#endif//!defined(PUBDEFINE_H_)