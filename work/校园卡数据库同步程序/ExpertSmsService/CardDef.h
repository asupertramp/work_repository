#if !defined(CARDDEF_H_)
#define CARDDEF_H_

#pragma pack(1)

/*卡操作的包*/

typedef struct

{

unsigned int AccountNo; /*帐号*/

char StudentNo[21]; /*学号*/

char inqPassword[7]; /*查询密码*/

char Operator[3]; /*操作员*/

short RetCode; /*后台处理返回值*/

} CardOperating;

/*卡片消/退费的包*/

typedef struct

{

unsigned int AccountNo; /*帐号*/

unsigned int CardNo; /*卡号*/

char FinancingType[3]; /*财务类型*/

int CardBalance; /*卡余额,精确至分*/

int TranAmt; /*交易额,精确至分*/

unsigned short UseCardNum; /*用卡次数，交易前*/

unsigned short TerminalNo; /*终端编号*/

char PassWord[7]; /*卡密码*/

char Operator[3]; /*操作员*/

char Abstract[129]; /*摘要*/

unsigned int TranJnl; /*交易流水号*/

unsigned int BackJnl; /*后台交易流水号*/

short RetCode; /*后台处理返回值*/

} CardConsume;

/*卡片收费的包*/

typedef struct

{

char Operator[4]; /*操作员*/

unsigned int AccountNo; /*帐号*/

unsigned int MercAcc; /*商户帐号2004-04-28增加*/

unsigned int CardNo; /*卡号*/

unsigned int FeeID; //收费ID号

int TranAmt; /*交易额,精确至分*/

char ConsumeType[4]; //收费类型

char FeeFlag[6]; /*FeeFlag[0]：0_自助交费 1_自动交费*/

/*FeeFlag[1]：0_校园卡交费 1_银行卡交费 2_现金交费 3_银行代收 */

/*FeeFlag[2]：0_已交费 1_未交费 2_已对帐 3_已核销 4_已作废*/

/*FeeFlag[3]: 0_一次交清 1_分期交费*/

char FeeDesc[31]; //费用描述

int CardBalance; /*卡余额,精确至分*/

unsigned short TerminalNo; /*终端编号*/

char FeeTerm[11]; /*费用时序*/

char BankAcc[21]; /*银行卡号*/

char Cname[31]; /*中文名姓名*/

char IdentityCode[21]; /*身份证号*/

int LateFeeAmt; /*滞纳金额 精确至分*/

int LateFeeRate; /* 滞纳金率 */

char LateFeeStDate[15]; /*滞纳金起计日期 YYYYMMDD*/

char ExpDate[15]; /* 必交费有效期 */

char BillNo[51]; /* 票据编号 */

unsigned int TranJnl; /*交易流水号*/

unsigned int BackJnl; /*后台交易流水号*/

short RetCode; /*后台处理返回值*/

} CardCharge;

/*帐户信息包*/

typedef struct

{

char Name[21]; /*姓名*/

char SexNo[2]; /*性别*/

char DeptCode[19]; /*部门代码*/

unsigned int CardNo; /*卡号*/

unsigned int AccountNo; /*帐号*/

char StudentCode[21]; /*学号*/

char IDCard[21]; /*身份证号*/

char PID[3]; /*身份代码*/

char IDNo[13]; /*身份序号*/

int Balance; /*现余额*/

char Password[7]; /*消费密码*/

char ExpireDate[7]; /*账户截止日期*/

unsigned short SubSeq; /*补助戳*/

char IsOpenInSys; /*是否在本系统内开通*/

short TerminalNo; /*终端号码*/

short RetCode; /*后台处理返回值*/

} AccountMsg;

/*查询交易流水的数据包*/

typedef struct

{

char InqType; /*查询类型,0-查询当日流水;1-历史流水*/

unsigned int Account; /*持卡人帐号*/

unsigned int MercAcc; /*商户帐号*/

short TerminalNo; /*终端号码*/

char StartTime[15]; /*起始时间,YYYYMMDDHHMMSS*/

char EndTime[15]; /*结束时间,YYYYMMDDHHMMSS*/

char FileName[64]; /*接收到的文件名称*/

int RecNum; /*查询到的记录数目*/

}InqTranFlow;

/*查询开通流水*/

typedef struct

{

unsigned int Account; /*持卡人帐号*/

char FileName[64]; /*接收到的文件名称*/

int RecNum; /*查询到的记录数目*/

}InqOpenFlow;


//模糊查询时返回的流水文件格式:

#pragma pack(1) 


/*模糊查询帐户信息包*/
typedef struct
{
	char      		Name[31]; 			/*姓名*/
	char      		SexNo[2]; 			/*性别*/
	char			DeptCode[19];		/*部门代码*/
	unsigned int	CardNo; 			/*卡号*/
	unsigned int	AccountNo; 		/*帐号*/
	char			StudentCode[21];	/*学号*/
	char			IDCard[21]; 		/*身份证号*/
	char			PID[3];			/*身份代码*/
	char			IDNo[13]; 			/*身份序号*/
	int			Balance; 			/*现余额*/
	char			ExpireDate[7];		/*账户截止日期*/
	unsigned int		SubSeq;			/*补助戳*/
}HazyInqAccMsg;


/*流水文件结构*/

typedef struct

{

long Account; /*帐号*/

long BackJnl; /*后台流水号*/

long MercAccount; /*商户帐号*/

long TerminalNo; /*终端编号*/

char OperCode[4]; /*操作员编号*/

char TranCode[3]; /*事件代码*/

char JnlStatus[2]; /*流水状态*/

char JnDateTime[15]; /*流水发生日期时间YYYYMMDDHH24MISS*/

char EffectDate [9]; /*流水生效日期YYYYMMDD*/

long Balance; /*余额*/

long TranAmt; /*交易额*/

char ConsumeType[4]; /*财务类型*/

char Resume[129]; /*备注*/

}TrjnFlowFile;

/*模糊查询时返回的开通流水的文件结构*/

typedef struct

{

long Account; /*帐号*/

long SysCode; /*开通系统系统代码*/ 

char  SysName[41];    /*开通系统系统名称*/

char OpenDate[15]; /*开通日期YYYYMMDDHH24MISS*/

}OpenFlowFile;

#pragma pack()

#endif
