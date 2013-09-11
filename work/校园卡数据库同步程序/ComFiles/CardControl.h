#if !defined(CARDCONTROL_H_)
#define CARDCONTROL_H_

/*下面是控制文件的结构*/

/*前8+30 * sizeof (struct tabCtrlHead)为文件头*/

/* 前8字节为SYNTONG */

/*表顺序如下：*/

/*ID_CONTROL.BIN 文件头

位置 头结构 对应数据表名称

================================================

#0 TControlHeadRec0 部门组织表

#1 TControlHeadRec1 身份代码表

#2 TControlHeadRec2 证件类型表

#3 TControlHeadRec3 民族表

#4 TControlHeadRec4 国籍表

#5 TControlHeadRec5 政治面貌

#6 TControlHeadRec6 校/厂区代码表

#7 TControlHeadRec7 宿舍（苑/栋）

#8 TControlHeadRec8 文化程度

#9 TControlHeadRec9 卡样管理表

#10 TControlHeadRec10 技术职称

#11 TControlHeadRec11 行政职务

================================================*/

#define CONTROL_STR "SYNTONG" /* 控制文件标识 */

#define OFFSET_T_DEPARTMENT 0 /* 部门组织表 */

#define OFFSET_T_PID 1 /* 身份代码表 */

#define OFFSET_T_IDTYPE 2 /* 证件类型表 */

#define OFFSET_T_PEOPLE 3 /* 民族表 */

#define OFFSET_T_NATION 4 /* 国籍表 */

#define OFFSET_T_ZZMM 5 /* 政治面貌 */

#define OFFSET_T_AREA 6 /* 校/厂区代码表 */

#define OFFSET_T_SS_YUAN 7 /* 宿舍（苑/栋 */

#define OFFSET_T_WHCD 8 /* 文化程度 */

#define OFFSET_T_CARDTYPE 9 /* 卡样管理表 */

#define OFFSET_T_JSZC 10 /* 技术职称 */

#define OFFSET_T_XZZW 11 /* 行政职务 */

#define OFFSET_SCHOOLCODE 12 /* 0:学校代码SchoolCode*/

#define OFFSET_SUBJECT 13 /* 1:日报字典Subject*/

#define OFFSET_FEE 14 /* 2:操作费用设定表fee*/

#define OFFSET_CONFIGINFO 15 /* 3:各种代码字典ConfigInfo*/

#define OFFSET_BRANCH 16 /* 4:商户部门表branch*/

#define OFFSET_CSZD 17 /* 5:系统参数cszd*/

#define OFFSET_TRCD 18 /* 6:事件代码表trcd*/

#define OFFSET_MESSAGE 19 /* 7:系统信息表message*/


#pragma pack(1)

//文件头

struct tabCtrlHead

{

unsigned short structlength; /*每条记录长度*/

unsigned short count; /*记录数量*/

long offset; /*从文件头开始，该表第一条记录偏移量*/

};

//部门组织结构

struct t_department{

char dept_code[15+1];    //部门代码

char dept_name[40+1];    //部门名称

char area_code[3+1];    //所属校/厂区

char dept_level;        //部门级别

char dept_easycode[10+1];    //助记码

char dept_type;            //部门类型

char dept_flag;            //启用状态

char dept_desc[20+1];    //描述信息

char dept_opercode[3+1];    //操作员代码

};

 //身份类型

struct t_pid{

char pid_code[2+1];    //身份代码

char class_code;        //持卡人类型（1学生，2教工，3校外人员）

char area_code[3+1];    //校/厂区代码

char pid_name[40+1];    //身份名称

char pid_easycode[10+1];    //助记码

char pid_flag;            //启用状态

char pid_opercode[3+1];     //操作员代码

char pid_cardtypeno[3+1];    //卡样式号

int pid_zkl;            //折扣率

};

 //证件类型表

struct t_idtype{

char idtype_code[3+1];

char idtype_name[16+1];

char idtype_easycode[10+1];

};

//民族表

struct t_people{

char people_code[2+1];

char people_name[10+1];

char people_easycode[10+1];

char people_flag;

};

//国籍表

struct t_nation{

char nation_code[2+1];

char nation_name[10+1];

char nation_easycode[10+1];

char nation_flag;

};

//政治面貌

struct t_zzmm{

char zzmm_code[2+1];

char zzmm_name[30+1];

char zzmm_easycode[10+1];

char zzmm_flag;

};

//校/厂区代码表

struct t_area{

char area_code[3+1];

char area_name[40+1];

char area_easycode[10+1];

};

/* 2003/08/06 add */

//宿舍（苑/栋）

struct t_ss_yuan {

char code[3+1];   //代码

char name[20+1];     //名称

char easycode[10+1];//助记码

char type;          //类型

};

//文化程度

struct t_whcd {

char code[2+1];

char name[20+1];

char easycode[10+1];

char useflag;

};

//卡样式管理

struct t_cardtype {

char cardtypeno[2+1];

char cardtypename[20+1];

char cardcontent[100+1];

char useflag;

};

//技术职称

struct t_jszc {

char code[3+1];

char name[30+1];

char easycode[10+1];

char useflag;

};

//行政职务

struct t_xzzw {

char code[3+1];

char name[30+1];

char easycode[10+1];

char useflag;

};

/* add end */

//学校代码

struct t_schcode{

char SchCode[2+1];

char Name[40+1];

char EnglishName[81];

char Address[81];

char Remark[41];

};

//日报字典

struct t_subject{

char SubjectCode[8+1];

char SubjectName[18+1];

char ShortName[12+1];

char SuperSubject[8+1];

int Sequence;

char flag[11];

};

//操作费用设定表

struct t_fee{

char FeeCode[3+1];

char FeeName[20+1];

char SchCode[2+1];

char TranCode[2+1];

char PID[2+1];

int FeeAmt;

int FeeAmtRate;

char FeeFlag[3];

};

//各种代码字典

struct t_configinfo{

char Code[3+1];

char Name[41];

char AssistantCode[10+1];

char Type[3];

};

//商户部门表

struct t_branch{

char DeptCode[4];

char AssistantCode[10+1];

char Name[31];

char SuDeptCode[4];

char DeptLevel;

char DeptType;

};

//系统参数

struct t_cszd{

char Code[4];

char Name[21];

char Value[21];

char Remark[41];

char Flag[3];

};

//事件代码表

struct t_trcd{

char TranCode[2+1];

char TranName[40+1];

char Flag[11];

};

//系统信息表

struct t_message{

short MsgCode;

char Describe[251];

};

#pragma pack()

//附录3：返回值定义

#define ERR_EXCEPTION -9999 //截获异常

#define ERR_OK 0 //交易成功

#define ERR_VER -1 //版本不符

#define ERR_RETCODE -2 //返回码不对

#define ERR_LENGTH -3 //数据长度不对

#define ERR_FILENAME -4 //文件名非法

#define ERR_FILESTAT -5 //文件访问状态非法

#define ERR_FAIL -6 //操作失败

/*sios error : ERR_SIOS_ */

#define ERR_SIOS_NOREC -100 //指定的记录不存在

#define ERR_SIOS_DOWNLOAD -101 //下载文件失败



/*net error : ERR_NET_ */

#define ERR_NET_CONNECT -200 //网络连接不通

#define ERR_NET_SEND -201 //数据发送出错

#define ERR_NET_RECV -202 //数据接收出错

#define ERR_NET_RECVFILE -203 //接收文件出错

#define ERR_NET_SENDFILE -204 //发送文件出错

/*trans errot : ERR_TRN_ */

#define ERR_TRN_SUBCODE -300 //无效的子系统代码

#define ERR_TRN_STATION -301 //无效的站点号



/*EN_CARD error : ERR_ENCARD_ */

#define ERR_ENCARD_RHEAD -500 //读加密卡头错

#define ERR_ENCARD_CONFIG -501 //读配置区出错

#define ERR_ENCARD_RKEY -502 //读密钥错

#define ERR_ENCARD_OPEN -503 //打开加密卡失败



/*DLL error : ERR_DLL_ from -1000 */

#define ERR_DLL_SIOS -1001 //SIOS没有正常运行

#define ERR_DLL_DSQL -1002 //DSQL操作错误

#define ERR_DLL_BUF_MIN -1003 //分配的缓冲区太小，不能拷贝

#define ERR_DLL_UNPACK -1004 //解包出错

#define ERR_DLL_REDO -1005 //重做业务2003-09-05

#define ERR_DLL_NOPHOTO -1006 //没有相片文件

#define ERR_DLL_NOFILE -1007 //指定文件不存在

/*定义升级返回值 from 1100*/

#define ERR_FILEEXIST -1100 //文件已经存在

#define ERR_REFUSE -1101 //操作被拒绝

#define ERR_NO_FILE -1102 //没有文件

#define ERR_DEL_FAIL -1103 //删除文件失败

#define ERR_COMM_FAIL -1104 //通讯失败



/*第三方返回值定义 from 1200*/

#define ERR_TA_TRANAMT -1200 //交易额错误

#define ERR_TA_NOT_INIT -1201 //第三方API没有初始化

#define ERR_TA_CARDREADER -1202 //读卡器错误

#define ERR_TA_READCARD -1203 //读卡失败

#define ERR_TA_WRITECARD -1204 //写卡失败

#define ERR_TA_LIMIT_FUNC -1205 //函数调用功能限制

#define ERR_TA_CARDTYPE -1206 //不是消费卡

#define ERR_TA_SNO -1207 //非本院校卡

#define ERR_TA_EXPIRECARD -1208 //过期卡

#define ERR_TA_FAIL_CHGUT -1209 //修改用卡次数失败

#define ERR_TA_NOT_SAMECARD -1210 //写卡时卡号不符

#define ERR_TA_WRONG_PWD -1211 //卡消费时输入密码错误

#define ERR_TA_LOW_BALAN -1212 //卡内余额不足

#define ERR_TA_EXCEED_QUOTA -1213 //超过消费限额

#define ERR_TA_LOST_CARD -1214 //挂失卡

#define ERR_TA_FREEZE_CARD -1215 //冻结卡

#define ERR_TA_CARDNO -1216 //卡号帐号不符

#define ERR_TA_ID_CLOSE -1217 //身份关闭

#define ERR_TA_CR_DLL -1218 //加载读卡器动态链接库失败

#define ERR_TA_CR_INIT -1219 //读卡器初始化失败

#define ERR_TA_PARA -1220 //参数错误

#define ERR_TA_NOREC -1221 //没有这个帐户

#define ERR_TA_SUB_SUCC -1222 //补助成功,也是正确的返回信息

#define ERR_TA_SUB_FAIL -1223 //补助失败,也是正确的返回信息

#define ERR_TA_INITED -1224 //读卡器已经初始化，请关闭

#endif