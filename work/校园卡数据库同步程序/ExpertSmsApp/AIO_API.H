// AIO_API.h : main header file for the AIO_API DLL
//

#if !defined(AFX_AIO_API_H__BD1503C4_0E12_45CB_855F_3B8A41D7790D__INCLUDED_)
#define AFX_AIO_API_H__BD1503C4_0E12_45CB_855F_3B8A41D7790D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "CardControl.h"
#include "CardDef.h"


//函数声明部分
#define EXTC extern "C"

EXTC int WINAPI NC_BussComm(char* sendBuf,int sendLen,char * recvBuf,
							int *recvLen,char priority,char * IP,short port,short timeOut = 5);
EXTC int WINAPI NC_UpLoadFile (char* fileName,char * IP,short port);
EXTC int WINAPI NC_DownLoadFile (char* fileName,char * IP,short port);
EXTC int WINAPI NC_DownControlFile(char * IP,short port,short timeOut = 10);
/*
 *函数名称：DSQL_Query_File
 *函数功能：DSQL查询(返回二进制文件)
 *参数列表：Dsql ：sql语句；fn：返回的文件名
 *			nblocknum：返回的记录数目；
 *			RetCode：Dsql查询的返回值
 *			IP：IP地址；port－端口号；portftp－ftp端口号
 *			timeOut－超时时间
 *返回值表：
 */
EXTC int WINAPI DSQL_Query_File(const char *Dsql , 
								char fillGap ,
								char *fn , 
								int * nBlockNum , 
								int	* RetCode ,
								char * IP,
								short port , 
								short ftpport,
								short timeOut = 5);
/*
 *函数名称：DSQL_Query_Record
 *函数功能：DSQL精确查询(返回一条二进制记录或者文本记录, size < 1024)
 *参数列表：Dsql：sql语句；sBlock：返回记录缓冲区(size = 1024)
 *			fillGap:分割符 (如果是'\0'返回二进制文件，
 *			其他返回以FillGap分隔的文本文件)；
 *			RetCode：Dsql查询的返回值
 *			nBlockSize：返回的记录大小,IP：IP地址；port－端口号；
 *			timeOut－超时时间
 *返回值表：
 *备注：
 */
EXTC int WINAPI DSQL_Query_Record(	const char *Dsql , 
									char fillGap ,
									char * sBlock , 
									int * nBlockSize , 
									int	* RetCode ,
									char * IP,
									short port ,
									short timeOut = 5);
/*
 *函数名称：DSQL_Oper_Record
 *函数功能：DSQL操作记录
 *参数列表：Dsql：sql语句；nReturn：操作返回值,IP：
 *			IP地址；port－端口号；
 *			timeOut－超时时间
 *返回值表：
 *备注：
 */
EXTC int WINAPI DSQL_Oper_Record(const char *Dsql , 
								 int * nReturn , 
								 char * IP,
								 short port ,
								 short timeOut = 5);

/*函数名:G_GetAPIPath
**功能:取得API的路径
**输出参数:szPath－API的路径缓冲区，nBuffLen － 缓冲区的长度
**输入参数:无
**返回值:void
**创建日期：2003-07-08
*/
EXTC void WINAPI G_GetAPIPath(char *szPath , WORD nBuffLen);

/*
 *函数名称：G_Chg_NodeID
 *函数功能：综合业务子系统通知综合前置机重建节点信息
 *参数列表：无
 *返回值表：参见返回值表
 *备注：需要综合业务每次全部增加、删除、修改完节点时，
 *		通知一次就可以，不要多次通知，影响性能
 */
EXTC int WINAPI G_Chg_NodeID();
EXTC void WINAPI G_GetAPIPath(char *szPath , WORD nBuffLen);
/*函数名:EC_GetCfg
 *功能:取得加密卡中的全局配置
 *输出参数:peh-加密卡头部信息，pec－全局配置结构指针
 *输入参数:无
 *返回值:RET_OK/RET_ERR_ENCARD
 *备注：
 */
EXTC int WINAPI EC_GetCfg( PUCHAR pec);
EXTC BOOL WINAPI G_PW_Encrypt( char *iBuf, int iLen, char *oBuf );
EXTC BOOL WINAPI G_PW_Decrypt( char *iBuf, int iLen, char *oBuf );
EXTC BOOL WINAPI G_Sign( char *iBuf, int iLen, char *oBuf );




/*
**函数名称：NC_DownPhotoFile
**函数功能：下载相片文件
**输入参数：IP-SIOS的IP地址, port-sios 的端口号,
**			IDNo-身份序号，PhotoFn-相片文件的名称
**输出参数: 无
**返回值:	大于0表示上送的文件的大小，小于0表示失败
**创建时间：2003-09-08
*/
EXTC int  WINAPI NC_DownPhotoFile(char *IP , short Port , 
								   char * IDNo , 
								   char *PhotoFn, 
								   short TimeOut=10);



/*
**函数名称：TA_Init
**函数功能：设置动态库以第三方方式运行
**参数说明：IP-SIOS的IP地址, port-sios 的端口号 
**			SysCode-系统代码,ProxyOffline-代理服务是否脱机
**			MaxJnl-最大流水号
**返回值：TRUE/FALSE
**创建时间：2003-08-21
**修改时间：2004-03-10
**修改内容：去掉参数CardKey-卡片密钥
**			改名TA_Init
*/
EXTC BOOL  WINAPI TA_Init(char *IP , short port , unsigned short SysCode, 
						  unsigned short TerminalNo, bool *ProxyOffline, ULONG *MaxJnl);

/*
**函数名称：TA_CRInit
**函数功能：初始化读卡器
**参数列表：CardReaderType－输入参数，读卡器类型，0－usb读卡器，1－串口读卡器。
**			port－输入参数，端口号，
**			Baud_Rate－输入参数，波特率，
**返回值:	见返回值列表
**创建时间：2004-03-10
*/
EXTC int _stdcall TA_CRInit(char CardReaderType,int port,long Baud_Rate);

/*
**函数名称：TA_CRClose
**函数功能：关闭读卡器
**参数列表：void
**返回值:	true/false
**创建时间：2004-03-10
*/
EXTC BOOL _stdcall TA_CRClose(void);

/*
**函数名称：TA_FastReadCard
**函数功能：快速读卡号，适用于检验是否有卡靠近读卡反应区
**			如果只需要快速读取卡号，则不需要初始化动态库(TA_Init())
**参数列表：CardNo－输出参数，从卡片中读出的卡号
**返回值:	见返回值列表Errormsg.h
**创建时间：2004-03-10
*/
EXTC int _stdcall TA_FastGetCardNo(unsigned int *CardNo);


/*
**函数名称：TA_CRBeep
**函数功能：读卡器峰鸣
**参数列表：BeepSecond－输入参数，峰鸣的毫秒数。
**返回值:	见返回值列表Errormsg.h
**创建时间：2004-03-10
*/
EXTC int _stdcall TA_CRBeep(unsigned int BeepMSecond);

/*
**函数名称：TA_ReadCardSimple
**函数功能：简单读卡信息，不检验白名单。
**参数列表：pAccMsg－输出参数，从卡片中读出的卡片信息。
**返回值:	见返回值列表Errormsg.h
**创建时间：2004-03-10
*/
EXTC int _stdcall TA_ReadCardSimple(AccountMsg * pAccMsg);




/*
**函数名称：TA_CheckWL
**函数功能：第三方根据帐号和卡号检查白名单。
**参数列表：AccountNo－输入参数，需要验证的帐号
**			CardNo－输入参数，卡号
**			CheckID－输入参数，是否检验身份开通关闭状态
**返回值:	见返回值列表Errormsg.h
**创建时间：2004-03-10
*/
EXTC int _stdcall TA_CheckWL (unsigned int AccountNo , unsigned int CardNo , bool CheckID=true);


/*
**函数名称：TA_ReadCard
**函数功能：读卡信息。读出卡信息并检验白名单，判断卡片的有效性。
**参数列表：pAccMsg－帐户信息包,如果需要请求补助时必须填写pAccMsg->TerminalNo
**			CheckID－输入参数，是否检验身份开通关闭状态
**			CheckSub－输入参数，是否提取补助
**返回值:	见返回值列表Errormsg.h
**创建时间：2004-03-10
*/
EXTC int _stdcall TA_ReadCard(AccountMsg *pAccMsg,bool CheckID=true ,bool CheckSub= false);


/*
**函数名称：TA_CardOpen
**函数功能：开通
**参数列表：pCardOper－第三方操作的整体数据包，在这里需要填写的参数是帐号和经手人。
**			pCardOper->RetCode是后台交易的返回值
**			TimeOut － 输入参数，超时时间（秒），缺省值为10秒。
**返回值:	见返回值列表Errormsg.h
**创建时间：2004-03-11
*/
EXTC int _stdcall TA_CardOpen(CardOperating *pCardOper, short TimeOut = 10);

/*
**函数名称：TA_CardClose
**函数功能：关闭
**参数列表：pCardOper－第三方操作的整体数据包，在这里需要填写的参数是帐号和操作员。
**			pCardOper->RetCode是后台交易的返回值
**			TimeOut － 输入参数，超时时间（秒），缺省值为10秒。
**返回值:	见返回值列表Errormsg.h
**创建时间：2004-03-11
*/
EXTC int _stdcall TA_CardClose(CardOperating *pCardOper, short TimeOut=10);

/*
**函数名称：TA_CardLost
**函数功能：挂失
**参数列表：pCardOper－第三方操作的整体数据包，在这里需要填写的参数是帐号和操作员。
**			pCardOper->RetCode是后台交易的返回值
**			TimeOut － 输入参数，超时时间（秒），缺省值为10秒。
**返回值:	见返回值列表Errormsg.h
**创建时间：2004-03-11
*/
EXTC int _stdcall TA_CardLost(CardOperating *pCardOper, short TimeOut=10);

/*
**函数名称：TA_Consume
**函数功能：卡片消费(可以脱机)
**参数列表：pCardCons－第三方操作的整体数据包,要求必须填入卡号
**			pCardCons->RetCode是后台交易的返回值
**			IsVerfy－是否验证累计消费额，如果超过累计消费额，则需要输入消费密码。
**			TimeOut － 输入参数，超时时间（秒），缺省值为10秒。
**返回值:	见返回值列表Errormsg.h
**创建时间：2004-03-11
*/
EXTC int _stdcall TA_Consume(CardConsume *pCardCons, bool IsVerfy, short TimeOut=10);


/*
**函数名称：TA_Refund
**函数功能：卡片退费(联机交易)
**参数列表：pCardCons－第三方操作的整体数据包,要求必须填入卡号
**			pCardCons->RetCode是后台交易的返回值
**			TimeOut － 输入参数，超时时间（秒），缺省值为10秒。
**返回值:	见返回值列表Errormsg.h
**创建时间：2004-03-15
*/
EXTC int _stdcall TA_Refund(CardConsume *pCardCons , short TimeOut=10);



/*
**函数名称：TA_InqAcc
**函数功能：根据帐号/卡号/学工号/证件号精确查询帐户信息
**参数列表：pAccMsg－第三方帐户信息的整体数据包
**			(需要填写卡号或者是帐号或者是学工号或者是证件号)。
**			输出参数，pAccMsg ->RetCode为后台处理的返回值
**			TimeOut － 输入参数，超时时间（秒），缺省值为10秒。
**返回值:	见返回值列表Errormsg.h
**创建时间：2004-03-15
*/
EXTC int _stdcall TA_InqAcc(AccountMsg * pAccMsg, short TimeOut = 10);



/*
**函数名称：TA_HazyInqAcc
**函数功能：按部门代码模糊查询持卡人信息。
**参数列表：pAccMsg－输入参数，查询条件(可以根据Name,DeptCode,SexNo,StudentNo,PID查询)
**			查询的文件放到RecvTemp目录下，文件名写入到FileName中
**			FileName－输出参数，返回的文件名称，最少64个字节
**			RecNum-输出参数，查询到的记录数目
**			TimeOut － 输入参数，超时时间（秒），缺省值为10秒。
**返回值:	见返回值列表Errormsg.h
**创建时间：2004-03-15
*/
EXTC int _stdcall TA_HazyInqAcc(AccountMsg *pAccMsg, int *RecNum , char *FileName,short TimeOut = 10);

/*
**函数名称：TA_InqTranFlow
**函数功能：交易流水查询。
**参数列表：pInqTranFlow－输入参数,可以根据持卡人帐号、商户帐号、
**			终端号码组合查询当天的或者历史的交易流水。
**			查询的文件放到RecvTemp目录下，文件名写入到pInqTranFlow->FileName中。	
**			pInqTranFlow->RecNum-输出参数，查询到的记录数目
**			TimeOut － 输入参数，超时时间（秒），缺省值为10秒。
**返回值:	见返回值列表Errormsg.h
**创建时间：2004-03-15
*/
EXTC int _stdcall TA_InqTranFlow(InqTranFlow *pInqTranFlow, short TimeOut = 10);


/*
**函数名称：TA_InqOpenFlow
**函数功能：开通流水查询。
**参数列表：pInqOpenFlow－输入参数,可以根据持卡人帐号、商户帐号、
**			终端号码组合查询当天的或者历史的交易流水。
**			查询的文件放到RecvTemp目录下，文件名写入到pInqOpenFlow->FileName中。	
**			pInqOpenFlow->RecNum-输出参数，查询到的记录数目
**			TimeOut － 输入参数，超时时间（秒），缺省值为10秒。
**返回值:	见返回值列表Errormsg.h
**创建时间：2004-03-15
*/
EXTC int _stdcall TA_InqOpenFlow(InqOpenFlow *pInqOpenFlow, short TimeOut = 10);


/*
**函数名称：TA_Charge
**函数功能：卡片收费
**参数列表：pCardCharg－第三方操作的整体数据包,要求必须填入卡号
**			pCardCharg->RetCode是后台交易的返回值
**			IsVerfy－是否验证累计消费额，如果超过累计消费额，则需要输入消费密码。
**			TimeOut － 输入参数，超时时间（秒），缺省值为10秒。
**返回值:	见返回值列表Errormsg.h
**创建时间：2004-03-11
*/
EXTC int _stdcall TA_Charge(CardCharge *pCardCharg, bool IsVerfy, short TimeOut=10);

/*函数名:TA_DownControlFile
 *功能:下载控制文件，控制文件的目录是\ControlFile
 *输入参数:timeout－超时时间
 *输出参数:无
 *返回值:大于0表示下载的文件的大小，小于0表示失败
 */
EXTC int _stdcall TA_DownControlFile(short timeOut=10);



/*
**函数名称：TA_DownPhotoFile
**函数功能：下载相片文件
**输入参数：IDNo-身份序号，PhotoFn-相片文件的名称
**输出参数: 无
**返回值:	大于0表示上送的文件的大小，小于0表示失败
**创建时间：2004-03-19
*/
EXTC int  _stdcall TA_DownPhotoFile(char * IDNo , 
								   char *PhotoFn, 
								   short TimeOut=10);

/*
 *函数名称：TA_Dsql_QFile
 *函数功能：第三方DSQL查询(返回二进制文件或者文本文件)
 *参数列表：Dsql ：sql语句；fn：返回的文件名
 *			fillGap:分割符 (如果是'\0'返回二进制文件，
 *			其他返回以FillGap分隔的文本文件)；
 *			nblocknum：返回的记录数目；
 *			RetCode：Dsql查询的返回值
 *			timeOut－超时时间
 *返回值表：
 */
EXTC int _stdcall TA_Dsql_QFile(const char *Dsql , 
								char fillGap ,
								char *fn , 
								int * nBlockNum , 
								int	* RetCode ,
								short timeOut=10);

/*
 *函数名称：TA_Dsql_QRecord
 *函数功能：第三方DSQL精确查询(返回一条二进制记录或者文本记录, size < 1024)
 *参数列表：Dsql：sql语句；sBlock：返回记录缓冲区(size = 1024)
 *			fillGap:分割符 (如果是'\0'返回二进制文件，
 *			其他返回以FillGap分隔的文本文件)；
 *			nBlockSize：输入输出参数，输入－缓冲区的的大小，输出－返回的记录大小
 *			RetCode：Dsql查询的返回值
 *			timeOut－超时时间
 *返回值表：
 *备注：
 */
EXTC int _stdcall TA_Dsql_QRecord(	const char *Dsql , 
									char fillGap ,
									char * sBlock , 
									int * nBlockSize , 
									int	* RetCode ,
									short timeOut=10);

/*
 *函数名称：TA_Dsql_ORecord
 *函数功能：第三方DSQL操作记录
 *参数列表：Dsql：sql语句；nReturn：操作返回值,IP：
 *			IP地址；port－端口号；
 *			timeOut－超时时间
 *返回值表：
 *备注：
 */
EXTC int _stdcall TA_Dsql_ORecord(const char *Dsql , 
								 int * nReturn , 
								 short timeOut=10);
/*
**函数名:TA_BussComm
**功能:第三方向sios发送并接收加密和校验的数据包
**输入参数:sendBuf-要分解的数据;sendLen-要分解数据的长度,priority-优先级
**			timeout－通讯超时,缺省是10秒
**			recvLen-分配的缓冲区长度
**输出参数:recvBuf-解包完成后的数据;recvLen-解包后的数据长度
**返回值:参见返回值列表
**创建时间：2004-03-26
**修改记录：
*/
EXTC int WINAPI TA_BussComm(char* sendBuf,
							int sendLen,
							char * recvBuf,
							int *recvLen,
							char priority,
							short timeOut=10);

/*函数名:TA_DownLoadFile
 *功能:下载文件，返回文件的目录是\RecvTemp
 *输入参数:fn-文件名称，timeout－超时时间
 *输出参数:无
 *返回值:大于0表示下载的文件的大小，小于0表示失败
 */
EXTC int _stdcall TA_DownLoadFile(char *fn , short timeOut=5);


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AIO_API_H__BD1503C4_0E12_45CB_855F_3B8A41D7790D__INCLUDED_)
