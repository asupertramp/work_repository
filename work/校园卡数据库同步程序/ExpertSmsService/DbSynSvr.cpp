#include "stdafx.h"
#include "DbSynSvr.h"
#include <time.h>
#include "CSMSClient2000.h"
#include "..\Comfiles\comutils.h"

#include "..\Comfiles\CardControl.h"
#include "..\Comfiles\CardDef.h"
#include "..\Comfiles\LogForMe.h"
#include <afxtempl.h>



inline void TESTHR(HRESULT x) {if FAILED(x) _com_issue_error(x);};

CDbSynSvr::CDbSynSvr(void)
{

	//�����߳̾��
	m_hThread = INVALID_HANDLE_VALUE;
	//��������߳��˳��¼�
	m_hEvtExit = INVALID_HANDLE_VALUE;

	//���ݿ����Ӳ���
	memset(&DBConParam, 0, sizeof(DBConParam));
	//���ݿ�����
	m_pConnection = NULL;

	m_nCheckPeriod = 60;
	m_nValidTime = 24;


	
	
}

CDbSynSvr::~CDbSynSvr(void)
{   

}

void CDbSynSvr::ClearSelectVar()
{

	
}
	


/********************************************************************
purpose:    	��ʼ�������߳�
Parameters:		
Return Value:
*********************************************************************/
bool CDbSynSvr::Init()
{

	m_Params.InitParam();
	bool bProxyOff;
	ULONG MaxJnl;
	if (!TA_Init(m_Params.params.ProxyAddr, m_Params.params.ProxyPort, m_Params.params.SysCode, m_Params.params.TerNo,
		&bProxyOff, &MaxJnl)){
			DebugLog("��ʼ��ʧ��,��رճ��򣬼�����!");
			PrintDebugLog("����TA_Init���г�ʼ��ʧ��,IP:%s, Port:%d, SysCode:%d, TerminalNo:%d",
				m_Params.params.ProxyAddr, m_Params.params.ProxyPort, m_Params.params.SysCode, m_Params.params.TerNo);
			FiniLogFile();
			return false;
			//while (1)
			//{
			//	Sleep(1000);
			//}

		}
		if (bProxyOff) {
			DebugLog("�������ѻ�״̬!");
			DebugLog("�������ѻ�״̬!");
		}
		DebugLog("����TA_Init��ʼ��SIOS��������ɹ�");


		char filepath[255];
		memset(filepath,0,255);
		::GetModuleFileName(NULL, filepath, 255);
		CString strModuleName = filepath;
		int nPos = strModuleName.ReverseFind('\\');
		if (nPos == -1) {
			return 0;
		}
		m_strModulePath = strModuleName.Left(nPos+1); 
		m_strListFile =  m_strModulePath + "Memberlist.dat";
		m_strControlFile = m_strModulePath + "Control.dat";


		m_strDbPath.Format("%s", m_Params.params.DBName);
		m_strBlackPath.Format("%s", m_Params.params.BLName);

	if (!GetLocalParam()) {
		ErrorLog("��ȡ����ʧ��,��������ļ�");
		return false;
	}
	m_hEvtExit = CreateEvent(NULL, false, false, NULL);
	DWORD dwTheadId;
	m_hThread = CreateThread(NULL, 0, ThreadFunction, this, 0, &dwTheadId);
	if (m_hThread == INVALID_HANDLE_VALUE)
	{
		SysErrLog("���������߳�ʧ��!");
		CloseHandle(m_hEvtExit);
		return false;
	}
	return true;
}

/********************************************************************
purpose:    	�رշ����߳�
Parameters:		
Return Value:
*********************************************************************/
void CDbSynSvr::Destroy()
{
	SetEvent(m_hEvtExit);
	if (WaitForSingleObject(m_hThread, 5000) == WAIT_TIMEOUT)
	{
		ErrorLog("�ر�ר�ҳ�ȡ�����߳�ʧ��,ǿ�йر�!");
		TerminateThread(m_hThread, -1);
	}
	CloseHandle(m_hThread);
	CloseHandle(m_hEvtExit);
}

/********************************************************************
purpose:    	�߳���ں���
Parameters:		
Return Value:
*********************************************************************/
DWORD WINAPI CDbSynSvr::ThreadFunction(LPVOID param)
{
	CDbSynSvr *pThis = (CDbSynSvr*)param;
	return pThis->DbSynSvrFun();
}


/********************************************************************
purpose:  ������
Parameters:		
Return Value:
*********************************************************************/
DWORD CDbSynSvr::DbSynSvrFun()
{
	CoInitialize(NULL);
	CString strMsg1,strMsg2;
	CString strtemp;

   

	while (WaitForSingleObject(m_hEvtExit, m_nCheckPeriod*1000)==WAIT_TIMEOUT){
		//��ȡ����
		GetLocalParam();
    

        if(!Download())
		{
		  continue;
		}
		ImportControlBin();
		ImportMemberList();
        CheckNewBList();



		EventLog("                                      ");
		EventLog("**************************************");
		EventLog("          ��⵽����Ա����          ");
		EventLog("**************************************");

	
	}
	CoUninitialize();
    return 0;
}



/********************************************************************
purpose:    	������ݿ����޸��£��ɼ��б仯���ſ����ŷ�������m_gateID��
Parameters:		
Return Value:
*********************************************************************/
bool CDbSynSvr::CheckNewBList()
{
    
	CString strBlack = "newblist.bin";

	CString strBFile = m_strBlackPath + strBlack;
	CString strBTempFile = m_strBlackPath + "Temp.bin";
    
	PrintTraceLog(m_strBlackPath);
	PrintTraceLog("�������ļ�%s", strBFile);

	WIN32_FIND_DATA FileData;
	HANDLE hSearch;
	hSearch = FindFirstFile(strBFile, &FileData); 
	if (hSearch == INVALID_HANDLE_VALUE) 
	{ 
		EventLog("δ�ҵ�%s�ļ�,����ͬ��", strBFile); 
		return 1;
	}	 

	if (FileData.nFileSizeHigh == 0 && FileData.nFileSizeLow == 0) {
		EventLog("newblist.bin�ļ�����Ϊ0,����ͬ��"); 
		return 1;
	}


	if (MoveFile(strBFile, strBTempFile) == FALSE) {
		EventLog("�޷��ƶ�newblist.bin�ļ�,�ļ���ռ��");
	}

	//���ļ�,��������
	//CArray<ACCOUNT_MSG, ACCOUNT_MSG> lstAccount;		


	FILE *stream;
	char line[100];
	try
	{
		if ((stream = fopen(strBTempFile, "r" )) == NULL)
		{
			ErrorLog("�޷�����ʱ�ļ�!");
			return 1;
		}

		while(fgets( line, 100, stream ) != NULL)
		{
			if(strlen(line) == 0)
			{
				TraceLog("0����");
				continue;
			}
			PrintTraceLog("line:%s", line);
			CString strline(line);

			ACCOUNT_MSG amsg={0};
			amsg.ID = strline.Left(strline.Find(' '));
			strline.Delete(0, strline.Find(' ') + 1);
			PrintDebugLog("amsg.ID:%s, strline:%s", amsg.ID, strline);


			amsg.CardID = strline.Left(strline.Find(' '));
			strline.Delete(0, strline.Find(' ') + 1);
			PrintDebugLog("amsg.ID:%s, strline:%s", amsg.CardID, strline);
		    PrintDebugLog("strline.Left(5): %s", strline.Left(5));
			//if (strline.Left(5) == "1 0 0") {
				//����
			//	amsg.status = 1;
			//	PrintTraceLog("acc:%s,status:%d",amsg.ID,amsg.status);
			//}else 
			if (strline.Left(5) == "1 0 0"){
                continue;
			}else if (strline.Left(5) == "0 1 0"){
				//��ʧ
				amsg.status = 1;
				PrintDebugLog("acc_ID(accountno):%s,status:%d",amsg.ID,amsg.status);
			}else if (strline.Left(5) == "0 0 0"){
				strline.Delete(0, 8);
				strline.Delete(0, strline.Find(' ') + 1);
				if (strline.Left(1) == "0")
				{
					amsg.status = 2;//����
					PrintDebugLog("acc:%s,status:%d",amsg.ID,amsg.status);
				} 
				else if (strline.Left(1) == "1")
				{
					amsg.status = 3;//ɾ��
					PrintDebugLog("acc:%s,status:%d",amsg.ID,amsg.status);
				} 
				else if (strline.Left(1) == "2" )
				{
					amsg.status = 0; //�����ⶳ���
					PrintDebugLog("acc:%s,status:%d",amsg.ID,amsg.status);
				}
			
			}
			vMsg.push_front(amsg);
		}
		fclose( stream );						
	}	
	catch (...) {
		ErrorLog("�����쳣!");
		fclose(stream);
	}
	DeleteFile(strBTempFile);

	PrintDebugLog("������%d���ʻ��䶯��Ϣ",vMsg.size() );
	int j= vMsg.size();

	for (int i = 0; i<j ; i++) {
		
			//ResetStatus(vMsg.back().ID,vMsg.back().status);

	    if(!Connect())
		{
		 DebugLog("�����ݿ����!");
		 return 0;
		}

		try{
			_CommandPtr pCmdChange  = NULL;
			_RecordsetPtr	pRst  = NULL;
			char strSql[512];
			TESTHR(pRst.CreateInstance(__uuidof(Recordset)));
			TESTHR(pCmdChange.CreateInstance(__uuidof(Command)));
			pCmdChange->ActiveConnection = m_pConnection;

			//
				_CommandPtr	cm("ADODB.Command");
			char strSql1[512];	
			try
			{	

				sprintf(strSql1, "use Gsccsserver");
				cm->CommandText = strSql1;
				cm->CommandType = adCmdText;
				cm->ActiveConnection = m_pConnection;
				cm->Execute(0,NULL, adExecuteNoRecords);

			}
			catch (_com_error &e) {
				PrintErrorLog("ImportMemberList()����ʱ�����쳣,�쳣��Ϣ:%s", e.ErrorMessage());

			}
			catch (...) {
				ErrorLog("ImportMemberList()δ֪�쳣");
			}
			//
			CString CaNo = 0;
			UINT FLG = 0;
			sprintf(strSql, "select * from users where AccountNo = '%s'", vMsg.back().ID);
			TraceLog(strSql);
			pRst->Open(strSql, _variant_t((IDispatch *)m_pConnection,true), 
				adOpenStatic, adLockReadOnly, adCmdText);
			if (!pRst->EndOfFile) {
				//������ԱSQL
				switch(vMsg.back().status)
				{
				case 0://�������һ�ⶳ
					CaNo = pRst->Fields->Item["CardNo"]->Value;
	                FLG   = pRst->Fields->Item["Flag"]->Value;
					sprintf(strSql, "vMsg.back().ID= '%s'", vMsg.back().CardID);
					TraceLog(strSql);
					if( CaNo != vMsg.back().CardID )
					{sprintf(strSql, "Update users set CardNo  = '%s', Flag = 0 ,Curstate = 1 where AccountNo ='%s'" ,vMsg.back().CardID ,vMsg.back().ID);}
					else if (FLG == 1)
										{sprintf(strSql, "Update users set CardNo  = '%s', Flag = 0 ,Curstate = 1 where AccountNo ='%s'" ,vMsg.back().CardID ,vMsg.back().ID);}
					else{
						sprintf(strSql, " ");}
					break;
				case 1://��ʧ
					sprintf(strSql, "Update users set Flag = 1 ,Curstate = 1 where accountno = '%s'",vMsg.back().ID);
					break;
				case 2://����
					//sprintf(strSql, "Update users set Flag = 2 ,Curstate = 1 where accountno = '%s'",vMsg.back().ID);
					sprintf(strSql, " " ); 
					break;
				case 3://ɾ��
					sprintf(strSql, "Update users set Flag = 3 ,Curstate = 1 where accountno = '%s'",vMsg.back().ID);
					break;

				default:
					break;
				}

				TraceLog(strSql);
				pCmdChange->CommandText = strSql;				
				pCmdChange->Execute(NULL, NULL, adCmdText);
			}	
			pRst->Close();	

		}catch(_com_error err){
			PrintSysErrLog("������Ա�б��̳߳���:%s", err.ErrorMessage());
		}

		CloseConnect();	


			//sprintf("id:%s,status:%d", vMsg.back().ID, vMsg.back().status );
			vMsg.pop_back();

	}
	vMsg.clear();
	return 0;
}

/********************************************************************
purpose: ����ʱ�����
Parameters:		
Return Value:
*********************************************************************/
/**void CDbSynSvr::ResetStatus( CString strID, INT status )
{
	if(!Connect())
		DebugLog("�����ݿ����!");
		return;

	try{
		_CommandPtr pCmdChange  = NULL;
		_RecordsetPtr	pRst  = NULL;
		char strSql[512];
		TESTHR(pRst.CreateInstance(__uuidof(Recordset)));
		TESTHR(pCmdChange.CreateInstance(__uuidof(Command)));
		pCmdChange->ActiveConnection = m_pConnection;



		sprintf(strSql, "select * from users where AccountNo = '%s'", strID);
		TraceLog(strSql);
		pRst->Open(strSql, _variant_t((IDispatch *)m_pConnection,true), 
			adOpenStatic, adLockReadOnly, adCmdText);
		if (!pRst->EndOfFile) {
			//������ԱSQL
			switch(status)
			{
			case 0:
			    sprintf(strSql, "Update users set flag = 0 where accountno = '%s' Update users set InUse = 0 where accountno ='%s'",strID,strID);
				break;
			case 1:
			    sprintf(strSql, "Update users set InUse = 1 where accountno = '%s'",strID);
				break;
			case 2:
			    sprintf(strSql, "Update users set flag = 1 where accountno = '%s'",strID);
			    break;
			case 3:
				sprintf(strSql, "Update users set flag = 3 where accountno = '%s'",strID);
			    break;
			case 4:
				sprintf(strSql, "Update users set flag = 2 where accountno = '%s'",strID);
				break;
			default:
			    break;
			}
			
			TraceLog(strSql);
			pCmdChange->CommandText = strSql;				
			pCmdChange->Execute(NULL, NULL, adCmdText);
		}	
		pRst->Close();	



	//}catch(CException err){
	//	TCHAR   szCause[255];
	//	err.GetErrorMessage(szCause, 255);
	//	PrintSysErrLog("������Ա�б��̳߳���:%s", szCause);
	}catch(_com_error err){
		PrintSysErrLog("������Ա�б��̳߳���:%s", err.ErrorMessage());
	}

	return ;
	CloseConnect();	
}



*/

	/********************************************************************
	purpose: ���ÿһ����Ҫ���µ��ſ����������Ӧ��DISPATH�ṹ���װ�ã�׼���·�
	Parameters:		
	Return Value:
	*********************************************************************/
	bool CDbSynSvr::Download()
	{

			EventLog("��ʼ������Ա�б�,���Ե�...");
		    
			int nRecNum ;
			char chFn[64] = {0};
            AccountMsg am = {0};
			int nResult = TA_HazyInqAcc(&am , &nRecNum , chFn, 600);
			CString strMsg;
			if (nResult == ERR_OK) {
				strMsg.Format("������Ա�б�ɹ�!�����ؼ�¼%d��", nRecNum);	
				CString strDest = m_strModulePath+"RecvTemp\\" + chFn;
				PrintDebugLog(strDest);
				CopyFile(strDest, m_strListFile, FALSE);
				DeleteFile(strDest);

			}else{	
				strMsg.Format("������Ա�б�ʧ��!����(%d)",nResult);
				DebugLog(strMsg);
				return false;
			}

		

      
		EventLog("         ��ʼ���ؿ��Ʋ���,���Ե�...         ");
	    nResult = TA_DownControlFile();
		if (nResult>0) {
			CString strDest = m_strModulePath+"ControlFile\\Control.bin";
			EventLog(strDest);
			CopyFile(strDest, m_strControlFile, FALSE);
			DeleteFile(strDest);
			strMsg.Format("���ؿ��Ʋ�������!����ֵ(%d)",nResult);	
			EventLog(strMsg);
			return true;
		}else{
			strMsg.Format("���ؿ��Ʋ���ʧ��!����(%d)",nResult);
			DebugLog(strMsg);
			return false;

		}


	}


/********************************************************************
purpose:   �ϵ�ʱ�����ʱ�����Ƿ���δ�·���ɵļ�¼������װ��m_gateID����������ѭ��
Parameters:		
Return Value:
*********************************************************************/
void CDbSynSvr::ImportControlBin()
{   

	if(!Connect()) return ;
	_RecordsetPtr pRst=NULL;
//
	char strSql[512];
	char strSql1[512];
	_CommandPtr	cm("ADODB.Command");
	try
	{	

		sprintf(strSql, "use Gsccsserver");
		cm->CommandText = strSql;
		cm->CommandType = adCmdText;
		cm->ActiveConnection = m_pConnection;
		cm->Execute(0,NULL, adExecuteNoRecords);
		TraceLog(strSql);

	}
	catch (_com_error &e) {
		PrintErrorLog("ImportControlBin()����ʱ�����쳣,�쳣��Ϣ:%s", e.ErrorMessage());

	}
	catch (...) {
		ErrorLog("ImportControlBin()δ֪�쳣");
	}

	
   // 

	CFile f;
	CFileException ex;
	if (!f.Open(m_strControlFile, CFile::modeRead, &ex)){		
		TCHAR szError[1024];
		ex.GetErrorMessage(szError, 1024);		
		PrintSysErrLog("�����ļ�(Name:%s)�򿪴���:%s", m_strControlFile, szError);
		return ;
	}

	try{
		_CommandPtr pCmdChange  = NULL;
		_RecordsetPtr	pRst  = NULL;
		char strSql[512];
		TESTHR(pRst.CreateInstance(__uuidof(Recordset)));
		TESTHR(pCmdChange.CreateInstance(__uuidof(Command)));
		pCmdChange->ActiveConnection =m_pConnection;		

		char fileId[8];
		struct tabCtrlHead head;
		struct t_department depart;
		struct t_area area;
		if (f.Read(fileId, 8) != 8)
		{
			throw new CFileException();
		}
		if(memcmp(fileId, CONTROL_STR, 8) !=0)
		{
			throw new CFileException();
		}
		//���벿�Ŵ���
		f.Seek(8+sizeof(head)*OFFSET_T_DEPARTMENT , CFile::begin);
		if(f.Read(&head, sizeof(head)) != sizeof(head))
		{
			throw new CFileException();
		}
		if(head.structlength != sizeof(depart)){
			throw new CFileException();
		}
		f.Seek(head.offset, CFile::begin);	
		int nCurCount = 0;
		int nTotalCount = head.count;

		while(WaitForSingleObject(m_hEvtExit,0) == WAIT_TIMEOUT)
		{
			if (f.Read(&depart, sizeof(depart)) != sizeof(depart)) {
				throw new CFileException();
			}
			sprintf(strSql, "select * from department where dept_code = 'A%s%s'", depart.area_code, depart.dept_code);
			pRst->Open(strSql, _variant_t((IDispatch *)m_pConnection,true), 
				adOpenStatic, adLockReadOnly, adCmdText);
			if (pRst->EndOfFile) {
				//��������SQL���
				sprintf(strSql, "insert into department(dept_code, dept_name , area_code, dept_flag, curstate)"
					" values('A%s%s','%s', 'A%s','1', '1')",
					depart.area_code, depart.dept_code, depart.dept_name, depart.area_code);
				PrintDebugLog(strSql);
				pCmdChange->CommandText = strSql;				
				pCmdChange->Execute(NULL, NULL, adCmdText);
			}
			pRst->Close();
			nCurCount++;			
            if(nCurCount == nTotalCount)
			break;
		    if(nCurCount % 100 ==0)
			{ sprintf(strSql1, "���м�¼%d��,�����%d��", nTotalCount,nCurCount);
			  PrintDebugLog(strSql1);
			}
				//pThis->PostMessage(WM_SETPOS, nCurCount, nTotalCount);
			//CString strState;
			//strState.Format("���м�¼%d��,�����%d��", nTotalCount,nCurCount);
			//DebugLog(strState);
		}


		//����У������
		f.Seek(8+sizeof(head)*OFFSET_T_AREA , CFile::begin);
		if(f.Read(&head, sizeof(head)) != sizeof(head))
		{
			throw new CFileException();
		}
		if(head.structlength != sizeof(area)){
			throw new CFileException();
		}
		f.Seek(head.offset, CFile::begin);		
		nCurCount = 0;
		nTotalCount = head.count;
		while(WaitForSingleObject(m_hEvtExit,0) == WAIT_TIMEOUT)
		{
			if (f.Read(&area, sizeof(area)) != sizeof(area)) {
				throw new CFileException();
			}
			sprintf(strSql, "select * from department where area_code = 'A%s'", area.area_code);
			pRst->Open(strSql, _variant_t((IDispatch *)m_pConnection,true), 
				adOpenStatic, adLockReadOnly, adCmdText);
			if (!pRst->EndOfFile) {
				//��������SQL���
				sprintf(strSql, "update department set area_name= '%s' where area_code = 'A%s'",
					area.area_name, area.area_code);
				PrintDebugLog(strSql);
				pCmdChange->CommandText = strSql;				
				pCmdChange->Execute(NULL, NULL, adCmdText);
			}
			pRst->Close();
			nCurCount++;			
			if(nCurCount == nTotalCount)
				break;
			if(nCurCount % 100 ==0)
			{sprintf(strSql1, "���м�¼%d��,�����%d��", nTotalCount,nCurCount);
			 TraceLog(strSql1);}


				//pThis->PostMessage(WM_SETPOS, nCurCount, nTotalCount);	
		}
		//pThis->PostMessage(WM_SETPOS, nCurCount, nTotalCount);

	//}catch(CFileException err){
	//	TCHAR   szCause[255];
	//	err.GetErrorMessage(szCause, 255);
	//	PrintSysErrLog("��������̳߳���:%s", szCause);
	}catch(_com_error err){
		PrintSysErrLog("������Ա�б��̳߳���:%s", err.ErrorMessage());
	}	
	//pThis->PostMessage(WM_SETPOS, 0, 0);
	f.Close();
	CloseConnect();
	return ;
	


}


/********************************************************************
purpose:    	�����������������ʱ��troommember_backup,�����������·�����������
Parameters:		
Return Value:
*********************************************************************/
bool CDbSynSvr::ImportMemberList()
{
	if(!Connect())
		return false;


	_CommandPtr	cm("ADODB.Command");
//
	char strSql[512];
	char strSql1[512];	
	try
	{	

		sprintf(strSql, "use Gsccsserver");
		cm->CommandText = strSql;
		cm->CommandType = adCmdText;
		cm->ActiveConnection = m_pConnection;
		cm->Execute(0,NULL, adExecuteNoRecords);

	}
	catch (_com_error &e) {
		PrintErrorLog("ImportMemberList()����ʱ�����쳣,�쳣��Ϣ:%s", e.ErrorMessage());

	}
	catch (...) {
		ErrorLog("ImportMemberList()δ֪�쳣");
	}

//	


	CFile f;
	CFileException ex;
	if (!f.Open(m_strListFile, CFile::modeRead, &ex)){		
		TCHAR szError[1024];
		//ex.GetErrorMessage(szError, 1024);		
		PrintSysErrLog("��Ա�б��ļ�(Name:%s)�򿪴���:%s", m_strListFile, szError);
		return 1;
	}
	try{
		_CommandPtr pCmdChange  = NULL;
		_RecordsetPtr	pRst  = NULL;
		char strSql[512];
		HazyInqAccMsg accmsg;
		TESTHR(pRst.CreateInstance(__uuidof(Recordset)));
		TESTHR(pCmdChange.CreateInstance(__uuidof(Command)));
		pCmdChange->ActiveConnection = m_pConnection;

		int nCurCount = 0;
		int nTotalCount = f.GetLength() / sizeof(HazyInqAccMsg);
		while(WaitForSingleObject(m_hEvtExit,0) == WAIT_TIMEOUT)
		{
			UINT nCount = f.Read(&accmsg, sizeof(HazyInqAccMsg));
			if (nCount != sizeof(HazyInqAccMsg)) {
				break;
			}
			sprintf(strSql, "select * from users where AccountNo = '%d' ", accmsg.AccountNo);
			pRst->Open(strSql, _variant_t((IDispatch *)m_pConnection,true), 
				adOpenStatic, adLockReadOnly, adCmdText);
			if (pRst->EndOfFile) {
				//������ԱSQL
                    sprintf(strSql, "insert into users(AccountNo, Name, CardNo, DeptCode, StudentCode, IDCard, SexNo,Flag,curstate)"
					" values('%d','%s','%u','A%s','%s','%s','%s','2' ,'1') ",
					accmsg.AccountNo, accmsg.Name, accmsg.CardNo, accmsg.DeptCode, accmsg.StudentCode, accmsg.IDCard, accmsg.SexNo);
				    PrintDebugLog(strSql);
				    pCmdChange->CommandText = strSql;				
				    pCmdChange->Execute(NULL, NULL, adCmdText);

			 }
			pRst->Close();
			nCurCount++;
				
			if(nCurCount == nTotalCount)
				break;
            if(nCurCount % 1000 == 0 )
			{sprintf(strSql1, "���м�¼�ı�%d��,����ɸ���%d��", nTotalCount,nCurCount);
			 PrintDebugLog(strSql1);
			}
			//	pThis->PostMessage(WM_SETPOS, nCurCount, nTotalCount);
		}		
		//pThis->PostMessage(WM_SETPOS, nCurCount, nTotalCount);
	}catch(_com_error err){
		PrintSysErrLog("������Ա�б��̳߳���:%s", err.ErrorMessage());
	}
	//pThis->PostMessage(WM_SETPOS, 0, 0);
	f.Close();
	CloseConnect();
	return 0;
}


//�������ݿ�
bool CDbSynSvr::Connect(void)     
{
	if (m_pConnection)
	{
		return true;
	}
	char constr[512];
	sprintf(constr, "Provider=%s;Persist Security Info=False;Data Source=%s;"
		"User ID=%s;Password=%s;PLSQLRSet=1",DBConParam.DRIVER,	
		DBConParam.DSN, DBConParam.USER, DBConParam.PASS);
	
	
	PrintDebugLog("���ݿ������ַ���%s",constr);

	try
	{
		TESTHR(m_pConnection.CreateInstance(__uuidof(Connection)));
		m_pConnection->CursorLocation = adUseServer;
		m_pConnection->Open(constr,"","",adModeUnknown);
	}
	catch (_com_error &e) {
		PrintErrorLog("CDbSynSvr���ݿ������쳣,�쳣��Ϣ:%s", e.ErrorMessage());	
		m_pConnection.Release();
		return false;
	}
	catch (...) {
		ErrorLog("CDbSynSvr���ݿ�����δ֪�쳣");
		return false;
	}
	EventLog("CDbSynSvr���ݿ����ӳɹ�");
	return true;
}
//�Ͽ����ݿ�����
void CDbSynSvr::CloseConnect(void)
{
	m_pConnection->Close();
	m_pConnection = NULL;
}

//��ȡ���ز���
bool CDbSynSvr::GetLocalParam(void)
{


	char filepath[255];
	memset(filepath,0,255);
	::GetModuleFileName(NULL, filepath, 255);
	string strParamFileName = filepath;
	string::size_type nPos = strParamFileName.rfind("\\");
	if (nPos == (string::size_type)-1) {
		return false;
	}
	strParamFileName.resize(++nPos);
	//strParamFileName += strFileName;
	strParamFileName += "DbSyn.ini";
	PrintDebugLog("�����ļ�:%s", strParamFileName.c_str());	
	GetPrivateProfileString("DBPARAM", "DRIVER", "SQL Server", DBConParam.DRIVER,
		sizeof(DBConParam.DRIVER),strParamFileName.c_str());	
	GetPrivateProfileString("DBPARAM", "DSN", "EXPERTSELECT", DBConParam.DSN,
		sizeof(DBConParam.DSN),strParamFileName.c_str());	
	GetPrivateProfileString("DBPARAM", "USER", "root", DBConParam.USER,
		sizeof(DBConParam.USER),strParamFileName.c_str());
	GetPrivateProfileString("DBPARAM", "PWD", "poot", DBConParam.PASS,
		sizeof(DBConParam.PASS),strParamFileName.c_str());

	m_nCheckPeriod = GetPrivateProfileInt("RUNPARAM", "CHECKPERIOD", 60, 
		strParamFileName.c_str());	
	m_nValidTime = GetPrivateProfileInt("RUNPARAM", "VALIDTIME", 48, 
		strParamFileName.c_str());
	m_nWaitAnswer = GetPrivateProfileInt("RUNPARAM", "WAITTIME", 15, 
		strParamFileName.c_str());

	//CString strParam;
	//strParam.Format("�����������(��)|%d|������С��Чʱ��(Сʱ)|%d|�ȴ����Żظ�ʱ��(����)|%d|",
		//m_nCheckPeriod, m_nValidTime, m_nWaitAnswer);
	//WriteMailSlot("\\\\.\\mailslot\\ExpertSMSMonitor_Param", strParam);	


	//m_Com.nComNo = GetPrivateProfileInt("COMPARAM", "ComPort", 1, strParamFileName.c_str());
	//m_Com.nBaudrate = GetPrivateProfileInt("COMPARAM", "Baudrate", 9600, strParamFileName.c_str());
	return true;
}






