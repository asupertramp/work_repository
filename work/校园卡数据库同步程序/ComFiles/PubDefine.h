/********************************************************************
	created:	2006/03/06
	created:	6:3:2006   19:16
	filename: 	d:\Newwork\Hkquerysvr\ComFiles\PubDefine.h
	file path:	d:\Newwork\Hkquerysvr\ComFiles
	file base:	PubDefine
	file ext:	h
	author:		张国华
	
	purpose:	公共变量,类型定义 
*********************************************************************/
#pragma once 

#if !defined(PUBDEFINE_H_)
#define PUBDEFINE_H_

#include <string>
#include <vector>
#include <afxdisp.h>
using namespace std;





//数据库连接参数结构
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




#define  NORMAL	     0 	//正常
#define  LOST        1  //挂失
#define  ADDED        2  //新增
#define  MODIFIED         3  //修改
#define  DELETED         3  //修改


#define  NOT_IN_PROCECCING        0   //未使用中
#define  IN_PROCECCING            1   //使用中



typedef struct
{
	UINT8 minute;
	UINT8 hour;
	UINT8 day;
	UINT8 month;
	UINT8 year;
}Matt_Time;//用于表示授权有效时间的结构


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

//时间，BCD码格式
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
	UINT8 Secter;           //扇区号
	UINT16 Index;
	UINT8  Length;			//和Index的后8位相加不要超过128字节(写的时候，读的时候无所谓）
	UINT8  Data[128];		//Time 和flash的数据放在这里
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
	//UINT8 Type;		//射频卡＝＝00
	UINT32 CodeID;
	Matt_Time start_tm; //授权起始时间
	Matt_Time end_tm;   //授权结束时间
	BYTE  daycheck;     //用字节数表示的每周有效的天数例如00000101表示此授权周一，周三有效
	UINT8 remark;       //备用
	//UINT8 Pad[3];		//填充
}Dog_AuthorEntry;			//授权号存在0x4000开始的地方


typedef struct
{
	UINT8 Status;
	UINT8 Type;
	UINT32 CodeID;
	UINT8 Time[7];
	UINT8 Pad[3];
}Dog_RecordEntry;			//记录存放在0x8000开始的地方






#endif//!defined(PUBDEFINE_H_)