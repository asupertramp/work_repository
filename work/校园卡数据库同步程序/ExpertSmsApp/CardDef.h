#if !defined(CARDDEF_H_)
#define CARDDEF_H_

#pragma pack(1)

/*�������İ�*/

typedef struct

{

unsigned int AccountNo; /*�ʺ�*/

char StudentNo[21]; /*ѧ��*/

char inqPassword[7]; /*��ѯ����*/

char Operator[3]; /*����Ա*/

short RetCode; /*��̨������ֵ*/

} CardOperating;

/*��Ƭ��/�˷ѵİ�*/

typedef struct

{

unsigned int AccountNo; /*�ʺ�*/

unsigned int CardNo; /*����*/

char FinancingType[3]; /*��������*/

int CardBalance; /*�����,��ȷ����*/

int TranAmt; /*���׶�,��ȷ����*/

unsigned short UseCardNum; /*�ÿ�����������ǰ*/

unsigned short TerminalNo; /*�ն˱��*/

char PassWord[7]; /*������*/

char Operator[3]; /*����Ա*/

char Abstract[129]; /*ժҪ*/

unsigned int TranJnl; /*������ˮ��*/

unsigned int BackJnl; /*��̨������ˮ��*/

short RetCode; /*��̨������ֵ*/

} CardConsume;

/*��Ƭ�շѵİ�*/

typedef struct

{

char Operator[4]; /*����Ա*/

unsigned int AccountNo; /*�ʺ�*/

unsigned int MercAcc; /*�̻��ʺ�2004-04-28����*/

unsigned int CardNo; /*����*/

unsigned int FeeID; //�շ�ID��

int TranAmt; /*���׶�,��ȷ����*/

char ConsumeType[4]; //�շ�����

char FeeFlag[6]; /*FeeFlag[0]��0_�������� 1_�Զ�����*/

/*FeeFlag[1]��0_У԰������ 1_���п����� 2_�ֽ𽻷� 3_���д��� */

/*FeeFlag[2]��0_�ѽ��� 1_δ���� 2_�Ѷ��� 3_�Ѻ��� 4_������*/

/*FeeFlag[3]: 0_һ�ν��� 1_���ڽ���*/

char FeeDesc[31]; //��������

int CardBalance; /*�����,��ȷ����*/

unsigned short TerminalNo; /*�ն˱��*/

char FeeTerm[11]; /*����ʱ��*/

char BankAcc[21]; /*���п���*/

char Cname[31]; /*����������*/

char IdentityCode[21]; /*���֤��*/

int LateFeeAmt; /*���ɽ�� ��ȷ����*/

int LateFeeRate; /* ���ɽ��� */

char LateFeeStDate[15]; /*���ɽ�������� YYYYMMDD*/

char ExpDate[15]; /* �ؽ�����Ч�� */

char BillNo[51]; /* Ʊ�ݱ�� */

unsigned int TranJnl; /*������ˮ��*/

unsigned int BackJnl; /*��̨������ˮ��*/

short RetCode; /*��̨������ֵ*/

} CardCharge;

/*�ʻ���Ϣ��*/

typedef struct

{

char Name[21]; /*����*/

char SexNo[2]; /*�Ա�*/

char DeptCode[19]; /*���Ŵ���*/

unsigned int CardNo; /*����*/

unsigned int AccountNo; /*�ʺ�*/

char StudentCode[21]; /*ѧ��*/

char IDCard[21]; /*���֤��*/

char PID[3]; /*��ݴ���*/

char IDNo[13]; /*������*/

int Balance; /*�����*/

char Password[7]; /*��������*/

char ExpireDate[7]; /*�˻���ֹ����*/

unsigned short SubSeq; /*������*/

char IsOpenInSys; /*�Ƿ��ڱ�ϵͳ�ڿ�ͨ*/

short TerminalNo; /*�ն˺���*/

short RetCode; /*��̨������ֵ*/

} AccountMsg;

/*��ѯ������ˮ�����ݰ�*/

typedef struct

{

char InqType; /*��ѯ����,0-��ѯ������ˮ;1-��ʷ��ˮ*/

unsigned int Account; /*�ֿ����ʺ�*/

unsigned int MercAcc; /*�̻��ʺ�*/

short TerminalNo; /*�ն˺���*/

char StartTime[15]; /*��ʼʱ��,YYYYMMDDHHMMSS*/

char EndTime[15]; /*����ʱ��,YYYYMMDDHHMMSS*/

char FileName[64]; /*���յ����ļ�����*/

int RecNum; /*��ѯ���ļ�¼��Ŀ*/

}InqTranFlow;

/*��ѯ��ͨ��ˮ*/

typedef struct

{

unsigned int Account; /*�ֿ����ʺ�*/

char FileName[64]; /*���յ����ļ�����*/

int RecNum; /*��ѯ���ļ�¼��Ŀ*/

}InqOpenFlow;


//ģ����ѯʱ���ص���ˮ�ļ���ʽ:

#pragma pack(1) 


/*ģ����ѯ�ʻ���Ϣ��*/
typedef struct
{
	char      		Name[31]; 			/*����*/
	char      		SexNo[2]; 			/*�Ա�*/
	char			DeptCode[19];		/*���Ŵ���*/
	unsigned int	CardNo; 			/*����*/
	unsigned int	AccountNo; 		/*�ʺ�*/
	char			StudentCode[21];	/*ѧ��*/
	char			IDCard[21]; 		/*���֤��*/
	char			PID[3];			/*��ݴ���*/
	char			IDNo[13]; 			/*������*/
	int			Balance; 			/*�����*/
	char			ExpireDate[7];		/*�˻���ֹ����*/
	unsigned int		SubSeq;			/*������*/
}HazyInqAccMsg;


/*��ˮ�ļ��ṹ*/

typedef struct

{

long Account; /*�ʺ�*/

long BackJnl; /*��̨��ˮ��*/

long MercAccount; /*�̻��ʺ�*/

long TerminalNo; /*�ն˱��*/

char OperCode[4]; /*����Ա���*/

char TranCode[3]; /*�¼�����*/

char JnlStatus[2]; /*��ˮ״̬*/

char JnDateTime[15]; /*��ˮ��������ʱ��YYYYMMDDHH24MISS*/

char EffectDate [9]; /*��ˮ��Ч����YYYYMMDD*/

long Balance; /*���*/

long TranAmt; /*���׶�*/

char ConsumeType[4]; /*��������*/

char Resume[129]; /*��ע*/

}TrjnFlowFile;

/*ģ����ѯʱ���صĿ�ͨ��ˮ���ļ��ṹ*/

typedef struct

{

long Account; /*�ʺ�*/

long SysCode; /*��ͨϵͳϵͳ����*/ 

char  SysName[41];    /*��ͨϵͳϵͳ����*/

char OpenDate[15]; /*��ͨ����YYYYMMDDHH24MISS*/

}OpenFlowFile;

#pragma pack()

#endif
