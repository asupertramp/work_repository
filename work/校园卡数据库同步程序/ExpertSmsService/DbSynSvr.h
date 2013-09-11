/********************************************************************
	created:	2007/05/10
	created:	10:5:2007   10:36
	filename: 	d:\Works\ExpertSmsSvr\ExpertSmsService\ExpertSelSvr.h
	file path:	d:\Works\ExpertSmsSvr\ExpertSmsService
	file base:	ExpertSelSvr
	file ext:	h
	author:		�Ź���
	
	purpose:	�Ž�ϵͳ����
*********************************************************************/

#pragma once
#include <afx.h>
#include <vector>
#include <list>
#include "..\ComFiles\PubDefine.h"
#include "..\ComFiles\LogForMe.h"
#include "..\ComFiles\ExecParam.h"
#import "c:\Program Files\Common Files\System\ADO\msado15.dll" \
	no_namespace rename("EOF", "EndOfFile")



using namespace std;

//Ĭ�ϲ����ļ���
//const CString strFileName = "ExpertSms.ini";

class CDbSynSvr
{
private:

 
    list<ACCOUNT_MSG> vMsg;
	
	//�����߳̾��
	HANDLE m_hThread;
	//��������߳��˳��¼�
	HANDLE m_hEvtExit;

	DBCON_PARAM DBConParam;

	//�������
	UINT m_nCheckPeriod;
	//��Ч����ʱ��(�ൽ��ʱ��Сʱ��)
	UINT m_nValidTime;

	UINT m_nWaitAnswer;


	//���ݿ�����
	_ConnectionPtr	m_pConnection;

	CString m_strFlowFile;
	CString m_strControlFile;
	CString m_strListFile;
	CString m_strBranchMapFile;
	CString m_strModulePath;
	CString m_strBlackPath;
	CString m_strDbPath;

public:
	CDbSynSvr(void);
	~CDbSynSvr(void);

	CExecParam m_Params;


	
private:
	//����Ƿ�����ʱ���Ƿ��Ѿ�����
	bool CheckTimeValid(COleDateTime tAtt);
	//�����߳���ں���
	static DWORD WINAPI ThreadFunction(LPVOID param);
	//��ȡ���ز���
	bool GetLocalParam(void);
	//���m_gateID��ȡ����
	void ClearSelectVar();
	//�������ݿ�
	bool Connect(void);
	//�Ͽ����ݿ�����
	void CloseConnect(void);
	
	//��ѯ���ݿ���guestmember�����Ƿ����¼������Ա���еĻ�����Ҫ��д���ſ����ŷ���m_gateID
	bool CheckNewBList();
    //��ѯ�Ƿ��д�ɾ����Ա���еĻ�


	//��DISPATH�ӿڷ�װ��׼���·�
	bool Download();
	
	//������
	DWORD DbSynSvrFun();

	//���·�����guestmenber���е���Ա״̬��Ϊ2
	void ResetStatus( CString strID, INT status );
   
	//�����ʱ��
    void ImportControlBin();

    bool ImportMemberList();	
	

public:
	//���������߳�
	bool Init(void);
	//�ر�����߳�,�����ڴ��
	void Destroy(void);
};
