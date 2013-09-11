// ExecParam.h: interface for the CExecParam class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXECPARAM_H__6F332CFD_A5BB_46BD_8A0E_24371E19491B__INCLUDED_)
#define AFX_EXECPARAM_H__6F332CFD_A5BB_46BD_8A0E_24371E19491B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//Ĭ�ϲ����ļ���
const CString strFileName = "Interface.ini";

//���в�������
typedef struct _Paramter_Exec{
	char ProxyAddr[16];			//�����ַ
	UINT ProxyPort;			//����˿�
	UINT SysCode;		//��ϵͳ����
	UINT TerNo;		//�ն˺�	
	char DBName[256];	//���ݿ��ļ���ַ
	char BLName[256];	//�������ļ���ַ
}PARAM_EXEC;


/************************************************************************/
//���в���������
/************************************************************************/
class CExecParam
{
public:
	CExecParam(void);
	~CExecParam(void);
public:
	//���в���
	PARAM_EXEC params;
	//�����ļ���(��·��)
	CString strParamFileName;
public:
	bool GetLocalParam(void);
	bool SaveParamToLocal(void);
	bool InitParam(void);
};


#endif // !defined(AFX_EXECPARAM_H__6F332CFD_A5BB_46BD_8A0E_24371E19491B__INCLUDED_)
